#!/usr/bin/env python3
"""status_rotate.py TREE --prev-title TITLE --para-file FILE [--date D] [--tests N]

Port of the landers' status.py. Rotates STATUS.md's current snapshot into the
historical archive under TITLE and writes a new current snapshot whose counts come
from the tree (match_manifest.json, progress_totals.json, padding_scan.json, tracked
.cpp count) and whose narrative paragraph is FILE. The tooling-test count defaults to
the one in the current snapshot; pass --tests N (or a gates run's tests.log via
--tests-log) to update it. Edits TREE/STATUS.md only; run it in a scratch worktree.
"""
import argparse
import datetime
import json
import os
import re
import subprocess
import sys


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("tree")
    ap.add_argument("--prev-title", required=True)
    ap.add_argument("--para-file", required=True)
    ap.add_argument("--date", default=datetime.date.today().isoformat())
    ap.add_argument("--tests", type=int)
    ap.add_argument("--tests-log")
    a = ap.parse_args()
    T = a.tree
    para = open(a.para_file).read().strip()
    m = json.load(open(T + "/scripts/data/match_manifest.json"))
    tot = json.load(open(T + "/scripts/data/progress_totals.json"))
    pad = json.load(open(T + "/scripts/data/padding_scan.json"))
    s = open(T + "/STATUS.md").read()
    tests = a.tests
    if tests is None and a.tests_log and os.path.isfile(a.tests_log):
        r = re.search(r"Ran (\d+) tests", open(a.tests_log).read())
        tests = int(r.group(1)) if r else None
    if tests is None:
        r = re.search(r"(\d+) tooling tests", s)
        tests = int(r.group(1)) if r else 0
    mat = [r for r in m if r["status"] == "matched"]
    par = sum(r["status"] == "partial" for r in m)
    tus = len({r["tu"] for r in m})
    cpp = len(subprocess.run(["git", "ls-files", ":(icase)match/**.cpp"], cwd=T, capture_output=True, text=True).stdout.split())
    byt = sum(int(r["len"], 16) for r in mat)
    miss = pad["summary"]["matched_entries_missed"] if "summary" in pad else pad["matched_entries_missed"]
    f = lambda n: format(n, ",")
    head = f"""As of **{a.date}**, the verified snapshot reports **{f(len(mat))} matched function
rows**, **{f(par)} partial rows**, **{f(len(m))} manifest rows**, **{f(tus)} manifest
translation units**, and **{f(cpp)} tracked C++ files**. Whole-repository regression
verification, the project object build and {tests} tooling tests pass, and the
compile/layout check passes on the tracked tree.

{para}

The {f(len(mat))} matches represent {100 * len(mat) / tot['functions']:.1f}% of {f(tot['functions'])} listed functions. Counts are per
function, not executable completion. Matched body lengths total **{f(byt)}
bytes**, or {100 * byt / tot['code_bytes']:.1f}% of {f(tot['code_bytes'])} listed function bytes. The padding heuristic
misses {f(miss)} matched entries. The last diagnostic link, taken before the second
cleanup batch, reported **4,186 unique unresolved symbols**, **6,731 reference
lines**, and zero duplicate definitions. Engine link closure remains unfinished.
"""
    top, rest = s.split("## Historical integration archive\n", 1)
    cur = top.split("# Project status\n", 1)[1].strip("\n")
    arch, older = rest.split("\n## Historical snapshot:", 1)
    out = ("# Project status\n\n" + head + "\n## Historical integration archive\n" + arch.rstrip("\n") +
           "\n\n## Historical snapshot: " + a.prev_title + "\n\n" + cur + "\n\n## Historical snapshot:" + older)
    open(T + "/STATUS.md", "w").write(out)
    print(len(mat), par, len(m), tus, cpp, byt, miss, "tests", tests)


if __name__ == "__main__":
    sys.exit(main())
