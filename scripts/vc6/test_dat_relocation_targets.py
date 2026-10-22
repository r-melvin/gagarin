#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original synthetic COFF fixtures; no retail bytes embedded.
"""Regression tests for address-labelled DAT_ relocation targets."""
import contextlib
import io
import struct
import tempfile
import unittest
from pathlib import Path
from unittest.mock import patch

import raw_match
import diff_retail
import verify_all
import verify_tus
import subprocess


def coff_object(target_name, *, kind=0x0006, addend=0, tail=b''):
    """Make one i386 COFF function with a relocation to an undefined symbol."""
    body = struct.pack('<I', addend & 0xFFFFFFFF) + tail
    raw_ptr = 60
    reloc_ptr = raw_ptr + len(body)
    sym_ptr = reloc_ptr + 10
    names = b'func\0' + target_name.encode('ascii') + b'\0'
    string_table = struct.pack('<I', 4 + len(names)) + names
    target_offset = 4 + len(b'func\0')

    def name_field(name, offset):
        if len(name.encode('ascii')) <= 8:
            return name.encode('ascii').ljust(8, b'\0')
        return b'\0\0\0\0' + struct.pack('<I', offset)

    function_symbol = struct.pack('<8sIhHBB', name_field('func', 0), 0,
                                  1, 0x20, 2, 0)
    target_symbol = struct.pack('<8sIhHBB', name_field(target_name, target_offset),
                                0, 0, 0, 2, 0)
    header = struct.pack('<HHIIIHH', 0x14C, 1, 0, sym_ptr, 2, 0, 0)
    section = struct.pack('<8sIIIIIIHHI', b'.text\0\0\0', 0, 0,
                          len(body), raw_ptr, reloc_ptr, 0, 1, 0,
                          0x60000020)
    relocation = struct.pack('<IIH', 0, 1, kind)
    return header + section + body + relocation + function_symbol + target_symbol + string_table


