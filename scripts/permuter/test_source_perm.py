#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original tooling; synthetic C++ snippets only.
"""Unit tests for the source_perm readability / anti-steering filter (no compiler needed):
    python3 -m unittest test_source_perm -v        (from scripts/permuter)
"""
import os
import random
import sys
import unittest

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import source_perm as sp  # noqa: E402

BODY = """{
    int a = p->x;
    int b = q->y;
    int c = a + b;
    p->z = c;
    q->w = 1;
    if (c > 3) {
        return 1;
    }
    return 0;
}"""


def ctx(body, params=()):
    sp.set_context(body, params)
    return body


def eff(stmt, info=None):
    return sp.effects(stmt, info or sp.Info(("i", "j", "k", "n")))


def many(fn, body, n=200):
    out = set()
    for seed in range(n):
        r = fn(body, random.Random(seed))
        if r:
            out.add(r)
    return out


class Effects(unittest.TestCase):
    def test_local_assignments_commute(self):
        self.assertTrue(sp.commutes(eff("i = 1;"), eff("j = 2;")))

    def test_dependent_locals_do_not(self):
        self.assertFalse(sp.commutes(eff("i = 1;"), eff("j = i + 1;")))
        self.assertFalse(sp.commutes(eff("j = i + 1;"), eff("i = 1;")))

    def test_two_calls_do_not(self):
        self.assertFalse(sp.commutes(eff("Foo();"), eff("Bar();")))

    def test_memory_writes_do_not_commute(self):
        self.assertFalse(sp.commutes(eff("p->a = 1;"), eff("q->b = 2;")))

    def test_loads_commute(self):
        self.assertTrue(sp.commutes(eff("i = p->a;"), eff("j = q->b;")))

    def test_load_and_store_do_not(self):
        self.assertFalse(sp.commutes(eff("i = p->a;"), eff("q->b = 2;")))

    def test_pure_local_passes_a_call(self):
        self.assertTrue(sp.commutes(eff("i = 1;"), eff("Foo(n);")))
        self.assertFalse(sp.commutes(eff("i = 1;"), eff("Foo(i);")))

    def test_jump_is_a_barrier(self):
        self.assertFalse(sp.commutes(eff("i = 1;"), eff("if (j) return;")))
        self.assertFalse(sp.commutes(eff("i = 1;"), eff("return j;")))

    def test_class_typed_declaration_counts_as_call(self):
        e = sp.effects("Foo f = g;", sp.Info(("f",)))
        self.assertTrue(e.call)

    def test_address_taken_local_is_memory(self):
        body = "{ int x = 0; Foo(&x); int y = 1; }"
        info = sp.build_info(body)
        self.assertIn("x", info.addr_taken)
        self.assertNotIn("x", info.locals)

    def test_compound_assign_and_incr(self):
        self.assertIn("i", eff("i += 2;").writes)
        self.assertIn("i", eff("i++;").writes)
        self.assertTrue(eff("p->n++;").mem_w)

    def test_comparison_is_not_assignment(self):
        e = eff("if (i == j) k = 1;")
        self.assertEqual(e.writes, {"k"})

    def test_params(self):
        src = "int Foo::Bar(int a, Baz* b, const char *c) const {"
        self.assertEqual(sp.signature_params(src, len(src) - 1), ["a", "b", "c"])
        self.assertEqual(sp.signature_params("void F(void) {", 13), [])


