#!/usr/bin/env bash
# verify_batch.sh <batch.json> — re-prove every percentage an agent claimed.
#
# THE RULE THIS ENFORCES: no number reported by a subagent enters the manifest
# until it has been re-measured here against the user's own retail binary. Over
# a long session this has caught wrong symbols, wrong lengths, stale documented
# percentages (three times) and one batch scored against the wrong object file.
#
# It compiles the REAL translation unit, not a scratch clone, which matters:
# the number of functions in a file changes the compiler's cross-jumping, so a
# body can score differently alone than beside its siblings.
#
# Falls back to raw_match.py when diff_retail.py cannot produce a score, which
# happens for the many addresses the Ghidra analysis does not list at all.
#
# Input JSON: a list of {tu, addr, sym, len, name, status, pct}; len is HEX.
cd "$(dirname "$0")/../.."
python3 -c "
import json,sys
for e in json.load(open('$1')): print(e['tu'], e['sym'], e['addr'], e['len'], e['pct'])
" | while read tu sym addr len pct; do
  got=$(bash scripts/vc6/match.sh "$tu" "$sym" "$addr" "$len" 2>/dev/null | grep '^match:' | awk '{print $2}')
  if [ -z "$got" ]; then
    obj="build-vc6/$(basename "${tu%.cpp}").obj"
    got=$(python3 scripts/vc6/raw_match.py --obj "$obj" --sym "$sym" --addr "$addr" --len "$len" 2>/dev/null | grep '^match:' | awk '{print $2}')
    [ -n "$got" ] && got="$got(raw)"
  fi
  echo "$addr $tu claimed=$pct got=${got:-FAIL}"
done
