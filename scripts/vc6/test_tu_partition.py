#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original (synthetic fixtures only; needs no binary)
"""Fixture checks for the TU partition rules."""
import unittest

import tu_partition as tp


def ext(*rows):
    return {"entries": [["0x%X" % a, "0x10", "0x0", "nop", k, []] for a, k in rows]}


def vt(slots, va="0x900000"):
    return [{"vtable_va": va, "base_offset": 0, "slots": ["0x%X" % s for s in slots]}]


def cls(name, chain=None):
    return {"demangled_name": name, "mangled_name": ".?AV" + name, "locators": [],
            "base_chain": chain or [name]}


def files(*specs):
    return [{"file": f, "string_va": "0x%X" % (0x810000 + 0x100 * i), "sites": [{"site": "0x%X" % s, "line": 1} for s in sites]}
            for i, (f, sites) in enumerate(specs)]


class PartitionTests(unittest.TestCase):
    def run_fixture(self, asserts, rows, vtables=None, classes=None, sdd=None, names=None):
        evidence = {"asserts": asserts, "vtables": vtables or {}, "scalar_deleting": sdd or {}}
        rtti = {"classes": classes or {}}
        res = tp.partition(evidence, ext(*rows), rtti, names)
        return {r["addr"]: r for r in res["functions"]}, res

    def test_witnessed_contiguity_and_brackets(self):
        rows = [(0x1000 + 0x20 * i, "engine") for i in range(10)]
        a = files(("A.cpp", [0x1000 + 4]), ("A.cpp", [0x1040 + 4]), ("B.cpp", [0x1080 + 4]))
        a[1]["file"] = "A.cpp"
        a = [a[0], a[2]]
        a[1]["string_va"] = "0x810100"
        a[0]["sites"].append({"site": "0x1044", "line": 2})
        f, res = self.run_fixture(a, rows)
        self.assertEqual(f["0x1000"]["tu_kind"], "witnessed")
        self.assertEqual((f["0x1020"]["tu"], f["0x1020"]["tu_kind"]), ("A.cpp", "inferred-contiguity"))
        self.assertEqual(f["0x1040"]["tu_kind"], "witnessed")
        self.assertEqual(f["0x1060"]["tu_kind"], "unknown")       # A tail or an assert-free TU or B head
        self.assertEqual(f["0x1060"]["bracket"], ["A.cpp", "B.cpp"])
        self.assertEqual(f["0x10C0"]["bracket"], ["B.cpp", None])

    def test_out_of_order_assert_is_demoted_to_comdat(self):
        rows = [(0x1000 + 0x20 * i, "engine") for i in range(6)]
        a = files(("A.cpp", [0x1004, 0x1044, 0x1064]), ("B.cpp", [0x1024]))
        f, res = self.run_fixture(a, rows)
        self.assertEqual(f["0x1020"]["tu_kind"], "comdat")
        self.assertIn("inlined assert", f["0x1020"]["evidence"])
        self.assertEqual(f["0x1040"]["tu"], "A.cpp")
        self.assertEqual(res["meta"]["out_of_order_witnessed_functions"], 1)

    def test_class_owned_slots_and_inherited_slots(self):
        rows = [(0x1000 + 0x20 * i, "engine") for i in range(8)]
        a = files(("A.cpp", [0x1004]), ("B.cpp", [0x10E4]))
        vts = {"Base|.?AVBase": vt([0x1040, 0x1060]), "Derived|.?AVDerived": vt([0x1040, 0x1080], "0x900100")}
        classes = {"b": cls("Base"), "d": cls("Derived", ["Derived", "Base"])}
        f, _ = self.run_fixture(a, rows, vts, classes)
        self.assertEqual((f["0x1040"]["tu"], f["0x1040"]["tu_kind"]), ("class:Base", "inferred-class"))
        self.assertEqual(f["0x1060"]["tu"], "class:Base")
        self.assertEqual(f["0x1080"]["tu"], "class:Derived")      # 0x1040 is inherited, 0x1080 is new
        self.assertEqual(f["0x1040"]["bracket"], ["A.cpp", "B.cpp"])
        self.assertEqual(f["0x1020"]["tu_kind"], "unknown")       # before the first class cluster
        self.assertEqual(f["0x1060"]["tu_kind"], "inferred-class")

    def test_same_class_fills_between(self):
        rows = [(0x1000 + 0x20 * i, "engine") for i in range(8)]
        a = files(("A.cpp", [0x1004]), ("B.cpp", [0x10E4]))
        vts = {"X|.?AVX": vt([0x1040, 0x1080])}
        f, _ = self.run_fixture(a, rows, vts, {"x": cls("X")})
        self.assertEqual((f["0x1060"]["tu"], f["0x1060"]["tu_kind"]), ("class:X", "inferred-contiguity"))

    def test_other_class_slot_blocks_contiguity(self):
        rows = [(0x1000 + 0x20 * i, "engine") for i in range(8)]
        a = files(("A.cpp", [0x1004]), ("B.cpp", [0x10E4]))
        vts = {"X|.?AVX": vt([0x1040, 0x1080]), "Y|.?AVY": vt([0x1060], "0x900100")}
        f, _ = self.run_fixture(a, rows, vts, {"x": cls("X"), "y": cls("Y")})
        self.assertEqual(f["0x1060"]["tu"], "class:Y")

    def test_class_inside_witnessed_tu_pulls_its_slots_in(self):
        rows = [(0x1000 + 0x20 * i, "engine") for i in range(8)]
        a = files(("A.cpp", [0x1004, 0x1064]), ("B.cpp", [0x10E4]))
        vts = {"X|.?AVX": vt([0x1040, 0x1080])}      # 0x1040 sits inside A's interval, 0x1080 is past it
        f, _ = self.run_fixture(a, rows, vts, {"x": cls("X")})
        self.assertEqual((f["0x1040"]["tu"], f["0x1040"]["tu_kind"]), ("A.cpp", "inferred-contiguity"))
        self.assertEqual((f["0x1080"]["tu"], f["0x1080"]["tu_kind"]), ("A.cpp", "inferred-class"))

    def test_template_and_scalar_deleting_are_comdat(self):
        rows = [(0x1000 + 0x20 * i, "engine") for i in range(8)]
        a = files(("A.cpp", [0x1004]), ("B.cpp", [0x10E4]))
        vts = {"V<int>|.?AV?$V@H": vt([0x1040]), "C|.?AVC": vt([0x1060, 0x1080], "0x900100")}
        classes = {"v": cls("V<int>"), "c": cls("C")}
        f, _ = self.run_fixture(a, rows, vts, classes, sdd={"0x1060": "0x10A0"})
        self.assertEqual(f["0x1040"]["tu_kind"], "comdat")
        self.assertEqual(f["0x1060"]["tu_kind"], "comdat")
        self.assertEqual(f["0x1060"]["class"], "C")
        self.assertEqual(f["0x10A0"]["tu"], "class:C")
        self.assertIn("destructor called by", f["0x10A0"]["evidence"])

    def test_symbol_shape_comdat_and_library_kinds(self):
        rows = [(0x1000, "engine"), (0x1020, "engine"), (0x1040, "crt"), (0x1060, "engine")]
        a = files(("A.cpp", [0x1004, 0x1064]))
        f, _ = self.run_fixture(a, rows, names={0x1020: "??0?$Foo@H@@QAE@XZ"})
        self.assertEqual(f["0x1020"]["tu_kind"], "comdat")
        self.assertEqual(f["0x1020"]["hint_tu"], "A.cpp")
        self.assertEqual(f["0x1040"]["tu_kind"], "unknown")
        self.assertIn("extent kind crt", f["0x1040"]["evidence"])

    def test_longest_nondecreasing(self):
        self.assertEqual(tp.longest_nondecreasing([0, 1, 5, 2, 3]), [0, 1, 3, 4])
        self.assertEqual(tp.longest_nondecreasing([]), [])


if __name__ == "__main__":
    unittest.main()
