#!/usr/bin/env python3
"""Tests for the tumigrate tools (no compiler): python3 -m unittest discover -s scripts/agent_tools/tumigrate/tests"""
import json
import os
import shutil
import subprocess
import sys
import tempfile
import unittest

HERE = os.path.dirname(os.path.abspath(__file__))
TOOLS = os.path.dirname(HERE)
sys.path.insert(0, TOOLS)
import identity  # noqa: E402
import migrate  # noqa: E402
import fit  # noqa: E402
import cppsplit  # noqa: E402
import initorder  # noqa: E402


def write(path, text):
    os.makedirs(os.path.dirname(path), exist_ok=True)
    open(path, "w").write(text)


class Identity(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.mkdtemp(prefix="tumig_t_")
        self.addCleanup(shutil.rmtree, self.tmp, True)
        self.copy = os.path.join(self.tmp, "copied", "identity.py")
        os.makedirs(os.path.dirname(self.copy))
        shutil.copy(os.path.join(TOOLS, "identity.py"), self.copy)
        for n in ("base.json", "new.json"):
            write(os.path.join(self.tmp, n), "[]")

    def run_copy(self, env_extra, cwd):
        env = {k: v for k, v in os.environ.items() if k != "GAG_LAND_DIR"}
        env.update(env_extra)
        return subprocess.run([sys.executable, self.copy, self.tmp, self.tmp, os.path.join(self.tmp, "base.json"),
                               os.path.join(self.tmp, "new.json")], cwd=cwd, env=env, capture_output=True, text=True)

    def test_copied_script_finds_sectioncmp_via_env(self):
        land = os.path.join(TOOLS, "..", "land")
        r = self.run_copy({"GAG_LAND_DIR": land}, self.tmp)
        self.assertEqual(r.returncode, 0, r.stderr)
        self.assertIn("identity: 0 identical", r.stdout)

    def test_copied_script_without_sectioncmp_fails_loudly(self):
        r = self.run_copy({"GAG_LAND_DIR": os.path.join(self.tmp, "nowhere")}, self.tmp)
        self.assertEqual(r.returncode, 2)
        self.assertIn("cannot import sectioncmp", r.stderr)
        self.assertNotIn("identity:", r.stdout)

    def test_bound_names_compare_equal(self):
        bf = os.path.join(self.tmp, "bind.json")
        write(bf, json.dumps({"?DAT_00600000@@3HA": "0x00600000", "?g_name@@3HA": "0x00600000", "?other@@3HA": "0x00700000"}))
        old = os.environ.get("TUMIG_BINDINGS")
        os.environ["TUMIG_BINDINGS"] = bf
        self.addCleanup(lambda: os.environ.pop("TUMIG_BINDINGS") if old is None else os.environ.__setitem__("TUMIG_BINDINGS", old))
        saved = dict(identity.BIND)
        self.addCleanup(lambda: (identity.BIND.clear(), identity.BIND.update(saved)))
        identity.BIND.clear()
        identity.BIND.update(identity.load_bindings([[{"sym": "?f@@YAXXZ", "addr": "0x401000"}]]))
        self.assertEqual(identity.canon("?DAT_00600000@@3HA"), identity.canon("?g_name@@3HA"))
        self.assertNotEqual(identity.canon("?DAT_00600000@@3HA"), identity.canon("?other@@3HA"))
        self.assertEqual(identity.canon("?f@@YAXXZ"), "@0x401000")
        self.assertEqual(identity.canon("?unbound@@3HA"), "?unbound@@3HA")


SITES = {"TU001": {"strings": ["0x500000"], "push_sites": ["0x401000"]}}


def plan(dest, files):
    return dict(tu="TU001", name="Foo.cpp", lo=0x401000, hi=0x401fff, hi_earliest=0x401fff, lo_latest=0, sub=0,
                dest=dest, flags=" ".join(sorted(migrate.DEFAULT_FLAGS.split())), files=files, skipped=[], inits=[])


HDR = "// SPDX-License-Identifier: GPL-3.0-or-later\n// Provenance: own-binary-via-Ghidra\n\n"


class Compose(unittest.TestCase):
    def setUp(self):
        self.tree = tempfile.mkdtemp(prefix="tumig_c_")
        self.addCleanup(shutil.rmtree, self.tree, True)

    def test_dest_contributor_is_merged_not_deleted(self):
        write(os.path.join(self.tree, "match/x/dest.cpp"),
              HDR + "// FUNCTION: GAMEMD 0x401000\nint A() { return 1; }\n\n// FUNCTION: GAMEMD 0x409000\nint Z() { return 9; }\n")
        write(os.path.join(self.tree, "match/x/other.cpp"),
              HDR + "// FUNCTION: GAMEMD 0x401010\nint B() { return 2; }\n")
        p = plan("match/x/dest.cpp", [
            dict(file="match/x/dest.cpp", flags="", whole=False, move=[0], all_rows=[0x401000, 0x409000], rows=[0x401000], notes=[]),
            dict(file="match/x/other.cpp", flags="", whole=True, move=[0], all_rows=[0x401010], rows=[0x401010], notes=[])])
        text, rewrites, deleted = migrate.compose(self.tree, p, SITES)
        self.assertEqual(deleted, ["match/x/other.cpp"])
        self.assertNotIn("match/x/dest.cpp", rewrites)
        for needle in ("int A()", "int B()", "int Z()"):
            self.assertEqual(text.count(needle), 1, needle)
        self.assertLess(text.index("int A()"), text.index("int B()"))

    def test_split_file_globals_become_externs(self):
        write(os.path.join(self.tree, "match/x/split.cpp"),
              HDR + "int g_count = 5;\nunsigned char g_tbl[4] = {1,\n 2, 3, 4};\nstatic int s_local = 1;\nconst int kC = 3;\n"
              "int Proto(int);\ntypedef int T;\n\n// FUNCTION: GAMEMD 0x401000\nint A() { return g_count; }\n\n"
              "// FUNCTION: GAMEMD 0x409000\nint Z() { return 9; }\n")
        p = plan("match/x/new.cpp", [dict(file="match/x/split.cpp", flags="", whole=False, move=[0],
                                         all_rows=[0x401000, 0x409000], rows=[0x401000], notes=[])])
        text, rewrites, deleted = migrate.compose(self.tree, p, SITES)
        self.assertIn("extern int g_count;", text)
        self.assertIn("extern unsigned char g_tbl[4];", text)
        self.assertNotIn("g_count = 5", text)
        self.assertNotIn("g_tbl[4] =", text)
        self.assertIn("static int s_local = 1;", text)
        self.assertIn("const int kC = 3;", text)
        self.assertIn("int Proto(int);", text)
        self.assertIn("typedef int T;", text)
        # the definitions stay in the split source
        self.assertIn("int g_count = 5;", rewrites["match/x/split.cpp"])
        self.assertEqual(deleted, [])

    def test_apply_refuses_to_overwrite_non_contributor_dest(self):
        write(os.path.join(self.tree, "match/x/dest.cpp"), "int keep;\n")
        with self.assertRaises(SystemExit):
            migrate.apply(self.tree, plan("match/x/dest.cpp", []), SITES)
        self.assertEqual(open(os.path.join(self.tree, "match/x/dest.cpp")).read(), "int keep;\n")


class ForwardDeclarations(unittest.TestCase):
    def setUp(self):
        self.tree = tempfile.mkdtemp(prefix="tumig_f_")
        self.addCleanup(shutil.rmtree, self.tree, True)

    def test_heads(self):
        hs = cppsplit.heads("static inline double U() { return 1; }\nint C::m(int a) { return a; }\n"
                            "void* F(int a, float b);\nextern int g;\nint h = f(3);\nstruct S { int f(); };\n"
                            "// int Commented();\nconst char* s(const char* p) const { return \"{\"; }\n")
        self.assertEqual([(h["name"], h["kind"]) for h in hs], [("U", "def"), ("F", "decl"), ("s", "def")])
        self.assertEqual(hs[0]["proto"], "static inline double U();")

    def test_use_before_definition_in_address_order(self):
        # the helper sits behind a comment-only annotation (it belongs to chunk 0x402000), its user is at 0x401000
        write(os.path.join(self.tree, "match/x/a.cpp"),
              HDR + "// SYNTHETIC: GAMEMD 0x402000 -- anchor\nstatic inline int Helper(int v)\n{\n    return v + 1;\n}\n\n"
              "// FUNCTION: GAMEMD 0x401000\nint A() { return Helper(2); }\n")
        p = plan("match/x/new.cpp", [dict(file="match/x/a.cpp", flags="", whole=True, move=[0, 1],
                                         all_rows=[0x401000, 0x402000], rows=[0x401000, 0x402000], notes=[])])
        text, _, _ = migrate.compose(self.tree, p, SITES)
        self.assertEqual(text.count("static inline int Helper(int v);"), 1)
        self.assertLess(text.index("static inline int Helper(int v);"), text.index("int A()"))
        self.assertLess(text.index("int A()"), text.index("static inline int Helper(int v)\n{"))

    def test_use_in_hoisted_code_gets_the_prototype_in_front_of_it(self):
        write(os.path.join(self.tree, "match/x/a.cpp"),
              HDR + "typedef int T;\n\nint Wrapper(T v)\n{\n    return Helper(v);\n}\n\n"
              "// SYNTHETIC: GAMEMD 0x402000 -- anchor\nint Helper(T v)\n{\n    return v;\n}\n\n"
              "// FUNCTION: GAMEMD 0x401000\nint A() { return 1; }\n")
        p = plan("match/x/new.cpp", [dict(file="match/x/a.cpp", flags="", whole=True, move=[0, 1],
                                         all_rows=[0x401000, 0x402000], rows=[0x401000, 0x402000], notes=[])])
        text, _, _ = migrate.compose(self.tree, p, SITES)
        self.assertLess(text.index("typedef int T;"), text.index("int Helper(T v);"))
        self.assertLess(text.index("int Helper(T v);"), text.index("int Wrapper(T v)"))

    def test_canonical_header_declaration_wins(self):
        write(os.path.join(self.tree, "match/x/canon.h"), "int Helper(int v);\n")
        write(os.path.join(self.tree, "match/x/a.cpp"),
              HDR + '#include "canon.h"\n\n// SYNTHETIC: GAMEMD 0x402000 -- anchor\nint Helper(int v)\n{\n    return v;\n}\n\n'
              "// FUNCTION: GAMEMD 0x401000\nint A() { return Helper(1); }\n")
        p = plan("match/x/new.cpp", [dict(file="match/x/a.cpp", flags="", whole=True, move=[0, 1],
                                         all_rows=[0x401000, 0x402000], rows=[0x401000, 0x402000], notes=[])])
        text, _, _ = migrate.compose(self.tree, p, SITES)
        self.assertNotIn("Forward declaration", text)
        self.assertEqual(text.count("int Helper(int v);"), 0)


class ExistingDestination(unittest.TestCase):
    def setUp(self):
        self.root = tempfile.mkdtemp(prefix="tumig_d_")
        self.addCleanup(shutil.rmtree, self.root, True)
        self.saved = migrate.SR
        self.addCleanup(migrate.set_inputs, self.saved)
        migrate.set_inputs(os.path.join(self.root, "in"))
        write(migrate.TUMAP, "tu_id,name_or_bound,text_lo,text_hi,hi_earliest,lo_latest,sub_index\n"
                             "TU001,Foo.CPP,0x401000,0x401fff,0x401fff,0x401000,0\n")
        write(migrate.INIT_DELTA, "[]")
        self.tree = os.path.join(self.root, "tree")
        write(os.path.join(self.tree, "match/other.cpp"), HDR + "// FUNCTION: GAMEMD 0x401010\nint B() { return 2; }\n")
        write(os.path.join(self.tree, "match/Foo.cpp"), HDR + "int only_data = 1;\n")
        write(os.path.join(self.tree, "scripts/data/match_manifest.json"), json.dumps(
            [dict(tu="match/other.cpp", addr="0x401010", sym="?B@@YAHXZ", len="0x8", name="B", status="matched", pct=100)]))

    def test_plan_lists_an_existing_destination_as_contributor(self):
        p = migrate.plan(self.tree, "TU001", {}, None)
        self.assertEqual(p["dest"], "match/Foo.cpp")
        self.assertEqual([f["file"] for f in p["files"]], ["match/Foo.cpp", "match/other.cpp"])
        self.assertEqual(p["files"][0]["rows"], [])

    def test_apply_merges_into_it_and_keeps_its_code(self):
        p = migrate.plan(self.tree, "TU001", {}, None)
        subprocess.run(["git", "-C", self.tree, "init", "-q"], check=True)
        subprocess.run(["git", "-C", self.tree, "add", "."], check=True)
        res = migrate.apply(self.tree, p, SITES)
        text = open(os.path.join(self.tree, "match/Foo.cpp")).read()
        self.assertIn("int only_data = 1;", text)
        self.assertIn("int B()", text)
        self.assertEqual(res["deleted"], ["match/other.cpp"])

    def test_fit_never_skips_the_destination(self):
        calls = []

        def fake_cl(tree, rel, text, objdir):
            calls.append(text)
            return ("int B()" not in text) or True, ""

        saved = fit.cl
        fit.cl = fake_cl
        fit.SITES = SITES
        self.addCleanup(setattr, fit, "cl", saved)
        p = fit.fit(self.tree, "TU001", {}, self.root)
        self.assertIn("match/Foo.cpp", [f["file"] for f in p["files"]])
        # the destination alone must compile; a failing contributor is skipped, the destination is not
        fit.cl = lambda tree, rel, text, objdir: ("int B()" not in text, "x.cpp(1) : error C2371: 'g' : redefinition; different basic types\n")
        p = fit.fit(self.tree, "TU001", {}, self.root)
        self.assertEqual([f["file"] for f in p["files"]], ["match/Foo.cpp"])
        self.assertIn("TYPE CONFLICT", p["skipped"][-1]["why"])


class AttestedName(unittest.TestCase):
    def test_attested_name_replaces_a_family_guess(self):
        row = dict(name_or_bound="Ini.CPP", name_confidence="assert")
        self.assertEqual(migrate.attested_dest(row, "match/InfantryType.cpp"), "match/Ini.cpp")
        self.assertEqual(migrate.attested_dest(row, "match/ini.cpp"), "match/ini.cpp")
        self.assertIsNone(migrate.attested_dest(row, None))
        guess = dict(name_or_bound="Infantry.CPP", name_confidence="low")
        self.assertEqual(migrate.attested_dest(guess, "match/Other.cpp"), "match/Other.cpp")

    def test_plan_uses_the_attested_name(self):
        root = tempfile.mkdtemp(prefix="tumig_a_")
        self.addCleanup(shutil.rmtree, root, True)
        saved = migrate.SR
        self.addCleanup(migrate.set_inputs, saved)
        migrate.set_inputs(os.path.join(root, "in"))
        write(migrate.TUMAP, "tu_id,name_or_bound,text_lo,text_hi,hi_earliest,lo_latest,sub_index,name_confidence\n"
                             "TU001,Ini.CPP,0x401000,0x401fff,0x401fff,0x401000,0,assert\n")
        write(migrate.INIT_DELTA, "[]")
        tree = os.path.join(root, "tree")
        write(os.path.join(tree, "match/a.cpp"), HDR + "// FUNCTION: GAMEMD 0x401010\nint B() { return 2; }\n")
        write(os.path.join(tree, "scripts/data/match_manifest.json"), json.dumps(
            [dict(tu="match/a.cpp", addr="0x401010", sym="?B@@YAHXZ", len="0x8", name="B", status="matched", pct=100)]))
        self.assertEqual(migrate.plan(tree, "TU001", {}, "match/InfantryType.cpp")["dest"], "match/Ini.cpp")


class TypeConflict(unittest.TestCase):
    def test_conflicts_are_reported_not_hidden(self):
        log = ("a.cpp(3) : error C2371: 'DAT_00AC4E74' : redefinition; different basic types\n"
               "a.cpp(9) : error C2065: 'x' : undeclared identifier\n")
        self.assertEqual(len(fit.conflicts(log)), 1)
        self.assertIn("TYPE CONFLICT", fit.why_failed("p: ", log))
        self.assertEqual(fit.why_failed("p: ", "a.cpp(9) : error C2065: 'x' : undeclared identifier\n"),
                         "p: a.cpp(9) : error C2065: 'x' : undeclared identifier")


class DefinedGlobalsLast(unittest.TestCase):
    def setUp(self):
        self.tree = tempfile.mkdtemp(prefix="tumig_g_")
        self.addCleanup(shutil.rmtree, self.tree, True)

    def test_split_defined_globals(self):
        keep, blocks = migrate.split_defined_globals(
            ["typedef int T;", "// BEGIN defined globals (x)", "Foo g;", "// END defined globals", "int k;"])
        self.assertEqual(keep, ["typedef int T;", "int k;"])
        self.assertEqual(blocks, [["// BEGIN defined globals (x)", "Foo g;", "// END defined globals"]])

    def test_assert_on_a_chunk_variable_stays_behind_it(self):
        write(os.path.join(self.tree, "match/x/a.cpp"),
              HDR + "struct S { int a; };\nGG_STATIC_ASSERT(sizeof(S) == 4);\n\n// SYNTHETIC: GAMEMD 0x401000\ndouble g = 1.0 / h;\n"
              "\nGG_STATIC_ASSERT(sizeof(g) == 8);\nGG_STATIC_ASSERT(sizeof(S) == 4);\n")
        p = plan("match/x/new.cpp", [dict(file="match/x/a.cpp", flags="", whole=True, move=[0],
                                         all_rows=[0x401000], rows=[0x401000], notes=[])])
        text, _, _ = migrate.compose(self.tree, p, SITES)
        self.assertLess(text.index("double g ="), text.index("sizeof(g)"))
        self.assertEqual(text.count("sizeof(S) == 4"), 2)

    def test_trailing_definitions_are_not_hoisted_in_front_of_the_functions(self):
        # `Foo g;` has a constructor: its dynamic initialiser has to run after the initialisers of the functions' file part
        write(os.path.join(self.tree, "match/x/a.cpp"),
              HDR + "struct Foo { Foo(); };\nextern Foo g;\n\n// FUNCTION: GAMEMD 0x401000\nint A()\n{\n    return 1;\n}\n\n"
              "// BEGIN defined globals (x)\nFoo g;\n// END defined globals\n")
        write(os.path.join(self.tree, "match/x/b.cpp"), HDR + "// SYNTHETIC: GAMEMD 0x401800\nFoo h;\n")
        p = plan("match/x/new.cpp", [
            dict(file="match/x/a.cpp", flags="", whole=True, move=[0], all_rows=[0x401000], rows=[0x401000], notes=[]),
            dict(file="match/x/b.cpp", flags="", whole=True, move=[0], all_rows=[0x401800], rows=[0x401800], notes=[])])
        text, _, _ = migrate.compose(self.tree, p, SITES)
        self.assertLess(text.index("int A()"), text.index("Foo h;"))
        self.assertLess(text.index("Foo h;"), text.index("\nFoo g;"))
        self.assertEqual(text.count("Foo g;"), 2)   # the extern declaration and the definition


class InitOrder(unittest.TestCase):
    S = lambda self, n, d: (n, 0, "_$E%d" % n, d)

    def test_pairs_by_order_when_counts_and_bytes_agree(self):
        rows = [(0x63F510, "_$E5"), (0x63F4F0, "_$E2"), (0x63F690, "_$E8")]
        syms = [self.S(19, "a"), self.S(22, "b"), self.S(25, "c")]
        want = {0x63F4F0: "a", 0x63F510: "b", 0x63F690: "c"}
        self.assertEqual(initorder.pair(rows, syms, want), {0x63F4F0: "_$E19", 0x63F510: "_$E22", 0x63F690: "_$E25"})

    def test_check_xcu(self):
        a, b, c = ("_$E4", "A"), ("_$E7", "B"), ("_$E9", "C")
        self.assertTrue(initorder.check_xcu([a, b, c], [[a, b], [c]], [(0x10, "_$E4"), (0x20, "_$E9")]))
        with self.assertRaises(initorder.OrderError):      # a base object's own order changed
            initorder.check_xcu([b, a, c], [[a, b]], [])
        with self.assertRaises(initorder.OrderError):      # an initialiser is gone
            initorder.check_xcu([a, b], [[a, b, c]], [])
        with self.assertRaises(initorder.OrderError):      # rows out of retail address order
            initorder.check_xcu([a, b], [[a, b]], [(0x10, "_$E7"), (0x20, "_$E4")])

    def test_object_inits_are_in_section_order_not_name_order(self):
        import wwlib
        orig = (wwlib.sections, wwlib.defined_symbols, wwlib.section_bytes)
        wwlib.sections = lambda data: [(".text", 1, 0, 0)] * 12
        wwlib.defined_symbols = lambda data: [("_$E10", 2, 0, 3), ("_$E4", 9, 0, 3), ("_$E7", 11, 0, 3)]
        wwlib.section_bytes = lambda data, secs, s: bytes([s])
        self.addCleanup(lambda: (setattr(wwlib, "sections", orig[0]), setattr(wwlib, "defined_symbols", orig[1]),
                                 setattr(wwlib, "section_bytes", orig[2])))
        d = tempfile.mkdtemp(prefix="tumig_o_")
        self.addCleanup(shutil.rmtree, d, True)
        write(os.path.join(d, "x.obj"), "")
        self.assertEqual([s[2] for s in initorder.object_inits(os.path.join(d, "x.obj"))], ["_$E10", "_$E4", "_$E7"])

    def test_refuses_a_merge_that_changes_the_order(self):
        rows = [(0x63F4F0, "_$E2"), (0x63F510, "_$E5")]
        syms = [self.S(19, "b"), self.S(22, "a")]
        want = {0x63F4F0: "a", 0x63F510: "b"}
        with self.assertRaises(initorder.OrderError) as cm:
            initorder.pair(rows, syms, want)
        self.assertIn("0x63F510", str(cm.exception))

    def test_unmatched_initialisers_without_rows_are_skipped_by_digest(self):
        rows = [(0x10, "_$E2"), (0x30, "_$E6")]
        syms = [self.S(3, "a"), self.S(4, "zz"), self.S(7, "c")]
        self.assertEqual(initorder.pair(rows, syms, {0x10: "a", 0x30: "c"}), {0x10: "_$E3", 0x30: "_$E7"})

    def test_renumber_text_and_bindings(self):
        text = '[{"addr": "0x63F4F0", "sym": "_$E2"}, {"addr": "0x63F510", "sym": "_$E5"}]'
        new, ch = initorder.renumber_text(text, {"0x63F4F0": "_$E19", "0x63F510": "_$E22"})
        self.assertIn('"sym": "_$E22"', new)
        self.assertEqual(len(ch), 2)
        rk = initorder.rekey_bindings({"match/P.cpp::_$E2": "0x63F4F0", "match/Q.cpp::_$E2": "0x63F4F0"}, "match/P.cpp",
                                      {"0x63F4F0": "_$E19"})
        self.assertEqual(rk, [{"old": "match/P.cpp::_$E2", "new": "match/P.cpp::_$E19", "addr": "0x63F4F0"}])

    def test_identity_follows_a_renumbered_initialiser(self):
        d = tempfile.mkdtemp(prefix="tumig_n_")
        self.addCleanup(shutil.rmtree, d, True)
        row = lambda tu, sym: dict(addr="0x63F4F0", tu=tu, sym=sym)
        write(os.path.join(d, "b.json"), json.dumps([row("match/P.cpp", "_$E2")]))
        write(os.path.join(d, "n.json"), json.dumps([row("match/P.cpp", "_$E19")]))
        saved = (identity.sections, identity.load_sectioncmp)
        identity.sections = lambda od, tu: {"_$E2": ("h", ())} if od == "B" else {"_$E19": ("h", ())}
        identity.load_sectioncmp = lambda: None
        self.addCleanup(lambda: (setattr(identity, "sections", saved[0]), setattr(identity, "load_sectioncmp", saved[1])))
        old = sys.argv
        sys.argv = ["identity.py", "B", "N", os.path.join(d, "b.json"), os.path.join(d, "n.json"), "--all-touched", "match/P.cpp"]
        try:
            with self.assertRaises(SystemExit) as cm:
                identity.main()
        finally:
            sys.argv = old
        self.assertEqual(cm.exception.code, 0)


class Inputs(unittest.TestCase):
    def setUp(self):
        self.saved = migrate.SR
        self.addCleanup(migrate.set_inputs, self.saved)

    def test_missing_inputs_error_names_option(self):
        migrate.set_inputs(tempfile.mkdtemp(prefix="tumig_i_"))
        with self.assertRaises(SystemExit) as cm:
            migrate.check_inputs()
        self.assertIn("--inputs", str(cm.exception))
        self.assertIn("tu_map_v2.csv", str(cm.exception))

    def test_inputs_option_and_dirty_tree_refusal(self):
        root = tempfile.mkdtemp(prefix="tumig_i_")
        self.addCleanup(shutil.rmtree, root, True)
        write(os.path.join(root, "in/tumap2/tu_map_v2.csv"), "tu_id\n")
        write(os.path.join(root, "in/tumig1/assert_sites.json"), "{}")
        repo = os.path.join(root, "repo")
        write(os.path.join(repo, "a.cpp"), "int a;\n")
        for cmd in (["init", "-q"], ["add", "a.cpp"], ["-c", "user.name=t", "-c", "user.email=t@t", "commit", "-q", "-m", "x"]):
            subprocess.run(["git", "-C", repo] + cmd, check=True, capture_output=True)
        write(os.path.join(repo, "a.cpp"), "int a; // uncommitted\n")
        argv = ["fit.py", "--tree", repo, "--tu", "TU001", "--base-objs", root, "--base-manifest", root,
                "--out", os.path.join(root, "out"), "--inputs", os.path.join(root, "in")]
        old = sys.argv
        sys.argv = argv
        try:
            with self.assertRaises(SystemExit) as cm:
                fit.main()
        finally:
            sys.argv = old
        self.assertIn("uncommitted changes", str(cm.exception))
        self.assertEqual(open(os.path.join(repo, "a.cpp")).read(), "int a; // uncommitted\n")


class Classcheck(unittest.TestCase):
    def test_missing_vtable_cache_degrades(self):
        import contextlib
        import io
        import unittest.mock as mock
        from pathlib import Path
        sys.path.insert(0, os.path.dirname(TOOLS))
        import classcheck
        import common
        data = {"class_sizes.json": {"classes": []}, "ctor_field_offsets.json": {"constructors": []},
                "rtti_classes.json": {"classes": {}}}
        tmp = tempfile.mkdtemp(prefix="cc_cache_")
        self.addCleanup(shutil.rmtree, tmp, True)
        err = io.StringIO()
        with mock.patch.object(common, "CACHE", Path(tmp)), mock.patch.object(common, "load_json", data.__getitem__), \
                contextlib.redirect_stderr(err):
            ev = classcheck.evidence("NoSuchClass")
        self.assertEqual(ev["vtables"], [])
        self.assertIn("vtable_slots.py", err.getvalue())


if __name__ == "__main__":
    unittest.main()
