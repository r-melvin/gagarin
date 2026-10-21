#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original; local file-based agent coordination, no network calls.
"""Shared worktree mailbox and address claims. Messages are data, not commands.

The default state lives beside the common .git directory in .coordination/,
so worktrees share one registry. This is cooperative locking, not an access
control boundary. Inbox polling does not wake another agent's process.
"""
import argparse
from contextlib import contextmanager
from datetime import datetime, timezone
import fcntl
import json
import os
from pathlib import Path
import subprocess
import tempfile


class QueueError(ValueError):
    pass


def shared_directory():
    result = subprocess.run(['git', 'rev-parse', '--path-format=absolute', '--git-common-dir'],
                            check=True, text=True, capture_output=True)
    return Path(result.stdout.strip()).parent / '.coordination'


@contextmanager
def locked_state(directory):
    directory = Path(directory)
    directory.mkdir(parents=True, exist_ok=True)
    with (directory / 'lock').open('a') as lock:
        fcntl.flock(lock, fcntl.LOCK_EX)
        path = directory / 'state.json'
        state = json.loads(path.read_text()) if path.exists() else {
            'schema': 1, 'tasks': {}, 'messages': [], 'cursors': {}, 'blocked_addresses': []}
        if state.get('schema') != 1:
            raise QueueError('unsupported coordination schema')
        original = json.dumps(state, sort_keys=True)
        yield state
        if json.dumps(state, sort_keys=True) != original:
            temp_path = None
            try:
                with tempfile.NamedTemporaryFile(mode='w', dir=directory, delete=False) as tmp:
                    temp_path = Path(tmp.name)
                    json.dump(state, tmp, indent=2)
                    tmp.write('\n')
                    tmp.flush()
                    os.fsync(tmp.fileno())
                os.replace(temp_path, path)
            finally:
                if temp_path and temp_path.exists():
                    temp_path.unlink()


def post(state, sender, recipient, message):
    entry = {'id': max((m['id'] for m in state['messages']), default=0) + 1,
             'from': sender, 'to': recipient, 'message': message,
             'utc': datetime.now(timezone.utc).isoformat()}
    state['messages'].append(entry)
    return entry


def claim(state, task_id, agent):
    task = state['tasks'].get(task_id)
    if task is None:
        raise QueueError('unknown task; ask the integrator to assign a cluster')
    if task['owner'] != agent:
        raise QueueError('task belongs to another agent')
    if task['status'] == 'active':
        return task
    if task['status'] != 'queued':
        raise QueueError('task is not queued')
    addresses = {int(a, 0) for a in task['addresses']}
    if addresses & {int(a, 0) for a in state.get('blocked_addresses', [])}:
        raise QueueError('task overlaps an excluded/capped address')
    for other_id, other in state['tasks'].items():
        if other_id != task_id and other['status'] in ('queued', 'active', 'review'):
            if addresses & {int(a, 0) for a in other['addresses']}:
                raise QueueError('address overlap with ' + other_id)
    task['status'] = 'active'
    return task


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--state-dir', type=Path)
    commands = ap.add_subparsers(dest='command', required=True)
    commands.add_parser('status')
    inbox = commands.add_parser('inbox')
    inbox.add_argument('--agent', required=True)
    inbox.add_argument('--ack', action='store_true')
    send = commands.add_parser('post')
    send.add_argument('--agent', required=True)
    send.add_argument('--to', required=True)
    text = send.add_mutually_exclusive_group(required=True)
    text.add_argument('--message')
    text.add_argument('--file', type=Path)
    take = commands.add_parser('claim')
    take.add_argument('--agent', required=True)
    take.add_argument('--task', required=True)
    submit = commands.add_parser('submit')
    submit.add_argument('--agent', required=True)
    submit.add_argument('--task', required=True)
    submit.add_argument('--commit')
    submit.add_argument('--note', required=True)
    args = ap.parse_args()
    try:
        with locked_state(args.state_dir or shared_directory()) as state:
            if args.command == 'status':
                output = state['tasks']
            elif args.command == 'post':
                output = post(state, args.agent, args.to,
                              args.file.read_text() if args.file else args.message)
            elif args.command == 'inbox':
                cursor = state['cursors'].get(args.agent, 0)
                output = [m for m in state['messages'] if m['id'] > cursor
                          and m['to'] in (args.agent, 'all')]
                if args.ack and output:
                    state['cursors'][args.agent] = max(m['id'] for m in output)
            elif args.command == 'claim':
                output = claim(state, args.task, args.agent)
            else:
                task = state['tasks'].get(args.task)
                if task is None or task['owner'] != args.agent or task['status'] != 'active':
                    raise QueueError('submission requires your active task')
                if args.commit:
                    subprocess.run(['git', 'cat-file', '-e', args.commit + '^{commit}'],
                                   check=True, capture_output=True)
                task.update(status='review', commit=args.commit, result=args.note)
                output = post(state, args.agent, 'codex',
                              'Review task ' + args.task + ': ' + args.note)
        print(json.dumps(output, indent=2))
        return 0
    except (OSError, ValueError, subprocess.CalledProcessError) as exc:
        ap.exit(1, 'agent_mailbox: ' + str(exc) + '\n')


if __name__ == '__main__':
    raise SystemExit(main())
