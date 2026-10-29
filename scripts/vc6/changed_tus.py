#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original project tooling.
"""Select translation units affected by a change, for --changed in the gates.

A TU is affected when its own source, or any file in its transitive quoted
#include closure, differs from a git ref (tracked diff plus untracked files).
Angle-bracket includes are toolchain headers and are not followed. Quoted
includes resolve against the including file's directory, then the TU's
directory, as the period compiler does. Includes in comments or #if 0 count as
dependencies, which can only widen the set.

A change to the toolchain wrapper or to a scoring script invalidates every
TU, and a changed manifest invalidates the TUs whose rows changed.
"""
import json
import os
import re
import subprocess

INCLUDE_RE = re.compile(r'^\s*#\s*include\s*"([^"]+)"', re.MULTILINE)

# A change to any of these can change the score of any TU.
GLOBAL_INPUTS = (
    "scripts/vc6/vc6cl.sh", "scripts/vc6/raw_match.py", "scripts/vc6/diff_retail.py",
    "scripts/vc6/retail_image.py", "scripts/vc6/verify_vtable.py",
    "scripts/vc6/verify_all.py", "scripts/vc6/changed_tus.py",
    "scripts/vc6/compile_all.py", "scripts/vc6/compile_all.sh",
)
MANIFEST = "scripts/data/match_manifest.json"


def direct_includes(root, rel, cache):
    """Repo-relative quoted include targets of `rel` that exist (cached)."""
    if rel in cache:
        return cache[rel]
    try:
        with open(os.path.join(root, rel), encoding="latin-1") as stream:
            text = stream.read()
    except OSError:
        text = ""
    cache[rel] = found = INCLUDE_RE.findall(text)
    return found


def include_closure(root, tu, cache=None):
    """Set of repo-relative paths (the TU included) reachable from `tu`.

    Resolution follows the period compiler (logic reused from the landing
    tools' IncludeIndex): the directory of the including file, then the
    directories of each file that included it, nearest first, ending at the
    TU's own directory (the compile's working directory).
    """
    cache = {} if cache is None else cache
    seen = {tu}
    stack = [(tu, [os.path.dirname(tu)])]
    while stack:
        current, chain = stack.pop()
        for name in direct_includes(root, current, cache):
            for base in [os.path.dirname(current)] + chain[::-1]:
                candidate = os.path.normpath(os.path.join(base, name)).replace(os.sep, "/")
                if os.path.isfile(os.path.join(root, candidate)):
                    if candidate not in seen:
                        seen.add(candidate)
                        stack.append((candidate, chain + [os.path.dirname(candidate)]))
                    break
    return seen


def git_lines(root, *args):
    out = subprocess.run(["git", *args], cwd=root, capture_output=True, text=True, check=True)
    return [line for line in out.stdout.split("\0" if "-z" in args else "\n") if line]


def changed_paths(root, ref="HEAD"):
    """Paths differing from `ref` in the working tree, including untracked files."""
    paths = set(git_lines(root, "diff", "--name-only", "-z", ref, "--"))
    paths.update(git_lines(root, "ls-files", "-z", "--others", "--exclude-standard"))
    return paths


def manifest_changed_tus(root, ref):
    """TUs whose manifest rows differ between `ref` and the working tree."""
    def by_tu(rows):
        grouped = {}
        for row in rows:
            grouped.setdefault(row["tu"], []).append(json.dumps(row, sort_keys=True))
        return {tu: sorted(v) for tu, v in grouped.items()}
    old = subprocess.run(["git", "show", f"{ref}:{MANIFEST}"], cwd=root,
                         capture_output=True, text=True)
    old_rows = by_tu(json.loads(old.stdout)) if old.returncode == 0 else {}
    with open(os.path.join(root, MANIFEST)) as stream:
        new_rows = by_tu(json.load(stream))
    return {tu for tu in set(old_rows) | set(new_rows) if old_rows.get(tu) != new_rows.get(tu)}


def select_changed(root, units, ref="HEAD", changed=None, manifest_tus=None):
    """Subset of `units` (repo-relative TU paths) affected by the change.

    `changed` / `manifest_tus` may be supplied (tests); otherwise from git.
    """
    changed = changed_paths(root, ref) if changed is None else set(changed)
    if any(path in changed for path in GLOBAL_INPUTS):
        return set(units)
    if manifest_tus is None:
        manifest_tus = manifest_changed_tus(root, ref) if MANIFEST in changed else set()
    cache = {}
    return {tu for tu in units
            if tu in manifest_tus or include_closure(root, tu, cache) & changed}
