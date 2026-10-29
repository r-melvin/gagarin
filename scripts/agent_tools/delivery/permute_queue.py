#!/usr/bin/env python3
"""permute_queue.py: rank partial rows for the permuter and scaffold their run dirs.

    permute_queue.py [--tree WT] [--limit N] [--out DIR] [--scaffold K] [--jobs 4]

For every partial row: compile its TU once, run diff_retail and record pct and whether the
instruction MULTISET is identical (same instructions, different order/registers: a scheduling or
colouring problem the permuter can search, not a missing statement), and whether the RA2 1.08 twin
is byte-identical (ra2diff pairs.csv: same source, so the remaining gap is a compile problem).
Writes queue.tsv ranked: multiset-identical and twin-identical first, then by pct. With
--scaffold K, runs scripts/permuter/new_run.sh for the top K rows and copies the function's
current C++ chunk into base.c as the starting restatement (the permuter clone itself is external;
see CONTRIBUTING.md). No model is involved; a 100% result still has to come back through
`pkt.py bind/finish` to become a manifest row.
"""
import argparse
import concurrent.futures as cf
import csv
import json
import os
import re
import subprocess
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import dlib as D  # noqa: E402
import landlib as L  # noqa: E402

PAIRS = [os.environ.get("GAG_RA2_PAIRS", ""), os.path.join(L.SCRATCH_ROOT, "ra2diff/pairs.csv"), os.path.join(D.BACKUPS, "ra2diff/pairs.csv")]


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--tree", default=D.MAIN_REPO)
    ap.add_argument("--limit", type=int, default=0, help="limit the number of TUs compiled")
    ap.add_argument("--out")
    ap.add_argument("--scaffold", type=int, default=0)
    ap.add_argument("--jobs", type=int, default=D.MAX_JOBS)
    a = ap.parse_args(argv)
    out = a.out or D.scratch_dir("permute_queue_")
    os.makedirs(out, exist_ok=True)
    man = json.load(open(os.path.join(a.tree, D.MANIFEST)))
    partial = [r for r in man if r["status"] != "matched"]
    tus = sorted({r["tu"] for r in partial})
    if a.limit:
        tus = tus[:a.limit]
    twins = {}
    pf = D.first_existing(PAIRS)
    if pf:
        for row in csv.DictReader(open(pf)):
            try:
                twins[D.hx(row["yr_addr"])] = (row.get("kind"), float(row.get("similarity") or 0))
            except Exception:
                pass
    objs = {}

    def comp(tu):
        obj = os.path.join(out, "obj", os.path.splitext(tu)[0] + ".obj")
        ok, _ = D.compile_tu(a.tree, tu, obj)
        return tu, (obj if ok else None)

    with cf.ThreadPoolExecutor(min(a.jobs, D.MAX_JOBS)) as ex:
        objs = dict(ex.map(comp, tus))
    rows = [r for r in partial if r["tu"] in objs]

    def score(r):
        obj = objs[r["tu"]]
        if not obj:
            return r, None, None
        pct, text = D.diff_retail_pct(a.tree, obj, r)
        ms = re.search(r"^multiset: (identical|retail-only.*)$", text, re.M)
        return r, pct, (ms.group(1) if ms else None)

    with cf.ThreadPoolExecutor(min(a.jobs, D.MAX_JOBS)) as ex:
        res = list(ex.map(score, rows))
    q = []
    for r, pct, ms in res:
        tw = twins.get(D.hx(r["addr"]))
        twin_identical = bool(tw and tw[0] == "exact" and tw[1] >= 1.0)
        q.append(dict(addr=r["addr"], tu=r["tu"], sym=r["sym"], len=r["len"], pct=pct, manifest_pct=r.get("pct"),
                      multiset_identical=(ms == "identical"), multiset=ms or "", ra2_twin_identical=twin_identical,
                      rank=(0 if ms == "identical" else 1) + (0 if twin_identical else 1)))
    q.sort(key=lambda x: (x["rank"], -(x["pct"] or 0)))
    with open(os.path.join(out, "queue.tsv"), "w") as f:
        f.write("addr\ttu\tsym\tlen\tpct\tmultiset_identical\tra2_twin_identical\tmultiset\n")
        for x in q:
            f.write("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n" % (x["addr"], x["tu"], x["sym"], x["len"], x["pct"], x["multiset_identical"], x["ra2_twin_identical"], x["multiset"][:80]))
    n_ms = sum(x["multiset_identical"] for x in q)
    n_tw = sum(x["ra2_twin_identical"] for x in q)
    print("%d partial rows scored in %d TUs: %d multiset-identical, %d RA2-twin-identical, %d both; queue %s" % (
        len(q), len(objs), n_ms, n_tw, sum(x["multiset_identical"] and x["ra2_twin_identical"] for x in q), os.path.join(out, "queue.tsv")))
    for x in q[: a.scaffold]:
        rd = os.path.join(out, "runs", x["addr"])
        cname = "gg_" + re.sub(r"\W", "_", (re.sub(r"^\?(\w+)@(\w+)@@.*", r"\2_\1", x["sym"]) if x["sym"].startswith("?") else x["sym"]))
        subprocess.run(["bash", os.path.join(a.tree, "scripts/permuter/new_run.sh"), x["addr"], cname, x["sym"], rd, x["len"]],
                       cwd=a.tree, capture_output=True, text=True)
        text = open(os.path.join(a.tree, x["tu"])).read()
        lines, pre, chunks, inters = D.split(text)
        body = next((lines[c["start"]:c["end"]] for c in chunks if D.hx(x["addr"]) in c["addrs"]), None)
        if body:
            open(os.path.join(rd, "current_body.cpp"), "w").write("\n".join(body) + "\n")
        print("scaffolded", rd)
    return 0


if __name__ == "__main__":
    sys.exit(main())
