#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original synthetic objects and image; no retail bytes. The LINK probe runs only where the toolchain is installed.
"""hybrid: the retail-content data object, droppable sections, slot checks and the tail pins."""

import os
from pathlib import Path
import shutil
import struct
import subprocess
import tempfile
import unittest

import coffgen
import hybrid
import link_diag
import pindata
from test_pindata import build_object, sym
from verify_vtable import parse_coff

RDATA, DATA, RSRC = 0x7E1000, 0x812000, 0xB7A000


class FakeRetail(hybrid.Retail):
    """A synthetic stand-in for the pinned image: .text, .rdata (IAT, descriptors, ILT, names),
    .data with a bss tail and .rsrc, every byte a function of its address."""

    def __init__(self):
        self.sections = []
        self.pe = bytearray(0x1000)
        struct.pack_into("<I", self.pe, 0x3C, 0x80)
        for name, va, vsize, rawsize in ((".text", 0x401000, 0x300, 0x1000), (".rdata", RDATA, 0x230, 0x1000),
                                         (".data", DATA, 0x2100, 0x1000), (".rsrc", RSRC, 0x40, 0x1000)):
            rawptr = len(self.pe)
            self.pe += bytes((va + i) & 0xFF for i in range(rawsize))
            self.sections.append((name, va, vsize, rawptr, rawsize))
        self.by_name = {n: (va, vs, rp, rs) for n, va, vs, rp, rs in self.sections}
        # .rdata: IAT 0x18 bytes at the start (2 imports + terminator, 2 dlls: 4 dwords + 2)
        iat, descriptors, ilt, names = RDATA, RDATA + 0x80, RDATA + 0xBC, RDATA + 0x100
        self.patch(RDATA, bytes(0x80))
        for i, va in enumerate((iat, iat + 12)):
            self.patch(descriptors + 20 * i, struct.pack("<IIIII", ilt + 12 * i - 0x400000, 0, 0,
                                                         names + 0x20 * i - 0x400000, va - 0x400000))
        self.patch(descriptors + 40, bytes(20))
        for i in range(2):   # each dll: two imports and a terminator
            self.patch(ilt + 12 * i, struct.pack("<III", names + 0x40 - 0x400000, names + 0x50 - 0x400000, 0))
        struct.pack_into("<IIII", self.pe, 0x80 + 0x78 + 8, descriptors - 0x400000, 60, 0, 0)
        struct.pack_into("<II", self.pe, 0x80 + 0x78 + 8 * 12, iat - 0x400000, 0x18)

    def patch(self, va, data):
        for _, start, _, rawptr, _ in self.sections:
            if start <= va < start + 0x1000:
                self.pe[rawptr + va - start:rawptr + va - start + len(data)] = data
                return
        raise AssertionError(va)


class DataObjectTests(unittest.TestCase):
    def test_pieces_tile_rdata_and_data_at_retail_addresses(self):
        retail = FakeRetail()
        obj, layout = hybrid.data_object(retail)
        names = [n for n, _, _ in layout]
        self.assertEqual(names, [".idata$5", ".rdata", ".idata$2", ".idata$3", ".idata$4", ".idata$6", ".data", ".bss",
                                 ".rsrc$01"])
        rdata = [(n, va, size) for n, va, size in layout if n not in (".data", ".bss", ".rsrc$01")]
        # contiguous from the IAT to the end of .rdata, except the zero gap LINK puts before plain .rdata
        self.assertEqual(rdata[0][1], RDATA)
        for (_, va, size), (_, nxt, _) in zip(rdata, rdata[1:]):
            self.assertIn(nxt - (va + size), (0, 8))
        self.assertEqual(rdata[-1][1] + rdata[-1][2], RDATA + 0x230)
        self.assertEqual(dict((n, size) for n, _, size in layout)[".data"] + dict((n, size) for n, _, size in layout)[".bss"],
                         0x2100)
        # section headers: names, sizes, bss without file data, the import library's attributes
        nsec = struct.unpack_from("<H", obj, 2)[0]
        self.assertEqual(nsec, len(layout))
        headers = {}
        for i in range(nsec):
            off = 20 + 40 * i
            name = obj[off:off + 8].rstrip(b"\0").decode()
            headers[name] = struct.unpack_from("<IIIIIIHHI", obj, off + 8)
        self.assertEqual((headers[".bss"][2], headers[".bss"][3]), (0x2100 - 0x1000, 0))   # size, no file data
        self.assertEqual(headers[".idata$2"][8], 0xC0300040)
        self.assertEqual(headers[".idata$6"][8], 0xC0200040)
        self.assertEqual(headers[".data"][8], 0xC0300040)
        # contents are the image's bytes
        sec = headers[".rsrc$01"]
        self.assertEqual(obj[sec[3]:sec[3] + 0x40], retail.fill(RSRC, 0x40))

    def test_nonzero_gap_after_the_iat_is_refused(self):
        retail = FakeRetail()
        retail.patch(RDATA + 0x18, b"\x01")
        with self.assertRaises(Exception):
            hybrid.data_object(retail)

    def test_fill_zero_pads_past_raw_data(self):
        retail = FakeRetail()
        self.assertEqual(retail.fill(DATA + 0xFFE, 4), bytes((DATA + 0xFFE + i) & 0xFF for i in range(2)) + bytes(2))


