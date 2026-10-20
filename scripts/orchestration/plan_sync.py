#!/usr/bin/env python3
"""plan_sync.py — rewrite the phase-three counters in the plan from the manifest.

Keeps docs/matching_decomp_plan.md honest: the matched count, the partial
count, the annotated total and the translation-unit count are derived from
scripts/data/match_manifest.json rather than hand-edited, so they cannot drift.

Run after every integrate.py.
"""
import json,os,re,collections
R=os.path.join(os.path.dirname(os.path.abspath(__file__)),'..','..','')
man=json.load(open(R+'scripts/data/match_manifest.json'))
c=collections.Counter(e['status'] for e in man)
tus=len({e['tu'] for e in man})
p=R+'docs/matching_decomp_plan.md'; s=open(p).read()
s2=re.sub(r'\*\*\d+ functions byte-matched\*\* across \d+ TUs', f'**{c["matched"]} functions byte-matched** across {tus} TUs', s)
s2=re.sub(r'\d+ documented partials', f'{c["partial"]} documented partials', s2)
s2=re.sub(r'\d+ annotated in total', f'{len(man)} annotated in total', s2)
open(p,'w').write(s2)
print(dict(c), "tus", tus, "changed", s!=s2)
