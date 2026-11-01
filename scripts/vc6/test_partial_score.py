#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original project tooling.
"""Tests for partial_score.py and refresh_partials.py (no compiler, no retail image).

A fake repo root holds stand-in vc6cl.sh and diff_retail.py scripts, so the plumbing (patch skips,
exit status, manifest left alone) is checked without Wine.
"""
import atexit
import contextlib
import io
import json
import os
import shutil
import tempfile
import unittest

import partial_score
import refresh_partials

PATCHES = {"patches": [
    {"addr": "0x49F5C0", "patched_insns": ["mov al,0x1", "ret"], "overwritten_insns": ["push ecx", "push ebx", "push esi"]},
    {"addr": "0x4A80D0", "patched_insns": ["mov eax,0x2", "ret"], "overwritten_insns": ["sub esp,0x120"]},
]}


def fake_root(compile_ok=True):
    d = tempfile.mkdtemp(prefix="partial_score_")
    atexit.register(shutil.rmtree, d, True)
    os.makedirs(os.path.join(d, "scripts/vc6"))
    os.makedirs(os.path.join(d, "scripts/data"))
    json.dump(PATCHES, open(os.path.join(d, "scripts/data/distribution_patches.json"), "w"))
    # vc6cl.sh: /Fo<obj> <src>; writes an empty object unless told to fail.
    open(os.path.join(d, "scripts/vc6/vc6cl.sh"), "w").write(
        '#!/bin/bash\n%s\nfor a in "$@"; do case "$a" in /Fo*) : > "${a#/Fo}";; esac; done\n' %
        ("" if compile_ok else "exit 1"))
    # diff_retail.py: score 90.0 unless --skip is given, then 100.0; echoes the skip it saw.
    open(os.path.join(d, "scripts/vc6/diff_retail.py"), "w").write(
        "import sys\n"
        "a = sys.argv\n"
        "print('match: %s%%' % ('100.0' if '--skip' in a else '90.0'))\n"
        "if '--skip' in a:\n"
        "    print('skip=' + a[a.index('--skip') + 1], file=sys.stderr)\n")
    return d


def row(addr, **kw):
    r = {"tu": "match/a.cpp", "addr": addr, "sym": "?f@@YAXXZ", "len": "0x10", "name": "f",
         "status": "partial", "pct": 50.0}
    r.update(kw)
    return r


class PatchSkips(unittest.TestCase):
    def test_counts_instructions_of_both_sides(self):
        d = fake_root()
        self.assertEqual(partial_score.patch_skips(d), {"0x49f5c0": "2,3", "0x4a80d0": "2,1"})

    def test_missing_table_means_no_skips(self):
        self.assertEqual(partial_score.patch_skips(tempfile.mkdtemp()), {})

    def test_the_tree_table_names_every_patched_row_the_manifest_holds(self):
        root = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
        skips = partial_score.patch_skips(root)
        self.assertTrue(skips)
        for k, v in skips.items():
            r, c = (int(x) for x in v.split(","))
            self.assertGreaterEqual(r, 1)
            self.assertGreaterEqual(c, 1)


class Score(unittest.TestCase):
    def test_patched_row_is_scored_past_the_patch(self):
        d = fake_root()
        self.assertEqual(partial_score.score(d, "x.obj", row("0x49F5C0")), 100.0)

    def test_unpatched_row_is_scored_whole(self):
        d = fake_root()
        self.assertEqual(partial_score.score(d, "x.obj", row("0x49F5C4")), 90.0)

    def test_no_percentage_line_is_no_score(self):
        d = fake_root()
        open(os.path.join(d, "scripts/vc6/diff_retail.py"), "w").write("print('error')\n")
        self.assertIsNone(partial_score.score(d, "x.obj", row("0x49F5C0")))


class Refresh(unittest.TestCase):
    def run_refresh(self, root, rows):
        m = os.path.join(root, "manifest.json")
        json.dump(rows, open(m, "w"))
        src = os.path.join(root, "match")
        os.makedirs(src, exist_ok=True)
        open(os.path.join(src, "a.cpp"), "w").write("")
        old_root, refresh_partials.ROOT = refresh_partials.ROOT, root
        out, err = io.StringIO(), io.StringIO()
        try:
            with contextlib.redirect_stdout(out), contextlib.redirect_stderr(err):
                argv, refresh_partials.sys.argv = refresh_partials.sys.argv, ["refresh_partials", "--manifest", m]
                try:
                    rc = refresh_partials.main()
                finally:
                    refresh_partials.sys.argv = argv
        finally:
            refresh_partials.ROOT = old_root
        return rc, out.getvalue(), err.getvalue(), json.load(open(m))

    def test_all_rows_failing_to_compile_is_an_error_and_leaves_the_manifest(self):
        d = fake_root(compile_ok=False)
        rows = [row("0x49F5C0", best_pct=96.0), row("0x500000")]
        rc, out, err, after = self.run_refresh(d, rows)
        self.assertEqual(rc, 1)
        self.assertIn("all 2 partial rows failed to compile", err)
        self.assertEqual(after, rows)

    def test_clean_run_rewrites_the_pct(self):
        d = fake_root()
        rows = [row("0x500000")]
        rc, out, err, after = self.run_refresh(d, rows)
        self.assertEqual(rc, 0)
        self.assertEqual(after[0]["pct"], 90.0)

    def test_patched_row_is_refreshed_past_its_patch(self):
        d = fake_root()
        rows = [row("0x49F5C0", pct=3.3, best_pct=96.0)]
        rc, out, err, after = self.run_refresh(d, rows)
        self.assertEqual((rc, after[0]["pct"], after[0]["best_pct"]), (0, 100.0, 100.0))

    def test_matched_only_manifest_is_a_clean_no_op(self):
        d = fake_root(compile_ok=False)
        rc, out, err, after = self.run_refresh(d, [row("0x500000", status="matched", pct=100)])
        self.assertEqual(rc, 0)


if __name__ == "__main__":
    unittest.main()
