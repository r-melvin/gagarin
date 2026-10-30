#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original synthetic COFF fixtures.
"""comdatize: an ml-shaped object gets a COMDAT ANY .text; everything else is untouched."""

import struct
import unittest

import coffgen
import comdatize


def ml_shaped_object(code=b"\x90\xc3"):
    """Header, one plain .text, one section symbol with aux, one external label."""
    text_flags = coffgen.SCN_CNT_CODE | coffgen.SCN_MEM_EXECUTE | coffgen.SCN_MEM_READ | coffgen.ALIGN[16]
    nsyms = 3
    raw = 20 + 40
    symptr = raw + len(code)
    head = struct.pack("<HHIIIHH", coffgen.I386, 1, 0, symptr, nsyms, 0, 0)
    sect = struct.pack("<8sIIIIIIHHI", b".text", 0, 0, len(code), raw, 0, 0, 0, 0, text_flags)
    sym_text = struct.pack("<8sIhHBB", b".text", 0, 1, 0, coffgen.CLASS_STATIC, 1)
    aux = struct.pack("<IHHIHBBBB", len(code), 0, 0, 0, 0, 0, 0, 0, 0)
    sym_label = struct.pack("<8sIhHBB", b"_label", 0, 1, 0x20, coffgen.CLASS_EXTERNAL, 0)
    return head + sect + code + sym_text + aux + sym_label + struct.pack("<I", 4)


class ComdatizeTests(unittest.TestCase):
    def test_marks_text_comdat_any(self):
        src = ml_shaped_object()
        out, count = comdatize.comdatize(src)
        self.assertEqual(count, 1)
        flags = struct.unpack_from("<I", out, 20 + 36)[0]
        self.assertTrue(flags & coffgen.SCN_LNK_COMDAT)
        symptr = struct.unpack_from("<I", out, 8)[0]
        self.assertEqual(out[symptr + 18 + 14], coffgen.COMDAT_ANY)
        self.assertEqual(len(out), len(src))
        diff = [i for i in range(len(src)) if src[i] != out[i]]
        self.assertEqual(set(diff), {20 + 36 + 1, symptr + 18 + 14})

    def test_idempotent(self):
        once, _ = comdatize.comdatize(ml_shaped_object())
        twice, count = comdatize.comdatize(once)
        self.assertEqual(count, 0)
        self.assertEqual(once, twice)

    def test_rejects_non_i386(self):
        with self.assertRaises(ValueError):
            comdatize.comdatize(b"\x64\x86" + bytes(40))


if __name__ == "__main__":
    unittest.main()
