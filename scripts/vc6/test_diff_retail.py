#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original; synthetic x86 byte streams only, no retail bytes.
"""Regression tests for contiguous retail-byte instruction decoding."""
import contextlib
import io
import json
import struct
import tempfile
import unittest
from pathlib import Path
from types import SimpleNamespace
from unittest.mock import patch

try:
    import diff_retail as diff_module
except ModuleNotFoundError:
    from scripts.vc6 import diff_retail as diff_module

explicit_length = diff_module.explicit_length
ghidra_bytes = diff_module.ghidra_bytes
raw_x86_insns = diff_module.raw_x86_insns
from test_float_literal_reloc import coff_object


class RetailSpanTests(unittest.TestCase):
    def setUp(self):
        # These tests exercise the mocked bridge, independently of a local PE.
        reader = patch.object(diff_module, "configured_span", return_value=None)
        reader.start()
        self.addCleanup(reader.stop)

    def test_linear_decode_keeps_bytes_after_call(self):
        # call next; mov eax,1; ret. The decoder must continue at the next
        # contiguous byte instead of following only the current CFG edge set.
        code = bytes.fromhex("E8 00 00 00 00 B8 01 00 00 00 C3")
        insns = raw_x86_insns(code, 0x401000)
        self.assertEqual([i[0] for i in insns], [0, 5, 10])
        self.assertEqual([i[2] for i in insns], ["call", "mov", "ret"])
        self.assertEqual(sum(len(i[1]) // 2 for i in insns), len(code))

    def test_linear_decode_uses_real_base_address(self):
        code = bytes.fromhex("E8 00 00 00 00 C3")
        insns = raw_x86_insns(code, 0x401000)
        self.assertIn("0x401005", insns[0][3])
        self.assertEqual(insns[0][0], 0)

    def test_rep_prefix_and_wrapped_instruction_preserve_exact_bytes(self):
        # rep movsd; mov dword ptr [esp+0x12345678],0x04030201; ret.
        # The long immediate/displacement instruction is wrapped by objdump.
        code = bytes.fromhex(
            "F3 A5 C7 84 24 78 56 34 12 01 02 03 04 C3")
        insns = raw_x86_insns(code, 0x402000)
        self.assertEqual(insns[0][2], "rep movs")
        self.assertEqual([i[0] for i in insns], [0, 2, 13])
        self.assertEqual(bytes.fromhex("".join(i[1] for i in insns)), code)

    def test_memory_reader_requires_exact_contiguous_span(self):
        response = [{"address": "0x1000", "size": 2, "hex": "90c3"}]
        with patch.object(diff_module.subprocess, "run", return_value=SimpleNamespace(
                returncode=0, stdout=json.dumps(response), stderr="")):
            self.assertEqual(ghidra_bytes(0x1000, 2), bytes.fromhex("90c3"))

    def test_memory_reader_rejects_missing_bytes(self):
        response = [{"address": "0x1000", "size": 1, "hex": "90"}]
        with patch.object(diff_module.subprocess, "run", return_value=SimpleNamespace(
                returncode=0, stdout=json.dumps(response), stderr="")):
            with self.assertRaisesRegex(SystemExit, "requested 2 bytes"):
                ghidra_bytes(0x1000, 2)

    def test_memory_reader_rejects_gaps(self):
        response = [
            {"address": "0x1000", "size": 1, "hex": "90"},
            {"address": "0x1002", "size": 1, "hex": "c3"},
        ]
        with patch.object(diff_module.subprocess, "run", return_value=SimpleNamespace(
                returncode=0, stdout=json.dumps(response), stderr="")):
            with self.assertRaisesRegex(SystemExit, "not contiguous"):
                ghidra_bytes(0x1000, 2)

    def test_auto_function_size_is_refused(self):
        with self.assertRaisesRegex(SystemExit, "--len auto is refused"):
            explicit_length("auto")

    def test_explicit_length_must_be_positive_hex(self):
        self.assertEqual(explicit_length("0x20"), 0x20)
        with self.assertRaisesRegex(SystemExit, "positive byte span"):
            explicit_length("0x0")


class CompiledInputTests(unittest.TestCase):
    def test_failed_objdump_cannot_be_reported_as_zero_percent(self):
        with patch.object(diff_module.subprocess, "run", return_value=SimpleNamespace(
                returncode=1, stdout="", stderr="object missing")):
            with self.assertRaisesRegex(SystemExit, "objdump failed.*object missing"):
                diff_module.objdump_insns("missing.obj", "wanted")

    def test_missing_symbol_cannot_be_reported_as_zero_percent(self):
        output = "00000000 <other>:\n   0: c3                    ret\n"
        with patch.object(diff_module.subprocess, "run", return_value=SimpleNamespace(
                returncode=0, stdout=output, stderr="")):
            with self.assertRaisesRegex(SystemExit, "no instructions.*wanted"):
                diff_module.objdump_insns("other.obj", "wanted")


class LiteralPoolGuardTests(unittest.TestCase):
    def run_diff(self, blob, retail_insn, compiled_insn, retail_raw, span="0x4"):
        with tempfile.TemporaryDirectory() as temp:
            obj = Path(temp) / "literal.obj"
            obj.write_bytes(blob)
            output = io.StringIO()
            argv = ["diff_retail.py", "--obj", str(obj), "--sym", "func",
                    "--addr", "0x401000", "--len", span]
            with patch("sys.argv", argv), \
                    patch.object(diff_module, "ghidra_bytes", return_value=retail_raw), \
                    patch.object(diff_module, "raw_x86_insns", return_value=[retail_insn]), \
                    patch.object(diff_module, "objdump_insns",
                                 return_value=([compiled_insn], {0})), \
                    patch.object(diff_module.raw_match, "retail_bytes",
                                 side_effect=lambda addr, n: struct.pack("<f", 2.5)), \
                    contextlib.redirect_stdout(output):
                try:
                    diff_module.main()
                except SystemExit as exc:
                    return exc.code, output.getvalue()
            self.fail("diff_retail.main did not exit")

    def test_direct_diff_rejects_wrong_float_hidden_by_normalized_relocation(self):
        retail_raw = struct.pack("<I", 0x402000)
        retail_insn = (0, retail_raw.hex(), "mov", "eax, [0x402000]")
        compiled_insn = (0, "00000000", "mov", "eax, [0x402000]")
        result, output = self.run_diff(
            coff_object(struct.pack("<f", 1.25)), retail_insn,
            compiled_insn, retail_raw)
        self.assertEqual(result, diff_module.raw_match.HARD_LITERAL_FAILURE)
        self.assertIn("HARD FLOAT-LITERAL FAILURE", output)
        self.assertNotIn("match: 100.0%", output)

    def test_partial_instruction_mismatch_keeps_existing_diagnostic(self):
        retail_raw = struct.pack("<I", 0x402000)
        retail_insn = (0, retail_raw.hex(), "mov", "eax, [0x402000]")
        compiled_insn = (0, "00000000", "xor", "eax, eax")
        result, output = self.run_diff(
            coff_object(struct.pack("<f", 1.25)), retail_insn,
            compiled_insn, retail_raw)
        self.assertEqual(result, 1)
        self.assertNotIn("HARD FLOAT-LITERAL FAILURE", output)
        self.assertIn("match: 0.0%", output)

    def test_short_coff_span_is_ineligible_for_literal_hard_failure(self):
        retail_raw = struct.pack("<I", 0x402000) + b"\0\0\0\0"
        retail_insn = (0, retail_raw.hex(), "mov", "eax, [0x402000]")
        compiled_insn = (0, "0000000000000000", "mov", "eax, [0x402000]")
        result, output = self.run_diff(
            coff_object(struct.pack("<f", 1.25)), retail_insn,
            compiled_insn, retail_raw, span="0x8")
        self.assertEqual(result, 0)
        self.assertIn("match: 100.0%", output)
        self.assertNotIn("HARD FLOAT-LITERAL FAILURE", output)


if __name__ == "__main__":
    unittest.main()
