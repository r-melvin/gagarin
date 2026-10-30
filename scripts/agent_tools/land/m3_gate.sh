#!/usr/bin/env bash
# m3_gate.sh: the full M3 landing gate for one worktree, as one command.
#
#   m3_gate.sh WORKTREE [--full] [--jobs N] [--out DIR] [--link-progress]
#
# Steps, in order (each runs even if an earlier one failed; every rc is recorded):
#   prebuild      build_project.py --out build-vc6/gate
#   link_diag     link_diag.py --objdir build-vc6/gate --out build-vc6/svg-diag
#   compile       compile_all.sh [--changed]            (--changed unless --full)
#   verify        verify_all.py  [--changed]
#   build         build_project.py --out build-vc6/gate
#   link_m3       link_m1.py --hybrid --pin-data --order-tail --source-data --search-literals
#                   --distribution-patches --rsrc-from-project --rsrc-art-from-retail
#   compare       compare_image.py --placement .../placement.json --json .../compare.json
#   duplicates    check_duplicates.py
#   unittests     python3 -m unittest discover -s scripts/vc6   (GAMEMD_BINARY unset, as the gate does)
# --link-progress also runs the M1 link and refreshes link_progress (tracked files). It never touches scripts/data/link_progress.json or the progress SVGs unless --link-progress is
# given, and it commits and pushes nothing. Logs and the summary go to DIR (default
# WORKTREE/build-vc6/m3_gate); DIR/m3_gate_summary.json is printed last and holds: matched,
# partials, regressed, differing_bytes per section, project_bytes (+ excl. ??_R3), the
# placement_json path, duplicates, unittests, per-step rc and an overall ok flag.
# matched/partials count only the TUs verify_all checked (those affected by the change unless --full).
# Exit 0 iff every step passed. Needs GAMEMD_BINARY (no default). Diff two runs' placement with
# placement_diff.py.
#
# Waiting for it from a background shell: use this script's exit status or `$!`, never
# `pgrep -f <pattern>` (the pattern is in your own command line and matches itself).
set -u
here="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
wt=""; full=0; jobs=4; out=""; lp=0
while [ $# -gt 0 ]; do
  case "$1" in
    --full) full=1;; --jobs) jobs="$2"; shift;; --out) out="$2"; shift;; --link-progress) lp=1;;
    -h|--help) sed -n 2,30p "$0"; exit 0;;
    -*) echo "m3_gate.sh: unknown option $1" >&2; exit 2;;
    *) wt="$1";;
  esac
  shift
done
[ -d "$wt" ] || { echo "usage: m3_gate.sh WORKTREE [--full] [--jobs N] [--out DIR] [--link-progress]" >&2; exit 2; }
[ -n "${GAMEMD_BINARY:-}" ] || { echo "m3_gate.sh: GAMEMD_BINARY is not set" >&2; exit 2; }
cd "$wt" || exit 2
wt="$(pwd)"
out="${out:-$wt/build-vc6/m3_gate}"
mkdir -p "$out" build-vc6
# a fresh worktree has no toolchain: link the main checkout's (the /toolchain gitignore pattern covers the link)
if [ ! -e toolchain ]; then
  main="$(cd "$(git rev-parse --git-common-dir)/.." && pwd)"
  [ -e "$main/toolchain" ] && ln -s "$main/toolchain" toolchain
fi
O="build-vc6/gate"; M3="$out/gate-link-m3"
: > "$out/steps.tsv"
step() {  # step NAME LOG cmd...
  local name="$1" log="$2"; shift 2
  "$@" > "$log" 2>&1; local rc=$?
  printf '%s\t%s\n' "$name" "$rc" >> "$out/steps.tsv"
  echo "$name rc=$rc"
}
ch=(); [ "$full" = 1 ] || ch=(--changed)
step prebuild   "$out/gate-prebuild.log" python3 scripts/vc6/build_project.py --out "$O" --jobs "$jobs"
step link_diag  "$out/gate-diag.log"     python3 scripts/vc6/link_diag.py --objdir "$O" --out build-vc6/svg-diag
step compile    "$out/gate-compile.log"  scripts/vc6/compile_all.sh --jobs "$jobs" ${ch[@]+"${ch[@]}"}
step verify     "$out/gate-verify.log"   python3 scripts/vc6/verify_all.py --jobs "$jobs" ${ch[@]+"${ch[@]}"}
step build      "$out/gate-build.log"    python3 scripts/vc6/build_project.py --out "$O" --jobs "$jobs"
step link_m3    "$out/gate-m3.log"       python3 scripts/vc6/link_m1.py --objdir "$O" --out "$M3" --hybrid --pin-data --order-tail --source-data --search-literals --distribution-patches --rsrc-from-project --rsrc-art-from-retail
# compare_image exits 1 when the image differs from retail; that is the measurement, not a gate failure
python3 scripts/vc6/compare_image.py --placement "$M3/placement.json" --json "$M3/compare.json" "$M3/m1.exe" > "$out/gate-compare.log" 2>&1
crc=$?; [ -f "$M3/compare.json" ] && crc=0
printf 'compare\t%s\n' "$crc" >> "$out/steps.tsv"; echo "compare rc=$crc"
step duplicates "$out/gate-dup.log"      python3 scripts/vc6/check_duplicates.py
step unittests  "$out/gate-unittest.log" env -u GAMEMD_BINARY python3 -m unittest discover -s scripts/vc6 -p 'test_*.py'
if [ "$lp" = 1 ]; then
  step link_m1 "$out/gate-m1.log" python3 scripts/vc6/link_m1.py --objdir "$O" --out "$out/gate-link" --pin-data --order-tail
  step link_progress "$out/gate-link-progress.log" python3 scripts/orchestration/link_svg.py --refresh --diag build-vc6/svg-diag/report.json --m1 "$out/gate-link" --m3 "$M3"
fi
python3 "$here/m3_gate_summary.py" "$out" --worktree "$wt"
grep -qv $'\t0$' "$out/steps.tsv" && exit 1
exit 0
