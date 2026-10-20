#!/usr/bin/env bash
# vc6_compile.sh — decomp-permuter's compile step for this project.
#
# decomp-permuter invokes a run directory's ./compile.sh as
#     ./compile.sh <permuted.c> -o <candidate.o>
# This script is what that stub execs.  It splices the permuted C body into the
# run directory's C++ shim (see splice.py) and compiles the result with the
# period VC6 cl.exe under Wine, emitting an i386 COFF object that objdump — and
# therefore the permuter's own x86 scorer — reads directly.  No conversion of
# the object is needed: the permuter's target side is the ELF blob built by
# make_target.py, and objdump normalises both.
#
# Required environment (set by the run directory's compile.sh stub):
#   GG_RUNDIR  the run directory (holds shim.cpp.in)
#   GG_FUNC    the C function name in base.c whose body is spliced
#   GG_SYM     the MSVC-mangled symbol of the function in the compiled object
set -euo pipefail
REPO="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
SRC="$1"; shift
OUT=""
while [ $# -gt 0 ]; do
  case "$1" in
    -o) OUT="$2"; shift 2 ;;
    *) shift ;;
  esac
done
: "${GG_RUNDIR:?vc6_compile: GG_RUNDIR not set}"
: "${GG_FUNC:?vc6_compile: GG_FUNC not set}"
: "${GG_SYM:?vc6_compile: GG_SYM not set}"

WORK="$(mktemp -d)"
trap 'rm -rf "$WORK"' EXIT
CPP="$WORK/cand.cpp"
python3 "$REPO/scripts/permuter/splice.py" "$SRC" "$GG_RUNDIR/shim.cpp.in" \
        "$GG_FUNC" "$CPP"

# cl.exe is driven in the temp directory so nothing lands in the tree.
( cd "$WORK" && bash "$REPO/scripts/vc6/vc6cl.sh" /Fo"cand.obj" "cand.cpp" ) \
    > "$WORK/cl.log" 2>&1 || { grep -iE "error|fatal" "$WORK/cl.log" >&2 || true; exit 1; }
grep -qiE " error | fatal " "$WORK/cl.log" && { cat "$WORK/cl.log" >&2; exit 1; }
[ -f "$WORK/cand.obj" ] || exit 1

# Reduce the COFF object to the same byte-blob form as target.o (see
# obj_to_blob.py) so the scorer never sees alignment padding as insertions.
python3 "$REPO/scripts/permuter/obj_to_blob.py" "$WORK/cand.obj" "$GG_SYM" "$OUT"
