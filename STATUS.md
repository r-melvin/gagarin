# Project status

As of **2026-10-22**, the verified snapshot reports **6,419 matched function
rows**, **415 partial rows**, **6,834 manifest rows**, **1,273 manifest
translation units**, and **1,281 tracked C++ files**. Whole-repository regression
verification, the project object build and 142 tooling tests pass, and the
compile/layout check passes on the tracked tree.

The ten vector stream-save entry points (0x67A3C0 family) are now modelled as
__thiscall members instead of __fastcall free functions with an unused EDX
parameter, and all ten match. 0x4103E0, Randomizer::RandomRanged (0x65C7E0)
and the RGB-to-HSV conversion (0x6613A0, 84.7% to 97.5%) also improve. An inert
`if (1) {}` that a permuter run had left in 0x407170 is removed, so that row is
now an honest partial at 89.5%. Two redundant aliases in
FlyLocomotionClass::MoveTo (0x4CCC80) are removed with no byte change (47.7%).
Every new exact row passes raw bytes and strict relocation checks.

The 6,419 matches represent 32.5% of 19,753 listed functions. Counts are per
function, not executable completion. Matched body lengths total **492,751
bytes**, or 13.0% of 3,797,269 listed function bytes. The padding heuristic
misses 531 matched entries. The last diagnostic link, taken before the second
cleanup batch, reported **4,186 unique unresolved symbols**, **6,731 reference
lines**, and zero duplicate definitions. Engine link closure remains unfinished.

## Historical integration archive


The integration records below are historical batch snapshots. Their
batch-specific counts describe earlier states and are
superseded by the current totals above. They are retained as evidence of the
sequence and scope of completed work, with each batch's recorded caveats. Later fidelity audits can invalidate an earlier reported match; the archived literal correction is one such example.

## Historical snapshot: AbstractClass COM bases

As of **2026-10-22**, the verified snapshot reports **6,408 matched function
rows**, **426 partial rows**, **6,834 manifest rows**, **1,273 manifest
translation units**, and **1,281 tracked C++ files**. Whole-repository regression
verification, the project object build and 142 tooling tests pass, and the
compile/layout check passes on the tracked tree.

AbstractClass now derives its four COM interfaces (IPersistStream,
IRTTITypeInfo, INoticeSink and INoticeSource) as real base classes, so the
compiler emits the interface table stores, adjustor thunks and scalar deleting
destructors that retail has. Both AbstractClass constructors reach 100%, and
seven rows are new exact matches: the AbstractClass and AbstractTypeClass scalar
deleting destructors, the three IRTTITypeInfo adjustor thunks, and the
MissionClass and CaptureManagerClass scalar deleting destructors. The
CaptureManagerClass constructor is a new partial. The flag byte at +0x14 is
modelled once, as bool bit-fields: retail only ever reads and writes it with
byte operations. That also brings CellClass::TryAssignJumpjet (0x487D70) to
100%. Every new or changed exact row passes raw bytes and strict relocation
checks, and the six AbstractClass and AbstractTypeClass tables verify slot by
slot.

The 6,408 matches represent 32.4% of 19,753 listed functions. Counts are per
function, not executable completion. Matched body lengths total **491,826
bytes**, or 13.0% of 3,797,269 listed function bytes. The padding heuristic
misses 531 matched entries. The last diagnostic link, taken before the second
cleanup batch, reported **4,186 unique unresolved symbols**, **6,731 reference
lines**, and zero duplicate definitions. Engine link closure remains unfinished.

## Historical snapshot: claimed-leaf sweep

As of **2026-10-22**, the verified snapshot reports **6,399 matched function
rows**, **428 partial rows**, **6,827 manifest rows**, **1,273 manifest
translation units**, and **1,281 tracked C++ files**. Whole-repository regression
verification, compile/layout checks, the project object build and 142 tooling
tests pass.

A claimed-leaf sweep gives manifest rows to functions whose addresses were
mentioned or declared in tree but never scored: 101 are new exact matches and
11 are documented partials. The 17 existing bodies of the member-setter and
position-below-limit families are now scored; the ten setters become real
`__thiscall` members of Setter_00487C70. Ninety small leaves that other
translation units only declared get bodies in three new address-ordered sweep
translation units, and WideStringClass gains five members (its copy
constructor, 0x7B6780, 0x7B7110, 0x7B7180 and 0x7B7660). The stale
annotations at 0x4CAD50 and 0x70D180 are re-marked so each address has one
owner. Every exact row passes raw bytes and strict relocation checks. Across
all project objects, sections change only by the three new translation units,
the setter symbols (now members) and the five new WideStringClass bodies.

The 6,399 matches represent 32.4% of 19,753 listed functions. Counts are per
function, not executable completion. Matched body lengths total **491,319
bytes**, or 12.9% of 3,797,269 listed function bytes. The padding heuristic
misses 531 matched entries. The last diagnostic link, taken before the second
cleanup batch, reported **4,186 unique unresolved symbols**, **6,731 reference
lines**, and zero duplicate definitions. Engine link closure remains unfinished.

## Historical snapshot: mixed leaf batch

As of **2026-10-22**, the verified snapshot reports **6,298 matched function
rows**, **417 partial rows**, **6,715 manifest rows**, **1,268 manifest
translation units**, and **1,278 tracked C++ files**. Whole-repository regression
verification, compile/layout checks, the project object build and 142 tooling
tests pass.

A mixed leaf batch lands across platform, network, renderer, map, movement and
core code: 75 functions are new exact matches and 76 are documented partials.
Twelve existing partials become exact and two improve. The five blitter
specialisations 0x493CC0, 0x494B60, 0x494D90, 0x496820 and 0x497A10 are
replaced in place. The GadgetClass constructor (0x4E12F0) becomes exact once
LinkClass gains its inline constructor. The bodies at 0x4882D0, 0x5B2990 and
0x5CEAD0 stay with their existing owners, CheckListClass, Dir16 and MSAnim,
rather than new placeholder classes; the CheckListClass scalar deleting
destructor (0x4886E0) becomes exact with them. 0x5C61D0 now returns
`const unsigned short*` everywhere, since both callers read EAX as a word
table. 0x646480's partial score is re-measured at 89.4%. Three single-function
translation units that became empty are removed, and the XSurface circle
routine (0x7BB920) is declared in the shared renderer/surface_class.h. Every exact row
passes raw bytes and strict relocation checks. Across all project objects,
sections change only by the new and removed TUs, the replaced bodies, the
0x5C61D0 return type, the DAT_00A8DAB8 relocation symbol (now `unsigned int`,
identical bytes), and compiler label numbering in ColorListClass::DrawItem
(identical bytes and label offsets).

The 6,298 matches represent 31.9% of 19,753 listed functions. Counts are per
function, not executable completion. Matched body lengths total **488,715
bytes**, or 12.9% of 3,797,269 listed function bytes. The padding heuristic
misses 523 matched entries. The last diagnostic link, taken before the second
cleanup batch, reported **4,186 unique unresolved symbols**, **6,731 reference
lines**, and zero duplicate definitions. Engine link closure remains unfinished.

## Historical snapshot: UI input-controls module

As of **2026-10-22**, the verified snapshot reports **6,210 matched function
rows**, **354 partial rows**, **6,564 manifest rows**, **1,204 manifest
translation units**, and **1,214 tracked C++ files**. Whole-repository regression
verification, compile/layout checks, the project object build and 142 tooling
tests pass.

The UI input-controls module lands: the gadget, control, list, gauge, slider
and button families, the GScreen/Display/Scroll/Mouse chain, the sidebar
classes, the graphic menus, load-options, progress-screen and web-browser
screens, and the window-manager mouse. 165 functions are new exact matches
(including five constructors that are compiled so their translation units emit
the vtables and deleting destructors) and 35 are documented partials. Two
existing rows change symbol only: 0x48E600 becomes ControlClass::SetPeer and
0x559EB0 becomes a LoadOptionsClass virtual. The GadgetClass deleting
destructor and vtable come from the canonical constructor's translation unit,
so the constructor has a single definition; 0x4F42F0 keeps the name
GScreenClass::FlagToRedraw. VectorClass gains a member-template element
accessor. Every exact row passes raw bytes and strict relocation checks, and
the ten in-tree UI vtables verify every requested slot. Across all project
objects, sections change only by the new TUs, the two renamed symbols, the
GadgetClass slot names in four gadget vtables, ShapeButton's added slot 34, the
GadgetClass deleting destructor (now emitted with its body), one renamed
callee in ScenarioClass::PauseGame, and compiler label numbering in three
BuildingClass bodies (identical bytes and label offsets).

The 6,210 matches represent 31.4% of 19,753 listed functions. Counts are per
function, not executable completion. Matched body lengths total **460,381
bytes**, or 12.1% of 3,797,269 listed function bytes. The padding heuristic
misses 522 matched entries. The last diagnostic link, taken before the second
cleanup batch, reported **4,186 unique unresolved symbols**, **6,731 reference
lines**, and zero duplicate definitions. Engine link closure remains unfinished.

## Historical snapshot: vector, class-factory and generated-code quick wins

As of **2026-10-22**, the verified snapshot reports **6,045 matched function
rows**, **319 partial rows**, **6,364 manifest rows**, **1,164 manifest
translation units**, and **1,174 tracked C++ files**. Whole-repository regression
verification, compile/layout checks, the project object build and 142 tooling
tests pass.

Vector, class-factory and generated-code quick wins land: VectorClass and
DynamicVectorClass slot bodies for 36 element types, the TClassFactory<T>
template with its 77 instantiations, and compiler-generated deleting
destructors, persist Save stubs and refcount stubs. 724 functions are new exact
matches; the 77 factory constructors move off the VtableObj stand-in onto the
real constructor with identical bytes, and the 77 factory vtables verify 5/5.
LZO1X, COMSUPP, a CRT strchr fragment and 59 import thunks are marked LIBRARY,
CRT callee declarations become LIBRARY markers, and WideStringClass now calls
the narrow CRT tolower/toupper. Every exact row passes raw bytes and strict
relocation checks. Across all project objects, sections change only by the new
TUs, the removed VtableObj constructors, the RLE blitter destructors (which now
inline the empty base destructor, as retail does), the added BlitTrans
constructors and the four WideStringClass case-conversion relocation names.

The 6,045 matches represent 30.6% of 19,753 listed functions. Counts are per
function, not executable completion. Matched body lengths total **439,336
bytes**, or 11.6% of 3,797,269 listed function bytes. The padding heuristic
misses 516 matched entries. The last diagnostic link, taken before the second
cleanup batch, reported **4,186 unique unresolved symbols**, **6,731 reference
lines**, and zero duplicate definitions. Engine link closure remains unfinished.

## Historical snapshot: stream, string and timer leaves

As of **2026-10-22**, the verified snapshot reports **5,321 matched function
rows**, **319 partial rows**, **5,640 manifest rows**, **1,116 manifest
translation units**, and **1,126 tracked C++ files**. Whole-repository regression
verification, compile/layout checks, the project object build and 142 tooling
tests pass.

Stream, string and timer leaves land: the BlowPipe/PKPipe/PKStraw and LCW/LZO
compression straws, the buffer, cache and hash pipes and straws, StringClass
members, WinModemClass status slots and small timer, colour, hash-table and
constructor leaves. 45 functions are new exact matches and 3 are new partials.
The BlowPipe, BlowStraw, PKPipe and PKStraw deleting destructors (0x5B45C0,
0x632F90, 0x632FF0, 0x633370) are now emitted by their real classes, which
retires `observable_node_dtor_methods`. WinModemClass and StringClass have
single shared definitions, and the wide whitespace helper (0x7B6EC0) moves onto
WideStringClass. Every exact row passes raw bytes and strict relocation
checks. Across all project objects, sections change only by the new TUs, the
moved destructors and the 0x7B6EC0 body; three MapStageList sections keep
their bytes and change only the names of their StringClass relocation targets.

## Historical snapshot: house/building module

As of **2026-10-22**, the verified snapshot reports **5,276 matched function
rows**, **316 partial rows**, **5,592 manifest rows**, **1,099 manifest
translation units**, and **1,109 tracked C++ files**. Whole-repository regression
verification, compile/layout checks, the project object build and 142 tooling
tests pass.

The house/building module lands under `match/economy/house_building/`:
BuildingClass, BuildingTypeClass, HouseClass and HouseTypeClass bodies. 119
functions are new exact matches and 59 are new partials; 15 matched functions
move here from older TUs (two of which, `damage_flags_methods` and
`can_retaliate_methods`, are now empty and removed). Every exact row in the
module passes raw bytes and strict relocation checks. Rules view members are
named after the INI keys they are read from, and HouseTypeClass +0xB8 becomes
`ArrayIndex2` (+0xB4, returned by slot 16, stays `ArrayIndex`).
`HouseClass::Update` (0x4F8440) is held back until its callee signatures are
confirmed, and the BuildingClass constructor (0x43B740) is blocked on the
canonical TechnoClass. Across all project objects, sections change only by
the new TUs and by the removal of the 15 migrated functions from their old TUs.

## Historical snapshot: /Gr default and identity corrections

As of **2026-10-22**, the verified snapshot reports **5,157 matched function
rows**, **257 partial rows**, **5,414 manifest rows**, **1,070 manifest
translation units**, and **1,080 tracked C++ files**. Whole-repository regression
verification, compile/layout checks, the project object build and 142 tooling
tests pass.

The project default compiler flags are now `/nologo /c /O2 /Gr /DNDEBUG /Gy`.
`/Gr` makes free and static functions `__fastcall` by default, and `/GX` is
gone: the retail image has no C++ exception-handling tables. Every per-TU
`VC6FLAGS` line gains `/Gr` and loses `/GX`; TU-specific `/Ob1`, `/Ob2` and
`/Op` stay. No TU needed to keep `/GX`.

Functions that retail calls with caller cleanup are now declared `__cdecl`:
two atexit callbacks (0x438590 and the 0x4128F0 teardown), the CRT stand-ins
`Strcmpi` (0x7C8D20), `OpNew` (0x7C8E17) and `pow`, and the table helpers at
0x4CADE0 and 0x4CAC40. 152 manifest symbols are renamed for the new
decoration (`@@YA` to `@@YI`, `@@SA` to `@@SI`, `_x` to `@x@N`). Two partials
now match, each passing raw bytes and strict relocation checks:

- `FUN_00452D40` (was 82.2%);
- `ScenarioClass::PauseGame` (0x683EB0, was 91.0%).

Four other partials improve (0x45E8F0 86.0% to 95.3%, 0x40A850 74.0% to
78.0%, 0x5301A0 96.5% to 97.4%, 0x4BC750 0.6% to 0.7%). No row loses score.
Across all 1,080 project objects, sections change only through the renamed
symbols and function-pointer types, the promoted and improved rows, and
destructors that now inline without `/GX`; none of those is a manifest row.

A follow-up batch corrects identities from vtable slots, callers and the
binary's own trace strings, with every emitted section unchanged: 0x4CFD90
`FlyLocomotionClass::IsPowered`, 0x47AAB0 `CDFileClass::Open`, 0x55BAA0
`LogicClass::AddObject`, 0x551B20/0x551B90 `LayerClass::Save`/`Load`, 0x4F42F0
`GScreenClass::FlagToRedraw` (slot 14) and 0x6D1800 TabClass slot 33, plus the
string-attested `ThemeClass::QueueSong`/`PlaySong`, `IPXManagerClass::Init` and
`RadarClass_OneTime`. Four partial spans grow to their CFG-closed extent
including jump and index tables (0x41EAF0 and 0x41EE90 to 0x198, 0x6622C0 to
0xD68, 0x729E50 to 0x1C4, now 57.0%); the
[extent audit](scripts/data/function_extent_audit.json) records them and three
rejected span leads. Five vtable-referenced entries the Ghidra list lacks are
added to the [unlisted entry points](scripts/data/unlisted_entry_points.json),
with [evidence](scripts/data/unlisted_entry_points_evidence.json).

The 5,157 matches represent 26.1% of 19,753 listed functions. Counts are per
function, not executable completion. Matched body lengths total **384,253
bytes**, or 10.1% of 3,797,269 listed function bytes. The padding heuristic
misses 313 matched entries. The last diagnostic link, taken before the second
cleanup batch, reported **4,186 unique unresolved symbols**, **6,731 reference
lines**, and zero duplicate definitions. Engine link closure remains unfinished.

## Historical snapshot: canonical vector templates

As of **2026-10-22**, the verified snapshot reports **5,155 matched function
rows**, **259 partial rows**, **5,414 manifest rows**, **1,070 manifest
translation units**, and **1,080 tracked C++ files**. Whole-repository regression
verification, compile/layout checks, the project object build and 142 tooling
tests pass. There are zero annotation issues across 5,447 body addresses.

The latest batch binds more retail functions to the canonical `VectorClass` and
`DynamicVectorClass` templates. RTTI shows that 0x40B300 and 0x40B270 are the
deleting destructor and `Clear` of `VectorClass<SubzoneConnectionStruct>`
(vtable 0x7E177C), and that 0x5890B0, 0x588CC0 and 0x5892D0 belong to
`DynamicVectorClass<SubzoneConnectionStruct>` (vtable 0x7ED5A0). The old
helper rows are renamed and moved. The other slots of the four pair-vector
vtables and of 0x7ED5A0 are now claimed: 21 new rows, all exact, and all 35
slots resolve to retail. Two partials now match:

- `BrainClass::~BrainClass` (0x43A600), a real destructor over a
  `DynamicVectorClass<NeuronClass*>` member, replacing the 95.5% view with a
  hand-written vector alias;
- `FactoryClass::StartProduction` (0x4CA5A0), through the inline `Delete`
  (was 56.0%).

The three hand-written `TextDynVector` definitions in the list controls are now
the canonical template. `ListClass::AddItem` now expands the template's inline `AddItem` and stays exact.
`MultiplayerGameMode::Get` (0x5D5F30, 79.3%) and the `SmudgeTypeClass`
constructor (0x6B5260, 97.3%) were retried against the template and stay
partial; the variants are recorded in their comments.

No matched row is lost. Across all 1,080 project objects, named sections change
only in the pair-vector TU, `StartProduction`, and `ListClass::Dtor`, which
differs only in a renamed relocation target. Removed sections are the five
retired helper bodies. Added sections are unannotated template members.

The 5,155 matches represent 26.1% of 19,753 listed functions. Counts are per
function, not executable completion. Matched body lengths total **383,875
bytes**, or 10.1% of 3,797,269 listed function bytes. The padding heuristic
misses 313 matched entries. The last diagnostic link, taken before the second
cleanup batch, reported **4,186 unique unresolved symbols**, **6,731 reference
lines**, and zero duplicate definitions. Engine link closure remains unfinished.

## Historical snapshot: VectorClass rework

As of **2026-10-22**, the verified snapshot reports **5,132 matched function
rows**, **261 partial rows**, **5,393 manifest rows**, **1,070 manifest
translation units**, and **1,080 tracked C++ files**. Whole-repository regression
verification, compile/layout checks, the project object build and 142 tooling
tests pass. There are zero annotation issues across 5,426 body addresses.

The latest batch reworks `VectorClass` and `DynamicVectorClass` toward their
original class structure. One constructor, `VectorClass(int, T*)` with both
arguments defaulted, replaces the default/capacity pair and constructs caller
storage in place. The count field is `Count`, read through an inline
`GetCount()` accessor, and by-index `Delete` and by-value `RemoveItem` are inline
members. The four pair-vector constructors are now explicit instantiations of
that constructor rather than a macro, and stay exact. Three functions now
match, each passing raw bytes and strict relocation checks:

- `ListClass::RemoveItem` (0x557730), through the inline `Delete` and `Count()`;
- `SuperClass::Lose` (0x6CB7B0), through the inline `RemoveItem`, which keeps
  retail's indirect `FindItemIndex` call;
- the `TagTypes` cleanup callback (0x6E5B20). The registry at 0xB0E780 is a
  namespace-scope object, not a class static: retail's cleanup has no
  destruction guard, which VC6 emits for a static data member.

