#!/usr/bin/env bash
# vc6rc.sh — drive the period Microsoft resource compiler (RC.EXE, VC6 SP5) under Wine.
#
# Same toolchain root and Wine prefix as vc6cl.sh. The toolchain is never committed.
#
# Usage:  scripts/vc6/vc6rc.sh [rc flags] file.rc      (e.g. /fo out.res)
# Runs in the directory of the script argument so relative #include and ICON paths resolve.
set -euo pipefail

REPO="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
VC6_ROOT="${VC6_ROOT:-$REPO/toolchain/MSVC600}"
export WINEPREFIX="${WINEPREFIX:-$REPO/toolchain/wineprefix}"
export WINEDEBUG="${WINEDEBUG:--all}"
export MESA_LOADER_DRIVER_OVERRIDE="${MESA_LOADER_DRIVER_OVERRIDE:-swrast}"
export LIBGL_ALWAYS_SOFTWARE=1

VC98="$VC6_ROOT/VC98"
MSDEV="$VC6_ROOT/Common/MSDev98"
if [[ ! -f "$MSDEV/Bin/RC.EXE" ]]; then
  echo "vc6rc: RC.EXE not found under VC6_ROOT=$VC6_ROOT" >&2
  exit 2
fi
export WINEPATH="$VC98/Bin;$MSDEV/Bin"
export INCLUDE="$VC98/Include"
export LIB="$VC98/Lib"
exec wine "$MSDEV/Bin/RC.EXE" "$@"
