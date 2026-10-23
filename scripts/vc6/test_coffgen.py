#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original synthetic COFF fixtures.
"""coffgen: written objects parse back, stubs are 0xCC only, renames keep references."""

from pathlib import Path
import struct
import tempfile
import unittest

import coffgen
from verify_vtable import parse_coff


def parse(data):
    with tempfile.TemporaryDirectory() as tmp:
        path = Path(tmp) / "x.obj"
        path.write_bytes(data)
        return parse_coff(path)


def section_flags(data, index):
    return struct.unpack_from("<I", data, 20 + 40 * (index - 1) + 36)[0]


class WriterTests(unittest.TestCase):
    def build(self):
        w = coffgen.ObjectWriter()
        w.add_code_comdat(["?stub_00401000@@YAXXZ", "?Foo@@YAXXZ", "_FUN_00401000"], 0x23, 16)
        w.add_code_comdat(["?gap_00401030@@YAXXZ"], 5, 1, section=".text$zz")
        w.add_common("?DAT_00812000@@3HA", 12)
        w.add_alias("?Other@@YAXXZ", "?Foo@@YAXXZ")
        w.set_anchor(["?stub_00401000@@YAXXZ", "?Matched@@YAXXZ"])
        return w.build()

    def test_sections_symbols_and_fill(self):
        data = self.build()
        raw, sections, symbols, aux = parse(data)
        names = [s["name"] for s in sections.values()]
        self.assertEqual(names, [".text", ".text$zz", ".data$zz"])
        text = sections[1]
        body = raw[text["raw_ptr"]:text["raw_ptr"] + text["raw_size"]]
        self.assertEqual(body, b"\xcc" * 0x23)          # no byte but int3
        self.assertEqual(section_flags(data, 1) & 0x00F00000, coffgen.ALIGN[16])
        self.assertEqual(section_flags(data, 2) & 0x00F00000, coffgen.ALIGN[1])
        self.assertTrue(section_flags(data, 1) & coffgen.SCN_LNK_COMDAT)
        by_name = {s["name"]: s for s in symbols.values()}
        for name in ("?stub_00401000@@YAXXZ", "?Foo@@YAXXZ", "_FUN_00401000"):
            self.assertEqual((by_name[name]["section"], by_name[name]["value"]), (1, 0))
        self.assertEqual(by_name["?DAT_00812000@@3HA"]["section"], 0)
        self.assertEqual(by_name["?DAT_00812000@@3HA"]["value"], 12)      # COMMON size
        self.assertEqual(by_name["?Other@@YAXXZ"]["storage_class"], 105)  # weak external
        # COMDAT selection ANY in the section's auxiliary record.
        sec_sym = next(i for i, s in symbols.items() if s["name"] == ".text" and s["section"] == 1)
        self.assertEqual(aux[sec_sym + 1][14], coffgen.COMDAT_ANY)

    def test_anchor_relocations_point_at_every_name(self):
        raw, sections, symbols, _ = parse(self.build())
        anchor = sections[3]
        targets = [symbols[idx]["name"] for _, idx, kind in anchor["relocs"]]
        self.assertEqual(targets, ["?stub_00401000@@YAXXZ", "?Matched@@YAXXZ"])
        self.assertTrue(all(kind == coffgen.REL_DIR32 for _, _, kind in anchor["relocs"]))
        self.assertEqual(anchor["raw_size"], 8)

    def test_rejects_empty_stub(self):
        with self.assertRaises(ValueError):
            coffgen.ObjectWriter().add_code_comdat(["?x@@YAXXZ"], 0)


class RenameTests(unittest.TestCase):
    def object_with_reference(self):
        """A code stub defining ?A and a data table relocated against ?A."""
        w = coffgen.ObjectWriter()
        w.add_code_comdat(["?A@@YAXXZ"], 16)
        w.add_code_comdat(["?S@@YAXXZ"], 16)
        w.set_anchor(["?A@@YAXXZ"])
        return w.build()

    def test_retarget_moves_only_the_definition(self):
        data, n = coffgen.rename_symbols(self.object_with_reference(), {"?A@@YAXXZ": "__displaced_A"})
        self.assertEqual(n, 1)
        _, sections, symbols, _ = parse(data)
        defined = {s["name"] for s in symbols.values() if s["section"] > 0 and s["storage_class"] == 2}
        self.assertIn("__displaced_A", defined)
        self.assertNotIn("?A@@YAXXZ", defined)
        target = symbols[sections[3]["relocs"][0][1]]
        self.assertEqual((target["name"], target["section"]), ("?A@@YAXXZ", 0))   # still the old name

    def test_rename_with_references(self):
        data, _ = coffgen.rename_symbols(self.object_with_reference(), {"?A@@YAXXZ": "?dup@@YAXXZ"},
                                         retarget=False)
        _, sections, symbols, _ = parse(data)
        target = symbols[sections[3]["relocs"][0][1]]
        self.assertEqual((target["name"], target["section"]), ("?dup@@YAXXZ", 1))

    def test_static_promotion(self):
        data = bytearray(self.object_with_reference())
        idx = next(i for i, name, *_ in coffgen.read_symbols(bytes(data)) if name == "?S@@YAXXZ")
        symptr = struct.unpack_from("<I", data, 8)[0]
        data[symptr + 18 * idx + 16] = coffgen.CLASS_STATIC
        out, n = coffgen.rename_symbols(bytes(data), {"?S@@YAXXZ": "?static_1@@YAXXZ"}, retarget=False,
                                        statics=True)
        self.assertEqual(n, 1)
        sym = next(s for s in coffgen.read_symbols(out) if s[1] == "?static_1@@YAXXZ")
        self.assertEqual(sym[4], coffgen.CLASS_EXTERNAL)

    def test_section_names(self):
        data = coffgen.set_section_names(self.object_with_reference(), {2: ".text$zz"})
        _, sections, _, _ = parse(data)
        self.assertEqual(sections[2]["name"], ".text$zz")
        self.assertEqual(coffgen.section_symbols(data)[2], ["?S@@YAXXZ"])


if __name__ == "__main__":
    unittest.main()
