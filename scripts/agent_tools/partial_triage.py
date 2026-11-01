#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original tooling; reads only the project's own sources/objects and the pinned PE
# (through scripts/vc6/diff_retail.py).
"""partial_triage.py: classify every partial manifest row by the shape of its residual and route it.

    partial_triage.py [--tree WT] [--out DIR] [-j 4] [--min-pct P] [--only ADDR ...] [--limit-tus N]

For each `partial` row the TU is compiled once (in parallel, never more than 4 at a time), the
function is scored with diff_retail.py --dump-streams, and the retail/compiled instruction streams
are classified (registers, stack displacements, immediates and branch targets are masked with
residual_classify.dissect, so "same instruction" means the same mnemonic and operand shape):

  register-only  same instructions at the same positions, only register names differ
  stack-only     same, only [esp/ebp+N] displacements or an esp frame adjustment differ
  order-only     the same multiset of instructions in a different order: homm3 B16, no known
                 lever, so parked; or the same stream with different branch targets (block
                 layout), which stays with the permuter
  inline-shape   an instruction-count delta concentrated (>= 60%) in alignment hunks where one
                 side calls and the other does not: a call that retail inlines, or the reverse
  structural     anything else (a mix of the above, a missing/extra instruction, constants)

Bookkeeping classes: reloc-only (streams identical, the remaining gap is a relocation target,
switch table or literal), compile-fail, no-score.

The labels come from residual_classify.classify (extended there, not duplicated here): a
register-only row whose differences are all operand swaps (`add eax,ecx` vs `add ecx,eax`, swapped
base/index, `cmp a,b` vs `cmp b,a`) routes to `source_perm --only commute`; regpredict adds the
homm3 first-fit register-model label (B1/B8/B16) and a lever hint as columns.

Routing: register-only -> permuter; order-only -> parked (B16), or permuter for block layout; stack-only -> reccmp-stackcmp; inline-shape ->
inline library; structural -> manual, except a structural row whose non-branch instruction
multiset is equal (a reorder plus register choice, or branch polarity) which still routes to the
permuter (likewise one whose positions agree except registers and stack slots). `delta` is max(retail, compiled) minus the longest common subsequence of the masked
instructions, i.e. how many instructions have to change.

Output (all paths absolute): DIR/triage.tsv, DIR/summary.json, DIR/obj/*.obj, DIR/streams/*.json.
A relative --out is made absolute before anything is written, and a TU whose object is missing
after the compiler ran is recorded as compile-fail, never skipped silently.
Needs GAMEMD_BINARY (the pinned image). Tests: python3 -m unittest test_partial_triage.
"""
import argparse
import collections
import concurrent.futures as cf
import difflib
import json
import os
import re
import subprocess
import sys
import time

HERE = os.path.dirname(os.path.abspath(__file__))
REPO = os.path.dirname(os.path.dirname(HERE))
sys.path.insert(0, os.path.join(REPO, "scripts", "vc6"))
import residual_classify as rc  # noqa: E402
import regpredict as rp  # noqa: E402

MAX_JOBS = 4
INLINE_SHARE = 0.60
PARKED = "parked (B16)"
SWAP_ROUTE = "source_perm --only commute"
ROUTE = {"register-only": "permuter", "order-only": PARKED, "stack-only": "reccmp-stackcmp",
         "inline-shape": "inline library", "structural": "manual", "reloc-only": "manual",
         "compile-fail": "manual", "no-score": "manual"}
CLASSES = ["register-only", "order-only", "stack-only", "inline-shape", "structural",
           "reloc-only", "compile-fail", "no-score"]
DP_LIMIT = 4_000_000


# ---------------------------------------------------------------- stream classification
def lcs_pairs(a, b):
    """Index pairs (i, j) of a longest common subsequence of two key lists (difflib beyond DP_LIMIT)."""
    n, m = len(a), len(b)
    if n * m > DP_LIMIT:
        sm = difflib.SequenceMatcher(None, a, b, autojunk=False)
        return [(blk.a + k, blk.b + k) for blk in sm.get_matching_blocks() for k in range(blk.size)]
    L = [[0] * (m + 1) for _ in range(n + 1)]
    for i in range(n - 1, -1, -1):
        row, nxt, ai = L[i], L[i + 1], a[i]
        for j in range(m - 1, -1, -1):
            row[j] = nxt[j + 1] + 1 if ai == b[j] else max(nxt[j], row[j + 1])
    pairs, i, j = [], 0, 0
    while i < n and j < m:
        if a[i] == b[j]:
            pairs.append((i, j))
            i += 1
            j += 1
        elif L[i + 1][j] >= L[i][j + 1]:
            i += 1
        else:
            j += 1
    return pairs


