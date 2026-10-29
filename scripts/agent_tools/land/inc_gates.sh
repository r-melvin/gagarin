#!/usr/bin/env bash
# inc_gates.sh [--tree WT] [--base REV] [gates.py options] : incremental gates for packet prep.
# Defaults: tree = current directory's repo toplevel, base = HEAD (so staged/unstaged tracked changes
# and `git add`ed new files are the change under test). Untracked files are ignored.
here="$(dirname "$(readlink -f "${BASH_SOURCE[0]}")")"
args=("$@")
has() { for a in "${args[@]}"; do [ "$a" = "$1" ] && return 0; done; return 1; }
has --tree || args+=(--tree "$(git rev-parse --show-toplevel)")
has --base || args+=(--base HEAD)
exec python3 "$here/gates.py" --mode inc "${args[@]}"
