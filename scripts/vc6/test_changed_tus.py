#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original
"""Include-closure, --changed selection and report ordering; no binary needed."""
import contextlib
import io
import json
import tempfile
import time
import unittest
from pathlib import Path
from unittest.mock import patch

import changed_tus
import compile_all
import verify_all


def write(root, rel, text=""):
    path = Path(root) / rel
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(text)


class ClosureTests(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.root = self.tmp.name
        self.addCleanup(self.tmp.cleanup)
        write(self.root, "match/a/x.cpp", '#include "x.h"\n#include <windows.h>\n')
        write(self.root, "match/a/x.h", '  #  include "../_layout/l.h"\n// #include "never.h"\n')
        write(self.root, "match/_layout/l.h", '#include "m.h"\n')
        write(self.root, "match/_layout/m.h", '#include "l.h"\n')  # cycle
        write(self.root, "match/b/y.cpp", '#include "../_layout/m.h"\n#include "missing.h"\n')
        write(self.root, "match/c/z.cpp", "int z;\n")

    def test_transitive_closure_follows_quoted_includes_only(self):
        self.assertEqual(
            changed_tus.include_closure(self.root, "match/a/x.cpp"),
            {"match/a/x.cpp", "match/a/x.h", "match/_layout/l.h", "match/_layout/m.h"})

    def test_cycle_and_unresolved_include_terminate(self):
        self.assertEqual(
            changed_tus.include_closure(self.root, "match/b/y.cpp"),
            {"match/b/y.cpp", "match/_layout/m.h", "match/_layout/l.h"})

    def test_include_resolves_against_includer_chain_nearest_first(self):
        write(self.root, "match/d/w.cpp", '#include "shared/s.h"\n')
        write(self.root, "match/d/shared/s.h", '#include "t.h"\n')
        write(self.root, "match/d/t.h")  # next to the TU, not to s.h
        self.assertIn("match/d/t.h", changed_tus.include_closure(self.root, "match/d/w.cpp"))
        write(self.root, "match/d/shared/t.h")  # nearer: beside the includer
        got = changed_tus.include_closure(self.root, "match/d/w.cpp")
        self.assertIn("match/d/shared/t.h", got)
        self.assertNotIn("match/d/t.h", got)

    def test_header_change_selects_every_includer_transitively(self):
        units = ["match/a/x.cpp", "match/b/y.cpp", "match/c/z.cpp"]
        got = changed_tus.select_changed(self.root, units, changed={"match/_layout/m.h"})
        self.assertEqual(got, {"match/a/x.cpp", "match/b/y.cpp"})

    def test_source_change_selects_only_that_tu(self):
        units = ["match/a/x.cpp", "match/b/y.cpp", "match/c/z.cpp"]
        self.assertEqual(changed_tus.select_changed(self.root, units, changed={"match/c/z.cpp"}),
                         {"match/c/z.cpp"})

    def test_unrelated_change_selects_nothing(self):
        units = ["match/a/x.cpp", "match/c/z.cpp"]
        self.assertEqual(changed_tus.select_changed(self.root, units, changed={"README.md"}), set())

    def test_scoring_script_change_selects_everything(self):
        units = ["match/a/x.cpp", "match/c/z.cpp"]
        self.assertEqual(
            changed_tus.select_changed(self.root, units, changed={"scripts/vc6/diff_retail.py"}),
            set(units))

    def test_manifest_change_selects_changed_rows_only(self):
        units = ["match/a/x.cpp", "match/c/z.cpp"]
        got = changed_tus.select_changed(self.root, units, changed={changed_tus.MANIFEST},
                                         manifest_tus={"match/c/z.cpp"})
        self.assertEqual(got, {"match/c/z.cpp"})

    def test_layout_header_is_its_own_unit(self):
        got = changed_tus.select_changed(self.root, ["match/_layout/l.h", "match/_layout/m.h"],
                                         changed={"match/_layout/m.h"})
        self.assertEqual(got, {"match/_layout/l.h", "match/_layout/m.h"})


class OrderingTests(unittest.TestCase):
    def test_verify_report_is_independent_of_completion_order_and_jobs(self):
        tus = [f"match/t/t{i}.cpp" for i in range(6)]
        rows = []
        for i, tu in enumerate(tus):
            rows.append(dict(tu=tu, addr=f"0x{0x401000 + i:x}", sym="s", len="0x10",
                             name=f"n{i}", status="matched"))
            rows.append(dict(tu=tu, addr=f"0x{0x501000 + i:x}", sym="p", len="0x10",
                             name=f"p{i}", status="partial"))

        def fake_check(n, tu, tu_rows, objdir):
            time.sleep(0.05 * (len(tus) - n))  # earlier TUs finish last
            return True, [(tu_rows[0], n != 2, "50.0%")]

        outputs = []
        for jobs in ("1", "6"):
            with tempfile.TemporaryDirectory() as work:
                manifest = Path(work) / "m.json"
                manifest.write_text(json.dumps(list(reversed(rows))))
                out = io.StringIO()
                with patch("sys.argv", ["verify_all.py", "--manifest", str(manifest), "--jobs", jobs]), \
                        patch.object(verify_all, "check_tu", side_effect=fake_check), \
                        contextlib.redirect_stdout(out), self.assertRaises(SystemExit) as status:
                    verify_all.main()
                self.assertEqual(status.exception.code, 1)
                outputs.append(out.getvalue())
        self.assertEqual(outputs[0], outputs[1])
        lines = [l for l in outputs[0].splitlines() if l.startswith("  match/")]
        self.assertEqual([l.split()[0] for l in lines], tus)
        self.assertIn("5 matched (100%), 6 documented partials, 1 regressed, across 6 TUs", outputs[0])

    def test_verify_changed_restricts_tus_and_counts(self):
        rows = [dict(tu=f"match/t/t{i}.cpp", addr="0x1", sym="s", len="0x1", name="n", status="partial")
                for i in range(3)]
        with tempfile.TemporaryDirectory() as work:
            manifest = Path(work) / "m.json"
            manifest.write_text(json.dumps(rows))
            out = io.StringIO()
            with patch("sys.argv", ["verify_all.py", "--manifest", str(manifest), "--changed", "HEAD~1"]), \
                    patch.object(verify_all.changed_tus, "select_changed",
                                 return_value={"match/t/t1.cpp"}) as select, \
                    patch.object(verify_all, "check_tu", return_value=(True, [])), \
                    contextlib.redirect_stdout(out), self.assertRaises(SystemExit):
                verify_all.main()
        self.assertEqual(select.call_args[0][2], "HEAD~1")
        self.assertIn("1 of 3 TUs affected", out.getvalue())
        self.assertIn("across 1 TUs", out.getvalue())

    def test_compile_all_report_order_is_independent_of_jobs(self):
        def fake_tu(root, tmp, n, tu):
            time.sleep(0.05 * (5 - n))
            return (f"  ok   {tu}" if n != 1 else f"  FAIL {tu}"), (["err"] if n == 1 else []), n != 1

        results = []
        for jobs in ("1", "5"):
            out = io.StringIO()
            with patch.object(compile_all, "list_tus", return_value=[f"match/a/{i}.cpp" for i in range(5)]), \
                    patch.object(compile_all, "list_headers", return_value=["match/_layout/h.h"]), \
                    patch.object(compile_all, "check_tu", side_effect=fake_tu), \
                    patch.object(compile_all, "check_header",
                                 return_value=("  ok   match/_layout/h.h (asserts pass)", [], True)), \
                    contextlib.redirect_stdout(out):
                self.assertEqual(compile_all.main(["--jobs", jobs]), 1)
            results.append(out.getvalue())
        self.assertEqual(results[0], results[1])
        self.assertEqual(results[0].splitlines()[:3],
                         ["  ok   match/a/0.cpp", "  FAIL match/a/1.cpp", "err"])
        self.assertTrue(results[0].rstrip().endswith("=== compile_all: FAILURES ==="))


if __name__ == "__main__":
    unittest.main()
