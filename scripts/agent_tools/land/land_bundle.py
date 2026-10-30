#!/usr/bin/env python3
"""land_bundle.py: land several READY packets as one verified bundle.

    land_bundle.sh [options] PACKET...        (PACKET = a READY dir, or its parent)

  1. A scratch worktree is cut from --base (default: HEAD of --repo). Each packet is
     applied in order: `git apply --3way --index` of patch.diff (its
     scripts/data/match_manifest.json hunks excluded), then its manifest_delta.json
     merged into the manifest with collision checks (same address added by two
     packets, add over an existing row, change/remove of a missing row, old-symbol
     mismatch, rows naming a missing TU). A packet that does not apply or collides is
     REJECTED and the bundle continues without it. After each packet a throwaway
     commit records the prefix state.
  2. The full gates (gates.py --mode full) run ONCE on the whole bundle.
  3. If a gate fails, the culprit is bisected by running the failing gates (incremental
     mode) on prefixes of the bundle; the culprit is dropped and reported, and the
     full gates run again on the remainder (up to --max-rounds times). A dropped
     packet is also run alone against the base, to tell "broken" from "interacts".
  4. Only after the bundle passes are the real commits created: one per packet, with
     the packet's proposed message, the tree of that prefix, and .github/assets/
     progress.svg regenerated from that prefix's manifest (what scripts/hooks/pre-commit
     does). They go on branch --branch. With --ff the target repo's checked-out branch
     is then fast-forwarded in a single `git merge --ff-only` after safety checks.

Nothing touches --repo's working tree unless --ff is given and every check passes
(HEAD still equals the base, touched tracked files clean, no incoming path lands on an
untracked/ignored file or through a symlink).
"""
import argparse
import json
import os
import re
import subprocess
import sys
import time

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
import landlib as L  # noqa: E402

MANIFEST = L.MANIFEST


def say(*a):
    print(*a, flush=True)


