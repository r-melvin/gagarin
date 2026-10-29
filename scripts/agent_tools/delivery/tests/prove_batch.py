#!/usr/bin/env python3
"""prove_batch.py: show that ONE full gate on a batch tip proves what the per-packet full gates
proved, on real landing history.

    prove_batch.py [--base d2682f0] [--tip 935745b] [--runs <scratch>/land-b7] [--jobs 4]

The b7 lander ran gates.py --mode full once per packet (run4..run11b, each against its parent).
This runs gates.py --mode full ONCE on the tip against the batch base and compares:
  - verify: every matched row re-proved (same oracle), regressed set (expected empty both ways);
  - strict: the set of rows strict-checked at the tip (added/changed vs base) is a superset of the
    union of the per-packet strict rows, and every one passes;
  - sections: the TUs whose sections changed between base and tip equal the union of the
    per-packet changed TUs (a change in packet k that packet k+1 reverts would show here);
  - every other gate PASS.
Writes a JSON report beside the run dir and prints AGREE/DISAGREE.
"""
import argparse
import glob
import json
import os
import subprocess
import sys
import time

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.dirname(HERE))
import dlib as D  # noqa: E402
import landlib as L  # noqa: E402


def main(argv=None):
    ap = argparse.ArgumentParser()
    ap.add_argument("--base", default="d2682f0")
    ap.add_argument("--tip", default="935745b")
    ap.add_argument("--runs", default=os.path.join(L.SCRATCH_ROOT, "land-b7"))
    ap.add_argument("--per-packet", default="run4,run5c,run6,run7,run8,run9,run10b,run11b")
    ap.add_argument("--jobs", type=int, default=D.MAX_JOBS)
    ap.add_argument("--repo", default=D.MAIN_REPO)
    a = ap.parse_args(argv)
    base = L.rev_parse(a.repo, a.base)
    tip = L.rev_parse(a.repo, a.tip)
    work = D.scratch_dir("prove_batch_")
    wt = D.add_worktree(a.repo, os.path.join(work, "wt"), tip)
    t0 = time.time()
    # per-packet symbol maps: the lander's extra maps if still present, else the packets' READY maps
    maps = sorted(glob.glob(os.path.join(a.runs, "symmap_*_extra.json")))
    if not maps:
        for pk in ("w6-tu130", "w6-tu171", "w6-tu288", "w6-tu237", "w6-tu099", "w6-tu230", "w6-tu180", "w6-tu161"):
            maps += L.Packet(os.path.join(D.BACKUPS, pk, "READY")).symbol_map_files()
    try:
        wanted = [os.path.join(a.runs, r, "summary.json") for r in a.per_packet.split(",")]
        if not all(os.path.isfile(w) for w in wanted):
            # the lander's run dirs are gone (/tmp): regenerate the per-packet full gates, one per commit
            a.runs = os.path.join(work, "per_packet")
            os.makedirs(a.runs, exist_ok=True)
            commits = L.git(a.repo, "rev-list", "--reverse", "%s..%s" % (base, tip)).split()
            names = []
            for i, c in enumerate(commits, 1):
                L.git(wt, "checkout", "-q", "--detach", c)
                rd = os.path.join(a.runs, "run%d" % i)
                cmd = [sys.executable, os.path.join(D.TOOLS, "land", "gates.py"), "--tree", wt, "--base", c + "^", "--mode", "full",
                       "--jobs", str(a.jobs), "--run", rd, "--no-promote"]
                for mf in maps:
                    cmd += ["--symmap", mf]
                t = time.time()
                L.run(cmd, cwd=wt, env=L.toolenv(), log=rd + ".log")
                print("per-packet %s %s: %.0fs" % (c[:10], L.git(a.repo, "log", "-1", "--format=%s", c).strip()[:60], time.time() - t), flush=True)
                names.append("run%d" % i)
            a.per_packet = ",".join(names)
            L.git(wt, "checkout", "-q", "--detach", tip)
            t0 = time.time()
        run = os.path.join(work, "gates")
        cmd = [sys.executable, os.path.join(D.TOOLS, "land", "gates.py"), "--tree", wt, "--base", base, "--mode", "full",
               "--jobs", str(a.jobs), "--run", run, "--no-promote"]
        # the per-packet symbol maps the lander used (strict needs the same bindings)
        for mf in maps:
            cmd += ["--symmap", mf]
        rc, text = L.run(cmd, cwd=wt, env=L.toolenv(), log=os.path.join(work, "gates.log"))
        wall = time.time() - t0
        summ = json.load(open(os.path.join(run, "summary.json")))
        batch = {g["gate"]: g for g in summ["results"]}
        strict_tip = json.load(open(os.path.join(run, "strict.json"))) if os.path.isfile(os.path.join(run, "strict.json")) else []
        sec_tip = set(json.load(open(os.path.join(run, "sections.json")))["changed"])
        # per-packet union
        per = {}
        strict_union, sec_union, regressed_union, walls = {}, set(), set(), 0.0
        for r in a.per_packet.split(","):
            sp = os.path.join(a.runs, r, "summary.json")
            if not os.path.isfile(sp):
                continue
            s = json.load(open(sp))
            per[r] = {g["gate"]: g["status"] for g in s["results"]}
            walls += s["wall_secs"]
            if s.get("verify"):
                regressed_union |= set(s["verify"]["regressed"])
            st = os.path.join(a.runs, r, "strict.json")
            if os.path.isfile(st):
                for row in json.load(open(st)):
                    strict_union[row["addr"].lower()] = row
            sj = os.path.join(a.runs, r, "sections.json")
            if os.path.isfile(sj):
                sec_union |= set(json.load(open(sj))["changed"])
        tip_strict = {r["addr"].lower(): r for r in strict_tip}
        missing_strict = sorted(set(strict_union) - set(tip_strict))
        strict_fail_tip = sorted(k for k, v in tip_strict.items() if v["raw"] or v["strict"])
        rep = dict(base=base, tip=tip, batch_wall=round(wall, 1), per_packet_wall_sum=round(walls, 1),
                   batch_gates={k: v["status"] for k, v in batch.items()},
                   per_packet_gates=per,
                   verify_rows_tip=summ["verify"]["rows"] if summ.get("verify") else None,
                   regressed_tip=summ["verify"]["regressed"] if summ.get("verify") else None,
                   regressed_union=sorted(regressed_union),
                   strict_rows_tip=len(tip_strict), strict_rows_union=len(strict_union),
                   strict_missing_at_tip=missing_strict, strict_fail_tip=strict_fail_tip,
                   sections_changed_tip=sorted(sec_tip), sections_changed_union=sorted(sec_union),
                   sections_only_tip=sorted(sec_tip - sec_union), sections_only_union=sorted(sec_union - sec_tip))
        # equivalence: the tip verdict of every gate equals the union of the per-packet verdicts
        # (FAIL iff some packet failed it), and the row/section sets agree
        union_fail = {g for v in per.values() for g, st in v.items() if st == "FAIL"}
        tip_fail = {g for g, v in batch.items() if v["status"] == "FAIL"}
        rep["gate_verdicts_equal"] = tip_fail == union_fail
        rep["gates_failing_tip"], rep["gates_failing_union"] = sorted(tip_fail), sorted(union_fail)
        agree = (not missing_strict and not strict_fail_tip and not rep["regressed_tip"] and not regressed_union
                 and sec_tip == sec_union and tip_fail == union_fail)
        rep["verdict"] = "AGREE" if agree else "DISAGREE"
        json.dump(rep, open(os.path.join(work, "prove_batch.json"), "w"), indent=1)
        print(json.dumps({k: v for k, v in rep.items() if k not in ("sections_changed_tip", "sections_changed_union", "per_packet_gates")}, indent=1))
        print("per-packet gates:", {r: [g for g, s in v.items() if s == "FAIL"] for r, v in per.items()})
        print("sections changed: tip %d TUs, union %d TUs" % (len(sec_tip), len(sec_union)))
        print("%s  (batch full gate %.0fs vs %d per-packet full gates summing %.0fs)  report %s" % (
            rep["verdict"], wall, len(per), walls, os.path.join(work, "prove_batch.json")))
        return 0 if agree else 1
    finally:
        D.remove_worktree(a.repo, wt)


if __name__ == "__main__":
    sys.exit(main())
