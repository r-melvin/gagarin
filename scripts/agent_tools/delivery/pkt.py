#!/usr/bin/env python3
"""pkt.py: one command for a matching worker, from an empty shell to a linted READY packet.

    pkt.py budget                         memory/worktree/compiler-load budget (refuses when over)
    pkt.py init NAME [--base REV] [--reuse]        scratch worktree + toolchain link + READY skeleton + env file
    pkt.py span ADDR...                   CFG-closed span, manifest/claim status, Ghidra size, for each address
    pkt.py score TU [ADDR...]             compile TU, score every body claim (raw_match, else diff_retail %)
    pkt.py bind                           strict verify_relocations on every exact row; derive bindings; write map
    pkt.py finish                         results.tsv, manifest_delta.json, README skeleton, base_sha, inc gates,
                                          pktlint; then backs READY up to <backups>/int-evidence/NAME/ (GAG_BACKUPS)
    pkt.py done                           remove the worktree (after the backup exists)

All state lives in $PKT_DIR (default <scratch root>/<NAME>, the scratch root being ../gagarin-scratch next to the main checkout, written by
init into ./pkt.env); the worktree is $PKT_DIR/wt. Rows the worker claims are listed in
$PKT_DIR/READY/rows.tsv (addr<TAB>sym<TAB>len[<TAB>name]); `score` fills sym/len when it can
(FUN_<addr> symbols, CFG spans). Nothing here touches the main checkout, pushes, stashes or
uses `git add -A`.
"""
import argparse
import csv
import json
import os
import re
import shutil
import subprocess
import sys
import time

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import dlib as D  # noqa: E402
import landlib as L  # noqa: E402

HERE = os.path.dirname(os.path.abspath(__file__))
SCRATCH_ROOT = os.path.dirname(D.SCRATCH)       # ../gagarin-scratch next to the main checkout
BUDGET = dict(min_free_gb=float(os.environ.get("PKT_MIN_FREE_GB", "6")), max_swap_pct=80,
              max_worktrees=int(os.environ.get("PKT_MAX_WORKTREES", "8")), max_cl=int(os.environ.get("PKT_MAX_CL", "24")))


def say(*a):
    print(*a, flush=True)


def env_file():
    return os.path.join(os.getcwd(), "pkt.env")


def load_env():
    e = {}
    for cand in (os.environ.get("PKT_ENV"), env_file()):
        if cand and os.path.isfile(cand):
            for ln in open(cand):
                if "=" in ln and not ln.startswith("#"):
                    k, v = ln.rstrip("\n").split("=", 1)
                    e[k] = v
            break
    if "PKT_DIR" in os.environ:
        e["PKT_DIR"] = os.environ["PKT_DIR"]
    if "PKT_DIR" not in e:
        raise SystemExit("no pkt.env here and PKT_DIR unset: run `pkt.py init NAME` first (or cd to its dir)")
    e.setdefault("WT", os.path.join(e["PKT_DIR"], "wt"))
    e.setdefault("READY", os.path.join(e["PKT_DIR"], "READY"))
    e.setdefault("OBJ", os.path.join(e["PKT_DIR"], "obj"))
    e.setdefault("NAME", os.path.basename(e["PKT_DIR"]))
    return e


# ---------------------------------------------------------------- budget
def budget(verbose=True):
    """Memory, swap, worktree and compiler-process budget. Returns (ok, lines)."""
    mem = {}
    for ln in open("/proc/meminfo"):
        k, v = ln.split(":")
        mem[k] = int(v.split()[0]) * 1024
    free_gb = mem.get("MemAvailable", 0) / 2**30
    swap_total, swap_free = mem.get("SwapTotal", 0), mem.get("SwapFree", 0)
    swap_pct = 100.0 * (swap_total - swap_free) / swap_total if swap_total else 0.0
    wts = [l.split()[0] for l in L.git(D.MAIN_REPO, "worktree", "list").splitlines()]
    ours = [w for w in wts if D.created_by_us(w)]                       # this tool family's own worktrees
    others = [w for w in wts if w.startswith((SCRATCH_ROOT, "/tmp/")) and w not in ours]
    ps = subprocess.run(["ps", "-eo", "comm="], capture_output=True, text=True).stdout.lower()
    ncl = sum(1 for l in ps.splitlines() if l.strip() in ("cl.exe", "wine-preloader", "wine64-preloader") or l.strip().startswith("cl.exe"))
    load1 = os.getloadavg()[0]
    checks = [(free_gb >= BUDGET["min_free_gb"], "memory available %.1f GB (floor %.0f GB)" % (free_gb, BUDGET["min_free_gb"])),
              (swap_pct <= BUDGET["max_swap_pct"], "swap used %.0f%% (ceiling %d%%)" % (swap_pct, BUDGET["max_swap_pct"])),
              (len(ours) < BUDGET["max_worktrees"], "own worktrees %d (ceiling %d); other agents' scratch/tmp worktrees: %d" % (len(ours), BUDGET["max_worktrees"], len(others))),
              (ncl <= BUDGET["max_cl"], "compiler processes %d (ceiling %d), load %.1f, jobs cap %d" % (ncl, BUDGET["max_cl"], load1, D.MAX_JOBS)),
              (True, "scratch disk: %s (RAM-backed /tmp is not used)" % D.SCRATCH)]
    ok = all(c for c, _ in checks)
    lines = [("  " if c else "  OVER: ") + m for c, m in checks]
    if verbose:
        for l in lines:
            say(l)
    return ok, lines


