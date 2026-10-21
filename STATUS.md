# Project status

The latest whole-repository regression passed with **3,711 fully matched
functions**, **165 partial rows**, and 895 manifest translation units, with no
matched function regressing. All **901 tracked C++ files** produced project
objects and their hash check passed. The compile/layout gate, 75 verifier tests
and duplicate-address check passed. The complete byte-for-byte executable
target has not been achieved.

## Latest integration: native TagClass construction and one shared definition

The [TagClass constructor](match/ai/tag_class_ctor.cpp) adds a full 380-byte
match using native base and trigger constructor calls and a plain C++
`new TriggerClass(...)` expression. The no-GX probe avoids exception cleanup
absent from retail. Its coordinate source is a named global; two additional
vector-shaped registry prefixes are defined without claiming their owning
classes or later runtime initialization.

All tracked TagClass methods and the CellClass tag caller now use the
[single shared TagClass definition](match/_layout/tag_class.h). The two old
TagClass class definitions and the offset-only CellClass caller's TagClass
view are retired. `CellClass::ReplaceTag` also uses the shared full CellClass
layout and a typed tag pointer. The six affected existing bodies remain exact.
`GetInstance` now uses native `new TagClass(...)`, pinned to no-GX; the
`TagClass::Construct` stand-in is gone. `DeleteAll` retains a documented primary-slot
call view, because the complete COM inheritance graph remains unreconstructed.

The existing 30-byte deleting entry at `0x6E58B0` now belongs to TagClass
instead of an opaque sweep host. It calls the native destructor declaration
and conditionally deallocates. The TagClass registry and deferred list, the
coordinate source, and two constructor registry prefixes have loader-zero
storage evidence; this does not prove runtime setup. TagTypeClass's raw RTTI
name confirms `class`, and the source class key and affected manglings now agree.
All eight affected TagTypeClass bodies remain exact.

The [AbstractClass constructor](match/core/abstract_class_ctor.cpp) is also
represented by its native C++ constructor, preserving the preceding partial
body's bytes and relocation offsets exactly. It remains a 71-byte partial row
at the recorded 81.2%; this migration adds no exact-match claim.

The [WarheadTypeClass](match/core/vector_warheadtypeclass_methods.cpp) and
[SuperWeaponTypeClass](match/core/vector_superweapontypeclass_methods.cpp) vector
pairs contain 24 exact rows: 16 new matches and eight migrated claims. The
Warhead migrations replace four incorrect BufferHolder owner models. Their
four seven-slot tables pass conditional `--weak-defaults` checks on project
objects. GX/no-GX probes pin no-GX for full derived deleting bodies, and focused
REA confirms all 24 complete entry spans.

The `/dll /noentry /nodefaultlib` diagnostic link still fails with 4,146 unique
unresolved symbols (6,356 reference lines), with no duplicate definitions.
Native TagClass and AbstractClass constructor symbols now resolve. The native
TagClass destructor and TriggerClass constructor remain unresolved; normalized
function comparisons do not establish those implementations. Default libraries
are excluded, so these counts are not an engine-only function-gap census.
Engine link closure and whole-image comparison remain unfinished.

Matched function lengths total 264,541 bytes (258 KiB): 18.8% of listed
functions and 7.0% of listed function lengths. The padding heuristic misses
200 matched entries. Residual vector families contain 249 generic deleting
bindings across 128 instantiation views, 125 base Clear rows, 123 native
dynamic Clear rows plus one DiskID stand-in, and 16 resize rows. The separate
30-byte deleting-body sweep has 75 remaining rows.

## Previous verified integration: native type vectors and shared TagClass storage

The [SmudgeTypeClass](match/core/vector_smudgetypeclass_methods.cpp) and
[OverlayTypeClass](match/core/vector_overlaytypeclass_methods.cpp) vector pairs
contain 24 exact rows: 16 new matches and eight migrated claims. Their four
RTTI-backed seven-slot tables pass conditional `--weak-defaults` checks against
project objects. GX/no-GX probes pin no-GX for the full derived deleting bodies.
Focused REA analysis confirms the complete entry spans.

[ObjectClass::FUN_005F5F30](match/core/object_class_cell_methods.cpp) adds a
seven-byte exact getter for `Location.Z`; its original method name is unknown.
Seven existing TagClass methods now use the shared layout declaration. The
const TagType query callees and Trigger notification names now resolve to
existing matched implementations. Eleven affected function bodies remain exact.
Four methods retain conflicting legacy class definitions. These require
consolidation into one definition before an integrated C++ build can satisfy
the one-definition rule; complete TagClass hierarchy consolidation is pending.

