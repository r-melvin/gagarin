#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original synthetic images; no retail bytes.
"""Tests for x86scan, twinpair and extent_recall on small synthetic PE-like images.

    python3 -m unittest test_twin_extent      (from scripts/agent_tools)
"""
import json
import struct
import sys
import tempfile
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import extent_recall as ER  # noqa: E402
import twinpair as TP  # noqa: E402
import x86scan as X  # noqa: E402

BASE, TEXT, RDATA, DATA = 0x400000, 0x401000, 0x410000, 0x420000


def rel32(op, at, to):
    return bytes([op]) + struct.pack("<i", to - (at + 5))


def pad(code, to_len=None):
    n = (16 - len(code) % 16) % 16 if to_len is None else to_len - len(code)
    return code + b"\xcc" * n


def image(text, rdata=b"\0" * 64, data=b"\0" * 64):
    return X.Image.from_sections(BASE, [(".text", TEXT, text), (".rdata", RDATA, rdata), (".data", DATA, data)])


class DecodeTests(unittest.TestCase):
    def d(self, hexs, va=TEXT):
        b = bytes.fromhex(hexs) + b"\x90" * 8
        return X.decode(b, 0, va)

    def test_lengths(self):
        for h, n in (("55", 1), ("8bec", 2), ("c74610 78563412", 7), ("66b81234", 4), ("a1 00104200", 5),
                     ("8b4424 04", 4), ("8d8c24 10010000", 7), ("c2 0400", 3), ("6a ff", 2), ("0fb645 08", 4),
                     ("f6 45 08 01", 4), ("f7 45 08 01000000", 7), ("d9 45 08", 3), ("0f 84 10000000", 6)):
            self.assertEqual(self.d(h.replace(" ", ""))[0], n, h)

    def test_kinds_and_targets(self):
        n, kind, tgt, fields, op, pre, tbl = self.d("e8 fb 0f 00 00")
        self.assertEqual((n, kind, tgt), (5, X.CALL, TEXT + 5 + 0xFFB))
        self.assertEqual(fields, ((1, X.REL),))
        self.assertEqual(self.d("eb fe")[1:3], (X.JMP, TEXT))
        self.assertEqual(self.d("74 02")[1:3], (X.JCC, TEXT + 4))
        self.assertEqual(self.d("0f 85 00 01 00 00")[1:3], (X.JCC, TEXT + 6 + 0x100))
        self.assertEqual(self.d("c3")[1], X.RET)
        self.assertEqual(self.d("cc")[1], X.INT3)
        self.assertEqual(self.d("ff d0")[1], X.CALLIND)
        self.assertEqual(self.d("ff 25 00 10 41 00")[1], X.JMPIND)

    def test_jump_table_operand(self):
        r = self.d("ff 24 85 00 00 41 00")
        self.assertEqual((r[0], r[1], r[6]), (7, X.JMPIND, 0x410000))

    def test_invalid_and_truncated(self):
        self.assertIsNone(X.decode(b"\xe8\x00", 0, TEXT))
        self.assertIsNone(X.decode(b"\x9a" + b"\0" * 8, 0, TEXT))

    def test_imm_and_disp_fields(self):
        r = self.d("c7 05 00 00 42 00 00 10 40 00")
        self.assertEqual(r[3], ((2, X.DISP), (6, X.IMM)))