def _is_call(shape):
    return shape.split(" ", 1)[0] == "call"


def inline_hunks(R, C, shapes_r, shapes_c):
    """Alignment hunks of the shape streams: [(r0, r1, c0, c1)] for every unmatched gap."""
    pairs = lcs_pairs(shapes_r, shapes_c)
    out, pi, pj = [], 0, 0
    for i, j in pairs + [(len(R), len(C))]:
        if i > pi or j > pj:
            out.append((pi, i, pj, j))
        pi, pj = i + 1, j + 1
    return out


def classify_streams(retail, comp, relocs=(), base=0):
    """Classify one row. retail/comp: lists of (offset, hexbytes, mnemonic, operands).

    Returns {"class", "delta", "len_delta", "aligned_pct", "route", "detail"}.
    """
    rv = rc.reloc_values(comp, relocs)
    R = [rc.dissect(m, o, set(), True) for _, _, m, o in retail]
    C = [rc.dissect(m, o, rv[i], False) for i, (_, _, m, o) in enumerate(comp)]
    nr, nc = len(R), len(C)
    res = {"len_delta": nc - nr}
    pairs = lcs_pairs(R, C)
    res["delta"] = max(nr, nc) - len(pairs)
    res["aligned_pct"] = round(100.0 * len(pairs) / max(nr, nc, 1), 1)
    tr, tc = rc.branch_targets(retail, base), rc.branch_targets(comp, 0)
    # operand-swap sites (commutative op, base/index, cmp) among same-shape instruction pairs, wherever the rest differs
    res["swaps"] = sum(1 for r, c in zip(R, C) if r[0] == c[0] and rp.operand_swap_kind(r[0], r[1], c[1])) if nr == nc else 0

    def done(cls, detail="", route=None):
        res.update({"class": cls, "route": route or ROUTE[cls], "detail": detail})
        full = rc.classify(retail, comp, relocs, base)
        res["labels"] = ",".join(full["labels"])
        pred = full.get("regpredict")
        res["regpredict"] = pred["label"] if pred else ""
        res["lever"] = pred["lever"] if pred and cls in ("register-only", "structural", "order-only") else ""
        if cls == "register-only" and any(x in full["labels"] for x in ("commutative-swap", "cmp-swap")):
            res["route"] = SWAP_ROUTE
        return res

    if R == C:
        if tr == tc:
            res["delta"] = 0
            return done("reloc-only", "streams identical")
        return done("order-only", "branch targets differ (block layout)", route="permuter")

    if collections.Counter(R) == collections.Counter(C):
        return done("order-only", "same instructions, different order")

    def keep(L):
        return collections.Counter((x[0], x[3]) for x in L if not rc.is_branch(x[0].split()[0]))

    shapes_r, shapes_c = [x[0] for x in R], [x[0] for x in C]
    if nr == nc and shapes_r == shapes_c:
        nreg = sum(1 for r, c in zip(R, C) if r[1] != c[1])
        nstk = sum(1 for r, c in zip(R, C) if r[2] != c[2])
        nimm = sum(1 for r, c in zip(R, C) if r[3] != c[3])
        if tr != tc:
            return done("structural", "branch targets differ with operand differences")
        if nreg and not nstk and not nimm:
            return done("register-only", "%d insns" % nreg)
        if nstk and not nreg and not nimm:
            return done("stack-only", "%d insns" % nstk)
        tags = [t for t, v in (("reg", nreg), ("stack", nstk), ("const", nimm)) if v]
        return done("structural", "+".join(tags), route="permuter" if nimm == 0 or keep(R) == keep(C) else "manual")

    # inline-shape: the length delta sits in hunks where exactly one side makes calls
    total = nc - nr
    if total:
        call_part, call_hunks, targets = 0, 0, []
        for r0, r1, c0, c1 in inline_hunks(R, C, shapes_r, shapes_c):
            cr = sum(1 for s in shapes_r[r0:r1] if _is_call(s))
            cc = sum(1 for s in shapes_c[c0:c1] if _is_call(s))
            if cr != cc:
                call_part += (c1 - c0) - (r1 - r0)
                call_hunks += 1
                if cr > cc:
                    targets += [retail[k][3].split()[0] for k in range(r0, r1) if _is_call(shapes_r[k])]
        if call_hunks and call_part * total > 0 and abs(call_part) >= INLINE_SHARE * abs(total):
            who = "we inline a call retail makes" if total > 0 else "retail inlines a call we make"
            d = "%s (%+d insns in %d hunk%s)" % (who, call_part, call_hunks, "s" if call_hunks > 1 else "")
            if targets:
                d += "; retail call target " + ",".join(sorted(set(targets))[:3])
            return done("inline-shape", d)

    # structural; the permuter can still search it when the non-branch instructions are the same set
    if nr == nc and keep(R) == keep(C):
        return done("structural", "reorder+registers/stack or branch polarity", route="permuter")
    only_r = collections.Counter(x[0] for x in R) - collections.Counter(x[0] for x in C)
    only_c = collections.Counter(x[0] for x in C) - collections.Counter(x[0] for x in R)
    return done("structural", "retail-only %d, compiled-only %d" % (sum(only_r.values()), sum(only_c.values())))


