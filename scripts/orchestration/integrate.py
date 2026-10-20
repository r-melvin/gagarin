#!/usr/bin/env python3
"""integrate.py <batch.json> — merge VERIFIED entries into scripts/data/match_manifest.json.

Run this only after scripts/orchestration/verify_batch.sh has re-proved every
percentage in the batch. Existing entries are updated in place when their
percentage or status changed, so a lift pass records movement rather than
duplicating a row; genuinely new addresses are appended. The manifest is kept
sorted by translation unit then address.

The manifest is the project's source of truth for what is matched, and
scripts/vc6/verify_all.py re-proves every row in it.
"""
import json,os,sys
p=os.path.join(os.path.dirname(os.path.abspath(__file__)),'..','data','match_manifest.json')
man=json.load(open(p))
have={int(e['addr'],16):e for e in man}
new=json.load(open(sys.argv[1]))
added=0
for e in new:
    old=have.get(int(e['addr'],16))
    if old is not None:
        # Compare EVERY field, not just pct/status. A refactor that leaves the
        # bytes untouched still changes 'sym' (the mangled name moves when a
        # free function becomes a member, or a body becomes a template
        # instantiation) and 'tu' (a body moves file). Watching only pct and
        # status silently skipped all 335 rows of the vector-template
        # conversion, which would have left the manifest naming symbols that no
        # longer exist in the object and made verify_all.py report 335 failures.
        changed = [k for k in e if old.get(k) != e[k]]
        if changed:
            print("update", e['addr'], ','.join(changed)); old.update(e)
        else:
            print("skip dup", e['addr'])
        continue
    man.append(e); added+=1
man.sort(key=lambda e:(e['tu'],int(e['addr'],16)))
json.dump(man,open(p,'w'),indent=1); open(p,'a').write('\n')
m=sum(1 for e in man if e['status']=='matched'); print(f"added {added}; total {len(man)} annotated, {m} matched")
