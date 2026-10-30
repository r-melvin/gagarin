#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original project tooling.
"""Binary-free layout/compile regression gate (called by compile_all.sh).

Compiles every matching TU under match/** and every P2 layout header (via a
throwaway includer) with the period VC6 toolchain. The layout headers carry
GG_STATIC_ASSERT offsetof/sizeof checks, so a clean compile proves the class
layout spine still holds without the retail binary.

  --jobs N         compile N units concurrently (default nproc, max 8); output
                   order is the same for any N.
  --changed [REF]  only units whose source or transitively included header
                   differs from git REF (default HEAD).

Units are reported in byte (C-locale) path order, TUs first, then layout
headers, then the resource script (match/rsrc/gamemd.rc, compiled by RC.EXE). Exit 0 iff every selected unit compiles clean.
"""
import argparse
import concurrent.futures
import os
import re
import subprocess
import sys
import tempfile

import changed_tus

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
CL = os.path.join(ROOT, "scripts/vc6/vc6cl.sh")
ASM = os.path.join(ROOT, "scripts/vc6/vc6asm.sh")   # .asm units (ml.exe), AGENTS.md "Hand-written assembly"
RC = os.path.join(ROOT, "scripts/vc6/vc6rc.sh")
RESOURCE_SCRIPT = "match/rsrc/gamemd.rc"


def default_jobs():
    return max(1, min(8, os.cpu_count() or 1))


def list_tus(root):
    found = []
    for base, _, names in os.walk(os.path.join(root, "match")):
        for name in names:
            if name.endswith((".cpp", ".c", ".asm")):
                found.append(os.path.relpath(os.path.join(base, name), root).replace(os.sep, "/"))
    return sorted(found)


def list_headers(root):
    layout = os.path.join(root, "match/_layout")
    return sorted(f"match/_layout/{n}" for n in os.listdir(layout) if n.endswith(".h"))


def error_lines(log):
    pattern = re.compile(r"error|fatal", re.I)
    return [l for l in log.splitlines() if pattern.search(l) and "libEGL" not in l][:3]


def compile_one(root, tmp, directory, filename, objname):
    obj = os.path.join(tmp, objname)
    # Capture the compiler output in a file, never a pipe: Wine may leave a
    # wineserver running that inherits the child's stdout, and a reader waiting
    # for pipe EOF would then stall until that server exits. The wait below
    # returns as soon as the launcher itself exits.
    with open(obj + ".log", "w+", errors="replace") as log:
        proc = subprocess.run(["bash", ASM if filename.endswith(".asm") else CL, f"/Fo{obj}", filename], cwd=os.path.join(root, directory),
                              stdin=subprocess.DEVNULL, stdout=log, stderr=subprocess.STDOUT)
        log.seek(0)
        output = log.read()
    ok = proc.returncode == 0 and os.path.isfile(obj)
    return ok, ([] if ok else error_lines(output))


def check_tu(root, tmp, n, tu):
    ok, errs = compile_one(root, tmp, os.path.dirname(tu), os.path.basename(tu),
                           f"{n}_{os.path.basename(tu)}.obj")
    return (f"  ok   {tu}" if ok else f"  FAIL {tu}"), errs, ok


def check_header(root, tmp, n, header):
    base = os.path.basename(header)[:-2]
    includer = os.path.join(root, "match/_layout", f"_ca_{base}.cpp")
    with open(includer, "w") as stream:
        stream.write(f'#include "{base}.h"\nint _chk_{base}(){{return 0;}}\n')
    try:
        ok, errs = compile_one(root, tmp, "match/_layout", f"_ca_{base}.cpp", f"h{n}_{base}.obj")
    finally:
        os.remove(includer)
    return (f"  ok   {header} (asserts pass)" if ok else f"  FAIL {header}"), errs, ok


def check_rc(root, tmp):
    """The reconstructed resource script must compile with the period RC.EXE."""
    res = os.path.join(tmp, "gamemd.res")
    with open(res + ".log", "w+", errors="replace") as log:
        proc = subprocess.run(["bash", RC, "/r", "/fo", res, os.path.basename(RESOURCE_SCRIPT)],
                              cwd=os.path.join(root, os.path.dirname(RESOURCE_SCRIPT)), stdin=subprocess.DEVNULL,
                              stdout=log, stderr=subprocess.STDOUT)
        log.seek(0)
        output = log.read()
    ok = proc.returncode == 0 and os.path.isfile(res)
    return (f"  ok   {RESOURCE_SCRIPT} (RC.EXE)" if ok else f"  FAIL {RESOURCE_SCRIPT}"), \
        ([] if ok else error_lines(output)), ok


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("--jobs", type=int, default=default_jobs())
    ap.add_argument("--changed", nargs="?", const="HEAD", metavar="REF")
    args = ap.parse_args(argv)
    if args.jobs < 1:
        ap.error("--jobs must be positive")

    tus, headers = list_tus(ROOT), list_headers(ROOT)
    if args.changed:
        keep = changed_tus.select_changed(ROOT, tus + headers, args.changed)
        tus = [t for t in tus if t in keep]
        headers = [h for h in headers if h in keep]
        print(f"--changed {args.changed}: {len(tus)} TUs, {len(headers)} layout headers affected")

    fail = False
    with tempfile.TemporaryDirectory(prefix="compile_all_") as tmp, \
            concurrent.futures.ThreadPoolExecutor(max_workers=args.jobs) as pool:
        futures = [pool.submit(check_tu, ROOT, tmp, n, tu) for n, tu in enumerate(tus)]
        futures += [pool.submit(check_header, ROOT, tmp, n, h) for n, h in enumerate(headers)]
        if not args.changed and os.path.isfile(os.path.join(ROOT, RESOURCE_SCRIPT)):
            futures.append(pool.submit(check_rc, ROOT, tmp))
        for future in futures:
            line, errs, ok = future.result()
            print(line)
            for err in errs:
                print(err)
            fail = fail or not ok
    print("=== compile_all: FAILURES ===" if fail else "=== compile_all: ALL GREEN ===")
    return 1 if fail else 0


if __name__ == "__main__":
    sys.exit(main())
