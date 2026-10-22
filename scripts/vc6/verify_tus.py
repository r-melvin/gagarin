#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original
"""Recompile selected TUs and check their annotated functions against retail."""

import argparse
import json
import os
import subprocess
import sys
import tempfile


ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
CL = os.path.join(ROOT, "scripts", "vc6", "vc6cl.sh")
OUT = os.path.join(ROOT, "build-vc6")


def compile_tu(tu):
    """Compile one TU, rejecting stale outputs and preserving readable errors.

    Wine descendants can inherit capture pipes after CL exits, so compiler output
    goes to a temporary file instead of subprocess.PIPE.
    """
    obj = os.path.join(OUT, os.path.basename(tu)[:-4] + ".obj")
    src = os.path.join(ROOT, tu)
    os.makedirs(OUT, exist_ok=True)
    if os.path.exists(obj):
        os.remove(obj)

    with tempfile.TemporaryFile(mode="w+t", encoding="utf-8", errors="replace") as log:
        try:
            result = subprocess.run(
                ["bash", CL, "/Fo" + obj, os.path.basename(src)],
                cwd=os.path.dirname(src), stdout=log, stderr=subprocess.STDOUT,
                text=True)
        except OSError as exc:
            return None, f"could not start VC6 compiler: {exc}"
        log.flush()
        log.seek(0)
        output = log.read()

    if result.returncode != 0:
        # A compiler may leave a partial object on failure. Do not let a later
        # verification mistake it for a successful build.
        if os.path.exists(obj):
            os.remove(obj)
        detail = output.strip() or "(compiler produced no diagnostic output)"
        return None, f"compiler exited with status {result.returncode}\n{detail}"
    if not os.path.isfile(obj):
        detail = output.strip() or "(compiler produced no diagnostic output)"
        return None, f"compiler exited successfully but produced no object\n{detail}"
    return obj, ""


def verify(obj, entry):
    """Try the exact raw-byte oracle first, then the instruction diff."""
    last = "?"
    for tool in ("raw_match.py", "diff_retail.py"):
        result = subprocess.run(
            ["python3", os.path.join(ROOT, "scripts", "vc6", tool),
             "--obj", obj, "--sym", entry["sym"], "--addr", entry["addr"],
             "--len", entry["len"]],
            capture_output=True, text=True)
        if tool == "raw_match.py" and result.returncode == 3:
            return False, "hard float-literal relocation failure"
        if tool == "raw_match.py" and result.returncode == 4:
            return False, "address-labelled DAT relocation target mismatch"
        if result.returncode == 0 and "100.0%" in result.stdout:
            return True, "100.0%"
        percentages = [line.split()[-1] for line in result.stdout.splitlines()
                       if line.startswith("match:")]
        if result.returncode:
            last = f"{tool} failed (exit {result.returncode})"
        elif percentages:
            last = percentages[-1]
    return False, last


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("patterns", nargs="*", help="substring filters for TU paths")
    args = parser.parse_args(argv)

    with open(os.path.join(ROOT, "scripts", "data", "match_manifest.json"),
              encoding="utf-8") as manifest:
        entries = json.load(manifest)
    patterns = args.patterns
    tus = sorted({entry["tu"] for entry in entries
                  if not patterns or any(pattern in entry["tu"] for pattern in patterns)})
    if not tus:
        print("no TU matched")
        return 1

    regressed = ok = 0
    for tu in tus:
        obj, error = compile_tu(tu)
        if obj is None:
            print(f"COMPILE FAIL {tu}\n{error}")
            regressed += 1
            continue
        for entry in (item for item in entries if item["tu"] == tu):
            good, pct = verify(obj, entry)
            if good:
                ok += 1
            elif entry["status"] == "matched":
                print(f"REGRESSION {tu} {entry['addr']} {entry['name']} -> {pct}")
                regressed += 1
    print(f"=== {len(tus)} TUs: {ok} at 100%, {regressed} regressed ===")
    return 1 if regressed else 0


if __name__ == "__main__":
    sys.exit(main())
