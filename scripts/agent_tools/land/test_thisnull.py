#!/usr/bin/env python3
"""Unit tests for thisnull.py and the `thisnull` land gate.

    GAMEMD_BINARY=... python3 -m unittest test_thisnull        (from this directory)

The retail-byte checks are skipped when GAMEMD_BINARY is not set.
"""
import os
import sys
import types
import unittest
import unittest.mock as mock

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import thisnull as TN  # noqa: E402

BIN = os.environ.get("GAMEMD_BINARY", "")


class Annotation(unittest.TestCase):
    def test_same_line_and_line_above_only(self):
        lines = ["a", "// THISNULL: GAMEMD 0x459F40", "if (this == 0) return 0;", "b", "x // THISNULL: GAMEMD 0x401000"]
        self.assertEqual(TN.annotation_addr(lines, 2), 0x459F40)
        self.assertEqual(TN.annotation_addr(lines, 1), 0x459F40)
        self.assertIsNone(TN.annotation_addr(lines, 3))
        self.assertEqual(TN.annotation_addr(lines, 4), 0x401000)
        self.assertIsNone(TN.annotation_addr(["// THISNULL: GAMEMD notanaddr", "x"], 1))

    def test_is_matched(self):
        self.assertTrue(TN.is_matched({"status": "matched", "pct": 100.0}))
        self.assertFalse(TN.is_matched({"status": "partial", "pct": 97.0}))
        self.assertFalse(TN.is_matched({"status": "matched", "pct": 99.0}))
        self.assertFalse(TN.is_matched(None))


@unittest.skipUnless(BIN and os.path.isfile(BIN), "GAMEMD_BINARY not set")
class RetailBytes(unittest.TestCase):
    def test_entry_tests(self):
        self.assertTrue(TN.entry_tests_this(BIN, 0x459F40))      # push esi; mov esi,ecx; test esi,esi
        self.assertFalse(TN.entry_tests_this(BIN, 0x459F60))     # reads an argument first, no this test

    def test_gate(self):
        import gates
        diff = "diff --git a/match/x.h b/match/x.h\n+++ b/match/x.h\n+  if (this == 0) return 0; // THISNULL: GAMEMD %s\n"

        def run(addr, row):
            ctx = types.SimpleNamespace(tree="t", base="b", man=[row] if row else [])
            with mock.patch.object(gates.L, "git", return_value=diff % addr), mock.patch.object(gates.L, "BINARY", BIN):
                return gates.thisnull(ctx)[0]
        good = {"addr": "0x459F40", "status": "matched", "pct": 100.0}
        self.assertEqual(run("0x459F40", good), "PASS")
        self.assertEqual(run("0x459F40", None), "FAIL")                                             # no manifest row
        self.assertEqual(run("0x459F40", dict(good, status="partial", pct=90.0)), "FAIL")           # not matched
        self.assertEqual(run("0x459F60", dict(good, addr="0x459F60")), "FAIL")                      # bytes do not test this


if __name__ == "__main__":
    unittest.main()
