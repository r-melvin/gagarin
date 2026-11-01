# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original project tooling.
"""Tests for the reccmp image tooling: the pure logic in debug_neutral, reccmp_sanitize, reccmp_audit and
reccmp_image (no compiler, linker or reccmp installation needed)."""

import json
from pathlib import Path
import sys
import tempfile
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parent))
import coffgen  # noqa: E402
import debug_neutral  # noqa: E402
import hybrid  # noqa: E402
import reccmp_audit  # noqa: E402
import reccmp_image  # noqa: E402
import reccmp_sanitize  # noqa: E402

CODE = coffgen.SCN_CNT_CODE | coffgen.SCN_MEM_EXECUTE | coffgen.SCN_MEM_READ


def obj(text=b"\x90\x90", debug=b"AAAA", relocs=(), rdata=None):
    sections = [(".text", CODE, text, len(text), list(relocs))]
    if rdata is not None:
        sections.append((".rdata", hybrid.DATA_FLAGS, rdata, len(rdata), []))
    sections.append((".debug$S", hybrid.DATA_FLAGS, debug, len(debug), []))
    return hybrid.write_object(sections)


class DebugNeutral(unittest.TestCase):
    def test_debug_sections_are_ignored(self):
        self.assertEqual(debug_neutral.compare_object(obj(debug=b"AAAA"), obj(debug=b"BBBBBBBB")), [])

    def test_code_bytes_are_compared(self):
        found = debug_neutral.compare_object(obj(), obj(text=b"\x90\xCC"))
        self.assertTrue(any("bytes differ" in f for f in found))

    def test_relocation_targets_are_compared_by_name(self):
        a = obj(text=bytes(4), relocs=[(0, "_target_a", coffgen.REL_DIR32)])
        b = obj(text=bytes(4), relocs=[(0, "_target_b", coffgen.REL_DIR32)])
        self.assertEqual(debug_neutral.compare_object(a, a), [])
        self.assertTrue(any("relocations differ" in f for f in debug_neutral.compare_object(a, b)))

    def test_missing_section_is_reported(self):
        found = debug_neutral.compare_object(obj(rdata=b"data"), obj())
        self.assertTrue(found)

    def test_categories(self):
        self.assertEqual(debug_neutral.categorise(["section order differs"]), "section_order")
        self.assertEqual(debug_neutral.categorise([".rdata$r ??_R3Foo@@8: bytes differ (16 vs 16 bytes)"]), "rtti_chd_bytes")
        self.assertEqual(debug_neutral.categorise([".text ?f@@YAXXZ: bytes differ (2 vs 2 bytes)"]), "other")

    def test_object_directories(self):
        with tempfile.TemporaryDirectory() as tmp:
            plain, debug = Path(tmp, "plain"), Path(tmp, "debug")
            for d in (plain, debug):
                d.mkdir()
                (d / "a.obj").write_bytes(obj())
            (plain / "b.obj").write_bytes(obj())
            (debug / "b.obj").write_bytes(obj(text=b"\xCC\xCC", debug=b"ZZ"))
            report = debug_neutral.compare_objects(plain, debug)
            self.assertEqual(report["objects_compared"], 2)
            self.assertEqual(list(report["differences"]), ["b.obj"])
            self.assertEqual(report["by_kind"], {"other": 1})


class Sanitize(unittest.TestCase):
    def test_listing_lines_become_comments(self):
        lines = ["//   FUNCTION: GAMEMD 0x401000  Foo::Bar", "// FUNCTION: GAMEMD 0x401000", "void Foo::Bar()"]
        self.assertEqual(reccmp_sanitize.defang_listings(lines), [1])
        self.assertIn("(listing)", lines[0])
        self.assertEqual(lines[1], "// FUNCTION: GAMEMD 0x401000")

    def test_markers_move_below_the_comment_block(self):
        lines = ["// FUNCTION: GAMEMD 0x401000", "//", "// Does a thing.", "void Foo::Bar()", "{"]
        self.assertEqual(reccmp_sanitize.rotate_markers(lines), [1])
        self.assertEqual(lines, ["//", "// Does a thing.", "// FUNCTION: GAMEMD 0x401000", "void Foo::Bar()", "{"])

    def test_adjacent_marker_is_left_alone(self):
        lines = ["// FUNCTION: GAMEMD 0x401000", "void Foo::Bar()", "{"]
        self.assertEqual(reccmp_sanitize.rotate_markers(lines), [])
        self.assertEqual(lines[0], "// FUNCTION: GAMEMD 0x401000")

    def test_line_count_and_code_lines_are_preserved(self):
        lines = ["", "// FUNCTION: GAMEMD 0x401000", "// STRING: GAMEMD 0x81784C", "", "// note", "int x;", "void g();"]
        before = list(lines)
        reccmp_sanitize.rotate_markers(lines)
        self.assertEqual(len(lines), len(before))
        self.assertEqual(lines[-2:], before[-2:])

    def test_nameref_markers_are_not_rotated(self):
        lines = ["// SYNTHETIC: GAMEMD 0x401000", "// Foo::`scalar deleting destructor'", "void x();"]
        self.assertEqual(reccmp_sanitize.rotate_markers(lines), [])


