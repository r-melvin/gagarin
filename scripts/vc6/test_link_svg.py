#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original synthetic link-report fixtures.
"""link_svg: refresh from link tool output and deterministic rendering."""

import json
import os
from pathlib import Path
import sys
import tempfile
import unittest

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "orchestration"))
import link_svg  # noqa: E402

MAP = """ m1

  Address         Publics by Value              Rva+Base     Lib:Object

 0001:00000000       ?A@@YAXXZ                  00401000 f   a.obj
 0001:00000010       ?stub_00401010@@YAXXZ      00401014 f i stubs.obj
 0001:00000040       ?B@@YAXXZ                  00401040 f   b.obj

 entry point at        0001:00000000
"""


class LinkSvgTest(unittest.TestCase):
    def fixture(self, tmp):
        tmp = Path(tmp)
        (tmp / "m1/stubs").mkdir(parents=True)
        (tmp / "report.json").write_text(json.dumps({
            "unresolved_total": 7, "counts": {"function": 4, "data": 3}, "duplicate_definitions": 0, "objects": 2}))
        (tmp / "m1/link_report.json").write_text(json.dumps({
            "link_exit_code": 0, "unresolved_after_stubs": 0, "duplicates": [], "stubs_placed": 1}))
        (tmp / "m1/mapcheck.json").write_text(json.dumps({
            "matched_functions": 2, "matched_at_retail_address": 2, "ordered_entries": 3, "drift_events": 2,
            "landmarks": {"entry point (WinMainCRTStartup)": {"delta": -16}}}))
        (tmp / "m1/stubs/plan.json").write_text(json.dumps({"placed": [
            {"addr": "0x401000", "symbol": "?A@@YAXXZ", "kind": "matched", "len": "0x10"},
            {"addr": "0x401010", "symbol": "?stub_00401010@@YAXXZ", "kind": "stub", "len": "0x30"},
            {"addr": "0x401040", "symbol": "?B@@YAXXZ", "kind": "matched", "len": "0x8"}]}))
        (tmp / "m1/m1.map").write_text(MAP)
        return tmp

    def test_refresh_and_render(self):
        with tempfile.TemporaryDirectory() as tmp:
            tmp = self.fixture(tmp)
            s = link_svg.refresh(tmp / "report.json", tmp / "m1")
            self.assertEqual(s["m0"]["unresolved"], 7)
            self.assertEqual(s["m1"]["unresolved_after_stubs"], 0)
            self.assertEqual(s["m1"]["entries_at_retail_address"], 2)
            self.assertEqual(s["m1"]["bytes_at_retail_address"], 0x18)
            self.assertEqual(s["m1"]["ordered_bytes"], 0x48)
            self.assertEqual([m["state"] for m in s["milestones"]], ["done", "done", "next", "todo", "todo", "todo"])
            svg = link_svg.render(s)
            self.assertEqual(svg, link_svg.render(json.loads(json.dumps(s))))
            self.assertTrue(svg.startswith("<svg ") and svg.endswith("</svg>\n"))
            self.assertIn("2 of 3 ordered entries", svg)
            self.assertIn("Unsigned image", svg)


if __name__ == "__main__":
    unittest.main()