[TagClass::Array](match/ai/tag_class_array.cpp) now has one 24-byte BSS
definition, consistent with the pinned image's loader-zero section tail.
This establishes initial storage, not later runtime initialization. The
`/dll /noentry /nodefaultlib` diagnostic link reports 4,156 unique unresolved
symbols (6,368 reference lines) and no duplicate definitions. The former
registry alias and the shared registry symbol are absent from unresolved
references. Default libraries remain excluded; this is not an engine-only gap
count. Engine link closure and whole-image comparison remain unfinished.

Matched function lengths total 263,025 bytes (257 KiB): 18.7% of listed
functions and 6.9% of listed function lengths. The padding heuristic misses
198 matched entries. Residual vector families contain 251 generic deleting
bindings across 129 instantiation views, 126 base Clear rows, 124 native
dynamic Clear rows plus one DiskID stand-in, and 16 resize rows.

## Previous verified integration: shared object accessors and a pinned-image oracle

The [InfantryTypeClass](match/core/vector_infantrytypeclass_methods.cpp) and
[TerrainTypeClass](match/core/vector_terraintypeclass_methods.cpp) vector pairs
contain 24 exact rows: 15 new matches and nine migrated claims. Each pair has
two RTTI-backed seven-slot tables. All four pass scoped checks against project
objects with conditional `--weak-defaults` resolution. GX/no-GX probes pin the
no-GX mode for their full derived deleting bodies. Focused REA analysis also
confirmed all 24 contiguous entry spans after the shared bridge became free.

The existing [object accessors](match/core/object_class_methods.cpp) now live
on the shared `ObjectClass`: `AttachTrigger` (49 bytes),
`SetHealthPercentage` (72 bytes), and `IsRedHP` (74 bytes). They use the common
object/type layouts and `RulesInstance`. The unsupported separate function
claim at `0x5F5B4C` was removed: it contains four NOPs before the evidenced
`0x5F5B50` entry, with no function record or xrefs in the current Ghidra analysis.
There was no manifest row at that address, so this does not remove a match.
The wrapper header and fake accessor host are retired. Method names remain
consult-only hypotheses where the binary does not establish their spelling.

The [level methods](match/core/object_class_level_methods.cpp) now reuse the
shared `CellClass` layout and assert each consumed field and slot offset.
All three remain exact. [FlightLevel](match/core/flight_level.cpp) has one
four-byte BSS definition, matching the pinned PE's loader-zero tail; this does
not claim knowledge of later runtime initialization. The Team attach call and
two Building health checks now use native ObjectClass declarations. The
Building garrison-owner row remains partial; its instruction bytes and
relocation offsets are unchanged from the preceding compiled snapshot.

Setting `GAMEMD_BINARY` selects direct PE reads in both byte and instruction
oracles. The reader verifies the SHA-256 and requires the whole span to be
backed by exactly one PE section; invalid configured images fail without a
bridge fallback. Seven synthetic tests cover identity and boundary failures.
With no image selected, the existing Ghidra reader remains available. This
lets byte verification proceed independently of queued decompilation analysis;
the finalized eight-shard full regression took 31.66 seconds in this run.
See [CONTRIBUTING.md](CONTRIBUTING.md) for use.

The `/dll /noentry /nodefaultlib` diagnostic link still fails with 4,179 unique
unresolved symbols (6,406 reference lines), and no duplicate definitions.
The consolidated Rules, FlightLevel, Team attach and Building health symbols
no longer appear among its unresolved references. Default libraries are
excluded, so the total is not an engine-only function-gap count. Link closure
and whole-image comparison remain unfinished.

Matched function lengths total 261,897 bytes (256 KiB): 18.6% of listed
functions and 6.9% of listed function lengths. The padding heuristic misses
196 matched entries. Residual vector families contain 255 generic deleting
bindings across 131 instantiation views, 128 base Clear rows, 126 native
dynamic Clear rows plus one DiskID stand-in, and 16 resize rows.

## Previous verified integration: ObjectClass sorting and native type vectors

The [AircraftTypeClass](match/core/vector_aircrafttypeclass_methods.cpp) and
[UnitTypeClass](match/core/vector_unittypeclass_methods.cpp) vector pairs contain
24 exact rows: 15 new matches and nine migrated claims, including the Unit
resize body at `0x4EDEA0`. All four RTTI-backed seven-slot tables pass scoped
checks against project objects with conditional `--weak-defaults` resolution.
Paired GX/no-GX probes pin the no-GX mode for the full derived deleting bodies.

[ObjectClass::FUN_005F6220](match/core/object_class_sort_methods.cpp) adds a
38-byte exact comparator. It calls primary slot `+0xB8` on both objects and
returns whether the receiver's signed result is greater. Its original name is
unknown. Two compact typed-call variants changed four register-staging bytes;
the exact source retains an explicitly documented abstract call view. This
models the call ABI, not original virtual ownership or complete concrete tables.