class Bundle:
    def __init__(self, args):
        self.a = args
        self.repo = os.path.abspath(args.repo)
        self.base = L.rev_parse(self.repo, args.base or "HEAD")
        self.id = time.strftime("%Y%m%d-%H%M%S")
        self.work = os.path.abspath(args.work or os.path.join(L.RUNS, "bundle-" + self.id))
        os.makedirs(self.work, exist_ok=True)
        self.wts = []                      # scratch worktrees we created (only these are ever removed)
        self.packets = []
        self.report = []
        self.round = 0

    # ------------------------------------------------------------- worktrees
    def scratch(self, name):
        wt = os.path.join(self.work, name)
        L.git(self.repo, "worktree", "add", "--detach", wt, self.base)
        os.symlink(L.TOOLCHAIN, os.path.join(wt, "toolchain"))
        self.wts.append(wt)
        return wt

    def cleanup(self):
        if self.a.keep:
            say("kept scratch worktrees under", self.work)
            return
        for wt in self.wts:
            if wt.startswith(self.work + os.sep) and os.path.isdir(wt):
                if os.path.islink(os.path.join(wt, "toolchain")):
                    os.unlink(os.path.join(wt, "toolchain"))
                L.git(self.repo, "worktree", "remove", "--force", wt, check=False)
        L.git(self.repo, "worktree", "prune", check=False)
        for ref in L.git(self.repo, "for-each-ref", "--format=%(refname)", "refs/land-wip/%s/" % self.id).split():
            L.git(self.repo, "update-ref", "-d", ref)

    # ------------------------------------------------------------- applying
    def apply_packets(self, packets, tag):
        """Fresh scratch worktree, apply packets in order. Returns (wt, applied, rejected)."""
        wt = self.scratch("wt-%s" % tag)
        self.touched = {}
        applied, rejected = [], []
        # each delta is merged into the manifest as the previous packets left it
        for p in packets:
            ok, why = self.apply_one(wt, p, len(applied) + 1, tag)
            if ok:
                applied.append(p)
            else:
                rejected.append((p, why))
                say("  REJECT %-28s %s" % (p.name, why))
        return wt, applied, rejected

    def apply_one(self, wt, p, k, tag):
        errs = p.validate()
        if errs:
            return False, "; ".join(errs)
        msg = p.commit_message()
        if not msg:
            return False, "no 'Proposed commit message' found in README.md"
        ptxt = open(p.patch, errors="replace").read()
        if re.search(r"^(new file mode|old mode|new mode|deleted file mode) 120000", ptxt, re.M) or \
                re.search(r"^index [0-9a-f]+\.\.[0-9a-f]+ 120000", ptxt, re.M):
            return False, "patch creates, changes or deletes a symlink (mode 120000)"
        allowed = [re.compile(x) for x in L.ALLOWED_PATHS + list(self.a.allow_path)]
        bad = [f for f in p.patch_files() if not any(x.search(f) for x in allowed)]
        if bad:
            return False, "patch touches paths outside the allowed set (use --allow-path to permit): " + ", ".join(bad[:4])
        head = L.git(wt, "rev-parse", "HEAD").strip()
        r = subprocess.run(["git", "-C", wt, "apply", "--3way", "--index", "--whitespace=nowarn",
                            "--exclude=" + MANIFEST, "--exclude=" + L.BINDINGS, p.patch], capture_output=True, text=True)
        if r.returncode:
            L.git(wt, "reset", "-q", "--hard", head)
            L.git(wt, "clean", "-q", "-fd", "--", "match")      # scratch worktree only
            errl = [x for x in r.stderr.splitlines() if x.startswith(("error:", "fatal:"))] or r.stderr.splitlines() or ["?"]
            return False, "patch does not apply: %s%s" % (errl[0][:160], " (+%d more errors)" % (len(errl) - 1) if len(errl) > 1 else "")
        man, _ = L.load_manifest(os.path.join(wt, MANIFEST))
        trial = dict(self.touched)
        merged, errs, warns = L.merge_deltas(man, [(p.name, p.delta())], touched=trial)
        for w in warns[:5]:
            say("  warning:", w)
        if errs:
            L.git(wt, "reset", "-q", "--hard", head)
            return False, "manifest delta collides: " + "; ".join(errs[:4]) + (" (+%d more)" % (len(errs) - 4) if len(errs) > 4 else "")
        tracked = set(L.TreeFiles(wt).paths)
        missing = sorted({r["tu"] for _, d in [(0, p.delta())] for r in self.delta_rows(d)
                          if r["tu"] not in tracked and r.get("status")})
        if missing:
            L.git(wt, "reset", "-q", "--hard", head)
            return False, "delta rows name TUs not present after the patch: " + ", ".join(missing[:3])
        self.touched = trial
        open(os.path.join(wt, MANIFEST), "w").write(L.dump_manifest(merged))
        L.git(wt, "add", "--", MANIFEST)
        add = p.bindings_delta()
        corr, corr_errs = p.binding_corrections()
        nb, bad = L.merge_bindings(wt, add, corr)
        bad = ["binding_corrections.json: " + e for e in corr_errs] + bad
        bad = list(p.binding_conflicts) + bad
        if bad:
            L.git(wt, "reset", "-q", "--hard", head)
            return False, "packet bindings (delta file / patch.diff hunks) contradict the central bindings: " + "; ".join(bad[:4])
        if nb:
            L.git(wt, "add", "--", L.BINDINGS)
            say("  %d central bindings added or corrected from the packet (delta file, patch.diff hunks, binding_corrections.json)" % nb)
        for c in corr:
            say("  CORRECTED central binding %s: %s -> %s (%s)" % (c["symbol"], c["old_addr"], c["new_addr"], c["evidence"][:100]))
        L.git(wt, "commit", "-q", "--no-verify", "-m", "wip packet %d %s" % (k, p.name))
        sha = L.git(wt, "rev-parse", "HEAD").strip()
        L.git(self.repo, "update-ref", "refs/land-wip/%s/%s-%d" % (self.id, tag, k), sha)
        p.wip = sha
        p.msg = msg
        return True, ""

    @staticmethod
    def delta_rows(d):
        if isinstance(d, list):
            return [r for r in d if isinstance(r, dict) and "tu" in r]
        return list(d.get("add", [])) + [m["row"] for m in d.get("modify", [])]

    # ------------------------------------------------------------- gates
    def gates(self, wt, mode, tag, packets, only=None, force_tests=False, msg_text=None):
        run = os.path.join(self.work, "gates-%s" % tag)
        mapfiles = list(self.a.symmap)
        waive = set()
        for p in packets:
            mapfiles += p.symbol_map_files()
            waive |= p.waived_strict()
        msgf = os.path.join(self.work, "msg-%s.txt" % tag)
        open(msgf, "w").write(msg_text if msg_text is not None else "\n".join(p.msg for p in packets))
        cmd = [sys.executable, os.path.join(HERE, "gates.py"), "--tree", wt, "--base", self.base, "--mode", mode,
               "--run", run, "--msg", msgf, "--jobs", str(self.a.jobs)]
        for mf in mapfiles:
            cmd += ["--symmap", mf]
        for w in sorted(waive):
            cmd += ["--waive", hex(w)]
        for ap in self.a.allow_path:
            cmd += ["--allow-path", ap]
        for aw in list(self.a.allow_word) + [w for p in packets for w in p.allowed_words()]:
            cmd += ["--allow-word", aw]
        if only:
            cmd += ["--only", ",".join(only)]
        if self.a.no_promote:
            cmd.append("--no-promote")
        rc, text = L.run(cmd, cwd=wt, env=L.toolenv(), log=os.path.join(self.work, "gates-%s.out" % tag))
        res = {}
        sp = os.path.join(run, "summary.json")
        if os.path.isfile(sp):
            res = {g["gate"]: g for g in json.load(open(sp))["results"]}
        for ln in text.splitlines():
            if ln.startswith(("GATE ", "RESULT", "changed paths")):
                say("   ", ln)
        failed = [g for g, v in res.items() if v["status"] == "FAIL"]
        if rc and not failed:
            failed = ["(gates.py exited %d: see %s)" % (rc, os.path.join(self.work, "gates-%s.out" % tag))]
        return rc == 0, failed, run

    def checkout(self, wt, sha):
        L.git(wt, "checkout", "-q", "--detach", sha)

    # ------------------------------------------------------------- bisect
    def bisect(self, packets, failed_gates):
        """Smallest prefix k whose incremental gates (failed ones) fail. Returns index or None."""
        names = [g for g in failed_gates if re.match(r"^[a-z]+$", g)]
        only = sorted(set(names) | {"static", "compile"})
        say("  bisecting on prefixes with gates: %s (inc mode)" % ",".join(only))
        wt = self.scratch("wt-bisect%d" % self.round)
        cache, fails = {}, {}

        def bad(k):
            if k == 0:
                return False
            if k in cache:
                return cache[k]
            self.checkout(wt, packets[k - 1].wip)
            ok, f, _ = self.gates(wt, "inc", "bisect%d-p%d" % (self.round, k), packets[:k], only=only)
            cache[k] = not ok
            fails[k] = f
            say("    prefix %d (%s): %s" % (k, packets[k - 1].name, "FAIL " + ",".join(f) if not ok else "pass"))
            return cache[k]

        if not bad(len(packets)):
            return None, []        # not reproducible incrementally (e.g. a full-only effect)
        lo, hi = 0, len(packets)   # lo passes, hi fails
        while hi - lo > 1:
            mid = (lo + hi) // 2
            if bad(mid):
                hi = mid
            else:
                lo = mid
        return hi - 1, fails[hi]

    # ------------------------------------------------------------- finalize
    def make_commits(self, packets):
        """One real commit per packet, created from the WIP trees. Returns the tip sha."""
        parent = self.base
        out = []
        for p in packets:
            tree = L.git(self.repo, "rev-parse", p.wip + "^{tree}").strip()
            tree = self.with_progress_svg(p.wip, tree)
            msgf = os.path.join(self.work, "commitmsg-%s.txt" % p.name)
            open(msgf, "w").write(p.msg)
            if "Co-Authored-By:" not in p.msg:
                say("  note: %s message has no Co-Authored-By trailer" % p.name)
            parent = L.git(self.repo, "commit-tree", tree, "-p", parent, "-F", msgf).strip()
            out.append((p.name, parent))
        return out

    def with_progress_svg(self, wip, tree):
        """Regenerate progress.svg from this prefix's manifest (the pre-commit hook's job)."""
        tmp = os.path.join(self.work, "svg")
        os.makedirs(tmp, exist_ok=True)
        files = {}
        for name, dst in ((MANIFEST, "manifest.json"), ("scripts/data/progress_totals.json", "totals.json"),
                          ("scripts/orchestration/progress_svg.py", "progress_svg.py")):
            files[dst] = L.git(self.repo, "show", "%s:%s" % (wip, name), text=False)
            open(os.path.join(tmp, dst), "wb").write(files[dst])
        svg = os.path.join(tmp, "progress.svg")
        r = subprocess.run([sys.executable, "-I", os.path.join(tmp, "progress_svg.py"), svg,
                            "--manifest", os.path.join(tmp, "manifest.json"),
                            "--totals", os.path.join(tmp, "totals.json")], capture_output=True)
        if r.returncode:
            raise RuntimeError("progress_svg failed: " + r.stderr.decode()[-300:])
        blob = L.git(self.repo, "hash-object", "-w", svg).strip()
        idx = os.path.join(self.work, "index.tmp")
        if os.path.exists(idx):
            os.unlink(idx)
        env = dict(os.environ, GIT_INDEX_FILE=idx)
        subprocess.run(["git", "-C", self.repo, "read-tree", tree], env=env, check=True)
        subprocess.run(["git", "-C", self.repo, "update-index", "--add", "--cacheinfo",
                        "100644,%s,.github/assets/progress.svg" % blob], env=env, check=True)
        out = subprocess.run(["git", "-C", self.repo, "write-tree"], env=env, check=True, capture_output=True, text=True)
        return out.stdout.strip()

    def ff_guard(self, tip):
        """Refuse the fast-forward unless it is safe. Returns list of problems."""
        probs = []
        head = L.git(self.repo, "rev-parse", "HEAD").strip()
        if head != self.base:
            probs.append("repo HEAD %s moved from base %s; rebase/re-run the bundle on the new HEAD" % (head[:9], self.base[:9]))
        out = L.git(self.repo, "diff", "--name-status", "--no-renames", "-z", self.base, tip, text=False)
        parts = [x.decode() for x in out.split(b"\0") if x]
        ent = [(parts[i][0], parts[i + 1]) for i in range(0, len(parts) - 1, 2)]
        modified = [n for s, n in ent if s != "A"]
        if modified:
            st = L.git(self.repo, "status", "--porcelain", "-z", "--", *modified, text=False).split(b"\0")
            for rec in st:
                if len(rec) > 3:
                    probs.append("tracked file has local changes and would be overwritten: " + rec[3:].decode())
        for s, n in ent:
            full = os.path.join(self.repo, n)
            if s == "A" and os.path.lexists(full):
                probs.append("incoming path would land on an untracked/ignored %s: %s" % (
                    "directory" if os.path.isdir(full) and not os.path.islink(full) else "file or link", n))
            parts_ = n.split("/")
            for i in range(1, len(parts_)):
                d = os.path.join(self.repo, *parts_[:i])
                if os.path.islink(d):
                    probs.append("incoming path goes through a symlink: " + n)
                    break
                if os.path.lexists(d) and not os.path.isdir(d):
                    probs.append("incoming path has a non-directory in the way: " + n)
                    break
            if s != "A" and os.path.islink(full):
                probs.append("incoming path is an existing symlink: " + n)
        return sorted(set(probs))


