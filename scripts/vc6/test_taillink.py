#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original synthetic objects and archives; no retail bytes.
"""taillink: library members become orderable COMDATs; order list and filler logic."""

from pathlib import Path
import struct
import tempfile
import unittest

import coffgen
import tail_layout
import taillink
from test_crt_ident import archive


def sym(name, value, section, scl, naux=0):
    return name.encode().ljust(8, b"\0") + struct.pack("<IhHBB", value, section, 0x20 if scl == 2 else 0, scl, naux)


def member(code, symbols, comdat=False):
    """One .text section (plain or COMDAT) with the given extra symbols after its section symbol."""
    flags = 0x60500020 | (taillink.coffgen.SCN_LNK_COMDAT if comdat else 0)
    syms = sym(".text", 0, 1, coffgen.CLASS_STATIC, 1) + struct.pack("<IHHIHB3x", len(code), 0, 0, 0, 0, 0)
    syms += b"".join(symbols)
    nsyms = 2 + len(symbols)
    symptr = 20 + 40 + len(code)
    header = struct.pack("<HHIIIHH", coffgen.I386, 1, 0, symptr, nsyms, 0, 0)
    sec = b".text\0\0\0" + struct.pack("<IIIIIIHHI", 0, 0, len(code), 60, 0, 0, 0, 0, flags)
    return header + sec + code + syms + struct.pack("<I", 4)


def section_flags(obj):
    return struct.unpack_from("<I", obj, 20 + 36)[0]


class PrepareMemberTests(unittest.TestCase):
    def test_plain_section_becomes_comdat_keyed_by_first_symbol(self):
        obj = member(b"\xc3" * 8, [sym("_b", 4, 1, 2), sym("_a", 0, 1, 2)])
        out, keys = taillink.prepare_member(obj, [(1, "7C0000")])
        self.assertTrue(section_flags(out) & coffgen.SCN_LNK_COMDAT)
        self.assertEqual(keys, {1: "_b"})   # symbol-table order, not offset order (LINK probe)
        rows = {n: (v, s, c) for _, n, v, s, c, _ in coffgen.read_symbols(out)}
        self.assertEqual(rows["_b"][2], coffgen.CLASS_EXTERNAL)
        aux = 20 + 40 + 8 + 18 * 1   # the section symbol's auxiliary record
        self.assertEqual(out[aux + 14], coffgen.COMDAT_ANY)

    def test_static_key_is_renamed_to_a_unique_external(self):
        obj = member(b"\xc3" * 4, [sym("$S1", 0, 1, coffgen.CLASS_STATIC)], comdat=True)
        out, keys = taillink.prepare_member(obj, [(1, "7C1234")])
        self.assertEqual(keys, {1: "?tail_7C1234@@YAXXZ"})
        rows = {n: c for _, n, _, _, c, _ in coffgen.read_symbols(out)}
        self.assertEqual(rows["?tail_7C1234@@YAXXZ"], coffgen.CLASS_EXTERNAL)

    def test_nameless_section_gets_a_new_symbol(self):
        obj = member(b"\xc3" * 4, [], comdat=True)
        out, keys = taillink.prepare_member(obj, [(1, "7C2000")])
        rows = {n: (s, v) for _, n, v, s, _, _ in coffgen.read_symbols(out)}
        self.assertEqual(rows[keys[1]], (1, 0))


def entry(addr, length, name, align=16):
    return {"addr": addr, "len": length, "align": align, "name": name, "names": [(name, 0)]}


