#!/usr/bin/env bash
# vc6asm.sh — assemble hand-written assembly with the period MASM (ml.exe 6.15) under Wine.
#
# Sibling of vc6cl.sh (same toolchain root, WINEPREFIX/WINEPATH and the checkout-independent
# source alias). Used only for the .asm translation units under match/asm/, which recover
# routines that were hand-written assembly in the original (AGENTS.md "Hand-written assembly").
# After assembling, comdatize.py marks the .text section COMDAT (selection ANY) so that LINK can
# place the object through /ORDER; ml has no option for it.
#
# Usage: scripts/vc6/vc6asm.sh [/Fo<obj>] [extra ml flags] <file.asm>
# Env:   VC6_ROOT, WINEPREFIX as for vc6cl.sh.
set -euo pipefail

REPO="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
VC6_ROOT="${VC6_ROOT:-$REPO/toolchain/MSVC600}"
export WINEPREFIX="${WINEPREFIX:-$REPO/toolchain/wineprefix}"
export WINEDEBUG="${WINEDEBUG:--all}"
export MESA_LOADER_DRIVER_OVERRIDE="${MESA_LOADER_DRIVER_OVERRIDE:-swrast}"
export LIBGL_ALWAYS_SOFTWARE=1

VC98="$VC6_ROOT/VC98"
MSDEV="$VC6_ROOT/Common/MSDev98"
if [[ ! -f "$VC98/Bin/ml.exe" && ! -f "$VC98/Bin/ML.EXE" ]]; then
  echo "vc6asm: ml.exe not found under VC6_ROOT=$VC6_ROOT" >&2
  exit 2
fi
ML="$VC98/Bin/ml.exe"; [[ -f "$ML" ]] || ML="$VC98/Bin/ML.EXE"
export WINEPATH="$VC98/Bin;$MSDEV/Bin"

# Locked flag set: no per-file override exists or is needed.
FLAGS="/nologo /c /coff"

# Same fixed-length source alias as vc6cl.sh (the path strings reach the object).
ALIAS_BASE=/tmp
ARGS=()
OBJ=""
SRC=""
for arg in "$@"; do
  case "$arg" in
    /Fo*) OBJ="${arg#/Fo}"; ARGS+=("$arg") ;;
    /*|-*) ARGS+=("$arg") ;;
    *.asm)
      SRC="$arg"
      if [[ -f "$arg" ]]; then
        abs="$(cd "$(dirname "$arg")" && pwd)/$(basename "$arg")"
        if [[ "$abs" == "$REPO"/* ]]; then
          alias="$ALIAS_BASE/vc6-$(printf %s "$REPO" | md5sum | cut -c1-10)"
          [[ "$(readlink "$alias" 2>/dev/null)" == "$REPO" ]] || { ln -s "$REPO" "$alias.$$" && mv -T "$alias.$$" "$alias"; }
          abs="$alias${abs#"$REPO"}"
          abs="Z:${abs//\//\\}"
          ARGS+=("$abs")
          continue
        fi
      fi
      ARGS+=("$arg") ;;
    *) ARGS+=("$arg") ;;
  esac
done
[[ -n "$SRC" ]] || { echo "vc6asm: no .asm source given" >&2; exit 2; }
[[ -n "$OBJ" ]] || OBJ="$(basename "${SRC%.asm}").obj"

wine "$ML" $FLAGS ${ML_EXTRA_FLAGS:-} "${ARGS[@]}"
exec python3 "$REPO/scripts/vc6/comdatize.py" "$OBJ"
