#!/usr/bin/env bash
# fetch_jwasm.sh — build the open-source MASM replacement (JWasm) used when ml.exe is absent (CI).
#
# JWasm is under the Sybase Open Watcom Public Licence 1.0. It is fetched and built here at
# build/CI time into toolchain/ (.gitignore'd) and is never committed or redistributed.
# Pinned commit; rebuilt only when toolchain/bin/jwasm is missing or was built from another pin.
set -euo pipefail
REPO="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
TC="$REPO/toolchain"
PIN=a5c4ea03cc0545a15d81a354251b5f534bef7a1b
URL="${JWASM_URL:-https://github.com/JWasm/JWasm.git}"
SRC="$TC/src/jwasm"
BIN="$TC/bin/jwasm"
STAMP="$TC/bin/jwasm.pin"

if [[ -x "$BIN" && "$(cat "$STAMP" 2>/dev/null)" == "$PIN" ]]; then
  echo "fetch_jwasm: $BIN already built at $PIN, skipping."
  exit 0
fi

mkdir -p "$TC/src" "$TC/bin"
if [[ ! -d "$SRC/.git" ]]; then
  git init -q "$SRC"
  git -C "$SRC" remote add origin "$URL"
fi
git -C "$SRC" fetch -q --depth 1 origin "$PIN"
git -C "$SRC" checkout -q --detach FETCH_HEAD
[[ "$(git -C "$SRC" rev-parse HEAD)" == "$PIN" ]] || { echo "fetch_jwasm: pin mismatch" >&2; exit 1; }

# -std=gnu99: gcc >= 15 defaults to C23, where `bool` is a keyword.
make -C "$SRC" -f GccUnix.mak CC='gcc -std=gnu99 -w' -j"$(nproc 2>/dev/null || echo 2)"
install -D "$SRC/GccUnixR/jwasm" "$BIN"
printf %s "$PIN" >"$STAMP"
echo "fetch_jwasm: installed $BIN ($PIN)"
