#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original
"""Generated functions must participate in ownership and duplicate checks."""
import contextlib
import io
import json
import tempfile
import unittest
from pathlib import Path
from unittest.mock import patch

import check_duplicates


class SyntheticOwnershipTests(unittest.TestCase):
    def run_gate(self, duplicate, marker="SYNTHETIC"):
        with tempfile.TemporaryDirectory() as work:
            root = Path(work)
            source = root / 'match/test/generated.cpp'
            source.parent.mkdir(parents=True)
            source.write_text('// %s: GAMEMD 0x401000\n' % marker)
            if duplicate:
                (source.parent / 'standin.cpp').write_text(
                    '// FUNCTION: GAMEMD 0x401000\n')
            manifest = root / 'scripts/data/match_manifest.json'
            manifest.parent.mkdir(parents=True)
            manifest.write_text(json.dumps([
                {'addr': '0x401000', 'tu': 'match/test/generated.cpp'}]))
            output = io.StringIO()
            with patch.object(check_duplicates, 'ROOT', str(root)), \
                    contextlib.redirect_stdout(output), \
                    self.assertRaises(SystemExit) as status:
                check_duplicates.main()
            return status.exception.code, output.getvalue()

    def test_generated_function_can_own_manifest_row(self):
        code, output = self.run_gate(False)
        self.assertEqual(code, 0, output)

    def test_generated_function_colliding_with_standin_is_rejected(self):
        code, output = self.run_gate(True)
        self.assertEqual(code, 1, output)
        self.assertIn('DUPLICATE', output)


    def test_template_specialization_can_own_manifest_row(self):
        code, output = self.run_gate(False, marker="TEMPLATE")
        self.assertEqual(code, 0, output)

    def test_template_specialization_collision_is_rejected(self):
        code, output = self.run_gate(True, marker="TEMPLATE")
        self.assertEqual(code, 1, output)
        self.assertIn('DUPLICATE', output)


if __name__ == '__main__':
    unittest.main()


class LibraryMarkerTests(unittest.TestCase):
    def run_gate(self, files):
        with tempfile.TemporaryDirectory() as work:
            root = Path(work)
            for name, text in files.items():
                path = root / name
                path.parent.mkdir(parents=True, exist_ok=True)
                path.write_text(text)
            manifest = root / 'scripts/data/match_manifest.json'
            manifest.parent.mkdir(parents=True)
            manifest.write_text('[]')
            output = io.StringIO()
            with patch.object(check_duplicates, 'ROOT', str(root)), \
                    contextlib.redirect_stdout(output), \
                    self.assertRaises(SystemExit) as status:
                check_duplicates.main()
            return status.exception.code, output.getvalue()

    def test_library_marker_is_not_a_body_claim(self):
        code, output = self.run_gate({
            'match/_rt/lib.h': '// LIBRARY: GAMEMD 0x7c8a8e\n// _x\n',
            'match/a/a.cpp': '// LIBRARY: GAMEMD 0x7c8a8e\n'})
        self.assertEqual(code, 0, output)
        self.assertIn('1 marked LIBRARY', output)

    def test_library_and_body_on_one_address_is_reported_not_fatal(self):
        code, output = self.run_gate({
            'match/_rt/lib.h': '// LIBRARY: GAMEMD 0x7c8a8e\n',
            'match/a/a.cpp': '// FUNCTION: GAMEMD 0x7c8a8e\n'})
        self.assertEqual(code, 0, output)
        self.assertIn('NOTE', output)
