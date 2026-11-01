#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original project tooling.
"""Copy the match/ sources to a scratch tree that reccmp's annotation parser reads the way it was meant.

Run with reccmp's own interpreter (reccmp_image.py finds it from the reccmp-reccmp script).

match/ is never edited. The copy keeps every file's line count and every code line where it was (the PDB's
line records refer to them) and changes three things, each counted in the JSON report:

  string   reccmp 0.1.4 asserts (and aborts the whole run) when a STRING marker reaches a declaration that
           holds no string literal, which is an annotation error in our sources: the marker line becomes a
           comment reccmp does not read.
  listing  file headers list the TU's annotations as `//   FUNCTION: GAMEMD 0x...  Name` (two or more spaces after
           the slashes). reccmp reads each as a marker and then drops the real one as a duplicate: those lines
           become plain comments.
  rotate   reccmp ties a FUNCTION/GLOBAL/STRING/VTABLE marker to the line right after it, and takes a comment there
           for a by-name function. Our sources put a comment block between the marker and the signature, so the
           marker lines are moved down to sit just above the first code line (the comment lines shift up by the
           same count; nothing else moves).

Usage:  reccmp_sanitize.py SRC_DIR DST_DIR REPORT.json
"""

import json
from pathlib import Path
import re
import shutil
import sys

SUFFIXES = {".cpp", ".c", ".h", ".hpp", ".inl", ".inc", ".asm"}
STRING_MARKER = re.compile(r"^(\s*//\s*)STRING(\s*:)", re.I)
WINDOW = 12   # marker lines this far above the failing line are candidates
MARKER = re.compile(r"^\s*//\s*(?P<type>\w+):\s*GAMEMD\s+0x[0-9a-f]+", re.I)
LISTING = re.compile(r"^(\s*//)(\s{2,}|\t\s*)(\w+)(:\s*GAMEMD\s+0x[0-9a-f]+)", re.I)
ROTATE_TYPES = {"FUNCTION", "GLOBAL", "STRING", "VTABLE"}


def parses(path, lines):
    from reccmp.parser.parser import DecompParser   # only the parse check needs reccmp
    parser = DecompParser(None)
    parser.reset_and_set_filename(str(path))
    try:
        parser.read("\n".join(lines) + "\n")
    except AssertionError:
        return parser.line_number
    return None


def sanitize_file(path, lines):
    """(lines that parse, [(line number, original text)] changed)."""
    changed = []
    while (failed := parses(path, lines)) is not None:
        hits = [i for i in range(max(0, failed - WINDOW), min(len(lines), failed))
                if STRING_MARKER.match(lines[i]) and (i + 1, lines[i]) not in changed]
        if not hits:
            raise SystemExit(f"reccmp_sanitize: {path}:{failed} fails the annotation parser and no STRING marker is near it")
        for i in hits:
            changed.append((i + 1, lines[i]))
            lines[i] = STRING_MARKER.sub(r"\1STRING (unusable for reccmp)\2", lines[i], count=1)
    return lines, changed


def defang_listings(lines):
    """Turn header listing lines into plain comments; returns the changed line numbers."""
    changed = []
    for i, line in enumerate(lines):
        m = LISTING.match(line)
        if m and m.group(3).upper() in ROTATE_TYPES | {"LIBRARY", "TEMPLATE", "SYNTHETIC", "STUB"}:
            lines[i] = LISTING.sub(r"\1\2\3 (listing)\4", line, count=1)
            changed.append(i + 1)
    return changed


def rotate_markers(lines):
    """Move marker lines below the comment block that follows them; returns the first line number of each move."""
    moved, i, n = [], 0, len(lines)
    while i < n:
        m = MARKER.match(lines[i])
        if not m or m["type"].upper() not in ROTATE_TYPES:
            i += 1
            continue
        j, markers, others = i, [], []
        while j < n:
            line = lines[j]
            mm = MARKER.match(line)
            if mm:
                if mm["type"].upper() not in ROTATE_TYPES:
                    markers = None
                    break
                markers.append(line)
            elif line.strip() == "" or line.lstrip().startswith("//"):
                others.append(line)
            else:
                break
            j += 1
        if markers is None or j >= n or not others:
            i = max(j, i + 1)
            continue
        lines[i:j] = others + markers
        moved.append(i + 1)
        i = j
    return moved


def main(argv=None):
    src, dst, report = (Path(a) for a in (argv or sys.argv[1:]))
    shutil.rmtree(dst, ignore_errors=True)
    findings = {}
    counts = {"string": 0, "listing": 0, "rotate": 0}
    for path in sorted(p for p in src.rglob("*") if p.suffix.lower() in SUFFIXES and p.is_file()):
        rel = path.relative_to(src)
        text = path.read_text(encoding="utf-8", errors="surrogateescape")
        lines = text.split("\n")
        if lines and lines[-1] == "":
            lines.pop()
        listed = defang_listings(lines)
        moved = rotate_markers(lines)
        lines, changed = sanitize_file(path, lines)
        counts["listing"] += len(listed)
        counts["rotate"] += len(moved)
        counts["string"] += len(changed)
        out = dst / rel
        out.parent.mkdir(parents=True, exist_ok=True)
        out.write_text("\n".join(lines) + "\n", encoding="utf-8", errors="surrogateescape")
        if changed:
            findings[rel.as_posix()] = [[n, t.strip()] for n, t in changed]
    report.write_text(json.dumps({"files": len(list(dst.rglob("*"))), "changes": counts, "string_markers_unusable": findings}, indent=1) + "\n")
    print(f"sanitized copy of {src} in {dst}: {counts}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