class OrderTests(unittest.TestCase):
    def test_natural_alignment_needs_no_filler(self):
        order, fillers, names_at, skipped, end = taillink.order_entries(
            [entry(0x1000, 0x1C, "_a"), entry(0x1020, 4, "_b")], 0x1000)
        self.assertEqual((order, fillers, skipped, end), (["_a", "_b"], [], [], 0x1024))
        self.assertEqual(names_at, {0x1000: "_a", 0x1020: "_b"})

    def test_unidentified_bytes_get_a_filler(self):
        order, fillers, names_at, skipped, _ = taillink.order_entries(
            [entry(0x1000, 0x10, "_a"), entry(0x1050, 4, "_b")], 0x1000)
        self.assertEqual(fillers, [("?tailgap_00001010@@YAXXZ", 0x40)])
        self.assertEqual(order, ["_a", "?tailgap_00001010@@YAXXZ", "_b"])
        self.assertEqual(names_at[0x1010], "?tailgap_00001010@@YAXXZ")

    def test_gap_before_the_first_entry_and_unaligned_thunks(self):
        order, fillers, _, _, end = taillink.order_entries(
            [entry(0x1007, 6, "_t1", 1), entry(0x100D, 6, "_t2", 1)], 0x1000)
        self.assertEqual(fillers, [("?tailgap_00001000@@YAXXZ", 7)])
        self.assertEqual(end, 0x1013)

    def test_overlap_is_skipped(self):
        order, _, _, skipped, _ = taillink.order_entries([entry(0x1000, 0x20, "_a"), entry(0x1010, 4, "_b")], 0x1000)
        self.assertEqual(order, ["_a"])
        self.assertEqual(skipped[0]["name"], "_b")


class CheckMapTests(unittest.TestCase):
    def test_counts(self):
        layout = {"thunks": [{"addr": "0x1000", "name": "_t@0"}],
                  "sections": [{"addr": "0x1010", "symbols": [["_f", 0], ["_g", 4]]}]}
        got = taillink.check_map({"_t@0": 0x1000, "_f": 0x1010, "_g": 0x2000}, layout)
        self.assertEqual((got["symbols"], got["at_retail_address"], got["displaced"], got["not_in_map"]), (3, 2, 1, 0))
        self.assertEqual(got["first_displaced"][0]["symbol"], "_g")


class PlanTailTests(unittest.TestCase):
    def test_members_are_copied_and_ordered(self):
        layout = {"thunks": [{"addr": "0x1000", "name": "_thunk@0"}],
                  "sections": [{"addr": "0x1010", "len": 8, "align": 16, "library": "T.LIB", "member_index": 0,
                                "member": "a.obj", "section": 1, "comdat": False, "symbols": [["_f", 0]]}]}
        with tempfile.TemporaryDirectory() as tmp:
            tmp = Path(tmp)
            (tmp / "T.LIB").write_bytes(archive([("a.obj", member(b"\xc3" * 8, [sym("_f", 0, 1, 2)]))]))
            plan = taillink.plan_tail(layout, tmp, 0x1000, tmp / "out")
            self.assertEqual(plan["order"][0:1] + plan["order"][-1:], ["_thunk@0", "_f"])
            (copy,) = plan["objects"]
            self.assertTrue(section_flags(copy.read_bytes()) & coffgen.SCN_LNK_COMDAT)
            self.assertEqual(plan["names_at"][0x1010], "_f")
            self.assertEqual(plan["report"]["problems"], [])

    def test_member_name_mismatch_is_reported_not_linked(self):
        layout = {"thunks": [], "sections": [{"addr": "0x1000", "len": 8, "align": 16, "library": "T.LIB",
                                              "member_index": 0, "member": "other.obj", "section": 1,
                                              "comdat": False, "symbols": [["_f", 0]]}]}
        with tempfile.TemporaryDirectory() as tmp:
            tmp = Path(tmp)
            (tmp / "T.LIB").write_bytes(archive([("a.obj", member(b"\xc3" * 8, [sym("_f", 0, 1, 2)]))]))
            plan = taillink.plan_tail(layout, tmp, 0x1000, tmp / "out")
            self.assertEqual(plan["objects"], [])
            self.assertEqual(len(plan["report"]["problems"]), 1)


class ThunkRunTests(unittest.TestCase):
    def test_runs_before_the_tail_and_in_gaps(self):
        jmp = lambda slot: b"\xff\x25" + struct.pack("<I", slot)
        text = b"\xcc" * 4 + jmp(0x7E1000) + jmp(0x7E1004) + b"\x55" * 10 + jmp(0x7E1008) + b"\xcc" * 2
        base = 0x401000
        tail = base + 4 + 12
        gaps = [{"kind": "import_thunks", "addr": f"0x{tail + 10:X}", "len": 6}, {"kind": "padding", "addr": "0x0", "len": 1}]
        self.assertEqual(tail_layout.thunk_runs(tail, None, base, text, gaps),
                         [(base + 4, 0x7E1000), (base + 10, 0x7E1004), (tail + 10, 0x7E1008)])


if __name__ == "__main__":
    unittest.main()
