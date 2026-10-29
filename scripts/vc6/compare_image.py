#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original project tooling; reads the pinned PE ($GAMEMD_BINARY) at run time only.
"""Compare a linked image with the pinned retail image, section by section.

Every section of IMAGE is compared with the bytes retail has at the same VAs (file-backed part
only). Prints the sections' sizes against retail's and the differing byte ranges (ranges closer
than --merge bytes are joined). The PE headers are not compared; AGENTS.md lists their known
differences. Exit status 0 when every section's bytes and virtual size equal retail's.

With a placement.json (link_m1.py --hybrid writes one next to m1.exe) it also reports, per section, how
many bytes of the image come from compiled project objects, from toolchain libraries and from retail fill.

Usage:  GAMEMD_BINARY=gamemd.exe scripts/vc6/compare_image.py IMAGE [--merge 16] [--limit 20] [--placement P] [--json OUT]
"""
import argparse
import json
import os
import struct
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import hybrid  # noqa: E402


def image_sections(data):
    """[(name, VA, virtual size, file bytes)] of a PE image."""
    pe = struct.unpack_from("<I", data, 0x3C)[0]
    base = struct.unpack_from("<I", data, pe + 24 + 28)[0]
    out = []
    for i in range(struct.unpack_from("<H", data, pe + 6)[0]):
        off = pe + 0xF8 + 40 * i
        vsize, rva, rawsize, rawptr = struct.unpack_from("<IIII", data, off + 8)
        out.append((data[off:off + 8].rstrip(b"\0").decode(), base + rva, vsize, data[rawptr:rawptr + min(vsize, rawsize)]))
    return out


def differing_ranges(ours, want, merge=16):
    """[(start, end)] where the byte strings differ (equal length), nearby ranges joined."""
    ranges, start = [], None
    for k, (a, b) in enumerate(zip(ours, want)):
        if a != b and start is None:
            start = k
        elif a == b and start is not None:
            ranges.append([start, k])
            start = None
    if start is not None:
        ranges.append([start, len(ours)])
    joined = []
    for lo, hi in ranges:
        if joined and lo - joined[-1][1] < merge:
            joined[-1][1] = hi
        else:
            joined.append([lo, hi])
    return [tuple(r) for r in joined]


def compare(image, retail, merge=16):
    """{section: {"va", "vsize", "retail_vsize", "diff_bytes", "ranges": [(VA, length)]}}"""
    out = {}
    for name, va, vsize, data in image_sections(image):
        have = retail.by_name.get(name)
        want = retail.fill(va, len(data))
        ranges = differing_ranges(data, want, merge)
        out[name] = {"va": va, "vsize": vsize, "retail_vsize": have[1] if have else None,
                     "diff_bytes": sum(a != b for a, b in zip(data, want)),
                     "ranges": [(va + lo, hi - lo) for lo, hi in ranges]}
    return out


def origin_counts(sections, pieces):
    """{section: {"vsize", "file", "project", "library", "retail"}} from placement pieces.

    sections: [(name, VA, virtual size, file bytes)]; pieces: [[section, VA, size, origin, name]] for every
    byte that does not come from the pinned image (origin "project": compiled project objects, "library":
    toolchain library members). Every other byte of the section is retail fill. Counts are bytes of the
    virtual size, so an uninitialised symbol past the file-backed part counts too."""
    out = {}
    for name, va, vsize, data in sections:
        counts = {"project": 0, "library": 0}
        for pname, pva, size, origin, _ in pieces:
            if pname != name:
                continue
            lo, hi = max(pva, va), min(pva + size, va + vsize)
            if hi > lo:
                counts[origin] = counts.get(origin, 0) + hi - lo
        out[name] = {"vsize": vsize, "file": len(data), **counts, "retail": vsize - sum(counts.values())}
    return out


def print_origins(counts):
    print("bytes by origin (of virtual size)")
    totals = {}
    for name, c in list(counts.items()) + [("total", None)]:
        if c is None:
            c = totals
        else:
            for k, v in c.items():
                totals[k] = totals.get(k, 0) + v
        print(f"{name:7} {c['vsize']:9} project {c['project']:9} ({100 * c['project'] / c['vsize']:5.2f}%)  "
              f"library {c['library']:8} ({100 * c['library'] / c['vsize']:5.2f}%)  "
              f"retail fill {c['retail']:9} ({100 * c['retail'] / c['vsize']:5.2f}%)")


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("image", type=Path)
    ap.add_argument("--merge", type=int, default=16)
    ap.add_argument("--limit", type=int, default=20, help="ranges to print per section")
    ap.add_argument("--json", type=Path, help="also write the per-section result and the bytes by origin here")
    ap.add_argument("--placement", type=Path, help="placement.json written by link_m1.py --hybrid "
                    "(default: next to IMAGE when present): reports the bytes by origin")
    args = ap.parse_args(argv)
    binary = os.environ.get("GAMEMD_BINARY")
    if not binary:
        raise SystemExit("compare_image: GAMEMD_BINARY is not set")
    image = args.image.read_bytes()
    result = compare(image, hybrid.Retail(binary), args.merge)
    clean = True
    for name, r in result.items():
        same_size = r["vsize"] == r["retail_vsize"]
        clean &= same_size and not r["diff_bytes"]
        print(f"{name:7} VA 0x{r['va']:X} virtual size 0x{r['vsize']:X} (retail "
              f"{'0x%X' % r['retail_vsize'] if r['retail_vsize'] is not None else 'absent'}) "
              f"differing bytes {r['diff_bytes']} in {len(r['ranges'])} ranges")
        for va, length in r["ranges"][:args.limit]:
            print(f"    0x{va:X} +0x{length:X}")
    placement = args.placement or args.image.with_name("placement.json")
    origins = None
    if placement.is_file():
        origins = origin_counts(image_sections(image), json.loads(placement.read_text())["pieces"])
        print_origins(origins)
    if args.json:
        args.json.write_text(json.dumps({
            "identical": clean, "origins": origins,
            "sections": {n: {"va": r["va"], "vsize": r["vsize"], "retail_vsize": r["retail_vsize"],
                             "diff_bytes": r["diff_bytes"], "ranges": len(r["ranges"])} for n, r in result.items()}},
            indent=1, sort_keys=True) + "\n")
    return 0 if clean else 1


if __name__ == "__main__":
    sys.exit(main())
