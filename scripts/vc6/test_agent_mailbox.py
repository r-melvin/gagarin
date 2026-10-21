#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original; synthetic local coordination fixtures.
import importlib.util
import json
from pathlib import Path
import tempfile
import unittest

spec = importlib.util.spec_from_file_location('agent_mailbox', Path(__file__).resolve().parents[1] / 'orchestration/agent_mailbox.py')
mailbox = importlib.util.module_from_spec(spec)
spec.loader.exec_module(mailbox)


class MailboxTests(unittest.TestCase):
    def state(self):
        return {'schema': 1, 'tasks': {
            'first': {'owner': 'claude', 'status': 'queued', 'addresses': ['0x401000']}
        }, 'messages': [], 'cursors': {}, 'blocked_addresses': []}

    def test_claim_owner_overlap_and_cap(self):
        state = self.state()
        with self.assertRaises(mailbox.QueueError):
            mailbox.claim(state, 'first', 'other')
        state['blocked_addresses'] = ['0x401000']
        with self.assertRaises(mailbox.QueueError):
            mailbox.claim(state, 'first', 'claude')
        state['blocked_addresses'] = []
        state['tasks']['second'] = {'owner': 'codex', 'status': 'review', 'addresses': ['0x401000']}
        with self.assertRaises(mailbox.QueueError):
            mailbox.claim(state, 'first', 'claude')
        del state['tasks']['second']
        self.assertEqual(mailbox.claim(state, 'first', 'claude')['status'], 'active')
        self.assertEqual(mailbox.claim(state, 'first', 'claude')['status'], 'active')

    def test_persistence_and_rollback(self):
        with tempfile.TemporaryDirectory() as directory:
            with mailbox.locked_state(directory) as state:
                state.update(self.state())
                mailbox.post(state, 'claude', 'codex', 'Evidence ready')
            with mailbox.locked_state(directory) as state:
                self.assertEqual(state['messages'][0]['id'], 1)
                self.assertEqual(state['messages'][0]['message'], 'Evidence ready')
                self.assertEqual(mailbox.post(state, 'codex', 'claude', 'Reviewing')['id'], 2)
            before = (Path(directory) / 'state.json').read_bytes()
            with self.assertRaises(RuntimeError):
                with mailbox.locked_state(directory) as state:
                    state['messages'].clear()
                    raise RuntimeError('abort')
            self.assertEqual((Path(directory) / 'state.json').read_bytes(), before)

    def test_unknown_schema_rejected(self):
        with tempfile.TemporaryDirectory() as directory:
            (Path(directory) / 'state.json').write_text(json.dumps({'schema': 2}))
            with self.assertRaises(mailbox.QueueError):
                with mailbox.locked_state(directory):
                    pass


if __name__ == '__main__':
    unittest.main()