Every use of the renamed field was found by compiling the whole tree with the
accessor removed, because `v.Count != 0` and `v.Count` bound to `int&` still
compile against an accessor. No matched row was lost. Across all 1,080 project
objects, every other named section keeps its bytes and relocation tuples except
where a symbol was renamed or an unannotated template member is now emitted in
a different object. `MultiplayerGameMode::Get` (0x5D5F30) now uses the
canonical template and stays at 79.3%.

The 5,132 matches represent 26.0% of 19,753 listed functions. Counts are per
function, not executable completion. Matched body lengths total **381,695
bytes**, or 10.1% of 3,797,269 listed function bytes. The padding heuristic
misses 312 matched entries. The last diagnostic link, taken before the second
cleanup batch, reported **4,186 unique unresolved symbols**, **6,731 reference
lines**, and zero duplicate definitions. Engine link closure remains unfinished.



## Historical snapshot: second-look patches

As of **2026-10-22**, the verified snapshot reports **5,129 matched function
rows**, **264 partial rows**, **5,393 manifest rows**, **1,070 manifest
translation units**, and **1,080 tracked C++ files**. Whole-repository regression
verification, compile/layout checks, the project object build and 142 tooling
tests pass. There are zero annotation issues across 5,426 body addresses.

The latest batch reviews the remaining second-look patches against current
source. Fifteen functions now match, including the four pair-vector
constructors, five RLE and alpha blitters, the two WOL colour-dialog handlers,
`FlyLocomotionClass::ProcessSpin`, and two small helpers whose earlier source
was wrong. 0x471F90 walks its table backwards and returns a bool. 0x433ED0 and
its callee are `__thiscall` members. Each of the fifteen passes raw bytes and
strict relocation checks. Twenty-seven partials are re-scored, and four
semantic corrections were confirmed against the binary first:

- the tunnel `ZAdjust` arms add the vertical delta, not `coord.Z`;
- one Lucent50 blend term shifts by one, not two;
- the network manager compares player names with the CRT's case-insensitive
  compare;
- the shadow-gradient builder passes a by-value area and a limit to its
  spread call, and reads its bias factor as a double.

`MSPrintAnim::Construct` now subtracts the font lead, not the margin, as
retail does. The network manager's positional score falls (6.0% to 3.6%)
because its frame is now the right size.

Patches that relied on an alias, a volatile, undefined behaviour, a misdeclared
type or an unproven argument grouping were rejected or held, and the
remaining review leads stay out of the tree. Every other named section in
the 44 checked objects keeps its bytes and relocation tuples.
`MSPrintAnim::Update` remains partial pending its nine-slot table
reconstruction.

The 5,129 matches represent 26.0% of 19,753 listed functions. Counts are per
function, not executable completion. Matched body lengths total **381,343
bytes**, or 10.0% of 3,797,269 listed function bytes. The padding heuristic
misses 312 matched entries. The last diagnostic link, taken before the second
cleanup batch, reported **4,186 unique unresolved symbols**, **6,731 reference
lines**, and zero duplicate definitions. Engine link closure remains unfinished.

## Historical snapshot: native Rocket and DropPod locomotion

As of **2026-10-22**, the verified snapshot reports **5,114 matched function
rows**, **279 partial rows**, **5,393 manifest rows**, **1,070 manifest
translation units**, and **1,080 tracked C++ files**. Whole-repository regression
verification, compile/layout checks, the project object build and 142 tooling
tests pass. There are zero annotation issues across 5,426 body addresses.

The latest batch integrates native `RocketLocomotionClass` and
`DropPodLocomotionClass` implementations. Rocket adds ten exact functions. Its
constructor, `Process` and `MoveTo` stay partial (13.3%, 3.7% and 30.2%); the
last two emit sections shorter than retail. DropPod has 25 exact functions:
five rows migrate from the retired interface translation unit and twenty are
new. `Process` (2.3%, short section) and `MoveTo` (27.1%) stay partial. A
redundant reference alias was removed from DropPod `MoveTo`. The ordinary
destructor at 0x4B5B00 stays with its existing generic row. `IID_IPiggyback` is
now defined once, and the CLSIDs and IIDs match the retail data. Both
ILocomotion tables (50 slots) and the DropPod IPiggyback table (8 slots) verify
slot by slot. The ten-slot primary tables verify only if the compiler's weak
default is accepted for the deleting destructor, so final linking is not
proven. The 0x8A0820 storage is now one three-dword coordinate view. The
competing layout-only Rocket and DropPod headers are retired. Every other
named section in the 1,078 objects present before and after the batch keeps
its bytes and relocation tuples.

The repository-wide steering audit continues, and further removals may lower
the matched count. The remaining second-look patches are under review.
`MSPrintAnim::Update` remains partial pending its nine-slot table
reconstruction.

The 5,114 matches represent 25.9% of 19,753 listed functions. Counts are per
function, not executable completion. Matched body lengths total **378,631
bytes**, or 10.0% of 3,797,269 listed function bytes. The padding heuristic
misses 311 matched entries. The last diagnostic link, taken before the second
cleanup batch, reported **4,186 unique unresolved symbols**, **6,731 reference
lines**, and zero duplicate definitions. Engine link closure remains unfinished.

## Historical snapshot: third steering cleanup

As of **2026-10-22**, the verified snapshot reports **5,084 matched function
rows**, **274 partial rows**, **5,358 manifest rows**, **1,069 manifest
translation units**, and **1,079 tracked C++ files**. Whole-repository regression
verification, compile/layout checks, the project object build and 142 tooling
tests pass. There are zero annotation issues across 5,391 body addresses.

The latest batch is the third steering cleanup. It removes volatile-qualified
accesses, redundant pointer aliases, a discarded comma operand and a byte union
alias from eighteen functions in seventeen translation units, including a
second named-pointer alias in `ListClass::RemoveItem`. With plain source,
`Matrix3D::GetYRotation` now matches and one constructor keeps its match with
identical bytes. Fourteen former matches are now partial, and two existing
partials are re-scored lower. Five demoted functions now emit sections shorter
than retail, so their percentages are diagnostic only. One named pointer to an
embedded vector is kept, because retail holds that address in a register for
the inlined teardown. The `HouseClass::DestroyAll*` callers now name their
0x71AD40 callee `TemporalClass::JustLetGo` rather than `Detach` (0x71ADE0),
which fixes their relocation targets without changing their bytes. The 39
unaffected named sections in the changed translation units keep their bytes and
relocation tuples. The cleanup ledger is
[recorded here](scripts/data/match_steering_cleanup.json).

The repository-wide steering audit continues, and further removals may lower
the matched count. Rocket and DropPod integration candidates and the remaining
second-look patches are under review; candidate code must meet the same rule.
`MSPrintAnim::Update` remains partial pending its nine-slot table
reconstruction.

The 5,084 matches represent 25.7% of 19,753 listed functions. Counts are per
function, not executable completion. Matched body lengths total **377,018
bytes**, or 9.9% of 3,797,269 listed function bytes. The padding heuristic
misses 311 matched entries. The last diagnostic link, taken before the second
cleanup batch, reported **4,186 unique unresolved symbols**, **6,731 reference
lines**, and zero duplicate definitions. Engine link closure remains unfinished.

## Historical snapshot: second steering cleanup

As of **2026-10-22**, the verified snapshot reports **5,097 matched function
rows**, **261 partial rows**, **5,358 manifest rows**, **1,069 manifest
translation units**, and **1,079 tracked C++ files**. Whole-repository regression
verification, compile/layout checks, the project object build and 142 tooling
tests pass. There are zero annotation issues across 5,391 body addresses.

The latest batch is the second steering cleanup. It removes volatile-qualified
accesses used only for scheduling or register choice from sixteen early utility
translation units and two `SlaveManagerClass` methods. It also makes the shared
`field_A8` countdown an ordinary `int`, replaces a pointer-to-pointer cursor
alias in `PassengersClass::RemovePassenger`, and drops an unsigned cast in
`MSAnim`'s inline time-left reader. Twenty-nine former matches are now partial,
three existing partials are re-scored lower, and two more were recompiled
without a score change. Four demoted functions now emit sections shorter than
retail, so their percentages are diagnostic only. The 109 unaffected named
sections in the changed translation units keep their bytes and relocation
tuples. The cleanup ledger is
[recorded here](scripts/data/match_steering_cleanup.json).

The repository-wide steering audit continues, and further removals may lower
the matched count. Rocket and DropPod integration candidates and the remaining
second-look patches are under review; candidate code must meet the same rule.
`MSPrintAnim::Update` remains partial pending its nine-slot table
reconstruction.

The 5,097 matches represent 25.8% of 19,753 listed functions. Counts are per
function, not executable completion. Matched body lengths total **378,253
bytes**, or 10.0% of 3,797,269 listed function bytes. The padding heuristic
misses 311 matched entries. The last diagnostic link, taken before this batch,
reported **4,186 unique unresolved symbols**, **6,731 reference lines**, and zero
duplicate definitions. Engine link closure remains unfinished.

## Historical snapshot: first steering cleanup and callback scoping

As of **2026-10-22**, the verified snapshot reports **5,126 matched function
rows**, **232 partial rows**, **5,358 manifest rows**, **1,069 manifest
translation units**, and **1,079 tracked C++ files**. Whole-repository regression
verification, compile/layout checks, the project object build and 142 tooling
tests pass. There are zero annotation issues across 5,391 body addresses.

The latest batch removes match-only volatile reloads, redundant receiver aliases,
an interior-member cursor with offset casts, and cancelling counter updates.
Three former matches are now partial: `MSBitPrintAnim::Construct` (88.6%),
`0x408930` (50.0%), and the LCW pipe output method (99.0%). Four existing
partials are also re-scored after cleanup. Forty-four unaffected complete
sections preserve their bytes and relocation tuples. The scoped cleanup ledger
is [recorded here](scripts/data/match_steering_cleanup.json).

The relocation checker now scopes VC6 `_$E<number>` callback bindings to the
function's identified translation unit; absent that context, an explicit local
binding is required. Three synthetic regressions and the real particle callback
checks pass. This tooling fix changes no C++ source or match totals.

This is the first cleanup batch; the repository-wide steering audit continues.
Further removals may lower the matched count. Rocket and DropPod integration
candidates and the remaining second-look patches are under review; candidate
code must meet the same rule. `MSPrintAnim::Update` remains partial pending its
nine-slot table reconstruction.

The 5,126 matches represent 26.0% of 19,753 listed functions. Matched body
lengths total **380,297 bytes**, or 10.0% of 3,797,269 listed function bytes.
The padding heuristic misses 314 matched entries. The diagnostic link reports
**4,186 unique unresolved symbols**, **6,731 reference lines**, and zero
duplicate definitions. Engine link closure remains unfinished.

## Historical snapshot: index mutations and terrain constructor

As of **2026-10-22**, the verified snapshot reports **5,129 matched function
rows**, **229 partial rows**, **5,358 manifest rows**, **1,069 manifest
translation units**, and **1,079 tracked C++ files**. Whole-repository regression
verification, compile/layout checks, the project object build and 139 tooling
tests pass. There are zero annotation issues across 5,391 body addresses.

The latest batch promotes `IndexClass::AddIndex`, `IndexClass::RemoveIndex`
and the `TerrainTypeClass` constructor after independent second-look review.
The index uses array construction and whole-record copies; the terrain
constructor uses the existing indexed append helper. Assertions pin both index
record views. Ten affected/adjacent rows pass raw and strict checks over 31
relocation fields; twenty unaffected prior sections preserve complete bytes and
relocation tuples. An extra unreferenced array-construction helper COMDAT is
byte-identical to the existing project copies; the diagnostic link has no
duplicate definitions. Local REA/Ghidra analysis corroborates the index removal
flow, subject to its raw-loader ABI limitations.

Code-generation-only volatile accesses, redundant pointer aliases and casts are
now forbidden by the project rules. An audit of existing source is in progress;
removing such constructs may reduce the matched count. Rocket and DropPod
integration candidates and remaining second-look patches are under review.
`MSPrintAnim::Update` remains partial pending its nine-slot table reconstruction.

The 5,129 matches represent 26.0% of 19,753 listed functions. Matched body
lengths total **381,014 bytes**, or 10.0% of 3,797,269 listed function bytes.
The padding heuristic misses 314 matched entries. The diagnostic link reports
**4,186 unique unresolved symbols**, **6,731 reference lines**, and zero
duplicate definitions. Engine link closure remains unfinished.

## Historical snapshot: clamp setter and particle static initializer

As of **2026-10-22**, the verified snapshot reports **5,126 matched function
rows**, **232 partial rows**, **5,358 manifest rows**, **1,069 manifest
translation units**, and **1,079 tracked C++ files**. Whole-repository regression
verification, compile/layout checks, the project object build and 139 tooling
tests pass. There are zero annotation issues across 5,391 body addresses.

The latest batch promotes two independently reviewed second-look candidates:
the clamped setter at `0x406620` and `ParticleClass::vf_66` at `0x62D710`.
The setter uses an inline clamp helper; the particle initializer uses an inline
by-value helper to reproduce the temporary inside the local-static guard.
Neither helper is claimed as a recovered retail function. Function markers now
identify the actual annotated definitions.

Both bodies and the unchanged particle atexit callback pass raw and strict
checks, including all six initializer relocation fields. Seventeen unaffected
prior sections preserve their normalized bytes and relocation layouts. The
particle review also confirms unchanged static storage and no new helper or
vtable symbol. Rocket and DropPod integration candidates and the remaining
second-look patches are under review. `MSPrintAnim::Update` remains partial
pending its nine-slot table reconstruction.

The 5,126 matches represent 26.0% of 19,753 listed functions. Matched body
lengths total **380,275 bytes**, or 10.0% of 3,797,269 listed function bytes.
The padding heuristic misses 314 matched entries. The diagnostic link reports
**4,186 unique unresolved symbols**, **6,731 reference lines**, and zero
duplicate definitions. Engine link closure remains unfinished.

## Historical snapshot: native Mech locomotion and base stream loading

As of **2026-10-22**, the verified snapshot reports **5,124 matched function
rows**, **234 partial rows**, **5,358 manifest rows**, **1,069 manifest
translation units**, and **1,079 tracked C++ files**. Whole-repository regression
verification, compile/layout checks, the project object build and 139 tooling
tests pass. There are zero annotation issues across 5,391 body addresses.

The latest batch integrates native `MechLocomotionClass` methods, adds 13 exact
function rows and retains three frozen partials. Its deleting destructor moves
from the generic family to compiler output. `LocomotionClass::Load` moves into
the native base class, with its DropPod and Fly callers updated. The old flat
Mech layout and separate Load implementation are retired.

The 62 exact Mech/base/caller rows pass raw and strict verification across 86
relocation fields. Fifty-three unaffected prior sections preserve their normalized
bytes and relocation layouts; all 17 Mech sections agree with the frozen
candidate, including the three partials. The 16-byte Mech CLSID matches retail.
The 50-slot ILocomotion table passes directly; the ten-slot primary table passes
under a recorded weak-default assumption for its deleting-destructor slot.
Final-link selection remains unproved. `MSPrintAnim::Update` remains partial
pending its nine-slot table reconstruction. Rocket and DropPod integration
candidates and Claude's returned second-look patches are under review.

The 5,124 matches represent 25.9% of 19,753 listed functions. Matched body
lengths total **380,178 bytes**, or 10.0% of 3,797,269 listed function bytes.
The padding heuristic misses 314 matched entries. The diagnostic link reports
**4,186 unique unresolved symbols**, **6,731 reference lines**, and zero
duplicate definitions. Engine link closure remains unfinished.

## Historical snapshot: native Hover locomotion and timer initializer

As of **2026-10-22**, the verified snapshot reports **5,111 matched function
rows**, **231 partial rows**, **5,342 manifest rows**, **1,069 manifest
translation units**, and **1,079 tracked C++ files**. Whole-repository regression
verification, compile/layout checks, the project object build and 139 tooling
tests pass. There are zero annotation issues across 5,375 body addresses.

The latest batch integrates native `HoverLocomotionClass` methods and a shared
cell-direction pair declaration. It adds 18 exact function rows and retains five
frozen partials; the deleting destructor moves from the generic family to native
compiler output. A timer initializer also moves from partial to matched. The
19 exact Hover rows and three timer/adjacent-cell checks pass raw and strict
verification across 80 relocation fields. Fourteen unaffected prior sections
preserve their bytes and relocation tuples; the five new partial sections retain
their normalized bytes and relocation layouts. The Hover CLSID matches retail.

The 50-slot ILocomotion table passes directly. The ten-slot primary table passes
under a recorded weak-default assumption for its deleting-destructor slot;
final-link selection remains unproved. `MSPrintAnim::Update` remains partial
pending its nine-slot table reconstruction. Mech integration is under review.

The 5,111 matches represent 25.9% of 19,753 listed functions. Matched body
lengths total **379,427 bytes**, or 10.0% of 3,797,269 listed function bytes.
The padding heuristic misses 314 matched entries. The diagnostic link reports
**4,184 unique unresolved symbols**, **6,723 reference lines**, and zero
duplicate definitions. Engine link closure remains unfinished.

## Historical snapshot: named-global relocation audit

As of **2026-10-22**, the verified snapshot reports **5,092 matched function
rows**, **227 partial rows**, **5,319 manifest rows**, **1,068 manifest
translation units**, and **1,078 tracked C++ files**. Whole-repository regression
verification, compile/layout checks, the project object build and 139 tooling
tests pass. There are zero annotation issues across 5,352 body addresses.

The latest audit corrects 37 previously recorded matches: 31 x87 initializers
had swapped constant operands, one map method swapped global operands, and five
CCINI methods used registry count fields four bytes early. The byte oracle now
checks address-labelled `DAT_` targets, including relocation addends, and rejects
mismatches before fallback. It also respects explicit partial status at 100%.
All 37 corrected bodies pass raw and strict checks over 157 relocation fields;
90 unaffected prior function sections are preserved. The scoped audit checks
1,729 address-labelled fields with zero remaining mismatches. Other relocation
bindings still require their separate strict checks. The correction ledger is
[saved here](scripts/data/named_dat_target_corrections.json).

`MSPrintAnim::Update` has exact body bytes but remains partial pending its
nine-slot vtable reconstruction. Hover and Mech integrations remain under review.

The 5,092 matches represent 25.8% of 19,753 listed functions. Matched body
lengths total **377,609 bytes**, or 9.9% of 3,797,269 listed function bytes.
The padding heuristic misses 314 matched entries. The diagnostic link reports
**4,140 unique unresolved symbols**, **6,670 reference lines**, and zero
duplicate definitions. Engine link closure remains unfinished.

## Historical snapshot: native locomotion base methods

As of **2026-10-22**, the verified snapshot reports **5,086 matched function
rows**, **233 partial rows**, **5,319 manifest rows**, **1,069 manifest
translation units**, and **1,079 tracked C++ files**. Whole-repository regression
verification, compile/layout checks, the project object build and 112 tooling
tests pass. There are zero annotation issues across 5,352 body addresses.

The latest batch integrates native `LocomotionClass` base methods and shared
interface declarations. It adds 22 exact entries and migrates 12 existing exact
base methods. All 34 pass raw and strict checks across 26 relocation fields.
Three Drive helpers and three other affected callers also pass raw and strict
checks across ten additional relocation fields. All 56 affected prior emitted
sections preserve their sizes, non-relocation bytes and relocation positions/types;
all seven affected partials retain their scores. No emitted native base vtable
or completed locomotion hierarchy is claimed.

The 5,086 matches represent 25.7% of 19,753 listed functions. Matched body
lengths total **376,528 bytes**, or 9.9% of 3,797,269 listed function bytes.
The padding heuristic misses 314 matched entries. The diagnostic link reports
**4,140 unique unresolved symbols**, **6,670 reference lines**, and zero
duplicate definitions. Engine link closure remains unfinished.

## Historical snapshot: native particle runtime methods

As of **2026-10-22**, the verified snapshot reports **5,064 matched function
rows**, **233 partial rows**, **5,297 manifest rows**, **1,072 manifest
translation units**, and **1,082 tracked C++ files**. Whole-repository regression
verification, compile/layout checks, the project object build and 112 tooling
tests pass. There are zero annotation issues across 5,330 body addresses.

