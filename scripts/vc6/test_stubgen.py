#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original synthetic object and extent fixtures (no retail bytes).
"""stubgen: layout arithmetic, /ORDER spelling and a full plan over a synthetic object set."""

import json
from pathlib import Path
import tempfile
import unittest

import coffgen
import stubgen


class HelperTests(unittest.TestCase):
    def test_name_address(self):
        self.assertEqual(stubgen.name_address("?FUN_0041EC90@AITriggerTypeClass@@QAE_NXZ"), 0x41EC90)
        self.assertEqual(stubgen.name_address("_FUN_00729E50@4"), 0x729E50)
        self.assertEqual(stubgen.name_address("?VT_007E16B0@@3PADA"), 0x7E16B0)
        self.assertEqual(stubgen.name_address("?DAT_00B1CF70@@3HA"), 0xB1CF70)
        self.assertIsNone(stubgen.name_address("?Reset@Obj_007B4620@@QAEXXZ"))   # receiver, not method
        self.assertIsNone(stubgen.name_address("??0?$HashTable_006249A0@H@@QAE@XZ"))
        self.assertIsNone(stubgen.name_address("_FUN_00000010"))                # outside the image

    def test_order_name(self):
        self.assertEqual(stubgen.order_name("_FUN_00729E50@4"), "FUN_00729E50@4")
        self.assertEqual(stubgen.order_name("?stub_00401000@@YAXXZ"), "?stub_00401000@@YAXXZ")
        self.assertEqual(stubgen.order_name("@lzo1x_1_compress@20"), "@lzo1x_1_compress@20")

    def test_stub_layout_uses_the_whole_slot(self):
        entries = [["0x401000", "0xD", "0x3", "nop", "engine", []],
                   ["0x401010", "0x5", "0x1", "mixed", "engine", []],
                   ["0x401016", "0x4", "0x0", "none", "engine", []]]
        self.assertEqual(stubgen.stub_layout(entries), [(0x401000, 0x10, 16), (0x401010, 0x6, 16),
                                                       (0x401016, 0x4, 2)])

    def test_looks_like_function(self):
        self.assertTrue(stubgen.looks_like_function("?F@@YAXXZ", set()))
        self.assertFalse(stubgen.looks_like_function("?g@@3HA", set()))
        self.assertFalse(stubgen.looks_like_function("??_7X@@6B@", set()))
        self.assertTrue(stubgen.looks_like_function("_f", {"_f"}))
        self.assertTrue(stubgen.looks_like_function("_api@8", set()))


