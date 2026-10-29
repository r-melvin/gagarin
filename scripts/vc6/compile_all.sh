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
# The work lives in compile_all.py so units can compile concurrently with a
# deterministic report order; this wrapper keeps the historical entry point.
exec python3 "$(dirname "${BASH_SOURCE[0]}")/compile_all.py" "$@"
