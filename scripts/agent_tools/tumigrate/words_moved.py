#!/usr/bin/env python3
"""Forbidden-word hits in added lines that are NOT verbatim moves of removed lines.
  words_moved.py TREE BASE"""
import os, subprocess, sys, collections
sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..', 'land'))
from landlib import FORBID_RE
tree, base = sys.argv[1:3]
out = subprocess.run(['git', '-C', tree, 'diff', '-U0', '--no-color', base, '--'], capture_output=True, text=True).stdout
rem = collections.Counter(l[1:].strip() for l in out.splitlines() if l.startswith('-') and not l.startswith('---'))
hits = []
for l in out.splitlines():
    if l.startswith('+') and not l.startswith('+++') and FORBID_RE.search(l):
        k = l[1:].strip()
        if rem[k] > 0:
            rem[k] -= 1
        else:
            hits.append(l)
for h in hits: print('NEW-WORD', h[:200])
print('new-word hits:', len(hits))
sys.exit(1 if hits else 0)
