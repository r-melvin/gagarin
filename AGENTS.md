# AGENTS.md — gagarin project rules

These rules apply to everyone working on gagarin, human or AI agent. Where any
other file conflicts with them, this file wins. `README.md` describes the
project; `CONTRIBUTING.md` explains the day-to-day workflow.

## Goal

gagarin is a matching decompilation of the *Red Alert 2 / Yuri's Revenge*
engine, retail `gamemd.exe` **v1.001**, built with MSVC 6.0 SP5. The aim is to
preserve source that is lost: a human-readable, structured C++ project, as
close to Westwood's organization as binary evidence permits, whose complete
build reproduces the pinned retail executable byte for byte. This is the
ultimate completion target; it has not been achieved. Matching annotated
functions instruction for instruction is an intermediate fidelity gate.

A function is **matched** only when:

- its compiled bytes equal retail at its annotated address (relocations
  normalised);
- the vtables it relies on match slot for slot;
- the `GLOBAL`/`STRING` addresses it references agree with the binary;
- every struct member offset it touches is confirmed against an instruction in
  the binary and pinned by an `offsetof`/`sizeof` static assert.

The unit of matching is the function. Source recovery of statically linked CRT
and third-party code is out of scope: mark it `LIBRARY` and move on. Those
dependencies still have to be accounted for in the complete build and image
comparison; excluding their source recovery does not exclude their bytes from
the final target.

Do not claim a byte-identical executable until a reproducible integrated build
has produced one and the complete file equals the pinned retail image, without
relocation normalization or other byte masking. Per-function checks, successful
compilation and a successful link do not establish whole-image identity.

For annotated functions, the oracle is the per-function match percentage against
the retail binary, not behaviour tests.

## Legal scope (non-negotiable)

Read and follow [LEGAL.md](LEGAL.md). Its legal and provenance requirements
are part of these project rules and apply to everyone working on gagarin.

## Evidence

The retail binary is the only authority. Every other source (YRpp, TSpp, RA1,
Ghidra's decompiler output, earlier documents) is a hypothesis to be confirmed
against an instruction in the binary before it lands as a repo fact.

- RTTI read from the binary outranks every document, this repo's included.
- Two sources that agree are not independent if they share an ancestor (for
  example, the same Ghidra export).
- Ghidra's `disasm` at an interior address can re-flow and truncate a function.
  Disassemble from the entry point and slice; repair with `ghidra analyze`.
- Re-validate function entry points against the current analysis before use.

## Engineering rules

- Do not use `volatile`, redundant pointer aliases, or casts solely to force a
  byte match. Remove such steering and record the function as partial when
  ordinary C++ does not match. ABI and layout casts require binary evidence.

- Target the 32-bit MSVC6 ABI: `__thiscall` (ECX = `this`) for methods,
  `__stdcall` for COM/WinAPI virtuals, 4-byte pointers. Do not assume `/Gz`;
  determine the convention from the disassembly for each function.
- Declare members in exact retail order. Name gaps `unknown_XX`. Add
  `GG_STATIC_ASSERT` (`match/_rt/gg_static_assert.h`) for every offset and
  size, and assert vtables slot by slot.
- No inline `_asm`, naked functions or `#pragma optimize` to force a match. A
  readable partial beats a hack; asm is a last resort and needs the user's
  explicit approval for the specific function.
- Annotate every function, vtable, global and string with reccmp markers
  (`// FUNCTION: GAMEMD 0xADDR`, `VTABLE`, `GLOBAL`, `STRING`, plus `LIBRARY`,
  `STUB`, `TEMPLATE`, `SYNTHETIC` where they apply). Within a TU, order functions
  by ascending retail address.
- `FUN_`/`DAT_` placeholder names and `unknown_XX` members are legitimate until a
  real name is confirmed. A real name must be attested by the binary (RTTI,
  import, debug or INI string), or cross-checked against YRpp or Tiberian Sun
  structure and confirmed by the binary's behaviour, and tagged accordingly.
  Never transcribe names, comments or text from any outside source, and never
  use names recalled from memory without that evidence; use a placeholder.
- Pin compiler flags by bisection for each cluster, never by assumption. The
  binary has no C++ exception-handling tables, and free functions default to
  `__fastcall`, so the target default is `/O2 /Gr /DNDEBUG /Gy` without `/GX`;
  `/Ob2` is set per TU only where the evidence requires it.
- Keep `scripts/data/match_manifest.json` truthful: a row is `matched` only if
  `scripts/vc6/verify_all.py` proves it.

## Toolchain

- `cl.exe` 12.00 / `link.exe` 6.00.8447 from itsmattkc/MSVC600, under Wine
  (WoW64), driven by `scripts/vc6/vc6cl.sh`. The retail Rich header reports
  build 8447 (SP5); the fetched compiler's code generator stamps the same build
  in every object.
- `scripts/vc6/match.sh` is the per-function loop, `scripts/vc6/compile_all.sh`
  the binary-free CI gate, and `scripts/vc6/verify_all.py` the whole-repo
  regression check.
- reccmp 0.1.4 with `reccmp-project.yml` (target `GAMEMD`, binary pinned by
  SHA-256).

## Before committing

- `compile_all.sh` passes, and `verify_all.py` shows no matched function
  regressing.
- No forbidden file is staged. Add paths explicitly; never `git add -A`.
- Provenance headers and annotations are present on every new file.

## When to stop and ask

Ugly decomp, a large function, a one-register mismatch or a need for more
disassembly are normal conditions; none of them is a reason to stop. Stop and
ask only if:

- a fact cannot be recovered from the binary;
- a function still won't match after three materially different attempts
  (flag bisection, rephrasing or the permuter, a layout re-check). Report the
  best percentage and the remaining instruction delta;
- a licensing question needs a human decision;
- the work needs a destructive action or network access that isn't available.

When delegating, give each worker a single cluster of addresses, and never put
two workers on the same address.
