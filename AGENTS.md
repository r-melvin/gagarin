# AGENTS.md — gagarin project rules

These rules apply to everyone working on gagarin, human or AI agent. Where any
other file conflicts with them, this file wins. `README.md` describes the
project; `CONTRIBUTING.md` explains the day-to-day workflow.

## Goal

gagarin is a matching decompilation of the *Red Alert 2 / Yuri's Revenge*
engine, retail `gamemd.exe` **v1.001**, built with MSVC 6.0 SP5. The aim is to
preserve source that is lost: C++ that, compiled with the period toolchain,
reproduces the retail binary instruction for instruction at every annotated
function.

A function is **matched** only when:

- its compiled bytes equal retail at its annotated address (relocations
  normalised);
- the vtables it relies on match slot for slot;
- the `GLOBAL`/`STRING` addresses it references agree with the binary;
- every struct member offset it touches is confirmed against an instruction in
  the binary and pinned by an `offsetof`/`sizeof` static assert.

The unit of matching is the function. Statically linked CRT and third-party
code is out of scope: mark it `LIBRARY` and move on. Never promise a
byte-identical `.exe`.

The oracle is the per-function match percentage against the retail binary, not
behaviour tests.

## Legal scope (non-negotiable)

What may be committed:

- decompiled C/C++ source, address-annotated;
- layouts, offsets, vtable and global addresses, expressed as code and
  constants;
- the reccmp config, build and verification scripts, CI, and census data
  derived from the binary.

What must never be committed (all `.gitignore`d):

- the retail binary, the game's MIX assets, or any EA byte;
- any PDB, `.obj`, `.exe` or other build output;
- the Microsoft VC6 toolchain, which is fetched at build time;
- verbatim text from sources without a compatible licence (YRpp ships none, so
  it is consult-only: reconfirm every fact against the binary and never copy its
  headers);
- material from private or unpublished projects.

Licence: GPLv3 with EA's Section 7 additional terms (no EA trademarks,
modifications marked, no claim of EA affiliation). EA's released RA1/TD source
is a naming and structure reference only, never a transcription source; RA1 was
built with Watcom and is two engine generations back. Clean-room
reimplementations (OpenRA-ra2, ra2yrcpp and others) are black-box behaviour
references only, never a code or layout source.

Every source and header file carries a provenance header naming where its facts
came from (see `CONTRIBUTING.md` for the tags).

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

- Target the 32-bit MSVC6 ABI: `__thiscall` (ECX = `this`) for methods,
  `__stdcall` for COM/WinAPI virtuals, 4-byte pointers. Do not assume `/Gz`;
  determine the convention from the disassembly for each function.
- Declare members in exact retail order. Name gaps `unknown_XX`. Add
  `GG_STATIC_ASSERT` (`match/_rt/gg_static_assert.h`) for every offset and
  size, and assert vtables slot by slot.
- Inline `_asm` is allowed where it is the only way to reproduce the compiler's
  output. Matching beats cleanliness.
- Annotate every function, vtable, global and string with reccmp markers
  (`// FUNCTION: GAMEMD 0xADDR`, `VTABLE`, `GLOBAL`, `STRING`, plus `LIBRARY`,
  `STUB`, `TEMPLATE`, `SYNTHETIC` where they apply). Within a TU, order functions
  by ascending retail address.
- `FUN_`/`DAT_` placeholder names and `unknown_XX` members are legitimate until a
  real name is confirmed. Westwood names come from YRpp, TSpp (names and
  structure only; TS addresses never transfer) or RA1 idiom converted to RA2
  camelCase (`Take_Damage` → `ReceiveDamage`).
- Pin compiler flags by bisection for each cluster, never by assumption. The
  first cluster (`StorageClass`) locked at `/O2 /DNDEBUG /Gy /GX`.
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
