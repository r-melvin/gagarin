#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original synthetic linker-output fixtures.
"""Check link_diag's log parsing and symbol classification without Wine or retail bytes."""

from pathlib import Path
import struct
import tempfile
import unittest

import link_diag


LOG = r"""
a.obj : error LNK2001: unresolved external symbol "public: void __thiscall Foo::Bar(int)" (?Bar@Foo@@QAEXH@Z)
b.obj : error LNK2001: unresolved external symbol "public: void __thiscall Foo::Bar(int)" (?Bar@Foo@@QAEXH@Z)
a.obj : error LNK2001: unresolved external symbol "int DAT_00B1CF70" (?DAT_00B1CF70@@3HA)
a.obj : error LNK2001: unresolved external symbol "void (__cdecl* g_hook)(void)" (?g_hook@@3P6AXXZA)
a.obj : error LNK2001: unresolved external symbol "const Foo::`vftable'" (??_7Foo@@6B@)
a.obj : error LNK2001: unresolved external symbol "char VT_007E3584" (?VT_007E3584@@3DA)
a.obj : error LNK2001: unresolved external symbol __imp__BinkPause@8
a.obj : error LNK2001: unresolved external symbol _FUN_007C8B48
a.obj : error LNK2001: unresolved external symbol _FUN_004A0000
a.obj : error LNK2001: unresolved external symbol @lzo_like@20
a.obj : error LNK2001: unresolved external symbol _strlen
a.obj : error LNK2005: "int Twice" (?Twice@@3HA) already defined in c.obj
LINK : warning LNK4088: image being generated due to /FORCE option; image may not run
"""


class LinkDiagTests(unittest.TestCase):
    def setUp(self):
        self.unresolved, self.duplicates = link_diag.parse_link_log(LOG)

    def test_parse_dedupes_symbols_and_keeps_referencers(self):
        self.assertEqual(len(self.unresolved), 10)
        self.assertEqual(self.unresolved["?Bar@Foo@@QAEXH@Z"]["objects"], {"a.obj", "b.obj"})
        self.assertIsNone(self.unresolved["_strlen"]["text"])
        self.assertEqual(self.duplicates, {"?Twice@@3HA": {"a.obj", "c.obj"}})

    def kind(self, sym, libs=()):
        return link_diag.classify(sym, self.unresolved[sym]["text"], set(libs), ())

    def test_classification(self):
        self.assertEqual(self.kind("?Bar@Foo@@QAEXH@Z"), "function")
        self.assertEqual(self.kind("?DAT_00B1CF70@@3HA"), "data")
        self.assertEqual(self.kind("?g_hook@@3P6AXXZA"), "data")  # function-pointer variable
        self.assertEqual(self.kind("??_7Foo@@6B@"), "vtable")
        self.assertEqual(self.kind("?VT_007E3584@@3DA"), "vtable")
        self.assertEqual(self.kind("__imp__BinkPause@8"), "import")
        self.assertEqual(self.kind("_FUN_007C8B48"), "crt")  # placeholder inside the CRT block
        self.assertEqual(self.kind("_FUN_004A0000"), "function")
        self.assertEqual(self.kind("@lzo_like@20"), "function")
        self.assertEqual(self.kind("_strlen", ["_strlen"]), "crt")
        self.assertEqual(self.kind("_strlen"), "data")  # no call relocation seen

    def test_report_counts_and_addresses(self):
        result = link_diag.report(LOG, {"_strlen"}, Path("/nonexistent"))
        self.assertEqual(result["unresolved_total"], 10)
        self.assertEqual(result["counts"], {"function": 3, "data": 2, "vtable": 2, "crt": 2, "import": 1})
        self.assertEqual(result["duplicate_definitions"], 1)
        self.assertEqual(result["distinct_addresses"]["crt"], 1)

    def test_archive_symbols_reads_first_linker_member(self):
        names = [b"_a", b"__imp__b@4"]
        body = struct.pack(">I", len(names)) + b"\0" * 4 * len(names) + b"\0".join(names) + b"\0"
        header = b"/".ljust(16) + b"0".ljust(12) + b"0".ljust(6) + b"0".ljust(6) + b"0".ljust(8)
        header += str(len(body)).encode().ljust(10) + b"`\n"
        with tempfile.TemporaryDirectory() as tmp:
            lib = Path(tmp) / "x.lib"
            lib.write_bytes(b"!<arch>\n" + header + body)
            self.assertEqual(link_diag.archive_symbols(lib), {"_a", "__imp__b@4"})

    def test_wine_path(self):
        self.assertEqual(link_diag.wine_path("/x/y.obj"), "Z:\\x\\y.obj")
        self.assertEqual(link_diag.unix_object("Z:\\x\\y.obj", Path("/o")), "/x/y.obj")


if __name__ == "__main__":
    unittest.main()