class PlanTests(unittest.TestCase):
    EXTENTS = [["0x401000", "0xD", "0x3", "nop", "engine", []],
               ["0x401010", "0x20", "0x0", "none", "engine", []],
               ["0x401030", "0x5", "0xB", "mixed", "engine", []],
               ["0x401040", "0x3", "0xD", "nop", "engine", []],
               ["0x7C8A8E", "0x10", "0x0", "none", "crt", []]]
    MANIFEST = [{"tu": "match/a.cpp", "addr": "0x401000", "sym": "?M@@YAXXZ", "len": "0x10", "status": "matched"},
                {"tu": "match/a.cpp", "addr": "0x401030", "sym": "?P@@YAXXZ", "len": "0x5", "status": "partial"},
                {"tu": "match/a.cpp", "addr": "0x401040", "sym": "?S@@YAXXZ", "len": "0x3", "status": "matched"}]
    BINDINGS = {"?Callee@@YAXXZ": "0x00401010", "match/a.cpp::?Alias@@YAXXZ": "0x00401000"}

    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        root = Path(self.tmp.name)
        objdir = root / "obj"
        (objdir / "match").mkdir(parents=True)
        w = coffgen.ObjectWriter()
        w.add_code_comdat(["?M@@YAXXZ"], 0x10)
        w.add_code_comdat(["?P@@YAXXZ"], 0x10)
        w.add_code_comdat(["?S@@YAXXZ"], 0x10)
        w.set_anchor(["?Callee@@YAXXZ", "_FUN_007C8A8E", "?DAT_00812000@@3HA", "?Unknown@@YAXXZ",
                      "?Alias@@YAXXZ", "?P@@YAXXZ", "_lib_func"])
        data = bytearray(w.build())
        # make ?S static, as VC6 emits file-local functions
        idx = next(i for i, name, *_ in coffgen.read_symbols(bytes(data)) if name == "?S@@YAXXZ")
        symptr = int.from_bytes(data[8:12], "little")
        data[symptr + 18 * idx + 16] = coffgen.CLASS_STATIC
        (objdir / "match/a.obj").write_bytes(bytes(data))
        (objdir / "objects.json").write_text(json.dumps(
            {"success": True, "objects": [{"object": "match/a.obj", "source": "match/a.cpp"}]}))
        self.out = root / "out"
        self.result = stubgen.plan(objdir, {"_lib_func"}, self.out, manifest=self.MANIFEST,
                                   extents=self.EXTENTS, symbol_bindings=self.BINDINGS)

    def tearDown(self):
        self.tmp.cleanup()

    def stub_symbols(self):
        return {name: (section, value, scl) for _, name, value, section, scl, _ in
                coffgen.read_symbols((self.out / "stubs.obj").read_bytes())}

    def test_order_and_placement(self):
        order = (self.out / "order.txt").read_text().split()
        self.assertEqual(order, ["?M@@YAXXZ", "?stub_00401010@@YAXXZ", "?stub_00401030@@YAXXZ",
                                 "?static_00401040@@YAXXZ"])
        kinds = [(p["addr"], p["kind"]) for p in self.result["placed"]]
        self.assertEqual(kinds, [("0x401000", "matched"), ("0x401010", "stub"), ("0x401030", "stub"),
                                 ("0x401040", "matched")])
        self.assertEqual(self.result["static_functions_promoted"], 1)

    def test_stub_names_and_partial_displacement(self):
        syms = self.stub_symbols()
        self.assertGreater(syms["?Callee@@YAXXZ"][0], 0)          # defined by the 0x401010 stub
        self.assertGreater(syms["?P@@YAXXZ"][0], 0)               # partial row: the stub owns its name
        self.assertEqual(syms["?Alias@@YAXXZ"][2], 105)           # second name of a matched function
        # COMMON sized to the next known data address (here: the end of .data)
        self.assertEqual(syms["?DAT_00812000@@3HA"], (0, 0x367BE4, 2))
        self.assertGreater(syms["?Unknown@@YAXXZ"][0], 0)        # unbound function: tail stub
        copy = self.out / "objects/match/a.obj"
        names = {name: section for _, name, _, section, scl, _ in coffgen.read_symbols(copy.read_bytes())
                 if scl == 2}
        self.assertEqual(names["?P@@YAXXZ"], 0)                   # reference kept, definition renamed
        self.assertTrue(any(n.startswith("__displaced_00401030") for n in names))
        self.assertIn("?static_00401040@@YAXXZ", names)
        self.assertEqual(self.result["extra_stubs"]["code_unbound"], 1)
        self.assertNotIn("_lib_func", syms)                       # a library provides it

    def test_stub_sizes_cover_the_retail_slot(self):
        data = (self.out / "stubs.obj").read_bytes()
        sizes = {}
        for _, name, value, section, scl, _ in coffgen.read_symbols(data):
            if name.startswith("?stub_") and scl == 2:
                sizes[name] = int.from_bytes(data[20 + 40 * (section - 1) + 16:20 + 40 * (section - 1) + 20],
                                             "little")
        self.assertEqual(sizes, {"?stub_00401010@@YAXXZ": 0x20, "?stub_00401030@@YAXXZ": 0x10})


if __name__ == "__main__":
    unittest.main()
