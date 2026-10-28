#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original synthetic data; no retail bytes.
"""imports: library symbols of the import address table slots."""

import sys
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import imports  # noqa: E402
import tail_layout  # noqa: E402


class FakeRetail:
    pe = b""
    sections = []


class ImportSymbolTests(unittest.TestCase):
    def setUp(self):
        self.slots, self.names = tail_layout.import_slots, tail_layout.decorated_names
        tail_layout.import_slots = lambda *a: {0x7E1008: ("kernel32", "Beta"), 0x7E1000: ("kernel32", "Alpha"),
                                              0x7E100C: ("wsock32", 7), 0x7E1010: ("binkw32", "_BinkOpen@8"),
                                              0x7E1014: ("user32", "Missing")}
        tail_layout.decorated_names = lambda libdir, extra=(): {("kernel32", "Alpha"): "_Alpha@4",
                                                                ("kernel32", "Beta"): "_Beta@0",
                                                                ("wsock32", 7): "_socket@12"}

    def tearDown(self):
        tail_layout.import_slots, tail_layout.decorated_names = self.slots, self.names

    def test_symbols_follow_slot_order_and_thunks_are_referenced_by_name(self):
        symbols, missing = imports.import_symbols(FakeRetail(), "lib", thunks={"_Beta@0"})
        self.assertEqual(symbols[:3], ["__imp__Alpha@4", "_Beta@0", "__imp__socket@12"])
        self.assertEqual(symbols[3], "__imp__BinkOpen@8")   # a decorated DLL export is its own symbol
        self.assertEqual(missing, [(0x7E1014, "user32", "Missing")])


if __name__ == "__main__":
    unittest.main()
