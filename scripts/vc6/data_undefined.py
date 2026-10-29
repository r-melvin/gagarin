#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original project tooling (measurement only; reads the pinned PE for section ranges).
"""List the data symbols matched code references through a pin (an extern bound to a retail address) that no
project object defines, per translation unit: the globals that still come from retail fill in the M3 image.
Exact (relocation based), unlike the dword-scan estimate of data_census.py.

Usage: GAMEMD_BINARY=... data_undefined.py --objdir build-vc6/gate [--tu match/ai/foo.cpp]
Columns: tu, name, va, region, distance to the next pinned address (upper bound of the size)."""
import argparse
import bisect
import json
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import coffgen  # noqa: E402
import pindata  # noqa: E402
from verify_vtable import parse_coff  # noqa: E402

ROOT = Path(__file__).resolve().parents[2]


def region_of(va):
    if 0x7E1000 <= va < 0x7E1000 + 0x30074:
        return "rdata"
    d = 0x812000
    if d <= va < d + 0x367BE4:
        return "data" if va < d + 0x6C000 else "bss"
    return "?"


def collect(objdir):
    """(users {name: {tu}}, undefined {name: va}) for the objects built in objdir."""
    objdir = Path(objdir).resolve()
    index = json.loads((objdir / "objects.json").read_text())
    manifest = json.loads((ROOT / "scripts/data/match_manifest.json").read_text())
    pe, _, pe_sections = pindata.load_retail()
    plan = pindata.derive(objdir, index, manifest, pe, pe_sections)
    glob = plan["global"]
    defined = set()
    users = {}
    for o in index["objects"]:
        path = objdir / o["object"]
        try:
            data, sections, symbols, _ = parse_coff(path)
        except Exception:
            continue
        for s in symbols.values():
            if s["storage_class"] != coffgen.CLASS_EXTERNAL:
                continue
            if s["section"] > 0:
                defined.add(s["name"])
            elif s["name"] in glob and pindata.in_data(glob[s["name"]]):
                users.setdefault(s["name"], set()).add(o["source"])
    return users, {n: glob[n] for n in users if n not in defined}


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--objdir", type=Path, required=True)
    ap.add_argument("--tu")
    args = ap.parse_args()
    users, undefined = collect(args.objdir)
    vas = sorted(set(undefined.values()))
    for n, va in sorted(undefined.items(), key=lambda kv: kv[1]):
        nxt = vas[bisect.bisect_right(vas, va)] if va != vas[-1] else va
        for tu in sorted(users[n]):
            if args.tu and tu != args.tu:
                continue
            print(f"{tu}\t{n}\t0x{va:X}\t{region_of(va)}\t{nxt - va}\t{len(users[n])}")


if __name__ == "__main__":
    main()
