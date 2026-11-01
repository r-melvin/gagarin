#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original. Tests for global_decls.py and global_unify.py.
import os
import sys
import tempfile
import unittest

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import global_decls as GD  # noqa: E402
import global_unify as GU  # noqa: E402


def decls(text):
    code, _ = GD.strip_code(text)
    return [GD.parse_decl(st) for _, _, st in GD.statements(code)]


class ParseTests(unittest.TestCase):
    def test_extern_and_definition(self):
        d = decls("extern const char STR_00817F70[];\nint g_Count = 3;\nconst float k = 1.0f;\n")
        self.assertEqual([(x["name"], x["extern"], x["type"]) for x in d],
                         [("STR_00817F70", True, "const char []"), ("g_Count", False, "int"), ("k", False, "const float")])

    def test_extern_with_initialiser_is_a_definition(self):
        d = decls("extern const float X = 1.0f;\n")[0]
        self.assertFalse(d["extern"])
        self.assertTrue(d["init"])

    def test_skips_functions_types_and_bodies(self):
        d = decls("void f(int a);\nstruct S { int x; };\nint g() { return 1; }\nextern int ok;\n")
        self.assertEqual([x["name"] for x in d if x], ["ok"])

    def test_qualified_member_is_flagged(self):
        d = decls("extern DynamicVectorClass<A* > Holder::Array;\n")[0]
        self.assertTrue(d["qualified"])

    def test_initialiser_braces_and_extern_c(self):
        d = decls('extern "C" {\nextern int a;\n}\nint t[] = { 1, 2 };\nextern int b;\n')
        self.assertEqual([x["name"] for x in d if x], ["a", "t", "b"])


class ScanTests(unittest.TestCase):
    def test_annotation_binds_an_unnamed_declaration(self):
        with tempfile.TemporaryDirectory() as t:
            os.makedirs(os.path.join(t, "match"))
            os.makedirs(os.path.join(t, "scripts/data"))
            open(os.path.join(t, "scripts/data/symbol_bindings.json"), "w").write("{}")
            open(os.path.join(t, "match/a.cpp"), "w").write(
                "// GLOBAL: GAMEMD 0x8A0000 / 0x8A0004\nextern int First;\nextern int Second;\n\n"
                "extern int DAT_008A0008;\n")
            res = GD.scan_tree(t)
            self.assertEqual({a: [d["name"] for d in ds] for a, ds in res.items()},
                             {0x8A0000: ["First"], 0x8A0004: ["Second"], 0x8A0008: ["DAT_008A0008"]})

    def test_flags(self):
        res = {0x8A0000: [dict(name="A", type="int", extern=True, file="a.cpp"), dict(name="DAT_008A0000", type="int", extern=True, file="b.cpp")]}
        row = GD.analyse(res)[0x8A0000]
        self.assertIn("names", row["flags"])
        self.assertIn("multi-decl", row["flags"])


class UnifyTests(unittest.TestCase):
    def test_choose_name(self):
        site = lambda n: dict(name=n, type="int")  # noqa: E731
        self.assertEqual(GU.choose_name(0x8A0000, [site("DAT_008A0000"), site("Foo")], {}), "Foo")
        self.assertEqual(GU.choose_name(0x8A0000, [site("Foo"), site("Bar")], {}), None)
        self.assertEqual(GU.choose_name(0x8A0000, [site("DAT_008A0000"), site("X_008A0000")], {}), "DAT_008A0000")
        self.assertEqual(GU.choose_name(0x8A0000, [site("Foo"), site("Bar")], {"0x008A0000": "Bar"}), "Bar")

    def test_add_include_goes_after_the_last_leading_include(self):
        t = '// c\n#include <stddef.h>\n#include "a.h"\n\nint x;\n'
        self.assertEqual(GU.add_include(t, "g.h"), '// c\n#include <stddef.h>\n#include "a.h"\n#include "g.h"\n\nint x;\n')
        self.assertEqual(GU.add_include(GU.add_include(t, "g.h"), "g.h").count("g.h"), 1)

    def test_type_tokens(self):
        self.assertEqual(GU.type_tokens("const DynamicVectorClass<HouseClass* > X[0x10]", "X"), ["DynamicVectorClass", "HouseClass"])


if __name__ == "__main__":
    unittest.main()
