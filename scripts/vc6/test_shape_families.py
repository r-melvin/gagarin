#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original synthetic instruction-text fixtures; no binary needed.
"""shape_families: normalisation, hashing and clustering on synthetic input."""

import unittest

import shape_families as sf

LO, HI = 0x400000, 0x900000


def h(texts):
    return sf.shape_hashes(texts, LO, HI)


class Normalise(unittest.TestCase):
    def n(self, t, coarse=False):
        return sf.normalise(t, LO, HI, coarse)

    def test_calls_and_jumps_masked(self):
        self.assertEqual(self.n("call 0x4a1234"), "call T")
        self.assertEqual(self.n("jne 0x401020"), "jne T")
        self.assertEqual(self.n("call DWORD PTR [eax+0x8]"), "call DWORD PTR [eax+0x8]")

    def test_addresses_masked_registers_kept(self):
        self.assertEqual(self.n("mov eax,ds:0x7e1234"), "mov eax,ds:A")
        self.assertEqual(self.n("push 0x82a000"), "push A")
        self.assertEqual(self.n("mov ecx,DWORD PTR [edx*4+0x7e1234]"), "mov ecx,DWORD PTR [edx*4+A]")
        self.assertNotEqual(self.n("mov eax,ecx"), self.n("mov eax,edx"))

    def test_levels(self):
        t = "mov eax,DWORD PTR [ecx+0x30]"
        self.assertEqual(self.n(t), t)
        self.assertEqual(self.n(t, True), "mov eax,DWORD PTR [ecx+N]")
        self.assertEqual(self.n("ret 0x8", True), "ret 0x8")
        self.assertEqual(self.n("sub esp,-0x10"), "sub esp,-0x10")

    def test_rep_prefix(self):
        self.assertEqual(self.n("rep movs DWORD PTR es:[edi],DWORD PTR ds:[esi]"),
                         "rep movs DWORD PTR es:[edi],DWORD PTR ds:[esi]")


class Hashing(unittest.TestCase):
    def test_same_shape_different_addresses(self):
        a = h(["mov eax,ds:0x7e1000", "call 0x401100", "ret"])
        b = h(["mov eax,ds:0x7e2000", "call 0x4ffff0", "ret"])
        self.assertEqual(a, b)

    def test_exact_vs_coarse(self):
        a = h(["mov eax,DWORD PTR [ecx+0x30]", "ret"])
        b = h(["mov eax,DWORD PTR [ecx+0x34]", "ret"])
        self.assertNotEqual(a[0], b[0])
        self.assertEqual(a[1], b[1])

    def test_register_difference_splits(self):
        self.assertNotEqual(h(["mov eax,ecx", "ret"])[1], h(["mov eax,edx", "ret"])[1])


def F(addr, ln, status, hashes, **kw):
    d = {"addr": addr, "len": ln, "status": status, "hashes": hashes, "n_insns": 3}
    d.update(kw)
    return d


class Cluster(unittest.TestCase):
    def test_families_and_totals(self):
        funcs = [
            F(1, 10, "matched", ["a", "x"], tu="t.cpp", sym="s", pct=100),
            F(2, 10, "unmatched", ["a", "x"]),
            F(3, 20, "unmatched", ["a", "x"]),
            F(4, 7, "unmatched", ["b", "x"]),      # coarse-only join
            F(5, 8, "unmatched", ["c", "c"]),
            F(6, 8, "unmatched", ["c", "c"]),      # all unmatched: no exemplar
            F(7, 9, "matched", ["d", "d"]),
            F(8, 9, "matched", ["d", "d"]),        # nothing to recover: dropped
            F(9, 5, "unmatched", ["e", "e1"]),     # singleton
        ]
        fams = sf.cluster(funcs)
        self.assertEqual([f["hash"] for f in fams["exact"]], ["a", "c"])
        self.assertEqual(fams["exact"][0]["recoverable_bytes"], 30)
        self.assertEqual(fams["exact"][1]["recoverable_bytes"], 0)
        t = sf.totals(fams)
        self.assertEqual(t["exact"]["recoverable_functions"], 2)
        self.assertEqual(t["exact"]["recoverable_bytes"], 30)
        self.assertEqual(t["coarse"]["recoverable_functions"], 3)
        self.assertEqual(t["coarse"]["recoverable_bytes"], 37)
        self.assertEqual(fams["coarse"][0]["exemplar"]["addr"], 1)

    def test_report_renders(self):
        funcs = [F(1, 10, "matched", ["a", "a"], tu="t.cpp", sym="s", name="N", pct=100),
                 F(2, 10, "unmatched", ["a", "a"], rtti=["Foo[3]"])]
        fams = sf.cluster(funcs)
        out = sf.report(fams, sf.totals(fams), 2)
        self.assertIn("Foo[3]", out)
        self.assertIn("0x1 ", out)


if __name__ == "__main__":
    unittest.main()
