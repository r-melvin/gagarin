#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: gagarin's own match manifest and CFG-derived function census.
"""Export verified manifest claims and census spans as objdiff report v2 JSON.

This is a progress view, not an objdiff byte comparison. Only manifest rows with
status "matched" contribute to fuzzy/matched bytes; partial and unclaimed spans
remain unmatched regardless of instruction diagnostic percentages.
"""

from __future__ import annotations

import argparse
import json
import sys
from collections import defaultdict
from pathlib import Path, PurePosixPath
from typing import Any


REPORT_VERSION = 2
MEASURE_KEYS = (
    "fuzzy_match_percent", "total_code", "matched_code", "matched_code_percent",
    "total_data", "matched_data", "matched_data_percent", "total_functions",
    "matched_functions", "matched_functions_percent", "complete_code",
    "complete_code_percent", "complete_data", "complete_data_percent",
    "total_units", "complete_units",
)


def empty_measures() -> dict[str, int | float]:
    return {key: 0 for key in MEASURE_KEYS}


def percent(part: int, total: int) -> float:
    return 0.0 if total == 0 else part * 100.0 / total


def finish_measures(m: dict[str, int | float]) -> dict[str, int | float]:
    m["matched_code_percent"] = percent(int(m["matched_code"]), int(m["total_code"]))
    m["matched_data_percent"] = percent(int(m["matched_data"]), int(m["total_data"]))
    m["matched_functions_percent"] = percent(int(m["matched_functions"]), int(m["total_functions"]))
    m["complete_code_percent"] = percent(int(m["complete_code"]), int(m["total_code"]))
    m["complete_data_percent"] = percent(int(m["complete_data"]), int(m["total_data"]))
    return m


def _integer(value: Any, label: str) -> int:
    try:
        result = int(value, 0) if isinstance(value, str) else int(value)
    except (ValueError, TypeError) as exc:
        raise ValueError(f"{label}: expected integer, got {value!r}") from exc
    if result <= 0:
        raise ValueError(f"{label}: length must be positive")
    return result


def _safe_source(root: Path, raw: Any, addr: int) -> str:
    if not isinstance(raw, str) or not raw:
        raise ValueError(f"0x{addr:08X}: missing translation unit path")
    path = PurePosixPath(raw)
    if path.is_absolute() or ".." in path.parts or "\\" in raw:
        raise ValueError(f"0x{addr:08X}: unsafe source path {raw!r}")
    if path.suffix.lower() not in {".cpp", ".c", ".cc", ".cxx", ".asm"}:
        raise ValueError(f"0x{addr:08X}: expected source file path, got {raw!r}")
    candidate = root.joinpath(*path.parts)
    if not candidate.is_file():
        raise ValueError(f"0x{addr:08X}: source path does not exist: {raw!r}")
    if not candidate.resolve().is_relative_to(root.resolve()):
        raise ValueError(f"0x{addr:08X}: source path escapes repository root: {raw!r}")
    return path.as_posix()


