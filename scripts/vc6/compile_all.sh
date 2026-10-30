#!/usr/bin/env bash
# compile_all.sh — binary-free layout/compile regression gate.
#
# Compiles every matching TU under match/** and every P2 layout header (via a
# throwaway includer) with the period VC6 toolchain. Because the layout headers
# carry GG_STATIC_ASSERT offsetof/sizeof checks, a clean compile proves the whole
# class-layout spine still holds — WITHOUT needing the retail binary. This is the
# part of the P5 gate that CI can run on its own; the full per-function match
# (scripts/vc6/verify_all.py) additionally needs the user's gamemd.exe + Ghidra.
#
# Usage: scripts/vc6/compile_all.sh [--jobs N] [--changed [REF]]
# Exit 0 iff every TU and every layout header compiles clean.
# With python3 available the work runs in compile_all.py (parallel, deterministic
# report order). Without it (the CI image has no python3) the serial loop below
# runs; it takes no options.
if command -v python3 >/dev/null 2>&1; then
  exec python3 "$(dirname "${BASH_SOURCE[0]}")/compile_all.py" "$@"
fi
set -uo pipefail
REPO="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
cd "$REPO"
fail=0
tmp="$(mktemp -d)"; trap 'rm -rf "$tmp"' EXIT

# 1. Every matching TU.
while IFS= read -r tu; do
  d="$(dirname "$tu")"; f="$(basename "$tu")"
  if ( cd "$d" && bash "$REPO/scripts/vc6/vc6cl.sh" /Fo"$tmp/$f.obj" "$f" ) \
       >"$tmp/log" 2>&1 && [ -f "$tmp/$f.obj" ]; then
    echo "  ok   $tu"
  else
    echo "  FAIL $tu"; grep -iE "error|fatal" "$tmp/log" | grep -v libEGL | head -3
    fail=1
  fi
done < <(find match -name '*.cpp' -o -name '*.c' | sort)

# 2. Every P2 layout header (compile-check its asserts via a throwaway includer).
for h in match/_layout/*.h; do
  base="$(basename "$h" .h)"
  printf '#include "%s.h"\nint _chk_%s(){return 0;}\n' "$base" "$base" \
    > "match/_layout/_ca_$base.cpp"
  if ( cd match/_layout && bash "$REPO/scripts/vc6/vc6cl.sh" \
         /Fo"$tmp/$base.obj" "_ca_$base.cpp" ) >"$tmp/log" 2>&1 \
       && [ -f "$tmp/$base.obj" ]; then
    echo "  ok   $h (asserts pass)"
  else
    echo "  FAIL $h"; grep -iE "error" "$tmp/log" | grep -v libEGL | head -3
    fail=1
  fi
  rm -f "match/_layout/_ca_$base.cpp"
done

# 3. The reconstructed resource script (RC.EXE; the icon and cursor groups are not part of it).
if [ -f match/rsrc/gamemd.rc ]; then
  if ( cd match/rsrc && bash "$REPO/scripts/vc6/vc6rc.sh" /r /fo "$tmp/gamemd.res" gamemd.rc ) \
       >"$tmp/log" 2>&1 && [ -f "$tmp/gamemd.res" ]; then
    echo "  ok   match/rsrc/gamemd.rc (RC.EXE)"
  else
    echo "  FAIL match/rsrc/gamemd.rc"; grep -iE "error" "$tmp/log" | head -3
    fail=1
  fi
fi

[ "$fail" = 0 ] && echo "=== compile_all: ALL GREEN ===" || echo "=== compile_all: FAILURES ==="
exit "$fail"
