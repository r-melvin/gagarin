#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original tooling; synthetic instruction streams only.
"""Tests for partial_triage (no compiler, no binary): python3 -m unittest test_partial_triage -v"""
import os
import sys
import tempfile
import unittest

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import partial_triage as pt  # noqa: E402


def S(*pairs):
    """[(mnemonic, operands)] -> stream tuples with increasing offsets."""
    return [(i * 3, "00", m, o) for i, (m, o) in enumerate(pairs)]


class Classes(unittest.TestCase):
    def cls(self, r, c, relocs=()):
        return pt.classify_streams(S(*r), S(*c), relocs)

    def test_register_only(self):
        r = self.cls([("mov", "eax,ecx"), ("add", "eax,0x4"), ("ret", "")],
                     [("mov", "edx,ecx"), ("add", "edx,0x4"), ("ret", "")])
        self.assertEqual((r["class"], r["route"], r["delta"]), ("register-only", "permuter", 2))

    def test_stack_only(self):
        r = self.cls([("sub", "esp,0x10"), ("mov", "eax,[esp+0x8]"), ("ret", "")],
                     [("sub", "esp,0x14"), ("mov", "eax,[esp+0xc]"), ("ret", "")])
        self.assertEqual((r["class"], r["route"]), ("stack-only", "reccmp-stackcmp"))

    def test_order_only(self):
        r = self.cls([("mov", "eax,[ecx+0x4]"), ("mov", "edx,[ecx+0x8]"), ("ret", "")],
                     [("mov", "edx,[ecx+0x8]"), ("mov", "eax,[ecx+0x4]"), ("ret", "")])
        self.assertEqual((r["class"], r["route"]), ("order-only", "parked (B16)"))
        self.assertEqual(r["delta"], 1)
        self.assertEqual(r["regpredict"], "B16-schedule")

    def test_block_layout_order_only_stays_with_permuter(self):
        r = pt.classify_streams(S(("jmp", "0x6"), ("inc", "eax"), ("ret", "")),
                                S(("jmp", "0x3"), ("inc", "eax"), ("ret", "")))
        self.assertEqual((r["class"], r["route"]), ("order-only", "permuter"))

    def test_commutative_swap_routes_to_commute_pass(self):
        r = self.cls([("add", "eax,ecx"), ("ret", "")], [("add", "ecx,eax"), ("ret", "")])
        self.assertEqual((r["class"], r["route"]), ("register-only", "source_perm --only commute"))
        self.assertIn("commutative-swap", r["labels"])

    def test_swap_sites_counted_in_mixed_rows(self):
        r = self.cls([("add", "eax,ecx"), ("inc", "edx"), ("ret", "")], [("add", "ecx,eax"), ("inc", "ebx"), ("ret", "")])
        self.assertEqual(r["swaps"], 1)
        self.assertEqual(r["route"], "permuter")        # not purely a swap, so not routed to --only commute

    def test_cmp_swap_routes_to_commute_pass(self):
        r = self.cls([("cmp", "eax,ecx"), ("ret", "")], [("cmp", "ecx,eax"), ("ret", "")])
        self.assertEqual(r["route"], "source_perm --only commute")

    def test_register_only_carries_regpredict(self):
        r = self.cls([("mov", "esi,ecx"), ("push", "esi"), ("ret", "")], [("mov", "ebx,ecx"), ("push", "ebx"), ("ret", "")])
        self.assertEqual((r["class"], r["route"], r["regpredict"]), ("register-only", "permuter", "B1-rebind"))

    def test_inline_shape_we_inline(self):
        retail = [("push", "esi"), ("push", "0x1"), ("call", "0x401000"), ("pop", "esi"), ("ret", "")]
        comp = [("push", "esi"), ("mov", "eax,[ecx+0x4]"), ("test", "eax,eax"), ("jne", "0x20"),
                ("mov", "eax,0x1"), ("add", "eax,[ecx+0x8]"), ("mov", "[ecx+0x4],eax"), ("pop", "esi"),
                ("ret", "")]
        r = self.cls(retail, comp)
        self.assertEqual((r["class"], r["route"]), ("inline-shape", "inline library"))
        self.assertIn("we inline", r["detail"])

    def test_inline_shape_retail_inlines(self):
        comp = [("push", "esi"), ("push", "0x1"), ("call", "0x401000"), ("pop", "esi"), ("ret", "")]
        retail = [("push", "esi"), ("mov", "eax,[ecx+0x4]"), ("test", "eax,eax"), ("jne", "0x20"),
                  ("mov", "eax,0x1"), ("add", "eax,[ecx+0x8]"), ("mov", "[ecx+0x4],eax"), ("pop", "esi"),
                  ("ret", "")]
        r = self.cls(retail, comp)
        self.assertEqual(r["class"], "inline-shape")
        self.assertIn("retail inlines", r["detail"])

    def test_extra_instruction_without_call_is_structural(self):
        r = self.cls([("mov", "eax,ecx"), ("ret", "")], [("mov", "eax,ecx"), ("inc", "eax"), ("ret", "")])
        self.assertEqual((r["class"], r["route"]), ("structural", "manual"))

    def test_mixed_reg_and_stack_is_structural(self):
        r = self.cls([("mov", "eax,[esp+0x8]"), ("ret", "")], [("mov", "edx,[esp+0xc]"), ("ret", "")])
        self.assertEqual((r["class"], r["detail"], r["route"]), ("structural", "reg+stack", "permuter"))

    def test_constant_difference_is_structural(self):
        r = self.cls([("add", "eax,0x4"), ("ret", "")], [("add", "eax,0x8"), ("ret", "")])
        self.assertEqual((r["class"], r["detail"], r["route"]), ("structural", "const", "manual"))

    def test_identical_is_reloc_only(self):
        s = [("mov", "eax,ecx"), ("ret", "")]
        r = self.cls(s, s)
        self.assertEqual((r["class"], r["delta"]), ("reloc-only", 0))

    def test_reorder_plus_registers_routes_to_permuter(self):
        r = self.cls([("mov", "eax,[ecx+0x4]"), ("mov", "edx,[ecx+0x8]"), ("ret", "")],
                     [("mov", "esi,[ecx+0x8]"), ("mov", "eax,[ecx+0x4]"), ("ret", "")])
        self.assertEqual((r["class"], r["route"]), ("structural", "permuter"))

    def test_call_hunk_with_small_share_is_not_inline(self):
        # a one-instruction call difference inside a long stream with many other missing insns
        retail = [("call", "0x401000")] + [("mov", "eax,[ecx+%#x]" % (4 * i)) for i in range(1, 7)] + [("ret", "")]
        comp = [("nop", "")] * 0 + [("mov", "eax,[ecx+%#x]" % (4 * i)) for i in range(1, 7)] + \
               [("inc", "eax"), ("dec", "ebx"), ("inc", "ecx"), ("inc", "edx"), ("ret", "")]
        r = self.cls(retail, comp)
        self.assertEqual(r["class"], "structural")

    def test_lcs_pairs(self):
        self.assertEqual(pt.lcs_pairs(list("abcd"), list("acd")), [(0, 0), (2, 1), (3, 2)])
        big = list(range(2100))
        self.assertEqual(len(pt.lcs_pairs(big, big)), 2100)   # difflib path (n*m over the DP limit)

    def test_every_class_has_a_route(self):
        self.assertEqual(set(pt.CLASSES), set(pt.ROUTE))