# ---------------------------------------------------------------- init
def reset_rows(d):
    """A fresh packet starts with no rows: move aside (never delete, never reuse) the rows.tsv and
    rows_state.json a previous packet left in this dir, so none is carried into the new delta."""
    for stale in (os.path.join(d, "READY", "rows.tsv"), os.path.join(d, "rows_state.json")):
        if os.path.exists(stale):
            os.replace(stale, stale + ".prev")


def cmd_init(a):
    ok, _ = budget()
    if not ok and not a.force:
        raise SystemExit("budget exceeded; wait for other jobs or pass --force (the OOM killer has ended sessions before)")
    d = os.path.join(SCRATCH_ROOT, a.name)
    wt = os.path.join(d, "wt")
    if os.path.exists(wt):
        raise SystemExit("exists: " + wt)
    if os.path.isfile(os.path.join(d, "READY", "patch.diff")) and not getattr(a, "reuse", False):
        raise SystemExit("refusing: %s already holds a READY/patch.diff (init would overwrite its READY files); "
                         "pick another NAME or pass --reuse" % d)
    os.makedirs(os.path.join(d, "READY"), exist_ok=True)
    os.makedirs(os.path.join(d, "obj"), exist_ok=True)
    base = L.rev_parse(D.MAIN_REPO, a.base)
    D.add_worktree(D.MAIN_REPO, wt, base)
    open(os.path.join(d, "READY", "base_sha"), "w").write(base + "\n")
    env = dict(PKT_DIR=d, WT=wt, READY=os.path.join(d, "READY"), OBJ=os.path.join(d, "obj"), NAME=a.name, BASE=base,
               GAMEMD_BINARY=L.BINARY, GAG_JOBS=str(D.MAX_JOBS), TOOLS=D.TOOLS)
    open(os.path.join(d, "pkt.env"), "w").write("".join("%s=%s\n" % kv for kv in env.items()))
    rows = os.path.join(d, "READY", "rows.tsv")
    reset_rows(d)
    open(rows, "w").write("# addr\tsym\tlen\tname   (sym/len may be left empty: `pkt.py score` fills FUN_<addr> symbols and CFG spans)\n")
    say("worktree %s at %s" % (wt, base[:10]))
    say("packet dir %s; `cd %s` then use pkt.py there (reads ./pkt.env)" % (d, d))
    say("""checklist (from AGENTS.md, CONTRIBUTING.md, the briefs and standing directions):
  - ground truth: REA MCP / ghidra CLI on the retail exe; CFG-closed spans (`pkt.py span ADDR`)
  - canonical headers: include them; NEVER a new per-TU view of a class that has one (pktlint `views`)
  - no volatile on accesses/locals, no aliases, no steering casts, no asm, no #pragma optimize
  - names binary-attested or placeholders (FUN_/DAT_/unknown_XX/vf_N); no forbidden words (pktlint `words`)
  - one TU = one file: new code for a migrated original TU goes INTO that TU file (pktlint `migrated`)
  - functions in ascending address order; provenance header; static-initialiser shapes are held
  - never `git add -A`/`.`/`-N`, never stash/clean/reset --hard; -j%d max; no watch loops (background the job)
  - loop: edit -> `pkt.py score TU` -> ... -> `pkt.py bind` -> `pkt.py finish`""" % D.MAX_JOBS)


