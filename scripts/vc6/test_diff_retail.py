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


def duplicate_text_comdat_object(path, *, relocation=False, nonzero_symbol=False,
                                relocation_target=3, relocation_offset=None):
    """Write a tiny COFF object with two .text sections and a foreign $L label."""
    import struct

    victim_function = (bytes.fromhex("e8 00 00 00 00 8b f8 c3") if relocation
                       else bytes.fromhex("b8 01 00 00 00 8b f8 c3"))
    prefix = b"\x90\x90" if nonzero_symbol else b""
    victim = prefix + victim_function
    other = bytes.fromhex("90 90 90 90 90 90 90 90 90 c3")
    data_start = 20 + 2 * 40
    raw1 = data_start
    raw2 = raw1 + len(victim)
    reloc_ptr1 = raw2 + len(other) if relocation else 0
    reloc_ptr2 = reloc_ptr1 + 10 if relocation else 0
    symbol_ptr = raw2 + len(other) + (20 if relocation else 0)
    nsyms = 4 if relocation else 3
    section_data = bytearray()
    for name, raw_size, raw_ptr in ((b".text", len(victim), raw1),
                                    (b".text", len(other), raw2)):
        is_victim = raw_ptr == raw1
        section_data.extend(struct.pack(
            "<8sIIIIIIHHI", name.ljust(8, b"\0"), 0, 0, raw_size,
            raw_ptr,
            reloc_ptr1 if relocation and is_victim else
            reloc_ptr2 if relocation else 0,
            0, 1 if relocation else 0, 0,
            0x60000020))
    if relocation_offset is None:
        relocation_offset = len(prefix) + 1
    relocs = (struct.pack("<IIH", relocation_offset, relocation_target, 0x0014)
              + struct.pack("<IIH", 1, 3, 0x0014)) if relocation else b""

    def symbol(name, value, section, storage):
        return struct.pack("<8sIhHBB", name.ljust(8, b"\0"), value,
                           section, 0, storage, 0)

    symbol_data = (symbol(b"victim", len(prefix), 1, 2)
                   + symbol(b"switch", 0, 2, 2)
                   + symbol(b"$Lsplit", 8 if nonzero_symbol else 6, 2, 6))
    if relocation:
        symbol_data += symbol(b"external", 0, 0, 2)
    header = struct.pack("<HHIIIHH", 0x14C, 2, 0, symbol_ptr, nsyms, 0, 0)
    string_table = struct.pack("<I", 4)
    path.write_bytes(header + bytes(section_data) + victim + other + relocs
                     + symbol_data + string_table)


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

    def test_linear_decode_includes_embedded_zero_runs(self):
        # Zero bytes inside a contiguous span are code/data bytes too. GNU
        # objdump otherwise suppresses zero runs unless `-z` is enabled.
        code = bytes.fromhex("90 00 00 90 c3")
        insns = raw_x86_insns(code, 0x401000)
        self.assertEqual([i[0] for i in insns], [0, 1, 3, 4])
        self.assertEqual(sum(len(i[1]) // 2 for i in insns), len(code))
        self.assertEqual(bytes.fromhex("".join(i[1] for i in insns)), code)

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
    def test_cross_comdat_switch_label_cannot_split_victim_instruction(self):
        with tempfile.TemporaryDirectory() as temp:
            obj = Path(temp) / "duplicate_text.obj"
            duplicate_text_comdat_object(obj)
            insns, relocs = diff_module.objdump_insns(str(obj), "victim")
        self.assertEqual([insn[1] for insn in insns],
                         ["b801000000", "8bf8", "c3"])
        self.assertEqual([insn[2] for insn in insns], ["mov", "mov", "ret"])
        self.assertEqual(relocs, set())

    def test_relocations_are_kept_from_the_selected_comdat_only(self):
        with tempfile.TemporaryDirectory() as temp:
            obj = Path(temp) / "duplicate_text_reloc.obj"
            # The relocation belongs to the victim section, not the second
            # same-named .text section containing the foreign local label.
            duplicate_text_comdat_object(obj, relocation=True)
            insns, relocs = diff_module.objdump_insns(str(obj), "victim")
        self.assertEqual([insn[1] for insn in insns], ["e800000000", "8bf8", "c3"])
        self.assertEqual(relocs, {1})

    def test_nonzero_symbol_start_keeps_local_offsets_and_ignores_foreign_reloc(self):
        with tempfile.TemporaryDirectory() as temp:
            obj = Path(temp) / "offset_comdat_reloc.obj"
            duplicate_text_comdat_object(obj, relocation=True, nonzero_symbol=True)
            old_listing = diff_module.subprocess.run(
                ["objdump", "-d", "-r", "-M", "intel", str(obj)],
                capture_output=True, text=True, check=True).stdout
            insns, relocs = diff_module.objdump_insns(str(obj), "victim")
        # Confirm the generated fixture exercises the real binutils failure:
        # the foreign section's offset-8 label appears in the victim section
        # and splits the second byte of its mov edi,eax instruction.
        victim_listing = old_listing.split("00000002 <victim>:", 1)[1].split(
            "Disassembly of section .text:", 1)[0]
        self.assertIn(".byte 0x8b", victim_listing)
        self.assertIn("clc", victim_listing)
        self.assertEqual([insn[0] for insn in insns], [0, 5, 7])
        self.assertEqual([insn[1] for insn in insns], ["e800000000", "8bf8", "c3"])
        self.assertEqual(relocs, {1})

    def test_invalid_relocation_symbol_index_is_rejected(self):
        with tempfile.TemporaryDirectory() as temp:
            obj = Path(temp) / "invalid_reloc_target.obj"
            duplicate_text_comdat_object(
                obj, relocation=True, relocation_target=999)
            with self.assertRaisesRegex(SystemExit, "relocation target is not a primary symbol"):
                diff_module.objdump_insns(str(obj), "victim")

    def test_relocation_field_crossing_symbol_section_is_rejected(self):
        with tempfile.TemporaryDirectory() as temp:
            obj = Path(temp) / "crossing_reloc.obj"
            duplicate_text_comdat_object(
                obj, relocation=True, relocation_offset=6)
            with self.assertRaisesRegex(SystemExit, "crosses requested function span"):
                diff_module.objdump_insns(str(obj), "victim")

    def test_missing_symbol_cannot_be_reported_as_zero_percent(self):
        with tempfile.TemporaryDirectory() as temp:
            obj = Path(temp) / "other.obj"
            duplicate_text_comdat_object(obj)
            with self.assertRaisesRegex(SystemExit, "cannot read COFF symbol wanted"):
                diff_module.objdump_insns(str(obj), "wanted")


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


def label_object(path, code, relocs, labels):
    """Write a one-section COFF object: `func` at 0, `$L` labels, DIR32 relocations.

    `labels` maps a label name (at most 8 bytes) to its section offset; `relocs`
    maps a relocation offset to the label it names, as VC6 does for switch tables."""
    names = list(labels)
    section_ptr = 20 + 40
    reloc_ptr = section_ptr + len(code)
    symbol_ptr = reloc_ptr + 10 * len(relocs)

    def symbol(name, value, storage):
        return struct.pack("<8sIhHBB", name.ljust(8, b"\0"), value, 1, 0, storage, 0)

    table = [symbol(b"func", 0, 2)] + [symbol(n.encode(), labels[n], 6) for n in names]
    reloc_data = b"".join(struct.pack("<IIH", at, 1 + names.index(n) + 0, 0x0006)
                          for at, n in relocs.items())
    header = struct.pack("<HHIIIHH", 0x14C, 1, 0, symbol_ptr, len(table), 0, 0)
    section = struct.pack("<8sIIIIIIHHI", b".text", 0, 0, len(code), section_ptr,
                          reloc_ptr, 0, len(relocs), 0, 0x60000020)
    path.write_bytes(header + section + code + reloc_data + b"".join(table)
                     + struct.pack("<I", 4))


ADDR = 0x401000
HEAD = bytes.fromhex("8b442404 83f801 770d")         # mov eax,[esp+4]; cmp eax,1; ja +13
CASES = bytes.fromhex("b801000000 c3 33c0c3")         # case 0: eax=1; case 1: eax=0
PAD = bytes.fromhex("909090")


def jump_switch(addr, table_at, slots, pad=PAD):
    """Function body, alignment padding, then a dword jump table at `table_at`."""
    code = (HEAD + bytes.fromhex("ff2485") + struct.pack("<I", table_at) + CASES + pad
            + b"".join(struct.pack("<I", slot) for slot in slots))
    return code


def run_diff(obj, retail, length):
    output = io.StringIO()
    argv = ["diff_retail.py", "--obj", str(obj), "--sym", "func",
            "--addr", hex(ADDR), "--len", hex(length)]
    with patch("sys.argv", argv), \
            patch.object(diff_module, "ghidra_bytes", return_value=retail), \
            contextlib.redirect_stdout(output):
        try:
            diff_module.main()
        except SystemExit as exc:
            return exc.code, output.getvalue()
    raise AssertionError("diff_retail.main did not exit")


class SwitchTableTests(unittest.TestCase):
    """Switch tables are compared as relocation targets, never decoded as code."""

    def score(self, code, relocs, labels, retail, length):
        with tempfile.TemporaryDirectory() as temp:
            obj = Path(temp) / "switch.obj"
            label_object(obj, code, relocs, labels)
            return run_diff(obj, retail, length)

    def jump_case(self, retail_slots=(ADDR + 16, ADDR + 22), length=36, retail_tail=None):
        retail = jump_switch(ADDR, ADDR + 28, retail_slots)
        compiled = jump_switch(0, 0, (0, 0))
        labels = {"$LTAB": 28, "$LC0": 16, "$LC1": 22}
        relocs = {12: "$LTAB", 28: "$LC0", 32: "$LC1"}
        return self.score(compiled, relocs, labels, retail[:length], length)

    def test_table_inside_span_is_compared_not_decoded(self):
        code, out = self.jump_case()
        self.assertEqual(code, 0)
        self.assertIn("table: 2/2 switch table entries match", out)
        self.assertIn("match: 100.0%", out)
        self.assertNotIn("add byte ptr", out)

    def test_table_slot_targeting_another_case_is_a_mismatch(self):
        code, out = self.jump_case(retail_slots=(ADDR + 16, ADDR + 16))
        self.assertEqual(code, 1)
        self.assertIn("table: 1/2 switch table entries match", out)
        self.assertNotIn("match: 100.0%", out)

    def test_compiled_side_longer_than_span_does_not_misread_the_table(self):
        # Retail's span stops after the last case; the compiled code runs three
        # alignment bytes longer, so its table starts inside the compared length.
        code, out = self.jump_case(length=25)
        self.assertEqual(code, 0)
        self.assertIn("lies outside the retail span", out)
        self.assertIn("match: 100.0%", out)

    def test_compiled_code_longer_than_retail_still_fails(self):
        extra = bytes.fromhex("40")                  # inc eax before the final ret
        retail = jump_switch(ADDR, ADDR + 28, (ADDR + 16, ADDR + 22))[:25]
        compiled = HEAD + bytes.fromhex("ff2485") + b"\0" * 4 + CASES[:-1] + extra + CASES[-1:]
        compiled += bytes.fromhex("909090") + b"\0" * 8
        code, out = self.score(compiled, {12: "$LTAB", 29: "$LC0", 33: "$LC1"},
                               {"$LTAB": 29, "$LC0": 16, "$LC1": 22}, retail, 25)
        self.assertEqual(code, 1)
        self.assertNotIn("match: 100.0%", out)

    def byte_case(self, retail_bytes):
        head = bytes.fromhex("8b442404 33c9")
        body = (head + bytes.fromhex("8a88") + b"{btab}" + bytes.fromhex("ff248d") + b"{jtab}"
                + CASES)

        def build(btab, jtab, slots, index):
            code = body.replace(b"{btab}", struct.pack("<I", btab)).replace(
                b"{jtab}", struct.pack("<I", jtab))
            return code + b"".join(struct.pack("<I", s) for s in slots) + index

        retail = build(ADDR + 36, ADDR + 28, (ADDR + 19, ADDR + 25), retail_bytes)
        compiled = build(0, 0, (0, 0), bytes.fromhex("000101"))
        labels = {"$LBTAB": 36, "$LJTAB": 28, "$LC0": 19, "$LC1": 25}
        relocs = {8: "$LBTAB", 15: "$LJTAB", 28: "$LC0", 32: "$LC1"}
        return self.score(compiled, relocs, labels, retail, len(retail))

    def test_byte_index_table_is_compared(self):
        code, out = self.byte_case(bytes.fromhex("000101"))
        self.assertEqual(code, 0)
        self.assertIn("table: 5/5 switch table entries match", out)
        self.assertIn("match: 100.0%", out)

    def test_byte_index_table_difference_is_a_mismatch(self):
        code, out = self.byte_case(bytes.fromhex("000100"))
        self.assertEqual(code, 1)
        self.assertIn("table: 4/5 switch table entries match", out)
        self.assertNotIn("match: 100.0%", out)

    def test_function_without_a_table_is_unchanged(self):
        # The compiled tail past --len is dropped after a terminator, exactly as
        # before, and nothing table-related is printed.
        retail = HEAD + CASES
        compiled = HEAD + CASES + bytes.fromhex("90 0000 0000")
        code, out = self.score(compiled, {}, {}, retail, len(retail))
        self.assertEqual(code, 0)
        self.assertIn("dropped 5 bytes past the function end", out)
        self.assertNotIn("table:", out)
        self.assertIn("match: 100.0%", out)

    def test_function_without_a_table_still_fails_on_a_changed_instruction(self):
        retail = HEAD + CASES
        compiled = HEAD + CASES.replace(bytes.fromhex("33c0"), bytes.fromhex("33c9"))
        code, out = self.score(compiled, {}, {}, retail, len(retail))
        self.assertEqual(code, 1)
        self.assertNotIn("table:", out)
        self.assertNotIn("match: 100.0%", out)


if __name__ == "__main__":
    unittest.main()
