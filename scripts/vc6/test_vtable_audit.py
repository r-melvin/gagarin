#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original synthetic data; no retail bytes.
"""vtable_audit: slot classification."""

import bisect
import sys
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import vtable_audit  # noqa: E402

ENTRIES = [{"addr": 0x401000, "end": 0x401020, "symbol": "?f@@YAXXZ", "kind": "matched"},
           {"addr": 0x401020, "end": 0x401040, "symbol": "?stub_00401020@@YAXXZ", "kind": "stub"},
           {"addr": 0x401040, "end": 0x401060, "symbol": "?g@@YAXXZ", "kind": "matched"}]
STARTS = [e["addr"] for e in ENTRIES]


def classify(name, target, bound=None):
    return vtable_audit.classify(name, target, ENTRIES, STARTS, bound or {}, [(0x500000, 0x501000)], 0x600000)


class ClassifyTests(unittest.TestCase):
    def test_the_slot_names_the_matched_function_at_its_entry(self):
        self.assertEqual(classify("?f@@YAXXZ", 0x401000), ("own body", None))
        self.assertEqual(classify("?h@@YAXXZ", 0x401000, {"?h@@YAXXZ": 0x401000}), ("own body", None))
        self.assertEqual(classify("?h@@YAXXZ@pin00401000", 0x401000), ("own body", None))

    def test_another_name_for_a_matched_body_is_an_alias(self):
        self.assertEqual(classify("?h@@YAXXZ", 0x401040), ("alias", "?g@@YAXXZ"))

    def test_stub_library_data_and_elsewhere(self):
        self.assertEqual(classify("?x@@YAXXZ", 0x401020)[0], "stub")
        self.assertEqual(classify("?x@@YAXXZ", 0x500010)[0], "library")
        self.assertEqual(classify("??_R4A@@6B@", 0x700000)[0], "data")
        self.assertEqual(classify("?x@@YAXXZ", 0x401008), ("elsewhere", "inside ?f@@YAXXZ"))
        self.assertEqual(classify("?x@@YAXXZ", 0x4F0000)[0], "elsewhere")


if __name__ == "__main__":
    unittest.main()