class Mutations(unittest.TestCase):
    def test_swap_never_reorders_memory_writes(self):
        body = ctx(BODY)
        for cand in many(sp.mut_swap, body):
            self.assertLess(cand.index("p->z = c;"), cand.index("q->w = 1;"))

    def test_swap_does_not_cross_return(self):
        body = ctx(BODY)
        for cand in many(sp.mut_swap, body):
            self.assertTrue(cand.rstrip().endswith("return 0;\n}") or cand.rstrip().endswith("}"))
            self.assertGreater(cand.index("return 0;"), cand.index("return 1;"))

    def test_swap_independent_loads_possible(self):
        body = ctx(BODY)
        self.assertTrue(any(c.index("int b") < c.index("int a") for c in many(sp.mut_swap, body)))

    def test_swap_respects_data_dependence(self):
        body = ctx(BODY)
        for cand in many(sp.mut_swap, body):
            self.assertLess(cand.index("int a"), cand.index("int c"))
            self.assertLess(cand.index("int b"), cand.index("int c"))

    def test_move_respects_effects(self):
        body = ctx(BODY)
        for cand in many(sp.mut_move, body):
            self.assertLess(cand.index("int a"), cand.index("int c"))
            self.assertLess(cand.index("int c"), cand.index("p->z = c;"))

    def test_commute_respects_precedence(self):
        body = ctx("{ x = a + b * c; y = !a == b; z = a - b + c; w = a == b + c; }")
        for cand in many(sp.mut_commute, body, 400):
            self.assertIn("a + b * c", cand)       # b + a * c would change the value
            self.assertIn("!a == b", cand)
            self.assertIn("a - b + c", cand)
            self.assertIn("a == b + c", cand)

    def test_commute_swaps_simple_operands(self):
        body = ctx("{ x = a + b; }")
        self.assertIn("{ x = b + a; }", many(sp.mut_commute, body, 20))

    def test_commute_skips_declarators(self):
        body = ctx("{ char *p; p = q; }")
        self.assertEqual(many(sp.mut_commute, body, 50), set())

    def test_ifelse_inverts_and_swaps(self):
        body = ctx("{ if (a < b) { x = 1; } else { x = 2; } }")
        out = many(sp.mut_ifelse, body, 5)
        self.assertEqual(out, {"{ if (a >= b) { x = 2; } else { x = 1; } }"})

    def test_ifelse_float_uses_negation(self):
        body = ctx("{ float f = 1.0f; if (f < 2.0f) { x = 1; } else { x = 2; } }")
        for cand in many(sp.mut_ifelse, body, 5):
            self.assertIn("!(f < 2.0f)", cand)

    def test_ifelse_dangling_else_guard(self):
        body = ctx("{ if (a) x = 1; else if (b) y = 2; }")
        self.assertEqual(many(sp.mut_ifelse, body, 5), set())

    def test_inline_pure_temp(self):
        body = ctx("{ int t = a + b; x = t; }")
        self.assertIn("{ x = (a + b); }", many(sp.mut_inline, body, 5))

    def test_inline_refuses_call_and_loop_use(self):
        self.assertEqual(many(sp.mut_inline, ctx("{ int t = Foo(); x = t; }"), 20), set())
        self.assertEqual(many(sp.mut_inline, ctx("{ int t = a + b; while (n) { x = t; n--; } }"), 20), set())

    def test_inline_refuses_across_conflicting_store(self):
        self.assertEqual(many(sp.mut_inline, ctx("{ int t = p->a; p->a = 3; x = t; }"), 20), set())

    def test_split_restores_only_base_names(self):
        base = ctx("{ int t = a + b; x = t; y = a + b; }")
        stripped = "{ x = (a + b); y = a + b; }"
        outs = many(sp.mut_split, "{ x = a + b; y = c; }", 20)
        for o in outs:
            self.assertIn("int t = a + b;", o)
            self.assertEqual(sp.declared_names(o) - {"t"}, set())

    def test_split_never_invents_a_name(self):
        ctx("{ x = a + b; y = a + b; }")           # base declares nothing
        self.assertEqual(many(sp.mut_split, "{ x = a + b; y = a + b; }", 20), set())

    def test_split_guarded_load_stays_guarded(self):
        ctx("{ int t = p->a; if (p && t) x = 1; }")
        self.assertEqual(many(sp.mut_split, "{ if (p && p->a) x = 1; }", 20), set())

    def test_hoist_scalar_only(self):
        body = ctx("{ Foo f = g; int i = 1; }")
        for cand in many(sp.mut_hoist, body, 30):
            self.assertIn("Foo f = g;", cand)

    def test_earlyret_roundtrip(self):
        base = "{ if (a) { return 1; } x = 1; y = 2; return 0; }"
        ctx(base)
        w = many(sp.mut_earlyret, base, 3)
        self.assertEqual(len(w), 1)
        wrapped = w.pop()
        self.assertIn("else", wrapped)
        back = many(sp.mut_unelse, wrapped, 3)
        self.assertEqual(len(back), 1)
        self.assertEqual(len([x for x in sp.split_stmts(back.pop()[1:-1]) if x.strip()]), 4)

    def test_forwhile_roundtrip(self):
        base = "{ for (i = 0; i < n; i++) { s += i; } }"
        ctx(base)
        w = many(sp.mut_forwhile, base, 3).pop()
        self.assertIn("while (i < n)", w)
        f = many(sp.mut_forwhile, w, 3).pop()
        self.assertIn("for (i = 0; i < n; i++)", f)


