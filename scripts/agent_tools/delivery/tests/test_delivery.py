#!/usr/bin/env python3
"""Fast tests for the delivery tools (no compiler): python3 -m unittest tests.test_delivery -v
Synthetic packets are built in a temp dir; tree facts come from the main checkout's HEAD
(read-only). Compiler-backed behaviour is covered by tests/prove_rebase.py and prove_batch.py."""
import json
import os
import sys
import tempfile
import textwrap
import unittest

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.dirname(HERE))
# Tests use a neutral stand-in word; the real list is local-only (see landlib.load_forbid_re).
import tempfile as _tf
_wf = _tf.NamedTemporaryFile("w", suffix=".txt", delete=False)
_wf.write("zzforbidden\n"); _wf.close()
os.environ["GAG_FORBIDDEN_WORDS"] = _wf.name
import atexit as _ax
_ax.register(os.unlink, _wf.name)
import dlib as D  # noqa: E402
import pktlint  # noqa: E402
import landlib as L  # noqa: E402

TREE = None


def tree():
    global TREE
    if TREE is None:
        TREE = D.Tree(D.MAIN_REPO, "HEAD")
    return TREE


def mkpatch(files):
    """files: {path: new content} -> unified diff creating them."""
    out = []
    for path, text in files.items():
        lines = text.split("\n")
        out.append("diff --git a/%s b/%s\nnew file mode 100644\n--- /dev/null\n+++ b/%s\n@@ -0,0 +1,%d @@\n%s\n" % (
            path, path, path, len(lines), "\n".join("+" + l for l in lines)))
    return "".join(out)


HEADER = "// SPDX-License-Identifier: GPL-3.0-or-later\n// Provenance: own-binary-via-Ghidra\n"


COUNT = [0]


def packet(tmp, files, rows, readme=None, name=None):
    COUNT[0] += 1
    d = os.path.join(tmp, name or "pkt-test%d" % COUNT[0], "READY")
    os.makedirs(d)
    open(os.path.join(d, "patch.diff"), "w").write(mkpatch(files))
    json.dump(rows, open(os.path.join(d, "manifest_delta.json"), "w"))
    open(os.path.join(d, "README.md"), "w").write(readme or "Base: 935745b\n\n## Proposed commit message\n```\nMatch things\n\nCo-Authored-By: X <x@y>\n```\n")
    return L.Packet(d)


def lint(p, rules):
    lt = pktlint.Lint(p, tree(), D.MAIN_REPO)
    lt.run(False, 1, set(rules))
    return lt.findings


class Patch(unittest.TestCase):
    def test_split_added_new(self):
        ds = D.split_patch(mkpatch({"match/x/a.cpp": "l1\nl2", "match/x/b.h": "h"}))
        self.assertEqual([d.path for d in ds], ["match/x/a.cpp", "match/x/b.h"])
        self.assertTrue(ds[0].is_new and not ds[0].is_delete)
        self.assertEqual(ds[0].new_content(), "l1\nl2")
        self.assertEqual(ds[0].added_lines()[1], (2, "l2"))

    def test_rekey_delta_form(self):
        d = [{"addr": 4309024, "old_sym": "?a@@", "new": {"tu": "t", "addr": "0x41C020", "sym": "?b@@", "len": "0x9", "status": "matched", "pct": 100}}]
        ops = D.parse_delta(d)
        self.assertEqual(ops[0][0], "change")
        self.assertEqual(ops[0][2], {"sym": "?a@@"})
        self.assertEqual(D.normalise_delta(d)[0]["op"], "change")

    def test_derive_binding(self):
        self.assertEqual(D.derive_binding("?FUN_00655560@MapClass@@QAEXPAVTechnoClass@@UPoint2D@@@Z"), 0x655560)
        self.assertEqual(D.derive_binding("_DAT_00AC1B00"), 0xAC1B00)
        self.assertIsNone(D.derive_binding("?Reset@Obj_007B4620@@QAEXXZ"))
        self.assertIsNone(D.derive_binding("?IsControlledByHuman@HouseClass@@QBE_NXZ"))
        self.assertEqual(D.derive_binding("__imp__GetDlgCtrlID@4", {"GetDlgCtrlID": 0x7E1000}), 0x7E1000)


class TreeFacts(unittest.TestCase):
    def test_windows_and_canonical(self):
        t = tree()
        self.assertGreater(len(t.tu_windows()), 60)
        self.assertEqual(t.tu_for_addr(0x6F4A40), "match/combat/Techno.cpp")
        self.assertIn("HouseClass", t.canonical_classes())
        self.assertIn("match/_layout/house_class.h", t.canonical_classes()["HouseClass"])
        self.assertIn("AGENTS.md", t.paths)

    def test_rtti_kinds(self):
        k = D.rtti_kinds(D.MAIN_REPO)
        self.assertEqual(k.get("HouseClass"), "class")
        self.assertIn(k.get("CellStruct", "struct"), ("class", "struct"))


class LibraryFilter(unittest.TestCase):
    def test_marks_parse_column_zero_only(self):
        text = "// LIBRARY: GAMEMD 0x7c8962\n// WSOCK32!htonl\n  // LIBRARY: GAMEMD 0x401000\n// FUNCTION: GAMEMD 0x402000\n"
        self.assertEqual(D.library_marks(text), [(0x7C8962, 1)])
        self.assertEqual(D.body_claims(text), [(0x402000, 4)])

    def test_tree_library_claims_are_not_source_claims(self):
        t = tree()
        lib = t.library_claims()
        self.assertIn(0x7C8962, lib)
        self.assertIn("match/_rt/library_functions.h", lib[0x7C8962])
        self.assertNotIn(0x7C8962, t.claims())

    def test_dispatch_refilter_drops_library_rows(self):
        import dispatch
        rows = [{"addr": a} for a in ("0x7C8962", "0x401000", "0x402000", "0x403000")]
        keep, dropped = dispatch.refilter(rows, {0x401000: {}}, {0x402000: ["x.cpp"]}, {0x7C8962: ["lib.h"], 0x401000: ["lib.h"]})
        self.assertEqual([r["addr"] for r in keep], ["0x403000"])
        self.assertEqual(dropped, {"in_manifest": 1, "claimed": 1, "library": 1})


