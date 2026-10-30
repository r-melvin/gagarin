#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original synthetic COFF fixtures.
"""check_asm_text: .text extraction from a COFF object."""

import struct
import unittest

import check_asm_text


class TextBytesTests(unittest.TestCase):
    def test_picks_text_section(self):
        code = b"\x90\xc3"
        head = struct.pack("<HHIIIHH", 0x14C, 2, 0, 0, 0, 0, 0)
        data_sec = struct.pack("<8sIIIIIIHHI", b".data", 0, 0, 1, 20 + 80 + 2, 0, 0, 0, 0, 0)
        text_sec = struct.pack("<8sIIIIIIHHI", b".text", 0, 0, 2, 20 + 80, 0, 0, 0, 0, 0)
        obj = head + data_sec + text_sec + code + b"\x01"
        self.assertEqual(check_asm_text.text_bytes(obj), code)

    def test_missing_text(self):
        head = struct.pack("<HHIIIHH", 0x14C, 0, 0, 0, 0, 0, 0)
        with self.assertRaises(ValueError):
            check_asm_text.text_bytes(head)


if __name__ == "__main__":
    unittest.main()
