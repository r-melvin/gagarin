#!/usr/bin/env bash
# full_gates.sh [--tree WT] [--base REV] [gates.py options] : the full gates on one tree (what the bundle runs once).
here="$(dirname "$(readlink -f "${BASH_SOURCE[0]}")")"
args=("$@")
has() { for a in "${args[@]}"; do [ "$a" = "$1" ] && return 0; done; return 1; }
has --tree || args+=(--tree "$(git rev-parse --show-toplevel)")
has --base || args+=(--base HEAD)
exec python3 "$here/gates.py" --mode full "${args[@]}"
