#!/usr/bin/env python3
"""Unit tests for dupaddr.py (no objects, no retail binary).

    python3 -m unittest test_dupaddr        (from this directory)
"""
import json
import os
import sys
import tempfile
import unittest

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import dupaddr as D  # noqa: E402


def tree(files, bindings=None, rows=None):
    d = tempfile.mkdtemp(prefix="dupaddr_t_")
    for rel, text in files.items():
        p = os.path.join(d, rel)
        os.makedirs(os.path.dirname(p), exist_ok=True)
        with open(p, "w") as f:
            f.write(text)
    os.makedirs(os.path.join(d, "scripts/data"))
    with open(os.path.join(d, D.BINDINGS), "w") as f:
        json.dump(bindings or {}, f)
    with open(os.path.join(d, D.MANIFEST), "w") as f:
        json.dump(rows or [], f)
    return d


class SourceDefs(unittest.TestCase):
    def test_definition_vs_extern_static_const(self):
        t = ("// GLOBAL: GAMEMD 0x1\nvoid* DAT_00000001;\n"
             "// GLOBAL: GAMEMD 0x2\nextern int DAT_00000002;\n"
             "// GLOBAL: GAMEMD 0x3\nstatic int DAT_00000003;\n"
             "// GLOBAL: GAMEMD 0x4\nint Tab[4] = {1, 2,\n 3, 4};\n"
             "// GLOBAL: GAMEMD 0x5\nvoid (*pfn)(int);\n"
             "// GLOBAL: GAMEMD 0x6\nint proto(int);\n"
             "// GLOBAL: GAMEMD 0x7\nconst double DAT_7 = 2.0;\n"
             "// GLOBAL: GAMEMD 0x8\nconst char* const names[] = { \"a\" };\n"
             "// GLOBAL: GAMEMD 0x9\nconst char* DAT_9;\n"
             "// GLOBAL: GAMEMD 0xA\nextern const double DAT_A = 2.0;\n")
        self.assertEqual([(a, n) for a, n, _ in D.source_defs(t)], [(1, "DAT_00000001"), (4, "Tab"), (5, "pfn"), (9, "DAT_9"), (10, "DAT_A")])

    def test_annotation_without_own_declaration(self):
        t = "// GLOBAL: GAMEMD 0x10 (written by x)\n// note\n// GLOBAL: GAMEMD 0x20\nint A;\n"
        self.assertEqual([(a, n) for a, n, _ in D.source_defs(t)], [(0x20, "A")])


class Resolve(unittest.TestCase):
    def test_priority_and_names(self):
        d = tree({}, bindings={"?Foo@@3HA": "0x00401000", "a.cpp::?Bar@@3HA": "0x00402000"},
                 rows=[{"sym": "?M@C@@QAEXXZ", "addr": "0x00403000", "status": "matched"}])
        r = D.Resolver(d)
        self.assertEqual(r.addr("b.cpp", "?Foo@@3HA"), 0x401000)
        self.assertEqual(r.addr("a.cpp", "?Bar@@3HA"), 0x402000)
        self.assertIsNone(r.addr("b.cpp", "?Bar@@3HA"))
        self.assertEqual(r.addr("b.cpp", "?DAT_00B0FB48@@3PAUWholeFileBlock@@A"), 0xB0FB48)
        self.assertEqual(r.addr("b.cpp", "_FUN_00401010@8"), 0x401010)
        self.assertEqual(r.addr("b.cpp", "?M@C@@QAEXXZ"), 0x403000)
        self.assertIsNone(r.addr("b.cpp", "?Other@@3HA"))


class Gate(unittest.TestCase):
    def run_collect(self, files, strong, **kw):
        d = tree(files, **kw)
        return D.violations(D.collect(d, sorted(files), lambda tu: strong.get(tu)))

    def test_same_address_different_mangling_fails(self):
        v = self.run_collect({"a.cpp": "void* DAT_00B0FB48;\n", "b.cpp": "WholeFileBlock* DAT_00B0FB48;\n"},
                             {"a.cpp": ["?DAT_00B0FB48@@3PAXA"], "b.cpp": ["?DAT_00B0FB48@@3PAUWholeFileBlock@@A"]})
        self.assertEqual(list(v), [0xB0FB48])
        self.assertEqual(D.categorize(v[0xB0FB48]), "same-name")

    def test_declaration_only_is_fine(self):
        v = self.run_collect({"a.cpp": "extern int DAT_00B0FB48;\n", "b.cpp": "int DAT_00B0FB48;\n"},
                             {"b.cpp": ["?DAT_00B0FB48@@3HA"]})
        self.assertEqual(v, {})

    def test_binding_and_annotation_without_ghidra_name(self):
        v = self.run_collect({"a.cpp": "int gA;\n", "b.cpp": "// GLOBAL: GAMEMD 0x00500000\nlong gB;\n"},
                             {"a.cpp": ["?gA@@3HA"], "b.cpp": ["?gB@@3JA"]}, bindings={"?gA@@3HA": "0x00500000"})
        self.assertEqual(list(v), [0x500000])

    def test_annotation_needs_an_object_symbol(self):
        v = self.run_collect({"a.cpp": "// GLOBAL: GAMEMD 0x00500000\nstatic int gA;\n",
                              "b.cpp": "// GLOBAL: GAMEMD 0x00500000\nint gB;\n"},
                             {"a.cpp": [], "b.cpp": ["?gB@@3HA"]})
        self.assertEqual(v, {})

    def test_distinct_addresses_pass(self):
        v = self.run_collect({"a.cpp": "", "b.cpp": ""}, {"a.cpp": ["?DAT_00000001@@3HA"], "b.cpp": ["?DAT_00000002@@3HA"]})
        self.assertEqual(v, {})

    def test_code_category(self):
        v = self.run_collect({"a.cpp": "", "b.cpp": ""}, {"a.cpp": ["?FUN_00401000@A@@QAEXXZ"], "b.cpp": ["?FUN_00401000@B@@QAEXXZ"]})
        self.assertEqual(D.categorize(v[0x401000]), "code")


class Ratchet(unittest.TestCase):
    def test_new_legacy_fixed(self):
        mem = lambda *tus: [(t, "N", []) for t in tus]
        base = D.to_baseline({1: mem("a.cpp", "b.cpp"), 2: mem("c.cpp", "d.cpp")})
        new, fixed = D.new_violations({1: mem("a.cpp", "b.cpp")}, base)
        self.assertEqual((new, fixed), ({}, [2]))
        new, _ = D.new_violations({1: mem("a.cpp", "b.cpp", "e.cpp")}, base)      # a third TU joins a legacy address
        self.assertEqual(list(new), [1])
        new, _ = D.new_violations({3: mem("x.cpp", "y.cpp")}, base)                # a brand-new address
        self.assertEqual(list(new), [3])
        new, _ = D.new_violations({3: mem("x.cpp", "y.cpp")}, None)
        self.assertEqual(list(new), [3])


if __name__ == "__main__":
    unittest.main()