The latest batch integrates native `ParticleClass` and `ParticleSystemClass`
declarations and methods. It adds 24 exact entries and retains six frozen
partials. The system deleting destructor moves from the generic sweep to
compiler-generated native output; its ordinary destructor remains declared
at `0x62E070`. Two existing spawn methods keep their retail bytes with canonical
coordinate and constructor declarations. Partial object-base views remain.

All 27 exact entries pass raw and strict checks across 118 relocation fields.
The eight runtime tables cover 261 slots; the two primary deleting entries use
recorded weak-default assumptions, and final-link selection remains unproved.
The six partials retain their complete emitted sections. Fifty-six older saved
partial baselines also remain unchanged. All 70 affected prior sections preserve
their bytes and relocation positions/types; three renamed target tuples are
checked separately. Both CLSID constants match retail data.

The 5,064 matches represent 25.6% of 19,753 listed functions. Matched body
lengths total **376,290 bytes**, or 9.9% of 3,797,269 listed function bytes.
The padding heuristic misses 312 matched entries. The diagnostic link reports
**4,145 unique unresolved symbols**, **6,677 reference lines**, and zero
duplicate definitions. Engine link closure remains unfinished.

## Historical snapshot: native terrain, overlay and smudge methods

As of **2026-10-22**, the verified snapshot reports **5,040 matched function
rows**, **227 partial rows**, **5,267 manifest rows**, **1,070 manifest
translation units**, and **1,080 tracked C++ files**. Whole-repository regression
verification, compile/layout checks, the project object build and 112 tooling
tests pass. There are zero annotation issues across 5,300 body addresses.

The latest batch integrates native terrain, overlay and smudge classes. It adds
69 exact functions and retains 18 frozen partials. Three existing functions move
to their native owners; two additional symbols change with canonical class
keys, including the existing terrain factory and cell terrain getter. All 72
exact module functions pass raw and strict checks across 479 relocation fields.
The 24 tables pass scoped checks across 536 slots: 488 primary slots use
recorded weak-default assumptions; 48 secondary slots pass directly. These
checks do not establish final-link selection. Shared MapObj bases remain
explicitly partial views.

All 18 retained partials preserve their complete emitted sections and relocations.
Three requested spans exceed those emitted sections and remain unverified.
The 86 affected prior rows preserve full section sizes, non-relocation bytes
and relocation positions/types; renamed targets are checked separately. The
36 older saved partial baselines and two previous particle type cap sections
are unchanged. All 35 string occurrences (33 distinct symbols) and six CLSID
constants match retail data in the rebuilt objects.

The 5,040 matches represent 25.5% of 19,753 listed functions. Matched body
lengths total **374,180 bytes**, or 9.9% of 3,797,269 listed function bytes.
The padding heuristic misses 310 matched entries. The diagnostic link reports
**3,974 unique unresolved symbols**, **6,366 reference lines**, and zero
duplicate definitions. Engine link closure remains unfinished.

## Historical snapshot: native particle type methods

As of **2026-10-22**, the verified snapshot reports **4,971 matched function
rows**, **209 partial rows**, **5,180 manifest rows**, **1,064 manifest
translation units**, and **1,074 tracked C++ files**. Whole-repository regression
verification, compile/layout checks, the project object build and 112 tooling tests
pass. There are zero annotation issues across 5,213 body addresses.

The latest batch adds 21 matched native methods for `ParticleSystemTypeClass`
and `ParticleTypeClass`. Two factories move to their native classes, and two
existing spawn methods retain their matches after declaration cleanup. These
25 functions pass raw and strict checks across 190 relocation fields. Across
150 affected prior rows, complete emitted sections retain their sizes,
non-relocation bytes and relocation positions/types. Three rows change
relocation names; their effective targets are checked in the 25-function set. Two
capped type bodies remain partial at 96.6% and 22.4%; their complete emitted
bytes and relocation positions/types are unchanged from the frozen candidate.
Thirty-six older saved partial baselines are also unchanged.

The type headers share offset-asserted layouts and reuse existing registry and
type-array storage. The common object-type base remains a partial virtual view;
this batch does not complete the runtime particle hierarchy. The two 40-slot
primary tables agree under recorded weak-default assumptions, and six secondary
tables are checked directly. Final-link selection remains unproved.

The 4,971 matches represent 25.2% of 19,753 listed functions. Matched body
lengths total **366,508 bytes**, or 9.7% of 3,797,269 listed function bytes.
The padding heuristic misses 310 matched entries.
The diagnostic link reports **3,700 unique unresolved symbols**, **5,681
reference lines**, and zero duplicate definitions. Engine link closure remains
unfinished; per-function checks do not establish whole-executable identity.

## Historical snapshot: native Winsock and UDP lifetime

As of **2026-10-21**, the verified snapshot reports **4,950 matched function
rows**, **207 partial rows**, **5,157 manifest rows**, **1,061 manifest
translation units**, and **1,071 tracked C++ files**. Whole-repository matching,
compile/layout checks, the project object build and 112 tooling tests pass.
There are zero matched regressions and zero annotation issues across 5,190
body addresses. Thirty-six saved partial baselines remain unchanged.

The latest batch recovers the Winsock constructor, base and UDP destructors,
shared shutdown method, and both compiler-generated deleting destructors as
native C++. Each ordinary function has one out-of-line definition; `/Ob2` in
the two lifetime translation units reproduces the retail inline copies. No asm,
forced callers or emission shims are used. All six new functions pass raw and
strict checks across 43 relocation fields without weak defaults. The emitted
base and three vector tables agree under recorded weak-default assumptions.
The UDP table check also uses the capped slot-16 address binding described below;
these scoped checks do not prove final-link selection. The existing
IPX deleting-wrapper call now uses the canonical base destructor declaration;
native IPX wrapper recovery remains deferred.
UDP table slot 16 uses an explicit address binding to the capped MessageHandler
at `0x7B3AA0`; this batch does not provide its body. The duplicated vector tables
and deleting wrappers have identical section bytes and relocation expressions
across the current object providers.
All 348 affected prior rows preserve their full emitted sections and relocation
offsets/types, including six partial rows. The existing IPX wrapper also passes
two strict relocation checks, bringing this batch's total to 45 fields.

The [function extent audit](scripts/data/function_extent_audit.json) records
52 corrected comparison spans and 144 newly covered local relocation fields.

Matched lengths total **363,681 bytes**: 25.1% of listed functions and 9.6%
of listed function lengths. The padding heuristic misses 310 matched entries.
The diagnostic link reports **3,628 unique unresolved symbols**, **5,546
reference lines**, and zero duplicate definitions. Engine link closure remains
unfinished; per-function checks do not establish whole-executable identity.

## Historical snapshot: native IPX manager lifetime and adapter formatting

As of **2026-10-21**, the verified snapshot reports **4,944 matched function
rows**, **207 partial rows**, **5,151 manifest rows**, **1,059 manifest
translation units**, and **1,069 tracked C++ files**. Whole-repository matching,
compile/layout checks, the project object build and 112 tooling tests pass.
There are zero matched regressions and zero annotation issues across 5,184
body addresses. Thirty-six saved partial baselines remain unchanged.

The latest batch recovers the native IPX manager destructor, its compiler-generated
deleting wrapper, the base manager deleting wrapper, and IPX address formatting.
Three rows are new matches; the derived deleting wrapper replaces an existing
stand-in. The four functions pass strict checks across 13 relocation fields.
The 25-slot derived and 16-slot base tables agree with retail under the recorded
weak-default assumptions; final-link selection remains unproved. The IPX adapter
query declaration now belongs to the derived class, with its target unchanged.
The capped query body and the IPX interface deleting wrapper remain deferred.
All 344 other affected prior rows preserve their full emitted sections and
relocation offsets/types, including six partials. The sole relocation-name
change is the adapter query's move from the base to the derived declaration;
its effective target is independently verified as `0x7B0DD0`.

The [function extent audit](scripts/data/function_extent_audit.json) records
52 corrected comparison spans and 144 newly covered local relocation fields.
The new manager destructor uses its complete 0x8D code span, including both
return paths, excluding three trailing alignment bytes in the frozen candidate.

Matched lengths total **362,439 bytes**: 25.0% of listed functions and 9.5%
of listed function lengths. The padding heuristic misses 309 matched entries.
The diagnostic link reports **3,627 unique unresolved symbols**, **5,540
reference lines**, and zero duplicate definitions. Engine link closure remains
unfinished; per-function checks do not establish whole-executable identity.

## Historical snapshot: UDP methods and Winsock buffer pools

As of **2026-10-21**, the verified snapshot reports **4,941 matched function
rows**, **207 partial rows**, **5,148 manifest rows**, **1,058 manifest
translation units**, and **1,068 tracked C++ files**. Whole-repository matching,
compile/layout checks, the project object build and 112 tooling tests pass.
There are zero matched regressions and zero annotation issues across 5,181
body addresses. Thirty-six saved partial baselines remain unchanged.

The latest batch adds 19 ordinary UDP interface methods and two Winsock buffer
allocators as native C++. The allocator evidence replaces an opaque base-class
region with three 128-entry buffer pools. A shared declaration also unifies
three callers of the helper at `0x5D4D50`, whose original name remains unknown.
The 21 new functions and three existing callers pass raw and strict checks
across 106 relocation fields without weak defaults. All 20 UDP string literals
agree with the binary. The 31-slot retail UDP table is recorded; emitted-table
selection and lifetime methods remain deferred.
All 258 affected prior rows preserve their bytes and relocation offsets,
using the full emitted sections for three partial rows whose requested retail
spans cannot be extracted from their shorter or crossing-relocation objects.

The [function extent audit](scripts/data/function_extent_audit.json) now records
52 corrected comparison spans: 22 incomplete return operands, eight reachable
code tails, and 22 switch-table or alignment tails. All expanded spans match. Earlier
corrections exposed two source errors in `WhatAmI == 15` dispatch, now fixed.
The audit verifies 144 newly covered local relocation fields. These span checks
are not a proof that every function boundary in the project is complete.

Matched lengths total **361,902 bytes**: 25.0% of listed functions and 9.5%
of listed function lengths. The padding heuristic misses 309 matched entries.
The diagnostic link reports **3,627 unique unresolved symbols**, **5,537
reference lines**, and zero duplicate definitions. Engine link closure remains
unfinished; per-function checks do not establish whole-executable identity.

## Historical snapshot: IPX methods and initial extent audit

As of **2026-10-21**, the verified snapshot reports **4,920 matched function
rows**, **207 partial rows**, **5,127 manifest rows**, **1,056 manifest
translation units**, and **1,066 tracked C++ files**. Whole-repository matching,
compile/layout checks, the project object build and 112 tooling tests pass.
There are zero matched regressions and zero annotation issues across 5,160
body addresses. Thirty-six saved partial baselines remain unchanged.

The latest batch adds four exact ordinary IPX interface methods with a shared
native derived declaration. It also replaces two incompatible randomizer receiver
views with the existing canonical class and one global declaration. The declaration migration preserves 254
prior function spans and relocation offsets, including the full emitted sections
of affected partials. The four new methods and three
existing randomizer callers pass raw and strict checks across 97 relocation
fields. All 23 retail IPX table slots are recorded and the derived offsets are
asserted; emitted-table selection, constructors and destructors remain deferred.
The 0x3F310 class extent is modeled from observed allocations and field accesses.

The [function extent audit](scripts/data/function_extent_audit.json) corrects 44
previously shortened comparison spans: 18 incomplete return operands, five
reachable code tails, and 21 switch/index-table tails. Two exposed a reconstruction
error for `WhatAmI == 15`; the corrected C++ returns the original pointer. All
44 complete spans now match, and 138 newly covered local relocation fields are
verified. The two dispatch functions also pass full-span strict checks.

Matched lengths total **358,588 bytes**: 24.9% of listed functions and 9.4%
of listed function lengths. The padding heuristic misses 306 matched entries.
The diagnostic link reports **3,627 unique unresolved symbols**, **5,517
reference lines**, and zero duplicate definitions. Engine link closure and
whole-executable reproduction remain unfinished.

## Historical snapshot: ordinary Winsock methods and input declarations

As of **2026-10-21**, the verified snapshot reports **4,916 matched function
rows**, **207 partial rows**, **5,123 manifest rows**, **1,055 manifest
translation units**, and **1,065 tracked C++ files**. Whole-repository matching,
compile/layout checks, the project object build and 112 tooling tests pass.
There are zero matched regressions and zero annotation issues across 5,156
body addresses. Thirty-six saved partial baselines remain unchanged.

The latest batch adds 19 exact ordinary Winsock base methods, including packet
queues, checksums and socket operations. The shared input declaration also
replaces two UI call views. All 246 affected prior function bodies and relocation
offsets remain identical. The new methods and four existing input/UI functions
pass raw and strict checks across 81 relocation fields. Both seven-slot buffer
vector tables pass under their recorded weak-default assumptions. Winsock
constructor/destructor recovery and final-link table selection remain deferred.

Matched lengths total **355,356 bytes**: 24.9% of listed functions and 9.4%
of listed function lengths. The padding heuristic misses 306 matched entries.
The diagnostic link reports **3,623 unique unresolved symbols**, **5,502
reference lines**, and zero duplicate definitions. Engine link closure and
whole-executable reproduction remain unfinished.

## Historical snapshot: native connection hierarchy and manager methods

As of **2026-10-21**, the verified snapshot reports **4,897 matched function
rows**, **207 partial rows**, **5,104 manifest rows**, **1,054 manifest
translation units**, and **1,064 tracked C++ files**. Whole-repository matching,
compile/layout checks, the project object build and 112 tooling tests pass.
There are zero matched regressions and zero annotation issues across 5,137
body addresses. Thirty-six saved partial baselines remain unchanged.

The connection and manager batch adds 46 exact functions, migrates three exact
stand-ins onto native classes, and retains seven partials. It shares the IPX
address and Winsock declarations, replaces the duplicate manager view, and
preserves the existing startup caller. The destructor definitions are shared
consistently across translation units. All 81 affected prior rows keep identical
emitted bodies and relocation offsets. The 49 imported exact functions and
startup caller pass raw checks and strict checks for 107 relocation fields.

All seven partial retail extents are confirmed. Two partial objects are shorter
than retail; one has a relocation crossing the requested span. Their positional
scores remain diagnostics. The three connection table layouts agree across
39 slots under the recorded MSVC weak-default assumptions; this does not prove
final-link selection. Manager lifetime expansions remain deferred.

Matched lengths total **353,889 bytes**: 24.8% of listed functions and 9.3%
of listed function lengths. The padding heuristic misses 305 matched entries.
The diagnostic link reports **3,617 unique unresolved symbols**, **5,488
reference lines**, and zero duplicate definitions. Engine link closure and
whole-executable reproduction remain unfinished.

## Historical snapshot: renderer and transport declaration preparation

As of **2026-10-21**, the latest verified snapshot reports **4,851 matched
function rows**, **200 partial rows**, **5,051 manifest rows**, **1,051 manifest
translation units**, and **1,061 tracked C++ files**. Whole-repository regression,
compile/layout checks, the project build and 112 tooling tests pass with zero
matched regressions. All project objects are current. The annotation audit
reports 5,084 body addresses and zero issues. Thirty-six saved partial
baselines are unchanged.

The shared Winsock declaration replaces six differing class definitions and
the separate discard receiver view. Three existing network methods now use
native virtual members; all 185 rows across the seven affected translation
units retain identical emitted bodies and relocation offsets. The three
methods and twelve vector methods also pass strict checks for 25 relocation
fields. The 23-slot retail table is recorded as address bindings, not a claim
of emitted-table selection. Function totals are unchanged.

Transport preparation consolidates the lobby and event address declarations
into one 12-byte `IPXAddressClass`, confirmed by retail array strides and
embedded copies. The packed lobby node retains its verified size and offsets;
all 51 functions in the three consumer files remain exact. No function rows
were added.

The preceding function batch adds DSurface's ordinary methods to the canonical renderer
hierarchy: nine new exact functions, one existing exact getter migrated, and
ten partials. All ten exact spans pass raw checks and all six relocation fields
resolve to retail targets. Direct pinned-image checks cover all 38 vtable
slots; this establishes address bindings, not emitted-table selection or class
closure. Constructors and the deleting destructor remain deferred.

The import corrects four truncated partial extents, an oversized padding gap
that misplaced a row-stride field, and buffer-helper call bindings. The stride
at `+0x28` is confirmed by entry-origin disassembly and REA/Ghidra memory bytes.
Six partial objects are shorter than their retail spans; their instruction
scores are diagnostics, with no full-span raw-byte or semantic-equivalence
claim. The existing pixel-shift view is shared with the blitters rather than
adding another storage alias. No assembly or runtime shim was added.

Matched lengths total **349,752 bytes**: 24.6% of listed functions and 9.2%
of listed function lengths. The padding heuristic misses 301 matched entries.
The diagnostic link reports **3,558 unique unresolved symbols**, **5,381
reference lines**, and zero duplicate definitions. Engine link closure and
whole-executable reproduction remain unfinished. Earlier literal and decoder
oracle corrections remain in place.

## Historical snapshot: native BSurface Lock and shared DirectDraw calls

As of **2026-10-21**, the latest verified snapshot reports **4,842 matched
function rows**, **190 partial rows**, **5,032 manifest rows**, **1,041 manifest
translation units**, and **1,051 tracked C++ files**. Whole-repository regression,
compile/layout checks, the project build and 112 tooling tests pass with zero
matched regressions. All project objects are current. The annotation audit
reports 5,065 body addresses and zero issues. Thirty-six saved partial
baselines are unchanged.

The latest batch adds 70 ordinary RLE methods: 61 exact spans and nine readable
partials. All 52 relocation fields in the exact spans resolve to retail targets.
Direct retail checks cover 105 slots across 35 RTTI-backed leaf tables. These
are address bindings, not proof of production table emission, destructor
ownership or complete class closure. Harness rows remain excluded. Three
partials have shorter compiled sections than their retail spans; their stored
instruction-position scores do not measure full-span byte equality.

BSurface's Lock now belongs to the canonical renderer class, replacing its
generic small-method view. Its two existing getters remain exact. An explicit,
narrow DirectDraw COM declaration centralizes the pointer at `0x8A0094` and
replaces generic slot calls in YRDDraw::Restore. All four affected spans pass
raw checks; all 18 relocation fields resolve to retail targets. BSurface's
allocation-backed `0x20` size is asserted. Its deleting destructor retains the
existing exact generic body after bounded native attempts; no shim was added.

The earlier locomotion literal correction and scoped literal-oracle checks
remain in place. The instruction decoder now isolates each symbol's COFF
section, preventing
foreign switch labels in same-named sections from distorting instruction scores.
Synthetic regressions and frozen repro objects verify the correction. The two
legacy locomotion spans at `0x55A710` and `0x55AB40` now include their complete
`RET 8` instructions: all 19 and 45 bytes respectively match retail, with no
relocation fields. This corrects span metadata and adds no matched functions. Two AI-trigger
partials remeasured at 4.3% with the corrected decoder (previously 5.1%);
their source bodies are unchanged and neither is promoted.

Matched lengths total **349,020 bytes**: 24.5% of listed functions and 9.2%
of listed function lengths. The padding heuristic misses 301 matched entries.
The diagnostic link reports **3,545 unique unresolved symbols**, **5,326
reference lines**, and zero duplicate definitions. Engine link closure and
whole-executable reproduction remain unfinished.

## Historical snapshot: Surface hierarchy consolidation

As of **2026-10-21**, the latest verified snapshot has **4,781 fully matched
functions**, **181 partial rows**, **4,962 manifest rows**, **1,027 manifest
translation units**, and **1,037 tracked C++ files**. Whole-repository regression,
compile/layout checks, the project build and 94 tooling tests pass with zero
matched regressions. All project objects are current. The annotation audit
reports 4,995 body addresses and zero issues. Twenty earlier saved partial
baselines are unchanged.

