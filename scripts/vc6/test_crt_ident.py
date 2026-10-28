#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original synthetic fixtures; no retail or library bytes.
"""Check crt_ident's archive parsing, relocation masking and placement on synthetic data."""

import struct
import unittest

import crt_ident


def obj_with_text(code, reloc_offsets=()):
    """Minimal COFF object with one .text section and one external symbol."""
    hdr_size, sec_hdr = 20, 40
    rawptr = hdr_size + sec_hdr
    relptr = rawptr + len(code)
    relocs = b"".join(struct.pack("<IIH", o, 0, 0x14) for o in reloc_offsets)
    symptr = relptr + len(relocs)
    sec = struct.pack("<8sIIIIIIHHI", b".text", 0, 0, len(code), rawptr, relptr, 0, len(reloc_offsets), 0,
                      0x60500020)
    sym = struct.pack("<8sIhHBB", b"_f", 0, 1, 0x20, 2, 0)
    return struct.pack("<HHIIIHH", 0x14C, 1, 0, symptr, 1, 0, 0) + sec + code + relocs + sym + struct.pack("<I", 4)


def archive(members):
    out = b"!<arch>\n" + b"/".ljust(16) + b"0".ljust(12 + 6 + 6 + 8) + b"4".ljust(10) + b"`\n" + b"\0\0\0\0"
    for name, body in members:
        out += (name + "/").ljust(16).encode() + b"0".ljust(12 + 6 + 6 + 8) + str(len(body)).ljust(10).encode() + b"`\n" + body
        if len(body) & 1:
            out += b"\n"
    return out


class CrtIdentTests(unittest.TestCase):
    def test_archive_and_masking(self):
        code = b"\x55\x8b\xec\xe8\0\0\0\0\x5d\xc3"
        import tempfile, pathlib
        with tempfile.TemporaryDirectory() as d:
            p = pathlib.Path(d) / "x.lib"
            p.write_bytes(archive([("a.obj", obj_with_text(code, [4]))]))
            (name, obj), = crt_ident.archive_members(p)
        self.assertEqual(name, "a.obj")
        (sec,) = crt_ident.code_sections(obj)
        self.assertEqual(sec["mask"], bytes([0, 0, 0, 0, 1, 1, 1, 1, 0, 0]))
        self.assertEqual(sec["symbols"], [("_f", 0, True)])
        sec["runs"] = crt_ident.runs(sec)
        tail = b"\xcc" * 3 + b"\x55\x8b\xec\xe8\x12\x34\x56\x78\x5d\xc3" + b"\xcc" * 3
        self.assertEqual(crt_ident.candidates(sec, tail), [3])

    def test_identify_uses_member_contiguity(self):
        def sec(i, member, size, cands):
            return {"id": i, "member_key": member, "cands": cands, "size": size, "align": 1, "order": (0, member, i)}
        # section 1 is unique; section 2 (same member) matches at 20 and 50, only 20 touches section 1
        secs = [sec(0, 0, 10, [10]), sec(1, 0, 10, [20, 50])]
        placed, alive, inferred = crt_ident.identify(secs, bytes(100))
        self.assertEqual(placed, {0: 10, 1: 20})
        self.assertFalse(alive)

    def test_identical_siblings_are_order_inferred(self):
        def sec(i, size, cands):
            return {"id": i, "member_key": 0, "cands": cands, "size": size, "align": 1, "order": (0, 0, i)}
        placed, alive, inferred = crt_ident.identify([sec(0, 8, [0, 100]), sec(1, 8, [0, 100]), sec(2, 4, [150])], bytes(200))
        self.assertEqual(placed, {0: 0, 1: 100, 2: 150})
        self.assertEqual(inferred, {0, 1})
        # without a placed sibling nothing is invented
        placed, alive, inferred = crt_ident.identify([sec(0, 8, [0, 100]), sec(1, 8, [0, 100])], bytes(200))
        self.assertFalse(placed)


if __name__ == "__main__":
    unittest.main()