# ---------------------------------------------------------------- span
def cmd_span(a):
    import ctx
    tree = D.Tree(D.MAIN_REPO, "HEAD")
    claims = tree.claims()
    gh = {}
    try:
        import common
        gh = common.ghidra_functions()
    except Exception:
        pass
    print("addr\tcfg_len\tsource\tghidra_size\tmanifest\tclaimed_in")
    for x in a.addrs:
        va = D.hx(x)
        span, why = D.cfg_span(va)
        row = tree.by_addr.get(va)
        g = gh.get(va)
        print("0x%X\t0x%x\t%s\t%s\t%s\t%s" % (va, span, why.split(" (")[0], g["size"] if g else "-",
                                           ("%s %s%%" % (row["status"], row.get("pct"))) if row else "-", ",".join(claims.get(va, [])) or "-"))


# ---------------------------------------------------------------- rows + score
def read_rows(e):
    rows = {}
    p = os.path.join(e["READY"], "rows.tsv")
    if os.path.isfile(p):
        for ln in open(p):
            if ln.startswith("#") or not ln.strip():
                continue
            f = ln.rstrip("\n").split("\t") + ["", "", ""]
            rows[D.hx(f[0])] = dict(sym=f[1], len=f[2], name=f[3])
    return rows


def read_state(e):
    """rows_state.json as {addr: row}: the per-file scores (tu, pct) of every `score` run so far."""
    p = os.path.join(e["PKT_DIR"], "rows_state.json")
    if not os.path.isfile(p):
        return {}
    return {D.hx(k): v for k, v in json.load(open(p)).items()}


def merged_rows(e):
    """Rows of ALL scored files: the saved state (tu, pct per row, kept across score runs and files)
    overlaid with the non-empty sym/len/name fields the worker edited in rows.tsv."""
    rows = {va: dict(r) for va, r in read_state(e).items()}
    for va, t in read_rows(e).items():
        r = rows.setdefault(va, dict(sym="", len="", name=""))
        for k in ("sym", "len", "name"):
            if t.get(k):
                r[k] = t[k]
    return rows


def write_rows(e, rows):
    p = os.path.join(e["READY"], "rows.tsv")
    with open(p, "w") as f:
        f.write("# addr\tsym\tlen\tname\n")
        for a in sorted(rows):
            r = rows[a]
            f.write("0x%X\t%s\t%s\t%s\n" % (a, r.get("sym", ""), r.get("len", ""), r.get("name", "")))


def tu_rel(e, tu):
    tu = os.path.abspath(tu) if os.path.isabs(tu) or os.path.exists(tu) else os.path.join(e["WT"], tu)
    return os.path.relpath(tu, e["WT"])


def cmd_score(a):
    e = load_env()
    tu = tu_rel(e, a.tu)
    obj = os.path.join(e["OBJ"], os.path.splitext(tu)[0].replace("/", "__") + ".obj")
    ok, text = D.compile_tu(e["WT"], tu, obj)
    if not ok:
        print("\n".join(l for l in text.splitlines() if re.search(r"error|fatal|warning", l, re.I))[:4000])
        raise SystemExit("COMPILE FAIL " + tu)
    rows = merged_rows(e)
    want = {D.hx(x) for x in a.addrs}
    text_src = open(os.path.join(e["WT"], tu)).read()
    claims = D.rows_in_order(text_src)
    names = {n for n in D.defined_names(obj) if n.startswith("?") or n.startswith("_")}
    out = []
    for va in dict.fromkeys(claims):
        if want and va not in want:
            continue
        r = rows.setdefault(va, dict(sym="", len="", name=""))
        if not r["sym"]:
            cand = sorted((n for n in names if re.search(r"FUN_0*%X(@|$)" % va, n, re.I)), key=len)
            if cand:
                r["sym"] = cand[0]
        if not r["len"]:
            span, _ = D.cfg_span(va)
            r["len"] = "0x%x" % span
        if not r["sym"]:
            out.append((va, "NOSYM", "add the mangled symbol to READY/rows.tsv"))
            continue
        row = dict(sym=r["sym"], addr="0x%X" % va, len=r["len"], tu=tu)
        okm, t = D.raw_match(e["WT"], obj, row)
        if okm:
            r["pct"] = 100.0
            out.append((va, "100.0 raw", r["sym"]))
            continue
        pct, t2 = D.diff_retail_pct(e["WT"], obj, row)
        r["pct"] = pct
        last = [l for l in t2.splitlines() if l.startswith(("match:", "multiset:"))]
        out.append((va, "%s" % (pct if pct is not None else t2[-120:].replace("\n", " ")), " ".join(last[-2:])))
    # rows this TU used to carry but no longer claims are dropped, not carried into the packet
    claimed = set(claims)
    for va in [va for va, r in rows.items() if r.get("tu") == tu and va not in claimed]:
        del rows[va]
    rows_tu = {va: r for va, r in rows.items() if va in claimed}
    for va, r in rows_tu.items():
        r["tu"] = tu
    write_rows(e, rows)
    json.dump({"0x%X" % k: v for k, v in rows.items()}, open(os.path.join(e["PKT_DIR"], "rows_state.json"), "w"), indent=1)
    for va, st, extra in out:
        print("0x%X\t%s\t%s" % (va, st, extra))
    print("%d claims, %d exact" % (len(out), sum(1 for _, st, _ in out if st.startswith("100.0"))))