Surface and XSurface now share one canonical renderer header. The migration
preserves 15 exact entries, adds 14 exact entries, and includes seven readable
partial bodies without claiming semantic equivalence. BSurface uses that header;
the incomplete XSurface header and temporary BlitTrans class are removed. All
29 exact Surface/XSurface spans pass raw checks and all six relocation fields
resolve to retail targets. The base Surface table conditionally verifies 34
slots using recorded compiler weak defaults; direct retail checks confirm the
36 XSurface slot bindings, including addresses of partial bodies. Neither check
proves final-link selection or complete class closure; no harness probe lands.

The seven new partial scores reproduce except DrawLineEx, measured at 1.8%
rather than the submission's 1.9%; its body remains unchanged. After that
metadata correction, the focused 36-row check and fresh project build passed.
Other address-scoped Surface views still need separate consolidation. Existing
partial statuses remain truthful, and no assembly or runtime shim was added.

Matched lengths total **340,053 bytes**: 24.2% of listed functions and 9.0%
of listed function lengths. The padding heuristic misses 301 matched entries.
The diagnostic link reports **3,543 unique unresolved symbols**, **5,296
reference lines**, and zero duplicate definitions. Engine link closure and
whole-executable reproduction remain unfinished.

## Historical snapshot: RLE Lucent methods and shared interface

As of **2026-10-21**, the latest verified snapshot has **4,767 fully matched
functions**, **174 partial rows**, **4,941 manifest rows**, **1,023 manifest
translation units**, and **1,033 tracked C++ files**. Whole-repository regression,
compile/layout checks, the project build and 94 tooling tests pass with zero
matched regressions. All project objects are current. The annotation audit
reports 4,974 body addresses and zero issues. Twenty saved partial baselines
are unchanged.

The latest batch adds 32 exact ordinary RLE Lucent25/75 methods, with all
44 relocation fields resolving to retail targets. A single declaration-only
`RLEBlitter` interface models the separate RTTI root and its three virtual slots.
Direct pinned-image checks confirm the root RTTI/table and 48 slots across the
16 leaf tables. These are retail address bindings, not production table-emission,
deleting-destructor or complete class-closure claims. Harness tables and
wrappers, alpha-pool lifetime code, assembly and artificial probes are excluded
from this import. Existing partial bodies were preserved.

Matched lengths total **339,404 bytes**: 24.1% of listed functions and 8.9%
of listed function lengths. The padding heuristic misses 300 matched entries.
The diagnostic link reports **3,538 unique unresolved symbols**, **5,288
reference lines**, and zero duplicate definitions. Engine link closure and
whole-executable reproduction remain unfinished.

## Historical snapshot: Z-remap and alpha Blitter families

As of **2026-10-21**, the latest verified snapshot has **4,735 fully matched
functions**, **174 partial rows**, **4,909 manifest rows**, **1,019 manifest
translation units**, and **1,029 tracked C++ files**. Whole-repository regression,
compile/layout checks, the project build and 94 tooling tests pass with zero
matched regressions. All project objects are current. The annotation audit
reports 4,942 body addresses and zero issues. Sixteen saved partial baselines
are unchanged.

The latest batch adds 56 exact ordinary methods across Z-remap, alpha translation
and translucent Blitter clusters. All 21 relocation fields in those spans resolve
to retail targets. Four frozen bodies remain partial: `0x494D90` at 97.6%,
`0x494B60` at 69.3%, `0x494C40` at 68.4%, and `0x494690` at 60.8%, all by
instruction-position diagnostics. None is claimed byte-exact or retried.
Harness destructors and tables are excluded from the import claims. The
translucent TU naturally emits additional compiler COMDATs; these are not
claimed as matches. Alpha-pool lifetime code remains deferred. No assembly or
artificial emission probes were added.

Matched lengths total **333,234 bytes**: 24.0% of listed functions and 8.8%
of listed function lengths. The padding heuristic misses 300 matched entries.
The diagnostic link reports **3,538 unique unresolved symbols**, **5,283
reference lines**, and zero duplicate definitions. Engine link closure and
whole-executable reproduction remain unfinished.

## Historical snapshot: Lucent methods and Vox playback lookup

As of **2026-10-21**, the latest verified snapshot has **4,679 fully matched
functions**, **170 partial rows**, **4,849 manifest rows**, **1,016 manifest
translation units**, and **1,026 tracked C++ files**. Whole-repository regression
and compile/layout checks passed with zero matched regressions; 94 tooling tests
pass. All project objects are current. The annotation audit reports 4,882 body
addresses and zero issues. Fourteen saved partial baselines are unchanged.

The latest batch adds 95 exact ordinary methods across three Lucent Blitter
clusters and promotes `VoxClass::Play` to an exact match. Strict checks verify
55 relocation fields in those Lucent methods and 15 across Play and its unchanged
matched sibling. The Lucent import excludes harness destructors, vtable emission
and alpha-pool lifetime code; complete class closure remains unproven.

The readable Snapshot constructor at `0x473750` now copies the two-unit range as a 32-bit
value, as retail does. It remains partial at 83.0% (44/53 instruction positions), not a
byte-exact match. Lucent50 `0x492830` remains partial at 0% by that diagnostic;
its emitted body is shorter than the retail span. No assembly or artificial
emission probes were added. Capped matching searches remain stopped.

Matched lengths total **329,559 bytes**: 23.7% of listed functions and 8.7%
of listed function lengths. The padding heuristic misses 300 matched entries.
The diagnostic link reports **3,537 unique unresolved symbols**, **5,275
reference lines**, and zero duplicate definitions. Engine link closure and
whole-executable reproduction remain unfinished.

## Historical snapshot: Native Blitter wrappers and verification hardening

As of **2026-10-21**, the latest verified snapshot has **4,583 fully matched
functions**, **170 partial rows**, **4,753 manifest rows**, **1,013 manifest
translation units**, and **1,023 tracked C++ files**. Whole-repository regression
and compile/layout checks passed with zero matched regressions; 94 tooling tests
pass. The project object index is current, and the duplicate audit reports zero
issues. Eleven older saved partial bodies and relocation offsets are unchanged.

Three Blitter clusters add 66 exact entries: 61 ordinary methods and five
compiler-generated deleting wrappers emitted by the production source without
probes. All 22 relocation fields across those spans resolve to retail targets.
The base table and three leaf tables pass conditional checks covering 20 slots;
these assume recorded compiler weak defaults and do not prove final-link
selection or complete class closure. The four emitted b-trans leaf wrappers
match only without `/GX`; paired flags leave its 24 ordinary method sections unchanged.

Three readable bodies remain partial: `0x493CC0` is 91.2% by instruction
comparison; `0x4912B0` and `0x7BC610` are 0% by that diagnostic. The first of
those zero-score candidates emits only 0x40 bytes for a 0x46-byte retail span,
so no complete-span raw-byte percentage is claimed. The manifest records these
metric qualifications. Alpha-pool lifetime code remains deferred to avoid a
conflicting global declaration. No assembly or artificial emission probes were
added.

The ownership gate now recognizes template annotations. The instruction checker
rejects a failed disassembler or missing function instead of reporting a false
0%; regression tests cover both fixes.

Matched lengths total **321,727 bytes**: 23.2% of listed functions and 8.5%
of listed function lengths. The padding heuristic misses 297 matched entries.
The diagnostic link reports **3,537 unique unresolved symbols**, **5,269
reference lines**, and zero duplicate definitions, compared with 3,535 unique
symbols and 5,264 references at commit `188f234`. Engine link closure and
whole-executable reproduction remain unfinished.

## Historical snapshot: Base64Pipe and early BlitPlain consolidation

As of **2026-10-21**, the latest verified snapshot has **4,517 fully matched
functions**, **167 partial rows**, **4,684 manifest rows**, **1,010 manifest
translation units**, and **1,020 tracked C++ files**. The 90-test suite,
compile/layout checks, and whole-repository regression passed with zero
matched regressions. All 1,020 C++ files produced current project objects and
passed the input-hash check. The annotation audit reports zero duplicate
issues; its count includes declaration-only markers. Eleven saved partial
bodies and relocation offsets are unchanged.

The latest consolidation migrates the already-matched Base64Pipe flush entry
from an address-scoped receiver to its RTTI-backed class. All four relocation
fields resolve to the codec entries and canonical Pipe methods. The complete
Base64Pipe size, lifetime and vtable emission remain unproven. This adds no new
match and introduces no runtime shim. A comment-only evidence correction was
followed by a fresh object build and focused byte/relocation checks.

Two confirmed false positives from the padding heuristic are recorded in
[padding classifications](scripts/data/padding_classifications.json): an
instruction interior at `0x417A70` and a switch table at `0x41A140`.

Eight ordinary `BlitPlain<unsigned char/unsigned short>` methods now match
full retail spans, including all four relocation fields to CRT `memmove`.
They use native C++ and emit no construction probes, sink globals, deleting
destructors or vtables; their table markers record retail identity only.
Both tested compiler flag sets produce exact bodies. Base/leaf lifetime and
production vtable emission remain unfinished.

Two independently checked manifest boundaries were corrected: SetPitch now
includes the complete `ret 4` instruction (0x156 bytes, still 100%); FlightPathStep
excludes eleven unreachable padding bytes (0x835 bytes, still partial, measured
9.2%). Neither source body changed. SetPitch's 16 relocation fields also agree
with their recorded retail targets.

Matched lengths total **318,385 bytes**: 22.9% of listed functions and 8.4%
of listed function lengths. The padding heuristic misses 292 matched entries.
The diagnostic link reports **3,535 unique unresolved symbols**, **5,264
reference lines**, and zero duplicate definitions, compared with 3,537 unique
symbols and 5,266 references at commit `0fbf9f5`. This diagnostic does not
establish engine link closure. Whole-executable reproduction remains unfinished.

## Historical snapshot: FilePipe

As of **2026-10-21**, the latest verified snapshot has **4,509 fully matched
functions**, **167 partial rows**, **4,676 manifest rows**, **1,009 manifest
translation units**, and **1,019 tracked C++ files**. The 90-test suite,
compile/layout checks, and whole-repository regression passed with zero
matched regressions. All 1,019 C++ files produced current project objects and
passed the input-hash check. The duplicate address audit found **4,709
addresses and zero issues**. Eleven saved partial-body byte/relocation checks
retain their baseline.

The native FilePipe batch adds three matches and migrates its existing deleting
wrapper. All four full function spans match; all four relocation fields resolve
to the retail targets. Its five-slot table passes a conditional check using the
recorded compiler weak default. Field offsets are asserted; the complete object
size and the file pointee's complete type remain unproven. This consolidates
one class without adding a runtime shim or artificial construction probe.

The manifest matches 22.8% of listed functions. Matched lengths total
**318,135 bytes**, or 8.4% of listed function lengths. The padding heuristic
misses 292 matched entries. The diagnostic link reports **3,537 unique
unresolved symbols**, **5,265 reference lines**, and zero duplicate definitions,
compared with 3,538 unique symbols and 5,265 references at commit `17b1d3e`.
This diagnostic does not establish engine link closure. Whole-executable
reproduction remains unfinished.

## Historical snapshot: fifteen vector pairs and FileStraw

As of **2026-10-21**, the latest verified snapshot has **4,506 fully matched
functions**, **167 partial rows**, **4,673 manifest rows**, **1,008 manifest
translation units**, and **1,018 tracked C++ files**. The 90-test suite,
compile/layout checks, and whole-repository regression passed with zero
regressions. All 1,018 C++ files produced current project objects and passed
the input-hash check. The duplicate
address audit found **4,706 addresses and zero duplicate issues**. Eleven saved
partial-body byte/relocation checks retain their baseline.

Fifteen native pointer-vector pairs contribute 180 entries (120 new matches,
60 migrations); FileStraw contributes three more (two new matches, one
migration). Together they add 122 matches and migrate 61 existing claims.
Across both groups, 183 function spans and 184 relocation fields match, and 31
tables pass checks covering 213 slots. These table checks use
recorded weak defaults where needed and remain conditional on those defaults.
The manifest matches 22.8% of listed functions. Their lengths sum to
**317,973 bytes**, or 8.4% of listed function lengths. The padding heuristic misses 291 matched entries.

The diagnostic link reports **3,538 unique unresolved symbols**, **5,265
reference lines**, and zero duplicate definitions, compared with 3,659 unique
symbols and 5,490 references at commit `094dcf9`. This diagnostic does not
establish engine link closure. Whole-executable reproduction remains unfinished.

## Historical snapshot: LCWPipe constructor and exact input method

The constructor at `0x551FF0` and input method at `0x5520A0` now match their
full retail spans. The constructor uses an inline Pipe base constructor whose
link-zeroing stores agree with the derived retail constructor. The permuter
closed the input method's register-allocation difference with a redundant
increment/decrement pair that VC6 removes. The source labels this explicitly
as compiler steering, not recovered original source; no extra instructions
remain in the compiled body. All five LCWPipe entries are now exact.

All 34 relocation fields across the five integrated spans agree with retail.
The LCWPipe and Pipe tables each pass five-slot conditional checks using the
recorded weak defaults. The RandomStraw fallback now calls the canonical Straw
slot directly; its two relocation targets are verified. The wider scoped
Pipe/SHA/Straw caller audit covers 44 call relocations.

The full regression and compile/layout gate passed, all 1,002 tracked C++ files
compiled, and 90 tooling tests passed. A comment-only evidence correction was
followed by a fresh object build; all five LCWPipe bodies and relocation offsets
remained identical to the checked objects. Eleven older saved partial bodies
remain unchanged; the prior LCWPipe partial was deliberately promoted after
its complete span matched. The permuter adapter now imports its adjacent
verification helpers without a manually configured `PYTHONPATH`; an isolated
Python subprocess test covers that failure.

Matched lengths total 309,312 bytes. The diagnostic link reports 3,659 unique
unresolved symbols, 5,490 reference lines and no duplicate definitions. Whole
executable reproduction remains unfinished.

## Historical snapshot: LCWPipe and remaining Straw callers

The native [LCWPipe implementation](match/core/lcw_pipe.cpp) replaces two
generic destructor bindings and adds an exact flush entry at `0x5522D0`.
Its input method at `0x5520A0` remains a 99% partial with two register-allocation
byte differences. All 31 relocation fields across the four integrated spans
resolve to the retail targets. Its five-slot table passes a conditional check:
slot zero uses the recorded VC6 weak default, and the partial input method is
bound explicitly for this table check. This does not establish a fully matched
class or final-link resolution.

The layout evidence identifies constructor entry `0x551FF0`, including its
`+0x20` store at `0x552030`. The declared `0x28` size records the observed field
extent; complete object size remains unproven. The block-header field offsets
are asserted. The remaining RandomStraw and CCINI cleanup aliases now call the
native Straw destructor; their 12 focused function checks remain exact.

The full regression, compile/layout gate, 1,002-object build and 89 tooling
tests passed. Eleven previously saved partial bodies retain identical bytes
and relocation offsets; the new LCWPipe partial has its own saved baseline.
There are 37 targeted Pipe/SHA/Straw caller-relocation checks, including the
six remaining generic dual-buffer cleanup entries. The diagnostic link reports
3,660 unique unresolved symbols, 5,490 reference lines and zero duplicate
definitions. Matched function lengths total 308,651 bytes; coverage is 22.2% of
listed functions and 8.1% of listed lengths. The padding heuristic misses 276
matched entries. Whole-image reproduction remains unfinished.

## Previous verified integration: nested pointer vectors and Straw

The nested-vector and mutable `char*` clusters and the native Straw
implementation add 17 exact function matches and migrate 13 existing address
claims: the vector clusters contribute 14 new matches and 12 migrations, while
Straw contributes three new matches and one migration. Their RTTI-backed tables
pass conditional checks for 31 slots across five tables. The nested vector's
14-entry implementation uses `VectorClass<DynamicVectorClass<char*>*>` and
`DynamicVectorClass<DynamicVectorClass<char*>*>`; the separate 12-entry `char*`
implementation does not claim a const-element specialization. The four-entry
Straw update includes the native deleting-destructor wrapper. These are
evidence-backed template bindings, not claims about recovered original source
files or complete pointee layouts.

The project-object relocation audit verified 32 relocation fields across 30
function spans. This is scoped binding evidence, not a whole-image comparison.
The tracked-source object build, compile/layout gate, and full regression all
passed. The `/dll /noentry /nodefaultlib` diagnostic link reports **3,664
unique unresolved symbols**, 5,490 reference lines and no duplicate
definitions; excluding default libraries means this does not establish engine
link closure.

Matched lengths total **308,460 bytes (301 KiB)**: 22.2% of listed functions
and 8.1% of listed function lengths. The current padding scan reports 276
matched entries missed by its heuristic. Generic families contain 115 deleting
bindings across 59 views, 58 base `Clear` rows, 56 native dynamic `Clear` rows
plus one DiskID stand-in, and six resize-family rows plus two other resize
helpers. The deleting-destructor sweep contains 72 rows. Complete executable
reproduction remains unfinished.

## Previous verified integration: MSAnimEntry vectors and Pipe/SHA stream methods

The native [MSAnimEntry pointer-vector implementation](match/core/vector_msanimentry_methods.cpp)
contains twelve entries: eight new exact matches and four migrated address
claims. Its two RTTI-backed seven-slot tables pass conditional checks against
the integrated project objects.

The shared [Pipe layout](match/_layout/pipe.h) and methods bind five entries,
including the ordinary destructor at `0x631C80`; the existing scalar-deleting
entry at `0x4AEC80` moved to the native class. The five-slot check is
conditional on VC6's unresolved deleting-destructor default. The `SHAPipe`
view adds exact method bodies at `0x69E9B0` and `0x69E9E0`, and three CCINI
stack-storage views now share the asserted [SHA pipe layout](match/_layout/sha_pipe_layout.h).
No native `SHAPipe` constructor, destructor, deleting wrapper, or vtable was
emitted in the four integration objects. The candidate for the retail
slot-zero wrapper at `0x477750` was not promoted: three natural C++ forms used
the wrong destructor call target, so the validated address-scoped stand-in
remains. No `SHAPipe` table-closure claim is made.

The eight dual-buffer destructor entries now preserve the retail call target
for each base cleanup: four Pipe entries call `0x631C80`, and four Straw entries
call `0x6C9850`. This binding was checked against the eight pinned retail call
instructions and their RTTI-identified LCW/LZO Pipe and Straw tables. The
25 targeted call-relocation checks for this batch are scoped evidence, not a
project-wide audit.

The batch adds fifteen new exact matches and migrates five existing claims.
The full regression passed with **4,364 matched functions**, 167 partial rows
and no regressions. All **998/998 tracked C++ files** produced current project
objects and passed the hash check. The compile/layout gate, 75 verifier tests
and duplicate-address check passed (4,564 addresses, zero problems). Eleven
saved partial-body byte/relocation checks retain their baseline bytes and
relocations. The `/dll /noentry /nodefaultlib` diagnostic link reports
**3,683 unique unresolved symbols**, 5,524 reference lines and no duplicate
definitions. Default libraries are excluded, so this diagnostic does not
establish engine link closure.

Matched lengths total **307,529 bytes (300 KiB)**: 22.1% of listed functions
and 8.1% of listed function lengths. The current padding scan reports 274
matched entries missed by its heuristic. Generic families contain 119 deleting
bindings across 63 views, 60 base `Clear` rows, 58 native dynamic `Clear` rows
plus one DiskID stand-in, and eight resize-family rows plus two other resize
helpers. The deleting-destructor sweep contains 73 rows. Complete executable
reproduction remains unfinished.

## Previous verified integration: TeamClass vectors, CD search paths and INI stream read

The native [TeamClass pointer-vector implementation](match/core/vector_teamclass_methods.cpp)
contains twelve entries across `VectorClass<TeamClass*>` and
`DynamicVectorClass<TeamClass*>`: seven new matches and five migrated address
claims, including the Dynamic `SetCapacity` row previously represented by a
resize-family view. The two RTTI-backed seven-slot tables pass conditional
checks against the integrated project objects. `/O2 /DNDEBUG /Gy` with `/GX`
disabled is required for the full Dynamic deleting-destructor body; the Vector
deleting body also matches with `/GX` enabled. These scoped table checks rely on
conditional weak defaults for deleting-destructor slots, not final-link evidence.

