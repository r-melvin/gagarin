# SPDX-License-Identifier: GPL-3.0-or-later
"""gen_trig_tables.py: mathematical sanity only; the bit-exact comparison needs the image (gen_trig_tables.py --check)."""
import struct
import unittest

import gen_trig_tables as g


def as_float(bits):
    return struct.unpack("<f", struct.pack("<I", bits))[0]


class TrigTableTests(unittest.TestCase):
    def test_lengths(self):
        self.assertEqual([len(t[4]()) for t in g.TABLES], [10241, 4097, 4097, 4097, 16384])

    def test_truncation_goes_toward_zero(self):
        self.assertEqual(g.f32_bits(1.0 - 2.0 ** -40), 0x3F7FFFFF)
        self.assertEqual(g.f32_bits(-(1.0 - 2.0 ** -40)), 0xBF7FFFFF)
        self.assertEqual(g.f32_bits(0.1), 0x3DCCCCCC)

    def test_sin_and_asin_landmarks(self):
        sin = g.sin_table()
        self.assertEqual(sin[0], 0)
        self.assertEqual(sin[2048], 0x3F800000)
        self.assertEqual(sin[8192 + 2048], 0x3F800000)
        asin = g.asin_table()
        self.assertEqual(asin[2048], 0)
        self.assertAlmostEqual(as_float(asin[4096]), 1.5707963, places=6)

    def test_x87_pi_shows_in_sin_of_pi(self):
        self.assertAlmostEqual(as_float(g.sin_table()[4096]) * 1e16, 1.2246064, places=6)

    def test_sqrt_mantissas(self):
        sqrt = g.sqrt_table()
        self.assertEqual((sqrt[0], sqrt[8192]), (0, 0x3504F3))
        self.assertTrue(all(a < b for a, b in zip(sqrt, sqrt[1:])))

    def test_render_annotates_every_table(self):
        text = g.render()
        for _, va, _, _, _ in g.TABLES:
            self.assertIn(f"// GLOBAL: GAMEMD 0x{va:X}", text)


if __name__ == "__main__":
    unittest.main()
