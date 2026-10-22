#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original; synthetic PE/COFF fixtures contain no retail bytes.
"""Synthetic regressions for verify_relocations; no game binary is used."""
import hashlib
import json
import struct
import tempfile
import unittest
from pathlib import Path

from verify_relocations import (DEFAULT_BINDINGS, DEFAULT_MANIFEST, VerifyError,
                                _literal_size, verify)


BASE = 0x00400000
TEXT_VA = 0x00401000
DATA_VA = 0x00401100


def coff_obj(text, relocations, symbols, data=b"\0" * 16):
    """Build a small i386 COFF object with .text/.data sections.

    Symbols are dictionaries with name/value/section and optional storage and
    weak_default fields. Relocations are (offset, symbol_name, kind) tuples.
    """
    symbol_index = {}
    index = 0
    for item in symbols:
        symbol_index[item["name"]] = index
        index += 1 + int(item.get("weak_default") is not None)

    header_end = 20 + 2 * 40
    text_ptr = header_end
    data_ptr = text_ptr + len(text)
    reloc_ptr = data_ptr + len(data)
    relocation_bytes = b"".join(
        struct.pack("<IIH", offset, symbol_index[name], kind)
        for offset, name, kind in relocations
    )
    symbols_ptr = reloc_ptr + len(relocation_bytes)

    strings = bytearray()

    def encode_name(name):
        raw = name.encode("ascii")
        if len(raw) <= 8:
            return raw.ljust(8, b"\0")
        offset = 4 + len(strings)
        strings.extend(raw + b"\0")
        return b"\0\0\0\0" + struct.pack("<I", offset)

    symbol_bytes = bytearray()
    nsyms = 0
    for item in symbols:
        name = item["name"]
        weak_default = item.get("weak_default")
        aux_count = int(weak_default is not None)
        storage = item.get("storage", 2)
        symbol_bytes.extend(struct.pack(
            "<8sIhHBB", encode_name(name), item["value"], item["section"],
            0, storage, aux_count,
        ))
        nsyms += 1
        if weak_default is not None:
            target_name, characteristics = weak_default
            aux = struct.pack("<II", symbol_index[target_name], characteristics)
            symbol_bytes.extend(aux + b"\0" * 10)
            nsyms += 1
    string_table = struct.pack("<I", 4 + len(strings)) + bytes(strings)

    file_header = struct.pack("<HHIIIHH", 0x14C, 2, 0, symbols_ptr,
                              nsyms, 0, 0)
    text_header = struct.pack(
        "<8sIIIIIIHHI", b".text", len(text), 0, len(text), text_ptr,
        reloc_ptr, 0, len(relocations), 0, 0x60000020,
    )
    data_header = struct.pack(
        "<8sIIIIIIHHI", b".data", len(data), 0, len(data), data_ptr,
        0, 0, 0, 0, 0xC0000040,
    )
    return (file_header + text_header + data_header + text + data
            + relocation_bytes + bytes(symbol_bytes) + string_table)


def pe_image(text=None, data=None):
    """Build a PE32 image whose .text/.data VAs are TEXT_VA and DATA_VA."""
    text = bytes(text if text is not None else b"\0" * 0x40)
    data = bytes(data if data is not None else b"\0" * 0x20)
    pe_offset = 0x80
    optional_size = 224
    section_table = pe_offset + 24 + optional_size
    text_raw = 0x200
    data_raw = text_raw + len(text)
    image = bytearray(data_raw + len(data))
    image[:2] = b"MZ"
    struct.pack_into("<I", image, 0x3C, pe_offset)
    image[pe_offset:pe_offset + 4] = b"PE\0\0"
    struct.pack_into("<HHIIIHH", image, pe_offset + 4, 0x14C, 2,
                     0, 0, 0, optional_size, 0x010F)
    optional = pe_offset + 24
    struct.pack_into("<H", image, optional, 0x10B)
    struct.pack_into("<I", image, optional + 28, BASE)
    image[section_table:section_table + 40] = struct.pack(
        "<8sIIIIIIHHI", b".text", len(text), TEXT_VA - BASE,
        len(text), text_raw, 0, 0, 0, 0, 0x60000020,
    )
    image[section_table + 40:section_table + 80] = struct.pack(
        "<8sIIIIIIHHI", b".data", len(data), DATA_VA - BASE,
        len(data), data_raw, 0, 0, 0, 0, 0xC0000040,
    )
    image[text_raw:text_raw + len(text)] = text
    image[data_raw:data_raw + len(data)] = data
    return bytes(image)