The [CD search-path methods](match/core/cd_global_state_update_methods.cpp)
add exact entries at `0x47AAC0`, `0x47AD50` and `0x47ADC0`. The 67-byte
`0x47AAC0` wrapper clears the list and tail-jumps to the separate helper at
`0x47AB10`; that helper remains unmatched. The 69-byte `0x47AD50` entry
allocates an eight-byte node and writes the observed `Next` and `Path` fields
at offsets `+0` and `+4`. Those calls now use the shared
[`SearchPath_0047AE10` layout](match/_layout/cd_search_path.h), whose size is
supported by the allocator request. No original owner or source boundary is
claimed.

The new 266-byte `0x474320` entry in
[CCINI stream reads](match/platform/ccini_class_read_ccfile_methods.cpp)
uses a supplied `Pipe` view and the receiver's digest fields; it does not
construct or clean up a local file stream. The source keeps its placeholder
symbol and argument types as ABI views; the original overload name is unknown.
This batch adds eleven new exact matches and migrates five existing address
claims.

The full regression passed with **4,349 matched functions**, 167 partial rows
and no regressions. All **995/995 tracked C++ files** produced current project
objects and passed the hash check. The compile/layout gate, 75 verifier tests
and duplicate-address check passed (4,549 addresses, zero problems). Eleven
saved partial-body byte/relocation checks retain their baseline bytes and
relocations. The `/dll /noentry /nodefaultlib` diagnostic link reports
**3,697 unique unresolved symbols**, 5,544 reference lines and no duplicate
definitions. Default libraries are excluded, so this diagnostic does not
establish engine link closure.

Matched lengths total **306,730 bytes (300 KiB)**: 22.0% of listed functions
and 8.1% of listed function lengths. The current padding scan reports 272
matched entries missed by its heuristic. Generic families contain 121 deleting
bindings across 64 views, 61 base `Clear` rows, 59 native dynamic `Clear` rows
plus one DiskID stand-in, and eight resize-family rows plus two other resize
helpers. Complete executable reproduction remains unfinished.

## Previous verified integration: RadarEvent vectors, memory-buffer cleanup calls and math entries

The native [RadarEvent pointer-vector implementation](match/core/vector_radar_event_methods.cpp)
now owns 12 existing address claims; it adds no new match rows. The obsolete
`VectorIntPair` implementation and header were removed. Both RTTI-backed
tables pass conditional seven-slot checks against their project objects.

Eight math routines at `0x4740B0` through `0x4741D0` were added to the
[address-ordered math implementation](match/core/math_global_updates_00473fe0.cpp),
and the [scalar state update at `0x47ADA0`](match/core/cd_global_state_update_methods.cpp)
adds one more exact match. Helper arguments and x87 results use compiler ABI
views; their
original return types, owning class and startup role remain unestablished.

Nine calls across six consumers now use the shared
[`MemoryBuffer::Clear`](match/core/memory_buffer_methods.cpp): INI CacheStraw,
MixFile, Convert, PCX preview, MS animation and smudge loading.
The old free-function symbol's unresolved object references fell from eight to
two, both in the separately scoped CcFile time-method views. CacheStraw records
the observed buffer prefix at `+0x0C` with an offset assertion; this does not
claim a complete object size or original member ownership.

The full regression passed with **4,338 matched functions**, 167 partial rows
and no regressions. All **994/994 tracked C++ files** produced current project
objects and passed the hash check. The compile/layout gate, 75 verifier tests
and duplicate-address check passed (4,538 addresses, zero problems). Eleven
saved partial-body byte/relocation checks retain their baseline bytes and
relocations. The `/dll /noentry /nodefaultlib` diagnostic link reports
**3,702 unique unresolved symbols**, 5,552 reference lines and no duplicate
definitions. Default libraries are excluded, so this diagnostic does not
establish engine link closure.

Matched lengths total **305,870 bytes (299 KiB)**: 22.0% of listed functions
and 8.1% of listed function lengths. The current padding scan reports 271
matched entries missed by its heuristic. Generic families contain 123 deleting
bindings across 65 views, 62 base `Clear` rows, 60 native dynamic `Clear` rows
plus one DiskID stand-in, and nine resize-family rows plus two other resize
helpers. Complete executable reproduction remains unfinished.

## Previous verified integration: MapSelection, ParticleClass and LightSourceClass vectors; CD slot 0

The native mutable-pointer vector implementations for
[MapSelection](match/core/vector_mapselection_methods.cpp),
[ParticleClass](match/core/vector_particleclass_methods.cpp) and
[LightSourceClass](match/core/vector_lightsourceclass_methods.cpp) add **23
exact matches** and migrate 13 prior claims. Each implementation covers 12
entries across `VectorClass<T*>` and `DynamicVectorClass<T*>`; retail RTTI
confirms the pointer element specialization and the zero-offset dynamic-to-base
chain. Their six integrated seven-slot tables pass conditional 7/7 checks.
The exact flags are `/O2 /DNDEBUG /Gy` with `/GX` disabled: each dynamic
deleting-destructor full body requires `/GX` off; with `/GX`, its emitted
COMDAT is shorter than the retail span.

The address-scoped [CD slot-0 method view](match/core/cd_callback_00473ab0.cpp)
also adds one exact match: its full 44-byte span at `0x4790E0` ends in `RET 4`.
The entry uses an ECX receiver, one stack dword, reads global byte `0x89E3A0`,
and writes a dword at receiver offset `+4`. RTTI associates its table at
`0x7E4C30` with `CD`, whose reported base chain includes zero-offset
`DiskSwap`; this view does not claim the complete class layout or original
method name. The batch adds **24 new matches** total.

The full regression passed with **4,329 matched functions**, 167 partial rows
and no regressions. All **993/993 tracked C++ files** produced current project
objects and passed the hash check. The compile/layout gate, 75 verifier tests
and duplicate-address check passed (4,527 addresses, zero problems). The
`/dll /noentry /nodefaultlib` diagnostic link reports **3,692 unique unresolved symbols**, 5,552 reference
lines and no duplicate definitions.
Default libraries are excluded, so this diagnostic does not establish engine
link closure.

Matched lengths total **305,606 bytes (298 KiB)**: 21.9% of listed functions
and 8.0% of listed function lengths. The current padding scan reports 271
matched entries missed by its heuristic. Generic families contain 125 deleting
bindings across 66 views, 63 base `Clear` rows, 61 native dynamic `Clear` rows
plus one DiskID stand-in, and nine resize-family rows plus two other resize
helpers. The complete executable target remains unfinished.

## Previous verified integration: three pointer-vector pairs and CD callback

Three native mutable-pointer vector implementations added 24 exact matches
and migrated 12 prior claims: [AlphaShapeClass](match/core/vector_alphashapeclass_methods.cpp),
[LightConvertClass](match/core/vector_lightconvertclass_methods.cpp) and
[EventClass](match/core/vector_eventclass_methods.cpp). Each covers 12 entries
across `VectorClass<T*>` and `DynamicVectorClass<T*>`; retail RTTI confirms the
element types and zero-offset dynamic-to-base chains. Their six integrated
seven-slot tables passed conditional 7/7 checks. The selected flags were
`/O2 /DNDEBUG /Gy` with `/GX` disabled: the dynamic deleting-body full span
requires `/GX` off, while the base deleting body also matched under `/GX`.

The [CD callback view](match/core/cd_callback_00473ab0.cpp) matched the
40-byte entry at `0x473AB0`. The callback uses slot zero of the RTTI-backed
three-slot `CD` table at `0x7E4C30`. Its local eight-byte stack reservation
does not establish the complete `CD` size; the source models only an
address-scoped callback view, leaves the remaining four bytes uninterpreted, and
uses a `void` call signature because slot zero's result is discarded. The
outer receiver byte at `+4` and its three callee-cleaned stack words are ABI
views; original owner and method signature are unknown. A [shared declaration
for `0x81C1D0`](match/_layout/global_0081c1d0.h) retains the existing C++
`g_FileSearchMode` symbol used by the callback and MixFile.

The [math-global update implementation](match/core/math_global_updates_00473fe0.cpp)
added six address-ordered routines. Its `double` return declaration for
`0x4CAC40` is an ABI view only; the helper's original return type remains
unconfirmed. That batch added 31 new matches (24 vector bodies, six math
routines and the callback) and migrated 12 existing address claims. The old
`BufferHolderDtor` and `BufferRelease` views then each contained 27 manifest
rows.

That snapshot's full regression passed with **4,305 matched functions**, 167
partial rows and no regressions. All **990/990 tracked C++ files** produced
current project objects and passed the hash check. The compile/layout gate, 75
verifier tests and duplicate-address check passed (4,503 addresses, zero
problems). Focused checks covered 359 matched rows and two existing partials
across 11 translation units. Nine saved partial-body byte/relocation checks and
both complete MixFile partial COMDATs retained their baseline bytes and
relocations. The `/dll /noentry /nodefaultlib` diagnostic link reported **3,714
unique unresolved symbols**, 5,595 reference lines and no duplicate
definitions. Default libraries are excluded, so this diagnostic does not
establish engine link closure.

Matched lengths totaled **304,034 bytes (297 KiB)**: 21.8% of listed functions
and 8.0% of listed function lengths. The padding scan reported 268 matched
entries missed by its heuristic. Generic families contained 131 deleting
bindings across 69 views, 66 base `Clear` rows, 64 native dynamic `Clear` rows
plus one DiskID stand-in, and 10 resize-family rows plus two other resize
helpers. The complete executable target remained unfinished.

## Previous verified integration: HouseType/AlphaLightingRemap vectors and table routines

The native [HouseTypeClass vector implementation](match/core/vector_housetypeclass_methods.cpp)
and [AlphaLightingRemapClass vector implementation](match/core/vector_alphalightingremapclass_methods.cpp)
each add eight new exact matches and migrate four prior address claims. Their
four integrated seven-slot tables pass conditional 7/7 checks. The new
[table lookup and reset routines](match/core/static_table_lookup_00473940.cpp)
add two matches: the lookup observes an 11-row, eight-byte-stride prefix with a
pointer at offset `+0` and an uninterpreted four-byte gap at `+4`, returning
STRING `0x817474` for out-of-range indices. The reset routine writes four
dwords at `0x89E280` through `0x89E28C`. The table at `0x81B7C8` and fallback
string at `0x817474` are in the writable `.data` section. The source's `__fastcall` and `void` declarations are
ABI bindings, not claims about original ownership or source signatures.

The [math-global update implementation](match/core/math_global_updates_00473570.cpp)
adds eight exact routines. With the two vector pairs, the batch adds 26 new
matches and migrates eight prior claims. Two helper functions at `0x4CAD50`
and `0x4CADE0` remain unclaimed after bounded source probes; their original
return types are unknown. The old `BufferHolderDtor` and `BufferRelease`
views now each contain 31 manifest rows.

The full regression passed with **4,274 matched functions**, 167 partial rows
and no regressions. All **985/985 tracked C++ files** produced current project
objects and passed the hash check. The compile/layout gate, 75 verifier tests
and duplicate-address check passed (4,472 addresses, zero problems). Focused
checks covered 367 matched rows across nine translation units. All nine saved
partial bodies retain identical bytes and relocation offsets. The
`/dll /noentry /nodefaultlib` diagnostic link reports **3,715 unique unresolved
symbols**, 5,587 reference lines and no duplicate definitions. Default
libraries are excluded, so this diagnostic does not establish engine link
closure.

Matched lengths total **302,155 bytes (295 KiB)**: 21.6% of listed functions
and 8.0% of listed function lengths. The current padding scan reports 265
matched entries missed by its heuristic. Generic families contain 133 deleting
bindings across 70 views, 67 base `Clear` rows, 65 native dynamic `Clear` rows
plus one DiskID stand-in, and 10 resize-family rows plus two other resize
helpers. The complete executable target remains unfinished.

## Previous verified integration: Airstrike/Bomb vectors and math-global updates

The native [AirstrikeClass vector implementation](match/core/vector_airstrikeclass_methods.cpp)
and [BombClass vector implementation](match/core/vector_bombclass_methods.cpp)
each contain 12 matched entries: eight new matches and four migrated address
claims. Their four integrated seven-slot tables pass conditional 7/7 checks.
Neither pair claims a standalone constructor or original translation-unit
ownership.

The [math-global update implementation](match/core/math_global_updates_004731c0.cpp)
now contains 13 exact, address-ordered routines, and the new
[473570 math-global implementation](match/core/math_global_updates_00473570.cpp)
contains five. Together with the vector pairs, the batch adds 29 new exact
matches and migrates eight prior claims. The routines use C linkage and
`void` result ABI bindings; global declarations follow observed access widths.
Original routine names, ownership and startup role are not claimed. Callers establish an eight-byte helper argument and
x87 result; the helper return type is retained as an ABI view and its original
type remains unconfirmed. Seven comments describing the former class-key
workaround were corrected without changing function bodies. The old
BufferHolderDtor and BufferRelease views now each contain 33 manifest rows.

The full regression passed with **4,248 matched functions**, 167 partial rows
and no regressions. The compile/layout gate, 75 verifier tests and the
duplicate-address check passed (4,448 addresses, zero problems). Focused checks
covered 116 matched rows across 13 translation units. All nine saved partial
bodies retain identical bytes and relocation offsets. The `/dll /noentry
/nodefaultlib` diagnostic link reports **3,702 unique unresolved symbols**,
5,573 reference lines and no duplicate definitions. Default libraries are
excluded, so this diagnostic does not establish engine link closure.

Matched lengths total **300,730 bytes (294 KiB)**: 21.5% of listed functions
and 7.9% of listed function lengths. The current padding scan reports 263
matched entries missed by its heuristic. Generic families contain 135 deleting
bindings across 71 views, 68 base `Clear` rows, 66 native dynamic `Clear` rows
plus one DiskID stand-in, and 10 resize-family rows plus two other resize
helpers. The complete executable target remains unfinished.

## Previous verified integration: class-key alignment, CaptureManager vectors and math globals

The MissionClass, RadioClass and TechnoClass spine and tracked sparse
ObjectClass/TechnoClass views now use `class` declarations with explicit public
sections. This matches the RTTI-backed class keys and keeps the existing public
ABI views; it does not unify the local layouts or establish Westwood's original
access declarations or complete hierarchies. Eight changed decorated-symbol
bindings were rechecked against retail bytes.

The native [CaptureManager vector implementation](match/core/vector_capturemanager_methods.cpp)
adds eight matched entries and migrates four prior address claims into the
VectorClass and DynamicVectorClass specializations. Both integrated seven-slot
tables pass conditional 7/7 checks. The [math-global update implementation](match/core/math_global_updates_004731c0.cpp)
adds five exact, address-ordered routines with C linkage and `void` result
ABI bindings. Referenced storage types follow the observed access widths;
original function names, ownership and startup role are unknown. The old BufferHolderDtor and
BufferRelease views now each contain 37 manifest rows.

The full regression passed with **4,219 matched functions**, 167 partial rows
and no regressions. All **979/979 tracked C++ files** produced current project
objects; compilation, 75 verifier tests and the duplicate-address check passed
(4,417 addresses, zero problems). Focused checks covered 108 matched rows
across 13 translation units. All nine saved partial bodies retain identical
bytes and relocation offsets. The `/dll /noentry /nodefaultlib` diagnostic link
reports **3,680 unique unresolved symbols**, 5,535 reference lines and no
duplicate definitions. Seven unresolved decorated names changed from struct
pointer to class pointer forms, the old `VTABLE_007E4AF4` reference disappeared,
and eight global dependencies appeared from the five math routines; the net
unresolved-symbol count did not decrease. Default libraries are excluded, so
this diagnostic does not establish engine link closure.

Matched lengths total **299,252 bytes (292 KiB)**: 21.4% of listed functions
and 7.9% of listed function lengths. The current padding scan reports 261
matched entries missed by its heuristic. Generic families contain 135 deleting
bindings across 71 views, 68 base `Clear` rows, 66 native dynamic `Clear` rows
plus one DiskID stand-in, and 10 resize-family rows plus two other resize
helpers. The complete executable target remains unfinished.

## Previous verified integration: CaptureManager receiver and node consolidation

Three existing matched methods—`CanCapture` (`0x471C90`), `FreeUnit`
(`0x471FF0`) and `NeedsToDrawLinks` (`0x472640`)—now use the shared
[`CaptureManagerClass`](match/_layout/capture_manager_class.h) receiver instead
of separate receiver definitions. `FreeUnit` also uses the shared
[`ControlNode`](match/_layout/control_node.h) layout, removing its duplicate
record view. The receiver now has one additional exact body,
[`FUN_004729C0`](match/combat/capture_manager_release_methods.cpp), whose
0xB6-byte entry exhibits deleting-destructor behavior. Its `FUN_` name is
retained; this does not claim recovery of the original destructor declaration
or the full COM hierarchy. The registry dispatch view and its used +0x10 slot
are asserted from the observed RTTI, constructor and call evidence. The
declaration-only `FUN_004723B0` binding remains provisional.

The full regression passed with **4,206 matched functions**, 167 partial rows
and no regressions. All **977/977 tracked C++ files** produced current project
objects; the compile/layout gate, 75 verifier tests and duplicate-address
check passed (4,404 addresses, zero problems). Focused checks covered 16
matched rows and one existing partial across eight translation units. All nine
saved partial bodies retain identical bytes and relocation offsets. The
`/dll /noentry /nodefaultlib` diagnostic link reports **3,673 unique unresolved
symbols**, 5,520 reference lines and no duplicate definitions. Default
libraries are excluded; this diagnostic does not establish engine link
closure. The previously unresolved canonical `FreeUnit` symbol is now defined, and
`FreeAll` now resolves its call to the canonical `CaptureManagerClass::FreeUnit`
body. The declaration-only `FUN_004723B0` binding remains unresolved; the total
unresolved-symbol count is unchanged.

Matched lengths total **298,589 bytes (292 KiB)**: 21.3% of listed functions
and 7.9% of listed function lengths. The padding heuristic misses 260 matched
entries. Generic families contain 135 deleting bindings across 71 views, 68
base `Clear` rows, 66 native dynamic `Clear` rows plus one DiskID stand-in, and
10 resize-family rows plus two other resize helpers. Engine link closure and
complete executable reproduction remain unfinished.

## Previous verified integration: CaptureManager canonical migration

Five existing methods now use the canonical
[`CaptureManagerClass`](match/_layout/capture_manager_class.h) declaration:
four in [`capture_manager_class.cpp`](match/combat/capture_manager_class.cpp)
and `GetOriginalOwner` in
[`capture_manager_class_more_methods.cpp`](match/combat/capture_manager_class_more_methods.cpp).
This removes two competing receiver definitions while preserving their matched
rows. The address-scoped `FreeUnit` body remains separate; its declaration-only
canonical reference was already unresolved in the prior link diagnostic. Other
receiver views remain separate, and the full COM inheritance is not recovered.

Two new exact methods in
[`capture_manager_state_methods.cpp`](match/combat/capture_manager_state_methods.cpp)
return `0x50` and `0x42` from six-byte bodies at `0x4729A0` and `0x4729B0`.
They occupy observed primary-vtable slots +0x30 and +0x2C. Their original
names and declared return types remain unknown. The state TU now has seven
matched rows, including its five existing methods.

The full regression passed with **4,205 matched functions**, 167 partial rows
and no regressions. All **976/976 tracked C++ files** produced current project
objects; the compile/layout gate, 75 verifier tests and duplicate-address
check passed (4,403 addresses, zero problems). Focused checks covered 12
matched rows across three translation units. All nine saved partial bodies
retain identical bytes and relocation offsets. The `/dll /noentry /nodefaultlib`
diagnostic link reports **3,673 unique unresolved symbols**, 5,519 reference
lines and no duplicate definitions. Default libraries are excluded; this
diagnostic does not establish engine link closure.

Matched lengths total **298,407 bytes (291 KiB)**: 21.3% of listed functions
and 7.9% of listed function lengths. The padding heuristic misses 260 matched
entries. Current generic families contain 135 deleting bindings across 71
views, 68 base `Clear` rows, 66 native dynamic `Clear` rows plus one DiskID
stand-in, and 10 resize-family rows plus two other resize helpers. Engine
link closure and complete executable reproduction remain unfinished.

