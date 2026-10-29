#!/usr/bin/env python3
# Provenance: original. Self-tests for trivgen (need the pinned retail image; the compile test needs the VC6 toolchain).
import os
import sys
import tempfile
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import emit  # noqa: E402
import gen  # noqa: E402
import lift  # noqa: E402
import patterns  # noqa: E402
import x86  # noqa: E402


def body(addr, var=None):
    sp = lift.lift(addr)
    return emit.emit(sp, var or emit.variants(sp)[0]).body


class OperandParsing(unittest.TestCase):
    def test_memory_forms(self):
        i = x86.parse_insn(0, "00", "mov eax,DWORD PTR [ecx+0x10]")
        self.assertEqual((i.ops[1].base, i.ops[1].disp, i.ops[1].size), ("ecx", 0x10, 4))
        i = x86.parse_insn(0, "00", "mov DWORD PTR ds:0x887720,0x0")
        self.assertTrue(i.ops[0].absolute())
        self.assertEqual(i.ops[0].disp, 0x887720)
        i = x86.parse_insn(0, "00", "mov eax,DWORD PTR [edx+ecx*8+0x4]")
        self.assertEqual((i.ops[1].index, i.ops[1].scale, i.ops[1].disp), ("ecx", 8, 4))


class RetailShapes(unittest.TestCase):
    """Addresses whose bytes are fixed in the pinned image."""

    def test_static_init_fp(self):
        sp = lift.lift(0x410640)
        self.assertEqual(patterns.pattern_of(sp), "static-init-fp")
        self.assertIn("DAT_00887728 = DAT_008876D8 / DAT_007E1FC0;", body(0x410640))

    def test_static_init_stores_keep_order_and_void(self):
        text = body(0x4107E0)
        self.assertTrue(text.startswith("void __cdecl FUN_004107E0()"))
        self.assertLess(text.index("DAT_00887720 = 0;"), text.index("DAT_00887718 = 0x80;"))

    def test_empty(self):
        self.assertEqual(patterns.pattern_of(lift.lift(0x41B900)), "empty")

    def test_member_getter_is_const_member_with_unknown_field(self):
        sp = lift.lift(0x41CFA0)
        out = emit.emit(sp, emit.variants(sp)[0])
        self.assertEqual(out.kind, "member")
        self.assertIn("unknown_", out.body)
        self.assertIn(" const", out.body)

    def test_variants_dedupe_by_body(self):
        sp = lift.lift(0x41B900)
        bodies = {emit.emit(sp, v).body for v in emit.variants(sp)}
        self.assertEqual(len(bodies), 1)


class Layout(unittest.TestCase):
    def test_gap_and_assert(self):
        sp = lift.lift(0x41CFA0)
        out = emit.emit(sp, emit.variants(sp)[0])
        b = gen.Bin("trivial_tu000_test_methods", "core")
        b.add(out)
        h = b.header_text(None)
        self.assertIn("GG_STATIC_ASSERT(offsetof(", h)
        self.assertIn("char unknown_00[0x", h)

    def test_overlap_is_refused(self):
        v = emit.View("X")
        v.fields[0] = emit.Field(0, 4)
        v.fields[2] = emit.Field(2, 4)
        self.assertTrue(gen.overlaps(v))


@unittest.skipUnless(os.environ.get("TRIVGEN_COMPILE_TEST"), "set TRIVGEN_COMPILE_TEST=1 (needs worktree + toolchain)")
class VerifierRejectsWrongCode(unittest.TestCase):
    def test_wrong_constant_is_not_exact(self):
        import verify
        d = verify.WT / "match" / "core"
        stem = "trivial_tu997_selftest_methods"
        (d / f"{stem}.cpp").write_text("int __cdecl FUN_004107E0() { return 7; }\n")
        try:
            obj, errs, _ = verify.compile_bin(f"match/core/{stem}.cpp")
            self.assertIsNotNone(obj)
            r = verify.check_function(obj, 0x4107E0, 0x1a, Path(tempfile.gettempdir()) / "x.json")
            self.assertFalse(r["ok"])
        finally:
            (d / f"{stem}.cpp").unlink()


if __name__ == "__main__":
    unittest.main()
