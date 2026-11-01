#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original; synthetic instruction streams only.
"""Tests for regpredict (homm3-style register model labels)."""
import unittest

import regpredict as rp
import residual_classify as rc


def D(*lines):
    out = []
    for line in lines:
        m, _, o = line.partition(" ")
        out.append(rc.dissect(m, o, set(), True))
    return out


class Predict(unittest.TestCase):
    def test_identical_is_none(self):
        self.assertIsNone(rp.predict(D("mov eax,ecx"), D("mov eax,ecx")))

    def test_schedule_parked(self):
        p = rp.predict(D("inc eax", "dec ecx"), D("dec ecx", "inc eax"))
        self.assertEqual(p["label"], "B16-schedule")

    def test_role_swap_of_call_crossing_values(self):
        r = D("mov esi,ecx", "mov edi,edx", "call 0x401000", "push esi", "push edi")
        c = D("mov edi,ecx", "mov esi,edx", "call 0x401000", "push edi", "push esi")
        p = rp.predict(r, c)
        self.assertEqual(p["label"], "B1-role-swap")
        self.assertIn("creation order", p["lever"])

    def test_call_crossing_mismatch(self):
        r = D("mov esi,ecx", "call 0x401000", "push esi")
        c = D("mov edx,ecx", "call 0x401000", "push edx")
        self.assertEqual(rp.predict(r, c)["label"], "B1-call-crossing")

    def test_rebind(self):
        r = D("mov esi,ecx", "push esi")
        c = D("mov ebx,ecx", "push ebx")
        p = rp.predict(r, c)
        self.assertEqual(p["label"], "B1-rebind")
        self.assertIn("retail follows first-fit", p["detail"])

    def test_commutative_and_cmp_labels(self):
        self.assertEqual(rp.predict(D("add eax,ecx"), D("add ecx,eax"))["label"], "commutative-swap")
        self.assertEqual(rp.predict(D("cmp eax,ecx"), D("cmp ecx,eax"))["label"], "cmp-swap")
        self.assertEqual(rp.predict(D("sub eax,ecx"), D("sub ecx,eax"))["label"], "B1-role-swap")

    def test_zero_cse(self):
        r = D("xor eax,eax", "mov [ecx],eax", "mov [ecx+0x4],eax")
        c = D("mov [ecx],0x0", "mov [ecx+0x4],0x0", "ret")
        self.assertEqual(rp.predict(r, c)["label"], "B8-zero-cse")

    def test_unmodelled(self):
        self.assertEqual(rp.predict(D("inc eax"), D("dec eax"))["label"], "unmodelled")

    def test_first_fit_prefix(self):
        self.assertTrue(rp.first_fit_prefix(["esi", "edi", "ebx"]))
        self.assertFalse(rp.first_fit_prefix(["edi", "esi"]))
        self.assertTrue(rp.first_fit_prefix(["eax", "ecx"]))


if __name__ == "__main__":
    unittest.main()
