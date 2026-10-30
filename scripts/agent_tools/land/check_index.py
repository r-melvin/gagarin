#!/usr/bin/env python3
"""check_index.py TREE [--tus a,b] [--jobs N]: validate the include index against cl /E.

For every TU, runs the real VC6 preprocessor (`cl /E`) and collects the files it
actually opened (`#line N "file"` markers). Soundness requirement: every opened
file under match/ is in the index's closure for that TU. The index may
over-approximate (includes in dead #if branches); that only widens the affected
set. Exit 1 on any missing file.
"""
import argparse
import concurrent.futures as cf
import os
import re
import sys
import tempfile

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import landlib as L  # noqa: E402

ALIAS = re.compile(r'^[Zz]:/tmp/vc6-[0-9a-f]{10}/(.*)$')
LINE = re.compile(rb'^#line \d+ "([^"]+)"', re.M)


def opened(tree, tu, env):
    fd, tmp = tempfile.mkstemp(prefix="pp_")
    os.close(fd)
    try:
        with open(tmp, "wb") as out, open(os.devnull, "wb") as err:
            import subprocess
            subprocess.run(["bash", os.path.join(tree, "scripts/vc6/vc6cl.sh"), "/E", os.path.basename(tu)],
                           cwd=os.path.join(tree, os.path.dirname(tu)), env=env, stdout=out, stderr=err)
        data = open(tmp, "rb").read()
    finally:
        os.unlink(tmp)
    got = set()
    for m in LINE.finditer(data):
        p = m.group(1).decode("latin1").replace("\\\\", "/").replace("\\", "/")
        a = ALIAS.match(p)
        if a:                              # in-repo file via the vc6cl.sh checkout alias: repo-relative
            got.add(os.path.normpath(a.group(1)))
            continue
        if ":" in p:                       # system header (drive letter)
            continue
        got.add(os.path.normpath(os.path.join(os.path.dirname(tu), p)))
    return got


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("tree")
    ap.add_argument("--tus", default="")
    ap.add_argument("--jobs", type=int, default=12)
    a = ap.parse_args()
    tree = os.path.abspath(a.tree)
    idx = L.IncludeIndex(L.TreeFiles(tree))
    tus = a.tus.split(",") if a.tus else idx.tus()
    env = L.toolenv()
    bad = extra = total = 0
    with cf.ThreadPoolExecutor(a.jobs) as ex:
        for tu, got in zip(tus, ex.map(lambda t: opened(tree, t, env), tus)):
            cl = set(idx.closure(tu))
            miss = got - cl
            total += len(got)
            extra += len(cl - got)
            if miss:
                bad += 1
                print("MISSING from index closure of %s: %s" % (tu, sorted(miss)[:5]))
    print("%d TUs, %d opened files checked, %d TUs with a gap, %d over-approximated entries" % (
        len(tus), total, bad, extra))
    return 1 if bad else 0


if __name__ == "__main__":
    sys.exit(main())
