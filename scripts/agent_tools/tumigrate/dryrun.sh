#!/bin/bash
# Apply every listed TU in sequence to a scratch tree, then compile; reports per-TU compile errors.
set -u
T=$(dirname "$(readlink -f "$0")")
TREE=$1; OUT=$2; shift 2
mkdir -p "$OUT/plans"
for tu in "$@"; do
  python3 "$T/migrate.py" plan --tree "$TREE" --tu "$tu" > "$OUT/plans/$tu.json" || { echo "PLANFAIL $tu"; continue; }
  python3 "$T/migrate.py" apply --tree "$TREE" --plan "$OUT/plans/$tu.json" > "$OUT/plans/$tu.applied.json" || echo "APPLYFAIL $tu"
done