The shared `ObjectClass` declaration now owns the existing `GetYSort` and
`IsCrushable` methods. The native [GetYSort implementation](match/core/object_class_ysort_methods.cpp)
remains exact for all 54 bytes, and its separate host/interface header is
retired. The 195-byte [IsCrushable implementation](match/core/object_class_crushable_methods.cpp)
uses the shared object/type prefixes, sparse techno views, and the existing
const House ally overload. All three [House ally methods](match/economy/house_class_ally_methods.cpp)
remain exact and use the shared object layout. Their slot-call views make no
complete hierarchy claim; existing names/const qualifiers remain source-level
hypotheses where the instructions cannot prove them.

The LayerClass declaration now uses its retail RTTI class key at `0x816B10`,
and its `ObjectClass*` argument uses the canonical class-pointer mangling.
`AddObject` remains exact. The bounded `SortedAdd` probe at `0x551A90` did not
match; its draft remains outside the repository and the address is unclaimed.

The local `/dll /noentry /nodefaultlib` diagnostic link still fails with 4,200
unique unresolved symbols (6,441 reference lines) and no duplicate definitions.
Default libraries are excluded, so these counts do not measure engine-only
function gaps. Link closure and whole-image comparison remain unfinished.

Matched function lengths total 260,937 bytes (255 KiB): 18.5% of listed
functions and 6.9% of listed function lengths. The padding heuristic misses
194 matched entries. Residual vector families contain 259 generic deleting
bindings across 133 instantiation views, 130 base Clear rows, 128 native
dynamic Clear rows plus one DiskID stand-in, and 17 resize rows.

## Previous verified integration: native type vectors and shared class declarations

The native [AnimTypeClass](match/core/vector_animtypeclass_methods.cpp) and
[BuildingTypeClass](match/core/vector_buildingtypeclass_methods.cpp) vector pairs
contain 24 exact function rows: 16 new matches and eight migrated claims.
Each pair has two RTTI-backed seven-slot tables; all four pass scoped checks
against the project objects with conditional `--weak-defaults` resolution.
Paired compiler probes pin no-GX flags: GX emits a short derived deleting
wrapper instead of the complete retail body. No constructors, TypeList tables,
original TU grouping or final linker placement are claimed by this batch.

Retail RTTI TypeDescriptors at `0x8177C8` and `0x817AF8` establish the class
keys for `AbstractClass` and `ObjectClass`. Their shared headers now use
`class` with public access and unchanged field layouts. Nine affected manifest
symbols were updated from source COFF struct-pointer mangling to class-pointer
mangling; all nine full bodies still match. These are compiler symbol names,
not names recovered from the stripped retail executable. Isolated local
struct declarations remain a follow-up; this is not a complete hierarchy or
linkage reconstruction.

The verifier now rejects nonzero compiler exits even when an object exists,
and rejects failed oracle commands that print a success percentage. The two
new tests cover those cases. The local `/dll /noentry /nodefaultlib` diagnostic
link has no duplicate definitions and reports 4,217 unique unresolved symbols
(6,472 reference lines). It still fails to link; default CRT/import libraries
are deliberately excluded, so these counts do not measure engine-only gaps.

Matched function lengths total 259,939 bytes (254 KiB): 18.5% of listed
functions and 6.8% of listed function lengths. The padding heuristic misses
192 matched entries. The residual vector families contain 263 generic deleting
bindings across 135 instantiation views, 132 base Clear rows, and 130 native
dynamic Clear rows plus one DiskID stand-in. The resize family has 18 rows.
These are intermediate verification results, not whole-image identity.

## Previous verified integration: ObjectClass health and TerrainClass / ParticleSystemClass vectors

Native vector clusters for [TerrainClass](match/core/vector_terrainclass_methods.cpp)
and [ParticleSystemClass](match/core/vector_particlesystemclass_methods.cpp)
add 24 address rows: 16 new exact matches and eight migrated claims. Both
classes have two RTTI-backed seven-slot tables. All four tables passed
conditional seven-slot checks against project objects using `--weak-defaults`,
without manual symbol maps.

The shared [ObjectClass health implementation](match/core/object_class_health_methods.cpp)
contains three full-span matches: `GetHealthPercentage` at `0x5F5C60` (32
bytes), `FUN_005F5D20` (112 bytes), and `GetHealthStatus` at `0x5F5DD0`
(169 bytes). The predicate name at `0x5F5D20` remains unconfirmed by the
binary. The three sparse Building views now inherit the confirmed `ObjectClass`
prefix and call its native health method; the intermediate direct-base
hierarchy is not reconstructed.

The shared [RulesClass view](match/core/rules_class.h) asserts the observed
fields at `+0x244`, `+0x54C`, `+0x1700`, `+0x1708`, and `+0x1804`. Its consumers
use the canonical `RulesInstance` pointer. This is a sparse layout; it makes
no full-size or complete-class claim. The integrated objects now reference the
canonical `ObjectClass::GetHealthPercentage` and `RulesInstance` symbols; the
three former health aliases and three Rules pointer aliases are absent from
the current diagnostic.

