# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original project tooling; synthetic instruction fixtures only (no retail bytes).
import os
import sys
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import shape_classify as sc  # noqa: E402


def mk(lines, start=0x401000):
    out, a = [], start
    for t in lines:
        out.append((a, 3, t))
        a += 3
    return out


def ctx(**kw):
    strings = {0x7E2000: "str", 0x7E2010: "file", 0x7E2020: "str"}
    base = dict(is_string=strings.get, writable=lambda va: 0x812000 <= va < 0x900000,
                imports={0x7E1100: "DefWindowProcA", 0x7E1104: "SendMessageA"},
                status={0x500000: "matched", 0x500010: "partial"}, vtables={0x7E5000})
    base.update(kw)
    return sc.Ctx(**base)


def feat(lines, **kw):
    return sc.features(mk(lines), ctx(**kw))


class Idioms(unittest.TestCase):
    def test_assert_site(self):
        f = feat(["push 0x7e2000", "push 0x123", "push 0x7e2010", "call 0x4a0000", "ret"])
        self.assertEqual(f["assert_site"], 1)
        self.assertEqual(f["str_push"], 2)

    def test_no_assert_without_line_or_call(self):
        self.assertEqual(feat(["push 0x7e2010", "ret"])["assert_site"], 0)

    def test_rtti_check(self):
        f = feat(["call DWORD PTR [eax+0x2c]", "cmp eax,0x7", "jne 0x401100"])
        self.assertEqual(f["rtti_check"], 1)
        self.assertEqual(feat(["call DWORD PTR [eax+0x30]", "cmp eax,0x7"])["rtti_check"], 0)

    def test_vector_add_and_remove(self):
        add = ["mov eax,DWORD PTR [esi+0x10]", "cmp eax,DWORD PTR [esi+0x8]", "jl 0x401100",
               "call 0x4a0000", "inc DWORD PTR [esi+0x10]"]
        self.assertEqual(feat(add)["vec_add"], 1)
        rem = ["cmp eax,DWORD PTR [esi+0x10]", "jge 0x401100", "dec DWORD PTR [esi+0x10]"]
        self.assertEqual(feat(rem)["vec_remove"], 1)

    def test_counted_loop(self):
        lines = ["inc esi", "cmp esi,DWORD PTR [edi+0x10]", "jl 0x401000"]
        f = feat(lines)
        self.assertEqual((f["counted_loop"], f["loop"]), (1, 1))

    def test_timer_read(self):
        f = feat(["mov eax,ds:0x8a0000", "mov ecx,DWORD PTR [esi+0x24]", "sub eax,ecx"])
        self.assertEqual(f["cdtimer_read"], 1)

    def test_coord_cell_shifts(self):
        self.assertEqual(feat(["sar eax,0x8", "shl ecx,0x8", "shl edx,0x4"])["coord_cell"], 2)

    def test_callee_split(self):
        f = feat(["call 0x500000", "call 0x500010", "call 0x500020", "call 0x500000"])
        self.assertEqual((f["callee_distinct"], f["callee_matched"], f["callee_partial"], f["callee_unmatched"]),
                         (3, 1, 1, 1))
        self.assertEqual(f["call_direct"], 4)

    def test_jump_table_member(self):
        f = feat(["mov eax,DWORD PTR [esi+0x30]", "cmp eax,0x5", "ja 0x401100", "jmp DWORD PTR [eax*4+0x401200]"])
        self.assertEqual((f["jump_table"], f["jump_table_member"], f["jump_table_max_cases"]), (1, 1, 6))

    def test_x87(self):
        self.assertEqual(feat(["fld DWORD PTR [esi]", "fmul st,st(1)", "mov eax,1"])["x87"], 2)

    def test_vtable_store(self):
        self.assertEqual(feat(["mov DWORD PTR [esi],0x7e5000"])["vtable_store"], 1)


class Classes(unittest.TestCase):
    def cls(self, lines, xcu=False, **kw):
        return sc.classify(feat(lines, **kw), xcu)[0]

    def test_ini_reader(self):
        lines = []
        for i in range(10):
            lines += ["push 0x7e2000", "call 0x5276d0"]
        self.assertEqual(self.cls(lines), "ini-reader")

    def test_static_init_by_table(self):
        self.assertEqual(self.cls(["ret"], xcu=True), "static-initialiser")

    def test_static_init_by_body(self):
        lines = [f"mov DWORD PTR ds:0x8120{i:02x},0x0" for i in range(12)]
        self.assertEqual(self.cls(lines), "static-initialiser")

    def test_ctor(self):
        self.assertEqual(self.cls(["mov DWORD PTR [esi],0x7e5000", "ret"]), "ctor-dtor")

    def test_window_proc(self):
        lines = ["call DWORD PTR ds:0x7e1100"] + ["cmp eax,0x100", "cmp eax,0x111"]
        self.assertEqual(self.cls(lines), "window-proc")

    def test_lookup(self):
        lines = []
        for i in range(8):
            lines += [f"mov eax,0x7e20{i:02x}", "ret"]
        self.assertEqual(self.cls(lines), "string-lookup")

    def test_state_machine(self):
        lines = ["mov eax,DWORD PTR [esi+0x30]", "cmp eax,0x5", "ja 0x401100", "jmp DWORD PTR [eax*4+0x401200]"]
        self.assertEqual(self.cls(lines), "state-machine")

    def test_math(self):
        self.assertEqual(self.cls(["fld DWORD PTR [esi]", "fmul st,st(1)", "fstp DWORD PTR [esi]", "mov eax,1"]),
                         "math")

    def test_generic(self):
        self.assertEqual(self.cls(["mov eax,1", "ret"]), "generic")

    def test_generation_score_orders_by_class_and_ratio(self):
        hi = feat(["call 0x500000"])
        lo = feat(["call 0x500020"])
        self.assertGreater(sc.gen_score("ini-reader", hi), sc.gen_score("ini-reader", lo))
        self.assertGreater(sc.gen_score("ini-reader", hi), sc.gen_score("generic", hi))

    def test_record_and_tsv(self):
        r = sc.record(0x401000, 1100, mk(["mov DWORD PTR [esi],0x7e5000", "ret"]), ctx(), rtti="FooClass")
        self.assertEqual((r["addr"], r["primary"], r["rtti"]), ("0x401000", "ctor-dtor", "FooClass"))
        tsv = sc.worklist_tsv([r]).splitlines()
        self.assertEqual(len(tsv), 2)
        self.assertEqual(tsv[1].split("\t")[:3], ["0x401000", "1100", "ctor-dtor"])
        self.assertEqual(sc.summarise([r])["ctor-dtor"]["count"], 1)


if __name__ == "__main__":
    unittest.main()
