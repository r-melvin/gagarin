#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original
"""Tests for idiom_lift.py. Fixtures are hand-written pseudo-C in the Ghidra dialect with
synthetic addresses, names and layouts; no binary, Ghidra session or retail text is needed."""
import tempfile
import unittest
from pathlib import Path

import idiom_lift as L

HEADER = """
#include "../_rt/gg_static_assert.h"
class BaseThing {
public:
    virtual ~BaseThing();
    virtual int vf_11();           // 11
    int Health;                    // +0x08
};
GG_STATIC_ASSERT(offsetof(BaseThing, Health) == 0x08);
class WidgetClass : public BaseThing {
public:
    virtual bool vf_17(int x);     // 17
    char ID[24];                   // +0x24
    int Target;
    double Ratio;
    float Scale;
    DynamicVectorClass<int> Items;
    CDTimerClass Timer;
    WidgetClass* Next;
};
GG_STATIC_ASSERT(offsetof(WidgetClass, ID) == 0x24);
GG_STATIC_ASSERT(offsetof(WidgetClass, Target) == 0x40);
GG_STATIC_ASSERT(offsetof(WidgetClass, Ratio) == 0x48);
GG_STATIC_ASSERT(offsetof(WidgetClass, Scale) == 0x50);
GG_STATIC_ASSERT(offsetof(WidgetClass, Items) == 0x60);
GG_STATIC_ASSERT(offsetof(WidgetClass, Timer) == 0x80);
GG_STATIC_ASSERT(offsetof(WidgetClass, Next) == 0x90);
"""


class FakeNames(L.Names):
    def __init__(self, funcs=None, globs=None):
        super().__init__(data=Path("/nonexistent"), match_root=Path("/nonexistent"))
        self._funcs = funcs or {}
        self._globs = globs or {}
        self._loaded = self._globals_loaded = True

    def func(self, addr):
        sym = self._funcs.get(addr)
        return L.demangle(sym) if sym else None

    def glob(self, addr):
        return self._globs.get(addr)


class FakeReader(L.Reader):
    def __init__(self, blobs):
        super().__init__(use_ghidra=False)
        self.blobs = blobs

    def read(self, addr, n=160):
        for base, data in self.blobs.items():
            if base <= addr < base + len(data):
                return data[addr - base:addr - base + n]
        return None


def make_ctx(funcs=None, globs=None, blobs=None, cls="WidgetClass", addr=None, rtti=None):
    tmp = tempfile.TemporaryDirectory()
    root = Path(tmp.name)
    (root / "w.h").write_text(HEADER)
    lay = L.Layouts(root=root)
    ctx = L.Ctx(names=FakeNames(funcs, globs), layouts=lay, reader=FakeReader(blobs or {}), cls=cls, addr=addr,
                rtti_names=rtti)
    ctx._tmp = tmp
    return ctx


def lift(body, passes=None, **kw):
    """Wrap `body` as a thiscall function and run the requested passes."""
    sig = kw.pop("sig", "uint __thiscall FUN_00500000(void *this,int param_1)")
    decls = kw.pop("decls", "")
    ctx = make_ctx(**kw)
    text = "\n%s\n\n{\n%s\n  \n%s\n}\n" % (sig, decls, body)
    doc, out = L.lift_text(text, ctx, passes)
    return out, ctx


