#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original project tooling; synthetic instruction streams only (no retail bytes).
"""Unit tests for inline_sites.py / vector_census.py (run: python3 -m unittest test_inline_sites)."""
import os, sys, types, unittest

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import inline_sites as IS
import vector_census as VC


def opts(**kw):
    o = types.SimpleNamespace(window=4, min_sites=3, min_insns=5, min_content=3, ool_extra=4)
    o.__dict__.update(kw)
    return o


def make(funcs):
    """funcs: {addr: [normalised strings]} -> the structure load_data returns."""
    table, vocab, fd = [], {}, []
    for a, strs in sorted(funcs.items()):
        toks = []
        for s in strs:
            if s not in vocab:
                vocab[s] = len(table)
                table.append(s)
            toks.append(vocab[s])
        fd.append((a, len(strs) * 3, toks, [a + 3 * i for i in range(len(toks))], [3] * len(toks)))
    return {"table": table, "funcs": fd, "kinds": {}}


BODY = ["mov R32,DWORD PTR [R32+0x4]", "cmp R32,0x40000", "jge +9", "mov R32,DWORD PTR ds:0x87f924",
        "mov R32,DWORD PTR [R32+R32*4]", "test R32,R32", "jne +5"]


class Normalise(unittest.TestCase):
    def test_registers_abstracted_displacements_kept(self):
        n = IS.normalise("mov", "eax,DWORD PTR [ecx+0x13c]", 0x1000, 6, 0x1000, 0x1100)
        self.assertEqual(n, "mov R32,DWORD PTR [R32+0x13c]")
        self.assertEqual(IS.normalise("mov", "al,BYTE PTR [esi+0xd]", 0, 3, 0, 0x100), "mov R8,BYTE PTR [R32+0xd]")

    def test_stack_displacements_abstracted(self):
        self.assertEqual(IS.normalise("mov", "eax,DWORD PTR [esp+0x14]", 0, 4, 0, 9), "mov R32,DWORD PTR [R32+S]")
        self.assertEqual(IS.normalise("mov", "eax,DWORD PTR [esp+0x14]", 0, 4, 0, 9, keep_stack=True),
                         "mov R32,DWORD PTR [R32+0x14]")

    def test_calls_keep_target_jumps_become_relative(self):
        self.assertEqual(IS.normalise("call", "0x5657a0", 0x1000, 5, 0, 0x2000), "call 0x5657a0")
        self.assertEqual(IS.normalise("jge", "0x1010", 0x1000, 2, 0x1000, 0x1100), "jge +14")
        self.assertEqual(IS.normalise("jmp", "0x9000", 0x1000, 2, 0x1000, 0x1100), "jmp far")

    def test_padding_dropped(self):
        self.assertIsNone(IS.normalise("nop", "", 0, 1, 0, 9))
        self.assertIsNone(IS.normalise("int3", "", 0, 1, 0, 9))


class Clusters(unittest.TestCase):
    def setUp(self):
        self.funcs = {}
        for i in range(5):
            self.funcs[0x1000 + 0x100 * i] = ["push R32", f"mov R32,0x{i:x}"] + BODY + [f"add R32,0x{i:x}", "ret"]
        self.funcs[0x2000] = ["xor R32,R32", "ret"]
        self.funcs[0x3000] = list(BODY)          # an out-of-line copy of the body

    def test_cluster_found_with_sites_and_out_of_line_copy(self):
        d = make(self.funcs)
        o = opts(ool_extra=1)
        cl = IS.find_clusters(d, o)
        self.assertTrue(cl)
        reps = IS.build_report(d, cl, o, st={0x1000: "matched"}, rows={})
        best = max(reps, key=lambda r: r["insns"])
        self.assertEqual(best["insns"], len(BODY))
        self.assertEqual(best["sites"], 6)           # five inline sites plus the whole-function copy
        self.assertEqual([x["addr"] for x in best["out_of_line"]], [0x3000])
        self.assertEqual(best["blocked_functions"], 5)   # 0x1000 is matched; 4 inline sites + the copy remain
        self.assertEqual(best["label"], "anchored")

    def test_below_min_sites_is_not_reported(self):
        d = make({0x1000: BODY, 0x2000: BODY + ["ret"]})
        self.assertEqual(IS.find_clusters(d, opts(min_sites=3)), [])

    def test_sub_body_with_same_sites_suppressed(self):
        d = make(self.funcs)
        cl = IS.find_clusters(d, opts())
        bodies = [tuple(d["table"][t] for t in b) for b, _ in cl]
        self.assertEqual(sum(1 for b in bodies if "test R32,R32" in b and "cmp R32,0x40000" in b), 1)


class Census(unittest.TestCase):
    DELETE = ["mov R32,DWORD PTR [R32+0x10]", "mov R32,DWORD PTR [esp+0x4]", "cmp R32,R32", "jge fwd", "dec R32",
              "cmp R32,R32", "mov DWORD PTR [R32+0x10],R32", "jge fwd", "mov R32,DWORD PTR [R32+0x4]", "inc R32",
              "mov R32,DWORD PTR [R32+R32*4]", "mov DWORD PTR [R32+R32*4-0x4],R32", "ret 0x4"]

    def test_delete_detected_only_with_matching_scale(self):
        self.assertEqual(len(VC.find_delete(self.DELETE)), 1)
        bad = [s.replace("*4-0x4", "*8-0x4") for s in self.DELETE]
        self.assertEqual(VC.find_delete(bad), [])

    def test_virtual_find_needs_minus_one_test(self):
        self.assertEqual(VC.find_find_virtual(["call DWORD PTR [R32+0x10]", "cmp R32,0xffffffff"]), [0])
        self.assertEqual(VC.find_find_virtual(["call DWORD PTR [R32+0x10]", "ret"]), [])


if __name__ == "__main__":
    unittest.main()