The eight-shard regression, compile gate, tracked-source object build and hash
check passed: 3,630 functions matched, 165 rows remain partial, all 884 tracked
C++ files produced objects, and the manifest contains 880 translation units.
All 66 verifier tests passed. The `/dll /noentry /nodefaultlib` diagnostic
reports zero `LNK2005` duplicate definitions, 6,502 `LNK2001` unresolved
reference lines and 4,233 unique unresolved symbols (`LNK1120`), down from
4,255. Default libraries are excluded, so this diagnostic does not establish
engine link closure. The tracked object build also passes `--check` against
the saved hashes.

Matched function bodies total 258,803 bytes (253 KiB, 18.4% of listed
functions and 6.8% of listed function-body bytes). The padding heuristic misses
190 currently matched entries. Current vector-family totals are 267 generic
deleting-destructor bindings across 137 instantiation views, 134 base `Clear`
rows, 132 native dynamic `Clear` rows plus one separate DiskID stand-in (133
dynamic rows total), and 18 address-specific resize views.

`GetFloorHeight` at `0x47B3A0` remains an unclaimed call target; the current
14% probe has a 148-byte real-instruction run and has not been promoted to a
function claim. No field-value fact is certified from that probe.

## Previous verified integration: AircraftClass, UnitClass, CellClass and CurrentFrame

Two native vector clusters add 24 address rows across
[AircraftClass](match/core/vector_aircraftclass_methods.cpp) and
[UnitClass](match/core/vector_unitclass_methods.cpp): 16 new matched claims and
eight migrated claims. Each class has vector-template methods; all four
affected vector tables passed conditional seven-slot checks against project
objects using `--weak-defaults` without manual symbol maps.

[CellClass::GetCoords](match/map/cell_class_get_coords.cpp) at `0x486840` has a
focused 100% comparison over its complete 73-byte span. It uses the existing
explicit-vptr `CellClass` layout to bind a nonvirtual const-member symbol. This
does not establish the complete virtual hierarchy or vtable.

The shared [`CurrentFrame` declaration](match/core/frame_counter.h) and its
[single definition](match/core/frame_counter.cpp) use address `0xA8ED84`. The
retail operand audit validated 96 `DIR32` references to that address across 68
matched functions in 41 translation units. The PE maps `.data` from VA
`0x812000` with virtual size `0x367BE4`, while only `0x6C000` bytes are
file-backed; `0xA8ED84` lies in the zero-filled virtual tail. This supports the
zero-initialized `int` storage declaration, but does not recover all runtime
writes or prove the counter's original namespace. The `DrawLinks` function at
`0x472160` remains partial; its entry-origin evidence observes a reference to
the counter at `0x4721A3`.

The eight-shard regression, compile gate, tracked-source object build and hash
check passed at that snapshot. The build produced objects for all 882 tracked
C++ files; the manifest contained 878 translation units. The verifier suite
had 66 passing tests, including the BSS-object parsing fixture.

The `/dll /noentry /nodefaultlib` diagnostic at that snapshot reported zero
`LNK2005` duplicate definitions, 6,538 `LNK2001` unresolved-reference lines
and 4,255 unique unresolved symbols (`LNK1120`), down from 4,283. This
diagnostic excludes default libraries and does not establish engine link closure. The shared
[RulesClass layout and declaration](match/core/rules_class.h) use the observed
member offsets at `0x54C` and `0x1804`, and one
[`RulesInstance` definition](match/combat/rad_site_class_methods.cpp) serves
both consumers. The `CurrentFrame` audit found one 4-byte BSS definition and
resolved its former aliases in the link diagnostic. `GetFloorHeight` at
`0x47B3A0` remains an unmatched native call target.

At that snapshot, vector-family totals were 271 generic deleting-destructor bindings
across 139 instantiation views, 136 base `Clear` rows, 134 native dynamic
`Clear` rows plus one separate DiskID stand-in (135 dynamic rows total), and 18
address-specific resize views.

## Previous fully verified batch: BulletClass and CampaignClass vectors

Two native mutable-pointer vector clusters are integrated: 12 address rows
each for `BulletClass*` and `CampaignClass*`, for 24 rows total. The batch adds
16 new exact-match claims and migrates eight prior address claims. Each class
has two RTTI-backed seven-slot tables. The eight-shard regression and compile
gates passed; all four affected tables passed conditional seven-slot checks
against persistent project objects using `--weak-defaults`, without manual
symbol maps. The tracked-project object build compiled all 878 translation
units, and `--check` confirmed the saved input and object hashes. These checks
do not establish engine link closure or whole-image identity.

