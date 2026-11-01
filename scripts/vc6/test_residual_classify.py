#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original; synthetic instruction streams only, no retail bytes.
"""Fixture tests for residual_classify.classify."""
import unittest

import residual_classify as rc


def stream(*lines, base=0):
    """Build (offset, hex, mnemonic, operands) tuples; every insn is 2 bytes."""
    out = []
    for i, line in enumerate(lines):
        m, _, o = line.partition(" ")
        out.append((base + 2 * i - base, "9090", m, o))
    return out


def labels(r, c, relocs=()):
    return rc.classify(stream(*r), stream(*c), relocs)["labels"]


class ClassifyTest(unittest.TestCase):
    def test_register_swap(self):
        r = ["mov eax,ecx", "add eax,edx", "ret"]
        c = ["mov edx,ecx", "add edx,eax", "ret"]
        self.assertEqual(labels(r, c), ["register-swap"])

    def test_stack_slot(self):
        r = ["mov eax,[esp+0x8]", "push eax", "ret"]
        c = ["mov eax,[esp+0xc]", "push eax", "ret"]
        self.assertEqual(labels(r, c), ["stack-slot"])

    def test_esp_adjust_is_stack(self):
        r = ["sub esp,0x10", "ret"]
        c = ["sub esp,0x14", "ret"]
        self.assertEqual(labels(r, c), ["stack-slot"])

    def test_scheduling(self):
        r = ["dec eax", "test eax,eax", "mov [esi+0x1c],eax"]
        c = ["dec eax", "mov [esi+0x1c],eax", "test eax,eax"]
        self.assertEqual(labels(r, c), ["scheduling"])

    def test_constant(self):
        r = ["mov eax,0x10", "ret"]
        c = ["mov eax,0x14", "ret"]
        self.assertEqual(labels(r, c), ["constant"])

    def test_missing_extra_mnemonic(self):
        r = ["movsx eax,byte ptr [ecx+0x4]", "ret"]
        c = ["mov al,byte ptr [ecx+0x4]", "ret"]
        self.assertEqual(labels(r, c), ["missing-extra"])

    def test_missing_extra_count(self):
        self.assertEqual(labels(["inc eax", "ret"], ["inc eax", "inc eax", "ret"]),
                         ["missing-extra"])

    def test_branch_polarity(self):
        r = ["cmp eax,ecx", "je 0x6", "inc eax", "ret"]
        c = ["cmp eax,ecx", "jne 0x6", "inc eax", "ret"]
        self.assertIn("branch-polarity", labels(r, c))

    def test_branch_polarity_with_extra_jmp(self):
        r = ["cmp eax,ecx", "jl 0x8", "inc eax", "ret"]
        c = ["cmp eax,ecx", "jge 0x8", "jmp 0x8", "inc eax", "ret"]
        self.assertIn("branch-polarity", labels(r, c))

    def test_absolute_address_is_not_a_constant(self):
        # compiled side carries a zero in the relocation slot, retail the address
        retail = [(0, "a1e8f78700", "mov", "eax,ds:0x87f7e8")]
        comp = [(0, "a100000000", "mov", "eax,ds:0x0")]
        self.assertEqual(rc.classify(retail, comp, [1])["labels"], ["reloc-or-table"])

    def test_call_target_masked(self):
        retail = [(0, "e8", "call", "0x5f6440"), (5, "c3", "ret", "")]
        comp = [(0, "e8", "call", "0x14"), (5, "c3", "ret", "")]
        self.assertEqual(rc.classify(retail, comp, [1])["labels"], ["reloc-or-table"])

    def test_branch_target_layout(self):
        retail = [(0, "7e", "jg", "0x16"), (2, "90", "nop", ""),
                  (4, "90", "nop", ""), (6, "c3", "ret", "")]
        comp = [(0, "7e", "jg", "0x6"), (2, "90", "nop", ""),
                (4, "90", "nop", ""), (6, "c3", "ret", "")]
        self.assertEqual(rc.classify(retail, comp, [], base=0x10)["labels"],
                         ["reloc-or-table"])
        comp2 = [(0, "7e", "jg", "0x6"), (2, "90", "nop", ""),
                 (4, "90", "nop", ""), (6, "c3", "ret", "")]
        retail2 = [(0, "7e", "jg", "0x14"), (2, "90", "nop", ""),
                   (4, "90", "nop", ""), (6, "c3", "ret", "")]
        self.assertEqual(rc.classify(retail2, comp2, [], base=0x10)["labels"],
                         ["branch-target"])

    def test_primary_and_eligibility(self):
        self.assertEqual(rc.primary(["register-swap", "scheduling"]), "scheduling")
        self.assertEqual(rc.primary(["register-swap", "missing-extra"]), "missing-extra")
        self.assertTrue({"register-swap", "scheduling"} <= rc.PERMUTABLE)
        self.assertNotIn("constant", rc.PERMUTABLE)


class SwapLabelsTest(unittest.TestCase):
    def test_commutative_swap(self):
        r = ["mov eax,ecx", "add eax,edx", "ret"]
        c = ["mov eax,ecx", "add edx,eax", "ret"]
        self.assertEqual(labels(r, c), ["register-swap", "commutative-swap"])

    def test_mixed_register_diff_is_not_a_pure_swap(self):
        r = ["mov eax,ecx", "add eax,edx", "ret"]
        c = ["mov edx,ecx", "add edx,eax", "ret"]
        self.assertNotIn("commutative-swap", labels(r, c))

    def test_base_index_swap(self):
        r = ["mov eax,[ecx+edx]", "ret"]
        c = ["mov eax,[edx+ecx]", "ret"]
        self.assertIn("commutative-swap", labels(r, c))

    def test_scaled_index_is_not_swappable(self):
        r = ["mov eax,[ecx+edx*4]", "ret"]
        c = ["mov eax,[edx+ecx*4]", "ret"]
        self.assertEqual(labels(r, c), ["register-swap"])

    def test_cmp_swap(self):
        r = ["cmp eax,ecx", "ret"]
        c = ["cmp ecx,eax", "ret"]
        self.assertEqual(labels(r, c), ["register-swap", "cmp-swap"])

    def test_sub_is_not_commutative(self):
        self.assertEqual(labels(["sub eax,ecx", "ret"], ["sub ecx,eax", "ret"]), ["register-swap"])

    def test_pure_transposition_is_parked(self):
        r = stream("dec eax", "test eax,eax", "mov [esi+0x1c],eax")
        c = stream("dec eax", "mov [esi+0x1c],eax", "test eax,eax")
        res = rc.classify(r, c)
        self.assertEqual(res["parked"], "B16")
        self.assertEqual(res["regpredict"]["label"], "B16-schedule")

    def test_register_swap_is_not_parked(self):
        res = rc.classify(stream("mov eax,ecx", "ret"), stream("mov edx,ecx", "ret"))
        self.assertNotIn("parked", res)


if __name__ == "__main__":
    unittest.main()
