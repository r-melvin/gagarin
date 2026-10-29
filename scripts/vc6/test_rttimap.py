#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original synthetic image; no retail bytes.
"""rttimap: compiled RTTI symbol names to retail addresses."""

import struct
import unittest

import rttimap

BASE = 0x800000


class Image:
    """Just enough of hybrid.Retail: fill(va, n) over one flat buffer at BASE."""

    def __init__(self):
        self.buf = bytearray(0x400)

    def put(self, va, *dwords):
        struct.pack_into("<%dI" % len(dwords), self.buf, va - BASE, *dwords)

    def string(self, va, text):
        self.buf[va - BASE:va - BASE + len(text) + 1] = text.encode() + b"\0"

    def search(self, body):
        found, at = [], self.buf.find(body)
        while at >= 0:
            found.append(BASE + at)
            at = self.buf.find(body, at + 1)
        return found

    def fill(self, va, n):
        return bytes(self.buf[va - BASE:va - BASE + n])


def image():
    """Derived (single inheritance from Base) and Twin (two bases: Base at 0, Other at 8), with their vtables."""
    im = Image()
    TD = {"Base": BASE + 0x00, "Derived": BASE + 0x20, "Other": BASE + 0x40}
    im.string(TD["Base"] + 8, ".?AVBase@@")
    im.string(TD["Derived"] + 8, ".?AVDerived@@")
    im.string(TD["Other"] + 8, ".?AVOther@@")
    # base class descriptors: td, contained, mdisp, pdisp, vdisp, attrs, chd
    bcd = {"Derived": BASE + 0x60, "Base": BASE + 0x80, "OtherAt8": BASE + 0xA0}
    im.put(bcd["Derived"], TD["Derived"], 1, 0, 0xFFFFFFFF, 0, 0, BASE + 0x100)
    im.put(bcd["Base"], TD["Base"], 0, 0, 0xFFFFFFFF, 0, 0, BASE + 0x120)
    im.put(bcd["OtherAt8"], TD["Other"], 0, 8, 0xFFFFFFFF, 0, 0, BASE + 0x140)
    # Derived: chd -> array [Derived, Base]
    im.put(BASE + 0x100, 0, 0, 2, BASE + 0x1C0)
    im.put(BASE + 0x1C0, bcd["Derived"], bcd["Base"])
    # Twin is not a class here; Derived has a second locator for the Other subobject at 8, same chd
    im.put(BASE + 0x200, 0, 0, 0, TD["Derived"], BASE + 0x100)   # COL 1: offset 0
    im.put(BASE + 0x220, 0, 8, 0, TD["Derived"], BASE + 0x100)   # COL 2: offset 8
    # vtables: COL slot then entries
    im.put(BASE + 0x300, BASE + 0x200, 0x401000)
    im.put(BASE + 0x310, BASE + 0x220, 0x401010)
    return im


CLASSES = {".?AVDerived@@": {
    "type_descriptor_va": "0x%X" % (BASE + 0x20),
    "locators": [{"locator_va": "0x%X" % (BASE + 0x200), "base_offset": 0, "cd_offset": 0,
                  "class_hierarchy_va": "0x%X" % (BASE + 0x100)},
                 {"locator_va": "0x%X" % (BASE + 0x220), "base_offset": 8, "cd_offset": 0,
                  "class_hierarchy_va": "0x%X" % (BASE + 0x100)}]}}


class EncodeTest(unittest.TestCase):
    def test_numbers(self):
        self.assertEqual(rttimap.encode_number(0), "A@")
        self.assertEqual(rttimap.encode_number(-1), "?0")
        self.assertEqual(rttimap.encode_number(8), "7")
        self.assertEqual(rttimap.encode_number(11), "L@")
        self.assertEqual(rttimap.encode_number(0x1234), "BCDE@")
        self.assertEqual(rttimap.signed(0xFFFFFFFF), -1)

    def test_type_descriptor_name(self):
        self.assertEqual(rttimap.type_descriptor_name(".?AVPixelFXClass@@"), "??_R0?AVPixelFXClass@@@8")
        self.assertEqual(rttimap.core(".?AUINIEntry@INIClass@@"), "INIEntry@INIClass@@")


class NamesTest(unittest.TestCase):
    def names(self, vtables=None):
        return rttimap.RttiNames(image(), CLASSES, vtables)

    def test_pieces(self):
        n = self.names().names
        self.assertEqual(n["??_R0?AVDerived@@@8"], BASE + 0x20)
        self.assertEqual(n["??_R3Derived@@8"], BASE + 0x100)
        self.assertEqual(n["??_R2Derived@@8"], BASE + 0x1C0)
        self.assertEqual(n["??_R1A@?0A@A@Derived@@8"], BASE + 0x60)
        self.assertEqual(n["??_R1A@?0A@A@Base@@8"], BASE + 0x80)
        self.assertEqual(n["??_R4Derived@@6B@"], BASE + 0x200)
        self.assertEqual(len(n), 6)

    def test_locator_follows_the_vtable(self):
        r = self.names({"??_7Derived@@6B@": BASE + 0x304, "??_7Derived@@6BOther@@@": BASE + 0x314})
        self.assertEqual(r.address("??_R4Derived@@6B@"), BASE + 0x200)
        self.assertEqual(r.address("??_R4Derived@@6BOther@@@"), BASE + 0x220)

    def test_locator_without_a_known_vtable_is_unknown_unless_primary(self):
        r = self.names()
        self.assertIsNone(r.address("??_R4Derived@@6BOther@@@"))

    def test_vtable_slot_that_is_not_a_locator_is_refused(self):
        r = self.names({"??_7Derived@@6BOther@@@": BASE + 0x308})   # slot before it holds 0x401000
        self.assertIsNone(r.address("??_R4Derived@@6BOther@@@"))

    def test_other_symbols_and_unknown_classes(self):
        r = self.names()
        self.assertIsNone(r.address("??_7Derived@@6B@"))
        self.assertIsNone(r.address("??_R0?AVMissing@@@8"))
        self.assertNotIn("??_R2Missing@@8", r)
        self.assertEqual(r["??_R3Derived@@8"], BASE + 0x100)
        with self.assertRaises(KeyError):
            r["??_R3Missing@@8"]

    def test_bare_type_descriptor_found_by_its_name(self):
        im = image()
        im.string(BASE + 0x2A8, ".?AUIThing@@")   # a descriptor at BASE+0x2A0: vtable ptr, spare, name
        im.put(BASE + 0x2A0, 0x7F0000, 0)
        r = rttimap.RttiNames(im, CLASSES, bare=[".?AUIThing@@", ".?AUAbsent@@"])
        self.assertEqual(r.address("??_R0?AUIThing@@@8"), BASE + 0x2A0)
        self.assertIsNone(r.address("??_R0?AUAbsent@@@8"))

    def test_conflicting_claims_are_dropped(self):
        r = self.names()
        r._add("??_R0?AVDerived@@@8", BASE + 0x40)
        self.assertIn("??_R0?AVDerived@@@8", r.ambiguous)
        self.assertIsNone(r.address("??_R0?AVDerived@@@8"))
        r._add("??_R0?AVDerived@@@8", BASE + 0x20)   # stays dropped
        self.assertIsNone(r.address("??_R0?AVDerived@@@8"))


if __name__ == "__main__":
    unittest.main()
