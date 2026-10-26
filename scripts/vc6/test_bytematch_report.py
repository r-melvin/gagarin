#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: tests for the gagarin bytematch manifest/census report exporter.
"""Focused tests for bytematch_report's census and measure accounting."""

import tempfile
import unittest
from pathlib import Path
import sys

sys.path.insert(0, str(Path(__file__).resolve().parent))
import bytematch_report as report


class ByteMatchReportTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.root = Path(self.temp.name)
        (self.root / "match/core").mkdir(parents=True)
        (self.root / "match/core/sample.cpp").write_text("// fixture\n", encoding="utf-8")
        self.census = [
            ["0x401000", "0x10", "0", "none", "engine", []],
            ["0x401020", "0x20", "0", "none", "engine", []],
            ["0x401050", "0x30", "0", "none", "crt", []],
        ]
        self.manifest = [
            {"tu": "match/core/sample.cpp", "addr": "0x401000", "sym": "?Matched@@", "len": "0x10",
             "name": "Readable::Matched", "status": "matched", "pct": 100},
            {"tu": "match/core/sample.cpp", "addr": "0x401020", "sym": "?Partial@@", "len": "0x20",
             "name": "Readable::Partial", "status": "partial", "pct": 100},
        ]

    def tearDown(self):
        self.temp.cleanup()

    def test_totals_unclaimed_and_partial_100_are_not_byte_matches(self):
        result, context = report.build_report(self.manifest, self.census, self.root)
        m = result["measures"]
        self.assertEqual(result["version"], 2)
        self.assertEqual(m["total_functions"], 3)
        self.assertEqual(m["matched_functions"], 1)
        self.assertEqual(m["total_code"], 0x60)
        self.assertEqual(m["matched_code"], 0x10)
        self.assertEqual(m["fuzzy_match_percent"], 100 * 0x10 / 0x60)
        partial = result["units"][0]["functions"][1]
        self.assertEqual(partial["fuzzy_match_percent"], 0)
        self.assertTrue(all(u["metadata"]["complete"] is False for u in result["units"]))
        unknown = next(u for u in result["units"] if u["name"] == "unrecovered/crt")
        self.assertNotIn("source_path", unknown["metadata"])
        self.assertTrue(unknown["metadata"]["auto_generated"])
        self.assertEqual(context["unclaimed_function_count"], 1)
        self.assertEqual(result["units"][0]["functions"][0]["name"], "?Matched@@")
        self.assertEqual(result["units"][0]["functions"][0]["metadata"]["demangled_name"], "Readable::Matched")
        self.assertEqual(m["matched_data_percent"], 0)
        self.assertEqual(m["complete_data_percent"], 0)
        self.assertEqual(m["complete_code_percent"], 0)

    def test_manifest_length_override_is_explicit_and_used(self):
        manifest = [dict(self.manifest[0], **{"len": "0x18"})]
        result, context = report.build_report(manifest, self.census[:1], self.root)
        self.assertEqual(result["measures"]["total_code"], 0x18)
        self.assertEqual(context["census_code_bytes"], 0x10)
        self.assertEqual(context["effective_code_bytes"], 0x18)
        self.assertEqual(context["length_override_count"], 1)
        self.assertEqual(context["length_overrides"][0]["manifest_length"], 0x18)

    def test_source_path_rejects_parent_escape_and_missing_source(self):
        for path in ("../sample.cpp", "missing.cpp"):
            with self.subTest(path=path), self.assertRaises(ValueError):
                report.build_report([dict(self.manifest[0], tu=path)], self.census[:1], self.root)

    def test_duplicate_claims_and_census_addresses_rejected(self):
        with self.assertRaisesRegex(ValueError, "duplicate manifest"):
            report.build_report(self.manifest + [self.manifest[0]], self.census, self.root)
        with self.assertRaisesRegex(ValueError, "duplicate census"):
            report.build_report([], self.census + [self.census[0]], self.root)

    def test_unknown_status_and_out_of_census_claim_rejected(self):
        with self.assertRaisesRegex(ValueError, "unknown status"):
            report.build_report([dict(self.manifest[0], status="pending")], self.census, self.root)
        with self.assertRaisesRegex(ValueError, "outside census"):
            report.build_report([dict(self.manifest[0], addr="0x402000")], self.census, self.root)

    def test_empty_census_rejected(self):
        with self.assertRaisesRegex(ValueError, "census is empty"):
            report.build_report([], [], self.root)

    def test_source_symlink_cannot_escape_repository_root(self):
        outside = Path(self.temp.name).parent / (Path(self.temp.name).name + "-outside.cpp")
        outside.write_text("// outside\n", encoding="utf-8")
        try:
            (self.root / "match/core/escape.cpp").symlink_to(outside)
            with self.assertRaisesRegex(ValueError, "escapes repository root"):
                report.build_report([dict(self.manifest[0], tu="match/core/escape.cpp")], self.census[:1], self.root)
        finally:
            outside.unlink(missing_ok=True)


if __name__ == "__main__":
    unittest.main()