A VC6 diagnostic link with `/dll /noentry /nodefaultlib` reported no duplicate
definitions (`LNK2005`), down from two in the previous diagnostic. It still
reported 6,615 unresolved-reference lines (`LNK2001`) and 4,283 unique
unresolved symbols (`LNK1120`). This diagnostic excludes default libraries and
does not constitute an engine link.

The two prior duplicate-definition conflicts were addressed by sharing the
[RadSiteClass declarations](match/combat/rad_site_class_methods.h) and keeping
one `RulesInstance` definition in the shared
[implementation](match/combat/rad_site_class_methods.cpp). The [SidebarClass
declarations](match/ui/sidebar_class_methods.h) are also shared; the distinct
classifier at `0x6ABC60` remains separate from `GetObjectTabIdx` at `0x6ABCD0`.
The latest diagnostic reports zero `LNK2005` conflicts after these changes.

At that earlier snapshot, vector-family totals were 275 generic deleting-destructor bindings
across 141 instantiation views, 138 base `Clear` rows, 136 native dynamic
`Clear` rows plus one separate DiskID stand-in (137 dynamic rows total), and 18
address-specific resize views.

The tracked-source object build is available through
[`build_project.py`](scripts/vc6/build_project.py). It compiles tracked C++
translation units to path-preserving VC6 objects and records input and object
hashes. Its `--check` mode verifies those hashes and rejects stale indexes; it
does not link. The new object-build target is not an integrated engine build.

## Previous fully verified batch: InfantryClass and FoggedObjectClass vectors

The mutable-pointer `InfantryClass*` and `FoggedObjectClass*` clusters add 24
address rows across [InfantryClass](match/core/vector_infantryclass_methods.cpp)
and [FoggedObjectClass](match/core/vector_foggedobjectclass_methods.cpp): 15 new
exact matches and nine migrated claims. Each class has two RTTI-backed
seven-slot tables; no TypeList specialization, constructor, or complete
object-size claim is made. The sources assert the accessed vector member
offsets and 4-byte pointer size. They compile with `/O2 /DNDEBUG /Gy` and `/GX`
disabled; the full-span dynamic deleting-destructor bodies match under those
flags. Four affected tables pass conditional seven-slot checks against the
integrated objects using `--weak-defaults`, without manual symbol maps. Full
regression and compilation gates passed; final-link resolution remains
unverified.

## Previous fully verified batch: HouseClass and TagClass vectors

The mutable-pointer `HouseClass*` and `TagClass*` clusters add 24 address rows
across [HouseClass](match/core/vector_houseclass_methods.cpp) and
[TagClass](match/core/vector_tagclass_methods.cpp): 15 new exact matches and
nine migrated claims. Each class has two RTTI-backed seven-slot tables; no
TypeList specialization, constructor, or complete object-size claim is made.
The sources assert the accessed vector member offsets and 4-byte pointer size.
They compile with `/O2 /DNDEBUG /Gy` and `/GX` disabled; the full-span dynamic
deleting-destructor bodies match under those flags. Four affected tables pass
conditional seven-slot checks against the integrated objects using
`--weak-defaults`, without manual symbol maps. Full regression and compilation
gates passed; final-link resolution remains unverified.

## Tracked source inventory

[`scripts/vc6/source_inventory.py`](scripts/vc6/source_inventory.py) reports
tracked `.cpp` paths by subsystem, their manifest rows and the VC6 flags selected
from each source marker or the wrapper default. Run it from the repository root:

```bash
python3 scripts/vc6/source_inventory.py --out /tmp/source-inventory.json
```

It enumerates source paths with `git ls-files`; the output describes tracked
paths, while content is read from the current worktree. At the latest fully
verified snapshot, the inventory has 901 tracked C++ files and 3,876 manifest
rows, with no manifest TU missing from tracked sources. Six tracked files
had no manifest rows and two source basename collisions; the report lists
those cases explicitly.
An ambient `VC6_FLAGS` setting overrides the per-file marker and wrapper
default at compile time.

## Previous fully verified batch: AbstractClass, FootClass and BuildingClass

Three mutable-pointer vector clusters are integrated: 12 entries each for
`AbstractClass*`, `FootClass*` and `BuildingClass*`, across
[AbstractClass](match/core/vector_abstractclass_methods.cpp),
[FootClass](match/core/vector_footclass_methods.cpp) and
[BuildingClass](match/core/vector_buildingclass_methods.cpp). Together they
contain 36 address rows: 22 new exact-match candidates and 14 migrated claims.
Each class has two RTTI-backed seven-slot tables; no TypeList specialization or
constructor claim is made. The implementations assert the accessed member
offsets and 4-byte pointer size, without asserting complete class sizes.
The eight-shard whole-repository regression and compile gates passed. All six
affected tables pass seven-slot checks against the integrated objects using
`--weak-defaults` without manual symbol maps. These are conditional object-level
checks; final-link resolution remains unverified.

