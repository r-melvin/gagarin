#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original; synthetic PE fixtures contain no retail bytes.
"""The offline oracle must pin identity and refuse non-file-backed spans."""
import hashlib
import json
import os
from pathlib import Path
import struct
import tempfile
import unittest
from unittest.mock import patch

import diff_retail
import raw_match
import retail_image


def synthetic_pe(overlap=False, virtual_size=16):
    data = bytearray(0x204)
    data[:2] = b'MZ'
    struct.pack_into('<I', data, 0x3C, 0x80)
    data[0x80:0x84] = b'PE\0\0'
    struct.pack_into('<HH', data, 0x84, 0x14C, 2 if overlap else 1)
    struct.pack_into('<H', data, 0x94, 0xE0)
    struct.pack_into('<H', data, 0x98, 0x10B)
    struct.pack_into('<I', data, 0x98 + 28, 0x400000)
    for i in range(2 if overlap else 1):
        struct.pack_into('<8sIIII', data, 0x178 + 40 * i,
                         b'.text', virtual_size, 0x1000, 4, 0x200)
    data[0x200:] = b'ABCD'
    return bytes(data)


class PinnedImageTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        root = Path(self.temp.name)
        self.image = root / 'synthetic.exe'
        self.pin = root / 'totals.json'
        self.write_image(synthetic_pe())
        self.patches = [patch.dict(os.environ, {'GAMEMD_BINARY': str(self.image)}),
                        patch.object(retail_image, 'DEFAULT_TOTALS', self.pin)]
        for item in self.patches:
            item.start()

    def tearDown(self):
        for item in reversed(self.patches):
            item.stop()
        self.temp.cleanup()

    def write_image(self, data):
        self.image.write_bytes(data)
        self.pin.write_text(json.dumps({'_meta': {'sha256': hashlib.sha256(data).hexdigest()}}))

    def test_both_oracles_read_file_without_bridge(self):
        with patch.object(raw_match.subprocess, 'run') as bridge:
            self.assertEqual(raw_match.retail_bytes(0x401001, 2), b'BC')
            self.assertEqual(diff_retail.ghidra_bytes(0x401000, 4), b'ABCD')
            bridge.assert_not_called()

    def test_hash_mismatch_is_fatal_without_bridge_fallback(self):
        self.image.write_bytes(self.image.read_bytes()[:-1] + b'Z')
        with patch.object(raw_match.subprocess, 'run') as bridge:
            with self.assertRaisesRegex(ValueError, 'SHA-256 mismatch'):
                raw_match.retail_bytes(0x401000, 4)
            with self.assertRaisesRegex(SystemExit, 'SHA-256 mismatch'):
                diff_retail.ghidra_bytes(0x401000, 4)
            bridge.assert_not_called()

    def test_zero_fill_and_boundary_crossing_are_rejected(self):
        for address, length in [(0x401004, 1), (0x401003, 2), (0x400FFF, 2)]:
            with self.subTest(address=address, length=length):
                with self.assertRaisesRegex(ValueError, 'file-backed'):
                    retail_image.configured_span(address, length)

    def test_file_alignment_past_virtual_size_is_rejected(self):
        self.write_image(synthetic_pe(virtual_size=2))
        with self.assertRaisesRegex(ValueError, 'file-backed'):
            retail_image.configured_span(0x401000, 4)

    def test_overlapping_sections_are_ambiguous(self):
        self.write_image(synthetic_pe(overlap=True))
        with self.assertRaisesRegex(ValueError, 'found 2'):
            retail_image.configured_span(0x401000, 4)

    def test_nonpositive_length_is_rejected(self):
        for length in (0, -1):
            with self.assertRaisesRegex(ValueError, 'positive'):
                retail_image.configured_span(0x401000, length)

    def test_unconfigured_mode_preserves_legacy_reader(self):
        with patch.dict(os.environ, {}, clear=True):
            self.assertIsNone(retail_image.configured_span(0x401000, 4))


if __name__ == '__main__':
    unittest.main()