## Previous integration: CaptureManager methods and shared stream view

The shared [`ControlNode`](match/_layout/control_node.h) layout replaces three
duplicate record definitions used by existing mind-control methods. The retail
allocator requests 0x14 bytes; binary accesses establish pointers at +0/+4,
frame data at +8, duration at +0x10, and an untyped four-byte gap at +0x0C.
The three existing consumers retain exact matches. Other `CaptureManager`
receiver views remain separate, and the full COM inheritance is not claimed.

[`capture_manager_state_methods.cpp`](match/combat/capture_manager_state_methods.cpp)
now contains five matched CaptureManager methods: `FUN_004722E0`,
`FUN_004726C0`, `FUN_004726F0`, `Save` at `0x4728E0`, and `GetClassID` at
`0x472960`. Save uses the observed `IStream::Write` slot at +0x10; the shared
[`Gg_IStream` prefix](match/_rt/gg_istream.h) records that `__stdcall` ABI.
`GetClassID` copies four observed DWORDs into a 16-byte output view. The FUN
names remain address-based; interface and field types are ABI models, not
recovered original source declarations. The broader COM hierarchy remains
unverified.

The full regression passed with **4,203 matched functions**, 167 partial rows
and no regressions. All **976/976 tracked C++ files** produced current project
objects; the compile/layout gate, 75 verifier tests and duplicate-address
check passed (4,401 addresses, zero problems). Focused checks covered 23
matched rows and one existing partial across six translation units. All nine
saved partial bodies retain identical bytes and relocation offsets. The
`/dll /noentry /nodefaultlib` diagnostic link reports **3,673 unique unresolved
symbols**, 5,519 reference lines and no duplicate definitions. Default
libraries are excluded; this diagnostic does not establish engine link
closure.

Matched lengths total **298,395 bytes (291 KiB)**: 21.3% of listed functions
and 7.9% of listed function lengths. The padding heuristic misses 260 matched
entries. Current generic families contain 135 deleting bindings across 71
views, 68 base `Clear` rows, 66 native dynamic `Clear` rows plus one DiskID
stand-in, and 10 resize-family rows plus two other resize helpers. Engine
link closure and complete executable reproduction remain unfinished.

## Previous integration: ControlNode vectors and math entries

The [`ControlNode*`](match/core/vector_controlnode_methods.cpp) vector pair
adds seven exact matches and migrates five existing claims. Retail RTTI
establishes the pointer element type, the zero-offset DynamicVectorClass-to-
VectorClass base chain, and two seven-slot tables at `0x7E4BC4` and `0x7E4BA4`.
Both tables pass conditional `--weak-defaults` checks against current project
objects. The full derived deleting-destructor body matches without `/GX`. No
ControlNode layout, constructor, TypeList specialization or original TU
boundary is claimed. Five existing address rows moved out of buffer-holder,
buffer-release and generic resize views into this class-specific TU; no old
row was dropped.

Two new exact entries at `0x43B110` and `0x43B130` bring
[the grouped math TU](match/core/math_global_updates_0043af70.cpp) to thirteen
matched rows. They write only observed dword values at the confirmed globals;
the source grouping does not establish original ownership or startup role.

The existing `GetOriginalOwner` row at `0x4722F0` now records its complete
0x32-byte span through the `RET 4` immediate; its C++ source is unchanged and
still matches all 50 bytes. The prior manifest length stopped at the `C2`
opcode. This extent correction adds two bytes to the sum of matched function lengths.

The full regression passed with **4,198 matched functions**, 167 partial
rows and no regressions. All **975/975 tracked C++ files** produced current
project objects; the compile/layout gate, 75 verifier tests and duplicate-
address check passed. Focused checks covered 105 rows across five translation
units. All eight verifier shards and the object-index build were rerun after
the span correction; compile/test inputs were unchanged. Eight saved partial
bodies retain identical bytes and relocation offsets. The
`/dll /noentry /nodefaultlib` diagnostic link reports **3,669 unique unresolved
symbols**, 5,513 reference lines and no duplicate definitions. Default
libraries are excluded; this diagnostic does not establish engine link
closure or a reduction in unresolved dependencies.

Matched lengths total **298,115 bytes (291 KiB)**: 21.3% of listed functions
and 7.9% of listed function lengths. The padding heuristic misses 260 matched
entries. Current generic families contain 135 deleting bindings across 71
views, 68 base `Clear` rows, 66 native dynamic `Clear` rows plus one DiskID
stand-in, and 10 resize-family rows plus two other resize helpers. Engine
link closure and complete executable reproduction remain unfinished.

## Previous integration: shared 0x89C818 storage view and math updates

The [shared storage view](match/_layout/global_0089c818.h) records the observed
two 16-bit writes at `0x89C818` and `0x89C81A`, plus a 32-bit read at
`0x89C818`. Its overlapping word/dword fields do not claim the original type,
signedness, semantic owner or pointer interpretation. The existing
`0x4587D0` call site uses an explicit dword-to-`void*` cast only to model its
observed argument slot.

Two new exact entries at `0x43B0E0` and `0x43B0F0` bring
[the grouped math TU](match/core/math_global_updates_0043af70.cpp) to eleven
matched rows. `0x43B0E0` clears the two observed words; `0x43B0F0` clears three
32-bit globals. The source grouping does not establish original ownership or
startup role.

Renderer comments were narrowed to observed instructions. Historical cross-
check provenance tags remain explicitly historical, not binary authority.
`0x5FF420` is still a 3.9% partial; its source body was unchanged in that batch,
and no retry strategy was attempted. Its header records the unresolved
8-byte/`float` mismatch at `0x7EF6F8`.

The full regression passed with **4,189 matched functions**, 167 partial rows,
and no regressions. All **974/974 tracked C++ files** produced current project
objects; the compile/layout gate, 75 verifier tests and duplicate-address
check passed. Focused checks covered 14 rows across two translation units.
Eight saved partial bodies retain identical bytes and relocation offsets. The
`/dll /noentry /nodefaultlib` diagnostic link reported **3,663 unique unresolved
symbols**, 5,504 reference lines and no duplicate definitions. Default
libraries were excluded, so this was not an engine-only gap census.

Matched lengths total **297,672 bytes (291 KiB)**: 21.2% of listed functions
and 7.8% of listed function lengths. The padding heuristic missed 259 matched
entries. Current generic families contained 135 deleting bindings across 71
views, 68 base `Clear` rows, 66 native dynamic `Clear` rows plus one DiskID
stand-in, and 10 resize-family rows plus three other resize helpers. Engine
link closure and complete executable reproduction remained unfinished.

## Previous integration: BulletTypeClass vectors, SpotLightClass spelling and grouped math updates

The [`BulletTypeClass*`](match/core/vector_bullettypeclass_methods.cpp) vector
pair adds **eight exact matches** and migrates four existing claims. Retail
RTTI establishes the pointer element type and zero-offset
DynamicVectorClass-to-VectorClass base chain. Its two seven-slot tables pass
conditional `--weak-defaults` checks against current project objects. The full
derived deleting-destructor bodies match with `/GX` disabled. No constructor,
TypeList specialization, pointee layout, complete object size, original TU
boundary or final-link selection is claimed.

Renderer references
now use the RTTI-backed `SpotLightClass` spelling in four files and three
manifest symbols. This identifies the element type and registry uses; no
standalone `SpotLightClass` RTTI descriptor was found, and the registry remains
an opaque vector view. The partial builder at `0x5FF420` remains a free routine.

The neutral
[math update implementation](match/core/math_global_updates_0043af70.cpp)
contains nine exact entries: two earlier ratios, five previously added
operations at `0x43AFB0`, `0x43AFD0`, `0x43AFF0`, `0x43B010` and `0x43B050`,
and two new operations at `0x43B080` and `0x43B0B0`. The entries load and store
the observed globals, use read-only `.rdata` constants, and call the observed
helpers where shown by the disassembly. These are grouped for organization;
their original source owners and startup role are unknown. The helper
declarations model the observed stack-double arguments and x87 result; the
original `float` versus `double` return declaration is not established.

The full regression, compile/layout gate, 75 verifier tests and
**974/974 tracked-source object build** passed. Eight saved partial bodies
retain identical bytes and relocation offsets. Focused checks covered 28 rows
across four translation units: 27 matched and one existing partial, with no
regression. The two BulletTypeClass tables pass conditional checks. The
`/dll /noentry /nodefaultlib` diagnostic link reports **3,660 unique unresolved
symbols**, 5,500 reference lines and no duplicate definitions. Default
libraries are excluded, so this is not an engine-only gap census.

Matched lengths total **297,639 bytes (291 KiB)**: 21.2% of listed functions
and 7.8% of listed function lengths. The padding heuristic misses 259 matched
entries. Current generic families contain 135 deleting bindings across 71
views, 68 base `Clear` rows, 66 native dynamic `Clear` rows plus one DiskID
stand-in, and 10 resize-family rows plus three other resize helpers. Engine
link closure and complete executable reproduction remain unfinished.

## Previous verified integration: `_WIN32_FIND_DATAA` and SpotLightClass vectors; grouped math updates

The [`_WIN32_FIND_DATAA*`](match/core/vector_win32_find_dataa_methods.cpp) and
[`SpotLightClass*`](match/core/vector_spotlightclass_methods.cpp) vector pairs
add **16 exact matches** and migrate eight existing claims: eight new and four
migrated for each pair. Retail RTTI establishes the pointer element types and
zero-offset DynamicVectorClass-to-VectorClass base chains. All four affected
seven-slot tables pass conditional `--weak-defaults` checks against current
project objects. The full derived deleting-destructor bodies match with `/GX`
disabled. No constructors, TypeList specializations, pointee layouts, complete
object sizes, original TU boundaries or final-link selection are claimed.

The neutral
[math update implementation](match/core/math_global_updates_0043af70.cpp)
contains seven exact entries: two earlier ratios and five new operations at
`0x43AFB0`, `0x43AFD0`, `0x43AFF0`, `0x43B010` and `0x43B050`. The entries load
and store the observed globals, use read-only `.rdata` constants, and call the
observed helpers where shown by the disassembly. These are grouped for
organization; their original source owners and startup role are unknown. The
helper declarations model the observed stack-double arguments and x87 result;
the original `float` versus `double` return declaration is not established.

The full regression, compile/layout gate, 75 verifier tests and
**973/973 tracked-source object build** passed. Eight saved partial bodies
retain identical bytes and relocation offsets. Focused checks covered 31 rows
across three translation units. The `/dll /noentry /nodefaultlib` diagnostic
link reports **3,666 unique unresolved symbols**, 5,513 reference lines and no
duplicate definitions. Default libraries are excluded, so this is not an
engine-only gap census.

Matched lengths total **296,988 bytes (290 KiB)**: 21.1% of listed functions
and 7.8% of listed function lengths. The padding heuristic misses 258 matched
entries. Current generic families contain 137 deleting bindings across 72
views, 69 base `Clear` rows, 67 native dynamic `Clear` rows plus one DiskID
stand-in, and 10 resize-family rows plus three other resize helpers. Engine
link closure and complete executable reproduction remain unfinished.

## Previous verified integration: KamikazeControl, IConnectionPoint and surface-description vectors; buffer prefixes and math routines

The `KamikazeControl*`, `IConnectionPoint*` and `_DDSURFACEDESC*` vector pairs
add **23 exact matches** and migrate 13 existing claims: eight new and four
migrated for KamikazeControl, seven new and five migrated for IConnectionPoint,
and eight new and four migrated for `_DDSURFACEDESC`. The IConnectionPoint
cluster includes the existing resize entry at `0x4A13C0`. Retail RTTI establishes
the pointer element types and zero-offset DynamicVectorClass-to-VectorClass
base chains. All six affected seven-slot tables pass conditional
`--weak-defaults` checks against current project objects. The full derived
deleting-destructor bodies match with `/GX` disabled; no constructors, TypeList
specializations, pointee layouts, complete object sizes, original TU boundaries
or final-link selection are claimed.

The address-scoped prefix view in
[buffer_prefix_methods.cpp](match/core/buffer_prefix_methods.cpp) now records
the entries at `0x43AF10` and `0x43AF20`, alongside five earlier entries. Their
observed fields are at `+0`, `+4` and `+8`; the 12-byte view is only a minimum
prefix, and class identity, full size and original ownership remain unknown.
Two 19-byte math routines at `0x43AF70` and `0x43AF90` are matched from their
observed global loads, divisions and stores. Their constant operands are in
read-only `.rdata`; the source does not claim when or why the routines run.

The full regression, compile/layout gate, 75 verifier tests and
**971/971 tracked-source object build** passed. Eight saved partial bodies
retain identical bytes and relocation offsets. Focused checks covered 45 rows
across five translation units. The `/dll /noentry /nodefaultlib` diagnostic
link reports **3,676 unique unresolved symbols**, 5,529 reference lines and no
duplicate definitions. Default libraries are excluded, so this is not an
engine-only gap census.

Matched lengths total **295,713 bytes (289 KiB)**: 21.0% of listed functions
and 7.8% of listed function lengths. The padding heuristic misses 256 matched
entries. Current generic families contain 141 deleting bindings across 74
views, 71 base `Clear` rows, 69 native dynamic `Clear` rows plus one DiskID
stand-in, and 10 resize-family rows plus three other resize helpers. Engine
link closure and complete executable reproduction remain unfinished.

## Previous verified integration: StartingTechnoStruct, NodeNameType and HWND vectors; buffer prefixes

The `HouseClass::StartingTechnoStruct*`, `NodeNameType*` and `HWND__*` vector
pairs add **23 exact matches** and migrate 13 existing claims: eight new bodies
and four migrated rows for StartingTechnoStruct, seven new and five migrated
for NodeNameType, and eight new and four migrated for HWND. RTTI establishes
the pointer element types and zero-offset DynamicVectorClass-to-VectorClass
base chains. All six affected seven-slot tables pass conditional
`--weak-defaults` checks against current project objects. The full derived
deleting-destructor bodies match with `/GX` disabled; no constructors,
TypeList specializations, pointee layouts, complete object sizes, original TU
boundaries or final-link selection are claimed. The nested
`HouseClass::StartingTechnoStruct` spelling uses the existing canonical
HouseClass declaration; it adds no data member or layout claim.

Four new entries at `0x43AD80`, `0x43ADF0`, `0x43AEB0` and `0x43AEF0` are
grouped with the earlier `0x43AD40` entry in
[buffer_prefix_methods.cpp](match/core/buffer_prefix_methods.cpp). Each uses
an address-scoped 12-byte C prefix view with observed fields at `+0`, `+4` and
`+8`; the complete object size and original class identities remain unknown.
The grouping is provisional organization and does not claim a shared original
owner or source translation unit. All five full entry spans match.

The full eight-shard regression, compile/layout gate, **75 verifier tests** and
**967/967 tracked-source object build** passed. Eight saved partial bodies
retain identical bytes and relocation offsets; focused checks covered 41 rows
across four translation units and direct raw checks covered all five prefixes.
The diagnostic `/dll /noentry /nodefaultlib` link reports **3,696 unique
unresolved symbols**, 5,567 reference lines and no duplicate definitions.
Default libraries are excluded, so this is not an engine-only gap census.

Matched lengths total **294,117 bytes (287 KiB)**: 20.9% of listed functions
and 7.7% of listed function lengths. The padding heuristic misses 253 matched
entries. Current generic families contain 147 deleting bindings across 77
views, 74 base `Clear` rows, 72 native dynamic `Clear` rows plus one DiskID
stand-in, and 11 resize-family rows plus three other resize helpers. Engine
link closure and complete executable reproduction remain unfinished.

## Previous verified integration: AnimationPalette and GlobalPacketType vectors, and MemoryBuffer

The nested `WorldDominationTour::Map::AnimationPalette*` and
`GlobalPacketType*` vector pairs add **16 exact matches** and migrate eight
existing claims. Each pair adds eight new bodies and moves four existing rows.
Retail RTTI establishes the pointer element types and zero-offset
DynamicVectorClass-to-VectorClass base chains. All four affected seven-slot
tables pass conditional `--weak-defaults` checks against current project
objects. The full derived deleting-destructor bodies match with `/GX` disabled;
no pointee layout, enclosing `Map` layout, constructor, TypeList binding,
original translation-unit boundary or final-link selection is claimed.

The existing 51-byte `MemoryBuffer::operator=` row is now implemented on the
shared `MemoryBuffer` declaration. Its behavior matches the retail entry: a
self-assignment guard, conditional release of the destination's owned buffer,
then borrowed pointer and size stores. The C++ reference spelling models the
observed ABI; no original parameter name is inferred. The former
`Owned_0043AE10` stand-in was removed; its existing row migrated to the shared
`MemoryBuffer` implementation.

The new 49-byte entry at `0x43AD40` is kept as an address-scoped 12-byte prefix
view. It confirms pointer and size stores at `+0` and `+4`, and an allocation
flag at `+8`; neither the original class identity nor complete object size is
known. The prefix is not assigned to `MemoryBuffer`.

The full eight-shard regression, compile/layout gate, **75 verifier tests** and
**964/964 tracked-source object build** passed. Eight saved partial bodies
retain identical bytes and relocation offsets; focused checks covered 30 rows
across five translation units. The diagnostic
`/dll /noentry /nodefaultlib` link reports **3,720 unique unresolved symbols**,
5,612 reference lines and no duplicate definitions. Default libraries are
excluded, so this is not an engine-only gap census.

Matched lengths total **292,435 bytes (286 KiB)**: 20.8% of listed functions
and 7.7% of listed function lengths. The padding heuristic misses 250 matched
entries. Current generic families contain 153 deleting bindings across 80
views, 77 base `Clear` rows, 75 native dynamic `Clear` rows plus one DiskID
stand-in, and 12 resize-family rows plus three other resize helpers. Engine
link closure and complete executable reproduction remain unfinished.

## Previous verified integration: IonBlastClass and LaserDrawClass vectors

The [IonBlastClass](match/core/vector_ionblastclass_methods.cpp) and
[LaserDrawClass](match/core/vector_laserdrawclass_methods.cpp) pointer-vector
pairs add **16 exact matches** and migrate eight existing claims: each adds
eight new bodies and moves four existing rows. Retail RTTI establishes their
pointer element types and zero-offset DynamicVectorClass-to-VectorClass base
chains. All four seven-slot tables pass conditional `--weak-defaults` checks
against current project objects. Paired probes show that each full derived
deleting body requires no GX; base deleting bodies also match with GX. No
pointee layout, constructor, TypeList binding, original translation-unit
boundary or final-link selection is claimed.

The separate `0x4101C0` identity audit left repository source unchanged. Its
constructor owner is supported as `AbstractClass`; a temporary explicit-vptr
prototype matched its tested bytes at 100%, with the unused 32-bit stack
argument modeled as `int`. Ordinary multiple inheritance emitted eight stores,
while a no-vtable variant emitted six. These probes do not establish the
original argument type or name, native multiple-inheritance vtables, or the
complete hierarchy. Two Bomb callers remain for separate integration.

The fourth hierarchy probe was rejected by automatic review at the three-attempt
limit before it ran. No retry was made; the existing source and matched row
remain unchanged.

The full eight-shard regression, compile/layout gate, **75 verifier tests** and
**961/961 tracked-source object build** passed. Eight saved partial bodies
retain identical bytes and relocation offsets. The diagnostic
`/dll /noentry /nodefaultlib` link reports **3,736 unique unresolved symbols**,
5,642 reference lines and no duplicate definitions. Default libraries are
excluded, so this is not an engine-only gap census.

Matched lengths total **291,250 bytes (284 KiB)**: 20.7% of listed functions
and 7.7% of listed function lengths. The padding heuristic misses 248 matched
entries. Current generic families contain 157 deleting bindings across 82
views, 79 base `Clear` rows, 77 native dynamic `Clear` rows plus one DiskID
stand-in, and 12 resize-family rows plus three other resize helpers. Engine
link closure and complete executable reproduction remain unfinished.

## Previous verified integration: E-Bolt/RadBeam vectors and native MemoryBuffer overloads

