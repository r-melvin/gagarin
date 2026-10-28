#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original synthetic objects and image; no retail bytes.
"""pindata: retail addresses of referenced data from relocation sites, and the relocation retargeting."""

import json
from pathlib import Path
import struct
import tempfile
import unittest

import coffgen
import pindata

COMDAT_FLAGS = 0x60501020 | 0x1000


def sym(name, value, section, scl, naux=0, typ=0):
    raw = name.encode().ljust(8, b"\0")
    return raw + struct.pack("<IhHBB", value, section, typ, scl, naux)


def build_object(functions, extra_symbols=()):
    """functions: [(name, code bytes, [(offset, symbol index, kind)])] each a .text COMDAT.
    Symbol indices: 0.. are the function symbols, then extra_symbols (raw 18-byte records)."""
    n = len(functions)
    headers, body, offset = b"", b"", 20 + 40 * n
    relocs_at = []
    for i, (name, code, relocs) in enumerate(functions):
        rel = b"".join(struct.pack("<IIH", o, s, k) for o, s, k in relocs)
        headers += b".text\0\0\0" + struct.pack("<IIIIIIHHI", 0, 0, len(code), offset, offset + len(code) if rel else 0,
                                                0, len(relocs), 0, COMDAT_FLAGS)
        body += code + rel
        offset += len(code) + len(rel)
    syms = b"".join(sym(f[0], 0, i + 1, coffgen.CLASS_EXTERNAL) for i, f in enumerate(functions))
    syms += b"".join(extra_symbols)
    nsyms = n + len(extra_symbols)
    names = b"\0\0\0\0"
    names = struct.pack("<I", 4)
    return struct.pack("<HHIIIHH", coffgen.I386, n, 0, offset, nsyms, 0, 0) + headers + body + syms + names


def fake_image(dwords):
    """A one-section retail stand-in: .text at 0x401000 holding the given bytes."""
    image = bytearray(0x400) + bytes(dwords)
    return bytes(image), [(".text", 0x401000, len(dwords), 0x400, len(dwords))]


