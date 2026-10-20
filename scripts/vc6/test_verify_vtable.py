#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original; synthetic PE/COFF fixtures contain no retail bytes.
"""Synthetic regressions for verify_vtable; no game binary is used."""
import hashlib
import io
import json
import struct
import sys
import tempfile
import unittest
from contextlib import redirect_stdout
from pathlib import Path
from unittest.mock import patch

from verify_vtable import VerifyError, main as verifier_main, verify, parse_coff


def coff_obj(target_names=("foo", "bar"), slot_targets=(0, 1),
             include_second_reloc=True, relocation_kind=6, aux=False,
             relocation_to_aux=False):
    # Two sections: executable function targets and a two-slot read-only table.
    names = [b".text", b".rdata"]
    records = []
    target_indices = []
    for i, name in enumerate(target_names):
        target_indices.append(len(records))
        records.append((name.encode(), i * 4, 1, 0))
        if aux and i == 0:
            records.append((b"", 0, 0, 0, True))
    vt_index = len(records)
    records.append((b"vftable", 0, 2, 0))

    header_size = 20 + 40 * 2
    text_data = b"\xC3\xC3\xC3\xC3" * len(target_names)
    table_data = b"\0" * 8
    text_ptr = header_size
    table_ptr = text_ptr + len(text_data)
    reloc_ptr = table_ptr + len(table_data)
    relocs = []
    for slot, target_no in enumerate(slot_targets):
        if slot == 1 and not include_second_reloc:
            continue
        sym_index = 1 if relocation_to_aux and slot == 0 else target_indices[target_no]
        relocs.append(struct.pack("<IIH", slot * 4, sym_index, relocation_kind))
    sym_ptr = reloc_ptr + 10 * len(relocs)

    # Auxiliary entries have real symbol-table indices but no primary symbol.
    symdata = bytearray()
    stringdata = bytearray()
    actual_index = 0
    for pos, item in enumerate(records):
        if len(item) == 5 and item[4]:
            symdata.extend(b"\0" * 18)
            actual_index += 1
            continue
        name, value, section, _ = item
        if len(name) > 8:
            encoded_name = b"\0\0\0\0" + struct.pack("<I", 4 + len(stringdata))
            stringdata.extend(name + b"\0")
        else:
            encoded_name = name.ljust(8, b"\0")
        aux_count = int(pos + 1 < len(records) and len(records[pos + 1]) == 5)
        symdata.extend(struct.pack("<8sIhHBB", encoded_name, value,
                                   section, 0, 2 if section == 1 else 3, aux_count))
        actual_index += 1
    nsyms = actual_index
    string_table = struct.pack("<I", 4 + len(stringdata)) + bytes(stringdata)
    file_header = struct.pack("<HHIIIHH", 0x14C, 2, 0, sym_ptr, nsyms, 0, 0)
    section_headers = []
    section_headers.append(struct.pack("<8sIIIIIIHHI", b".text", 0, 0,
                                       len(text_data), text_ptr, 0, 0, 0, 0, 0x60000020))
    section_headers.append(struct.pack("<8sIIIIIIHHI", b".rdata", 0, 0,
                                       len(table_data), table_ptr, reloc_ptr,
                                       0, len(relocs), 0, 0x40000040))
    return (file_header + b"".join(section_headers) + text_data + table_data
            + b"".join(relocs) + bytes(symdata) + string_table)


class BssSectionTests(unittest.TestCase):
    def test_bss_allocation_is_not_read_from_file_headers(self):
        data = bytearray(coff_obj())
        struct.pack_into("<8s", data, 20, b".bss")
        struct.pack_into("<II", data, 20 + 16, 0x1000, 0)
        struct.pack_into("<I", data, 20 + 36, 0xC0000080)
        with tempfile.TemporaryDirectory() as tmp:
            path = Path(tmp) / "bss.obj"
            path.write_bytes(data)
            _, sections, _, _ = parse_coff(path)
            self.assertTrue(sections[1]["uninitialized"])
            self.assertEqual(sections[1]["raw_size"], 0x1000)
            # An initialized section with the same absent raw pointer remains
            # invalid: accepting BSS must not relax the header-overlap checks.
            struct.pack_into("<I", data, 20 + 36, 0xC0000040)
            path.write_bytes(data)
            with self.assertRaises(VerifyError):
                parse_coff(path)


