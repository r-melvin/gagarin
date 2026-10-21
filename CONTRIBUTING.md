# Contributing to gagarin

Thanks for helping preserve the Red Alert 2 / Yuri's Revenge engine. The rules
are in [AGENTS.md](AGENTS.md) and [LEGAL.md](LEGAL.md); this guide covers the practical side.

The ultimate deliverable is a human-readable, structured C++ project whose
complete build reproduces the pinned v1.001 `gamemd.exe` byte for byte. The
per-function workflow below is an intermediate gate. A tracked-source object
build is available, but it does not link the engine or compare the whole image.
Completion requires those gates as well as the source reconstruction.
CRT/third-party source recovery remains out of scope, but the complete build
must account for those dependencies.

## What you need

- A legally owned retail **`gamemd.exe` v1.001**. Its SHA-256 is in
  `reccmp-project.yml`. Never commit it or share it.
- Wine (WoW64), Python 3 and 7-Zip.
- Ghidra with `gamemd.exe` imported and analysed, plus a CLI wrapper exposing
  `disasm`, `decompile`, `x-ref` and `memory read` (see `scripts/ghidra-cli`).
  Set `GHIDRA` if the binary isn't at `~/.cargo/bin/ghidra`.
- The VC6 toolchain: run `scripts/vc6/fetch_toolchain.sh`.

Check the setup with:

```bash
scripts/vc6/compile_all.sh
scripts/vc6/match.sh match/economy/storage_class.cpp \
    "?GetTotalValue@StorageClass@@QBEHXZ" 0x6C9600 0x4f
```

For byte and instruction comparisons, you can select the local retail image
without using the Ghidra bridge:

```bash
export GAMEMD_BINARY="/path/to/gamemd.exe"
python3 scripts/vc6/verify_all.py
```

`raw_match.py` and `diff_retail.py` inherit this setting. They verify the image's
SHA-256 against the project pin and require the full span to be backed by one
PE section. A configured bad path or hash fails; it never falls back to Ghidra.
With the variable unset, the existing Ghidra memory reader remains available.
REA/Ghidra is still used for analysis and entry-point evidence.

To compile every tracked C++ translation unit into a persistent,
path-preserving object tree, run:

```bash
python3 scripts/vc6/build_project.py --jobs 8
python3 scripts/vc6/build_project.py --check
```

The first command writes objects and an input/object hash index under the
ignored `build-vc6/project/` directory. `--check` verifies that the tracked
C++ sources and headers, manifest, compiler wrapper, and indexed objects still
match that record; it rejects stale inputs or objects. It does not compile or
link. These commands create a path-preserving object build, not an integrated
engine link or a whole-image comparison.

## Picking a target

`scripts/data/match_manifest.json` records every claimed function with its
address, symbol, length, status (`matched` or `partial`) and percentage.
`scripts/vc6/claimed.py` tells you whether an address is already taken. Good
first targets are small leaf `__thiscall` accessors, and `partial` rows close
to 100%.

Open an issue or draft PR naming the addresses you're taking, so two people
don't work on the same function.

## Matching a function

1. Disassemble from the validated entry point (`ghidra disasm 0xADDR -n N`).
   Confirm the complete contiguous span, including the final `RET`, against
   raw memory bytes: Ghidra's listing and function-size field can omit blocks
   after calls. Treat the decompiler's output as a hint only.
2. Write the C++ under `match/<subsystem>/`, using the original 32-bit layout:
   - members in retail order, gaps named `unknown_XX`;
   - `GG_STATIC_ASSERT(offsetof(...))` / `sizeof` for every member you rely on,
     each confirmed against an instruction in the binary;
   - the correct calling convention (`__thiscall` methods, `__stdcall` COM).
3. Run `match.sh` and iterate on types, statement order, phrasing and flags.
   Inline `_asm` is acceptable when nothing else reproduces the output.
4. For the last few register or ordering mismatches, try the permuter:
   `scripts/permuter/new_run.sh <addr> <C-name> <native-symbol> /tmp/run <length>`.
   The fifth argument is the full validated retail span in hex. Before searching,
   check the generated target against those raw bytes and require the adapter's
   compiled body to equal a fresh compile of the actual C++ source. Keep raw
   targets, adapters and search output under `/tmp`.

For class integrations, `scripts/vc6/verify_vtable.py` compares requested COFF
vtable slots with the pinned retail PE. Supply `--obj`, `--sym`, `--addr`,
`--slots` and `--binary`; targets must resolve through 100%-matched manifest
rows or an explicit `--symbol-map` JSON object for library symbols.
`--weak-defaults` conditionally follows unresolved `SEARCH_LIBRARY` weak
externals through their recorded COFF default when no same-name strong
definition or mapping is known. A final link can select a strong library
definition instead. This scoped check does not establish final-link resolution,
unrequested slots, or whole-image identity.

## File conventions

Each file starts with a provenance header:

```cpp
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
```

Tags:

| Tag | Meaning |
| --- | --- |
| `own-binary-via-Ghidra` | facts read from the retail binary (required for every committed fact) |
| `YRpp-cross-check` | name or signature suggested by YRpp, reconfirmed in the binary |
| `EA-GPL-RA1-reference` | naming or shape informed by EA's GPL RA1 source (carries EA's Section 7 terms) |
| `Phobos-GPL3:<path>@<commit>` | Phobos's own material, with upstream path and full commit; import requires the provenance and applicable-terms review in [LEGAL.md](LEGAL.md), and retail facts still need binary confirmation |
| `private-ref-cross-check` | location suggested by the author's unpublished notes, reconfirmed in the binary |
| `original` | written from scratch (helpers, shims) |

Annotate everything with reccmp markers and order functions by ascending
address within the file:

```cpp
// FUNCTION: GAMEMD 0x6C9600
int StorageClass::GetTotalValue() const { ... }
```

`FUN_xxxxxxxx` names are fine until a real name is confirmed. Don't guess
names. Westwood names come from YRpp, TSpp or RA1 idiom, and every one of them
must still match the binary's behaviour.

## Before opening a PR

- `scripts/vc6/compile_all.sh` passes (CI runs this).
- `python3 scripts/vc6/verify_all.py` shows no matched function regressing.
- New rows are added to `scripts/data/match_manifest.json` with honest status
  and percentage.
- No binaries, PDBs, `.obj` files, assets, toolchain files or copied YRpp text
  are included. Stage paths explicitly.
- The PR description lists each function with its address and match
  percentage.

## Licence

By contributing you agree that your work is released under GPLv3 with EA's
Section 7 additional terms, as described in [LEGAL.md](LEGAL.md).
