# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original project tooling.
"""Tests for the structure-migration tools (synthetic COFF objects; no compiler, no retail binary)."""

import json
import struct
import sys
import tempfile
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import chd_census  # noqa: E402
import emitter_map  # noqa: E402
import static_init_dump  # noqa: E402
import tu_mapping  # noqa: E402
import wwlib  # noqa: E402


def make_obj(symbols, comdat=True):
    """symbols: [(name, bytes)] each in its own section; returns COFF object bytes (x86, no relocations)."""
    secs, syms, strtab = [], [], b""
    raw_off = 20 + 40 * len(symbols)
    body = b""
    for i, (name, raw) in enumerate(symbols):
        hdr = b".text\0\0\0" + struct.pack("<IIIIIIHHI", 0, 0, len(raw), raw_off + len(body), 0, 0, 0, 0,
                                          0x60000020 | (0x1000 if comdat else 0))
        secs.append(hdr)
        body += raw
        nm = name.encode()
        off = 4 + len(strtab)
        strtab += nm + b"\0"
        syms.append(b"\0\0\0\0" + struct.pack("<I", off) + struct.pack("<IhHBB", 0, i + 1, 0x20, 2, 0))
    symptr = raw_off + len(body)
    head = struct.pack("<HHIIIHH", 0x14C, len(symbols), 0, symptr, len(symbols), 0, 0)
    return head + b"".join(secs) + body + b"".join(syms) + struct.pack("<I", 4 + len(strtab)) + strtab


def make_dir(root, objs):
    """objs: {source: coff bytes}; writes objects.json and the objects."""
    index = []
    for src, data in objs.items():
        p = Path(root) / (src.replace("/", "_") + ".obj")
        p.write_bytes(data)
        index.append({"source": src, "object": p.name, "success": True})
    (Path(root) / "objects.json").write_text(json.dumps({"objects": index}))
    return root


def chd(attr):
    return struct.pack("<IIII", 0, attr, 1, 0)


class Census(unittest.TestCase):
    def test_attributes_and_flip(self):
        with tempfile.TemporaryDirectory() as a, tempfile.TemporaryDirectory() as b:
            make_dir(a, {"x.cpp": make_obj([("??_R3FooClass@@8", chd(5))])})
            make_dir(b, {"x.cpp": make_obj([("??_R3FooClass@@8", chd(1))])})
            before, after = chd_census.census(a), chd_census.census(b)
            self.assertEqual(after[("x.cpp", "??_R3FooClass@@8")], 1)
            table = chd_census.rows(after, before, retail={"FooClass@@8": ("FooClass", 1)})
            self.assertEqual(table[0]["status"], "ok")
            s = chd_census.summarise(table)
            self.assertEqual(s["flipped"], [("x.cpp", "FooClass", 5, 1)])


class Emitter(unittest.TestCase):
    def test_first_definer_is_kept_and_divergence_flagged(self):
        with tempfile.TemporaryDirectory() as d:
            make_dir(d, {"a.cpp": make_obj([("??_R3FooClass@@8", chd(5))]),
                         "b.cpp": make_obj([("??_R3FooClass@@8", chd(1))])})
            m = emitter_map.build_map(d, manifest=[])
            e = m["??_R3FooClass@@8"]
            self.assertEqual(e["kept"], "a.cpp")
            self.assertEqual(e["definers"], ["a.cpp", "b.cpp"])
            self.assertFalse(e["identical"])
            self.assertEqual(e["chd"]["ours"], 5)

    def test_manifest_address_orders_the_link(self):
        with tempfile.TemporaryDirectory() as d:
            make_dir(d, {"a.cpp": make_obj([("??_R3FooClass@@8", chd(5))]),
                         "b.cpp": make_obj([("??_R3FooClass@@8", chd(1))])})
            m = emitter_map.build_map(d, manifest=[{"tu": "b.cpp", "addr": "0x401000"}])
            self.assertEqual(m["??_R3FooClass@@8"]["kept"], "b.cpp")

    def test_diff(self):
        old = {"s": {"kept": "a", "digest": "1"}, "t": {"kept": "a", "digest": "1"}, "u": {"kept": "a", "digest": "1"}}
        new = {"s": {"kept": "b", "digest": "1"}, "t": {"kept": "a", "digest": "2"}, "v": {"kept": "a", "digest": "1"}}
        kinds = {c["symbol"]: c["change"] for c in emitter_map.diff_maps(old, new)}
        self.assertEqual(kinds, {"s": "emitter", "t": "bytes", "u": "removed", "v": "added"})


class StaticInit(unittest.TestCase):
    def test_renumber_detected(self):
        with tempfile.TemporaryDirectory() as a, tempfile.TemporaryDirectory() as b:
            make_dir(a, {"x.cpp": make_obj([("_$E5", b"\x90\xc3")], comdat=False)})
            make_dir(b, {"x.cpp": make_obj([("_$E7", b"\x90\xc3")], comdat=False)})
            diff = static_init_dump.diff(static_init_dump.dump(a), static_init_dump.dump(b))
            self.assertEqual([c["change"] for c in diff], ["renumbered"])


class Mapping(unittest.TestCase):
    def test_family_name(self):
        self.assertEqual(tu_mapping.family_name("TriggerTypeClass"), "TriggerType")
        self.assertEqual(tu_mapping.family_name("DynamicVectorClass<int>"), "DynamicVector")
        self.assertEqual(tu_mapping.family_name("INIClass::INIEntry"), "INIEntry")

    def test_rules(self):
        tu_map = {"link_order": [{"tu": "House.cpp", "lo": "0x1000", "hi": "0x2000"}],
                  "functions": [
                      {"addr": "0x1000", "tu": "House.cpp", "tu_kind": "witnessed"},
                      {"addr": "0x1500", "tu": None, "tu_kind": "unknown"},
                      {"addr": "0x3000", "tu": "class:TriggerTypeClass@after:x", "tu_kind": "inferred-class"},
                      {"addr": "0x3100", "tu": "class:TriggerTypeClass", "tu_kind": "inferred-contiguity"},
                      {"addr": "0x3200", "tu": None, "tu_kind": "comdat"},
                      {"addr": "0x3300", "tu": "class:HouseClass", "tu_kind": "inferred-class"},
                  ]}
        manifest = [{"tu": "match/a.cpp", "addr": "0x1000"}, {"tu": "match/a.cpp", "addr": "0x1500"},
                    {"tu": "match/b.cpp", "addr": "0x3000"}, {"tu": "match/b.cpp", "addr": "0x3100"},
                    {"tu": "match/b.cpp", "addr": "0x3200"},
                    {"tu": "match/c.cpp", "addr": "0x3300"}, {"tu": "match/c.cpp", "addr": "0x1000"},
                    {"tu": "match/d.cpp", "addr": "0x3200"}]
        m = tu_mapping.build(tu_map, manifest)
        self.assertEqual(m["match/a.cpp"]["target"], "House.cpp")   # window rule, unknown ignored
        self.assertEqual(m["match/b.cpp"]["target"], "TriggerType.CPP")
        self.assertEqual(m["match/c.cpp"]["status"], "split")
        self.assertEqual(m["match/d.cpp"]["status"], "unplaced")


if __name__ == "__main__":
    unittest.main()
