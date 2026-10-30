#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original
"""Check compile_all's compiler launch without Wine."""
import os
import stat
import tempfile
import time
import unittest

import compile_all


class PipeInheritanceTests(unittest.TestCase):
    def test_lingering_descendant_does_not_stall(self):
        # The launcher leaves a background process holding its stdout, as a
        # wineserver does. compile_one must return when the launcher exits.
        with tempfile.TemporaryDirectory() as work:
            fake = os.path.join(work, "cl.sh")
            with open(fake, "w") as stream:
                stream.write('#!/usr/bin/env bash\n(sleep 20) &\n'
                             'echo "fatal error: boom"\n'
                             'case "$1" in /Fo*) ;; esac\nexit 1\n')
            os.chmod(fake, os.stat(fake).st_mode | stat.S_IXUSR)
            old = compile_all.CL
            compile_all.CL = fake
            try:
                start = time.time()
                ok, errs = compile_all.compile_one(work, work, ".", "x.cpp", "x.obj")
                took = time.time() - start
            finally:
                compile_all.CL = old
            self.assertFalse(ok)
            self.assertEqual(errs, ["fatal error: boom"])
            self.assertLess(took, 10)


class SuffixCaseTests(unittest.TestCase):
    def test_mixed_case_suffixes_are_listed_and_names_kept(self):
        with tempfile.TemporaryDirectory() as work:
            for rel in ("House.CPP", "Ion.cpp", "Tag.Cpp", "Raw.C", "low.c", "Skip.txt", "Hdr.H"):
                path = os.path.join(work, "match", "core", rel)
                os.makedirs(os.path.dirname(path), exist_ok=True)
                open(path, "w").close()
            os.makedirs(os.path.join(work, "match", "_layout"))
            for rel in ("A.H", "b.h", "c.cpp"):
                open(os.path.join(work, "match", "_layout", rel), "w").close()
            self.assertEqual(compile_all.list_tus(work), [
                "match/_layout/c.cpp",
                "match/core/House.CPP", "match/core/Ion.cpp", "match/core/Raw.C",
                "match/core/Tag.Cpp", "match/core/low.c"])
            self.assertEqual(compile_all.list_headers(work),
                             ["match/_layout/A.H", "match/_layout/b.h"])


if __name__ == "__main__":
    unittest.main()
