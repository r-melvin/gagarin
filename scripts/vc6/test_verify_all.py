#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original
"""Check gate decisions without Wine, Ghidra or a retail binary."""
import contextlib
import io
import json
import os
import shlex
import signal
import subprocess
import sys
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

    def test_exited_compiler_does_not_wait_for_inherited_output(self):
        """A Wine descendant can retain stdout after the compiler exits."""
        with tempfile.TemporaryDirectory() as work:
            root = Path(work)
            source = root / 'match/test' / (root.name + '.cpp')
            source.parent.mkdir(parents=True)
            source.write_text('int fixture;\n')
            scripts = root / 'scripts/vc6'
            scripts.mkdir(parents=True)
            child_pid = root / 'descendant.pid'
            compiler = root / 'compiler.py'
            compiler.write_text(
                'import pathlib, subprocess, sys\n'
                "obj = next(a[3:] for a in sys.argv[1:] if a.startswith('/Fo'))\n"
                "pathlib.Path(obj).write_text('fixture')\n"
                "child = subprocess.Popen([sys.executable, '-c', "
                "'import time; time.sleep(30)'])\n"
                f'pathlib.Path({str(child_pid)!r}).write_text(str(child.pid))\n')
            (scripts / 'vc6cl.sh').write_text(
                shlex.quote(sys.executable) + ' ' + shlex.quote(str(compiler)) + ' "$@"\n')
            entry = row(50)
            entry['tu'] = str(source.relative_to(root))
            manifest = root / 'manifest.json'
            manifest.write_text(json.dumps([entry]))
            runner = (
                f'import sys; sys.path.insert(0, {str(Path(verify_all.__file__).parent)!r}); '
                f'import verify_all; verify_all.ROOT = {str(root)!r}; '
                f'sys.argv = ["verify_all.py", "--manifest", {str(manifest)!r}]; '
                'verify_all.main()')
            try:
                result = subprocess.run([sys.executable, '-c', runner],
                                        capture_output=True, text=True, timeout=5)
                self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
                self.assertIn('1 documented partials', result.stdout)
            finally:
                if child_pid.exists():
                    try:
                        os.kill(int(child_pid.read_text()), signal.SIGTERM)
                    except ProcessLookupError:
                        pass
                Path('/tmp/va_' + source.stem + '.obj').unlink(missing_ok=True)


if __name__ == '__main__':
    unittest.main()
