# CLAUDE.md

Read `AGENTS.md` first; it is the project law and wins any conflict. Then
`CONTRIBUTING.md` for the workflow.

## Working loop

1. Start from `git status --short`. The default branch is `main`. Other sessions
   may share the working tree, so leave changes you didn't make alone.
2. Pick an unmatched or `partial` function. Use `scripts/data/match_manifest.json`
   and `scripts/vc6/claimed.py` to avoid functions that are already claimed.
   Work leaf-first and climb the class hierarchy.
3. Get ground truth from the Ghidra CLI over the user's `gamemd.exe`:
   `ghidra disasm 0xADDR -n N` (from the entry point), `ghidra decompile`,
   `ghidra x-ref <subcmd>` and `ghidra memory read`.
4. Write VC6-compilable C++ with layout asserts, then iterate with
   `scripts/vc6/match.sh <src> <mangled-sym> <addr> <len>` until it reaches
   100%. Use `scripts/permuter/` for last-mile register or ordering problems.
5. Annotate it, add a provenance header, update the manifest, run
   `compile_all.sh` and `verify_all.py`, and commit with explicit paths.

Keep going while targets remain and the tree is safe. The conditions for
stopping are in `AGENTS.md`.

## Local-only material

The working copy may contain untracked notes and RE seeds (`docs/`, `state/`,
`reference/`). Use them as hypotheses only, and never commit them, quote them
into tracked files, or name private sources in tracked files.

## Reporting

For each task, report: the functions targeted (address and name), the match
result for each, the asserts and annotations added, the provenance tags, the
commit, and the next target. If a function didn't reach 100%, give the best
percentage, the remaining instruction delta and the variants tried.