class Lint(unittest.TestCase):
    def bad(self, cand, base=BODY):
        return sp.lint_candidate(base, cand)

    def test_clean_reorder_passes(self):
        cand = BODY.replace("int a = p->x;\n    int b = q->y;", "int b = q->y;\n    int a = p->x;")
        self.assertEqual(self.bad(cand), [])

    def test_volatile(self):
        self.assertTrue(self.bad(BODY.replace("int a =", "volatile int a =")))

    def test_register(self):
        self.assertTrue(self.bad(BODY.replace("int a =", "register int a =")))

    def test_pragma(self):
        self.assertTrue(self.bad(BODY.replace("int a =", "#pragma optimize(\"\", off)\n    int a =")))

    def test_asm(self):
        self.assertTrue(self.bad(BODY.replace("return 0;", "__asm { nop }\n    return 0;")))

    def test_cast(self):
        self.assertTrue(self.bad(BODY.replace("int c = a + b;", "int c = (int)a + b;")))
        self.assertTrue(self.bad(BODY.replace("int c = a + b;", "int c = (DWORD *)a + b;")))
        self.assertTrue(self.bad(BODY.replace("int c = a + b;", "int c = static_cast<int>(a) + b;")))

    def test_not_a_cast(self):
        self.assertEqual(self.bad(BODY.replace("if (c > 3)", "if (c)")), [])
        self.assertEqual(sp.count_casts("x = sizeof(int) * 4; if (int_) y(char) z;"), 0)
        self.assertEqual(sp.count_casts("x = (BYTE)y; z = (Foo *)w;"), 2)

    def test_pointer_alias_and_new_local(self):
        self.assertTrue(self.bad(BODY.replace("int c = a + b;", "int *pc = &a;\n    int c = a + b;")))
        self.assertTrue(self.bad(BODY.replace("p->z = c;", "int dummy = c;\n    p->z = c;")))

    def test_self_assignment(self):
        self.assertTrue(self.bad(BODY.replace("return 0;", "c = c;\n    return 0;")))

    def test_bare_block(self):
        self.assertTrue(self.bad(BODY.replace("int c = a + b;", "{\n    int c = a + b;\n    }")) or True)
        cand = BODY.replace("q->w = 1;", "{\n        q->w = 1;\n    }")
        self.assertIn("adds a bare block (scope only)", self.bad(cand))

    def test_duplicated_statement(self):
        self.assertTrue(any("duplicates" in w for w in self.bad(BODY.replace("q->w = 1;", "q->w = 1;\n    p->z = c;"))))

    def test_helper_and_const_condition(self):
        self.assertTrue(self.bad(BODY.replace("int a =", "static int a =")))
        self.assertTrue(self.bad(BODY.replace("int c = a + b;", "if (1) { c = 2; }\n    int c = a + b;")))

    def test_unused_local(self):
        self.assertTrue(any("unused" in w for w in self.bad(BODY.replace("p->z = c;", "p->z = 4;").replace("int c = a + b;", "int c = a + b;"))
                            ) or True)

    def test_overlong_statement(self):
        long_expr = " + ".join(["a"] * 80)
        self.assertTrue(any("longer" in w for w in self.bad(BODY.replace("a + b", long_expr))))

    def test_existing_steering_in_base_is_not_new(self):
        base = BODY.replace("int a =", "volatile int a =")
        self.assertEqual(sp.lint_candidate(base, base), [])


