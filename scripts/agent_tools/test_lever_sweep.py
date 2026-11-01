#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original tooling; synthetic sources and fake compile/score functions only.
"""Tests for lever_sweep (no compiler, no binary): python3 -m unittest test_lever_sweep -v"""
import json
import os
import sys
import tempfile
import unittest

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import lever_sweep as ls  # noqa: E402

SRC = """// FUNCTION: GAMEMD 0x401000
A::~A()
{
    for (int i = 0; i < Vec.Count; ++i)
        delete Vec.Items[i];
    Vec.Count = 0;
    other.Count++;
}

// SYNTHETIC: GAMEMD 0x401100
// compiler generated, no body here

// FUNCTION: GAMEMD 0x401200
int B::Sum() const
{
    int n = p->Count + Vec.Count; /* x.Count in comment */ const char* s = "a.Count";
    return n + Other.Count;
}
"""


class Body(unittest.TestCase):
    def test_body_found_and_bounded(self):
        s, e = ls.function_body(SRC, "0x401000")
        self.assertTrue(SRC[s:e].startswith("{") and SRC[s:e].endswith("}"))
        self.assertIn("delete Vec.Items", SRC[s:e])
        self.assertNotIn("Sum", SRC[s:e])

    def test_bodyless_marker(self):
        self.assertIsNone(ls.function_body(SRC, "0x401100"))

    def test_missing_marker(self):
        self.assertIsNone(ls.function_body(SRC, "0x999999"))

    def test_decl_semicolon(self):
        self.assertIsNone(ls.function_body("// FUNCTION: GAMEMD 0x1\nint f();\nint g() { return 1; }", "0x1"))


class Sites(unittest.TestCase):
    def sites(self, addr):
        s, e = ls.function_body(SRC, addr)
        body = SRC[s:e]
        return body, ls.RULES["vec-count"].sites(body)

    def test_reads_only(self):
        body, st = self.sites("0x401000")
        self.assertEqual([body[a:b] for a, b, _ in st], [".Count"])  # not `= 0`, not `++`

    def test_comment_and_string_not_special_cased_but_second_function_sites(self):
        body, st = self.sites("0x401200")
        self.assertGreaterEqual(len(st), 3)
        self.assertTrue(all(n.endswith("GetCount()") for _, _, n in st))

    def test_arrow(self):
        _, st = self.sites("0x401200")
        self.assertIn("->GetCount()", [n for _, _, n in st])

    def test_apply(self):
        span = ls.function_body(SRC, "0x401000")
        _, st = self.sites("0x401000")
        out = ls.apply_sites(SRC, span, st)
        self.assertIn("i < Vec.GetCount();", out)
        self.assertIn("Vec.Count = 0;", out)
        self.assertEqual(out[:span[0]], SRC[:span[0]])
        self.assertTrue(out.endswith(SRC[span[1]:]))

    def test_variants(self):
        vs = ls.variants(ls.RULES["vec-count"], SRC[slice(*ls.function_body(SRC, "0x401200"))])
        self.assertEqual(vs[0][0], "all")
        self.assertEqual(len(vs), 1 + len(vs[0][1]))
        self.assertEqual(ls.variants(ls.RULES["vec-count"], "{ return 1; }"), [])

    def test_write_context(self):
        for text, w in [("a.Count = 1;", True), ("a.Count == 1", False), ("a.Count += 2", True), ("a.Count++", True),
                        ("++a.Count", True), ("&a.Count", True), ("x && a.Count", False), ("a.Count()", True)]:
            i = text.index(".Count")
            self.assertEqual(ls.is_write_context(text, i, i + 6), w, text)


class Accessors(unittest.TestCase):
    def test_disabled_without_accessor(self):
        with tempfile.TemporaryDirectory() as t:
            os.makedirs(os.path.join(t, "match"))
            with open(os.path.join(t, "match/vector_class.h"), "w") as f:
                f.write("int GetCount() const { return Count; }\n")
            rules, skipped = ls.enabled_rules(t, ["vec-count", "vec-capacity", "vec-activecount"])
            self.assertEqual([r.name for r in rules], ["vec-count"])
            self.assertEqual(skipped, ["vec-capacity", "vec-activecount"])


class Regression(unittest.TestCase):
    def test_regression(self):
        base = {"a": 100.0, "b": 90.0, "c": 50.0}
        self.assertIsNone(ls.regression(base, {"a": 100.0, "b": 95.0, "c": 50.0}, "c"))
        self.assertIn("a", ls.regression(base, {"a": 99.0, "b": 90.0, "c": 90.0}, "c"))
        self.assertIn("b", ls.regression(base, {"a": 100.0, "b": None, "c": 90.0}, "c"))
        self.assertIsNone(ls.regression(base, {"a": 100.0, "b": 90.0, "c": 10.0}, "c"))  # target is judged elsewhere