class WalkTests(unittest.TestCase):
    def build(self):
        # A: push ebp; mov ebp,esp; call C; cmp eax,3; ja L; jmp [eax*4+T]; ... cases ... ret ; jmp tail
        a = TEXT
        c_va = TEXT + 0x80
        tail_va = TEXT + 0xC0
        code = bytearray(b"\xcc" * 0x100)
        body = b"\x55\x8b\xec" + rel32(0xE8, a + 3, c_va) + b"\x83\xf8\x03" + b"\x77\x0f"
        tbl_va = TEXT + 0xE0
        body += b"\xff\x24\x85" + struct.pack("<I", tbl_va)
        # case bodies right after: 4 one-byte cases then a default ret
        case0 = a + len(body)
        body += b"\x90\xc3" + b"\x90\xc3" + b"\x90\xc3" + b"\x90\xc3"       # 4 cases, 2 bytes each
        body += b"\x5d" + rel32(0xE9, a + len(body) + 1, tail_va)             # default: pop ebp; jmp tail
        code[0:len(body)] = body
        code[0x80:0x83] = b"\x33\xc0\xc3"                                    # C: xor eax,eax; ret
        code[0xC0:0xC1] = b"\xc3"                                            # tail: ret
        for i in range(4):
            code[0xE0 + 4 * i:0xE0 + 4 * i + 4] = struct.pack("<I", case0 + 2 * i)
        return bytes(code), a, c_va, tail_va, tbl_va

    def test_walk_follows_cases_records_calls_tail_and_table(self):
        code, a, c_va, tail_va, tbl_va = self.build()
        img = image(code)
        w = X.walk(img, a, starts={tail_va})
        self.assertEqual([t for _, t in w.calls], [c_va])
        self.assertEqual([t for _, t in w.tail], [tail_va])
        self.assertEqual(len(w.tables), 1)
        self.assertEqual(len(w.tables[0][1]), 4)                # cmp 3 -> 4 entries
        self.assertGreaterEqual(w.end, tbl_va + 16)
        self.assertFalse(w.bad)
        self.assertNotIn(c_va, w.insns)

    def test_discover_adds_call_targets(self):
        code, a, c_va, tail_va, _ = self.build()
        img = image(code)
        walks, starts, ev = X.discover(img, [a])
        self.assertIn(c_va, starts)
        self.assertEqual(ev[c_va]["call"], [a + 3])

    def test_mask_zeroes_calls_and_absolute_addresses(self):
        code = pad(b"\x55\x8b\xec" + rel32(0xE8, TEXT + 3, TEXT + 0x40) + b"\xa1" + struct.pack("<I", DATA) + b"\x5d\xc3")
        img = image(code + b"\xcc" * 0x40)
        w = X.walk(img, TEXT)
        toks = X.mask_bytes(img, w)
        self.assertIn(b"\xe8\0\0\0\0", toks)
        self.assertIn(b"\xa1\0\0\0\0", toks)

    def test_rtti_vtables(self):
        td, col, vt = RDATA + 0x00, RDATA + 0x20, RDATA + 0x40
        r = bytearray(0x80)
        r[0:8] = b"\0" * 8
        r[8:8 + 8] = b".?AVFoo@@"[:8]
        r[8:8 + 10] = b".?AVFoo@@\0"
        r[0x20:0x34] = struct.pack("<IiIII", 0, 0, 0, td, td)
        r[0x3C:0x40] = struct.pack("<I", col)
        r[0x40:0x48] = struct.pack("<II", TEXT, TEXT + 0x10)
        img = image(pad(b"\xc3") * 2, bytes(r))
        self.assertEqual(X.rtti_vtables(img), {(".?AVFoo@@", 0): [TEXT, TEXT + 0x10]})


