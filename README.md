# gagarin

**gagarin** is a matching decompilation of the *Command & Conquer: Red Alert 2 —
Yuri's Revenge* engine: C++ source that, compiled with the original Microsoft
Visual C++ 6.0 (SP5) toolchain, reproduces the retail `gamemd.exe` **v1.001**
instruction-for-instruction, function by function. The name honours cosmonaut
Yuri Gagarin, and nothing else.

## Why

Westwood's source for Red Alert 2 and Yuri's Revenge is lost. EA released the
code for Tiberian Dawn and Red Alert 1 in 2020, but never for RA2/YR, and no
copy is known to survive. The game lives on only as a 2001 x86 binary.

gagarin rebuilds that source from the binary itself, to preserve it: readable,
compilable code whose correctness can be checked mechanically, byte for byte,
against the game people still own and play. It is not a remake, not an engine
replacement, and it ships no game content.

## Progress

![gagarin matching progress](.github/assets/progress.svg)

| Measure | Count | Share |
| --- | --- | --- |
| Functions matched at 100% | **3,230** | **16.4%** of 19,753 |
| Code matched | 231 KB | 6.2% of 3,708 KB in `.text` |
| Functions in progress (partial match) | 160 | 0.8% |
| Translation units under `match/` | 807 | |
| Functions in the binary (Ghidra analysis, includes CRT/third-party) | 19,753 | |

Matching started with the small functions, so the share of code bytes trails the
share of functions. The game's own code is somewhere around 18,000 functions
once CRT and library code is set aside. Regenerate the graphic with
`scripts/orchestration/progress_svg.py` after updating the manifest; the totals
it divides by live in `scripts/data/progress_totals.json`. Work so far is spread
across `core` (the class hierarchy: `AbstractClass` → `ObjectClass` →
`TechnoClass` → `FootClass` → units/buildings/infantry/aircraft), `map`,
`platform`, `ui`, `combat`, `movement`, `ai`, `economy`, `network`, `renderer`
and `audio`, plus `_layout/` headers that pin class layouts and vtables with
`offsetof`/`sizeof` static asserts.

A raw `.text` [padding scan](scripts/orchestration/padding_scan.py) reproduces
19,077 aligned starts after `CC`/`90` runs. Of these, 801 are absent from the
current Ghidra function list: 742 fall inside listed bounding spans and 59 lie
outside them. The heuristic also misses 1,477 listed entries, including 152
already matched functions, so its candidate count is **not an upper bound on
the total function count**. Nine formerly unlisted entries have since been
matched against the binary: `0x409FF0`, `0x41BB30`, `0x435340`, `0x4CB990`, `0x5BCB60`, `0x6E6080`,
`0x723E40`, `0x72B9E0` and `0x72CAC0`. The [review list](scripts/data/padding_scan.json)
tracks claims separately; 790 unlisted candidates remain unclaimed, including
48 outside listed bounding spans. The AircraftClass function at `0x4155F0`
has also been reconstructed as a 98.6% C++ partial. [Rea/Ghidra evidence summaries](scripts/data/padding_recovery.json)
record the recovered function boundaries and their raw-image input
identities; final match status comes from the VC6 byte oracle. Reproduce it with
`python3 scripts/orchestration/padding_scan.py /path/to/gamemd.exe
/path/to/ghidra-functions.json /tmp/padding-scan.json`, using an export from
`ghidra function list --limit 100000 --json`.

Statically linked CRT and third-party code is out of scope (as in other MSVC
decomps such as LEGO Island). The goal is a per-function match across the
game's own code, not a single byte-identical `.exe`.

`scripts/data/match_manifest.json` lists every claimed function with its
address, symbol, length and match percentage.

## What "matched" means