class PinTests(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.dir = Path(self.tmp.name)

    def tearDown(self):
        self.tmp.cleanup()

    def derive(self, objects, rows, image_bytes):
        for name, data in objects.items():
            (self.dir / name).write_bytes(data)
        index = {"objects": [{"source": n[:-4] + ".cpp", "object": n} for n in objects]}
        pe, secs = fake_image(image_bytes)
        return pindata.derive(self.dir, index, rows, pe, secs)

    def test_global_and_addend(self):
        # _g (undefined) read at +0 and +8: retail dwords 0x7E1000 and 0x7E1008 -> base 0x7E1000.
        obj = build_object([("_f", b"\xa1\0\0\0\0\xa1\x08\0\0\0\xc3", [(1, 1, pindata.DIR32), (6, 1, pindata.DIR32)])],
                           [sym("_g", 0, 0, coffgen.CLASS_EXTERNAL)])
        code = b"\xa1" + struct.pack("<I", 0x7E1000) + b"\xa1" + struct.pack("<I", 0x7E1008) + b"\xc3"
        # second reloc's addend is 8 in the object
        data = bytearray(obj)
        data[20 + 40 + 6:20 + 40 + 7] = b"\x08"
        rows = [{"status": "matched", "tu": "a.cpp", "sym": "_f", "addr": "0x401000", "len": hex(len(code))}]
        plan = self.derive({"a.obj": bytes(data)}, rows, code)
        self.assertEqual(plan["global"], {"_g": 0x7E1000})
        self.assertEqual(plan["report"]["rejected_inconsistent"], [])

    def test_inconsistent_global_is_rejected(self):
        obj = build_object([("_f", b"\xa1\0\0\0\0\xa1\0\0\0\0\xc3", [(1, 1, pindata.DIR32), (6, 1, pindata.DIR32)])],
                           [sym("_g", 0, 0, coffgen.CLASS_EXTERNAL)])
        code = b"\xa1" + struct.pack("<I", 0x7E1000) + b"\xa1" + struct.pack("<I", 0x7E1004) + b"\xc3"
        rows = [{"status": "matched", "tu": "a.cpp", "sym": "_f", "addr": "0x401000", "len": hex(len(code))}]
        plan = self.derive({"a.obj": obj}, rows, code)
        self.assertEqual(plan["global"], {})
        self.assertEqual(plan["report"]["rejected_inconsistent"][0]["symbol"], "_g")

    def test_global_in_two_objects_must_agree(self):
        def obj():
            return build_object([("_f", b"\xa1\0\0\0\0\xc3", [(1, 1, pindata.DIR32)])],
                                [sym("_g", 0, 0, coffgen.CLASS_EXTERNAL)])
        code = b"\xa1" + struct.pack("<I", 0x7E1000) + b"\xc3" + b"\xa1" + struct.pack("<I", 0x7E1010) + b"\xc3"
        rows = [{"status": "matched", "tu": "a.cpp", "sym": "_f", "addr": "0x401000", "len": "0x6"},
                {"status": "matched", "tu": "b.cpp", "sym": "_f", "addr": "0x401006", "len": "0x6"}]
        plan = self.derive({"a.obj": obj(), "b.obj": obj()}, rows, code)
        self.assertEqual(plan["global"], {})
        self.assertEqual(plan["report"]["rejected_inconsistent"][0]["scope"], "global")

    def test_text_targets_and_unmatched_rows_are_not_pinned(self):
        obj = build_object([("_f", b"\xe8\0\0\0\0\xc3", [(1, 1, pindata.REL32)])],
                           [sym("_callee", 0, 0, coffgen.CLASS_EXTERNAL)])
        code = b"\xe8" + struct.pack("<i", 0x10) + b"\xc3"
        rows = [{"status": "matched", "tu": "a.cpp", "sym": "_f", "addr": "0x401000", "len": "0x6"},
                {"status": "partial", "tu": "a.cpp", "sym": "_f", "addr": "0x401000", "len": "0x6"}]
        plan = self.derive({"a.obj": obj}, rows, code)
        self.assertEqual((plan["global"], plan["object"]), ({}, {}))
        self.assertEqual(plan["report"]["sites_not_data"], 1)

    def test_comdat_literal_is_pinned_per_object(self):
        # _f references a COMDAT-defined symbol of its own object (section 2 is not built: use f's own
        # second function section as the "definition" so the symbol is a COMDAT external).
        funcs = [("_f", b"\xdd\x05\0\0\0\0\xc3", [(2, 1, pindata.DIR32)]), ("_lit", b"\0" * 8, [])]
        obj = build_object(funcs)
        code = b"\xdd\x05" + struct.pack("<I", 0x7E1708) + b"\xc3"
        rows = [{"status": "matched", "tu": "a.cpp", "sym": "_f", "addr": "0x401000", "len": "0x7"}]
        plan = self.derive({"a.obj": obj}, rows, code)
        self.assertEqual(plan["global"], {})
        (pins,) = plan["object"].values()
        self.assertEqual(list(pins.values()), [("_lit", 0x7E1708)])

    def test_retarget_object_rewrites_relocations_and_adds_absolute_names(self):
        obj = build_object([("_f", b"\xa1\x08\0\0\0\xc3", [(1, 1, pindata.DIR32)])],
                           [sym("_g", 0, 0, coffgen.CLASS_EXTERNAL)])
        plan = {"global": {"_g": 0x7E1000}, "object": {}}
        out, count, pins = pindata.retarget_object(Path("x.obj"), obj, plan)
        self.assertEqual((count, pins), (1, {"_g@pin007E1000": 0x7E1000}))   # DIR32 only: no rel companion
        names = {n: i for i, n, *_ in coffgen.read_symbols(out)}
        self.assertIn("_g@pin007E1000", names)
        reloc = struct.unpack_from("<IIH", out, 20 + 40 + 6)
        self.assertEqual(reloc[1], names["_g@pin007E1000"])
        self.assertEqual(out[20 + 40 + 1:20 + 40 + 5], b"\x08\0\0\0")   # addend untouched

    def test_rel32_sites_use_the_image_base_relative_companion(self):
        obj = build_object([("_f", b"\xe8\0\0\0\0\xa1\0\0\0\0\xc3", [(1, 1, pindata.REL32), (6, 1, pindata.DIR32)])],
                           [sym("_g", 0, 0, coffgen.CLASS_EXTERNAL)])
        plan = {"global": {"_g": 0x7C8D20}, "object": {}}
        out, count, pins = pindata.retarget_object(Path("x.obj"), obj, plan)
        self.assertEqual(count, 2)
        self.assertEqual(pins, {"_g@pin007C8D20": 0x7C8D20, "_g@pinrel007C8D20": 0x7C8D20 - 0x400000})
        names = {i: n for i, n, *_ in coffgen.read_symbols(out)}
        base = 20 + 40 + 11   # relocations follow the 11 code bytes
        self.assertEqual(names[struct.unpack_from("<I", out, base + 4)[0]], "_g@pinrel007C8D20")
        self.assertEqual(names[struct.unpack_from("<I", out, base + 14)[0]], "_g@pin007C8D20")

    def test_unused_pin_names_are_not_added(self):
        obj = build_object([("_f", b"\xa1\0\0\0\0\xc3", [(1, 1, pindata.DIR32)])],
                           [sym("_g", 0, 0, coffgen.CLASS_EXTERNAL)])
        out, count, used = coffgen.retarget_relocations(obj, {1: "_a"}, {1: "_b"})
        self.assertEqual((count, used), (1, {"_a"}))
        self.assertNotIn("_b", [n for _, n, *_ in coffgen.read_symbols(out)])

    def test_retarget_relocations_noop(self):
        obj = build_object([("_f", b"\xc3", [])])
        self.assertEqual(coffgen.retarget_relocations(obj, {}), (obj, 0, set()))


if __name__ == "__main__":
    unittest.main()