class DemangleTests(unittest.TestCase):
    def test_member(self):
        d = L.demangle("?ReadInteger@CCINIClass@@QAEHPBD0H@Z")
        self.assertEqual((d["cls"], d["name"], d["kind"], d["ret"]), ("CCINIClass", "ReadInteger", "member", "int"))
        self.assertEqual(d["args"], ["const char*", "const char*", "int"])

    def test_virtual_bool_and_class_pointer(self):
        d = L.demangle("?vf_25@TiberiumClass@@UAE_NPAVCCINIClass@@@Z")
        self.assertEqual((d["kind"], d["ret"], d["args"]), ("virtual", "bool", ["CCINIClass*"]))

    def test_static_free_ctor_template(self):
        self.assertEqual(L.demangle("?Foo@Bar@@SAHH@Z")["kind"], "static")
        d = L.demangle("?Foo@@YAXH@Z")
        self.assertEqual((d["kind"], d["cls"], d["ret"]), ("free", "", "void"))
        d = L.demangle("??0Foo@@QAE@XZ")
        self.assertEqual((d["name"], d["cls"]), ("Foo", "Foo"))
        d = L.demangle("?AddItem@?$DynamicVectorClass@PAVFoo@@@@QAE_NAAPAVFoo@@@Z")
        self.assertEqual(d["cls"], "DynamicVectorClass<Foo*>")

    def test_unknown_returns_none(self):
        self.assertIsNone(L.demangle("_notmangled"))


class TextHelperTests(unittest.TestCase):
    def test_split_top_respects_nesting_and_strings(self):
        self.assertEqual(L.split_top('a, f(b, c), "x,y", (d, e)'), ["a", "f(b, c)", '"x,y"', "(d, e)"])

    def test_match_close_skips_comments(self):
        self.assertEqual(L.match_close("{ /* it's } */ x }", 0, "{", "}"), 17)


class VcallTests(unittest.TestCase):
    def test_slot_on_this_uses_class_slot_name(self):
        out, ctx = lift("  uVar1 = (**(code **)(*(int *)this + 0x44))(this,5);", ["vcalls"], decls="  uint uVar1;")
        self.assertIn("this->vf_17(5)", out)
        self.assertEqual(ctx.stats.sites["vcalls"], 1)

    def test_slot_on_field_receiver(self):
        out, _ = lift("  (**(code **)(*(int *)*(int *)((int)this + 0x40) + 0x2c))(*(int *)((int)this + 0x40));",
                      ["vcalls", "fields", "cleanup"])
        self.assertIn("this->Target->vf_11()", out)

    def test_missing_receiver_arg_is_implicit_this_and_marked(self):
        out, ctx = lift("  (**(code **)(*(int *)this + 8))(3,0);", ["vcalls"])
        self.assertIn("this->vf_2(3, 0)", out)
        self.assertEqual(ctx.stats.marks["vcalls.implicit_this"], 1)


class FieldTests(unittest.TestCase):
    def test_base_and_derived_fields(self):
        out, ctx = lift("  *(int *)((int)this + 8) = *(int *)((int)this + 0x40);", ["fields"])
        self.assertIn("this->Health = this->Target;", out)
        self.assertEqual(ctx.stats.sites["fields"], 2)

    def test_array_member_decays_and_scalar_takes_address(self):
        out, _ = lift("  puVar1 = (byte *)((int)this + 0x24);\n  puVar2 = (int *)((int)this + 0x40);", ["fields"],
                      decls="  byte *puVar1;\n  int *puVar2;")
        self.assertIn("puVar1 = this->ID;", out)
        self.assertIn("puVar2 = &this->Target;", out)

    def test_nested_member_into_builtin_type(self):
        out, _ = lift("  iVar1 = *(int *)((int)this + 0x88);\n  iVar2 = *(int *)((int)this + 0x70);", ["fields"],
                      decls="  int iVar1;\n  int iVar2;")
        self.assertIn("iVar1 = this->Timer.TimeLeft;", out)
        self.assertIn("iVar2 = this->Items.Count;", out)

    def test_unmapped_offset_gets_unknown_name_and_is_reported(self):
        out, ctx = lift("  *(int *)((int)this + 0x1c) = 1;", ["fields"])
        self.assertIn("this->unknown_1C = 1;", out)
        self.assertEqual(ctx.unmapped["WidgetClass"], {0x1C})
        text = L.build_output(L.Doc("\nint f(void)\n{\n}\n"), out, ctx)
        self.assertIn("offsets with no layout field in WidgetClass: 0x1C", text)

    def test_pointer_field_type_follows_into_pointee_class(self):
        out, _ = lift("  *(int *)(*(int *)((int)this + 0x90) + 8) = 7;", ["fields"])
        self.assertIn("this->Next->Health = 7;", out)

    def test_no_class_leaves_text_alone(self):
        out, ctx = lift("  *(int *)((int)this + 8) = 1;", ["fields"], cls=None)
        self.assertIn("this + 8", out)
        self.assertEqual(ctx.stats.marks["fields.no_class"], 1)


