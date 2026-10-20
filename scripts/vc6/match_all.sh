#!/usr/bin/env bash
# match_all.sh <src.cpp> <triples.txt>
#
# Compile one TU once with the period VC6 toolchain, then score every function
# in it against the user's retail gamemd.exe. The triples file carries one
# `<mangled-sym> <retail-addr> <len>` per line (blank lines and # comments
# ignored). Prints one `addr sym pct` line per function and a final tally.
#
# This is match.sh's batch form. match.sh recompiles per function, which costs
# a full Wine compile for every address; a TU holding N related functions only
# needs one. Reading N sibling diffs from one compile is also how a family's
# single phrasing lever becomes visible.
set -u
ROOT="$(cd "$(dirname "$0")/../.." && pwd)"
SRC="$1"; TRIPLES="$2"
# A fixed object path collides when two agents score the same TU at once, and a
# collision scores one agent's functions against the other's object, which
# looks like a total mismatch rather than a clash. Keep it per-process.
OBJ="$(mktemp -t "ma_$(basename "${SRC%.cpp}")_XXXXXX").obj"
trap 'rm -f "$OBJ"' EXIT
( cd "$(dirname "$SRC")" && bash "$ROOT/scripts/vc6/vc6cl.sh" "/Fo$OBJ" "$(basename "$SRC")" ) >/dev/null
if [ ! -f "$OBJ" ]; then echo "COMPILE FAIL $SRC" >&2; exit 2; fi
ok=0; n=0
while read -r sym addr len; do
    case "$sym" in ''|\#*) continue;; esac
    n=$((n+1))
    pct=$(python3 "$ROOT/scripts/vc6/diff_retail.py" --obj "$OBJ" --sym "$sym" \
          --addr "$addr" --len "$len" 2>/dev/null | sed -n 's/^match: //p')
    if [ "$pct" != "100.0%" ]; then
        raw=$(python3 "$ROOT/scripts/vc6/raw_match.py" --obj "$OBJ" --sym "$sym" \
              --addr "$addr" --len "$len" 2>/dev/null | sed -n 's/^match: //p')
        [ "$raw" = "100.0%" ] && pct="$raw"
    fi
    [ "$pct" = "100.0%" ] && ok=$((ok+1))
    printf '%s %s %s\n' "$addr" "$sym" "${pct:-?}"
done < "$TRIPLES"
echo "=== $ok / $n at 100% ==="
