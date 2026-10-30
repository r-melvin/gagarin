#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original project tooling; reads the pinned PE ($GAMEMD_BINARY) at run time only.
"""Compare the resources RC.EXE makes from match/rsrc/gamemd.rc with the pinned image, resource by resource.

Dialogs, the menu and the version information must be byte-identical. Prints each difference's
resource, offset and the first differing bytes. Exit status 0 when all are identical.

Usage:  GAMEMD_BINARY=gamemd.exe scripts/vc6/rsrc_check.py [--res build-vc6/rsrc/gamemd_rc.res]
"""
import argparse
import os
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import rsrc_decompile  # noqa: E402
import rsrc_pack  # noqa: E402

NAMES = {1: "CURSOR", 3: "ICON", 4: "MENU", 5: "DIALOG", 12: "GROUP_CURSOR", 14: "GROUP_ICON", 16: "VERSION"}


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--res", type=Path, default=rsrc_pack.ROOT / "build-vc6/rsrc/gamemd_rc.res")
    args = ap.parse_args(argv)
    proc = rsrc_pack.compile_rc(rsrc_pack.RSRC / "gamemd.rc", args.res)
    if proc.returncode:
        print(proc.stdout)
        return 2
    mine = {(t, n): d for t, n, l, d in rsrc_pack.read_res(args.res.read_bytes())}
    retail, _, _ = rsrc_decompile.read_resources(os.environ["GAMEMD_BINARY"])
    bad = same = total = 0
    for t, n, l, d in retail:
        if t not in (4, 5, 16):
            continue
        total += 1
        got = mine.get((t, n))
        if got == d:
            same += 1
            continue
        bad += 1
        if got is None:
            print(f"{NAMES[t]} {n}: missing")
            continue
        k = next((i for i in range(min(len(got), len(d))) if got[i] != d[i]), min(len(got), len(d)))
        print(f"{NAMES[t]} {n}: size {len(got)} vs retail {len(d)}; first difference at {k}: "
              f"{got[k:k + 12].hex(' ')} vs {d[k:k + 12].hex(' ')}")
    extra = [k for k in mine if k not in {(t, n) for t, n, _, _ in retail}]
    print(f"{same}/{total} identical (DIALOG/MENU/VERSION), {bad} differing, {len(extra)} extra: {extra}")
    return 1 if bad or extra else 0


if __name__ == "__main__":
    sys.exit(main())
