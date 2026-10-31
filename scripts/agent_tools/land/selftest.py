#!/usr/bin/env python3
"""selftest.py: end-to-end scenarios for land_bundle against a throwaway clone.

    selftest.py [--repo CLONE] [--keep]

Builds synthetic READY packets from the clone's HEAD, then checks that land_bundle
  * lands the good ones (one commit each, in order),
  * rejects manifest collisions at apply time (explicit add over a row; two packets writing one address),
  * bisects and drops: a matched-function regression (verify), a forbidden word
    (words), a broken layout assert (compile), a duplicate address claim (dups),
  * refuses a fast-forward when the target repo's HEAD moved, or an incoming path
    lands on an untracked file, and performs one when safe.
REPO must be a clone you do not mind creating branches in (default: a fresh clone
of the main repo under /tmp). It never touches the main repo.
"""
import json
import os
import re
import shutil
import subprocess
import sys
import tempfile

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
# Neutral stand-in word list; the real list is local-only (see landlib.load_forbid_re).
import tempfile as _tf
_wf = _tf.NamedTemporaryFile("w", suffix=".txt", delete=False)
_wf.write("zzforbidden\n"); _wf.close()
os.environ["GAG_FORBIDDEN_WORDS"] = _wf.name
import atexit as _ax
_ax.register(os.unlink, _wf.name)
import landlib as L  # noqa: E402

FAILS = []


def check(cond, what):
    print("  %s %s" % ("ok  " if cond else "FAIL", what), flush=True)
    if not cond:
        FAILS.append(what)


def sh(*a, cwd=None, check_=True):
    p = subprocess.run(a, cwd=cwd, capture_output=True, text=True)
    if check_ and p.returncode:
        raise RuntimeError("%s: %s" % (a, p.stderr))
    return p.stdout


def make_packet(repo, outdir, name, edits, delta=None, msg=None, new_files=None):
    """edits: {path: (old, new)}; new_files: {path: text}. Returns READY dir."""
    wt = tempfile.mkdtemp(prefix="synth_", dir=outdir)
    shutil.rmtree(wt)
    sh("git", "-C", repo, "worktree", "add", "-q", "--detach", wt, "HEAD")
    try:
        for p, (old, new) in (edits or {}).items():
            t = open(os.path.join(wt, p)).read()
            assert old in t, (p, old)
            open(os.path.join(wt, p), "w").write(t.replace(old, new, 1))
        for p, t in (new_files or {}).items():
            os.makedirs(os.path.dirname(os.path.join(wt, p)), exist_ok=True)
            open(os.path.join(wt, p), "w").write(t)
            sh("git", "-C", wt, "add", "--", p)
        patch = sh("git", "-C", wt, "diff", "--binary", "HEAD")
    finally:
        sh("git", "-C", repo, "worktree", "remove", "--force", wt)
    d = os.path.join(outdir, name, "READY")
    os.makedirs(d, exist_ok=True)
    open(os.path.join(d, "patch.diff"), "w").write(patch)
    json.dump(delta or [], open(os.path.join(d, "manifest_delta.json"), "w"))
    open(os.path.join(d, "README.md"), "w").write(
        "# %s\n\nBase: main HEAD\n\nProposed commit message:\n\n    %s\n\n    Synthetic selftest packet.\n\n"
        "    Co-Authored-By: selftest <noreply@example.invalid>\n" % (name, msg or "Selftest packet " + name))
    return d


def bundle(repo, work, packets, *extra):
    cmd = [sys.executable, os.path.join(HERE, "land_bundle.py"), "--repo", repo, "--work", work, *extra, *packets]
    p = subprocess.run(cmd, capture_output=True, text=True, env=L.toolenv())
    return p.returncode, p.stdout + p.stderr


