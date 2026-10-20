#!/usr/bin/env bash
# fetch_toolchain.sh — fetch the period MSVC6 toolchain + init a Wine prefix.
#
# The toolchain is MS-proprietary and is NEVER committed (AGENTS.md Legal Scope);
# this script reproduces it at build/CI time into toolchain/ (.gitignore'd).
#
#   cl.exe 12.00.8804 (SP6 backend) + link.exe 6.00.8447 (SP5).
#   See docs/toolchain_evidence.md §2a for the build-number reconciliation.
set -euo pipefail
REPO="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
TC="$REPO/toolchain"
mkdir -p "$TC"

if [[ ! -f "$TC/MSVC600/VC98/Bin/CL.EXE" ]]; then
  echo "fetch: cloning itsmattkc/MSVC600 (shallow) ..."
  git clone --depth 1 https://github.com/itsmattkc/MSVC600.git "$TC/MSVC600"
else
  echo "fetch: MSVC600 already present, skipping."
fi

export WINEPREFIX="$TC/wineprefix"
export WINEDEBUG=-all MESA_LOADER_DRIVER_OVERRIDE=swrast LIBGL_ALWAYS_SOFTWARE=1
if [[ ! -f "$WINEPREFIX/drive_c/windows/system32/kernel32.dll" ]]; then
  echo "fetch: initialising Wine prefix at $WINEPREFIX ..."
  wineboot -i
  wineserver -w
fi

echo "fetch: verifying compiler ..."
M="$TC/MSVC600/VC98"; CM="$TC/MSVC600/Common/MSDev98"
WINEPATH="$M/Bin;$CM/Bin" wine "$M/Bin/CL.EXE" 2>/dev/null | grep -i version || true
echo "fetch: done. Build with scripts/vc6/vc6cl.sh"