# ---------------------------------------------------------------- compile and score
def abs_out(path):
    """Absolute output directory, created and proven writable (a relative path once failed silently)."""
    p = os.path.abspath(path)
    probe = os.path.join(p, ".probe")
    try:
        os.makedirs(p, exist_ok=True)
        with open(probe, "w") as f:
            f.write("ok")
        os.unlink(probe)
    except OSError as exc:
        raise SystemExit("partial_triage: output directory %s is not writable: %s" % (p, exc))
    return p


def obj_path(out, tu):
    return os.path.join(out, "obj", re.sub(r"[/\\]", "__", os.path.splitext(tu)[0]) + ".obj")


def compile_tu(tree, tu, obj):
    """(ok, log) for one TU compiled to the absolute path `obj`."""
    assert os.path.isabs(obj) and os.path.isabs(tree)
    os.makedirs(os.path.dirname(obj), exist_ok=True)
    if os.path.exists(obj):
        os.unlink(obj)
    drv = "vc6asm.sh" if tu.endswith(".asm") else "vc6cl.sh"
    p = subprocess.run(["bash", os.path.join(tree, "scripts", "vc6", drv), "/Fo" + obj, os.path.basename(tu)],
                       cwd=os.path.join(tree, os.path.dirname(tu)), capture_output=True, text=True)
    log = (p.stdout + p.stderr).strip()
    if p.returncode != 0:
        return False, "compiler exit %d: %s" % (p.returncode, log[-300:])
    if not os.path.isfile(obj):
        return False, "compiler exited 0 but wrote no object at " + obj
    return True, ""


def compile_all(tree, tus, out, jobs=MAX_JOBS, compile_fn=compile_tu):
    """{tu: (obj or None, error)}; each TU is compiled exactly once."""
    def one(tu):
        obj = obj_path(out, tu)
        ok, why = compile_fn(tree, tu, obj)
        return tu, ((obj, "") if ok else (None, why))

    with cf.ThreadPoolExecutor(max(1, min(jobs, MAX_JOBS))) as ex:
        return dict(ex.map(one, tus))


def score_row(tree, out, obj, row):
    """Run diff_retail with --dump-streams; returns (pct, streams dict or None, message)."""
    dump = os.path.join(out, "streams", "%s.json" % row["addr"])
    os.makedirs(os.path.dirname(dump), exist_ok=True)
    if os.path.exists(dump):
        os.unlink(dump)
    p = subprocess.run([sys.executable, os.path.join(tree, "scripts", "vc6", "diff_retail.py"), "--obj", obj,
                        "--sym", row["sym"], "--addr", row["addr"], "--len", row["len"],
                        "--dump-streams", dump], capture_output=True, text=True, cwd=tree)
    m = re.findall(r"match: ([0-9.]+)%", p.stdout)
    pct = float(m[-1]) if m else None
    if not os.path.isfile(dump):
        return pct, None, (p.stdout + p.stderr).strip().splitlines()[-1:] or [""]
    with open(dump) as f:
        d = json.load(f)
    return pct, {"retail": [tuple(x) for x in d["retail"]], "comp": [tuple(x) for x in d["comp"]],
                 "relocs": d["relocs"]}, ""


