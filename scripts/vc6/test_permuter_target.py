#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original
"""Permuter targets must preserve memory bytes across analysis gaps."""
import importlib.util
import contextlib
import io
import json
import subprocess
import unittest
from pathlib import Path
from unittest.mock import patch

spec = importlib.util.spec_from_file_location(
    'permuter_target', Path(__file__).resolve().parents[1] / 'permuter/make_target.py')
target = importlib.util.module_from_spec(spec)
spec.loader.exec_module(target)


class TargetMemoryTests(unittest.TestCase):
    def read(self, blocks, length=8):
        result = subprocess.CompletedProcess([], 0, stdout=json.dumps(blocks))
        with patch.object(target.subprocess, 'run', return_value=result) as run:
            value = target.func_bytes(0x401000, length)
        self.assertEqual(run.call_args.args[0][1:],
                         ['memory', 'read', '0x401000', str(length)])
        self.assertTrue(run.call_args.kwargs['check'])
        return value

    def test_reads_all_bytes_without_reconstructing_instruction_listing(self):
        # Synthetic memory: the middle bytes must survive even when an
        # analysis provider would omit their instructions from the body.
        self.assertEqual(self.read([
            {'address': '0x401000', 'hex': '00010203'},
            {'address': '0x401004', 'hex': '04050607'}]), bytes(range(8)))

    def test_rejects_memory_gap_instead_of_joining_blocks(self):
        with self.assertRaisesRegex(ValueError, 'noncontiguous'):
            self.read([{'address': '0x401000', 'hex': '00010203'},
                       {'address': '0x401006', 'hex': '0607'}])

    def test_rejects_short_memory_read(self):
        with self.assertRaisesRegex(ValueError, '4 of 8'):
            self.read([{'address': '0x401000', 'hex': '00010203'}])

    def test_requires_explicit_span_before_any_analysis_query(self):
        with patch('sys.argv', ['make_target.py', '--addr', '0x401000',
                                '--out', '/tmp/unused-target.o']), \
                patch.object(target.subprocess, 'run') as run, \
                contextlib.redirect_stderr(io.StringIO()), \
                self.assertRaises(SystemExit) as status:
            target.main()
        self.assertEqual(status.exception.code, 2)
        run.assert_not_called()


if __name__ == '__main__':
    unittest.main()
