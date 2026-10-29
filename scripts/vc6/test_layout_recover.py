#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original
"""Fixture tests for layout_recover.py and ctor_gen.py.

The listings below are hand-written objdump-style text, not retail bytes; the tests need no
binary.
"""
import os
from pathlib import Path
import tempfile
import unittest

import binfn
import ctor_gen
import layout_recover as lr


def listing(lines, base=0x1000):
    out = []
    a = base
    for ln in lines:
        out.append('  %x:\t90 90 90 \t%s' % (a, ln))
        a += 3
    return binfn.parse_objdump('\n'.join(out))


SWZ = 0x6CF240


class ParseTests(unittest.TestCase):
    def test_parse_and_mem(self):
        ins = listing(['mov    DWORD PTR [esi+0x21c],eax', 'rep stos DWORD PTR es:[edi],eax'])
        self.assertEqual(ins[0].mn, 'mov')
        self.assertEqual(binfn.mem(ins[0].ops[0]), (4, 'esi', 0x21C))
        self.assertEqual(ins[1].mn, 'stos')

    def test_tracker_follows_receiver(self):
        tr = binfn.Tracker('ecx')
        for i in listing(['mov    esi,ecx', 'lea    edx,[esi+0x20]', 'mov    eax,DWORD PTR [esi+0x8]',
                          'call   0x2000', 'push   edx']):
            tr.step(i)
        self.assertEqual(tr.held.get('esi'), 0)
        self.assertNotIn('edx', tr.held)          # cleared by the call
        self.assertNotIn('eax', tr.held)

    def test_stack_receiver(self):
        tr = binfn.Tracker('stack')
        for i in listing(['push   ebx', 'push   esi', 'mov    esi,DWORD PTR [esp+0xc]']):
            tr.step(i)
        self.assertEqual(tr.held.get('esi'), 0)


class ExtractorTests(unittest.TestCase):
    def test_swizzle_marks_pointer_fields(self):
        ins = listing(['push   ebx', 'push   esi', 'mov    esi,DWORD PTR [esp+0xc]',
                       'lea    ecx,[esi+0x21c]', 'push   ecx', 'push   0xb0c110', 'call   0x6cf240',
                       'lea    edx,[esi+0x14c]', 'push   edx', 'push   0xb0c110', 'call   0x6cf240'])
        evs = lr.extract_swizzle(ins, SWZ)
        self.assertEqual([(e.off, e.pointer) for e in evs], [(0x21C, True), (0x14C, True)])

    def test_swizzle_loop_expands_array(self):
        ins = listing(['mov    esi,DWORD PTR [esp+0x4]', 'lea    edi,[esi+0x304]', 'mov    ebp,0x8',
                       'push   edi', 'push   0xb0c110', 'call   0x6cf240', 'add    edi,0x4', 'dec    ebp',
                       'jne    0x1009'])
        evs = lr.extract_swizzle(ins, SWZ)
        self.assertEqual([e.off for e in evs], [0x304 + 4 * k for k in range(8)])

    def test_istream_read_write(self):
        ins = listing(['mov    esi,ecx', 'lea    eax,[esi+0x30]', 'push   0x0', 'push   0x10', 'push   eax',
                       'push   edi', 'call   DWORD PTR [edx+0xc]'])
        evs = lr.extract_streams(ins, 'ecx')
        self.assertEqual([(e.off, e.width, e.source) for e in evs], [(0x30, 0x10, 'stream')])

    def test_crc_sequence_and_sizes(self):
        sinks = {0x2000: 4, 0x2010: 8, 0x2020: 1}
        ins = listing(['mov    esi,ecx', 'mov    eax,DWORD PTR [esi+0x214]', 'push   eax', 'call   0x2000',
                       'mov    ecx,DWORD PTR [esi+0x15c]', 'mov    edx,DWORD PTR [esi+0x158]', 'push   ecx',
                       'push   edx', 'call   0x2010', 'mov    al,BYTE PTR [esi+0x250]', 'push   eax',
                       'call   0x2020'])
        evs = lr.extract_crc(ins, sinks.get)
        self.assertEqual([(e.off, e.width) for e in evs], [(0x214, 4), (0x158, 4), (0x15C, 4), (0x250, 1)])

    def test_ini_keys_pair_with_stores(self):
        strings = {0x844520: 'Cameo', 0x844510: 'Speed'}
        ins = listing(['mov    esi,ecx', 'mov    eax,DWORD PTR [esi+0x604]', 'push   eax', 'push   0x844520',
                       'push   ebx', 'call   0x5276d0', 'mov    DWORD PTR [esi+0x604],eax',
                       'mov    ecx,DWORD PTR [esi+0x600]', 'push   ecx', 'push   0x844510', 'push   ebx',
                       'call   0x5276d0', 'mov    DWORD PTR [esi+0x600],eax'])
        evs = lr.extract_ini(ins, strings.get, {0x5276d0: 'ReadInteger'}.get)
        self.assertEqual([(e.off, e.key, e.typ) for e in evs], [(0x604, 'Cameo', 'int'), (0x600, 'Speed', 'int')])


