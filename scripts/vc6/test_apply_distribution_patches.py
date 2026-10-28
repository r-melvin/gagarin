#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original project tooling.
"""Tests for the post-link distribution-patch step (no compiler, no retail image)."""
import unittest

import apply_distribution_patches as adp


class StandInSourceTest(unittest.TestCase):
    def patch(self, addr, sig, body):
        return {"addr": addr, "patch_len": 3, "stand_in": {"convention": "__stdcall", "signature": sig, "body": body}}

    def test_names_each_stand_in_by_address(self):
        src = adp.stand_in_source([self.patch("0x49F5C0", "bool __stdcall f()", "return true;")])
        self.assertIn('extern "C" bool __stdcall gg_patch_0049F5C0() { return true; }', src)

    def test_declares_msg_for_message_handlers(self):
        src = adp.stand_in_source([self.patch("0x49F740", "void __fastcall f(MSG*)", "{}")])
        self.assertIn("typedef struct tagMSG MSG;", src)
        self.assertIn("gg_patch_0049F740(MSG*)", src)

    def test_rejects_signature_without_placeholder_name(self):
        with self.assertRaises(SystemExit):
            adp.stand_in_source([self.patch("0x1", "bool __stdcall g()", "return true;")])


if __name__ == "__main__":
    unittest.main()
