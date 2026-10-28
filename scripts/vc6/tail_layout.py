#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original project tooling; reads the retail image at run time, writes names, addresses and sizes only.
"""Write scripts/data/crt_tail_layout.json: the library tail of retail's .text as a layout.

Combines crt_ident (which archive section sits where) with the import-thunk runs
(`jmp [IAT slot]`, each named from the retail import table and the toolchain's import
libraries). The file holds names, addresses, sizes and archive coordinates, never
bytes; link_m1.py --order-tail consumes it without the retail image.

Usage:  GAMEMD_BINARY=gamemd.exe scripts/vc6/tail_layout.py [--out scripts/data/crt_tail_layout.json]
"""
import argparse
import json
import re
import struct
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import crt_ident  # noqa: E402
import coffgen  # noqa: E402
import implib  # noqa: E402
import link_diag  # noqa: E402
from verify_vtable import load_pe  # noqa: E402

ROOT = Path(__file__).resolve().parents[2]
JMP_IAT = re.compile(rb"\xff\x25([\x00-\xff]{4})")


def import_slots(pe, base, sections):
    """{IAT slot VA: (dll stem lower, function name)} from the retail import directory."""
    def rva(r):
        for _, start, vsize, rawptr, rawsize in sections:
            if start <= base + r < start + min(vsize, rawsize):
                return rawptr + base + r - start
        return None

    peoff = struct.unpack_from("<I", pe, 0x3C)[0]
    opt = peoff + 24
    imp_rva = struct.unpack_from("<I", pe, opt + 104)[0]
    out, at = {}, rva(imp_rva)
    while at is not None:
        orig, _, _, name_rva, first = struct.unpack_from("<IIIII", pe, at)
        if not name_rva:
            break
        dll = pe[rva(name_rva):].split(b"\0", 1)[0].decode("latin-1").lower().rsplit(".", 1)[0]
        lookup = rva(orig or first)
        for i in range(10000):
            entry = struct.unpack_from("<I", pe, lookup + 4 * i)[0]
            if not entry:
                break
            if entry & 0x80000000:
                out[base + first + 4 * i] = (dll, entry & 0xFFFF)
            else:
                out[base + first + 4 * i] = (dll, pe[rva(entry) + 2:].split(b"\0", 1)[0].decode("latin-1"))
        at += 20
    return out


def decorated_names(libdir, extra=()):
    """{(dll stem lower, undecorated name): decorated link symbol} from the import libraries
    (extra: further import library paths, such as the generated binkw32.lib)."""
    out = {}
    for path in [libdir / lib for lib in link_diag.IMPORT_LIBS] + [Path(e) for e in extra]:
        if not path.is_file():
            continue
        stem = path.name.lower().rsplit(".", 1)[0]
        for sym in link_diag.archive_symbols(path):
            if sym.startswith("__imp__"):
                dec = sym[len("__imp_"):]
                out[(stem, re.sub(r"@\d+$", "", dec[1:]))] = dec
        # Short-import members record the ordinal an ordinal-only import (WSOCK32) is bound by.
        for _, member in crt_ident.archive_members(path):
            if member[:4] == b"\0\0\xff\xff" and len(member) > 20:
                ordinal, flags = struct.unpack_from("<HH", member, 16)
                if (flags >> 2) & 7 == 0:
                    out[(stem, ordinal)] = member[20:].split(b"\0", 1)[0].decode("latin-1")
            elif member[:2] == b"L\x01":
                ordinal = long_import_ordinal(member)
                if ordinal is not None:
                    for _, name, _, section, scl, _ in coffgen.read_symbols(member):
                        if scl == 2 and section > 0 and name.startswith("__imp__"):
                            out[(stem, ordinal)] = name[len("__imp_"):]
    return out


def long_import_ordinal(obj):
    """Ordinal recorded in the .idata$5 slot of a long-format import member, if it imports by ordinal."""
    for i in range(struct.unpack_from("<H", obj, 2)[0]):
        off = 20 + 40 * i
        if obj[off:off + 8].rstrip(b"\0") == b".idata$5":
            size, ptr = struct.unpack_from("<II", obj, off + 16)
            if size == 4 and ptr:
                value = struct.unpack_from("<I", obj, ptr)[0]
                return value & 0xFFFF if value & 0x80000000 else None
    return None


