# gagarin

**gagarin** is a matching decompilation project for the *Command & Conquer:
Red Alert 2 — Yuri's Revenge* engine, retail `gamemd.exe` **v1.001**. The goal
is readable C++ that compiles with the MSVC 6-era toolchain and matches the
retail instructions, function by function. Reconstruction is in progress.

## Why

This project preserves engine code by reconstructing C++ from the retail
binary and checking annotated functions mechanically against it. The target
image is identified by its SHA-256 in [reccmp-project.yml](reccmp-project.yml).
The project works from that binary; it does not claim to have recovered
Westwood's original source files.

## Progress

![gagarin matching progress](.github/assets/progress.svg)

| Measure | Count | Share |
| --- | --- | --- |
| Functions matched at 100% | **3,348** | **16.9%** of 19,753 |
| Sum of matched function lengths | 236 KiB | 6.4% of 3,708 KiB of listed function lengths |
| Functions in progress (partial match) | 164 | 0.8% |
| Tracked C++ translation units under `match/` | 849 | |
| Entries in the Ghidra `.text` function list (includes CRT/third-party) | 19,753 | |

Counts and matched lengths come from the [manifest](scripts/data/match_manifest.json).
The denominators in [progress_totals.json](scripts/data/progress_totals.json)
come from a Ghidra function-list export: 19,753 entries and the sum of their
reported body sizes, 3,797,269 bytes. These are analysis counts, not a complete
census of engine functions or unique byte coverage. The raw `.text` section is
4,060,045 bytes, as recorded by the [padding scan](scripts/data/padding_scan.json).
CRT/third-party entries have not been subtracted from the denominators, so the
percentages do not measure completion of the engine-only goal.

Regenerate the graphic with `scripts/orchestration/progress_svg.py` after
updating the manifest. Source is grouped by subsystem under `match/`;
`match/_layout/` contains layout headers with static assertions.

A raw `.text` [padding scan](scripts/orchestration/padding_scan.py) finds
19,077 byte-pattern candidates: aligned positions following `CC`/`90` runs.
Of these, 801 are absent from the saved Ghidra function list: 742 fall inside
listed bounding spans and 59 outside them. The heuristic also misses 1,477
listed entries, including 157 matched entries. Its candidate count is therefore
**not an upper bound on the function count**. The current
[review list](scripts/data/padding_scan.json) records 789 unclaimed candidates,
including 47 outside listed bounding spans.

[REA/Ghidra evidence summaries](scripts/data/padding_recovery.json) record
observed boundaries and raw-image input identities for investigated entries.
Match status is recorded separately in the manifest. Reproduce the scan with:

```bash
python3 scripts/orchestration/padding_scan.py /path/to/gamemd.exe \
    /path/to/ghidra-functions.json /tmp/padding-scan.json
```

The function export is produced by `ghidra function list --limit 100000 --json`.
Statically linked CRT and third-party code is outside the matching scope under
[AGENTS.md](AGENTS.md). The goal is to match the engine function by function;
a byte-identical executable is not a completion criterion.

## What "matched" means

