# Contributing to gagarin

Thanks for helping preserve the Red Alert 2 / Yuri's Revenge engine. The rules
are in `AGENTS.md`; this guide covers the practical side.

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

## Picking a target

`scripts/data/match_manifest.json` records every claimed function with its
address, symbol, length, status (`matched` or `partial`) and percentage.
`scripts/vc6/claimed.py` tells you whether an address is already taken. Good
first targets are small leaf `__thiscall` accessors, and `partial` rows close
to 100%.

Open an issue or draft PR naming the addresses you're taking, so two people
don't work on the same function.

## Matching a function

1. Disassemble from the entry point (`ghidra disasm 0xADDR -n N`). That listing
   is what you have to match. Treat the decompiler's output as a hint only.
2. Write the C++ under `match/<subsystem>/`, using the original 32-bit layout:
   - members in retail order, gaps named `unknown_XX`;
   - `GG_STATIC_ASSERT(offsetof(...))` / `sizeof` for every member you rely on,
     each confirmed against an instruction in the binary;
   - the correct calling convention (`__thiscall` methods, `__stdcall` COM).
3. Run `match.sh` and iterate on types, statement order, phrasing and flags.
   Inline `_asm` is acceptable when nothing else reproduces the output.
4. For the last few register or ordering mismatches, try the permuter
   (`scripts/permuter/new_run.sh`).

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
Section 7 additional terms, as described in `README.md`.