def triage_rows(rows, objs, tree, out, jobs=MAX_JOBS, patched=frozenset(), score_fn=score_row):
    def one(row):
        rec = {"addr": row["addr"], "tu": row["tu"], "name": row.get("name", ""), "sym": row["sym"],
               "manifest_pct": row.get("pct"), "pct": None}
        obj, why = objs.get(row["tu"], (None, "TU not compiled"))
        if not obj:
            rec.update({"class": "compile-fail", "delta": "", "len_delta": "", "aligned_pct": "",
                        "route": ROUTE["compile-fail"], "detail": why[:120]})
            return rec
        pct, st, msg = score_fn(tree, out, obj, row)
        rec["pct"] = pct
        if st is None:
            rec.update({"class": "no-score", "delta": "", "len_delta": "", "aligned_pct": "",
                        "route": ROUTE["no-score"], "detail": str(msg)[:120]})
            return rec
        rec.update(classify_streams(st["retail"], st["comp"], st["relocs"], int(row["addr"], 16)))
        if row["addr"].lower() in patched:
            rec["detail"] = ("distribution patch; " + rec["detail"]).strip("; ")
        return rec

    with cf.ThreadPoolExecutor(max(1, min(jobs, MAX_JOBS))) as ex:
        return list(ex.map(one, rows))


COLS = ["addr", "class", "delta", "len_delta", "route", "pct", "manifest_pct", "aligned_pct", "swaps", "labels", "regpredict", "lever",
        "tu", "name", "detail"]


def write_tsv(path, recs):
    with open(path, "w") as f:
        f.write("\t".join(COLS) + "\n")
        for r in sorted(recs, key=lambda r: (CLASSES.index(r["class"]), r["delta"] if r["delta"] != "" else 1 << 30,
                                             int(r["addr"], 16))):
            f.write("\t".join(str(r.get(c, "")).replace("\t", " ").replace("\n", " ") for c in COLS) + "\n")


def summarise(recs):
    by = collections.Counter(r["class"] for r in recs)
    route = collections.Counter(r["route"] for r in recs)
    small = collections.Counter(r["class"] for r in recs if r["delta"] != "" and r["delta"] <= 4)
    swapped = sum(1 for r in recs if r.get("swaps"))
    return {"rows": len(recs), "rows_with_operand_swap_sites": swapped, "classes": {c: by[c] for c in CLASSES if by[c]},
            "routes": dict(route.most_common()), "delta_le_4": dict(small)}


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--tree", default=os.environ.get("GAG_WORKTREE") or REPO)
    ap.add_argument("--out", help="output directory (default: <scratch>/partial_triage_<time>); made absolute")
    ap.add_argument("-j", type=int, default=MAX_JOBS)
    ap.add_argument("--min-pct", type=float, default=0.0)
    ap.add_argument("--only", nargs="*", default=[], help="restrict to these addresses")
    ap.add_argument("--limit-tus", type=int, default=0, help="only the first N TUs (testing)")
    a = ap.parse_args(argv)
    tree = os.path.abspath(a.tree)
    scratch = os.environ.get("GAG_SCRATCH_ROOT") or os.path.join(os.path.dirname(tree), "gagarin-scratch")
    out = abs_out(a.out or os.path.join(scratch, "partial_triage_" + time.strftime("%Y%m%d_%H%M%S")))
    with open(os.path.join(tree, "scripts", "data", "match_manifest.json")) as f:
        man = json.load(f)
    only = {x.lower() for x in a.only}
    rows = [r for r in man if r["status"] == "partial" and (r.get("pct") or 0) >= a.min_pct
            and (not only or r["addr"].lower() in only)]
    tus = sorted({r["tu"] for r in rows})
    if a.limit_tus:
        tus = tus[:a.limit_tus]
        rows = [r for r in rows if r["tu"] in set(tus)]
    patched = set()
    try:
        with open(os.path.join(tree, "scripts", "data", "distribution_patches.json")) as f:
            patched = {p["addr"].lower() for p in json.load(f)["patches"]}
    except (OSError, KeyError, ValueError):
        pass
    print("%d partial rows in %d TUs; out %s" % (len(rows), len(tus), out), flush=True)
    objs = compile_all(tree, tus, out, a.j)
    bad = [t for t, (o, _) in objs.items() if not o]
    print("compiled %d/%d TUs" % (len(tus) - len(bad), len(tus)), flush=True)
    for t in bad[:10]:
        print("  compile-fail %s: %s" % (t, objs[t][1][:160]))
    if tus and len(bad) == len(tus):
        print("partial_triage: no TU compiled; check the toolchain and --tree", file=sys.stderr)
        return 2
    recs = triage_rows(rows, objs, tree, out, a.j, patched)
    write_tsv(os.path.join(out, "triage.tsv"), recs)
    summ = summarise(recs)
    with open(os.path.join(out, "summary.json"), "w") as f:
        json.dump(summ, f, indent=1)
    print(json.dumps(summ, indent=1))
    print("wrote", os.path.join(out, "triage.tsv"))
    return 0


if __name__ == "__main__":
    sys.exit(main())