# ---------------------------------------------------------------- bind
def state_rows(e):
    """The packet's delta rows from the per-file state. A row whose address is already in the base
    manifest is an explicit change row (op=change, old sym/status) when it re-keys the symbol/tu/len or
    improves a partial; an unchanged or no-better row is not a result of this packet."""
    st = read_state(e)
    if not st:
        raise SystemExit("no scores yet: run `pkt.py score TU` first")
    base = D.Tree(D.MAIN_REPO, L.Packet(e["READY"]).base_sha())
    rows = []
    for addr, r in st.items():     # addr: int
        if not r.get("sym") or not r.get("tu") or r.get("pct") is None:
            continue
        exact = r["pct"] == 100.0
        cur = base.by_addr.get(D.hx(addr))
        if cur and exact and cur.get("status") == "matched" and cur.get("tu") == r["tu"] and cur.get("sym") == r["sym"] \
                and D.hx(cur["len"]) == D.hx(r["len"]):
            continue    # already exact in the base manifest: not a new result of this packet
        if cur and not exact and cur.get("status") == "partial" and cur.get("sym") == r["sym"] and cur.get("tu") == r["tu"] \
                and D.hx(cur["len"]) == D.hx(r["len"]) and round(r["pct"], 1) <= float(cur.get("pct") or 0):
            continue    # a partial that did not improve
        rows.append(dict(tu=r["tu"], addr="0x%X" % addr, sym=r["sym"], len=r["len"],
                         name=r.get("name") or re.sub(r"^\?(\w+)@(\w+)@@.*", r"\2::\1", r["sym"]) if r["sym"].startswith("?") else r["sym"],
                         status="matched" if exact else "partial", pct=100.0 if exact else round(r["pct"], 1)))
        if cur:
            rows[-1]["op"] = "change"
            rows[-1]["old"] = dict(sym=cur.get("sym"), status=cur.get("status"))
    rows.sort(key=lambda r: D.hx(r["addr"]))
    return rows, base


def write_work_manifest(e, rows):
    """Base manifest + this packet's rows (as finish merges them), written to $PKT_DIR/manifest_work.json, so
    bindings to the packet's own new symbols resolve instead of showing UNBOUND."""
    man, _ = L.load_manifest(os.path.join(e["WT"], D.MANIFEST))
    merged, errs, _ = L.merge_deltas(man, [(e["NAME"], rows)])
    if errs:
        raise SystemExit("delta collides with the base manifest: " + "; ".join(errs[:3]))
    p = os.path.join(e["PKT_DIR"], "manifest_work.json")
    open(p, "w").write(L.dump_manifest(merged))
    return p