class SlotTests(unittest.TestCase):
    """function_matches and pad_trim compare outside relocation sites only."""

    def parsed(self, code, relocs=(), extra=()):
        obj = build_object([("_f", code, list(relocs))], list(extra))
        with tempfile.TemporaryDirectory() as tmp:
            path = Path(tmp) / "a.obj"
            path.write_bytes(obj)
            return parse_coff(path)

    def retail_with(self, code):
        retail = FakeRetail()
        retail.patch(0x401000, code)
        return retail

    def test_relocation_sites_are_masked(self):
        parsed = self.parsed(b"\xa1\0\0\0\0\xc3", [(1, 1, pindata.DIR32)], [sym("_g", 0, 0, 2)])
        retail = self.retail_with(b"\xa1\x00\x10\x7e\x00\xc3")
        self.assertTrue(hybrid.function_matches(parsed, "_f", 0x401000, 6, retail))

    def test_a_different_body_is_false_and_a_missing_symbol_none(self):
        parsed = self.parsed(b"\x90\xc3")
        retail = self.retail_with(b"\x91\xc3")
        self.assertFalse(hybrid.function_matches(parsed, "_f", 0x401000, 2, retail))
        self.assertIsNone(hybrid.function_matches(parsed, "_nope", 0x401000, 2, retail))
        self.assertIsNone(hybrid.function_matches(None, "_f", 0x401000, 2, retail))

    def test_a_body_longer_than_the_object_is_false(self):
        self.assertFalse(hybrid.function_matches(self.parsed(b"\xc3"), "_f", 0x401000, 4, self.retail_with(b"\xc3")))

    def test_padding_is_cut_only_when_retail_has_other_bytes_after_the_function(self):
        code = b"\xc3" + b"\x90" * 15
        parsed = self.parsed(code)
        self.assertEqual(hybrid.pad_trim(parsed, "_f", 0x401000, 1, self.retail_with(b"\xc3" + b"\x9d\x41" * 7 + b"\0")),
                         (1, 1))
        self.assertIsNone(hybrid.pad_trim(parsed, "_f", 0x401000, 1, self.retail_with(code)))

    def test_a_jump_table_after_the_function_is_not_padding(self):
        code = b"\xc3\x90\x90\x90" + b"\0\0\0\0" * 2
        parsed = self.parsed(code, [(4, 1, pindata.DIR32), (8, 1, pindata.DIR32)], [sym("_t", 0, 0, 2)])
        retail = self.retail_with(b"\xc3\x90\x90\x90" + struct.pack("<II", 0x401001, 0x401002))
        self.assertIsNone(hybrid.pad_trim(parsed, "_f", 0x401000, 1, retail))