class LintRules(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.mkdtemp(prefix="dlt_", dir=D.SCRATCH)

    def rules(self, files, rows, which, readme=None):
        return [f for f in lint(packet(self.tmp, files, rows, readme), which) if f["rule"] in which]

    def test_words_and_steering(self):
        src = HEADER + textwrap.dedent("""
            // zzforbidden says so
            // FUNCTION: GAMEMD 0x401000
            int f() { volatile int x = 1; if (1) { } __asm { nop } return x; }
            """)
        f = self.rules({"match/x/a.cpp": src}, [], {"words", "steering"})
        kinds = sorted({(x["rule"], x["level"]) for x in f})
        self.assertIn(("words", "E"), kinds)
        self.assertIn(("steering", "E"), kinds)
        msgs = " ".join(x["msg"] for x in f)
        self.assertIn("inline-asm", msgs)
        self.assertIn("volatile on an access", msgs)
        self.assertIn("const-condition", msgs)

    def test_volatile_declaration_needs_evidence(self):
        src = HEADER + "// shared with the thread procedure started by CreateThread at 0x401234\nextern volatile int DAT_0087E878;\n"
        f = self.rules({"match/x/a.h": src}, [], {"steering"})
        self.assertEqual(f, [])
        src2 = HEADER + "\nextern volatile int DAT_0087E878;\n"
        f = self.rules({"match/x/b.h": src2}, [], {"steering"})
        self.assertEqual([x["level"] for x in f], ["W"])

    def test_views_canonical_and_classkey(self):
        src = HEADER + "class HouseClass {\npublic:\n int x;\n};\nstruct TechnoClass : public ObjectClass {\n};\n"
        f = self.rules({"match/x/view.h": src}, [], {"views", "classkey"})
        self.assertTrue(any(x["rule"] == "views" and "HouseClass" in x["msg"] and x["level"] == "E" for x in f))
        self.assertTrue(any(x["rule"] == "classkey" and "TechnoClass" in x["msg"] for x in f))

    def test_migrated_and_order_and_provenance(self):
        src = "// FUNCTION: GAMEMD 0x6F7930\nvoid b() {}\n// FUNCTION: GAMEMD 0x6F4A40\nvoid a() {}\n"
        rows = [{"tu": "match/combat/Techno2.cpp", "addr": "0x6F4A40", "sym": "?a@@YAXXZ", "len": "0x24", "status": "matched", "pct": 100},
                {"tu": "match/combat/Techno2.cpp", "addr": "0x6F7930", "sym": "?b@@YAXXZ", "len": "0x31", "status": "matched", "pct": 100}]
        f = self.rules({"match/combat/Techno2.cpp": src}, rows, {"migrated", "order", "provenance"})
        rules = {x["rule"] for x in f}
        self.assertEqual(rules, {"migrated", "order", "provenance"})
        mig = next(x for x in f if x["rule"] == "migrated")
        self.assertEqual(mig["dest"], "match/combat/Techno.cpp")

    def test_delta_rules(self):
        src = HEADER + "// FUNCTION: GAMEMD 0x401000\nvoid a() {}\n// FUNCTION: GAMEMD 0x6F4A40\nvoid q() {}\n"
        rows = [{"tu": "match/x/a.cpp", "addr": "0x401000", "sym": "?a@@YAXXZ", "len": "0x10", "status": "matched", "pct": 99.0, "_change": "x"},
                {"tu": "match/x/a.cpp", "addr": "0x400FF0", "sym": "?z@@YAXXZ", "len": "0x10", "status": "matched", "pct": 100},
                {"tu": "match/x/a.cpp", "addr": "0x6F4A40", "sym": "?q@@YAXXZ", "len": "0x24", "status": "matched", "pct": 100}]
        f = self.rules({"match/x/a.cpp": src}, rows, {"delta", "dupclaims"})
        msgs = " | ".join(x["msg"] for x in f if x["level"] == "E")
        self.assertIn("matched with pct 99.0", msgs)
        self.assertIn("not sorted", msgs)
        self.assertIn("no FUNCTION/SYNTHETIC/TEMPLATE body claim", msgs)      # 0x400FF0 has no body
        self.assertTrue(any("replaces an existing row" in x["msg"] for x in f))   # 0x6F4A40 is matched on main

    def test_sdd_rule(self):
        hand = HEADER + textwrap.dedent("""
            // FUNCTION: GAMEMD 0x401000
            void *Foo::Slot0(unsigned flags) { this->~Foo(); if (flags & 1) delete this; return this; }
            """)
        f = self.rules({"match/x/a.cpp": hand}, [], {"sdd"})
        self.assertTrue(any(x["level"] == "E" and "scalar deleting" in x["msg"] for x in f), f)
        named = HEADER + "// FUNCTION: GAMEMD 0x401000\nvoid *Foo::ScalarDeletingDtor(unsigned f) { return this; }\n"
        self.assertTrue(any(x["level"] == "E" for x in self.rules({"match/x/b.cpp": named}, [], {"sdd"})))
        view = HEADER + textwrap.dedent("""
            struct Obj_00401000 {
                // FUNCTION: GAMEMD 0x401000
                void *ScalarDeletingDtor(unsigned flags);
                // FUNCTION: GAMEMD 0x401010
                void *Other(unsigned flags);
            };
            """)
        f = self.rules({"match/x/c.h": view}, [], {"sdd"})
        self.assertEqual(sorted(x["level"] for x in f), ["E", "W"], f)
        ok = HEADER + "// FUNCTION: GAMEMD 0x401000\nvoid Foo::Reset(unsigned flags) { if (flags & 1) { Dirty = 0; } }\n"
        self.assertEqual(self.rules({"match/x/d.cpp": ok}, [], {"sdd"}), [])

    def test_flags_and_thisnull_rules(self):
        src = HEADER + "// VC6FLAGS: /MT /Ob2 /GR /Gy /DNDEBUG /Gr /O2 /c /nologo\n// FUNCTION: GAMEMD 0x401000\nint Foo::f() { return this && Bar; }\n"
        f = self.rules({"match/x/a.cpp": src}, [], {"flags", "thisnull"})
        self.assertEqual(sorted(x["rule"] for x in f), ["flags", "thisnull"], f)
        src = HEADER + "// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT\n// FUNCTION: GAMEMD 0x401000\nint Foo::f() { return Bar; }\n"
        self.assertEqual(self.rules({"match/x/b.cpp": src}, [], {"flags", "thisnull"}), [])

    def test_inits_rule(self):
        ini, src = D.init_addresses()
        if not ini:
            self.skipTest("no initialiser list available")
        a = next(iter(a for a in ini if a not in tree().by_addr), None)
        if a is None:
            self.skipTest("every initialiser address is already a manifest row")
        rows = [{"tu": "match/x/i.cpp", "addr": "0x%X" % a, "sym": "?i@@YAXXZ", "len": "0x13", "status": "matched", "pct": 100}]
        f = self.rules({"match/x/i.cpp": HEADER + "// FUNCTION: GAMEMD 0x%X\nvoid i() {}\n" % a}, rows, {"inits"})
        self.assertTrue(any(x["level"] == "E" for x in f))

    def test_spans_rule_direction(self):
        rows = [{"tu": "match/x/s.cpp", "addr": "0x50DAC0", "sym": "?j@@YAXXZ", "len": "0x38", "status": "matched", "pct": 100},
                {"tu": "match/x/s.cpp", "addr": "0x6F4A40", "sym": "?s@@YAXXZ", "len": "0x10", "status": "matched", "pct": 100},
                {"tu": "match/x/s.cpp", "addr": "0x6F7930", "sym": "?t@@YAXXZ", "len": "0x40", "status": "matched", "pct": 100}]
        f = self.rules({"match/x/s.cpp": HEADER}, rows, {"spans"})
        if any("span check" in x["msg"] for x in f):
            self.skipTest("no retail image (set GAMEMD_BINARY): the spans rule degrades to a warning")
        by = {x["addr"]: x["level"] for x in f}
        self.assertEqual(by.get("0x6F4A40"), "E")    # shorter than the 0x24 CFG span: unproven tail
        self.assertEqual(by.get("0x6F7930"), "E")    # 0x31 + INT3 padding counted as function bytes
        self.assertEqual(by.get("0x50DAC0"), "W")    # 0x27 + a jump table: a real tail, flagged only

    def test_rea_rule(self):
        p = packet(self.tmp, {"match/x/a.cpp": HEADER}, [], readme="Base: 935745b\nGround truth: ghidra CLI disasm.\n\n## Proposed commit message\n```\nx\n```\n")
        f = [x for x in lint(p, {"rea"}) if x["rule"] == "rea"]
        self.assertEqual([x["level"] for x in f], ["W"])
        p = packet(self.tmp, {"match/x/a.cpp": HEADER}, [], readme="Evidence: REA ev_18a3f84f\n\n## Proposed commit message\n```\nx\n```\n")
        self.assertEqual([x for x in lint(p, {"rea"}) if x["rule"] == "rea"], [])

    def test_commit_message_forms(self):
        p = packet(self.tmp, {"match/x/a.cpp": HEADER}, [], readme="## Proposed commit message\n\n  Indented title\n\n  body\n\n  Co-Authored-By: A <a@b>\n")
        self.assertTrue(p.commit_message().startswith("Indented title"))


class Toolfix(unittest.TestCase):
    """Fixes from the 2026-10-23 tooling review (rules 1-7)."""

    def setUp(self):
        self.tmp = tempfile.mkdtemp(prefix="dlt_", dir=D.SCRATCH)

    def mk(self, files, rows, readme="Base: 935745b\n", extra=None, name=None):
        COUNT[0] += 1
        d = os.path.join(self.tmp, name or "p%d" % COUNT[0], "READY")
        os.makedirs(d)
        open(os.path.join(d, "patch.diff"), "w").write(mkpatch(files) if isinstance(files, dict) else files)
        json.dump(rows, open(os.path.join(d, "manifest_delta.json"), "w"))
        if readme is not None:
            open(os.path.join(d, "README.md"), "w").write(readme)
        for k, v in (extra or {}).items():
            open(os.path.join(d, k), "w").write(v)
        return L.Packet(d)

    # 1. commit message forms
    def test_shape_commit_forms(self):
        def shape(p):
            return [f for f in lint(p, {"shape"}) if f["level"] == "E"]
        a = self.mk({"match/x/a.cpp": HEADER}, [], readme="Base: 935745b\n\nProposed commit: Recover things\n")
        self.assertEqual(shape(a), [])
        self.assertTrue(a.commit_message().startswith("Recover things"))
        b = self.mk({"match/x/a.cpp": HEADER}, [], readme="Base: 935745b\n\nProposed commit: Title\n```\nTitle\n\nbody\n```\n")
        self.assertEqual(shape(b), [])
        self.assertIn("body", b.commit_message())
        c = self.mk({"match/x/a.cpp": HEADER}, [], readme=None, extra={"commit_msg.txt": "Subject\n\nCo-Authored-By: A <a@b>\n", "base_sha": "935745b\n"})
        self.assertEqual(shape(c), [])
        d = self.mk({"match/x/a.cpp": HEADER}, [], readme="Base: 935745b\nno message here\n")
        self.assertTrue(any("commit message" in f["msg"] for f in shape(d)))

    # 3. base sha forms
    def test_base_sha_forms(self):
        sha = "8dd6a8de574785d7ab0bcd8e23d3e07cf469e572"
        cases = [
            dict(readme=None, extra={"base_sha": sha + "\n"}),
            dict(readme=None, extra={"BASE_SHA": sha.upper() + "\n"}),
            dict(readme=None, extra={"base_sha.txt": "base " + sha}),
            dict(readme="Base: `%s`.\n" % sha),
            dict(readme="Base%s, checkpoint d08f92b plus bindings\n" % sha),
            dict(readme="## Base\nbase sha = %s\n" % sha),
        ]
        for c in cases:
            p = self.mk({"match/x/a.cpp": HEADER}, [], **c)
            self.assertEqual(p.base_sha(), sha, c)
        self.assertIsNone(self.mk({"match/x/a.cpp": HEADER}, [], readme="Based on prior work, see d08f92b\n").base_sha())
        self.assertEqual(self.mk({"match/x/a.cpp": HEADER}, [], readme="x\n", extra={"base_sha": "", "BASE_SHA": sha}).base_sha(), sha)

    # 2. stale must not write git metadata
    def test_stale_writes_no_git_metadata(self):
        import unittest.mock as mock
        wl = L.git(D.MAIN_REPO, "worktree", "list")
        p = self.mk({"match/x/never_exists.cpp": HEADER + "int a;\n"}, [])
        with mock.patch.object(D, "add_worktree", side_effect=AssertionError("stale must not add a worktree")):
            f = [x for x in lint(p, {"stale"})]
        self.assertEqual(f, [])
        self.assertEqual(wl, L.git(D.MAIN_REPO, "worktree", "list"))
        mod = "diff --git a/AGENTS.md b/AGENTS.md\n--- a/AGENTS.md\n+++ b/AGENTS.md\n@@ -1,1 +1,1 @@\n-no such line\n+x\n"
        q = self.mk(mod, [])
        f = lint(q, {"stale"})
        self.assertTrue(any(x["rule"] == "stale" and x["level"] == "E" for x in f))
        # creating an existing file is reported too
        r = self.mk({"AGENTS.md": "x"}, [])
        self.assertTrue(any(x["rule"] == "stale" for x in lint(r, {"stale"})))

    # 4. a (decl; reloc) parenthetical on the next line is a declaration
    def test_decl_marker_continues_on_next_line(self):
        src = HEADER + ("// FUNCTION: GAMEMD 0x730A10 / 0x730990\n// (decl; reloc) -- numbered command handlers.\n"
                        "int FUN_00730A10(int);\n// FUNCTION: GAMEMD 0x730B00 (decl; reloc)\nint g();\n")
        self.assertEqual(D.rows_in_order(src), [])
        self.assertEqual(D.rows_in_order("// FUNCTION: GAMEMD 0x730A10\n// (note)\nint f() {}\n"), [0x730A10])
        p = self.mk({"match/x/s.cpp": src}, [])
        lt = pktlint.Lint(p, tree(), D.MAIN_REPO)
        self.assertEqual(lt.patch_claims(), {})
        # and a real body claim elsewhere in the tree does not make it a duplicate
        addr = next(iter(tree().claims()))
        src2 = HEADER + "// FUNCTION: GAMEMD 0x%X\n// (decl; reloc) -- x\nint h();\n" % addr
        f = [x for x in lint(self.mk({"match/x/s2.cpp": src2}, []), {"dupclaims"}) if x["rule"] == "dupclaims"]
        self.assertEqual(f, [])

    # 5. delta rows must be this packet's claims/results
    def test_delta_carryover(self):
        t = tree()
        exact = next(r for r in t.manifest if r["status"] == "matched" and r.get("len"))
        free = [a for a in range(0x401000, 0x500000, 0x100) if a not in t.by_addr and a + 0x100 not in t.by_addr][:2]
        A1, A2 = "0x%X" % free[0], "0x%X" % free[1]
        src = HEADER + "// FUNCTION: GAMEMD %s\nvoid a() {}\n" % A1
        new = {"tu": "match/x/a.cpp", "addr": A1, "sym": "?a@@YAXXZ", "len": "0x10", "status": "matched", "pct": 100}
        carry = dict(exact)
        carry["pct"] = carry.get("pct", 100)
        bad_len = dict(exact, len="0x%x" % (D.hx(exact["len"]) + 4))
        rows = sorted([new, carry], key=lambda r: D.hx(r["addr"]))
        f = [x for x in lint(self.mk({"match/x/a.cpp": src}, rows), {"delta"}) if x["level"] == "E"]
        msgs = " | ".join(x["msg"] for x in f)
        self.assertIn("already in the manifest", msgs)
        self.assertNotIn(A1, msgs)
        # same address, different len on an exact row: conflict
        f = [x for x in lint(self.mk({"match/x/a.cpp": src}, sorted([new, bad_len], key=lambda r: D.hx(r["addr"]))), {"delta"}) if x["level"] == "E"]
        self.assertIn("conflicts with the existing exact row", " | ".join(x["msg"] for x in f))
        # an explicit change row for an unclaimed address is allowed
        ch = dict(exact, len="0x%x" % (D.hx(exact["len"]) + 4), _change="len corrected")
        f = [x for x in lint(self.mk({"match/x/a.cpp": src}, sorted([new, ch], key=lambda r: D.hx(r["addr"]))), {"delta"}) if x["level"] == "E"]
        self.assertEqual([x for x in f if "carried" in x["msg"] or "conflicts" in x["msg"] or "no body claim" in x["msg"]], [])
        # a new row for an address the patch does not claim
        stray = {"tu": "match/x/a.cpp", "addr": A2, "sym": "?z@@YAXXZ", "len": "0x10", "status": "matched", "pct": 100}
        f = [x for x in lint(self.mk({"match/x/a.cpp": src}, [new, stray]), {"delta"}) if x["level"] == "E"]
        self.assertTrue(any(A2 in x["msg"] for x in f))
        self.assertFalse(any(A1 in x["msg"] for x in f))
        f = [x for x in lint(self.mk({"match/x/a.cpp": src}, [new]), {"delta"}) if x["level"] == "E"]
        self.assertEqual(f, [])

    def test_pkt_rows_do_not_carry_over(self):
        import pkt
        d = tempfile.mkdtemp(prefix="pktinit_", dir=D.SCRATCH)
        os.makedirs(os.path.join(d, "READY"))
        open(os.path.join(d, "READY", "rows.tsv"), "w").write("0x401000\t?a@@YAXXZ\t0x10\t\n")
        open(os.path.join(d, "rows_state.json"), "w").write("{}")
        pkt.reset_rows(d)
        self.assertEqual(pkt.read_rows(dict(READY=os.path.join(d, "READY"))), {})
        self.assertFalse(os.path.exists(os.path.join(d, "rows_state.json")))
        self.assertTrue(os.path.exists(os.path.join(d, "READY", "rows.tsv.prev")))

    # 6. class-view duplication is judged post-patch
    def test_views_canonical_move(self):
        t = tree()
        old = name = None
        for n, h in sorted(t.canonical_classes().items()):
            txt = t.text(h[0]) if len(h) == 1 else None
            if txt and h[0].startswith("match/_layout/") and txt.count("\n") < 200 and "\r" not in txt \
                    and [m.group(2) for m in D.CLASS_DEF.finditer(txt)] == [n] and txt.endswith("\n"):
                old, name = h[0], n
                break
        self.assertIsNotNone(old)
        oldtxt = t.text(old)
        lines = oldtxt[:-1].split("\n")
        newhdr = "match/_layout/zz_moved_view.h"
        add = mkpatch({newhdr: HEADER + "class %s {\npublic:\n int x;\n};\n" % name})
        rm = "diff --git a/%s b/%s\ndeleted file mode 100644\n--- a/%s\n+++ /dev/null\n@@ -1,%d +0,0 @@\n%s\n" % (
            old, old, old, len(lines), "\n".join("-" + l for l in lines))
        f = [x for x in lint(self.mk(add + rm, []), {"views"}) if x["rule"] == "views"]
        self.assertEqual(f, [], f)
        # same new header without removing the old definition: two canonical definitions
        f = [x for x in lint(self.mk(add, [], name="nomove"), {"views"}) if x["rule"] == "views"]
        self.assertTrue(any(x["level"] == "E" for x in f))
        # a per-TU view of a canonical class is still flagged
        view = mkpatch({"match/x/view.h": HEADER + "class %s {\npublic:\n int x;\n};\n" % name})
        f = [x for x in lint(self.mk(view, [], name="view"), {"views"}) if x["rule"] == "views"]
        self.assertTrue(any(x["level"] == "E" and "canonical header" in x["msg"] for x in f))


class Toolfix2(unittest.TestCase):
    """Round 2: post_files scratch placement, per-file pkt rows, bind manifest, explicit change rows."""

    def setUp(self):
        self.tmp = tempfile.mkdtemp(prefix="dlt2_", dir=D.SCRATCH)
        self.target = next(p for p in sorted(tree().paths) if p.startswith("match/") and p.endswith(".cpp") and tree().text(p))

    def _patch_first_line(self, path):
        import difflib
        old = tree().text(path).split("\n")
        new = [old[0] + " PATCHED"] + old[1:]
        body = "".join(l + "\n" for l in list(difflib.unified_diff(old, new, lineterm="", n=3))[2:])
        return "diff --git a/%s b/%s\n--- a/%s\n+++ b/%s\n%s" % (path, path, path, path, body), old[0]

    def _post(self, scratch):
        import unittest.mock as mock
        diff, first = self._patch_first_line(self.target)
        COUNT[0] += 1
        d = os.path.join(self.tmp, "pp%d" % COUNT[0], "READY")
        os.makedirs(d)
        open(os.path.join(d, "patch.diff"), "w").write(diff)
        json.dump([], open(os.path.join(d, "manifest_delta.json"), "w"))
        lt = pktlint.Lint(L.Packet(d), tree(), D.MAIN_REPO)
        with mock.patch.object(D, "SCRATCH", scratch):
            post = lt.post_files()
        return post[self.target].split("\n")[0], first

    def test_post_files_inside_and_outside_a_repo(self):
        import subprocess
        outside = tempfile.mkdtemp(prefix="plout_", dir="/dev/shm" if os.path.isdir("/dev/shm") else None)
        inside = os.path.join(self.tmp, "repo")
        os.makedirs(inside)
        subprocess.run(["git", "init", "-q", inside], check=True)
        nested = os.path.join(inside, "deep", "er")
        os.makedirs(nested)
        for sc in (outside, inside, nested):
            got, first = self._post(sc)
            self.assertEqual(got, first + " PATCHED", "scratch " + sc)

    def test_apply_outside_repo_keeps_prepatch_text_away(self):
        import subprocess
        repo = os.path.join(self.tmp, "r2")
        work = os.path.join(repo, "w")
        os.makedirs(work)
        subprocess.run(["git", "init", "-q", repo], check=True)
        open(os.path.join(work, "a.txt"), "w").write("x\n")
        r = pktlint.apply_outside_repo(work, "diff --git a/a.txt b/a.txt\n--- a/a.txt\n+++ b/a.txt\n@@ -1 +1 @@\n-x\n+y\n")
        self.assertEqual(r.returncode, 0)
        self.assertEqual(open(os.path.join(work, "a.txt")).read(), "y\n")

    # ---- pkt.py
    def env(self, base_sha=None):
        d = os.path.join(self.tmp, "pk")
        for sub in ("READY", "wt/scripts/data"):
            os.makedirs(os.path.join(d, sub), exist_ok=True)
        e = dict(PKT_DIR=d, WT=os.path.join(d, "wt"), READY=os.path.join(d, "READY"), OBJ=os.path.join(d, "obj"), NAME="pk")
        open(os.path.join(d, "READY", "base_sha"), "w").write((base_sha or L.rev_parse(D.MAIN_REPO, "HEAD")) + "\n")
        return e

    def test_score_keeps_rows_of_every_file(self):
        import unittest.mock as mock
        import pkt
        e = self.env()
        wt = e["WT"]
        os.makedirs(os.path.join(wt, "match/x"))
        srcs = {"match/x/a.cpp": [0x7F0000, 0x7F0010], "match/x/b.cpp": [0x7F0100]}
        for tu, addrs in srcs.items():
            open(os.path.join(wt, tu), "w").write("".join("// FUNCTION: GAMEMD 0x%X\nvoid f%X() {}\n" % (a, a) for a in addrs))
        names = {a for v in srcs.values() for a in v}

        def score(tu, extra=()):
            with mock.patch.object(D, "compile_tu", return_value=(True, "")), \
                    mock.patch.object(D, "defined_names", return_value={"?f%X@@YAXXZ" % a for a in names} | {"?FUN_%08X@@YAXXZ" % a for a in names}), \
                    mock.patch.object(D, "raw_match", side_effect=lambda w, o, row: (row["addr"] != "0x7F0010", "")), \
                    mock.patch.object(D, "diff_retail_pct", return_value=(55.5, "match: 55.5%")), \
                    mock.patch.object(D, "cfg_span", return_value=(0x10, "x")), \
                    mock.patch.object(pkt, "load_env", return_value=e):
                pkt.cmd_score(type("A", (), {"tu": tu, "addrs": list(extra)})())
        score("match/x/a.cpp")
        score("match/x/b.cpp")
        st = json.load(open(os.path.join(e["PKT_DIR"], "rows_state.json")))
        self.assertEqual(sorted(st), ["0x7F0000", "0x7F0010", "0x7F0100"])
        self.assertEqual({k: v["tu"] for k, v in st.items()}, {"0x7F0000": "match/x/a.cpp", "0x7F0010": "match/x/a.cpp", "0x7F0100": "match/x/b.cpp"})
        self.assertEqual(st["0x7F0010"]["pct"], 55.5)
        # a hand edit in rows.tsv survives; dropping a claim from a.cpp removes only a.cpp's row
        rows = pkt.read_rows(e)
        rows[0x7F0100]["name"] = "Hand::Named"
        pkt.write_rows(e, rows)
        open(os.path.join(wt, "match/x/a.cpp"), "w").write("// FUNCTION: GAMEMD 0x7F0000\nvoid f7F0000() {}\n")
        score("match/x/a.cpp")
        st = json.load(open(os.path.join(e["PKT_DIR"], "rows_state.json")))
        self.assertEqual(sorted(st), ["0x7F0000", "0x7F0100"])
        self.assertEqual(st["0x7F0100"]["name"], "Hand::Named")

    def fake_base_tree(self, base_rows):
        class T:
            by_addr = {D.hx(r["addr"]): r for r in base_rows}
        return T()

    def test_state_rows_emit_change_ops_for_rekeys_and_improved_partials(self):
        import unittest.mock as mock
        import pkt
        e = self.env()
        base = [dict(tu="match/x/a.cpp", addr="0x7F0000", sym="?old@@YAXXZ", len="0x10", status="matched", pct=100, name="old"),
                dict(tu="match/x/a.cpp", addr="0x7F0010", sym="?p@@YAXXZ", len="0x10", status="partial", pct=40.0, name="p"),
                dict(tu="match/x/a.cpp", addr="0x7F0020", sym="?q@@YAXXZ", len="0x10", status="partial", pct=40.0, name="q"),
                dict(tu="match/x/a.cpp", addr="0x7F0030", sym="?same@@YAXXZ", len="0x10", status="matched", pct=100, name="same")]
        st = {"0x7F0000": dict(sym="?new@@YAXXZ", len="0x10", tu="match/x/a.cpp", pct=100.0),      # re-key
              "0x7F0010": dict(sym="?p@@YAXXZ", len="0x10", tu="match/x/a.cpp", pct=70.0),          # improved partial
              "0x7F0020": dict(sym="?q@@YAXXZ", len="0x10", tu="match/x/a.cpp", pct=40.0),          # no better: dropped
              "0x7F0030": dict(sym="?same@@YAXXZ", len="0x10", tu="match/x/a.cpp", pct=100.0),      # unchanged: dropped
              "0x7F0040": dict(sym="?add@@YAXXZ", len="0x10", tu="match/x/b.cpp", pct=100.0)}       # new, other file
        json.dump(st, open(os.path.join(e["PKT_DIR"], "rows_state.json"), "w"))
        fake = mock.Mock(rev="deadbeef", by_addr=self.fake_base_tree(base).by_addr)
        with mock.patch.object(D, "Tree", return_value=fake):
            rows, _ = pkt.state_rows(e)
        by = {r["addr"]: r for r in rows}
        self.assertEqual(sorted(by), ["0x7F0000", "0x7F0010", "0x7F0040"])
        self.assertEqual(by["0x7F0000"]["op"], "change")
        self.assertEqual(by["0x7F0000"]["old"], {"sym": "?old@@YAXXZ", "status": "matched"})
        self.assertEqual((by["0x7F0010"]["op"], by["0x7F0010"]["status"], by["0x7F0010"]["pct"]), ("change", "partial", 70.0))
        self.assertNotIn("op", by["0x7F0040"])
        # landlib merges them as explicit changes with no replace-warning
        man, errs, warns = L.merge_deltas(base, [("pk", rows)])
        self.assertEqual((errs, warns), ([], []))
        self.assertEqual({r["addr"]: r["sym"] for r in man}["0x7F0000"], "?new@@YAXXZ")
        # and pktlint treats them as change rows
        self.assertTrue(pktlint.Lint.is_change_row(by["0x7F0000"]))

    def test_bind_manifest_includes_the_packets_own_rows(self):
        import pkt
        e = self.env()
        base = [dict(tu="match/x/a.cpp", addr="0x7F0000", sym="?old@@YAXXZ", len="0x10", status="matched", pct=100, name="old")]
        open(os.path.join(e["WT"], D.MANIFEST), "w").write(L.dump_manifest(base))
        rows = [dict(tu="match/x/b.cpp", addr="0x7F0040", sym="?add@@YAXXZ", len="0x10", name="add", status="matched", pct=100.0),
                dict(tu="match/x/a.cpp", addr="0x7F0000", sym="?new@@YAXXZ", len="0x10", name="new", status="matched", pct=100.0,
                     op="change", old={"sym": "?old@@YAXXZ", "status": "matched"})]
        p = pkt.write_work_manifest(e, rows)
        man = json.load(open(p))
        self.assertEqual({r["sym"] for r in man}, {"?add@@YAXXZ", "?new@@YAXXZ"})
        self.assertTrue(all("op" not in r and "old" not in r for r in man))
        self.assertEqual(open(os.path.join(e["WT"], D.MANIFEST)).read(), L.dump_manifest(base))   # base untouched

    def test_strict_passes_the_given_manifest(self):
        import unittest.mock as mock
        seen = []
        with mock.patch("subprocess.run", side_effect=lambda cmd, **k: (seen.append(cmd), mock.Mock(returncode=0, stdout="", stderr=""))[1]):
            D.strict("/t", "o.obj", dict(sym="s", addr="0x1", len="0x1"), None, "/work/m.json")
            D.strict("/t", "o.obj", dict(sym="s", addr="0x1", len="0x1"), None)
        self.assertEqual(seen[0][seen[0].index("--manifest") + 1], "/work/m.json")
        self.assertEqual(seen[1][seen[1].index("--manifest") + 1], D.MANIFEST)

    def test_object_names_keep_the_stem_for_c_files(self):
        import re
        for f in ("pkt.py", "pktlint.py", "pktrebase.py", "permute_queue.py"):
            self.assertIsNone(re.search(r"\[:-4\]", open(os.path.join(os.path.dirname(HERE), f)).read()), f)


class Toolfix4(unittest.TestCase):
    def test_multiset_parse_accepts_trailing_text(self):
        import permute_queue as PQ
        self.assertEqual(PQ.parse_multiset("multiset: identical (26 vs 26 instructions) - scheduling only\n"), "identical")
        self.assertTrue(PQ.parse_multiset("multiset: retail-only {'jl': 1}  compiled-only {'jg': 1}").startswith("retail-only"))
        self.assertIsNone(PQ.parse_multiset("match: 90.0%"))

    def test_queue_falls_back_to_manifest_pct_and_ranks(self):
        import permute_queue as PQ
        base = dict(tu="a.cpp", sym="s", len="0x10")
        rows = [
            PQ.queue_entry(dict(base, addr="0x1", pct=40.0), None, None, False),         # score failed
            PQ.queue_entry(dict(base, addr="0x2", pct=80.0), 85.0, "identical", False),
            PQ.queue_entry(dict(base, addr="0x3", pct=90.0), 95.0, "retail-only {}", False),
            PQ.queue_entry(dict(base, addr="0x4", pct=10.0), 20.0, "identical", True),
        ]
        self.assertEqual((rows[0]["pct"], rows[0]["pct_src"]), (40.0, "manifest"))
        self.assertEqual([r["addr"] for r in PQ.rank_queue(rows)], ["0x4", "0x2", "0x3", "0x1"])

    def test_rea_none_fallback_line_is_accepted(self):
        tmp = tempfile.mkdtemp(prefix="dlt_", dir=D.SCRATCH)
        base = "Base: 935745b\nWe used REA for nothing.\n"
        tail = "\n## Proposed commit message\n```\nMatch\n\nCo-Authored-By: X <x@y>\n```\n"
        bad = [f for f in lint(packet(tmp, {}, [], base + tail), {"rea"}) if f["rule"] == "rea"]
        ok = [f for f in lint(packet(tmp, {}, [], base + "REA: none (ghidra CLI fallback)\n" + tail), {"rea"}) if f["rule"] == "rea"]
        self.assertTrue(bad)
        self.assertEqual(ok, [])

    def test_done_held_backs_up_diff_then_removes(self):
        import pkt
        from unittest import mock
        import subprocess
        root = tempfile.mkdtemp(prefix="dlt_held_", dir=D.SCRATCH)
        wt, bk, pd = (os.path.join(root, n) for n in ("wt", "bk", "pkt"))
        os.makedirs(wt); os.makedirs(pd)
        for c in (["init", "-q"], ["config", "user.email", "a@b"], ["config", "user.name", "n"]):
            subprocess.run(["git", "-C", wt, *c], check=True)
        open(os.path.join(wt, "a.cpp"), "w").write("one\n")
        subprocess.run(["git", "-C", wt, "add", "a.cpp"], check=True)
        subprocess.run(["git", "-C", wt, "commit", "-qm", "x"], check=True)
        open(os.path.join(wt, "a.cpp"), "w").write("two\n")
        open(os.path.join(wt, "new.cpp"), "w").write("fresh\n")
        open(os.path.join(pd, "rows.tsv"), "w").write("0x1\n")
        e = dict(NAME="held1", WT=wt, PKT_DIR=pd)
        removed = []
        with mock.patch.object(pkt, "load_env", return_value=e), mock.patch.object(D, "BACKUPS", bk), \
                mock.patch.object(D, "remove_worktree", side_effect=lambda r, w: removed.append(w)):
            pkt.cmd_done(type("A", (), {"force": False, "held": True})())
        diff = open(os.path.join(bk, "held1", "HELD", "worktree.diff")).read()
        self.assertIn("+two", diff)
        self.assertIn("+fresh", diff)
        self.assertTrue(os.path.isfile(os.path.join(bk, "held1", "HELD", "pkt_dir", "rows.tsv")))
        self.assertEqual(removed, [wt])
        with mock.patch.object(pkt, "load_env", return_value=e), mock.patch.object(D, "BACKUPS", bk):
            with self.assertRaises(SystemExit):
                pkt.cmd_done(type("A", (), {"force": False, "held": False})())


class CreatedListGuard(unittest.TestCase):
    """Incident 2026-10-22: a sweep removed other agents' worktrees. The tools may remove only
    what they created."""

    def test_refuses_foreign_paths(self):
        foreign = tempfile.mkdtemp(prefix="foreign_", dir=D.SCRATCH)   # made outside the ledger
        try:
            with self.assertRaises(D.NotOursError):
                D.remove_dir(foreign)
            with self.assertRaises(D.NotOursError):
                D.remove_worktree(D.MAIN_REPO, foreign)
            self.assertTrue(os.path.isdir(foreign))
            with self.assertRaises(D.NotOursError):
                D.add_worktree(D.MAIN_REPO, foreign, "HEAD")           # never over an existing path
        finally:
            os.rmdir(foreign)

    def test_removes_own_paths(self):
        d = D.scratch_dir("guard_")
        wt = D.add_worktree(D.MAIN_REPO, os.path.join(d, "wt"), "HEAD", toolchain=False)
        self.assertTrue(D.created_by_us(wt))
        self.assertIn(wt, L.git(D.MAIN_REPO, "worktree", "list"))
        D.remove_worktree(D.MAIN_REPO, wt)
        self.assertNotIn(wt, L.git(D.MAIN_REPO, "worktree", "list"))
        D.remove_dir(d)
        self.assertFalse(os.path.exists(d))

    def test_no_sweeps_in_sources(self):
        import glob
        here = os.path.dirname(HERE)
        for f in glob.glob(os.path.join(here, "*.py")) + glob.glob(os.path.join(here, "tests", "*.py")):
            if os.path.abspath(f) == os.path.abspath(__file__):
                continue
            src = open(f).read()
            self.assertNotIn('"prune"', src, f)
            if os.path.basename(f) != "dlib.py":
                self.assertNotIn('"worktree", "remove"', src, f)
                self.assertNotIn("rmtree", src, f)


class Skeleton(unittest.TestCase):
    def test_analyse_disasm(self):
        import skeleton
        c = {"disasm": [
            {"addr": "0x1", "bytes": "56", "text": "push esi", "note": None},
            {"addr": "0x2", "bytes": "8bf1", "text": "mov esi,ecx", "note": None},
            {"addr": "0x3", "bytes": "", "text": "mov al,BYTE PTR [esi+0x41b]", "note": None},
            {"addr": "0x4", "bytes": "", "text": "mov eax,DWORD PTR [esi+0x2e4]", "note": None},
            {"addr": "0x5", "bytes": "", "text": "call DWORD PTR [eax+0x2e4]", "note": None},
            {"addr": "0x6", "bytes": "", "text": "call 0x565730", "note": "GetTargetCell"},
            {"addr": "0x7", "bytes": "", "text": "ret 0x8", "note": None}],
            "refs": [{"addr": "0xa8ed84", "kind": "global", "name": "CurrentFrame", "text": None},
                     {"addr": "0x824fe4", "kind": "string", "text": "EVA_x"}]}
        a = skeleton.analyse(c)
        self.assertTrue(a["thiscall"])
        self.assertEqual(a["ret_n"], 8)
        self.assertEqual(a["accesses"], {0x41B: {1}, 0x2E4: {4}})
        self.assertEqual(a["callees"], [(0x565730, "GetTargetCell")])
        self.assertEqual(a["vcalls"], [("eax", 0x2E4)])
        self.assertIn(0xA8ED84, a["globals"])
        self.assertEqual(a["strings"][0x824FE4], "EVA_x")


class Merge(unittest.TestCase):
    def test_merge_into_tu_orders_chunks_and_hoists_preamble(self):
        tmp = tempfile.mkdtemp(prefix="dlm_", dir=D.SCRATCH)
        os.makedirs(os.path.join(tmp, "match/core"))
        dest = "match/core/T.cpp"
        open(os.path.join(tmp, dest), "w").write(HEADER + "//   Original translation unit T.CPP. code range (0x401000-0x402000).\n"
                                                 "#include \"a.h\"\nextern int G;\n\n// FUNCTION: GAMEMD 0x401000\nvoid a() {}\n\n// FUNCTION: GAMEMD 0x401800\nvoid c() {}\n")
        src = "match/x/new.cpp"
        stext = HEADER.replace("own-binary-via-Ghidra", "own-binary-via-Ghidra | private-ref-cross-check") + "// VC6FLAGS: /O2\n#include \"../core/a.h\"\nextern int H;\n\n// FUNCTION: GAMEMD 0x401400\nvoid b() {}\n"
        rows = {dest: {0x401000, 0x401800, 0x401400}, src: {0x401400}}
        text, tags = D.merge_into_tu(tmp, dest, {src: stext}, rows)
        order = D.rows_in_order(text)
        self.assertEqual(order, [0x401000, 0x401400, 0x401800])
        self.assertIn("private-ref-cross-check", tags)
        self.assertIn("// Provenance: own-binary-via-Ghidra | private-ref-cross-check", text)
        self.assertNotIn("VC6FLAGS", text)
        self.assertLess(text.index("extern int H;"), text.index("// FUNCTION: GAMEMD 0x401000"))
        self.assertTrue(text.startswith("// SPDX"))

    def test_drop_chunks(self):
        from pktrebase import Rebase
        text = "pre\n// FUNCTION: GAMEMD 0x401000\nvoid a() {}\n// FUNCTION: GAMEMD 0x401400\nvoid b() {}\n"
        out = Rebase.drop_chunks(text, {0x401000})
        self.assertNotIn("void a()", out)
        self.assertIn("void b()", out)


class NewTools(unittest.TestCase):
    """cppscan, branch2packet.build_delta, placement_leads.Order, ini_names.readers."""

    def test_cppscan_bodies(self):
        import cppscan
        src = "struct A { void f() { x(); } };\n// void g() { }\nint B::h(int a) const { if (a) { return 1; } return 0; }\n"
        got = [(h, l0) for h, _, l0, _ in cppscan.function_bodies(src)]
        self.assertEqual(got, [("void f()", 1), ("int B::h(int a) const", 3)])

    def test_branch2packet_delta(self):
        import branch2packet as B
        base = [{"tu": "match/a.cpp", "addr": "0x401000", "sym": "?a@@YAXXZ", "len": "0x10", "name": "a", "status": "matched", "pct": 100},
                {"tu": "match/a.cpp", "addr": "0x401010", "sym": "?b@@YAXXZ", "len": "0x10", "name": "b", "status": "matched", "pct": 100}]
        rows = [{"tu": "match/a.cpp", "addr": 0x401020, "sym": "?c@@YAXXZ", "len": 0x10, "name": "c", "status": "matched", "pct": 100},
                dict(base[0], status="partial", pct=90.0), dict(base[1])]
        d, notes, errs = B.build_delta(base, rows, [])
        self.assertEqual(errs, [])
        self.assertEqual([(r["addr"], r["op"]) for r in d], [("0x401000", "change"), ("0x401020", "add")])
        self.assertEqual(d[0]["old"], {"sym": "?a@@YAXXZ"})
        self.assertEqual(len(notes), 1)
        d, _, errs = B.build_delta(base, [], ["0x401010", "0x999999"])
        self.assertEqual([r["op"] for r in d], ["remove"])
        self.assertTrue(errs)
        _, _, errs = B.build_delta(base, [dict(rows[0], pct=50)], [])
        self.assertTrue(any("matched with pct" in e for e in errs))

    def test_placement_order(self):
        import placement_leads as P
        o = P.Order([{"tu": "A.cpp", "lo": "0x1000", "hi": "0x1100"}, {"tu": "B.cpp", "lo": "0x2000", "hi": "0x2100"}])
        self.assertEqual(o.slot(0x1050), 0.0)
        self.assertEqual(o.slot(0x1500), 0.5)
        self.assertEqual(o.slot(0x500), -0.5)
        self.assertEqual(o.slot(0x3000), 1.5)
        self.assertEqual(o.label(0.5), "between A.cpp and B.cpp")

    def test_ini_readers(self):
        import ini_names as N
        src = ("// FUNCTION: GAMEMD 0x401000\nbool Foo::ReadINI(IniView* ini)\n{\n"
               "    Cost = ini->ReadInt(ID, \"Cost\", Cost);\n"
               "    Speed = (float)ini->ReadDouble(ID, \"Speed\", Speed);\n"
               "    Other = ini->ReadInt(ID, \"Other\", 5);\n"
               "    unknown_10 = ini->ReadInt(ID, \"Z\", unknown_10);\n}\n")
        man = {0x401000: {"status": "matched", "pct": 100}}
        got = N.readers("match/x.cpp", src, man)
        self.assertEqual([(r["cls"], r["field"], r["key"], r["addr"]) for r in got],
                         [("Foo", "Cost", "Cost", "0x401000"), ("Foo", "Speed", "Speed", "0x401000")])


class Toolfix1030(unittest.TestCase):
    PLAIN = ("--- a/match/x/a.cpp\t2026-10-30 10:00:00\n+++ b/match/x/a.cpp\t2026-10-30 10:00:01\n@@ -1,2 +1,3 @@\n l1\n+l2\n l3\n"
             "--- /dev/null\n+++ b/match/x/n.h\n@@ -0,0 +1,1 @@\n+h\n")

    def test_split_plain_unified_diff(self):
        ds = D.split_patch(self.PLAIN)
        self.assertEqual([d.path for d in ds], ["match/x/a.cpp", "match/x/n.h"])
        self.assertTrue(ds[1].is_new and not ds[0].is_new)
        self.assertEqual(ds[1].new_content(), "h")

    def test_split_garbage_raises_and_blank_is_empty(self):
        self.assertEqual(D.split_patch(""), [])
        with self.assertRaises(ValueError):
            D.split_patch("this is not a patch\n")

    def test_lint_errors_on_unsplittable_patch(self):
        tmp = tempfile.mkdtemp(prefix="dlt_", dir=D.SCRATCH)
        p = packet(tmp, {"match/x/a.cpp": "x"}, [])
        open(p.patch, "w").write("garbage that is not a patch\n")
        f = [x for x in lint(p, {"shape"}) if x["rule"] == "shape"]
        self.assertTrue(any(x["level"] == "E" and "0 files" in x["msg"] for x in f), f)

    def test_thisnull_only_real_null_tests(self):
        def hits(expr):
            src = HEADER + "// FUNCTION: GAMEMD 0x401000\nint Foo::f() { return %s; }\n" % expr
            tmp = tempfile.mkdtemp(prefix="dlt_", dir=D.SCRATCH)
            return [x for x in lint(packet(tmp, {"match/x/a.cpp": src}, []), {"thisnull"}) if x["rule"] == "thisnull"]
        for ok in ("x != this && y", "p->f == this && y", "this == p", "g(this)", "a(this, b)"):
            self.assertEqual(hits(ok), [], ok)
        for bad in ("this && y", "this == 0", "this == NULL", "this != 0", "!this", "0 != this", "y || this && z"):
            self.assertTrue(hits(bad), bad)
        src = HEADER + "// FUNCTION: GAMEMD 0x401000\nint Foo::f() { if (this) { return 1; } return 0; }\n"
        tmp = tempfile.mkdtemp(prefix="dlt_", dir=D.SCRATCH)
        self.assertTrue(lint(packet(tmp, {"match/x/a.cpp": src}, []), {"thisnull"}))

    def test_upper_case_suffix_is_linted_as_source(self):
        src = HEADER + "// FUNCTION: GAMEMD 0x401000\nint Foo::f() { return this && 1; }\n"
        tmp = tempfile.mkdtemp(prefix="dlt_", dir=D.SCRATCH)
        f = [x for x in lint(packet(tmp, {"match/x/House.CPP": src}, []), {"thisnull"}) if x["rule"] == "thisnull"]
        self.assertTrue(f)
        self.assertTrue("match/x/House.CPP".lower().endswith(L.SRC_EXT))

    def test_pkt_init_refuses_existing_ready_patch(self):
        import pkt
        import types
        import unittest.mock as mock
        root = tempfile.mkdtemp(prefix="pktinit_", dir=D.SCRATCH)
        os.makedirs(os.path.join(root, "nm", "READY"))
        open(os.path.join(root, "nm", "READY", "patch.diff"), "w").write("keep\n")
        with mock.patch.object(pkt, "SCRATCH_ROOT", root), mock.patch.object(pkt, "budget", lambda: (True, "")):
            with self.assertRaises(SystemExit) as cm:
                pkt.cmd_init(types.SimpleNamespace(name="nm", base="HEAD", force=False, reuse=False))
        self.assertIn("--reuse", str(cm.exception))
        self.assertEqual(open(os.path.join(root, "nm", "READY", "patch.diff")).read(), "keep\n")


class BindingCorrectionsLint(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.mkdtemp(prefix="dlt_", dir=D.SCRATCH)
        central = json.loads(L.git(D.MAIN_REPO, "show", "HEAD:" + L.BINDINGS))
        self.sym, self.cur = next((k, v) for k, v in central.items() if "::" not in k)
        self.new = "0x%08X" % (int(self.cur, 16) + 4)

    def findings(self, corrections, rule="bindings", extra=None):
        p = packet(self.tmp, {"match/x/a.cpp": HEADER}, [])
        json.dump(corrections, open(os.path.join(p.dir, "binding_corrections.json"), "w"))
        for k, v in (extra or {}).items():
            json.dump(v, open(os.path.join(p.dir, k), "w"))
        return [f for f in lint(p, {rule}) if f["rule"] == rule]

    def entry(self, **kw):
        return dict(dict(symbol=self.sym, old_addr=self.cur, new_addr=self.new, evidence="disasm at 0x401000 loads from the new address"), **kw)

    def test_valid_correction_is_a_warning(self):
        f = self.findings([self.entry()])
        self.assertEqual([x["level"] for x in f], ["W"])
        self.assertIn("CORRECTS", f[0]["msg"])

    def test_empty_evidence_and_shape_are_errors(self):
        self.assertEqual([x["level"] for x in self.findings([self.entry(evidence="")])], ["E"])
        self.assertEqual([x["level"] for x in self.findings([{"symbol": self.sym}])], ["E", "E", "E"])
        self.assertEqual([x["level"] for x in self.findings({"not": "a list"})], ["E"])

    def test_old_value_must_match_central(self):
        f = self.findings([self.entry(old_addr="0x00000001")])
        self.assertEqual([x["level"] for x in f], ["E"])
        self.assertIn("central is", f[0]["msg"])
        f = self.findings([self.entry(symbol="?not_in_central@@3HA")])
        self.assertEqual([x["level"] for x in f], ["E"])

    def rekey_findings(self, removed, rekeys=None, extra_map=None):
        p = packet(self.tmp, {"match/x/a.cpp": HEADER}, [])
        central = json.loads(L.git(D.MAIN_REPO, "show", "HEAD:" + L.BINDINGS))
        gone = {k: central[k] for k in removed}
        body = "".join('-  "%s": "%s"\n' % kv for kv in gone.items())
        open(os.path.join(p.dir, "patch.diff"), "a").write(
            "diff --git a/%s b/%s\n--- a/%s\n+++ b/%s\n@@ -1,1 +1,0 @@\n%s" % ((L.BINDINGS,) * 4 + (body,)))
        if rekeys is not None:
            json.dump(rekeys, open(os.path.join(p.dir, "binding_rekeys.json"), "w"))
        return [f for f in lint(p, {"bindings"}) if f["rule"] == "bindings"]

    def test_unlisted_removed_key_is_an_error_at_lint(self):
        central = json.loads(L.git(D.MAIN_REPO, "show", "HEAD:" + L.BINDINGS))
        k = self.sym
        f = self.rekey_findings([k])
        self.assertEqual([x["level"] for x in f], ["E"])
        self.assertIn("does not list", f[0]["msg"])
        twin = next((n for n, a in central.items() if n != k and a == central[k]), None)
        if twin:
            f = self.rekey_findings([k], [dict(old=k, new=twin, addr=central[k])])
            self.assertEqual([x for x in f if x["level"] == "E"], [])

    def test_no_file_no_findings(self):
        p = packet(self.tmp, {"match/x/a.cpp": HEADER}, [])
        self.assertEqual([x for x in lint(p, {"bindings"}) if x["rule"] == "bindings"], [])

    def test_guard_symbol_keys_warn(self):
        f = self.findings([], "rekeys", {"symbol_map_x.json": {"_$S12": "0x401000", "match/a.cpp::_$S3": "0x401004", "?ok@@3HA": "0x401008"}})
        self.assertEqual(sorted(x["level"] for x in f), ["W", "W"])
        self.assertTrue(any("honoured only from the central" in x["msg"] for x in f))
        f = self.findings([], "rekeys", {"manifest_rekeys.json": [{"addr": "0x401000", "old_sym": "_$S5", "new": {"sym": "?n@@3HA"}}]})
        self.assertEqual(len(f), 1)

    def test_guard_key_problem(self):
        self.assertIsNone(D.guard_key_problem("?f@@YAXXZ"))
        self.assertIsNone(D.guard_key_problem("_$Sx"))
        self.assertIsNotNone(D.guard_key_problem("_$E4"))


class Toolfix1030b(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.mkdtemp(prefix="dlt_", dir=D.SCRATCH)

    def test_worktree_patch_carries_untracked_new_files(self):
        import subprocess
        r = os.path.join(self.tmp, "repo")
        os.makedirs(os.path.join(r, "match/_layout"))
        os.makedirs(os.path.join(r, "match/x"))
        g = lambda *a: subprocess.run(["git", "-C", r, "-c", "user.name=t", "-c", "user.email=t@t", *a], check=True, capture_output=True, text=True).stdout
        g("init", "-q")
        open(os.path.join(r, "match/x/a.cpp"), "w").write("a\n")
        g("add", "."); g("commit", "-qm", "base")
        base = g("rev-parse", "HEAD").strip()
        open(os.path.join(r, "match/x/a.cpp"), "w").write("a\nb\n")
        open(os.path.join(r, "match/_layout/new.h"), "w").write("#pragma once\n")
        open(os.path.join(r, "match/x/b.asm"), "w").write("; FUNCTION: GAMEMD 0x401000\n")
        diff = D.worktree_patch(r, base, ["match_manifest.json"])
        self.assertEqual(sorted(d.path for d in D.split_patch(diff)), ["match/_layout/new.h", "match/x/a.cpp", "match/x/b.asm"])
        self.assertIn("+#pragma once", diff)

    def test_includes_rule(self):
        hdr = "match/_layout/vqa_class.h"
        self.assertNotIn(hdr, tree().paths)
        src = HEADER + '#include "../_layout/vqa_class.h"\n#include <windows.h>\n'
        p = packet(self.tmp, {"match/x/user.cpp": src}, [])
        f = [x for x in lint(p, {"includes"}) if x["rule"] == "includes"]
        self.assertEqual([x["level"] for x in f], ["E"])
        p = packet(self.tmp, {"match/x/user.cpp": src, hdr: HEADER + "#pragma once\n"}, [])
        self.assertEqual([x for x in lint(p, {"includes"}) if x["rule"] == "includes"], [])

    def test_asm_claims_and_compile_driver(self):
        asm = "; FUNCTION: GAMEMD 0x401000\nfoo proc\nfoo endp\n"
        self.assertEqual([a for a, _ in D.body_claims(asm)], [0x401000])
        p = packet(self.tmp, {"match/asm/foo.asm": asm}, [])
        lt = pktlint.Lint(p, tree(), D.MAIN_REPO)
        self.assertEqual(lt.patch_claims(), {"match/asm/foo.asm": {0x401000}})
        calls = []
        orig = L.run
        L.run = lambda cmd, **kw: (calls.append(cmd), (1, ""))[1]
        try:
            D.compile_tu(self.tmp, "match/asm/foo.asm", os.path.join(self.tmp, "o", "foo.obj"))
            D.compile_tu(self.tmp, "match/x/foo.cpp", os.path.join(self.tmp, "o", "foo2.obj"))
        finally:
            L.run = orig
        self.assertTrue(calls[0][1].endswith("vc6asm.sh"))
        self.assertTrue(calls[1][1].endswith("vc6cl.sh"))


if __name__ == "__main__":
    unittest.main()