The [E-Bolt](match/core/vector_ebolt_methods.cpp) and
[RadBeam](match/core/vector_radbeam_methods.cpp) pointer-vector pairs add
**16 exact matches** and migrate eight existing claims: each adds eight new
bodies and moves four existing rows. Retail RTTI establishes the pointer
element types and zero-offset DynamicVectorClass-to-VectorClass base chains.
All four seven-slot tables pass conditional `--weak-defaults` checks against
current project objects. Paired flag probes show both base deleting bodies
also match with GX, while the full derived deleting bodies require no GX. No
pointee layout, constructor, TypeList binding, original translation-unit
boundary or final-link selection is claimed.

The existing 45-byte row at `0x43ADC0` is now the native
`MemoryBuffer(int)` constructor. It has no default argument and adds no
zero-argument constructor; the old `Owned_0043ADC0` stand-in is removed. The
existing `0x4101C0` row remains exact after that removal. The `0x4019A0`
deleting body now uses the asserted `MemoryBuffer` member at `+0x58`.
`ThemeClass::Scan` at `0x7207F0` uses a typed `MemoryBuffer*` view for cleanup
while retaining its raw 12-byte stack storage and explicit construction
order. The full spans of all affected bodies pass their raw oracle checks.

The full eight-shard regression, compile/layout gate, **75 verifier tests** and
**959/959 tracked-source object build** passed. Eight saved partial bodies
retain identical bytes and relocation offsets. The diagnostic
`/dll /noentry /nodefaultlib` link reports **3,752 unique unresolved symbols**,
5,672 reference lines and no duplicate definitions. Default libraries are
excluded, so this is not an engine-only gap census.

Matched lengths total **290,114 bytes (283 KiB)**: 20.6% of listed functions
and 7.6% of listed function lengths. The padding heuristic misses 246 matched
entries. Current generic families contain 161 deleting bindings across 84
views, 81 base `Clear` rows, 79 native dynamic `Clear` rows plus one DiskID
stand-in, and 12 resize-family rows plus three other resize helpers. Engine
link closure and complete executable reproduction remain unfinished.

## Previous verified integration: CrossDissolve vectors and typed MemoryBuffer cleanup calls

The [CrossDissolveEffect pointer-vector pair](match/core/vector_crossdissolveeffect_methods.cpp)
adds **eight exact matches** and migrates four existing claims. Retail RTTI
supports the pointer element type and zero-offset DynamicVectorClass-to-
VectorClass base chain. All twelve full entry-origin spans match under
`/O2 /DNDEBUG /Gy` without `/GX`; paired probes show the base deleting body
also matches with GX, while the full derived deleting body requires no GX.
Both seven-slot tables pass conditional `--weak-defaults` checks against
current project objects. No pointee layout, constructor, TypeList binding,
original translation-unit boundary or final-link selection is claimed.

The existing `MemoryBuffer::Clear` call is now expressed through typed views in
`FileSystem_LoadWholeFileEx` and `CCINIClass::WriteUUBlock`. Their complete
0x97-byte and 0x130-byte spans still match at 100%. In WriteUUBlock, the local
12-byte buffer storage and explicit constructor call remain; neither change
claims that the local was originally declared as `MemoryBuffer` or that
0x43AE50 is a destructor.

The full eight-shard regression, compile/layout gate, **75 verifier tests** and
**957/957 tracked-source object build** passed. Eight saved partial bodies
retain identical bytes and relocation offsets. The diagnostic
`/dll /noentry /nodefaultlib` link reports **3,768 unique unresolved symbols**,
5,705 reference lines and no duplicate definitions. Default libraries are
excluded, so this is not an engine-only gap census.

Matched lengths total **288,996 bytes (282 KiB)**: 20.5% of listed functions
and 7.6% of listed function lengths. The padding heuristic misses 244 matched
entries. Current generic families contain 165 deleting bindings across 86
views, 83 base `Clear` rows, 81 native dynamic `Clear` rows plus one DiskID
stand-in, and 12 resize-family rows plus three other resize helpers. Engine
link closure and complete executable reproduction remain unfinished.

The bounded GetFileTime attempt was rejected before execution because it
targeted the explicitly excluded set-file-time/file-time scope, outside the
current authorization. No compile or oracle ran, no workaround was attempted,
and work continued on the independent cleanup callers above.

## Previous verified integration: MemoryBuffer cleanup and AnimClass/ButtonFadeEffect vectors

The existing `MemoryBuffer::Clear` row at `0x43AE50` is now bound to the shared
type in [memory_buffer_methods.cpp](match/core/memory_buffer_methods.cpp). Its
full 0x28-byte body matches retail; instructions establish conditional freeing
through the ownership byte and unconditional clearing of the pointer, size and
ownership byte. The BSurface member at `+0x14` now uses `MemoryBuffer`, and its
`0x411650` call is expressed as `Inner.Clear()`; the two BSurface pixel methods
remain exact. The former `Owned_0043AE50` header is removed. The CCFile I/O and
read headers also use the shared layout, preserving four existing exact rows.
Other direct `FUN_0043AE50` adapters and caller views remain; this is not a
repository-wide caller migration or a destructor claim.

The mutable [AnimClass pointer-vector](match/core/vector_animclass_ptr_methods.cpp)
and [ButtonFadeEffect pointer-vector](match/core/vector_buttonfadeeffect_methods.cpp)
clusters add 16 exact matches and migrate eight existing claims: each adds
eight new bodies and moves four existing rows. The mutable AnimClass cluster
is separate from the existing `const AnimClass*` implementation, which remains
unchanged. Retail RTTI supports the element spellings and zero-offset dynamic
base chains; no pointee layouts, constructors, TypeList entries, or original
translation-unit boundaries are claimed. All four seven-slot tables pass
conditional `--weak-defaults` checks. Paired flag probes show that each
cluster's dynamic deleting body needs no GX; the AnimClass base deleting body
also matches with GX. No-GX objects reproduce the checked 0x49-byte deleting
bodies.

The eight-shard regression, compile/layout gate, **75 verifier tests** and
**956/956 tracked-source object build** passed. Eight saved partial bodies
retain identical bytes and relocation offsets. The diagnostic
`/dll /noentry /nodefaultlib` link reports **3,777 unique unresolved symbols**,
5,722 reference lines and no duplicate definitions. Default libraries are
excluded, so this is not an engine-only gap census.

Matched lengths total **288,428 bytes (282 KiB)**: 20.5% of listed functions
and 7.6% of listed function lengths. The padding heuristic misses 243 matched
entries. Current generic families contain 167 deleting bindings across 87
views, 84 base `Clear` rows, 82 native dynamic `Clear` rows plus one DiskID
stand-in, and 12 resize-family rows plus three other resize helpers. Engine
link closure and complete executable reproduction remain unfinished.

## Previous verified integration: shared MemoryBuffer and Subtitle/MapRegion vectors

The constructor at `0x43AD00` now has a native `MemoryBuffer` binding in
[memory_buffer_methods.cpp](match/core/memory_buffer_methods.cpp); its complete
`0x31`-byte body matches retail. The shared layout asserts the pointer at `+0`,
size at `+4`, ownership byte at `+8`, and total size `0x0C`. The size is also
bounded by `CCFileClass::Close` using the `Buffer` at `+0x58` and `Position` at
`+0x64`. The model names and `bool` spelling are source choices; the binary
establishes the field offsets and ownership-byte behavior. Six affected
CCFileClass rows still pass their focused check. The former
`Owned_0043AD00` stand-in is removed. Other local MemoryBuffer views, including
the CCFile read and I/O views, remain to be consolidated.

Native [SubTitle](match/core/vector_subtitle_methods.cpp) and
[MapRegionClass](match/core/vector_mapregionclass_methods.cpp) vector
specializations cover 24 rows: 15 new exact matches and nine migrated claims.
SubTitle contributes eight new rows and four migrations; MapRegionClass adds
seven new rows and migrates five, including `SetCapacity` at `0x5AC820` from
the resize helper. Entry-origin spans and raw comparisons cover all rows.
The two SubTitle and two MapRegionClass seven-slot tables pass conditional
`--weak-defaults` checks against project objects. The deleting-destructor rows
use their separately emitted base and dynamic symbols. Paired flag probes show
that both SubTitle deleting bodies need no GX; MapRegionClass's dynamic
deleting body needs no GX, while its base deleting body also matches with GX.
The no-GX candidates reproduce their `0x49`-byte retail spans; GX emits short
wrappers for the SubTitle pair and the MapRegionClass dynamic wrapper.
No pointee layout, constructor, TypeList, original source-TU boundary, or
final-link resolution is claimed.

The eight-shard regression, compile/layout gate, **75 verifier tests** and
**954/954 tracked-source object build** passed. Eight saved partial bodies
retain identical bytes and relocation offsets. The diagnostic
`/dll /noentry /nodefaultlib` link reports **3,793 unique unresolved symbols**,
5,751 reference lines and no duplicate definitions. Default libraries are
excluded, so this is not an engine-only gap census.

Matched lengths total **287,292 bytes (281 KiB)**: 20.4% of listed functions
and 7.6% of listed function lengths. The padding heuristic misses 241 matched
entries. Current generic families contain 171 deleting bindings across 89
views, 86 base `Clear` rows, 84 native dynamic `Clear` rows plus one DiskID
stand-in, and 12 resize-family rows plus three other resize helpers. The
deferred ShadowBlock caller candidate is being investigated at `0x3B0`; no
ShadowBlock source was changed in this batch.
Engine link closure and complete executable reproduction remain unfinished.

## Previous verified integration: native GenericNode constructor and two vector pairs

The former explicit initializer at `0x40E320` is now the native
`GenericNode()` constructor in [the INI node translation unit](match/platform/ini_class_node_methods.cpp).
Its full 17-byte span matches retail under `/O2 /DNDEBUG /Gy /GX /Ob2`.
`GenericList()` relies on automatic construction of its two `GenericNode`
members, seats the list table and links the sentinels; `InitList()` remains an
explicit reset helper. The existing `INIEntry` constructor retains its later
link resets and still matches. The prior stand-in name and translation-unit
binding are removed. The GenericNode, GenericList, and INI list primary tables
pass direct one-slot checks against current objects. This does not recover all
callers, original hierarchy, or the complete GenericNode virtual API.

The [ShadowControlClass pointer-vector](match/core/vector_shadowcontrolclass_methods.cpp)
and [nested WinsockBufferType pointer-vector](match/core/vector_winsockbuffer_methods.cpp)
specializations add **16 exact matches** and migrate eight existing family
claims: eight new bodies and four migrated bindings per specialization.
Retail RTTI supports the element spellings and zero-offset dynamic-to-base
views. The Winsock source only models the nested pointer spelling; neither
enclosing nor pointee layout is claimed. Both seven-slot tables per pair pass
conditional `--weak-defaults` checks. Full entry-origin body spans and raw
comparisons support the new bindings. The 0x49-byte `DynamicVectorClass`
deleting bodies require no GX; paired GX objects emit 0x20-byte wrappers.

The eight-shard regression, compile/layout gate, **75 verifier tests**, and
**951/951 tracked-source object build** passed. Seven saved partial bodies
retain identical bytes and relocation offsets. The diagnostic
`/dll /noentry /nodefaultlib` link reports **3,810 unique unresolved symbols**,
5,782 reference lines and no duplicate definitions. Default libraries are
excluded, so this is not an engine-only gap census.

Matched lengths total **286,332 bytes (280 KiB)**: 20.3% of listed functions
and 7.5% of listed function lengths. The padding heuristic misses 239 matched
entries. Current generic families contain 175 deleting bindings across 91
views, 88 base Clear rows, 86 native dynamic Clear rows plus one DiskID
stand-in, and 13 resize-family rows plus three other resize helpers. Engine
link closure and complete executable reproduction remain unfinished.

## Previous verified integration: six media and network pointer-vector pairs

The [VocClass](match/core/vector_vocclass_methods.cpp),
[VoxClass](match/core/vector_voxclass_methods.cpp),
[MovieHandle](match/core/vector_moviehandle_methods.cpp),
[WaypointPathClass](match/core/vector_waypointpathclass_methods.cpp),
[tConnInfoStruct](match/core/vector_tconninfostruct_methods.cpp) and
[unsigned-char pointer](match/core/vector_unsigned_char_ptr_methods.cpp)
pairs add **48 exact matches** and migrate 24 existing claims. Each pair has
eight new bodies and four moved bindings. Retail RTTI and function bodies
support the pointer element types and zero-offset `DynamicVectorClass` base
views; `tConnInfoStruct` remains a struct-pointer specialization. No new
constructor, TypeList binding or original source-file boundary is claimed.

Full entry-origin spans and raw comparisons support all 48 new bodies. Paired
GX/no-GX probes confirm the 0x49-byte derived deleting entries require no GX;
GX emits 0x20-byte wrappers. All twelve seven-slot tables pass conditional
`--weak-defaults` checks against current project objects.

The native [GenericList](match/platform/ini_class_node_methods.cpp) constructor at
`0x52ACE0` and `List<INIEntry*>` constructor at `0x52AF50` match their full
retail spans (0x69 and 0x6F bytes) in the INI translation unit using
`/O2 /DNDEBUG /Gy /GX /Ob2`. This removes the GenericListObject stand-in;
explicit-vptr modeling and the original virtual API remain incomplete.

The full eight-shard regression, compile/layout gate, **75 verifier tests** and
**949/949 tracked-source object build** passed. Seven saved partial bodies
retain identical bytes and relocation offsets. The diagnostic
`/dll /noentry /nodefaultlib` link reports **3,826 unique unresolved symbols**,
5,812 reference lines and no duplicate definitions. Default libraries are
excluded, so this is not an engine-only gap census.

Matched lengths total **285,196 bytes (279 KiB)**: 20.2% of listed functions
and 7.5% of listed function lengths. The padding heuristic misses 237 matched
entries. Remaining generic families contain 179 deleting bindings across 93
views, 90 base Clear rows, 88 native dynamic Clear rows plus one DiskID
stand-in, and 13 resize-family rows plus three other resize helpers. Engine
link closure and complete executable reproduction remain unfinished.

## Previous verified integration: six native pointer-vector pairs

The [TriggerTypeClass](match/core/vector_triggertypeclass_methods.cpp),
[TActionClass](match/core/vector_tactionclass_methods.cpp),
[TEventClass](match/core/vector_teventclass_methods.cpp),
[TemporalClass](match/core/vector_temporalclass_methods.cpp),
[TiberiumClass](match/core/vector_tiberiumclass_methods.cpp) and
[VeinholeMonsterClass](match/core/vector_veinholemonsterclass_methods.cpp)
pointer-vector pairs added **48 exact matches** and migrated 24 existing
claims. Each pair contained twelve distinct matched bodies. Retail RTTI
confirmed the pointer types and zero-offset `DynamicVectorClass` to
`VectorClass` base chains.

Full entry-origin REA spans and raw comparisons supported every row. GX/no-GX
probes reproduced each 0x49-byte dynamic deleting body only without GX; GX
produced short 0x20-byte wrappers. All twelve seven-slot tables passed
conditional `--weak-defaults` checks against project objects. No new
constructor, TypeList or original source-file boundary was claimed.

The full eight-shard regression, compile/layout gate, **75 verifier tests** and
**943/943 tracked-source object build** passed. Seven saved partial bodies
retained identical bytes and relocation offsets. The diagnostic
`/dll /noentry /nodefaultlib` link reported **3,874 unique unresolved symbols**,
5,902 reference lines and no duplicate definitions. Default libraries were
excluded, so this was not an engine-only gap census.

A typed TagType append experiment reached 97.9%, with an ADD destination and
following PUSH differing. After three source attempts, automatic approval
review rejected a fourth retry, citing the three-attempt limit. The experiment
was preserved outside the repository; the exact existing constructor and
shared headers were restored and reverified. No append API or constructor
regression landed in that batch. The registry cleanup remained partial.

Matched lengths totaled **281,788 bytes (275 KiB)**: 20.0% of listed functions
and 7.4% of listed function lengths. The padding heuristic missed 230 matched
entries. Remaining generic families contained 191 deleting bindings across 99
views, 96 base Clear rows, 94 native dynamic Clear rows plus one DiskID
stand-in, and 13 resize-family rows plus three other resize helpers. Engine
link closure and complete executable reproduction remained unfinished.

## Previous verified integration: typed TagType registry and four vector pairs

`TagTypeClass::Array` now uses the actual shared
`DynamicVectorClass<TagTypeClass*>` type, replacing its layout-only declaration.
The [registry definition](match/ai/tag_type_class_array.cpp) asserts its accessed
fields and complete 0x18-byte storage. Retail startup at `0x6E5AE0` confirms the
concrete dynamic-vector table, empty items/capacity/count, flags 1/0 and growth
10. The natural C++ static object reproduces that complete **61-byte initializer**
with `/O2 /Ob2 /DNDEBUG /Gy`; `/Ob2` combines the initialization and cleanup
registration helpers as in retail. This is one new exact match.

The factory, lookup, loader and saver now access typed items directly, removing
six casts. The existing constructor helper still views both this registry and
the separate `0xB0F670` registry through its explicit adapter; that helper is
not newly consolidated. Six saved bodies in the affected caller TUs retain
identical bytes and relocation offsets.

The generated cleanup at `0x6E5B20` is a **new documented partial**: retail is
59 bytes, while VC6 emits 88 bytes with an extra guard byte and branch. Its
instruction comparison is 0%; it is not counted as matched. Natural-object,
flag-bisection and explicit-destructor probes did not resolve the difference,
so further matching was capped and work continued elsewhere. No assembly or
manual startup/cleanup adapter was added. Runtime initialization is now modeled,
but the cleanup and complete-image fidelity remain unfinished.
(Superseded: the VectorClass batch makes the registry a namespace-scope
`TagTypes` object, which removes the guard and matches 0x6E5B20.)

The [DiskLaserClass](match/core/vector_disklaserclass_methods.cpp),
[EMPulseClass](match/core/vector_empulseclass_methods.cpp),
[GraphicMenuItem](match/core/vector_graphicmenuitem_methods.cpp) and
[TagTypeClass](match/core/vector_tagtypeclass_methods.cpp) pointer-vector pairs
add **31 exact matches** and migrate seventeen existing claims. GraphicMenuItem
adds seven and migrates five, including its former generic resize entry;
the other pairs each add eight and migrate four. All eight seven-slot tables,
plus the registry object's emitted dynamic table, pass conditional
`--weak-defaults` checks. Full entry-origin spans and GX/no-GX probes confirm
the actual derived deleting symbols and required no-GX flags. No new vector
constructor or TypeList binding is claimed.

The full eight-shard regression, compile/layout gate, **75 verifier tests** and
**937/937 tracked-source object build** passed. Six saved existing partial
bodies also remain byte-for-byte unchanged with identical relocation offsets.
The diagnostic `/dll /noentry /nodefaultlib` link reports **3,922 unique
unresolved symbols**, 5,992 reference lines and no duplicate definitions.
Default libraries are excluded, so this is not an engine-only gap census.

Matched lengths total **278,380 bytes (272 KiB)**: 19.8% of listed functions and
7.3% of listed function lengths. The padding heuristic misses 224 matched
entries. Remaining families have 203 deleting bindings across 105 views,
102 base Clear rows, 100 native dynamic Clear rows plus one DiskID stand-in,
and 13 resize-family rows plus three other resize helpers. Engine link closure
and complete executable reproduction remain unfinished.

## Previous verified integration: shared GenericNode and three vector pairs

Three existing GenericNode entries now use the shared
[GenericNode/GenericList implementation](match/core/generic_list_methods.cpp):
the 17-byte initializer, 75-byte link operation and 69-byte deleting body.
Two duplicate layout views are removed. Entry-origin instructions and RTTI
confirm `NextNode` at +4 and `PrevNode` at +8; the old view had reversed these
names, which are now corrected without changing the compiled behavior.
All three complete bodies retain their exact matches. The initializer remains
an explicitly modeled entry; native C++ constructor emission is not claimed.

The GenericNode table is now a defined one-slot member-function-pointer cell,
verified **1/1 without weak defaults** against retail slot zero at `0x7E1B0C`.
Shared inline initialization/teardown references that definition. GenericList's
separate UI deleting body also uses its defined table, removing an unresolved
alias. GenericList and both INI list tables retain their direct 1/1 checks.
Original complete virtual declarations remain unrecovered; this is the
documented explicit-vptr model. The 71-function focused check retained every
match before the full regression.

