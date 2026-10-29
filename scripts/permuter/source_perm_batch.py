#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original tooling.
"""Run source_perm.py over the permuter-eligible rows of partial_residuals.json.

  source_perm_batch.py --out DIR [--minutes 3] [-j 6] [--max-len 0x200] [--limit N]

Rows whose function body already carries steering (volatile, casts, asm) are
skipped. Results go to DIR/<addr>/ and DIR/summary.json.
"""
import argparse, concurrent.futures, json, os, re, subprocess, sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import source_perm as sp  # noqa: E402


def one(row, out, minutes, seed):
    d = os.path.join(out, row["addr"])
    os.makedirs(d, exist_ok=True)
    p = subprocess.run(
        [sys.executable, os.path.join(ROOT, "scripts/permuter/source_perm.py"),
         "--tu", row["tu"], "--addr", row["addr"], "--sym", row["sym"], "--len", row["len"],
         "--minutes", str(minutes), "--seed", str(seed), "--out", d],
        capture_output=True, text=True)
    log = p.stdout + p.stderr
    open(os.path.join(d, "log.txt"), "w").write(log)
    m = re.search(r"base score (\d+)", log)
    f = re.search(r"done: candidates (\d+) best (\d+) certified (\w+)", log)
    return {"addr": row["addr"], "tu": row["tu"], "name": row["name"], "label": row["primary"],
            "base": int(m.group(1)) if m else None,
            "best": int(f.group(2)) if f else None,
            "candidates": int(f.group(1)) if f else None,
            "certified": bool(f and f.group(3) == "True")}


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--residuals", default=os.path.join(ROOT, "scripts/data/partial_residuals.json"))
    ap.add_argument("--out", required=True)
    ap.add_argument("--minutes", type=float, default=3)
    ap.add_argument("-j", type=int, default=6)
    ap.add_argument("--max-len", default="0x200")
    ap.add_argument("--limit", type=int, default=1000)
    ap.add_argument("--skip", nargs="*", default=[])
    ap.add_argument("--seed", type=int, default=1)
    a = ap.parse_args()
    rows = []
    for r in json.load(open(a.residuals)):
        if not r["eligible"] or int(r["len"], 16) > int(a.max_len, 16) or r["addr"].lower() in a.skip:
            continue
        try:
            src = open(os.path.join(ROOT, r["tu"])).read()
            b0, b1 = sp.find_function(src, int(r["addr"], 16))
        except (SystemExit, OSError):
            continue
        if sp.steering_count(src[b0:b1]):
            continue
        rows.append(r)
    rows.sort(key=lambda r: int(r["len"], 16))
    rows = rows[:a.limit]
    print(f"{len(rows)} rows", flush=True)
    res = []
    with concurrent.futures.ThreadPoolExecutor(a.j) as ex:
        futs = [ex.submit(one, r, a.out, a.minutes, a.seed) for r in rows]
        for f in concurrent.futures.as_completed(futs):
            x = f.result()
            res.append(x)
            print(x, flush=True)
            json.dump(res, open(os.path.join(a.out, "summary.json"), "w"), indent=1)


if __name__ == "__main__":
    main()
