#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Inventory tracked C++ translation units and their function manifest rows.

Provenance: original project tooling; reads tracked source paths, the tracked
match manifest, and the tracked VC6 wrapper. It does not discover untracked
work-in-progress files or inspect private documentation.
"""

from __future__ import annotations

import argparse
import json
import re
import subprocess
import sys
from collections import Counter, defaultdict
from pathlib import Path
from typing import Any


DEFAULT_MANIFEST = Path("scripts/data/match_manifest.json")
DEFAULT_WRAPPER = Path("scripts/vc6/vc6cl.sh")
VC6_MARKER = re.compile(r"^\s*//\s*VC6FLAGS:\s*(.*?)\s*$")
DEFAULT_FLAGS = re.compile(r'^DEFAULT_FLAGS="([^"]*)"\s*$')


class InventoryError(RuntimeError):
    pass


def git_tracked_paths(root: Path, *pathspecs: str) -> list[str]:
    result = subprocess.run(
        ["git", "ls-files", "-z", "--", *pathspecs],
        cwd=root,
        check=True,
        stdout=subprocess.PIPE,
    )
    return sorted(p.decode("utf-8") for p in result.stdout.split(b"\0") if p)


def read_tracked_text(root: Path, relative: str, tracked: set[str]) -> str:
    if relative not in tracked:
        raise InventoryError(f"required input is not git-tracked: {relative}")
    path = root / relative
    if path.is_symlink():
        raise InventoryError(f"refusing to follow tracked symlink: {relative}")
    try:
        return path.read_text(encoding="utf-8")
    except OSError as exc:
        raise InventoryError(f"cannot read tracked file {relative}: {exc}") from exc


def read_vc6_default(wrapper_text: str) -> str:
    for line in wrapper_text.splitlines():
        match = DEFAULT_FLAGS.match(line)
        if match:
            return match.group(1)
    raise InventoryError("could not find DEFAULT_FLAGS assignment in tracked vc6cl.sh")


def file_flags(source_text: str, default_flags: str) -> tuple[str, str]:
    for line in source_text.splitlines():
        match = VC6_MARKER.match(line)
        if match:
            value = match.group(1)
            if value:
                return value, "VC6FLAGS marker"
            return default_flags, "vc6cl.sh DEFAULT_FLAGS (empty marker fallback)"
    return default_flags, "vc6cl.sh DEFAULT_FLAGS"


def manifest_rows(manifest: Any) -> list[dict[str, Any]]:
    if isinstance(manifest, list):
        rows = manifest
    elif isinstance(manifest, dict) and isinstance(manifest.get("functions"), list):
        rows = manifest["functions"]
    else:
        raise InventoryError("manifest must be a function-row array")
    for index, row in enumerate(rows):
        if not isinstance(row, dict) or not isinstance(row.get("tu"), str):
            raise InventoryError(f"manifest row {index} has no string 'tu' field")
    return rows


def subsystem_for(path: str) -> str:
    parts = Path(path).parts
    if len(parts) >= 3 and parts[0] == "match":
        return parts[1]
    return "(match root)"


def summarize_rows(rows: list[dict[str, Any]]) -> dict[str, Any]:
    counts = Counter(str(row.get("status", "(missing)")) for row in rows)
    return {
        "row_count": len(rows),
        "status_counts": dict(sorted(counts.items())),
        "rows": [
            {
                "addr": row.get("addr"),
                "sym": row.get("sym"),
                "len": row.get("len"),
                "status": row.get("status"),
                "pct": row.get("pct"),
            }
            for row in sorted(
                rows,
                key=lambda row: (
                    str(row.get("addr", "")),
                    str(row.get("sym", "")),
                    str(row.get("name", "")),
                ),
            )
        ],
    }


def build_inventory(root: Path) -> tuple[dict[str, Any], int]:
    root = root.resolve()
    tracked_paths = set(
        git_tracked_paths(
            root,
            "match",
            str(DEFAULT_MANIFEST),
            str(DEFAULT_WRAPPER),
        )
    )
    tracked_cpp = sorted(path for path in tracked_paths if path.endswith(".cpp"))
    manifest_text = read_tracked_text(root, str(DEFAULT_MANIFEST), tracked_paths)
    wrapper_text = read_tracked_text(root, str(DEFAULT_WRAPPER), tracked_paths)
    try:
        rows = manifest_rows(json.loads(manifest_text))
    except json.JSONDecodeError as exc:
        raise InventoryError(f"invalid manifest JSON: {exc}") from exc

    default_flags = read_vc6_default(wrapper_text)
    by_tu: dict[str, list[dict[str, Any]]] = defaultdict(list)
    for row in rows:
        by_tu[row["tu"]].append(row)

    tracked_set = set(tracked_cpp)
    missing_tus = sorted(set(by_tu) - tracked_set)
    no_manifest = sorted(tracked_set - set(by_tu))
    missing_worktree_files: list[str] = []
    subsystem_tus: dict[str, list[dict[str, Any]]] = defaultdict(list)
    basenames: dict[str, list[str]] = defaultdict(list)

    for relative in tracked_cpp:
        basenames[Path(relative).name].append(relative)
        source_path = root / relative
        if source_path.is_symlink() or not source_path.is_file():
            missing_worktree_files.append(relative)
            source_text = ""
            flag_value, flag_source = default_flags, "vc6cl.sh DEFAULT_FLAGS"
        else:
            source_text = read_tracked_text(root, relative, tracked_paths)
            flag_value, flag_source = file_flags(source_text, default_flags)

        row_summary = summarize_rows(by_tu.get(relative, []))
        subsystem_tus[subsystem_for(relative)].append(
            {
                "path": relative,
                "vc6_flags": flag_value,
                "vc6_flags_source": flag_source,
                **row_summary,
            }
        )

    collisions = [
        {"basename": name, "paths": sorted(paths)}
        for name, paths in sorted(basenames.items())
        if len(paths) > 1
    ]
    groups = []
    for name, units in sorted(subsystem_tus.items()):
        status_counts: Counter[str] = Counter()
        for unit in units:
            status_counts.update(unit["status_counts"])
        groups.append(
            {
                "subsystem": name,
                "translation_unit_count": len(units),
                "manifest_row_count": sum(unit["row_count"] for unit in units),
                "status_counts": dict(sorted(status_counts.items())),
                "translation_units": units,
            }
        )

    warnings = []
    if no_manifest:
        warnings.append("tracked .cpp files with no manifest rows are listed separately")
    if missing_tus:
        warnings.append("manifest translation units are absent from tracked .cpp files")
    if collisions:
        warnings.append("tracked C++ basenames are not unique; use paths in build lists")
    if missing_worktree_files:
        warnings.append("some tracked C++ paths are missing or symlinks in the worktree")

    inventory = {
        "schema_version": 1,
        "scope": "git ls-files -z -- match; tracked .cpp files only",
        "flags_model": {
            "wrapper": str(DEFAULT_WRAPPER),
            "default_flags": default_flags,
            "tu_marker": "first // VC6FLAGS: marker, matching vc6cl.sh behavior",
            "note": "An ambient VC6_FLAGS environment variable overrides both at compile time.",
        },
        "tracked_cpp_count": len(tracked_cpp),
        "manifest_row_count": len(rows),
        "subsystems": groups,
        "tracked_cpp_without_manifest": no_manifest,
        "manifest_tus_missing_tracked_cpp": missing_tus,
        "basename_collisions": collisions,
        "missing_worktree_files": missing_worktree_files,
        "warnings": warnings,
    }
    return inventory, int(bool(missing_tus or missing_worktree_files))


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--repo", type=Path, default=Path(__file__).resolve().parents[2])
    parser.add_argument("--out", type=Path, help="write JSON here instead of stdout")
    args = parser.parse_args()
    try:
        inventory, status = build_inventory(args.repo)
    except (InventoryError, subprocess.CalledProcessError) as exc:
        print(f"source_inventory: error: {exc}", file=sys.stderr)
        return 1

    output = json.dumps(inventory, indent=2, sort_keys=True) + "\n"
    if args.out:
        args.out.write_text(output, encoding="utf-8")
    else:
        sys.stdout.write(output)
    for warning in inventory["warnings"]:
        print(f"source_inventory: warning: {warning}", file=sys.stderr)
    return status


if __name__ == "__main__":
    raise SystemExit(main())
