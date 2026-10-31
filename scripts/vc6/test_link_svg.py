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
            self.assertEqual([m["state"] for m in s["milestones"]], ["done", "done", "done", "next", "todo", "todo"])
            self.assertNotIn("m2", s)
            self.assertNotIn("m3", s)
            svg = link_svg.render(s)
            self.assertEqual(svg, link_svg.render(json.loads(json.dumps(s))))
            self.assertTrue(svg.startswith("<svg ") and svg.endswith("</svg>\n"))
            self.assertIn("2 of 3 ordered entries", svg)
            self.assertIn("Unsigned image", svg)
            self.assertIn("entry point -16 bytes", svg)

    def test_filler_is_reported_apart_not_double_counted(self):
        with tempfile.TemporaryDirectory() as tmp:
            tmp = self.fixture(tmp)
            plan = json.loads((tmp / "m1/stubs/plan.json").read_text())
            # ?B is a matched slot of 0x8 whose COMDAT is shorter; the filler holds the rest of the slot.
            plan["placed"].append({"addr": "0x401044", "symbol": "?gap_00401040@@YAXXZ", "kind": "filler", "len": "0x4"})
            (tmp / "m1/stubs/plan.json").write_text(json.dumps(plan))
            (tmp / "m1/m1.map").write_text(MAP.replace(
                "\n entry point", " 0001:00000044       ?gap_00401040@@YAXXZ       00401044 f   stubs.obj\n\n entry point"))
            m1 = link_svg.refresh(tmp / "report.json", tmp / "m1")["m1"]
            self.assertEqual((m1["ordered_entries"], m1["ordered_bytes"]), (3, 0x48))
            self.assertEqual((m1["entries_at_retail_address"], m1["bytes_at_retail_address"]), (2, 0x18))
            self.assertEqual((m1["filler_entries"], m1["filler_bytes"], m1["filler_entries_at_retail_address"]), (1, 4, 1))
            self.assertEqual(m1["entries_by_kind"]["filler"]["bytes"], 4)
            self.assertEqual(m1["entries_by_kind"]["matched"]["entries"], 2)

    def test_m2_m3_sections(self):
        with tempfile.TemporaryDirectory() as tmp:
            tmp = self.fixture(tmp)
            (tmp / "pinned").mkdir()
            (tmp / "pinned/mapcheck.json").write_text(json.dumps({
                "drift_events": 0, "landmarks": {"entry point (WinMainCRTStartup)": {"delta": 0}}}))
            (tmp / "m2a.json").write_text(json.dumps({
                "matched_rows": 10, "identical": 9, "differ": 1, "differ_with_other_bytes": 1, "missing": []}))
            (tmp / "hy").mkdir()
            sec = {"diff_bytes": 0, "vsize": 16, "retail_vsize": 16}
            (tmp / "hy/compare.json").write_text(json.dumps({
                "identical": True, "sections": {".text": sec, ".data": dict(sec, diff_bytes=3)}}))
            (tmp / "m3").mkdir()
            (tmp / "m3/compare.json").write_text(json.dumps({
                "identical": True, "sections": {".text": sec, ".data": sec},
                "origins": {".text": {"vsize": 16, "file": 16, "project": 4, "library": 2, "retail": 10},
                            ".data": {"vsize": 16, "file": 8, "project": 8, "library": 0, "retail": 8}}}))
            s = link_svg.refresh(tmp / "report.json", tmp / "m1", tmp / "m2a.json", tmp / "pinned", tmp / "m3", tmp / "hy")
            self.assertEqual(s["m2"]["identical_in_place"], 9)
            self.assertEqual(s["m2"]["pinned_entry_point_delta"], 0)
            self.assertEqual(s["m2"]["hybrid_sections"][".data"]["diff_bytes"], 3)
            self.assertEqual(s["m3"]["total"], {"vsize": 32, "project": 12, "library": 2, "retail": 18, "diff_bytes": 0})
            svg = link_svg.render(s)
            self.assertIn("9 of 10 matched rows", svg)
            self.assertIn("1 of 2 equal retail", svg)
            self.assertIn("12 / 2 / 18", svg)
            self.assertIn("37.50% source", svg)
            # Omitted inputs keep the earlier figures.
            again = link_svg.refresh(tmp / "report.json", tmp / "m1", previous=s)
            self.assertEqual(again["m2"], s["m2"])
            self.assertEqual(again["m3"], s["m3"])


if __name__ == "__main__":
    unittest.main()