def build_report(manifest: list[dict[str, Any]], census: list[list[Any]], root: Path) -> tuple[dict[str, Any], dict[str, Any]]:
    if not census:
        raise ValueError("function extent census is empty")
    census_by_addr: dict[int, tuple[int, str]] = {}
    for entry in census:
        if not isinstance(entry, list) or len(entry) < 5:
            raise ValueError(f"invalid census entry: {entry!r}")
        addr = int(entry[0], 16)
        if addr in census_by_addr:
            raise ValueError(f"duplicate census address 0x{addr:08X}")
        length = _integer(entry[1], f"census 0x{addr:08X}")
        census_by_addr[addr] = (length, str(entry[4]))

    claims: dict[int, dict[str, Any]] = {}
    for row in manifest:
        try:
            addr = int(row["addr"], 16)
        except (KeyError, ValueError, TypeError) as exc:
            raise ValueError(f"invalid manifest address in row {row!r}") from exc
        if addr in claims:
            raise ValueError(f"duplicate manifest claim at 0x{addr:08X}")
        if addr not in census_by_addr:
            raise ValueError(f"manifest claim outside census at 0x{addr:08X}")
        if row.get("status") not in {"matched", "partial"}:
            raise ValueError(f"unknown status at 0x{addr:08X}: {row.get('status')!r}")
        row = dict(row)
        row["_length"] = _integer(row.get("len"), f"manifest 0x{addr:08X}")
        row["_source"] = _safe_source(root, row.get("tu"), addr)
        claims[addr] = row

    assignments: dict[str, list[dict[str, Any]]] = defaultdict(list)
    overrides: list[dict[str, Any]] = []
    for addr, (census_len, kind) in sorted(census_by_addr.items()):
        row = claims.get(addr)
        length = row["_length"] if row else census_len
        if row and length != census_len:
            overrides.append({"address": f"0x{addr:08X}", "census_length": census_len, "manifest_length": length})
        if row:
            source = row["_source"]
            unit_name = str(PurePosixPath(source).with_suffix(""))
            display_name = row.get("name")
            readable_name = isinstance(display_name, str) and bool(display_name.strip()) and not display_name.startswith("?")
            if not readable_name:
                display_name = f"FUN_{addr:08X}"
            metadata: dict[str, Any] = {"virtual_address": addr}
            if readable_name:
                metadata["demangled_name"] = display_name
            symbol = row.get("sym")
            if not isinstance(symbol, str) or not symbol.strip():
                raise ValueError(f"0x{addr:08X}: missing manifest symbol")
            item = {"name": symbol, "size": length,
                    "fuzzy_match_percent": 100 if row["status"] == "matched" else 0,
                    "metadata": metadata}
            key = unit_name
            unit_meta = {"source_path": source, "complete": False, "progress_categories": []}
        else:
            key = f"unrecovered/{kind}"
            item = {"name": f"FUN_{addr:08X}", "size": length, "fuzzy_match_percent": 0,
                    "metadata": {"virtual_address": addr}}
            unit_meta = {"auto_generated": True, "complete": False, "progress_categories": []}
        assignments[key].append({"item": item, "matched": bool(row and row["status"] == "matched"), "unit_metadata": unit_meta})

    units: list[dict[str, Any]] = []
    for name in sorted(assignments):
        entries = assignments[name]
        m = empty_measures()
        m["total_code"] = sum(e["item"]["size"] for e in entries)
        m["matched_code"] = sum(e["item"]["size"] for e in entries if e["matched"])
        m["total_functions"] = len(entries)
        m["matched_functions"] = sum(e["matched"] for e in entries)
        m["fuzzy_match_percent"] = percent(int(m["matched_code"]), int(m["total_code"]))
        m["total_units"] = 1
        finish_measures(m)
        meta = entries[0]["unit_metadata"]
        units.append({"name": name, "measures": m, "sections": [],
                      "functions": [e["item"] for e in entries], "metadata": meta})

    total = empty_measures()
    total["total_code"] = sum(int(u["measures"]["total_code"]) for u in units)
    total["matched_code"] = sum(int(u["measures"]["matched_code"]) for u in units)
    total["total_functions"] = sum(int(u["measures"]["total_functions"]) for u in units)
    total["matched_functions"] = sum(int(u["measures"]["matched_functions"]) for u in units)
    total["total_units"] = len(units)
    total["fuzzy_match_percent"] = percent(int(total["matched_code"]), int(total["total_code"]))
    finish_measures(total)
    report = {"measures": total, "units": units, "version": REPORT_VERSION, "categories": []}
    census_total = sum(length for length, _ in census_by_addr.values())
    context = {
        "schema": "gagarin/bytematch-report-context/1",
        "census_function_count": len(census_by_addr),
        "manifest_claim_count": len(claims),
        "unclaimed_function_count": len(census_by_addr) - len(claims),
        "census_code_bytes": census_total,
        "effective_code_bytes": int(total["total_code"]),
        "length_override_count": len(overrides),
        "length_overrides": overrides,
        "matched_function_count": int(total["matched_functions"]),
        "matched_code_bytes": int(total["matched_code"]),
        "interpretation": "Manifest status is a per-function verified claim. Instruction percentages are not byte fuzzy-match percentages. This export does not run objdiff or compare native object files.",
    }
    return report, context


def export(root: Path, output: Path) -> tuple[dict[str, Any], dict[str, Any]]:
    manifest_path = root / "scripts/data/match_manifest.json"
    census_path = root / "scripts/data/function_extents.json"
    manifest = json.loads(manifest_path.read_text(encoding="utf-8"))
    census_doc = json.loads(census_path.read_text(encoding="utf-8"))
    if census_doc.get("schema") != "gagarin/function_extents/1":
        raise ValueError("unsupported function extent census schema")
    report, context = build_report(manifest, census_doc.get("entries", []), root)
    output.parent.mkdir(parents=True, exist_ok=True)
    output.write_text(json.dumps(report, indent=2, sort_keys=True) + "\n", encoding="utf-8")
    context_path = output.with_name("report-context.json")
    context_path.write_text(json.dumps(context, indent=2, sort_keys=True) + "\n", encoding="utf-8")
    return report, context


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--root", type=Path, default=Path(__file__).resolve().parents[2], help="repository root (default: detected from this script)")
    parser.add_argument("--output", type=Path, default=None, help="report path (default: build/GAMEMD_1.001/report.json under root)")
    args = parser.parse_args(argv)
    root = args.root.resolve()
    output = (args.output or root / "build/GAMEMD_1.001/report.json").resolve()
    try:
        report, context = export(root, output)
    except (OSError, ValueError, json.JSONDecodeError) as exc:
        print(f"bytematch_report: {exc}", file=sys.stderr)
        return 2
    print(f"Wrote {output}")
    print(f"Coverage: {context['manifest_claim_count']}/{context['census_function_count']} functions; "
          f"{context['matched_function_count']} matched; {context['length_override_count']} length overrides "
          f"({context['census_code_bytes']} census bytes, {context['effective_code_bytes']} effective bytes)")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