def resolve_packet(path):
    path = os.path.abspath(path)
    if os.path.isfile(os.path.join(path, "patch.diff")):
        return L.Packet(path)
    if os.path.isfile(os.path.join(path, "READY", "patch.diff")):
        return L.Packet(os.path.join(path, "READY"))
    raise SystemExit("not a READY packet (no patch.diff): " + path)


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("packets", nargs="+")
    ap.add_argument("--repo", default=L.MAIN_REPO)
    ap.add_argument("--base", help="base rev (default: HEAD of --repo)")
    ap.add_argument("--branch", help="branch to create for the result (default land/<timestamp>)")
    ap.add_argument("--work", help="work dir for scratch worktrees and logs")
    ap.add_argument("--ff", action="store_true", help="fast-forward the repo's checked-out branch afterwards")
    ap.add_argument("--jobs", type=int, default=min(16, (os.cpu_count() or 8) // 2))
    ap.add_argument("--max-rounds", type=int, default=4)
    ap.add_argument("--gate-mode", choices=["full", "inc"], default="full", help="mode of the bundle gate (default full)")
    ap.add_argument("--apply-only", action="store_true", help="apply and stop (no gates, no commits)")
    ap.add_argument("--allow-path", action="append", default=[])
    ap.add_argument("--allow-word", action="append", default=[], help="regex of added lines the word check ignores")
    ap.add_argument("--symmap", action="append", default=[], help="extra symbol map JSON for the strict relocation check")
    ap.add_argument("--status-para", help="narrative paragraph file: rotate STATUS.md into the LAST commit")
    ap.add_argument("--status-prev-title", help="title for the snapshot being archived (required with --status-para)")
    ap.add_argument("--no-promote", action="store_true")
    ap.add_argument("--no-solo", action="store_true", help="skip the solo check of dropped packets")
    ap.add_argument("--keep", action="store_true")
    a = ap.parse_args(argv)
    t0 = time.time()
    B = Bundle(a)
    if a.status_para and not a.status_prev_title:
        raise SystemExit("--status-para needs --status-prev-title")
    packets = [resolve_packet(p) for p in a.packets]
    names = [p.name for p in packets]
    if len(set(names)) != len(names):
        raise SystemExit("duplicate packet names: " + ", ".join(sorted(n for n in names if names.count(n) > 1)))
    say("bundle %s: base %s, %d packets, work %s" % (B.id, B.base[:9], len(packets), B.work))
    if a.ff:
        head = L.git(B.repo, "rev-parse", "HEAD").strip()
        if head != B.base:
            say("FAST-FORWARD REFUSED: repo HEAD %s moved from base %s; re-run with --base HEAD" % (head[:9], B.base[:9]))
            return 3
    dropped = []
    try:
        remaining = list(packets)
        final_run = None
        for B.round in range(1, a.max_rounds + 1):
            say("== round %d: applying %d packets" % (B.round, len(remaining)))
            wt, applied, rejected = B.apply_packets(remaining, "r%d" % B.round)
            for p, why in rejected:
                dropped.append((p.name, "apply: " + why))
            if not applied:
                say("nothing left to land")
                break
            say("  applied: " + ", ".join(p.name for p in applied))
            if a.apply_only:
                say("apply-only: worktree %s" % wt)
                a.keep = True
                return 0
            say("== round %d: %s gates on the bundle (%d packets)" % (B.round, a.gate_mode, len(applied)))
            ok, failed, run = B.gates(wt, a.gate_mode, "r%d" % B.round, applied)
            if ok:
                final_run = run
                remaining = applied
                break
            say("  gates failed: %s" % ", ".join(failed))
            k, why = B.bisect(applied, failed)
            if k is None:
                say("  failure does not reproduce on the full prefix in incremental mode, or applies to the bundle as a whole")
                dropped.append(("(bundle)", "gates failed (%s) but no packet could be isolated" % ",".join(failed)))
                remaining = []
                break
            culprit = applied[k]
            say("  CULPRIT: %s (prefix %d is the first failing prefix; gates: %s)" % (culprit.name, k + 1, ",".join(why)))
            failed = why
            dropped.append((culprit.name, "fails %s at prefix %d" % (",".join(why), k + 1)))
            if not a.no_solo:
                sw, sa, sr = B.apply_packets([culprit], "solo-%s" % culprit.name)
                if sa:
                    sok, sf, _ = B.gates(sw, "inc", "solo-%s" % culprit.name, sa,
                                         only=sorted({g for g in failed if re.match(r"^[a-z]+$", g)} | {"static", "compile"}))
                    say("  solo check against base: %s" % ("also fails (packet itself is broken)" if not sok
                                                           else "passes alone (it interacts with the earlier packets)"))
                    dropped[-1] = (culprit.name, dropped[-1][1] + ("; solo: " + ("FAIL" if not sok else "pass")))
            remaining = [p for p in applied if p is not culprit]
            if not remaining:
                break
            # everything after the culprit may depend on it: the next round re-applies from scratch
        else:
            say("max rounds reached without a passing bundle")
            remaining = []
        if not remaining or final_run is None:
            say("RESULT: no bundle landed. dropped: %s" % json.dumps(dropped))
            return 1
        if a.status_para:
            r = subprocess.run([sys.executable, os.path.join(HERE, "status_rotate.py"), wt, "--prev-title", a.status_prev_title,
                                "--para-file", a.status_para, "--tests-log", os.path.join(final_run, "tests.log")],
                               capture_output=True, text=True)
            if r.returncode:
                say("status rotation failed:", r.stderr.strip()[-300:])
                return 4
            L.git(wt, "add", "--", "STATUS.md")
            L.git(wt, "commit", "-q", "--no-verify", "-m", "wip status")
            remaining[-1].wip = L.git(wt, "rev-parse", "HEAD").strip()
            say("STATUS.md rotated into the last commit:", r.stdout.strip())
        say("== bundle passed; creating %d commits" % len(remaining))
        commits = B.make_commits(remaining)
        tip = commits[-1][1]
        branch = a.branch or "land/%s" % B.id
        L.git(B.repo, "update-ref", "refs/heads/" + branch, tip)
        for n, c in commits:
            say("  %s  %s" % (c[:10], n))
        say("branch %s -> %s" % (branch, tip[:10]))
        if a.ff:
            probs = B.ff_guard(tip)
            if probs:
                say("FAST-FORWARD REFUSED:")
                for pr in probs:
                    say("  " + pr)
                say("branch %s holds the result; repo untouched" % branch)
                return 3
            r = subprocess.run(["git", "-C", B.repo, "merge", "--ff-only", branch], capture_output=True, text=True)
            say("fast-forward:", (r.stdout + r.stderr).strip().splitlines()[0] if (r.stdout + r.stderr).strip() else "")
            if r.returncode:
                return 3
        else:
            say("not fast-forwarded. To land: git -C %s merge --ff-only %s" % (B.repo, branch))
        json.dump({"base": B.base, "branch": branch, "tip": tip, "commits": commits, "dropped": dropped,
                   "gate_run": final_run, "wall_secs": round(time.time() - t0, 1)},
                  open(os.path.join(B.work, "result.json"), "w"), indent=1)
        say("RESULT: landed %d of %d packets%s in %.0fs; dropped: %s" % (
            len(remaining), len(packets), " (ff done)" if a.ff else "", time.time() - t0, json.dumps(dropped)))
        return 0
    finally:
        B.cleanup()


if __name__ == "__main__":
    sys.exit(main())