After that batch, the tree had 281 generic deleting-destructor bindings across 144
instantiation views, 141 base `Clear` rows, 139 native dynamic `Clear` rows
plus one separate DiskID stand-in, and 19 address-specific resize views.

**gagarin** reconstructs the *Command & Conquer: Red Alert 2 — Yuri's Revenge*
engine, retail `gamemd.exe` **v1.001**, as a coherent, human-readable C++ project.
The ultimate goal is a buildable, structured C++ project that reproduces the
complete v1.001 `gamemd.exe` byte for byte. Its classes, inheritance,
interfaces, source organization and coding style should be as close to
Westwood's original project as the evidence allows. Preserving the engine through
this reconstruction is the deliverable: readable C++, shared engine types and
implementations, and an integrated build. This goal has not been achieved;
reconstruction is in progress.

Per-function instruction matching under the MSVC 6-era toolchain is an
intermediate fidelity check. The final target requires an integrated project
build and a comparison of the complete executable, without byte masking.

## Why

This project preserves engine code by reconstructing C++ from the retail
binary and checking annotated functions mechanically against it. The target
image is identified by its SHA-256 in [reccmp-project.yml](reccmp-project.yml).
The project works from that binary; it does not claim to have recovered
Westwood's original source files.

## Earlier verified vector consolidation snapshot (3,527 matches)

Five native vector-class translation units contain 66 function rows: 12 in
[AnimClass](match/core/vector_animclass_methods.cpp), 13 in
[MultiMissionClass](match/core/vector_multimission_methods.cpp), 12 for
[`const char*`](match/core/vector_const_char_methods.cpp), 12 for
[`const unsigned short*`](match/core/vector_const_ushort_methods.cpp), and 17
for [SmudgeTypeClass](match/core/vector_smudgetype_methods.cpp). The batch adds
38 exact rows and migrates 28 address claims. MultiMission's
probe used `/Ob2` with `/GX` disabled. The corrected SmudgeType probe also used
the no-`/GX` candidate; all 17 typed rows compared 100% over their checked
retail spans. An earlier `/GX`-inherited probe was misconfigured and did not
establish a source mismatch. The whole-repository regression and compile gates
pass for this batch.

The aggregate is 3,527 exact rows, 165 partial rows and 866 manifest
translation units; matched body lengths total 251,906 bytes (246 KiB, 17.9% of
listed function bytes). The worktree has 869 tracked C++ files. All eleven
affected class tables pass seven-slot checks against the integrated objects
using `--weak-defaults` and no symbol map. This is conditional object-level
evidence; it does not establish final-link resolution.

The batch adds or migrates the following vector-family bindings: generic
deleting-destructor family 287 bindings across 147 instantiation views; 144
base `Clear` rows and 142 native dynamic `Clear` rows, plus the separate DiskID
stand-in; 21 address-specific and five generic resize views; 36 base POD
constructor rows; and eight DynamicVector POD constructor rows, unchanged from
the previous snapshot. All 13 entries from the former address-scoped copy
family now live in class-specific native translation units. The former copy,
default-constructor and capacity-constructor banks have been retired after
their claimed rows moved.

MultiMission contributes 13 entries and uses `/O2 /DNDEBUG /Gy /Ob2` with
`/GX` disabled; its base capacity constructor is at `0x5EF0B0`. The const-char
and const-unsigned-short clusters each contribute 12 entries and two
RTTI-backed tables, with no constructor or TypeList claim. The corrected
SmudgeType no-`/GX` candidate matches all 17 checked typed entries at 100%; its
Vector, DynamicVector and TypeList deleting-destructor bodies are emitted as
their actual class symbols. This supersedes the previous probe's apparent
short-body issue, which came from inheriting `/GX`; no shim or cross-mapping is
needed. The full gates passed with 58 tests and no duplicate addresses.

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
| Integrated project build | A tracked-source object build exists in [build_project.py](scripts/vc6/build_project.py); the engine has not been linked. The existing compile gate also compiles translation units separately. | Resolve remaining project dependencies, establish an integrated engine link, and account for library dependencies. |
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
- [Surface](match/renderer/surface_class.h): eight matched entries share the
  confirmed Surface prefix: its constructor, six ordinary methods, and the
  compiler-generated scalar deleting destructor in its
  [implementation](match/renderer/surface_class.cpp). The empty inline destructor
  models the body embedded in that deleting destructor; no separate ordinary
  destructor entry is bound. Its rectangle result now uses the shared XYWH
  layout, as confirmed by downstream clipping operations. The interface pins
  34 virtual slots and asserts Width/Height offsets; unknown signatures remain placeholders, and complete
  Surface and derived sizes remain unconfirmed.
