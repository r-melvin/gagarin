#!/usr/bin/env python3
# SPDX-Provenance: original
#
# progress_svg.py — render the README progress graphic from the match manifest
# and the binary-derived totals. Needs no retail binary.
#
#   matched / partial  -> scripts/data/match_manifest.json
#   totals             -> scripts/data/progress_totals.json
#
# Usage: progress_svg.py [out.svg]   (default .github/assets/progress.svg)

import json
import os
import sys
from collections import Counter

ROOT = os.path.normpath(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..', '..'))
W = 720


def stats():
    m = json.load(open(os.path.join(ROOT, 'scripts/data/match_manifest.json')))
    t = json.load(open(os.path.join(ROOT, 'scripts/data/progress_totals.json')))
    matched = [r for r in m if r['status'] == 'matched']
    return {
        'matched': len(matched),
        'partial': sum(1 for r in m if r['status'] == 'partial'),
        'bytes': sum(int(r['len'], 16) for r in matched),
        'total': t['functions'],
        'total_bytes': t['code_bytes'],
        'subsystems': Counter(r['tu'].split('/')[1] for r in matched).most_common(),
    }


def bar(y, label, done, part, total, note):
    x, w, h = 24, W - 48, 18
    dw = w * done / total
    pw = w * part / total
    pct = 100.0 * done / total
    return (
        f'<text x="{x}" y="{y}" class="label">{label}</text>'
        f'<text x="{W - 24}" y="{y}" class="pct" text-anchor="end">{pct:.1f}%</text>'
        f'<rect x="{x}" y="{y + 8}" width="{w}" height="{h}" rx="9" class="track"/>'
        f'<rect x="{x}" y="{y + 8}" width="{dw + pw:.1f}" height="{h}" rx="9" class="partial"/>'
        f'<rect x="{x}" y="{y + 8}" width="{dw:.1f}" height="{h}" rx="9" class="done"/>'
        f'<text x="{x}" y="{y + 44}" class="note">{note}</text>'
    )


def render(s):
    out = []
    y = 40
    out.append(f'<text x="24" y="{y}" class="title">gagarin — matching progress</text>')
    y += 36
    out.append(bar(y, 'Functions matched', s['matched'], s['partial'], s['total'],
                   f"{s['matched']:,} matched · {s['partial']:,} partial · {s['total']:,} in the binary"))
    y += 82
    out.append(bar(y, 'Code bytes matched', s['bytes'], 0, s['total_bytes'],
                   f"{s['bytes'] / 1024:,.0f} KB of {s['total_bytes'] / 1024:,.0f} KB in .text"))
    y += 82
    out.append(f'<text x="24" y="{y}" class="label">Matched functions by subsystem</text>')
    y += 14
    top = s['subsystems'][0][1]
    for name, n in s['subsystems']:
        w = (W - 48 - 110 - 60) * n / top
        out.append(f'<text x="24" y="{y + 12}" class="note">{name}</text>'
                   f'<rect x="134" y="{y + 2}" width="{max(w, 2):.1f}" height="12" rx="6" class="done"/>'
                   f'<text x="{134 + w + 8:.1f}" y="{y + 12}" class="note">{n:,}</text>')
        y += 20
    y += 16
    style = (
        '.bg{fill:#ffffff}.title{font:600 20px sans-serif;fill:#1f2328}'
        '.label{font:600 14px sans-serif;fill:#1f2328}.pct{font:600 14px monospace;fill:#1f2328}'
        '.note{font:12px sans-serif;fill:#59636e}.track{fill:#e6e8eb}'
        '.done{fill:#1a7f37}.partial{fill:#d4a72c}'
        '@media (prefers-color-scheme: dark){.bg{fill:#0d1117}.title,.label,.pct{fill:#e6edf3}'
        '.note{fill:#9198a1}.track{fill:#262c36}.done{fill:#3fb950}.partial{fill:#d29922}}'
    )
    return (f'<svg xmlns="http://www.w3.org/2000/svg" width="{W}" height="{y}" viewBox="0 0 {W} {y}" '
            f'role="img" aria-label="gagarin matching progress">'
            f'<style>{style}</style><rect width="{W}" height="{y}" rx="12" class="bg"/>'
            + ''.join(out) + '</svg>\n')


def main():
    out = sys.argv[1] if len(sys.argv) > 1 else os.path.join(ROOT, '.github/assets/progress.svg')
    os.makedirs(os.path.dirname(out), exist_ok=True)
    s = stats()
    open(out, 'w').write(render(s))
    print('%d/%d functions (%.1f%%), %d/%d bytes (%.1f%%) -> %s' % (
        s['matched'], s['total'], 100.0 * s['matched'] / s['total'],
        s['bytes'], s['total_bytes'], 100.0 * s['bytes'] / s['total_bytes'], out))


if __name__ == '__main__':
    main()
