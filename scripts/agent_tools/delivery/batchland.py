#!/usr/bin/env python3
"""batchland.py: rebase N READY packets onto the tip and land them as one bundle.

    batchland.py PACKET... [--repo R] [--rev TIP] [--out DIR] [--jobs 4] [--gate-each]
                 [--ff] [--branch NAME] [--lint] [--status-para FILE --status-prev-title T]

  1. pktlint on every packet (fast; a packet with errors is dropped unless --no-lint);
  2. pktrebase of each packet onto the prefix (tip, then tip + packet 1, ...): patch
     re-targeted, new files merged into migrated TU files, delta re-pointed, re-keys,
     bindings derived, every matched row proved raw + strict. A packet with conflicts is
     dropped and its report kept; the rest continue on the shorter prefix;
  3. land/land_bundle.py on the rebased packets: applies them in order, runs the FULL gates
     ONCE on the bundle, bisects (incremental gates) and drops a culprit on failure, then
     makes one commit per packet (messages from the packets, progress.svg regenerated) on a
     branch; --ff fast-forwards the checked-out branch after land_bundle's safety checks;
  4. --gate-each: incremental gates on every commit of the branch against its parent, so each
     intermediate commit is individually proved as well (2-12 s each).

Proof strength: the full gate at the bundle tip re-proves every matched row of the tree
against the retail bytes, runs strict on every row the bundle adds or changes, and compares
every object's sections with the base; with --gate-each every intermediate commit also has
the incremental gate (the same oracle on its affected TUs). See tests/prove_batch.py for the
equivalence run on the b7 landing history.
"""
import argparse
import json
import os
import shutil
import subprocess
import sys
import time

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import dlib as D  # noqa: E402
import landlib as L  # noqa: E402
from pktlint import resolve_packet  # noqa: E402

HERE = os.path.dirname(os.path.abspath(__file__))