The required standard for a `matched` manifest row is equality with retail
bytes at its annotated address, with relocations normalised. Functions being
matched use [reccmp](https://github.com/isledecomp/reccmp) annotations such as:

```cpp
// FUNCTION: GAMEMD 0x6C9600
int StorageClass::GetTotalValue() const
```

Project rules require binary evidence and static assertions for touched member
offsets and vtable slots. Readable C++ is preferred; asm and shims are a last
resort. These are requirements for contributions, not a claim that every
existing source file has received an exhaustive layout audit.

`verify_all.py` recompiles manifest translation units and checks rows recorded
at 100%. Partial rows are compile-checked; their stored percentages are not
remeasured by that gate.

## You need your own copy of the game

To verify matches you need a legally owned retail `gamemd.exe` v1.001.
Project rules prohibit committing the retail executable, game assets, PDBs,
build outputs, or the Microsoft toolchain. The toolchain fetch script downloads
it separately; it is excluded by `.gitignore`.

## Building and verifying

The scripts use Wine (WoW64), Python 3, Git for toolchain fetching, and GNU
`objdump` for instruction diffs. Configure a local Ghidra CLI with your
`gamemd.exe`. The raw byte oracle uses `~/.cargo/bin/ghidra`; the instruction
oracle accepts a `GHIDRA` path override. `verify_all.py` tries the raw oracle
first, then falls back to the instruction oracle.

```bash
# Fetch the period MSVC 6.0 toolchain (itsmattkc/MSVC600) into toolchain/.
scripts/vc6/fetch_toolchain.sh

# Compile every TU and layout header under VC6 (no retail binary needed; this is the CI gate).
scripts/vc6/compile_all.sh

# Compile one TU and diff one function against retail.
#   match.sh <src> <mangled-symbol> <retail-addr> <length>
scripts/vc6/match.sh match/economy/storage_class.cpp \
    "?GetTotalValue@StorageClass@@QBEHXZ" 0x6C9600 0x4f

# Re-verify 100% rows; compile-check documented partial rows.
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
instructions and certify C++ with the VC6 oracle. Keep raw excerpts and full
analysis output outside committed source; commit only reviewed derived facts.

The [compiler wrapper](scripts/vc6/vc6cl.sh) defaults to
`/O2 /DNDEBUG /Gy /GX`; a `VC6FLAGS` comment or `VC6_FLAGS` environment setting
can override it. Contributions must determine flags from matching evidence.
The wrapper records `cl.exe` 12.00.8804 and `link.exe` 6.00.8447 from
itsmattkc/MSVC600. Matching output is the check on toolchain suitability;
these version strings do not prove identity with Westwood's original compiler
installation.

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
provenance header (for example, `own-binary-via-Ghidra | EA-GPL-RA1-reference |
YRpp-cross-check | original`). See `CONTRIBUTING.md` for the full workflow
and `AGENTS.md` for the rules.

Every external source is a hypothesis, never an authority: an offset, address
or signature lands only once an instruction in the binary confirms it.

## Credits

- **[itsmattkc/MSVC600](https://github.com/itsmattkc/MSVC600)** — toolchain
  fetched by `scripts/vc6/fetch_toolchain.sh` and run under Wine.
- **[reccmp](https://github.com/isledecomp/reccmp)** — address annotation format
  and project configuration. Per-function verification is implemented by this
  repository's `scripts/vc6/` byte and instruction oracles.
- **[decomp-permuter](https://github.com/simonlindholm/decomp-permuter)** —
  supported by `scripts/permuter/` for bounded source-variation searches.
- **[REA](https://github.com/morluto/rea)** — the reverse-engineer-anything
  skill and tools used with the Ghidra provider for focused decompilation,
  control-flow/value-flow analysis, and evidence records. The
  [excerpt helper](scripts/orchestration/rea_function.py) pins the retail image
  hash and records analysis provenance; retail instructions and VC6 matching
  remain the factual checks.
- **[Ghidra](https://ghidra-sre.org/)** — disassembly, decompilation and
  cross-reference analysis used by the local workflow.
- **[YRpp](https://github.com/Phobos-developers/YRpp)**,
  **[TSpp](https://github.com/Vinifera-Developers/TSpp)** and
  **[EA's Red Alert source](https://github.com/electronicarts/CnC_Red_Alert)** —
  naming and structural references identified in source provenance comments.
  Under project rules, these supply hypotheses; retail instructions must
  establish RA2/YR addresses, layouts and vtable slots. YRpp is consult-only,
  TS addresses do not transfer, and EA source is reference-only.

Project rules permit clean-room implementations only as black-box behaviour
references, never as code or layout sources.

## Licence

GPLv3 (see [LICENSE](LICENSE)). Project policy in [AGENTS.md](AGENTS.md)
also adopts the [EA Section 7 additional terms](https://github.com/electronicarts/CnC_Red_Alert/blob/main/LICENSE.md):
no use of EA trademarks, modifications must be marked, and no claim of EA
affiliation. gagarin is an independent preservation project, not affiliated
with or endorsed by EA or Westwood.