class CoffTests(unittest.TestCase):
    def test_bytes_fill_is_exact(self):
        w = coffgen.ObjectWriter()
        w.add_code_comdat(["_a"], 3, 1, fill=b"\x01\x02\x03")
        obj = w.build()
        raw = struct.unpack_from("<I", obj, 20 + 20)[0]
        self.assertEqual(obj[raw:raw + 3], b"\x01\x02\x03")
        with self.assertRaises(ValueError):
            coffgen.ObjectWriter().add_code_comdat(["_a"], 4, 1, fill=b"\x01")

    def test_truncate_section_updates_header_and_aux(self):
        w = coffgen.ObjectWriter()
        w.add_code_comdat(["_a"], 16, 16)
        obj = coffgen.truncate_section(w.build(), 1, 5)
        self.assertEqual(struct.unpack_from("<I", obj, 20 + 16)[0], 5)
        symptr = struct.unpack_from("<I", obj, 8)[0]
        self.assertEqual(struct.unpack_from("<I", obj, symptr + 18)[0], 5)
        with self.assertRaises(ValueError):
            coffgen.truncate_section(obj, 1, 6)

    def test_site_retargeting_beats_the_symbol_mapping(self):
        obj = build_object([("_f", b"\xa1\0\0\0\0\xa1\0\0\0\0\xc3", [(1, 1, pindata.DIR32), (6, 1, pindata.DIR32)])],
                           [sym("_g", 0, 0, coffgen.CLASS_EXTERNAL)])
        out, count, used = coffgen.retarget_relocations(obj, {}, None, {(1, 6): ("_second", "_second_rel")})
        self.assertEqual((count, used), (1, {"_second"}))
        names = {i: n for i, n, *_ in coffgen.read_symbols(out)}
        first, second = (struct.unpack_from("<I", out, 20 + 40 + 11 + 10 * k + 4)[0] for k in (0, 1))
        self.assertEqual((names[first], names[second]), ("_g", "_second"))

    def test_remove_sections_flags_only_noncomdat_sections(self):
        w = coffgen.ObjectWriter()
        w.add_code_comdat(["_a"], 4, 4)
        w.sections.append((".data", 0xC0300040, b"\0" * 4, ["_d"], False))
        obj, removed = coffgen.remove_sections(w.build(), lambda name, flags, idx: False)
        self.assertEqual(removed, [".data"])


class HardenTests(unittest.TestCase):
    def build(self):
        w = coffgen.ObjectWriter()
        w.add_code_comdat(["_entry"], 4, 4)
        w.sections.append((".data", 0xC0300040, b"\1" * 8, ["_junk"], False))
        w.sections.append((".text$x", 0x60500020, b"\xc3" * 4, [], False))
        return w.build()

    def test_unordered_sections_become_droppable_comdats(self):
        obj, dropped = hybrid.harden(self.build(), {"_entry"}, "t")
        self.assertEqual(dropped, [2, 3])
        for index in (2, 3):
            self.assertTrue(struct.unpack_from("<I", obj, 20 + 40 * (index - 1) + 36)[0] & coffgen.SCN_LNK_COMDAT)
        self.assertEqual(obj[20 + 80:20 + 88].rstrip(b"\0"), b".text")   # an emptied .text$x group pads .text
        keys = {n for _, n, _, sec, scl, _ in coffgen.read_symbols(obj) if scl == 2 and sec in (2, 3)}
        self.assertTrue(keys >= {"_junk"})
        self.assertEqual(len(keys), 2)

    def test_the_ordered_section_is_left_alone(self):
        obj, _ = hybrid.harden(self.build(), {"_entry"}, "t")
        self.assertEqual(obj[20:20 + 40], self.build()[20:20 + 40])

    def test_a_label_does_not_become_the_comdat_key(self):
        w = coffgen.ObjectWriter()
        w.sections.append((".data", 0xC0300040, b"\1" * 8, [], False))
        obj = bytearray(w.build())
        symptr, nsyms = struct.unpack_from("<II", obj, 8)
        strtab = obj[symptr + 18 * nsyms:]
        label = sym("$L1", 0, 1, 6)
        obj = bytes(obj[:symptr + 18 * nsyms]) + label + bytes(strtab)
        obj = obj[:12] + struct.pack("<I", nsyms + 1) + obj[16:]
        out, dropped = hybrid.harden(obj, set(), "t")
        self.assertEqual(dropped, [1])
        self.assertEqual([scl for _, n, _, sec, scl, _ in coffgen.read_symbols(out) if sec == 1 and n != ".data"][0], 2)


