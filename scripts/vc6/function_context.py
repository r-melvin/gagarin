#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original project tooling; reads only tracked gagarin metadata/source and generated object metadata.
"""Emit a compact, non-authoritative context report for manifest addresses.

This preflight does not compile, compare with retail, infer ABI from a name, or
claim that a recorded manifest status has just been re-verified.
"""

from __future__ import annotations

import argparse
import contextlib
import hashlib
import io
import json
import re
import struct
import subprocess
import sys
from pathlib import Path, PurePosixPath
from typing import Any


def sha256(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def tracked_paths(root: Path, pathspec: str) -> set[str]:
    command = ["git", "ls-files", "-z"]
    if pathspec:
        command.extend(["--", pathspec])
    result = subprocess.run(
        command, cwd=root, check=True,
        stdout=subprocess.PIPE, stderr=subprocess.PIPE,
    )
    return {part.decode("utf-8") for part in result.stdout.split(b"\0") if part}


def checked_path(root: Path, relative: str, tracked: set[str], *, under_match: bool = False) -> Path:
    pure = PurePosixPath(relative)
    if pure.is_absolute() or ".." in pure.parts or not pure.parts:
        raise ValueError(f"unsafe repository path: {relative!r}")
    if under_match and (not pure.parts or pure.parts[0] != "match"):
        raise ValueError(f"source path is outside match/: {relative!r}")
    normalized = pure.as_posix()
    if normalized not in tracked:
        raise ValueError(f"path is not tracked: {normalized}")
    path = root.joinpath(*pure.parts)
    match_root = (root / "match").resolve()
    resolved = path.resolve(strict=False)
    if under_match and not resolved.is_relative_to(match_root):
        raise ValueError(f"resolved source escapes match/: {normalized}")
    # Do not follow a tracked symlink, including one in an intermediate directory.
    current = root
    for part in pure.parts:
        current = current / part
        if current.is_symlink():
            raise ValueError(f"refusing tracked symlink: {normalized}")
    if not path.is_file():
        raise ValueError(f"tracked file is missing: {normalized}")
    return path


def reject_symlink_components(path: Path, label: str) -> None:
    """Reject symlinks in an absolute filesystem path before opening descendants."""
    absolute = path.absolute()
    current = Path(absolute.anchor)
    for part in absolute.parts[1:]:
        current = current / part
        if current.is_symlink():
            raise ValueError(f"refusing symlink component in {label}: {current}")


def load_json(path: Path) -> Any:
    return json.loads(path.read_text(encoding="utf-8"))


def parse_address(text: str) -> int:
    if not re.fullmatch(r"0[xX][0-9a-fA-F]{1,8}", text):
        raise argparse.ArgumentTypeError("address must be 0x followed by 1-8 hex digits")
    return int(text, 16)


def decorated_member_owner_hint(symbol: str) -> tuple[str | None, str | None]:
    """Return limited MSVC method/owner-name hints; never ABI or class-key evidence."""
    match = re.match(r"^\?([^@]+)@([^@]+)@@", symbol)
    if not match:
        return None, None
    return match.group(1), match.group(2)


def source_declared_type_names(root: Path, tu_path: Path, tracked_match: set[str]) -> dict[str, Any]:
    """Collect declared class/struct names from tracked includes; not COFF class keys."""
    match_root = (root / "match").resolve()
    pending = [tu_path]
    visited: set[Path] = set()
    scanned: set[str] = set()
    names: set[str] = set()
    problems: list[str] = []
    class_re = re.compile(r"\b(?:class|struct)\s+([A-Za-z_][A-Za-z_0-9]*)\b")
    include_re = re.compile(r'^\s*#\s*include\s*"([^"]+)"', re.M)

    def local_include(parent: Path, include: str) -> Path | None:
        parts = PurePosixPath(include)
        if parts.is_absolute():
            problems.append(f"absolute include omitted: {include}")
            return None
        current = parent
        for part in parts.parts:
            if part in ("", "."):
                continue
            if part == "..":
                current = current.parent
            else:
                current = current / part
            if not current.absolute().is_relative_to(match_root):
                problems.append(f"include escapes match/: {include}")
                return None
            if current.is_symlink():
                problems.append(f"symlink include omitted: {include}")
                return None
        return current

    while pending:
        path = pending.pop()
        resolved = path.absolute()
        if resolved in visited:
            continue
        visited.add(resolved)
        resolved_target = resolved.resolve(strict=False)
        if not resolved_target.is_relative_to(match_root):
            problems.append(f"include outside match/: {path}")
            continue
        try:
            rel = resolved.relative_to(root.resolve()).as_posix()
        except ValueError:
            problems.append(f"include outside project root: {path}")
            continue
        try:
            safe = checked_path(root, rel, tracked_match, under_match=True)
        except ValueError as exc:
            problems.append(str(exc))
            continue
        scanned.add(rel)
        text = safe.read_text(encoding="utf-8", errors="replace")
        code = re.sub(r"/\*.*?\*/|//[^\n]*", " ", text, flags=re.S)
        code = re.sub(r'"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'', " ", code)
        code = re.sub(r"\b__declspec\s*\([^()]*\)", " ", code)
        names.update(class_re.findall(code))
        for include in include_re.findall(text):
            candidate = local_include(safe.parent, include)
            if candidate is not None:
                pending.append(candidate)
    return {"declared_type_names": sorted(names), "files_scanned": sorted(scanned),
            "gaps": sorted(set(problems))}


def validate_index_paths(root: Path, object_dir: Path, index: dict[str, Any], tracked_all: set[str],
                         tracked_match: set[str]) -> None:
    """Validate every path check_index may read before invoking that helper."""
    reject_symlink_components(object_dir, "object directory")
    for field in ("input_sha256",):
        values = index.get(field)
        if not isinstance(values, dict):
            raise ValueError(f"object index {field} is not a path mapping")
        for relative in values:
            if not isinstance(relative, str):
                raise ValueError(f"object index {field} contains a non-string path")
            checked_path(root, relative, tracked_all, under_match=True)
    for name in ("scripts/vc6/vc6cl.sh", "scripts/data/match_manifest.json"):
        checked_path(root, name, tracked_all)
    objects = index.get("objects")
    if not isinstance(objects, list):
        raise ValueError("object index objects is not an array")
    base = object_dir.resolve()
    for item in objects:
        if not isinstance(item, dict):
            raise ValueError("object index contains a non-object entry")
        source = item.get("source")
        if not isinstance(source, str):
            raise ValueError("object index entry has no source path")
        checked_path(root, source, tracked_match, under_match=True)
        for key in ("object", "log"):
            relative = item.get(key)
            if not isinstance(relative, str):
                raise ValueError(f"object index entry has no {key} path")
            pure = PurePosixPath(relative)
            if pure.is_absolute() or ".." in pure.parts or not pure.parts:
                raise ValueError(f"unsafe {key} path in object index: {relative!r}")
            path = object_dir.joinpath(*pure.parts)
            current = object_dir
            for part in pure.parts:
                current = current / part
                if current.is_symlink():
                    raise ValueError(f"refusing symlink {key} path in object index: {relative}")
            if not path.resolve(strict=False).is_relative_to(base):
                raise ValueError(f"{key} path in object index escapes object directory: {relative}")


def manifest_row_groups(manifest: Any) -> dict[int, list[dict[str, Any]]]:
    rows = manifest if isinstance(manifest, list) else manifest.get("functions", [])
    if not isinstance(rows, list):
        raise ValueError("manifest must be a row array or contain a functions array")
    grouped: dict[int, list[dict[str, Any]]] = {}
    for index, row in enumerate(rows):
        if not isinstance(row, dict) or not isinstance(row.get("addr"), str):
            continue
        try:
            addr = int(row["addr"], 16)
        except ValueError:
            continue
        grouped.setdefault(addr, []).append({**row, "_manifest_index": index})
    return grouped


def address_field(row: dict[str, Any]) -> int | None:
    value = row.get("addr", row.get("address"))
    try:
        return int(value, 16) if isinstance(value, str) else None
    except ValueError:
        return None


def census_context(row: dict[str, Any] | None) -> dict[str, Any] | None:
    if row is None:
        return None
    keys = ("addr", "entry_source", "entry_point_is_lead", "confidence", "inferred",
            "insn_count", "ret_imm", "ret_imms", "conflicting_returns",
            "reads_ecx_before_write", "reads_edx_before_write", "tail_jump_targets", "ghidra_name")
    return {key: row[key] for key in keys if key in row}


def extent_context(row: dict[str, Any] | None) -> dict[str, Any] | None:
    if row is None:
        return None
    # Whitelist metadata only; never serialize byte strings or arbitrary audit payloads.
    keys = ("address", "source", "symbol", "old_size", "corrected_size", "reason",
            "normalized_raw_match", "newly_covered_relocation_fields",
            "newly_covered_relocation_targets_verified", "full_span_strict_relocation_fields",
            "source_sha256", "object_sha256", "compiler_flags", "source_correction")
    return {key: row[key] for key in keys if key in row}


def index_currentness(root: Path, object_dir: Path, index: dict[str, Any],
                      tracked_all: set[str], tracked_match: set[str]) -> dict[str, Any]:
    """Reuse build_project's authoritative input/object freshness check."""
    helper_dir = root / "scripts" / "vc6"
    if str(helper_dir) not in sys.path:
        sys.path.insert(0, str(helper_dir))
    import build_project  # imported from the target project's tracked scripts

    output = io.StringIO()
    with contextlib.redirect_stdout(output):
        try:
            validate_index_paths(root, object_dir, index, tracked_all, tracked_match)
            status = build_project.check_index(root, object_dir)
            reason = output.getvalue().strip()
        except Exception as exc:  # Keep a useful report for stale/malformed indexes.
            status = 1
            reason = f"{type(exc).__name__}: {exc}"
    return {"current": status == 0, "check_output": reason,
            "index_success": bool(index.get("success")),
            "input_scope": index.get("input_scope"),
            "indexed_source_count": index.get("source_count"),
            "indexed_successful_objects": index.get("successful_objects")}


def function_aux_size(data: bytes, symbol_index: int, symbol: dict[str, Any],
                      auxiliary: dict[int, bytes]) -> int | None:
    """Read a COFF function auxiliary TotalSize when a section-defined symbol has one."""
    if symbol.get("section", 0) <= 0 or symbol.get("storage_class") == 105:
        return None
    if symbol.get("aux_count", 0) < 1:
        return None
    if len(data) < 20:
        return None
    symbol_table = struct.unpack_from("<I", data, 8)[0]
    symbol_offset = symbol_table + symbol_index * 18
    if symbol_offset + 18 > len(data):
        return None
    symbol_type = struct.unpack_from("<H", data, symbol_offset + 14)[0]
    if not symbol_type & 0x20:  # IMAGE_SYM_DTYPE_FUNCTION
        return None
    record = auxiliary.get(symbol_index + 1)
    if record is None or len(record) < 8:
        return None
    size = int.from_bytes(record[4:8], "little")
    return size or None


def analyze_object(root: Path, object_dir: Path, index: dict[str, Any], row: dict[str, Any],
                   tracked_match: set[str]) -> dict[str, Any]:
    source_rel = row.get("tu")
    if not isinstance(source_rel, str):
        return {"error": "manifest row has no translation-unit path"}
    try:
        source_path = checked_path(root, source_rel, tracked_match, under_match=True)
    except ValueError as exc:
        return {"error": str(exc), "source_path": source_rel}
    source_hash = sha256(source_path)
    if not index.get("_currentness", {}).get("current"):
        return {"source_path": source_rel, "source_sha256": source_hash,
                "error": "object index is stale or contains unsafe paths; COFF preflight suppressed"}
    entries = [item for item in index.get("objects", []) if item.get("source") == source_rel]
    if len(entries) != 1:
        return {"source_path": source_rel, "source_sha256": source_hash,
                "error": f"object index has {len(entries)} entries for this TU"}
    item = entries[0]
    result: dict[str, Any] = {
        "source_path": source_rel,
        "source_sha256": source_hash,
        "indexed_source_sha256": item.get("source_sha256"),
        "source_matches_index": source_hash == item.get("source_sha256"),
        "compiler_flags": item.get("flags"),
        "flags_source": item.get("flags_source"),
        "object_path": item.get("object"),
        "object_sha256": item.get("object_sha256"),
        "object_success": item.get("success"),
    }
    if not item.get("success"):
        result["error"] = "object index records this TU as unsuccessful"
        return result
    relative_obj = PurePosixPath(str(item.get("object", "")))
    if relative_obj.is_absolute() or ".." in relative_obj.parts or not relative_obj.parts:
        result["error"] = "unsafe object path in index"
        return result
    object_path = object_dir.joinpath(*relative_obj.parts)
    if object_path.is_symlink() or not object_path.is_file():
        result["error"] = "indexed object missing or is a symlink"
        return result
    if not object_path.resolve().is_relative_to(object_dir.resolve()):
        result["error"] = "indexed object resolves outside object directory"
        return result
    if sha256(object_path) != item.get("object_sha256"):
        result["error"] = "object hash differs from object index"
        return result
    if not result["source_matches_index"]:
        result["error"] = "source hash differs from object index"
        return result
    helper_dir = root / "scripts" / "vc6"
    if str(helper_dir) not in sys.path:
        sys.path.insert(0, str(helper_dir))
    import verify_vtable

    try:
        data, sections, symbols, auxiliary = verify_vtable.parse_coff(object_path)
    except verify_vtable.VerifyError as exc:
        result["error"] = f"malformed COFF object: {exc}"
        return result
    expected = str(row.get("sym", ""))
    exact = [(idx, sym) for idx, sym in symbols.items() if sym["name"] == expected]
    invalid_sections = [(idx, sym) for idx, sym in exact
                        if sym["section"] > 0 and sym["section"] not in sections]
    definitions = [(idx, sym) for idx, sym in exact
                   if sym["section"] > 0 and sym["section"] in sections]
    undef = [(idx, sym) for idx, sym in exact if sym["section"] == 0]
    owner_method, owner_name = decorated_member_owner_hint(expected)
    by_index = []
    for idx, sym in definitions:
        section = sections.get(sym["section"], {})
        raw_size = int(section.get("raw_size", 0))
        available = raw_size - int(sym["value"])
        aux_size = function_aux_size(data, idx, sym, auxiliary)
        by_index.append({
            "coff_symbol_index": idx,
            "section_number": sym["section"],
            "section_name": section.get("name"),
            "symbol_offset": sym["value"],
            "requested_length": int(str(row["len"]), 16),
            "emitted_section_raw_size": raw_size,
            "available_bytes_from_symbol": max(0, available),
            "coff_function_aux_size": aux_size,
            "section_span_check": "out_of_bounds" if available < int(str(row["len"]), 16) else "within_section",
            "aux_size_check": ("shorter_than_requested" if aux_size is not None and aux_size < int(str(row["len"]), 16)
                               else "at_least_requested_or_unavailable"),
        })
    same_method = []
    if owner_method:
        for idx, sym in symbols.items():
            method, owner = decorated_member_owner_hint(sym["name"])
            if (method == owner_method and sym["name"] != expected and sym["section"] > 0
                    and sym["section"] in sections):
                same_method.append({"symbol": sym["name"], "owner_name_hint": owner,
                                    "same_owner_name_hint": owner == owner_name,
                                    "section_number": sym["section"], "symbol_index": idx})
    type_scan = source_declared_type_names(root, source_path, tracked_match)
    result.update({
        "expected_symbol": expected,
        "symbol_defined_count": len(definitions),
        "symbol_undefined_count": len(undef),
        "symbol_preflight": ("unique_definition" if len(definitions) == 1
                             else "missing_definition" if not definitions
                             else "ambiguous_definitions"),
        "invalid_positive_section_symbols": [
            {"coff_symbol_index": idx, "symbol": sym["name"], "section_number": sym["section"]}
            for idx, sym in invalid_sections],
        "expected_decorated_method_hint": owner_method,
        "expected_decorated_owner_name_hint": owner_name,
        "same_method_alternative_definitions": same_method[:20],
        "matching_symbol_sections": by_index,
        "object_section_count": len(sections),
        "object_file_size": len(data),
        "source_declared_type_scan": type_scan,
    })
    if invalid_sections:
        result["error"] = "matching COFF symbol has a positive section number absent from the section table"
    if owner_name:
        result["decorated_owner_name_seen_in_scanned_source"] = owner_name in type_scan["declared_type_names"]
    if len(definitions) == 1:
        sym = definitions[0][1]
        section = sections.get(sym["section"], {})
        requested = int(str(row["len"]), 16)
        available = int(section.get("raw_size", 0)) - int(sym["value"])
        recorded_status = row.get("status")
        short_section = available < requested
        aux_size = by_index[0]["coff_function_aux_size"]
        short_symbol = aux_size is not None and aux_size < requested
        if short_section or short_symbol:
            result["span_severity"] = "error" if recorded_status == "matched" else "warning"
            causes = []
            if short_section:
                causes.append("requested span exceeds COFF section bytes from this symbol")
            if short_symbol:
                causes.append("requested span exceeds COFF function auxiliary size")
            result["span_note"] = "; ".join(causes)
        else:
            result["span_severity"] = "none"
    return result


def build_context(root: Path, addresses: list[int], object_dir: Path) -> dict[str, Any]:
    root = root.resolve()
    tracked_all = tracked_paths(root, "")
    tracked_match = tracked_paths(root, "match")
    data_files = ["scripts/data/match_manifest.json", "scripts/data/ret_imm_census.json",
                  "scripts/data/function_extent_audit.json", "scripts/vc6/vc6cl.sh"]
    safe_files = {name: checked_path(root, name, tracked_all) for name in data_files}
    manifest = load_json(safe_files["scripts/data/match_manifest.json"])
    census = load_json(safe_files["scripts/data/ret_imm_census.json"])
    extents = load_json(safe_files["scripts/data/function_extent_audit.json"])
    reject_symlink_components(object_dir, "object directory")
    index_path = object_dir / "objects.json"
    reject_symlink_components(index_path, "object index")
    if not index_path.is_file():
        raise ValueError(f"object index not found or is symlink: {index_path}")
    if not index_path.resolve().is_relative_to(object_dir.resolve()):
        raise ValueError("object index resolves outside object directory")
    index = load_json(index_path)
    currentness = index_currentness(root, object_dir, index, tracked_all, tracked_match)
    index["_currentness"] = currentness
    grouped = manifest_row_groups(manifest)
    census_by_addr = {address_field(item): item for item in census.get("functions", [])
                      if isinstance(item, dict) and address_field(item) is not None}
    extents_by_addr = {address_field(item): item for item in extents.get("functions", [])
                       if isinstance(item, dict) and address_field(item) is not None}
    records = []
    for address in addresses:
        rows = grouped.get(address, [])
        record: dict[str, Any] = {
            "address": f"0x{address:08X}",
            "manifest_row_count": len(rows),
            "fresh_verification": "not_run",
            "census_record": census_context(census_by_addr.get(address)),
            "extent_record": extent_context(extents_by_addr.get(address)),
        }
        if len(rows) > 1:
            record["manifest_status"] = "ambiguous_duplicate_address"
            record["manifest_rows"] = [
                {k: v for k, v in row.items() if not k.startswith("_")} for row in rows
            ]
            record["coff_preflight"] = {"error": "address has multiple manifest rows; no TU selected"}
        elif not rows:
            record["manifest_status"] = "unclaimed"
            record["coff_preflight"] = {"note": "no annotated manifest TU/object to inspect"}
        else:
            row = rows[0]
            record["manifest_status"] = row.get("status")
            record["recorded_pct"] = row.get("pct")
            record["manifest_row"] = {k: v for k, v in row.items() if not k.startswith("_")}
            record["coff_preflight"] = analyze_object(root, object_dir, index, row, tracked_match)
            extent = record.get("extent_record")
            coff = record["coff_preflight"]
            if extent and extent.get("source") == row.get("tu"):
                record["extent_record_currentness"] = {
                    "source_hash_matches_current": extent.get("source_sha256") == coff.get("source_sha256"),
                    "object_hash_matches_current": extent.get("object_sha256") == coff.get("object_sha256"),
                    "note": "recorded extent audit only; these hashes do not revalidate its binary conclusions",
                }
        records.append(record)
    errors = []
    warnings = []
    if not currentness["current"]:
        warnings.append("object index is stale or invalid; COFF details are suppressed")
    for record in records:
        coff = record.get("coff_preflight", {})
        if record.get("manifest_status") == "matched":
            if coff.get("error"):
                errors.append(f"{record['address']}: {coff['error']}")
            if coff.get("symbol_preflight") not in (None, "unique_definition"):
                errors.append(f"{record['address']}: {coff['symbol_preflight']}")
            if coff.get("span_severity") == "error":
                errors.append(f"{record['address']}: emitted span is shorter than requested")
        elif coff.get("span_severity") == "warning":
            warnings.append(f"{record['address']}: emitted section is shorter than requested")
        extent_state = record.get("extent_record_currentness")
        if extent_state and (not extent_state["source_hash_matches_current"] or
                             not extent_state["object_hash_matches_current"]):
            warnings.append(f"{record['address']}: recorded extent audit hashes differ from current source/object")
        if record.get("manifest_status") == "ambiguous_duplicate_address":
            errors.append(f"{record['address']}: duplicate manifest address")
    return {
        "tool": "function_context.py",
        "scope": "preflight context only; no fresh match or ABI verdict",
        "project_root": str(root),
        "inputs": {name: {"sha256": sha256(path)} for name, path in safe_files.items()},
        "object_index": {
            "path": str(index_path),
            "sha256": sha256(index_path),
            **currentness,
        },
        "preflight_errors": sorted(set(errors)),
        "preflight_warnings": sorted(set(warnings)),
        "records": records,
    }


def markdown(context: dict[str, Any]) -> str:
    lines = ["# Function context preflight", "",
             "This report is not a fresh byte match, ABI proof, or declaration of identity.",
             f"Object index current: **{context['object_index']['current']}**. "
             f"Fresh verification: **not run**.", "",
             "| Address | Manifest | Recorded % | TU | Symbol preflight | Span | Fresh check |",
             "|---|---|---:|---|---|---|---|"]
    for rec in context["records"]:
        row = rec.get("manifest_row", {})
        coff = rec.get("coff_preflight", {})
        matches = coff.get("matching_symbol_sections", [])
        span = ", ".join(
            f"{entry['available_bytes_from_symbol']}/{entry['requested_length']} available"
            for entry in matches
        ) or "n/a"
        lines.append("| `{}` | {} | {} | `{}` | {} | {} | not run |".format(
            rec["address"], rec.get("manifest_status"), rec.get("recorded_pct", "—"),
            row.get("tu", "—"), coff.get("symbol_preflight", coff.get("error", "—")), span))
    for rec in context["records"]:
        coff = rec.get("coff_preflight", {})
        lines.extend(["", f"## {rec['address']}", "",
                      f"Census: `{json.dumps(rec.get('census_record'), sort_keys=True)}`",
                      f"Extent record: `{json.dumps(rec.get('extent_record'), sort_keys=True)}`"])
        if rec.get("manifest_row"):
            lines.append(f"Manifest row: `{json.dumps(rec['manifest_row'], sort_keys=True)}`")
        if rec.get("extent_record_currentness"):
            lines.append(f"Recorded extent currentness: `{json.dumps(rec['extent_record_currentness'], sort_keys=True)}`")
        if coff.get("source_path"):
            lines.append(f"Source/index details: `{json.dumps({k: coff.get(k) for k in ('source_path', 'source_sha256', 'source_matches_index', 'compiler_flags', 'flags_source', 'object_path', 'object_sha256')}, sort_keys=True)}`")
        if coff.get("source_declared_type_scan"):
            lines.append(f"Scanned declared-type-name hints: `{json.dumps(coff['source_declared_type_scan'], sort_keys=True)}`")
        if coff.get("matching_symbol_sections"):
            lines.append(f"Emitted section extent: `{json.dumps(coff['matching_symbol_sections'], sort_keys=True)}`")
        if coff.get("symbol_preflight") == "missing_definition":
            lines.extend([f"Expected decorated symbol: `{coff.get('expected_symbol')}`."])
            owner = coff.get("expected_decorated_owner_name_hint")
            lines.append(f"Owner-name parse hint: `{owner}` (decoration only; not class-key or ABI evidence).")
            lines.append(f"Same-method alternative definitions: `{json.dumps(coff.get('same_method_alternative_definitions', []), sort_keys=True)}`.")
        if coff.get("span_severity") in ("warning", "error"):
            lines.append(f"Span diagnostic (**{coff['span_severity']}**): {coff['span_note']}.")
    lines.extend(["", "## Data freshness", "",
                  f"Index check: `{context['object_index'].get('check_output')}`.",
                  "Manifest status and percentage are recorded claims. This command does not rerun the oracle."])
    if context.get("preflight_errors"):
        lines.extend(["", "Blocking preflight findings:"])
        lines.extend(f"- {error}" for error in context["preflight_errors"])
    if context.get("preflight_warnings"):
        lines.extend(["", "Preflight warnings:"])
        lines.extend(f"- {warning}" for warning in context["preflight_warnings"])
    return "\n".join(lines) + "\n"


def find_root(start: Path) -> Path:
    for candidate in (start, *start.parents):
        if (candidate / "scripts/data/match_manifest.json").is_file() and \
                (candidate / "scripts/vc6/build_project.py").is_file():
            return candidate
    raise ValueError("could not locate gagarin root; pass --project-root")


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--addr", action="append", required=True, type=parse_address,
                        help="manifest address (repeatable), e.g. 0x00401000")
    parser.add_argument("--project-root", type=Path, help="gagarin checkout root")
    parser.add_argument("--objects", type=Path, help="object index directory; defaults to build-vc6/project")
    parser.add_argument("--format", choices=("json", "markdown"), default="json")
    parser.add_argument("--out", type=Path, help="output path; default stdout")
    args = parser.parse_args(argv)
    try:
        root = (args.project_root or find_root(Path(__file__).resolve())).resolve()
        object_dir = args.objects or root / "build-vc6/project"
        context = build_context(root, args.addr, object_dir)
        rendered = markdown(context) if args.format == "markdown" else json.dumps(context, indent=2, sort_keys=True) + "\n"
        if args.out:
            args.out.write_text(rendered, encoding="utf-8")
        else:
            sys.stdout.write(rendered)
        return 1 if context["preflight_errors"] else 0
    except (OSError, ValueError, KeyError, json.JSONDecodeError, subprocess.CalledProcessError) as exc:
        print(f"function_context: {exc}", file=sys.stderr)
        return 1


if __name__ == "__main__":
    raise SystemExit(main())
