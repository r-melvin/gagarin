#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original synthetic objects and image; no retail bytes.
"""datasource: which project data definitions may replace retail fill, and how they are placed."""

import struct
import tempfile
import unittest
from pathlib import Path

import coffgen
import datasource
import hybrid
import pindata
from test_hybrid import DATA, RDATA, FakeRetail
from verify_vtable import parse_coff

COMDAT = coffgen.SCN_LNK_COMDAT
RDATA_FLAGS = 0x40300040


def build(sections, symbols):
    """sections: [(name, flags, data, [(offset, symbol index, type)])]; symbols: [(name, value, section, class,
    aux bytes or None)] -> object bytes (symbol indices count aux records)."""
    offset = 20 + 40 * len(sections)
    headers, body = b"", b""
    for name, flags, data, relocs in sections:
        size = data if isinstance(data, int) else len(data)   # an int is an uninitialised section of that size
        data = b"" if isinstance(data, int) else data
        rel = b"".join(struct.pack("<IIH", *r) for r in relocs)
        headers += name.encode().ljust(8, b"\0") + struct.pack(
            "<IIIIIIHHI", 0, 0, size, offset if data else 0, offset + len(data) if rel else 0, 0, len(relocs), 0, flags)
        body += data + rel
        offset += len(data) + len(rel)
    syms, count, strtab = b"", 0, bytearray(4)
    for name, value, section, scl, aux in symbols:
        raw = name.encode()
        if len(raw) > 8:
            field = struct.pack("<II", 0, len(strtab))
            strtab += raw + b"\0"
        else:
            field = raw.ljust(8, b"\0")
        syms += field + struct.pack("<IhHBB", value, section, 0, scl, 1 if aux else 0)
        count += 1
        if aux:
            syms += aux.ljust(18, b"\0")
            count += 1
    struct.pack_into("<I", strtab, 0, len(strtab))
    return struct.pack("<HHIIIHH", coffgen.I386, len(sections), 0, offset, count, 0, 0) + headers + body + syms + bytes(strtab)