class SymbolTests(unittest.TestCase):
    FUNCS = {0x500100: "?Poke@WidgetClass@@QAEXH@Z", 0x500200: "?Twice@Util@@SAHH@Z",
             0x500300: "?Free@@YAXH@Z", 0x500400: "?vf_17@WidgetClass@@UAE_NH@Z"}

    def test_member_static_free_and_unknown_calls(self):
        out, ctx = lift("  FUN_00500100(this,4);\n  iVar1 = FUN_00500200(3);\n  FUN_00500300(1);\n  FUN_00599999(this);",
                        ["symbols"], funcs=self.FUNCS, decls="  int iVar1;")
        self.assertIn("this->Poke(4);", out)
        self.assertIn("Util::Twice(3)", out)
        self.assertIn("Free(1);", out)
        self.assertIn("FUN_00599999(this);", out)
        self.assertEqual(ctx.stats.sites["symbols.calls"], 3)
        self.assertEqual(ctx.stats.marks["symbols.unnamed_calls"], 1)

    def test_direct_call_of_own_virtual_is_qualified(self):
        out, _ = lift("  FUN_00500400(this,1);", ["symbols"], funcs=self.FUNCS)
        self.assertIn("WidgetClass::vf_17(1);", out)

    def test_stack_object_receiver_becomes_dot_call(self):
        out, _ = lift("  FUN_00500100(&local_10,1);", ["symbols"], funcs=self.FUNCS)
        self.assertIn("local_10.Poke(1);", out)

    def test_nested_calls_rewrite_inside_out(self):
        out, _ = lift("  FUN_00500100(this,FUN_00500200(2));", ["symbols"], funcs=self.FUNCS)
        self.assertIn("this->Poke(Util::Twice(2));", out)

    def test_globals_by_name_and_fallback(self):
        out, ctx = lift("  iVar1 = DAT_00a8ed84 - DAT_00b00000;", ["symbols"], globs={0xA8ED84: "CurrentFrame"},
                        decls="  int iVar1;")
        self.assertIn("CurrentFrame - DAT_00B00000", out)
        self.assertEqual(ctx.stats.sites["symbols.globals"], 1)


class StringTests(unittest.TestCase):
    def test_s_label_and_char_cast_dat(self):
        blobs = {0x900000: b"Spread\0,\0\0"}
        out, ctx = lift('  f((byte *)s_Spread_00900000, (byte *)&DAT_00900007);', ["strings"], blobs=blobs)
        self.assertIn('f("Spread", STR_00900007 /* "," */);', out)
        self.assertEqual(ctx.stats.sites["strings"], 2)

    def test_unreadable_string_left_and_counted(self):
        out, ctx = lift("  f(s_Gone_00900100);", ["strings"])
        self.assertIn("s_Gone_00900100", out)
        self.assertEqual(ctx.stats.marks["strings.unread"], 1)


