#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original; temporary fixture manifests and mocked compiler only.
"""Focused tests for selected-TU compilation and manifest selection."""

import contextlib
import io
import json
import tempfile
import unittest
from pathlib import Path
from types import SimpleNamespace
from unittest.mock import patch

try:
    import verify_tus
except ModuleNotFoundError:
    from scripts.vc6 import verify_tus


class CompileSelectedTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.root = Path(self.temp.name)
        self.out = self.root / "build-vc6"
        self.source = self.root / "match" / "test" / "fixture.cpp"
        self.source.parent.mkdir(parents=True)
        self.source.write_text("int fixture;\n", encoding="utf-8")
        self.patches = [
            patch.object(verify_tus, "ROOT", str(self.root)),
            patch.object(verify_tus, "OUT", str(self.out)),
            patch.object(verify_tus, "CL", "/fixture/vc6cl.sh"),
        ]
        for item in self.patches:
            item.start()

    def tearDown(self):
        for item in reversed(self.patches):
            item.stop()
        self.temp.cleanup()

    def compile(self, side_effect):
        with patch.object(verify_tus.subprocess, "run", side_effect=side_effect) as run:
            result = verify_tus.compile_tu("match/test/fixture.cpp")
        return result, run

    def test_success_creates_output_directory_and_requires_object(self):
        def compiler(command, **kwargs):
            Path(next(arg[3:] for arg in command if arg.startswith("/Fo"))).write_bytes(b"obj")
            return SimpleNamespace(returncode=0)

        (result, error), run = self.compile(compiler)
        self.assertEqual(error, "")
        self.assertEqual(Path(result).read_bytes(), b"obj")
        self.assertTrue(self.out.is_dir())
        self.assertEqual(run.call_args.kwargs["stderr"], verify_tus.subprocess.STDOUT)
        self.assertNotIn("capture_output", run.call_args.kwargs)

    def test_nonzero_exit_rejects_and_removes_partial_object(self):
        def compiler(command, **kwargs):
            Path(next(arg[3:] for arg in command if arg.startswith("/Fo"))).write_bytes(b"partial")
            kwargs["stdout"].write("fatal compiler diagnostic\n")
            return SimpleNamespace(returncode=2)

        (result, error), _ = self.compile(compiler)
        self.assertIsNone(result)
        self.assertIn("status 2", error)
        self.assertIn("fatal compiler diagnostic", error)
        self.assertFalse((self.out / "fixture.obj").exists())

    def test_stale_object_cannot_mask_success_without_new_output(self):
        self.out.mkdir()
        stale = self.out / "fixture.obj"
        stale.write_bytes(b"stale")
        (result, error), _ = self.compile(
            lambda *_args, **_kwargs: SimpleNamespace(returncode=0))
        self.assertIsNone(result)
        self.assertIn("produced no object", error)
        self.assertFalse(stale.exists())


class ManifestSelectionTests(unittest.TestCase):
    def test_main_reads_public_data_manifest_not_docs(self):
        with tempfile.TemporaryDirectory() as work:
            root = Path(work)
            public = root / "scripts" / "data" / "match_manifest.json"
            private = root / "docs" / "match_manifest.json"
            public.parent.mkdir(parents=True)
            private.parent.mkdir(parents=True)
            expected = {"tu": "match/public.cpp", "sym": "pub", "addr": "0x1",
                        "len": "0x1", "name": "pub", "status": "partial"}
            decoy = dict(expected, tu="match/private.cpp")
            public.write_text(json.dumps([expected]), encoding="utf-8")
            private.write_text(json.dumps([decoy]), encoding="utf-8")
            compiled = []

            def fake_compile(tu):
                compiled.append(tu)
                return "fixture.obj", ""

            with patch.object(verify_tus, "ROOT", str(root)), \
                    patch.object(verify_tus, "compile_tu", side_effect=fake_compile), \
                    patch.object(verify_tus, "verify", return_value=(True, "100.0%")), \
                    contextlib.redirect_stdout(io.StringIO()) as output:
                status = verify_tus.main([])

            self.assertEqual(status, 0)
            self.assertEqual(compiled, [expected["tu"]])
            self.assertIn("1 TUs", output.getvalue())


if __name__ == "__main__":
    unittest.main()