def cmd_bind(a):
    """Strict-prove every exact row and build the MINIMAL complete packet map: start from the
    packet's own map, and for each unbound target take the central bindings file, else a
    binding derived from the symbol name / retail IAT / $L position; every binding is checked
    against the relocation field by verify_relocations before it counts."""
    e = load_env()
    rows, base = state_rows(e)
    exact = [r for r in rows if r["status"] == "matched"]
    manifest_work = write_work_manifest(e, rows)
    mapfile = os.path.join(e["READY"], "symbol_map.json")
    pmap = D.read_json(mapfile) if os.path.isfile(mapfile) else {}
    central_p = D.first_existing(D.BINDINGS_CANDIDATES, e["WT"])
    central = D.read_json(central_p) if central_p else {}
    iat = D.iat_by_name()
    objs = {}
    for tu in sorted({r["tu"] for r in exact}):
        obj = os.path.join(e["OBJ"], os.path.splitext(tu)[0].replace("/", "__") + ".obj")
        ok, text = D.compile_tu(e["WT"], tu, obj)
        if not ok:
            raise SystemExit("COMPILE FAIL " + tu)
        objs[tu] = obj
        pmap.update(D.label_bindings(obj, [r for r in exact if r["tu"] == tu]))
    tmpmap = os.path.join(e["PKT_DIR"], "map_work.json")
    json.dump(pmap, open(tmpmap, "w"), indent=1)
    fails, derived = [], {}
    for r in exact:
        for _ in range(24):
            ok, target, text = D.strict(e["WT"], objs[r["tu"]], r, tmpmap, manifest_work)
            if ok:
                break
            va = None
            src = None
            if target and target in central:
                va, src = D.hx(str(central[target])), "central"
            elif target:
                va, src = D.derive_binding(target, iat), "derived"
            if target and va is not None and target not in pmap:
                pmap[target] = "0x%X" % va
                derived[target] = src
                json.dump(pmap, open(tmpmap, "w"), indent=1)
                continue
            fails.append((r["addr"], target or text[-160:]))
            break
    json.dump(pmap, open(mapfile, "w"), indent=1)
    for addr, why in fails:
        print("UNBOUND\t%s\t%s" % (addr, why))
    print("%d exact rows, %d strict failures; map %s (%d entries: %d from central bindings, %d derived from names/IAT/$L)" % (
        len(exact), len(fails), mapfile, len(pmap), sum(v == "central" for v in derived.values()), sum(v == "derived" for v in derived.values())))
    return 1 if fails else 0


# ---------------------------------------------------------------- finish
def cmd_finish(a):
    e = load_env()
    rows, base = state_rows(e)
    R = e["READY"]
    json.dump(rows, open(os.path.join(R, "manifest_delta.json"), "w"), indent=1)
    with open(os.path.join(R, "results.tsv"), "w") as f:
        f.write("addr\tsymbol\t%\tstatus\ttu\n")
        for r in rows:
            f.write("%s\t%s\t%s\t%s\t%s\n" % (r["addr"], r["sym"], r["pct"], "exact" if r["status"] == "matched" else "partial", r["tu"]))
    # patch: tracked changes + new files the worker added explicitly (never -A)
    L.git(e["WT"], "add", "--", *sorted({r["tu"] for r in rows}))
    diff = L.git(e["WT"], "diff", "--cached", "--binary", base.rev, "--", ".", ":(exclude)%s" % D.MANIFEST)
    diff += L.git(e["WT"], "diff", "--binary", "--", ".", ":(exclude)%s" % D.MANIFEST)
    open(os.path.join(R, "patch.diff"), "w").write(diff)
    nexact = sum(r["status"] == "matched" for r in rows)
    npart = len(rows) - nexact
    readme = os.path.join(R, "README.md")
    if not os.path.isfile(readme):
        tus = sorted({r["tu"] for r in rows})
        open(readme, "w").write("""# %s READY packet

Base: %s. Result: %d exact (raw_match PASS, strict verify_relocations PASS), %d partial.
Files: patch.diff (manifest excluded), manifest_delta.json (%d rows, sorted by address), symbol_map.json,
results.tsv, gates.log, base_sha.

## Held / not landed (reason)
- (fill in: address, best %%, variants tried, remaining delta)

## Notes for the lander
- (ODR debt, header patches, re-keys)

## Proposed commit message
```
Match %d functions in %s

(one paragraph: what the functions are, where the names come from, header changes)

Co-Authored-By: Claude Opus 5.5 <noreply@anthropic.com>
```
""" % (e["NAME"], base.rev, nexact, npart, len(rows), nexact, ", ".join(os.path.basename(t) for t in tus)))
        say("README.md skeleton written: fill the held items and the commit message")
    run = os.path.join(e["PKT_DIR"], "gates")
    cmd = [sys.executable, os.path.join(D.TOOLS, "land", "gates.py"), "--tree", e["WT"], "--base", base.rev, "--mode", "inc",
           "--jobs", str(D.MAX_JOBS), "--run", run]
    mp = os.path.join(R, "symbol_map.json")
    if os.path.isfile(mp):
        cmd += ["--symmap", mp]
    # gates read the index: stage the manifest with the delta applied, then restore it
    man, raw = L.load_manifest(os.path.join(e["WT"], D.MANIFEST))
    merged, errs, _ = L.merge_deltas(man, [(e["NAME"], rows)])
    if errs:
        raise SystemExit("delta collides with the base manifest: " + "; ".join(errs[:3]))
    open(os.path.join(e["WT"], D.MANIFEST), "w").write(L.dump_manifest(merged))
    L.git(e["WT"], "add", "--", D.MANIFEST)
    try:
        rc, text = L.run(cmd, cwd=e["WT"], env=L.toolenv(), log=os.path.join(R, "gates.log"))
    finally:
        open(os.path.join(e["WT"], D.MANIFEST), "w").write(raw)
        L.git(e["WT"], "add", "--", D.MANIFEST)
    for l in text.splitlines():
        if l.startswith(("GATE", "RESULT")):
            say("  " + l)
    lint = subprocess.run([sys.executable, os.path.join(HERE, "pktlint.py"), R, "--rev", base.rev], capture_output=True, text=True)
    say(lint.stdout[-3000:])
    bk = os.path.join(D.BACKUPS, e["NAME"])
    if a.backup:
        os.makedirs(bk, exist_ok=True)
        shutil.copytree(R, os.path.join(bk, "READY"), dirs_exist_ok=True, symlinks=True)
        say("backed up to", bk)
    say("finish: %d exact, %d partial; gates rc %d; lint rc %d" % (nexact, npart, rc, lint.returncode))
    return 1 if rc or lint.returncode else 0