- [XSurface](match/renderer/xsurface_class.h): seven methods share one native
  [implementation](match/renderer/xsurface_class.cpp) and the confirmed Surface
  base, replacing the Unlock stand-in and adding six exact methods. Bounded
  pixel reads and writes use asserted point and XYWH rectangle layouts; the
  fill wrapper obtains its bounds through the shared Surface interface.
  The lock-counter offset is asserted, and the two added virtual slots through
  `+0x8C` have native bodies. Other inherited slot overrides, the deleting
  destructor binding and complete object size remain unfinished.
- [BSurface](match/renderer/bsurface_class.h): native bytes-per-pixel and pitch
  methods share the confirmed `BSurface → XSurface → Surface` chain and asserted
  member offsets. Its owned-buffer view now has a shared header. Lock, lifetime
  code and ABuffer's separate `BSurfaceLayout` call interface remain to consolidate;
  complete size and all inherited signatures are unconfirmed.
- [VectorClass and DynamicVectorClass](match/core/vector_class.h): shared
  seven-slot templates replace the base `PlainVector` and dynamic
  `CountedVector::Destroy` stand-ins. The family files bind 144 base and 142
  native dynamic `Clear` entries; one separate DiskID row remains a stand-in.
  The [ToolTip-pointer specialization](match/ui/tooltip_vector_methods.cpp)
  binds twelve matched entries: eight other virtual methods, two `Clear` bodies,
  and two compiler-generated scalar deleting destructors. ToolTipManager uses
  these templates with its RTTI-confirmed const element type.
  [Layout assertions](match/core/vector_class_layout_asserts.cpp) check actual
  template members and sizes under VC6. The [int specialization](match/core/vector_int_methods.cpp)
  binds fifteen entries, including both seven-slot tables' distinct methods,
  copy constructor and two capacity constructors. The separate TypeList<int>
  specialization has three entries, including its default constructor. All
  thirteen entries from the former address-scoped copy-constructor family now
  use native templates: the int pair and three pointer entries from the former
  address-scoped copy-constructor bank,
  the AnimType pointer specialization described below, one copy constructor in
  each of the UnitType, AircraftType, InfantryType and BuildingType
  implementations, two in the VoxelAnimType implementation, and one in the
  ParticleSystemType implementation.
  Raw RTTI preserves their pointee const qualifiers; copying allocates and copies
  Capacity elements. Additional emitted methods and other copy specializations
  remain unverified.
  The two const SmudgeType capacity constructors are now in the native
  [SmudgeType implementation](match/core/vector_smudgetype_methods.cpp).
  Capacity constructors for BuildingType, VoxelAnimType, TerrainType and
  ParticleSystemType now reside in their native class implementations, as do
  those for UnitType, AircraftType and InfantryType. AnimType, int and mutable
  TechnoType capacity constructors remain in their own translation units.
  Extra emitted methods are not newly claimed by these constructor clusters, and
  final-link selection remains unverified.
  Three native no-`/GX` class-cluster implementations cover 51 matched
  functions, 17 each across the vector templates for `const UnitTypeClass*`,
  `const AircraftTypeClass*` and `const InfantryTypeClass*`: [UnitTypeClass](match/core/vector_unittype_methods.cpp),
  [AircraftTypeClass](match/core/vector_aircrafttype_methods.cpp) and
  [InfantryTypeClass](match/core/vector_infantrytype_methods.cpp). They add 22
  exact matches and rehome 29 prior address claims. The UnitType cluster has a `TypeList` default constructor at
  `0x67A740`; its copy constructor is `TypeList` at `0x513740`. AircraftType
  has a `TypeList` default constructor at `0x512960` and copy constructor at
  `0x5137D0`. InfantryType's copy constructor at `0x513860` belongs to
  `DynamicVectorClass`, while its `TypeList` default constructor is at
  `0x67A820`. All nine seven-slot tables pass conditional COFF weak-default
  checks against retail; final-link resolution remains unverified. The three
  cluster files assert the member offsets they use, but do not claim complete
  object sizes.
  Four more native no-`/GX` class clusters cover 68 matched functions across
  `const BuildingTypeClass*` (17), `const VoxelAnimTypeClass*` (18),
  `const TerrainTypeClass*` (16) and `const ParticleSystemTypeClass*` (17):
  [BuildingTypeClass](match/core/vector_buildingtype_methods.cpp),
  [VoxelAnimTypeClass](match/core/vector_voxelanimtype_methods.cpp),
  [TerrainTypeClass](match/core/vector_terraintype_methods.cpp) and
  [ParticleSystemTypeClass](match/core/vector_particlesystemtype_methods.cpp).
  They add 28 exact matches and rehome 40 existing address claims. Their twelve
  seven-slot tables pass conditional COFF weak-default checks against retail;
  final-link resolution remains unverified. Their implementations assert the member
  offsets they use, without claiming complete object sizes.
  The AnimType pointer implementation in
  [vector_animtype_methods.cpp](match/core/vector_animtype_methods.cpp) covers
  seventeen matched functions across
  `VectorClass<const AnimTypeClass*>`,
  `DynamicVectorClass<const AnimTypeClass*>` and
  `TypeList<const AnimTypeClass*>`. All seventeen match their complete retail
  spans; eight addresses add new match claims and nine rehome existing claims.
  Its three tables also pass conditional COFF weak-default checks. These
  results do not establish whole-image identity.
  The native integration covers fifteen entries
  across `VectorClass<TechnoTypeClass*>`, `DynamicVectorClass<TechnoTypeClass*>`
  and `TypeList<TechnoTypeClass*>`: thirteen virtual or deleting-destructor
  bodies and two capacity constructors. Seven entries are new exact matches;
  the other eight rehome existing address claims. These TechnoType specializations
  use mutable pointer elements; they do not change the const-qualified ToolTip
  specialization above. Three additional native vector clusters cover 40
  entries across [TeamTypeClass](match/core/vector_teamtype_methods.cpp),
  [MPlayerScoreType](match/core/vector_mplayer_score_methods.cpp) and
  [const TechnoTypeClass](match/core/vector_const_technotype_methods.cpp).
  TeamType and MPlayerScoreType each cover 14 entries, adding eight exact
  matches and rehoming six claims apiece. The const-TechnoType cluster covers
  12 entries, adding seven exact matches and rehoming five claims. TeamType
  has three RTTI-backed tables, but this batch makes no TypeList constructor
  claim. MPlayerScoreType uses a mutable struct-pointer
  element type and has two RTTI-backed tables; it makes no TypeList or dynamic
  capacity-constructor claim, and its base capacity constructor at `0x5C59E0`
  moved from a POD helper into the native class implementation. Raw const-
  TechnoType RTTI establishes VectorClass and DynamicVectorClass specializations
  but no TypeList specialization or constructor address. All seven affected
  tables pass conditional COFF weak-default checks against retail; final-link
  resolution remains unverified. The batch passed the whole-repository
  regression and compilation gates. The native SmudgeType implementation now
  covers 17 entries across VectorClass, DynamicVectorClass and TypeList,
  including the former capacity, copy and default-constructor bindings. All
  three seven-slot tables pass conditional checks; complete object size and
  final-link resolution remain unestablished. The generic deleting-destructor
  family has 287 bindings across 147 base-template instantiation views. Their written vptr and
  RTTI identify the base-destruction path and element type, but do not
  establish each wrapper's original declaring class, source-file boundaries,
  or duplicate-COMDAT linker behavior. The int and ToolTip specializations
  account for the slot-zero targets in their retail base and derived tables.
  The dynamic `Clear` total excludes the DiskID entry at `0x69C4A0`, which
  retains the `CountedVector<DiskID>::Destroy` matching stand-in because its
  retail declaring class is unresolved; other legacy users are marked
  `VectorClassLayout` or `DynamicVectorClassLayout`. Other virtual methods and
  original source-file ownership remain incomplete.
  The resize helpers retain 21 address-specific views and five generic resize
  views. SmudgeType's `0x67B050` SetCapacity body now has a native binding.