class IniTests(unittest.TestCase):
    FUNCS = {0x500500: "?ReadInteger@CCINIClass@@QAEHPBD0H@Z",
             0x500510: "?ReadDouble@CCINIClass@@QAENPBD0N@Z",
             0x500520: "?ReadBool@CCINIClass@@QAE_NPBD0_N@Z"}

    def body(self):
        return ("  uVar2 = FUN_00500500(param_1,(char *)((int)this + 0x24),s_Power_00900000,*(undefined4 *)((int)this + 0x40));\n"
                "  *(undefined4 *)((int)this + 0x40) = uVar2;\n"
                "  fVar3 = FUN_00500510(param_1,(char *)((int)this + 0x24),s_Ratio_00900010,*(double *)((int)this + 0x48));\n"
                "  *(double *)((int)this + 0x48) = (double)fVar3;\n"
                "  fVar3 = FUN_00500510(param_1,(char *)((int)this + 0x24),s_Scale_00900020,(double)*(float *)((int)this + 0x50));\n"
                "  *(float *)((int)this + 0x50) = (float)fVar3;\n"
                "  iVar4 = FUN_00500500(param_1,(char *)((int)this + 0x24),s_Other_00900030,5);\n"
                "  *(int *)((int)this + 0x40) = iVar4;")

    def run_ini(self):
        blobs = {0x900000: b"Power\0\0\0\0\0\0\0\0\0\0\0Ratio\0\0\0\0\0\0\0\0\0\0\0Scale\0\0\0\0\0\0\0\0\0\0\0Other\0"}
        return lift(self.body(), None, funcs=self.FUNCS, blobs=blobs,
                    decls="  uint uVar2;\n  float10 fVar3;\n  int iVar4;",
                    sig="uint __thiscall FUN_00500000(void *this,int param_1)")

    def test_canonical_reader_lines(self):
        out, ctx = self.run_ini()
        self.assertIn('this->Target = param_1->ReadInteger(this->ID, "Power", this->Target);', out)
        self.assertIn('this->Ratio = param_1->ReadDouble(this->ID, "Ratio", this->Ratio);', out)
        self.assertGreaterEqual(ctx.stats.sites["ini"], 2)

    def test_float_field_keeps_its_cast(self):
        out, _ = self.run_ini()
        self.assertRegex(out, r'this->Scale = \(float\)param_1->ReadDouble\(this->ID, "Scale"')

    def test_non_field_default_is_not_counted_as_idiom(self):
        out, ctx = self.run_ini()
        self.assertIn('"Other", 5)', out)
        self.assertEqual(ctx.stats.marks["ini.other_default"], 1)


class VectorTests(unittest.TestCase):
    ADD = ("  iVar1 = *(int *)((int)this + 0x68);\n"
           "  if ((*(int *)((int)this + 0x70) < iVar1) ||\n"
           "     ((((*(char *)((int)this + 0x6d) != '\\0' || (iVar1 == 0)) &&\n"
           "       (0 < *(int *)((int)this + 0x74))) &&\n"
           "      (cVar2 = (**(code **)(*(int *)((int)this + 0x60) + 8))((int)this + 0x60,*(int *)((int)this + 0x74) + iVar1,0),\n"
           "      cVar2 != '\\0')))) {\n"
           "    iVar3 = *(int *)((int)this + 0x70);\n"
           "    *(int *)((int)this + 0x70) = iVar3 + 1;\n"
           "    *(int *)(*(int *)((int)this + 100) + iVar3 * 4) = param_1;\n"
           "  }")
    DECLS = "  int iVar1;\n  char cVar2;\n  int iVar3;"

    def test_additem_expansion(self):
        out, ctx = lift(self.ADD, ["vcalls", "fields", "vector"], decls=self.DECLS)
        self.assertIn("this->Items.AddItem(param_1);", out)
        self.assertNotIn("CapacityIncrement", out)
        self.assertEqual(ctx.stats.sites["vector.additem"], 1)

    def test_additem_half_match_is_marked(self):
        broken = self.ADD.replace("    *(int *)(*(int *)((int)this + 100) + iVar3 * 4) = param_1;\n", "    foo();\n")
        out, ctx = lift(broken, ["vcalls", "fields", "vector"], decls=self.DECLS)
        self.assertIn("LIFT? AddItem-shaped condition", out)
        self.assertEqual(ctx.stats.marks["vector.additem_partial"], 1)

    def test_delete_shift_loop(self):
        body = ("  *(int *)((int)this + 0x70) = *(int *)((int)this + 0x70) + -1;\n"
                "  for (iVar1 = param_1; iVar1 < *(int *)((int)this + 0x70); iVar1 = iVar1 + 1) {\n"
                "    *(int *)(*(int *)((int)this + 100) + iVar1 * 4) = *(int *)(*(int *)((int)this + 100) + iVar1 * 4 + 4);\n"
                "  }")
        out, ctx = lift(body.replace("+ -1", "- 1"), ["fields", "vector"], decls="  int iVar1;")
        self.assertIn("this->Items.Delete(param_1);", out)
        self.assertEqual(ctx.stats.sites["vector.delete_remove"], 1)

    def test_counted_loop_and_element_index(self):
        body = ("  iVar1 = 0;\n  if (0 < *(int *)((int)this + 0x70)) {\n    do {\n"
                "      iVar2 = *(int *)(*(int *)((int)this + 100) + iVar1 * 4);\n"
                "      use(iVar2);\n      iVar1 = iVar1 + 1;\n    } while (iVar1 < *(int *)((int)this + 0x70));\n  }")
        out, ctx = lift(body, ["fields", "cleanup", "vector"], decls="  int iVar1;\n  int iVar2;")
        self.assertIn("for (int iVar1 = 0; iVar1 < this->Items.Count; iVar1++) {", out)
        self.assertIn("use(this->Items.Items[iVar1]);", out)
        self.assertEqual(ctx.stats.sites["vector.count_loops"], 1)


