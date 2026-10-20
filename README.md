# gagarin

**gagarin** reconstructs the *Command & Conquer: Red Alert 2 — Yuri's Revenge*
engine, retail `gamemd.exe` **v1.001**, as a coherent, human-readable C++ project.
The ultimate goal is a buildable, structured C++ project that reproduces the
complete v1.001 `gamemd.exe` byte for byte. Its classes, inheritance,
interfaces, source organization and coding style should be as close to
Westwood's original project as the evidence allows. Preserving that project is the
deliverable: readable C++, shared engine types and implementations, and an
integrated build. This goal has not been achieved; reconstruction is in progress.

Per-function instruction matching under the MSVC 6-era toolchain is an
intermediate fidelity check. The final target requires an integrated project
build and a comparison of the complete executable, without byte masking.

## Why

This project preserves engine code by reconstructing C++ from the retail
binary and checking annotated functions mechanically against it. The target
image is identified by its SHA-256 in [reccmp-project.yml](reccmp-project.yml).
The project works from that binary; it does not claim to have recovered
Westwood's original source files.

## Source-project reconstruction progress

Matching coverage and project reconstruction are tracked separately. A higher
match count does not by itself establish a coherent class hierarchy or a
project-wide build. The status below records demonstrated capabilities and
remaining completion gates, rather than estimating how much original source
structure has been recovered.

| Milestone | Current state and evidence | Completion gate |
| --- | --- | --- |
| Reproducible compilation and matching | Gates are available for recovered translation units through [compile_all.sh](scripts/vc6/compile_all.sh) and [verify_all.py](scripts/vc6/verify_all.py). | Keep compilation passing and preserve existing matches through every structural change. |
| Shared classes and inheritance | Partial. [LinkClass](match/core/link_class_methods.h), [GadgetClass](match/ui/gadget_class_methods.h), [StorageClass](match/economy/storage_class.h) and the [vector templates](match/core/vector_class.h) have shared declarations; address-scoped views still coexist, for example [gadget copy views](match/ui/gadget_copy_004b5630.h). | Consolidate related methods and confirmed layouts into common class definitions, with verified bases, members and virtual slots. |
| Source and subsystem organization | Source is grouped under `match/`; consolidation into class-owned headers and implementations is ongoing. Original file/module boundaries have not been audited repository-wide. | Use recovered names, RTTI, call relationships and source-path evidence where available; record uncertainty instead of inventing original filenames or ownership. |
| Integrated project build | Not yet established. The current [compile gate](scripts/vc6/compile_all.sh) compiles translation units separately; the tracked tree has no top-level source-project build target or whole-engine link gate. | Provide a project-wide build that compiles and links the reconstructed engine through shared declarations and implementations. |
| Complete executable reproduction | Not established. Current gates do not produce or compare a complete `gamemd.exe`. | Reproduce and compare the entire pinned PE file byte for byte, including code, data, headers, imports, relocations and resources; account for library dependencies and deterministic build metadata. |
| Engine reconstruction and fidelity | In progress; verified function totals are below. There is no audited class-completion percentage yet. | Recover the in-scope engine functions and dependencies, consolidate their source, and verify the integrated project while retaining per-function fidelity. |

Address-scoped matching files and narrow layout views are working forms, not the
intended final organization. Consolidation should replace duplicate views and
function stand-ins with shared types and real methods as the binary evidence
supports them. Each consolidation batch must retain address/provenance records,
pass compilation, and reprove the moved functions against retail. Fewer source
files after consolidation can represent progress without adding new matches.

Verified consolidation steps:

- [ShapeButtonClass](match/ui/shape_button_class.h): the recovered methods
  share one declaration and one [implementation](match/ui/shape_button_class.cpp),
  replacing three conflicting declarations and three implementation files.
  The eight earlier methods retain their exact matches; the regular destructor
  and compiler-generated deleting destructor now use the real class. The
  declaration inherits the
  confirmed `ToggleClass → ControlClass → GadgetClass → LinkClass` chain;
  the full set of methods for those classes is still incomplete.
- [ControlClass](match/ui/control_class.h) and [ToggleClass](match/ui/toggle_class_methods.h):
  shared inheritance replaces Toggle's separate constructor prefix view and
  opaque virtual table. Five Control methods and three Toggle methods match;
  the [Gadget constructor](match/ui/gadget_class_ctor.cpp) is a documented partial.
- [ToolTipManager](match/ui/tooltip_manager_shared.h): seventeen verified family functions
  share one declaration and [implementation](match/ui/tooltip_manager.cpp), also
  used by ShapeButton's tooltip calls. The embedded vector now uses the shared
  `DynamicVectorClass<const ToolTip*>` template and its confirmed base. The partial Find view remains separate;
  the manager's exact total size is not established. Its table cache lookup is
  now a native method, and tooltip bounds use a shared asserted rectangle layout.
  The table search also uses the canonical class directly, replacing its layout
  cast to an address-scoped helper. Its shared qsort callback also matches,
  including retail's signed key comparison.
