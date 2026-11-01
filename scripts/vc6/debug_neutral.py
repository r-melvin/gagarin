#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original project tooling.
"""Prove that debug info does not change code or data.

Two comparisons, both reporting every difference and exiting 1 if there is one:

  objects  every object of two object directories (the plain build and the /Z7 build): the
           .text/.data/.rdata (and every other non-debug) section, in order, by name, flags,
           bytes and relocations (offset, target symbol name, type), plus the external symbols
           each defines. Sections named .debug* are the debug info and are skipped.
  images   two linked images: the section table (name, VA, virtual size) and the bytes of every
           section, listing the differing ranges.

Usage:
  debug_neutral.py objects PLAIN_OBJDIR DEBUG_OBJDIR [--json FILE]
  debug_neutral.py images PLAIN.exe DEBUG.exe [--json FILE]
"""

import argparse
import json
from pathlib import Path
import struct
import sys

COMDAT = 0x1000


def read_object(data):
    """[(name, flags, bytes, [(offset, symbol, type)], key)] for the non-debug sections of a COFF object,
    and {external name: (section name, value)} for its defined external symbols."""
    machine, nsec, _, symptr, nsym = struct.unpack_from("<HHIII", data, 0)
    strtab = symptr + 18 * nsym
    strings_end = strtab + struct.unpack_from("<I", data, strtab)[0] if nsym else strtab

    def sym_name(raw):
        if raw[:4] == b"\0\0\0\0":
            off = struct.unpack_from("<I", raw, 4)[0]
            end = data.index(b"\0", strtab + off, strings_end)
            return data[strtab + off:end].decode("latin-1")
        return raw.rstrip(b"\0").decode("latin-1")

    symbols = []   # (name, value, section, storage class, aux count) per slot; None for aux slots
    i = 0
    while i < nsym:
        raw = data[symptr + 18 * i:symptr + 18 * i + 18]
        value, section, _, storage, naux = struct.unpack_from("<IhHBB", raw, 8)
        symbols.append((sym_name(raw[:8]), value, section, storage, naux))
        symbols.extend([None] * naux)
        i += 1 + naux
    heads = []
    for n in range(nsec):
        name, _, _, rawsize, rawptr, relptr, _, nreloc, _, flags = struct.unpack_from("<8sIIIIIIHHI", data, 20 + 40 * n)
        heads.append((name.rstrip(b"\0").decode("latin-1"), rawsize, rawptr, relptr, nreloc, flags))
    keys = {}   # section number -> first external symbol defined at offset 0 (the COMDAT key)
    defined = {}
    for s in symbols:
        if s is None:
            continue
        name, value, section, storage, _ = s
        if storage == 2 and section > 0:
            defined[name] = (heads[section - 1][0], value)
            if value == 0:
                keys.setdefault(section, name)
    ordinal = {}
    label = {}   # section number -> (section name, COMDAT key or ordinal among same-name sections)
    for n, head in enumerate(heads, 1):
        label[n] = (head[0], keys.get(n) if head[5] & COMDAT else ordinal.setdefault(head[0], 0))
        if not head[5] & COMDAT:
            ordinal[head[0]] += 1

    def target_name(idx):
        """A symbol's name; for a local label or static (the compiler numbers $L labels differently when it
        writes debug info) the section it lies in and its offset, so equal targets compare equal."""
        s = symbols[idx]
        if s is None:
            return "?"
        name, value, section, storage, _ = s
        if storage in (3, 6) and section > 0 and (name.startswith("$L") or name.startswith("$S")):
            return f"local:{label[section][0]}:{label[section][1]}:{value}"
        return name

    sections = []
    for n, (name, rawsize, rawptr, relptr, nreloc, flags) in enumerate(heads, 1):
        if name.startswith(".debug"):
            continue
        body = b"" if not rawptr or flags & 0x80 else data[rawptr:rawptr + rawsize]
        relocs = []
        for r in range(nreloc):
            off, idx, kind = struct.unpack_from("<IIH", data, relptr + 10 * r)
            relocs.append((off, target_name(idx), kind))
        sections.append((name, flags, body, relocs, keys.get(n) if flags & COMDAT else None))
    return sections, defined


def compare_object(plain, debug):
    """List of difference strings between two COFF objects (empty when none)."""
    (a, defs_a), (b, defs_b) = read_object(plain), read_object(debug)
    out = []
    if len(a) != len(b):
        out.append(f"non-debug section count {len(a)} != {len(b)}")
    index = {}
    for sec in b:
        index.setdefault((sec[0], sec[4]), []).append(sec)
    seen = {}
    for pos, sec in enumerate(a):
        key = (sec[0], sec[4])
        n = seen[key] = seen.get(key, -1) + 1
        other = index.get(key, [])
        if n >= len(other):
            out.append(f"{sec[0]} {sec[4] or ''}: missing from the debug object")
            continue
        o = other[n]
        label = f"{sec[0]}{' ' + sec[4] if sec[4] else ''}"
        if sec[1] != o[1]:
            out.append(f"{label}: flags {sec[1]:#x} != {o[1]:#x}")
        if sec[2] != o[2]:
            out.append(f"{label}: bytes differ ({len(sec[2])} vs {len(o[2])} bytes)")
        if sec[3] != o[3]:
            out.append(f"{label}: relocations differ ({len(sec[3])} vs {len(o[3])})")
    if [(s[0], s[4]) for s in a] != [(s[0], s[4]) for s in b] and not out:
        out.append("section order differs")
    if defs_a != defs_b:
        only_a, only_b = sorted(set(defs_a) - set(defs_b)), sorted(set(defs_b) - set(defs_a))
        moved = sorted(k for k in set(defs_a) & set(defs_b) if defs_a[k] != defs_b[k])
        out.append(f"defined externals differ: {len(only_a)} only plain, {len(only_b)} only debug, {len(moved)} moved")
    return out


