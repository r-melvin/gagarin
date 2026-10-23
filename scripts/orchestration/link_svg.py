#!/usr/bin/env python3
# SPDX-Provenance: original
#
# link_svg.py — render the README link-milestone graphic from
# scripts/data/link_progress.json. Needs no retail binary.
#
# Refresh the data from the link tools' output, then render:
#   link_svg.py --refresh --diag D/report.json --m1 M1DIR
#     D      link_diag.py --out directory (report.json)
#     M1DIR  link_m1.py --out directory (link_report.json, mapcheck.json,
#            stubs/plan.json, m1.map)
#   link_svg.py [out.svg] [--data F]
#   (default out: .github/assets/link_progress.svg)

import argparse
import json
import os
import sys

ROOT = os.path.normpath(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..', '..'))
DATA = os.path.join(ROOT, 'scripts/data/link_progress.json')
W = 720

# Milestones and their states; the identity definition (M5) is the one in
# AGENTS.md: the complete unsigned image equals the pinned retail file.
MILESTONES = [
    ('M0', 'Diagnostic link', 'done'),
    ('M1', 'Address-faithful stub link', 'done'),
    ('M2', 'Hybrid runnable build', 'next'),
    ('M3', 'Matched objects swap in', 'todo'),
    ('M4', 'Pure-source playable', 'todo'),
    ('M5', 'Unsigned image identical', 'todo'),
]


def refresh(diag, m1dir):
    """Collect the figures from link_diag.py and link_m1.py output."""
    sys.path.insert(0, os.path.join(ROOT, 'scripts/vc6'))
    import mapcheck
    d = json.load(open(diag))
    rep = json.load(open(os.path.join(m1dir, 'link_report.json')))
    chk = json.load(open(os.path.join(m1dir, 'mapcheck.json')))
    plan = json.load(open(os.path.join(m1dir, 'stubs/plan.json')))['placed']
    publics, _ = mapcheck.parse_map(open(os.path.join(m1dir, 'm1.map'), encoding='latin-1').read())
    at = [p for p in plan if publics.get(p['symbol']) == int(p['addr'], 16)]
    return {
        'milestones': [{'id': i, 'name': n, 'state': s} for i, n, s in MILESTONES],
        'm0': {'unresolved': d['unresolved_total'], 'by_kind': d['counts'],
               'duplicate_definitions': d['duplicate_definitions'], 'objects': d['objects']},
        'm1': {'link_exit_code': rep['link_exit_code'], 'unresolved_after_stubs': rep['unresolved_after_stubs'],
               'duplicates': len(rep['duplicates']), 'stubs_placed': rep['stubs_placed'],
               'matched_functions': chk['matched_functions'],
               'matched_at_retail_address': chk['matched_at_retail_address'],
               'ordered_entries': chk['ordered_entries'], 'entries_at_retail_address': len(at),
               'ordered_bytes': sum(int(p['len'], 16) for p in plan),
               'bytes_at_retail_address': sum(int(p['len'], 16) for p in at),
               'drift_events': chk['drift_events'],
               'entry_point_delta': chk['landmarks']['entry point (WinMainCRTStartup)']['delta']},
    }


def bar(y, label, value, total, note, cls='done'):
    x, w, h = 24, W - 48, 18
    pct = 100.0 * value / total if total else 0.0
    return (
        f'<text x="{x}" y="{y}" class="label">{label}</text>'
        f'<text x="{W - 24}" y="{y}" class="pct" text-anchor="end">{pct:.2f}%</text>'
        f'<rect x="{x}" y="{y + 8}" width="{w}" height="{h}" rx="9" class="track"/>'
        f'<rect x="{x}" y="{y + 8}" width="{w * value / total if total else 0:.1f}" height="{h}" rx="9" class="{cls}"/>'
        f'<text x="{x}" y="{y + 44}" class="note">{note}</text>'
    )


def render(s):
    m0, m1 = s['m0'], s['m1']
    out = []
    y = 40
    out.append(f'<text x="24" y="{y}" class="title">gagarin — link milestones</text>')
    y += 30
    n = len(s['milestones'])
    step = (W - 140) / (n - 1)
    cy = y + 12
    out.append(f'<line x1="70" y1="{cy}" x2="{W - 70}" y2="{cy}" class="rail"/>')
    for i, ms in enumerate(s['milestones']):
        cx = 70 + i * step
        out.append(f'<circle cx="{cx:.1f}" cy="{cy}" r="10" class="m-{ms["state"]}"/>'
                   f'<text x="{cx:.1f}" y="{cy + 4}" class="mid" text-anchor="middle">{ms["id"][1:]}</text>'
                   f'<text x="{cx:.1f}" y="{cy + 30}" class="mlabel" text-anchor="middle">{ms["id"]} · {ms["state"]}</text>')
        words = ms['name'].split()
        half = (len(words) + 1) // 2
        for j, line in enumerate((' '.join(words[:half]), ' '.join(words[half:]))):
            if line:
                out.append(f'<text x="{cx:.1f}" y="{cy + 46 + 14 * j}" class="note" text-anchor="middle">{line}</text>')
    y = cy + 96
    top = max(m0['unresolved'], 1)
    out.append(f'<text x="24" y="{y}" class="label">Unresolved externals</text>')
    y += 14
    for name, v in (('M0 diagnostic link', m0['unresolved']), ('M1 after stubs', m1['unresolved_after_stubs'])):
        w = (W - 48 - 150 - 60) * v / top
        out.append(f'<text x="24" y="{y + 12}" class="note">{name}</text>'
                   f'<rect x="174" y="{y + 2}" width="{max(w, 2):.1f}" height="12" rx="6" class="warn"/>'
                   f'<text x="{174 + max(w, 2) + 8:.1f}" y="{y + 12}" class="note">{v:,}</text>')
        y += 20
    y += 24
    out.append(bar(y, 'M1: matched functions at their retail address', m1['matched_at_retail_address'],
                   m1['matched_functions'],
                   f"{m1['matched_at_retail_address']:,} of {m1['matched_functions']:,} placed matched functions; "
                   f"{m1['stubs_placed']:,} int3 stubs fill the rest"))
    y += 82
    out.append(bar(y, 'M1: engine .text entries at their retail address', m1['entries_at_retail_address'],
                   m1['ordered_entries'],
                   f"{m1['entries_at_retail_address']:,} of {m1['ordered_entries']:,} ordered entries · "
                   f"{m1['bytes_at_retail_address']:,} of {m1['ordered_bytes']:,} bytes · "
                   f"{m1['drift_events']} local drift events"))
    y += 70
    out.append(f'<text x="24" y="{y}" class="note">Layout probe only: stub bodies are int3 and the library tail is not '
               f'ordered (entry point {m1["entry_point_delta"]:+,} bytes).</text>')
    y += 20
    style = (
        '.bg{fill:#ffffff}.title{font:600 20px sans-serif;fill:#1f2328}'
        '.label{font:600 14px sans-serif;fill:#1f2328}.pct{font:600 14px monospace;fill:#1f2328}'
        '.note{font:12px sans-serif;fill:#59636e}.mlabel{font:600 12px sans-serif;fill:#1f2328}'
        '.mid{font:600 11px sans-serif;fill:#ffffff}.track{fill:#e6e8eb}.rail{stroke:#d0d7de;stroke-width:3}'
        '.done,.m-done{fill:#1a7f37}.m-next{fill:#d4a72c}.m-todo{fill:#8c959f}.warn{fill:#bc4c00}'
        '@media (prefers-color-scheme: dark){.bg{fill:#0d1117}.title,.label,.pct,.mlabel{fill:#e6edf3}'
        '.note{fill:#9198a1}.track{fill:#262c36}.rail{stroke:#3d444d}.done,.m-done{fill:#3fb950}'
        '.m-next{fill:#d29922}.m-todo{fill:#656c76}.warn{fill:#db6d28}}'
    )
    return (f'<svg xmlns="http://www.w3.org/2000/svg" width="{W}" height="{y}" viewBox="0 0 {W} {y}" '
            f'role="img" aria-label="gagarin link milestones">'
            f'<style>{style}</style><rect width="{W}" height="{y}" rx="12" class="bg"/>'
            + ''.join(out) + '</svg>\n')


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('out', nargs='?', default=os.path.join(ROOT, '.github/assets/link_progress.svg'))
    ap.add_argument('--data', default=DATA)
    ap.add_argument('--refresh', action='store_true', help='rewrite --data from --diag and --m1 first')
    ap.add_argument('--diag', help='link_diag.py report.json')
    ap.add_argument('--m1', help='link_m1.py --out directory')
    a = ap.parse_args()
    if a.refresh:
        if not (a.diag and a.m1):
            ap.error('--refresh needs --diag and --m1')
        with open(a.data, 'w') as f:
            json.dump(refresh(a.diag, a.m1), f, indent=1, sort_keys=True)
            f.write('\n')
    s = json.load(open(a.data))
    os.makedirs(os.path.dirname(a.out), exist_ok=True)
    open(a.out, 'w').write(render(s))
    print('M0 unresolved %d; M1 unresolved %d; matched at retail address %d/%d -> %s' % (
        s['m0']['unresolved'], s['m1']['unresolved_after_stubs'], s['m1']['matched_at_retail_address'],
        s['m1']['matched_functions'], a.out))


if __name__ == '__main__':
    main()