class PairTests(unittest.TestCase):
    def fn(self, addr, body=b"x", strs=(), calls=(), shape=None):
        f = TP.Fn()
        f.addr, f.end = addr, addr + len(body)
        f.toks = [bytes([c]) for c in body]
        f.hash = body
        f.shape = shape or body
        f.strs = frozenset(strs)
        f.calls = tuple(calls)
        f.nbytes = len(body)
        return f

    def test_unique_string_pairs_and_ties_are_not_guessed(self):
        yf = {1: self.fn(1, b"abcdefgh", ["only-here"]), 2: self.fn(2, b"zzzzzzzz", ["both"]), 3: self.fn(3, b"yyyyyyyy", ["both"])}
        rf = {11: self.fn(11, b"abcdefgx", ["only-here"]), 12: self.fn(12, b"qqqqqqqq", ["both"])}
        p = TP.Pairing(yf, rf, {}, {})
        p.by_strings()
        self.assertEqual(p.y2r, {1: 11})
        self.assertEqual(p.method[1], "string")

    def test_unique_hash_pairs(self):
        yf = {1: self.fn(1, b"identical-code"), 2: self.fn(2, b"other-code-x")}
        rf = {11: self.fn(11, b"identical-code"), 12: self.fn(12, b"other-code-y")}
        p = TP.Pairing(yf, rf, {}, {})
        p.by_hash()
        self.assertEqual(p.y2r, {1: 11})

    def test_anchored_hash_groups_pair_by_position(self):
        same = b"same-code-stub!"
        yf = {10: self.fn(10, b"anchor-one-aaaa"), 20: self.fn(20, same), 30: self.fn(30, b"anchor-two-bbbb"),
              40: self.fn(40, same), 50: self.fn(50, b"anchor-three-cc")}
        rf = {110: self.fn(110, b"anchor-one-aaaa"), 120: self.fn(120, same), 130: self.fn(130, b"anchor-two-bbbb"),
              140: self.fn(140, same), 150: self.fn(150, b"anchor-three-cc")}
        p = TP.Pairing(yf, rf, {}, {})
        p.by_hash()
        p.by_hash_anchored()
        self.assertEqual(p.y2r, {10: 110, 20: 120, 30: 130, 40: 140, 50: 150})
        self.assertEqual(p.method[20], "hash-anchor")

    def test_vtable_slot_pairs_but_identical_twin_vetoes_a_shifted_slot(self):
        yvt = {("C", 0): [1, 2]}
        rvt = {("C", 0): [11, 12]}
        yf = {1: self.fn(1, b"aaaaaaaa-body"), 2: self.fn(2, b"bbbbbbbb-body")}
        rf = {11: self.fn(11, b"aaaaaaaa-body"), 12: self.fn(12, b"bbbbbbbb-bodz")}
        p = TP.Pairing(yf, rf, yvt, rvt)
        p.by_vtables()
        self.assertEqual(p.y2r, {1: 11, 2: 12})
        # slot shifted by one in RA2, and the identical twin of Y1 still unpaired: the shifted pair is vetoed
        rvt2 = {("C", 0): [12, 11]}
        p2 = TP.Pairing(yf, rf, yvt, rvt2)
        p2.by_vtables()
        self.assertEqual(p2.y2r, {})

    def test_callee_order_propagates(self):
        yf = {1: self.fn(1, b"caller-body-same", calls=[2, 3]), 2: self.fn(2, b"callee-one-body"), 3: self.fn(3, b"callee-two-body")}
        rf = {11: self.fn(11, b"caller-body-same", calls=[12, 13]), 12: self.fn(12, b"callee-one-bodx"), 13: self.fn(13, b"callee-two-bodx")}
        p = TP.Pairing(yf, rf, {}, {})
        p.add(1, 11, "hash")
        p.by_callees(0.5)
        self.assertEqual(p.y2r, {1: 11, 2: 12, 3: 13})
        self.assertEqual(p.method[2], "callee-order")

    def test_callee_order_with_contradicting_pair_is_a_conflict(self):
        yf = {1: self.fn(1, b"caller-body-same", calls=[2, 3]), 2: self.fn(2, b"callee-one-body"), 3: self.fn(3, b"callee-two-body")}
        rf = {11: self.fn(11, b"caller-body-same", calls=[12, 13]), 12: self.fn(12, b"callee-one-bodx"), 13: self.fn(13, b"callee-two-bodx")}
        p = TP.Pairing(yf, rf, {}, {})
        p.add(1, 11, "hash")
        p.add(2, 13, "hash")
        p.by_callees(0.5)
        self.assertNotIn(3, p.y2r)
        self.assertEqual([c["kind"] for c in p.conflicts], ["callee-order-disagrees"])

    def test_similarity_and_kind(self):
        a, b = self.fn(1, b"abcdefghij"), self.fn(2, b"abcdefghij")
        self.assertEqual(TP.similarity(a, b), 1.0)
        c = self.fn(3, b"abcdefghiX")
        self.assertAlmostEqual(TP.similarity(a, c), 0.9, 2)
        p = TP.Pairing({1: a, 3: c}, {2: b}, {}, {})
        p.add(1, 2, "hash")
        self.assertEqual(TP.kind_of(p, 1), "exact")

    def test_twin_map_roundtrip_and_old_csv_format(self):
        with tempfile.TemporaryDirectory() as t:
            m = Path(t) / "twin_map.json"
            m.write_text(json.dumps({"pairs": [{"yr_addr": "0x401000", "ra2_addr": "0x402000", "kind": "exact", "similarity": 1.0}]}))
            self.assertEqual(TP.load_twins(m), {0x401000: ("exact", 1.0, 0x402000)})
            c = Path(t) / "pairs.csv"
            c.write_text("ra2_addr,yr_addr,size_ra2,size_yr,kind,similarity,yr_manifest_status,yr_name,class\n"
                         "0x402000,0x401000,10,10,exact,1.0,matched,,\n0x402100,0x401100,10,12,changed-vtslot,0.4,,,\n")
            tw = TP.load_twins(c)
            self.assertEqual(tw[0x401000], ("exact", 1.0, 0x402000))
            self.assertEqual(TP.twin_label(tw[0x401100][0]), "changed")
            self.assertEqual(TP.twin_label("exact"), "identical")
            self.assertEqual(TP.twin_label(None), "none")

    def test_csv_writer_keeps_old_columns(self):
        a = self.fn(0x401000, b"abcdefghij")
        b = self.fn(0x402000, b"abcdefghij")
        p = TP.Pairing({0x401000: a}, {0x402000: b}, {}, {})
        p.add(0x401000, 0x402000, "hash")
        with tempfile.TemporaryDirectory() as t:
            out = Path(t) / "pairs.csv"
            TP.write_csv(out, p)
            old = TP.load_old(out)
            self.assertEqual(old, {0x401000: (0x402000, "exact", 1.0)})
            self.assertTrue(out.read_text().startswith("ra2_addr,yr_addr,size_ra2,size_yr,kind,similarity"))

    def test_compare_old_counts_agreement_and_conflicts(self):
        yf = {1: self.fn(1, b"aaaaaaaaaa"), 2: self.fn(2, b"bbbbbbbbbb"), 3: self.fn(3, b"cccccccccc")}
        rf = {11: self.fn(11, b"aaaaaaaaaa"), 12: self.fn(12, b"bbbbbbbbbb"), 13: self.fn(13, b"cccccccccc")}
        p = TP.Pairing(yf, rf, {}, {})
        p.by_hash()
        old = {1: (11, "exact", 1.0), 2: (13, "exact", 1.0), 9: (19, "near", 0.95)}
        s, rows = TP.compare_old(p, old)
        self.assertEqual((s["agree"], s["conflict"], s["only_new"], s["only_old"]), (1, 1, 1, 1))
        self.assertEqual(rows[0]["yr"], 2)