class VerifyRelocationsTests(unittest.TestCase):
    def make_case(self, text, relocations, symbols, retail_text=None,
                  manifest=None, explicit=None, pinned_sha=None,
                  central=None, obj_data=None, retail_data=None):
        temp = tempfile.TemporaryDirectory()
        self.addCleanup(temp.cleanup)
        root = Path(temp.name)
        obj_path = root / "fixture.obj"
        binary_path = root / "fixture.exe"
        manifest_path = root / "manifest.json"
        totals_path = root / "totals.json"
        map_path = root / "symbol-map.json" if explicit is not None else None
        central_path = root / "bindings.json" if central is not None else None

        obj_path.write_bytes(coff_obj(text, relocations, symbols,
                                      obj_data if obj_data is not None else b"\0" * 16))
        binary = pe_image(text=retail_text if retail_text is not None else b"\0" * 0x40,
                          data=retail_data)
        binary_path.write_bytes(binary)
        manifest_path.write_text(json.dumps(manifest or []))
        if map_path:
            map_path.write_text(json.dumps(explicit))
        if central_path:
            central_path.write_text(json.dumps(central))
        sha = pinned_sha if pinned_sha is not None else hashlib.sha256(binary).hexdigest()
        totals_path.write_text(json.dumps({"_meta": {"sha256": sha}}))
        return obj_path, binary_path, manifest_path, totals_path, map_path, central_path

    def run_verify(self, *, text, relocations, symbols, retail_text=None,
                   manifest=None, explicit=None, pinned_sha=None, length=8,
                   allow_library_defaults=False, central=None, obj_data=None,
                   retail_data=None):
        obj, binary, manifest_path, totals, symbol_map, central_path = self.make_case(
            text, relocations, symbols, retail_text, manifest, explicit,
            pinned_sha, central, obj_data, retail_data,
        )
        # The tracked bindings file is replaced by the fixture's (or none).
        return verify(obj, "entry", TEXT_VA, length, binary, manifest_path,
                      symbol_map, totals, allow_library_defaults, central_path)

    @staticmethod
    def symbols_for(*targets):
        return ([{"name": "entry", "value": 0, "section": 1}]
                + list(targets))

    def test_dir32_and_rel32_resolve_with_signed_addends(self):
        text = struct.pack("<Ii", 4, -4) + b"\0" * 8
        retail_text = struct.pack("<Ii", DATA_VA + 4,
                                  DATA_VA + 0x1C - (TEXT_VA + 8)) + b"\0" * 8
        symbols = self.symbols_for(
            {"name": "dir_global", "value": 0, "section": 0},
            {"name": "rel_global", "value": 0, "section": 0},
        )
        manifest = [
            {"sym": "dir_global", "addr": hex(DATA_VA), "status": "matched", "pct": 100},
            {"sym": "rel_global", "addr": hex(DATA_VA + 0x20), "status": "matched", "pct": 100},
        ]
        rows = self.run_verify(
            text=text,
            relocations=[(0, "dir_global", 0x0006), (4, "rel_global", 0x0014)],
            symbols=symbols, retail_text=retail_text, manifest=manifest,
        )
        self.assertEqual([(r["kind"], r["target"]) for r in rows], [
            ("DIR32", DATA_VA + 4), ("REL32", DATA_VA + 0x1C),
        ])
        self.assertEqual(rows[1]["offset"], 4)

    def test_wrong_retail_target_is_rejected(self):
        text = struct.pack("<I", 0) + b"\0" * 4
        retail_text = struct.pack("<I", DATA_VA + 1) + b"\0" * 4
        with self.assertRaisesRegex(VerifyError, "retail target is"):
            self.run_verify(
                text=text, relocations=[(0, "global", 0x0006)],
                symbols=self.symbols_for({"name": "global", "value": 0, "section": 0}),
                retail_text=retail_text,
                manifest=[{"sym": "global", "addr": hex(DATA_VA),
                           "status": "matched", "pct": 100}],
            )

    def test_unknown_symbol_in_different_section_fails(self):
        with self.assertRaisesRegex(VerifyError, "has no unique matched or explicit binding"):
            self.run_verify(
                text=struct.pack("<I", 0) + b"\0" * 4,
                relocations=[(0, "helper", 0x0006)],
                symbols=self.symbols_for({"name": "helper", "value": 0, "section": 2}),
            )

    def test_same_span_local_label_uses_its_offset(self):
        text = struct.pack("<i", 0) + b"\x90\x90\xC3\0"
        retail_text = struct.pack("<i", 2) + b"\x90\x90\xC3\0"
        rows = self.run_verify(
            text=text, relocations=[(0, "local", 0x0014)],
            symbols=self.symbols_for({"name": "local", "value": 6, "section": 1}),
                retail_text=retail_text,
        )
        self.assertEqual(rows[0]["target"], TEXT_VA + 6)

    def test_ambiguous_manifest_binding_requires_unique_choice(self):
        with self.assertRaisesRegex(VerifyError, "ambiguous binding for global"):
            self.run_verify(
                text=struct.pack("<I", 0) + b"\0" * 4,
                relocations=[(0, "global", 0x0006)],
                symbols=self.symbols_for({"name": "global", "value": 0, "section": 0}),
                manifest=[
                    {"sym": "global", "addr": hex(DATA_VA), "status": "matched", "pct": 100},
                    {"sym": "global", "addr": hex(DATA_VA + 4), "status": "matched", "pct": 100},
                ],
            )

    def test_explicit_mapping_cannot_conflict_with_manifest(self):
        with self.assertRaisesRegex(VerifyError, "conflicts with matched manifest rows"):
            self.run_verify(
                text=struct.pack("<I", 0) + b"\0" * 4,
                relocations=[(0, "global", 0x0006)],
                symbols=self.symbols_for({"name": "global", "value": 0, "section": 0}),
                manifest=[{"sym": "global", "addr": hex(DATA_VA),
                           "status": "matched", "pct": 100}],
                explicit={"global": hex(DATA_VA + 4)},
            )

    def callback_case(self, manifest, explicit=None):
        return self.run_verify(
            text=b"\0" * 8,
            retail_text=struct.pack("<I", DATA_VA) + b"\0" * 4,
            relocations=[(0, "_$E2", 0x0006)],
            symbols=self.symbols_for(
                {"name": "_$E2", "value": 0, "section": 2}),
            manifest=manifest, explicit=explicit,
        )

    def test_callback_from_other_tu_cannot_supply_binding(self):
        with self.assertRaisesRegex(VerifyError, "no unique matched or explicit binding"):
            self.callback_case([
                {"sym": "_$E2", "addr": hex(DATA_VA), "tu": "other.cpp",
                 "status": "matched", "pct": 100},
            ])

    def test_explicit_callback_map_is_not_conflicted_by_other_tu(self):
        rows = self.callback_case([
            {"sym": "_$E2", "addr": hex(DATA_VA + 4), "tu": "other.cpp",
             "status": "matched", "pct": 100},
        ], explicit={"_$E2": hex(DATA_VA)})
        self.assertEqual(rows[0]["target"], DATA_VA)

    def test_callback_binding_uses_own_tu_only(self):
        manifest = [
            {"sym": "entry", "addr": hex(TEXT_VA), "tu": "own.cpp",
             "status": "matched", "pct": 100},
            {"sym": "_$E2", "addr": hex(DATA_VA), "tu": "own.cpp",
             "status": "matched", "pct": 100},
            {"sym": "_$E2", "addr": hex(DATA_VA + 4), "tu": "other.cpp",
             "status": "matched", "pct": 100},
        ]
        self.assertEqual(self.callback_case(manifest)[0]["target"], DATA_VA)
        with self.assertRaisesRegex(VerifyError, "conflicts with matched manifest rows"):
            self.callback_case(manifest, explicit={"_$E2": hex(DATA_VA + 4)})

    def test_relocation_crossing_span_boundary_is_rejected(self):
        with self.assertRaisesRegex(VerifyError, "crosses the requested span boundary"):
            self.run_verify(
                text=b"\0" * 8,
                relocations=[(6, "global", 0x0006)],
                symbols=self.symbols_for({"name": "global", "value": 0, "section": 0}),
                length=8,
            )

    def test_overlapping_relocation_fields_are_rejected(self):
        with self.assertRaisesRegex(VerifyError, "overlapping relocation fields"):
            self.run_verify(
                text=b"\0" * 8,
                relocations=[(0, "first", 0x0006), (2, "second", 0x0006)],
                symbols=self.symbols_for(
                    {"name": "first", "value": 0, "section": 0},
                    {"name": "second", "value": 0, "section": 0},
                ),
                retail_text=struct.pack("<I", DATA_VA) + b"\0" * 4,
                manifest=[
                    {"sym": "first", "addr": hex(DATA_VA), "status": "matched", "pct": 100},
                    {"sym": "second", "addr": hex(DATA_VA + 4), "status": "matched", "pct": 100},
                ],
            )

    def test_unsupported_relocation_type_is_rejected(self):
        with self.assertRaisesRegex(VerifyError, "unsupported relocation type"):
            self.run_verify(
                text=struct.pack("<I", 0) + b"\0" * 4,
                relocations=[(0, "global", 0x0007)],
                symbols=self.symbols_for({"name": "global", "value": 0, "section": 0}),
                manifest=[{"sym": "global", "addr": hex(DATA_VA),
                           "status": "matched", "pct": 100}],
            )

    def test_pinned_binary_sha_is_required(self):
        with self.assertRaisesRegex(VerifyError, "binary SHA-256 mismatch"):
            self.run_verify(
                text=struct.pack("<I", 0) + b"\0" * 4,
                relocations=[(0, "global", 0x0006)],
                symbols=self.symbols_for({"name": "global", "value": 0, "section": 0}),
                manifest=[{"sym": "global", "addr": hex(DATA_VA),
                           "status": "matched", "pct": 100}],
                pinned_sha="0" * 64,
            )

    def test_search_library_weak_default_is_opt_in_and_reported(self):
        weak_name = "weak_global"
        symbols = self.symbols_for(
            {"name": weak_name, "value": 0, "section": 0, "storage": 105,
             "weak_default": ("fallback", 2)},
            {"name": "fallback", "value": 0, "section": 2},
        )
        args = dict(
            text=struct.pack("<I", 0) + b"\0" * 4,
            relocations=[(0, weak_name, 0x0006)],
            symbols=symbols,
            retail_text=struct.pack("<I", DATA_VA) + b"\0" * 4,
            manifest=[{"sym": "fallback", "addr": hex(DATA_VA),
                       "status": "matched", "pct": 100}],
        )
        with self.assertRaisesRegex(VerifyError, "SEARCH_LIBRARY.*--weak-defaults"):
            self.run_verify(**args)
        rows = self.run_verify(**args, allow_library_defaults=True)
        self.assertEqual(rows[0]["symbol"], "fallback")
        self.assertEqual(rows[0]["weak_defaults"], [weak_name])
        self.assertEqual(rows[0]["target"], DATA_VA)

    def global_case(self, **kwargs):
        return self.run_verify(
            text=b"\0" * 8, retail_text=struct.pack("<I", DATA_VA) + b"\0" * 4,
            relocations=[(0, "global", 0x0006)],
            symbols=self.symbols_for({"name": "global", "value": 0, "section": 0}),
            **kwargs)

    def test_bindings_file_supplies_binding(self):
        rows = self.global_case(central={"global": hex(DATA_VA)})
        self.assertEqual(rows[0]["target"], DATA_VA)
        with self.assertRaisesRegex(VerifyError, "retail target is"):
            self.global_case(central={"global": hex(DATA_VA + 4)})

    def test_symbol_map_overrides_bindings_file(self):
        rows = self.global_case(central={"global": hex(DATA_VA + 4)},
                                explicit={"global": hex(DATA_VA)})
        self.assertEqual(rows[0]["target"], DATA_VA)

    def test_bindings_file_cannot_conflict_with_manifest(self):
        with self.assertRaisesRegex(VerifyError, "bindings file binding for global conflicts"):
            self.global_case(central={"global": hex(DATA_VA)},
                             manifest=[{"sym": "global", "addr": hex(DATA_VA + 4),
                                        "status": "matched", "pct": 100}])

    def test_tu_scoped_binding_applies_to_its_tu_only(self):
        own = [{"sym": "entry", "addr": hex(TEXT_VA), "tu": "own.cpp",
                "status": "matched", "pct": 100}]
        rows = self.global_case(central={"own.cpp::global": hex(DATA_VA)}, manifest=own)
        self.assertEqual(rows[0]["target"], DATA_VA)
        with self.assertRaisesRegex(VerifyError, "no unique matched or explicit binding"):
            self.global_case(central={"other.cpp::global": hex(DATA_VA)}, manifest=own)

    def test_switch_label_after_span_uses_its_position(self):
        # 4-byte span; the $L label (a jump table) sits at +8 in the same section.
        rows = self.run_verify(
            text=struct.pack("<I", 0) + b"\0" * 12, length=4,
            retail_text=struct.pack("<I", TEXT_VA + 8) + b"\0" * 12,
            relocations=[(0, "$L12", 0x0006)],
            symbols=self.symbols_for({"name": "$L12", "value": 8, "section": 1, "storage": 6}))
        self.assertEqual(rows[0]["target"], TEXT_VA + 8)
        with self.assertRaisesRegex(VerifyError, "retail target is"):
            self.run_verify(
                text=struct.pack("<I", 0) + b"\0" * 12, length=4,
                retail_text=struct.pack("<I", TEXT_VA + 12) + b"\0" * 12,
                relocations=[(0, "$L12", 0x0006)],
                symbols=self.symbols_for({"name": "$L12", "value": 8, "section": 1, "storage": 6}))

    def literal_case(self, name, obj_data, retail_data, target=DATA_VA + 4):
        return self.run_verify(
            text=b"\0" * 8, retail_text=struct.pack("<I", target) + b"\0" * 4,
            relocations=[(0, name, 0x0006)],
            symbols=self.symbols_for({"name": name, "value": 0, "section": 2}),
            obj_data=obj_data, retail_data=retail_data)

    def test_literal_binds_where_retail_bytes_equal_it(self):
        name = "??_C@_02A@hi?$AA@"
        retail = b"\0" * 4 + b"hi\0" + b"\0" * 25
        self.assertEqual(self.literal_case(name, b"hi\0", retail)[0]["target"], DATA_VA + 4)
        with self.assertRaisesRegex(VerifyError, "differ from its contents"):
            self.literal_case(name, b"hi\0", b"\0" * 4 + b"ho\0" + b"\0" * 25)

    def test_literal_size_comes_from_its_name(self):
        self.assertEqual(_literal_size("??_C@_00A@?$AA@"), 1)
        self.assertEqual(_literal_size("??_C@_0BB@PACM@x"), 17)
        self.assertEqual(_literal_size("__real@8@3fff8000000000000000"), 8)
        self.assertIsNone(_literal_size("?global@@3HA"))

    def test_tracked_bindings_file_agrees_with_manifest(self):
        central = json.loads(DEFAULT_BINDINGS.read_text())
        manifest = json.loads(DEFAULT_MANIFEST.read_text())
        exact = {}
        for row in manifest:
            if row.get("status") == "matched" and row.get("pct") == 100:
                exact.setdefault(row["sym"], set()).add(int(row["addr"], 16))
        for key, value in central.items():
            name = key.partition("::")[2] or key
            address = int(value, 16)
            self.assertLessEqual(address, 0xFFFFFFFF)
            if name in exact and "::" not in key:
                self.assertIn(address, exact[name], key)


if __name__ == "__main__":
    unittest.main()
