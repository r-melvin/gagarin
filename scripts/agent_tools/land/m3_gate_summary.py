#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original project tooling.
"""m3_gate_summary.py: build the machine-readable summary of one m3_gate.sh run (called by it).

    m3_gate_summary.py OUTDIR [--worktree WT]

Reads OUTDIR/steps.tsv (step<TAB>rc), gate-verify.log, gate-m3/compare.json (compare_image --json),
the duplicate and unittest logs, and writes OUTDIR/m3_gate_summary.json (also printed).
"""
import argparse
import json
import os
import re
import sys


def read(p):
    try:
        return open(p, errors="replace").read()
    except OSError:
        return ""


def summarize(outdir, worktree=""):
    steps = {}
    for ln in read(os.path.join(outdir, "steps.tsv")).splitlines():
        k, _, v = ln.partition("\t")
        if k:
            steps[k] = int(v) if v.lstrip("-").isdigit() else v
    s = dict(worktree=worktree, steps=steps)
    m = re.search(r"=== (\d+) matched \(100%\), (\d+) documented partials, (\d+) regressed", read(os.path.join(outdir, "gate-verify.log")))
    s["matched"], s["partials"], s["regressed"] = (int(x) for x in m.groups()) if m else (None, None, None)
    try:
        cmp_ = json.load(open(os.path.join(outdir, "gate-link-m3", "compare.json")))
    except (OSError, ValueError):
        cmp_ = {}
    s["identical"] = cmp_.get("identical")
    s["differing_bytes"] = {n: v["diff_bytes"] for n, v in cmp_.get("sections", {}).items()}
    org = cmp_.get("origins") or {}
    s["project_bytes"] = sum(v.get("project", 0) for v in org.values()) if org else None
    s["library_bytes"] = sum(v.get("library", 0) for v in org.values()) if org else None
    pj = os.path.join(outdir, "gate-link-m3", "placement.json")
    s["placement_json"] = pj if os.path.isfile(pj) else None
    if s["placement_json"]:
        pieces = json.load(open(pj))["pieces"]
        s["project_bytes_excl_r3"] = sum(p[2] for p in pieces if p[3] == "project" and not p[4].startswith("??_R3"))
    dup = read(os.path.join(outdir, "gate-dup.log")).strip().splitlines()
    s["duplicates"] = dup[-1] if dup else None
    ut = read(os.path.join(outdir, "gate-unittest.log")).strip().splitlines()
    s["unittests"] = ut[-1] if ut else None
    s["ok"] = bool(steps) and all(v == 0 for v in steps.values() if isinstance(v, int)) and s["identical"] is not None
    return s


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("outdir")
    ap.add_argument("--worktree", default="")
    a = ap.parse_args(argv)
    s = summarize(a.outdir, a.worktree)
    text = json.dumps(s, indent=1, sort_keys=True)
    open(os.path.join(a.outdir, "m3_gate_summary.json"), "w").write(text + "\n")
    print(text)
    return 0


if __name__ == "__main__":
    sys.exit(main())
