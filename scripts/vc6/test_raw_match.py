#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original
"""Synthetic COFF regressions; no retail or compiler-produced bytes required."""
import struct
import tempfile
import unittest
import contextlib
import io
from unittest.mock import patch
from pathlib import Path

from raw_match import main, obj_func_bytes


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
    def lookup(self, records, length=4, mutate=None):
        with tempfile.TemporaryDirectory() as work:
            path = Path(work) / 'synthetic.obj'
            data = bytearray(coff(records))
            if mutate:
                mutate(data)
            path.write_bytes(data)
            return obj_func_bytes(path, 'target', length)

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

    def test_span_cannot_read_relocations_as_function_bytes(self):
        with self.assertRaisesRegex(ValueError, 'exceeds COFF section'):
            self.lookup([symbol(1, 1)], length=6)

    def test_span_must_be_positive(self):
        for length in (0, -1):
            with self.assertRaisesRegex(ValueError, 'must be positive'):
                self.lookup([symbol(1, 1)], length=length)

    def test_truncated_section_is_rejected(self):
        with self.assertRaisesRegex(ValueError, 'truncated raw data'):
            self.lookup([symbol(1, 1)],
                        mutate=lambda d: struct.pack_into('<I', d, 40, len(d)))

    def test_relocation_cannot_cover_bytes_outside_span(self):
        with self.assertRaisesRegex(ValueError, 'crosses requested'):
            self.lookup([symbol(1, 1)], length=3)

    def test_unsupported_relocation_width_is_rejected(self):
        with self.assertRaisesRegex(ValueError, 'unsupported COFF relocation'):
            self.lookup([symbol(1, 1)],
                        mutate=lambda d: struct.pack_into('<H', d, 74, 0x000A))

    def test_relative_32_bit_relocation_is_supported(self):
        self.assertEqual(self.lookup([symbol(1, 1)],
                         mutate=lambda d: struct.pack_into('<H', d, 74, 0x0014)),
                         (b'CODE', {0}))

    def test_relocation_target_must_exist(self):
        with self.assertRaisesRegex(ValueError, 'not a primary symbol'):
            self.lookup([symbol(1, 1)],
                        mutate=lambda d: struct.pack_into('<I', d, 70, 99))

    def test_relocation_target_cannot_be_auxiliary(self):
        with self.assertRaisesRegex(ValueError, 'not a primary symbol'):
            self.lookup([symbol(0, aux=1), symbol(1, 0), symbol(1, 1)],
                        mutate=lambda d: struct.pack_into('<I', d, 70, 1))

    def test_short_retail_read_cannot_report_a_match(self):
        with tempfile.TemporaryDirectory() as work:
            path = Path(work) / 'synthetic.obj'
            path.write_bytes(coff([symbol(1, 1)]))
            argv = ['raw_match.py', '--obj', str(path), '--sym', 'target',
                    '--addr', '0x400000', '--len', '0x4']
            output = io.StringIO()
            with patch('sys.argv', argv), patch('raw_match.retail_bytes', return_value=b'COD'), contextlib.redirect_stdout(output):
                with self.assertRaises(SystemExit) as error:
                    main()
            self.assertEqual(error.exception.code, 2)
            self.assertIn('received 3', output.getvalue())
            self.assertNotIn('match: 100.0%', output.getvalue())


if __name__ == '__main__':
    unittest.main()
