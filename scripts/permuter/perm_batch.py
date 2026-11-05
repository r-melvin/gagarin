#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original tooling; drives source_perm.py over partial_triage.py routes.
"""perm_batch.py: run source_perm.py over the permuter-routed rows of a triage, within a budget.

    perm_batch.py TRIAGE_DIR --tree WT --out DIR [--jobs 3] [--minutes 10] [--min-pct 85] [--limit N]

Best first, resumable (a row with DIR/<addr>/best.txt is skipped). Each row keeps only best.txt and
best.cpp; everything else in its directory is deleted when it ends. Stops launching below 50 GB free.
The rows are never applied: DIR/results.tsv lists improvements for a worker to take through the gates.
"""
import argparse, concurrent.futures as cf, csv, json, os, shutil, subprocess, sys

MIN_FREE = 50 << 30


def run(row, a):
    d = os.path.join(a.out, row["addr"])
    if os.path.exists(os.path.join(d, "best.txt")):
        return row, "skipped"
    if shutil.disk_usage(a.out).free < MIN_FREE:
        return row, "low-disk"
    os.makedirs(d, exist_ok=True)
    r = subprocess.run([sys.executable, os.path.join(a.tree, "scripts/permuter/source_perm.py"), "--tu", row["tu"], "--addr", row["addr"],
                        "--sym", row["sym"], "--len", row["len"], "--minutes", str(a.minutes), "--out", d],
                       cwd=a.tree, capture_output=True, text=True)
    for n in os.listdir(d):
        if n not in ("best.txt", "best.cpp"):
            p = os.path.join(d, n)
            shutil.rmtree(p) if os.path.isdir(p) else os.remove(p)
    if not os.path.exists(os.path.join(d, "best.txt")):
        return row, "failed: " + r.stderr.strip()[-120:]
    return row, "certified" if "certified True" in open(os.path.join(d, "best.txt")).read() else "no-match"


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("triage_dir"); ap.add_argument("--tree", required=True); ap.add_argument("--out", required=True)
    ap.add_argument("--jobs", type=int, default=3); ap.add_argument("--minutes", type=int, default=10)
    ap.add_argument("--min-pct", type=float, default=85); ap.add_argument("--limit", type=int)
    a = ap.parse_args()
    a.out = os.path.abspath(a.out); os.makedirs(a.out, exist_ok=True)
    a.tree = os.path.abspath(a.tree)      # source_perm.py works in the repo it runs from, so run the tree's own copy
    man = {int(r["addr"], 16): r for r in json.load(open(os.path.join(a.tree, "scripts/data/match_manifest.json")))}
    rows = []
    for t in csv.DictReader(open(os.path.join(a.triage_dir, "triage.tsv")), delimiter="\t"):
        m = man.get(int(t["addr"], 16))
        if t["route"] == "permuter" and m and m["status"] == "partial" and float(t["pct"] or 0) >= a.min_pct:
            rows.append(dict(addr=t["addr"], tu=m["tu"], sym=m["sym"], len=m["len"], pct=float(t["pct"])))
    rows.sort(key=lambda r: -r["pct"])
    rows = rows[: a.limit] if a.limit else rows
    print("%d rows" % len(rows), flush=True)
    with cf.ThreadPoolExecutor(a.jobs) as ex, open(os.path.join(a.out, "results.tsv"), "a") as f:
        for row, st in ex.map(lambda r: run(r, a), rows):
            best = os.path.join(a.out, row["addr"], "best.txt")
            txt = open(best).read().strip().replace("\n", " ") if os.path.exists(best) else ""
            f.write("%s\t%.1f\t%s\t%s\n" % (row["addr"], row["pct"], st, txt)); f.flush()


if __name__ == "__main__":
    main()