class Audit(unittest.TestCase):
    def test_names_only_ignores_tagged_operands_and_line_notes(self):
        orig = ["push ebx", "mov ecx, dword ptr [DAT_00B0F670 (DATA)]", "call The stored ratio is a fixed-point value (FUNCTION)"]
        recomp = ["push ebx \t(a.cpp:85)", "mov ecx, dword ptr [<OFFSET2>]", "call FUN_004071A0 (FUNCTION) \t(a.cpp:86)"]
        self.assertTrue(reccmp_audit.names_only(orig, recomp))

    def test_names_only_rejects_real_differences(self):
        self.assertFalse(reccmp_audit.names_only(["mov eax, ebx"], ["mov eax, ecx"]))
        self.assertFalse(reccmp_audit.names_only(["mov eax, [esp + 4]"], ["mov eax, [esp + 8]"]))
        self.assertFalse(reccmp_audit.names_only(["ret"], ["ret", "nop"]))

    def test_bare_address_matches_a_data_name(self):
        self.assertTrue(reccmp_audit.names_only(["mov eax, InvalidCell (DATA)"], ["mov eax, 0xabdc50"]))

    def test_provenance(self):
        with tempfile.TemporaryDirectory() as tmp:
            path = Path(tmp, "placement.json")
            path.write_text(json.dumps({"pieces": [[".text", 0x401000, 0x10, "project", "a"],
                                                     [".text", 0x401020, 0x10, "library", "b"],
                                                     [".rdata", 0x7E1000, 0x10, "project", "c"]]}))
            of = reccmp_audit.provenance(path)
            self.assertEqual([of(0x401000), of(0x40100F), of(0x401010), of(0x401020), of(0x7E1000)],
                             ["project", "project", "retail", "library", "retail"])


class Image(unittest.TestCase):
    def test_stack_targets_take_unlanded_near_misses_in_percentage_order(self):
        with tempfile.TemporaryDirectory() as tmp:
            manifest = Path(tmp, "m.json")
            manifest.write_text(json.dumps([{"addr": "0x401000", "status": "partial"}, {"addr": "0x401100", "status": "matched"},
                                            {"addr": "0x401200", "status": "partial"}, {"addr": "0x401300", "status": "partial"}]))
            queue = Path(tmp, "q.tsv")
            queue.write_text("addr\tpct\tmultiset_identical\n0x401000\t98.0\tTrue\n0x401100\t99.9\tTrue\n"
                             "0x401200\t99.0\tTrue\n0x401300\t99.5\tFalse\n")
            self.assertEqual(reccmp_image.stack_targets(queue, manifest, 5), ["0x401200", "0x401000"])
            self.assertEqual(reccmp_image.stack_targets(queue, manifest, 1), ["0x401200"])

    def test_reccmp_summary(self):
        with tempfile.TemporaryDirectory() as tmp:
            log = Path(tmp, "r.log")
            log.write_text("noise\nImplemented:  39.12%  (4936 / 12616)\nAccuracy:     90.97%\n4931 functions are aligned (39.09%)\n")
            self.assertEqual(reccmp_image.reccmp_summary(log), {"implemented": 39.12, "functions_implemented": 4936,
                                                               "functions_total": 12616, "accuracy": 90.97, "aligned": 4931})


if __name__ == "__main__":
    unittest.main()