def thunk_runs(tail_base, tail, text_base, text, gaps):
    """[(addr, slot VA)] for every thunk in the first run before the tail and in the tail's thunk gaps."""
    spans = []
    start = tail_base
    while start - 6 >= text_base and JMP_IAT.fullmatch(text[start - 6 - text_base:start - text_base]):
        start -= 6
    spans.append((start, tail_base))
    for g in gaps:
        if g["kind"] == "import_thunks":
            a = int(g["addr"], 16)
            spans.append((a, a + g["len"]))
    out = []
    for a, b in spans:
        for va in range(a, b, 6):
            m = JMP_IAT.fullmatch(text[va - text_base:va - text_base + 6])
            if m:
                out.append((va, struct.unpack("<I", m.group(1))[0]))
    return out


def build(libdir, hints=None):
    ident = crt_ident.run(libdir, None, hints)
    import os
    sha = json.loads(Path(crt_ident.DEFAULT_TOTALS).read_text())["_meta"]["sha256"]
    pe, base, secs = load_pe(os.environ["GAMEMD_BINARY"], sha)
    text = next(s for s in secs if s[0] == ".text")
    text_bytes = pe[text[3]:text[3] + min(text[2], text[4])]
    tail_base = int(ident["stats"]["tail_start"], 16)
    slots = import_slots(pe, base, secs)
    names = decorated_names(libdir)
    _, bink = implib.parse_def((ROOT / "scripts/vc6/binkw32.def").read_text(encoding="latin-1"))
    names.update({("binkw32", e if isinstance(e, str) else e[0]): (e if isinstance(e, str) else e[0]) for e in bink})
    thunks, unnamed = [], 0
    for va, slot in thunk_runs(tail_base, None, text[1], text_bytes, ident["gaps"]):
        entry = slots.get(slot)
        sym = names.get((entry[0], entry[1])) if entry else None
        unnamed += sym is None
        thunks.append({"addr": f"0x{va:08X}", "name": sym})
    sections = []
    for r in ident["sections"]:
        sections.append({"addr": r["addr"], "len": r["len"], "align": r["align"], "library": r["library"],
                         "member_index": r["member_index"], "member": r["member"], "section": r["section"],
                         "comdat": r["comdat"], "inferred_by_order": r["inferred_by_order"],
                         "symbols": [[s["name"], int(s["addr"], 16) - int(r["addr"], 16)] for s in r["symbols"]]})
    return {"schema": 1,
            "provenance": "own-binary-via-crt_ident: names, addresses and sizes only; regenerate with tail_layout.py",
            "tail_start": ident["stats"]["tail_start"], "stats": ident["stats"], "thunks": thunks,
            "unnamed_thunks": unnamed, "sections": sections}


def call_hints(objdir):
    """{symbol: retail VA} for names that matched code calls at a single address."""
    import pindata
    objdir = Path(objdir)
    pe, _, secs = pindata.load_retail()
    plan = pindata.derive(objdir, json.loads((objdir / "objects.json").read_text()),
                          json.loads((ROOT / "scripts/data/match_manifest.json").read_text()), pe, secs)
    return plan["calls"]


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    ap.add_argument("--libdir", type=Path, default=ROOT / "toolchain/MSVC600/VC98/Lib")
    ap.add_argument("--objdir", type=Path,
                    help="build_project.py output: REL32 targets of matched code settle library sections "
                         "that match in several places")
    ap.add_argument("--out", type=Path, default=ROOT / "scripts/data/crt_tail_layout.json")
    args = ap.parse_args(argv)
    hints = call_hints(args.objdir) if args.objdir else None
    layout = build(args.libdir, hints)
    args.out.write_text(json.dumps(layout, indent=1) + "\n")
    print(f"{len(layout['sections'])} sections, {len(layout['thunks'])} thunks ({layout['unnamed_thunks']} unnamed) -> {args.out}")


if __name__ == "__main__":
    main()
