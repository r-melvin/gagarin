// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Original translation unit TU044 of retail gamemd.exe v1.001; its source-file name is
//   not attested by the binary, so the file keeps a placeholder name. Code range 0x471540-0x47318f,
//   segmented from retail evidence (link-ordered static-initialiser table, RTTI class
//   ownership, neighbouring object bounds). Functions are in ascending retail address order.
//   Obj_/Gbl_ views below are per-function placeholder receivers. Replacing
//   them with the canonical class re-mangles their symbols, so that is left to
//   a separate rename-only change.
//
// Retail RTTI TypeDescriptors 0x81B5E8 and 0x81B620 identify
// VectorClass<CaptureManagerClass*> and DynamicVectorClass<CaptureManagerClass*>;
// the latter's CHD gives the former as a zero-offset base. Complete entry-origin
// spans bind these methods; no standalone constructor or original TU is claimed.
// GX shortens the derived deleting wrapper; no GX matches its full retail body.
//
// Retail PAUControlNode RTTI establishes the pointer element type and zero-offset
// DynamicVectorClass -> VectorClass base chain. Complete entry-origin spans
// establish the bound methods. GX emits a short derived deleting wrapper;
// no GX reproduces its full retail body. No TypeList or constructor is bound;
// original TU boundaries, final link and complete object sizes are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
//
// Complete retail entry spans: 0x4722E0 (0x0C), 0x4726C0 (0x29),
// 0x4726F0 (0x2C), 0x4728E0 (0x7F), 0x472960 (0x38), and two six-byte
// entries at 0x4729A0/0x4729B0. The FUN method
// names and source grouping are unknown; Save/GetClassID follow their
// IPersistStream/IPersist vtable positions and observed operations.
// These methods use the existing receiver layout. 0x4726F0 calls the
// owner's +4 interface through slot +0x10 with COM-style stack this.
//
//   cross-checked against an outside reference.
//
//   an outside reference method map).
//
//   Names cross-checked against an outside reference.
//
//   Bytes matched against the user's retail gamemd.exe v1.001 at 0x471FF0.
//
// File-scope DynamicVectorClass<T> objects whose exit-time destructors were
// emitted as stand-alone stubs: each stub restores the VectorClass<T> vtable,
// frees the array when it is owned, and clears the flag and capacity. T is the
// element type of the vector's RTTI TypeDescriptor, read through the vptr stored by the
// matching initialiser. The initialisers (the __xc table entries, which also
// register these stubs with atexit) are left to the translation-unit migration;
// they compile here as a by-product and are not claimed. The globals' retail
// addresses are bound for verification through the per-TU symbol map.
//
// VectorClass construction, ordered ascending by retail address, written out
// longhand per the family rule.
// VC6FLAGS: /nologo /c /O2 /Gr /GR /DNDEBUG /Gy /MT /Ob2
//   /Ob2: retail's __xc entries point straight at the initialiser bodies (no
//   out-of-line _$E thunk behind a jump).

#include "../FUNCTION.H"
#include "../core/vector_add_item_free.h"

// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.

// VTABLE: GAMEMD 0x7E4AF4 -- VectorClass<CaptureManagerClass*>.
template class VectorClass<CaptureManagerClass*>;
// VTABLE: GAMEMD 0x7E4AD4 -- DynamicVectorClass<CaptureManagerClass*>.
template class DynamicVectorClass<CaptureManagerClass*>;

typedef VectorClass<CaptureManagerClass*> GgCaptureManagerVector;
typedef DynamicVectorClass<CaptureManagerClass*> GgCaptureManagerDynamicVector;
GG_STATIC_ASSERT(sizeof(CaptureManagerClass*) == 4);
GG_STATIC_ASSERT(sizeof(GgCaptureManagerVector) == 0x10);
GG_STATIC_ASSERT(offsetof(GgCaptureManagerVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgCaptureManagerVector, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgCaptureManagerVector, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgCaptureManagerVector, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgCaptureManagerVector, unknown_0E) == 0x0E);
GG_STATIC_ASSERT(sizeof(GgCaptureManagerDynamicVector) == 0x18);
GG_STATIC_ASSERT(offsetof(GgCaptureManagerDynamicVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgCaptureManagerDynamicVector, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgCaptureManagerDynamicVector, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgCaptureManagerDynamicVector, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgCaptureManagerDynamicVector, unknown_0E) == 0x0E);
GG_STATIC_ASSERT(offsetof(GgCaptureManagerDynamicVector, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgCaptureManagerDynamicVector, CapacityIncrement) == 0x14);



