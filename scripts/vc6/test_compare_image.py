#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original synthetic data; no retail bytes.
"""compare_image: bytes by origin."""

import sys
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import compare_image  # noqa: E402


class OriginCounts(unittest.TestCase):
    def test_pieces_count_by_origin_and_the_rest_is_retail(self):
        sections = [(".text", 0x1000, 0x100, bytes(0x100)), (".data", 0x2000, 0x80, bytes(0x40))]
        pieces = [[".text", 0x1000, 0x20, "project", "a"], [".text", 0x1040, 0x10, "library", "b"],
                  [".data", 0x2030, 0x20, "project", "c"]]
        c = compare_image.origin_counts(sections, pieces)
        self.assertEqual(c[".text"], {"vsize": 0x100, "file": 0x100, "project": 0x20, "library": 0x10, "retail": 0xD0})
        # an uninitialised tail counts in the virtual size
        self.assertEqual(c[".data"]["project"], 0x20)
        self.assertEqual(c[".data"]["retail"], 0x60)

    def test_a_piece_outside_the_section_is_clipped(self):
        c = compare_image.origin_counts([(".text", 0x1000, 0x10, bytes(0x10))], [[".text", 0x1008, 0x100, "project", "a"]])
        self.assertEqual(c[".text"]["project"], 8)


if __name__ == "__main__":
    unittest.main()
