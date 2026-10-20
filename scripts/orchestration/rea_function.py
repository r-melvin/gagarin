#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original
"""Run REA on a validated .text entry and extent omitted by whole-image analysis.

Usage: rea_function.py /path/to/gamemd.exe 0x6E6080 0xDD /tmp/tag-reader.json

The output is REA's complete Evidence record, including assembly and bytes;
output inside this repository is rejected. A provenance sidecar binds its temporary raw
input to the pinned retail image. Calls/globals outside the selected range are
unavailable to the raw-image decompiler. This is an analysis aid, not a match
oracle or a source of trusted stack types.
"""
import argparse
import hashlib
import json
from pathlib import Path
import subprocess
import tempfile

from padding_scan import ROOT, text_section


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('binary', type=Path)
    ap.add_argument('address', type=lambda s: int(s, 0))
    ap.add_argument('length', type=lambda s: int(s, 0))
    ap.add_argument('out', type=Path)
    args = ap.parse_args()
    if args.out.resolve().is_relative_to(ROOT):
        ap.error('raw REA evidence contains retail bytes; choose an output outside the repository')
    blob = args.binary.read_bytes()
    digest = hashlib.sha256(blob).hexdigest()
    expected = json.loads((ROOT / 'scripts/data/progress_totals.json').read_text())['_meta']['sha256']
    if digest != expected:
        ap.error('binary SHA-256 differs from the pinned retail image')
    base, text = text_section(blob)
    offset = args.address - base
    if args.length <= 0 or offset < 0 or offset + args.length > len(text):
        ap.error('the selected nonempty range must be wholly inside file-backed .text')
    if args.out.exists() or args.out.with_suffix('.provenance.json').exists():
        ap.error('choose a new output path to preserve existing evidence')
    excerpt = text[offset:offset + args.length]
    raw_digest = hashlib.sha256(excerpt).hexdigest()
    with tempfile.TemporaryDirectory(prefix='gagarin-rea-') as work:
        raw = Path(work) / ('function-%x.bin' % args.address)
        raw.write_bytes(excerpt)
        result = subprocess.run([
            'rea', 'function', str(raw), '--procedure', hex(args.address),
            '--target-format', 'raw-binary', '--architecture', 'x86',
            '--entry-point', hex(args.address), '--provider', 'ghidra',
            '--format', 'json',
        ], capture_output=True, text=True)
    if result.returncode:
        raise SystemExit(result.stderr or result.stdout or 'REA analysis failed')
    record = json.loads(result.stdout)
    if record.get('operation') != 'analyze_function' or not record.get('evidence_id'):
        raise SystemExit('REA did not return a function Evidence record')
    if record['subject']['digest']['sha256'] != raw_digest:
        raise SystemExit('REA input digest does not match the selected retail range')
    observed = record['normalized_result']['procedure']
    if int(observed['address'], 16) != args.address:
        raise SystemExit('REA returned a different procedure entry')
    args.out.write_text(json.dumps(record, indent=1) + '\n')
    args.out.with_suffix('.provenance.json').write_text(json.dumps({
        'schema': 'gagarin/rea_function_input/1',
        'retail_sha256': digest,
        'section': '.text',
        'section_start': hex(base),
        'section_relative_offset': hex(offset),
        'entry_point': hex(args.address),
        'excerpt_length': args.length,
        'excerpt_sha256': raw_digest,
        'rea_evidence_id': record['evidence_id'],
        'observed_body': observed['body'],
        'limitations': 'Raw input omits surrounding code, imports, strings and globals; this is not a VC6 match verdict.',
    }, indent=1) + '\n')
    print('%s: %s, %s observed bytes -> %s' % (
        hex(args.address), record['evidence_id'], observed['body']['total_bytes'], args.out))


if __name__ == '__main__':
    main()
