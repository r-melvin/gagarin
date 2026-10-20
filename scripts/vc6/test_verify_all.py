#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original
"""Check gate decisions without Wine, Ghidra or a retail binary."""
import contextlib
import io
import json
import tempfile
import unittest
from pathlib import Path
from unittest.mock import patch

import verify_all


def row(pct):
    return dict(tu='match/test/gate_fixture.cpp', addr='0x401000',
                sym='fixture', len='0x10', name='fixture', pct=pct,
                status='matched' if pct == 100 else 'partial')


class GateDecisionTests(unittest.TestCase):
    def run_gate(self, entries, match=True, compiles=True):
        with tempfile.TemporaryDirectory() as work:
            manifest = Path(work) / 'manifest.json'
            manifest.write_text(json.dumps(entries))
            with patch('sys.argv', ['verify_all.py', '--manifest', str(manifest)]), \
                    patch.object(verify_all.os.path, 'exists', return_value=compiles), \
                    patch.object(verify_all.os, 'remove'), \
                    patch.object(verify_all.subprocess, 'run') as compiler, \
                    patch.object(verify_all, 'verify', return_value=(match, '0.0%')) as oracle, \
                    contextlib.redirect_stdout(io.StringIO()), \
                    self.assertRaises(SystemExit) as exit_status:
                verify_all.main()
            return exit_status.exception.code, compiler.call_count, oracle.call_count

    def test_partial_is_compiled_without_unused_oracle_call(self):
        self.assertEqual(self.run_gate([row(50)]), (0, 1, 0))

    def test_matched_rows_still_require_oracle(self):
        self.assertEqual(self.run_gate([row(100), row(50)]), (0, 1, 1))

    def test_regressed_match_fails_gate(self):
        self.assertEqual(self.run_gate([row(100)], match=False), (1, 1, 1))

    def test_partial_compile_failure_still_fails_gate(self):
        self.assertEqual(self.run_gate([row(50)], compiles=False), (1, 1, 0))


if __name__ == '__main__':
    unittest.main()
