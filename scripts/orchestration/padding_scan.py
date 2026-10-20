#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original | own-binary-via-Ghidra
"""Inventory aligned CC/90 run endings in the user's pinned retail PE.

Usage: padding_scan.py gamemd.exe ghidra-functions.json out.json
Export entries with: ghidra function list --limit 100000 --json
No binary bytes are written to the report. Candidates remain unverified leads.
"""
import argparse
import bisect
from collections import Counter
import hashlib
import json
from pathlib import Path
import struct

ROOT = Path(__file__).resolve().parents[2]
PADDING = {0x90, 0xCC}


def text_section(blob):
    if blob[:2] != b'MZ':
        raise ValueError('not a DOS/PE image')
    pe = struct.unpack_from('<I', blob, 0x3C)[0]
    if blob[pe:pe + 4] != b'PE\0\0':
        raise ValueError('missing PE signature')
    sections = struct.unpack_from('<H', blob, pe + 6)[0]
    opt_size = struct.unpack_from('<H', blob, pe + 20)[0]
    opt = pe + 24
    if struct.unpack_from('<H', blob, opt)[0] != 0x10B:
        raise ValueError('expected PE32 image')
    base = struct.unpack_from('<I', blob, opt + 28)[0]
    for i in range(sections):
        off = opt + opt_size + i * 40
        if blob[off:off + 8].rstrip(b'\0') == b'.text':
            vsize, rva, raw_size, raw_ptr = struct.unpack_from('<IIII', blob, off + 8)
            size = min(vsize, raw_size)  # exclude file alignment / virtual zero-fill
            data = blob[raw_ptr:raw_ptr + size]
            if len(data) != size:
                raise ValueError('truncated .text')
            return base + rva, data
    raise ValueError('no .text section')


def scan(base, data):
    """Yield maximal filler run ends that are aligned and inside the section.

    This is deliberately a byte heuristic: CC/90 can be opcodes, instruction
    operands, or data. A run ending at the section end is not a candidate.
    """
    i = 0
    while i < len(data):
        if data[i] not in PADDING:
            i += 1
            continue
        start = i
        while i < len(data) and data[i] in PADDING:
            i += 1
        if i < len(data) and (base + i) % 16 == 0:
            yield base + i, i - start


def missed_reason(addr, base, data):
    off = addr - base
    if off == 0:
        return 'section-start'
    if addr % 16:
        return 'not-16-byte-aligned'
    if data[off] in PADDING:
        return 'entry-byte-is-CC-or-90'
    return 'no-preceding-CC-or-90'


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('binary', type=Path)
    ap.add_argument('functions', type=Path)
    ap.add_argument('out', type=Path)
    ap.add_argument('--manifest', type=Path, default=ROOT / 'scripts/data/match_manifest.json')
    args = ap.parse_args()
    blob = args.binary.read_bytes()
    digest = hashlib.sha256(blob).hexdigest()
    expected = json.loads((ROOT / 'scripts/data/progress_totals.json').read_text())['_meta']['sha256']
    if digest != expected:
        ap.error('binary SHA-256 differs from the pinned retail image')
    base, data = text_section(blob)
    end = base + len(data)
    functions = json.loads(args.functions.read_text())
    listed = {int(f['entry_point'], 16): f for f in functions
              if base <= int(f['entry_point'], 16) < end}
    manifest = json.loads(args.manifest.read_text())
    claimed = {int(r['addr'], 16): r for r in manifest
               if base <= int(r['addr'], 16) < end}
    matched = {a for a, r in claimed.items() if r['status'] == 'matched'}
    candidates = dict(scan(base, data))
    starts = sorted(listed)
    # Prefix maxima handle overlapping Ghidra spans. Sizes are bounding spans,
    # not instruction ownership: containment is a warning, never a rejection.
    span_ends = []
    for addr in starts:
        lim = addr + int(listed[addr]['size'])
        span_ends.append(max(lim, span_ends[-1] if span_ends else lim))
    unlisted = []
    for addr in sorted(candidates.keys() - listed.keys()):
        i = bisect.bisect_right(starts, addr) - 1
        unlisted.append({
            'addr': '0x%X' % addr,
            'padding_run_length': candidates[addr],
            'claimed': addr in claimed,
            'inside_listed_bounding_span': i >= 0 and addr < span_ends[i],
        })
    missing = sorted(matched - candidates.keys())
    summary = {
        'padding_candidates': len(candidates),
        'listed_entries': len(listed),
        'candidates_already_listed': len(candidates.keys() & listed.keys()),
        'candidates_unlisted': len(unlisted),
        'unlisted_already_claimed': sum(r['claimed'] for r in unlisted),
        'unlisted_unclaimed': sum(not r['claimed'] for r in unlisted),
        'unlisted_unclaimed_outside_listed_bounding_spans': sum(
            not r['claimed'] and not r['inside_listed_bounding_span'] for r in unlisted),
        'unlisted_inside_listed_bounding_span': sum(r['inside_listed_bounding_span'] for r in unlisted),
        'listed_entries_missed': len(listed.keys() - candidates.keys()),
        'matched_entries': len(matched),
        'matched_entries_missed': len(missing),
        'padding_run_lengths': dict(sorted(Counter(candidates.values()).items())),
        'listed_missed_reasons': dict(sorted(Counter(
            missed_reason(a, base, data) for a in listed.keys() - candidates.keys()).items())),
    }
    report = {
        'header': {
            'schema': 'gagarin/padding_scan/1',
            'sha256': digest,
            'provenance': 'own-binary: raw PE bytes; current Ghidra entry-point export; match manifest',
            'generated_by': 'scripts/orchestration/padding_scan.py',
            'status': 'leads only; no candidate is promoted to a function by this scan',
            'method': 'maximal mixed CC/90 run ends at a 16-byte-aligned non-CC/90 byte inside .text',
            'section_start': '0x%X' % base,
            'section_end_exclusive': '0x%X' % end,
            'section_bytes_scanned': len(data),
            'function_export_sha256': hashlib.sha256(args.functions.read_bytes()).hexdigest(),
            'manifest_sha256': hashlib.sha256(args.manifest.read_bytes()).hexdigest(),
            'limitations': [
                'False positives include embedded data and filler-valued instruction operands.',
                'False negatives include unaligned entries, entries without filler and entries starting with CC/90.',
                'Ghidra bounding spans can include holes or have incorrect boundaries.',
                'Includes CRT/third-party regions; candidate count is not an engine-function count.',
                'Neither a function-count upper bound nor a reason to change the progress denominator.',
            ],
        },
        'summary': summary,
        'unlisted_candidates': unlisted,
        'matched_entries_missed': [
            {'addr': '0x%X' % a, 'tu': claimed[a]['tu'], 'name': claimed[a]['name'],
             'reason': missed_reason(a, base, data)} for a in missing],
    }
    args.out.write_text(json.dumps(report, indent=1) + '\n')
    print(json.dumps(summary, indent=1))


if __name__ == '__main__':
    main()
