#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original synthetic repository fixture.
"""Tests source_inventory using only a temporary Git index and text fixtures."""

import json
import subprocess
import tempfile
import unittest
from pathlib import Path

import source_inventory


class SourceInventoryTests(unittest.TestCase):
    def test_tracked_scope_flags_rows_warnings_and_missing_paths(self):
        with tempfile.TemporaryDirectory(prefix="gagarin_source_inventory_") as tmp:
            root = Path(tmp)
            subprocess.run(["git", "init", "-q"], cwd=root, check=True)

            def write(relative, contents):
                path = root / relative
                path.parent.mkdir(parents=True, exist_ok=True)
                path.write_text(contents, encoding="utf-8")
                return path

            manifest = [
                {
                    "tu": "match/core/a.cpp",
                    "addr": "0x401000",
                    "sym": "MatchedFunction",
                    "len": "0x10",
                    "status": "matched",
                    "pct": 100,
                },
                {
                    "tu": "match/core/a.cpp",
                    "addr": "0x401010",
                    "sym": "PartialFunction",
                    "len": "0x10",
                    "status": "partial",
                    "pct": 50,
                },
                {
                    "tu": "match/ui/link.cpp",
                    "addr": "0x402000",
                    "sym": "LinkedSourceFunction",
                    "len": "0x10",
                    "status": "partial",
                    "pct": 75,
                },
                {
                    "tu": "match/core/missing.cpp",
                    "addr": "0x403000",
                    "sym": "MissingSourceFunction",
                    "len": "0x10",
                    "status": "matched",
                    "pct": 100,
                },
            ]
            write("scripts/data/match_manifest.json", json.dumps(manifest))
            write(
                "scripts/vc6/vc6cl.sh",
                'DEFAULT_FLAGS="/nologo /c /O2 /DNDEBUG /Gy /GX"\n',
            )
            write("match/core/a.cpp", "// VC6FLAGS:\n")
            write("match/ui/a.cpp", "// VC6FLAGS: /nologo /c /O1\n")
            write("match/ui/target.cpp", "// unreferenced target text\n")
            link = root / "match/ui/link.cpp"
            link.symlink_to("target.cpp")
            write("match/core/untracked.cpp", "// must not be inventoried\n")

            subprocess.run(
                [
                    "git",
                    "add",
                    "scripts/data/match_manifest.json",
                    "scripts/vc6/vc6cl.sh",
                    "match/core/a.cpp",
                    "match/ui/a.cpp",
                    "match/ui/link.cpp",
                ],
                cwd=root,
                check=True,
            )

            inventory, status = source_inventory.build_inventory(root)
            self.assertEqual(status, 1)
            self.assertEqual(inventory["tracked_cpp_count"], 3)
            self.assertNotIn(
                "match/core/untracked.cpp",
                [
                    unit["path"]
                    for group in inventory["subsystems"]
                    for unit in group["translation_units"]
                ],
            )
            self.assertEqual(
                inventory["tracked_cpp_without_manifest"], ["match/ui/a.cpp"]
            )
            self.assertEqual(
                inventory["manifest_tus_missing_tracked_cpp"],
                ["match/core/missing.cpp"],
            )
            self.assertEqual(
                inventory["missing_worktree_files"], ["match/ui/link.cpp"]
            )
            self.assertEqual(
                inventory["basename_collisions"],
                [
                    {
                        "basename": "a.cpp",
                        "paths": ["match/core/a.cpp", "match/ui/a.cpp"],
                    }
                ],
            )

            groups = {g["subsystem"]: g for g in inventory["subsystems"]}
            core = groups["core"]["translation_units"][0]
            self.assertEqual(core["vc6_flags"], "/nologo /c /O2 /DNDEBUG /Gy /GX")
            self.assertEqual(
                core["vc6_flags_source"],
                "vc6cl.sh DEFAULT_FLAGS (empty marker fallback)",
            )
            self.assertEqual(core["status_counts"], {"matched": 1, "partial": 1})

            ui_units = {unit["path"]: unit for unit in groups["ui"]["translation_units"]}
            self.assertEqual(ui_units["match/ui/a.cpp"]["vc6_flags"], "/nologo /c /O1")
            self.assertEqual(ui_units["match/ui/a.cpp"]["row_count"], 0)
            self.assertEqual(ui_units["match/ui/link.cpp"]["row_count"], 1)


if __name__ == "__main__":
    unittest.main()
