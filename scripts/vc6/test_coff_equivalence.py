#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original synthetic COFF fixtures; no retail bytes.
import json
from pathlib import Path
import struct
import tempfile
import unittest
import coffgen
from coff_equivalence import plan_folds
import stubgen


class FoldTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.root = Path(self.temp.name)
        self.bindings = {'_alias': (0x401000, 'symbol_bindings'),
                         '_provider': (0x401000, 'manifest'),
                         '_target': (0x402000, 'symbol_bindings'),
                         '_other': (0x402000, 'symbol_bindings')}

    def tearDown(self):
        self.temp.cleanup()

    def obj(self, filename, name, code=b'\xe8\0\0\0\0\xc3', target='_target'):
        writer = coffgen.ObjectWriter()
        writer.add_code_comdat([name], len(code))
        section = list(writer.sections[0]); section[2] = code; writer.sections[0] = tuple(section)
        if target:
            writer.add_alias('_unused_' + name, target)
        data = bytearray(writer.build())
        if target:
            target_index = next(i for i, n, *_ in coffgen.read_symbols(data) if n == target)
            symptr = struct.unpack_from('<I', data, 8)[0]
            data[symptr:symptr] = struct.pack('<IIH', 1, target_index, 0x14)
            struct.pack_into('<I', data, 8, symptr + 10)
            struct.pack_into('<I', data, 20 + 24, symptr)
            struct.pack_into('<H', data, 20 + 32, 1)
            struct.pack_into('<H', data, symptr + 10 + 18 + 4, 1)
        path = self.root / filename; path.write_bytes(data)
        return path

    def folds(self, provider=None, alias=None, bindings=None):
        provider = provider or self.obj('p.obj', '_provider')
        alias = alias or self.obj('a.obj', '_alias', target='_other')
        return plan_folds({0x401000: ('_provider', 6)},
                          {'_provider': [provider], '_alias': [alias]}, bindings or self.bindings)

    def test_equal_code_and_bound_relocations_fold(self):
        renames, accepted, rejected = self.folds()
        self.assertEqual(len(accepted), 1)
        self.assertEqual(accepted[0]['relocations'], ((1, 0x14, 0x402000),))
        self.assertFalse(rejected)
        self.assertTrue(next(iter(renames.values()))['_alias'].startswith('__collocated_'))

    def test_different_instructions_refused(self):
        _, accepted, rejected = self.folds(alias=self.obj('a.obj', '_alias', b'\xe8\0\0\0\0\x90'))
        self.assertFalse(accepted); self.assertTrue(rejected)

    def test_different_relocation_targets_refused(self):
        bindings = dict(self.bindings); bindings['_other'] = (0x403000, 'symbol_bindings')
        self.assertFalse(self.folds(bindings=bindings)[1])

    def test_unbound_relocation_refused_even_for_same_spelling(self):
        bindings = dict(self.bindings); del bindings['_target']
        self.assertFalse(self.folds(alias=self.obj('a.obj', '_alias'), bindings=bindings)[1])

    def test_bound_weak_relocation_still_refused(self):
        path = self.obj('a.obj', '_alias')
        data = bytearray(path.read_bytes())
        weak = next(i for i, n, *_ in coffgen.read_symbols(data) if n == '_unused__alias')
        reloc = struct.unpack_from('<I', data, 20 + 24)[0]
        struct.pack_into('<I', data, reloc + 4, weak)
        path.write_bytes(data)
        bindings = dict(self.bindings); bindings['_unused__alias'] = (0x402000, 'symbol_bindings')
        self.assertFalse(self.folds(alias=path, bindings=bindings)[1])

    def test_distinct_addresses_do_not_fold(self):
        bindings = dict(self.bindings); bindings['_alias'] = (0x401010, 'symbol_bindings')
        self.assertEqual(self.folds(bindings=bindings), ({}, [], []))

    def test_all_definitions_must_agree(self):
        p = self.obj('p.obj', '_provider'); a = self.obj('a.obj', '_alias')
        bad = self.obj('bad.obj', '_alias', b'\xe8\0\0\0\0\x90')
        self.assertFalse(plan_folds({0x401000: ('_provider', 6)},
                                   {'_provider': [p], '_alias': [a, bad]}, self.bindings)[1])

    def test_competing_weak_definition_refused(self):
        p = self.obj('p.obj', '_provider'); a = self.obj('a.obj', '_alias')
        writer = coffgen.ObjectWriter(); writer.add_alias('_alias', '_other')
        weak = self.root / 'weak.obj'; weak.write_bytes(writer.build())
        self.assertFalse(plan_folds({0x401000: ('_provider', 6)},
                                   {'_provider': [p], '_alias': [a, weak]}, self.bindings)[1])

    def test_code_beyond_validated_extent_refused(self):
        self.assertFalse(self.folds(alias=self.obj('a.obj', '_alias', b'\xe8\0\0\0\0\xc3\xc3'))[1])

    def test_plan_retargets_references_and_preserves_alias(self):
        p = self.obj('p.obj', '_provider'); a = self.obj('a.obj', '_alias')
        (self.root / 'objects.json').write_text(json.dumps({'objects': [
            {'source': 'p.cpp', 'object': p.name}, {'source': 'a.cpp', 'object': a.name}]}))
        result = stubgen.plan(self.root, set(), self.root / 'out',
            manifest=[{'tu': 'p.cpp', 'addr': '0x401000', 'sym': '_provider', 'len': '0x6', 'status': 'matched'}],
            extents=[['0x401000', '0x6', '0xA', 'nop', 'engine', []]],
            symbol_bindings={'_alias': '0x401000', '_target': '0x402000'})
        self.assertEqual(len(result['collocated_comdats']), 1)
        symbols = {name: scl for _, name, _, _, scl, _ in coffgen.read_symbols((self.root / 'out/stubs.obj').read_bytes())}
        self.assertEqual(symbols['_alias'], 105)
        names = {name for _, name, *_ in coffgen.read_symbols((self.root / 'out/objects/a.obj').read_bytes())}
        self.assertIn('_alias', names)
        self.assertTrue(any(n.startswith('__collocated_') for n in names))

    def test_weak_default_retargeted_to_public_alias(self):
        writer = coffgen.ObjectWriter()
        writer.add_code_comdat(['_alias'], 6)
        writer.add_alias('_weak', '_alias')
        data, _ = coffgen.rename_symbols(writer.build(), {'_alias': '__dead'}, retarget_weak_defaults=True)
        rows = {n: (i, sec) for i, n, _, sec, _, _ in coffgen.read_symbols(data)}
        symptr = struct.unpack_from('<I', data, 8)[0]
        target = struct.unpack_from('<I', data, symptr + 18 * (rows['_weak'][0] + 1))[0]
        self.assertEqual(target, rows['_alias'][0])
        self.assertEqual(rows['_alias'][1], 0)
        self.assertGreater(rows['__dead'][1], 0)

    def duplicate_plan(self, second_code, alias_code):
        p = self.obj('p.obj', '_provider')
        q = self.obj('q.obj', '_provider', second_code)
        a = self.obj('a.obj', '_alias', alias_code)
        (self.root / 'objects.json').write_text(json.dumps({'objects': [
            {'source': n + '.cpp', 'object': path.name}
            for n, path in [('p', p), ('q', q), ('a', a)]]}))
        return stubgen.plan(self.root, set(), self.root / 'out',
            manifest=[{'tu': n + '.cpp', 'addr': addr, 'sym': '_provider',
                       'len': '0x6', 'status': 'matched'}
                      for n, addr in [('p', '0x401000'), ('q', '0x401010')]],
            extents=[[addr, '0x6', '0xA', 'nop', 'engine', []]
                     for addr in ['0x401000', '0x401010']],
            symbol_bindings={'_alias': '0x401010', '_target': '0x402000'})

    def test_duplicate_provider_alias_uses_row_specific_definition(self):
        # The original spelling is shared, but only q.obj is renamed to the
        # second address. Its body must be the one used for equivalence.
        code = b'\xe8\0\0\0\0\x90'
        result = self.duplicate_plan(code, code)
        fold, = result['collocated_comdats']
        self.assertEqual(fold['provider'], '?dup_00401010@@YAXXZ')
        path = self.root / 'out/objects/q.obj'
        self.assertIn('?dup_00401010@@YAXXZ',
                      {n for _, n, *_ in coffgen.read_symbols(path.read_bytes())})
        data = (self.root / 'out/stubs.obj').read_bytes()
        rows = {n: (i, scl) for i, n, _, _, scl, _ in coffgen.read_symbols(data)}
        self.assertEqual(rows['_alias'][1], 105)
        symptr = struct.unpack_from('<I', data, 8)[0]
        default = struct.unpack_from('<I', data, symptr + 18 * (rows['_alias'][0] + 1))[0]
        self.assertEqual(default, rows['?dup_00401010@@YAXXZ'][0])

    def test_duplicate_provider_does_not_use_first_address_body(self):
        result = self.duplicate_plan(b'\xe8\0\0\0\0\x90',
                                     b'\xe8\0\0\0\0\xc3')
        self.assertFalse(result['collocated_comdats'])
        self.assertEqual(result['collocated_comdats_rejected'][0]['provider'],
                         '?dup_00401010@@YAXXZ')


if __name__ == '__main__':
    unittest.main()
