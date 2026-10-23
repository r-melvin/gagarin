#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original synthetic instruction fixtures; reads only tracked data.
"""extent_census: CFG walk on synthetic code, and consistency of the tracked extent table."""

import json
from pathlib import Path
import shutil
import unittest

import extent_census

BASE = 0x401000
CODE = bytes.fromhex(
    "85c0"              # 401000 test eax,eax
    "7403"              # 401002 je 401007
    "33c0"              # 401004 xor eax,eax
    "c3"                # 401006 ret
    "ff2485101040 00"   # 401007 jmp [eax*4+0x401010]
    "9090"              # 40100e
    "18104000 1a104000"  # 401010 jump table -> 401018, 40101a
    "c3cc"              # 401018 ret; int3
    "b001c3"            # 40101a mov al,1; ret
    "909090"            # 40101d padding
    "750e"              # 401020 jne 401030 (another entry: tail call)
    "c3"                # 401022 ret
    + "90" * 13 +       # 401023
    "c3"                # 401030 ret
    .replace(" ", ""))


class FakeImage:
    def read(self, va, n):
        return CODE[va - BASE:va - BASE + n]


@unittest.skipUnless(shutil.which("objdump"), "objdump not installed")
class WalkTests(unittest.TestCase):
    def test_jump_table_targets_and_table_extend_the_span(self):
        length, flags = extent_census.walk(FakeImage(), BASE, 0x401020, frozenset({BASE, 0x401020, 0x401030}))
        self.assertEqual(length, 0x1D)
        self.assertEqual(flags, {"table"})

    def test_branch_to_another_entry_is_a_tail_call(self):
        length, _ = extent_census.walk(FakeImage(), 0x401020, 0x401031, frozenset({0x401020, 0x401030}))
        self.assertEqual(length, 3)

    def test_without_the_entry_the_branch_is_followed(self):
        length, _ = extent_census.walk(FakeImage(), 0x401020, 0x401031, frozenset({0x401020}))
        self.assertEqual(length, 0x11)


class HelperTests(unittest.TestCase):
    def test_gap_kind(self):
        self.assertEqual(extent_census.gap_kind(b""), "none")
        self.assertEqual(extent_census.gap_kind(b"\x90\x90"), "nop")
        self.assertEqual(extent_census.gap_kind(b"\xcc"), "cc")
        self.assertEqual(extent_census.gap_kind(b"\x90\xcc"), "mixed")

    def test_kind_of(self):
        self.assertEqual(extent_census.kind_of(0x401000), "engine")
        self.assertEqual(extent_census.kind_of(0x55BC00), "lzo")
        self.assertEqual(extent_census.kind_of(0x7C8962), "thunk")
        self.assertEqual(extent_census.kind_of(0x7CD80F), "crt")
        self.assertEqual(extent_census.kind_of(0x7DC720), "comsupp")


class TableTests(unittest.TestCase):
    """The tracked table tiles .text: every entry ends where the next begins."""

    @classmethod
    def setUpClass(cls):
        path = extent_census.DATA / "function_extents.json"
        if not path.is_file():
            raise unittest.SkipTest("function_extents.json not generated")
        cls.doc = json.loads(path.read_text())

    def test_entries_tile_without_overlap(self):
        entries = self.doc["entries"]
        addrs = [int(e[0], 16) for e in entries]
        self.assertEqual(addrs, sorted(set(addrs)))
        for e, nxt in zip(entries, addrs[1:]):
            self.assertEqual(int(e[0], 16) + int(e[1], 16) + int(e[2], 16), nxt, e[0])
        self.assertEqual(self.doc["binary_sha256"], extent_census.SHA256)

    def test_every_manifest_row_is_an_entry(self):
        addrs = {int(e[0], 16) for e in self.doc["entries"]}
        manifest = json.loads((extent_census.DATA / "match_manifest.json").read_text())
        missing = [r["addr"] for r in manifest if int(r["addr"], 16) not in addrs]
        self.assertEqual(missing, [])


if __name__ == "__main__":
    unittest.main()
