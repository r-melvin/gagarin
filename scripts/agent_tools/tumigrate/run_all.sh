#!/bin/bash
# Fit every listed TU in sequence (WIP commit per TU) in TREE.
T=$(dirname "$(readlink -f "$0")")
TREE=$1; OUT=$2; shift 2
for tu in "$@"; do
  echo "=== $tu $(date +%T)"
  python3 "$T/fit.py" --tree "$TREE" --tu "$tu" --base-objs "$OUT/../base_objs" --base-manifest "$OUT/../base_manifest.json" --out "$OUT" $(for x in ${TUMIG_EXCL:-}; do echo --exclude "$x=order-dependent-stub-family:verify_all-regresses-when-split"; done) || echo "FITFAIL $tu"
done