class TailPinTests(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.dir = Path(self.tmp.name)

    def tearDown(self):
        self.tmp.cleanup()

    def image(self, code):
        pe = bytearray(0x400) + code
        return bytes(pe), [(".text", 0x401000, len(code), 0x400, len(code))]

    def test_every_cross_section_target_becomes_a_pin_and_calls_are_reported(self):
        # _f: mov eax,[_g] ; call _h ; ret.  _g is data, _h code retail keeps outside any listed section.
        code = b"\xa1\0\0\0\0\xe8\0\0\0\0\xc3"
        obj = build_object([("_f", code, [(1, 1, pindata.DIR32), (6, 2, pindata.REL32)])],
                           [sym("_g", 0, 0, 2), sym("_h", 0, 0, 2)])
        path = self.dir / "t.obj"
        path.write_bytes(obj)
        retail = b"\xa1" + struct.pack("<I", 0x7E1010) + b"\xe8" + struct.pack("<i", 0x7C0000 - 0x40100A) + b"\xc3"
        pe, secs = self.image(retail)
        pins, calls, conflicts, sites = pindata.derive_tail([(path, [(1, 0x401000, len(code))])], pe, secs)
        self.assertEqual(sorted(v for v in pins[path].values()), [("_g", 0x7E1010), ("_h", 0x7C0000)])
        self.assertEqual(calls, {"_h": 0x7C0000})
        self.assertEqual((conflicts, sites), ([], {}))

    def test_a_symbol_that_disagrees_with_itself_is_pinned_site_by_site(self):
        code = b"\xa1\0\0\0\0\xa1\0\0\0\0\xc3"
        obj = build_object([("_f", code, [(1, 1, pindata.DIR32), (6, 1, pindata.DIR32)])], [sym("_g", 0, 0, 2)])
        path = self.dir / "t.obj"
        path.write_bytes(obj)
        retail = b"\xa1" + struct.pack("<I", 0x7E1000) + b"\xa1" + struct.pack("<I", 0x7E1004) + b"\xc3"
        pe, secs = self.image(retail)
        pins, calls, conflicts, sites = pindata.derive_tail([(path, [(1, 0x401000, len(code))])], pe, secs)
        self.assertEqual(pins, {})
        self.assertEqual(conflicts[0]["symbol"], "_g")
        self.assertEqual(sites[path], {(1, 1): ("_g", 0x7E1000), (1, 6): ("_g", 0x7E1004)})
        out, count, used = pindata.retarget_object(path, obj, {"object": pins, "site": sites, "global": {}})
        self.assertEqual((count, set(used)), (2, {"_g@pin007E1000", "_g@pin007E1004"}))

    def test_targets_outside_the_image_are_not_pinned(self):
        code = b"\xa1\0\0\0\0\xc3"
        obj = build_object([("_f", code, [(1, 1, pindata.DIR32)])], [sym("_g", 0, 0, 2)])
        path = self.dir / "t.obj"
        path.write_bytes(obj)
        pe, secs = self.image(b"\xa1" + struct.pack("<I", 0x1000) + b"\xc3")
        self.assertEqual(pindata.derive_tail([(path, [(1, 0x401000, len(code))])], pe, secs)[0], {})


class HybridPlanTests(unittest.TestCase):
    """stubgen.plan with a retail stand-in: stubs and fillers carry its bytes, a matched body that
    differs gives its slot back, and the output has no anchor table."""

    def plan(self, retail):
        import json
        import stubgen
        tmp = tempfile.TemporaryDirectory()
        self.addCleanup(tmp.cleanup)
        root = Path(tmp.name)
        (root / "obj/match").mkdir(parents=True)
        w = coffgen.ObjectWriter()
        w.add_code_comdat(["?M@@YAXXZ"], 0x10)
        w.add_code_comdat(["?S@@YAXXZ"], 0x10)
        (root / "obj/match/a.obj").write_bytes(w.build())
        (root / "obj/objects.json").write_text(json.dumps(
            {"success": True, "objects": [{"object": "match/a.obj", "source": "match/a.cpp"}]}))
        manifest = [{"tu": "match/a.cpp", "addr": "0x401000", "sym": "?M@@YAXXZ", "len": "0x10", "status": "matched"},
                    {"tu": "match/a.cpp", "addr": "0x401020", "sym": "?S@@YAXXZ", "len": "0x10", "status": "matched"}]
        extents = [["0x401000", "0x10", "0x0", "none", "engine", []], ["0x401010", "0x10", "0x0", "none", "engine", []],
                   ["0x401020", "0x10", "0x0", "none", "engine", []]]
        result = stubgen.plan(root / "obj", set(), root / "out", manifest=manifest, extents=extents,
                              symbol_bindings={}, retail=retail)
        self.out = root / "out"
        return result

    def section_bytes(self, symbol):
        obj = (self.out / "stubs.obj").read_bytes()
        for _, name, value, section, scl, _ in coffgen.read_symbols(obj):
            if name == symbol and section > 0:
                size, ptr = struct.unpack_from("<II", obj, 20 + 40 * (section - 1) + 16)
                return obj[ptr:ptr + size]
        raise AssertionError(symbol)

    def test_stub_bytes_come_from_the_image_and_a_differing_body_is_demoted(self):
        retail = FakeRetail()
        retail.patch(0x401000, b"\xcc" * 0x10)   # equals the compiled 0xCC body: stays matched
        result = self.plan(retail)
        self.assertEqual(self.section_bytes("?stub_00401010@@YAXXZ"), retail.fill(0x401010, 0x10))
        self.assertEqual([p["kind"] for p in result["placed"]], ["matched", "stub", "stub"])
        self.assertEqual([d["addr"] for d in result["hybrid_rows_demoted_to_retail_bytes"]], ["0x401020"])
        self.assertEqual(self.section_bytes("?stub_00401020@@YAXXZ"), retail.fill(0x401020, 0x10))

    def test_no_anchor_table_and_order_symbols_for_include(self):
        result = self.plan(FakeRetail())
        obj = (self.out / "stubs.obj").read_bytes()
        names = [obj[20 + 40 * i:28 + 40 * i].rstrip(b"\0") for i in range(struct.unpack_from("<H", obj, 2)[0])]
        self.assertNotIn(b".data$zz", names)
        self.assertEqual(result["order_symbols"], ["?stub_00401000@@YAXXZ", "?stub_00401010@@YAXXZ",
                                                   "?stub_00401020@@YAXXZ"])


class ComdatOrderTests(unittest.TestCase):
    """stubgen.plan, hybrid: two objects define the COMDAT ?G; LINK keeps the copy of the first object in
    link order, so only a mismatching definer that precedes the row's object makes the row's copy a dup_."""

    def plan(self, owner_first):
        import json
        import stubgen
        tmp = tempfile.TemporaryDirectory()
        self.addCleanup(tmp.cleanup)
        root = Path(tmp.name)
        (root / "obj/match").mkdir(parents=True)
        retail = FakeRetail()
        gva = 0x401000 if owner_first else 0x401020
        retail.patch(gva, b"\xcc" * 0x10)
        # The object with the lowest claimed address is first in link order. The row owner's ?G is the
        # 0xCC body retail has; the other object's ?G differs.
        owner = coffgen.ObjectWriter()
        owner.add_code_comdat(["?G@@YAXXZ"], 0x10, fill=0xCC)
        other = coffgen.ObjectWriter()
        other.add_code_comdat(["?G@@YAXXZ"], 0x10, fill=0xAA)
        other.add_code_comdat(["?S@@YAXXZ"], 0x10)
        (root / "obj/match/a.obj").write_bytes(owner.build())
        (root / "obj/match/b.obj").write_bytes(other.build())
        (root / "obj/objects.json").write_text(json.dumps({"success": True, "objects": [
            {"object": "match/b.obj", "source": "match/b.cpp"}, {"object": "match/a.obj", "source": "match/a.cpp"}]}))
        sva = 0x401020 if owner_first else 0x401000
        manifest = [{"tu": "match/a.cpp", "addr": f"0x{gva:X}", "sym": "?G@@YAXXZ", "len": "0x10", "status": "matched"},
                    {"tu": "match/b.cpp", "addr": f"0x{sva:X}", "sym": "?S@@YAXXZ", "len": "0x10", "status": "matched"}]
        extents = [["0x401000", "0x10", "0x0", "none", "engine", []], ["0x401010", "0x10", "0x0", "none", "engine", []],
                   ["0x401020", "0x10", "0x0", "none", "engine", []]]
        return stubgen.plan(root / "obj", set(), root / "out", manifest=manifest, extents=extents,
                            symbol_bindings={}, retail=retail), gva

    def placed_symbol(self, result, addr):
        return next(p["symbol"] for p in result["placed"] if p["addr"] == f"0x{addr:X}")

    def test_first_object_in_link_order_keeps_the_real_symbol(self):
        result, gva = self.plan(owner_first=True)
        self.assertEqual(self.placed_symbol(result, gva), "?G@@YAXXZ")

    def test_row_behind_a_mismatching_earlier_definer_is_renamed(self):
        result, gva = self.plan(owner_first=False)
        self.assertEqual(self.placed_symbol(result, gva), f"?dup_{gva:08X}@@YAXXZ")


class CompareImageTests(unittest.TestCase):
    def test_ranges_and_sizes(self):
        import compare_image
        retail = FakeRetail()
        text = retail.fill(0x401000, 0x300)
        ours = bytearray(text)
        ours[0x10] ^= 1
        ours[0x20] ^= 1
        ours[0x200] ^= 1
        self.assertEqual(compare_image.differing_ranges(bytes(ours), text, 16), [(0x10, 0x21), (0x200, 0x201)])
        self.assertEqual(compare_image.differing_ranges(bytes(ours), text, 4), [(0x10, 0x11), (0x20, 0x21), (0x200, 0x201)])
        image = bytearray(0x700)
        struct.pack_into("<I", image, 0x3C, 0x80)
        struct.pack_into("<H", image, 0x86, 1)
        struct.pack_into("<I", image, 0x80 + 24 + 28, 0x400000)
        struct.pack_into("<IIII", image, 0x80 + 0xF8 + 8, 0x300, 0x1000, 0x300, 0x400)
        image[0x80 + 0xF8:0x80 + 0x100] = b".text\0\0\0"
        image[0x400:0x700] = ours
        result = compare_image.compare(bytes(image), retail)
        self.assertEqual(result[".text"]["diff_bytes"], 3)
        self.assertEqual(result[".text"]["ranges"], [(0x401010, 0x11), (0x401200, 1)])
        self.assertEqual(result[".text"]["retail_vsize"], 0x300)


def toolchain_ready():
    vc6, _ = link_diag.toolenv()
    return shutil.which("wine") and (vc6 / "VC98/Bin/LINK.EXE").is_file()


@unittest.skipUnless(toolchain_ready(), "Wine or the VC6 toolchain is not installed")
class LinkProbeTests(unittest.TestCase):
    """LINK 6 keeps the retail-content sections first and drops the hardened ones under /OPT:REF
    with /INCLUDE as the only root; IMAGE_SCN_LNK_REMOVE is not honoured (hence the COMDATs)."""

    def test_hardened_sections_leave_the_image(self):
        retail_like = hybrid.write_object([(".rdata", hybrid.DATA_FLAGS, b"\x11" * 0x20, 0x20),
                                           (".data", hybrid.DATA_FLAGS | coffgen.SCN_MEM_WRITE, b"\x22" * 0x10, 0x10),
                                           (".bss", hybrid.BSS_FLAGS, None, 0x30)])
        w = coffgen.ObjectWriter()
        w.add_code_comdat(["_entry"], 4, 4)
        w.sections.append((".data", 0xC0300040, b"\x33" * 0x18, ["_junk"], False))
        w.sections.append((".rdata", 0x40300040, b"\x44" * 0x18, [], False))
        w.sections.append((".bss", 0xC0300080, b"\0" * 0x18, [], False))
        project, dropped = hybrid.harden(w.build(), {"_entry"}, "probe")
        self.assertEqual(len(dropped), 3)
        vc6, env = link_diag.toolenv()
        with tempfile.TemporaryDirectory(dir=os.environ.get("GAG_SCRATCH")) as tmp:
            root = Path(tmp)
            (root / "a.obj").write_bytes(retail_like)
            (root / "b.obj").write_bytes(project)
            wp = link_diag.wine_path
            subprocess.run(["wine", str(vc6 / "VC98/Bin/LINK.EXE"), "/NOLOGO", "/NODEFAULTLIB", "/ENTRY:entry",
                            "/SUBSYSTEM:CONSOLE", "/FIXED", "/OPT:REF", "/OPT:NOICF", "/INCLUDE:_entry",
                            "/MAP:" + wp(root / "t.map"), "/OUT:" + wp(root / "t.exe"), wp(root / "a.obj"),
                            wp(root / "b.obj")], env=env, check=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
            exe = (root / "t.exe").read_bytes()
        pe = struct.unpack_from("<I", exe, 0x3C)[0]
        sections = {}
        for i in range(struct.unpack_from("<H", exe, pe + 6)[0]):
            off = pe + 0xF8 + 40 * i
            sections[exe[off:off + 8].rstrip(b"\0").decode()] = struct.unpack_from("<II", exe, off + 8)
        self.assertEqual(sections[".rdata"][0], 0x20)
        self.assertEqual(sections[".data"][0], 0x10 + 0x30)


if __name__ == "__main__":
    unittest.main()
