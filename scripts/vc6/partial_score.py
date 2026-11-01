#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original project tooling; scores compiled objects against the retail span, embeds no retail bytes.
"""Measure a partial manifest row the way the manifest records it.

refresh_partials.py and the landing gates share this, so the number a row carries and the
number a gate re-measures come from one rule:

  * the span is the row's explicit `len` (diff_retail refuses an inferred one);
  * a function carrying a distribution patch (scripts/data/distribution_patches.json) is
    scored past the patched prologue: retail drops the patch instructions and the compiled
    side drops the original instructions the patch replaced, so the 3-byte `mov al,1 / ret`
    over `push ecx / push ebx / push esi` does not misalign every later instruction.
    Without that skip a patched function that matches everywhere else scores about 1%.

`score(root, obj, row)` returns the percentage, or None when diff_retail gives no score.
"""
import json
import os
import subprocess

PATCHES = "scripts/data/distribution_patches.json"


def patch_skips(root):
    """{lower-case address: 'RETAIL,COMPILED'} instruction counts to drop, from the tree's patch table."""
    path = os.path.join(root, PATCHES)
    if not os.path.isfile(path):
        return {}
    out = {}
    for p in json.load(open(path)).get("patches", []):
        out[p["addr"].lower()] = "%d,%d" % (len(p["patched_insns"]), len(p["overwritten_insns"]))
    return out


def score(root, obj, row, skips=None, env=None):
    """Percentage of `row` (a manifest entry) that `obj` matches against retail, or None."""
    if skips is None:
        skips = patch_skips(root)
    cmd = ["python3", os.path.join(root, "scripts/vc6/diff_retail.py"), "--obj", obj,
           "--sym", row["sym"], "--addr", row["addr"], "--len", row["len"]]
    skip = skips.get(row["addr"].lower())
    if skip:
        cmd += ["--skip", skip]
    out = subprocess.run(cmd, capture_output=True, text=True, env=env).stdout.strip()
    if not out.endswith("%"):
        return None
    return float(out.splitlines()[-1].split(":")[1].strip().rstrip("%"))