class RttiTests(unittest.TestCase):
    def test_whatami_comparison_gets_name_comment(self):
        out, _ = lift("  if (this->vf_11() == 0x1c) { go(); }", ["rtti"], rtti={0x1C: "Building"})
        self.assertIn("this->vf_11() == 0x1c /* AbstractType Building */", out)

    def test_number_kept_without_table(self):
        out, ctx = lift("  if (p->vf_11() != 5) { go(); }", ["rtti"], rtti={})
        self.assertIn("p->vf_11() != 5 /* AbstractType 5 */", out)


class TimerTests(unittest.TestCase):
    GET = ("  iVar1 = *(int *)((int)this + 0x88);\n"
           "  if (*(int *)((int)this + 0x80) != -1) {\n"
           "    iVar2 = DAT_00a8ed84 - *(int *)((int)this + 0x80);\n"
           "    if (iVar2 < iVar1) {\n      iVar1 = iVar1 - iVar2;\n    }\n    else {\n      iVar1 = 0;\n    }\n  }")
    D = "  int iVar1;\n  int iVar2;"

    def test_get_time_left(self):
        out, ctx = lift(self.GET, ["fields", "symbols", "timer"], decls=self.D, globs={0xA8ED84: "CurrentFrame"})
        self.assertIn("iVar1 = this->Timer.GetTimeLeft();", out)
        self.assertEqual(ctx.stats.sites["timer"], 1)

    def test_start(self):
        out, _ = lift("  *(int *)((int)this + 0x80) = DAT_00a8ed84;\n  *(int *)((int)this + 0x88) = param_1;",
                      ["fields", "symbols", "timer"], globs={0xA8ED84: "CurrentFrame"})
        self.assertIn("this->Timer.Start(param_1);", out)

    def test_partial_shape_is_marked(self):
        out, ctx = lift("  iVar1 = DAT_00a8ed84 - *(int *)((int)this + 0x80);", ["fields", "symbols", "timer"],
                        decls=self.D, globs={0xA8ED84: "CurrentFrame"})
        self.assertIn("LIFT? CDTimerClass inline", out)
        self.assertEqual(ctx.stats.marks["timer.partial"], 1)


