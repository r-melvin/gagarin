#!/usr/bin/env python3
"""compare_modes.py: check that gates.py `inc` and `full` agree on a historical commit.

    compare_modes.py --repo REPO --commit C [--base P] [--jobs N] [--work DIR]

Cuts a scratch worktree at C (base defaults to C^), then runs the gates twice, each
with its OWN cold object cache so neither run can reuse the other's objects:
  inc  : gates.py --mode inc
  full : gates.py --mode full
and compares, gate by gate:
  * status of every gate that ran in both (inc may SKIP `tests` when no scripts changed);
  * the set of regressed matched rows (verify);
  * the set of rows failing raw/strict (strict);
  * the set of changed/added/removed sections (sections): full compares every object,
    inc only the affected ones, so equality proves nothing changed outside the affected set;
  * dups / naked / dupdefs / lint / words outcomes.
Exit 0 only if they agree. Also prints both wall times.
"""
import argparse
import json
import os
import shutil
import subprocess
import sys
import time

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
import landlib as L  # noqa: E402


def run_gates(wt, base, mode, run, cache, jobs):
    env = L.toolenv({"LAND_CACHE": cache})
    t = time.time()
    p = subprocess.run([sys.executable, os.path.join(HERE, "gates.py"), "--tree", wt, "--base", base, "--mode", mode,
                        "--run", run, "--jobs", str(jobs)], capture_output=True, text=True, env=env, cwd=wt)
    wall = time.time() - t
    open(run + ".out", "w").write(p.stdout + p.stderr)
    summ = json.load(open(os.path.join(run, "summary.json")))
    strict = []
    sp = os.path.join(run, "strict.json")
    if os.path.isfile(sp):
        strict = sorted(r["addr"] for r in json.load(open(sp)) if r["raw"] or r["strict"])
    return summ, strict, wall, p.returncode


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--repo", default=L.MAIN_REPO)
    ap.add_argument("--commit", required=True)
    ap.add_argument("--base")
    ap.add_argument("--jobs", type=int, default=min(16, (os.cpu_count() or 8) // 2))
    ap.add_argument("--work")
    ap.add_argument("--keep", action="store_true")
    a = ap.parse_args()
    commit = L.rev_parse(a.repo, a.commit)
    base = L.rev_parse(a.repo, a.base or commit + "^")
    work = os.path.abspath(a.work or os.path.join(L.RUNS, "compare-%s" % commit[:9]))
    shutil.rmtree(work, ignore_errors=True)
    os.makedirs(work)
    wt = os.path.join(work, "wt")
    L.git(a.repo, "worktree", "add", "--detach", wt, commit)
    os.symlink(L.TOOLCHAIN, os.path.join(wt, "toolchain"))
    try:
        print("commit %s base %s" % (commit[:9], base[:9]))
        inc, inc_strict, inc_wall, inc_rc = run_gates(wt, base, "inc", os.path.join(work, "inc"), os.path.join(work, "cache_inc"), a.jobs)
        full, full_strict, full_wall, full_rc = run_gates(wt, base, "full", os.path.join(work, "full"), os.path.join(work, "cache_full"), a.jobs)
        gi = {g["gate"]: g for g in inc["results"]}
        gf = {g["gate"]: g for g in full["results"]}
        bad = []
        print("%-9s %-5s %-5s" % ("gate", "inc", "full"))
        for g in gf:
            si, sf = gi.get(g, {}).get("status", "-"), gf[g]["status"]
            note = ""
            if si != sf and not (si == "SKIP" and g in ("tests",)):
                bad.append("gate %s: inc=%s full=%s" % (g, si, sf))
                note = "  <-- DISAGREE"
            print("%-9s %-5s %-5s%s" % (g, si, sf, note))
        if inc["verify"]["regressed"] != full["verify"]["regressed"]:
            bad.append("verify regressed sets differ: inc %s full %s" % (inc["verify"]["regressed"][:5], full["verify"]["regressed"][:5]))
        if inc_strict != full_strict:
            bad.append("strict failing rows differ: inc %s full %s" % (inc_strict[:5], full_strict[:5]))
        si = {tuple(x) for x in inc["sections"] or []}
        sf = {tuple(x) for x in full["sections"] or []}
        if si != sf:
            bad.append("section change sets differ: only-inc %s only-full %s" % (sorted(si - sf)[:3], sorted(sf - si)[:3]))
        out_of_scope = sorted({tu for tu, _, _ in sf} - set(inc["affected"]))
        if out_of_scope:
            bad.append("full found changed objects outside the affected set: %s" % out_of_scope[:5])
        print("affected TUs: %d of %d; section changes (full/inc): %d/%d in %d TUs; verify rows inc %d full %d; "
              "regressed rows %d/%d; strict failing %d/%d" % (
                  len(inc["affected"]), inc["tus_total"], len(sf), len(si), len({t for t, _, _ in sf}),
                  inc["verify"]["rows"], full["verify"]["rows"], len(inc["verify"]["regressed"]),
                  len(full["verify"]["regressed"]), len(inc_strict), len(full_strict)))
        print("wall: inc %.1fs (cold cache)  full %.1fs (cold cache)" % (inc_wall, full_wall))
        print("AGREE" if not bad else "DISAGREE")
        for b in bad:
            print("  " + b)
        json.dump({"commit": commit, "base": base, "inc": inc, "full": full, "disagreements": bad,
                   "inc_wall": inc_wall, "full_wall": full_wall}, open(os.path.join(work, "compare.json"), "w"), indent=1)
        return 1 if bad else 0
    finally:
        if os.path.islink(os.path.join(wt, "toolchain")):
            os.unlink(os.path.join(wt, "toolchain"))
        L.git(a.repo, "worktree", "remove", "--force", wt, check=False)
        if not a.keep:
            shutil.rmtree(os.path.join(work, "cache_inc"), ignore_errors=True)
            shutil.rmtree(os.path.join(work, "cache_full"), ignore_errors=True)


if __name__ == "__main__":
    sys.exit(main())
