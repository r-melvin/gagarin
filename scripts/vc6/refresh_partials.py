#!/usr/bin/env python3
# refresh_partials.py — re-measure the recorded pct of every non-matched entry.
#
# verify_all.py re-proves the 100% matches on every run, but a partial's
# percentage is just a note in the manifest; nothing re-measures it. That makes
# those numbers drift silently whenever the scoring rules change. Both harness
# fixes made this session moved them: rejecting register renames as relocations
# lowered scores that had been inflated. Retail spans must be validated in the
# manifest; Ghidra's reported function size can omit post-call blocks. Run this
# after any diff_retail.py change.
import argparse, json
import tempfile, os, subprocess, sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

MANIFEST = "scripts/data/match_manifest.json"


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--manifest', default=os.path.join(ROOT, MANIFEST))
    args = ap.parse_args()
    entries = json.load(open(args.manifest))
    changed = []
    for e in entries:
        if e["status"] == "matched":
            continue
        # Compile the translation unit fresh. An earlier version scored whatever
        # .obj happened to be sitting in build-vc6/, which is the same
        # stale-object fault that was fixed in match.sh: it silently rewrote
        # manifest percentages from a build that no longer matched the source.
        # It wrote 0.0% for an entry that measures 56.6% when compiled.
        fd, obj = tempfile.mkstemp(suffix=".obj", prefix="refresh_")
        os.close(fd)
        os.unlink(obj)
        src = os.path.join(ROOT, e["tu"])
        # vc6cl.sh must be given as an ABSOLUTE path: we run with cwd set to the
        # source's directory (the driver wants a bare basename), so a
        # repo-relative script path does not resolve there.
        cl = subprocess.run(
            ["bash", os.path.join(ROOT, "scripts/vc6/vc6cl.sh"),
             "/Fo" + obj, os.path.basename(src)],
            cwd=os.path.dirname(src), stdout=subprocess.DEVNULL,
            stderr=subprocess.DEVNULL)
        if cl.returncode or not os.path.exists(obj):
            if os.path.exists(obj):
                os.unlink(obj)
            print(f"  COMPILE FAIL {e['addr']}  {e['tu']} — not scoring")
            continue
        # The differ requires the explicit manifest span; it must not infer
        # a potentially truncated extent from Ghidra's function record.
        out = subprocess.run(
            ["python3", os.path.join(ROOT, "scripts/vc6/diff_retail.py"), "--obj", obj,
             "--sym", e["sym"], "--addr", e["addr"], "--len", e["len"]],
            capture_output=True, text=True).stdout.strip()
        os.unlink(obj)
        if not out.endswith("%"):
            print(f"  skip (no score) {e['addr']}")
            continue
        pct = float(out.splitlines()[-1].split(":")[1].strip().rstrip("%"))
        if abs(pct - e.get("pct", 0)) > 0.05:
            changed.append((e["addr"], e.get("pct", 0), pct, e["tu"]))
            e["pct"] = pct
    json.dump(entries, open(args.manifest, "w"), indent=1)
    open(args.manifest, "a").write("\n")
    for a, was, now, tu in changed:
        print(f"  {a:9s} {was:5.1f}% -> {now:5.1f}%  {tu}")
    print(f"{len(changed)} refreshed")
    return 0


if __name__ == "__main__":
    sys.exit(main())
