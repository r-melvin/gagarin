#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original synthetic compiler fixtures.
"""Check object isolation and failed-build handling without Wine or retail bytes."""

import contextlib
import io
import json
from pathlib import Path
import subprocess
import tempfile
import unittest
from unittest.mock import patch

import build_project


class ProjectBuildTests(unittest.TestCase):
    def test_same_basename_objects_are_distinct_and_indexed(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            units = []
            for subsystem in ("ai", "economy"):
                source = root / f"match/{subsystem}/same.cpp"
                source.parent.mkdir(parents=True)
                source.write_text("int fixture;\n")
                units.append(dict(path=source.relative_to(root).as_posix(), row_count=1,
                                  vc6_flags="/O2 /Gy", vc6_flags_source="fixture"))
            scripts = root / "scripts/vc6"
            scripts.mkdir(parents=True)
            (scripts / "vc6cl.sh").write_text("fixture")
            manifest = root / "scripts/data/match_manifest.json"
            manifest.parent.mkdir(parents=True)
            manifest.write_text("[]")
            header = root / "match/ai/shared.h"
            header.write_text("// header input\n")
            inventory = dict(subsystems=[dict(translation_units=units)], warnings=[])
            tracked = [unit["path"] for unit in units] + ["match/ai/shared.h"]

            def compiler(command, **kwargs):
                self.assertNotEqual(kwargs["stdout"], subprocess.PIPE)
                obj = Path(command[2][3:])
                obj.write_bytes(str(kwargs["cwd"]).encode())
                return subprocess.CompletedProcess(command, 0)

            out = root / "output"
            with patch.object(build_project, "build_inventory", return_value=(inventory, 0)), \
                    patch.object(build_project, "git_tracked_paths", return_value=tracked), \
                    patch.object(build_project.subprocess, "run", side_effect=compiler), \
                    patch.dict(build_project.os.environ, {"VC6_FLAGS": ""}), \
                    contextlib.redirect_stdout(io.StringIO()):
                self.assertEqual(build_project.build(root, out, 2), 0)
            index = json.loads((out / "objects.json").read_text())
            objects = [item["object"] for item in index["objects"]]
            self.assertEqual(objects, ["match/ai/same.obj", "match/economy/same.obj"])
            self.assertNotEqual((out / objects[0]).read_bytes(), (out / objects[1]).read_bytes())
            self.assertEqual(index["successful_objects"], 2)
            with patch.object(build_project, "git_tracked_paths", return_value=tracked), \
                    contextlib.redirect_stdout(io.StringIO()):
                self.assertEqual(build_project.check_index(root, out), 0)
                header.write_text("// changed header\n")
                with self.assertRaisesRegex(build_project.InventoryError, "source/header inputs changed"):
                    build_project.check_index(root, out)
                header.write_text("// header input\n")
                (out / objects[0]).write_bytes(b"changed object")
                with self.assertRaisesRegex(build_project.InventoryError, "object missing or changed"):
                    build_project.check_index(root, out)

    def test_stale_or_failed_compiler_objects_are_never_accepted(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            source = root / "match/core/a.cpp"
            source.parent.mkdir(parents=True)
            source.write_text("int fixture;\n")
            out = root / "output"
            obj = out / "match/core/a.obj"
            obj.parent.mkdir(parents=True)
            unit = dict(path="match/core/a.cpp", row_count=1, vc6_flags="/O2", vc6_flags_source="fixture")
            for code, creates_object in [(0, False), (1, True)]:
                obj.write_bytes(b"stale")

                def compiler(command, **kwargs):
                    self.assertFalse(obj.exists())
                    if creates_object:
                        obj.write_bytes(b"incomplete")
                    return subprocess.CompletedProcess(command, code)

                with patch.object(build_project.subprocess, "run", side_effect=compiler):
                    result = build_project.compile_unit(root, out, unit)
                self.assertFalse(result["success"])
                self.assertFalse(obj.exists())
                self.assertNotIn("object_sha256", result)


if __name__ == "__main__":
    unittest.main()
