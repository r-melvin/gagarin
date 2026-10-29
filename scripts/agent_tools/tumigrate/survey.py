#!/usr/bin/env python3
"""Survey: for each assert-named TU, which manifest rows/files fall in its range."""
import csv, json, os, sys, collections, re
TUMAP = os.environ.get('GAG_TUMAP') or os.path.join(os.environ.get('GAG_SCRATCH_ROOT') or os.path.join(os.path.dirname(os.path.abspath(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..', '..', '..'))), 'gagarin-scratch'), 'tumap2/tu_map_v2.csv')
def load(tree):
    m = json.load(open(f'{tree}/scripts/data/match_manifest.json'))
    tus = [x for x in csv.DictReader(open(TUMAP)) if x['name_confidence'] == 'assert']
    return m, tus
def rows_in(m, lo, hi):
    return [r for r in m if lo <= int(r['addr'], 16) <= hi]
def main(tree):
    m, tus = load(tree)
    byfile = collections.defaultdict(list)
    for r in m: byfile[r['tu']].append(int(r['addr'], 16))
    out = []
    for t in tus:
        lo, hi = int(t['text_lo'], 16), int(t['text_hi'], 16)
        rs = rows_in(m, lo, hi)
        if not rs: continue
        files = collections.Counter(r['tu'] for r in rs)
        info = []
        whole = 0
        for f, n in files.most_common():
            tot = len(byfile[f]); info.append((f, n, tot)); whole += (n == tot)
        out.append(dict(tu=t['tu_id'], name=t['name_or_bound'], lo=t['text_lo'], hi=t['text_hi'],
                        hi_earliest=t['hi_earliest'], sub=t['sub_index'], nrows=len(rs),
                        nmatched=sum(r['status']=='matched' for r in rs), files=info, whole=whole))
    return out
if __name__ == '__main__':
    out = main(sys.argv[1])
    json.dump(out, open(sys.argv[2], 'w'), indent=1)
    for o in out:
        print(o['tu'], o['name'], o['nrows'], 'files', len(o['files']), 'whole', o['whole'])
        for f, n, tot in o['files']: print('   ', n, '/', tot, f)
