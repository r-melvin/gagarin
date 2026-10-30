#!/usr/bin/env bash
# vc6asm.sh — assemble hand-written assembly with the period MASM (ml.exe 6.15) under Wine.
#
# Sibling of vc6cl.sh (same toolchain root, WINEPREFIX/WINEPATH and the checkout-independent
# source alias). Used only for the .asm translation units under match/asm/, which recover
# routines that were hand-written assembly in the original (AGENTS.md "Hand-written assembly").
# After assembling, comdatize.py marks the .text section COMDAT (selection ANY) so that LINK can
# place the object through /ORDER; ml has no option for it.
#
# Assembler selection: ml.exe under Wine when present (default; local gates unchanged). When it
# is absent, or VC6_ASM=jwasm, toolchain/bin/jwasm (built by fetch_jwasm.sh; override with
# VC6_JWASM) is used with `-coff -c -Zg` ("-Zg" = output matches Masm). JWasm is byte- and
# relocation-identical to ml on the project units; known divergences are `cmp r8,r8` and
# `movq mm,mm` encodings. Do not feed JWasm objects to local ByteMatch accounting when ml is
# available. Exit 77 only if neither assembler exists.
#
# Usage: scripts/vc6/vc6asm.sh [/Fo<obj>] [extra ml flags] <file.asm>
# Env:   VC6_ROOT, WINEPREFIX as for vc6cl.sh; VC6_ASM=ml|jwasm; VC6_JWASM=<path>.
set -euo pipefail

REPO="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
VC6_ROOT="${VC6_ROOT:-$REPO/toolchain/MSVC600}"
export WINEPREFIX="${WINEPREFIX:-$REPO/toolchain/wineprefix}"
export WINEDEBUG="${WINEDEBUG:--all}"
export MESA_LOADER_DRIVER_OVERRIDE="${MESA_LOADER_DRIVER_OVERRIDE:-swrast}"
export LIBGL_ALWAYS_SOFTWARE=1

VC98="$VC6_ROOT/VC98"
MSDEV="$VC6_ROOT/Common/MSDev98"
JW="${VC6_JWASM:-$REPO/toolchain/bin/jwasm}"
HAVE_ML=0; [[ -f "$VC98/Bin/ml.exe" || -f "$VC98/Bin/ML.EXE" ]] && HAVE_ML=1
case "${VC6_ASM:-}" in
  ml)    ASM=ml ;;
  jwasm) ASM=jwasm ;;
  "")    if [[ $HAVE_ML = 1 ]]; then ASM=ml; else ASM=jwasm; fi ;;
  *)     echo "vc6asm: VC6_ASM must be ml or jwasm" >&2; exit 2 ;;
esac
if [[ $ASM = ml && $HAVE_ML = 0 ]] || [[ $ASM = jwasm && ! -x "$JW" ]]; then
  echo "vc6asm: no usable assembler ($ASM): ml.exe under VC6_ROOT=$VC6_ROOT, jwasm at $JW (scripts/vc6/fetch_jwasm.sh)" >&2
  exit 77   # distinct code: callers may skip .asm units when no MASM-compatible assembler exists
fi

if [[ $ASM = jwasm ]]; then
  OBJ=""; SRC=""
  for arg in "$@"; do
    case "$arg" in
      /Fo*) OBJ="${arg#/Fo}" ;;
      *.asm|*.ASM) SRC="$arg" ;;
      /*|-*) ;;   # ml-only flags (ML_EXTRA_FLAGS is not honoured either)
    esac
  done
  [[ -n "$SRC" ]] || { echo "vc6asm: no .asm source given" >&2; exit 2; }
  [[ -n "$OBJ" ]] || OBJ="$(basename "${SRC%.*}").obj"
  OBJ="$(cd "$(dirname "$OBJ")" && pwd)/$(basename "$OBJ")"
  # The source path reaches the object (.file record): assemble from its own directory by
  # basename so the object does not depend on the checkout location.
  ( cd "$(dirname "$SRC")" && "$JW" -nologo -coff -c -Zg -Fo"$OBJ" "$(basename "$SRC")" )
  echo "vc6asm: assembled with jwasm" >&2
  exec python3 "$REPO/scripts/vc6/comdatize.py" "$OBJ"
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
    *.asm|*.ASM)   # before /*: an absolute source path also starts with /
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
[[ -n "$OBJ" ]] || OBJ="$(basename "${SRC%.*}").obj"

wine "$ML" $FLAGS ${ML_EXTRA_FLAGS:-} "${ARGS[@]}"
exec python3 "$REPO/scripts/vc6/comdatize.py" "$OBJ"
