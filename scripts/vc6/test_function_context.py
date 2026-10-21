#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original synthetic fixture tests; no retail bytes or functions.
"""Tests the function-context preflight with synthetic COFF and repository metadata."""

from __future__ import annotations

import hashlib
import json
import os
import struct
import subprocess
import sys
import tempfile
import unittest
from pathlib import Path

def find_helper_dir() -> Path:
    colocated = Path(__file__).resolve().parent
    if (colocated / "build_project.py").is_file() and (colocated / "verify_vtable.py").is_file():
        return colocated
    configured = os.environ.get("GAGARIN_ROOT")
    candidates = [Path(configured)] if configured else []
    candidates += [Path.cwd(), *Path.cwd().parents]
    for base in candidates:
        helper = base / "scripts/vc6"
        if (helper / "build_project.py").is_file() and (helper / "verify_vtable.py").is_file():
            return helper.resolve()
    raise RuntimeError("set GAGARIN_ROOT or run from a checkout containing scripts/vc6 helpers")


sys.path.insert(0, str(find_helper_dir()))
import function_context


def make_coff(path: Path, symbol: str, body_size: int, *, aux_size=None,
              symbol_section=1, corrupt_raw_pointer=False) -> None:
    raw = b"\x90" * body_size
    header_size = 20
    section_header_size = 40
    raw_ptr = header_size + section_header_size
    sym_ptr = raw_ptr + len(raw)
    string = symbol.encode("ascii") + b"\0"
    strings = struct.pack("<I", 4 + len(string)) + string
    symbol_count = 2  # external function plus one auxiliary function record
    header = struct.pack("<HHIIIHH", 0x14C, 1, 0, sym_ptr, symbol_count, 0, 0)
    section_name = b".text$fn\0"
    section = struct.pack("<8sIIIIIIHHI", section_name, 0, 0, len(raw),
                          len(raw) + 0x1000 if corrupt_raw_pointer else raw_ptr,
                          0, 0, 0, 0, 0x60000020)
    name = b"\0\0\0\0" + struct.pack("<I", 4)
    function_symbol = struct.pack("<8sIhHBB", name, 0, symbol_section, 0x20, 2, 1)
    aux = bytearray(18)
    struct.pack_into("<I", aux, 4, body_size if aux_size is None else aux_size)
    path.write_bytes(header + section + raw + function_symbol + bytes(aux) + strings)