class GhidraArtefactTests(unittest.TestCase):
    def test_concat_sub_zext(self):
        out, _ = lift("  return CONCAT31((int3)((uint)iVar1 >> 8),1);", ["ghidra"], decls="  int iVar1;")
        self.assertIn("return 1;", out)
        out, _ = lift("  x = SUB41(y,0) + ZEXT14(z);", ["ghidra"])
        self.assertIn("(unsigned char)y + (unsigned int)z", out)

    def test_concat44_is_kept(self):
        out, ctx = lift("  x = CONCAT44(a,b);", ["ghidra"])
        self.assertIn("CONCAT44(a,b)", out)
        self.assertEqual(ctx.stats.marks["ghidra.concat_kept"], 1)

    def test_bool_return_pattern(self):
        body = "  uVar1 = FUN_00500100(this,1);\n  if ((char)uVar1 == '\\0') {\n    return uVar1 & 0xffffff00;\n  }\n  return 1;"
        out, ctx = lift(body, ["ghidra", "symbols", "cleanup"], decls="  uint uVar1;",
                        funcs={0x500100: "?Check@WidgetClass@@QAE_NH@Z"})
        self.assertIn("if (!this->Check(1)) {", out)
        self.assertIn("return false;", out)
        self.assertIn("return true;", out)

    def test_zero_pointer_casts(self):
        out, _ = lift("  p = (byte *)0x0;\n  q = (undefined4 *)0x0;", ["ghidra"])
        self.assertIn("p = 0;", out)
        self.assertIn("q = 0;", out)

    def test_do_while_to_for_with_guard(self):
        body = ("  iVar1 = 0;\n  if (0 < param_1) {\n    do {\n      work(iVar1);\n      iVar1 = iVar1 + 1;\n"
                "    } while (iVar1 < param_1);\n  }\n  done();")
        out, ctx = lift(body, ["cleanup"], decls="  int iVar1;")
        self.assertIn("for (int iVar1 = 0; iVar1 < param_1; iVar1++) {", out)
        self.assertIn("work(iVar1);", out)
        self.assertNotIn("do {", out)
        self.assertEqual(ctx.stats.sites["ghidra.loops_to_for"], 1)

    def test_reverse_loop_and_comma_while(self):
        body = ("  iVar1 = param_1;\n  while (iVar1 = iVar1 + -1, -1 < iVar1) {\n    work(iVar1);\n  }")
        out, _ = lift(body, ["cleanup"], decls="  int iVar1;")
        self.assertIn("for (int iVar1 = param_1 - 1; iVar1 >= 0; iVar1--) {", out)

    def test_do_with_continue_is_kept(self):
        body = ("  iVar1 = 0;\n  do {\n    if (a) {\n      continue;\n    }\n    iVar1 = iVar1 + 1;\n  } while (iVar1 < 4);")
        out, ctx = lift(body, ["cleanup"], decls="  int iVar1;")
        self.assertIn("do {", out)
        self.assertEqual(ctx.stats.marks["ghidra.loops_kept"], 1)

    def test_single_use_temporaries_collapse_but_multi_use_stay(self):
        body = ("  iVar1 = f(1);\n  g(iVar1);\n  iVar2 = f(2);\n  g(iVar2);\n  h(iVar2);")
        out, _ = lift(body, ["cleanup"], decls="  int iVar1;\n  int iVar2;")
        self.assertIn("g(f(1));", out)
        self.assertIn("iVar2 = f(2);", out)

    def test_temp_not_collapsed_when_value_is_read_again(self):
        body = "  iVar1 = f(1);\n  g(iVar1);\n  h(iVar1);"
        out, _ = lift(body, ["cleanup"], decls="  int iVar1;")
        self.assertIn("iVar1 = f(1);", out)

    def test_pure_alias_inlined(self):
        body = "  puVar1 = &this->ID;\n  a(puVar1);\n  b(puVar1);\n  c(puVar1);"
        out, ctx = lift(body, ["cleanup"], decls="  byte *puVar1;")
        self.assertIn("a(&this->ID);", out)
        self.assertEqual(ctx.stats.sites["ghidra.aliases_inlined"], 3)

    def test_pseudo_types_normalised(self):
        out, _ = lift("  x = (undefined4 *)p;\n  y = (uint)z;", ["cleanup"])
        self.assertIn("(int *)p", out)
        self.assertIn("(unsigned int)z", out)


