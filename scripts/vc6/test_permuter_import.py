#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original; subprocess regression for the local permuter adapter.
import os
from pathlib import Path
import subprocess
import sys
import tempfile
import unittest


class PermuterAdapterImportTests(unittest.TestCase):
    def test_adapter_loads_outside_repository_without_pythonpath(self):
        adapter = Path(__file__).resolve().parents[1] / 'permuter/obj_to_blob.py'
        environment = dict(os.environ)
        environment.pop('PYTHONPATH', None)
        with tempfile.TemporaryDirectory() as directory:
            result = subprocess.run(
                [sys.executable, '-I', '-c',
                 'import runpy,sys; runpy.run_path(sys.argv[1], run_name="import_test")',
                 str(adapter)], cwd=directory, env=environment,
                capture_output=True, text=True)
        self.assertEqual(result.returncode, 0, result.stderr)


if __name__ == '__main__':
    unittest.main()
