#!/usr/bin/env python3
# SPDX-Provenance: original
#
# link_svg.py — render the README link-milestone graphic from
# scripts/data/link_progress.json. Needs no retail binary.
#
# Refresh the data from the link tools' output, then render:
#   link_svg.py --refresh --diag D/report.json --m1 M1DIR [--m1-pinned DIR]
#               [--m2a m2a.json] [--m2-hybrid DIR] [--m3 DIR]
#     D      link_diag.py --out directory (report.json)
#     M1DIR  link_m1.py --out directory (link_report.json, mapcheck.json,
#            stubs/plan.json, m1.map)
#     --m1-pinned DIR  link_m1.py --pin-data --order-tail --out directory (mapcheck.json)
#     --m2a F          m2a_overlay.py --json output for that pinned link
#     --m2-hybrid DIR  directory holding compare.json (compare_image.py --json) of the
#                      --hybrid image
#     --m3 DIR         directory holding compare.json of the --hybrid --source-data
#                      --search-literals --distribution-patches image (with origins)
#   Optional inputs left out keep the figures already in the data file.
#   link_svg.py [out.svg] [--data F]
#   (default out: .github/assets/link_progress.svg)

import argparse
import json
import os
import subprocess
import sys

ROOT = os.path.normpath(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..', '..'))
DATA = os.path.join(ROOT, 'scripts/data/link_progress.json')
W = 720

# Milestones and the states --refresh writes into the data file (render reads the
# data file only); the identity definition (M5) is the one in AGENTS.md: the
# complete unsigned image equals the pinned retail file.
MILESTONES = [
    ('M0', 'Diagnostic link', 'done'),
    ('M1', 'Address-faithful stub link', 'done'),
    ('M2', 'Hybrid runnable build', 'done'),
    ('M3', 'Matched objects swap in', 'next'),
    ('M4', 'Pure-source playable', 'todo'),
    ('M5', 'Unsigned image identical', 'todo'),
]


def refresh(diag, m1dir, m2a=None, m1_pinned=None, m3=None, m2_hybrid=None, previous=None):
    """Collect the figures from link_diag.py and link_m1.py output (and the optional M2/M3 inputs).

    Sections whose inputs are not given are carried over from `previous` (the old data)."""
    sys.path.insert(0, os.path.join(ROOT, 'scripts/vc6'))
    import mapcheck
    d = json.load(open(diag))
    rep = json.load(open(os.path.join(m1dir, 'link_report.json')))
    chk = json.load(open(os.path.join(m1dir, 'mapcheck.json')))
    plan = json.load(open(os.path.join(m1dir, 'stubs/plan.json')))['placed']
    publics, _ = mapcheck.parse_map(open(os.path.join(m1dir, 'm1.map'), encoding='latin-1').read())
    at = [p for p in plan if publics.get(p['symbol']) == int(p['addr'], 16)]
    out = {
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
    previous = previous or {}
    m2 = dict(previous.get('m2') or {})
    if m1_pinned:
        pc = json.load(open(os.path.join(m1_pinned, 'mapcheck.json')))
        m2['pinned_drift_events'] = pc['drift_events']
        m2['pinned_entry_point_delta'] = pc['landmarks']['entry point (WinMainCRTStartup)']['delta']
    if m2a:
        r = json.load(open(m2a))
        m2.update({'matched_rows': r['matched_rows'], 'identical_in_place': r['identical'],
                   'differ': r['differ'], 'differ_with_other_bytes': r['differ_with_other_bytes'],
                   'missing': len(r['missing'])})
    if m2_hybrid:
        c = json.load(open(os.path.join(m2_hybrid, 'compare.json')))
        m2['hybrid_sections_identical'] = bool(c['identical'])
        m2['hybrid_sections'] = {n: {'diff_bytes': v['diff_bytes'], 'size_equal': v['vsize'] == v['retail_vsize']}
                                 for n, v in c['sections'].items()}
    if m2:
        out['m2'] = m2
    m3d = previous.get('m3')
    if m3:
        c = json.load(open(os.path.join(m3, 'compare.json')))
        if not c.get('origins'):
            raise SystemExit('link_svg: %s/compare.json has no origins (run compare_image.py with the placement.json)' % m3)
        secs = {n: dict(o, diff_bytes=c['sections'][n]['diff_bytes'], va=c['sections'][n].get('va', 0)) for n, o in c['origins'].items()}
        tot = {k: sum(o[k] for o in secs.values()) for k in ('vsize', 'project', 'library', 'retail', 'diff_bytes')}
        m3d = {'sections': secs, 'total': tot, 'identical': bool(c['identical'])}
    if m3d:
        out['m3'] = m3d
    # Source snapshot (git HEAD short hash) each refreshed stage was measured at.
    try:
        head = subprocess.run(['git', '-C', ROOT, 'rev-parse', '--short', 'HEAD'], capture_output=True,
                              text=True, check=True).stdout.strip()
    except (OSError, subprocess.CalledProcessError):
        head = None
    snaps = dict(previous.get('snapshots') or {})
    for key, given in (('m0', True), ('m1', True), ('m2', m2a or m2_hybrid or m1_pinned), ('m3', m3)):
        if given and head:
            snaps[key] = head
    if snaps:
        out['snapshots'] = snaps
    return out


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
    m2, m3 = s.get('m2'), s.get('m3')
    if m2 and 'identical_in_place' in m2:
        y += 8
        out.append(bar(y, 'M2: matched functions byte-identical to retail in place (--pin-data --order-tail)',
                       m2['identical_in_place'], m2['matched_rows'],
                       f"{m2['identical_in_place']:,} of {m2['matched_rows']:,} matched rows · "
                       f"{m2['differ']:,} differ ({m2['differ_with_other_bytes']:,} beyond displaced addresses) · "
                       f"entry point {m2.get('pinned_entry_point_delta', 0):+,} bytes · "
                       f"{m2.get('pinned_drift_events', 0)} drift events"))
        y += 70
    if m2 and 'hybrid_sections' in m2:
        secs = m2['hybrid_sections']
        same = [n for n, v in secs.items() if v['diff_bytes'] == 0 and v['size_equal']]
        verdict = 'all equal retail' if len(same) == len(secs) else f'{len(same)} of {len(secs)} equal retail'
        out.append(f'<text x="24" y="{y}" class="label">M2: --hybrid image sections ({verdict})</text>')
        out.append(f'<text x="24" y="{y + 18}" class="note">' + ' · '.join(
            f"{n} {'identical' if n in same else str(v['diff_bytes']) + ' bytes differ'}"
            for n, v in secs.items()) + '</text>')
        y += 46
    if m3:
        t = m3['total']
        y += 4
        out.append(f'<text x="24" y="{y}" class="label">M3: virtual size from source, library and retail fill</text>')
        out.append(f'<text x="{W - 24}" y="{y}" class="pct" text-anchor="end">{100.0 * t["project"] / t["vsize"]:.2f}% source</text>')
        y += 12
        x0, bw = 80, W - 24 - 80 - 210
        for name, c in sorted(m3['sections'].items(), key=lambda kv: kv[1].get('va', 0)) + [('total', t)]:
            v = c['vsize'] or 1
            wp, wl = bw * c['project'] / v, bw * c['library'] / v
            out.append(f'<text x="24" y="{y + 12}" class="note">{name}</text>'
                       f'<rect x="{x0}" y="{y + 2}" width="{bw}" height="12" rx="6" class="track"/>'
                       f'<rect x="{x0}" y="{y + 2}" width="{max(wp, 0):.1f}" height="12" rx="6" class="done"/>'
                       f'<rect x="{x0 + wp:.1f}" y="{y + 2}" width="{wl:.1f}" height="12" class="warn"/>'
                       f'<text x="{x0 + bw + 8}" y="{y + 12}" class="note">'
                       f'{c["project"]:,} / {c["library"]:,} / {c["retail"]:,}</text>')
            y += 20
        out.append(f'<text x="24" y="{y + 10}" class="note">source / library / retail fill, bytes of {t["vsize"]:,} · '
                   f'{t["diff_bytes"]:,} differing section bytes</text>')
        y += 28
    out.append(f'<text x="24" y="{y}" class="note">Layout probe: stub bodies are int3; default M1 entry point '
               f'{m1["entry_point_delta"]:+,} bytes from retail'
               + (f', {m2["pinned_entry_point_delta"]:+,} with --order-tail.' if m2 and 'pinned_entry_point_delta' in m2 else '.')
               + '</text>')
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
    ap.add_argument('--m1-pinned', help='link_m1.py --pin-data --order-tail --out directory')
    ap.add_argument('--m2a', help='m2a_overlay.py --json output')
    ap.add_argument('--m2-hybrid', help='directory with compare.json of the --hybrid image')
    ap.add_argument('--m3', help='directory with compare.json of the M3 image (with origins)')
    a = ap.parse_args()
    if a.refresh:
        if not (a.diag and a.m1):
            ap.error('--refresh needs --diag and --m1')
        previous = json.load(open(a.data)) if os.path.exists(a.data) else None
        with open(a.data, 'w') as f:
            json.dump(refresh(a.diag, a.m1, a.m2a, a.m1_pinned, a.m3, a.m2_hybrid, previous), f, indent=1, sort_keys=True)
            f.write('\n')
    s = json.load(open(a.data))
    os.makedirs(os.path.dirname(a.out), exist_ok=True)
    open(a.out, 'w').write(render(s))
    print('M0 unresolved %d; M1 unresolved %d; matched at retail address %d/%d -> %s' % (
        s['m0']['unresolved'], s['m1']['unresolved_after_stubs'], s['m1']['matched_at_retail_address'],
        s['m1']['matched_functions'], a.out))


if __name__ == '__main__':
    main()
