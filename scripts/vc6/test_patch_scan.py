#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original synthetic fixtures; no retail bytes.
"""Check patch_scan's stub matcher and prologue/epilogue comparison on synthetic code."""

import unittest

import patch_scan


class Img:
    def __init__(self, base, code):
        self.base, self.code = base, code

    def read(self, va, n):
        off = va - self.base
        return self.code[off:off + n]


class StubTests(unittest.TestCase):
    def test_stub_shapes(self):
        for code, n in ((b"\xb0\x01\xc3", 3), (b"\xb8\x02\x00\x00\x00\xc3", 6), (b"\x33\xc0\xc3", 3),
                        (b"\xc3", 1), (b"\xc2\x04\x00", 3), (b"\xe9\x00\x00\x00\x00", 5)):
            self.assertEqual(patch_scan.stub_at(code + b"\x90" * 8, 0), n)
        self.assertEqual(patch_scan.stub_at(b"\x55\x8b\xec\x83\xec\x10", 0), 0)


class AnalyseTests(unittest.TestCase):
    def test_pop_without_push_is_flagged(self):
        # push esi is gone: mov esi,ecx ; mov eax,esi ; pop esi ; ret
        ev = patch_scan.analyse(Img(0x1000, b"\x8b\xf1\x8b\xc6\x5e\xc3"), 0x1000)
        self.assertEqual(ev["pops_without_push"], ["esi"])

    def test_balanced_function_is_not_flagged(self):
        ev = patch_scan.analyse(Img(0x1000, b"\x56\x8b\xf1\x8b\xc6\x5e\xc3"), 0x1000)
        self.assertEqual(ev["pops_without_push"], [])

    def test_add_esp_without_sub_is_flagged(self):
        ev = patch_scan.analyse(Img(0x1000, b"\x33\xc0\x83\xc4\x10\xc3"), 0x1000)
        self.assertEqual(ev["add_esp_without_sub"], [0x10])


if __name__ == "__main__":
    unittest.main()
