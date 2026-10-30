#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original project tooling (edits project sources; reads the pinned PE for the table contents).
"""Emit C++ definitions of constant tables whose initial values the pinned image holds.

Each spec is NAME:VA:TYPE:COUNT[:const]. TYPE is float, int, unsigned, short, unsigned short, char or unsigned char.
The definitions are written (annotated with `// GLOBAL: GAMEMD 0xVA`) to the file given with --out.

Usage: GAMEMD_BINARY=... define_table.py --out match/core/foo_tables.cpp --note "text" NAME:0x84F084:float:10241 ...
"""
import argparse
import struct
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import hybrid  # noqa: E402
import pindata  # noqa: E402

CODES = {"float": ("f", 4), "int": ("i", 4), "unsigned": ("I", 4), "unsigned int": ("I", 4), "short": ("h", 2),
         "unsigned short": ("H", 2), "char": ("b", 1), "unsigned char": ("B", 1)}


def spell(code, typ, v, chunk):
    if code == "f":
        for p in range(1, 10):
            t = f"{v:.{p}g}"
            if struct.pack("<f", float(t)) == chunk:
                break
        else:
            raise SystemExit(f"float {chunk.hex()} has no spelling")
        if "." not in t and "e" not in t:
            t += ".0"
        return t + "f"
    if code in "IHB":
        return str(v) if v < 10 else f"0x{v:X}"
    return str(v)


def definition(retail, name, va, typ, count, const, per_line=8):
    code, width = CODES[typ]
    raw = bytes(retail.fill(va, count * width))
    vals = struct.unpack("<" + code * count, raw)
    items = [spell(code, typ, v, raw[i * width:(i + 1) * width]) for i, v in enumerate(vals)]
    while len(items) > 1 and items[-1] in ("0", "0.0f"):
        items.pop()
    lines = ["    " + ", ".join(items[i:i + per_line]) + "," for i in range(0, len(items), per_line)]
    head = f"extern {'const ' if const else ''}{typ} {name}[{count}] = {{"
    return [f"// GLOBAL: GAMEMD 0x{va:X}", head] + lines + ["};", ""]


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--out", type=Path, required=True)
    ap.add_argument("--note", default="")
    ap.add_argument("specs", nargs="+")
    a = ap.parse_args()
    retail = hybrid.Retail(pindata.retail_path())
    out = ["// SPDX-License-Identifier: GPL-3.0-or-later", "// Provenance: own-binary-via-Ghidra",
           "//   Table contents read from the user's retail gamemd.exe v1.001 at the address in each annotation."]
    out += [f"//   {n}" for n in a.note.splitlines()] + [""]
    for s in a.specs:
        parts = s.split(":")
        name, va, typ, count = parts[0], int(parts[1], 16), parts[2], int(parts[3])
        out += definition(retail, name, va, typ, count, "const" in parts[4:])
    a.out.write_text("\n".join(out))


if __name__ == "__main__":
    main()