class ExtentRecallTests(unittest.TestCase):
    def build(self):
        code = bytearray(b"\xcc" * 0x200)
        # A @0x000 (listed): call C(0x100); cmp/ja/jmp [eax*4+tbl] 2 cases; ret; case labels
        a = TEXT
        body = b"\x55\x8b\xec" + rel32(0xE8, a + 3, TEXT + 0x100) + b"\x83\xf8\x01\x77\x0a"
        body += b"\xff\x24\x85" + struct.pack("<I", TEXT + 0x1C0)
        c0 = a + len(body)
        body += b"\x90\x5d\xc3" + b"\x90\x5d\xc3"
        code[0:len(body)] = body
        code[0x1C0:0x1C8] = struct.pack("<II", c0, c0 + 3)
        # B @0x40 (listed): ends in ret; has an interior catch-like label at 0x4A
        code[0x40:0x4C] = b"\x55\x8b\xec\x33\xc0\x5d\xc3" + b"\x33\xc0\x5d\xc3\xcc"[:5]
        # C @0x100 (unlisted, called from A): real missed
        code[0x100:0x106] = b"\x8b\x44\x24\x04\x5e\xc3"
        # D @0x120 (unlisted): only a jmp thunk
        code[0x120:0x125] = rel32(0xE9, TEXT + 0x120, TEXT + 0x40)
        # E @0x140 (unlisted): referenced only by a data pointer, after padding, not called: still real, medium
        code[0x140:0x146] = b"\x56\x8b\x74\x24\x08\xc3"
        return bytes(code), c0

    def census(self):
        return [["0x401000", "0x50", "0xB", "cc", "engine", []], ["0x401040", "0x10", "0x0", "cc", "engine", []]]

    def test_classes(self):
        code, c0 = self.build()
        data = bytearray(0x40)
        data[0:4] = struct.pack("<I", TEXT + 0x140)         # data pointer to E
        data[4:8] = struct.pack("<I", TEXT + 0x43)          # data pointer into B (instruction boundary: 0x43 = xor eax,eax)
        data[8:12] = struct.pack("<I", TEXT + 0x1C2)        # data pointer into the jump table -> data
        data[12:16] = struct.pack("<I", 0x401002)           # points inside an instruction of A -> data
        img = image(code, data=bytes(data))
        rep = ER.run(img, self.census())
        by = {e["addr"]: e for e in rep["candidates"]}
        self.assertEqual(by["0x401100"]["cls"], "real_missed")
        self.assertEqual(by["0x401100"]["confidence"], "high")        # called from a listed function, padded, plausible start
        self.assertEqual(by["0x401120"]["cls"], "padding_thunk")
        self.assertEqual(by["0x401140"]["cls"], "real_missed")
        self.assertEqual(by["0x401043"]["cls"], "alt_entry")
        self.assertEqual(by["0x401043"]["inside"], "0x401040")
        self.assertEqual(by["0x4011C2"]["cls"], "data")
        self.assertEqual(by["0x401002"]["cls"], "data")
        self.assertNotIn("0x401000", by)                              # census starts are not candidates
        self.assertEqual(rep["summary"]["classes"]["real_missed"], 2)
        props = {p["addr"] for p in rep["proposed_additions"]}
        self.assertIn("0x401100", props)
        self.assertIn("0x401140", props)

    def test_census_is_not_modified_and_report_is_json(self):
        code, _ = self.build()
        img = image(code)
        cen = self.census()
        before = json.dumps(cen)
        rep = ER.run(img, cen)
        self.assertEqual(json.dumps(cen), before)
        json.dumps(ER.slim(rep))


if __name__ == "__main__":
    unittest.main()
