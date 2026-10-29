#!/usr/bin/env python3
"""bench_old_flow.py: time the landers' manual gate sequence on a tree, for comparison.

    bench_old_flow.py --tree WT --base-tree BASEWT --rows ROWS.json --map MAP.json [--shards 8]

Runs, one after the other and each timed, what /tmp/gagarin-land-w3|w4/gates.sh plus the
extra landing steps did (scripts are copied in legacy/):
  compile_all.sh | verify_all.py in N parallel shards (sub-manifests) | unittests |
  check_duplicates | build_project --jobs 8 + --check | dupdefs | check_naked |
  per-file lint (new vs base) | base build_project --jobs 8 + whole-tree section
  comparison (legacy/sections.py) | raw_match + strict verify_relocations on the packet
  rows (legacy/raw_strict.py).
BASEWT is a worktree at the base commit with the toolchain symlink. ROWS.json is a list of
addresses (hex strings); MAP.json is {"default": "<symbol map path>"}.
"""
import argparse
import json
import os
import subprocess
import sys
import tempfile
import time

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
import landlib as L  # noqa: E402


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--tree", required=True)
    ap.add_argument("--base-tree", required=True)
    ap.add_argument("--rows", required=True)
    ap.add_argument("--map", required=True)
    ap.add_argument("--shards", type=int, default=8)
    a = ap.parse_args()
    env = L.toolenv()
    T, B = os.path.abspath(a.tree), os.path.abspath(a.base_tree)
    out = tempfile.mkdtemp(prefix="bench_old_")
    times = []

    def stage(name, cmd, cwd, parallel=None):
        t = time.time()
        if parallel:
            procs = [subprocess.Popen(c, cwd=cwd, env=env, stdout=open(os.path.join(out, "%s_%d.log" % (name, i)), "w"),
                                      stderr=subprocess.STDOUT) for i, c in enumerate(parallel)]
            rc = max(p.wait() for p in procs)
        else:
            with open(os.path.join(out, name + ".log"), "w") as f:
                rc = subprocess.run(cmd, cwd=cwd, env=env, stdout=f, stderr=subprocess.STDOUT).returncode
        dt = time.time() - t
        times.append((name, rc, dt))
        print("%-12s rc=%d %7.1fs" % (name, rc, dt), flush=True)

    py = sys.executable
    stage("compile_all", ["bash", "scripts/vc6/compile_all.sh"], T)
    man = json.load(open(os.path.join(T, L.MANIFEST)))
    tus = sorted({r["tu"] for r in man})
    shards = []
    for i in range(a.shards):
        mp = os.path.join(out, "shard%d.json" % i)
        mine = set(tus[i::a.shards])
        json.dump([r for r in man if r["tu"] in mine], open(mp, "w"))
        shards.append([py, "scripts/vc6/verify_all.py", "--manifest", mp])
    stage("verify_all", None, T, parallel=shards)
    stage("tests", [py, "-m", "unittest", "discover", "-s", "scripts/vc6", "-p", "test_*.py"], T)
    stage("dups", [py, "scripts/vc6/check_duplicates.py"], T)
    stage("build", [py, "scripts/vc6/build_project.py", "--jobs", "8"], T)
    stage("check", [py, "scripts/vc6/build_project.py", "--check"], T)
    stage("dupdefs", [py, os.path.join(HERE, "legacy/dupdefs.py"), "build-vc6/project"], T)
    stage("naked", [py, "scripts/vc6/check_naked.py"], T)
    # lint: decomplint every touched file in new and base, serially like lint.sh
    files = subprocess.run(["git", "diff", "--name-only", "--diff-filter=AM", subprocess.check_output(
        ["git", "-C", B, "rev-parse", "HEAD"], text=True).strip(), "--", "match"], cwd=T, capture_output=True, text=True).stdout.split()
    files = [f for f in files if f.endswith((".cpp", ".h"))]
    script = "; ".join("reccmp-decomplint --module GAMEMD '%s/%s'; [ -f '%s/%s' ] && reccmp-decomplint --module GAMEMD '%s/%s'" % (T, f, B, f, B, f)
                       for f in files) or "true"
    stage("lint", ["bash", "-c", script], T)
    stage("base_build", [py, "scripts/vc6/build_project.py", "--jobs", "8"], B)
    stage("sections", [py, os.path.join(HERE, "legacy/sections.py"), B + "/build-vc6/project", T + "/build-vc6/project",
                       os.path.join(out, "sections.json")], T)
    stage("raw_strict", [py, os.path.join(HERE, "legacy/raw_strict.py"), T, a.rows, a.map, os.path.join(out, "raw_strict.json")], T)
    total = sum(t for _, _, t in times)
    print("TOTAL %.1fs (%.1f min); logs %s" % (total, total / 60, out))
    json.dump(times, open(os.path.join(out, "times.json"), "w"))


if __name__ == "__main__":
    main()