def held_backup(e):
    """--held: a packet with nothing READY (held-only). Save the worktree diff to the backup dir first."""
    dest = os.path.join(D.BACKUPS, e["NAME"], "HELD")
    os.makedirs(dest, exist_ok=True)
    wt = e["WT"]
    L.git(wt, "add", "-N", "--", ".", check=False)   # include new files in the diff; tracked content is untouched
    diff = L.git(wt, "diff", "--binary", "HEAD", "--", ".")
    open(os.path.join(dest, "worktree.diff"), "w").write(diff)
    if os.path.isdir(e["PKT_DIR"]):
        # Copy only the small packet files: never the worktree, build output or symlinks
        # (a followed toolchain link once made each backup ~80 GB and filled the drive).
        import shutil
        skip = shutil.ignore_patterns("wt", "obj", "build-vc6", "toolchain", "__pycache__", "*.obj", "*.exe", "tmp*")
        shutil.copytree(e["PKT_DIR"], os.path.join(dest, "pkt_dir"), dirs_exist_ok=True,
                        symlinks=True, ignore=skip)
    say("held: worktree diff (%d bytes) backed up to %s" % (len(diff), dest))


def cmd_done(a):
    e = load_env()
    bk = os.path.join(D.BACKUPS, e["NAME"], "READY")
    if a.held:
        held_backup(e)
    elif not os.path.isdir(bk) and not a.force:
        raise SystemExit("no backup at %s: run `pkt.py finish` first (or --force)" % bk)
    try:
        D.remove_worktree(D.MAIN_REPO, e["WT"])
    except D.NotOursError as ex:
        raise SystemExit(str(ex) + " (this worktree was not created by pkt.py init; remove it yourself if it is yours)")
    say("worktree removed; packet dir kept at", e["PKT_DIR"])


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sp = ap.add_subparsers(dest="cmd", required=True)
    sp.add_parser("budget")
    p = sp.add_parser("init"); p.add_argument("name"); p.add_argument("--base", default="HEAD"); p.add_argument("--force", action="store_true"); p.add_argument("--reuse", action="store_true", help="init in a packet dir that already has READY/patch.diff")
    p = sp.add_parser("span"); p.add_argument("addrs", nargs="+")
    p = sp.add_parser("score"); p.add_argument("tu"); p.add_argument("addrs", nargs="*")
    sp.add_parser("bind")
    p = sp.add_parser("finish"); p.add_argument("--no-backup", dest="backup", action="store_false")
    p = sp.add_parser("done"); p.add_argument("--force", action="store_true"); p.add_argument("--held", action="store_true", help="held-only packet (no READY): back up the worktree diff to the backup dir, then remove the worktree")
    a = ap.parse_args(argv)
    if a.cmd == "budget":
        ok, _ = budget()
        return 0 if ok else 1
    return {"init": cmd_init, "span": cmd_span, "score": cmd_score, "bind": cmd_bind, "finish": cmd_finish, "done": cmd_done}[a.cmd](a) or 0


if __name__ == "__main__":
    sys.exit(main())