def coff_weak_alias(characteristics=3, target_index=0, strong_same_name=False,
                    duplicate_strong=False):
    weak_name = "??_EThing@@UAEPAXI@Z"
    symbols = [("??_GThing@@UAEPAXI@Z", 0, 1, 2, 0)]
    if strong_same_name:
        symbols.append((weak_name, 0, 1, 2, 0))
        if duplicate_strong:
            symbols.append((weak_name, 4, 1, 2, 0))
    weak_index = len(symbols)
    symbols.append((weak_name, 0, 0, 105, 1))
    symbols.append(("??_Other@@UAEXXZ", 4, 1, 2, 0))
    other_index = sum(1 + item[4] for item in symbols[:-1])
    symbols.append(("vftable", 0, 2, 3, 0))
    header_size = 20 + 2 * 40
    text_data = b"\xC3" * 8
    table_data = b"\0" * 8
    text_ptr = header_size
    table_ptr = text_ptr + len(text_data)
    reloc_ptr = table_ptr + len(table_data)
    relocations = (struct.pack("<IIH", 0, weak_index, 6)
                   + struct.pack("<IIH", 4, other_index, 6))
    sym_ptr = reloc_ptr + len(relocations)
    symdata = bytearray()
    strings = bytearray()
    for name, value, section, storage, aux_count in symbols:
        rawname = name.encode()
        if len(rawname) > 8:
            field = b"\0\0\0\0" + struct.pack("<I", 4 + len(strings))
            strings.extend(rawname + b"\0")
        else:
            field = rawname.ljust(8, b"\0")
        symdata.extend(struct.pack("<8sIhHBB", field, value, section,
                                   0, storage, aux_count))
        if storage == 105:
            symdata.extend(struct.pack("<II", target_index, characteristics) + b"\0" * 10)
    nsyms = len(symdata) // 18
    hdr = struct.pack("<HHIIIHH", 0x14C, 2, 0, sym_ptr, nsyms, 0, 0)
    sec1 = struct.pack("<8sIIIIIIHHI", b".text", 0, 0, len(text_data),
                       text_ptr, 0, 0, 0, 0, 0x60000020)
    sec2 = struct.pack("<8sIIIIIIHHI", b".rdata", 0, 0, len(table_data),
                       table_ptr, reloc_ptr, 0, 2, 0, 0x40000040)
    strtab = struct.pack("<I", 4 + len(strings)) + bytes(strings)
    return hdr + sec1 + sec2 + text_data + table_data + relocations + bytes(symdata) + strtab


def pe_image(targets=(0x401000, 0x401004)):
    peoff = 0x80
    optsize = 224
    section_table = peoff + 24 + optsize
    rawptr = 0x200
    data = bytearray(rawptr + 8)
    data[:2] = b"MZ"
    struct.pack_into("<I", data, 0x3C, peoff)
    data[peoff:peoff + 4] = b"PE\0\0"
    struct.pack_into("<HHIIIHH", data, peoff + 4, 0x14C, 1, 0, 0, 0, optsize, 0x010F)
    opt = peoff + 24
    struct.pack_into("<H", data, opt, 0x10B)
    struct.pack_into("<I", data, opt + 28, 0x400000)
    struct.pack_into("<8sIIIIIIHHI", data, section_table, b".rdata", 8,
                      0x1000, 8, rawptr, 0, 0, 0, 0, 0x40000040)
    struct.pack_into("<II", data, rawptr, *targets)
    return bytes(data)