class OtherIdiomTests(unittest.TestCase):
    def test_coord_shifts_are_annotated_not_rewritten(self):
        out, ctx = lift("  a = pt.X >> 8;\n  b = cell.Y << 8;", ["coord"])
        self.assertIn("pt.X >> 8 /* coord->cell */", out)
        self.assertIn("cell.Y << 8 /* cell->coord */", out)
        self.assertEqual(ctx.stats.sites["coord"], 2)

    def test_assert_site_comment(self):
        out, ctx = lift('  Assert_Fail("expr", "wwlib/vector.cpp", 142);', ["assert"])
        self.assertIn("assert site: wwlib/vector.cpp:142", out)
        self.assertEqual(ctx.stats.sites["assert"], 1)

    def test_static_initialiser_table(self):
        body = "\n".join("  DAT_00b00%03x = %s;" % (0x100 + 4 * k, v)
                         for k, v in enumerate(["1", "0xfffffffe", "3", "4", "5"]))
        body = body.replace("DAT_00b00104 = 0xfffffffe;\n", "DAT_00b00104 = 0xfffffffe;\n")
        out, ctx = lift(body, ["sinit"])
        self.assertIn("int DAT_00B00100[5] = {", out)
        self.assertIn("1, -2, 3, 4, 5", out)
        self.assertEqual(ctx.stats.sites["sinit"], 1)

    def test_short_store_run_is_not_a_table(self):
        out, ctx = lift("  DAT_00b00100 = 1;\n  DAT_00b00104 = 2;", ["sinit"])
        self.assertEqual(ctx.stats.sites.get("sinit", 0), 0)
        self.assertIn("DAT_00b00100 = 1;", out)


class OutputTests(unittest.TestCase):
    def test_header_lists_passes_and_signature_comes_from_symbol(self):
        funcs = {0x500000: "?Reset@WidgetClass@@QAE_NH@Z", 0x500100: "?Poke@WidgetClass@@QAEXH@Z"}
        ctx = make_ctx(funcs=funcs, addr=0x500000)
        text = "\nuint __thiscall FUN_00500000(void *this,int param_1)\n\n{\n  FUN_00500100(this,param_1);\n  return 1;\n}\n"
        doc, body = L.lift_text(text, ctx)
        out = L.build_output(doc, body, ctx, 0x500000)
        self.assertIn("//   symbols.calls", out)
        self.assertIn("// FUNCTION: GAMEMD 0x500000", out)
        self.assertIn("bool WidgetClass::Reset(int param_1)", out)
        self.assertIn("this->Poke(param_1);", out)
        self.assertIn("return true;", out)

    def test_implicit_this_flag(self):
        ctx = make_ctx()
        text = "\nvoid __thiscall FUN_00500000(void *this)\n\n{\n  *(int *)((int)this + 0x40) = 1;\n}\n"
        _, body = L.lift_text(text, ctx, implicit_this=True)
        self.assertIn("Target = 1;", body)
        self.assertNotIn("this->", body)

    def test_pass_selection(self):
        out, ctx = lift("  *(int *)((int)this + 0x40) = 1;", ["strings"])
        self.assertIn("(int)this + 0x40", out)
        self.assertNotIn("fields", ctx.stats.sites)

    def test_reindent_handles_switch_cases(self):
        body = L.reindent("switch (x) {\ncase 1:\nfoo();\nbreak;\ndefault:\nbar();\n}\nbaz();")
        self.assertEqual(body.split("\n")[1], "    case 1:")
        self.assertEqual(body.split("\n")[2], "        foo();")
        self.assertEqual(body.split("\n")[-1], "baz();")


if __name__ == "__main__":
    unittest.main()