def main():
    ap = __import__("argparse").ArgumentParser()
    ap.add_argument("--repo")
    ap.add_argument("--keep", action="store_true")
    a = ap.parse_args()
    root = tempfile.mkdtemp(prefix="landselftest_")
    repo = a.repo or os.path.join(root, "clone")
    if not a.repo:
        sh("git", "clone", "-q", "--no-hardlinks", L.MAIN_REPO, repo)
    head = sh("git", "-C", repo, "rev-parse", "HEAD").strip()
    P = os.path.join(root, "packets")
    os.makedirs(P)
    cls = "match/core/abstract_class_slots.cpp"
    cls2 = "match/core/AbsType.cpp"
    row = {"tu": cls, "addr": "0x410450", "sym": "?IsDirty@AbstractClass@@UAGJXZ", "len": "0x11",
           "name": "dup", "status": "matched", "pct": 100}
    pk = {
        "good1": make_packet(repo, P, "good1", {cls: ("// FUNCTION: GAMEMD 0x410440", "// selftest note one\n// FUNCTION: GAMEMD 0x410440")}),
        "good2": make_packet(repo, P, "good2", {cls2: ("// FUNCTION:", "// selftest note two\n// FUNCTION:")}),
        "regress": make_packet(repo, P, "regress", {cls: ("return !Dirty;", "return Dirty;")}),
        "words": make_packet(repo, P, "words", {cls: ("// FUNCTION: GAMEMD 0x410470", "// as zzforbidden did\n// FUNCTION: GAMEMD 0x410470")}),
        "layout": make_packet(repo, P, "layout", {"match/_layout/abstract_class.h": (
            "GG_STATIC_ASSERT(offsetof(AbstractClass, UniqueID)      == 0x10);",
            "GG_STATIC_ASSERT(offsetof(AbstractClass, UniqueID)      == 0x14);")}),
        "dupclaim": make_packet(repo, P, "dupclaim", {}, new_files={
            "match/core/selftest_dup_claim.cpp": "// SPDX-License-Identifier: GPL-3.0-or-later\n// Provenance: own-binary-via-Ghidra\n"
            "// FUNCTION: GAMEMD 0x410450\nint selftest_dup_claim() { return 1; }\n"}),
        "collide": make_packet(repo, P, "collide", {cls2: ("// FUNCTION:", "// collide note\n// FUNCTION:")}, delta=[dict(row, op="add")]),
        "adda": make_packet(repo, P, "adda", {cls2: ("// FUNCTION:", "// add a\n// FUNCTION:")}, delta=[dict(row, addr="0x4FFF0000", name="a")]),
        "addb": make_packet(repo, P, "addb", {cls: ("// FUNCTION: GAMEMD 0x410480", "// add b\n// FUNCTION: GAMEMD 0x410480")}, delta=[dict(row, addr="0x4FFF0000", name="b")]),
    }
    print("== scenario 1: good1 + good2 land, one commit each")
    rc, out = bundle(repo, os.path.join(root, "w1"), [pk["good1"], pk["good2"]], "--branch", "t/s1")
    check(rc == 0 and "landed 2 of 2" in out, "two good packets land (rc=%d)" % rc)
    log = sh("git", "-C", repo, "log", "--format=%s", head + "..t/s1").splitlines()
    check(log == ["Selftest packet good2", "Selftest packet good1"], "one commit per packet, in order: %s" % log)
    check(sh("git", "-C", repo, "rev-parse", "HEAD").strip() == head, "repo HEAD untouched without --ff")

    print("== scenario 2: manifest collision rejected at apply")
    rc, out = bundle(repo, os.path.join(root, "w2"), [pk["good1"], pk["collide"]], "--branch", "t/s2")
    check(rc == 0 and "REJECT collide" in out and "add of present address" in out, "collision named and packet rejected")
    check("landed 1 of 2" in out, "remaining packet still lands")
    rc, out = bundle(repo, os.path.join(root, "w2b"), [pk["adda"], pk["addb"]], "--branch", "t/s2b")
    check("REJECT addb" in out and "already modified differently" in out, "two packets writing one new address: second rejected")

    print("== scenario 3: bisect drops regress and words, keeps the good ones")
    rc, out = bundle(repo, os.path.join(root, "w3"), [pk["good1"], pk["regress"], pk["good2"], pk["words"]], "--branch", "t/s3")
    check("CULPRIT: regress" in out, "regress identified (gates: verify)")
    check("CULPRIT: words" in out, "words identified")
    check("landed 2 of 4" in out, "two packets land: " + (re.findall(r"RESULT: .*", out) or ["?"])[-1][:120])
    log = sh("git", "-C", repo, "log", "--format=%s", head + "..t/s3").splitlines() if "t/s3" in sh("git", "-C", repo, "branch", "--list", "t/s3") else []
    check(log == ["Selftest packet good2", "Selftest packet good1"], "result commits: %s" % log)

    print("== scenario 4: layout assert break and duplicate claim")
    rc, out = bundle(repo, os.path.join(root, "w4"), [pk["good1"], pk["layout"], pk["dupclaim"]], "--branch", "t/s4")
    check("CULPRIT: layout" in out, "layout break identified")
    check("CULPRIT: dupclaim" in out or "dupclaim" in out, "duplicate claim identified")

    print("== scenario 5: fast-forward guards")
    rc, out = bundle(repo, os.path.join(root, "w5"), [pk["good1"]], "--branch", "t/s5", "--ff")
    check(rc == 0 and "fast-forward:" in out and sh("git", "-C", repo, "rev-parse", "HEAD").strip() == sh("git", "-C", repo, "rev-parse", "t/s5").strip(),
          "clean ff succeeds")
    sh("git", "-C", repo, "reset", "-q", "--hard", head)
    # untracked file where a new file would land
    nf = make_packet(repo, P, "newfile", {}, new_files={"match/core/selftest_new_file.cpp": "// SPDX-License-Identifier: GPL-3.0-or-later\n// Provenance: own-binary-via-Ghidra\nint selftest_new_file() { return 2; }\n"})
    open(os.path.join(repo, "match/core/selftest_new_file.cpp"), "w").write("local work\n")
    rc, out = bundle(repo, os.path.join(root, "w6"), [nf], "--branch", "t/s6", "--ff")
    check(rc == 3 and "untracked/ignored file" in out, "ff refused: incoming path would overwrite an untracked file")
    check(open(os.path.join(repo, "match/core/selftest_new_file.cpp")).read() == "local work\n", "the untracked file is intact")
    os.unlink(os.path.join(repo, "match/core/selftest_new_file.cpp"))
    # ignored file (the dangerous case: git would delete it silently)
    open(os.path.join(repo, ".git/info/exclude"), "a").write("\nmatch/core/selftest_new_file.cpp\n")
    open(os.path.join(repo, "match/core/selftest_new_file.cpp"), "w").write("ignored local work\n")
    rc, out = bundle(repo, os.path.join(root, "w7"), [nf], "--branch", "t/s7", "--ff")
    check(rc == 3 and "untracked/ignored file" in out, "ff refused: incoming path would overwrite an IGNORED file")
    check(open(os.path.join(repo, "match/core/selftest_new_file.cpp")).read() == "ignored local work\n", "the ignored file is intact")
    os.unlink(os.path.join(repo, "match/core/selftest_new_file.cpp"))
    # HEAD moved
    sh("git", "-C", repo, "-c", "user.name=t", "-c", "user.email=t@example.invalid", "commit", "-q", "--allow-empty", "-m", "moved")
    rc, out = bundle(repo, os.path.join(root, "w8"), [pk["good1"]], "--branch", "t/s8", "--ff", "--base", head)
    check(rc == 3 and "moved from base" in out, "ff refused when repo HEAD moved")
    print()
    print("SELFTEST %s (%d failed) work=%s" % ("PASS" if not FAILS else "FAIL", len(FAILS), root))
    if not a.keep and not FAILS:
        shutil.rmtree(root, ignore_errors=True)
    return 1 if FAILS else 0


if __name__ == "__main__":
    sys.exit(main())