A function counts as matched only when its compiled bytes equal the retail
bytes at its annotated address, with relocations normalised. Every source
function carries a [reccmp](https://github.com/isledecomp/reccmp) annotation:

```cpp
// FUNCTION: GAMEMD 0x6C9600
int StorageClass::GetTotalValue() const
```

Struct member offsets and vtable slots are confirmed against instructions in the
binary and pinned with static asserts. Inline `_asm` is used only where it is
the only way to reproduce the compiler's exact output.

## You need your own copy of the game

This repository contains **no EA code, binaries, assets or PDBs**. To verify a
match you need a legally owned retail `gamemd.exe` v1.001 (its SHA-256 is pinned
in `reccmp-project.yml`). The Microsoft toolchain is fetched at build time and
never committed.

## Building and verifying

Requirements: Wine (WoW64), Python 3, 7-Zip, and for per-function diffs a
Ghidra CLI with your `gamemd.exe` loaded (set `GHIDRA` if it is not at
`~/.cargo/bin/ghidra`).

```bash
# Fetch the period MSVC 6.0 toolchain (itsmattkc/MSVC600) into toolchain/.
scripts/vc6/fetch_toolchain.sh

# Compile every TU and layout header under VC6 (no retail binary needed; this is the CI gate).
scripts/vc6/compile_all.sh

# Compile one TU and diff one function against retail.
#   match.sh <src> <mangled-symbol> <retail-addr> <length>
scripts/vc6/match.sh match/economy/storage_class.cpp \
    "?GetTotalValue@StorageClass@@QBEHXZ" 0x6C9600 0x4f

# Re-verify every function in the manifest against retail.
python3 scripts/vc6/verify_all.py
```

For functions omitted by whole-image analysis, inspect an entry and length
already validated against retail with the local Rea CLI:

```bash
python3 scripts/orchestration/rea_function.py /path/to/gamemd.exe \
    0x6E6080 0xDD /tmp/tag-reader-evidence.json
```

The helper checks the image hash, uses a temporary raw x86 image at the original
address, and writes a provenance sidecar. Raw-image pseudocode lacks external
callee signatures and global definitions; confirm inferred facts against the
instructions and certify C++ with the VC6 oracle. Complete Rea output includes
retail bytes and belongs outside committed source.

Compiler flags are pinned by bisection per cluster, never assumed (the first
cluster locked at `/O2 /DNDEBUG /Gy /GX`). The toolchain evidence: the retail
Rich header reports linker and compiler build 8447 (VC6 SP5), and the fetched
compiler's code generator stamps the same build in every object.

## Layout

```text
match/            the decompiled source, by subsystem; _layout/ holds layout-only headers
match/_rt/        static-assert support
scripts/vc6/      VC6-under-Wine compile, diff and verification harness
scripts/permuter/ decomp-permuter integration for last-mile register/order mismatches
scripts/ghidra/   Ghidra helper scripts
scripts/data/     match manifest and binary-derived census data
AGENTS.md         project rules (legal scope, engineering rules)
CONTRIBUTING.md   how to set up and match a function
```

## Contributing

Pick an unmatched function, read its disassembly, write C++ in the original
32-bit layout, and iterate with `match.sh` until it reaches 100%. Annotate it,
order functions by ascending address within the TU, and give each file a
provenance header (`own-binary-via-Ghidra | EA-GPL-RA1-reference |
YRpp-cross-check | original`). See `CONTRIBUTING.md` for the full workflow
and `AGENTS.md` for the rules.

Every external source is a hypothesis, never an authority: an offset, address
or signature lands only once an instruction in the binary confirms it.

## Credits

- **[itsmattkc/MSVC600](https://github.com/itsmattkc/MSVC600)** — the portable
  period Microsoft Visual C++ 6.0 toolchain (`cl.exe` 12.00.8804, `link.exe`
  6.00.8447) the match is rebuilt under (via Wine). MS-proprietary; fetched at
  build/CI time, never committed.
- **[isledecomp/reccmp](https://github.com/isledecomp/reccmp)** — the MSVC x86
  matching harness (annotation address-map format, per-function match-% metric,
  CI gate, `vtable`/`datacmp`/`stackcmp` verifiers, Ghidra import). The canonical
  precedent is the isle (LEGO Island) decompilation.
- **[objdiff](https://github.com/encounter/objdiff)** /
  **[asm-differ](https://github.com/simonlindholm/asm-differ)** — per-function
  inner-loop object diffing (MSVC demangle, x86 COFF).
- **[decomp.me](https://github.com/decompme/decomp.me)** /
  **[decomp-permuter](https://github.com/simonlindholm/decomp-permuter)** —
  collaborative scratches and last-mile register/order matching.
- **[CMR2Decomp](https://github.com/Brawltendo/CMR2Decomp)** — the closest
  precedent (a year-2000 MSVC6 DirectX7 PC game decompiled with
  reccmp + Ghidra + MSVC600); source of the initial compiler-flag hypothesis.
- **[Phobos-developers/YRpp](https://github.com/Phobos-developers/YRpp)** —
  community RA2/YR engine interface; the primary source of retail addresses,
  `__thiscall`/`__stdcall` signatures, and exact MSVC layout/vtable order. Ships
  **no LICENSE**, so it is treated as **consult-only**: every offset/address it
  supplies is reconfirmed against the user's own binary before it lands as a repo
  fact, and its headers are not vendored verbatim.
- **[Vinifera-Developers/TSpp](https://github.com/Vinifera-Developers/TSpp)**
  (**GPLv3**, and it incorporates EA-released GPLv3 source) — a 350-header class
  map of the Tiberian Sun binary. TS is RA2's direct ancestor, so TSpp is the
  best available source of the *original Westwood member and method names* and of
  base-class member order for everything RA2 inherited (e.g. `GadgetClass`:
  `X/Y/Width/Height/IsToRepaint/IsSticky/IsDisabled/Flags` + the `StuckOn`/
  `Focused` statics, confirmed identical up to +0x24 in RA2). Unlike YRpp its
  license is explicit and compatible with gagarin's, so it can be cited as a
  naming source rather than merely consulted. **Names and structure only — TS
  addresses never transfer to RA2, and RA2's vtables insert extra slots (RA2's
  `GadgetClass` adds 0x70/0x74 over TS's); every RA2 slot and offset is still
  derived from the user's own binary.**
- **[Phobos-developers/Phobos](https://github.com/Phobos-developers/Phobos)** /
  **[Vinifera-Developers/Vinifera](https://github.com/Vinifera-Developers/Vinifera)**
  — engine-extension projects whose hook sites corroborate RE offsets and
  behavior for RA2 (Phobos) and TS (Vinifera).
- **[Ares / Antares](https://github.com/AlexB-SVK/Ares)** — additional RE offset
  corroboration (Antares is BSD-licensed, preferred where it overlaps).
- **[EA `CnC_Red_Alert`](https://github.com/electronicarts/CnC_Red_Alert)**
  (GPLv3 + EA Section-7) — original Westwood `*Class` naming and algorithm shape
  **as a reference only**, never a transcription crib (RA1 is Watcom, a
  structural cousin two generations back; snake_case is corrected to RA2
  camelCase). Any closely-adapted file carries EA's Section-7 terms. In practice
  RA1's `*.CPP` bodies are the fastest way to confirm the *shape* of a routine
  whose bytes are already in hand — e.g. RA1 `GADGET.CPP` independently confirmed
  the derived `Enable`/`Disable`/`Remove`/`Draw_Me`/`Sticky_Process`/`Action`/
  `Clear_Focus` control flow (RA2 widens the sticky masks from
  `LEFTPRESS`/`LEFTRELEASE` to `0x11`/`0x44` to cover the right button).
- **[EA `CnC_Remastered_Collection`](https://github.com/electronicarts/CnC_Remastered_Collection)**,
  **[Vanilla Conquer](https://github.com/TheAssemblyArmada/Vanilla-Conquer)**, and
  **[Chronoshift](https://github.com/TheAssemblyArmada/Chronoshift)** (all GPLv3)
  — the same RA1/TD lineage in more readable form; secondary shape references
  under the same reference-only rule as EA `CnC_Red_Alert`.
- **[REA](https://github.com/morluto/rea)** — the reverse-engineer-anything
  skill and tools used for focused decompilation, control-flow and value-flow
  analysis, and structured evidence records. We use its Ghidra provider;
  conclusions are checked against retail instructions and VC6 byte matching.
- **[Ghidra](https://ghidra-sre.org/)** — provides disassembly, decompilation,
  and cross-reference analysis of the user's own binary.
- **[ModEnc](https://www.modenc.renegadeprojects.com/)** /
  **DeeZire** — `rules.ini`/`art.ini`/`ai.ini` and MIX/SHP/VXL/HVA field names
  and field-read order (which constrains `*TypeClass` member layout).
- **Westwood Studios / EA** — creators of Red Alert 2 and Yuri's Revenge. This
  project exists to preserve their work; it requires and does not replace the
  original game data.

Clean-room reimplementations (OpenRA-ra2, ra2yrcpp and the like) are used only
as black-box behaviour references, never as a code or layout source.

## Licence

GPLv3 (see `LICENSE`), with EA's Section 7 additional terms as applied to the
released C&C source: no use of EA trademarks, modifications must be marked, and
no claim of EA affiliation. *Command & Conquer*, *Red Alert 2* and *Yuri's
Revenge* are trademarks of Electronic Arts. gagarin is an independent
preservation project, not affiliated with or endorsed by EA or Westwood.
