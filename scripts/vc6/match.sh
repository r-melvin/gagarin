#!/usr/bin/env bash
# match.sh — one-shot per-function inner loop: compile a TU under VC6 and diff
# the named function against retail gamemd.exe (reloc-normalised). The P3 loop.
#
# Usage:
#   scripts/vc6/match.sh <source.cpp> <mangled-symbol> <retail-addr-hex> <len-hex>
#
# Example:
#   scripts/vc6/match.sh match/economy/storage_class.cpp \
#       '?GetTotalValue@StorageClass@@QBEHXZ' 0x6C9600 0x4f
set -euo pipefail
REPO="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
SRC="$1"; SYM="$2"; ADDR="$3"; LEN="$4"
OUT="$REPO/build-vc6"; mkdir -p "$OUT"
ABS_SRC="$(cd "$(dirname "$SRC")" && pwd)/$(basename "$SRC")"
OBJ="$OUT/$(basename "${SRC%.*}").obj"

# Compile in the source's own dir so relative includes resolve; emit obj to OUT.
# Remove any previous object first: a failed compile used to leave the old one
# in place and the diff below then silently scored STALE BYTES. Three files sat
# uncompilable in the tree reporting their previous percentages because of it.
rm -f "$OBJ"

CL_LOG="$(mktemp)"
( cd "$(dirname "$ABS_SRC")" && bash "$REPO/scripts/vc6/vc6cl.sh" \
    /Fo"$OBJ" "$(basename "$ABS_SRC")" ) > "$CL_LOG" 2>&1 || true
grep -iv "libEGL\|pci id\|dri2\|wineusb\|fixme:" "$CL_LOG" || true

if grep -qiE "error|fatal" "$CL_LOG" || [ ! -f "$OBJ" ]; then
  echo "COMPILE FAIL $SRC — not scoring (see above)" >&2
  rm -f "$CL_LOG"
  exit 2
fi
rm -f "$CL_LOG"

python3 "$REPO/scripts/vc6/diff_retail.py" --obj "$OBJ" --sym "$SYM" \
    --addr "$ADDR" --len "$LEN"