- [Surface](match/renderer/surface_class.h): BitFont and ZBuffer now share the
  confirmed Surface interface and geometry declarations. Six native methods
  live in its [implementation](match/renderer/surface_class.cpp), replacing
  three stand-ins and adding three exact default methods. The interface pins
  all 34 virtual slots; unknown signatures remain placeholders, and the complete
  object size and complete derived layouts are not established.
- [XSurface](match/renderer/xsurface_class.h): four methods share one native
  [implementation](match/renderer/xsurface_class.cpp) and the confirmed Surface
  base, replacing the Unlock stand-in and adding three exact methods. Its
  lock-counter offset is asserted, and its virtual table includes the two
  added slots through `+0x8C`. The complete object size remains unconfirmed.
- [VectorClass and DynamicVectorClass](match/core/vector_class.h): 162 base
  and 160 dynamic `Clear` entries now instantiate the real seven-slot templates,
  replacing the `PlainVector`/`CountedVector::Destroy` stand-ins. The 335 existing
  deleting-destructor matches retain their bytes with the same shared base
  definition. ToolTipManager uses these templates with its RTTI-confirmed const
  element type. [Layout assertions](match/core/vector_class_layout_asserts.cpp)
  check actual template members and sizes under VC6. The DiskID entry at
  `0x69C4A0` retains the `CountedVector<DiskID>::Destroy` matching stand-in
  because its retail declaring class is unresolved; other legacy users are marked `VectorClassLayout` or
  `DynamicVectorClassLayout`. Other virtual methods and original source-file
  ownership remain incomplete.
- [Periodic state updates](match/core/periodic_state_updates_00439480.cpp): nine
  recovered routines use one address-ordered implementation and shared global
  declarations. Their original class or file ownership is not established.

Update this table and the consolidation record after each verified batch,
recording the affected classes, supporting source/evidence, and remaining
gaps. Update function totals separately; do not infer structural completion
from the matching percentages.

The remaining work toward the source-project goal is tracked by these gates:

- [ ] Consolidate address-scoped class views into shared declarations and real
  inheritance, verifying member offsets and every required virtual slot.
- [ ] Establish evidence-backed class and subsystem ownership for recovered
  functions; record which original source boundaries remain unknown.
- [ ] Add an integrated build and link target for the reconstructed C++ project,
  resolving dependencies through shared source rather than matching stand-ins.
- [ ] Recover the remaining in-scope engine functions and verify their matches
  with the period toolchain.
- [ ] Account for CRT/third-party dependencies and the complete PE layout,
  data, resources and build metadata, then verify the integrated build's output
  byte for byte against the pinned retail `gamemd.exe`.
- [ ] Audit the integrated source tree against those gates before declaring
  the reconstruction complete.

These are project-wide gates, not claims that individual classes have received
no work. Completed consolidation batches are listed above; function-level
results are counted below. No overall completion percentage is claimed until
the engine scope and structural audit provide a defensible denominator.

## Function-matching progress

![gagarin matching progress](.github/assets/progress.svg)

| Measure | Count | Share |
| --- | --- | --- |
| Functions matched at 100% | **3,382** | **17.1%** of 19,753 |
| Sum of matched function lengths | 237 KiB | 6.4% of 3,708 KiB of listed function lengths |
| Functions in progress (partial match) | 165 | 0.8% |
| Tracked C++ translation units under `match/` | 850 | |
| Entries in the Ghidra `.text` function list (includes CRT/third-party) | 19,753 | |

Counts and matched lengths come from the [manifest](scripts/data/match_manifest.json).
The denominators in [progress_totals.json](scripts/data/progress_totals.json)
come from a Ghidra function-list export: 19,753 entries and the sum of their
reported body sizes, 3,797,269 bytes. These are analysis counts, not a complete
census of engine functions or unique byte coverage. The raw `.text` section is
4,060,045 bytes, as recorded by the [padding scan](scripts/data/padding_scan.json).
CRT/third-party entries have not been subtracted from the denominators, so the
percentages do not measure completion of the reconstructed source project.

Regenerate the graphic with `scripts/orchestration/progress_svg.py` after
updating the manifest. Source is grouped by subsystem under `match/`;
`match/_layout/` contains layout headers with static assertions.

A raw `.text` [padding scan](scripts/orchestration/padding_scan.py) finds
19,077 byte-pattern candidates: aligned positions following `CC`/`90` runs.
Of these, 801 are absent from the saved Ghidra function list: 742 fall inside
listed bounding spans and 59 outside them. The heuristic also misses 1,477
listed entries, including 158 matched entries. Its candidate count is therefore
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
Source recovery of statically linked CRT and third-party code is outside the
matching scope under [AGENTS.md](AGENTS.md). Their bytes still belong to the
complete executable reproduction target, so the build must account for those
dependencies. Per-function matching does not prove whole-image identity.

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

When a cluster's ownership and layout are established, consolidate its methods
into shared class headers and implementations. Reverify its functions after
moves or type/signature changes, and update the manifest with the actual symbols
and source paths. Keep temporary matching conveniences out of the final class
interfaces unless the binary requires them.

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