def say(*a):
    print(*a, flush=True)


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("packets", nargs="+")
    ap.add_argument("--repo", default=D.MAIN_REPO)
    ap.add_argument("--rev", default="HEAD")
    ap.add_argument("--out", help="work dir (default under dlib.SCRATCH)")
    ap.add_argument("--jobs", type=int, default=D.MAX_JOBS)
    ap.add_argument("--branch")
    ap.add_argument("--ff", action="store_true")
    ap.add_argument("--gate-each", action="store_true")
    ap.add_argument("--no-lint", action="store_true")
    ap.add_argument("--lint-warn-only", action="store_true", help="lint errors do not drop the packet")
    ap.add_argument("--status-para")
    ap.add_argument("--status-prev-title")
    ap.add_argument("--keep", action="store_true")
    a = ap.parse_args(argv)
    t0 = time.time()
    repo = os.path.abspath(a.repo)
    tip = L.rev_parse(repo, a.rev)
    jobs = min(a.jobs, D.MAX_JOBS)
    work = a.out or D.scratch_dir("batchland_")
    os.makedirs(work, exist_ok=True)
    D.register_created(work)
    say("batchland: tip %s, %d packets, work %s" % (tip[:10], len(a.packets), work))
    result = dict(tip=tip, packets=[], dropped=[], secs={})

    # 1. lint
    pk = [resolve_packet(p) for p in a.packets]
    keep = []
    t = time.time()
    for p in pk:
        if a.no_lint:
            keep.append(p)
            continue
        js = os.path.join(work, "lint-%s.json" % p.name)
        r = subprocess.run([sys.executable, os.path.join(HERE, "pktlint.py"), p.dir, "--repo", repo, "--rev", tip, "--json", js],
                           capture_output=True, text=True)
        errs = [x for x in json.load(open(js))["findings"] if x["level"] == "E"] if os.path.isfile(js) else [{"msg": "lint crashed"}]
        # 'migrated' and 'stale' are what pktrebase fixes; they do not drop a packet here
        hard = [x for x in errs if x.get("rule") not in ("migrated", "stale", "dupclaims")]
        say("  lint %-20s %d errors (%d need a human)" % (p.name, len(errs), len(hard)))
        if hard and not a.lint_warn_only:
            result["dropped"].append((p.name, "lint: " + "; ".join(x["msg"][:100] for x in hard[:3])))
            say("  DROP %s: %s" % (p.name, hard[0]["msg"][:160]))
        else:
            keep.append(p)
    result["secs"]["lint"] = round(time.time() - t, 1)

    # 2. rebase onto the growing prefix
    t = time.time()
    wt = D.add_worktree(repo, os.path.join(work, "prefix"), tip, toolchain=False)
    rebased = []
    try:
        prefix = tip
        for k, p in enumerate(keep, 1):
            out = os.path.join(work, "rebased-%s" % p.name)
            r = subprocess.run([sys.executable, os.path.join(HERE, "pktrebase.py"), p.dir, "--repo", repo, "--rev", prefix,
                                "--out", out, "--gates", "none", "--jobs", str(jobs)], capture_output=True, text=True)
            rep = json.load(open(os.path.join(out, "report.json"))) if os.path.isfile(os.path.join(out, "report.json")) else {}
            tail = [l for l in r.stdout.splitlines() if l.startswith(("  merged", "  remapped", "  re-keyed", "  proved", "  CONFLICT"))]
            for l in tail[:12]:
                say("   ", l)
            if r.returncode != 0 or not rep.get("ok"):
                result["dropped"].append((p.name, "rebase: %d conflicts (see %s)" % (len(rep.get("conflicts", [])), out)))
                say("  DROP %s: rebase conflicts" % p.name)
                continue
            # extend the prefix: apply the rebased patch + delta, wip commit
            rp = L.Packet(out)
            r2 = subprocess.run(["git", "-C", wt, "apply", "--index", "--whitespace=nowarn", rp.patch], capture_output=True, text=True)
            if r2.returncode:
                result["dropped"].append((p.name, "rebased patch does not apply on the prefix: " + r2.stderr[:200]))
                L.git(wt, "reset", "-q", "--hard", prefix)
                continue
            man, _ = L.load_manifest(os.path.join(wt, D.MANIFEST))
            merged, errs, _ = L.merge_deltas(man, [(p.name, rp.delta())])
            if errs:
                result["dropped"].append((p.name, "delta collides on the prefix: " + "; ".join(errs[:2])))
                L.git(wt, "reset", "-q", "--hard", prefix)
                continue
            open(os.path.join(wt, D.MANIFEST), "w").write(L.dump_manifest(merged))
            L.git(wt, "add", "--", D.MANIFEST)
            L.git(wt, "commit", "-q", "--no-verify", "-m", "wip %d %s" % (k, p.name))
            prefix = L.git(wt, "rev-parse", "HEAD").strip()
            rebased.append(out)
            result["packets"].append(dict(name=p.name, rebased=out, merged=rep.get("merged"), rekeyed=len(rep.get("rekeyed", [])),
                                          derived=len(rep.get("derived_bindings", {})), proved=rep.get("proved_rows")))
            say("  ok   %-20s prefix %s" % (p.name, prefix[:10]))
    finally:
        D.remove_worktree(repo, wt)
    result["secs"]["rebase"] = round(time.time() - t, 1)
    if not rebased:
        say("nothing to land; dropped: %s" % json.dumps(result["dropped"]))
        json.dump(result, open(os.path.join(work, "result.json"), "w"), indent=1)
        return 1

    # 3. land_bundle on the rebased packets (full gates once, bisect, commits)
    t = time.time()
    branch = a.branch or "land/batch-%s" % time.strftime("%Y%m%d-%H%M%S")
    cmd = [sys.executable, os.path.join(D.TOOLS, "land", "land_bundle.py"), *rebased, "--repo", repo, "--base", tip,
           "--branch", branch, "--jobs", str(jobs), "--work", os.path.join(work, "bundle")]
    if a.ff:
        cmd.append("--ff")
    if a.status_para:
        cmd += ["--status-para", a.status_para, "--status-prev-title", a.status_prev_title or ""]
    if a.keep:
        cmd.append("--keep")
    rc, text = L.run(cmd, cwd=repo, env=L.toolenv(), log=os.path.join(work, "land_bundle.log"))
    for l in text.splitlines():
        if l.startswith(("    GATE", "    RESULT", "  REJECT", "  CULPRIT", "RESULT", "branch", "fast-forward", "FAST-FORWARD", "  ")) and len(l) < 300:
            say("   ", l)
    result["secs"]["bundle"] = round(time.time() - t, 1)
    bres = os.path.join(work, "bundle", "result.json")
    if os.path.isfile(bres):
        result["bundle"] = json.load(open(bres))
    if rc:
        say("land_bundle failed (rc %d); log %s" % (rc, os.path.join(work, "land_bundle.log")))

    # 4. per-commit incremental gates
    if a.gate_each and rc == 0 and result.get("bundle"):
        t = time.time()
        wt2 = D.add_worktree(repo, os.path.join(work, "each"), tip)
        each = []
        try:
            parent = tip
            for name, sha in result["bundle"]["commits"]:
                L.git(wt2, "checkout", "-q", "--detach", sha)
                run = os.path.join(work, "each-%s" % name)
                maps = L.Packet(next(r for r in rebased if r.endswith(name))).symbol_map_files() if any(r.endswith(name) for r in rebased) else []
                c = [sys.executable, os.path.join(D.TOOLS, "land", "gates.py"), "--tree", wt2, "--base", parent, "--mode", "inc",
                     "--jobs", str(jobs), "--run", run]
                for m in maps:
                    c += ["--symmap", m]
                rc2, tx = L.run(c, cwd=wt2, env=L.toolenv(), log=run + ".log")
                res = [l for l in tx.splitlines() if l.startswith("RESULT")]
                each.append(dict(commit=sha, name=name, rc=rc2, result=res[-1] if res else ""))
                say("   each %-20s %s" % (name, res[-1] if res else "rc %d" % rc2))
                parent = sha
        finally:
            D.remove_worktree(repo, wt2)
        result["gate_each"] = each
        result["secs"]["gate_each"] = round(time.time() - t, 1)
    result["secs"]["total"] = round(time.time() - t0, 1)
    json.dump(result, open(os.path.join(work, "result.json"), "w"), indent=1)
    say("batchland: %d landed, %d dropped, %.0fs; result %s" % (
        len(result.get("bundle", {}).get("commits", [])), len(result["dropped"]), time.time() - t0, os.path.join(work, "result.json")))
    return rc


if __name__ == "__main__":
    sys.exit(main())
