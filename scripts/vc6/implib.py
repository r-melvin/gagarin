#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original project tooling.
"""Write a COFF short-import library from a .def file (replaces LIB /DEF).

LIB /DEF in VC6 records every export with the "no prefix" import-name type, so
the image imports `BinkOpen@8` where retail imports `_BinkOpen@8`. This writer
records each export with the plain NAME type: the symbol named in the .def is
both the linker symbol and the name in the import table, exactly as written.

.def syntax understood: `LIBRARY name`, `EXPORTS`, then one export per line,
optionally `name @ordinal` (imports by ordinal). `;` starts a comment.

Usage:
  scripts/vc6/implib.py scripts/vc6/binkw32.def OUT.lib
"""

import struct
import sys
from pathlib import Path

I386 = 0x14C
NAME_TYPE = {"ordinal": 0, "name": 1}
DIR32NB = 7
CLASS_EXTERNAL, CLASS_STATIC, CLASS_SECTION = 2, 3, 0x68
DATA_RW4 = 0xC0300040   # initialised data, read/write, 4-byte aligned
DATA_RW2 = 0xC0200040


def parse_def(text):
    library, exports, in_exports = None, [], False
    for raw in text.splitlines():
        line = raw.split(";", 1)[0].strip()
        if not line:
            continue
        word = line.split()[0].upper()
        if word == "LIBRARY":
            library = line.split()[1].strip('"')
            in_exports = False
        elif word == "EXPORTS":
            in_exports = True
        elif in_exports:
            parts = line.split()
            ordinal = int(parts[1][1:]) if len(parts) > 1 and parts[1].startswith("@") else None
            exports.append((parts[0], ordinal))
        else:
            raise ValueError(f"unsupported .def line: {raw!r}")
    if not library:
        raise ValueError(".def has no LIBRARY line")
    return library, exports


def _coff(sections, symbols, strings=b""):
    """sections: [(name, flags, data, relocs[(off, symidx, type)])]; symbols: raw 18-byte records."""
    head = 20 + 40 * len(sections)
    body, table, ptr = bytearray(), bytearray(), head
    for name, flags, data, relocs in sections:
        rel = b"".join(struct.pack("<IIH", *r) for r in relocs)
        table += name.encode().ljust(8, b"\0") + struct.pack(
            "<IIIIIIHHI", 0, 0, len(data), ptr, ptr + len(data) if relocs else 0, 0, len(relocs), 0, flags)
        body += data + rel
        ptr += len(data) + len(rel)
    syms = b"".join(symbols)
    hdr = struct.pack("<HHIIIHH", I386, len(sections), 0, ptr, len(symbols), 0, 0)
    return hdr + bytes(table) + bytes(body) + syms + struct.pack("<I", 4 + len(strings)) + strings


class _Names:
    def __init__(self):
        self.table = bytearray()

    def field(self, name):
        raw = name.encode("latin-1")
        if len(raw) <= 8:
            return raw.ljust(8, b"\0")
        off = 4 + len(self.table)
        self.table += raw + b"\0"
        return struct.pack("<II", 0, off)


def _sym(names, name, value, section, scl, naux=0):
    return names.field(name) + struct.pack("<IhHBB", value, section, 0, scl, naux)