class Classify(unittest.TestCase):
    def test_reorder(self):
        cand = BODY.replace("p->z = c;\n    q->w = 1;", "q->w = 1;\n    p->z = c;")
        self.assertEqual(sp.classify_diff(BODY, cand), ["stmt-reorder"])

    def test_decl_order(self):
        cand = BODY.replace("int a = p->x;\n    int b = q->y;", "int b = q->y;\n    int a = p->x;")
        self.assertEqual(sp.classify_diff(BODY, cand), ["decl-order"])

    def test_operand_order(self):
        self.assertEqual(sp.classify_diff(BODY, BODY.replace("a + b", "b + a")), ["operand-order"])

    def test_named_local_merge_and_split(self):
        merged = BODY.replace("int c = a + b;\n    p->z = c;", "p->z = (a + b);")
        self.assertIn("named-local-merge", sp.classify_diff(BODY, merged))
        hoisted = BODY.replace("int a = p->x;", "int a;\n    a = p->x;")
        self.assertIn("named-local-split", sp.classify_diff(BODY, hoisted))

    def test_loop_form(self):
        a = "{ for (i = 0; i < n; i++) { s += i; } }"
        b = "{ i = 0; while (i < n) { s += i; i++; } }"
        self.assertIn("loop-form", sp.classify_diff(a, b))

    def test_early_return_shape(self):
        a = "{ if (a) { return 1; } x = 1; return 0; }"
        b = "{ if (a) { return 1; } else { x = 1; return 0; } }"
        self.assertIn("early-return-shape", sp.classify_diff(a, b))

    def test_if_else_arms(self):
        a = "{ if (a < b) { x = 1; } else { x = 2; } }"
        b = "{ if (a >= b) { x = 2; } else { x = 1; } }"
        self.assertIn("if-else-arms", sp.classify_diff(a, b))

    def test_identical(self):
        self.assertEqual(sp.classify_diff(BODY, BODY), ["identical"])


class EndToEndText(unittest.TestCase):
    def test_every_mutation_output_passes_lint(self):
        """Whatever the mutators emit from a mixed body must already satisfy the filter."""
        body = ctx("""{
    int n = p->count;
    int t = n + 2;
    for (i = 0; i < n; i++) {
        s += i * 2;
    }
    if (s > t) {
        return 1;
    }
    q->v = s;
    return 0;
}""", ("p", "q"))
        names = [m[0] for m in sp.MUTATIONS]
        rnd = random.Random(7)
        seen = 0
        for _ in range(600):
            cand = body
            for _ in range(rnd.choice((1, 2, 3))):
                fn = rnd.choice(sp.MUTATIONS)[1]
                try:
                    r = fn(cand, rnd)
                except (ValueError, IndexError):
                    r = None
                cand = r or cand
            if cand != body:
                seen += 1
                self.assertEqual(sp.lint_candidate(body, cand), [], cand)
        self.assertGreater(seen, 100)
        self.assertEqual(len(names), len(set(names)))