class Fixture(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.dir = Path(self.tmp.name)
        self.retail = FakeRetail()
        self.regions = datasource.Regions(self.retail)

    def tearDown(self):
        self.tmp.cleanup()

    def run_candidates(self, obj, addresses, names=None, aliases=None):
        path = self.dir / "a.obj"
        path.write_bytes(obj)

        def address_of(idx, symbol):
            return addresses.get(symbol["name"])

        return datasource.candidates(path, parse_coff(path), obj, address_of,
                                     datasource.Resolver(names or {}, aliases=aliases), self.retail, self.regions)


class CandidateTests(Fixture):
    def literal(self, at, size=4):
        return bytes(self.retail.fill(at, size))

    def test_a_literal_equal_to_retail_is_accepted_and_one_that_differs_is_rejected(self):
        want = self.literal(RDATA + 0x140, 4)
        good = build([(".rdata", COMDAT | RDATA_FLAGS, want, [])], [("??_C@_a", 0, 1, 2, None)])
        accepted, rejected = self.run_candidates(good, {"??_C@_a": RDATA + 0x140})
        self.assertEqual([(c["kind"], c["va"], c["size"]) for c in accepted], [("string", RDATA + 0x140, 4)])
        self.assertEqual(rejected, [])
        bad = build([(".rdata", COMDAT | RDATA_FLAGS, b"\xff" * 4, [])], [("??_C@_a", 0, 1, 2, None)])
        accepted, rejected = self.run_candidates(bad, {"??_C@_a": RDATA + 0x140})
        self.assertEqual(accepted, [])
        self.assertIn("contents differ", rejected[0]["why"])

    def test_no_address_is_reported(self):
        obj = build([(".rdata", COMDAT | RDATA_FLAGS, bytes(4), [])], [("__real@4", 0, 1, 2, None)])
        accepted, rejected = self.run_candidates(obj, {})
        self.assertEqual((accepted, rejected[0]["why"], rejected[0]["kind"]), ([], "no retail address", "float"))

    def test_plain_section_symbols_end_where_the_next_begins(self):
        body = self.literal(DATA + 0x100, 8)
        obj = build([(".data", 0xC0300040, body, [])], [("_a", 0, 1, 2, None), ("_b", 4, 1, 2, None)])
        accepted, rejected = self.run_candidates(obj, {"_a": DATA + 0x100, "_b": DATA + 0x104})
        self.assertEqual(sorted((c["names"][0], c["size"]) for c in accepted), [("_a", 4), ("_b", 4)])

    def test_a_name_defined_at_several_addresses_resolves_to_the_instance_at_the_slots_address(self):
        # scalar deleting destructor ??_G: one name, instances at 0x401230 (the name) and 0x401300 (?dup_...)
        self.retail.patch(RDATA + 0x140, struct.pack("<I", 0x401300))
        obj = build([(".rdata", COMDAT | RDATA_FLAGS, bytes(4), [(0, 1, coffgen.REL_DIR32)])],
                    [("??_7A@@6B@", 0, 1, 2, None), ("??_GA@@UAEPAXI@Z", 0, 0, 2, None)])
        names = {"??_GA@@UAEPAXI@Z": 0x401230}
        acc, rej = self.run_candidates(obj, {"??_7A@@6B@": RDATA + 0x140}, names)
        self.assertIn("is at 0x401230", rej[0]["why"])
        aliases = {("??_GA@@UAEPAXI@Z", 0x401300): "?dup_00401300@@YAXXZ"}
        acc, rej = self.run_candidates(obj, {"??_7A@@6B@": RDATA + 0x140}, names, aliases)
        self.assertEqual([c["relocs"] for c in acc], [[(0, "?dup_00401300@@YAXXZ", coffgen.REL_DIR32)]])
        # a slot holding the address the name itself links to keeps the name, bound to that
        # retail address like every code target of an adopted vtable
        self.retail.patch(RDATA + 0x140, struct.pack("<I", 0x401230))
        acc, rej = self.run_candidates(obj, {"??_7A@@6B@": RDATA + 0x140}, names, aliases)
        self.assertEqual([c["relocs"] for c in acc], [[(0, "??_GA@@UAEPAXI@Z@pin00401230", coffgen.REL_DIR32)]])

    def test_relocation_targets_must_be_known_and_agree_with_retail(self):
        # a one-slot vtable: retail's dword is the address of function _f
        self.retail.patch(RDATA + 0x140, struct.pack("<I", 0x401230))
        obj = build([(".rdata", COMDAT | RDATA_FLAGS, bytes(4), [(0, 1, coffgen.REL_DIR32)])],
                    [("??_7A@@6B@", 0, 1, 2, None), ("?f@@YAXXZ", 0, 0, 2, None)])
        acc, rej = self.run_candidates(obj, {"??_7A@@6B@": RDATA + 0x140}, {"?f@@YAXXZ": 0x401230})
        self.assertEqual([c["relocs"] for c in acc], [[(0, "?f@@YAXXZ@pin00401230", coffgen.REL_DIR32)]])   # code targets are bound to their address too
        acc, rej = self.run_candidates(obj, {"??_7A@@6B@": RDATA + 0x140}, {"?f@@YAXXZ": 0x401240})
        self.assertIn("is at 0x401240", rej[0]["why"])
        acc, rej = self.run_candidates(obj, {"??_7A@@6B@": RDATA + 0x140}, {})
        self.assertIn("has no known address", rej[0]["why"])

    def test_a_data_target_becomes_a_pin(self):
        self.retail.patch(RDATA + 0x140, struct.pack("<I", RDATA + 0x200))
        obj = build([(".rdata", COMDAT | RDATA_FLAGS, struct.pack("<I", 0), [(0, 1, coffgen.REL_DIR32)])],
                    [("??_7A@@6B@", 0, 1, 2, None), ("_other", 0, 0, 2, None)])
        acc, _ = self.run_candidates(obj, {"??_7A@@6B@": RDATA + 0x140}, {"_other": RDATA + 0x200})
        self.assertEqual(acc[0]["relocs"][0][1], pindata.pin_name("_other", RDATA + 0x200))

    def test_a_weak_external_is_referenced_through_its_default(self):
        self.retail.patch(RDATA + 0x140, struct.pack("<I", 0x401230))
        weak_aux = struct.pack("<II", 3, 3)   # default: symbol 3
        obj = build([(".rdata", COMDAT | RDATA_FLAGS, bytes(4), [(0, 1, coffgen.REL_DIR32)])],
                    [("??_7A@@6B@", 0, 1, 2, None), ("??_EA@@UAEPAXI@Z", 0, 0, coffgen.CLASS_WEAK_EXTERNAL, weak_aux),
                     ("??_GA@@UAEPAXI@Z", 0, 0, 2, None)])
        acc, _ = self.run_candidates(obj, {"??_7A@@6B@": RDATA + 0x140}, {"??_GA@@UAEPAXI@Z": 0x401230})
        self.assertEqual(acc[0]["relocs"][0][1], "??_GA@@UAEPAXI@Z@pin00401230")

    def test_bss_definitions_are_accounted_in_the_bss_tail(self):
        bss_va = DATA + 0x1000 + 0x40   # inside the bss tail of the fake image
        obj = build([(".bss", 0xC0300080, 8, [])], [("?v@@3HA", 0, 1, 2, None)])
        acc, rej = self.run_candidates(obj, {"?v@@3HA": bss_va})
        self.assertEqual([(c["kind"], c["va"], c["size"], c["data"]) for c in acc], [("bss", bss_va, 8, None)])
        acc, rej = self.run_candidates(obj, {"?v@@3HA": RDATA + 0x1C0})   # initialised address: a zero-filled piece is fine only if retail is zero
        self.assertIn("contents differ", rej[0]["why"])


class InitialiserTests(Fixture):
    def object(self, thunk):
        text = b"\xe9\0\0\0\0" + b"\x90" * 11
        return build([(".CRT$XCU", 0xC0300040, bytes(4), [(0, 0, coffgen.REL_DIR32)]),
                      (".text", 0x60500020, text, [(1, 1, coffgen.REL_REL32)])],
                     [("_$E2" if thunk else "?static_00401230@@YAXXZ", 0, 2 if thunk else 0, 3 if thunk else 2, None),
                      ("?static_00401230@@YAXXZ", 0, 0, 2, None)])

    def run_init(self, obj, names):
        path = self.dir / "a.obj"
        path.write_bytes(obj)
        self.retail.patch(DATA, bytes(4) + struct.pack("<I", 0x401230) + bytes(8))
        slots = datasource.initialiser_slots(self.retail)
        return slots, datasource.initialisers(path, parse_coff(path), obj, datasource.Resolver(names), slots)

    def test_the_table_is_the_run_after_the_opening_zero(self):
        slots, _ = self.run_init(self.object(False), {})
        self.assertEqual(slots, {0x401230: [DATA + 4]})

    def test_an_entry_is_placed_in_the_slot_that_holds_the_initialiser(self):
        _, (acc, rej, nsec, consecutive, thunks) = self.run_init(self.object(False), {"?static_00401230@@YAXXZ": 0x401230})
        self.assertEqual([(c["va"], c["relocs"]) for c in acc], [(DATA + 4, [(0, "?static_00401230@@YAXXZ", coffgen.REL_DIR32)])])
        self.assertEqual((rej, nsec, consecutive, thunks), ([], 1, 1, 0))

    def test_a_jump_thunk_entry_names_the_body_it_jumps_to(self):
        _, (acc, rej, nsec, consecutive, thunks) = self.run_init(self.object(True), {"?static_00401230@@YAXXZ": 0x401230})
        self.assertEqual((acc[0]["names"], acc[0]["thunk"], thunks), (["?static_00401230@@YAXXZ"], True, 1))

    def test_an_initialiser_with_no_address_or_no_slot_is_rejected(self):
        _, (acc, rej, *_) = self.run_init(self.object(False), {})
        self.assertIn("no known address", rej[0]["why"])
        _, (acc, rej, *_) = self.run_init(self.object(False), {"?static_00401230@@YAXXZ": 0x401240})
        self.assertIn("absent from retail's table", rej[0]["why"])


class AssignTests(unittest.TestCase):
    def piece(self, va, size, kind="global", name="n", data=None, relocs=()):
        return {"names": [name], "kind": kind, "va": va, "size": size, "data": data if data is not None else bytes(size),
                "relocs": list(relocs), "object": "o.obj"}

    def test_identical_definitions_merge_and_a_contained_alias_merges(self):
        pieces, rejected = datasource.assign([self.piece(0x100, 4, name="a"), self.piece(0x100, 4, name="b"),
                                              self.piece(0x100, 2, name="c")], [])
        self.assertEqual([(p["va"], p["size"], p["names"]) for p in pieces], [(0x100, 4, ["a", "b", "c"])])
        self.assertEqual(rejected, [])

    def test_a_partial_overlap_is_rejected(self):
        pieces, rejected = datasource.assign([self.piece(0x100, 4), self.piece(0x102, 4, name="m")], [])
        self.assertEqual(len(pieces), 1)
        self.assertIn("overlaps", rejected[0]["why"])

    def test_uninitialised_definitions_end_where_the_next_begins(self):
        pieces, _ = datasource.assign([self.piece(0x100, 16, "bss", "a", data=None), self.piece(0x10C, 8, "bss", "b", data=None)], [])
        self.assertEqual([(p["va"], p["size"]) for p in pieces], [(0x100, 12), (0x10C, 8)])


class DataObjectTests(unittest.TestCase):
    def test_pieces_replace_retail_fill_in_address_order_with_their_relocations(self):
        retail = FakeRetail()
        piece = {"va": RDATA + 0x40, "size": 8, "data": bytes(8), "relocs": [(4, "?f@@YAXXZ", coffgen.REL_DIR32)],
                 "names": ["x"], "kind": "vtable"}
        data_piece = {"va": DATA + 0x20, "size": 4, "data": b"\1\2\3\4", "relocs": [], "names": ["y"], "kind": "global"}
        bss_piece = {"va": DATA + 0x1100, "size": 4, "data": None, "relocs": [], "names": ["z"], "kind": "bss"}
        plain, layout = hybrid.data_object(retail)
        obj, layout2 = hybrid.data_object(retail, [data_piece, piece, bss_piece])
        self.assertEqual(layout, layout2)
        nsec = struct.unpack_from("<H", obj, 2)[0]
        self.assertEqual(nsec, struct.unpack_from("<H", plain, 2)[0] + 2 + 2)   # two pieces split their regions' fill
        secs = []
        for i in range(nsec):
            off = 20 + 40 * i
            name = obj[off:off + 8].rstrip(b"\0").decode()
            size, ptr, relptr, _, nrel, _, flags = struct.unpack_from("<IIIIHHI", obj, off + 16)
            secs.append((name, size, ptr, nrel, flags))
        names = [s[0] for s in secs]
        self.assertEqual(names.count(".rdata"), 3)   # fill, piece, fill
        rd = [s for s in secs if s[0] == ".rdata"]
        self.assertEqual([s[3] for s in rd], [0, 1, 0])
        self.assertEqual(rd[1][1], 8)
        self.assertEqual(rd[0][4] & 0x00F00000, 0x00300000)   # the region keeps its alignment
        self.assertEqual(rd[1][4] & 0x00F00000, 0x00100000)   # pieces are byte-aligned
        # total bytes per region unchanged
        for region in (".rdata", ".data"):
            a = sum(s[1] for s in secs if s[0] == region)
            b = 0
            nsec0 = struct.unpack_from("<H", plain, 2)[0]
            for i in range(nsec0):
                off = 20 + 40 * i
                if plain[off:off + 8].rstrip(b"\0").decode() == region:
                    b += struct.unpack_from("<I", plain, off + 16)[0]
            self.assertEqual(a, b)

    def test_a_piece_outside_the_regions_is_refused(self):
        with self.assertRaises(Exception):
            hybrid.data_object(FakeRetail(), [{"va": 0x900000, "size": 4, "data": bytes(4), "relocs": []}])


if __name__ == "__main__":
    unittest.main()
