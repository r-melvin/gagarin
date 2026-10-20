#!/usr/bin/env python3
"""verify_tus.py — recompile the named TUs (or every TU in the manifest) with the
period VC6 toolchain and re-run the per-function oracle against the user's retail
binary. A focused, fast version of verify_all.py for the inner loop: it prints one
line per non-100% function plus a summary, and exits non-zero if any function the
manifest calls `matched` fails to reach 100%.

Usage:  scripts/vc6/verify_tus.py [substring ...]
        (no arguments = every TU in the manifest)
"""
import json, os, subprocess, sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
CL   = os.path.join(ROOT, "scripts", "vc6", "vc6cl.sh")
OUT  = os.path.join(ROOT, "build-vc6")


def compile_tu(tu):
    obj = os.path.join(OUT, os.path.basename(tu)[:-4] + ".obj")
    src = os.path.join(ROOT, tu)
    r = subprocess.run(["bash", CL, "/Fo" + obj, os.path.basename(src)],
                       cwd=os.path.dirname(src), capture_output=True, text=True)
    if not os.path.exists(obj):
        return None, (r.stdout + r.stderr)
    bad = [l for l in (r.stdout + r.stderr).splitlines() if " error " in l or ": error" in l]
    return (None, "\n".join(bad)) if bad else (obj, "")


def verify(obj, e):
    for tool in ("diff_retail.py", "raw_match.py"):
        r = subprocess.run(["python3", os.path.join(ROOT, "scripts", "vc6", tool),
                            "--obj", obj, "--sym", e["sym"], "--addr", e["addr"],
                            "--len", e["len"]], capture_output=True, text=True)
        if "100.0%" in r.stdout:
            return True, "100.0%"
        pct = [l.split()[-1] for l in r.stdout.splitlines() if l.startswith("match:")]
        last = pct[-1] if pct else "?"
    return False, last


def main():
    man = json.load(open(os.path.join(ROOT, "docs", "match_manifest.json")))
    pats = sys.argv[1:]
    tus = sorted({e["tu"] for e in man if not pats or any(p in e["tu"] for p in pats)})
    if not tus:
        print("no TU matched"); return 1

    regressed = ok = 0
    for tu in tus:
        obj, err = compile_tu(tu)
        if obj is None:
            print(f"COMPILE FAIL {tu}\n{err}"); regressed += 1; continue
        for e in [x for x in man if x["tu"] == tu]:
            good, pct = verify(obj, e)
            if good:
                ok += 1
            elif e["status"] == "matched":
                print(f"REGRESSION {tu} {e['addr']} {e['name']} -> {pct}")
                regressed += 1
    print(f"=== {len(tus)} TUs: {ok} at 100%, {regressed} regressed ===")
    return 1 if regressed else 0


if __name__ == "__main__":
    sys.exit(main())
