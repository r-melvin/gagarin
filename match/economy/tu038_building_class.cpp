// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Original translation unit TU038 of retail gamemd.exe v1.001; its source-file name is
//   not attested by the binary, so the file keeps a placeholder name. Code range 0x43af40-0x45af9f,
//   segmented from retail evidence (link-ordered static-initialiser table, RTTI class
//   ownership, neighbouring object bounds). Functions are in ascending retail address order.
//   Obj_/Gbl_ views below are per-function placeholder receivers. Replacing
//   them with the canonical class re-mangles their symbols, so that is left to
//   a separate rename-only change.
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

#include "house_building/building_a_views.h"
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

// GLOBAL: GAMEMD 0x89C818
// The cell value slot 189 returns; its static initialiser 0x43B0E0 writes both
// words.
extern CellStruct DAT_0089C818;

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

#include <stdlib.h>
#include "house_building/building_a_views.h"

// One refund of a production slot: the production object is looked up, the building is flagged while the
// owner is told, then the flag is restored (inline in retail, once per slot).
inline void BAReleaseSlot(BuildingAView* b, int handle)
{
    BAProdView* prod = FUN_004CA160(handle);
    unsigned char saved = b->unknown_81;
    b->unknown_81 = 1;
    if (prod) {
        if (!prod->vf_33()->vf_37(1, 0, 0, b->Owner)) {
            b->Owner->FUN_004FAA10(b->Type->unknown_EB8, prod->vf_33()->vf_16(0, 0));
        }
    }
    b->unknown_81 = saved;
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
// FUNCTION: GAMEMD 0x43ED40
//
// CAPPED at 10.1% (first transcription plus two reshapes). The facing from this building (plus the per-type
// firing offset, a zero coordinate by default) to a target. Delta: retail keeps the offset in ESI/EDI with
// the Z in a stack slot and reaches one shared transform call from both branches with different buffers;
// the sequential, shared-pointer and branch-swapped forms differ in prologue, frame (0x18 vs 0x2c) and call order.
HBDir BuildingAView::vf_314(BAObjView* target)
{
    HBCoord off = DAT_0089C848;
    BATypeView* type = Type;
    HBPoint2D p;
    HBPoint2D buf;
    if (type->unknown_E44.X == 0xFFFF && type->unknown_E44.Y == 0xFFFF) {
        p = type->unknown_11E0;
        if (p.X != 0 || p.Y != 0) {
            HBPoint2D* r = DAT_00887324->FUN_006D2070(&buf, &p);
            off.X = r->X;
            off.Y = r->Y;
            off.Z = 0;
        }
    } else {
        HBPoint2D* r = DAT_00887324->FUN_006D2070(&p, &type->unknown_E44);
        off.X = r->X;
        off.Y = r->Y;
        off.Z = 0;
    }
    HBCoord c;
    HBCoord* pc = vf_18(&c);
    int px = pc->X + off.X;
    int py = pc->Y + off.Y;
    HBCoord t;
    HBCoord* pt = target->vf_18(&t);
    int tx = pt->X;
    HBDir d;
    d.Raw = (short)((FUN_004CAE30((double)py - pt->Y, (double)tx - px) - DAT_007E2820) * DAT_007E2818);
    return d;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x442C40
// CAPPED at 86.5% (multiset identical). Delta: retail loads the AddItem vptr before the capacity sum and uses EDX
// for the type value; AddItem written as cap-local, member-reload and nested forms (86.5/84.3/77.5%).
void BuildingAView::vf_9()
{
    FUN_006F3F40();
    if (Owner) {
        unknown_53C = Owner->unknown_34->unknown_B8;
        Owner->FUN_004FF700(this);
    }
    if (Type) {
        unknown_70 = unknown_6C = Type->unknown_A0;
        int v = Type->unknown_680;
        if (v == -1) {
            v = Type->unknown_684;
        }
        unknown_2FC = v;
        Facing.FUN_004C9680(Type->unknown_71C);
        if (!Type->vf_48()) {
            unknown_6DC = 0;
        } else {
            Type->FUN_00465AF0();
            unknown_6E9 = 1;
        }
        if (Owner && Owner->unknown_2C0 && !Type->unknown_CCE && Type->unknown_C8E && Type->unknown_408) {
            unknown_150.FUN_00750090(1);
        }
    }
    if (Type && Type->unknown_16B0) {
        DAT_008B41E0.AddItem(this);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4436F0
bool BuildingAView::vf_80(int mode, HBCell* cell, int a3, int a4)
{
    if (mode == 5) {
        vf_222(1, DAT_0087F7E8.FUN_005657A0(cell), 0, 0);
    } else if (mode == 6 || mode == 1) {
        bool blocked = false;
        if (!Type->unknown_16B9
            || (Owner->FUN_0050B730() && DAT_00A8B238 && DAT_00A8B320 && unknown_2C0 == 0)) {
            if (Type->unknown_408 != 0 || vf_161()) {
                FUN_00443860(cell, 1);
            }
        } else {
            blocked = true;
        }
        if (Type->unknown_408 != 0 && !blocked) {
            BATargetRef targetBuf;
            BAEvent ev;
            BAEvent* queued = ev.FUN_004C65E0(vf_14(), 0x16, *targetBuf.FUN_006E6AB0(this));
            if (DAT_00A802C8.Count < 128) {
                DAT_00A802C8.List[DAT_00A802C8.Head] = *queued;
                DAT_00A802C8.unknown_378C[DAT_00A802C8.Head] = timeGetTime();
                DAT_00A802C8.Head = (DAT_00A802C8.Head + 1) & 0x7F;
                DAT_00A802C8.Count++;
            }
        }
    }
    return true;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x443B90
// CAPPED at 17.1%. Retail places the Base(0) fallback inline right after the first two tests and jumps back
// to it from the later failures; the three shapes tried (target=0 else-if, if/else with a trailing call, early
// returns) all put that block last. Instruction multiset differs by one jcc sense.
void BuildingAView::vf_242(BAObjView* target)
{
    if (unknown_AC != 0x13 && vf_212()) {
        if (target && vf_254(0)->First && !vf_254(0)->First->Type->unknown_2A4 && !vf_235(target)) {
            FUN_006FCDB0(0);
            if (Type->unknown_16C4 || Type->unknown_16CA) {
                if (!Owner->FUN_0050B730() && !vf_223()) {
                    vf_122(0x13, 0);
                    vf_123();
                }
            }
            return;
        }
    } else {
        target = 0;
    }
    FUN_006FCDB0(target);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4456D0
void BuildingAView::vf_312()
{
    int i;
    if (Owner == DAT_00A83D4C && !unknown_81 && unknown_41B && unknown_660) {
        switch (Type->unknown_EB8) {
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
            sound = RulesInstance->unknown_700;
        } else {
            sound = RulesInstance->unknown_70C;
            if (Owner->IsControlledByCurrentPlayer()) {
                vf_82(7);
            }
            NeedsRepairs = 1;
            if (Owner->IsControlledByCurrentPlayer()) {
                FUN_00752700(s_EVA_Repairing_00818F18, -1, -1);
            }
        }
    } else {
        sound = RulesInstance->unknown_70C;
    }
    if (Owner->IsControlledByCurrentPlayer()) {
        CoordStruct where = Location;
        FUN_007509E0(sound, &where, 0);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x447110
//
// CAPPED (see the report): retail is a three-case switch on the mode whose "nothing to do" exits jump to the
// shared epilogue, which no switch/return/flag formulation tried here reproduces; the first-written
// if-chain form below scores best.
void BuildingAView::vf_104(int mode)
{
    if (!unknown_6E9) {
        if (Type->unknown_16C0) {
            Type->vf_33(Owner);
            Owner->FUN_0050B730();
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
        if (vf_97() == 0x13 || unknown_6DF) {
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
    if (Owner->FUN_0050B6F0()) {
        VocClass::PlayGlobal(RulesInstance->unknown_70C, 1.0f, 0x2000, 0);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x447210
// CAPPED at 3.3% (first transcription, two forms). Delta: retail pushes EDI after the early returns and has a 0xc frame;
// the same register-lifetime effect as vf_80 but in the other direction.
int BuildingAView::vf_29(BAObjView* obj, char flag)
{
    int r;
    if (Type->unknown_1701) {
        return 0;
    }
    if (obj->vf_11() == 6 && obj->unknown_520->unknown_1701) {
        return 0;
    }
    r = FUN_006FFEC0(obj, flag);
    if (r == 8) {
        return 8;
    }
    if (r == 4) {
        if (Type->unknown_CD1 && DAT_00A83D4C == Owner) {
            if (!unknown_268) {
                if (Owner->unknown_24.vf_8() - Owner->unknown_24.vf_9() <= Type->unknown_EEC) {
                    r = 0;
                    return r;
                }
            }
        } else if (!((Type->unknown_16AE || Type->unknown_16AF) && unknown_114 > 0)) {
            if (vf_258() <= 0 && Type->unknown_EB8 == 0) {
                r = 0;
                return r;
            }
        }
        r = 4;
        if (Type->unknown_EB8 != 0 && unknown_3D3) {
            r = 0;
        }
        return r;
    }
    if (r == 5) {
        if (vf_254(0)->First == 0) {
            goto checkTarget;
        }
        if (!vf_254(0)->First->Type->unknown_2A5 || Type->unknown_16C3) {
            r = 0;
        }
        if (unknown_AC == 0x13) {
            r = 0;
            return r;
        }
    }
    if (r == 1 || r == 2) {
        if (!vf_40()) {
            r = 7;
            return r;
        }
        int kind = Type->unknown_EB8;
        if (kind == 0x10 || kind == 0x28 || kind == 3) {
            if (!DAT_0087F770->FUN_0054F5C0(DAT_00A8EBF8) && !DAT_0087F770->FUN_0054F5C0(DAT_00A8EBFC)) {
                r = 7;
                return r;
            }
            HBCoord tmp;
            HBCoord* c = obj->vf_18(&tmp);
            HBCell cell;
            cell.X = (short)(c->X / 256);
            cell.Y = (short)(c->Y / 256);
            HBCell cellCopy = cell;
            if (Type->unknown_EB8 != 3) {
                HBCoord where;
                where.X = (cell.X << 8) + 0x80;
                where.Y = (cell.Y << 8) + 0x80;
                where.Z = 0;
                if (!vf_179(&where)) {
                    r = 2;
                }
                if (!(DAT_0087F7E8.FUN_005657A0(&cellCopy)->unknown_140 & 0x100)
                    && DAT_0087F7E8.FUN_005657A0(&cellCopy)->unknown_4C != 0) {
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
    if (obj->vf_34()->unknown_233) {
        r = 2;
    }
    return r;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x447540
// CAPPED at 42.2%. Delta: retail keeps one separate "xor ebx,ebx; jmp done" per exit and a flat r==1||r==2 test; goto, else-if and split forms all give the same 42.2%.
int BuildingAView::vf_28(HBCell* cell, char a, char b)
{
    int r;
    if (Type->unknown_1701) {
        return 0;
    }
    if (Type->unknown_408 != 0 && a != 0) {
        r = FUN_00700600(cell, 0, b);
        HBCoord tmp;
        if (!DAT_0087F7E8.FUN_00586360(DAT_0087F7E8.FUN_005657A0(cell)->vf_18(&tmp))
            && r == 1
            && DAT_0087F7E8.FUN_005657A0(cell)->unknown_EC == 5
            && Type->unknown_5ED && Type->unknown_5EC) {
            return 6;
        }
    } else {
        r = FUN_00700600(cell, a, b);
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
            if (Type->unknown_EB8 != 3) {
                HBCoord where;
                where.Z = 0;
                where.X = (cell->X << 8) + 0x80;
                where.Y = (cell->Y << 8) + 0x80;
                if (!vf_179(&where)) {
                    r = 2;
                }
                if (!(DAT_0087F7E8.FUN_005657A0(cell)->unknown_140 & 0x100)
                    && DAT_0087F7E8.FUN_005657A0(cell)->unknown_4C != 0) {
                    r = 2;
                    goto done;
                }
            }
        }
    }
    if (r == 5) {
        if (vf_254(0)->First == 0) {
            return r;
        }
        if (!vf_254(0)->First->Type->unknown_2A5 || Type->unknown_16C3) {
            r = 0;
        }
        if (unknown_AC == 0x13) {
            r = 0;
        } else if (r == 5) {
            return r;
        }
    }
done:
    if (vf_161() && Owner->FUN_0050B6F0()) {
        r = 1;
    }
    return r;
}

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
// FUNCTION: GAMEMD 0x447B20
// CAPPED at 5.3%. Delta: retail keeps a 0x34 frame with a dead Location copy (Z=0, X, Y stores) and shares one
// epilogue; early-return, single-result and per-block-temporary forms tried.
HBCoord BuildingAView::FUN_00447B20(BAObjView* arg)
{
    HBCoord tmp;
    HBCoord r;
    if (Type->unknown_16BC) {
        HBCell cell;
        HBCell* c = vf_110(&cell);
        HBCell shifted;
        shifted.X = c->X + 2;
        shifted.Y = c->Y + 1;
        r.X = (shifted.X << 8) + 0x80;
        r.Y = (shifted.Y << 8) + 0x80;
        r.Z = Location.Z;
        return r;
    }
    if (Type->unknown_16BB) {
        HBCoord* p = FUN_005F6C80(&tmp, arg);
        r.X = p->X + 0x80;
        r.Y = p->Y;
        r.Z = p->Z;
        return r;
    }
    if (Type->unknown_16AB && arg) {
        HBCoord* pa = arg->vf_18(&tmp);
        HBCoord tb;
        HBCoord* pb = vf_18(&tb);
        int bx = pb->X;
        int ax = pa->X;
        HBDir d;
        d.Raw = (short)((FUN_004CAE30((double)pb->Y - pa->Y, (double)ax - bx) - DAT_007E2820) * DAT_007E2818);
        int dir = ((d.Whole >> 7) + 1 >> 1) & 0xFF;
        HBCoord* pc = vf_18(&tb);
        if (dir >= 0 && dir < 0x40) {
            r.X = pc->X + 0x80;
            r.Y = pc->Y - 0x80;
        } else if (dir >= 0x40 && dir < 0x80) {
            r.X = pc->X + 0x80;
            r.Y = pc->Y + 0x80;
        } else if (dir >= 0x80 && dir < 0xC0) {
            r.X = pc->X - 0x80;
            r.Y = pc->Y + 0x80;
        } else {
            r.X = pc->X - 0x80;
            r.Y = pc->Y - 0x80;
        }
        r.Z = pc->Z;
        return r;
    }
    if (!Type->unknown_16CB && !Type->unknown_16A9) {
        return *FUN_005F6C80(&tmp, arg);
    }
    switch (Type->unknown_1780) {
    case 0:
        return *vf_18(&tmp);
    case 1: {
        HBCoord* pc = vf_18(&tmp);
        HBCoord* off = Type->unknown_1788;
        r.X = off->X + pc->X;
        r.Y = off->Y + pc->Y;
        r.Z = off->Z + pc->Z;
        return r;
    }
    default: {
        int idx = FUN_0065AD90(arg);
        if (idx >= 0 && idx < Type->unknown_1780) {
            HBCoord* off = &Type->unknown_1788[idx];
            HBCoord* pc = vf_18(&tmp);
            r.X = off->X + pc->X;
            r.Y = off->Y + pc->Y;
            r.Z = off->Z + pc->Z;
            return r;
        }
        return *vf_18(&tmp);
    }
    }
}

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
// FUNCTION: GAMEMD 0x447F10
//
// CAPPED at 91.0% (instruction multiset identical): retail takes the absolute value of the quantised limit
// before the absolute value of the facing difference; every operand order tried evaluates them the other way.
int BuildingAView::vf_240(BAObjView* target, int b, int c)
{
    if (!Type->unknown_157B || (Type->unknown_157C && vf_258())) {
        if (!FUN_0070FEC0()) {
            if (Type->unknown_16C3) {
                return 6;
            }
            if (vf_97() != 0x13 && vf_97() != 0x12) {
                if (!vf_212()) {
                    return 6;
                }
                if (unknown_714) {
                    return 3;
                }
                int r = FUN_006FC0B0(target, b, c);
                if (r == 0 && vf_255()) {
                    HBDir want = vf_314(target);
                    int quant = Type->unknown_16C5 ? 0 : 8;
                    short diff = Facing.FUN_004C93D0().Raw;
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
// FUNCTION: GAMEMD 0x448160
// CAPPED at 81.7% (multiset identical). Delta: retail keeps the type pointer in EAX and the kind in ECX; the
// kind-first and result-first orders both allocate the other way.
char BuildingAView::vf_316()
{
    int kind = Type->unknown_EB8;
    char r = unknown_3D3;
    if (kind != 0) {
        if (r) {
            unknown_3D3 = 0;
        } else {
            int i = 0;
            int count = Owner->unknown_78;
            if (count > 0) {
                do {
                    BuildingAView* other = Owner->unknown_6C[i];
                    if (!other->unknown_81) {
                        BATypeView* ot = other->Type;
                        if (ot->unknown_EB8 == Type->unknown_EB8) {
                            if ((Type->unknown_CCE && ot->unknown_CCE) || (!Type->unknown_CCE && !ot->unknown_CCE)) {
                                other->unknown_3D3 = 0;
                            }
                        }
                    }
                    i++;
                } while (i < count);
            }
            unknown_3D3 = 1;
            if (Owner->FUN_0050B6F0()) {
                FUN_00752700(s_EVA_PrimaryBuildingSelected_00818F28, -1, -1);
            }
            if (Type->unknown_EB8 == 7) {
                Owner->FUN_0050DB00(this);
            }
        }
        vf_73(2);
        r = unknown_3D3;
    }
    return r;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x449410
int BuildingClass::GetYSort() const
{
    int base = ObjectClass::GetYSort();

    BuildingTypeClass* flags = Type;

    return base + ((flags->bools_16A4[0x16C5 - 0x16A4] ? 0x20 : 0) - (flags->bools_16A4[0x16B7 - 0x16A4] ? 0x10 : 0));
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x449440
int BuildingClass::vf_107(CellClass* target, int a2, int a3, int a4, int a5)
{
    CellStruct cell = target->MapCoords;
    BuildingTypeClass* type = Type;
    if (type->UndeploysInto != 0 && IsOnMap) {
        return DAT_0087F7E8.FUN_005657A0(&cell)->FUN_0047C620(type->SpeedType, type, Owner) ? 0 : 7;
    }
    return type->vf_42(&cell, Owner) ? 0 : 7;
}

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
// FUNCTION: GAMEMD 0x4496B0
// CAPPED at 41.5%. Delta: retail realigns the stack (AND ESP,-8, 0x38 frame), keeps a masked flag byte in a stack
// local and evaluates the price conversion before the counter call; local flag, temp price and operand-swap forms tried.
int BuildingAView::vf_135()
{
    int i;
    unsigned char active;
    if (vf_33()->unknown_CD5) {
        FUN_0070E000(unknown_C4);
        unknown_C4 = 0;
    }
    if (vf_171()) {
        unknown_6DD = 1;
        if (!Type->unknown_16C3) {
            int idx = Type->unknown_16F0;
            HBIdx3View* link;
            if (idx == -1 || (link = DAT_00A83CBC[idx]->unknown_28->unknown_C8) == 0
                || Owner->unknown_5550.FUN_0049FAE0(link->unknown_DF8) != 0) {
                if (Type->unknown_16F0 != -1) {
                    goto price;
                }
            }
            if (!Type->unknown_157B || vf_258() > 0) {
                if (Target) {
                    vf_122(1, 0);
                    vf_123();
                    return 1;
                }
            }
        }
    price:
        int price = (int)(DAT_007E27F8 * FUN_005B3A00()->unknown_18);
        return DAT_00A8B230->Counter.FUN_0065C7E0(0, 2) + price;
    }
    if (Type->unknown_16B5) {
        return 100;
    }
    switch (unknown_BC) {
    case 0:
        FUN_00447780(1);
        unknown_BC = 1;
        break;
    case 1:
        if (Type->unknown_16A9 || Type->unknown_16AA || Type->unknown_16AB) {
            for (i = 0; i < unknown_E8; i++) {
                BAObjView* o = FUN_0065AD30(i);
                if (o && (active = o->unknown_14 & 1) != 0) {
                    if (o->vf_97() == 7) {
                        HBCoord a, b, d;
                        HBCoord* pa = o->vf_18(&a);
                        HBCoord* pb = vf_18(&b);
                        HBCoord* diff = d.FUN_0041C230(pb->X - pa->X, pb->Y - pa->Y, pb->Z - pa->Z);
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
        if (Type->unknown_16BD) {
            FUN_00449540();
        }
        break;
    }
    if (Type->unknown_16AA && FUN_0065AE30()) {
        if (vf_157(0x1D) != 1 && vf_157(0x13) == 1) {
            vf_122(0x14, 0);
        }
    }
    if (Type->unknown_16A9) {
        int price = (int)(DAT_007E27F8 * FUN_005B3A00()->unknown_10);
        return DAT_00A8B230->Counter.FUN_0065C7E0(0, 2) + price;
    }
    int price = (int)(DAT_007E27F8 * FUN_005B3A00()->unknown_10);
    return DAT_00A8B230->Counter.FUN_0065C7E0(0, 2) + price * 3;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x449A40
int BuildingClass::vf_136()
{
    return vf_135();
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x449A50
int BuildingAView::vf_145()
{
    HBCoord soundPos;
    HBCoord pos;
    switch (unknown_BC) {
    case 0: {
        FUN_00447780(0);
        vf_157(0xB);
        int sound = Type->unknown_E6C;
        if (sound != -1 || (sound = RulesInstance->unknown_6C8) != -1) {
            soundPos = Location;
            FUN_007509E0(sound, &soundPos, &unknown_6A0);
        }
        unknown_80 = 1;
        unknown_BC = 1;
        break;
    }
    case 1:
        unknown_80 = 1;
        pos = Location;
        FUN_00750D40(&pos, &unknown_6A0);
        if (unknown_6DD) {
            vf_157(0xC);
            vf_157(3);
            FUN_00447780(1);
            vf_311(0);
            vf_122(5, 0);
            if (!Type->unknown_16BF) {
                HBDir dir((unsigned char)Type->unknown_ED8);
                Facing.FUN_004C9300(&dir);
            }
            Type->FUN_00465AF0();
            unknown_6A0.FUN_00406060();
            return 1;
        }
        break;
    }
    return 1;
}

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
            DAT_008871E0->At_4A8, false, true, 1.0f, 0.0f);
        if (laser) {
            laser->IsHouseColor = true;
            laser->Thickness = 3;
        }
    }

    this->At_2EC = CDTimer_0044ABD0(DAT_008871E0->At_4A4);
    this->At_664 = 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x44B760
int BuildingClass::vf_133()
{
    return MissionClass::vf_133();
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x44B770
int BuildingClass::vf_137()
{
    return MissionClass::vf_137();
}

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
// FUNCTION: GAMEMD 0x44D760
void BuildingAView::vf_238(void* arg)
{
    if (arg && Owner->FUN_0050B6F0()) {
        HBCoord coordTmp;
        HBCoord* c = vf_19(&coordTmp, 0);
        HBCell cell;
        cell.X = (short)(c->X / 256);
        cell.Y = (short)(c->Y / 256);
        HBCell tmp = cell;
        tmp.FUN_00660B80();
    }
}

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
    } else if (vf_255() && !Type->unknown_16C5) {
        unsigned int raw = Facing.FUN_004C93D0().Whole;
        out->Raw = (short)(((((raw >> 10) + 1) >> 1) & 0x1F) * 0x800);
    } else {
        *out = vf_314(Target);
    }
    return out;
}

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
        if (ratio <= RulesInstance->unknown_1700) {
            low = 1;
            name = Type->unknown_1424;
        } else {
            low = 0;
            name = Type->unknown_1414;
        }
        if (name && *name) {
            FUN_00451890(name, 0x12, low, 0, 0);
        }
    }
    if (Type->unknown_16AD && Anims[10] == ptr) {
        double ratio = FUN_005F5C60();
        char* name;
        int low;
        if (ratio <= RulesInstance->unknown_1700) {
            low = 1;
            name = Type->unknown_1028;
        } else {
            low = 0;
            name = Type->unknown_1018;
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
    if (Type == (BATypeView*)ptr) {
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
// FUNCTION: GAMEMD 0x44EB10
int BuildingClass::vf_195()
{
    if (!HasBeenCaptured && DAT_00A8B230->Counter.FUN_0065C7E0(0, 0x63) < 0x19 && Type->Factory == 7) {
        return RulesInstance->unknown_F70;
    }
    return TechnoClass::vf_195();
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x44EBF0
// CAPPED at 67.4%. Delta: retail merges the type!=7 path into the fifth inlined slot copy (jump into the middle);
// loop, helper-inline and if/else-with-helper forms tried, none merges.
void BuildingAView::vf_55(char arg)
{
    if (arg) {
        if (Factory) {
            FUN_004C9FF0(Factory);
            if (Factory) {
                Factory->vf_8(1);
            }
            Factory = 0;
        }
        if (Owner) {
            if (Type->unknown_EB8 == 7) {
                if (Owner->unknown_53BC[0]) {
                    BAReleaseSlot(this, Owner->unknown_53BC[0]);
                }
                if (Owner->unknown_53BC[1]) {
                    BAReleaseSlot(this, Owner->unknown_53BC[1]);
                }
                if (Owner->unknown_53BC[2]) {
                    BAReleaseSlot(this, Owner->unknown_53BC[2]);
                }
                if (Owner->unknown_53BC[3]) {
                    BAReleaseSlot(this, Owner->unknown_53BC[3]);
                }
                if (Owner->unknown_53BC[4]) {
                    BAReleaseSlot(this, Owner->unknown_53BC[4]);
                }
            } else {
                int handle = Owner->FUN_00500510(Type->unknown_EB8, Type->unknown_CCE, 0);
                if (handle) {
                    BAReleaseSlot(this, handle);
                }
            }
        }
        vf_160(3);
    } else {
        int i;
        for (i = 0; i < unknown_E8; i++) {
            BAObjView* o = FUN_0065AD30(i);
            if (o && !Owner->FUN_004F9A90(o)) {
                vf_158(3, o);
            }
        }
    }
    FUN_005F5280(arg);
}

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
        if (BuildingBGlobal_00A8B238 == 0)
            goto refuse;
        if (BuildingBGlobal_00A8B320 == 0)
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
// FUNCTION: GAMEMD 0x44F640
// CAPPED at 26.0% (13 of 50 instructions). Retail lays the equal-to-empty-coordinate path (the vf_18 copy) after
// the non-equal path, entered by a final `je`; cl keeps it first behind `jne` for every spelling tried
// (`==&&` then-block, `!=||` then-block, a `goto`, an if/else with one return).
HBCoord* BuildingBView::vf_45(HBCoord* out, int)
{
    HBCoord tmp;
    BuildingBTypeView* type = Type;
    if (type->CoordEC8.X != BuildingBEmptyCoord.X || type->CoordEC8.Y != BuildingBEmptyCoord.Y
        || type->CoordEC8.Z != BuildingBEmptyCoord.Z) {
        HBCoord loc = Location;
        *out = loc + type->CoordEC8;
    } else {
        *out = *vf_18(&tmp);
    }
    return out;
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

// FUNCTION: GAMEMD 0x4500A0
CoordStruct BuildingClass::vf_41()
{
    CoordStruct c = vf_18();
    return c + Type->TargetCoordOffset;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4503E0
// Empty function.
void __cdecl FUN_004503E0()
{
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x451330
int BuildingBView::vf_180()
{
    if (!NoCrew && Type->unknown_CCD) {
        int rate;
        int side = Owner->SideIndex;
        if (side == 0)
            rate = BuildingBRules->unknown_14F8;
        else if (side == 1)
            rate = BuildingBRules->unknown_14FC;
        else if (side == 2)
            rate = BuildingBRules->unknown_1500;
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
// FUNCTION: GAMEMD 0x4513D0
int BuildingBView::vf_27()
{
    if (BState && ActuallyPlacedOnMap)
        return Type->vf_39();
    return Type->vf_48();
}

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
// FUNCTION: GAMEMD 0x452250
int BuildingClass::vf_321()
{
    return 0;
}

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

    while (i < DAT_00A8EB50) {
        Obj_00452D40* obj = DAT_00A8EB44[i];

        if (obj != 0 && obj->Owner->At_16BE != 0 && DAT_00A8E7AC == 0
            && obj->At_90 != 0 && obj->At_81 == 0) {
            obj->FUN_00452DC0(0);
            obj->FUN_00452DC0(2);
            obj->FUN_00452DC0(4);
            obj->FUN_00452DC0(6);
            obj->FUN_004533A0(1);
        }

        i++;
    }
}

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
// FUNCTION: GAMEMD 0x453D60
void BuildingClass::vf_60(CoordStruct* coord)
{
    CellStruct cell = CellOfCoord(*coord);
    unsigned int& flags = BuildingBMap.Func_5657A0(&cell)->OccupationFlags;
    flags |= 0x80;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x453DC0
void BuildingClass::vf_61(CoordStruct* coord)
{
    CellStruct cell = CellOfCoord(*coord);
    unsigned int& flags = BuildingBMap.Func_5657A0(&cell)->OccupationFlags;
    flags &= ~0x80u;
}

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
// FUNCTION: GAMEMD 0x454190
HRESULT __stdcall BuildingBView::Save(IStream* pStm, BOOL fClearDirty)
{
    HRESULT hr = Func_70C250(pStm, fClearDirty);
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
// FUNCTION: GAMEMD 0x454250
bool BuildingClass::vf_128()
{
    return IsReadyToCommence ? true : false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x454260
void BuildingBView::vf_13(BuildingBCrcView* crc)
{
    Func_70C270(crc);
    int c4Left = C4Timer.GetTimeLeft();
    crc->AddInt(c4Left);
    int cashLeft = CashProductionTimer.GetTimeLeft();
    crc->AddInt(cashLeft);
    crc->AddInt(BState);
    crc->AddInt(QueueBState);
    crc->AddInt(OwnerCountryIndex);
    if (C4AppliedBy)
        crc->AddInt(C4AppliedBy->Rtti.Fetch_ID());
    crc->AddInt(unknown_544);
    if (FirestormAnim)
        crc->AddInt(FirestormAnim->Rtti.Fetch_ID());
    crc->AddInt(FactoryRetryTimer.GetTimeLeft());
    crc->AddInt(unknown_5FC);
    crc->AddInt(LaserFenceFrame);
    crc->AddInt(FirestormWallFrame);
    crc->AddBool(HasPower);
    crc->AddBool(StuffEnabled);
    crc->AddBool(BeingProduced);
    crc->AddBool(ShouldRebuild);
    crc->AddBool(unknown_6DC);
    crc->AddBool(IsReadyToCommence);
    crc->AddBool(IsBeingRepaired);
    crc->AddBool(NeedsRepairs);
    crc->AddBool(C4Applied);
    crc->AddBool(NoCrew);
    crc->AddBool(unknown_bool_6E1);
    crc->AddBool(unknown_bool_6E2);
    crc->AddBool(HasBeenCaptured);
    crc->AddBool(ActuallyPlacedOnMap);
    crc->AddBool(HasEngineer);
    crc->AddBool(unknown_bool_6E5);
    crc->AddBool(IsDamaged);
    crc->AddInt((unsigned short)unknown_short_700);
    crc->AddByte(UpgradeLevel);
}

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
                    || (BuildingBGlobal_00A8B238 != 0 && Owner != 0 && BuildingBPlayer != 0
                        && BuildingBPlayer->Func_4F9A50(Owner) && Owner->Func_4F9A50(BuildingBPlayer));
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
    int owner = Owner->unknown_30;
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
                if (building && building->Owner->unknown_30 == owner) {
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
                if (building && building->Owner->unknown_30 == owner) {
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
// FUNCTION: GAMEMD 0x4555D0
// Every refusal shares one epilogue in retail; written as separate returns cl gives each its own.
bool BuildingBView::vf_212()
{
    int two = 2;
    if (!HasPower && Overpowerers.Count < two)
        goto refuse;
    if (EMPLockRemaining > 0)
        goto refuse;
    if (Health == 0)
        goto refuse;
    if (Type->unknown_1573 && Type->unknown_EE4 > 0 && Owner->Func_4FCE30() < 1.0) {
        if (Overpowerers.Count < two)
            goto refuse;
    }
    {
        BuildingBTypeView* type = Type;
        if (type->unknown_1574) {
            BuildingBHouseView* owner = Owner;
            if (owner->unknown_timer_2A4.GetTimeLeft() != 0)
                goto refuse;
            if (owner->unknown_577B)
                goto refuse;
        }
        if (type->unknown_1552 && !HasEngineer)
            goto refuse;
    }
    if (vf_97() != 0x12 && vf_97() != 0x13)
        return true;
refuse:
    return false;
}

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
    int owner = Owner->unknown_30;
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
    int owner = Owner->unknown_30;
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
    int owner = Owner->unknown_30;
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
    int owner = Owner->unknown_30;
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

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x456970
// Empty function.
void __cdecl FUN_00456970()
{
}

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
// FUNCTION: GAMEMD 0x458DB0
bool BuildingBView::vf_171()
{
    if (vf_256())
        return true;
    return Func_701120();
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x458DD0
bool BuildingClass::vf_256()
{
    return Type->bools_1570[0x157B - 0x1570] && Type->bools_1570[0x157C - 0x1570] && vf_258() > 0;
}

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
// FUNCTION: GAMEMD 0x459870
int BuildingClass::vf_181()
{
    return Type->AntiAirValue;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x459880
int BuildingClass::vf_182()
{
    return Type->AntiArmorValue;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x459890
int BuildingClass::vf_183()
{
    return Type->AntiInfantryValue;
}

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
// FUNCTION: GAMEMD 0x459D80
bool TechnoClass::vf_164()
{
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x459D90
bool TechnoClass::vf_177(int a1)
{
    return true;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x459DA0
int TechnoClass::vf_188()
{
    return 2;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x459DB0
CellStruct TechnoClass::vf_189()
{
    return DAT_0089C818;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x459DC0
void TechnoClass::vf_190(int a1)
{
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x459DD0
bool TechnoClass::vf_200()
{
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x459DE0
void TechnoClass::vf_205()
{
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x459DF0
bool TechnoClass::vf_207()
{
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x459E00
bool TechnoClass::vf_208()
{
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x459E10
bool TechnoClass::vf_209()
{
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x459E20
bool TechnoClass::vf_210()
{
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x459E30
bool TechnoClass::vf_211()
{
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x459E40
bool TechnoClass::vf_224()
{
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x459E50
bool TechnoClass::vf_247(int a1)
{
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x459E60
void TechnoClass::vf_270(int a1, int a2)
{
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x459E70
int BuildingClass::vf_12()
{
    return 0x720;
}

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
// FUNCTION: GAMEMD 0x459EC0
int BuildingClass::vf_11()
{
    return 6;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x459ED0
const wchar_t* BuildingClass::vf_36()
{
    return Type->UIName;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x459EE0
ObjectTypeClass* BuildingClass::vf_34()
{
    return Type;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x459EF0
// CAPPED at 41.2% (7 of 17 instructions; retail-only: `add ecx,-0x80`, `lea esi,[eax-0x80]`; cl-only: two
// `sub reg,0x80`). Retail adds the negative constant (an `add` of 0xFFFFFF80 and an `lea` with a -0x80
// displacement) where cl always canonicalises a constant add of a negative immediate to `sub`. Variants
// tried: direct field subtraction, a struct copy with -=, operator- / operator+ with a named offset
// coordinate, and `+ -0x80`.
HBCoord* BuildingBView::vf_43(HBCoord* out)
{
    HBCoord c = Location;
    c.X -= 0x80;
    c.Y -= 0x80;
    *out = c;
    return out;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x459F20
void* BuildingBView::vf_8(unsigned int flags)
{
    Func_43BCF0();
    if (flags & 1)
        operator delete(this);
    return this;
}

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
// FUNCTION: GAMEMD 0x459F60
int Triple3i::FUN_00459F60(const Triple3i* other) const
{
    return a == other->a && b == other->b && c == other->c;
}

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
// FUNCTION: GAMEMD 0x45A160
void Obj_00437FC0::FUN_0045A160()
{
    if (Held) {
        IFACE_CALL(Held, 0x8);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x45A170
void Obj_00437FC0::FUN_0045A170()
{
    if (Held) {
        IFACE_CALL(Held, 0x4);
    }
}

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
