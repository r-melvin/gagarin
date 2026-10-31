// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Obj_/Gbl_ views below are per-function placeholder receivers. Replacing
//   them with the canonical class re-mangles their symbols, so that is left to
//   a separate rename-only change.
//
// Accepted /Ob2 partial drop: 0x43FB20 5.6% -> 4.9%.
//   Complete 0x43FB20..0x44057B body (0xA5B bytes, two RETs plus the shared
//   exit) read from the entry-bounded retail function. RTTI COL 0x7FC360 names
//   BuildingClass; its primary table 0x7E3EBC holds this function at slot 23.
//   Virtual calls are slot offsets divided by four: 0x350 = 212, 0x184 = 97,
//   0x1D4 = 117, 0x1D8 = 118, 0x200 = 128, 0x1EC = 123, 0x124 = 73,
//   0x3C8 = 242, 0x3AC = 235, 0x16C = 91, 0x1B8 = 110, 0xAC = 43, 0xD4 = 53.
//
//   Full 0x226-byte function at 0x453840 confirmed from retail gamemd.exe
//   v1.001 disassembly and focused REA evidence.
//
//   match/economy/house_building/building_a_methods_1.cpp.)
//
//   Bodies disassembled from retail gamemd.exe v1.001 at the addresses below.
//
// BuildingClass members, ordered ascending by retail address.
// Address index: 0x44F7A0, 0x455B90, 0x4529E0.
//
//   Original translation unit TU038 of retail gamemd.exe v1.001 (BuildingClass); its source-file
//   name is not attested by the binary, so the file keeps a placeholder name. Code range
//   0x43af40-0x45af9f; this file holds the BuildingClass-owned functions (RTTI class ownership,
//   vtable slots) and the rows that were already here, in ascending retail address order.
//   Other-class rows of the range stay in their own files.
//   Obj_/Gbl_ views below are per-function placeholder receivers. Replacing them with the canonical
//   class re-mangles their symbols, so that is left to a separate rename-only change.
//
//   The source-file name is not attested by the binary; the range was segmented from retail evidence
//   (link-ordered static-initialiser table, RTTI class ownership, neighbouring object bounds).
//
//   First batch of the building-a cluster: the short BuildingClass virtual methods. Every body was read
//   from the retail gamemd.exe v1.001 from its entry to its last RET, and every offset it touches is
//   pinned in building_a_views.h. Method names are slot labels (vf_N = primary-table byte offset / 4)
//   or FUN_<addr>: no original name is confirmed for them.
//
// BuildingClass entries 0x458A80..0x459F20 of the "building-b" cluster (views: building_b_views.h).
//
// TechnoClass bodies for primary-table (0x7F4960) slots 164, 177, 188-190,
// 200, 205, 207-211, 224, 247 and 270, emitted together at 0x459D80..0x459E62
// inside the building code. Slot numbers come from the RTTI-located table;
// names are placeholders (techno_class.h).
//
// Retail PAVFoggedObjectClass RTTI establishes the pointer element type and zero-offset
// DynamicVectorClass -> VectorClass base chain. Complete entry-origin spans
// establish the bound methods. GX emits a short derived deleting wrapper;
// no GX reproduces its full retail body. No TypeList or constructor is bound;
// original TU boundaries, final link and complete object sizes are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
//
// Retail PAVInfantryClass RTTI establishes the pointer element type and zero-offset
// DynamicVectorClass -> VectorClass base chain. Complete entry-origin spans
// establish the bound methods. GX emits a short derived deleting wrapper;
// no GX reproduces its full retail body. No TypeList or constructor is bound;
// original TU boundaries, final link and complete object sizes are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
//
// BuildingClass entries 0x4544A0..0x455DA0 of the "building-b" cluster (views: building_b_views.h).
//
// BuildingClass entries 0x44F5C0..0x4527D0 of the "building-b" cluster (views: building_b_views.h).
//
// Retail RTTI type descriptors name VectorClass<Reestablish*> and
// DynamicVectorClass<Reestablish*>; each address below is the vtable slot body
// of that specialization (slot owner read from the retail vtables).
// Pointer/scalar/enum element: no element layout is claimed.
//
//   Second batch of the building-a cluster: BuildingClass virtual methods of medium size. Every body was
//   read from the retail gamemd.exe v1.001 from its entry to its last RET; offsets are pinned in
//   building_a_views.h. Method names are slot labels (vf_N = primary-table byte offset / 4).
//
//   Third batch of the building-a cluster: the larger BuildingClass virtual methods. Every body was read from
//   the retail gamemd.exe v1.001 from its entry to its last RET with a linear decode of the retail bytes
//   (Ghidra's function-flow listing drops instructions after some calls); offsets are pinned in
//   building_a_views.h. Method names are slot labels (vf_N = primary-table byte offset / 4).
//
// BuildingClass entries 0x453A70..0x454260 of the "building-b" cluster (views: building_b_views.h).
//
// Buffer-holder deleting destructors, ordered ascending by retail address.
//
// The buffer-release template, ordered ascending by retail address.
//
// is written out longhand per the family rule.
//
// Translation unit: BuildingClass::GetPowerDrain.
//
//   LIBRARY: GAMEMD 0x7C5F00  __ftol  (CRT double->long; the (int) cast; reloc)
//
//   Evidence: disassembly of 0x458750; the same sequence is inlined in the
//   BuildingClass update body (building_class_update.cpp).
//
//   cross-checked against YRpp.
//
//   GLOBAL:   GAMEMD 0x00A83CBC g_SWArray (SWTypeClass** array Items)
//
//   Every displacement, constant and callee below was read off the user's retail
//   gamemd.exe v1.001 with the local Ghidra CLI at the address in each annotation.
//   The owning classes are not bound by RTTI or a binary string at these addresses,
//   so each receiver keeps a placeholder name derived from its address.
//
// Round 12 small unowned leaves between 0x402000 and 0x540000. Ordered ascending by
// retail address.
//
//   Retail gamemd.exe v1.001 disassembly at 0x451EA0; Anims at +0x55C and the
//   AnimClass flag byte at +0x19D come from the canonical layouts.
//
//   0x451EA0  BuildingClass::SetAnimInvisible
//   0x454CF0  BuildingClass::FUN_00454CF0
//   0x454D30  BuildingClass::FUN_00454D30
//   0x4598D0  BuildingClass::FUN_004598D0
//
//   Bodies disassembled from retail gamemd.exe v1.001 at the addresses below.
//
// BuildingClass members, ordered ascending by retail address.
// Address index: 0x43EE50, 0x451F60, 0x4528A0.
//
//   See building_draw_methods.h. Slot numbers and offsets are those of the
//   primary BuildingClass table at 0x7E3EBC; every field offset below is the
//   one the instruction at the cited retail address uses.

#include "../combat/building_class_fog_methods.h"

// Is every foundation cell of this building fogged? Walks the type's
// foundation list (terminated by a {0x7FFF,0x7FFF} entry), offsets each entry
// by the building's own map coordinates and tests the fog bit on the cell;
// the first clear cell answers false.
//
// The two coordinate locals are the whole frame (SUB ESP,8): `cell` is first
// the out-parameter of the map-coords slot and then the argument handed to
// GetCellAt, `base` the dereferenced result that VC6 hoists into EDI/BX and
// whose slot the per-cell sum then reuses. Writing them as four locals costs
// a third slot.
//
// MATCHED (100.0%, 50/50). The residual block-order delta (retail lays the
// `XOR AL,AL` block directly after the loop's back-jump and the `MOV AL,1`
// block last, VC6 the reverse) was a flattened function boundary, not a
// compiler difference: retail's source has the foundation walk as its own
// routine, and this method is the wrapper around it. Written as an inline
// helper carrying the loop and both of its returns, with the wrapper spelled
// as an explicit `if (!AllFogged(...)) { return false; } return true;`, the
// failure block gains the second predecessor the earlier passes were hunting
// for and cl places both blocks where retail has them. 92.0% to 100%.
// Variants measured this pass: the same helper forwarded directly
// (`return AllFogged(...)`, 92.0%, the old score); the helper taking `base`
// as a const reference (92.0%); the cell test alone lifted into an inline
// `CellFogged` helper with the loop left in place (63.5%); and the sense
// inverted as an `AnyClear` helper negated by the wrapper (72.0%). Earlier
// passes had tried, all at 92.0% or worse: while-loop with in-loop
// `return false`; `for(;;)` with the terminator `break`ing to `return true`;
// `for(;;)` with the terminator returning true and the clear cell `break`ing
// to `return false`; gotos to labelled returns in retail's textual order;
// `continue`-shaped bodies; a `for` with `++fd` in the header; and a
// `bool fogged` flag set false on the clear cell and returned after the loop
// (90.0%).
//
// The foundation walk itself: offset each entry by the building's map
// coordinates and test the fog bit; the first clear cell answers false.
static inline bool AllFogged_00457A10(CellStruct const* fd, CellStruct base,
                                      CellStruct& cell)
{
    while (fd->X != 0x7FFF || fd->Y != 0x7FFF) {
        CellStruct sum;
        sum.X = fd->X + base.X;
        sum.Y = fd->Y + base.Y;
        cell = sum;
        if (!(DAT_0087F7E8.FUN_005657A0(&cell)->Flags & 0x400000))
            return false;
        ++fd;
    }
    return true;
}

#include "../combat/building_class_kill_occupants_methods.h"

#include "../_layout/building_class.h"
#include "../_layout/building_type_class_layout.h"
#include "../_layout/house_class.h"
#include "../_layout/house_type_class.h"
#include "../_layout/anim_class.h"
#include "../_layout/cell_class.h"
#include "../_layout/cell.h"
#include "../combat/airstrike_class_methods.h"
#include "../core/rules_class.h"
#include "../core/frame_counter.h"
#include "../map/map_class_methods.h"
#include "../ui/tactical_class_coords_to_client_methods.h"
#include "../_layout/map_0087f7e8.h"
#include "../map/map_class_area_methods.h"

// FUNCTION: GAMEMD 0x7509E0 (decl; reloc) -- ECX = sound, EDX = coordinate,
// one stack argument (the sound's audio controller).
void FUN_007509E0(int sound, const CoordStruct* coordinate, AudioController* controller);

// FUNCTION: GAMEMD 0x750D40 (decl; reloc) -- ECX = coordinate, EDX = audio controller.
void FUN_00750D40(const CoordStruct* coordinate, AudioController* controller);

// The global object whose method 0x5FB2E0 converts a rate.
struct Global_00A8EB60
{
    // FUNCTION: GAMEMD 0x5FB2E0 (decl; reloc) -- one stack argument.
    int FUN_005FB2E0(int rate);
};

// GLOBAL: GAMEMD 0xA8EB60
extern Global_00A8EB60 DAT_00A8EB60;
// GLOBAL: GAMEMD 0x887324 -- the tactical object.
extern Tactical* DAT_00887324;
// GLOBAL: GAMEMD 0xABAD1C
extern int DAT_00ABAD1C;
// GLOBAL: GAMEMD 0x7E1718
extern const double DAT_007E1718;

// The frame timer's remaining time, expanded inline at each use: the whole
// duration while unstarted, 0 once it has run out, otherwise what is left.
static int TimeLeft(const CDTimerClass& timer)
{
    int left = timer.TimeLeft;
    if (timer.StartTime != -1) {
        int passed = CurrentFrame - timer.StartTime;
        if (passed >= left)
            return 0;
        left -= passed;
    }
    return left;
}

#include "../combat/building_coord_00453840.h"

#include "../core/small_misc36_methods.h"

#include "../core/small_misc50_methods.h"

#include "../_layout/abstract_type_class.h"
// GLOBAL: GAMEMD 0x887734
extern const wchar_t DAT_00887734[];
// STRING: GAMEMD 0x817830
extern const char STR_00817830[];

// FUNCTION: GAMEMD 0x734E60 (decl; reloc)
wchar_t* __fastcall StringTable_LoadString(const char*, int*, const char*, int);

// GLOBAL: GAMEMD 0x818CE8
extern const char STR_00818CE8[];

#include "../core/small_misc54_methods.h"

#include "../_layout/building_class.h"
#include "../_layout/house_class.h"
#include "../_layout/cell_class.h"
#include "../_layout/map_0087f7e8.h"

// GLOBAL: GAMEMD 0xA8E7AC -- nonzero while the scenario is being set up.
extern int ScenarioInit_00A8E7AC;

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0xA8E7AC
int ScenarioInit_00A8E7AC;
// END defined globals

#include "house_building/building_a_views.h"
#include "../_layout/session_class.h"
#include "../_layout/swizzle_manager_class.h"
#include "../_layout/building_class.h"
#include "../_layout/house_class.h"
#include "../_layout/tactical.h"

// FUNCTION: GAMEMD 0x772A90 (decl; reloc) - WeaponTypeClass::AllowedThreats, the weapon type in ECX.
unsigned int FUN_00772A90(WeaponTypeClass* weapon);

// The 16-bit direction from `to` towards `from`; inlined at its call sites.
static inline DirStruct DirectionTo(const CoordStruct& to, const CoordStruct& from)
{
    int bx = to.X;
    int ax = from.X;
    DirStruct d;
    d.Raw = (short)((FUN_004CAE30((double)to.Y - from.Y, (double)ax - bx) - DAT_007E2820) * DAT_007E2818);
    return d;
}

// A squared difference as a double (inline in retail: the integer is converted and multiplied by itself).
inline double BASquare(int v)
{
    return (double)v * v;
}

// The straight-line distance between two coordinates; inlined at its call sites.
static inline int Distance(const CoordStruct& b, const CoordStruct& a)
{
    return (int)FUN_004CAC40(BASquare(b.X - a.X) + BASquare(b.Y - a.Y) + BASquare(b.Z - a.Z));
}

#include <new.h>
#include "house_building/building_b_views.h"
#include "../_layout/building_class.h"
#include "../_layout/cell_class.h"

// The cell behind an abstract pointer, or null when it is something else (WhatAmI 0xB).
static inline CellClass* AsCell(AbstractClass* object)
{
    if (object == 0)
        return 0;
    return object->vf_11() == 0xB ? (CellClass*)object : 0;
}

// The local list of cleared objects: a DynamicVectorClass with a growth step of ten.
class BuildingBClearedList : public BuildingBVector<BuildingBObjectView>
{
public:
    BuildingBClearedList() : BuildingBVector<BuildingBObjectView>(0, 0)
    {
        CapacityIncrement = 10;
        Count = 0;
    }
};

// GLOBAL: GAMEMD 0x7E96A0 - CLSID of BuildingClass (16 bytes read from the image).
extern "C" const CLSID CLSID_Building =
    { 0x0E272DC6, 0x9C0F, 0x11D1, { 0xB7, 0x09, 0x00, 0xA0, 0x24, 0xDD, 0xAF, 0xD1 } };

#include "../_layout/techno_class.h"

// CellStruct — 2D short cell coordinate (sizeof = 4). Self-guarded for reuse.
#include "../_layout/cell.h"
GG_STATIC_ASSERT(sizeof(CellStruct) == 4);

#include "../_layout/global_0089c818.h"

#include "../core/vector_class_operations.h"
class FoggedObjectClass;

