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
