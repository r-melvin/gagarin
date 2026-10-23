#!/usr/bin/env bash
# vc6cl.sh — drive the period Microsoft Visual C++ 6.0 compiler under Wine.
#
# This is the reproducible period-toolchain entry point for the matching-decomp
# build (AGENTS.md "Toolchain" / plan P0.2). The toolchain itself is
# MS-proprietary and is NEVER committed: it is fetched into $VC6_ROOT at
# build/CI time (itsmattkc/MSVC600) and .gitignore'd.
#
# Identified compiler (this tree):
#   cl.exe   12.00.8804  (VC6 SP5 + Processor Pack backend)
#   link.exe  6.00.8447  (SP5 incremental linker)
# See docs/toolchain_evidence.md for how this reconciles with the retail binary.
#
# Usage:
#   scripts/vc6/vc6cl.sh [extra cl flags] <file.cpp> -- [extra args]
#   VC6_FLAGS="/O2 /DNDEBUG ..." scripts/vc6/vc6cl.sh src/foo.cpp
#
# Env:
#   VC6_ROOT   path to the MSVC600 install   (default: <repo>/toolchain/MSVC600)
#   WINEPREFIX wine prefix                    (default: <repo>/toolchain/wineprefix)
#   VC6_FLAGS  cl flag set being bisected/locked (default: the P0 hypothesis)
set -euo pipefail

REPO="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
VC6_ROOT="${VC6_ROOT:-$REPO/toolchain/MSVC600}"
export WINEPREFIX="${WINEPREFIX:-$REPO/toolchain/wineprefix}"
export WINEDEBUG="${WINEDEBUG:--all}"
# Headless/software GL so the compiler runs cleanly in CI and over SSH.
export MESA_LOADER_DRIVER_OVERRIDE="${MESA_LOADER_DRIVER_OVERRIDE:-swrast}"
export LIBGL_ALWAYS_SOFTWARE=1

VC98="$VC6_ROOT/VC98"
MSDEV="$VC6_ROOT/Common/MSDev98"
if [[ ! -f "$VC98/Bin/CL.EXE" ]]; then
  echo "vc6cl: CL.EXE not found under VC6_ROOT=$VC6_ROOT" >&2
  echo "       fetch itsmattkc/MSVC600 into that path (never commit it)." >&2
  exit 2
fi

# cl.exe needs MSPDB60.DLL from Common\MSDev98\Bin on PATH, plus VC98\Bin.
export WINEPATH="$VC98/Bin;$MSDEV/Bin"
export INCLUDE="$VC98/Include"
export LIB="$VC98/Lib"

# Locked/bisected flag set. P0.5 bisects this against the leaf cluster, then
# pins it here once the bytes match.
DEFAULT_FLAGS="/nologo /c /O2 /Gr /DNDEBUG /Gy"

# Per-TU flag override. A translation unit whose retail bytes are only
# reproducible under a different flag set declares it on a single line near the
# top of the file:
#
#     // VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /Ob2
#
# The marker must explain itself in the comment beside it, because departing
# from the locked set is a claim about the retail build and not a convenience.
# Every tool that compiles through this script — match.sh, match_all.sh,
# verify_all.py — inherits the override automatically, so a TU cannot score
# differently in the gate than it did in the inner loop. An explicit VC6_FLAGS
# in the environment still wins, which is what flag bisection relies on.
TU_FLAGS=""
for arg in "$@"; do
  case "$arg" in
    /*|-*) ;;
    *.cpp|*.c|*.cxx|*.cc)
      if [[ -f "$arg" ]]; then
        line="$(grep -m1 -E '^[[:space:]]*//[[:space:]]*VC6FLAGS:' "$arg" || true)"
        if [[ -n "$line" ]]; then
          TU_FLAGS="${line#*VC6FLAGS:}"
        fi
      fi
      ;;
  esac
done

if [[ -n "${VC6_FLAGS:-}" ]]; then
  FLAGS="$VC6_FLAGS"
elif [[ -n "$TU_FLAGS" ]]; then
  FLAGS="$TU_FLAGS"
else
  FLAGS="$DEFAULT_FLAGS"
fi

# VC6_EXTRA_FLAGS is appended to whichever set was chosen (default, per-TU or
# VC6_FLAGS). It exists for whole-tree flag experiments such as the /ML vs /MT
# check (scripts/vc6/crt_flag_check.py); it is never set in a normal build.
exec wine "$VC98/Bin/CL.EXE" $FLAGS ${VC6_EXTRA_FLAGS:-} "$@"