class DatRelocationTargetTests(unittest.TestCase):
    def check(self, name, *, kind=0x0006, addend=0, addr=0x401000,
              retail=None, tail=b''):
        blob = coff_object(name, kind=kind, addend=addend, tail=tail)
        with tempfile.TemporaryDirectory() as temp:
            obj = Path(temp) / 'candidate.obj'
            obj.write_bytes(blob)
            if retail is None:
                base = int(raw_match.DAT_ADDRESS_RE.match(name).group(1), 16)
                target = (base + addend) & 0xFFFFFFFF
                if kind == 0x0006:
                    retail = struct.pack('<I', target) + tail
                else:
                    disp = (target - (addr + 4)) & 0xFFFFFFFF
                    retail = struct.pack('<I', disp) + tail
            return obj, retail, raw_match.verify_address_label_relocations(
                str(obj), 'func', addr, retail)

    def test_undecorated_dat_dir32_with_addend(self):
        self.assertIsNone(self.check('DAT_0087DE30', addend=4)[2])

    def test_decorated_dat_dir32(self):
        self.assertIsNone(self.check('?DAT_0087DE30@@3PAUThing@@A')[2])

    def test_swapped_commutative_dat_target_fails(self):
        with self.assertRaisesRegex(raw_match.AddressLabelRelocationError,
                                    'DAT_0087DE30.*retail operand targets 0x0087de44'):
            self.check('DAT_0087DE30', retail=struct.pack('<I', 0x0087DE44))

    def test_rel32_uses_encoded_target_and_addend(self):
        self.assertIsNone(self.check('DAT_0087DE30', kind=0x0014,
                                     addend=8)[2])

    def test_rel32_wrong_target_fails(self):
        with self.assertRaisesRegex(raw_match.AddressLabelRelocationError,
                                    'retail operand targets'):
            self.check('DAT_0087DE30', kind=0x0014,
                       retail=struct.pack('<i', 0x0087DE48 - (0x401000 + 4)))

    def test_non_dat_function_symbol_is_outside_narrow_check(self):
        blob = coff_object('SomeFunction@@YAXXZ')
        with tempfile.TemporaryDirectory() as temp:
            obj = Path(temp) / 'candidate.obj'
            obj.write_bytes(blob)
            self.assertIsNone(raw_match.verify_address_label_relocations(
                str(obj), 'func', 0x401000, struct.pack('<I', 0x12345678)))

    def test_dat_text_inside_method_owner_is_not_a_global_label(self):
        # MSVC names can contain arbitrary template and owner text. Only a DAT
        # symbol at the start of the COFF name is an address-labelled global.
        name = '?Method@Class_DAT_0087DE30@@QAEXXZ'
        self.assertIsNone(raw_match.DAT_ADDRESS_RE.match(name))
        with tempfile.TemporaryDirectory() as temp:
            obj = Path(temp) / 'method.obj'
            obj.write_bytes(coff_object(name))
            self.assertIsNone(raw_match.verify_address_label_relocations(
                str(obj), 'func', 0x401000, struct.pack('<I', 0x12345678)))

    def test_partial_raw_span_stays_diagnostic_not_hard_failure(self):
        blob = coff_object('DAT_0087DE30', addend=0, tail=b'\x90')
        with tempfile.TemporaryDirectory() as temp:
            obj = Path(temp) / 'candidate.obj'
            obj.write_bytes(blob)
            result = raw_match.verify_relocation_targets_for_raw_exact_span(
                str(obj), 'func', 0x401000,
                struct.pack('<I', 0x0087DE30) + b'\x91')
            self.assertFalse(result)

    def test_wrong_dat_target_is_hard_even_with_unrelated_real_byte_difference(self):
        blob = coff_object('DAT_0087DE30', tail=b'\x00')
        with tempfile.TemporaryDirectory() as temp:
            obj = Path(temp) / 'partial.obj'
            obj.write_bytes(blob)
            with self.assertRaisesRegex(raw_match.AddressLabelRelocationError,
                                        'retail operand targets 0x0087de44'):
                raw_match.verify_relocation_targets_for_raw_exact_span(
                    str(obj), 'func', 0x401000,
                    struct.pack('<I', 0x0087DE44) + b'\x01')

    def test_short_comdat_checks_available_dat_operands_without_failing_float_partials(self):
        # The object section has only the first four bytes of the requested
        # retail span. The available DIR32 is still enough to reject a swapped
        # address-labelled operand; a short non-DAT body remains diagnostic.
        blob = coff_object('DAT_0087DE30', tail=b'')
        with tempfile.TemporaryDirectory() as temp:
            obj = Path(temp) / 'candidate.obj'
            obj.write_bytes(blob)
            with self.assertRaisesRegex(raw_match.AddressLabelRelocationError,
                                        'retail operand targets 0x0087de44'):
                raw_match.verify_relocation_targets_for_raw_exact_span(
                    str(obj), 'func', 0x401000,
                    struct.pack('<I', 0x0087DE44) + b'\0' * 4)

        # Use a non-address-labelled literal relocation to retain the existing
        # short-span fallback behavior; it is not a DAT target claim.
        from test_diff_retail import coff_object as literal_coff_object
        with tempfile.TemporaryDirectory() as temp:
            obj = Path(temp) / 'short.obj'
            obj.write_bytes(literal_coff_object(struct.pack('<f', 1.25)))
            self.assertFalse(raw_match.verify_relocation_targets_for_raw_exact_span(
                str(obj), 'func', 0x401000, b'\0' * 8))

    def test_raw_match_hard_failure_prevents_false_100(self):
        blob = coff_object('DAT_0087DE30')
        with tempfile.TemporaryDirectory() as temp:
            obj = Path(temp) / 'candidate.obj'
            obj.write_bytes(blob)
            output = io.StringIO()
            argv = ['raw_match.py', '--obj', str(obj), '--sym', 'func',
                    '--addr', '0x401000', '--len', '0x4']
            with patch('sys.argv', argv), \
                 patch.object(raw_match, 'retail_bytes',
                              return_value=struct.pack('<I', 0x0087DE44)), \
                 contextlib.redirect_stdout(output):
                with self.assertRaises(SystemExit) as error:
                    raw_match.main()
            self.assertEqual(error.exception.code, raw_match.HARD_RELOCATION_FAILURE)
            self.assertIn('HARD DAT-RELOCATION FAILURE', output.getvalue())
            self.assertNotIn('match: 100.0%', output.getvalue())

    def test_verify_all_stops_on_address_label_failure(self):
        result = subprocess.CompletedProcess([], raw_match.HARD_RELOCATION_FAILURE,
                                            stdout='HARD DAT-RELOCATION FAILURE')
        with patch.object(verify_all.subprocess, 'run', return_value=result) as run:
            verdict = verify_all.verify('fixture.obj', 'func', '0x401000', '0x4')
        self.assertEqual(verdict, (False, 'address-labelled DAT relocation target mismatch'))
        self.assertEqual(run.call_count, 1)

    def test_verify_tus_stops_on_address_label_failure(self):
        result = subprocess.CompletedProcess([], raw_match.HARD_RELOCATION_FAILURE,
                                            stdout='HARD DAT-RELOCATION FAILURE')
        entry = {'sym': 'func', 'addr': '0x401000', 'len': '0x4'}
        with patch.object(verify_tus.subprocess, 'run', return_value=result) as run:
            verdict = verify_tus.verify('fixture.obj', entry)
        self.assertEqual(verdict, (False, 'address-labelled DAT relocation target mismatch'))
        self.assertEqual(run.call_count, 1)

    def test_diff_fallback_hard_fails_same_wrong_target(self):
        # The extra real byte also differs, but a normalized instruction
        # comparison still reports an exact instruction stream. The DAT target
        # audit must run before the ordinary non-exact-byte fallback returns.
        blob = coff_object('DAT_0087DE30', tail=b'\0')
        with tempfile.TemporaryDirectory() as temp:
            obj = Path(temp) / 'candidate.obj'
            obj.write_bytes(blob)
            retail = struct.pack('<I', 0x0087DE44) + b'\1'
            insn = [(0, retail.hex(), 'mov', 'eax, [0x87de44]')]
            output = io.StringIO()
            argv = ['diff_retail.py', '--obj', str(obj), '--sym', 'func',
                    '--addr', '0x401000', '--len', '0x4']
            with patch('sys.argv', argv), \
                 patch.object(diff_retail, 'ghidra_bytes', return_value=retail), \
                 patch.object(diff_retail, 'raw_x86_insns', return_value=insn), \
                 patch.object(diff_retail, 'objdump_insns', return_value=(insn, {0})), \
                 contextlib.redirect_stdout(output):
                with self.assertRaises(SystemExit) as error:
                    diff_retail.main()
            self.assertEqual(error.exception.code, raw_match.HARD_RELOCATION_FAILURE)
            self.assertIn('HARD DAT-RELOCATION FAILURE', output.getvalue())
            self.assertNotIn('match: 100.0%', output.getvalue())


if __name__ == '__main__':
    unittest.main()