// VTABLE: GAMEMD 0x7E4514 -- VectorClass<FoggedObjectClass*>.
template class VectorClass<FoggedObjectClass*>;
typedef VectorClass<FoggedObjectClass*> GgFoggedObjectClassVectorClass;
GG_STATIC_ASSERT(offsetof(GgFoggedObjectClassVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgFoggedObjectClassVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgFoggedObjectClassVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgFoggedObjectClassVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7E44F4 -- DynamicVectorClass<FoggedObjectClass*>.
template class DynamicVectorClass<FoggedObjectClass*>;
typedef DynamicVectorClass<FoggedObjectClass*> GgFoggedObjectClassDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgFoggedObjectClassDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgFoggedObjectClassDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgFoggedObjectClassDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgFoggedObjectClassDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgFoggedObjectClassDynamicVectorClass, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgFoggedObjectClassDynamicVectorClass, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(FoggedObjectClass*) == 4);

#include "../core/vector_class_operations.h"
class InfantryClass;

// VTABLE: GAMEMD 0x7E43E8 -- VectorClass<InfantryClass*>.
template class VectorClass<InfantryClass*>;
typedef VectorClass<InfantryClass*> GgInfantryClassVectorClass;
GG_STATIC_ASSERT(offsetof(GgInfantryClassVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgInfantryClassVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgInfantryClassVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgInfantryClassVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7E43C8 -- DynamicVectorClass<InfantryClass*>.
template class DynamicVectorClass<InfantryClass*>;
typedef DynamicVectorClass<InfantryClass*> GgInfantryClassDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgInfantryClassDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgInfantryClassDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgInfantryClassDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgInfantryClassDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgInfantryClassDynamicVectorClass, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgInfantryClassDynamicVectorClass, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(InfantryClass*) == 4);

#include <new.h>
#include "house_building/building_b_views.h"
#include "../_layout/building_class.h"

#include <new.h>
#include "house_building/building_b_views.h"
#include "../_layout/building_class.h"
#include "../_layout/house_class.h"

#include "../core/vector_class_operations.h"

class Reestablish;

template class DynamicVectorClass<Reestablish*>;

GG_STATIC_ASSERT(sizeof(Reestablish*) == 4);
GG_STATIC_ASSERT(sizeof(VectorClass<Reestablish* >) == 0x10);
GG_STATIC_ASSERT(sizeof(DynamicVectorClass<Reestablish* >) == 0x18);

#include "house_building/building_a_views.h"
#include "../_layout/building_class.h"
#include "../_layout/house_class.h"
#include "../_layout/house_type_class.h"
#include "../combat/weapon_type_class.h"
#include "../_layout/factory_class.h"
#include "../_layout/rules_class.h"
#include "../_layout/infantry_class.h"
#include "../_layout/anim_class.h"
#include "../_layout/obj_004a1d30.h"
#include "../core/mission_class_methods.h"

#include <stdlib.h>
#include "house_building/building_a_views.h"

// One refund of a production slot: the production object is looked up, the building is flagged while the
// owner is told, then the flag is restored (inline in retail, once per slot).
inline void BAReleaseSlot(BuildingClass* b, FactoryClass* factory)
{
    BAProdView* prod = FUN_004CA160(factory);
    bool saved = b->InLimbo;
    b->InLimbo = 1;
    if (prod) {
        if (!prod->vf_33()->vf_37(1, 0, 0, b->Owner)) {
            b->Owner->FUN_004FAA10(b->Type->Factory, prod->vf_33()->vf_16(0, 0));
        }
    }
    b->InLimbo = saved;
}

#include <new.h>
#include "house_building/building_b_views.h"
#include "../_layout/building_class.h"
#include "../_layout/cell_class.h"

// The cell containing a world coordinate (leptons / 256, per axis).
static inline CellStruct CellOfCoord(const CoordStruct& c)
{
    CellStruct r;
    r.X = c.X / 256;
    r.Y = c.Y / 256;
    return r;
}

#include "../core/buffer_holder_dtor_methods.h"

#include "../core/buffer_release_methods.h"

#include "../core/com_holder_query_methods.h"

#include "../core/guarded_forward_methods.h"

#include "../core/small_misc25_methods.h"

//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.

#include <stddef.h>
#include "../_rt/gg_static_assert.h"


void __cdecl FUN_004503E0();
void __cdecl FUN_00456970();


#include "building_class_enable_methods.h"

#include "../ai/refresh_all_sides_methods.h"

#include "../ai/side_slot_dispatch_methods.h"

#include "../ai/unload_all_methods.h"

#include "../combat/building_class_fire_laser_methods.h"

#include "../combat/building_class_garrison_owner_methods.h"

#include "../combat/building_class_go_online_methods.h"

#include "../combat/building_class_impassable_rows_methods.h"

#include "../combat/building_class_occupy_methods.h"

#include "../combat/building_class_offline_methods.h"

#include "../combat/building_class_radial_methods.h"

#include "../combat/building_class_traversable_methods.h"

#include "../combat/building_class_unload_bunker_methods.h"

#include "../combat/building_class_voxel_barrel_methods.h"

// GLOBAL: GAMEMD 0x7E4408
// One 32nd of a turn, negated: the double at 0x7E4408.
static const double VoxelBarrelStep_00458810 = -0.19634954084936207;

// A 16-bit binary angle rounded to one of 32 facings, then re-centred on
// facing 8: `(raw >> 10) + 1 >> 1 & 0x1F` picks the nearest 32nd of a turn.
// The helper has to take the DirStruct rather than its raw word: reading
// `->Raw` at the call site instead costs 26 points (see the note below).
static inline int BarrelFacingIndex_00458810(const DirStruct_00458810* dir)
{
    return (int)((((dir->Raw >> 10) + 1) >> 1) & 0x1F) - 8;
}

#include "../core/small_misc12_methods.h"

#include "../core/small_misc15_methods.h"

#include "../core/small_misc19_methods.h"

#include "../core/small_misc39_methods.h"

#include "../core/small_misc3_methods.h"

#include "../core/small_misc41_methods.h"

#include "../core/small_misc4_methods.h"

#include "../core/small_misc53_methods.h"

#include "../core/small_misc8_methods.h"

#include "building_class_power_methods.h"

#include "building_class_power_output_methods.h"

// The sum of two coordinates.
static inline CoordStruct CoordSum(const CoordStruct& a, const CoordStruct& b)
{
    CoordStruct r;
    r.X = a.X + b.X;
    r.Y = a.Y + b.Y;
    r.Z = a.Z + b.Z;
    return r;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// Component addition inlined by the retail body at 0x4500CB..0x4500E0.
static inline CoordStruct operator+(const CoordStruct& a, const CoordStruct& b)
{
    CoordStruct result;
    result.X = a.X + b.X;
    result.Y = a.Y + b.Y;
    result.Z = a.Z + b.Z;
    return result;
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x818164
extern const char CivilianSideName_00458200[] = "Civilian";
// GLOBAL: GAMEMD 0x8190C8
extern const char EvaBuildingOnLine_00452260[] = "EVA_BuildingOnLine";
// GLOBAL: GAMEMD 0x819108
extern const char EvaBuildingOffLine[] = "EVA_BuildingOffLine";
// GLOBAL: GAMEMD 0x81926C
extern const char EvaStructureAbandoned_00458200[] = "EVA_StructureAbandoned";
// GLOBAL: GAMEMD 0xA80228
HouseVector_00458200 HouseArray_00458200;
// GLOBAL: GAMEMD 0x89C848
CoordStruct DAT_0089C848;
// GLOBAL: GAMEMD 0xB73550
int BuildingBGlobal_00B73550;
// END defined globals

#include "../_layout/building_class.h"
#include "../_layout/building_type_class_layout.h"
#include "../_layout/house_class.h"
#include "../_layout/house_type_class.h"
#include "../core/rules_class.h"

extern "C" int __cdecl _stricmp(const char* a, const char* b);

// GLOBAL: GAMEMD 0x7E1718
extern const double DAT_007E1718;

#include "building_class.h"

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0xA83CBC
SWChainNode** g_SWArray;
// END defined globals

#include <windows.h>
#include "../_layout/house_class.h"
#include "../_layout/player_ptr_00a83d4c.h"
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// ---------------------------------------------------------------------------
// 0x402C40 / 0x4031D0: walk of a queue that hangs off a global holder.
struct QNode_00402C40
{
    char Pad_00[0x18];
    int  Value;
    QNode_00402C40* FUN_004073E0();
};
GG_STATIC_ASSERT(offsetof(QNode_00402C40, Value) == 0x18);

struct Queue_00402C40
{
    int Pad_00[3];
    QNode_00402C40* FUN_004073C0();
};
GG_STATIC_ASSERT(sizeof(Queue_00402C40) == 0xC);

struct QHolder_00402C40
{
    Queue_00402C40 First;   // +0x00
    Queue_00402C40 Second;  // +0x0C
};
extern QHolder_00402C40* DAT_00815E98;

struct QCursor_004031D0
{
    QNode_00402C40* Cur;
    // FUNCTION: GAMEMD 0x4031D0
    void Begin();
};

// ---------------------------------------------------------------------------
// 0x417CA0: four-argument forwarder.
struct Fwd_00417CA0
{
    int FUN_006FFBE0(int a, int b, int c, int d);
    // FUNCTION: GAMEMD 0x417CA0
    int Forward(int a, int b, int c, int d);
};

// ---------------------------------------------------------------------------
// 0x422C70: refuse when a +0x184 pointer is set, otherwise forward to the base routine.
struct Base_00422C70
{
    bool FUN_005F4B10(int a, int b, int c);
};
struct Obj_00422C70 : Base_00422C70
{
    char Pad_01[0x184 - 1];
    void* Blocker;  // +0x184
    // FUNCTION: GAMEMD 0x422C70
    bool Try(int a, int b, int c);
};
GG_STATIC_ASSERT(offsetof(Obj_00422C70, Blocker) == 0x184);

// ---------------------------------------------------------------------------
// 0x43A5D0: fold the object's state and an elapsed-frame delta into a CRC view.
struct Crc_0043A5D0
{
    void FUN_004A1D50(int v);
};
struct CrcOwner_0043A5D0
{
    char Pad_00[0x30];
    int  Stamp;  // +0x30
    void FUN_00410410(Crc_0043A5D0* crc);
    // FUNCTION: GAMEMD 0x43A5D0
    void Crc(Crc_0043A5D0* crc);
};
extern int DAT_00A8ED84;

// ---------------------------------------------------------------------------
// 0x453370: reset a field when the house flag is set and the global is clear.
struct Owner_00453370
{
    char Pad_00[0x16BE];
    char Flag;  // +0x16BE
};
struct Obj_00453370
{
    char Pad_00[0x520];
    Owner_00453370* Owner;  // +0x520
    char Pad_524[0x618 - 0x524];
    int  Field618;          // +0x618
    // FUNCTION: GAMEMD 0x453370
    void ClearIfOwnerFlag();
};
GG_STATIC_ASSERT(offsetof(Obj_00453370, Field618) == 0x618);
extern int DAT_00A8E7AC;

// ---------------------------------------------------------------------------
// 0x4790B0: store a clamped mode value.
extern char DAT_0089E3A0;
extern int  DAT_0081C1D0;

// ---------------------------------------------------------------------------
// 0x47A6B0: open the device named by DAT_0081C5AC delete-on-close.
extern char DAT_0081C5AC[];

// ---------------------------------------------------------------------------
// 0x47B130: close the search handle if open.
extern HANDLE DAT_0081C8EC;

// ---------------------------------------------------------------------------
// 0x488480: byte at +4 of the list entry, or 0.
struct Entry_00488480
{
    char Pad_00[4];
    char Flag;  // +4
};
struct ListBase_00488480
{
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void Changed();     // slot 18, +0x48
    Entry_00488480* FUN_00557AC0(int index);
};
struct List_00488480 : ListBase_00488480
{
    // FUNCTION: GAMEMD 0x488450
    void SetFlag(int index, char value);
    // FUNCTION: GAMEMD 0x488480
    char FlagAt(int index);
};

// ---------------------------------------------------------------------------
// 0x48C600: elapsed time accumulated across a pause.
struct Timer_0088733C
{
    int FUN_006C8C40();
};
extern int DAT_00887338;
extern Timer_0088733C DAT_0088733C;
extern int DAT_00887340;

// ---------------------------------------------------------------------------
// 0x5278F0: forward two mapped keys to the reader.
struct Reader_005278F0
{
    int FUN_005276D0(int a, int b, int c);
    // FUNCTION: GAMEMD 0x5278F0
    int Read(int a, int b, int c);
};
int __fastcall FUN_007B5440(int v);

// ---------------------------------------------------------------------------
// 0x53D550: delete and clear every object in a global table.
struct Deletable_0053D550
{
    virtual ~Deletable_0053D550();
};
extern Deletable_0053D550* DAT_00A9FFC8[80];

// ---------------------------------------------------------------------------
// 0x53EC40 / 0x53EC70: key state table.
extern int   DAT_00AA0444;
extern short DAT_00AA0168[256];

// ===========================================================================
// 0x4016B0: copy a descriptor's fields into one 0x24-byte table row.
struct Row_004016B0
{
    char Pad_00[0x18];
    int  Value;     // +0x18
    int  Flags;     // +0x1C
    char Pad_20[4];
};
GG_STATIC_ASSERT(sizeof(Row_004016B0) == 0x24);
struct RowTable_004016B0
{
    Row_004016B0* Rows;
};
struct RowSrc_004016B0
{
    char Pad_00[8];
    int  Value;     // +0x08
    int  ModeA;     // +0x0C
    int  ModeB;     // +0x10
};

// ---------------------------------------------------------------------------
// 0x41B5E0: a flag that holds for most modes.
struct Obj_0041B5E0
{
    char Pad_00[0xAC];
    int  Mode;      // +0xAC
    char Pad_B0[0x6D2 - 0xB0];
    char Flag6D2;   // +0x6D2
    char Pad_6D3;
    char Flag6D4;   // +0x6D4
    // FUNCTION: GAMEMD 0x41B5E0
    bool Test();
};
GG_STATIC_ASSERT(offsetof(Obj_0041B5E0, Flag6D4) == 0x6D4);

// ---------------------------------------------------------------------------
// 0x41B610 / 0x41B660: CRC contribution and reference detach.
struct CrcSink_0041B610
{
    void FUN_004A1CA0(bool v);
    void FUN_004A1D50(int v);
};
struct CrcBase_0041B610
{
    void FUN_004DBAD0(CrcSink_0041B610* crc);
    void FUN_004D9960(void* target, bool all);
};
struct Obj_0041B610 : CrcBase_0041B610
{
    char  Pad_01[0x6C4 - 1];
    void* Ref6C4;           // +0x6C4
    char  Pad_6C8;
    bool  Flag6C9;          // +0x6C9
    char  Pad_6CA[2];
    void* Ref6CC;           // +0x6CC
    bool  Flag6D0;          // +0x6D0
    bool  Flag6D1;          // +0x6D1
    char  Pad_6D2;
    signed char Val6D3;     // +0x6D3
    // FUNCTION: GAMEMD 0x41B610
    void Crc(CrcSink_0041B610* crc);
    // FUNCTION: GAMEMD 0x41B660
    void Detach(void* target, bool all);
};
GG_STATIC_ASSERT(offsetof(Obj_0041B610, Ref6C4) == 0x6C4);
GG_STATIC_ASSERT(offsetof(Obj_0041B610, Ref6CC) == 0x6CC);
GG_STATIC_ASSERT(offsetof(Obj_0041B610, Val6D3) == 0x6D3);

// ---------------------------------------------------------------------------
// 0x42E0B0 / 0x42E110: a seven-value record with a double-valued rate limiter.
struct Limiter_0042E0B0
{
    int    F0, F4, F8, FC, F10, F14, F18;
    int    Pad_1C;
    double Last;        // +0x20
    double Prev;        // +0x28
    bool   Armed;       // +0x30
    char   Pad_31[3];
    void FUN_0042E1C0();
    // FUNCTION: GAMEMD 0x42E110
    bool Update(double now);
};
GG_STATIC_ASSERT(offsetof(Limiter_0042E0B0, Prev) == 0x28);
GG_STATIC_ASSERT(offsetof(Limiter_0042E0B0, Armed) == 0x30);

// ---------------------------------------------------------------------------
// 0x43C2A0: release each of eight owned objects through their release slot.
struct Owned_0043C2A0
{
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void v23();
    virtual void v24();
    virtual void v25();
    virtual void v26();
    virtual void v27();
    virtual void v28();
    virtual void v29();
    virtual void v30();
    virtual void v31();
    virtual void v32();
    virtual void v33();
    virtual void v34();
    virtual void v35();
    virtual void v36();
    virtual void v37();
    virtual void v38();
    virtual void v39();
    virtual void v40();
    virtual void v41();
    virtual void v42();
    virtual void v43();
    virtual void v44();
    virtual void v45();
    virtual void v46();
    virtual void v47();
    virtual void v48();
    virtual void v49();
    virtual void v50();
    virtual void v51();
    virtual void v52();
    virtual void v53();
    virtual void v54();
    virtual void v55();
    virtual void v56();
    virtual void v57();
    virtual void v58();
    virtual void v59();
    virtual void v60();
    virtual void v61();
    virtual void Release();     // slot 62, +0xF8
};
struct Holder_0043C2A0
{
    char Pad_00[0x5C8];
    Owned_0043C2A0* Items[8];   // +0x5C8
    // FUNCTION: GAMEMD 0x43C2A0
    void ReleaseAll();
};
GG_STATIC_ASSERT(offsetof(Holder_0043C2A0, Items) == 0x5C8);

// ---------------------------------------------------------------------------
// 0x45E8B0: store three values in the indexed 12-byte slot.
struct Slot_0045E8B0
{
    int A;
    int B;
    int C;
};
struct Slots_0045E8B0
{
    char Pad_00[0xF04];
    Slot_0045E8B0 Items[1];   // +0xF04
    // FUNCTION: GAMEMD 0x45E8B0
    void Set(int index, int a, int b, int c);
};
GG_STATIC_ASSERT(offsetof(Slots_0045E8B0, Items) == 0xF04);

// ---------------------------------------------------------------------------
// 0x46D430: clear the flag byte of every slot whose object reports true.
struct Probe_0046D430
{
    bool FUN_005E93F0();
};
extern Probe_0046D430* DAT_00A8DA90[8];
extern char DAT_0089E000[8];

// ---------------------------------------------------------------------------
// 0x474870: scale by 100/256 and forward.
struct Fwd_00474870
{
    int FUN_005275C0(int a, int b, int c, int d);
    // FUNCTION: GAMEMD 0x474870
    int Percent(int a, int b, int c);
};

// ---------------------------------------------------------------------------
// 0x476F70: forward with the text of a looked-up entry, or an empty default.
extern char DAT_00817474[];
struct Text_00476F70
{
    char Pad_00[0x24];
    char Text[1];   // +0x24
};
struct Lookup_00476F70
{
    Text_00476F70* FUN_006E7330();
};
struct Sink_00476F70
{
    void FUN_00528660(int a, int b, const char* text);
    // FUNCTION: GAMEMD 0x476F70
    void Forward(int a, int b, Lookup_00476F70* l);
};

// ---------------------------------------------------------------------------
// 0x48DF30: index of a name in the global name table, or -1.
extern char** DAT_00ABF394;
extern int    DAT_00ABF3A0;
int __cdecl FUN_007C8D20(const char* a, const char* b);

// ---------------------------------------------------------------------------
// 0x49B720: delete every owned item, then the array itself.
struct Pool_0049B720
{
    char Pad_00[0x3C];
    char** Items;   // +0x3C
    int    Count;   // +0x40
    // FUNCTION: GAMEMD 0x49B720
    void FreeAll();
};
GG_STATIC_ASSERT(offsetof(Pool_0049B720, Count) == 0x40);

// ---------------------------------------------------------------------------
// 0x44EF80: resolve an id through the object's slot 34, then ask the result.
struct Resolved_0044EF80
{
    int FUN_0045EE70();
};
struct Target_0044EF80
{
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void v23();
    virtual void v24();
    virtual void v25();
    virtual void v26();
    virtual void v27();
    virtual void v28();
    virtual void v29();
    virtual void v30();
    virtual void v31();
    virtual void v32();
    virtual void v33();
    virtual Resolved_0044EF80* Resolve(int a, int b);   // slot 34, +0x88
};
struct Owner_0044EF80
{
    char Pad_00[0x21C];
    int  Context;   // +0x21C
    // FUNCTION: GAMEMD 0x44EF80
    int Lookup(Target_0044EF80* t, int a);
};
GG_STATIC_ASSERT(offsetof(Owner_0044EF80, Context) == 0x21C);

// ---------------------------------------------------------------------------
// 0x454D70: poke every linked node whose type is one of three values.
struct Node_00454D70
{
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual int Type();         // slot 11, +0x2C
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void v23();
    virtual void v24();
    virtual void v25();
    virtual void v26();
    virtual void v27();
    virtual void v28();
    virtual void v29();
    virtual void v30();
    virtual void v31();
    virtual void v32();
    virtual void v33();
    virtual void v34();
    virtual void v35();
    virtual void v36();
    virtual void v37();
    virtual void v38();
    virtual void v39();
    virtual void v40();
    virtual void v41();
    virtual void v42();
    virtual void v43();
    virtual void v44();
    virtual void v45();
    virtual void v46();
    virtual void v47();
    virtual void v48();
    virtual void v49();
    virtual void v50();
    virtual void v51();
    virtual void v52();
    virtual void v53();
    virtual void v54();
    virtual void v55();
    virtual void v56();
    virtual void v57();
    virtual void v58();
    virtual void v59();
    virtual void v60();
    virtual void v61();
    virtual void v62();
    virtual void v63();
    virtual void v64();
    virtual void v65();
    virtual void v66();
    virtual void v67();
    virtual void v68();
    virtual void v69();
    virtual void v70();
    virtual void v71();
    virtual void v72();
    virtual void v73();
    virtual void v74();
    virtual void v75();
    virtual void v76();
    virtual void v77();
    virtual void v78();
    virtual void v79();
    virtual void v80();
    virtual void v81();
    virtual void v82();
    virtual void v83();
    virtual void v84();
    virtual void v85();
    virtual void v86();
    virtual void v87();
    virtual void v88();
    virtual void v89();
    virtual void v90();
    virtual void v91();
    virtual void v92();
    virtual void v93();
    virtual void v94();
    virtual void v95();
    virtual void v96();
    virtual void v97();
    virtual void v98();
    virtual void v99();
    virtual void v100();
    virtual void v101();
    virtual void v102();
    virtual void v103();
    virtual void v104();
    virtual void v105();
    virtual void v106();
    virtual void v107();
    virtual void v108();
    virtual void v109();
    virtual void v110();
    virtual void v111();
    virtual void v112();
    virtual void v113();
    virtual void v114();
    virtual void v115();
    virtual void v116();
    virtual void v117();
    virtual void v118();
    virtual void v119();
    virtual void v120();
    virtual void v121();
    virtual void v122();
    virtual void v123();
    virtual void v124();
    virtual void v125();
    virtual void v126();
    virtual void v127();
    virtual void v128();
    virtual void v129();
    virtual void v130();
    virtual void v131();
    virtual void v132();
    virtual void v133();
    virtual void v134();
    virtual void v135();
    virtual void v136();
    virtual void v137();
    virtual void v138();
    virtual void v139();
    virtual void v140();
    virtual void v141();
    virtual void v142();
    virtual void v143();
    virtual void v144();
    virtual void v145();
    virtual void v146();
    virtual void v147();
    virtual void v148();
    virtual void v149();
    virtual void v150();
    virtual void v151();
    virtual void v152();
    virtual void v153();
    virtual void v154();
    virtual void v155();
    virtual void v156();
    virtual void v157();
    virtual void v158();
    virtual void v159();
    virtual void v160();
    virtual void v161();
    virtual void v162();
    virtual void v163();
    virtual void v164();
    virtual void v165();
    virtual void v166();
    virtual void v167();
    virtual void v168();
    virtual void v169();
    virtual void v170();
    virtual void v171();
    virtual void v172();
    virtual void v173();
    virtual void v174();
    virtual void v175();
    virtual void v176();
    virtual void v177();
    virtual void v178();
    virtual void v179();
    virtual void v180();
    virtual void v181();
    virtual void v182();
    virtual void v183();
    virtual void v184();
    virtual void v185();
    virtual void v186();
    virtual void v187();
    virtual void v188();
    virtual void v189();
    virtual void v190();
    virtual void v191();
    virtual void v192();
    virtual void v193();
    virtual void v194();
    virtual void v195();
    virtual void v196();
    virtual void v197();
    virtual void v198();
    virtual void v199();
    virtual void v200();
    virtual void v201();
    virtual void v202();
    virtual void v203();
    virtual void v204();
    virtual void v205();
    virtual void v206();
    virtual void v207();
    virtual void v208();
    virtual void v209();
    virtual void v210();
    virtual void v211();
    virtual void v212();
    virtual void v213();
    virtual void v214();
    virtual void v215();
    virtual void v216();
    virtual void v217();
    virtual void v218();
    virtual void v219();
    virtual void v220();
    virtual void v221();
    virtual void v222();
    virtual void v223();
    virtual void v224();
    virtual void v225();
    virtual void v226();
    virtual void v227();
    virtual void v228();
    virtual void v229();
    virtual void v230();
    virtual void v231();
    virtual void v232();
    virtual void v233();
    virtual void v234();
    virtual void v235();
    virtual void v236();
    virtual void v237();
    virtual void v238();
    virtual void v239();
    virtual void v240();
    virtual void v241();
    virtual void v242();
    virtual void v243();
    virtual void v244();
    virtual void v245();
    virtual void v246();
    virtual void v247();
    virtual void v248();
    virtual void v249();
    virtual void v250();
    virtual void v251();
    virtual void v252();
    virtual void v253();
    virtual void v254();
    virtual void v255();
    virtual void v256();
    virtual void v257();
    virtual void v258();
    virtual void v259();
    virtual void v260();
    virtual void v261();
    virtual void v262();
    virtual void v263();
    virtual void Poke();        // slot 264, +0x420
    char Pad_04[0x30 - 4];
    Node_00454D70* Next;        // +0x30
};
GG_STATIC_ASSERT(offsetof(Node_00454D70, Next) == 0x30);
struct Chain_00454D70
{
    char Pad_00[0xE4];
    Node_00454D70* Head;        // +0xE4
    // FUNCTION: GAMEMD 0x454D70
    void PokeAll();
};
GG_STATIC_ASSERT(offsetof(Chain_00454D70, Head) == 0xE4);

// ---------------------------------------------------------------------------
// 0x486800: bit-mask test.
struct Mask_00486800
{
    char  Pad_00[0x78];
    int   Mask;         // +0x78
    short Counts[1];    // +0x7C
    // FUNCTION: GAMEMD 0x486800
    bool Allowed(int bit);
};
GG_STATIC_ASSERT(offsetof(Mask_00486800, Counts) == 0x7C);

// ---------------------------------------------------------------------------
// 0x49D070: a slot table's checked fetch.
struct Table_0049B610
{
    char  Used;         // +0x00
    char  Pad_01[0x13];
    int   F14;
    int   F18;
    char  F1C;
    char  Pad_1D[0x13];
    int   F30;
    int   F34;
    int   F38;
    void** Items;       // +0x3C
    int   Count;        // +0x40
    int   F44;
    int   F48, F4C, F50, F54, F58, F5C, F60, F64, F68;
    char  Enabled;      // +0x6C
    // FUNCTION: GAMEMD 0x49D070
    bool Fetch(void** out, int index);
};
GG_STATIC_ASSERT(offsetof(Table_0049B610, Count) == 0x40);
GG_STATIC_ASSERT(offsetof(Table_0049B610, Enabled) == 0x6C);

// ---------------------------------------------------------------------------
// 0x41A570 / 0x41C1E0: copy out the value held by the +0x3A0 sub-object.
struct Val_0041A570
{
    int V;
};
struct Slot_0041A570
{
    Val_0041A570* FUN_004C93D0(Val_0041A570* out);
};
struct Obj_0041A570
{
    char Pad_00[0x3A0];
    Slot_0041A570 Slot;     // +0x3A0
    // FUNCTION: GAMEMD 0x41A570
    Val_0041A570 Get_0041A570();
};
GG_STATIC_ASSERT(offsetof(Obj_0041A570, Slot) == 0x3A0);

struct Val_0041C1E0
{
    int V;
};
struct Slot_0041C1E0
{
    Val_0041C1E0* FUN_004C93D0(Val_0041C1E0* out);
};
struct Obj_0041C1E0
{
    char Pad_00[0x3A0];
    Slot_0041C1E0 Slot;     // +0x3A0
    // FUNCTION: GAMEMD 0x41C1E0
    Val_0041C1E0 Get_0041C1E0();
};
GG_STATIC_ASSERT(offsetof(Obj_0041C1E0, Slot) == 0x3A0);

// ---------------------------------------------------------------------------
// 0x430620: clear the 256-byte name at +0x0E and copy in up to 127 characters.
char* __cdecl FUN_007CA422(char* dst, const char* src, int n);
struct Named_00430620
{
    char Pad_00[0x0E];
    char Name[0x100];   // +0x0E
    // FUNCTION: GAMEMD 0x430620
    void SetName(const char* s);
};
GG_STATIC_ASSERT(offsetof(Named_00430620, Name) == 0x0E);

// ---------------------------------------------------------------------------
// 0x487C10: per-index flag, unless a type-6 node is linked while the global is set.
struct Row_00487C10
{
    char Flag;      // +0x00
    char Pad_01[0x23];
};
GG_STATIC_ASSERT(sizeof(Row_00487C10) == 0x24);
extern char DAT_00A8E9A0;
extern Row_00487C10 DAT_0089EA60[];
struct Owner_00487C10
{
    char Pad_00[0xE4];
    Node_00454D70* Head;    // +0xE4
    char Pad_E8[4];
    int  Index;             // +0xEC
    char Pad_F0[0x11C - 0xF0];
    char Blocked;           // +0x11C
    // FUNCTION: GAMEMD 0x487C10
    char RowFlag();
};
GG_STATIC_ASSERT(offsetof(Owner_00487C10, Blocked) == 0x11C);

// ---------------------------------------------------------------------------
// 0x42CEB0: does list `index` already hold the ordered pair (low, high)?
struct PairList_0042CEB0
{
    int  Pad_00;
    unsigned* Items;    // +0x04
    int  Pad_08[2];
    int  Count;         // +0x10
    int  Pad_14;
};
GG_STATIC_ASSERT(sizeof(PairList_0042CEB0) == 0x18);
struct Pairs_0042CEB0
{
    char Pad_00[0x74];
    PairList_0042CEB0 Lists[1];     // +0x74
    // FUNCTION: GAMEMD 0x42CEB0
    bool Has(unsigned short a, unsigned short b, int index);
};
GG_STATIC_ASSERT(offsetof(Pairs_0042CEB0, Lists) == 0x74);

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x88733C
extern Timer_0088733C DAT_0088733C;
// GLOBAL: GAMEMD 0x887340
extern int DAT_00887340;
// GLOBAL: GAMEMD 0x89E000
extern char DAT_0089E000[8];
// GLOBAL: GAMEMD 0x89E3A0
extern char DAT_0089E3A0;
// GLOBAL: GAMEMD 0xA8DA90
extern Probe_0046D430* DAT_00A8DA90[8];
// GLOBAL: GAMEMD 0xA9FFC8
extern Deletable_0053D550* DAT_00A9FFC8[80];
// GLOBAL: GAMEMD 0xAA0168
extern short DAT_00AA0168[256];
// GLOBAL: GAMEMD 0xAA0444
extern int DAT_00AA0444;
// GLOBAL: GAMEMD 0xABF3A0
extern int DAT_00ABF3A0;
// GLOBAL: GAMEMD 0x81C1D0
extern int DAT_0081C1D0;
// GLOBAL: GAMEMD 0x887338
extern int DAT_00887338;
// GLOBAL: GAMEMD 0xA8E9A0
extern char DAT_00A8E9A0;
// END defined globals

#include "building_class.h"

#include "../_layout/building_class.h"
#include "../_layout/anim_class.h"
#include "../_layout/anim_type_class.h"
#include "../_layout/cell_class.h"
#include "../core/abstract_class_distance3d_methods.h"

// GLOBAL: GAMEMD 0x7F4890 -- 32-entry table of animation frames per facing step.
extern int DAT_007F4890[32];

#include "../combat/building_class_clear_bunker_methods.h"

#include "../combat/building_class_disable_methods.h"

#include "../combat/building_class_occupant_anims_methods.h"

// Restart one animation slot with the artwork the building's current state
// calls for: the damaged name once health has fallen to the yellow threshold,
// otherwise the garrisoned name while somebody is inside, otherwise the plain
// one. Retail inlines this five times over, once per slot.
static inline void PlayNthAnim(BuildingClass* self, int slot, int effectDelay)
{
    if (self->Anims[slot] != 0) {
        int damaged = self->GetHealthPercentage()
                      <= RulesInstance->ConditionYellow;
        bool garrisoned = self->vf_258() > 0;

        const char* animName;
        if (damaged) {
            animName = self->Type->BuildingAnim[slot].Damaged;
        } else if (garrisoned) {
            animName = self->Type->BuildingAnim[slot].Garrisoned;
        } else {
            animName = self->Type->BuildingAnim[slot].Anim;
        }
        if (animName && *animName) {
            self->PlayAnim(animName, slot, damaged, garrisoned, effectDelay);
        }
    }
}

#include "../_layout/building_class.h"
#include "../_layout/map_0087f7e8.h"
#include "../core/vector_class.h"

#include "../ui/building_draw_methods.h"

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x43C2A0
void Holder_0043C2A0::ReleaseAll()
{
    for (int i = 0; i < 8; ++i)
    {
        if (Items[i])
        {
            Items[i]->Release();
            Items[i] = 0;
        }
    }
}

#include "../_layout/unit_class.h"
#include "../_layout/unit_type_class.h"
#include "../_layout/capture_manager_class.h"
#include "house_building/building_a2_fold.h"

// The length of the vector between two coordinates, as the original computed it inline (squared components
// summed in a double, square root, truncation).
static inline int BuildingDistance(const CoordStruct& a, const CoordStruct& b)
{
    int dx = a.X - b.X;
    int dy = a.Y - b.Y;
    return (int)FUN_004CAC40((double)dy * (double)dy + (double)(a.Z - b.Z) * (double)(a.Z - b.Z) + (double)dx * (double)dx);
}

// Moved from building_a2_radio.cpp (the BA2 parallel view family is retired); written against the canonical
// BuildingClass, TechnoClass, RadioClass, BuildingTypeClass and UnitTypeClass.
// PARTIAL: 21.3% (was 15.6% on the BA2 view). Remaining delta: retail reaches two shared return blocks (`return 10`
// from 13 jumps, `return 1` from 15) where ours repeats the 7-instruction epilogue at several single-condition
// sites; the 16A9 branch (`if (x == 1) return 10; return 1;`) is turned into neg/sbb arithmetic where retail keeps
// the branch; the frame is 0x5C where retail's is 0x40 (slot 18/42/110 results are copied from canonical
// by-value returns where retail reads them through the hidden-pointer result). Adjacent `return 10` guards joined
// with `||` (BalloonHover, HasPower) gained the most; splitting the 16A9 guard lost 9 points.
// FUNCTION: GAMEMD 0x43C2D0
// Slot 101, the radio message handler (BuildingClass::Receive_Message). The message numbers and the results
// (1 = accepted, 10 = refused) are kept numeric. The slot keeps the base signature: a1 is the sender
// (TechnoClass*), a3 points at the in/out object pointer.
int BuildingClass::vf_101(int a1, int message, int a3)
{
    TechnoClass* from = reinterpret_cast<TechnoClass*>(a1);
    AbstractClass** param = reinterpret_cast<AbstractClass**>(a3);

    switch (message) {
    case 0xF:
        FUN_006F4AB0(a1, message, a3);
        if (!Owner->FUN_004F9A90(from)) {
            return 0;
        }
        if (vf_97() == 0x12 || vf_97() == 0x13 || BState == 0
            || (!DAT_00A8E7AC && !HasFreeLinkFor(from) && !Type->bools_16A4[10] && !Type->bools_16A4[11])) {
            return 10;
        }
        if (from->vf_33()->MovementZone != 5) {
            if ((vf_33()->Naval && !from->vf_33()->Naval)
                || (!vf_33()->Naval && from->vf_33()->Naval)) {
                return 10;
            }
        }
        if (from->vf_33()->BalloonHover || !HasPower) {
            return 10;
        }
        if (Type->bools_16A4[10] || Type->bools_16A4[11]) {
            if ((from->vf_11() == 1 && !Type->bools_16A4[10]) || (from->vf_11() == 0xF && !Type->bools_16A4[11])) {
                return 10;
            }
            if (from->CaptureManager && static_cast<CaptureManagerClass*>(from->CaptureManager)->IsControllingSomething()) {
                return 10;
            }
            if (Passengers.NumPassengers + 1 <= Type->Passengers && from->vf_33()->Size <= Type->SizeLimit) {
                return 1;
            }
        }
        if (Type->bools_16A4[9]) {
            return 1;
        }
        if (Type->bools_16A4[7]) {
            if (!from->FUN_0070FB50() || vf_158(0x23, from) == 1) {
                return 10;
            }
            return 1;
        }
        if (Type->bools_16A4[5]) {
            if ((from->vf_11() != 1 && from->vf_11() != 2) || vf_158(0x23, from) == 1) {
                return 10;
            }
            return 1;
        }
        if ((Type->bools_16A4[30] || Type->bools_16A4[29]) && from->vf_11() == 0xF) {
            TechnoClass* other = !from ? 0 : (from->vf_11() == 0xF ? from : 0);
            if (other->CaptureManager && static_cast<CaptureManagerClass*>(other->CaptureManager)->IsControllingSomething()) {
                return 10;
            }
            if (other->IsMindControlled()) {
                return 10;
            }
            return Ammo ? 1 : 10;
        }
        if (Type->bools_16A4[39]) {
            return from->vf_rtti_3() == 2 ? 1 : 10;
        }
        if (Type->bools_16A4[15] && from->vf_11() == 1 && static_cast<UnitTypeClass*>(static_cast<UnitClass*>(from)->Type)->Harvester) {
            if (DAT_00A8E7AC || !Passengers.FirstPassenger) {
                return 1;
            }
        }
        if (Type->bools_16A4[24] && from->vf_11() == 1 && static_cast<UnitTypeClass*>(static_cast<UnitClass*>(from)->Type)->Weeder) {
            if (DAT_00A8E7AC || !Passengers.FirstPassenger) {
                return 1;
            }
        }
        return 0;
    case 0x15:
        if (vf_97() == 0x13) {
            return 10;
        }
        if (Type->bools_16A4[10] || Type->bools_16A4[11]) {
            return 1;
        }
        if (Type->bools_16A4[5] || Type->bools_16A4[6] || Type->bools_16A4[29] || Type->bools_16A4[30]) {
            IsReadyToCommence = 1;
            vf_122(0x14, 0);
            from->vf_122(0, 0);
            return 1;
        }
        if (Type->bools_16A4[7]) {
            IsReadyToCommence = 1;
            vf_122(0x14, 0);
            return 1;
        }
        if (Type->bools_16A4[15]) {
            from->vf_122(0x10, 0);
            return 1;
        }
        break;
    case 0xE:
        FUN_006F4AB0(a1, message, a3);
        if (!HasPower) {
            return 10;
        }
        if (Type->bools_16A4[5] && ContainsLink(from) && vf_158(0x22, from) == 10) {
            return 10;
        }
        if (Type->bools_16A4[7] && ContainsLink(from) && !from->FUN_0070FB50()) {
            return 10;
        }
        if (!Type->bools_16A4[29] && !Type->bools_16A4[30]) {
            if (!ContainsLink(from) && HasFreeLinkFor(from)) {
                vf_158(2, from);
                ContainsLink(from);
            }
            bool needsRetry = false;
            if (ContainsLink(from) && (Type->bools_16A4[15] || Type->bools_16A4[24])) {
                FootClass* other = !from ? 0 : (from->Flags.IsFoot ? static_cast<FootClass*>(from) : 0);
                CellClass* cell = DAT_0087F7E8.FUN_00565730(vf_42(other));
                if (other->Destination && cell != other->Destination) {
                    needsRetry = true;
                }
            }
            if (FUN_0065AD30(0) && (Type->bools_16A4[5] || Type->bools_16A4[7])) {
                CoordStruct there = FUN_0065AD30(0)->vf_18();
                CoordStruct here = vf_18();
                if (BuildingDistance(here, there) > 0x80) {
                    needsRetry = true;
                }
            }
            if (vf_158(0x13, from) != 1 && !needsRetry) {
                return 1;
            }
            *param = this;
            if (Type->bools_16A4[15] || Type->bools_16A4[24]) {
                Cell here = vf_110();
                Cell target = Cell(here.X + 3, here.Y + 1);
                *param = DAT_0087F7E8.FUN_005657A0(&target);
                if (vf_159(0x12, param, from) != 0x14) {
                    return 1;
                }
                vf_158(0x18, from);
                if (vf_158(0x16, from) == 1) {
                    return 1;
                }
                from->vf_93(DAT_0089C848, 1, 1);
                return 1;
            }
            if (!Type->bools_16A4[39]) {
                return 1;
            }
            *param = this;
            if (vf_159(0x12, param, from) != 0x14) {
                return 1;
            }
            vf_157(0x18);
            return 1;
        }
        if (HasFreeLinkFor(from)) {
            CoordStruct where = Location;
            *param = DAT_0087F7E8.FUN_00565730(&where);
            vf_159(0x12, param, from);
            return 1;
        }
        {
            for (int i = 0; i < RadioLinks.Capacity; i++) {
                TechnoClass* o = FUN_0065AD30(i);
                if (vf_158(0x22, o) == 10) {
                    vf_158(0x17, o);
                }
            }
        }
        if (HasFreeLinkFor(from)) {
            return 1;
        }
        return 10;
    case 0x10:
        if (Passengers.FirstPassenger != 0 || !HasFreeLinkFor(from) || InLimbo || Owner != from->vf_15()) {
            return 10;
        }
        if (Type->bools_16A4[23] || Type->bools_16A4[5] || Type->bools_16A4[24]) {
            return 1;
        }
        return 10;
    case 0xB:
        vf_122(0x14, 0);
        FUN_006F4AB0(a1, message, a3);
        return 1;
    case 0xC:
        if (vf_97() != 0x13) {
            vf_122(5, 0);
            if (Type->bools_16A4[21]) {
                DestroyNthAnim(7);
                DestroyNthAnim(0x12);
                double ratio = FUN_005F5C60();
                bool low = ratio <= Rules->ConditionYellow;
                char* name = low ? Type->BuildingAnim[8].Damaged : Type->BuildingAnim[8].Anim;
                if (name && *name) {
                    PlayAnim(name, 8, low, 0, 0);
                }
            }
        }
        FUN_006F4AB0(a1, message, a3);
        return 1;
    case 3:
        FUN_00447780(1);
        FUN_006F4AB0(a1, message, a3);
        return 1;
    case 8:
        if (Type->bools_16A4[5] || Type->bools_16A4[7]) {
            CoordStruct there = from->vf_18();
            CoordStruct here = vf_18();
            if (BuildingDistance(here, there) < 0x180) {
                return 1;
            }
        }
        FUN_006F4AB0(a1, message, a3);
        if (!Type->bools_16A4[25] && !Type->bools_16A4[5] && !Type->bools_16A4[7]) {
            return 1;
        }
        return 0x17;
    case 0xD:
        if (Type->bools_16A4[25]) {
            return 1;
        }
        break;
    }
    return FUN_006F4AB0(a1, message, a3);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x43CEA0
// Redraws the part of the building that falls inside `rect`; returns whether
// anything overlapped. Slot 65.
bool BuildingClass::vf_65(RectangleStruct* rect, bool force, int draw)
{
    if (DAT_00A8ED6B == 0 && DAT_00B73550 != 0) {
        if (!force && !NeedsRedraw)
            return false;
        if (!IsOnMap)
            return false;
        if (InLimbo)
            return false;
    }

    RectangleStruct extent;
    NeedsRedraw = false;
    *rect = *FUN_00421B60(&extent, rect, &DAT_00886FA0, 0, 0);

    int clipX = DAT_00886FA0.X;
    int clipY = DAT_00886FA0.Y;
    extent = vf_75();
    int left = extent.X + clipX;
    int top = extent.Y + clipY;
    int right = left + extent.Width;
    int bottom = top + extent.Height;

    if (rect->X < right && rect->Y < bottom
        && rect->X + rect->Width > left && rect->Y + rect->Height > top) {
        Point2D point;
        DAT_00887324->FUN_006D2140(vf_43(), &point);
        if (rect->X > DAT_00886FA0.X)
            point.X += DAT_00886FA0.X - rect->X;
        if (rect->Y > DAT_00886FA0.Y)
            point.Y += DAT_00886FA0.Y - rect->Y;
        if (draw) {
            if (!IsFogged)
                vf_313(&point, rect);
        } else {
            vf_69(&point, rect);
        }
        return true;
    }
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x43D030
// Draws the building's deploy/undeploy shape in two strips around `point`.
// Slot 70.
void BuildingClass::vf_70(Point2D* point, RectangleStruct* clip)
{
    CellStruct cell = vf_110();
    SHPStruct* shape = static_cast<SHPStruct*>(vf_27());
    if (!shape)
        return;
    if (Type->bools_1700[1])
        return;
    if (vf_97() == 0x18 && !UnloadTimer.FUN_004A51D0())
        return;
    if (vf_97() == 0x10 && Type->DeployingAnim) {
        ObjectClass* produced = Factory->FUN_004CA160();
        if (produced && produced->vf_33()->bools_D94[0])
            shape = Type->RoofDeployingAnim;
        else
            shape = Type->DeployingAnim;
    }

    Point2D origin = *point;
    int halfHeight = shape->unknown_04 / 2;
    int stripBottom = origin.Y - halfHeight;
    RectangleStruct rect = *clip;
    if (rect.Height > stripBottom)
        rect.Height = stripBottom;
    if (rect.Height > 0) {
        FUN_00705E00(shape, FUN_0043EF90(), &origin, &rect, 0, 0x100,
                     -2 - FUN_006D20E0(FUN_005F5F30()), 2, 0,
                     DAT_0087F7E8.FUN_005657A0(&cell)->Intensity_Normal, 0, 0, 0, 0, 0, 0);
    }

    Point2D lowerOrigin(point->X, origin.Y - stripBottom);
    rect = *clip;
    rect.Y += stripBottom;
    rect.Height = shape->unknown_04;
    if (rect.Y + shape->unknown_04 > clip->Y + clip->Height)
        rect.Height = clip->Y + clip->Height - rect.Y;
    if (rect.Y < clip->Y) {
        int clippedAway = rect.Y - clip->Y;
        rect.Y = clip->Y;
        rect.Height += clippedAway;
        lowerOrigin.Y += clippedAway;
    }
    if (rect.Height > 0) {
        FUN_00705E00(shape, FUN_0043EF90(), &lowerOrigin, &rect, 0, 0x100,
                     -FUN_006D20E0(FUN_005F5F30()), 0, 0,
                     DAT_0087F7E8.FUN_005657A0(&cell)->Intensity_Normal, 0, 0, 0, 0, 0, 0);
    }
}

#include "house_building/building_a4_views.h"

// The colour of one house-colour table entry in the display's pixel format: the format code selects which of
// three packings are added (the format 2 packing is added on top of the format 1 one, which sits on top of
// the base one).
inline unsigned BA4PackColor(unsigned char r, unsigned char g, unsigned char b)
{
    unsigned value = 0;
    switch (FUN_004BBC90()) {
    case 2:
        value |= (((((unsigned short)r) << 6) | (unsigned short)g) << 5) | (unsigned short)b;
    case 1:
        value |= (((((unsigned short)(g >> 1)) | (((unsigned short)r) << 5)) << 6) | (unsigned short)b);
    }
    value |= (((((unsigned short)(g >> 1)) | (((unsigned short)r) << 5)) << 5) | (unsigned short)b);
    return value;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x43DA80
void BuildingClass::vf_313(Point2D* pos, RectangleStruct* clip)
{
    CellStruct here = vf_110();
    int i;

    if (vf_97() == 0x10) {
        if (UnloadTimer.FUN_004A5110() || UnloadTimer.FUN_004A51B0() || UnloadTimer.FUN_004A51D0() || UnloadTimer.FUN_004A5130()) {
            if (IsTether) {
                for (i = 0; i < RadioLinks.Capacity; i++) {
                    ObjectClass* object = FUN_0065AD40(i);
                    if (object && !object->InLimbo && object->vf_11() != 6) {
                        CoordStruct a = object->vf_19(0);
                        a.Z = object->Location.Z;
                        if (DAT_00B73550 && !DAT_00A8ED6B && (DAT_00A8B230->unknown_0000 & 0x1000)) {
                            CoordStruct q = object->Location;
                            if (DAT_0087F7E8.IsLocationFogged(&q)) {
                                continue;
                            }
                            if (DAT_0087F7E8.IsLocationFogged(&a)) {
                                continue;
                            }
                        }
                        Point2D screen = DAT_00887324->FUN_006D2140(object->vf_43());
                        object->vf_69(&screen, clip);
                    }
                }
            }
        }
    }

    unsigned color = 0;
    if (Airstrike) {
        RulesColor_004B9BD0* c = &RulesInstance->ColorAdd[RulesInstance->LaserTargetColor];
        color |= BA4PackColor(c->R, c->G, c->B);
    }
    if (vf_88() && ForceShielded == 1) {
        RulesColor_004B9BD0* c = &RulesInstance->ColorAdd[RulesInstance->ForceShieldColor];
        color |= BA4PackColor(c->R, c->G, c->B);
    }

    CoordStruct loc = vf_18();
    CellStruct cell = BA4Off(loc.X / 256, loc.Y / 256);
    if (BA4At(cell)->FUN_00487950()) {
        color = 0;
    }

    if (vf_97() == 0x10 && Type->DoorAnim) {
        if (UnloadTimer.FUN_004A51D0() || UnloadTimer.FUN_004A5110() || UnloadTimer.FUN_004A5130() || UnloadTimer.FUN_004A51B0()) {
            int frame = (int)(UnloadTimer.PercentageDone() * Type->DoorStages);
            if (UnloadTimer.FUN_004A5130()) {
                frame = Type->DoorStages - frame;
            }
            if (UnloadTimer.FUN_004A51D0()) {
                frame = 0;
            }
            if (frame >= Type->DoorStages) {
                frame = Type->DoorStages - 1;
            }
            if (frame < 0) {
                frame = 0;
            }
            if (FUN_005F5C60() <= RulesInstance->ConditionYellow && Type->bools_1700[0]) {
                frame += Type->DoorStages;
            }
            int sortKey = -5 - FUN_006D20E0(FUN_005F5F30());
            FUN_00705E00(Type->DoorAnim, frame, pos, clip, 0, 0x100, sortKey, 0, 0,
                         BA4At(cell)->Intensity_Normal, 0, 0, 0, 0, 0, 0);
            if (UnloadTimer.FUN_004A5130() && frame == 0) {
                NeedsRedraw = 1;
            }
        }
    }

    if (Type->bools_16A4[33]) {
        bool inSale = false;
        if (CurrentMission == 0x12 || QueuedMission == 0x12) {
            if (StageClass::Value < Type->BuildingAnimFrame[0].Count + Type->BuildingAnimFrame[0].Frame - 1) {
                inSale = true;
            }
        }
        if (((CurrentMission != 0x13 || StageClass::Value < 1) && !inSale) || Type->bools_16A4[38]) {
            int tint;
            int shadowTint;
            if (DAT_00887418) {
                tint = ((PrimaryFacing.FUN_004C93D0().Whole >> 10) + 1 >> 1) & 0x1F;
                shadowTint = ((PrimaryFacing.FUN_004C93D0().Whole >> 10) + 1 >> 1) & 0x1F;
            } else {
                tint = -1;
                shadowTint = -1;
            }
            int phaseA = 0;
            int phaseB = 0;
            if (Type->TurretVoxel.HVAData) {
                phaseA = TurretAnimFrame % Type->TurretVoxel.HVAData->unknown_08;
            }
            if (Type->BarrelVoxel.HVAData) {
                phaseB = TurretAnimFrame % Type->BarrelVoxel.HVAData->unknown_08;
            }
            tint |= (phaseA & 0xFF) << 16;
            shadowTint |= (phaseB & 0xFF) << 16;

            BA4Matrix matrix;
            if (Type->TurretVoxel.unknown_00) {
                int dirA = ((PrimaryFacing.FUN_004C93D0().Whole >> 10) + 1 >> 1) & 0x1F;
                matrix.RotateZ((float)(dirA - 8) * (-0.19634954084936207));
                matrix.TranslateX((float)(Type->TurretOffset / 8));
                float vx = matrix.Row[0][3];
                float vy = matrix.Row[1][3];
                float vz = matrix.Row[2][3];
                Vector3D negative(-vx, -vy, -vz);
                Vector3D positive(vx, vy, vz);
                BA4Matrix second = matrix;
                second.Translate(negative);
                if (TurretRecoil.State) {
                    matrix.TranslateX(-TurretRecoil.TravelSoFar);
                    tint = -1;
                }
                if (BarrelRecoil.State) {
                    second.TranslateX(-BarrelRecoil.TravelSoFar);
                    tint = -1;
                }
                int dirB = ((BarrelFacing.FUN_004C93D0().Whole >> 10) + 1 >> 1) & 0x1F;
                second.RotateY(-((float)(dirB - 8) * (-0.19634954084936207)));
                second.Translate(positive);
                Point2D at;
                at.X = pos->X + Type->BuildingAnim[9].X;
                at.Y = pos->Y + Type->BuildingAnim[9].Y;
                bool tail = false;
                if (((PrimaryFacing.FUN_004C93D0().Whole >> 13) + 1 >> 1 & 3) > 0
                    && ((PrimaryFacing.FUN_004C93D0().Whole >> 13) + 1 >> 1 & 3) < 3) {
                    tail = true;
                } else if (Type->BarrelVoxel.unknown_00 && Type->BarrelVoxel.HVAData) {
                    BA4MatrixTemp product;
                    BA4MatrixTemp defaults;
                    vf_273(&Type->BarrelVoxel, 0, tint, &Type->VoxelTurretBarrelCache, clip, &at,
                           FUN_005AF980(&product, defaults.FUN_00754BE0(), &second),
                           BA4At(cell)->Intensity_Normal, color, 0);
                }
                {
                    BA4MatrixTemp product;
                    BA4MatrixTemp defaults;
                    vf_273(&Type->TurretVoxel, 0, tint, &Type->VoxelShadowCache, clip, &at,
                           FUN_005AF980(&product, defaults.FUN_00754BE0(), &matrix),
                           BA4At(cell)->Intensity_Normal, color, 0);
                }
                if (tail && Type->BarrelVoxel.unknown_00 && Type->BarrelVoxel.HVAData) {
                    BA4MatrixTemp product;
                    BA4MatrixTemp defaults;
                    vf_273(&Type->BarrelVoxel, 0, tint, &Type->VoxelTurretBarrelCache, clip, &at,
                           FUN_005AF980(&product, defaults.FUN_00754BE0(), &second),
                           BA4At(cell)->Intensity_Normal, color, 0);
                }
            } else if (Type->BarrelVoxel.unknown_00 && Type->BarrelVoxel.HVAData) {
                float vx = matrix.Row[0][3];
                float vy = matrix.Row[1][3];
                float vz = matrix.Row[2][3];
                Vector3D negative(-vx, -vy, -vz);
                Vector3D positive(vx, vy, vz);
                matrix.Translate(negative);
                int dirA = ((PrimaryFacing.FUN_004C93D0().Whole >> 10) + 1 >> 1) & 0x1F;
                matrix.RotateZ((float)(dirA - 8) * (-0.19634954084936207));
                int dirB = ((BarrelFacing.FUN_004C93D0().Whole >> 10) + 1 >> 1) & 0x1F;
                matrix.RotateY(-((float)(dirB - 8) * (-0.19634954084936207)));
                matrix.Translate(positive);
                Point2D at;
                at.X = pos->X + Type->BuildingAnim[9].X;
                at.Y = pos->Y + Type->BuildingAnim[9].Y;
                BA4MatrixTemp product;
                BA4MatrixTemp defaults;
                vf_273(&Type->BarrelVoxel, 0, shadowTint, &Type->VoxelTurretBarrelCache, clip, &at,
                       FUN_005AF980(&product, defaults.FUN_00754BE0(), &matrix),
                       BA4At(cell)->Intensity_Normal, color, 0);
            }
        }
    } else if (Type->bools_16A4[34]) {
        bool inSale = false;
        if (CurrentMission == 0x12 || QueuedMission == 0x12) {
            if (StageClass::Value < Type->BuildingAnimFrame[0].Count + Type->BuildingAnimFrame[0].Frame - 1) {
                inSale = true;
            }
        }
        if (!(CurrentMission == 0x13 && StageClass::Value > 0) && !inSale) {
            BA4MatrixTemp scratchMatrix;
            BA4MatrixTemp matrix = *FUN_00458810(&scratchMatrix);
            int angle = ((((PrimaryFacing.FUN_004C93D0().Whole >> 10) + 1 >> 1) & 0x1F) + DAT_00818CB0) % 32;
            bool visible = angle <= 0x10;
            AnimClass* child = Anims[9];
            if (visible && child) {
                if (DAT_00818CB4) {
                    child->Invisible = 0;
                }
                child->vf_65(&DAT_00886FA0, 1, 0);
                child->Invisible = 1;
            }
            Point2D at;
            at.X = pos->X + Type->BuildingAnim[9].X;
            at.Y = pos->Y + Type->BuildingAnim[9].Y;
            BA4MatrixTemp product;
            BA4MatrixTemp defaults;
            vf_273(&Type->BarrelVoxel, 0, -1, &Type->VoxelMainCache, clip, &at,
                   FUN_005AF980(&product, defaults.FUN_00754BE0(), &matrix),
                   BA4At(cell)->Intensity_Normal, color, 0);
            if (!visible && child) {
                if (DAT_00818CB4) {
                    child->Invisible = 0;
                }
                child->vf_65(&DAT_00886FA0, 1, 0);
                child->Invisible = 1;
            }
        }
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x43E900
int BuildingClass::vf_187()
{
    int value = -Tactical::AdjustForZ(FUN_005F5F30());

    BuildingTypeClass* type = Type;

    if (type->bools_16A4[0x16C5 - 0x16A4]) {
        return type->BuildingAnim[9].ZAdjust + value;
    }

    return value;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x43ED40
//
// CAPPED at 10.1% (first transcription plus two reshapes). The facing from this building (plus the per-type
// firing offset, a zero coordinate by default) to a target. Delta: retail keeps the offset in ESI/EDI with
// the Z in a stack slot and reaches one shared transform call from both branches with different buffers;
// the sequential, shared-pointer and branch-swapped forms differ in prologue, frame (0x18 vs 0x2c) and call order.
DirStruct BuildingClass::vf_314(AbstractClass* target)
{
    CoordStruct off = DAT_0089C848;
    BuildingTypeClass* type = Type;
    Point2D p;
    Point2D buf;
    if (type->PrimaryFirePixelOffset.X == 0xFFFF && type->PrimaryFirePixelOffset.Y == 0xFFFF) {
        p.X = type->BuildingAnim[9].X;
        p.Y = type->BuildingAnim[9].Y;
        if (p.X != 0 || p.Y != 0) {
            Point2D* r = DAT_00887324->FUN_006D2070(&buf, &p);
            off.X = r->X;
            off.Y = r->Y;
            off.Z = 0;
        }
    } else {
        Point2D* r = DAT_00887324->FUN_006D2070(&p, &type->PrimaryFirePixelOffset);
        off.X = r->X;
        off.Y = r->Y;
        off.Z = 0;
    }
    const CoordStruct& c = vf_18();
    int px = c.X + off.X;
    int py = c.Y + off.Y;
    const CoordStruct& t = target->vf_18();
    int tx = t.X;
    DirStruct d;
    d.Raw = (short)((FUN_004CAE30((double)py - t.Y, (double)tx - px) - DAT_007E2820) * DAT_007E2818);
    return d;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x43EE50
// When the building is in its active state and has its Anims[9] animation,
// show the frame for the current primary facing (32 steps) and zero the
// animation's step. Returns the frame, or 0 when nothing was done.
int BuildingClass::FUN_0043EE50()
{
    int frame = 0;
    if (vf_255() && Anims[9]) {
        DirStruct facing = PrimaryFacing.FUN_004C93D0();
        frame = DAT_007F4890[((facing.Whole >> 10) + 1 >> 1) & 0x1F];
        AnimClass* anim = Anims[9];
        if (anim) {
            anim->Value = frame;
            anim->Step = 0;
        }
    }
    return frame;
}


// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x43F180
bool BuildingClass::vf_73(int mark)
{
    CellStruct cell;
    int zero = 0;
    int x;
    int y;

    if (!TechnoClass::vf_73(mark)) {
        goto refuse;
    }

    cell = vf_110();

    switch (mark) {
    case 0:
        DAT_0087F7E8.FUN_005687F0(&cell, this);
        return true;

    case 1:
    case 3:
        if (Type->ToTile) {
            if (vf_107(BA4At(cell), -1, -1, 0, 1) == 0) {
                int width = Type->GetFoundationWidth();
                int height = Type->GetFoundationHeight(false);
                bool placed = zero;

                for (y = 0; y < height; y++) {
                    for (x = 0; x < width; x++) {
                        CellStruct c = cell + BA4Off(x, y);
                        if (BA4At(c)->FUN_0047C620(Type->SpeedType, Type, Owner)
                            && BA4At(c)->IsoTileTypeIndex != Type->ToTile->unknown_294
                            && BA4At(c)->LandType != 1) {
                            CellClass* mc = BA4At(c);
                            if (mc->SmudgeTypeIndex != -1) {
                                BA4Placed* placedType = DAT_00A8EC1C[mc->SmudgeTypeIndex];
                                CellStruct base = mc->MapCoords;
                                int index = mc->SmudgeData;
                                base.X -= (short)(index % placedType->unknown_298);
                                base.Y -= (short)(index / placedType->unknown_298);
                                for (int j = 0; j < placedType->unknown_29C; j++) {
                                    for (int i = 0; i < placedType->unknown_298; i++) {
                                        BA4At(base + BA4Off(i, j))->SmudgeTypeIndex = -1;
                                        BA4At(base + BA4Off(i, j))->FUN_004852D0();
                                    }
                                }
                            }
                            ObjectClass* created = Type->ToTile->vf_35(Owner);
                            CoordStruct where;
                            where.X = c.X * 256 + 128;
                            where.Y = c.Y * 256 + 128;
                            where.Z = zero;
                            created->vf_54(where, 0);
                            if (Owner == DAT_00A83D4C) {
                                CoordStruct reveal;
                                reveal.X = c.X * 256 + 128;
                                reveal.Y = c.Y * 256 + 128;
                                reveal.Z = zero;
                                DAT_0087F7E8.FUN_005678E0(&reveal, 1, DAT_00A83D4C, zero, zero, zero, 1, zero);
                                CoordStruct reveal2;
                                reveal2.X = c.X * 256 + 128;
                                reveal2.Y = c.Y * 256 + 128;
                                reveal2.Z = zero;
                                DAT_0087F7E8.FUN_005678E0(&reveal2, 1, DAT_00A83D4C, zero, zero, zero, 1, 1);
                            }
                            placed = true;
                        }
                    }
                }
                for (y = 0; y < height + 2; y++) {
                    for (x = 0; x < width + 2; x++) {
                        BA4At(cell + BA4Off(x - 1, y - 1))->FUN_00486E70();
                    }
                }
                if (placed) {
                    vf_160(3);
                    vf_62();
                    return true;
                }
            }
            TechnoClass::vf_73(0);
            goto refuse;
        }
        if (Type->bools_1570[1]) {
            BA4Spawned* spawned = new BA4Spawned(Type->ToOverlay, &cell, Owner->Type->ArrayIndex2);
            vf_160(3);
            vf_62();
            return true;
        }
        if (mark != 3) {
            if (vf_107(BA4At(cell), -1, -1, 0, 1) != 0) {
                goto refuse;
            }
        }
        DAT_0087F7E8.FUN_005683C0(&cell, this);
        {
            CoordStruct where;
            where.X = cell.X * 256 + 128;
            where.Y = cell.Y * 256 + 128;
            where.Z = zero;
            vf_109(Type->vf_27(where));
        }
        {
            CoordStruct center = vf_43();
            for (int k = 0; k < 21; k++) {
                if (Anims[k]) {
                    CoordStruct scratchOffset;
                    CoordStruct* offset = DAT_00887324->FUN_006D2360(&scratchOffset, &Type->BuildingAnim[k].X);
                    CoordStruct sumScratch;
                    CoordStruct sum = *sumScratch.FUN_0041C230(center.X + offset->X, offset->Y + center.Y, offset->Z + center.Z);
                    Anims[k]->vf_109(sum);
                }
            }
        }
        {
            int width = Type->GetFoundationWidth();
            int height = Type->GetFoundationHeight(false);
            for (y = 0; y < height; y++) {
                for (x = 0; x < width; x++) {
                    CellClass* mc = BA4At(cell + BA4Off(x, y));
                    if (mc->SmudgeTypeIndex != -1) {
                        BA4Placed* placedType = DAT_00A8EC1C[mc->SmudgeTypeIndex];
                        CellStruct base = mc->MapCoords;
                        int index = mc->SmudgeData;
                        base.X -= (short)(index % placedType->unknown_298);
                        base.Y -= (short)(index / placedType->unknown_298);
                        for (int j = 0; j < placedType->unknown_29C; j++) {
                            for (int i = 0; i < placedType->unknown_298; i++) {
                                BA4At(base + BA4Off(i, j))->SmudgeTypeIndex = -1;
                                BA4At(base + BA4Off(i, j))->FUN_004852D0();
                            }
                        }
                    }
                }
            }
            for (y = 0; y < height + 2; y++) {
                for (x = 0; x < width + 2; x++) {
                    BA4At(cell + BA4Off(x - 1, y - 1))->FUN_00486E70();
                }
            }
        }
        return true;

    case 2:
        {
            void* value = vf_121();
            int angle = vf_281(vf_111()->Intensity_Normal);
            BuildingClass* techno = BA4As<BuildingClass>(this, 6);
            if (vf_88() || (Airstrike && Airstrike->Target == techno)) {
                angle = GetEffectTintIntensity(angle);
            }
            LightTint = (short)angle;
            for (int k = 0; k < 21; k++) {
                AnimClass* anim = Anims[k];
                if (anim) {
                    if (anim->Type && anim->Type->ShouldUseCellDrawer) {
                        anim->LightConvert = value;
                        anim->TintColor = angle & 0xFFFF;
                    }
                    char facing = Translucency;
                    if (facing == 0xF && vf_26(0, 0) == 5) {
                        facing = 0x10;
                    }
                    for (int m = 0; m < 21; m++) {
                        if (Anims[m]) {
                            Anims[m]->TranslucencyLevel = facing;
                        }
                    }
                }
            }
            char facing = Translucency;
            if (facing == 0xF && vf_26(0, 0) == 5) {
                facing = 0x10;
            }
            for (int m = 0; m < 21; m++) {
                if (Anims[m]) {
                    Anims[m]->TranslucencyLevel = facing;
                }
            }
        }
        break;
    }
    return true;
refuse:
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x43FB20
void BuildingClass::vf_23()
{
    unsigned char working;
    if (vf_212() && vf_97() != 0x12 && vf_97() != 0x13)
        working = 1;
    else
        working = 0;

    if (working != WasOnline) {
        if (Type->WorkingSound != -1 || Type->NotWorkingSound != -1) {
            Audio8.FUN_00405FD0();
            CoordStruct location = Location;
            if (working)
                FUN_007509E0(Type->WorkingSound, &location, &Audio8);
            else
                FUN_007509E0(Type->NotWorkingSound, &location, &Audio8);
        }
        FUN_004549B0();
        WasOnline = working;
    } else {
        if (Type->WorkingSound != -1 || Type->NotWorkingSound != -1) {
            CoordStruct location = Location;
            FUN_00750D40(&location, &Audio8);
        }
    }

    unsigned char damaged;
    if (Type->bools_1570[0xB])
        damaged = GetHealthPercentage() <= RulesInstance->ConditionRed;
    else
        damaged = GetHealthPercentage() <= RulesInstance->ConditionYellow;
    if (damaged != RequiresDamageFires) {
        if (damaged) {
            FUN_0043C0D0();
        } else {
            for (int i = 0; i < 8; i++) {
                if (DamageFireAnims[i] != 0) {
                    ((ObjectClass*)DamageFireAnims[i])->vf_62();
                    DamageFireAnims[i] = 0;
                }
            }
        }
        RequiresDamageFires = damaged;
    }

    if (Type->bools_C8C[0x15])
        TurretIsRotating = PrimaryFacing.IsRotating();
    else
        TurretIsRotating = 0;

    if (TemporalTargetingMe != 0)
        ((AbstractClass*)TemporalTargetingMe)->vf_23();

    if (vf_117() || vf_118()) {
        // Active or occupied: spawn the type's anim at its muzzle points or, when
        // there are none, at the building's own location.
        if (Type->MaxNumberOccupants == 0 || RulesInstance->ChronoSparkle1 == 0) {
            if (CurrentFrame % 0x18 == 0 && RulesInstance->ChronoSparkle1 != 0)
                new AnimClass(RulesInstance->ChronoSparkle1, Location, 0, 1, 0x600, 0, false);
        } else {
            for (int index = 0; index < Type->MaxNumberOccupants; index++) {
                if ((CurrentFrame + index) % 0x18 == 0 && RulesInstance->ChronoSparkle1 != 0) {
                    Point2D projected;
                    Point2D* point = DAT_00887324->FUN_006D2070(&projected, &Type->MuzzleFlash[index]);
                    CoordStruct coordinate;
                    coordinate.X = point->X;
                    coordinate.Y = point->Y;
                    coordinate.Z = 0;
                    CoordStruct origin = vf_43();
                    coordinate.X += origin.X;
                    coordinate.Y += origin.Y;
                    coordinate.Z += origin.Z;
                    AnimClass* anim = new AnimClass(RulesInstance->ChronoSparkle1, coordinate, 0, 1, 0x600, 0, false);
                    anim->ZAdjust = -200;
                }
            }
        }
        if (Target != 0)
            vf_242(0);
        return;
    }

    if (TimeLeft(CashProductionTimer) == 1) {
        CashProductionTimer.StartTime = CurrentFrame;
        CashProductionTimer.TimeLeft = Type->ProduceCashDelay;
        if (!((HouseTypeClass*)Owner->Type)->MultiplayPassive && vf_212()) {
            if (Type->ProduceCashAmount > 0)
                Owner->GiveMoney(Type->ProduceCashAmount);
            else
                Owner->FUN_004F9790(-Type->ProduceCashAmount);
        }
    }

    if (Airstrike != 0 && ((AirstrikeClass*)Airstrike)->Target == this)
        vf_73(2);

    if (Type->bools_16A4[0x14] && Target != 0 && !((AbstractClass*)Target)->IsInAir())
        vf_242(0);

    FUN_004509D0();
    if (vf_128() && BState != 0 && vf_123())
        IsReadyToCommence = false;
    FUN_006F9E50();
    if (!IsAlive)
        return;

    if (vf_33()->IsGattling && FUN_0070DDF0() > 0)
        TurretAnimFrame++;

    if (Ammo == 0 && !Type->bools_16A4[0x1D] && !Type->bools_16A4[0x1E])
        Ammo = Type->Ammo;

    if (vf_97() != 1) {
        if (vf_33()->IsGattling && CurrentFrame - LastFireBulletFrame > RulesInstance->GuardAreaTargetingDelay + 5) {
            FUN_0070DE40(Type->RateDown);
            int current = FUN_0070DDF0();
            int stage = FUN_0070DDC0();
            if (stage > 0) {
                int limit;
                if (Veterancy.FUN_00750010())
                    limit = Type->EliteStage[stage - 1];
                else
                    limit = Type->WeaponStage[stage - 1];
                if (current < limit)
                    SetCurrentWeaponStage(stage - 1);
            }
        }
        if (vf_33()->IsGattling && FUN_0070DDF0() > 0)
            TurretAnimFrame++;
    }

    if (vf_128() && vf_123())
        IsReadyToCommence = false;

    if (QueueBState != -1) {
        if (BState != QueueBState) {
            BuildingAnimFrameStruct* row = &Type->BuildingAnimFrame[QueueBState];
            BState = QueueBState;
            int duration = row->Rate;
            if (BState == 0 || BState == 1)
                duration = DAT_00A8EB60.FUN_005FB2E0(row->Rate);
            StageClass::Timer.StartTime = CurrentFrame;
            StageClass::Timer.TimeLeft = duration;
            StageClass::Rate = duration;
            StageClass::Value = row->Frame;
        }
        QueueBState = -1;
    }

    if (Health != unknown_544) {
        Owner->RecheckPower = 1;
        Owner->RecheckRadar = 1;
        unknown_544 = Health;
    }

    if (Health == 0) {
        for (int i = 0; i < 8; i++) {
            if (DamageFireAnims[i] != 0) {
                ((ObjectClass*)DamageFireAnims[i])->vf_62();
                DamageFireAnims[i] = 0;
            }
        }
        if (TimeLeft(C4Timer) != 0)
            return;
        vf_53();
        FUN_00442D90((int)C4AppliedBy);
        vf_62();
        FUN_00441F60();
        return;
    }

    FUN_004503F0();
    if (Type->bools_1570[5]) {
        TechnoClass** list = (TechnoClass**)Overpowerers.Items;
        for (int i = Overpowerers.Count - 1; i >= 0; i--) {
            if (list[i]->Target != this && i < Overpowerers.Count) {
                Overpowerers.Count--;
                for (int j = i; j < Overpowerers.Count; j++)
                    list[j] = list[j + 1];
            }
        }
        int count = Overpowerers.Count;
        if (count >= 3 || (Owner->GetPowerPercentage() == DAT_007E1718 && HasPower && count >= 1))
            IsOverpowered = true;
        else
            IsOverpowered = false;
    }
    if (Type->bools_1570[0xB])
        FUN_00458200();
    FUN_00450630();
    if (Type->Factory != 0)
        FUN_004500F0();

    if (C4Applied) {
        if (TimeLeft(C4Timer) == 0) {
            if (Type->bools_16A4[0x12]) {
                bool special = false;
                for (int y = -2; y < 3; y++) {
                    for (int x = -2; x < 3; x++) {
                        CellStruct origin = vf_110();
                        CellStruct first;
                        first.X = origin.X + x;
                        first.Y = origin.Y + y;
                        int tile = DAT_0087F7E8.FUN_005657A0(&first)->IsoTileTypeIndex;
                        origin = vf_110();
                        CellStruct second;
                        second.X = origin.X + x;
                        second.Y = origin.Y + y;
                        int overlay = DAT_0087F7E8.FUN_005657A0(&second)->OverlayTypeIndex;
                        if ((tile >= DAT_00ABAD1C && tile < DAT_00ABAD1C + 0x10)
                            || (overlay >= 0x4A && overlay <= 0x65))
                            special = true;
                    }
                }
                CellStruct cell = vf_110();
                if (special)
                    DAT_0087F7E8.FUN_00574C20(&cell);
                else
                    DAT_0087F7E8.FUN_00574000(&cell);
                C4Applied = false;
                C4AppliedBy = 0;
            } else {
                int damage = Health;
                vf_91(&damage, 0, RulesInstance->C4Warhead, C4AppliedBy, true, false, 0);
            }
            if (!IsAlive)
                return;
            vf_73(2);
        }
    }

    if (Target == 0)
        return;
    if (IsCloseEnoughToAttack((AbstractClass*)Target))
        return;
    if (((AbstractClass*)Target)->vf_11() == 2 && !((AbstractClass*)Target)->IsOnFloor())
        return;
    vf_242(0);
}


// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x440580
bool BuildingClass::vf_54(const CoordStruct& where, int dir)
{
    int i;
    int x;
    int y;
    bool ok = vf_107(DAT_0087F7E8.FUN_00565730(where), -1, -1, 0, 1) == 0;

    if (ok) {
        if (Type == RulesInstance->WallTower) {
            CellClass* mc = DAT_0087F7E8.FUN_00565730(where);
            HouseClass* cellOwner = 0;
            if (mc->WallOwnerIndex >= 0) {
                cellOwner = HouseClass_Array.Items[mc->WallOwnerIndex];
            }
            if (cellOwner == Owner && (mc->OverlayTypeIndex == 2 || mc->OverlayTypeIndex == 0)) {
                Owner->FUN_004FCE80(&mc->MapCoords, 1);
            }
        } else if (Type->ToOverlay) {
            CellClass* mc = DAT_0087F7E8.FUN_00565730(where);
            HouseClass* cellOwner = 0;
            if (mc->WallOwnerIndex >= 0) {
                cellOwner = HouseClass_Array.Items[mc->WallOwnerIndex];
            }
            if (cellOwner == Owner && mc->OverlayTypeIndex == Type->ToOverlay->ArrayIndex) {
                Owner->FUN_004FCE80(&mc->MapCoords, 1);
            }
        } else if (Type->bools_16A4[19]) {
            CellStruct cell = BA4Off(where.X / 256, where.Y / 256);
            for (CellStruct* p = Type->vf_36(1); !(p->X == 0x7FFF && p->Y == 0x7FFF); p++) {
                CellClass* mc = BA4At(*p + cell);
                HouseClass* cellOwner = 0;
                if (mc->WallOwnerIndex >= 0) {
                    cellOwner = HouseClass_Array.Items[mc->WallOwnerIndex];
                }
                if (cellOwner == Owner && (mc->OverlayTypeIndex == 2 || mc->OverlayTypeIndex == 0 || mc->OverlayTypeIndex == 0x1A)) {
                    Owner->FUN_004FCE80(&mc->MapCoords, 1);
                }
                BuildingClass* neighbour = mc->GetBuilding();
                if (neighbour && neighbour->Type->bools_16A4[27]) {
                    if (neighbour->vf_14() == vf_14()) {
                        CellStruct copy = mc->MapCoords;
                        copy.FUN_00453240();
                    }
                }
            }
        }
    }

    if (Type->bools_1570[1]) {
        if (vf_107(DAT_0087F7E8.FUN_00565730(where), -1, -1, 0, 1) == 0) {
            ObjectClass* created = Type->ToOverlay->vf_35(Owner);
            if (created && created->vf_54(where, 0)) {
                DAT_0087F7E8.FUN_00565730(where)->WallOwnerIndex = Owner->ArrayIndex;
                vf_157(3);
                DAT_0087F7E8.FUN_005678E0(&where, Type->Sight, Owner, 0, 0, 0, 1, 0);
                DAT_0087F7E8.FUN_005678E0(&where, Type->Sight, Owner, 0, 0, 0, 1, 1);
                vf_62();
                return true;
            }
        }
        goto refuse;
    }

    if (Type->PowersUpBuilding) {
        Point2D unused;
        unused.X = 0;
        unused.Y = 0;
        CellStruct cell = BA4Off(where.X / 256, where.Y / 256);
        BuildingClass* other = DAT_0087F7E8.FUN_004AA290(&cell, &unused);
        if (!other || other->vf_11() != 6) {
            goto refuse;
        }
        BuildingTypeClass* thisType = Type;
        if (Owner != other->Owner) {
            goto refuse;
        }
        if (_stricmp(thisType->PowersUpBuilding, other->Type->ID) != 0) {
            goto refuse;
        }
        int levels = thisType->PowersUpToLevel;
        if (levels == -1) {
            if (!(other->UpgradeLevel < other->Type->Upgrades)) {
                if (other->UpgradeLevel != 0) {
                    goto refuse;
                }
            }
        } else {
            if (levels <= 0 || levels > 3) {
                goto refuse;
            }
            if (other->UpgradeLevel != 0) {
                goto refuse;
            }
        }
        Owner->RecheckRadar = 1;
        Owner->RecheckPower = 1;
        int count = Type->PowersUpToLevel;
        if (count == -1) {
            count = 1;
        }
        char* name = &other->Type->BuildingAnim[other->UpgradeLevel].Anim[0];
        if (_stricmp(name, Type->ImageFile) != 0) {
            strncpy(name, Type->ImageFile, 16);
        }
        for (; count != 0; count--) {
            other->FUN_00451400();
        }
        other->Upgrades[other->UpgradeLevel] = Type;
        Owner->FUN_0050B1D0();
        Owner->RecheckTechTree = 1;
        if (Type->bools_1760[3]) {
            Owner->AcquiredThreatNode();
        }
        vf_62();
        return true;
    }

    if (Type->bools_16A4[27]) {
        DirStruct facing;
        facing.Whole = dir;
        if ((((facing.Whole >> 12) + 1) & 6) == 4) {
            LaserFenceFrame = 8;
        } else {
            LaserFenceFrame = 12;
        }
    }
    if (ok && Type->bools_16A4[26]) {
        LaserFenceFrame = 0;
        CellStruct cell = BA4Off(where.X / 256, where.Y / 256);
        BuildingClass* other = BA4At(cell)->GetBuilding();
        if (other && other->Type->bools_16A4[27]) {
            if (other->vf_14() == vf_14()) {
                other->vf_62();
            }
        }
    }
    if (!TechnoClass::vf_54(where, dir)) {
        goto refuse;
    }
    if (Type->bools_16A4[35]) {
        Owner->HasCloakingRanges = 1;
    }
    if (!IsAlive) {
        return true;
    }
    if (Session_00A8B238.GameMode && !Owner->IsControlledByHuman() && !Owner->Type->MultiplayPassive) {
        ShouldRebuild = 1;
    }
    if (DAT_00A8B230->unknown_0000 & 0x1000) {
        CellStruct here = vf_110();
        CellStruct* p;
        for (p = Type->vf_36(0); !(p->X == 0x7FFF && p->Y == 0x7FFF); p++) {
            if (BA4At(p->FUN_0042D510(here))->Flags & 0x400000) {
                goto skip;
            }
        }
        FUN_00457AA0(0, 0, 0);
    }
skip:
    if ((!Type->UndeploysInto || !Type->ResourceGatherer) && !vf_32()) {
        FUN_00455F10(0);
    }
    {
        int width = Type->GetFoundationWidth();
        int height = Type->GetFoundationHeight(false);
        CellStruct cell = BA4Off(where.X / 256, where.Y / 256);
        for (y = 0; y < height + 2; y++) {
            for (x = 0; x < width + 2; x++) {
                BA4At(cell + BA4Off(x - 1, y - 1))->BlockedNeighbours++;
            }
        }
    }
    Owner->FUN_004FD150();
    Owner->FUN_004FFA50(this);
    Owner->RecheckTechTree = 1;
    unknown_544 = 0;
    if ((!DiscoveredByCurrentPlayer && (DAT_0087F7E8.FUN_00565730(where)->AltFlags & 0x10)) || Session_00A8B238.GameMode) {
        vf_102(DAT_00A83D4C);
    } else if (Type->LightIntensity) {
        if (!LightSource) {
            LightSourceClass* light = new LightSourceClass(vf_18(), Type->LightVisibility, Type->LightIntensity, Type->LightRedTint, Type->LightGreenTint, Type->LightBlueTint);
            LightSource = light;
        }
        LightSource->Activate(0);
    }
    if (Type->bools_16A4[26] && !DAT_00A8E7AC && IsAlive && !InLimbo) {
        FUN_00452DC0(0);
        FUN_00452DC0(2);
        FUN_00452DC0(4);
        FUN_00452DC0(6);
        CreateEndPost(true);
    }
    if (!Owner->IsControlledByHuman()) {
        vf_102(Owner);
    }
    if (IsOwnedByCurrentPlayer) {
        DAT_00880CF4 = 1;
        DAT_0087F7E8.FUN_004F42F0(0);
    }
    if (Type->NaturalParticleSystem && !NaturalParticleSystem) {
        CoordStruct offset = Type->NaturalParticleSystemLocation;
        CoordStruct loc = Location;
        CoordStruct target;
        target.X = Location.X + offset.X;
        target.Y = Location.Y + offset.Y;
        target.Z = Location.Z + offset.Z;
        NaturalParticleSystem = new BA4Tracker(Type->NaturalParticleSystem, &target, DAT_0087F7E8.FUN_00565730(&loc), 0, &DAT_0089C848, 0);
    }
    if (Type == RulesInstance->WallTower) {
        CellStruct base = DAT_0087F7E8.FUN_00565730(where)->MapCoords;
        BA4At(base + BA4Off(1, 0))->FUN_00480630(0);
        BA4At(base + BA4Off(-1, 0))->FUN_00480630(0);
        BA4At(base + BA4Off(0, 1))->FUN_00480630(0);
        BA4At(base + BA4Off(0, -1))->FUN_00480630(0);
    }
    if (Type == RulesInstance->GDIGateOne || Type == RulesInstance->NodGateOne) {
        CellStruct base = DAT_0087F7E8.FUN_00565730(where)->MapCoords;
        BA4At(base + BA4Off(-1, 0))->FUN_00480630(0);
        BA4At(base + BA4Off(3, 0))->FUN_00480630(0);
    }
    if (Type == RulesInstance->GDIGateTwo || Type == RulesInstance->NodGateTwo) {
        CellStruct base = DAT_0087F7E8.FUN_00565730(where)->MapCoords;
        BA4At(base + BA4Off(0, -1))->FUN_00480630(0);
        BA4At(base + BA4Off(0, 3))->FUN_00480630(0);
    }
    if (Type->bools_154B[0]) {
        Spotlight = new BuildingLightClass(this);
    }
    IsPrimaryFactory = 0;
    if (Type->Factory) {
        FUN_00448070(0);
    }
    for (i = 0; i < RulesInstance->list_08AC.Count; i++) {
        if (RulesInstance->list_08AC.Items[i] == Type) {
            Owner->ConYards.AddItem(this);
            break;
        }
    }
    if (Type->bools_16A4[5]) {
        Owner->UnitRepairStations.AddItem(this);
    }
    if (Type->bools_16A4[9]) {
        Owner->Grinders.AddItem(this);
    }
    if (Type->bools_16A4[10] || Type->bools_16A4[11]) {
        Owner->Absorbers.AddItem(this);
    }
    if (Type->bools_16A4[7]) {
        Owner->Bunkers.AddItem(this);
    }
    if (Type->bools_1570[11] && Type->TechLevel > -1) {
        Owner->Occupiables.AddItem(this);
    }
    if (Type->bools_16A4[8]) {
        Owner->CloningVats.AddItem(this);
    }
    if (Type->bools_16A4[12]) {
        Owner->SecretLabs.AddItem(this);
    }
    if (Type->PsychicDetectionRadius > 0) {
        Owner->PsychicDetectionBuildings.AddItem(this);
    }
    if (Type->bools_16A4[41]) {
        Owner->FactoryPlants.AddItem(this);
        Owner->CalculateCostMultipliers();
    }
    Owner->Buildings.AddItem(this);
    if (!Owner->IsControlledByHuman()) {
        Owner->Base.FUN_0042F260(this);
    }
    if (Type->Factory) {
        Owner->Update_FactoriesQueues(Type->Factory, Type->Naval, 0);
    }
    return true;
refuse:
    return false;
}

#include "../_layout/techno_class.h"
#include "../_layout/anim_class.h"
#include "../_layout/warhead_type_class.h"
#include "../_layout/capture_manager_class.h"
#include "../combat/particles/system_class.h"
#include "../core/randomizer.h"
#include "house_building/building_a2_fold.h"

// Moved from building_a2_damage.cpp (the BA2 parallel view family is retired); written against the canonical
// BuildingClass, TechnoClass, ObjectClass, HouseClass, BuildingTypeClass, RulesClass and ScenarioClass.
// The animation-name refresh the original expanded twice: the health ratio against the rules threshold decides
// which of the two names of every damage-state animation slot is shown.
inline void BuildingClass::RefreshAnimStates()
{
    double ratio = FUN_005F5C60();
    bool low = ratio <= Rules->ConditionYellow;
    if (IsDamaged != low) {
        IsDamaged = low;
        for (int i = 0; i < 0x15; i++) {
            if (Anims[i]) {
                char* name = low ? Type->BuildingAnim[i].Damaged : Type->BuildingAnim[i].Anim;
                if (name && *name) {
                    PlayAnim(name, i, low, 0, 0);
                }
            }
        }
    }
}

// PARTIAL: 1.6% (unchanged from the BA2 view; 745 retail vs 751 compiled instructions, 12 retail-only and 16
// compiled-only by multiset, the positional score is low because of an early shift). Remaining delta: retail keeps the attacker in EBP and the zero constant in EBX (every null test is
// `cmp ebp,ebx`; ours tests EDI), the frame is 0x8C where ours is 0x80 (retail keeps four hidden-pointer coordinate
// results where canonical by-value slot 18 returns are copied), and the two expansions of the health-ratio refresh
// are cross-jumped in ours but duplicated in retail.
// FUNCTION: GAMEMD 0x442230
// Slot 91, ReceiveDamage: the base-class damage run decides the resulting damage state; this override adds
// the occupant bookkeeping and the destruction / state-change reactions on top. The slot keeps the base ABI
// (void* warhead / source / house): the typed pointers are locals.
int BuildingClass::vf_91(int* damage, int distance, void* warheadArg, void* sourceArg, bool ignoreDefenses,
                         bool preventsPassengerEscape, void* houseArg)
{
    WarheadTypeClass* warhead = static_cast<WarheadTypeClass*>(warheadArg);
    TechnoClass* attacker = static_cast<TechnoClass*>(sourceArg);
    HouseClass* sourceHouse = static_cast<HouseClass*>(houseArg);
    int result = 0;

    if (this == attacker && !attacker->vf_33()->DamageSelf) {
        return result;
    }
    FUN_005F5C60();
    int stateBefore = FUN_0043EF90();
    int i = 0;

    if (attacker && !vf_32()) {
        Owner->LATime = CurrentFrame;
        Owner->LAEnemy = attacker->vf_15()->ArrayIndex;
        FUN_00708080(attacker);
    }

    CellStruct* cells = static_cast<CellStruct*>(vf_66(0));
    BuildingBVector<TechnoClass> occupants(0, 0);
    for (; i < RadioLinks.Capacity; i++) {
        TechnoClass* occupant = FUN_0065AD30(i);
        if (occupant) {
            occupants.AddItem(occupant);
        }
    }

    if (Type->bools_16A4[27] && !ignoreDefenses) {
        return 0;
    }
    if (Type->bools_16A4[18] && Type->Immune) {
        return 0;
    }

    if (Health) {
        result = FUN_00701900(damage, distance, warhead, attacker, ignoreDefenses, preventsPassengerEscape, sourceHouse);
        if (!IsAlive) {
            return result;
        }
        switch (result) {
        case 5:
            return result;
        case 4:
            if (BunkerLinkedItem) {
                occupants.RemoveItem(BunkerLinkedItem);
                FUN_004593A0();
            }
            if (CaptureManager) {
                static_cast<CaptureManagerClass*>(CaptureManager)->FreeAll();
            }
            if (LocomotorTarget) {
                FUN_0070FEE0(1);
            }
            for (i = 0; i < occupants.Count; i++) {
                TechnoClass* occupant = occupants.Items[i];
                CoordStruct a, b, c;
                CoordStruct from = occupant->vf_18();
                CoordStruct to = vf_18();
                CoordStruct delta = *c.FUN_0041C230(to.X - from.X, to.Y - from.Y, to.Z - from.Z);
                if (delta.FUN_0041C380() >= 256 && !Type->bools_16A4[39]) {
                    vf_158(0x17, occupant);
                    occupant->QueueUpToEnter = 0;
                } else {
                    int hurt = occupant->vf_33()->Strength * 10;
                    occupant->vf_91(&hurt, 0, Rules->C4Warhead, 0, true, true, 0);
                }
            }
            {
                int capacity = occupants.Capacity;
                occupants.Clear();
                occupants.SetCapacity(capacity, 0);
            }
            if (Type->bools_1570[11]) {
                FUN_00457DE0(0, 0);
            }
            if (LightSource) {
                LightSource->Deactivate(0);
            }
            vf_315(0, reinterpret_cast<int>(attacker), ignoreDefenses, reinterpret_cast<int>(cells));
            {
                int left = C4Timer.TimeLeft;
                if (C4Timer.StartTime != -1) {
                    int elapsed = CurrentFrame - C4Timer.StartTime;
                    if (elapsed >= left) {
                        break;
                    }
                    left -= elapsed;
                }
                if (left > 0) {
                    vf_62();
                    FUN_00441F60();
                }
            }
            break;
        case 2:
            if (NaturalParticleSystem) {
                static_cast<ParticleSystemClass*>(NaturalParticleSystem)->unknown_E8 = static_cast<ParticleSystemClass*>(NaturalParticleSystem)->unknown_E8 * 1.5f;
            }
            // fall through
        case 3:
            if (vf_33()->DamageSound == -1) {
                CoordStruct where = Location;
                FUN_00750E20(Rules->BuildingDamageSound, &where, 0);
            }
            while (!(cells->X == 0x7FFF && cells->Y == 0x7FFF)) {
                CellStruct offset = *cells++;
                CellStruct here = vf_110();
                CoordStruct pos;
                pos.X = (short)(offset.X + here.X) * 256 + 128;
                pos.Y = (short)(offset.Y + here.Y) * 256 + 128;
                pos.Z = 0;
                pos.Z = DAT_0087F7E8.FUN_00578080(&pos);
                if (!warhead->Sparky) {
                    continue;
                }
                int rows = Type->GetFoundationHeight(false);
                switch (DAT_00A8B230->unknown_0218.RandomRanged(0, rows + Type->GetFoundationWidth() + 5)) {
                case 1:
                case 2:
                case 3:
                case 4:
                case 5:
                    {
                        CoordStruct scatter;
                        AnimClass* anim = new AnimClass(const_cast<AnimTypeClass*>(Rules->list_0B74.Items[0]),
                                                        *FUN_0049F420(&scatter, &pos, 0x60, 0), 0,
                                                        DAT_00A8B230->unknown_0218.RandomRanged(1, 3), 0x600, 0, 0);
                        if (anim) {
                            anim->FUN_00424B50(this);
                        }
                    }
                    break;
                case 6:
                case 7:
                case 8:
                    {
                        CoordStruct scatter;
                        AnimClass* anim = new AnimClass(const_cast<AnimTypeClass*>(Rules->list_0B74.Items[1]),
                                                        *FUN_0049F420(&scatter, &pos, 0x60, 0), 0,
                                                        DAT_00A8B230->unknown_0218.RandomRanged(1, 3), 0x600, 0, 0);
                        if (anim) {
                            anim->FUN_00424B50(this);
                        }
                    }
                    break;
                case 9:
                    {
                        CoordStruct scatter;
                        AnimClass* anim = new AnimClass(const_cast<AnimTypeClass*>(Rules->list_0B74.Items[2]),
                                                        *FUN_0049F420(&scatter, &pos, 0x60, 0), 0, 1, 0x600, 0, 0);
                        if (anim) {
                            anim->FUN_00424B50(this);
                        }
                    }
                    break;
                }
            }
            break;
        }
    }

    if (!IsAlive) {
        return 4;
    }
    if (attacker) {
        if (result) {
            if (!Type->Insignificant && !vf_32()) {
                Owner->FUN_004F93E0(this);
            }
            OwnerCountryIndex = attacker->vf_15()->ArrayIndex;
            if (CurrentMission != 0x13 && !Owner->FUN_004F9A90(attacker) && vf_254(0)->WeaponType
                && !vf_254(0)->WeaponType->Projectile->unknown_2A4 && (!Target || !vf_235(Target))) {
                if (attacker->vf_11() == 2 || (Owner->IsControlledByHuman() && !Rules->PlayerReturnFire)) {
                    if (!PrimaryFacing.IsRotating() && vf_212()) {
                        DirStruct dir;
                        dir.Raw = 0;
                        dir.Raw = (unsigned short)(DAT_00A8B230->unknown_0218.Random() << 8);
                        PrimaryFacing.SetDesired(dir);
                    }
                } else {
                    vf_242(attacker);
                }
            }
        }
    }
    if (result) {
        RefreshAnimStates();
    }
    if (stateBefore != FUN_0043EF90()) {
        NeedsRedraw = 1;
        RefreshAnimStates();
    }
    return result;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x442C40
// CAPPED at 86.5% (multiset identical). Delta: retail loads the AddItem vptr before the capacity sum and uses EDX
// for the type value; AddItem written as cap-local, member-reload and nested forms (86.5/84.3/77.5%).
void BuildingClass::vf_9()
{
    TechnoClass::vf_9();
    if (Owner) {
        OwnerCountryIndex = Owner->Type->ArrayIndex2;
        Owner->FUN_004FF700(this);
    }
    if (Type) {
        EstimatedHealth = Health = Type->Strength;
        int v = Type->InitialAmmo;
        if (v == -1) {
            v = Type->Ammo;
        }
        Ammo = v;
        PrimaryFacing.FUN_004C9680(Type->ROT);
        if (!Type->vf_48()) {
            AI_Sellable = 0;
        } else {
            Type->ClearBuildUp();
            HasBuildUp = 1;
        }
        if (Owner && Owner->WarFactoryInfiltrated && !Type->Naval && Type->bools_C8C[2] && Type->UndeploysInto) {
            Veterancy.FUN_00750090(1);
        }
    }
    if (Type && Type->bools_16A4[0x16B0 - 0x16A4]) {
        DAT_008B41E0.AddItem(this);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4436F0
bool BuildingClass::vf_80(int mode, CellStruct* cell, int a3, int a4)
{
    if (mode == 5) {
        vf_222(1, DAT_0087F7E8.FUN_005657A0(cell), 0, 0);
    } else if (mode == 6 || mode == 1) {
        bool blocked = false;
        if (!Type->bools_16A4[0x16B9 - 0x16A4]
            || (Owner->IsControlledByHuman() && Session_00A8B238.GameMode && Session_00A8B238.unknown_18.MCVRedeploy && MindControlledBy == 0)) {
            if (Type->UndeploysInto != 0 || vf_161()) {
                FUN_00443860(cell, 1);
            }
        } else {
            blocked = true;
        }
        if (Type->UndeploysInto != 0 && !blocked) {
            TargetClass targetBuf;
            DAT_00A802C8.Add(EventClass(vf_14(), 0x16, *targetBuf.FUN_006E6AB0(this)));
        }
    }
    return true;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x443B90
// CAPPED at 17.1%. Retail places the Base(0) fallback inline right after the first two tests and jumps back
// to it from the later failures; the three shapes tried (target=0 else-if, if/else with a trailing call, early
// returns) all put that block last. Instruction multiset differs by one jcc sense.
void BuildingClass::vf_242(AbstractClass* target)
{
    if (CurrentMission != 0x13 && vf_212()) {
        if (target && vf_254(0)->WeaponType && !vf_254(0)->WeaponType->Projectile->unknown_2A4 && !IsCloseEnoughToAttack(target)) {
            TechnoClass::vf_242(0);
            if (Type->bools_16A4[0x16C4 - 0x16A4] || Type->bools_16A4[0x16CA - 0x16A4]) {
                if (!Owner->IsControlledByHuman() && !IsUnderEMP()) {
                    vf_122(0x13, 0);
                    vf_123();
                }
            }
            return;
        }
    } else {
        target = 0;
    }
    TechnoClass::vf_242(target);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4456D0
void BuildingClass::vf_312()
{
    int i;
    if (Owner == DAT_00A83D4C && !InLimbo && DiscoveredByCurrentPlayer && HasPower) {
        switch (Type->Factory) {
        case 7:
            for (i = 0; i < DAT_00A83C68.Count; i++) {
                if (DAT_00A83D4C->FUN_004F7870(DAT_00A83C68.Items[i], 0, 1)) {
                    DAT_0087F7E8.FUN_006A6300(7, i);
                }
            }
            break;
        case 0x28:
            for (i = 0; i < DAT_00A83CE0.Count; i++) {
                if (DAT_00A83D4C->FUN_004F7870(DAT_00A83CE0.Items[i], 0, 1)) {
                    DAT_0087F7E8.FUN_006A6300(0x28, i);
                }
            }
            break;
        case 0x10:
            for (i = 0; i < DAT_00A8E348.Count; i++) {
                if (DAT_00A83D4C->FUN_004F7870(DAT_00A8E348.Items[i], 0, 1)) {
                    DAT_0087F7E8.FUN_006A6300(0x10, i);
                }
            }
            break;
        case 3:
            for (i = 0; i < DAT_00A8B218.Count; i++) {
                if (DAT_00A83D4C->FUN_004F7870(DAT_00A8B218.Items[i], 0, 1)) {
                    DAT_0087F7E8.FUN_006A6300(3, i);
                }
            }
            break;
        }
    }
}


// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x445880
bool BuildingClass::vf_53()
{
    int i;
    bool result;
    bool anyUpgradeFlag = false;
    CoordStruct coord = Location;
    CellStruct cell;
    cell.X = (short)(coord.X / 256);
    cell.Y = (short)(coord.Y / 256);

    if (!InLimbo && Type != 0) {
        for (i = 0; i < 8; i++) {
            if (DamageFireAnims[i]) {
                DamageFireAnims[i]->vf_62();
                DamageFireAnims[i] = 0;
            }
        }
        if (Type->bools_16A4[40] && ActuallyPlacedOnMap) {
            Owner->NumOrePurifiers--;
            if (Owner->NumOrePurifiers < 0) {
                Owner->NumOrePurifiers = 0;
            }
        }
        if (Type->bools_16A4[39] && ActuallyPlacedOnMap) {
            Owner->AirportDocks -= Type->NumberOfDocks;
            if (Owner->AirportDocks < 0) {
                Owner->AirportDocks = 0;
            }
        }
        if (Type->InfantryGainSelfHeal && ActuallyPlacedOnMap) {
            Owner->InfantrySelfHeal -= Type->InfantryGainSelfHeal;
            if (Owner->InfantrySelfHeal < 0) {
                Owner->InfantrySelfHeal = 0;
            }
        }
        if (Type->UnitsGainSelfHeal && ActuallyPlacedOnMap) {
            Owner->UnitsSelfHeal -= Type->UnitsGainSelfHeal;
            if (Owner->UnitsSelfHeal < 0) {
                Owner->UnitsSelfHeal = 0;
            }
        }
        if (Type->bools_16A4[26]) {
            FUN_00452A40(0);
        }
        if (!DAT_00A8E7AC) {
            if (Type->bools_16A4[36]) {
                vf_318(DAT_0089C818.raw_dword);
            }
            if (Type->bools_D20[17]) {
                vf_320(DAT_0089C818.raw_dword);
            }
            if ((!Type->UndeploysInto || !Type->ResourceGatherer) && !vf_32()) {
                FUN_004561F0();
            }
        }
        for (i = 0; i < 3; i++) {
            if (Upgrades[i] && Upgrades[i]->bools_1760[3]) {
                anyUpgradeFlag = true;
                break;
            }
        }
        if (!DAT_00A8E9A0) {
            if (Type->bools_16A4[26] && !DAT_00A8E7AC) {
                LaserFenceFrame = 0;
            }
            return true;
        }
        if (Type == RulesInstance->WallTower) {
            for (i = 0; i < 8; i += 2) {
                CellClass* mc = BA4At(cell + DAT_0089F688[i & 7]);
                mc->FUN_00480630(0);
                if (mc->OverlayTypeIndex != -1 && DAT_00A83D84[mc->OverlayTypeIndex]->Wall && mc->OverlayData < 0x10) {
                    mc->FUN_00480CB0(200);
                }
            }
        }
        if (Type == RulesInstance->GDIGateOne || Type == RulesInstance->NodGateOne) {
            BA4At(cell + BA4Off(-1, 0))->FUN_00480630(0);
            BA4At(cell + BA4Off(3, 0))->FUN_00480630(0);
        }
        if (Type == RulesInstance->GDIGateTwo || Type == RulesInstance->NodGateTwo) {
            BA4At(cell + BA4Off(0, -1))->FUN_00480630(0);
            BA4At(cell + BA4Off(0, 3))->FUN_00480630(0);
        }
        if (!Type->ToTile) {
            int width = Type->GetFoundationWidth();
            int height = Type->GetFoundationHeight(false);
            CellStruct scratch = vf_110();
            CellStruct origin = scratch;
            for (int y = 0; y < height + 2; y++) {
                CellStruct corner = origin + BA4Off(-1, -1);
                for (i = 0; i < width + 2; i++) {
                    BA4At(corner + BA4Off(i, y))->BlockedNeighbours--;
                }
            }
        }
        if (DAT_00887324) {
            RectangleStruct buf = vf_75();
            DAT_00887324->FUN_006D2790(buf, false);
        }
        if (Spotlight) {
            Spotlight->vf_62();
        }
        Owner->FUN_004FF980(this);
        Owner->RecheckTechTree = 1;
        Owner->FUN_004FD150();
        if (Owner == DAT_00A83D4C) {
            DAT_00880CF4 = 1;
            DAT_0087F7E8.FUN_004F42F0(0);
        }
        Owner->FUN_0050A490(this);
    }
    result = TechnoClass::vf_53();
    if (anyUpgradeFlag) {
        Owner->AcquiredThreatNode();
    }
    if (Type->Factory) {
        Owner->Update_FactoriesQueues(Type->Factory, Type->Naval, 0);
    }
    if (Type->bools_16A4[26] && !DAT_00A8E7AC) {
        LaserFenceFrame = 0;
    }
    return result;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x445E50
//
// The facing towards the target (or the current facing without one). The two X differences are kept in
// integer temporaries of their own (the frame is 0x20 bytes only with them), the angle callee takes the
// Y difference first and the X difference second, and the result is a 16-bit direction.
DirStruct BuildingClass::vf_170()
{
    if (!vf_255() && Target) {
        return DirectionTo(vf_18(), Target->vf_18());
    }
    return PrimaryFacing.FUN_004C93D0();
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x445F00
AbstractClass* BuildingClass::vf_241(unsigned int threat, CoordStruct* coord, bool a3)
{
    if (vf_254(0)->WeaponType != 0) {
        threat |= FUN_00772A90(vf_254(0)->WeaponType);
    }
    if (vf_254(1)->WeaponType != 0) {
        threat |= FUN_00772A90(vf_254(1)->WeaponType);
    }
    return TechnoClass::vf_241(threat | 1, coord, a3);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x446FF0
void BuildingClass::vf_103(int mode)
{
    switch (mode) {
    case -1:
        IsBeingRepaired = IsBeingRepaired == 0;
        break;
    case 0:
        if (!IsBeingRepaired) {
            return;
        }
        IsBeingRepaired = 0;
        break;
    case 1:
        if (IsBeingRepaired) {
            return;
        }
        IsBeingRepaired = 1;
        break;
    }
    int sound;
    if (IsBeingRepaired) {
        if (Health == Type->Strength) {
            sound = RulesInstance->ScoldSound;
        } else {
            sound = RulesInstance->GenericClick;
            if (Owner->IsControlledByCurrentPlayer()) {
                vf_82(7);
            }
            NeedsRepairs = 1;
            if (Owner->IsControlledByCurrentPlayer()) {
                FUN_00752700(s_EVA_Repairing_00818F18, -1, -1);
            }
        }
    } else {
        sound = RulesInstance->GenericClick;
    }
    if (Owner->IsControlledByCurrentPlayer()) {
        CoordStruct where = Location;
        FUN_007509E0(sound, &where, 0);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x447110
//
// CAPPED (see the report): retail is a three-case switch on the mode whose "nothing to do" exits jump to the
// shared epilogue, which no switch/return/flag formulation tried here reproduces; the first-written
// if-chain form below scores best.
void BuildingClass::vf_104(int mode)
{
    if (!HasBuildUp) {
        if (Type->bools_16A4[0x16C0 - 0x16A4]) {
            Type->vf_33(Owner);
            Owner->IsControlledByHuman();
            vf_53();
            vf_62();
        }
        return;
    }
    bool act;
    if (mode == -1) {
        act = vf_97() != 0x13;
    } else if (mode == 0) {
        if (vf_97() != 0x13) {
            return;
        }
        act = false;
    } else if (mode == 1) {
        if (vf_97() == 0x13 || C4Applied) {
            return;
        }
        act = true;
    } else {
        act = false;
    }
    if (act) {
        vf_122(0x13, 0);
        vf_123();
    }
    if (Owner->IsControlledByCurrentPlayer()) {
        VocClass::PlayGlobal(RulesInstance->GenericClick, 1.0f, 0x2000, 0);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x447210
// CAPPED at 3.3% (first transcription, two forms). Delta: retail pushes EDI after the early returns and has a 0xc frame;
// the same register-lifetime effect as vf_80 but in the other direction.
int BuildingClass::vf_29(ObjectClass* obj, char flag)
{
    int r;
    if (Type->bools_1700[1]) {
        return 0;
    }
    if (obj->vf_11() == 6 && ((BuildingClass*)obj)->Type->bools_1700[1]) {
        return 0;
    }
    r = FUN_006FFEC0(obj, flag);
    if (r == 8) {
        return 8;
    }
    if (r == 4) {
        if (Type->GapGenerator && DAT_00A83D4C == Owner) {
            if (!GapSuperCharged) {
                if (Owner->IHouse_vf_08() - Owner->vf_09() <= Type->ExtraPowerDrain) {
                    r = 0;
                    return r;
                }
            }
        } else if (!((Type->bools_16A4[0x16AE - 0x16A4] || Type->bools_16A4[0x16AF - 0x16A4]) && Passengers.NumPassengers > 0)) {
            if (vf_258() <= 0 && Type->Factory == 0) {
                r = 0;
                return r;
            }
        }
        r = 4;
        if (Type->Factory != 0 && IsPrimaryFactory) {
            r = 0;
        }
        return r;
    }
    if (r == 5) {
        if (vf_254(0)->WeaponType == 0) {
            goto checkTarget;
        }
        if (!vf_254(0)->WeaponType->Projectile->unknown_2A5 || Type->bools_16A4[0x16C3 - 0x16A4]) {
            r = 0;
        }
        if (CurrentMission == 0x13) {
            r = 0;
            return r;
        }
    }
    if (r == 1 || r == 2) {
        if (!vf_40()) {
            r = 7;
            return r;
        }
        int kind = Type->Factory;
        if (kind == 0x10 || kind == 0x28 || kind == 3) {
            if (!DAT_0087F770->FUN_0054F5C0(DAT_00A8EBF8) && !DAT_0087F770->FUN_0054F5C0(DAT_00A8EBFC)) {
                r = 7;
                return r;
            }
            const CoordStruct& tmp = obj->vf_18();
            CellStruct cell;
            cell.X = (short)(tmp.X / 256);
            cell.Y = (short)(tmp.Y / 256);
            CellStruct cellCopy = cell;
            if (Type->Factory != 3) {
                CoordStruct where;
                where.X = (cell.X << 8) + 0x80;
                where.Y = (cell.Y << 8) + 0x80;
                where.Z = 0;
                if (!vf_179(&where)) {
                    r = 2;
                }
                if (!(DAT_0087F7E8.FUN_005657A0(&cellCopy)->Flags & 0x100)
                    && DAT_0087F7E8.FUN_005657A0(&cellCopy)->Passability != 0) {
                    r = 2;
                    return r;
                }
            }
        }
    }
    if (r != 5) {
        return r;
    }
checkTarget:
    if (obj->vf_34()->Immune) {
        r = 2;
    }
    return r;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x447540
// CAPPED at 42.2%. Delta: retail keeps one separate "xor ebx,ebx; jmp done" per exit and a flat r==1||r==2 test; goto, else-if and split forms all give the same 42.2%.
int BuildingClass::vf_28(CellStruct* cell, char a, char b)
{
    int r;
    if (Type->bools_1700[1]) {
        return 0;
    }
    if (Type->UndeploysInto != 0 && a != 0) {
        r = TechnoClass::vf_28(cell, 0, b);
        if (!DAT_0087F7E8.IsLocationShrouded(DAT_0087F7E8.FUN_005657A0(cell)->vf_18())
            && r == 1
            && DAT_0087F7E8.FUN_005657A0(cell)->LandType == 5
            && Type->ResourceDestination && Type->ResourceGatherer) {
            return 6;
        }
    } else {
        r = TechnoClass::vf_28(cell, a, b);
    }
    if (r == 1 || r == 2) {
        if (!vf_40() && r == 1) {
            r = 0;
            goto done;
        }
        if (vf_161()) {
            if (!DAT_0087F770->FUN_0054F5C0(DAT_00A8EBF8) && !DAT_0087F770->FUN_0054F5C0(DAT_00A8EBFC)) {
                r = 0;
                goto done;
            }
            if (Type->Factory != 3) {
                CoordStruct where;
                where.Z = 0;
                where.X = (cell->X << 8) + 0x80;
                where.Y = (cell->Y << 8) + 0x80;
                if (!vf_179(&where)) {
                    r = 2;
                }
                if (!(DAT_0087F7E8.FUN_005657A0(cell)->Flags & 0x100)
                    && DAT_0087F7E8.FUN_005657A0(cell)->Passability != 0) {
                    r = 2;
                    goto done;
                }
            }
        }
    }
    if (r == 5) {
        if (vf_254(0)->WeaponType == 0) {
            return r;
        }
        if (!vf_254(0)->WeaponType->Projectile->unknown_2A5 || Type->bools_16A4[0x16C3 - 0x16A4]) {
            r = 0;
        }
        if (CurrentMission == 0x13) {
            r = 0;
        } else if (r == 5) {
            return r;
        }
    }
done:
    if (vf_161() && Owner->IsControlledByCurrentPlayer()) {
        r = 1;
    }
    return r;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x447AC0
CoordStruct BuildingClass::vf_18()
{
    int height = Type->GetFoundationHeight(false) * 128 - 128;
    int width = Type->GetFoundationWidth() * 128 - 128;

    CoordStruct c = Location;

    CoordStruct temp;
    temp.X = width + c.X;
    temp.Y = height + c.Y;
    temp.Z = c.Z;
    return temp;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x447B20
// CAPPED at 5.3%. Delta: retail keeps a 0x34 frame with a dead Location copy (Z=0, X, Y stores) and shares one
// epilogue; early-return, single-result and per-block-temporary forms tried.
CoordStruct BuildingClass::vf_42(AbstractClass* arg)
{
    CoordStruct r;
    if (Type->bools_16A4[0x16BC - 0x16A4]) {
        CellStruct c = vf_110();
        CellStruct shifted;
        shifted.X = c.X + 2;
        shifted.Y = c.Y + 1;
        r.X = (shifted.X << 8) + 0x80;
        r.Y = (shifted.Y << 8) + 0x80;
        r.Z = Location.Z;
        return r;
    }
    if (Type->bools_16A4[0x16BB - 0x16A4]) {
        const CoordStruct& p = ObjectClass::vf_42(arg);
        r.X = p.X + 0x80;
        r.Y = p.Y;
        r.Z = p.Z;
        return r;
    }
    if (Type->bools_16A4[0x16AB - 0x16A4] && arg) {
        const CoordStruct& pa = arg->vf_18();
        const CoordStruct& pb = vf_18();
        int bx = pb.X;
        int ax = pa.X;
        DirStruct d;
        d.Raw = (short)((FUN_004CAE30((double)pb.Y - pa.Y, (double)ax - bx) - DAT_007E2820) * DAT_007E2818);
        int dir = ((d.Whole >> 7) + 1 >> 1) & 0xFF;
        const CoordStruct& pc = vf_18();
        if (dir >= 0 && dir < 0x40) {
            r.X = pc.X + 0x80;
            r.Y = pc.Y - 0x80;
        } else if (dir >= 0x40 && dir < 0x80) {
            r.X = pc.X + 0x80;
            r.Y = pc.Y + 0x80;
        } else if (dir >= 0x80 && dir < 0xC0) {
            r.X = pc.X - 0x80;
            r.Y = pc.Y + 0x80;
        } else {
            r.X = pc.X - 0x80;
            r.Y = pc.Y - 0x80;
        }
        r.Z = pc.Z;
        return r;
    }
    if (!Type->bools_16A4[0x16CB - 0x16A4] && !Type->bools_16A4[0x16A9 - 0x16A4]) {
        return ObjectClass::vf_42(arg);
    }
    switch (Type->NumberOfDocks) {
    case 0:
        return vf_18();
    case 1: {
        const CoordStruct& pc = vf_18();
        CoordStruct* off = Type->DockingOffsets.Items;
        r.X = off->X + pc.X;
        r.Y = off->Y + pc.Y;
        r.Z = off->Z + pc.Z;
        return r;
    }
    default: {
        int idx = FindLinkIndex(arg);
        if (idx >= 0 && idx < Type->NumberOfDocks) {
            CoordStruct* off = &Type->DockingOffsets.Items[idx];
            const CoordStruct& pc = vf_18();
            r.X = off->X + pc.X;
            r.Y = off->Y + pc.Y;
            r.Z = off->Z + pc.Z;
            return r;
        }
        return vf_18();
    }
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x447E00
//
// The straight-line distance to a target. CAPPED at 75.9% (instruction multiset identical): retail keeps
// the Y difference alone in a stack slot, converts it first and has a 0x24-byte frame; the variants tried
// (named differences, doubles, the inline square helper in three operand orders) all give 0x20.
int BuildingClass::vf_310(AbstractClass* target)
{
    return Distance(vf_42(target), target->vf_18());
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x447E90
CoordStruct BuildingClass::vf_19(AbstractClass* arg)
{
    if (Type->bools_16A4[0x16CB - 0x16A4]) {
        return vf_42(arg);
    }
    if (!Type->bools_16A4[0x16A9 - 0x16A4] && !Type->bools_16A4[0x16AB - 0x16A4]) {
        return vf_18();
    }
    return vf_42(arg);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x447F10
//
// CAPPED at 91.0% (instruction multiset identical): retail takes the absolute value of the quantised limit
// before the absolute value of the facing difference; every operand order tried evaluates them the other way.
int BuildingClass::vf_240(AbstractClass* target, int b, int c)
{
    if (!Type->bools_1570[0x157B - 0x1570] || (Type->bools_1570[0x157C - 0x1570] && vf_258())) {
        if (!IsBeingDrained()) {
            if (Type->bools_16A4[0x16C3 - 0x16A4]) {
                return 6;
            }
            if (vf_97() != 0x13 && vf_97() != 0x12) {
                if (!vf_212()) {
                    return 6;
                }
                if (DelayBeforeFiring) {
                    return 3;
                }
                int r = TechnoClass::vf_240(target, b, c);
                if (r == 0 && vf_255()) {
                    DirStruct want = vf_314(target);
                    int quant = Type->bools_16A4[0x16C5 - 0x16A4] ? 0 : 8;
                    short diff = PrimaryFacing.FUN_004C93D0().Raw;
                    diff -= want.Raw;
                    if (abs((short)(quant << 8)) < abs(diff)) {
                        return 2;
                    }
                }
                return r;
            }
        }
    }
    return 5;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x448160
// CAPPED at 81.7% (multiset identical). Delta: retail keeps the type pointer in EAX and the kind in ECX; the
// kind-first and result-first orders both allocate the other way.
char BuildingClass::vf_316()
{
    int kind = Type->Factory;
    char r = IsPrimaryFactory;
    if (kind != 0) {
        if (r) {
            IsPrimaryFactory = 0;
        } else {
            int i = 0;
            int count = Owner->Buildings.Count;
            if (count > 0) {
                do {
                    BuildingClass* other = Owner->Buildings.Items[i];
                    if (!other->InLimbo) {
                        BuildingTypeClass* ot = other->Type;
                        if (ot->Factory == Type->Factory) {
                            if ((Type->Naval && ot->Naval) || (!Type->Naval && !ot->Naval)) {
                                other->IsPrimaryFactory = 0;
                            }
                        }
                    }
                    i++;
                } while (i < count);
            }
            IsPrimaryFactory = 1;
            if (Owner->IsControlledByCurrentPlayer()) {
                FUN_00752700(s_EVA_PrimaryBuildingSelected_00818F28, -1, -1);
            }
            if (Type->Factory == 7) {
                Owner->FUN_0050DB00(this);
            }
        }
        vf_73(2);
        r = IsPrimaryFactory;
    }
    return r;
}

#include "../_layout/bomb_class.h"

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x448260
bool BuildingClass::vf_245(HouseClass* newOwner, bool announce)
{
    int i;

    if (newOwner != Owner) {        if (AttachedBomb && !Type->bools_1570[11]) {
            AttachedBomb->Disarm();
        }
        if (Type->bools_16A4[35]) {
            newOwner->HasCloakingRanges = 1;
        }
        if (Owner->Type->MultiplayPassive && Type->ProduceCashStartup) {
            newOwner->GiveMoney(Type->ProduceCashStartup);
            CashProductionTimer = CDTimerClass(Type->ProduceCashDelay);
        }
        unsigned int bit = 1 << (newOwner->Type->ArrayIndex2);
        if ((bit & DisplayProductionTo) != 0) {
            DisplayProductionTo = DisplayProductionTo - bit;
            if (Type->bools_16A4) {
                Owner->RadarVisibleTo = 0;
                int count = Owner->Buildings.Count;
            for (i = 0; i < count; i++) {
                    BuildingClass* b = Owner->Buildings.Items[i];
                    if (b && !b->InLimbo && b->Type->bools_16A4) {
                        Owner->RadarVisibleTo |= b->DisplayProductionTo;
                    }
                }
                DAT_0087F7E8.FUN_004F42F0(2);
            }
        }
        IsPrimaryFactory = 0;
        if (Type->bools_16A4[26]) {
            FUN_00452A40(0);
        }
        if (Owner->IsControlledByCurrentPlayer() || newOwner->IsControlledByCurrentPlayer()) {
            if (!newOwner->Type->MultiplayPassive && announce) {
                if (Type->bools_154B[7]) {
                    if (Owner != newOwner) {
                        if (Owner->IsControlledByCurrentPlayer()) {
                            FUN_00752700(s_EVA_TechBuildingLost_00818FC4, -1, -1);
                        }
                        if (newOwner->IsControlledByCurrentPlayer() && newOwner->IsControlledByCurrentPlayer() && Type->CaptureEvaEvent != -1) {
                            FUN_00752480(Type->CaptureEvaEvent, -1, -1);
                        }
                    }
                } else {
                    if (FUN_0065FA70(10, vf_110())) {
                        FUN_00752700(s_EVA_BuildingCaptured_00818FAC, -1, -1);
                    }
                }
            }
            DAT_00880CF4 = 1;
            DAT_0087F7E8.FUN_004F42F0(0);
        }
        NeedsRedraw = 1;
        HasEngineer = 1;
        if (Type->bools_154B[7]) {
            StuffEnabled = 1;
            if (LightSource) {
                LightSource->Activate(0);
            }
            if (Type->bools_16A4[26]) {
                CreateEndPost(false);
            }
            for (int k = 0; k < 21; k++) {
                if (Type->BuildingAnim[k].Powered && Anims[k]) {
                    Anims[k]->FUN_00425270();
                }
            }
        }
        if (Session_00A8B238.GameMode == 4 && !vf_33()->bools_C8C[19]) {
            newOwner->CapturedBuildings.IncrementUnitTotal(Type->ArrayIndex);
        }

        BA4HeldList held;
        for (i = 0; i < RadioLinks.Capacity; i++) {
            TechnoClass* object = FUN_0065AD30(i);
            if (object) {
                if (!object->Flags.IsFoot) {
                    object = 0;
                } else if (vf_158(0x13, object) == 1) {
                    bool inRange = false;
                    if (!Type->bools_16A4[25]) {
                        CoordStruct a = vf_42(object);
                        CoordStruct b = object->vf_18();
                        CoordStruct scratchC;
                        CoordStruct diff = *scratchC.FUN_0041C230(b.X - a.X, b.Y - a.Y, b.Z - a.Z);
                        inRange = diff.FUN_0041C380() < 0x40;
                    } else {
                        inRange = true;
                    }
                    if (inRange) {
                        unsigned char flag = object->IsTether;
                        object->vf_245(newOwner, 1);
                        BA4Held* entry = new BA4Held(object, flag);
                        held.AddItem(entry);
                        continue;
                    }
                    vf_158(0x17, object);
                    vf_158(3, object);
                    continue;
                }
                vf_158(0x17, object);
                vf_158(3, object);
            }
        }
        if (Factory) {
            Factory->AbandonProduction();
            if (Factory) {
                delete Factory;
            }
            Factory = 0;
        }
        Owner->FUN_004FF980(this);
        HouseClass* oldOwner = Owner;
        BA4TargetRef target;
        target.FUN_006E6AB0(this);
        HasBeenCaptured = 1;

        for (i = 0; i < RulesInstance->list_08AC.Count; i++) {
            if (RulesInstance->list_08AC.Items[i] == Type) {
                oldOwner->ConYards.RemoveItem(this);
                break;
            }
        }
        if (Type->bools_16A4[5]) {
            oldOwner->UnitRepairStations.RemoveItem(this);
        }
        if (Type->bools_16A4[9]) {
            oldOwner->Grinders.RemoveItem(this);
        }
        if (Type->bools_16A4[10] || Type->bools_16A4[11]) {
            oldOwner->Absorbers.RemoveItem(this);
        }
        if (Type->bools_16A4[7]) {
            oldOwner->Bunkers.RemoveItem(this);
        }
        if (Type->bools_1570[11] && Type->TechLevel > -1) {
            oldOwner->Occupiables.RemoveItem(this);
        }
        if (Type->bools_16A4[8]) {
            oldOwner->CloningVats.RemoveItem(this);
        }
        if (Type->bools_16A4[12]) {
            oldOwner->SecretLabs.RemoveItem(this);
        }
        if (Type->PsychicDetectionRadius > 0) {
            oldOwner->PsychicDetectionBuildings.RemoveItem(this);
        }
        if (Type->bools_16A4[41]) {
            oldOwner->FactoryPlants.RemoveItem(this);
            oldOwner->CalculateCostMultipliers();
        }
        oldOwner->Buildings.RemoveItem(this);
        if (Type->bools_16A4[40]) {
            oldOwner->NumOrePurifiers--;
        }
        if (Type->InfantryGainSelfHeal && ActuallyPlacedOnMap) {
            Owner->InfantrySelfHeal -= Type->InfantryGainSelfHeal;
            if (Owner->InfantrySelfHeal < 0) {
                Owner->InfantrySelfHeal = 0;
            }
        }
        if (Type->UnitsGainSelfHeal && ActuallyPlacedOnMap) {
            Owner->UnitsSelfHeal -= Type->UnitsGainSelfHeal;
            if (Owner->UnitsSelfHeal < 0) {
                Owner->UnitsSelfHeal = 0;
            }
        }
        if (Type->bools_16A4[39]) {
            oldOwner->AirportDocks -= Type->NumberOfDocks;
        }
        if (Type->bools_16A4[35]) {
            HasCloakingData = 0xFF;
            if (!CloakRadius) {
                CloakRadius = Type->CloakRadiusInCells;
            }
            NeedsRedraw = 1;
            CloakRadius = 1;
            vf_260(1);
        }
        if (Type->GapGenerator) {
            vf_262();
        }
        vf_291(0, 0, 0, 0);
        TechnoClass::vf_245(newOwner, true);
        if (Type->bools_16A4[35] && vf_212() && Type->bools_16A4[35]) {
            HasCloakingData = 1;
            if (CloakRadius == Type->CloakRadiusInCells) {
                CloakRadius = 0;
            }
            NeedsRedraw = 1;
        }
        if (Type->GapGenerator && vf_212()) {
            vf_261();
        }
        FUN_00448070(0);
        oldOwner->ToCapture = this;
        oldOwner->FUN_004FD150();
        Owner->FUN_004FD150();
        if (Owner->ToCapture == this) {
            Owner->ToCapture = 0;
        }
        if (oldOwner->IsControlledByCurrentPlayer() && Type->bools_16A4[21]) {
            DAT_0088098C = 0;
            DAT_00880990 = 0;
            DAT_00880994 = -1;
            DAT_0087F7E8.FUN_004A8BF0(0);
        }
        Owner->FUN_004FFA50(this);
        IsBeingRepaired = 0;
        vf_311(1);
        if (Type->bools_16A4[26] && !DAT_00A8E7AC) {
            if (IsAlive && !InLimbo) {
                FUN_00452DC0(0);
                FUN_00452DC0(2);
                FUN_00452DC0(4);
                FUN_00452DC0(6);
                CreateEndPost(true);
                if (DAT_00A8E7AC) {
                    goto afterFacing;
                }
            }
            if (Type->bools_16A4[26]) {
                LaserFenceFrame = 0;
            }
        }
    afterFacing:
        if (Owner->IsControlledByCurrentPlayer()) {
            vf_290(0, 0, 0, 0, 0);
            DAT_0087F7E8.FUN_004F42F0(1);
        }
        bit = 1 << (newOwner->Type->ArrayIndex2);
        if ((bit & DisplayProductionTo) != 0) {
            DisplayProductionTo = ~bit & DisplayProductionTo;
        }
        void* value = vf_121();
        int angle = vf_281(vf_111()->Intensity_Normal);
        if (vf_88() || (Airstrike && Airstrike->Target == FUN_00459F40())) {
            angle = GetEffectTintIntensity(angle);
        }
        LightTint = (short)angle;
        FUN_00451F60(value, angle & 0xFFFF);
        FUN_00452170(Translucency);

        for (i = 0; i < RulesInstance->list_08AC.Count; i++) {
            if (RulesInstance->list_08AC.Items[i] == Type) {
                newOwner->ConYards.AddItem(this);
                break;
            }
        }
        if (Type->bools_16A4[5]) {
            newOwner->UnitRepairStations.AddItem(this);
        }
        if (Type->bools_16A4[9]) {
            newOwner->Grinders.AddItem(this);
        }
        if (Type->bools_16A4[10] || Type->bools_16A4[11]) {
            newOwner->Absorbers.AddItem(this);
        }
        if (Type->bools_16A4[7]) {
            newOwner->Bunkers.AddItem(this);
        }
        if (Type->bools_1570[11] && Type->TechLevel > -1) {
            newOwner->Occupiables.AddItem(this);
        }
        if (Type->bools_16A4[8]) {
            newOwner->CloningVats.AddItem(this);
        }
        if (Type->bools_16A4[12]) {
            newOwner->SecretLabs.AddItem(this);
        }
        if (Type->PsychicDetectionRadius > 0) {
            newOwner->PsychicDetectionBuildings.AddItem(this);
        }
        if (Type->bools_16A4[41]) {
            newOwner->FactoryPlants.AddItem(this);
            newOwner->CalculateCostMultipliers();
        }
        newOwner->Buildings.AddItem(this);
        if (Type->bools_16A4[40]) {
            Owner->NumOrePurifiers++;
        }
        if (Type->InfantryGainSelfHeal) {
            Owner->InfantrySelfHeal += Type->InfantryGainSelfHeal;
        }
        if (Type->UnitsGainSelfHeal) {
            Owner->UnitsSelfHeal += Type->UnitsGainSelfHeal;
        }
        if (Type->bools_16A4[39]) {
            Owner->AirportDocks += Type->NumberOfDocks;
        }
        if (Type->Factory) {
            oldOwner->FUN_00509140(Type->Factory, Type->Naval, 0);
            newOwner->Update_FactoriesQueues(Type->Factory, Type->Naval, 0);
        }
        for (i = 0; i < held.Count; i++) {
            vf_158(2, held.Items[i]->Object);
            if (held.Items[i]->Flag) {
                IsTether = 1;
                held.Items[i]->Object->IsTether = 1;
            }
        }
        if (Session_00A8B238.GameMode && !newOwner->IsControlledByHuman() && InitialOwner != newOwner && !InitialOwner->Type->MultiplayPassive) {
            while (UpgradeLevel > 0) {
                int r = Upgrades[UpgradeLevel]->vf_46(Owner, 1);
                Owner->GiveMoney(r);
                FUN_00451690();
                Owner->RecheckPower = 1;
                Owner->RecheckRadar = 1;
            }
            vf_104(1);
        }
        oldOwner->RecheckTechTree = 1;
        newOwner->RecheckTechTree = 1;
        return true;
    }
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x449410
int BuildingClass::GetYSort() const
{
    int base = ObjectClass::GetYSort();

    BuildingTypeClass* flags = Type;

    return base + ((flags->bools_16A4[0x16C5 - 0x16A4] ? 0x20 : 0) - (flags->bools_16A4[0x16B7 - 0x16A4] ? 0x10 : 0));
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x449440
int BuildingClass::vf_107(CellClass* target, int a2, int a3, int a4, bool a5)
{
    CellStruct cell = target->MapCoords;
    BuildingTypeClass* type = Type;
    if (type->UndeploysInto != 0 && IsOnMap) {
        return DAT_0087F7E8.FUN_005657A0(&cell)->FUN_0047C620(type->SpeedType, type, Owner) ? 0 : 7;
    }
    return type->vf_42(&cell, Owner) ? 0 : 7;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4494C0
bool BuildingClass::vf_38()
{
    if (!IsBeingDrained() && !Type->bools_1570[0x1579 - 0x1570]) {
        if (HasBuildUp && BState != 0) {
            if (vf_97() != 0x13 && vf_97() != 0x12) {
                return true;
            }
        }
        if (Type->bools_16A4[0x16C0 - 0x16A4] && !Owner->FirestormActive) {
            return true;
        }
    }
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4496B0
// CAPPED at 41.5%. Delta: retail realigns the stack (AND ESP,-8, 0x38 frame), keeps a masked flag byte in a stack
// local and evaluates the price conversion before the counter call; local flag, temp price and operand-swap forms tried.
int BuildingClass::vf_135()
{
    int i;
    unsigned char active;
    if (vf_33()->IsGattling) {
        FUN_0070E000(MissionAccumulateTime);
        MissionAccumulateTime = 0;
    }
    if (IsArmed()) {
        IsReadyToCommence = 1;
        if (!Type->bools_16A4[0x16C3 - 0x16A4]) {
            int idx = Type->SuperWeapon;
            HBIdx3View* link;
            if (idx == -1 || (link = DAT_00A83CBC[idx]->unknown_28->unknown_C8) == 0
                || Owner->ActiveBuildingTypes.FUN_0049FAE0(link->unknown_DF8) != 0) {
                if (Type->SuperWeapon != -1) {
                    goto price;
                }
            }
            if (!Type->bools_1570[0x157B - 0x1570] || vf_258() > 0) {
                if (Target) {
                    vf_122(1, 0);
                    vf_123();
                    return 1;
                }
            }
        }
    price:
        int price = (int)(DAT_007E27F8 * FUN_005B3A00()->AARate);
        return DAT_00A8B230->unknown_0218.RandomRanged(0, 2) + price;
    }
    if (Type->bools_16A4[0x16B5 - 0x16A4]) {
        return 100;
    }
    switch (MissionStatus) {
    case 0:
        FUN_00447780(1);
        MissionStatus = 1;
        break;
    case 1:
        if (Type->bools_16A4[0x16A9 - 0x16A4] || Type->bools_16A4[0x16AA - 0x16A4] || Type->bools_16A4[0x16AB - 0x16A4]) {
            for (i = 0; i < RadioLinks.Capacity; i++) {
                TechnoClass* o = FUN_0065AD30(i);
                if (o && (active = o->Flags.IsTechno) != 0) {
                    if (o->vf_97() == 7) {
                        const CoordStruct& pa = o->vf_18();
                        const CoordStruct& pb = vf_18();
                        CoordStruct d;
                        CoordStruct* diff = d.FUN_0041C230(pb.X - pa.X, pb.Y - pa.Y, pb.Z - pa.Z);
                        if ((int)FUN_004CAC40((double)diff->X * diff->X + (double)diff->Z * diff->Z + (double)diff->Y * diff->Y) < 0x40) {
                            if (vf_158(0x13, o) == 1) {
                                vf_122(0x14, 0);
                                return 1;
                            }
                        }
                    }
                }
            }
        }
        if (Type->bools_16A4[0x16BD - 0x16A4]) {
            FUN_00449540();
        }
        break;
    }
    if (Type->bools_16A4[0x16AA - 0x16A4] && HasAnyLink()) {
        if (vf_157(0x1D) != 1 && vf_157(0x13) == 1) {
            vf_122(0x14, 0);
        }
    }
    if (Type->bools_16A4[0x16A9 - 0x16A4]) {
        int price = (int)(DAT_007E27F8 * FUN_005B3A00()->Rate);
        return DAT_00A8B230->unknown_0218.RandomRanged(0, 2) + price;
    }
    int price = (int)(DAT_007E27F8 * FUN_005B3A00()->Rate);
    return DAT_00A8B230->unknown_0218.RandomRanged(0, 2) + price * 3;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x449A40
int BuildingClass::vf_136()
{
    return vf_135();
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x449A50
int BuildingClass::vf_145()
{
    CoordStruct soundPos;
    CoordStruct pos;
    switch (MissionStatus) {
    case 0: {
        FUN_00447780(0);
        vf_157(0xB);
        int sound = Type->BuildupSound;
        if (sound != -1 || (sound = RulesInstance->Construction) != -1) {
            soundPos = Location;
            FUN_007509E0(sound, &soundPos, &Audio7);
        }
        NeedsRedraw = 1;
        MissionStatus = 1;
        break;
    }
    case 1:
        NeedsRedraw = 1;
        pos = Location;
        FUN_00750D40(&pos, &Audio7);
        if (IsReadyToCommence) {
            vf_157(0xC);
            vf_157(3);
            FUN_00447780(1);
            vf_311(0);
            vf_122(5, 0);
            if (!Type->bools_16A4[0x16BF - 0x16A4]) {
                DirStruct dir;
                dir.Raw = (unsigned char)Type->field_ED8 << 8;
                PrimaryFacing.FUN_004C9300(&dir);
            }
            Type->ClearBuildUp();
            Audio7.EndLooping();
            return 1;
        }
        break;
    }
    return 1;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x449BC0
bool Obj_00449BC0::FUN_00449BC0()
{
    // All seven refusals share the one `XOR AL,AL; POP ESI; RET` at 0x449C23,
    // so they are a single trailing `return false` reached by one condition
    // chain. There are two `MOV AL,0x1` sites though, so the early yes is its
    // own statement. Written as seven early returns VC6 emits seven epilogues
    // and scores 12.0%.
    Settings_00449BC0* settings = Settings;

    if (settings->Mode != 0) {
        if (!settings->Strict) {
            return true;
        }

        if (Session_00A8B238.GameMode != 0
            && Subject != 0
            && FUN_0050B730(Owner)
            && Session_00A8B238.GameMode != 0
            && Session_00A8B238.unknown_18.MCVRedeploy
            && Blocker == 0) {

            return true;
        }
    }

    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x44ABD0  BuildingClass::FireLaser (__thiscall, ret 0xC)
//
// Draw the prism support beam from this building's firing point to `target`:
// a new LaserDrawClass in the type's laser colour (no outer colours), lasting
// the rules-supplied duration, thickened to 3 and drawn in house colour; then
// restart the support timer with the rules-supplied delay and clear +0x664.
//
// Phrasing notes (each was load-bearing): the allocation is `operator new`
// plus an explicit Construct on the block (a `new T(...)` gives an EH frame
// or an internal compiler error, see the header); the zero base coordinate
// is a three-argument ctor temporary (three separate zero registers); the
// firing point goes through a named `flh` local so its temporary stays in
// the frame; and the timer is assigned before the +0x664 clear so the clear
// lands between the LEA and the timer stores.
void Building_0044ABD0::FireLaser(Coord_0044ABD0 target)
{
    Color_0044ABD0 black;
    black.R = 0;
    black.G = 0;
    black.B = 0;

    Coord_0044ABD0 flh;
    LaserDraw_0044ABD0* laser = (LaserDraw_0044ABD0*)operator new(sizeof(LaserDraw_0044ABD0));
    if (laser) {
        laser = laser->Construct(
            *(this->*this->Vtbl->GetFLH)(&flh, 0, Coord_0044ABD0(0, 0, 0)), target, 0, 1,
            this->Type->At_56FC, black, black,
            RulesInstance->PrismSupportDuration, false, true, 1.0f, 0.0f);
        if (laser) {
            laser->IsHouseColor = true;
            laser->Thickness = 3;
        }
    }

    this->At_2EC = CDTimer_0044ABD0(RulesInstance->PrismSupportDelay);
    this->At_664 = 0;
}


// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x44ACF0
int BuildingClass::vf_132()
{
    if (Type->bools_16A4[20]) {
        switch (MissionStatus) {
        case 0:
            {
                if (Type->bools_1570[3] && Type->PowerDrain > 0 && Owner->GetPowerPercentage() < 1.0) {
                    return 1;
                }
                ObjectClass* techno = BA4As<ObjectClass>(Target, 2);
                if (!Target || !techno || !techno->FUN_005F5F30()) {
                    vf_242(0);
                    MissionStatus = 0;
                    vf_122(5, 0);
                    vf_123();
                    return 1;
                }
                if (PrimaryFacing.IsRotating()) {
                    return 1;
                }
                DirStruct wanted = vf_314(Target);
                if (abs((short)0x2000) < abs((short)(PrimaryFacing.FUN_004C93D0().Raw - wanted.Raw))) {
                    PrimaryFacing.SetDesired(vf_314(Target));
                    return 1;
                }
                MissionStatus = 1;
                return 1;
            }
        case 1:
            {
                ObjectClass* techno = BA4As<ObjectClass>(Target, 2);
                if (!Target || !techno || !techno->FUN_005F5F30()) {
                    vf_242(0);
                    MissionStatus = 0;
                    return 1;
                }
                int result = vf_240(Target, 0, 1);
                if (result == 5 || result == 6 || result == 8) {
                    vf_242(0);
                    MissionStatus = 0;
                    return 1;
                }
                if (result == 2) {
                    MissionStatus = 0;
                    return 1;
                }
                if (result != 0) {
                    return 1;
                }
                vf_243(Target, 0);
                vf_243(Target, 1);
                MissionStatus = 0;
                return 1;
            }
        default:
            int base = (int)(FUN_005B3A00()->AARate * 900.0);
            return base + DAT_00A8B230->unknown_0218.RandomRanged(0, 2);
        }
    }

    if (!Target) {
        vf_242(0);
        SupportingPrisms = 0;
        if (vf_268()) {
            FUN_00705D60();
        }
        if (vf_97() == 0x1C) {
            return 1;
        }
        vf_122(5, 0);
        vf_123();
        return 1;
    }

    int direction = vf_185(Target);
    IsReadyToCommence = 1;
    int result = vf_240(Target, direction, 1);
    if (result == 2) {
        if (vf_255() && Type->bools_16A4[33]) {
            DirStruct wanted = vf_314(Target);
            int turn = Type->ROT;
            if (!turn || !(abs((short)(turn << 8)) < abs((short)(PrimaryFacing.FUN_004C93D0().Raw - wanted.Raw)))) {
                PrimaryFacing.FUN_004C9300(&wanted);
                result = vf_240(Target, direction, 1);
            }
        }
    }
    switch (result) {
    case 0:
        if (UpgradeLevel != 0 && Upgrades[1] != 0) {
            if (Upgrades[1]->FUN_00712130()) {
                vf_243(Target, 0);
                vf_243(Target, 1);
            }
        } else if (Type == RulesInstance->PrismType) {
            BuildingClass* best = 0;
            int bestDistance = 0x7FFFFFFF;
            CoordStruct here = vf_43();
            if (SupportingPrisms < RulesInstance->PrismSupportMax) {
                int count = Owner->Buildings.Count;
                for (int i = 0; i < count; i++) {
                    BuildingClass* candidate = Owner->Buildings.Items[i];
                    if (candidate && candidate->IsAlive && candidate->Type == RulesInstance->PrismType) {
                        int length = candidate->RearmTimer.GetTimeLeft();
                        if (length == 0 && candidate->DelayBeforeFiring == 0 && !candidate->IsBeingDrained()
                            && candidate->vf_97() != 1 && candidate != this) {
                            CoordStruct there = candidate->vf_43();
                            double dx = here.X - there.X;
                            double dy = there.Y - here.Y;
                            float dz = here.Z - there.Z;
                            int distance = (int)FUN_004CAC40(dx * dx + dz * dz + dy * dy);
                            if (distance <= vf_90(1)) {
                                if (!best || distance < bestDistance) {
                                    best = candidate;
                                    bestDistance = distance;
                                }
                            }
                        }
                    }
                }
                if (best) {
                    SupportingPrisms++;
                    CoordStruct zero;
                    zero.X = 0;
                    zero.Y = 0;
                    zero.Z = 0;
                    CoordStruct where = vf_44(0, zero);
                    best->DelayBeforeFiring = best->Type->DelayedFireDelay;
                    best->PrismStage = 2;
                    best->PrismTargetCoords = where;
                    best->DestroyNthAnim(3);
                    char* text;
                    int flag;
                    if (best->FUN_005F5C60() > RulesInstance->ConditionYellow) {
                        text = &best->Type->BuildingAnim[10].Anim[0];
                        flag = 0;
                    } else {
                        text = &best->Type->BuildingAnim[10].Damaged[0];
                        flag = 1;
                    }
                    if (text && *text) {
                        best->PlayAnim(text, 10, flag, 0, 0);
                    }
                    break;
                }
            }
            CoordStruct cleared = {0, 0, 0};
            DelayBeforeFiring = Type->DelayedFireDelay;
            PrismTargetCoords = cleared;
            PrismStage = 1;
            DestroyNthAnim(3);
            char* text;
            int flag;
            if (FUN_005F5C60() > RulesInstance->ConditionYellow) {
                text = &Type->BuildingAnim[10].Anim[0];
                flag = 0;
            } else {
                text = &Type->BuildingAnim[10].Damaged[0];
                flag = 1;
            }
            if (text && *text) {
                PlayAnim(text, 10, flag, 0, 0);
            }
        } else if (Type->bools_16A4[3]) {
            CoordStruct cleared = {0, 0, 0};
            DelayBeforeFiring = Type->DelayedFireDelay;
            PrismTargetCoords = cleared;
            PrismStage = 1;
            DestroyNthAnim(3);
            char* text;
            int flag;
            if (FUN_005F5C60() > RulesInstance->ConditionYellow) {
                text = &Type->BuildingAnim[10].Anim[0];
                flag = 0;
            } else {
                text = &Type->BuildingAnim[10].Damaged[0];
                flag = 1;
            }
            if (text && *text) {
                PlayAnim(text, 10, flag, 0, 0);
            }
        } else {
            vf_243(Target, direction);
        }
        if (Type->IsGattling) {
            FUN_0070DE70(MissionAccumulateTime);
            MissionAccumulateTime = 0;
            return 1;
        }
        TurretAnimFrame++;
        return 1;

    case 1:
    case 5:
    case 6:
    case 8:
        vf_242(0);
        SupportingPrisms = 0;
        if (vf_268()) {
            FUN_00705D60();
        }
        if (vf_97() == 0x1C) {
            return 1;
        }
        if (Type->IsGattling) {
            FUN_0070E000(MissionAccumulateTime);
            MissionAccumulateTime = 0;
        }
        vf_122(5, 0);
        vf_123();
        break;

    case 2:
        if (Target) {
            PrimaryFacing.SetDesired(vf_314(Target));
        }
        if (Type->IsGattling) {
            FUN_0070DE70(MissionAccumulateTime);
            MissionAccumulateTime = 0;
        }
        return 2;

    case 3:
        if (Target) {
            PrimaryFacing.SetDesired(vf_314(Target));
        }
        if (Type->IsGattling) {
            FUN_0070DE70(MissionAccumulateTime);
            MissionAccumulateTime = 0;
            return 2;
        }
        TurretAnimFrame++;
        return 2;

    case 9:
        vf_279(0);
        if (Type->IsGattling) {
            FUN_0070E000(MissionAccumulateTime);
            MissionAccumulateTime = 0;
        }
        break;

    case 10:
        if (Type->IsGattling) {
            FUN_0070E000(MissionAccumulateTime);
            MissionAccumulateTime = 0;
        }
        return 1;

    default:
        break;
    }
    if (Target) {
        PrimaryFacing.SetDesired(vf_314(Target));
    }
    MissionAccumulateTime = 0;
    return 1;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x44B760
int BuildingClass::vf_133()
{
    return MissionClass::vf_133();
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x44B770
int BuildingClass::vf_137()
{
    return MissionClass::vf_137();
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x44D5D0
bool BuildingClass::vf_102(HouseClass* house)
{
    if (TechnoClass::vf_102(house)) {
        if (!DAT_00A8E7AC) {
            Owner->LastBuiltBuildingType = Type->ArrayIndex;
            Owner->IsBuiltSomething = 1;
        }
        Owner->RecheckTechTree = 1;
        if (!HasAnyLink() && Owner->IsControlledByHuman() && vf_97() != 0x12 && QueuedMission != 0x12) {
            vf_311(0);
        } else if (!HasAnyLink() && !Owner->IsControlledByHuman() && house == Owner && vf_97() != 0x12) {
            vf_311(0);
        }
        return true;
    }
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x44D6A0
bool BuildingClass::EnterIdleMode(bool initial, bool a2)
{
    int mission;
    if (initial && !DAT_00A8E7AC && !DAT_00A8ED6B) {
        FUN_00447780(0);
        mission = 0x12;
    } else {
        FUN_00447780(1);
        mission = 5;
    }
    vf_122(mission, 0);
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x44D700
int BuildingClass::vf_174()
{
    BuildingTypeClass* type = Type;
    switch (type->PipScale) {
    case 2:
        if (type->bools_16A4[0x16BC - 0x16A4]) {
            double d = Owner->GetWeedStoragePercentage();
            return (int)(type->vf_29() * d);
        }
        return 0;
    default:
        return TechnoClass::vf_174();
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x44D760
void BuildingClass::vf_238(void* arg)
{
    if (arg && Owner->IsControlledByCurrentPlayer()) {
        CellStruct cell = CellOfCoord(vf_19(0));
        CellStruct tmp = cell;
        tmp.FUN_00660B80();
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x44D7D0
//
// A direction quantised from the facing: 8 bits without a target, 5 bits when the type allows the
// coarse form, otherwise the one the target slot computes. The pointer-returning form with the
// multiply by 0x800 is what keeps the 5-bit mask (a shift would let the compiler drop it).
HBDir* BuildingAView::vf_194(HBDir* out)
{
    if (Target == 0) {
        unsigned int raw = Facing.FUN_004C93D0().Whole;
        out->Raw = (short)((unsigned char)(((raw >> 7) + 1) >> 1) << 8);
    } else if (vf_255() && !Type->bools_16A4[0x16C5 - 0x16A4]) {
        unsigned int raw = Facing.FUN_004C93D0().Whole;
        out->Raw = (short)(((((raw >> 10) + 1) >> 1) & 0x1F) * 0x800);
    } else {
        *out = vf_314(Target);
    }
    return out;
}

// Moved from building_a2_state.cpp. CAPPED (partial, readable): 95.2% of the retail instructions align (96.9% with registers ignored); the positional
// score is lower (66.7%) because of two small shifts. Remaining delta: (1) in the state-2 countdown retail keeps the
// elapsed ticks in ECX and the remaining ticks in EAX, our register choice is the other way round (4 instructions);
// (2) retail does not cross-jump the third timer start into the first one (3 stores). Variants tried: the 900.0 and
// 1.0 constants as globals / literals, the frame (hoisted coordinate, 16-byte by-value result of slot 75), the order of
// the timer stores and BState store, and four spellings of the elapsed/left comparison.
// FUNCTION: GAMEMD 0x44E440
// Slot 149, the construction (build-up) mission step: MissionStatus 0 starts the build-up animation, 1 and 4 wait for
// it, 2 counts the timer down, 3 starts the sell-style reverse run; every path ends with the price query.
int BuildingClass::vf_149()
{
    CoordStruct where;   // declared up front: the retail frame keeps it apart from the later temporaries
    if (Type->bools_16A4[19]) {
        switch (MissionStatus) {
        case 0:
            if (UnloadTimer.FUN_004A51B0()) {
                RateTimer t;
                t.Timer.TimeLeft = t.Rate = (int)(Type->GateCloseDelay * 900.0);
                t.Timer.StartTime = CurrentFrame;
                MissionStatus = 2;
                GateTimer = t;
                break;
            }
            if (!UnloadTimer.FUN_004A5110()) {
                if (UnloadTimer.FUN_004A5130()) {
                    UnloadTimer.Update();
                } else {
                    UnloadTimer.StartTimer11(Type->DeployTime);
                    where = Location;
                    FUN_007509E0(RulesInstance->GateDown, &where, 0);
                    DAT_00887324->FUN_006D2790(vf_75(), 0);
                }
            }
            {
                MissionStatus = 1;
                RateTimer t;
                t.Timer.TimeLeft = t.Rate = (int)(Type->GateCloseDelay * 900.0);
                t.Timer.StartTime = CurrentFrame;
                GateTimer = t;
            }
            return 0;
        case 3:
            {
                UnloadTimer.StartTimer10(Type->DeployTime);
                MissionStatus = 4;
                CoordStruct where = Location;
                FUN_007509E0(RulesInstance->GateUp, &where, 0);
            }
            return 0;
        case 2:
            if (!FUN_0044E3A0()) {
                int duration = GateTimer.Rate;
                if (duration) {
                    int left = GateTimer.Timer.TimeLeft;
                    if (GateTimer.Timer.StartTime != -1) {
                        int elapsed = CurrentFrame - GateTimer.Timer.StartTime;
                        if (elapsed >= left) {
                            left = 0;
                        } else {
                            left = left - elapsed;
                        }
                    }
                    if ((double)(duration - left) / duration != 1.0) {
                        break;
                    }
                }
                MissionStatus = 3;
            } else {
                RateTimer t;
                t.Timer.TimeLeft = t.Rate = (int)(Type->GateCloseDelay * 900.0);
                t.Timer.StartTime = CurrentFrame;
                GateTimer = t;
            }
            break;
        case 1:
            if (UnloadTimer.FUN_004A51B0()) {
                MissionStatus = 2;
            }
            // fall through
        case 4:
            if (UnloadTimer.FUN_004A51D0()) {
                EnterIdleMode(false, 1);
                MissionStatus = 5;
                NeedsRedraw = 1;
            }
            if (UnloadTimer.FUN_004A5110() || UnloadTimer.FUN_004A5130() || UnloadTimer.FUN_004A51B0()) {
                int v = (int)(UnloadTimer.PercentageDone() * Type->GateStages);
                if (v != GateStage) {
                    GateStage = (signed char)v;
                    NeedsRedraw = 1;
                }
            }
            return 0;
        }
        int price = (int)(FUN_005B3A00()->Rate * 900.0);
        return price + DAT_00A8B230->unknown_0218.RandomRanged(0, 2);
    }
    vf_122(5, 0);
    return 1;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x44E7B0  BuildingClass::GetPowerOutput (__thiscall)
// Base output is the type's PowerBonus, read before the warp-out test. A
// building being warped out produces nothing. Otherwise the extra bonus is
// added when the instance flag is set, once more per passenger when the type
// is one of the two absorbing kinds and actually has a positive extra bonus,
// and each fitted upgrade's own PowerBonus is added when the building is
// upgraded at all. A positive total is finally scaled by the health ratio;
// anything else, or an unpowered building, reports zero.
int BuildingClass::GetPowerOutput()
{
    int output = this->Type->PowerBonus;

    if (this->vf_117())
        return 0;

    if (this->HasExtraPowerBonus)
        output += this->Type->ExtraPowerBonus;

    // Register naming is sensitive here: the multiply's destination must be
    // the bonus (`MOV EAX,[EAX+0xEE8]` reusing the dying type pointer, then
    // `IMUL EAX,ECX` with the passenger count in ECX). A flat
    // `&& bonus > 0 && n > 0` condition with the product in the body, in any
    // operand order and with or without locals, gives the bonus ECX and the
    // count EAX (93.8%). Splitting the count test into its own nested `if`
    // with the count bound first and the bonus re-read second is what makes
    // the bonus the destination operand.
    BuildingTypeClass* type = this->Type;
    if ((type->bools_16A4[0x16AE - 0x16A4] || type->bools_16A4[0x16AF - 0x16A4]) && type->ExtraPowerBonus > 0)
    {
        int n = this->Passengers.NumPassengers;
        if (n > 0)
        {
            int b = type->ExtraPowerBonus;
            output += b * n;
        }
    }

    if (this->UpgradeLevel)
    {
        for (int i = 0; i < 3; i++)
        {
            if (this->Upgrades[i])
                output += this->Upgrades[i]->PowerBonus;
        }
    }

    if (output > 0 && this->HasPower)
        return (int)(this->GetHealthPercentage() * output);

    return 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x44E880  (__thiscall)
//
// Retail body (len 0x62), entry ECX = this:
//   56              PUSH ESI
//   8bf1            MOV  ESI, ECX
//   8b06            MOV  EAX, [ESI]            ; vtable
//   ff90d4010000    CALL [EAX+0x1d4]           ; virtual slot 117 (offline?)
//   84c0            TEST AL, AL
//   754f            JNZ  ret0
//   8a8660060000    MOV  AL, [ESI+0x660]       ; HasPower
//   84c0            TEST AL, AL
//   7445            JZ   ret0
//   8b8e20050000    MOV  ECX, [ESI+0x520]      ; Type
//   8a9669060000    MOV  DL, [ESI+0x669]       ; HasExtraPowerDrain
//   84d2            TEST DL, DL
//   8b81e40e0000    MOV  EAX, [ECX+0xee4]      ; Type->PowerDrain
//   7406            JZ   skip_extra
//   0381ec0e0000    ADD  EAX, [ECX+0xeec]      ; + Type->ExtraPowerDrain
// skip_extra:
//   8a8e02070000    MOV  CL, [ESI+0x702]       ; UpgradeLevel
//   84c9            TEST CL, CL
//   7421            JZ   ret_eax
//   8d96ec050000    LEA  EDX, [ESI+0x5ec]      ; &Upgrades[0]
//   be03000000      MOV  ESI, 0x3              ; 3 upgrade slots
// loop:
//   8b0a            MOV  ECX, [EDX]
//   85c9            TEST ECX, ECX
//   7406            JZ   loop_next
//   0381e40e0000    ADD  EAX, [ECX+0xee4]      ; + upgrade->PowerDrain
// loop_next:
//   83c204          ADD  EDX, 0x4
//   4e              DEC  ESI
//   75ee            JNZ  loop
//   5e              POP  ESI
//   c3              RET
// ret0:
//   33c0            XOR  EAX, EAX
// ret_eax:
//   5e              POP  ESI
//   c3              RET
//
// Screened for the inline-assembly signature before conversion and it is
// absent: the prologue is a bare `56 PUSH ESI` with no `PUSH EBP; MOV EBP,ESP`,
// every local lives in a register, and no instruction in the body is outside
// what cl 12.00 generates from a C expression. Retail was compiled from
// ordinary C++ here, so the body below is C++.
int BuildingClass::GetPowerDrain()
{
    if (this->vf_117() || !this->HasPower) {
        return 0;
    }

    BuildingTypeClass* type = this->Type;
    int drain = type->PowerDrain;

    if (this->HasExtraPowerDrain) {
        drain += type->ExtraPowerDrain;
    }
    if (this->UpgradeLevel) {
        for (int i = 0; i < 3; ++i) {
            BuildingTypeClass* upgrade = this->Upgrades[i];

            if (upgrade != 0) {
                drain += upgrade->PowerDrain;
            }
        }
    }
    return drain;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x44E8F0
void BuildingAView::vf_10(BAObjView* ptr, bool removed)
{
    FUN_007077C0(ptr, removed);
    if (C4AppliedBy == ptr) {
        C4AppliedBy = 0;
    }
    if (FirestormAnim == ptr) {
        FirestormAnim = 0;
    }
    if (Factory == ptr) {
        Factory = 0;
    }
    if (Spotlight == ptr) {
        Spotlight = 0;
    }
    if (LightSource == ptr) {
        LightSource = 0;
    }
    if (Anims[8] == ptr) {
        double ratio = FUN_005F5C60();
        char* name;
        int low;
        if (ratio <= RulesInstance->ConditionYellow) {
            low = 1;
            name = Type->BuildingAnim[18].Damaged;
        } else {
            low = 0;
            name = Type->BuildingAnim[18].Anim;
        }
        if (name && *name) {
            FUN_00451890(name, 0x12, low, 0, 0);
        }
    }
    if (Type->bools_16A4[0x16AD - 0x16A4] && Anims[10] == ptr) {
        double ratio = FUN_005F5C60();
        char* name;
        int low;
        if (ratio <= RulesInstance->ConditionYellow) {
            low = 1;
            name = Type->BuildingAnim[3].Damaged;
        } else {
            low = 0;
            name = Type->BuildingAnim[3].Anim;
        }
        if (name && *name) {
            FUN_00451890(name, 3, low, 0, 0);
        }
    }
    if (ptr) {
        if (ptr->unknown_04.vf_3() == 4) {
            int i;
            for (i = 0; i < 8; i++) {
                if (DamageFireAnims[i] == ptr) {
                    DamageFireAnims[i] = 0;
                    return;
                }
            }
            if (ptr->unknown_118) {
                FUN_00451B40(ptr);
                return;
            }
        }
    }
    if (Type == (BuildingTypeClass*)ptr) {
        Type = 0;
    }
    int i;
    for (i = 0; i < 3; i++) {
        if (Upgrades[i] == ptr) {
            Upgrades[i] = 0;
        }
    }
    Overpowerers.RemoveItem(ptr);
    if (DAT_00A8E7AC) {
        Occupants.RemoveItem(ptr);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x44EB10
int BuildingClass::vf_195()
{
    if (!HasBeenCaptured && DAT_00A8B230->unknown_0218.RandomRanged(0, 0x63) < 0x19 && Type->Factory == 7) {
        return RulesInstance->Engineer;
    }
    return TechnoClass::vf_195();
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x44EBF0
// CAPPED at 67.4%. Delta: retail merges the type!=7 path into the fifth inlined slot copy (jump into the middle);
// loop, helper-inline and if/else-with-helper forms tried, none merges.
void BuildingClass::vf_55(bool arg)
{
    if (arg) {
        if (Factory) {
            Factory->AbandonProduction();
            if (Factory) {
                delete Factory;
            }
            Factory = 0;
        }
        if (Owner) {
            if (Type->Factory == 7) {
                if (Owner->Primary_ForBuildings) {
                    BAReleaseSlot(this, Owner->Primary_ForBuildings);
                }
                if (Owner->Primary_Unused1) {
                    BAReleaseSlot(this, Owner->Primary_Unused1);
                }
                if (Owner->Primary_Unused2) {
                    BAReleaseSlot(this, Owner->Primary_Unused2);
                }
                if (Owner->Primary_Unused3) {
                    BAReleaseSlot(this, Owner->Primary_Unused3);
                }
                if (Owner->Primary_ForDefenses) {
                    BAReleaseSlot(this, Owner->Primary_ForDefenses);
                }
            } else {
                FactoryClass* factory = Owner->GetPrimaryFactory(Type->Factory, Type->Naval, 0);
                if (factory) {
                    BAReleaseSlot(this, factory);
                }
            }
        }
        vf_160(3);
    } else {
        int i;
        for (i = 0; i < RadioLinks.Capacity; i++) {
            TechnoClass* o = FUN_0065AD30(i);
            if (o && !Owner->FUN_004F9A90(o)) {
                vf_158(3, o);
            }
        }
    }
    ObjectClass::vf_55(arg);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x44EF80
// PARTIAL: 80% -- the argument loads before the slot call are scheduled differently from retail.
int Owner_0044EF80::Lookup(Target_0044EF80* t, int a)
{
    if (t)
    {
        int ctx = Context;
        Resolved_0044EF80* r = t->Resolve(a, ctx);
        return r->FUN_0045EE70();
    }
    return -1;
}

// EXACT: 100.0% (494/494 instructions, 57 relocation fields verified, raw span identical modulo relocations).
// What made it match: slot 110 as a by-value return (hidden temporary shared with the constructor temporaries),
// the HBCell constructor temporaries reusing the argument slot, and separate loop variables (i, j) per loop.
// FUNCTION: GAMEMD 0x44EFB0
// Finds a cell next to the building where the mover may stand: the type's fixed exit cells first, then the
// cells around the building's centre, the preferred cell, the type's own offset list (terminated by
// 0x7FFF,0x7FFF) or else the rows and columns around the foundation. Returns the invalid cell on failure.
Cell BuildingClass::vf_309(ObjectClass* who, Cell preferred)
{
    Cell base = vf_110();
    Cell c;

    if (Type->bools_16E4[0]) {
        c = Cell(base.X + 1, base.Y + 2);
        if (DAT_0087F7E8.FUN_00568300(&c) && !who->vf_107(DAT_0087F7E8.FUN_005657A0(&c), -1, -1, 0, 1)) {
            return c;
        }
    }
    if (Type->bools_16E4[1]) {
        c = Cell(base.X + 2, base.Y + 2);
        if (DAT_0087F7E8.FUN_00568300(&c) && !who->vf_107(DAT_0087F7E8.FUN_005657A0(&c), -1, -1, 0, 1)) {
            return c;
        }
    }
    if (Type->bools_16E4[2]) {
        c = Cell(base.X + 2, base.Y + 1);
        if (DAT_0087F7E8.FUN_00568300(&c) && !who->vf_107(DAT_0087F7E8.FUN_005657A0(&c), -1, -1, 0, 1)) {
            return c;
        }
    }
    if (Type->Naval && Type->bools_16A4[25]) {
        c = Coord2Cell(vf_42(who));
        c.X++;
        c.Y++;
        if (DAT_0087F7E8.FUN_00568300(&c) && !who->vf_107(DAT_0087F7E8.FUN_005657A0(&c), -1, -1, 0, 0)) {
            return c;
        }
        c.Y--;
        if (DAT_0087F7E8.FUN_00568300(&c) && !who->vf_107(DAT_0087F7E8.FUN_005657A0(&c), -1, -1, 0, 0)) {
            return c;
        }
        c.Y++;
        c.X--;
        if (DAT_0087F7E8.FUN_00568300(&c) && !who->vf_107(DAT_0087F7E8.FUN_005657A0(&c), -1, -1, 0, 0)) {
            return c;
        }
    }
    if (preferred.X != DAT_0089C818.cell.X || preferred.Y != DAT_0089C818.cell.Y) {
        if (DAT_0087F7E8.FUN_00568300(&preferred)
            && !who->vf_107(DAT_0087F7E8.FUN_005657A0(&preferred), -1, -1, 0, 0)) {
            return preferred;
        }
    }

    CellStruct* offsets = Type->FoundationOutside;
    if (offsets && !Type->bools_16A4[29]) {
        while (!(offsets->X == 0x7FFF && offsets->Y == 0x7FFF)) {
            CellStruct* entry = offsets++;
            c = Cell(base.X + entry->X, base.Y + entry->Y);
            if (DAT_0087F7E8.FUN_00568300(&c) && !who->vf_107(DAT_0087F7E8.FUN_005657A0(&c), -1, -1, 0, 0)) {
                return c;
            }
        }
    } else {
        int rows = Type->GetFoundationHeight(false);
        for (int i = -1; i <= Type->GetFoundationWidth(); i++) {
            c = Cell(base.X + i, base.Y + rows);
            if (DAT_0087F7E8.FUN_00568300(&c) && !who->vf_107(DAT_0087F7E8.FUN_005657A0(&c), -1, -1, 0, 1)) {
                return c;
            }
            c = Cell(base.X + i, base.Y - 1);
            if (DAT_0087F7E8.FUN_00568300(&c) && !who->vf_107(DAT_0087F7E8.FUN_005657A0(&c), -1, -1, 0, 1)) {
                return c;
            }
        }
        int columns = Type->GetFoundationWidth();
        for (int j = -1; j <= Type->GetFoundationHeight(false); j++) {
            c = Cell(base.X + columns, base.Y + j);
            if (DAT_0087F7E8.FUN_00568300(&c) && !who->vf_107(DAT_0087F7E8.FUN_005657A0(&c), -1, -1, 0, 1)) {
                return c;
            }
            c = Cell(base.X - 1, base.Y + j);
            if (DAT_0087F7E8.FUN_00568300(&c) && !who->vf_107(DAT_0087F7E8.FUN_005657A0(&c), -1, -1, 0, 1)) {
                return c;
            }
        }
    }
    return DAT_0089C818;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x44F5C0
bool BuildingClass::vf_40()
{
    if (EMPLockRemaining > 0)
        return false;
    if (vf_161())
        return true;
    if (Type->bools_16A4[0x16B9 - 0x16A4]) {
        if (!Owner->IsControlledByHuman())
            goto refuse;
        if (Session_00A8B238.GameMode == 0)
            goto refuse;
        if (Session_00A8B238.unknown_18.MCVRedeploy == 0)
            goto refuse;
        if (MindControlledBy == 0)
            goto allow;
refuse:
        return false;
    }
allow:
    return Type->UndeploysInto != 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x44F640
// CAPPED at 26.0% (13 of 50 instructions). Retail lays the equal-to-empty-coordinate path (the vf_18 copy) after
// the non-equal path, entered by a final `je`; cl keeps it first behind `jne` for every spelling tried
// (`==&&` then-block, `!=||` then-block, a `goto`, an if/else with one return).
CoordStruct BuildingClass::vf_45(int)
{
    BuildingTypeClass* type = Type;
    if (type->ExitCoord.X != DAT_0089C848.X || type->ExitCoord.Y != DAT_0089C848.Y
        || type->ExitCoord.Z != DAT_0089C848.Z) {
        CoordStruct loc = Location;
        return CoordSum(loc, type->ExitCoord);
    } else {
        return vf_18();
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x44F7A0
// Recompute the owner's radar-visibility mask as the OR of the display masks of
// its live buildings whose type has the radar flag, then tell the map.
void BuildingClass::FUN_0044F7A0()
{
    Owner->RadarVisibleTo = 0;
    int count = Owner->Buildings.Count;
    for (int i = 0; i < count; i++) {
        BuildingClass* building = Owner->Buildings.Items[i];
        if (building != 0 && !building->InLimbo && building->Type->bools_16A4[0]) {
            Owner->RadarVisibleTo |= building->DisplayProductionTo;
        }
    }
    DAT_0087F7E8.FUN_004F42F0(2);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x44FE60
void FUN_0044FE60(Ini_0044FE60* ini)
{
    ini->FUN_005257C0(DAT_007E3E88, 0);

    for (int i = 0; i < DAT_00A8EB40.Count; i++) {
        BuildingClass* entry = DAT_00A8EB40.Items[i];

        if (!entry->InLimbo && !entry->Type->bools_16A4[0x1B]) {
            entry->FUN_0044FEC0(ini);
        }
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4500A0
CoordStruct BuildingClass::vf_41()
{
    CoordStruct c = vf_18();
    return c + Type->TargetCoordOffset;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4503E0
// Empty function.
void __cdecl FUN_004503E0()
{
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4504F0
//
// Record the prism stage, its target and the type's firing delay, drop animation
// slot 3, then start slot 0xA (damaged name once health is at the yellow threshold).
void BuildingClass::FUN_004504F0(int stage, const CoordStruct* target)
{
    DelayBeforeFiring = Type->DelayedFireDelay;
    PrismStage = stage;
    PrismTargetCoords = *target;

    DestroyNthAnim(3);

    int damaged = GetHealthPercentage() <= RulesInstance->ConditionYellow;
    const char* animName;
    if (damaged) {
        animName = Type->BuildingAnim[0xA].Damaged;
    } else {
        animName = Type->BuildingAnim[0xA].Anim;
    }
    if (animName && *animName) {
        PlayAnim(animName, 0xA, damaged, false, 0);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x450590
//
// Drop every overpowering unit whose target is no longer this building, then
// recompute IsOverpowered: three or more overpowerers always count; one or two
// count only on a fully powered house whose building has power.
void BuildingClass::FUN_00450590()
{
    for (int i = Overpowerers.Count - 1; i >= 0; i--) {
        if (Overpowerers.Items[i]->Target != this) {
            if (i < Overpowerers.Count) {
                Overpowerers.Count--;
                for (int j = i; j < Overpowerers.Count; j++) {
                    Overpowerers.Items[j] = Overpowerers.Items[j + 1];
                }
            }
        }
    }

    int count = Overpowerers.Count;
    if (count < 3) {
        if (Owner->GetPowerPercentage() == DAT_007E1718 && HasPower && count >= 1) {
            IsOverpowered = true;
        } else {
            IsOverpowered = false;
        }
    } else {
        IsOverpowered = true;
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x451330
int BuildingClass::vf_180()
{
    if (!NoCrew && Type->Crewed) {
        int rate;
        int side = Owner->SideIndex;
        if (side == 0)
            rate = RulesInstance->AlliedSurvivorDivisor;
        else if (side == 1)
            rate = RulesInstance->SovietSurvivorDivisor;
        else if (side == 2)
            rate = RulesInstance->ThirdSurvivorDivisor;
        else
            return 0;
        if (rate != 0) {
            if (HasBeenCaptured)
                rate += rate;
            int n = Type->vf_46(Owner, 0) / rate;
            if (n < 1)
                return 1;
            if (n > 5)
                return 5;
            return n;
        }
    }
    return 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4513D0
void* BuildingClass::vf_27()
{
    if (BState && ActuallyPlacedOnMap)
        return Type->vf_39();
    return Type->vf_48();
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x451750
//
// Pick one of three byte flags out of the owner's record for `index` — the
// second when `a`, the third when `b`, the first otherwise — and hand it on
// only if it is set. Retail still tests the pointer for null even though every
// arm produces the address of a member, so the selection is written through a
// pointer variable rather than folded into the call.
void Obj_00451750::FUN_00451750(int index, bool a, bool b, int extra)
{
    char* slot;

    if (a) {
        slot = &this->Owner->Slots[index].At_10;
    } else if (b) {
        slot = &this->Owner->Slots[index].At_20;
    } else {
        slot = &this->Owner->Slots[index].At_00;
    }

    if (slot != 0 && *slot != 0) {
        this->FUN_00451890(slot, index, a, b, extra);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x451E40  (__thiscall)
// Destroy one (or, for slot == -2, every) building animation. The kill is a
// virtual scalar-deleting-destructor call through AnimClass vtable slot
// 0x20 (`mov [vtbl]; push 1; call [vtbl+0x20]`).
void BuildingClass::DestroyNthAnim(int slot)
{
    if (slot == -2)
    {
        AnimClass** p = &this->Anims[0];
        for (int i = 0x15; i != 0; --i)
        {
            AnimClass* anim = *p;
            if (anim)
            {
                *p = 0;
                delete anim;
            }
            ++p;
        }
    }
    else
    {
        AnimClass* anim = this->Anims[slot];
        if (anim)
        {
            this->Anims[slot] = 0;
            delete anim;
        }
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x451EA0
// Hide one (or, for slot == -2, every) building animation.
void BuildingClass::SetAnimInvisible(int slot)
{
    if (slot == -2)
    {
        AnimClass** p = &this->Anims[0];
        for (int i = 0x15; i != 0; --i)
        {
            AnimClass* anim = *p;
            if (anim)
            {
                anim->Invisible = 1;
            }
            ++p;
        }
    }
    else
    {
        AnimClass* anim = this->Anims[slot];
        if (anim)
        {
            anim->Invisible = 1;
        }
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x451EE0  BuildingClass::ToggleDamagedAnims (__thiscall, ret 0x4)
// Swap the building between its healthy and damaged animation sets. Nothing
// happens if it is already in the requested state.
//
// The `name != 0` guard is a source-level test the compiler kept even though
// the value is a LEA result that can never be null — same shape as the dead
// null checks in MarkPassengersAsExited and MessageListClass::RemoveEdit.
void BuildingClass::ToggleDamagedAnims(bool damaged)
{
    if (IsDamaged == damaged)
        return;

    IsDamaged = damaged;

    for (int i = 0; i < 0x15; i++)
    {
        if (Anims[i] != 0)
        {
            const char* name = damaged ? Type->BuildingAnim[i].Damaged
                                       : Type->BuildingAnim[i].Anim;

            if (name != 0 && *name != 0)
                PlayAnim(name, i, damaged, 0, 0);
        }
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x451F60
// For each live animation: hand cell-drawn types the given lighting and tint,
// then set the translucency (15 becomes 16 while the building reports mission
// type 5) on every animation.
void BuildingClass::FUN_00451F60(void* lightConvert, int tint)
{
    for (int i = 0; i < 0x15; i++) {
        AnimClass* anim = Anims[i];
        if (anim) {
            if (anim->Type && anim->Type->ShouldUseCellDrawer) {
                anim->LightConvert = lightConvert;
                anim->TintColor = tint;
            }
            int level = Translucency;
            if (level == 0xF && vf_26(0, 0) == 5)
                level = 0x10;
            for (int j = 0; j < 0x15; j++) {
                if (Anims[j])
                    Anims[j]->TranslucencyLevel = level;
            }
        }
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x452170
void Obj_00452170::FUN_00452170(int value)
{
    int stamp = value;

    if (value == 15 && vt_068(0, 0) == 5) {
        stamp = 0x10;
    }

    Slot_00452170** slot = Slots;
    int             n    = 0x15;

    do {
        Slot_00452170* item = *slot;

        if (item) {
            item->Stamp = (char)stamp;
        }

        slot++;
        n--;
    } while (n != 0);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4521C0  (__thiscall)
// Suspend the active building anims while a temporal weapon targets us: stash
// each anim's current frame in PausedAnimFrame and freeze it.
void BuildingClass::DisableTemporal()
{
    this->HasPower = 0;
    AnimClass** p = &this->Anims[0];
    for (int i = 0x15; i != 0; --i)
    {
        AnimClass* anim = *p;
        if (anim)
        {
            int saved = anim->Value;
            anim->Paused = 1;
            anim->Unpaused = 0;
            anim->PausedAnimFrame = saved;
            anim->UnderTemporal = 1;
        }
        ++p;
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x452210  (__thiscall)
// Resume the building anims when the temporal weapon releases us.
void BuildingClass::EnableTemporal()
{
    this->HasPower = 1;
    AnimClass** p = &this->Anims[0];
    for (int i = 0x15; i != 0; --i)
    {
        AnimClass* anim = *p;
        if (anim)
        {
            anim->Paused = 0;
            anim->Unpaused = 1;
            anim->UnderTemporal = 0;
        }
        ++p;
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x452250
int BuildingClass::vf_321()
{
    return 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x452260  BuildingClass::GoOnline (__thiscall)
//
// Bring an unpowered building back online, unless it is EMP-locked. The
// power flag rises, a redraw is requested, the owner's two blackout-activated
// bytes and its tech-tree-recheck byte are raised, the building's light,
// end post and enabled animations come back (EnableStuff, expanded inline),
// any factory queue the building serves is re-evaluated, and the local
// player hears the EVA line.
void BuildingClass_00452260::GoOnline()
{
    if (this->HasPower)
        return;
    if (this->EMPLockRemaining != 0)
        return;

    this->HasPower = 1;
    this->NeedsRedraw = 1;
    this->Owner->PowerBlackoutWasActivated = 1;
    this->Owner->RadarBlackoutWasActivated = 1;
    this->Owner->RecheckTechTree = 1;
    this->EnableStuff();
    if (this->Type->Factory != 0)
        this->Owner->Update_FactoriesQueues(this->Type->Factory, this->Type->Naval, 0);
    if (this->Owner->IsControlledByCurrentPlayer())
        VoxClass_00452260::Play(EvaBuildingOnLine_00452260, -1, -1);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x452360
//
// Take a powered building offline. Only structures that are currently
// powered and actually depend on power (a positive drain, or the Powered
// flag) do anything: the power flag drops, a redraw is requested, the owner's
// two blackout-activated bytes and its tech-tree-recheck byte are raised, the
// building's animations and light are disabled, the local player hears the
// EVA line, and any factory queue the building served is re-evaluated.
void BuildingClass::GoOffline()
{
    if (!this->HasPower)
        return;

    BuildingTypeClass* type = this->Type;
    if (type->PowerDrain > 0 || type->bools_1570[0x1573 - 0x1570]) {
        this->HasPower = 0;
        this->NeedsRedraw = 1;
        this->Owner->RecheckPower = 1;
        this->Owner->RecheckRadar = 1;
        this->Owner->RecheckTechTree = 1;
        this->DisableStuff();
        if (this->Owner->IsControlledByCurrentPlayer())
            VoxClass_00452360::Play(EvaBuildingOffLine, -1, -1);
        if (this->Type->Factory != 0)
            this->Owner->Update_FactoriesQueues(this->Type->Factory, this->Type->Naval, 0);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x452410  BuildingClass::EnableStuff (__thiscall)
// Bring a building's attachments back online: its light source, its end post if
// the type wants one, and every animation the type marks as enabled that the
// instance actually has. VC6 strength-reduces the loop into two induction
// variables — a byte offset stepping 0x44 through the type's records and a
// pointer stepping 4 through the instance's — which is why the bound in the
// disassembly reads 0x594 rather than 21.
void BuildingClass::EnableStuff()
{
    StuffEnabled = true;

    if (LightSource != 0)
        LightSource->Activate(0);

    if (Type->bools_16A4[0x16BE - 0x16A4])
        CreateEndPost(false);

    for (int i = 0; i < 0x15; i++)
    {
        if (Type->BuildingAnim[i].Powered && Anims[i] != 0)
            AnimClass_Enable(Anims[i]);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x452480  BuildingClass::DisableStuff
//
// Everything a powered-down building stops doing: the light goes off, a cloak
// generator drops its field (remembering the radius if it had none yet), a
// charged gap generator is collapsed through the virtual, the sensor-style
// flag on the type gets its off call, and every enabled per-slot animation is
// halted.
void BuildingClass::DisableStuff()
{
    StuffEnabled = 0;
    if (LightSource != 0)
        LightSource->Deactivate(0);
    BuildingTypeClass* type = Type;
    if (type->bools_16A4[0x16C7 - 0x16A4]) {
        HasCloakingData = -1;
        if (CloakRadius == 0)
            CloakRadius = type->CloakRadiusInCells;
        NeedsRedraw = 1;
    }
    if (type->GapGenerator && GeneratingGap)
        vf_262();
    if (Type->bools_16A4[0x16BE - 0x16A4])
        CreateEndPost(0);
    for (int i = 0; i < 0x15; ++i) {
        if (Type->BuildingAnim[i].Powered && Anims[i])
            Anims[i]->FUN_00425260();
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x452540
//
// Ask a gate to let something through. Non-gates are always traversable.
// A gate already in the Open mission whose transition timer is neither
// "opening" (10) nor "closed" (00) answers with IsTraversable (open and
// settled). Otherwise the gate is forced out of its current mission, Open
// is queued and started, and the caller is told to wait.
bool BuildingClass_00452540::MakeTraversable()
{
    if (!this->Type->Gate)
        return true;

    if ((this->*this->Vtbl->GetCurrentMission)() == MISSION_OPEN_00452540
        && !this->GateTimer.AreStates10()
        && !this->GateTimer.AreStates00())
    {
        return this->IsTraversable();
    }

    (this->*this->Vtbl->ForceMission)(-1);
    (this->*this->Vtbl->QueueMission)(MISSION_OPEN_00452540, false);
    (this->*this->Vtbl->NextMission)();
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4525F0  (__thiscall)
// True if a unit may drive across this building's footprint. Always traversable
// unless the type forbids it; then only certain (WhatAmI==0x18) buildings with
// a passable cell qualify. WhatAmI is the virtual at vtable slot 0x184.
bool BuildingClass::IsTraversable()
{
    if (!this->Type->bools_16A4[0x16B7 - 0x16A4])
        return true;

    int kind = this->vf_97();
    if (kind == 0x18 && this->UnloadTimer.FUN_004A51B0())
        return true;

    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x452630
bool BuildingClass::vf_37()
{
    if (Health == 0)
        return false;
    if (!Type->bools_1570[0x157A - 0x1570])
        return false;
    if (vf_32())
        return false;
    return TechnoClass::vf_37();
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x452670
//
// Whether the upgrade type may be attached to this building for the house:
// the house must own the building and the upgrade must name this building's
// type. A slot of -1 is accepted while the building is below its type's upgrade
// cap; otherwise (and for slots 1 to 3) the building must carry no upgrade yet.
bool BuildingClass::FUN_00452670(BuildingTypeClass* upgrade, HouseClass* house)
{
    if (house == Owner && _stricmp(upgrade->PowersUpBuilding, Type->ID) == 0) {
        int level = upgrade->PowersUpToLevel;
        if (level != -1) {
            if (level <= 0 || level > 3) {
                return false;
            }
        } else if (UpgradeLevel < Type->Upgrades) {
            return true;
        }
        if (!UpgradeLevel) {
            return true;
        }
    }
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4526F0
// CAPPED at 48.0% (36 of 75 instructions; retail-only: 2 `add eax,imm` computing &Type->field after the load;
// compiled differs in block layout). Retail loads the occupant type once, before the elite branch, and keeps the
// elite/non-elite tests as `mov ecx,[eax+0xE20]; add eax,0xE20; test ecx,ecx`. Variants tried: the plain
// per-branch form kept here, a hoisted `type` local ahead of the branch, a local `elite` bool.
void BuildingBView::vf_254(int a)
{
    if (UpgradeLevel) {
        for (int i = 0; i < UpgradeLevel; i++) {
            if (Upgrades[i] && *Upgrades[i]->Func_7177C0(a))
                return;
        }
    }
    if (vf_256() && FiringOccupantIndex < Occupants.Count) {
        BuildingBOccupantView* occupant = Occupants.Items[FiringOccupantIndex];
        if (occupant->Veterancy.Func_750010()) {
            if (occupant->Type->unknown_E20 == 0)
                occupant->vf_254(0);
        } else {
            if (occupant->Type->unknown_E04 == 0)
                occupant->vf_254(0);
        }
        return;
    }
    Func_70E140(a);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4527D0
bool BuildingClass::vf_255()
{
    if (Type->bools_C8C[0xCA1 - 0xC8C])
        return true;
    if (UpgradeLevel) {
        for (int i = 0; i < UpgradeLevel; i++) {
            if (Upgrades[i] && Upgrades[i]->bools_C8C[0xCA1 - 0xC8C])
                return true;
        }
    }
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4528A0
// PARTIAL: 78.7% -- instruction multiset identical; retail reads both centre
// coordinates through one shared 12-byte stack slot (frame 0xC), this compiles
// two (frame 0x14). Named locals, scoped blocks, const refs and a reused local
// all keep two slots.
// True when the target's centre lies within the type's psychic detection radius
// (in cells) of this building's centre.
bool BuildingClass::FUN_004528A0(AbstractClass* target)
{
    CoordStruct here = vf_18();
    CoordStruct there = target->vf_18();
    int dx = here.X - there.X;
    int dy = here.Y - there.Y;
    int dz = here.Z - there.Z;
    int distance = (int)FUN_004CAC40((double)dx * dx + (double)dy * dy + (double)dz * dz);
    return distance <= Type->PsychicDetectionRadius * 256;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4529E0
// Once the scenario is running, for a live, owned building whose type has the
// flag at +0x16BE set, refresh sides 0, 2, 4 and 6 and then the end post.
void BuildingClass::FUN_004529E0()
{
    if (ScenarioInit_00A8E7AC == 0 && Type->bools_16A4[0x1A] && IsAlive && !InLimbo) {
        FUN_00452DC0(0);
        FUN_00452DC0(2);
        FUN_00452DC0(4);
        FUN_00452DC0(6);
        CreateEndPost(true);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x452D40
//
// Refresh all four sides of every eligible object, then mark it done.
//
// Exact under the project default /Gr. With the function itself compiled
// as fastcall, cl loads ECX ahead of the immediate push in the call run as
// retail does; the cdecl build of this same body had five load/push
// transpositions (82.2%) that no source spelling moved.
//
// The global suppressor at 0xA8E7AC is tested inside the loop rather than once
// before it -- retail reloads it per object -- so a value that changes mid-pass
// would take effect immediately. That is why it is not hoisted.
void FUN_00452D40()
{
    int i = 0;

    while (i < DAT_00A8EB40.Count) {
        BuildingClass* obj = DAT_00A8EB40.Items[i];

        if (obj != 0 && obj->Type->bools_16A4[0x16BE - 0x16A4] != 0 && DAT_00A8E7AC == 0
            && obj->IsAlive != 0 && obj->InLimbo == 0) {
            obj->FUN_00452DC0(0);
            obj->FUN_00452DC0(2);
            obj->FUN_00452DC0(4);
            obj->FUN_00452DC0(6);
            obj->CreateEndPost(true);
        }

        i++;
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x453370
void Obj_00453370::ClearIfOwnerFlag()
{
    if (!DAT_00A8E7AC && Owner->Flag)
        Field618 = 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// Partial: after correcting the base call to pass Coord by value,
// 7/194 instructions (3.6%) match. Frame layout and temporary lifetimes differ.
// FUNCTION: GAMEMD 0x453840
Coord_00453840* BuildingClass_00453840::FUN_00453840(
    Coord_00453840* out, int mode, int, int, int)
{
    Point2D projected;
    Coord_00453840 tmp;

    if (At_520->At_157B && (this->*Vtbl->At_408)() > 0) {
        const Point2D* offset = &At_520->At_1588 + At_69C;
        Point2D* client = DAT_00887324->FUN_006D2070(
            &projected, offset);
        int cx = client->X;
        int cy = client->Y;
        Coord_00453840* base = (this->*Vtbl->At_AC)(&tmp);
        return out->Set(base->X + cx, base->Y + cy, base->Z);
    }

    if (At_520->At_E44.X != 0xFFFF || At_520->At_E44.Y != 0xFFFF) {
        Point2D* client = DAT_00887324->FUN_006D2070(
            &projected, &At_520->At_E44);
        int cx = client->X;
        int cy = client->Y;
        if (At_520->At_1764) {
            Coord_00453840 zero = { 0, 0, 0 };
            Coord_00453840* base = FUN_006F3AD0(&tmp, mode, zero);
            return out->Set(base->X + cx, base->Y + cy, base->Z);
        }
        Coord_00453840* base = (this->*Vtbl->At_AC)(&tmp);
        return out->Set(base->X + cx, base->Y + cy, base->Z);
    }

    if (At_520->At_16C6) {
        Coord_00453840* result = FUN_00453BF0(&tmp, mode, 1);
        return out->Set(result->X, result->Y, result->Z);
    }

    Coord_00453840 zero = { 0, 0, 0 };
    Coord_00453840* base = FUN_006F3AD0(&tmp, mode, zero);
    int x = base->X;
    int y = base->Y;
    int z = base->Z;

    if (At_520->At_16C5) {
        Point2D offset;
        offset.X = At_520->At_11E0.X;
        offset.Y = At_520->At_11E0.Y;
        Point2D* client = DAT_00887324->FUN_006D2070(
            &projected, &offset);
        x += client->X;
        y += client->Y;
    }

    return out->Set(x, y, z);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x453A70
// The shared tail (vf_43 plus the pixel offset) sits inside the first block in retail and is entered by a
// goto from the type-offset path.
HBCoord* BuildingBView::vf_192(HBCoord* out, int a)
{
    HBCoord tmp;
    HBPoint2D* offset;
    int ox;
    int oy;
    if (Type->unknown_157B && vf_258() > 0) {
        HBPoint2D pixel;
        offset = BuildingBTactical->Func_6D2070(&pixel, &Type->OccupyPoints[FiringOccupantIndex]);
        ox = offset->X;
        oy = offset->Y;
tail:
        HBCoord* c = vf_43(&tmp);
        out->X = c->X + ox;
        out->Y = c->Y + oy;
        out->Z = c->Z;
        return out;
    }
    BuildingBTypeView* type = Type;
    if (type->PointE44.X == 0xFFFF && type->PointE44.Y == 0xFFFF) {
        if (type->unknown_16C6) {
            *out = *Func_453BF0(&tmp, a, 0);
            return out;
        }
        HBCoord* c = Func_6F3D60(&tmp, a);
        int x = c->X;
        int y = c->Y;
        int z = c->Z;
        if (Type->unknown_16C5) {
            HBPoint2D q = Type->PointOffset;
            HBPoint2D pixel;
            HBPoint2D* o = BuildingBTactical->Func_6D2070(&pixel, &q);
            x += o->X;
            y += o->Y;
        }
        out->X = x;
        out->Y = y;
        out->Z = z;
        return out;
    }
    HBPoint2D pixel2;
    offset = BuildingBTactical->Func_6D2070(&pixel2, &type->PointE44);
    ox = offset->X;
    oy = offset->Y;
    goto tail;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x453D60
void BuildingClass::vf_60(CoordStruct* coord)
{
    CellStruct cell = CellOfCoord(*coord);
    unsigned int& flags = BuildingBMap.Func_5657A0(&cell)->OccupationFlags;
    flags |= 0x80;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x453DC0
void BuildingClass::vf_61(CoordStruct* coord)
{
    CellStruct cell = CellOfCoord(*coord);
    unsigned int& flags = BuildingBMap.Func_5657A0(&cell)->OccupationFlags;
    flags &= ~0x80u;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x453E20
HRESULT __stdcall BuildingBView::Load(IStream* pStm)
{
    int id = Rtti.Fetch_ID();
    BuildingBAbstractIndex.RemoveIndex(id);
    HRESULT hr = Func_70BF50(pStm);
    if (hr < 0)
        return hr;
    new (this) BuildingBView(HBNoInit());
    int newId = Rtti.Fetch_ID();
    BuildingBAbstractIndex.AddIndexOutOfLine(newId, this);
    DAT_00B0C110.SwizzleManagerClass::vf_4(&Type);
    DAT_00B0C110.SwizzleManagerClass::vf_4(&Factory);
    DAT_00B0C110.SwizzleManagerClass::vf_4(&C4AppliedBy);
    DAT_00B0C110.SwizzleManagerClass::vf_4(&FirestormAnim);
    DAT_00B0C110.SwizzleManagerClass::vf_4(&PsiWarnAnim);
    DAT_00B0C110.SwizzleManagerClass::vf_4(&Spotlight);
    Audio7.Func_405BE0();
    Audio8.Func_405BE0();
    DAT_00B0C110.SwizzleManagerClass::vf_4(&SecretProduction);
    int count;
    int i;
    HRESULT r = pStm->Read(&count, 4, 0);
    if (r < 0)
        return r;
    for (i = 0; i < count; i++) {
        void* item;
        r = pStm->Read(&item, 4, 0);
        if (r < 0)
            return r;
        Overpowerers.AddItem(item);
    }
    for (i = 0; i < count; i++)
        DAT_00B0C110.SwizzleManagerClass::vf_4(&Overpowerers.Items[i]);
    r = pStm->Read(&count, 4, 0);
    if (r < 0)
        return r;
    for (i = 0; i < count; i++) {
        BuildingBOccupantView* item;
        r = pStm->Read(&item, 4, 0);
        if (r < 0)
            return r;
        Occupants.AddItem(item);
    }
    for (i = 0; i < count; i++)
        DAT_00B0C110.SwizzleManagerClass::vf_4(&Occupants.Items[i]);
    for (i = 0; i < 21; i++)
        DAT_00B0C110.SwizzleManagerClass::vf_4(&Anims[i]);
    for (i = 0; i < 3; i++)
        DAT_00B0C110.SwizzleManagerClass::vf_4(&Upgrades[i]);
    for (i = 0; i < 8; i++)
        DAT_00B0C110.SwizzleManagerClass::vf_4(&DamageFireAnims[i]);
    LightSource = 0;
    return hr;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x454190
HRESULT __stdcall BuildingClass::Save(IStream* pStm, BOOL fClearDirty)
{
    HRESULT hr = TechnoClass::Save(pStm, fClearDirty);
    if (hr < 0)
        return hr;
    int i;
    int count = Overpowerers.Count;
    HRESULT w = pStm->Write(&count, 4, 0);
    if (w < 0)
        return w;
    for (i = 0; i < count; i++) {
        w = pStm->Write(&Overpowerers.Items[i], 4, 0);
        if (w < 0)
            return w;
    }
    count = Occupants.Count;
    w = pStm->Write(&count, 4, 0);
    if (w < 0)
        return w;
    for (i = 0; i < count; i++) {
        w = pStm->Write(&Occupants.Items[i], 4, 0);
        if (w < 0)
            return w;
    }
    return hr;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x454250
bool BuildingClass::vf_128()
{
    return IsReadyToCommence ? true : false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x454260
void BuildingClass::vf_13(Obj_004A1D30* crc)
{
    TechnoClass::vf_13(crc);
    int c4Left = C4Timer.GetTimeLeft();
    crc->FUN_004A1D50(c4Left);
    int cashLeft = CashProductionTimer.GetTimeLeft();
    crc->FUN_004A1D50(cashLeft);
    crc->FUN_004A1D50(BState);
    crc->FUN_004A1D50(QueueBState);
    crc->FUN_004A1D50(OwnerCountryIndex);
    if (C4AppliedBy)
        crc->FUN_004A1D50(C4AppliedBy->vf_rtti_4());
    crc->FUN_004A1D50(unknown_544);
    if (FirestormAnim)
        crc->FUN_004A1D50(FirestormAnim->vf_rtti_4());
    crc->FUN_004A1D50(FactoryRetryTimer.GetTimeLeft());
    crc->FUN_004A1D50(unknown_5FC);
    crc->FUN_004A1D50(LaserFenceFrame);
    crc->FUN_004A1D50(FirestormWallFrame);
    crc->FUN_004A1CA0(HasPower);
    crc->FUN_004A1CA0(StuffEnabled);
    crc->FUN_004A1CA0(BeingProduced);
    crc->FUN_004A1CA0(ShouldRebuild);
    crc->FUN_004A1CA0(AI_Sellable);
    crc->FUN_004A1CA0(IsReadyToCommence);
    crc->FUN_004A1CA0(IsBeingRepaired);
    crc->FUN_004A1CA0(NeedsRepairs);
    crc->FUN_004A1CA0(C4Applied);
    crc->FUN_004A1CA0(NoCrew);
    crc->FUN_004A1CA0(unknown_bool_6E1);
    crc->FUN_004A1CA0(unknown_bool_6E2);
    crc->FUN_004A1CA0(HasBeenCaptured);
    crc->FUN_004A1CA0(ActuallyPlacedOnMap);
    crc->FUN_004A1CA0(HasEngineer);
    crc->FUN_004A1CA0(unknown_bool_6E5);
    crc->FUN_004A1CA0(IsDamaged);
    crc->FUN_004A1D50((unsigned short)LightTint);
    crc->FUN_004A1C10(UpgradeLevel);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4544A0
// Both arms compute one flag and share a single `return 3` / `return 5` pair,
// which is retail's layout (one block each). Returning from inside the arms
// makes cl duplicate the `return 5` epilogue (70.1%).
int BuildingBView::vf_26(bool a, BuildingBTargetView* target)
{
    char level = Translucency;
    if (level != 0) {
        if (level > 10) {
            bool keep;
            if (a) {
                keep = false;
                if (target != 0) {
                    HBCoord loc = Location;
                    HBCell cell = BuildingBCellOf(loc);
                    keep = BuildingBMap.Func_5657A0(&cell)->Func_4870D0(target->unknown_30);
                }
            } else {
                keep = unknown_41A || vf_202() || BuildingBGlobal_00B73550 == 0
                    || (Session_00A8B238.GameMode != 0 && Owner != 0 && DAT_00A83D4C != 0
                        && DAT_00A83D4C->IsAlliedWith(Owner) && Owner->IsAlliedWith(DAT_00A83D4C));
            }
            if (keep)
                return 3;
            return 5;
        }
        return (level > 5) + 1;
    }
    return Func_703860(a, target);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x454730
//
// Drop animation slot 0x13, then restart each slot whose record is flagged in
// the type, choosing the damaged name once health is at the yellow threshold.
void BuildingClass::FUN_00454730()
{
    DestroyNthAnim(0x13);

    for (int slot = 0; slot < 0x15; slot++) {
        if (Type->BuildingAnim[slot].PoweredSpecial) {
            int damaged = GetHealthPercentage() <= RulesInstance->ConditionYellow;
            const char* animName;
            if (damaged) {
                animName = Type->BuildingAnim[slot].Damaged;
            } else {
                animName = Type->BuildingAnim[slot].Anim;
            }
            if (animName && *animName) {
                PlayAnim(animName, slot, damaged, false, 0);
            }
        }
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x454930
//
// Start animation slot 0x13 (damaged name once health is at the yellow
// threshold), then drop every slot whose record is flagged in the type.
void BuildingClass::FUN_00454930()
{
    int damaged = GetHealthPercentage() <= RulesInstance->ConditionYellow;
    const char* animName;
    if (damaged) {
        animName = Type->BuildingAnim[0x13].Damaged;
    } else {
        animName = Type->BuildingAnim[0x13].Anim;
    }
    if (animName && *animName) {
        PlayAnim(animName, 0x13, damaged, false, 0);
    }

    for (int slot = 0; slot < 0x15; slot++) {
        if (Type->BuildingAnim[slot].PoweredSpecial) {
            DestroyNthAnim(slot);
        }
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x454CF0
// For a type that carries the cloaking data bool: mark the data present, drop
// the radius when it equals the type's, and request a redraw.
void BuildingClass::FUN_00454CF0()
{
    if (Type->bools_16A4[0x23])
    {
        unsigned char radius = CloakRadius;
        HasCloakingData = 1;
        if (radius == Type->CloakRadiusInCells)
        {
            CloakRadius = 0;
        }
        NeedsRedraw = 1;
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x454D30
// The opposite step: flag the data as reversed, restore the radius from the
// type when it is zero, and request a redraw.
void BuildingClass::FUN_00454D30()
{
    if (Type->bools_16A4[0x23])
    {
        unsigned char radius = CloakRadius;
        HasCloakingData = -1;
        if (radius == 0)
        {
            CloakRadius = Type->CloakRadiusInCells;
        }
        NeedsRedraw = 1;
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x454D70
void Chain_00454D70::PokeAll()
{
    for (Node_00454D70* n = Head; n; n = n->Next)
    {
        int t = n->Type();
        if (t == 1 || t == 0xF || t == 2)
            n->Poke();
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x454DB0
// CAPPED at 0.6% (5 of 648 instructions; 629 compiled; retail-only 18 `mov`, 5 `xor`, 2 `test`, `jge`, `jmp`;
// compiled-only 2 `cmp`, `jl`, 4 `pop`, `ret`). The semantics are recovered (build-up/sell-down translucency ramp,
// the cloak-sensor sweep over the cells under the sensor radius and the neighbour refresh) but the frame is 0x58
// against retail 0x44 and cl keeps `this` in ebp and zero in edi where retail keeps this in esi and zero in ebp, so
// the position-based score collapses. Variants tried: per-use coordinate temporaries, one shared coordinate temporary
// (kept), and wrapping the body in positive ifs instead of early returns.
void BuildingBView::vf_260(bool refresh)
{
    if (Type != 0) {
    HBCoord tmp;
    HBCell cell = BuildingBCellOf(*vf_18(&tmp));
    if (unknown_220 == 1) {
        if (Translucency < 15) {
            char step = Translucency + 1;
            Translucency = step;
            if (step == 1 || step == 6 || step == 11)
                NeedsRedraw = true;
            int level = step;
            if (level == 15 && vf_26(false, 0) == 5)
                level = 16;
            for (int i = 0; i < 21; i++) {
                if (Anims[i])
                    Anims[i]->unknown_178 = level;
            }
            if (Translucency == 15) {
                unknown_220 = 2;
                if (unknown_30C) {
                    unknown_30C->vf_8(1);
                    unknown_30C = 0;
                }
            }
        }
    } else if (unknown_220 == 3) {
        if (Translucency >= 0) {
            if (Translucency > 0)
                Translucency = Translucency - 1;
            char step = Translucency;
            if (step == 0 || step == 5 || step == 10)
                NeedsRedraw = true;
            int level = step;
            if (level == 15 && vf_26(false, 0) == 5)
                level = 16;
            for (int i = 0; i < 21; i++) {
                if (Anims[i])
                    Anims[i]->unknown_178 = level;
            }
            if (Translucency == 0) {
                unknown_220 = 0;
                if (unknown_30C == 0) {
                    HBCoord offset = Type->unknown_coord_768;
                    if (!(offset == BuildingBEmptyCoord)) {
                        BuildingBParticleSystemView* system = 0;
                        HBCoord where = Location + offset;
                        HBCoord here = Location;
                        BuildingBCellView* under = BuildingBMap.Func_565730(&here);
                        system = new BuildingBParticleSystemView(Type->unknown_764, &where, under, 0,
                                                                 &BuildingBEmptyCoord, 0);
                        unknown_30C = system;
                    }
                }
            }
        }
    }
    if (unknown_220 == 2 && vf_169())
        vf_279(0);
    if (unknown_220 == 0 && vf_168())
        vf_280(0);
    if (HasCloakingData && Type->unknown_16C7) {
    BuildingBSurfaceView* surface = BuildingBSurface;
    int owner = Owner->ArrayIndex;
    int size = surface->vf_31();
    int half = size / 2;
    if (HasCloakingData > 0) {
        if (CloakRadius == Type->unknown_1707) {
            HasCloakingData = 0;
            return;
        }
        CloakRadius = CloakRadius + 1;
        surface->vf_6(0);
        BuildingBColor16 color;
        surface->Func_7BB920(half, half, CloakRadius, *surface->vf_30(&color, 1));
        char* mask = surface->vf_23(0, 0);
        HBCell origin;
        origin.X = cell.X - half;
        origin.Y = cell.Y - half;
        for (int y = 0; y < size; y++) {
            for (int x = 0; x < size; x++) {
                if (*mask++ == 0)
                    continue;
                HBCell at(origin.X + x, origin.Y + y);
                BuildingBCellView* target = BuildingBMap.Func_5657A0(&at);
                if (target->Func_4870B0(owner))
                    continue;
                target->Func_487110(owner);
                for (BuildingBObjectView* object = target->FirstObject; object; object = object->NextObject) {
                    int kind = object->vf_11();
                    if (kind == 1 || kind == 0xF || kind == 2)
                        object->vf_264();
                }
                BuildingBView* building = target->Func_47C520();
                if (building && building->Owner->ArrayIndex == owner) {
                                        HBCell there = BuildingBCellOf(*building->vf_18(&tmp));
                    if (there.X == cell.X && there.Y == cell.Y) {
                        CloakRadius = CloakRadius - 1;
                        return;
                    }
                }
            }
        }
    } else {
        if (CloakRadius == 0) {
            HasCloakingData = 0;
            return;
        }
        CloakRadius = CloakRadius - 1;
        surface->vf_6(2);
        BuildingBColor16 color;
        surface->Func_7BB920(half, half, Type->unknown_1707, *surface->vf_30(&color, 0));
        if (CloakRadius)
            surface->Func_7BB920(half, half, CloakRadius, *surface->vf_30(&color, 1));
        char* mask = surface->vf_23(0, 0);
        HBCell origin;
        origin.X = cell.X - half;
        origin.Y = cell.Y - half;
        for (int y = 0; y < size; y++) {
            for (int x = 0; x < size; x++) {
                if (*mask++ != 0)
                    continue;
                HBCell at(origin.X + x, origin.Y + y);
                BuildingBCellView* target = BuildingBMap.Func_5657A0(&at);
                if (!target->Func_4870B0(owner))
                    continue;
                target->Func_487130(owner);
                for (BuildingBObjectView* object = target->FirstObject; object; object = object->NextObject) {
                    int kind = object->vf_11();
                    if (kind == 1 || kind == 0xF || kind == 2)
                        object->vf_264();
                }
                BuildingBView* building = target->Func_47C520();
                if (building && building->Owner->ArrayIndex == owner) {
                                        HBCell there = BuildingBCellOf(*building->vf_18(&tmp));
                    if (there.X == at.X && there.Y == at.Y) {
                        if (!refresh) {
                            CloakRadius = CloakRadius + 1;
                            return;
                        }
                    }
                }
            }
        }
        if (CloakRadius == 0) {
            for (int i = 0; i < BuildingBBuildingCount; i++) {
                BuildingBView* other = BuildingBBuildingItems[i];
                if (other->IsAlive && other != this && other->Type->unknown_16C7 && other->vf_212()
                    && !other->HasCloakingData) {
                                        HBCell there = BuildingBCellOf(*other->vf_18(&tmp));
                    short dx = cell.X - there.X;
                    short dy = cell.Y - there.Y;
                    int reach = Type->unknown_1707 + 2;
                    if (dx * dx + dy * dy < reach * reach * 4) {
                        if (other->Type->unknown_16C7) {
                            char old = other->CloakRadius;
                            other->HasCloakingData = 1;
                            if (old == other->Type->unknown_1707)
                                other->CloakRadius = 0;
                            other->NeedsRedraw = true;
                        }
                        if (other->CloakRadius)
                            other->CloakRadius = other->CloakRadius - 1;
                    }
                }
            }
        }
    }
    }
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4555D0
// Every refusal shares one epilogue in retail; written as separate returns cl gives each its own.
bool BuildingClass::vf_212()
{
    int two = 2;
    if (!HasPower && Overpowerers.Count < two)
        goto refuse;
    if (EMPLockRemaining > 0)
        goto refuse;
    if (Health == 0)
        goto refuse;
    if (Type->bools_1570[0x1573 - 0x1570] && Type->PowerDrain > 0 && Owner->GetPowerPercentage() < 1.0) {
        if (Overpowerers.Count < two)
            goto refuse;
    }
    {
        BuildingTypeClass* type = Type;
        if (type->bools_1570[0x1574 - 0x1570]) {
            HouseClass* owner = Owner;
            if (owner->PowerBlackoutTimer.GetTimeLeft() != 0)
                goto refuse;
            if (owner->IsBeingDrained)
                goto refuse;
        }
        if (type->bools_154B[0x1552 - 0x154B] && !HasEngineer)
            goto refuse;
    }
    if (vf_97() != 0x12 && vf_97() != 0x13)
        return true;
refuse:
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4556D0
// CAPPED at 3.8% (4 of 105). Retail pushes one callee-saved register late (ahead of the loop nest) and gives the radius
// ebx, the outer variable ebp, the inner variable esi and the squared outer variable edi; cl takes the radius in ebp and the
// outer variable in edi. Cause unproven. Variants tried: declared loop variables, swapped field arithmetic, an operator+
// cell sum, an operator== empty-cell test, R*R inline, a probe pointer to the cell, a hoisted outer-square local (kept;
// it stopped cl caching the cell word and lifted 455980/455A80 from 10.8/7.9), loop variables declared up front, a deferred
// radiusSq assignment, owner/radius declaration swap.
void BuildingBView::vf_318(HBCell cell)
{
    int radius = Type->unknown_1707;
    int radiusSq = radius * radius;
    int owner = Owner->ArrayIndex;
    if (cell == BuildingBEmptyCell) {
        HBCoord tmp;
        cell = BuildingBCellOf(*vf_18(&tmp));
    }
    for (int dy = -radius; dy < radius; dy++) {
        int dySq = dy * dy;
        for (int dx = -radius; dx < radius; dx++) {
            if (dx * dx + dySq < radiusSq) {
                HBCell c;
                c.X = cell.X + dx;
                c.Y = cell.Y + dy;
                BuildingBCellView* target = BuildingBMap.Func_5657A0(&c);
                target->Func_487160(owner);
                for (BuildingBObjectView* object = target->FirstObject; object; object = object->NextObject) {
                    int kind = object->vf_11();
                    if (kind == 1 || kind == 0xF || kind == 2)
                        object->vf_264();
                }
            }
        }
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x455820
// CAPPED at 24.3% (instruction multiset identical). Retail pushes one callee-saved register late (ahead of the loop nest) and gives the radius
// ebx, the outer variable ebp, the inner variable esi and the squared outer variable edi; cl takes the radius in ebp and the
// outer variable in edi. Cause unproven. Variants tried: declared loop variables, swapped field arithmetic, an operator+
// cell sum, an operator== empty-cell test, R*R inline, a probe pointer to the cell, a hoisted outer-square local (kept;
// it stopped cl caching the cell word and lifted 455980/455A80 from 10.8/7.9), loop variables declared up front, a deferred
// radiusSq assignment, owner/radius declaration swap.
void BuildingBView::vf_317(HBCell cell)
{
    if (!vf_212())
        return;
    int radius = Type->unknown_5F0;
    int radiusSq = radius * radius;
    int owner = Owner->ArrayIndex;
    if (cell == BuildingBEmptyCell) {
        HBCoord tmp;
        cell = BuildingBCellOf(*vf_18(&tmp));
    }
    for (int dy = -radius; dy < radius; dy++) {
        int dySq = dy * dy;
        for (int dx = -radius; dx < radius; dx++) {
            if (dx * dx + dySq < radiusSq) {
                HBCell c;
                c.X = cell.X + dx;
                c.Y = cell.Y + dy;
                BuildingBCellView* target = BuildingBMap.Func_5657A0(&c);
                target->Func_487150(owner);
                for (BuildingBObjectView* object = target->FirstObject; object; object = object->NextObject) {
                    int kind = object->vf_11();
                    if (kind == 1 || kind == 0xF || kind == 2)
                        object->vf_264();
                }
            }
        }
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x455980
// CAPPED at 33.7% (multiset differs by 1 `mov`). Retail pushes one callee-saved register late (ahead of the loop nest) and gives the radius
// ebx, the outer variable ebp, the inner variable esi and the squared outer variable edi; cl takes the radius in ebp and the
// outer variable in edi. Cause unproven. Variants tried: declared loop variables, swapped field arithmetic, an operator+
// cell sum, an operator== empty-cell test, R*R inline, a probe pointer to the cell, a hoisted outer-square local (kept;
// it stopped cl caching the cell word and lifted 455980/455A80 from 10.8/7.9), loop variables declared up front, a deferred
// radiusSq assignment, owner/radius declaration swap.
void BuildingBView::vf_320(HBCell cell)
{
    int radius = Type->unknown_5F4;
    int radiusSq = radius * radius;
    int owner = Owner->ArrayIndex;
    if (cell == BuildingBEmptyCell) {
        HBCoord tmp;
        cell = BuildingBCellOf(*vf_18(&tmp));
    }
    for (int dy = -radius; dy < radius; dy++) {
        int dySq = dy * dy;
        for (int dx = -radius; dx < radius; dx++) {
            if (dx * dx + dySq < radiusSq) {
                HBCell c;
                c.X = cell.X + dx;
                c.Y = cell.Y + dy;
                BuildingBMap.Func_5657A0(&c)->Func_487180(owner);
            }
        }
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x455A80
// CAPPED at 34.8% (multiset differs by 1 `mov`). Retail pushes one callee-saved register late (ahead of the loop nest) and gives the radius
// ebx, the outer variable ebp, the inner variable esi and the squared outer variable edi; cl takes the radius in ebp and the
// outer variable in edi. Cause unproven. Variants tried: declared loop variables, swapped field arithmetic, an operator+
// cell sum, an operator== empty-cell test, R*R inline, a probe pointer to the cell, a hoisted outer-square local (kept;
// it stopped cl caching the cell word and lifted 455980/455A80 from 10.8/7.9), loop variables declared up front, a deferred
// radiusSq assignment, owner/radius declaration swap.
void BuildingBView::vf_319(HBCell cell)
{
    if (!vf_212())
        return;
    int radius = Type->unknown_5F4;
    int radiusSq = radius * radius;
    int owner = Owner->ArrayIndex;
    if (cell == BuildingBEmptyCell) {
        HBCoord tmp;
        cell = BuildingBCellOf(*vf_18(&tmp));
    }
    for (int dy = -radius; dy < radius; dy++) {
        int dySq = dy * dy;
        for (int dx = -radius; dx < radius; dx++) {
            if (dx * dx + dySq < radiusSq) {
                HBCell c;
                c.X = cell.X + dx;
                c.Y = cell.Y + dy;
                BuildingBMap.Func_5657A0(&c)->Func_487170(owner);
            }
        }
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x455B90
// One bit per edge neighbour (directions 0, 2, 4, 6 -> bits 0..3) that holds a
// live, in-play building whose type has the flag at +0x16C0.
unsigned int BuildingClass::FUN_00455B90()
{
    CoordStruct here = Location;
    unsigned int mask = 0;
    CellClass* cell = DAT_0087F7E8.FUN_00565730(&here);
    for (int dir = 0; dir < 8; dir += 2) {
        BuildingClass* neighbour = cell->GetNeighbourCell(dir)->GetBuilding();
        if (neighbour != 0 && neighbour->Type->bools_16A4[0x1C] && !neighbour->InLimbo && neighbour->IsAlive) {
            mask |= 1 << (dir >> 1);
        }
    }
    return mask;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x455C20
// CAPPED at 75.3% (multiset identical, 89 instructions; the frame is 0x3C against retail 0x34, so every stack
// offset after the prologue differs). Variants tried: field-by-field rect sums, an operator+ without the named
// `shifted` temporary, an early-return hit path, and 40 declaration orders of the locals.
HBRect* BuildingBView::vf_75(HBRect* out)
{
    HBCoord tmp;
    HBCoord coord = *vf_43(&tmp);
    HBPoint2D point = BuildingBTactical->Offset;
    HBRect rect;
    if (coord == unknown_coord_64C && point == unknown_point_658) {
        rect = unknown_rect_63C;
    } else {
        HBPoint2D pixel;
        BuildingBTactical->Func_6D2140(&coord, &pixel);
        HBRect typeRect;
        HBRect shifted = *Type->Func_465570(&typeRect) + pixel;
        rect = shifted;
        unknown_coord_64C = coord;
        unknown_point_658 = point;
        unknown_rect_63C = rect;
    }
    *out = rect;
    return out;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x455D50
void BuildingClass::SetDestination(AbstractClass* target, bool a2)
{
    if (CurrentMission == 0x13)
        return;
    if (vf_161() || Type->bools_16A4[0x16B9 - 0x16A4])
        SetArchiveTarget(target);
    TechnoClass::SetDestination(target, a2);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x455DA0
bool BuildingClass::vf_161()
{
    BuildingTypeClass* type = Type;
    int mode = type->Factory;
    if (mode != 0x28 && mode != 0x10 && !type->bools_16A4[0x16AC - 0x16A4] && !type->bools_16A4[0x16A9 - 0x16A4])
        return false;
    return true;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x456580
//
// Mark every cell of the object's foundation as occupied by it, then record that
// it is placed.
//
// PARTIAL (74.3%, 26/35) — identical multiset, scheduling only. Retail loads
// the object's own coordinate before the foundation entry's in both sums
// (`MOV EAX,[ESI+0x208]; MOV EDX,[ECX+EDI*8]; ADD EAX,EDX`), computes the x
// sum first and pushes y, x, receiver; cl 8804 loads the entry's component
// first in both sums and computes y first. Binding the entry to a pointer
// local, which is what retail's `LEA ECX,[ECX+EDI*8]` between the two
// component loads describes, lifts this from the 68.6% the earlier pass
// recorded to 74.3% — the item address is formed once and both components
// come off it.
//
// Variants measured this pass, all 74.3% unless noted: the entry as a pointer
// local, as a `const&` and as a by-value copy (28.6%, a real struct copy);
// the sums as `member; += entry`, as `entry + member`, and through an inline
// `SumRL(b, a) { return a + b; }` helper exploiting cl's right-to-left
// argument evaluation to make the member the first operand evaluated; the
// whole cell-mark lifted into an inline helper taking the base coordinates
// and the entry pointer (the flattened-boundary lever); an inline forwarder
// with its parameters declared `(o, y, x)` so that cl's right-to-left order
// evaluates x first, both with by-value and `const&` parameters; and the
// base coordinates read through `const&` locals. The 68.6% forms (both sums
// written inline in the call, and locals without the entry pointer) are
// strictly worse. cl's load order inside a two-term sum is not reachable
// from source here — the remaining nine positions are that tie-break.
//
// The cell count is re-read on every iteration — retail's `MOV EAX,[EBX+0x10]` at
// 0x4565CA is inside the loop — so the bound stays a member read.
//
// TAIL-MERGE DIAGNOSTIC (eleventh-batch lever): does NOT apply here.
// Retail's callee-saved pushes sit exactly where ours do (prologue EBX, ESI,
// EDI on both sides), the
// number of epilogues agrees, and the compiled block order already matches,
// so there are no merged return blocks to split. The residual is register
// naming downstream of that, not a prologue hoist.
void BuildingClass::vf_293()
{
    DynamicVectorClass<Point2D>* cells = DAT_0087F7E8.FUN_00656580(Type);

    int i = 0;
    while (i < cells->Count) {
        Point2D* entry = &cells->Items[i];
        int x = RadarPosition.X + entry->X;
        int y = RadarPosition.Y + entry->Y;
        DAT_0087F7E8.FUN_00655560(this, x, y);
        i++;
    }

    IsRadarTracked = 1;
}

// GLOBAL: GAMEMD 0xA83DEC / 0xA83DF8 -- InfantryClass array items and count.
extern InfantryClass** DAT_00A83DEC;
extern int DAT_00A83DF8;

// The sum of two screen points.
static inline Point2D PointSum(const Point2D& a, const Point2D& b)
{
    Point2D r;
    r.X = a.X + b.X;
    r.Y = a.Y + b.Y;
    return r;
}


// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4565E0
// Takes the building's foundation cells off the radar and stops tracking it.
void BuildingClass::vf_294()
{
    DynamicVectorClass<Point2D>* foundation = DAT_0087F7E8.FUN_00656580(Type);
    for (int i = 0; i < foundation->Count; i++) {
        Point2D at = PointSum(RadarPosition, foundation->Items[i]);
        DAT_0087F7E8.FUN_00655740(this, at.X, at.Y);
    }
    IsRadarTracked = false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x456640
// Redraws the radar pixel of every foundation cell.
void BuildingClass::vf_295()
{
    DynamicVectorClass<Point2D>* foundation = DAT_0087F7E8.FUN_00656580(Type);
    for (int i = 0; i < foundation->Count; i++) {
        Point2D point = PointSum(RadarPosition, foundation->Items[i]);
        DAT_0087F7E8.FUN_006562D0(&point);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4566B0
//
// Radius (in cells) of the radial range indicator drawn round a selected
// building. Psychic detectors use their detection radius; gap generators one
// of two gap radii depending on super-charge; cloak generators and sensor
// arrays the cloak radius; anything else its primary weapon's range in cells,
// and zero when it has no usable weapon.
//
// The gap branch is a ternary: each arm loads its byte into CL and VC6
// duplicates the `MOVSX EAX,CL` epilogue into both, which is retail's shape;
// two `return`s emit the sign-extension straight from memory.
//
// PARTIAL (42.9%, 27/63; mnemonic multiset identical). Retail zeroes EBX at
// entry (`XOR EBX,EBX` between `MOV ESI,ECX` and `PUSH EDI`), tests the
// psychic radius straight out of EAX (`JG` to the shared epilogue), keeps the
// weapon in EDI and returns the zero from the two weapon-rejecting exits via
// `MOV EAX,EBX`. This form -- the radius read into the result variable, the
// weapon block nested under `result <= 0`, `result = 0` after the two
// guards, one trailing `return result` -- is the only phrasing that
// reproduces retail's control flow and instruction multiset exactly; the
// residual is register naming only: cl 8804 keeps the result in EDI (loads
// and tests the radius there, `XOR EDI,EDI` late, before the call) and the
// weapon in EBX, where retail has the constant zero in EBX from entry and the
// radius in EAX. Variants tried: nested `if` with one trailing `return 0`;
// two `return 0`s (each folds to its own `XOR EAX,EAX`); `int result = 0`
// returned at the end (constant-folded, no register, 1.6%); the same with the
// range path routed through `result` (12.7%, takes EBX but merges the range
// epilogue); `int range = 0` conditionally overwritten then `return 0` /
// `return range` (folded, 1.6%); a `zero` local used in the compares and the
// returns (folded); `result = radius` in the positive branch with an
// else-chain (15.6%: takes EBX but pays `MOV EBX,ECX`); `result = Range`
// re-zeroed on the fall path (folded); /Ox and /O1 (no register). Same class
// as "Zero not held in a register" in the methodology; the 8447-vs-8804
// constant-register choice is the suspected cause.
//
// TAIL-MERGE DIAGNOSTIC (eleventh-batch lever): does NOT apply. Both sides
// emit five separate epilogues at the same five sites and push EBX/ESI/EDI in
// the same order; nothing is merged that retail leaves split. The residual is
// the shared-zero class, not a colouring shift: retail hoists `XOR EBX,EBX`
// above `PUSH EDI` at entry and spends it once on `MOV EAX,EBX` at the shared
// zero exit, i.e. it splits the live range of `result` between EAX (the radius
// arm) and EBX (the zero arm), where cl 8804 keeps one register (EDI) for both
// and materialises the zero at the `result = 0` statement.
int BuildingClass_004566B0::GetRadialIndicatorRange()
{
    Type_004566B0* type = this->Type;
    int result = type->PsychicDetectionRadius;

    if (result <= 0) {
        if (type->GapGenerator)
            return this->GapSuperCharged ? type->SuperGapRadiusInCells
                                         : type->GapRadiusInCells;

        if (type->SensorArray || type->CloakGenerator)
            return type->CloakRadiusInCells;

        result = 0;
        WeaponStruct_004566B0* weapon = this->GetPrimaryWeapon();
        if (this->FUN_0070E240(weapon)) {
            int range = weapon->WeaponType->Range;
            if (range > 0)
                return range / 256;
        }
    }
    return result;
}

// The function-local white of the flashing glow; the empty destructor is registered with atexit (0x456970 is a RET).
class BuildingBWhite : public ColorStruct
{
public:
    BuildingBWhite()
    {
        R = 0xFF;
        G = 0xFF;
        B = 0xFF;
    }
    ~BuildingBWhite() {}
};

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x456750
void BuildingBView::vf_76(ColorStruct tint)
{
    int level = Func_4566B0();
    if (level > 0 && HasPower && Owner->IsControlledByCurrentPlayer()) {
        if (Type->unknown_1708) {
            static BuildingBWhite white;
            tint = Owner->Color;
            unsigned int phase = (timeGetTime() >> 1) & 0x3FF;
            if (!(phase & 0x200)) {
                if (!(phase & 0x100))
                    tint.FUN_006612C0(~phase & 0xFF, white);
                HBCoord tmp;
                BuildingBFunc_456980(0, 0, *vf_18(&tmp), tint, (float)level, 0, 1);
            }
            unsigned int spark = (unsigned int)((level + 0.5) / BuildingBFunc_4CAC40(2.0) * 60.0) * phase >> 10;
            if (spark > 0x20) {
                HBCoord tmp;
                BuildingBFunc_456980(0, 0, *vf_18(&tmp), Owner->Color, (float)spark, 1, 1);
            }
        } else {
            HBCoord tmp;
            BuildingBFunc_456980(tint.R, 1, *vf_18(&tmp), Owner->Color, (float)level, 0, 1);
        }
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x456970
// Empty function.
void __cdecl FUN_00456970()
{
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x456E00
// CAPPED at 95.2% (multiset identical, vptr register naming only: retail loads the vf_88 vptr into eax, cl into edx).
// Variants tried: ||-chain kept here, an if/goto form, a split frame declaration, a local for the vf_111 result.
void BuildingBView::vf_82(int a)
{
    if (a)
        NeedsRedraw = true;
    Func_6F9DD0(a);
    int frame;
    frame = vf_121();
    BuildingBCellView* cell = vf_111();
    int base = vf_281(cell->unknown_10A);
    if (vf_88() || (unknown_294 && unknown_294->unknown_50 == BuildingBCastBuilding(this)))
        base = Func_70E360(base);
    unknown_short_700 = base;
    unsigned int mask = (unsigned short)base;
    for (int i = 0; i < 21; i++) {
        BuildingBAnimObjView* anim = Anims[i];
        if (anim) {
            if (anim->unknown_C8 && anim->unknown_C8->unknown_35C) {
                anim->unknown_D4 = frame;
                anim->unknown_FC = mask;
            }
            ApplyAnimLevel();
        }
    }
    ApplyAnimLevel();
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x456F80
int BuildingClass::vf_281(int a)
{
    if ((DurationRemaining & 2) == 2) {
        if (a > 0x5DC)
            return a - 0x1F4;
        return a + 0x1F4;
    }
    return a;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x456FB0
//
// BLOCK-ORDER DELTA (status partial, 76.2% - 32/42). Everything through the
// branchless cast and the holder comparison is exact. What is left is which of
// the two tails VC6 lays down first: retail puts the override call at 0x457002
// and the plain return at 0x45700F, and we emit them the other way round, which
// inverts the last two branches with them. Four layouts were tried - the
// override as the last statement, as an `else`, reached by `goto` with the
// plain return labelled after it, and with both guards inverted - and VC6 keeps
// the plain return first every time. The instruction stream is otherwise
// identical.
int Obj_00456FB0::FUN_00456FB0(int value)
{
    int answer = vt_464(value);

    if (!vt_160()) {
        // Positive guard: retail's `JZ` at 0x456FDB jumps forward to the plain
        // return, so the holder-present case is the fall-through.
        if (Holder == 0) {
            goto plain;
        }

        // The null check is a real branch and only the type test is branchless,
        // so the two are written as separate constructs. Folded into one `&&`
        // VC6 branches on the type test as well. The zero arm is the
        // fall-through, which is why it is written as `this == 0` first.
        Obj_00456FB0* typed;

        if (this == 0) {
            typed = 0;
        } else {
            typed = (WhatAmI() == 6) ? this : 0;
        }

        if (Holder->Current != typed) {
            goto plain;
        }
    }

    // The override takes the *answer*, not the original argument: retail pushes
    // EDI, which `MOV EDI,EAX` loaded from the first call's result. It is
    // written before the plain return so VC6 lays its block out first, matching
    // retail's 0x457002-then-0x45700F order.
    return FUN_0070E360(answer);

plain:
    return answer;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x457020
// PARTIAL 67.4%, multiset identical. `return false` is the last statement, so
// every refusal shares the final block and the two `return true` blocks stay
// separate (retail has four return blocks). Remaining delta is register choice:
// retail keeps `this` in edi, the two pixel offsets in ebx/ebp and &Location in
// esi; cl keeps this in esi and the offsets in edi/ebx. Also tried: the corner
// from the `here` copy (31.2%) and a &Location pointer local (no change).
bool BuildingBView::vf_201(int* flag)
{
    if (Type->unknown_C9A)
        return false;
    if (InLimbo)
        return false;
    if (Owner->IsControlledByCurrentPlayer())
        return unknown_41B ? true : false;
    {
        HBCoord tmp;
        HBCell cell = BuildingBCellOf(*vf_18(&tmp));
        if (!BuildingBMap.Func_578460(&cell, 1))
            return false;
    }
    int widthPixels = (Type->Func_45ECA0(0) << 8) - 0x100;
    int heightPixels = (Type->Func_45EC90() << 8) - 0x100;
    bool blocked;
    HBCoord here = Location;
    if (BuildingBMap.Func_586360(&here)) {
        HBCoord corner;
        corner.X = Location.X + heightPixels;
        corner.Y = Location.Y + widthPixels;
        corner.Z = Location.Z;
        if (BuildingBMap.Func_586360(&corner) && BuildingBGlobal_00B73550)
            blocked = true;
        else
            blocked = false;
    } else {
        blocked = false;
    }
    if (unknown_220 != 2 && Translucency != 0xF && !IsFogged && !blocked)
        return true;
    if (vf_202()) {
        if (!DAT_00A83D4C->IsAlliedWith(Owner) && !IsFogged && !blocked)
            *flag = 1;
        return true;
    }
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4575B0
//
// Drain the whole array, last entry first, then run the finishing slot.
//
// The loop's index is the count itself and nothing here decrements it — the call
// through 0x451690 is what shortens the array, so the loop terminates through a
// side effect. That is why the count is re-read at the bottom rather than cached.
//
// The target pointer is re-read on each of its four uses; retail reloads
// `[ESI+0x21C]` every time rather than holding it.
void Obj_004575B0::FUN_004575B0()
{
    int one = 1;

    while (this->Count > 0) {
        Item_004575B0* item = this->Items[this->Count];
        int taken = (item->*item->Vptr->At_B8)(this->Target, one);
        this->Target->FUN_004F9950(taken);
        this->FUN_00451690();
        this->Target->At_5778 = (char)one;
        this->Target->At_5779 = (char)one;
    }

    (this->*this->Vptr->At_1A0)(one);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x457620
bool BuildingClass::vf_32()
{
    return Type->IsVehicle();
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x457630  (__thiscall)
// Index of the first super-weapon this building hosts that is currently active
// for the owning house; returns the raw type index (-1 sentinel) otherwise.
int BuildingClass::FirstActiveSWIdx()
{
    int idx = this->Type->SuperWeapon;
    if (idx != -1)
    {
        SWChainNode* node = g_SWArray[idx];
        SWChainC8* sw = node->field_28->field_C8;
        if (sw && !this->Owner->ActiveBuildingTypes.FUN_0049FAE0(sw->field_DF8))
            return -1;
    }
    return this->Type->SuperWeapon;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x457690  (__thiscall)
// As FirstActiveSWIdx, for the building's second hosted super-weapon.
int BuildingClass::SecondActiveSWIdx()
{
    int idx = this->Type->SuperWeapon2;
    if (idx != -1)
    {
        SWChainNode* node = g_SWArray[idx];
        SWChainC8* sw = node->field_28->field_C8;
        if (sw && !this->Owner->ActiveBuildingTypes.FUN_0049FAE0(sw->field_DF8))
            return -1;
    }
    return this->Type->SuperWeapon2;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4576F0
// Sends away every infantryman standing on this building's cell who is not heading elsewhere.
void BuildingClass::vf_184()
{
    for (int i = 0; i < DAT_00A83DF8; i++) {
        InfantryClass* unit = DAT_00A83DEC[i];
        BuildingClass* building = DAT_0087F7E8.FUN_00565730(unit->vf_19(0))->GetBuilding();
        if (unit->IsAlive && building && building == this) {
            if (unit->Destination == 0 || unit->Destination == building)
                unit->vf_93(DAT_0089C848, 1, 1);
        }
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x457770
// CAPPED at 15.4% (multiset: retail-only 5 `mov`, 2 `test`, 1 `add`; cl-only 1 `lea`, 2 `cmp`). Retail keeps the loop
// counters and both cell counts in stack slots and tests the found object and the type flag through registers
// (`mov cl,[eax+0xC9D]; test cl,cl`) where cl emits `cmp byte ptr`. Variants tried: operator+ cell sum, field-wise
// cell sum, goto-based exits, hoisted loop variables, a type local for the flag.
bool BuildingBView::vf_168()
{
    if (!Func_6FBDC0())
        goto refuse;
    {
        HBCell tmp;
        HBCell base = *vf_110(&tmp);
        int width = Type->Func_45EC90();
        int height = Type->Func_45ECA0(0);
        int x;
        int y;
        for (x = -1; x <= width; x++) {
            for (y = -1; y <= height; y++) {
                HBPoint2D zero;
                zero.X = 0;
                zero.Y = 0;
                HBCell cell;
                cell.X = base.X + x;
                cell.Y = base.Y + y;
                BuildingBView* found = BuildingBMap.Func_5657A0(&cell)->Func_47C3D0(&zero, 0, 0);
                if (found == this) {
                    HBCell again = cell;
                    found = BuildingBMap.Func_5657A0(&again)->Func_47EC40(0);
                }
                if (found && found->Owner != Owner && found->vf_33()->unknown_C9D)
                    goto refuse;
            }
        }
    }
    return true;
refuse:
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4578C0
// CAPPED at 15.4% (multiset: retail-only 5 `mov`, 2 `test`, 1 `add`; cl-only 1 `lea`, 2 `cmp`). Retail keeps the loop
// counters and both cell counts in stack slots and tests the found object and the type flag through registers
// (`mov cl,[eax+0xC9D]; test cl,cl`) where cl emits `cmp byte ptr`. Variants tried: operator+ cell sum, field-wise
// cell sum, goto-based exits, hoisted loop variables, a type local for the flag.
bool BuildingBView::vf_169()
{
    if (Func_6FBC90())
        goto accept;
    {
        HBCell tmp;
        HBCell base = *vf_110(&tmp);
        int width = Type->Func_45EC90();
        int height = Type->Func_45ECA0(0);
        int x;
        int y;
        for (x = -1; x <= width; x++) {
            for (y = -1; y <= height; y++) {
                HBPoint2D zero;
                zero.X = 0;
                zero.Y = 0;
                HBCell cell;
                cell.X = base.X + x;
                cell.Y = base.Y + y;
                BuildingBView* found = BuildingBMap.Func_5657A0(&cell)->Func_47C3D0(&zero, 0, 0);
                if (found == this) {
                    HBCell again = cell;
                    found = BuildingBMap.Func_5657A0(&again)->Func_47EC40(0);
                }
                if (found && found->Owner != Owner && found->vf_33()->unknown_C9D)
                    goto accept;
            }
        }
    }
    return false;
accept:
    return true;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x457A10
bool BuildingClass_00457A10::CheckFog()
{
    CellStruct cell;
    CellStruct base = *(this->*this->Vtbl->GetMapCoords)(&cell);
    CellStruct const* fd = (this->Type->*this->Type->Vtbl->GetFoundationData)(false);

    if (!AllFogged_00457A10(fd, base, cell)) {
        return false;
    }
    return true;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x457C90
// Clears a planted C4 charge (its timer restarts idle) and starts the invulnerability timer.
void BuildingClass::vf_85(int a, int b, bool c)
{
    if (C4Applied) {
        C4Applied = false;
        CDTimerClass idle;
        idle.StartTime = CurrentFrame;
        idle.TimeLeft = 0;
        C4Timer = idle;
        C4AppliedBy = 0;
    }
    FUN_0070E2B0(a, b, c);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x457CE0
//
// May this infantry enter the building? The building must be occupiable, not
// mid-unload or mid-garrison mission, on the usable map, and not warping out.
// An occupier needs the same owner (or a passive owner), a free slot, a
// building above red health and no mind control; an assaulter needs a
// hostile owner and somebody already inside to attack.
//
// The two branches are an if/else that fall into one shared `return true`;
// separate true returns per branch turn the last tests into SETE/SETNE.
bool Obj_00457CE0::CanBeOccupiedBy(Obj_00457CE0* infantry)
{
    if (infantry == 0) {
        return false;
    }
    if (!BuildingType->CanBeOccupied) {
        return false;
    }
    if (CurrentMission == 0x12 || CurrentMission == 0x13) {
        return false;
    }

    Coord_00457CE0 buf;
    if (!MapInstance_00457CE0.IsWithinUsableArea((this->*Vptr->GetCoords)(&buf))) {
        return false;
    }
    if ((this->*Vptr->IsBeingWarpedOut)()) {
        return false;
    }

    InfantryType_00457CE0* type = infantry->InfantryType;
    if (type->Occupier) {
        if (Owner != infantry->Owner && !Owner->Type->MultiplayPassive) {
            return false;
        }
        if ((this->*Vptr->GetOccupantCount)() == BuildingType->MaxNumberOccupants) {
            return false;
        }
        if (reinterpret_cast<ObjectClass*>(this)->IsRedHP()) {
            return false;
        }
        if (infantry->IsMindControlled()) {
            return false;
        }
    } else {
        if (!type->Assaulter) {
            return false;
        }
        if (Owner->IsAlliedWith(infantry)) {
            return false;
        }
        if ((this->*Vptr->GetOccupantCount)() == 0) {
            return false;
        }
    }
    return true;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4581F0
int BuildingClass::vf_258()
{
    return Occupants.Count;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x458200
//
// Keep a garrisonable civilian structure's ownership in step with whether
// anybody is inside it. Only types whose gate member is still -1 take part.
// A building already down at red health is poked first; then the Civilian
// house is found by walking HouseClass::Array for the house whose type sits
// on the "Civilian" side. Emptying the building hands it back to that house,
// with an abandoned sound, a radar event and the EVA line for the local
// player; garrisoning a building that currently belongs to the Civilian house
// hands it to the first occupant's owner. Both transitions refresh the
// occupant animations first.
//
// MATCHED (100%; it sat at 98.0%, 96/98 instructions, with the multiset identical, so the
// residual is scheduling only). The lever that mattered was declaration
// order: the Civilian house pointer has to be zeroed BEFORE the side lookup
// runs, because retail issues `XOR EBX,EBX` ahead of `CALL 0x6A46D0`.
// Declaring it after the lookup puts the zero behind the call: 95.9% versus
// 98.0%. The last two instructions were the `MOV EDX,0x2000` of the
// __fastcall sound call, which retail issues between the two argument pushes.
// cl evaluates arguments right to left by declared position, so that order
// means the panning is declared after the volume: PlayGlobal(index, volume,
// panning, controller). The volume, a float, still goes on the stack and the
// panning still reaches EDX, so the ABI is unchanged and 0x750920 itself
// compiles to the same bytes under either order.
void BuildingClass_00458200::UpdateGarrisonOwner()
{
    if (Type->unknown_634 != -1) {
        return;
    }

    if (reinterpret_cast<ObjectClass*>(this)->IsRedHP()) {
        FUN_00457DE0(0, 0);
    }

    House_00458200* civilian = 0;
    int count = HouseArray_00458200.Count;
    int side = FindSideIndex_00458200(CivilianSideName_00458200);
    for (int i = 0; i < count; ++i) {
        if (HouseArray_00458200.Items[i]->Type->SideIndex == side) {
            civilian = HouseArray_00458200.Items[i];
            break;
        }
    }

    if ((this->*Vtbl->GetOccupantCount)() == 0 && Owner != civilian) {
        if (Owner->IsControlledByCurrentPlayer()) {
            VocClass::PlayGlobal(RulesInstance_00458200->unknown_1C0,
                                 1.0f, 0x2000, 0);
            CellStruct_00458200 here;
            if (RadarEventClass_00458200::Create(
                    0xF, *(this->*Vtbl->GetMapCoords)(&here))) {
                VoxClass_00458200::Play(EvaStructureAbandoned_00458200, -1, -1);
            }
        }
        UpdateOccupantAnims();
        (this->*Vtbl->SetOwningHouse)(civilian, 0);
    }

    if ((this->*Vtbl->GetOccupantCount)() > 0 && Owner == civilian) {
        UpdateOccupantAnims();
        (this->*Vtbl->SetOwningHouse)(OccupantItems[0]->Owner, 0);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x458330
//
// Refresh the idle animation and the four active ones after anything that
// changes how the building should look — occupancy, ownership or damage.
// The slot order is retail's: Idle first, then Active through ActiveFour.
//
// PARTIAL: 88.5% -- the damaged flag lives in EDI where retail uses EBX (so
// retail tests it with `TEST BL,BL`); instruction multiset is identical. Two
// levers from the earlier match are kept because they are plain code:
//   * the damaged flag is an `int`, not a `bool` (dword MOV/XOR forms);
//   * the name is selected through `Type->BuildingAnim[slot].Field` in each
//     arm, and the flag is written as `GetHealthPercentage() <= ConditionYellow`.
void BuildingClass::UpdateOccupantAnims()
{
    PlayNthAnim(this, ANIM_SLOT_IDLE_00458330, 0);
    PlayNthAnim(this, ANIM_SLOT_ACTIVE_00458330, 0);
    PlayNthAnim(this, ANIM_SLOT_ACTIVE_TWO_00458330, 0);
    PlayNthAnim(this, ANIM_SLOT_ACTIVE_THREE_00458330, 0);
    PlayNthAnim(this, ANIM_SLOT_ACTIVE_FOUR_00458330, 0);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4585C0  BuildingClass::KillOccupants (__thiscall, ret 4)
//
// Empty a garrisonable building of its occupants. With no killer the
// occupants simply run their own slot +0xF8 destruction; with a killer, each
// occupant's firing port is projected to client space, an AnimClass is spawned
// at that point offset by the building's own coordinate, the killer is
// credited with the kill and the occupant is destroyed. Afterwards the
// occupant vector is cleared and re-sized to its old capacity and the
// building's recomputed slot +0x1BC value is applied.
//
// Two levers carried most of this: the killer == 0 arm has to be the source's
// `if` body (retail lays it inline and the killer arm as the far block — the
// reverse spelling inverts the whole layout), and the coordinate sum has to be
// staged in its own struct and assigned whole (`sum.X = origin->X + where.X;
// … where = sum;`), which keeps the three component loads together ahead of
// the three stores instead of sinking each add to its store (72.6% -> 85.5%).
// Binding the animation type to a local inside the allocation arm is what puts
// the `MOV EAX,[EAX]` deref ahead of the `MOV ECX,<anim>`.
//
// PARTIAL (85.5%, 100/117): the instruction multiset is identical. The residual
// is (a) retail storing the +0x69C counter before loading the occupant count
// where cl emits the load first, (b) the client point's two components: retail
// loads Y then X before storing either, cl loads and stores X then Y, and
// (c) three EAX/ECX naming swaps around the slot +0xAC and Construct calls.
// Variants tried: the client point staged in its own struct and assigned whole
// (14.3% — it forces a real second frame slot), the Y component bound to a
// local before the X store (14.4%), and the original arm order (72.6%).
void Building_004585C0::KillOccupants(Killer_004585C0* killer)
{
    this->Unknown_69C = 0;

    int i;
    if (killer == 0)
    {
        for (i = this->Occupants.Count - 1; i >= 0; i--)
        {
            Occupant_004585C0* dying = this->Occupants.Items[i];
            (dying->*dying->Vptr->At_F8)();
        }
    }
    else
    {
        for (i = this->Occupants.Count - 1; i >= 0; i--)
        {
            Point2D  pt;
            Coord_004585C0  where;
            Point2D* client = DAT_00887324->FUN_006D2070(
                &pt, &this->Type->OccupantOffsets[i]);
            where.X = client->X;
            where.Y = client->Y;
            where.Z = 0;

            Coord_004585C0  self;
            Coord_004585C0* origin = (this->*this->Vptr->At_AC)(&self);
            Coord_004585C0 sum;
            sum.X = origin->X + where.X;
            sum.Y = origin->Y + where.Y;
            sum.Z = origin->Z + where.Z;
            where = sum;

            Anim_004585C0* anim =
                (Anim_004585C0*)KillOccOperatorNew(0x1C8);
            if (anim) {
                AnimType_004585C0* type =
                    (*(killer->*killer->Vptr->At_3F8)(
                         0, &where, 0, 1, 0x600, 0, 0))->AnimType;
                anim = anim->Construct(type);
            } else {
                anim = 0;
            }
            anim->Unknown_100 = 0xFFFFFF38;

            Occupant_004585C0* victim = this->Occupants.Items[i];
            (killer->*killer->Vptr->At_E0)(victim);

            Occupant_004585C0* dying = this->Occupants.Items[i];
            (dying->*dying->Vptr->At_F8)();
        }
    }

    int capacity = this->Occupants.Capacity;
    (this->Occupants.*this->Occupants.Vptr->Clear)();
    (this->Occupants.*this->Occupants.Vptr->Resize)(capacity, 0);

    this->FUN_0070F6E0((this->*this->Vptr->At_1BC)());
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x458750
//
// Restart the cash-production timer from the type's delay, then, unless the
// owner is a passive multiplayer house and provided the building is active,
// credit (positive amount) or debit (negative amount) the owner.
void BuildingClass::FUN_00458750()
{
    CashProductionTimer = CDTimerClass(Type->ProduceCashDelay);

    if (!((HouseTypeClass*)Owner->Type)->MultiplayPassive && vf_212()) {
        if (Type->ProduceCashAmount > 0)
            Owner->GiveMoney(Type->ProduceCashAmount);
        else
            Owner->FUN_004F9790(-Type->ProduceCashAmount);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4587D0
bool Obj_004587D0::FUN_004587D0(Arg_004587D0* other)
{
    int derived = other->vt_08C(Owner);

    // The pointer cast models this call slot's existing ABI view only.
    void* context = (void*)DAT_0089C818.raw_dword;
    bool accepted = vt_100(derived, context) != 0;

    return accepted;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x458810
//
// Build the transform that carries a building's voxel barrel from model space
// to its firing pose: translate out to the building pivot, yaw by the turret's
// current facing, translate out to the rotation pivot, pitch by the barrel's
// current facing, translate out to the pitch pivot, then scale uniformly by
// the type's barrel scale.
//
// The facing index helper takes the returned direction object. A named float
// pitch temporary preserves retail's floating-point instruction order before
// the pitch-pivot translations. Read the scale after those translations.
Matrix3D* BuildingClass_00458810::GetVoxelBarrelOffsetMatrix(
    Matrix3D& ret)
{
    Matrix3D mtx;
    mtx.MakeIdentity();
    mtx.TranslateX((float)Type->VoxelBarrelOffsetToBuildingPivotPoint.X);
    mtx.TranslateY((float)Type->VoxelBarrelOffsetToBuildingPivotPoint.Y);
    mtx.TranslateZ((float)Type->VoxelBarrelOffsetToBuildingPivotPoint.Z);

    DirStruct_00458810 dir;
    int turret = BarrelFacingIndex_00458810(PrimaryFacing.Current(&dir));
    mtx.RotateZ((float)(turret * VoxelBarrelStep_00458810));

    mtx.TranslateX((float)Type->VoxelBarrelOffsetToRotatePivotPoint.X);
    mtx.TranslateY((float)Type->VoxelBarrelOffsetToRotatePivotPoint.Y);
    mtx.TranslateZ((float)Type->VoxelBarrelOffsetToRotatePivotPoint.Z);

    int barrel = BarrelFacingIndex_00458810(BarrelFacing.Current(&dir));
    float pitch = (float)-(barrel * VoxelBarrelStep_00458810);
    mtx.RotateY(pitch);

    mtx.TranslateX((float)Type->VoxelBarrelOffsetToPitchPivotPoint.X);
    mtx.TranslateY((float)Type->VoxelBarrelOffsetToPitchPivotPoint.Y);
    mtx.TranslateZ((float)Type->VoxelBarrelOffsetToPitchPivotPoint.Z);

    float scale = (float)Type->VoxelBarrelScale;
    mtx.ScaleX(scale);
    mtx.ScaleY(scale);
    mtx.ScaleZ(scale);

    ret = mtx;
    return &ret;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4589C0
int Obj_004589C0::FUN_004589C0()
{
    int total = (int)Storage.GetTotalAmount();

    if (total == 0) {
        return total;
    }

    return ((int)Storage.GetTotalAmount() * 4) / Settings->Divisor;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x458A00
//
// Does this building block the given cell? The cell has to actually hold this
// building (`CellClass::GetBuilding` must answer `this`); a type that left
// NumberImpassableRows at -1 blocks everywhere; a bunker type blocks while
// something is linked into it; otherwise the impassable band is the first
// NumberImpassableRows columns measured from the building's own top-left map
// coordinate, so the cell is blocked while its X still falls inside that band.
//
// MATCHED (100.0%, 44/44). Two levers, both measured across a 17-variant batch
// scored in one compile:
//   * the cell's coordinate has to be bound to an `int` local BEFORE the
//     map-coords slot is called. Retail hoists `MOVSX EDI,word ptr [EDI+0x24]`
//     above the call because the cell pointer is dead there and its incoming
//     argument slot is then free to serve as the slot's hidden out-pointer
//     (`LEA ECX,[ESP+0xc]`, and the function allocates no frame at all).
//     Reading the coordinate inside the comparison instead leaves it after the
//     call: 68.9%. The local takes it to 77.8%, and binding the slot's result
//     to its own `int edge` as well reaches 86.7%.
//   * the last 13.3% is a stray `XOR EAX,EAX` that cl 8804 inserts ahead of
//     `CMP/SETG AL` when a comparison is returned directly. Retail has no such
//     zero here (it does have one at 0x50E1B0, where the comparison is the
//     whole body), so the bool must not reach the return as a bare relational
//     expression. Spelling the test as an `if` with the two constant returns —
//     the same shape as every other arm of this predicate — removes it.
//     `bool r = ...; return r;` and a `? true : false` ternary also reach
//     100.0%; a `!(a <= b)` inversion, an `(a - b) > 0` rewrite, a `(char)`
//     cast, an inline `Exceeds(a, b)` helper, an `int limit` temporary,
//     swapping the comparison round, copying the coordinate struct by value
//     and moving the local's declaration all stay at 86.7% or worse.
bool BuildingClass::IsCellImpassable(CellClass* cell)
{
    if (cell->GetBuilding() != this) {
        return false;
    }
    if (Type->NumberImpassableRows == -1) {
        return true;
    }
    if (Type->bools_16A4[0x16AB - 0x16A4] && BunkerLinkedItem != 0) {
        return true;
    }

    int cellX = cell->MapCoords.X;
    int edge = vf_110().X;
    if (Type->NumberImpassableRows + edge > cellX) {
        return true;
    }
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x458A80
// CAPPED at 10.4% (28 of 268 instructions; 267 retail vs 268 compiled; retail-only 2 `xor`, `jmp`, `jne`;
// compiled-only 2 `cmp`, 3 `je`). The frame is 0x38 against retail 0x34, which shifts every stack offset, and retail
// tests the object and cell pointers with `cmp reg,ebx` against its zero register where cl emits `test`.
// Variants tried: base + offset copy (kept), base + *footprint++ and *footprint++ + base direct sums.
bool BuildingBView::vf_292(HBCoord* where, int dir)
{
    HBCell* footprint = vf_66(0);
    HBCell base = BuildingBCellOf(*where);
    BuildingBClearedList cleared;
    while (!(footprint->X == 0x7FFF && footprint->Y == 0x7FFF)) {
        HBCell offset = *footprint++;
        HBCell at = base + offset;
        BuildingBCellView* cell = BuildingBMap.Func_5657A0(&at);
        if (cell->SmudgeIndex != -1) {
            cell->SmudgeIndex = -1;
            cell->unknown_11E = 0;
            cell->unknown_40 = 0;
        }
        for (BuildingBObjectView* object = cell->FirstObject; object; object = cell->FirstObject) {
            if (!(object->unknown_14 & 1) || object->vf_11() == 6) {
                for (int i = cleared.Count - 1; i >= 0; i--) {
                    BuildingBObjectView* item = cleared.Items[i];
                    HBCoord home = item->Location;
                    if (!item->vf_54(&home, 0))
                        item->vf_62();
                }
                return false;
            }
            cleared.AddItem(object);
            object->vf_53();
        }
    }
    if (vf_54(where, dir)) {
        for (int i = cleared.Count - 1; i >= 0; i--) {
            BuildingBObjectView* item = cleared.Items[i];
            HBCell itemCell;
            HBCell zero(0, 0);
            HBCell start = *item->vf_110(&itemCell);
            HBCell found = *BuildingBMap.Func_56DC20(&itemCell, &start, item->vf_33()->unknown_67C, -1, 0, 0, 1, 1, 0,
                                                            0, 0, 1, &zero, 0, 0);
            HBCoord landing;
            if (!item->vf_54(BuildingBMap.Func_5657A0(&found)->vf_18(&landing), 0))
                item->vf_62();
        }
        return true;
    }
    vf_62();
    for (int i = cleared.Count - 1; i >= 0; i--) {
        BuildingBObjectView* item = cleared.Items[i];
        HBCoord home = item->Location;
        if (!item->vf_54(&home, 0))
            item->vf_62();
    }
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x458DB0
bool BuildingClass::IsArmed()
{
    if (vf_256())
        return true;
    return TechnoClass::IsArmed();
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x458DD0
bool BuildingClass::vf_256()
{
    return Type->bools_1570[0x157B - 0x1570] && Type->bools_1570[0x157C - 0x1570] && vf_258() > 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x458E00
int BuildingClass::vf_257()
{
    int limit = Type->GetFoundationHeight(false);
    if (Type->GetFoundationWidth() < limit)
        return Type->GetFoundationWidth() / 2;
    return Type->GetFoundationHeight(false) / 2;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4593A0  BuildingClass::UnloadBunker
//
// Let the bunkered unit out: its locomotor is switched back on through the
// COM slot +0x58, it is placed one half-cell off the bunker's own position
// through slot +0x70 (smart-pointer null checks and E_POINTER inlined), its
// slot +0x544 gets 1.0, the two back-links are cleared and the building goes
// through its +0x274 virtual with 3.
//
// The returned-coordinate buffer is scoped to the block that reads it. Retail's
// frame is that one 12-byte buffer: the adjusted copy lives in EBX/EBP and its
// Z is spilled into the dead buffer's third slot, which VC6 only does once the
// buffer's scope has closed. With the buffer and the adjusted copy in one scope
// the frame is 0x18 (95.6%).
void Building_004593A0::UnloadBunker()
{
    Unit_004593A0* unit = BunkerLinkedItem;
    if (unit != 0 && (unit->*unit->Vptr->WhatAmI)() == 1) {
        if (unit->Locomotor == 0)
            FUN_007DC720(0x80004003);
        LOCO_CALL0_004593A0(unit->Locomotor, 0x58);

        Coord_004593A0 coords;
        {
            Coord_004593A0 buf;
            Coord_004593A0* here = (this->*this->Vptr->GetCoords)(&buf);
            coords.X = here->X - 0x80;
            coords.Y = here->Y + 0x80;
            coords.Z = here->Z;
        }

        if (unit->Locomotor == 0)
            FUN_007DC720(0x80004003);
        LOCO_CALL70_004593A0(unit->Locomotor, 0x47, coords);

        (unit->*unit->Vptr->At_544)(1.0);
        unit->BunkerLinkedItem = 0;
        BunkerLinkedItem = 0;
        (this->*this->Vptr->At_274)(3);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x459470  BuildingClass::ClearBunker (__thiscall)
//
// Tear the bunker link down: the two garrison animations are destroyed, the
// bunker-exit sound plays at the building's own coordinates when the rules
// name one, the two "bunker cleared" animations play in their healthy or
// damaged spelling according to the building's health ratio, and then both
// back-links are cleared and the building is sent through its mission slot.
void BuildingClass::ClearBunker()
{
    DestroyNthAnim(10);
    DestroyNthAnim(11);

    if (BunkerLinkedItem != 0)
    {
        if (RulesInstance->BunkerWallsDownSound != -1)
        {
            CoordStruct coords = Location;
            VocClass::PlayAt(RulesInstance->BunkerWallsDownSound, &coords, 0);
        }

        const char* name;
        int damaged;

        if (GetHealthPercentage() <= RulesInstance->ConditionYellow)
        {
            damaged = 1;
            name = Type->BuildingAnim[12].Damaged;
        }
        else
        {
            damaged = 0;
            name = Type->BuildingAnim[12].Anim;
        }

        if (name != 0 && *name != 0)
            PlayAnim(name, 12, damaged, 0, 0);

        if (GetHealthPercentage() <= RulesInstance->ConditionYellow)
        {
            damaged = 1;
            name = Type->BuildingAnim[13].Damaged;
        }
        else
        {
            damaged = 0;
            name = Type->BuildingAnim[13].Anim;
        }

        if (name != 0 && *name != 0)
            PlayAnim(name, 13, damaged, 0, 0);

        vf_157(3);
        BunkerLinkedItem->BunkerLinkedItem = 0;
        BunkerLinkedItem = 0;
        TankBunkerState = 0;
        vf_122(5, 0);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x459840
// The first non-zero of three sub-object counters, falling back to the owner's
// own field. All four returns share one epilogue.
int Obj_00459840::FUN_00459840() const
{
    if (unknown_520->atEA4) {
        return unknown_520->atEA4;
    }

    if (unknown_520->atEA8) {
        return unknown_520->atEA8;
    }

    if (unknown_520->atEAC) {
        return unknown_520->atEAC;
    }

    return unknown_6F4;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x459870
int BuildingClass::vf_181()
{
    return Type->AntiAirValue;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x459880
int BuildingClass::vf_182()
{
    return Type->AntiArmorValue;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x459890
int BuildingClass::vf_183()
{
    return Type->AntiInfantryValue;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4598D0
// A type that undeploys and gathers resources never qualifies; otherwise the
// answer is the negation of slot 32.
bool BuildingClass::FUN_004598D0()
{
    BuildingTypeClass* type = Type;
    if (type->UndeploysInto != 0 && type->ResourceGatherer)
    {
        return false;
    }
    bool result = !vf_32();
    return result;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x459900
// CAPPED at 4.2% (239 retail vs 229 compiled instructions; retail-only 6 `mov`, 4 `lea`). Retail keeps the
// particle-system type in ebp and the empty-coordinate X in edi and spills the arg at [esp+0x10]; cl puts the
// type in edi and the arg in ebx. Variants tried: a 4-iteration loop (71 instructions, not unrolled), four
// expanded blocks kept here, the argument re-read per block, swapped operand order of the position sum.
// The four offsets of the type are handled by four expanded copies of the same block in retail.
void BuildingBView::vf_282()
{
    BuildingBParticleSystemTypeView* systemType = Type->unknown_774;
    if (systemType) {
        int arg = Type->unknown_156C;
        {
            HBCoord offset = Type->unknown_coords_7CC[0];
            if (!(offset == BuildingBEmptyCoord) && !offset.Func_459F60(&BuildingBGlobal_0089C870)) {
                HBCoord where = Location + offset;
                BuildingBParticleSystemView* system = new BuildingBParticleSystemView(systemType, &where, 0, this, &BuildingBEmptyCoord, 0);
                system->Func_6301F0(arg);
            }
        }
        {
            HBCoord offset = Type->unknown_coords_7CC[1];
            if (!(offset == BuildingBEmptyCoord) && !offset.Func_459F60(&BuildingBGlobal_0089C870)) {
                HBCoord where = Location + offset;
                BuildingBParticleSystemView* system = new BuildingBParticleSystemView(systemType, &where, 0, this, &BuildingBEmptyCoord, 0);
                system->Func_6301F0(arg);
            }
        }
        {
            HBCoord offset = Type->unknown_coords_7CC[2];
            if (!(offset == BuildingBEmptyCoord) && !offset.Func_459F60(&BuildingBGlobal_0089C870)) {
                HBCoord where = Location + offset;
                BuildingBParticleSystemView* system = new BuildingBParticleSystemView(systemType, &where, 0, this, &BuildingBEmptyCoord, 0);
                system->Func_6301F0(arg);
            }
        }
        {
            HBCoord offset = Type->unknown_coords_7CC[3];
            if (!(offset == BuildingBEmptyCoord) && !offset.Func_459F60(&BuildingBGlobal_0089C870)) {
                HBCoord where = Location + offset;
                BuildingBParticleSystemView* system = new BuildingBParticleSystemView(systemType, &where, 0, this, &BuildingBEmptyCoord, 0);
                system->Func_6301F0(arg);
            }
        }
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// BLOCK-ORDER DELTA (status partial, 41.7% - 5/12). Retail branches *into* the
// call (`JNZ` to a block placed after an earlier `POP ESI; RET`), so the
// function carries two epilogues with the call block out of line. We emit one
// epilogue and the call inline, which is what VC6 does for a plain `if` and for
// the inverted early-return form alike. Both were tried.
// Lift pass (2026-09-18): re-tried `if (!FUN_00465D40(...)) return;` and an
// explicit `goto notify;` layout that spells retail's block order literally -
// both 41.7% with a byte-identical stream. cl 8804 always cross-jumps the two
// two-instruction `POP ESI; RET` epilogues into one; retail (8447) keeps both.
// Recording as an 8447-vs-8804 cross-jump difference, not chased further.
// FUNCTION: GAMEMD 0x459C00
void BuildingClass_00459C00::FUN_00459C00()
{
    if (FUN_00465D40(unknown_520)) {
        FUN_006FC030(this);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x459C20
void BuildingClass::vf_219()
{
    if (ArchiveTarget && ArchiveTarget->vf_11() == 0xB) {
        if (AsCell(ArchiveTarget)->LandType == 5 && Type->ResourceDestination && Type->ResourceGatherer && Type->VoiceHarvest != -1) {
            vf_213(Type->VoiceHarvest);
            return;
        }
    }
    TechnoClass::vf_219();
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x459D80
bool TechnoClass::vf_164()
{
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x459D90
bool TechnoClass::vf_177(int a1)
{
    return true;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x459DA0
int TechnoClass::vf_188()
{
    return 2;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x459DB0
CellStruct TechnoClass::vf_189()
{
    return DAT_0089C818;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x459DC0
void TechnoClass::vf_190(int a1)
{
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x459DD0
bool TechnoClass::vf_200()
{
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x459DE0
void TechnoClass::vf_205()
{
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x459DF0
bool TechnoClass::vf_207()
{
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x459E00
bool TechnoClass::vf_208()
{
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x459E10
bool TechnoClass::vf_209()
{
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x459E20
bool TechnoClass::vf_210()
{
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x459E30
bool TechnoClass::vf_211()
{
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x459E40
bool TechnoClass::vf_224()
{
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x459E50
bool TechnoClass::vf_247(int a1)
{
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x459E60
void TechnoClass::vf_270(int a1, int a2)
{
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x459E70
int BuildingClass::vf_12()
{
    return 0x720;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x459E80
HRESULT __stdcall BuildingClass::GetClassID(CLSID* pClassID)
{
    if (pClassID == 0)
        return E_POINTER;
    *pClassID = CLSID_Building;
    return S_OK;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x459EC0
int BuildingClass::vf_11()
{
    return 6;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x459ED0
const wchar_t* BuildingClass::vf_36()
{
    return Type->UIName;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x459EE0
ObjectTypeClass* BuildingClass::vf_34()
{
    return Type;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x459EF0
// CAPPED at 41.2% (7 of 17 instructions; retail-only: `add ecx,-0x80`, `lea esi,[eax-0x80]`; cl-only: two
// `sub reg,0x80`). Retail adds the negative constant (an `add` of 0xFFFFFF80 and an `lea` with a -0x80
// displacement) where cl always canonicalises a constant add of a negative immediate to `sub`. Variants
// tried: direct field subtraction, a struct copy with -=, operator- / operator+ with a named offset
// coordinate, and `+ -0x80`.
CoordStruct BuildingClass::vf_43()
{
    CoordStruct c = Location;
    c.X -= 0x80;
    c.Y -= 0x80;
    return c;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x459F40
// Hand back the object only if it is of the expected kind. Retail computes the
// selection branchlessly (`SUB 6; NEG; SBB; NOT; AND`), which is what the
// conditional expression produces here.
Obj_00459F40* Obj_00459F40::FUN_00459F40()
{
    if (this == 0) {
        return 0;
    }

    return (WHAT_AM_I(this) == 6) ? this : 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x459F60
int Triple3i::FUN_00459F60(const Triple3i* other) const
{
    return a == other->a && b == other->b && c == other->c;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x459FF0
// DynamicVectorClass<InfantryClass*>::Clear

// FUNCTION: GAMEMD 0x45A020
// DynamicVectorClass<InfantryClass*>::Slot5

// FUNCTION: GAMEMD 0x45A040
// VectorClass<InfantryClass*>::Slot6

// FUNCTION: GAMEMD 0x45A3E0
// VectorClass<InfantryClass*>::operator==

// FUNCTION: GAMEMD 0x45A420
// VectorClass<InfantryClass*>::SetCapacity

// FUNCTION: GAMEMD 0x45A4D0
// VectorClass<InfantryClass*>::Clear

// FUNCTION: GAMEMD 0x45A500
// VectorClass<InfantryClass*>::FindItemIndex

// FUNCTION: GAMEMD 0x45A540
// VectorClass<InfantryClass*>::Slot5

// FUNCTION: GAMEMD 0x45A560
// DynamicVectorClass<InfantryClass*>::SetCapacity

// FUNCTION: GAMEMD 0x45A610
// DynamicVectorClass<InfantryClass*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x45AA60
// VectorClass<InfantryClass*>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x45AAB0
// DynamicVectorClass<InfantryClass*>::scalar deleting destructor

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x45A050
// Report a missing pointer, then hand it back regardless - the caller sees
// null and the report is advisory.
void* Obj_0045A000::FUN_0045A050()
{
    if (Ptr == 0) {
        FUN_007DC720(0x80004003);
    }

    return Ptr;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x45A070
// DynamicVectorClass<FoggedObjectClass*>::Clear

// FUNCTION: GAMEMD 0x45A0A0
// DynamicVectorClass<FoggedObjectClass*>::Slot5

// FUNCTION: GAMEMD 0x45A0C0
// VectorClass<FoggedObjectClass*>::Slot6

// FUNCTION: GAMEMD 0x45A640
// VectorClass<FoggedObjectClass*>::operator==

// FUNCTION: GAMEMD 0x45A680
// DynamicVectorClass<FoggedObjectClass*>::SetCapacity

// FUNCTION: GAMEMD 0x45A730
// DynamicVectorClass<FoggedObjectClass*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x45AB00
// DynamicVectorClass<FoggedObjectClass*>::scalar deleting destructor

// FUNCTION: GAMEMD 0x45AB50
// VectorClass<FoggedObjectClass*>::SetCapacity

// FUNCTION: GAMEMD 0x45AC00
// VectorClass<FoggedObjectClass*>::Clear

// FUNCTION: GAMEMD 0x45AC30
// VectorClass<FoggedObjectClass*>::FindItemIndex

// FUNCTION: GAMEMD 0x45AC70
// VectorClass<FoggedObjectClass*>::Slot5

// SYNTHETIC: GAMEMD 0x45AC90
// VectorClass<FoggedObjectClass*>::scalar deleting destructor

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x45A0D0
void FUN_0045A0D0(BufferHolder* obj)
{
    void* buffer = obj->Buffer;

    obj->unknown_10 = 0;

    if (buffer != 0 && obj->IsAllocated != 0) {
        FUN_007C8B3D(buffer);
        obj->Buffer = 0;
    }

    obj->IsAllocated = 0;
    obj->Length = 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x45A100
// DynamicVectorClass<Reestablish*>::Slot5 (slot 5)
// TEMPLATE: GAMEMD 0x45A120
// VectorClass<Reestablish*>::Slot6 (slot 6)
// TEMPLATE: GAMEMD 0x45A760
// VectorClass<Reestablish*>::operator== (slot 1)
// TEMPLATE: GAMEMD 0x45A7A0
// VectorClass<Reestablish*>::SetCapacity (slot 2)
// TEMPLATE: GAMEMD 0x45A880
// VectorClass<Reestablish*>::FindItemIndex (slot 4)
// TEMPLATE: GAMEMD 0x45A8C0
// VectorClass<Reestablish*>::Slot5 (slot 5)
// TEMPLATE: GAMEMD 0x45A8E0
// DynamicVectorClass<Reestablish*>::SetCapacity (slot 2)
// TEMPLATE: GAMEMD 0x45A990
// DynamicVectorClass<Reestablish*>::FindItemIndex (slot 4)
template class VectorClass<Reestablish*>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x45A130
RectangleStruct* RectangleStruct::FromPointSize(const Point2D* pair, int third, int fourth)
{
    X = pair->X;
    Y = pair->Y;
    Width = third;
    Height = fourth;

    return this;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x45A160
void Obj_00437FC0::FUN_0045A160()
{
    if (Held) {
        IFACE_CALL(Held, 0x8);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x45A170
void Obj_00437FC0::FUN_0045A170()
{
    if (Held) {
        IFACE_CALL(Held, 0x4);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x45A850
void FUN_0045A850(BufferHolder* obj)
{
    void* buffer = obj->Buffer;

    if (buffer != 0 && obj->IsAllocated != 0) {
        FUN_007C8B3D(buffer);
        obj->Buffer = 0;
    }

    obj->IsAllocated = 0;
    obj->Length = 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x45ACE0
void* BufferHolderDtor::FUN_0045ACE0(unsigned int flags)
{
    void* buffer = Buffer;

    *(char**)this = VTABLE_007E4468;

    if (buffer != 0 && IsAllocated != 0) {
        FUN_007C8B3D(buffer);
        Buffer = 0;
    }

    IsAllocated = 0;
    Length = 0;

    if (flags & 1) {
        FUN_007C8B3D(this);
    }

    return this;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x45AD30
void* BufferHolderDtor::FUN_0045AD30(unsigned int flags)
{
    void* buffer = Buffer;

    *(char**)this = VTABLE_007E4468;

    if (buffer != 0 && IsAllocated != 0) {
        FUN_007C8B3D(buffer);
        Buffer = 0;
    }

    IsAllocated = 0;
    Length = 0;

    if (flags & 1) {
        FUN_007C8B3D(this);
    }

    return this;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x45ADD0
// An index at or past the count fails; removing the last element succeeds with
// no copying at all, since the count drop alone is enough.
//
// The slide is written with the increment *after* the move. Retail's loop reads
// `INC EAX; MOV ESI,[EDX+EAX*4]; MOV [EDX+EAX*4-4],ESI`, which looks like a
// pre-incremented `Items[i-1] = Items[i]` - but writing it that way makes VC6
// compute the store address with a separate LEA. Written post-incremented the
// compiler performs that induction rewrite itself and lands on retail's form.
// Four phrasings tried; only this one closes it.
bool Vector_0045ADD0::FUN_0045ADD0(int index)
{
    int count = Count;

    if (index < count) {
        count--;
        Count = count;

        if (index < count) {
            do {
                Items[index] = Items[index + 1];

                index++;
            } while (index < Count);
        }

        return true;
    }

    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x45AE10
bool Vector_0045ADD0::FUN_0045AE10(int index)
{
    int count = Count;

    if (index < count) {
        count--;
        Count = count;

        if (index < count) {
            do {
                Items[index] = Items[index + 1];

                index++;
            } while (index < Count);
        }

        return true;
    }

    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x45AEA0
//
// Three exits, and each drops the currently-held interface differently, which
// is why they are written out rather than folded:
//   - empty source: clear the field first, then release the saved pointer, and
//     report E_NOINTERFACE
//   - failed query: release first, then clear, and report the query's HRESULT
//   - success: release the old one and store the new
//
// The empty-source case is the *trailing* block: retail's `JZ` at 0x45AEAC
// jumps forward past the whole query, so the query is the fall-through and the
// guard is written positively. Leading with the empty case instead scores
// 11.3%.
//
// `pv` lands in the incoming argument's own stack slot (`LEA EDX,[ESP+0xC]`,
// read back later as `[ESP+0x10]` once EBX is pushed). That is VC6 reusing the
// parameter home once the parameter is dead, not the source writing through the
// argument - `source` is read exactly once, at the top.
//
// The HRESULT is held in a named local rather than returned directly from each
// branch: retail keeps it in EDI and ends every path with `MOV EAX,EDI`.
//
// Each branch captures the held pointer into its *own* named local. Reading the
// member directly in both arms lets VC6 hoist the one load above the `TEST EDI,
// EDI`, which then serves both blocks and removes the success block's `PUSH EBX`
// - 43.4%. Distinct locals defeat that partial-redundancy elimination and the
// two blocks come out as retail has them.
//
// PARTIAL: retail uses a different HRESULT register and epilogue ordering.
// Use an ordinary return; volatile reloads used only for scheduling are forbidden.
long ComHolder_0045AEA0::FUN_0045AEA0(IUnk** source)
{
    long   hr;
    IUnk*  from = *source;

    if (from != 0) {
        void* pv;

        hr = COM_QUERY(from, &DAT_00818858, &pv);

        if (hr < 0) {
            IUnk* bad = Held;

            if (bad) {
                COM_SLOT_08(bad);
            }

            Held = 0;

            return hr;
        }

        IUnk* prev = Held;
        IUnk* got  = (IUnk*)pv;

        if (prev) {
            COM_SLOT_08(prev);
        }

        Held = got;

        return hr;
    }

    IUnk* old = Held;

    if (old) {
        Held = 0;
        COM_SLOT_08(old);
    }

    hr = 0x80004002;

    return hr;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x45AF20
//
// The same helper for the second interface. Written out rather than shared.
long ComHolder_0045AEA0::FUN_0045AF20(IUnk** source)
{
    long   hr;
    IUnk*  from = *source;

    if (from != 0) {
        void* pv;

        hr = COM_QUERY(from, &DAT_00819088, &pv);

        if (hr < 0) {
            IUnk* bad = Held;

            if (bad) {
                COM_SLOT_08(bad);
            }

            Held = 0;

            return hr;
        }

        IUnk* prev = Held;
        IUnk* got  = (IUnk*)pv;

        if (prev) {
            COM_SLOT_08(prev);
        }

        Held = got;

        return hr;
    }

    IUnk* old = Held;

    if (old) {
        Held = 0;
        COM_SLOT_08(old);
    }

    hr = 0x80004002;

    return hr;
}
