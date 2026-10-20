#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original
"""Synthetic COFF regressions; no retail or compiler-produced bytes required."""
import struct
import tempfile
import unittest
from pathlib import Path

from raw_match import obj_func_bytes


def symbol(section, value=0, aux=0):
    return struct.pack('<8sIhHBB', b'target', value, section, 0x20, 2, aux)


def coff(symbols):
    # A four-byte function starts at .text+1. Its sole relocation starts there.
    body = b'_CODE_'
    raw = 20 + 40
    reloc = raw + len(body)
    table = reloc + 10
    header = struct.pack('<HHIIIHH', 0x14C, 1, 0, table, len(symbols), 0, 0)
    section = struct.pack('<8sIIIIIIHHI', b'.text', 0, 0, len(body), raw,
                          reloc, 0, 1, 0, 0x20)
    fixup = struct.pack('<IIH', 1, 0, 6)
    return header + section + body + fixup + b''.join(symbols) + struct.pack('<I', 4)


class CoffDefinedSymbolTests(unittest.TestCase):
    def lookup(self, records):
        with tempfile.TemporaryDirectory() as work:
            path = Path(work) / 'synthetic.obj'
            path.write_bytes(coff(records))
            return obj_func_bytes(path, 'target', 4)

    def test_definition_after_undefined_declaration(self):
        self.assertEqual(self.lookup([symbol(0), symbol(1, 1)]), (b'CODE', {0}))

    def test_undefined_only_has_no_body(self):
        self.assertEqual(self.lookup([symbol(0), symbol(0)]), (None, set()))

    def test_non_section_symbols_are_skipped(self):
        self.assertEqual(self.lookup([symbol(-1), symbol(-2), symbol(1, 1)]),
                         (b'CODE', {0}))

    def test_auxiliary_payload_is_not_a_definition(self):
        # Deliberately make auxiliary bytes resemble a defined target symbol.
        self.assertEqual(self.lookup([symbol(0, aux=1), symbol(1, 0), symbol(1, 1)]),
                         (b'CODE', {0}))


if __name__ == '__main__':
    unittest.main()
