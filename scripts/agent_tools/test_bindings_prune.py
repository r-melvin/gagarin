#!/usr/bin/env python3
"""Unit tests for bindings_prune.py (no objects, no retail binary).

    python3 -m unittest test_bindings_prune        (from this directory)
"""
import os
import sys
import unittest

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import bindings_prune as P  # noqa: E402


class Stale(unittest.TestCase):
    def test_defined_or_referenced_is_live(self):
        per = {"match/a": {"?DAT_1@@3HA", "?Ref@@YAXXZ"}, "match/b": {"_DAT_2"}}
        union = set().union(*per.values())
        b = {"?DAT_1@@3HA": "0x1", "?Ref@@YAXXZ": "0x2", "_DAT_2": "0x3", "?DAT_00B0FB48@@3HA": "0x4", "?Gone@@3HA": "0x5"}
        self.assertEqual(P.stale_keys(b, per, union), ["?DAT_00B0FB48@@3HA", "?Gone@@3HA"])

    def test_scoped_key_uses_its_own_object(self):
        per = {"match/a": {"x"}, "match/b": {"y"}}
        union = {"x", "y"}
        b = {"match/a.cpp::x": "0x1", "match/a.cpp::y": "0x2", "match/gone.cpp::y": "0x3", "match/gone.cpp::z": "0x4"}
        # a.cpp::y: a's object lacks y (b has it) -> stale; a TU without an object falls back to any object
        self.assertEqual(P.stale_keys(b, per, union), ["match/a.cpp::y", "match/gone.cpp::z"])


if __name__ == "__main__":
    unittest.main()