class Pipeline(unittest.TestCase):
    def test_relative_out_becomes_absolute(self):
        with tempfile.TemporaryDirectory() as d:
            cwd = os.getcwd()
            os.chdir(d)
            try:
                p = pt.abs_out("rel/out")
                self.assertTrue(os.path.isabs(p))
                self.assertTrue(os.path.isdir(os.path.join(d, "rel", "out")))
            finally:
                os.chdir(cwd)

    def test_unwritable_out_is_fatal(self):
        with self.assertRaises(SystemExit):
            pt.abs_out("/proc/definitely/not/writable")

    def test_each_tu_compiled_once_and_failures_recorded(self):
        calls = []

        def fake(tree, tu, obj):
            calls.append(tu)
            self.assertTrue(os.path.isabs(obj))
            return (tu != "match/bad.cpp"), "boom"

        objs = pt.compile_all("/t", ["match/a.cpp", "match/bad.cpp"], "/o", 4, compile_fn=fake)
        self.assertEqual(sorted(calls), ["match/a.cpp", "match/bad.cpp"])
        self.assertIsNone(objs["match/bad.cpp"][0])
        self.assertTrue(objs["match/a.cpp"][0].endswith("match__a.obj"))

    def test_compile_tu_reports_missing_object(self):
        with tempfile.TemporaryDirectory() as d:
            os.makedirs(os.path.join(d, "scripts", "vc6"))
            os.makedirs(os.path.join(d, "match"))
            with open(os.path.join(d, "scripts", "vc6", "vc6cl.sh"), "w") as f:
                f.write("#!/bin/bash\nexit 0\n")      # claims success, writes nothing
            ok, why = pt.compile_tu(d, "match/x.cpp", os.path.join(d, "out", "x.obj"))
            self.assertFalse(ok)
            self.assertIn("no object", why)

    def test_compile_tu_reports_exit_code(self):
        with tempfile.TemporaryDirectory() as d:
            os.makedirs(os.path.join(d, "scripts", "vc6"))
            os.makedirs(os.path.join(d, "match"))
            with open(os.path.join(d, "scripts", "vc6", "vc6cl.sh"), "w") as f:
                f.write("#!/bin/bash\necho nope >&2\nexit 3\n")
            ok, why = pt.compile_tu(d, "match/x.cpp", os.path.join(d, "out", "x.obj"))
            self.assertFalse(ok)
            self.assertIn("exit 3", why)

    def test_triage_rows_and_tsv(self):
        rows = [{"addr": "0x401000", "tu": "match/a.cpp", "sym": "?a", "len": "0x10", "pct": 90, "name": "A::a"},
                {"addr": "0x402000", "tu": "match/bad.cpp", "sym": "?b", "len": "0x10", "pct": 50, "name": "B::b"},
                {"addr": "0x403000", "tu": "match/a.cpp", "sym": "?c", "len": "0x10", "pct": 80, "name": "C::c"}]
        objs = {"match/a.cpp": ("/o/a.obj", ""), "match/bad.cpp": (None, "compiler exit 2")}
        st = {"retail": S(("mov", "eax,ecx"), ("ret", "")), "comp": S(("mov", "edx,ecx"), ("ret", "")), "relocs": []}

        def fake_score(tree, out, obj, row):
            return (90.0, st, "") if row["addr"] == "0x401000" else (None, None, ["diff_retail: boom"])

        recs = pt.triage_rows(rows, objs, "/t", "/o", 4, frozenset({"0x401000"}), score_fn=fake_score)
        by = {r["addr"]: r for r in recs}
        self.assertEqual(by["0x401000"]["class"], "register-only")
        self.assertIn("distribution patch", by["0x401000"]["detail"])
        self.assertEqual(by["0x402000"]["class"], "compile-fail")
        self.assertEqual(by["0x403000"]["class"], "no-score")
        with tempfile.TemporaryDirectory() as d:
            path = os.path.join(d, "t.tsv")
            pt.write_tsv(path, recs)
            with open(path) as fh:
                lines = fh.read().splitlines()
            self.assertEqual(lines[0].split("\t"), pt.COLS)
            self.assertEqual(len(lines), 4)
            self.assertTrue(lines[1].startswith("0x401000\tregister-only\t"))
        s = pt.summarise(recs)
        self.assertEqual(s["classes"], {"register-only": 1, "compile-fail": 1, "no-score": 1})


if __name__ == "__main__":
    unittest.main()
