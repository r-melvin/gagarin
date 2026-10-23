#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original synthetic .def fixtures.
"""implib: exact import names (NAME type), archive symbol indexes, descriptor objects."""

from pathlib import Path
import struct
import tempfile
import unittest

import implib
import link_diag
from verify_vtable import parse_coff

DEF = """; comment
LIBRARY binkw32
EXPORTS
  _BinkOpen@8
  _BinkClose@4   ; trailing comment
  _ByOrdinal@4 @7
"""


def members(lib):
    out, i = [], 8
    while i < len(lib):
        hdr = lib[i:i + 60]
        size = int(hdr[48:58])
        out.append((hdr[:16].decode().strip(), lib[i + 60:i + 60 + size]))
        i += 60 + size + (size & 1)
    return out


class ImplibTests(unittest.TestCase):
    def setUp(self):
        self.library, self.exports = implib.parse_def(DEF)
        self.lib = implib.write_library("binkw32.dll", self.exports)

    def test_parse_def(self):
        self.assertEqual(self.library, "binkw32")
        self.assertEqual(self.exports, [("_BinkOpen@8", None), ("_BinkClose@4", None), ("_ByOrdinal@4", 7)])
        with self.assertRaises(ValueError):
            implib.parse_def("EXPORTS\n  x\n")

    def test_short_import_members_keep_the_exact_name(self):
        short = [body for name, body in members(self.lib) if body[:4] == b"\0\0\xff\xff"]
        self.assertEqual(len(short), 3)
        seen = {}
        for body in short:
            machine, = struct.unpack_from("<H", body, 6)
            size, hint, typ = struct.unpack_from("<IHH", body, 12)
            sym, dll = body[20:20 + size].split(b"\0")[:2]
            self.assertEqual((machine, dll), (0x14C, b"binkw32.dll"))
            seen[sym.decode()] = (typ >> 2 & 7, hint)
        self.assertEqual(seen["_BinkOpen@8"], (1, 0))      # IMPORT_NAME: imported as written
        self.assertEqual(seen["_ByOrdinal@4"], (0, 7))     # by ordinal

    def test_linker_members_index_every_symbol(self):
        with tempfile.TemporaryDirectory() as tmp:
            path = Path(tmp) / "b.lib"
            path.write_bytes(self.lib)
            names = link_diag.archive_symbols(path)
        for sym in ("_BinkOpen@8", "__imp__BinkOpen@8", "_BinkClose@4", "__IMPORT_DESCRIPTOR_binkw32",
                    "__NULL_IMPORT_DESCRIPTOR", "\x7fbinkw32_NULL_THUNK_DATA"):
            self.assertIn(sym, names)
        mem = members(self.lib)
        second = mem[1][1]
        nmem, = struct.unpack_from("<I", second, 0)
        nsym, = struct.unpack_from("<I", second, 4 + 4 * nmem)
        strings = second[8 + 4 * nmem + 2 * nsym:].split(b"\0")[:nsym]
        self.assertEqual(strings, sorted(strings))          # second member is sorted
        offsets = struct.unpack_from(f"<{nmem}I", second, 4)
        for off in offsets:
            self.assertEqual(self.lib[off + 58:off + 60], b"`\n")

    def test_descriptor_objects_parse(self):
        objs = [body for name, body in members(self.lib)[2:] if body[:2] == b"\x4c\x01"]
        self.assertEqual(len(objs), 3)
        with tempfile.TemporaryDirectory() as tmp:
            path = Path(tmp) / "d.obj"
            path.write_bytes(objs[0])
            raw, sections, symbols, _ = parse_coff(path)
        self.assertEqual([s["name"] for s in sections.values()], [".idata$2", ".idata$6"])
        self.assertEqual(len(sections[1]["relocs"]), 3)
        dll = raw[sections[2]["raw_ptr"]:sections[2]["raw_ptr"] + sections[2]["raw_size"]]
        self.assertEqual(dll.rstrip(b"\0"), b"binkw32.dll")

    def test_tracked_def_lists_the_retail_names(self):
        library, exports = implib.parse_def((Path(__file__).parent / "binkw32.def").read_text())
        self.assertEqual(library, "binkw32")
        self.assertEqual(len(exports), 13)
        self.assertTrue(all(name.startswith("_Bink") and "@" in name for name, _ in exports))


if __name__ == "__main__":
    unittest.main()