- [TypeList](match/core/type_list.h): the int specialization has three native
  entries: its copy constructor, default constructor and generated deleting
  destructor in [one implementation](match/core/typelist_int_methods.cpp).
  The SmudgeType pointer default is now in its native class implementation.
  AnimType, BuildingType, VoxelAnimType, TerrainType, ParticleSystemType,
  UnitType, AircraftType and InfantryType defaults are in their native class
  implementations. The mutable TechnoType pointer
  batch covers native VectorClass, DynamicVectorClass and TypeList specializations. Their three
  seven-slot tables each pass a conditional COFF weak-default check for the
  deleting-destructor slot; final-link resolution remains unverified.
  Raw RTTI and vtable slots establish inherited prefixes; complete sizes and
  absence of additional members are not claimed.
- Shared [2D geometry](match/_layout/geometry2d.h): renderer, radar, building
  layout and cell-redraw declarations use one XYWH `RectangleStruct` definition.
  BitFont's left/top/right/bottom bounds remain a distinct asserted type.
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
  resolving reconstructed engine dependencies through shared declarations and
  implementations, while accounting for library dependencies separately.
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
| Functions matched at 100% | **3,711** | **18.8%** of 19,753 |
| Sum of matched function lengths | 258 KiB | 7.0% of 3,708 KiB of listed function lengths |
| Functions in progress (partial match) | 165 | 0.8% |
| Tracked C++ files under `match/` | 901 | |
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
listed entries, including 200 matched entries. Its candidate count is therefore
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