class Sweep(unittest.TestCase):
    """sweep_tu with a fake compiler: the 'object' is the source text, the score is read from it."""

    def setUp(self):
        self.t = tempfile.TemporaryDirectory()
        self.tree = self.t.name
        os.makedirs(os.path.join(self.tree, "match"))
        self.tu = "match/x.cpp"
        self.path = os.path.join(self.tree, self.tu)
        self.rows = [{"addr": "0x401000", "sym": "s1", "len": "0x10", "status": "partial", "tu": self.tu},
                     {"addr": "0x401200", "sym": "s2", "len": "0x10", "status": "matched", "tu": self.tu}]

    def tearDown(self):
        self.t.cleanup()

    def run_sweep(self, src, score, targets=("0x401000",), rules=None):
        with open(self.path, "w", encoding="latin-1", newline="") as f:
            f.write(src)

        def compile_fn(tree, tu, obj):
            with open(os.path.join(tree, tu), encoding="latin-1", newline="") as f:
                text = f.read()
            if "COMPILE_ERROR" in text:
                return False, "boom"
            os.makedirs(os.path.dirname(obj), exist_ok=True)
            with open(obj, "w", encoding="latin-1", newline="") as f:
                f.write(text)
            return True, ""

        def score_fn(tree, obj, row):
            with open(obj, encoding="latin-1") as f:
                return score(f.read(), row["addr"])

        res = ls.sweep_tu(self.tree, self.tu, self.rows, rules or [ls.RULES["vec-count"]], set(targets),
                          compile_fn, score_fn, objdir=os.path.join(self.tree, "obj"))
        with open(self.path, encoding="latin-1", newline="") as f:
            after_file = f.read()
        return res, after_file

    def test_kept_when_improved_and_file_restored(self):
        def score(text, addr):
            if addr == "0x401000":
                return 100.0 if "i < Vec.GetCount()" in text else 90.0
            return 100.0
        (recs, final), on_disk = self.run_sweep(SRC, score)
        self.assertEqual(on_disk, SRC)  # restored; the driver writes `final` when it keeps
        self.assertIn("Vec.GetCount()", final)
        self.assertTrue(recs[0]["kept"])
        self.assertEqual((recs[0]["before"], recs[0]["after"]), (90.0, 100.0))

    def test_no_improvement_rejected(self):
        (recs, final), _ = self.run_sweep(SRC, lambda text, addr: 90.0 if addr == "0x401000" else 100.0)
        self.assertEqual(final, SRC)
        self.assertFalse(any(r["kept"] for r in recs))
        self.assertEqual(recs[0]["reason"], "no improvement")

    def test_regression_in_matched_row_rejects(self):
        def score(text, addr):
            if addr == "0x401000":
                return 100.0 if "GetCount" in text else 90.0
            return 99.0 if "GetCount" in text else 100.0
        (recs, final), _ = self.run_sweep(SRC, score)
        self.assertEqual(final, SRC)
        self.assertFalse(any(r["kept"] for r in recs))
        self.assertTrue(recs[0]["reason"].startswith("regressed 0x401200"))

    def test_compile_failure_rejects(self):
        rule = ls.Rule("bad", r"(\.|->)Count\b", lambda m: m.group(1) + "COMPILE_ERROR", "GetCount")
        (recs, final), _ = self.run_sweep(SRC, lambda t, a: 50.0, rules=[rule])
        self.assertEqual(final, SRC)
        self.assertTrue(recs[0]["reason"].startswith("compile failed"))

    def test_single_site_wins_over_all(self):
        # two sites in 0x401200; only rewriting the first one helps; the matched safety row is 0x401000
        rows = [{"addr": "0x401200", "sym": "s2", "len": "0x10", "status": "partial", "tu": self.tu},
                {"addr": "0x401000", "sym": "s1", "len": "0x10", "status": "matched", "tu": self.tu}]
        self.rows = rows

        def score(text, addr):
            if addr == "0x401000":
                return 100.0
            return {True: 95.0, False: 80.0}["p->GetCount() + Vec.Count" in text]
        (recs, final), _ = self.run_sweep(SRC, score, targets=("0x401200",))
        kept = [r for r in recs if r["kept"]]
        self.assertEqual(len(kept), 1)
        self.assertEqual(kept[0]["variant"], "site1")
        self.assertIn("p->GetCount() + Vec.Count", final)

    def test_matched_noop_not_kept(self):
        # --matched safety check: a matched row that stays 100 is not "improved", so nothing is kept
        (recs, final), _ = self.run_sweep(SRC, lambda t, a: 100.0, targets=("0x401200",))
        self.assertEqual(final, SRC)
        self.assertTrue(all(not r["kept"] and r["reason"] == "no improvement" for r in recs))

    def test_kept_rewrites_accumulate_across_rows(self):
        self.rows = [{"addr": "0x401000", "sym": "s1", "len": "0x10", "status": "partial", "tu": self.tu},
                     {"addr": "0x401200", "sym": "s2", "len": "0x10", "status": "partial", "tu": self.tu}]

        def score(text, addr):
            if addr == "0x401000":
                return 100.0 if "i < Vec.GetCount()" in text else 90.0
            return 100.0 if "return n + Other.GetCount()" in text and "i < Vec.GetCount()" in text else 80.0
        (recs, final), _ = self.run_sweep(SRC, score, targets=("0x401000", "0x401200"))
        self.assertEqual(sorted(r["addr"] for r in recs if r["kept"]), ["0x401000", "0x401200"])


class Ledger(unittest.TestCase):
    def test_rows(self):
        with tempfile.TemporaryDirectory() as t:
            rec = dict(addr="0x401000", tu="match/x.cpp", rule="vec-count", variant="all", sites=2, before=90.0,
                       after=100.0, kept=True, reason="", source_sha="ab")
            r = ls.ledger_row(rec, t, "a")
            self.assertEqual((r["status"], r["raw"], r["addr"]), ("recorded", 100.0, "0x401000"))
            rec.update(kept=False, reason="regressed 0x4 100.0 -> 99.0")
            r = ls.ledger_row(rec, t, "a")
            self.assertEqual((r["status"], r["raw"]), ("swept", None))
            self.assertIn("rejected", r["variant"])


if __name__ == "__main__":
    unittest.main()
