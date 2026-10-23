#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original synthetic COFF fixtures.
"""crt_flag_check: .drectve-only and $L-numbering differences are neutral; byte changes are not."""

import json
from pathlib import Path
import struct
import tempfile
import unittest

import crt_flag_check


def obj(fill=0xCC, label="$L100", drectve=b"-defaultlib:LIBC "):
    """Hand-built COFF: .drectve, a code section defining ?F and the static
    label, and a data table relocated against the label (a jump table)."""
    code = bytes([fill]) * 8
    table = bytes(4)
    sections = [(".drectve", 0x00100A00, drectve, b""),
                (".text", 0x60501020, code, b""),
                (".rdata", 0x40300040, table, struct.pack("<IIH", 0, 3, 6))]
    ptr = 20 + 40 * len(sections)
    headers, body = b"", b""
    for name, flags, data, rel in sections:
        headers += name.encode().ljust(8, b"\0") + struct.pack(
            "<IIIIIIHHI", 0, 0, len(data), ptr, ptr + len(data) if rel else 0, 0, len(rel) // 10, 0, flags)
        body += data + rel
        ptr += len(data) + len(rel)
    strtab = b"?F@@YAXXZ\0"
    symbols = (struct.pack("<II", 0, 4) + struct.pack("<IhHBB", 0, 2, 0x20, 2, 0)          # 0: ?F (long name)
               + struct.pack("<8sIhHBB", b".file", 0, -2, 0, 103, 0)                       # 1: .file
               + struct.pack("<8sIhHBB", b".text", 0, 2, 0, 3, 0)                          # 2: section
               + struct.pack("<8sIhHBB", label.encode(), 4, 2, 0, 6, 0))                   # 3: $L label
    head = struct.pack("<HHIIIHH", 0x14C, len(sections), 0, ptr, 4, 0, 0)
    return head + headers + body + symbols + struct.pack("<I", 4 + len(strtab)) + strtab


class CrtFlagTests(unittest.TestCase):
    def run_pair(self, a, b):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            for name, data in (("base", a), ("other", b)):
                (root / name / "match").mkdir(parents=True)
                (root / name / "match/x.obj").write_bytes(data)
                (root / name / "objects.json").write_text(json.dumps({"objects": [{"object": "match/x.obj"}]}))
            manifest = [{"addr": "0x401000", "sym": "?F@@YAXXZ", "status": "matched"}]
            return crt_flag_check.run(root / "base", root / "other", manifest)

    def test_drectve_and_label_numbering_are_neutral(self):
        r = self.run_pair(obj(), obj(label="$L999", drectve=b"-defaultlib:LIBCMT "))
        self.assertEqual(r["identical_except_drectve"], 1)
        self.assertEqual(r["drectve_changed"], 1)
        self.assertEqual(r["affected_rows"], [])

    def test_code_difference_is_reported_against_the_row(self):
        r = self.run_pair(obj(), obj(fill=0x90))
        self.assertEqual(len(r["differing_objects"]), 1)
        self.assertEqual(r["affected_rows"][0]["addr"], "0x401000")
        self.assertEqual(r["affected_by_status"], {"matched": 1})


if __name__ == "__main__":
    unittest.main()