def sha(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


class FunctionContextTests(unittest.TestCase):
    def fixture(self, *, status="partial", requested_len="0x4", emitted_len=4,
                expected_sym="?DoThing@Widget@@QAEHXZ", actual_sym=None,
                duplicate=False, traversal=False, stale=False, aux_size=None,
                symbol_section=1, corrupt_raw_pointer=False, symlink_object_dir=False):
        temp = tempfile.TemporaryDirectory(prefix="gagarin_function_context_")
        root = Path(temp.name)
        subprocess.run(["git", "init", "-q"], cwd=root, check=True)
        source = root / "match/core/thing.cpp"
        source.parent.mkdir(parents=True)
        source.write_text('#include "thing.h"\nvoid Widget::DoThing() {}\n', encoding="utf-8")
        (source.parent / "thing.h").write_text("class Widget {};\nclass Other {};\n", encoding="utf-8")
        source_rel = "../outside.cpp" if traversal else "match/core/thing.cpp"
        row = {"tu": source_rel, "addr": "0x00401000", "sym": expected_sym,
               "len": requested_len, "status": status, "pct": 55}
        manifest = [row, dict(row)] if duplicate else [row]
        files = {
            "scripts/data/match_manifest.json": json.dumps(manifest),
            "scripts/data/ret_imm_census.json": json.dumps({"functions": [
                {"addr": "0x00401000", "confidence": "high", "ret_imms": ["0x4"]}]}),
            "scripts/data/function_extent_audit.json": json.dumps({"functions": [
                {"addr": "0x00401000", "length": requested_len, "coverage": "entry-origin"}]}),
            "scripts/vc6/vc6cl.sh": 'DEFAULT_FLAGS="/nologo /c /O2"\n',
        }
        for relative, contents in files.items():
            path = root / relative
            path.parent.mkdir(parents=True, exist_ok=True)
            path.write_text(contents, encoding="utf-8")
        subprocess.run(["git", "add", "scripts", "match"], cwd=root, check=True)

        out = root / "build-vc6/project"
        obj = out / "match/core/thing.obj"
        obj.parent.mkdir(parents=True)
        make_coff(obj, actual_sym or expected_sym, emitted_len, aux_size=aux_size,
                  symbol_section=symbol_section, corrupt_raw_pointer=corrupt_raw_pointer)
        index = {
            "schema_version": 1, "success": True, "source_count": 1,
            "successful_objects": 1, "input_sha256": self.input_hashes(root),
            "wrapper_sha256": sha(root / "scripts/vc6/vc6cl.sh"),
            "manifest_sha256": sha(root / "scripts/data/match_manifest.json"),
            "objects": [{"source": "match/core/thing.cpp",
                         "source_sha256": sha(source), "object": "match/core/thing.obj",
                         "log": "match/core/thing.log",
                         "object_sha256": sha(obj), "success": True,
                         "flags": "/nologo /c /O2", "flags_source": "fixture"}],
        }
        if stale:
            source.write_text(source.read_text() + "// changed after object build\n", encoding="utf-8")
        out.mkdir(parents=True, exist_ok=True)
        if symlink_object_dir:
            (out / "linked").symlink_to(obj.parent, target_is_directory=True)
            index["objects"][0]["object"] = "linked/thing.obj"
        (out / "objects.json").write_text(json.dumps(index), encoding="utf-8")
        return temp, root, out

    @staticmethod
    def input_hashes(root: Path) -> dict[str, str]:
        result = subprocess.run(["git", "ls-files", "-z", "--", "match"], cwd=root,
                                check=True, stdout=subprocess.PIPE)
        return {name.decode(): sha(root / name.decode()) for name in result.stdout.split(b"\0") if name}

    def run_fixture(self, **kwargs):
        temp, root, out = self.fixture(**kwargs)
        self.addCleanup(temp.cleanup)
        return function_context.build_context(root, [0x401000], out)["records"][0]

    def test_missing_definition_is_reported_without_claiming_a_class_key(self):
        record = self.run_fixture(actual_sym="?DoThing@Other@@QAEHXZ")
        preflight = record["coff_preflight"]
        self.assertEqual(preflight["symbol_preflight"], "missing_definition")
        self.assertEqual(preflight["expected_decorated_owner_name_hint"], "Widget")
        self.assertTrue(preflight["decorated_owner_name_seen_in_scanned_source"])
        self.assertIn("Other", [candidate["owner_name_hint"] for candidate in preflight["same_method_alternative_definitions"]])
        self.assertIn("Other", preflight["source_declared_type_scan"]["declared_type_names"])
        self.assertEqual(record["fresh_verification"], "not_run")

    def test_msvc_declspec_is_not_reported_as_a_type_name(self):
        temp, root, out = self.fixture()
        self.addCleanup(temp.cleanup)
        header = root / "match/core/thing.h"
        header.write_text("class __declspec(novtable) Widget {};\nstruct Plain {};\n")
        result = function_context.source_declared_type_names(
            root, root / "match/core/thing.cpp", function_context.tracked_paths(root, "match"))
        self.assertIn("Widget", result["declared_type_names"])
        self.assertIn("Plain", result["declared_type_names"])
        self.assertNotIn("__declspec", result["declared_type_names"])

    def test_same_owner_alternate_return_type_is_reported(self):
        record = self.run_fixture(actual_sym="?DoThing@Widget@@QAEPAV1@XZ")
        candidates = record["coff_preflight"]["same_method_alternative_definitions"]
        self.assertEqual(len(candidates), 1)
        self.assertTrue(candidates[0]["same_owner_name_hint"])

    def test_stale_object_index_suppresses_coff_claims(self):
        record = self.run_fixture(stale=True)
        preflight = record["coff_preflight"]
        self.assertIn("object index is stale", preflight["error"])
        self.assertNotIn("symbol_preflight", preflight)

    def test_short_section_warns_for_partial_but_errors_for_matched(self):
        partial = self.run_fixture(status="partial", requested_len="0x5", emitted_len=3)
        matched = self.run_fixture(status="matched", requested_len="0x5", emitted_len=3)
        self.assertEqual(partial["coff_preflight"]["span_severity"], "warning")
        self.assertEqual(matched["coff_preflight"]["span_severity"], "error")
        self.assertEqual(partial["coff_preflight"]["matching_symbol_sections"][0]["emitted_section_raw_size"], 3)
        temp, root, out = self.fixture(status="matched", requested_len="0x5", emitted_len=3)
        self.addCleanup(temp.cleanup)
        context = function_context.build_context(root, [0x401000], out)
        self.assertTrue(any("emitted span is shorter" in issue
                            for issue in context["preflight_errors"]))

    def test_duplicate_manifest_address_is_not_arbitrarily_selected(self):
        record = self.run_fixture(duplicate=True)
        self.assertEqual(record["manifest_status"], "ambiguous_duplicate_address")
        self.assertEqual(record["coff_preflight"]["error"], "address has multiple manifest rows; no TU selected")

    def test_manifest_path_traversal_is_reported_and_not_opened(self):
        record = self.run_fixture(traversal=True)
        self.assertIn("unsafe repository path", record["coff_preflight"]["error"])

    def test_malformed_coff_is_reported_without_traceback(self):
        record = self.run_fixture(corrupt_raw_pointer=True)
        self.assertIn("malformed COFF object", record["coff_preflight"]["error"])

    def test_positive_symbol_section_must_exist(self):
        record = self.run_fixture(symbol_section=2)
        preflight = record["coff_preflight"]
        self.assertEqual(preflight["symbol_preflight"], "missing_definition")
        self.assertIn("positive section number absent", preflight["error"])
        self.assertEqual(preflight["invalid_positive_section_symbols"][0]["section_number"], 2)

    def test_auxiliary_size_shorter_than_requested_is_reported(self):
        record = self.run_fixture(requested_len="0x5", emitted_len=8, aux_size=3)
        preflight = record["coff_preflight"]
        entry = preflight["matching_symbol_sections"][0]
        self.assertEqual(entry["emitted_section_raw_size"], 8)
        self.assertEqual(entry["coff_function_aux_size"], 3)
        self.assertEqual(preflight["span_severity"], "warning")
        self.assertIn("auxiliary size", preflight["span_note"])

    def test_intermediate_symlink_index_path_is_rejected_before_coff_read(self):
        temp, root, out = self.fixture(symlink_object_dir=True)
        self.addCleanup(temp.cleanup)
        context = function_context.build_context(root, [0x401000], out)
        record = context["records"][0]
        self.assertFalse(context["object_index"]["current"])
        self.assertIn("refusing symlink object path", context["object_index"]["check_output"])
        self.assertIn("COFF preflight suppressed", record["coff_preflight"]["error"])


if __name__ == "__main__":
    unittest.main()
