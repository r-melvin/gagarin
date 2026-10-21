#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: synthetic COFF fixtures and mocked retail spans only.
"""Regression tests for hard checks of relocated MSVC float literals."""
import contextlib
import io
import struct
import tempfile
import unittest
from pathlib import Path
from unittest.mock import patch

import raw_match
import verify_all
import verify_tus


def coff_object(literal=None, external=False, width=4, trailing_bytes=b"",
                addend=0, relocation_type=0x0006, symbol_value=0,
                rdata_prefix=b""):
    """Build .text + optional .rdata with one DIR32 relocation at .text+0."""
    if external:
        target_name = b"external"
        target_section = 0
        target_value = 0
        rdata = b""
    else:
        target_name = b"__real@4@3fa00000" if width == 4 else b"__real@8@3ff4000000000000"
        target_section = 2
        target_value = symbol_value
        rdata = rdata_prefix + literal
    nsec = 2
    section_table_end = 20 + 40 * nsec
    text_ptr = section_table_end
    text = struct.pack("<I" if relocation_type == 0x0006 else "<i", addend) + trailing_bytes
    reloc_ptr = text_ptr + len(text)
    relocation = struct.pack("<IIH", 0, 1, relocation_type)
    rdata_ptr = reloc_ptr + len(relocation)
    symptr = rdata_ptr + len(rdata)
    symbols = 2
    string_table = b"\0\0\0\0"
    if target_section:
        encoded_name = struct.pack("<II", 0, 4)
        string_table += target_name + b"\0"
        target_sym = struct.pack("<8sIhHBB", encoded_name, target_value,
                                 target_section, 0x20, 2, 0)
    else:
        target_sym = struct.pack("<8sIhHBB", target_name.ljust(8, b"\0"),
                                 target_value, target_section, 0x20, 2, 0)
    function_sym = struct.pack("<8sIhHBB", b"func\0\0\0\0", 0, 1,
                               0x20, 2, 0)
    strtab = struct.pack("<I", len(string_table)) + string_table[4:]
    header = struct.pack("<HHIIIHH", 0x14C, nsec, 0, symptr, symbols, 0, 0)
    text_header = struct.pack("<8sIIIIIIHHI", b".text", 0, 0, len(text),
                              text_ptr, reloc_ptr, 0, 1, 0, 0x20)
    rdata_header = struct.pack("<8sIIIIIIHHI", b".rdata", 0, 0, len(rdata),
                               rdata_ptr if rdata else 0, 0, 0, 0, 0, 0x40)
    return (header + text_header + rdata_header + text + relocation + rdata
            + function_sym + target_sym + strtab)