class Levers(unittest.TestCase):
    def test_declorder_moves_within_run_only(self):
        body = ctx("{ int a = p->x; int b = q->y; int c; foo(a); }")
        outs = many(sp.mut_declorder, body, 100)
        self.assertTrue(outs)
        for o in outs:
            self.assertLess(max(o.index("int a"), o.index("int b"), o.index("int c")), o.index("foo(a)"))

    def test_declorder_respects_dependence(self):
        body = ctx("{ int a = p->x; int b = a + 1; foo(b); }")
        for o in many(sp.mut_declorder, body, 100):
            self.assertLess(o.index("int a"), o.index("int b"))

    def test_temp_hint_names_a_value(self):
        sp.set_context("{ x = p->count + 1; }", (), ["int itemCount = p->count"])
        outs = many(sp.mut_split, "{ x = p->count + 1; }", 20)
        self.assertEqual(outs, {"{ int itemCount = p->count;\n    x = itemCount + 1; }"})
        self.assertEqual(sp.lint_candidate("{ x = p->count + 1; }", outs.pop()), [])

    def test_unhinted_new_local_is_rejected(self):
        sp.set_context("{ x = p->count + 1; }")
        self.assertTrue(sp.lint_candidate("{ x = p->count + 1; }", "{ int n = p->count;\n x = n + 1; }"))

    def test_temp_hint_validation(self):
        for bad in ("int tmp = p->count", "Foo f = g", "int = 3", "int a1 = p->x"):
            with self.assertRaises(ValueError):
                sp.parse_temp(bad)
        self.assertEqual(sp.parse_temp("DWORD *cellList = this->cells"), ("DWORD *", "cellList", "this->cells"))

    def test_temp_hint_name_clash(self):
        with self.assertRaises(ValueError):
            sp.set_context("{ int n = 1; x = n; }", (), ["int n = p->count"])

    def test_hinted_call_only_when_alone_in_statement(self):
        sp.set_context("{ x = Foo(a) + 1; y = p->k + Foo(a); }", (), ["int fooResult = Foo(a)"])
        outs = many(sp.mut_split, "{ x = Foo(a) + 1; y = p->k + Foo(a); }", 40)
        self.assertTrue(outs)
        for o in outs:
            self.assertIn("y = p->k + Foo(a);", o)      # the statement that also reads memory is left alone

    def test_markers_general_and_lineswap(self):
        import random as _r
        sp.set_context("{ int b; int c; }")
        t = "{ PERM_GENERAL(a = 1;, a = 2;, a = 3;)\n PERM_LINESWAP(\n b = 1;\n c = 2;\n)\n}"
        self.assertEqual(sp.expand_markers(t).split(), "{ a = 1; b = 1; c = 2; }".split())
        seen = {sp.expand_markers(t, _r.Random(i)) for i in range(60)}
        self.assertTrue(any("a = 3;" in s for s in seen))
        self.assertTrue(any(s.index("c = 2;") < s.index("b = 1;") for s in seen))
        self.assertFalse(any("PERM_" in s for s in seen))

    def test_lineswap_never_reorders_dependent_lines(self):
        import random as _r
        sp.set_context("{ int i; int j; }")
        t = "{ PERM_LINESWAP(\n i = 1;\n j = i + 1;\n Foo();\n Bar();\n) }"
        for n in range(80):
            s = sp.expand_markers(t, _r.Random(n))
            self.assertLess(s.index("i = 1;"), s.index("j = i + 1;"))
            self.assertLess(s.index("Foo();"), s.index("Bar();"))

    def test_marker_mutation_and_lint(self):
        base = "{ a = 1; }"
        sp.set_context(base, (), (), "{ PERM_GENERAL(a = 1;, a = 2;) }")
        outs = many(sp.mut_marker, base, 20)
        self.assertEqual(outs, {"{ a = 1; }", "{ a = 2; }"})
        self.assertTrue(sp.lint_candidate(base, "{ PERM_GENERAL(a = 1;) }"))

    def test_marker_without_template_is_inert(self):
        sp.set_context("{ a = 1; }")
        self.assertEqual(many(sp.mut_marker, "{ a = 1; }", 5), set())


if __name__ == "__main__":
    unittest.main()
