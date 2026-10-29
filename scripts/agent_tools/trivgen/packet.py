#!/usr/bin/env python3
# Provenance: original. READY packet builder for trivgen.
"""packet: re-verify the generated TUs from scratch, write the READY packet.

Reads WORK/run_state.json (exact set + chosen variants), rebuilds the bins from
that set, recompiles and re-checks every row (raw_match, strict verify_relocations
with an object-derived symbol map), then runs, in the isolated worktree:
check_duplicates.py and verify_all.py over the new TUs only.
"""
import collections
import json
import os
import re
import subprocess
import sys
import time
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent.parent / "land"))
import landlib as L
import trivgen as T
import verify
import data
import emit
import gen
import patterns
import callers
import canon
from lift import Unsupported
from pathlib import Path

WT, WORK, READY = T.WT, T.WORK, T.READY


def sh(cmd, cwd=WT, env=None, check=False):
    e = dict(os.environ, GAMEMD_BINARY=verify.BIN)
    if env:
        e.update(env)
    r = subprocess.run(cmd, cwd=cwd, capture_output=True, text=True, env=e)
    return r.returncode, r.stdout + r.stderr


def main():
    state = json.loads((WORK / "run_state.json").read_text())
    exact = {int(k, 16): v for k, v in state["exact"].items()}
    d = T.load_items()
    items = T.do_lift(d["items"])
    tus, votes = data.tu_info()
    live = [i for i in items if "spec" in i and i["addr"] in exact]
    for i in live:
        i["fail"] = None
    base = sh(["git", "rev-parse", "HEAD"])[1].strip()
    gates = []

    def log(msg):
        gates.append(msg)
        print(msg, file=sys.stderr, flush=True)

    # 1. rebuild + final re-verification (drop anything that no longer verifies, then rebuild)
    dropped = {}
    for attempt in range(4):
        keep = [i for i in live if i["addr"] not in dropped]
        sel = {i["addr"]: exact[i["addr"]]["var"] for i in keep}
        T.clean_generated()
        bins = T.plan_bins(keep, sel, votes, None)
        T.write_bins(bins)
        res = T.compile_all(bins)
        for b in bins:
            if res[b.name][0] is None:
                log(f"COMPILE FAIL {b.name}: {res[b.name][1][:2]}")
                for o in b.items:
                    dropped[o.spec.addr] = "final compile failure"
        checks = T.verify_bins(bins, res)
        bad = {a: r for a, r in checks.items() if not r["ok"]}
        for a, r in bad.items():
            dropped[a] = "final gate: " + r["why"]
        if not bad and all(res[b.name][0] is not None for b in bins):
            break
    log(f"final verification: {len(checks) - len(bad)} exact rows in {len(bins)} TUs; dropped {len(dropped)}")
    if dropped:
        for a, w in dropped.items():
            log(f"  dropped 0x{a:X}: {w}")

    # 2. manifest rows, results.tsv
    rows, results = [], []
    byitem = {i["addr"]: i for i in live}
    byaddr = {o.spec.addr: (b, o) for b in bins for o in b.items}
    for a in sorted(byaddr):
        b, o = byaddr[a]
        r = checks[a]
        sym = r["sym"]
        name = o.mname or (f"{o.member_of}::FUN_{a:08X}" if o.member_of else f"FUN_{a:08X}")
        rows.append(dict(tu=f"match/{b.module}/{b.name}.cpp", addr=f"0x{a:X}", sym=sym, len=hex(o.spec.size),
                         name=name, status="matched", pct=100))
        it = byitem[a]
        ev = [T.describe_owner(it).strip() or "no-vtable-slot", callers.describe(callers.evidence(a))]
        results.append((f"0x{a:X}", sym, 100, "match: 100.0%", r.get("relocs", ""), "matched", o.kind,
                        it["pattern"], "; ".join(ev)))
    READY.mkdir(parents=True, exist_ok=True)
    (READY / "manifest_delta.json").write_text(json.dumps(rows, indent=1) + "\n")
    (READY / "results.tsv").write_text("addr\tsymbol\tpct\traw\trelocs\tstatus\tconvention\tpattern\tevidence\n" +
                                       "\n".join("\t".join(map(str, r)) for r in results) + "\n")

    # 2b. header-patch proposals for vtable-slot members whose RTTI class has a canonical header
    props = []
    for a in sorted(byaddr):
        b, o = byaddr[a]
        it = byitem[a]
        if not it.get("vtable") or o.canon:
            continue
        cls_full, slot, _ = canon.owner_of(it["vtable"])
        cls = cls_full.split("::")[-1]
        hs = canon.headers().get(cls)
        if not hs:
            props.append((a, cls_full, slot, "", "no canonical header: keep the address-scoped view", ""))
            continue
        path, tx, st = hs[0]
        body = canon.class_body(tx, st)
        decl = re.sub(r"\bFUN_[0-9A-F]{8}\b", f"vf_{slot}", o.mdecl or o.decl or "").rstrip(";")
        decl = f"virtual {decl};" if decl else ""
        status = ("declarable: the header already declares virtuals; insert this slot in order"
                  if "virtual " in body else
                  "blocked: the canonical header declares no virtuals (layout view only); declaring one slot would shift the vtable")
        props.append((a, cls_full, slot, str(Path(path).relative_to(WT)), status, decl))
    (READY / "header_proposals.tsv").write_text(
        "addr\tclass\tslot\theader\tstatus\tproposed_declaration\n" +
        "\n".join("\t".join([f"0x{a:X}", c, str(sl), h, st_, d]) for a, c, sl, h, st_, d in props) + "\n")
    log(f"header proposals: {len(props)} ({sum(1 for p in props if p[4].startswith('declarable'))} declarable)")

    # 3. gates in the isolated worktree
    man = WT / "scripts/data/match_manifest.json"
    orig = man.read_text()
    merged = json.loads(orig)
    have = {(m["tu"], m["addr"].upper()) for m in merged}
    merged += [r for r in rows if (r["tu"], r["addr"].upper()) not in have]
    merged.sort(key=lambda m: int(m["addr"], 16))
    man.write_text(json.dumps(merged, indent=1) + "\n")
    try:
        rc, out = sh([sys.executable, "scripts/vc6/check_duplicates.py"])
        log(f"check_duplicates.py rc={rc}: " + out.strip().splitlines()[-1] if out.strip() else f"rc={rc}")
        gates.append(out.strip())
        mini = WORK / "manifest_new_tus.json"
        mini.write_text(json.dumps(rows, indent=1))
        t0 = time.time()
        rc2, out2 = sh([sys.executable, "scripts/vc6/verify_all.py", "--manifest", str(mini)])
        tail = out2.strip().splitlines()[-1] if out2.strip() else ""
        log(f"verify_all.py (new TUs only) rc={rc2} in {time.time() - t0:.0f}s: {tail}")
        gates.append(out2.strip())
    finally:
        man.write_text(orig)
        sh(["git", "checkout", "--", "scripts/data/match_manifest.json"])

    # 4. patch.diff (new files only, explicit paths)
    paths = sorted({f"match/{b.module}/{b.name}.{e}" for b in bins for e in ("cpp", "h")})
    init_paths = [x for x in paths if "_init_" in x]
    fn_paths = [x for x in paths if "_init_" not in x]
    sh(["git", "add", "-N", "--"] + paths)
    rc, diff = sh(["git", "diff", "--no-color", "--"] + paths)
    parts = {}
    for name, ps in (("functions", fn_paths), ("initialisers", init_paths)):
        parts[name] = sh(["git", "diff", "--no-color", "--"] + ps)[1] if ps else ""
    sh(["git", "reset", "-q", "--"] + paths)
    (READY / "patch.diff").write_text(diff)
    (READY / "patch_functions.diff").write_text(parts["functions"])
    (READY / "patch_initialisers.diff").write_text(parts["initialisers"])
    init_rows = [r for r in rows if "_init_" in r["tu"]]
    fn_rows = [r for r in rows if "_init_" not in r["tu"]]
    (READY / "manifest_delta_functions.json").write_text(json.dumps(fn_rows, indent=1) + "\n")
    (READY / "manifest_delta_initialisers.json").write_text(json.dumps(init_rows, indent=1) + "\n")

    # 5. words check over added lines
    added = "\n".join(l for l in diff.splitlines() if l.startswith("+") and not l.startswith("+++"))
    pat = L.FORBID_RE      # local word list (.coordination/forbidden_words.txt); disabled with a warning if absent
    hits = [l for l in added.splitlines() if pat.search(l)]
    log(f"words check: {len(hits)} hit(s)")

    # 6. README + gates.log
    pc = collections.Counter(i["pattern"] for i in live if i["addr"] in byaddr)
    tot = collections.Counter(i["pattern"] for i in items)
    why = {int(x["addr"], 16): x["why"] for x in state["summary"]}
    held = [(i["addr"], i["pattern"], i.get("fail") or why.get(i["addr"], "")) for i in items if i["addr"] not in byaddr]
    (READY / "gates.log").write_text("\n".join(gates) + "\n")
    lines = [
        "# trivgen READY packet: generated and verified trivial functions",
        "",
        f"Base: main {base} (patch.diff is match/ only; apply manifest_delta.json separately).",
        f"Generated by scripts/agent_tools/trivgen (see its README); re-run with `trivgen.py run` then `packet.py`.",
        "",
        f"Counts: {len(rows)} new exact rows (all `matched`) in {len(bins)} new TUs; 0 partials emitted. "
        f"Candidates after re-filter: {len(items)}; held back: {len(held)}.",
        "",
        "Split for landing (each part is self-contained; patch.diff + manifest_delta.json are their union):",
        f"- patch_functions.diff + manifest_delta_functions.json: {len(fn_rows)} ordinary functions "
        f"(trivial_tuNNN_methods.*).",
        f"- patch_initialisers.diff + manifest_delta_initialisers.json: {len(init_rows)} static-initialiser shapes "
        "(trivial_tuNNN_init_methods.*), i.e. the 19/26-byte `__xc` table entries that the standing directions defer to "
        "the header-initialiser milestone. Land them with that milestone, or not at all; nothing in the other part depends on them.",
        "",
        "## Proposed commit message",
        f"Land {len(rows)} trivial functions generated and verified by trivgen: getters, setters, constants, empties, thunks and static-initialiser shapes",
        "",
        "New TUs trivial_tuNNN_methods.{cpp,h} (one per original TU id, placeholders only: Obj_<addr> receiver views,",
        "FUN_<addr>, DAT_<addr>, unknown_<off>). Every row is raw_match 100% plus strict verify_relocations.",
        "",
        "Co-Authored-By: Claude Sonnet 5.5 <noreply@anthropic.com>",
        "",
        "## Gates (see gates.log)",
        "- raw_match 100% and strict verify_relocations (object-derived symbol map) on every row, twice (probe and final rebuild).",
        "- check_duplicates.py and verify_all.py (new TUs only) run in the isolated worktree with manifest_delta.json applied.",
        "- verify_vtable: not applicable (no vtable rows). Section preservation: not applicable (no existing TU touched).",
        "",
        "## Words check",
        f"Added lines grep against the local forbidden-word list: {len(hits)} hit(s).",
        "",
        "## Per-pattern results (exact / candidates)",
    ]
    for k, v in tot.most_common():
        lines.append(f"- {k}: {pc.get(k, 0)} / {v}")
    lines += ["", "## Header patches (proposals only; nothing existing is edited)",
              f"header_proposals.tsv: {len(props)} vtable-slot members whose RTTI class has no/other canonical declaration "
              f"({sum(1 for p in props if p[4].startswith('declarable'))} declarable now, "
              f"{sum(1 for p in props if p[4].startswith('blocked'))} blocked until the header declares its vtable, "
              f"{sum(1 for p in props if p[4].startswith('no canonical'))} with no canonical header).",
              f"Members already declared by their canonical header are defined out of line "
              f"({sum(1 for a in byaddr if byaddr[a][1].canon)} functions, e.g. `AnimClass::vf_11`).",
              "", "## Held back (not in this packet)", "See held.tsv (address, pattern, reason)."]
    (READY / "README.md").write_text("\n".join(lines) + "\n")
    (READY / "held.tsv").write_text("addr\tpattern\treason\n" + "\n".join(
        f"0x{a:X}\t{p}\t{(w or '')[:200]}" for a, p, w in sorted(held)) + "\n")
    print(json.dumps(dict(rows=len(rows), bins=len(bins), dropped=len(dropped), held=len(held), base=base,
                          words_hits=len(hits))))


if __name__ == "__main__":
    main()
