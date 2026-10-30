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


def tu_row(tu, addr='0x401000'):
    return dict(tu=tu, addr=addr, sym='fixture', len='0x10', name='fixture',
                pct=50, status='partial')


def row(pct):
    return dict(tu='match/test/gate_fixture.cpp', addr='0x401000',
                sym='fixture', len='0x10', name='fixture', pct=pct,
                status='matched' if pct == 100 else 'partial')


class ObjectDirectoryTests(unittest.TestCase):
    def objects_of_one_run(self, entries):
        seen = []

        def fake_compile(cmd, **kwargs):
            out = [a for a in cmd if a.startswith('/Fo')][0][3:]
            seen.append(out)
            Path(out).write_bytes(b'obj')
            return subprocess.CompletedProcess(cmd, 0)

        with tempfile.TemporaryDirectory() as work:
            manifest = Path(work) / 'manifest.json'
            manifest.write_text(json.dumps(entries))
            with patch('sys.argv', ['verify_all.py', '--manifest', str(manifest)]), \
                    patch.object(verify_all.subprocess, 'run', side_effect=fake_compile), \
                    contextlib.redirect_stdout(io.StringIO()), \
                    self.assertRaises(SystemExit) as exit_status:
                verify_all.main()
        self.assertEqual(exit_status.exception.code, 0)
        return seen

    def test_objects_are_not_shared_tmp_va_files(self):
        seen = self.objects_of_one_run([tu_row('match/a/x.cpp')])
        self.assertEqual(len(seen), 1)
        self.assertNotEqual(os.path.dirname(seen[0]), tempfile.gettempdir())
        self.assertNotEqual(seen[0], '/tmp/va_x.obj')

    def test_same_basename_in_two_directories_gets_two_objects(self):
        seen = self.objects_of_one_run([tu_row('match/a/x.cpp', '0x401000'),
                                        tu_row('match/b/x.cpp', '0x402000')])
        self.assertEqual(len(seen), 2)
        self.assertEqual(len(set(seen)), 2)

    def test_two_runs_use_different_directories(self):
        first = self.objects_of_one_run([tu_row('match/a/x.cpp')])
        second = self.objects_of_one_run([tu_row('match/a/x.cpp')])
        self.assertNotEqual(os.path.dirname(first[0]), os.path.dirname(second[0]))


class SuffixCaseTests(unittest.TestCase):
    def test_object_name_keeps_stem_for_any_suffix_case(self):
        for tu, stem in (('match/a/Tag.CPP', 'Tag'), ('match/a/Ion.cpp', 'Ion'),
                         ('match/a/Raw.C', 'Raw'), ('match/a/low.c', 'low')):
            seen = []

            def fake_compile(cmd, **kwargs):
                seen.append([a for a in cmd if a.startswith('/Fo')][0][3:])
                return subprocess.CompletedProcess(cmd, 1)

            with tempfile.TemporaryDirectory() as objdir, \
                    patch.object(verify_all.subprocess, 'run', side_effect=fake_compile):
                verify_all.check_tu(7, tu, [], objdir)
                self.assertEqual(seen, [os.path.join(objdir, '7_%s.obj' % stem)], tu)


class GateDecisionTests(unittest.TestCase):
    def run_gate(self, entries, match=True, compiles=True, compiler_status=0):
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
                compiler.return_value.returncode = compiler_status
                verify_all.main()
            return exit_status.exception.code, compiler.call_count, oracle.call_count

    def test_partial_is_compiled_without_unused_oracle_call(self):
        self.assertEqual(self.run_gate([row(50)]), (0, 1, 0))

    def test_matched_rows_still_require_oracle(self):
        self.assertEqual(self.run_gate([row(100), row(50)]), (0, 1, 1))

    def test_partial_row_with_100_percent_diagnostic_stays_partial(self):
        entry = row(100)
        entry['status'] = 'partial'
        with tempfile.TemporaryDirectory() as work:
            manifest = Path(work) / 'manifest.json'
            manifest.write_text(json.dumps([entry]))
            output = io.StringIO()
            with patch('sys.argv', ['verify_all.py', '--manifest', str(manifest)]), \
                    patch.object(verify_all.os.path, 'exists', return_value=True), \
                    patch.object(verify_all.os, 'remove'), \
                    patch.object(verify_all.subprocess, 'run',
                                 return_value=subprocess.CompletedProcess([], 0)), \
                    patch.object(verify_all, 'verify', return_value=(True, '100.0%')) as oracle, \
                    contextlib.redirect_stdout(output), \
                    self.assertRaises(SystemExit) as exit_status:
                verify_all.main()
            self.assertEqual(exit_status.exception.code, 0)
            self.assertEqual(oracle.call_count, 0)
            self.assertIn('matched 0  partial 1', output.getvalue())

    def test_regressed_match_fails_gate(self):
        self.assertEqual(self.run_gate([row(100)], match=False), (1, 1, 1))

    def test_partial_compile_failure_still_fails_gate(self):
        self.assertEqual(self.run_gate([row(50)], compiles=False), (1, 1, 0))

    def test_failed_compiler_with_object_still_fails_gate(self):
        self.assertEqual(self.run_gate([row(100)], compiler_status=1), (1, 1, 0))

    def test_failed_oracles_cannot_report_success(self):
        result = subprocess.CompletedProcess([], 1, stdout='match: 100.0%')
        with patch.object(verify_all.subprocess, 'run', return_value=result):
            self.assertFalse(verify_all.verify('fixture.obj', 'fixture', '0x401000', '0x10')[0])

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