def categorise(found):
    """'section_order' (same sections and bytes, emitted in another order), 'rtti_chd_bytes' (a ??_R3 class
    hierarchy descriptor differs) or 'other' (anything else: code, data or relocation bytes)."""
    if found == ["section order differs"]:
        return "section_order"
    if all(f.startswith(".rdata$r ??_R3") and "bytes differ" in f for f in found):
        return "rtti_chd_bytes"
    return "other"


def compare_objects(plain_dir, debug_dir):
    """{relative object path: [differences]} for every object of the plain build, plus coverage counts."""
    plain_dir, debug_dir = Path(plain_dir), Path(debug_dir)
    names = sorted(p.relative_to(plain_dir).as_posix() for p in plain_dir.rglob("*.obj"))
    differences, compared = {}, 0
    sections = {".text": 0, ".data": 0, ".rdata": 0}
    for name in names:
        other = debug_dir / name
        if not other.is_file():
            differences[name] = ["no object in the debug build"]
            continue
        plain = (plain_dir / name).read_bytes()
        found = compare_object(plain, other.read_bytes())
        compared += 1
        for sec in read_object(plain)[0]:
            if sec[0] in sections:
                sections[sec[0]] += 1
        if found:
            differences[name] = found
    extra = sorted(p.relative_to(debug_dir).as_posix() for p in debug_dir.rglob("*.obj"))
    for name in sorted(set(extra) - set(names)):
        differences[name] = ["no object in the plain build"]
    kinds = {}
    for found in differences.values():
        kind = categorise(found)
        kinds[kind] = kinds.get(kind, 0) + 1
    return {"objects_compared": compared, "sections_compared": sections, "objects_with_differences": len(differences),
            "by_kind": kinds, "differences": differences}


def read_sections(path):
    """[(name, VA, virtual size, raw bytes)] of a PE32 image."""
    data = Path(path).read_bytes()
    pe = struct.unpack_from("<I", data, 0x3C)[0]
    nsec, opt = struct.unpack_from("<H", data, pe + 6)[0], struct.unpack_from("<H", data, pe + 20)[0]
    base = struct.unpack_from("<I", data, pe + 24 + 28)[0]
    out = []
    for i in range(nsec):
        name, vsize, va, rawsize, rawptr = struct.unpack_from("<8sIIII", data, pe + 24 + opt + 40 * i)
        out.append((name.rstrip(b"\0").decode("latin-1"), base + va, vsize, data[rawptr:rawptr + rawsize]))
    return out


def compare_images(plain, debug):
    """{section: {...}} with the differing byte ranges of every section, and the section table check."""
    a, b = read_sections(plain), read_sections(debug)
    report = {"tables_equal": [s[:3] for s in a] == [s[:3] for s in b], "sections": {}}
    for sa, sb in zip(a, b):
        ranges, start = [], None
        n = max(len(sa[3]), len(sb[3]))
        x, y = sa[3].ljust(n, b"\0"), sb[3].ljust(n, b"\0")
        if x != y:
            for i in range(n):
                if x[i] != y[i]:
                    if start is None:
                        start = i
                elif start is not None:
                    ranges.append((start, i - start))
                    start = None
            if start is not None:
                ranges.append((start, n - start))
        report["sections"][sa[0]] = {"va": sa[1], "vsize": sa[2], "differing_bytes": sum(r[1] for r in ranges),
                                     "ranges": [[sa[1] + o, l] for o, l in ranges]}
    return report


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = ap.add_subparsers(dest="mode", required=True)
    for mode in ("objects", "images"):
        p = sub.add_parser(mode)
        p.add_argument("plain", type=Path)
        p.add_argument("debug", type=Path)
        p.add_argument("--json", type=Path)
    args = ap.parse_args(argv)
    if args.mode == "objects":
        report = compare_objects(args.plain, args.debug)
        print(f"{report['objects_compared']} objects compared, sections {report['sections_compared']}; "
              f"{report['objects_with_differences']} with differences {report['by_kind']}")
        for name, found in list(report["differences"].items())[:40]:
            print(f"  {name}: {'; '.join(found)}")
        bad = report["objects_with_differences"]
    else:
        report = compare_images(args.plain, args.debug)
        print(f"section tables equal: {report['tables_equal']}")
        bad = 0 if report["tables_equal"] else 1
        for name, s in report["sections"].items():
            print(f"  {name} VA {s['va']:#x} +{s['vsize']:#x}: {s['differing_bytes']} differing bytes in {len(s['ranges'])} ranges"
                  + "".join(f"\n    {a:#x} +{n:#x}" for a, n in s["ranges"][:20]))
            bad += s["differing_bytes"] > 0
    if args.json:
        args.json.write_text(json.dumps(report, indent=1) + "\n")
    return 1 if bad else 0


if __name__ == "__main__":
    sys.exit(main())