class VerifyVtableTests(unittest.TestCase):
    def setup_case(self, obj_bytes=None, pe_bytes=None, manifest=None, mapping=None,
                   pinned_sha=None):
        temp = tempfile.TemporaryDirectory()
        self.addCleanup(temp.cleanup)
        root = Path(temp.name)
        obj = root / "fixture.obj"
        binary = root / "fixture.exe"
        man = root / "manifest.json"
        totals = root / "totals.json"
        obj.write_bytes(obj_bytes if obj_bytes is not None else coff_obj())
        pe_bytes = pe_bytes if pe_bytes is not None else pe_image()
        binary.write_bytes(pe_bytes)
        manifest = manifest if manifest is not None else [
            {"sym": "foo", "addr": "0x401000", "status": "matched", "pct": 100},
            {"sym": "bar", "addr": "0x401004", "status": "matched", "pct": 100},
        ]
        man.write_text(json.dumps(manifest))
        totals.write_text(json.dumps({"_meta": {"sha256": pinned_sha or hashlib.sha256(pe_bytes).hexdigest()}}))
        mapfile = None
        if mapping is not None:
            mapfile = root / "library.json"
            mapfile.write_text(json.dumps(mapping))
        return obj, binary, man, totals, mapfile

    def run_verify(self, **kwargs):
        weak_defaults = kwargs.pop("weak_defaults", False)
        slots = kwargs.pop("slots", 2)
        paths = self.setup_case(**kwargs)
        obj, binary, manifest, totals, mapping = paths
        return verify(obj, "vftable", 0x401000, slots, binary, manifest, mapping, totals,
                      allow_library_defaults=weak_defaults)

    def test_verified_slots(self):
        result = self.run_verify()
        self.assertEqual([row[2] for row in result], [0x401000, 0x401004])

    def test_wrong_retail_slot_rejected(self):
        with self.assertRaisesRegex(VerifyError, "slot 1"):
            self.run_verify(pe_bytes=pe_image((0x401000, 0x401000)))

    def test_unmatched_manifest_symbol_rejected(self):
        rows = [
            {"sym": "foo", "addr": "0x401000", "status": "partial", "pct": 99},
            {"sym": "bar", "addr": "0x401004", "status": "matched", "pct": 100},
        ]
        with self.assertRaisesRegex(VerifyError, "no 100%-matched"):
            self.run_verify(manifest=rows)

    def test_library_symbol_requires_explicit_mapping(self):
        with self.assertRaisesRegex(VerifyError, "no 100%-matched"):
            self.run_verify(obj_bytes=coff_obj(("__purecall", "bar")))
        result = self.run_verify(obj_bytes=coff_obj(("__purecall", "bar")),
                                 mapping={"__purecall": "0x401000"})
        self.assertEqual(len(result), 2)

    def test_missing_slot_relocation_rejected(self):
        with self.assertRaisesRegex(VerifyError, "no COFF relocation"):
            self.run_verify(obj_bytes=coff_obj(include_second_reloc=False))

    def test_nonpositive_slot_count_rejected_by_api(self):
        with self.assertRaisesRegex(VerifyError, "slot count must be positive"):
            self.run_verify(slots=0)

    def test_non_dir32_relocation_rejected(self):
        with self.assertRaisesRegex(VerifyError, "unsupported type"):
            self.run_verify(obj_bytes=coff_obj(relocation_kind=0x14))

    def test_auxiliary_record_cannot_be_relocation_target(self):
        with self.assertRaisesRegex(VerifyError, "auxiliary symbol index"):
            self.run_verify(obj_bytes=coff_obj(aux=True, relocation_to_aux=True))

    def test_weak_external_search_alias_resolves_target_index(self):
        mangled = "??_GThing@@UAEPAXI@Z"
        manifest = [
            {"sym": mangled, "addr": "0x401000", "status": "matched", "pct": 100},
            {"sym": "??_Other@@UAEXXZ", "addr": "0x401004", "status": "matched", "pct": 100},
        ]
        result = self.run_verify(obj_bytes=coff_weak_alias(), manifest=manifest)
        self.assertEqual([row[2] for row in result], [0x401000, 0x401004])

    def test_search_library_default_is_opt_in_and_reported_conditional(self):
        weak_name = "??_EThing@@UAEPAXI@Z"
        manifest = [
            {"sym": "??_GThing@@UAEPAXI@Z", "addr": "0x401000", "status": "matched", "pct": 100},
            {"sym": "??_Other@@UAEXXZ", "addr": "0x401004", "status": "matched", "pct": 100},
        ]
        with self.assertRaisesRegex(VerifyError, "SEARCH_LIBRARY.*--weak-defaults"):
            self.run_verify(obj_bytes=coff_weak_alias(characteristics=2), manifest=manifest)
        rows = self.run_verify(obj_bytes=coff_weak_alias(characteristics=2),
                               manifest=manifest, weak_defaults=True)
        self.assertEqual(rows[0][3], [weak_name])

    def test_search_library_prefers_known_same_name_mapping(self):
        weak_name = "??_EThing@@UAEPAXI@Z"
        manifest = [
            {"sym": weak_name, "addr": "0x401000", "status": "matched", "pct": 100},
            {"sym": "??_Other@@UAEXXZ", "addr": "0x401004", "status": "matched", "pct": 100},
        ]
        rows = self.run_verify(obj_bytes=coff_weak_alias(characteristics=2), manifest=manifest)
        self.assertEqual(rows[0][1], weak_name)
        self.assertEqual(rows[0][3], [])

    def test_search_library_prefers_defined_same_name_coff_symbol(self):
        weak_name = "??_EThing@@UAEPAXI@Z"
        manifest = [
            {"sym": weak_name, "addr": "0x401000", "status": "matched", "pct": 100},
            {"sym": "??_Other@@UAEXXZ", "addr": "0x401004", "status": "matched", "pct": 100},
        ]
        rows = self.run_verify(obj_bytes=coff_weak_alias(characteristics=2,
                                                         strong_same_name=True),
                               manifest=manifest)
        self.assertEqual(rows[0][1], weak_name)
        self.assertEqual(rows[0][3], [])

    def test_conflicting_strong_same_name_symbols_rejected(self):
        weak_name = "??_EThing@@UAEPAXI@Z"
        manifest = [
            {"sym": weak_name, "addr": "0x401000", "status": "matched", "pct": 100},
            {"sym": "??_Other@@UAEXXZ", "addr": "0x401004", "status": "matched", "pct": 100},
        ]
        with self.assertRaisesRegex(VerifyError, "ambiguous same-name strong"):
            self.run_verify(obj_bytes=coff_weak_alias(characteristics=2,
                                                      strong_same_name=True,
                                                      duplicate_strong=True),
                            manifest=manifest)

    def test_conditional_summary_is_explicit(self):
        manifest = [
            {"sym": "??_GThing@@UAEPAXI@Z", "addr": "0x401000", "status": "matched", "pct": 100},
            {"sym": "??_Other@@UAEXXZ", "addr": "0x401004", "status": "matched", "pct": 100},
        ]
        paths = self.setup_case(obj_bytes=coff_weak_alias(characteristics=2), manifest=manifest)
        obj, binary, manifest_file, totals, _ = paths
        argv = ["verify_vtable.py", "--obj", str(obj), "--sym", "vftable",
                "--addr", "0x401000", "--slots", "2", "--binary", str(binary),
                "--manifest", str(manifest_file), "--totals", str(totals), "--weak-defaults"]
        output = io.StringIO()
        with patch.object(sys, "argv", argv), redirect_stdout(output):
            self.assertEqual(verifier_main(), 0)
        self.assertIn("vtable slots conditionally verified: 2/2", output.getvalue())
        self.assertIn("a final link may select strong library definitions", output.getvalue())

    def test_weak_external_rejects_unsupported_search_kind(self):
        with self.assertRaisesRegex(VerifyError, "unsupported search kind"):
            self.run_verify(obj_bytes=coff_weak_alias(characteristics=4))

    def test_weak_external_rejects_alias_cycle(self):
        with self.assertRaisesRegex(VerifyError, "cycle in COFF weak-external"):
            self.run_verify(obj_bytes=coff_weak_alias(target_index=1))

    def test_weak_external_rejects_auxiliary_and_missing_alias_indices(self):
        with self.assertRaisesRegex(VerifyError, "auxiliary symbol index"):
            self.run_verify(obj_bytes=coff_weak_alias(target_index=2))
        with self.assertRaisesRegex(VerifyError, "missing symbol index"):
            self.run_verify(obj_bytes=coff_weak_alias(target_index=30))

    def test_pinned_image_hash_required(self):
        with self.assertRaisesRegex(VerifyError, "SHA-256 mismatch"):
            self.run_verify(pinned_sha="0" * 64)

    def test_coff_raw_pointer_cannot_point_into_headers(self):
        obj = bytearray(coff_obj())
        # The second section's PointerToRawData points at file offset 80.
        struct.pack_into("<I", obj, 20 + 40 + 20, 0)
        with self.assertRaisesRegex(VerifyError, "COFF section .rdata raw data overlaps"):
            self.run_verify(obj_bytes=bytes(obj))

    def test_coff_symbol_table_cannot_point_into_headers(self):
        obj = bytearray(coff_obj())
        struct.pack_into("<I", obj, 8, 10)
        with self.assertRaisesRegex(VerifyError, "COFF symbol table overlaps"):
            self.run_verify(obj_bytes=bytes(obj))

    def test_pe_raw_pointer_cannot_point_into_headers(self):
        image = bytearray(pe_image())
        peoff = struct.unpack_from("<I", image, 0x3C)[0]
        optsize = struct.unpack_from("<H", image, peoff + 20)[0]
        section_table = peoff + 24 + optsize
        struct.pack_into("<I", image, section_table + 20, 0x80)
        with self.assertRaisesRegex(VerifyError, "PE section .rdata raw data overlaps headers"):
            self.run_verify(pe_bytes=bytes(image))


if __name__ == "__main__":
    unittest.main()
