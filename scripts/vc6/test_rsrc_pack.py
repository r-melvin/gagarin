#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original
"""Binary-free checks of the resource packer, the placeholder files and the .rc text helpers."""
import struct
import tempfile
import unittest
from pathlib import Path

import rsrc_decompile
import rsrc_pack


class ResTests(unittest.TestCase):
    def test_res_round_trip_orders_by_type_then_id(self):
        records = [(5, 9, 0x409, b"abc"), (3, 2, 0x409, b"x" * 5), (3, 1, 0x409, b"y")]
        back = rsrc_pack.read_res(rsrc_pack.write_res(records))
        self.assertEqual(back, sorted(records, key=lambda r: r[:2]))

    def test_section_layout(self):
        data, fields = rsrc_pack.rsrc_section([(3, 1, 0x409, b"abcde"), (5, 7, 0x409, b"zz"), (3, 2, 0x409, b"q")])
        # root (2 types), two type dirs (2 + 1 names), three name dirs, three entries, data 4-aligned
        self.assertEqual(struct.unpack_from("<HH", data, 12), (0, 2))
        self.assertEqual(len(fields), 3)
        offsets = [struct.unpack_from("<I", data, f)[0] for f in fields]
        self.assertEqual([o % 4 for o in offsets], [0, 0, 0])
        self.assertEqual(offsets[1] - offsets[0], 8)          # five bytes pad to eight
        self.assertEqual(data[offsets[0]:offsets[0] + 5], b"abcde")
        self.assertEqual(len(data), offsets[2] + 4)

    def test_object_has_one_relocation_per_entry(self):
        with tempfile.TemporaryDirectory() as work:
            obj = rsrc_pack.rsrc_object([(3, 1, 0x409, b"abcd"), (3, 2, 0x409, b"efgh")], Path(work) / "r.obj")
            raw = obj.read_bytes()
            self.assertEqual(struct.unpack_from("<HH", raw, 0), (0x14C, 1))
            self.assertEqual(struct.unpack_from("<H", raw, 20 + 32)[0], 2)


class BlankImageTests(unittest.TestCase):
    def test_blank_dib_sizes_match_the_formula(self):
        for w, h, bpp in [(16, 16, 4), (48, 48, 8), (32, 32, 32), (24, 24, 4)]:
            self.assertEqual(len(rsrc_pack.blank_dib(w, h, bpp)), rsrc_pack.dib_size(w, h, bpp))

    def test_blank_png_is_padded_to_the_exact_size(self):
        png = rsrc_pack.blank_png(256, 256, 24160)
        self.assertEqual(len(png), 24160)
        self.assertTrue(png.startswith(b"\x89PNG\r\n\x1a\n"))
        self.assertTrue(png.endswith(b"IEND\xaeB`\x82"))


class RepositoryPlaceholderTests(unittest.TestCase):
    def test_every_group_in_the_manifest_has_matching_placeholder_files(self):
        rows = rsrc_pack.manifest()
        self.assertTrue(rows)
        records = rsrc_pack.art_records()
        images = [r for r in records if r[0] in (rsrc_pack.RT_ICON, rsrc_pack.RT_CURSOR)]
        self.assertEqual(len(images), sum(len(ids) for _, _, _, ids in rows))
        self.assertEqual(len({(t, n) for t, n, _, _ in images}), len(images))   # no id used twice

    def test_placeholders_hold_no_pixels(self):
        for kind, _, fname, _ in rsrc_pack.manifest():
            _, images = rsrc_pack.read_ico(rsrc_pack.RSRC / fname)
            for w, h, cc, planes, bpp, data in images:
                if data.startswith(b"\x89PNG"):
                    continue
                size = struct.unpack_from("<I", data, 0)[0]
                pal = 4 << bpp if bpp <= 8 else 0
                xor = (w * bpp + 31) // 32 * 4 * h
                self.assertEqual(size, 40)
                self.assertFalse(any(data[40:40 + pal + xor]), fname)


class RcTextTests(unittest.TestCase):
    def test_string_escapes(self):
        self.assertEqual(rsrc_decompile.esc('a"b\\c\xa9\n'), '"a""b\\\\c\\251\\n"')

    def test_keyword_statement_when_defaults_fit(self):
        item = {"class": 130, "title": "t", "style": 0x50020000, "exstyle": 0, "help": 0, "id": -1,
                "x": 1, "y": 2, "cx": 3, "cy": 4}
        self.assertEqual(rsrc_decompile.control_line(item), 'LTEXT         "t", IDC_STATIC, 1, 2, 3, 4')

    def test_control_statement_otherwise(self):
        item = {"class": "msctls_trackbar32", "title": "s", "style": 0x50010008, "exstyle": 0, "help": 0, "id": 5,
                "x": 1, "y": 2, "cx": 3, "cy": 4}
        self.assertEqual(rsrc_decompile.control_line(item),
                         'CONTROL       "s", 5, "msctls_trackbar32", TBS_BOTH | WS_TABSTOP, 1, 2, 3, 4')


if __name__ == "__main__":
    unittest.main()