class FloatLiteralRelocationTests(unittest.TestCase):
    def run_raw(self, blob, retail_bytes, span=4):
        with tempfile.TemporaryDirectory() as temp:
            obj = Path(temp) / "literal.obj"
            obj.write_bytes(blob)
            output = io.StringIO()
            argv = ["raw_match.py", "--obj", str(obj), "--sym", "func",
                    "--addr", "0x401000", "--len", hex(span)]
            with patch("sys.argv", argv), patch("raw_match.retail_bytes", side_effect=retail_bytes), \
                    contextlib.redirect_stdout(output):
                try:
                    raw_match.main()
                except SystemExit as exc:
                    return exc.code, output.getvalue()
            self.fail("raw_match.main did not exit")

    def test_wrong_literal_with_normalized_operand_is_hard_failure(self):
        target = 0x402000
        blob = coff_object(struct.pack("<f", 1.25))
        result, output = self.run_raw(
            blob, lambda addr, n: struct.pack("<I", target) if addr == 0x401000
            else struct.pack("<f", 2.5))
        self.assertEqual(result, raw_match.HARD_LITERAL_FAILURE)
        self.assertIn("HARD FLOAT-LITERAL FAILURE", output)
        self.assertNotIn("match: 100.0%", output)

    def test_literal_equal_to_retail_target_passes(self):
        target = 0x402000
        value = struct.pack("<f", 1.25)
        result, output = self.run_raw(
            coff_object(value), lambda addr, n: struct.pack("<I", target)
            if addr == 0x401000 else value)
        self.assertEqual(result, 0)
        self.assertIn("match: 100.0%", output)

    def test_double_literal_mismatch_is_also_a_hard_failure(self):
        target = 0x402000
        blob = coff_object(struct.pack("<d", 1.25), width=8)
        result, output = self.run_raw(
            blob, lambda addr, n: struct.pack("<I", target) if addr == 0x401000
            else struct.pack("<d", 2.5))
        self.assertEqual(result, raw_match.HARD_LITERAL_FAILURE)
        self.assertIn("__real@8@", output)

    def test_upper_dword_reference_compares_full_double_from_symbol_base(self):
        target = 0x402000
        value = struct.pack("<d", 1.25)

        def read(addr, n):
            if addr == 0x401000:
                return struct.pack("<I", target + 4)
            if addr == target:
                return value
            self.fail(f"unexpected retail read at {addr:#x} for {n} bytes")

        result, output = self.run_raw(
            coff_object(value, width=8, addend=4), read)
        self.assertEqual(result, 0)
        self.assertIn("match: 100.0%", output)

    def test_negative_rel32_addend_recovers_full_literal_base(self):
        function = 0x401000
        literal_base = 0x402004
        relocated_target = literal_base - 4
        value = struct.pack("<f", 1.25)

        def read(addr, n):
            if addr == function:
                return struct.pack("<i", relocated_target - (function + 4))
            if addr == literal_base:
                return value
            self.fail(f"unexpected retail read at {addr:#x} for {n} bytes")

        result, output = self.run_raw(
            coff_object(value, width=4, addend=-4, relocation_type=0x0014,
                        symbol_value=4, rdata_prefix=b"PAD!"), read)
        self.assertEqual(result, 0)
        self.assertIn("match: 100.0%", output)

    def test_partial_function_keeps_instruction_diagnostic(self):
        target = 0x402000
        result, output = self.run_raw(
            coff_object(struct.pack("<f", 1.25), trailing_bytes=b"\0\0\0\0"),
            lambda addr, n: (struct.pack("<I", target) + b"\1\0\0\0")
            if addr == 0x401000 else struct.pack("<f", 2.5), span=8)
        self.assertEqual(result, 1)
        self.assertIn("match: <100% (real diffs)", output)
        self.assertNotIn("HARD FLOAT-LITERAL FAILURE", output)

    def test_ordinary_external_relocation_is_unchanged(self):
        target = 0x402000
        calls = []

        def read(addr, n):
            calls.append((addr, n))
            return struct.pack("<I", target)

        result, output = self.run_raw(coff_object(external=True), read)
        self.assertEqual(result, 0)
        self.assertIn("match: 100.0%", output)
        self.assertEqual(calls, [(0x401000, 4)])

    def test_adjacent_relocation_fields_cover_each_differing_byte(self):
        self.assertTrue(raw_match.raw_span_matches_modulo_relocations(
            b"abcdefgh", b"ABCDEFGH", {0, 4}))


class HardLiteralFallbackTests(unittest.TestCase):
    def test_verify_all_does_not_fall_back_after_hard_literal_failure(self):
        failure = type("Result", (), {"returncode": 3,
                                      "stdout": "HARD FLOAT-LITERAL FAILURE", "stderr": ""})()
        with patch.object(verify_all.subprocess, "run", return_value=failure) as run:
            self.assertEqual(verify_all.verify("fixture.obj", "func", "0x401000", "0x4"),
                             (False, "hard float-literal relocation failure"))
        self.assertEqual(run.call_count, 1)

    def test_verify_tus_does_not_fall_back_after_hard_literal_failure(self):
        failure = type("Result", (), {"returncode": 3,
                                      "stdout": "HARD FLOAT-LITERAL FAILURE", "stderr": ""})()
        entry = {"sym": "func", "addr": "0x401000", "len": "0x4"}
        with patch.object(verify_tus.subprocess, "run", return_value=failure) as run:
            self.assertEqual(verify_tus.verify("fixture.obj", entry),
                             (False, "hard float-literal relocation failure"))
        self.assertEqual(run.call_count, 1)


if __name__ == "__main__":
    unittest.main()
