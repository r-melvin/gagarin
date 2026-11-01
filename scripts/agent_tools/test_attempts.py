#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original; temporary ledgers only.
"""Tests for the attempts.py refusal rules: python3 -m unittest test_attempts"""
import contextlib
import io
import os
import sys
import tempfile
import unittest
from pathlib import Path

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import attempts as A  # noqa: E402


class Refusal(unittest.TestCase):
    def setUp(self):
        self.d = tempfile.TemporaryDirectory()
        self.led = Path(self.d.name) / "a.jsonl"
        self.src = Path(self.d.name) / "x.cpp"

    def tearDown(self):
        self.d.cleanup()

    def run_cli(self, *argv):
        out = io.StringIO()
        with contextlib.redirect_stdout(out):
            rc = A.main(["--ledger", str(self.led), *argv])
        return rc, out.getvalue()

    def add(self, raw, text, addr="0x401000", *extra):
        self.src.write_text(text)
        return self.run_cli("add", addr, "--tu", "match/x.cpp", "--variant", "v" + text, "--raw", str(raw),
                            "--src", str(self.src), *extra)

    def test_identical_source_refused(self):
        self.assertEqual(self.add(50, "a")[0], 0)
        rc, out = self.add(60, "a")
        self.assertEqual(rc, 3)
        self.assertIn("byte-identical", out)
        self.assertIn("defer instead", out)
        self.assertEqual(len(A.load(self.led)), 1)        # nothing recorded for the refusal

    def test_cap_of_twelve(self):
        for i in range(12):
            self.assertEqual(self.add(10 + i, "s%d" % i)[0], 0)      # always a new best
        rc, out = self.add(99, "s99")
        self.assertEqual(rc, 3)
        self.assertIn("cap 12", out)

    def test_patience_four_without_new_best(self):
        self.assertEqual(self.add(80, "a")[0], 0)
        for i in range(4):
            self.assertEqual(self.add(70, "b%d" % i)[0], 0)
        rc, out = self.add(75, "c")
        self.assertEqual(rc, 3)
        self.assertIn("without a new best", out)

    def test_new_best_resets_patience(self):
        self.add(80, "a")
        for i in range(3):
            self.add(70, "b%d" % i)
        self.assertEqual(self.add(90, "best")[0], 0)
        self.assertEqual(self.add(70, "d")[0], 0)

    def test_imported_rows_do_not_count_as_attempts(self):
        A.append(self.led, [dict(addr="0x401000", raw=95.0, status="imported, unverified", date=None,
                                 variant="imp", source_sha=None)])
        for i in range(3):
            self.assertEqual(self.add(60 + i, "s%d" % i)[0], 0)      # below the imported best, but only 3 in a row

    def test_defer_is_a_valid_outcome_and_closes_the_address(self):
        self.add(50, "a")
        rc, out = self.run_cli("defer", "0x401000", "--reason", "needs a type from the next TU")
        self.assertEqual(rc, 0)
        self.assertIn("deferred", out)
        rc, out = self.add(60, "b")
        self.assertEqual(rc, 3)
        self.assertIn("deferred", out)
        self.assertEqual(self.add(60, "b", "0x401000", "--reopen")[0], 0)

    def test_force_skips_rules(self):
        self.add(50, "a")
        self.assertEqual(self.add(50, "a", "0x401000", "--force")[0], 0)

    def test_check_command(self):
        self.add(50, "a")
        self.src.write_text("a")
        rc, out = self.run_cli("check", "0x401000", "--src", str(self.src))
        self.assertEqual(rc, 3)
        rc, out = self.run_cli("check", "0x402000")
        self.assertEqual((rc, out.strip()), (0, "ok 0x402000"))

    def test_addresses_are_independent(self):
        self.add(50, "a", "0x401000")
        self.assertEqual(self.add(50, "a", "0x402000")[0], 0)

    def test_tried_addrs_counts_defers(self):
        self.add(50, "a")
        self.run_cli("defer", "0x402000", "--reason", "x")
        self.assertEqual(A.tried_addrs(A.load(self.led)), {0x401000, 0x402000})

    def test_best_ignores_defer_rows(self):
        self.add(50, "a")
        self.run_cli("defer", "0x401000", "--reason", "x")
        self.assertEqual(A.best(A.load(self.led), "0x401000")["raw"], 50)


if __name__ == "__main__":
    unittest.main()