The [CCINIClass](match/core/vector_cciniclass_methods.cpp),
[ColorScheme](match/core/vector_colorscheme_methods.cpp) and
[CoopCampaignClass](match/core/vector_coopcampaignclass_methods.cpp) pointer-vector
pairs add **23 exact matches** and migrate thirteen claims. ColorScheme adds
seven and migrates five, including the former generic resize entry `0x627F90`;
the other pairs each add eight and migrate four. All six seven-slot tables pass
conditional `--weak-defaults` checks against current project objects. Actual
derived deleting symbols reproduce the full 0x49-byte bodies with no-GX;
GX emits short wrappers. CCINI's earlier temporary symbol/span errors were
corrected before integration and independently rechecked over the complete
entry-origin spans. No new constructor or TypeList binding is claimed.

The eight-shard regression, compile/layout gate, **75 verifier tests** and
**933/933 tracked-source object build** passed. Six existing partial emitted
bodies remain byte-for-byte unchanged with identical relocation offsets.
The `/dll /noentry /nodefaultlib` diagnostic link reports **3,954 unique
unresolved symbols**, 6,049 reference lines and no duplicate definitions.
Default libraries are excluded, so this is not an engine-only gap census.

Matched lengths total **276,223 bytes (270 KiB)**: 19.6% of listed functions and
7.3% of listed function lengths. The padding heuristic misses 219 matched
entries. The remaining generic families contain 211 deleting bindings across
109 views, 106 base Clear rows, 104 native dynamic Clear rows plus one DiskID
stand-in, and 14 resize-family rows plus three other resize helpers. Engine
link closure and complete executable reproduction remain unfinished.

## Previous verified integration: shared list templates and three vector pairs

The INI entry and section lists now use a shared `List<T>` model with their
RTTI-confirmed zero-offset `GenericList` base. The entry-list constructor and
both deleting entries retain their complete 111/179/179-byte matches.
The section-list entry replaces an opaque host. `INIClass::Sections` and
`INISection::EntryList` use the actual template specializations with asserted
0x1C storage. Their original complete virtual API remains unrecovered; the
explicit inherited vptr model is documented.

The [GenericList deleting entry](match/core/generic_list_methods.cpp) also
replaces an opaque host and duplicate node layout. Retail RTTI and slot zero
identify its complete 179-byte body at `0x40E3E0`. Its table and both INI list
tables are now explicit one-slot member-function-pointer cells, each verified
**1/1 without weak defaults** against its project object. Shared inline list
operations reference the defined GenericList table instead of embedding its
retail address. This does not claim recovered native virtual declarations or
complete-image identity. All 18 initially affected existing functions retain
their matches.

The [FactoryClass](match/core/vector_factoryclass_methods.cpp),
[FileEntryClass](match/core/vector_fileentryclass_methods.cpp) and
[ConvertClass](match/core/vector_convertclass_methods.cpp) pointer-vector pairs
add **24 exact matches** and migrate twelve existing claims. Each pair's two
seven-slot tables pass conditional `--weak-defaults` checks against its project
object. Full-span checks and GX/no-GX probes establish the no-GX flags needed
for each full dynamic deleting body. No new constructor or TypeList binding is
claimed. FileEntryClass's isolated REA provider failed; current Ghidra entry
boundaries and pinned-PE full-byte comparisons supply its verification evidence.

All eight regression shards, the compile/layout gate, 75 verifier tests and
the **930/930 tracked-source object build** passed. Six existing partial emitted
bodies were also checked unchanged against saved baseline objects. The current
`/dll /noentry /nodefaultlib` diagnostic link reports **3,981 unique unresolved
symbols**, 6,098 reference lines and no duplicate definitions. Its default
libraries are excluded; this is not an engine-only gap census.

Matched lengths total **274,695 bytes (268 KiB)**: 19.5% of listed functions and
7.2% of listed function lengths. The padding heuristic misses 216 matched
entries. Remaining generic families have 217 deleting bindings across 112
views, 109 base Clear rows and 107 native dynamic Clear rows plus one DiskID
stand-in. A CCINIClass vector pair has passed corrected temporary probes but
is not integrated or counted here. Engine link closure and complete executable
reproduction remain unfinished.

## Previous verified integration: nested INI nodes and two vector pairs

The shared [INI node layouts](match/_layout/ini_nodes.h) now use the
RTTI-confirmed nested `INIClass::INIEntry` and `INIClass::INISection` names
and their zero-offset `Node<T>` bases. Their accessed offsets remain asserted;
the explicit vptr model and unrecovered original virtual API are documented.
Twelve existing node functions retain exact matches. `GetKeyCount` and
`GetKeyName` now belong to the shared INIClass and use these layouts, retaining
their complete 193-byte and 205-byte matches. `GetSection` also uses the shared
class; its existing partial score is unchanged, and all 304 emitted bytes and
relocation offsets are preserved. Complete CCINIClass recovery remains pending.

The two index miss paths now bind separate entry and section pointer defaults
at `0xB78830` and `0xB7882C`. REA disassembly and lookup callers confirm their
roles; PE section extents confirm loader-zero storage. Both definitions now
exist in the project, replacing one incorrect shared placeholder. The affected
matched methods retain their matches, and both existing index partial bodies
are unchanged.

The [DamageGroup pointer vectors](match/core/vector_damagegroup_methods.cpp)
and [BuildingLightClass pointer vectors](match/core/vector_buildinglightclass_methods.cpp)
add **16 exact matches** and migrate eight existing claims. Each pair has two
seven-slot tables verified conditionally against its project object with
`--weak-defaults`; this is not final-link proof. GX/no-GX probes establish the
no-GX flags needed for the full dynamic deleting bodies. No new constructor or
TypeList recovery is claimed.

The full eight-shard regression, compile/layout gate, 75 verifier tests and
tracked-source object build passed. The diagnostic `/dll /noentry /nodefaultlib`
link reports **4,008 unique unresolved symbols**, 6,145 reference lines and no
duplicate definitions. The shared INI lookups and both default cells resolve.
Default libraries are excluded, so this is not an engine-only gap census.

A bounded `GetEntry` recovery reached 4.3% (154 instruction differences in that
comparison); it remains temporary work outside the repository, with no manifest
row added. Work continued on other functions under the standing instruction.
Matched lengths now total **272,991 bytes (266 KiB)**: 19.4% of listed functions
and 7.2% of listed function lengths. The padding heuristic misses 213 matched
entries. Remaining generic families have 223 deleting bindings across 115
views, 112 base Clear rows and 110 native dynamic Clear rows plus one DiskID
stand-in. Complete engine linking and byte-for-byte image reproduction remain
unfinished.

## Previous verified integration: shared INI layout and native type factories

The shared [INIClass layout](match/_layout/ini_class.h) replaces three
competing declarations. Retail RTTI and entry-origin teardown instructions
confirm its fields; inline initialization and a neighboring live stack object
bound its size to 0x40. Its **200-byte native virtual destructor** is a new
exact match. The compiler-generated 30-byte deleting entry preserves its
existing match and replaces an opaque sweep host. Its one-slot table passes
conditionally with `--weak-defaults`. The retained CCINI deleting wrapper now
calls the native base destructor, without claiming complete CCINI recovery.

[GenericNode and GenericList](match/_layout/generic_list.h) now have shared
layouts and inline operations across the INI and UI clusters, with RTTI class
keys and asserted fields. The index prefix also has a shared definition. All
24 initially affected existing functions retain their matches. INIClass's
concrete `List<INISection*>` member is identified by RTTI but remains represented
by its explicitly named GenericList prefix. Full native list construction,
CCINIClass consolidation and the remaining nested-node views are still pending.

The [TagTypeClass and TriggerTypeClass factories](match/ai/type_find_or_allocate_methods.cpp)
now use their native classes, registries and `new` expressions. Both full
131-byte bodies retain their matches with no-GX flags. Tag INI loading calls
the canonical TriggerTypeClass factory, removing its free-function alias.

The [TechnoClass pointer vector pair](match/core/vector_technoclass_methods.cpp)
adds **six exact matches** and migrates six existing buffer-release, deleting,
resize and lookup claims. Both seven-slot tables pass conditional checks. Full
REA spans and GX/no-GX probes support the pair; constructor and copy methods
are not newly claimed. Together with the INI destructor, this batch adds
**seven exact matches**.

The current `/dll /noentry /nodefaultlib` diagnostic link reports 4,027 unique
unresolved symbols (6,173 reference lines), with no duplicate definitions.
The native INIClass destructor and both type factories resolve; their retired
aliases no longer appear. Default libraries are excluded, so these counts
are not an engine-only gap census. Integrated linking and complete-image
comparison remain unfinished.

The AbstractTypeClass constructor remains unimplemented. Its bounded temporary
recovery attempts did not pass the full-span oracle; no candidate row was added.

Matched lengths total 271,855 bytes (265 KiB): 19.3% of listed functions and
7.2% of listed function lengths. The padding heuristic misses 211 matched
entries. The generic vector families retain 227 deleting bindings across 117
views, 114 base Clear rows, 112 native dynamic Clear rows plus one DiskID
stand-in, and 15 resize-family rows plus three other resize helpers. The buffer
release and deleting families each retain 41 rows; ten type factories remain
in their generic family.

## Previous verified integration: native type construction and shared list methods

The native [TriggerTypeClass constructor](match/ai/trigger_type_class_ctor.cpp)
and [TagTypeClass constructor](match/ai/tag_type_class_ctor.cpp) match their
complete 374-byte and 314-byte retail bodies. Both use natural C++ base
construction, field assignments and vector appends, with no assembly or shim.
GX/no-GX probes confirm their no-GX flags. The base constructor declaration
at `0x410800` now has its native signature; its implementation remains pending.
All four explicit AbstractClass vptr offsets are now asserted.

[TagTypeClass](match/_layout/tag_type_class.h) has one shared layout header.
TagTypeClass and TriggerTypeClass list loaders and savers now belong to their
native classes and use the shared registry prefixes. Native `new` replaces
both list-loader construction adapters and retains their complete matches;
the two savers retain theirs. Explicit primary-slot call views remain until
the full COM signatures are recovered. The canonical TagTypeClass registry at
`0xB0E780` and shared region at `0xB0F658` have loader-zero storage evidence;
original ownership and later initialization remain unconfirmed.

The OverlayClass and MSTextEntry pointer-vector pairs add **15 new matches**
and migrate nine existing claims, including one resize stand-in. Their four
seven-slot vtable checks pass conditionally with `--weak-defaults`; final-link
selection remains unproved. Together with the two constructors, this batch
adds **17 exact matches**.

That batch's `/dll /noentry /nodefaultlib` diagnostic link reported 4,035 unique
unresolved symbols (6,176 reference lines), with no duplicate definitions.
Native TagTypeClass and TriggerTypeClass constructor calls now resolve; the
native AbstractTypeClass base constructor remains unresolved. Default libraries
are excluded, so these counts are not an engine-only gap census. Integrated
engine linking and complete-file comparison remain unfinished.

Matched lengths total 271,301 bytes (265 KiB): 19.2% of listed functions and
7.1% of listed function lengths. The padding heuristic misses 211 matched
entries. Remaining families bind 227 generic deleting bodies across 117 views,
114 base Clear rows, 112 native dynamic Clear rows plus one DiskID stand-in,
and 15 resize-family rows plus four other generic resize helpers.

## Previous verified integration: shared TriggerTypeClass and six vector pairs

The [shared TriggerTypeClass declaration](match/_layout/trigger_type_class.h)
replaces nine competing definitions. Fresh entry-origin REA analysis and raw
retail RTTI confirm its zero-offset AbstractTypeClass base, constructor field
writes, and the loader's 0xB4 allocation. Field names remain descriptive;
constructor writes alone do not establish their semantics. Its registry at
`0x8B4178` now has one loader-zero prefix definition, without claiming original
ownership or later initialization. TagClass construction and chain traversal
use the shared types instead of private prefix views and retain their matches.

The AbstractTypeClass, AITriggerTypeClass, TeamTypeClass,
ParticleSystemTypeClass, EgoClass and WaveClass pointer vector pairs add
**48 new exact matches** and migrate 24 existing claims into native template
specializations. Their twelve
seven-slot vtable checks pass conditionally with `--weak-defaults`; these are
scoped checks, not final-link evidence. Full retail spans, RTTI and GX/no-GX
probes support each pair. No assembly or shim was needed.

That batch's `/dll /noentry /nodefaultlib` diagnostic link reported 4,060 unique
unresolved symbols (6,212 reference lines), with no duplicate definitions.
Default libraries are excluded, so these are not engine-only gap counts.
At that point the loader's address-specific adapter remained in place and its
native constructor was pending; the latest batch replaces both.

Matched function lengths total 269,653 bytes (263 KiB): 19.2% of listed
functions and 7.1% of listed function lengths. The padding heuristic misses
209 matched entries. Residual vector families contain 231 generic deleting
bindings across 119 instantiation views, 116 base Clear rows, 114 native
dynamic Clear rows plus one DiskID stand-in, and 16 address-scoped resize-family rows. Four other resize helpers remain
in `vector_resize_methods.cpp`.

## Previous verified integration: shared TriggerClass and object registries

The [shared TriggerClass declaration](match/_layout/trigger_class.h) replaces
its competing method-specific definitions. Ten existing exact methods retain
their matches; the partial `ResetTimers` body and relocation offsets are
unchanged from the previous project objects. TagClass and House callers now
use this declaration or an explicitly named deleting-call view. Its RTTI
class key, 0x48-byte allocation size, accessed fields and link aliases are pinned.
Complete COM inheritance remains pending; TriggerTypeClass was consolidated in the latest batch.

The [native TriggerClass constructor](match/ai/trigger_class_ctor.cpp) is a
new **partial source recovery**, not a new match. The fixed 403-byte retail-span
oracle reports 79.1% (102/129 instructions; 27 differences), concentrated in
final branch ordering. Independent review confirmed the observed base call,
field and vptr writes, three vector appends, timer reset and mode/flag behavior.
The native GetInstance expression is exact with no-GX flags. Three matching
strategies were exhausted; the remaining delta stays documented rather than
being counted as exact.

The [native AbstractClass destructor](match/core/abstract_class_dtor.cpp)
preserves the existing full 28-byte match, replacing its opaque host. This
resolves the native base destructor call. The TagClass destructor still has
no committed implementation: its capped local candidate reached 57.5%
(127/221 instructions; 94 differences) and remains outside the manifest.

[Shared registry storage](match/core/abstract_registry.cpp) now binds the
vector-shaped prefixes at `0xB0F670`, `0xB0F698`, and `0xB0F708`. In particular,
`0xB0F698` is used by TagClass, TriggerClass, DiskLaser and ObjectClass; the
previous TagClass-specific member name was too narrow. Their storage aliases
now agree, and all eight initially affected exact rows remain exact. The
original owning class and runtime initialization remain unconfirmed. The
TriggerClass registry at `0xA8EAE8` also has one definition shared by its methods
and the House teardown caller.

Fresh AbstractTypeClass constructor/RTTI evidence replaces its private-path
citation and confirms its `class` key and zero-offset AbstractClass base. It
also corrects a stale vptr-address example. That constructor establishes member
starts and observed writes; it does not alone prove every array bound or the
closing size. TriggerTypeClass declarations now consistently use the RTTI
`class` key while retaining their existing prefix views.

The [VoxelAnimTypeClass](match/core/vector_voxelanimtypeclass_methods.cpp),
[ScriptTypeClass](match/core/vector_scripttypeclass_methods.cpp), and
[TriggerClass](match/core/vector_triggerclass_methods.cpp) vector pairs contain
36 exact rows: 24 new matches and 12 migrated claims. Their six seven-slot tables
pass conditional `--weak-defaults` checks on project objects. Full REA entry
spans and GX/no-GX probes support each native pair; no-GX reproduces the full
derived deleting bodies.

The `/dll /noentry /nodefaultlib` diagnostic link still fails with 4,112 unique
unresolved symbols (6,306 reference lines), and no duplicate definitions.
The native TriggerClass constructor and AbstractClass destructor now resolve;
source resolution does not imply exact matching of the partial constructor.
Old queue/TriggerArray aliases are absent from unresolved references. The
TagClass destructor remains unresolved. Default libraries are excluded, so
these counts are not an engine-only gap census. Engine link closure and the
whole-image comparison remain unfinished.

Matched function lengths total 266,245 bytes (260 KiB): 18.9% of listed
functions and 7.0% of listed function lengths. The padding heuristic misses
203 matched entries. Residual vector families contain 243 generic deleting
bindings across 125 instantiation views, 122 base Clear rows, 120 native
dynamic Clear rows plus one DiskID stand-in, and 16 resize rows.

## Previous verified integration: native TagClass construction and one shared definition

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
At that snapshot, native TagClass and AbstractClass constructor symbols resolved.
The native TagClass destructor and TriggerClass constructor remained unresolved; normalized
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
At that snapshot, four methods retained conflicting legacy class definitions.
Those definitions required consolidation before an integrated C++ build could
satisfy the one-definition rule; complete TagClass hierarchy recovery was pending.

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
verified snapshot, the inventory has 1,001 tracked C++ files and 4,548 manifest
rows across 991 manifest translation units, with no manifest TU missing from
tracked sources. Ten tracked files
have no manifest rows; the inventory also records two source basename
collisions. The report lists those cases explicitly.
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
The goal is a buildable, structured C++ project whose classes, inheritance,
interfaces and source organization follow Westwood's as closely as binary
evidence allows. Each annotated engine function must reproduce the retail
instructions with the period compiler, with confirmed layouts and bindings.
Statically linked CRT and third-party source recovery is outside scope.
Reconstruction and integrated engine linking remain in progress.

The function is the unit of matching. Successful compilation and individual
matches do not establish whole-executable identity, and the project does not
promise a byte-identical executable.

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
| Whole-image identity | Not established. Current gates do not produce or compare a complete `gamemd.exe`. | No byte-identical executable is promised; retain per-function verification as the matching standard. |
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
  the [Gadget constructor](match/ui/gadget_class_ctor.cpp) is exact.
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
  `CountedVector::Destroy` stand-ins. The family files bind 58 base and 56
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
  family has 121 bindings across 64 base-template instantiation views. Their
  written vptr and RTTI identify the base-destruction path and element type,
  but do not establish each wrapper's original declaring class, source-file boundaries,
  or duplicate-COMDAT linker behavior. The int and ToolTip specializations
  account for the slot-zero targets in their retail base and derived tables.
  The dynamic `Clear` total excludes the DiskID entry at `0x69C4A0`, which
  retains the `CountedVector<DiskID>::Destroy` matching stand-in because its
  retail declaring class is unresolved; other legacy users are marked
  `VectorClassLayout` or `DynamicVectorClassLayout`. Other virtual methods and
  original source-file ownership remain incomplete.
  The resize helpers retain eight address-specific family views and two other
  generic resize helpers. SmudgeType's `0x67B050` SetCapacity body now has a native binding.
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

- [Blitter](match/render/blitters/blitter.h) now underlies the native
  [Trans](match/render/blitters/b_trans.h),
  [Darken/Z](match/render/blitters/b_darken_xlatz.h), and
  [PlainXlat](match/render/blitters/b_plainxlat.h) families. Shared Z/alpha wrap
  declarations pin the touched offsets and globals. Five deleting wrappers
  emit naturally from production source; other lifetime and table claims stay
  limited to verified subsets. The alpha-pool lifetime code remains deferred.

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
| Functions matched at 100% | **5,064** | **25.6%** of 19,753 |
| Sum of matched function lengths | 376,290 bytes | 9.9% of 3,797,269 listed function bytes |
| Functions in progress (partial match) | 233 | 1.2% |
| Tracked C++ files under `match/` | 1,082 | |
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
listed entries, including 312 matched entries. Its candidate count is therefore
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
matching scope under [AGENTS.md](AGENTS.md). An integrated engine link still
needs those library dependencies. Per-function matching does not prove
whole-image identity.

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