// VTABLE: GAMEMD 0x7E4BC4 -- VectorClass<ControlNode*>.
template class VectorClass<ControlNode*>;
typedef VectorClass<ControlNode*> GgControlnodeVectorClass;
GG_STATIC_ASSERT(offsetof(GgControlnodeVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgControlnodeVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgControlnodeVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgControlnodeVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7E4BA4 -- DynamicVectorClass<ControlNode*>.
template class DynamicVectorClass<ControlNode*>;
typedef DynamicVectorClass<ControlNode*> GgControlnodeDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgControlnodeDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgControlnodeDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgControlnodeDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgControlnodeDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgControlnodeDynamicVectorClass, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgControlnodeDynamicVectorClass, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(ControlNode*) == 4);

#include "../_rt/gg_istream.h"

// The dword/int result is an ABI view, not a recovered original declaration.
struct CaptureOwnerSubobject_4726F0
{
    virtual int __stdcall unknown_00();
    virtual int __stdcall unknown_04();
    virtual int __stdcall unknown_08();
    virtual int __stdcall unknown_0C();
    virtual int __stdcall unknown_10();
};
struct CaptureOwnerView_4726F0
{
    char unknown_00[4];
    CaptureOwnerSubobject_4726F0 unknown_04;
};
GG_STATIC_ASSERT(offsetof(CaptureOwnerView_4726F0, unknown_04) == 0x04);

// Explicit slot-layout prefix for the observed indirect call, not a claim
// that every slot's target or the full owner interface has been recovered.
typedef int (__stdcall *CaptureOwnerCall_4726F0)(CaptureOwnerSubobject_4726F0*);
struct CaptureOwnerSlots_4726F0
{
    void* unknown_00[4];
    CaptureOwnerCall_4726F0 Slot10;
};
GG_STATIC_ASSERT(sizeof(CaptureOwnerCall_4726F0) == 4);
GG_STATIC_ASSERT(offsetof(CaptureOwnerSlots_4726F0, Slot10) == 0x10);

struct Guid_472960
{
    unsigned long unknown_00;
    unsigned long unknown_04;
    unsigned long unknown_08;
    unsigned long unknown_0C;
};
GG_STATIC_ASSERT(offsetof(Guid_472960, unknown_00) == 0);
GG_STATIC_ASSERT(offsetof(Guid_472960, unknown_04) == 4);
GG_STATIC_ASSERT(offsetof(Guid_472960, unknown_08) == 8);
GG_STATIC_ASSERT(offsetof(Guid_472960, unknown_0C) == 0xC);
GG_STATIC_ASSERT(sizeof(Guid_472960) == 0x10);

// GLOBAL: GAMEMD 0x007E9880 — first DWORD of CaptureManager's IPersist class ID.
extern "C" const unsigned long DAT_007E9880;
// GLOBAL: GAMEMD 0x007E9884 — second DWORD of the class ID.
extern "C" const unsigned long DAT_007E9884;
// GLOBAL: GAMEMD 0x007E9888 — third DWORD of the class ID.
extern "C" const unsigned long DAT_007E9888;
// GLOBAL: GAMEMD 0x007E988C — fourth DWORD of the class ID.
extern "C" const unsigned long DAT_007E988C;

// Globals read by this TU's static initialisers (placeholder names).
// GLOBAL: GAMEMD 0x7E1718
extern const double DAT_007E1718;
// GLOBAL: GAMEMD 0x7E4AC0
extern const double DAT_007E4AC0;
// GLOBAL: GAMEMD 0x89E120
extern double DAT_0089E120;

// FUNCTION: GAMEMD 0x00410320 (decl; reloc)
extern "C" long __stdcall FUN_00410320(void* subject, void* stream, int clearDirty);

#include "capture_manager_class.h"

#include "../ai/rebind_slots_methods.h"

#include "capture_manager_can_capture_methods.h"

#include "capture_manager_class_draw_links_methods.h"

#include "capture_manager_class_draw_methods.h"

#include "capture_manager_class_more_methods.h"

#include "capture_manager_free_unit_methods.h"

#include "../core/remove_last_matching_methods.h"


class AITriggerTypeClass;
class AbstractClass;
class AbstractTypeClass;
class AircraftClass;
class AircraftTypeClass;
class AirstrikeClass;
class AlphaShapeClass;
class AnimClass;
class AnimTypeClass;
class BuildingClass;
class BuildingLightClass;
class BuildingTypeClass;
class BulletClass;
class BulletTypeClass;
class CampaignClass;
class CaptureManagerClass;
class ColorScheme;
class CommandClass;
class DiskLaserClass;
class EBolt;
class EgoClass;
class FactoryClass;
class FootClass;
class HouseClass;
class HouseTypeClass;
class InfantryClass;
class InfantryTypeClass;
class IsometricTileClass;
class IsometricTileTypeClass;
class LightConvertClass;
class LightSourceClass;
class LineTrail;
class MixFileClass;
class MovieHandle;
class ObjectClass;
class OverlayClass;
class OverlayTypeClass;
class ParasiteClass;
class ParticleClass;
class ParticleSystemClass;
class ParticleSystemTypeClass;
class ParticleTypeClass;
class RadBeam;
class RadSiteClass;
class ScriptClass;
class ScriptTypeClass;
class SideClass;
class SlaveManagerClass;
class SmudgeClass;
class SmudgeTypeClass;
class SpawnManagerClass;
class SpotLightClass;
class SuperClass;
class SuperWeaponTypeClass;
class TActionClass;
class TEventClass;
class TagClass;
class TaskForceClass;
class TeamClass;
class TeamTypeClass;
class TechnoClass;
class TechnoTypeClass;
class TemporalClass;
class TerrainClass;
class TerrainTypeClass;
class TiberiumClass;
class TriggerClass;
class TriggerTypeClass;
class TubeClass;
class UnitClass;
class UnitTypeClass;
class VocClass;
class VoxClass;
class VoxelAnimClass;
class VoxelAnimTypeClass;
class WarheadTypeClass;
class WaveClass;
class WaypointPathClass;
class WeaponTypeClass;
struct HWND__;


#include "../core/vector_ctor_methods.h"

// SYNTHETIC: GAMEMD 0x471570
// GLOBAL: GAMEMD 0x89E170
double DAT_0089E170 = DAT_0089E120 / DAT_007E4AC0;

// SYNTHETIC: GAMEMD 0x471590
// GLOBAL: GAMEMD 0x89E158
double DAT_0089E158 = DAT_007E1718 / DAT_0089E170;

// GLOBAL: GAMEMD 0x89E0F0 -- RTTI identifies DynamicVectorClass<CaptureManagerClass*>.
extern DynamicVectorClass<CaptureManagerClass*> DAT_0089E0F0;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x471890
// Default constructor: an empty control-node vector, one allowed node, and the manager registers itself.
CaptureManagerClass::CaptureManagerClass()
    : ControlNodes(0)
{
    Owner = 0;
    MaxControlNodes = 1;
    InfiniteMindControl = 0;
    OverloadDeathSoundPlayed = 0;
    OverloadDamageDelay = 30;
    OverloadPipState = 0;
    DynamicVectorAddItemFree(&DAT_0089E0F0, this);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x471C90
//
// Whether this mind-controller may take `target`. Rejected: no target; a
// target owned by the same house as the controller; a type immune to
// psionics; a building that is bunker-linked; a target already mind
// controlled (either way); an iron-curtained target; a full controller that is
// not the single-slot kind; and a target busy constructing or selling.
//
// The house test is spelled `!(a != b)`: retail evaluates the target's house
// first, keeps it in EBP and compares `CMP EBP,EAX`. A plain `a == b` makes
// VC6 evaluate the right operand first and flips the compare operands; a
// named temporary keeps the order but swaps EBX/EBP between `this` and the
// temporary.
bool CaptureManagerClass::CanCapture(Techno_00471C90* target) const
{
    if (target == 0)
        return false;

    if (!((target->*target->Vtbl->GetOwningHouse)()
          != (((Techno_00471C90*)this->Owner)->*((Techno_00471C90*)this->Owner)->Vtbl->GetOwningHouse)()))
        return false;

    if ((target->*target->Vtbl->GetTechnoType)()->ImmuneToPsionics)
        return false;

    if (target->BunkerLinkedItem != 0) {
        if ((target->*target->Vtbl->WhatAmI)() == 1)
            return false;
    }

    if (target->IsMindControlled())
        return false;

    if (target->MindControlledByHouse != 0)
        return false;

    if ((target->*target->Vtbl->IsIronCurtained)())
        return false;

    if (!this->InfiniteMindControl) {
        if (this->ControlNodes.Count >= this->MaxControlNodes
            && this->MaxControlNodes != 1)
            return false;
    }

    int mission = target->CurrentMission;
    if (mission == 0x13 || mission == 0x12)
        return false;

    return true;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x471F90
//
// Walk the table from the last entry down to the first and, for every entry
// whose first word equals the key, free it and close the gap by shifting the
// later entries down one slot. Always reports success.
//
// (Revalidated against retail: the earlier single-probe, void-returning form
// missed the backward loop and the `MOV AL,1` result.)
bool Obj_00471F90::FUN_00471F90(void* key)
{
    for (int index = Count - 1; index >= 0; index--) {
        void* item = Items[index];

        if (*(void**)item == key) {
            if (item) {
                FUN_007C8B3D(item);
            }

            if (index < Count) {
                int last = Count - 1;

                Count = last;

                for (int j = index; j < Count; j++) {
                    Items[j] = Items[j + 1];
                }
            }
        }
    }

    return true;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x471FF0
//
// CaptureManagerClass::FreeUnit — release one mind-controlled unit.
//
// The ControlNodes vector is walked back to front looking for the node whose
// Unit is the argument. On a hit the mind-control ring animation is killed
// (slot 0xF8) and unlinked, the "control lost" voice is played at the unit's
// coordinates (the unit type's own sound if it has one, otherwise the rules
// fallback, and nothing at all if neither is set), the unit is handed back to
// the house recorded in the node, the manager's owner bookkeeping is updated,
// the back-pointer at +0x2C0 is cleared, the node is freed and the vector is
// closed up over the hole. A null unit reports false; anything else reports
// true, hit or not.
bool CaptureManagerClass::FreeUnit(TechnoClass* unit)
{
    if (unit == 0) {
        return false;
    }

    Techno_00471FF0* unitView = (Techno_00471FF0*)unit;

    for (int i = ControlNodes.Count - 1; i >= 0; i--) {
        ControlNode* node = ((ControlNode**)ControlNodes.Items)[i];
        if (node->Unit == unit) {
            if (unitView->MindControlRingAnim != 0) {
                Anim_00471FF0* anim = unitView->MindControlRingAnim;
                (anim->*anim->Vtbl->At_F8)();
                unitView->MindControlRingAnim = 0;
            }

            if ((unitView->*unitView->Vtbl->At_84)()->At_5B0 != -1) {
                VocClass_PlayAt_00471FF0(
                    (unitView->*unitView->Vtbl->At_84)()->At_5B0, unitView->GetCoords(), 0);
            } else if (RulesInstance_00471FF0->At_264 != -1) {
                VocClass_PlayAt_00471FF0(
                    RulesInstance_00471FF0->At_264, unitView->GetCoords(), 0);
            }

            (unitView->*unitView->Vtbl->At_3D4)(node->OriginalOwner, 1);
            FUN_004723B0(unit);
            unitView->MindControlledBy = 0;

            ControlNode* dead = ((ControlNode**)ControlNodes.Items)[i];
            if (dead != 0) {
                GameDelete_00471FF0(dead);
            }

            if (i < ControlNodes.Count) {
                ControlNodes.Count = ControlNodes.Count - 1;
                for (int j = i; j < ControlNodes.Count; j++) {
                    ((ControlNode**)ControlNodes.Items)[j] = ((ControlNode**)ControlNodes.Items)[j + 1];
                }
            }
        }
    }

    return true;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x472140  (__thiscall)
// Free every controlled unit, walking the node vector back-to-front.
void CaptureManagerClass::FreeAll()
{
    for (int i = ControlNodes.Count - 1; i >= 0; --i)
        FreeUnit(((ControlNode**)ControlNodes.Items)[i]->Unit);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x472160  CaptureManagerClass::DrawLinks (__thiscall)
//
// Draw the mind-control tethers. A link is drawn when either end is selected
// or the link's own count-down timer still has time on it; the line runs from
// the controller to the controlled unit's coordinate lifted by the unit type's
// +0x3DC, in the owning house's colour, with the per-link index cycling
// backwards through five offsets.
//
// PARTIAL (31.2%, 34/109; multiset is retail plus two `mov`). The control flow
// is instruction-for-instruction identical; what differs is callee-saved
// register naming across three long-lived locals. Retail keeps the loop index
// in EBP, the count-down remainder in the scratch EDX and the elapsed frames in
// ESI; VC6 puts the index in ESI and promotes the remainder into EBP, which
// then costs one extra spill: retail keeps the link coordinate's X in EBP and
// spills only Y, while VC6 spills both X and Y before the type call. Because
// the diff does not normalise register names the whole tail reads as divergent
// -- the honest measure is the two-instruction multiset delta. Variants tried:
// member-wise coordinate construction (23.9%); whole-struct copy
// `Coord from = unit->Location;` (31.2%, kept -- this is what puts `active` in
// BL as retail does); an inline by-value MakeCoord built in the pushed argument
// block (22.9%); `active` declared after the node/unit locals (31.2%, no
// change); the CDTimerClass read hand-inlined at the call site instead of
// through the member (31.2%, byte-identical output); the same read written as
// three early returns (16.2%).
// Lift pass 2 (2026-09-18): one more rejected - the whole CDTimerClass copied
// into a local before the test (`CDTimer_00472160 timer = node->Timer;`), the
// member-struct-copy lever that lifted 0x447AC0; here it spills all three timer
// words and drops to 16.8%. Re-read against retail the residual is a clean
// three-way register permutation with no instruction difference in the loop
// head: retail index->EBP, duration->EDX, elapsed->ESI; cl 8804
// index->ESI, duration->EBP, elapsed->EDX. That is the banked EBX/EBP
// callee-saved preference difference (0x50D440); best form kept at 31.2%.
//
// TAIL-MERGE DIAGNOSTIC (eleventh-batch lever): does NOT apply here.
// Retail's callee-saved pushes sit exactly where ours do (prologue EBX, EBP,
// ESI, EDI on both sides, none sunk), the
// number of epilogues agrees, and the compiled block order already matches,
// so there are no merged return blocks to split. The residual is register
// naming downstream of that, not a prologue hoist.
void CaptureManager_00472160::DrawLinks()
{
    bool ownerSelected = false;
    if (Owner->IsSelected)
        ownerSelected = true;

    for (int i = ControlNodes_Count - 1; i >= 0; i--)
    {
        bool active = false;

        ControlNode_00472160* node = ControlNodes_Items[i];
        Unit_00472160* unit = node->Unit;

        if (node->Timer.GetTimeLeft() > 0)
            active = true;

        if (unit->IsSelected)
            active = true;

        if (Owner != 0 && unit != 0 && (ownerSelected || active))
        {
            Coord_00472160 from = unit->Location;
            from.Z = from.Z + (unit->*unit->Vptr->GetType)()->unknown_3DC;

            Owner_00472160* owner = Owner;
            Color_00472160 color = owner->Owner->LinkColor;
            Coord_00472160 offset;
            offset.X = 0;
            offset.Y = 0;
            offset.Z = 0;

            Owner->FUN_00704E40(
                (owner->*owner->Vptr->At_B0)(-1 - (i % 5), offset, from, color));
        }
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4722A0  (__thiscall)
// True when control capacity is exhausted. Infinite control is never "full".
// Retail tests the infinite-control byte first, then compares Count with Max.
// The named bool local preserves the observed VC6 comparison sequence.
bool CaptureManagerClass::CannotControlAnyMore() const
{
    if (InfiniteMindControl)
        return false;
    bool full = ControlNodes.Count >= MaxControlNodes;
    return full;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4722C0  (__thiscall)
bool CaptureManagerClass::IsControllingSomething() const
{
    return ControlNodes.Count > 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4722D0  (__thiscall)
int CaptureManagerClass::GetControlledCount()
{
    return ControlNodes.Count;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4722E0
bool CaptureManagerClass::FUN_004722E0() const
{
    return MaxControlNodes == 1;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4722F0  (__thiscall)
// Walk the control-node vector back-to-front; for the node controlling `unit`,
// return its captured-from house. Returns null if `unit` is not controlled.
HouseClass* CaptureManagerClass::GetOriginalOwner(TechnoClass* unit) const
{
    for (int i = ControlNodes.Count - 1; i >= 0; --i)
    {
        if (((ControlNode**)ControlNodes.Items)[i]->Unit == unit)
            return ((ControlNode**)ControlNodes.Items)[i]->OriginalOwner;
    }
    return 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x472330
//
// Find the item whose type carries the current selection value, then point every
// slot holding the given key at it. Reports whether anything was rebound.
//
// Three things decide the bytes. The list count is read *before* the selection
// call (retail's `MOV ESI,[0xA80238]` precedes `CALL 0x6A46D0`), which is what
// puts the count in ESI and the walk cursor in EDX. The search is a plain
// indexed loop over the global — `DAT_00A8022C[i]` in both the compare and the
// found re-index — so VC6 loads the list base into EBX inside the preheader,
// after the `count <= 0` test, and strength-reduces the compare into the
// `ADD EDX,4` cursor; a cursor local initialised before the loop hoists that
// load above the test (90.6%). And the found path is `item = ...; break;`
// with one `if (item == 0) return false;` after the loop: the not-found exit
// and the null-item exit then come out as retail's two separate false tails
// (0x472369 and 0x472379), where a `return false` inside the found body is
// cross-jumped into the loop's exit (45.3%).
//
// The slot walk runs backwards and re-reads both the key parameter and the slot
// array on every iteration — retail reloads `[ESP+0x14]` and `[EDI+0x28]` inside
// the loop rather than holding either.
bool CaptureManagerClass::FUN_00472330(TechnoClass* key)
{
    int count = DAT_00A80238;
    int wanted = DAT_00818164.FUN_006A46D0();
    Item_00472330* item = 0;
    for (int i = 0; i < count; i++) {
        if (DAT_00A8022C[i]->Type->At_BC == wanted) {
            item = DAT_00A8022C[i];
            break;
        }
    }
    if (item == 0) {
        return false;
    }
    for (int j = this->ControlNodes.Count - 1; j >= 0; j--) {
        Slot_00472330* slot = ((Slot_00472330**)this->ControlNodes.Items)[j];
        if (slot->Key == key) {
            slot->Value = item;
        }
    }
    return true;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x472640  CaptureManagerClass::NeedsToDrawLinks (__thiscall)
// Mind-control links are drawn when either end is selected, or while any link
// is still inside its fade window. Retail walks the node list *descending* and
// gives each `return true` its own epilogue rather than setting a flag.
bool CaptureManagerClass::NeedsToDrawLinks()
{
    if (((ObjectClass*)Owner)->IsSelected)
        return true;

    if (((TechnoClass*)Owner)->Transporter != 0
        && ((ObjectClass*)((TechnoClass*)Owner)->Transporter)->IsSelected)
        return true;

    for (int i = ControlNodes.Count - 1; i >= 0; i--) {
        ControlNode* node = ((ControlNode**)ControlNodes.Items)[i];

        if (((ObjectClass*)node->Unit)->IsSelected)
            return true;

        int remaining = node->Duration;
        if (node->StartFrame != -1) {
            int elapsed = CurrentFrame - node->StartFrame;
            if (elapsed >= remaining)
                continue;

            remaining -= elapsed;
        }

        if (remaining > 0)
            return true;
    }

    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4726C0
bool CaptureManagerClass::FUN_004726C0(bool* state)
{
    if (InfiniteMindControl && ControlNodes.Count > MaxControlNodes) {
        *state = OverloadPipState > 0;
        return true;
    }
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4726F0
void CaptureManagerClass::FUN_004726F0(Obj_004A1D30* sink)
{
    AbstractClass::vf_13(sink);
    if (Owner != 0) {
        CaptureOwnerSubobject_4726F0* ownerInterface =
            &((CaptureOwnerView_4726F0*)Owner)->unknown_04;
        sink->FUN_004A1D50(ownerInterface->unknown_10());
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4728E0 — IPersistStream::Save slot +0x18; __stdcall, RET 0xC.
long __stdcall CaptureManagerClass::Save(Gg_IStream* stream, int clearDirty)
{
    long baseResult = FUN_00410320(this, stream, clearDirty);
    if (baseResult < 0) {
        return baseResult;
    }

    int count = ControlNodes.Count;
    long result = stream->Write(&count, 4, 0);
    if (result < 0) {
        return result;
    }
    for (int i = 0; i < count; ++i) {
        ControlNode* node = ((ControlNode**)ControlNodes.Items)[i];
        stream->Write(&node->OriginalOwner, 4, 0);
        result = stream->Write(&node->Unit, 4, 0);
        if (result < 0) {
            return result;
        }
    }
    return baseResult;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x472960 — IPersist::GetClassID slot +0x0C; __stdcall, RET 8.
long __stdcall CaptureManagerClass::GetClassID(Guid_472960* outGuid)
{
    if (outGuid == 0) {
        return (long)0x80004003;
    }
    outGuid->unknown_00 = DAT_007E9880;
    outGuid->unknown_04 = DAT_007E9884;
    outGuid->unknown_08 = DAT_007E9888;
    outGuid->unknown_0C = DAT_007E988C;
    return 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// Primary table 0x7E4B40: 0x4729A0 at +0x30, 0x4729B0 at +0x2C.
// Semantic names, original return types and const qualification are unknown.
// FUNCTION: GAMEMD 0x4729A0
int CaptureManagerClass::FUN_004729A0()
{
    return 0x50;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4729B0
int CaptureManagerClass::FUN_004729B0()
{
    return 0x42;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x472A80
// DynamicVectorClass<ControlNode*>::Clear

// FUNCTION: GAMEMD 0x472AB0
// DynamicVectorClass<ControlNode*>::Slot5

// FUNCTION: GAMEMD 0x472AD0
// VectorClass<ControlNode*>::Slot6

// FUNCTION: GAMEMD 0x472B40
// VectorClass<ControlNode*>::operator==

// FUNCTION: GAMEMD 0x472B80
// VectorClass<ControlNode*>::SetCapacity

// FUNCTION: GAMEMD 0x472C30
// VectorClass<ControlNode*>::Clear

// FUNCTION: GAMEMD 0x472C60
// VectorClass<ControlNode*>::FindItemIndex

// FUNCTION: GAMEMD 0x472CA0
// VectorClass<ControlNode*>::Slot5

// FUNCTION: GAMEMD 0x472CC0
// DynamicVectorClass<ControlNode*>::SetCapacity

// FUNCTION: GAMEMD 0x472D70
// DynamicVectorClass<ControlNode*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x473000
// VectorClass<ControlNode*>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x473050
// DynamicVectorClass<ControlNode*>::scalar deleting destructor

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x472AE0
// DynamicVectorClass<CaptureManagerClass*>::Clear
// FUNCTION: GAMEMD 0x472B10
// DynamicVectorClass<CaptureManagerClass*>::Slot5
// FUNCTION: GAMEMD 0x472B30
// VectorClass<CaptureManagerClass*>::Slot6
// FUNCTION: GAMEMD 0x472DA0
// VectorClass<CaptureManagerClass*>::operator==
// FUNCTION: GAMEMD 0x472DE0
// VectorClass<CaptureManagerClass*>::SetCapacity
// FUNCTION: GAMEMD 0x472E90
// VectorClass<CaptureManagerClass*>::Clear
// FUNCTION: GAMEMD 0x472EC0
// VectorClass<CaptureManagerClass*>::FindItemIndex
// FUNCTION: GAMEMD 0x472F00
// VectorClass<CaptureManagerClass*>::Slot5
// FUNCTION: GAMEMD 0x472F20
// DynamicVectorClass<CaptureManagerClass*>::SetCapacity
// FUNCTION: GAMEMD 0x472FD0
// DynamicVectorClass<CaptureManagerClass*>::FindItemIndex
// SYNTHETIC: GAMEMD 0x4730A0
// VectorClass<CaptureManagerClass*>::scalar deleting destructor
// SYNTHETIC: GAMEMD 0x4730F0
// DynamicVectorClass<CaptureManagerClass*>::scalar deleting destructor

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x473140
VectorCtor* VectorCtor::FUN_00473140(int size, void** array)
{
    Vector = 0;
    Length = size;
    IsValid = 1;
    IsAllocated = 0;

    *(char**)this = VT_007E4BC4;

    if (size != 0) {
        if (array != 0) {
            Vector = array;
        } else {
            Vector = (void**)FUN_007C8E17(size * 4);
            IsAllocated = 1;
        }
    }

    return this;
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x7E4AC0
extern const double DAT_007E4AC0 = 60.0;
// END defined globals
