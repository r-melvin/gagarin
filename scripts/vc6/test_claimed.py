#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original
"""Regression checks for address ownership during parallel reconstruction."""
import contextlib
import io
import json
from pathlib import Path
import tempfile
import unittest
from unittest.mock import patch

import claimed


class ClaimedTests(unittest.TestCase):
    def run_claims(self, files, addresses, manifest=()):
        with tempfile.TemporaryDirectory() as root:
            for name, text in files.items():
                path = Path(root, name)
                path.parent.mkdir(parents=True, exist_ok=True)
                path.write_text(text)
            path = Path(root, 'scripts/data/match_manifest.json')
            path.parent.mkdir(parents=True, exist_ok=True)
            path.write_text(json.dumps(list(manifest)))
            output = io.StringIO()
            with patch.object(claimed, 'ROOT', root), contextlib.redirect_stdout(output):
                status = claimed.main(addresses)
            return status, output.getvalue()

    def test_provenance_mentions_do_not_claim(self):
        status, output = self.run_claims(
            {'match/view.cpp': '// Calls neighboring function 0x0043d030.\n'},
            ['0x43D030'])
        self.assertEqual(status, 0)
        self.assertIn('reference', output)
        self.assertIn('unclaimed', output)
        self.assertNotIn('BODY', output)

    def test_body_is_not_cancelled_by_later_callee_declaration(self):
        status, output = self.run_claims({'match/view.c':
            '// FUNCTION: GAMEMD 0x0043d030\nvoid f(void) {}\n'
            '// FUNCTION: GAMEMD 0x43D030 (decl; reloc)\n'}, ['0x43D030'])
        self.assertEqual(status, 1)
        self.assertIn('BODY', output)
        self.assertIn('decl-only', output)

    def test_headers_and_decl_only_annotations_do_not_claim(self):
        status, output = self.run_claims({
            'match/view.h': '    // FUNCTION: GAMEMD 0x43D030\n',
            'match/caller.cpp': '// FUNCTION: GAMEMD 0x0043D030 (decl; reloc)\n'
        }, ['0x43D030'])
        self.assertEqual(status, 0)
        self.assertIn('declares', output)
        self.assertIn('decl-only', output)

    def test_longer_hex_address_is_not_a_match(self):
        status, output = self.run_claims(
            {'match/view.cpp': '// FUNCTION: GAMEMD 0x43D0300\n'}, ['0x43D030'])
        self.assertEqual(status, 0)
        self.assertNotIn('BODY', output)
        self.assertIn('unclaimed', output)

    def test_manifest_claim_and_unclaimed_address_are_independent(self):
        status, output = self.run_claims({}, ['0x43D030', '0x43D040'],
            [{'addr': '0x0043D030', 'tu': 'match/view.cpp', 'name': 'f', 'pct': 100}])
        self.assertEqual(status, 1)
        self.assertIn('manifest', output)
        self.assertIn('unclaimed', output.split('0x0043d040')[1])


if __name__ == '__main__':
    unittest.main()