def descriptor_members(dll):
    base = dll.rsplit(".", 1)[0]
    n = _Names()
    dllname = dll.encode() + b"\0"
    if len(dllname) % 2:
        dllname += b"\0"
    syms = [_sym(n, f"__IMPORT_DESCRIPTOR_{base}", 0, 1, CLASS_EXTERNAL),
            _sym(n, ".idata$2", DATA_RW4, 1, CLASS_SECTION),
            _sym(n, ".idata$6", 0, 2, CLASS_STATIC),
            _sym(n, ".idata$4", DATA_RW4, 0, CLASS_SECTION),
            _sym(n, ".idata$5", DATA_RW4, 0, CLASS_SECTION),
            _sym(n, "__NULL_IMPORT_DESCRIPTOR", 0, 0, CLASS_EXTERNAL),
            _sym(n, f"\x7f{base}_NULL_THUNK_DATA", 0, 0, CLASS_EXTERNAL)]
    desc = _coff([(".idata$2", DATA_RW4, bytes(20), [(12, 2, DIR32NB), (0, 3, DIR32NB), (16, 4, DIR32NB)]),
                  (".idata$6", DATA_RW2, dllname, [])], syms, bytes(n.table))
    n = _Names()
    null_desc = _coff([(".idata$3", DATA_RW4, bytes(20), [])],
                      [_sym(n, "__NULL_IMPORT_DESCRIPTOR", 0, 1, CLASS_EXTERNAL)], bytes(n.table))
    n = _Names()
    null_thunk = _coff([(".idata$5", DATA_RW4, bytes(4), []), (".idata$4", DATA_RW4, bytes(4), [])],
                       [_sym(n, f"\x7f{base}_NULL_THUNK_DATA", 0, 1, CLASS_EXTERNAL)], bytes(n.table))
    return [(desc, [f"__IMPORT_DESCRIPTOR_{base}"]), (null_desc, ["__NULL_IMPORT_DESCRIPTOR"]),
            (null_thunk, [f"\x7f{base}_NULL_THUNK_DATA"])]


def short_import(dll, symbol, ordinal):
    """IMPORT_OBJECT_HEADER + "symbol\\0dll\\0": code import, NAME or ORDINAL type."""
    data = symbol.encode("latin-1") + b"\0" + dll.encode() + b"\0"
    name_type = NAME_TYPE["ordinal"] if ordinal is not None else NAME_TYPE["name"]
    return struct.pack("<HHHHIIHH", 0, 0xFFFF, 0, I386, 0, len(data), ordinal or 0, name_type << 2) + data


def _member(name, body):
    hdr = (name.ljust(16) + "0".ljust(12) + "".ljust(6) + "".ljust(6) + "0".ljust(8)
           + str(len(body)).ljust(10) + "`\n").encode()
    return hdr + body + (b"\n" if len(body) % 2 else b"")


def write_library(dll, exports):
    """Bytes of an import library for dll with exports [(symbol, ordinal or None)]."""
    members = descriptor_members(dll)
    for sym, ordinal in exports:
        members.append((short_import(dll, sym, ordinal), [sym, "__imp_" + sym]))
    member_name = dll + "/"
    longnames = b""
    if len(member_name) > 16:
        longnames = dll.encode() + b"/\n"
        member_name = "/0"
    nsyms = sum(len(names) for _, names in members)
    names_blob = b"".join(s.encode("latin-1") + b"\0" for _, names in members for s in names)
    first_size = 4 + 4 * nsyms + len(names_blob)
    second_size = 4 + 4 * len(members) + 4 + 2 * nsyms + len(names_blob)
    offset = 8 + 60 + first_size + first_size % 2 + 60 + second_size + second_size % 2
    if longnames:
        offset += 60 + len(longnames) + len(longnames) % 2
    offsets = []
    for body, _ in members:
        offsets.append(offset)
        offset += 60 + len(body) + len(body) % 2
    first = struct.pack(">I", nsyms)
    first += b"".join(struct.pack(">I", offsets[i]) for i, (_, names) in enumerate(members) for _ in names)
    first += names_blob
    pairs = sorted((s.encode("latin-1"), i + 1) for i, (_, names) in enumerate(members) for s in names)
    second = struct.pack("<I", len(members)) + b"".join(struct.pack("<I", o) for o in offsets)
    second += struct.pack("<I", nsyms) + b"".join(struct.pack("<H", i) for _, i in pairs)
    second += b"".join(s + b"\0" for s, _ in pairs)
    out = b"!<arch>\n" + _member("/", first) + _member("/", second)
    if longnames:
        out += _member("//", longnames)
    for body, _ in members:
        out += _member(member_name, body)
    return out


def build_from_def(def_path, out_path):
    library, exports = parse_def(Path(def_path).read_text(encoding="latin-1"))
    dll = library if "." in library else library + ".dll"
    Path(out_path).write_bytes(write_library(dll, exports))
    return out_path


def main(argv=None):
    argv = sys.argv[1:] if argv is None else argv
    if len(argv) != 2:
        print(__doc__, file=sys.stderr)
        return 2
    build_from_def(argv[0], argv[1])
    return 0


if __name__ == "__main__":
    sys.exit(main())
