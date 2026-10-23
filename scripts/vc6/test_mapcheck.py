#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original synthetic linker-map fixtures.
"""mapcheck: map parsing, per-function address check and drift attribution."""

import json
from pathlib import Path
import tempfile
import unittest

import mapcheck

MAP = """ m1

 Preferred load address is 00400000

 Start         Length     Name                   Class
 0001:00000000 00001000H .text                   CODE

  Address         Publics by Value              Rva+Base     Lib:Object

 0001:00000000       ?A@@YAXXZ                  00401000 f   a.obj
 0001:00000010       ?stub_00401010@@YAXXZ      00401010 f i stubs.obj
 0001:00000040       ?B@@YAXXZ                  00401040 f   b.obj
 0001:00000050       ?C@@YAXXZ                  00401050 f   b.obj
 0001:00000060       _htonl@4                   00401060 f   WSOCK32:WSOCK32.dll
 0001:00000066       _GetVersion@0              00401066 f   KERNEL32:KERNEL32.dll
 0001:00000070       _WinMainCRTStartup         00401070 f   LIBCMT:wincrt0.obj

 entry point at        0001:00000070
"""

PLAN = {"placed": [{"addr": "0x401000", "symbol": "?A@@YAXXZ", "kind": "matched"},
                   {"addr": "0x401010", "symbol": "?stub_00401010@@YAXXZ", "kind": "stub"},
                   {"addr": "0x401030", "symbol": "?B@@YAXXZ", "kind": "matched"},
                   {"addr": "0x401040", "symbol": "?C@@YAXXZ", "kind": "matched"}]}


class MapcheckTests(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        root = Path(self.tmp.name)
        (root / "m.map").write_text(MAP)
        (root / "plan.json").write_text(json.dumps(PLAN))
        self.c = mapcheck.check(root / "m.map", root / "plan.json")

    def tearDown(self):
        self.tmp.cleanup()

    def test_parse_map(self):
        publics, sections = mapcheck.parse_map(MAP)
        self.assertEqual(publics["?B@@YAXXZ"], 0x401040)
        self.assertEqual(sections[0][3], ".text")

    def test_addresses_and_drift_source(self):
        self.assertEqual(self.c["matched_functions"], 3)
        self.assertEqual(self.c["matched_at_retail_address"], 1)
        self.assertEqual(self.c["first_divergence"]["symbol"], "?B@@YAXXZ")
        self.assertEqual(self.c["drift_events"], 1)
        event = self.c["events"][0]
        self.assertEqual((event["source_kind"], event["change"], event["linked_slot"], event["retail_slot"]),
                         ("stub", 0x10, 0x30, 0x20))
        self.assertEqual(self.c["matched_delta_histogram_top"][0], ["+0x10", 2])

    def test_landmarks(self):
        lm = self.c["landmarks"]
        self.assertEqual(lm["first import thunk block"]["linked"], "0x401060")
        self.assertEqual(lm["second import thunk block (KERNEL32)"]["linked"], "0x401066")
        self.assertEqual(lm["entry point (WinMainCRTStartup)"]["linked"], "0x401070")
        self.assertEqual(lm["import thunks linked"], 2)


if __name__ == "__main__":
    unittest.main()