HEADER = """
class Foo : public Base
{
public:
    int            Alpha;            // +0x10
    unsigned char  unknown_14[8];    // +0x14
    bool           Flag;             // +0x1C
    unknown_tail;
};
GG_STATIC_ASSERT(sizeof(Foo) == 0x20);
GG_STATIC_ASSERT(offsetof(Foo, Alpha) == 0x10);
"""


class HeaderAndMergeTests(unittest.TestCase):
    def index(self):
        d = tempfile.mkdtemp()
        os.makedirs(os.path.join(d, 'match', '_layout'))
        Path(d, 'match', '_layout', 'foo.h').write_text(HEADER)
        return lr.HeaderIndex(d)

    def test_members_and_sizes(self):
        h = self.index()
        f, ms, _ = h.members('Foo')
        self.assertEqual([(m.name, m.off) for m in ms], [('Alpha', 0x10), ('unknown_14', 0x14), ('Flag', 0x1C)])
        self.assertEqual(h.type_size('unsigned char'), 1)
        self.assertEqual(h.sizes['Foo'], 0x20)

    def test_gap_is_filled_from_merged_evidence(self):
        evs = [lr.Ev(0x14, 4, 'ctor', 'store', at=0x1), lr.Ev(0x14, 4, 'swizzle', 'ptr', at=0x2, pointer=True),
               lr.Ev(0x18, 1, 'ini', 'ReadBool("Hidden")', at=0x3, key='Hidden', typ='bool')]
        by_off = {}
        for e in evs:
            by_off.setdefault(e.off, []).append(e)
        props = lr.field_proposals(by_off, sorted(by_off), 0x14, 0x1C)
        self.assertEqual([(p['off'], p['type'], p['name']) for p in props],
                         [(0x14, 'void*', 'unknown_14'), (0x18, 'bool', 'Hidden')])
        self.assertEqual(props[0]['sources'], ['ctor', 'swizzle'])


class CtorGenTests(unittest.TestCase):
    def test_assignments_cover_init_list_and_body(self):
        text = 'Foo::Foo()\n    : Alpha(0), Beta(-1)\n{\n    Flag = true;\n    Timer.Rate = 5;\n}'
        self.assertEqual(ctor_gen.assignments(text),
                         [('Alpha', '0'), ('Beta', '-1'), ('Flag', '1'), ('Timer', '5')])

    def test_compare_reports_missing_and_extra(self):
        d = {'cls': 'Foo', 'init': [('base', 'Base()', 0)], 'body': ['Alpha = 0;', 'Gamma = 2;']}
        r = ctor_gen.compare(d, 'Foo::Foo()\n    : Alpha(0), Beta(1)\n{\n}')
        self.assertEqual(r['common'], 1)
        self.assertEqual(r['missing_in_draft'], ['Beta'])
        self.assertIn('Gamma', r['extra_in_draft'])


if __name__ == '__main__':
    unittest.main()
