// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Original translation unit TU241 of retail gamemd.exe v1.001; its source-file name is
//   not attested by the binary, so the file keeps a placeholder name. Code range 0x71a1c0-0x71b59f,
//   segmented from retail evidence (link-ordered static-initialiser table, RTTI class
//   ownership, neighbouring object bounds). Functions are in ascending retail address order.
//
// Retail PAVTemporalClass RTTI establishes the pointer element type and zero-offset
// DynamicVectorClass -> VectorClass base chain. Complete entry-origin spans
// establish the bound methods. GX emits a short derived deleting wrapper;
// no GX reproduces its full retail body. No TypeList or constructor is bound;
// original TU boundaries, final link and complete object sizes are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
//
//   cross-checked against an outside reference.
//
//   an outside reference.
//
// File-scope DynamicVectorClass<T> objects whose exit-time destructors were
// emitted as stand-alone stubs: each stub restores the VectorClass<T> vtable,
// frees the array when it is owned, and clears the flag and capacity. T is the
// element type of the vector's RTTI TypeDescriptor, read through the vptr stored by the
// matching initialiser. The initialisers (the __xc table entries, which also
// register these stubs with atexit) are left to the translation-unit migration;
// they compile here as a by-product and are not claimed. The globals' retail
// addresses are bound for verification through the per-TU symbol map.

#include "../core/vector_class_operations.h"

class TemporalClass;

// VTABLE: GAMEMD 0x7F5134 -- VectorClass<TemporalClass*>.
template class VectorClass<TemporalClass*>;
typedef VectorClass<TemporalClass*> GgTemporalClassVectorClass;
GG_STATIC_ASSERT(offsetof(GgTemporalClassVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgTemporalClassVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgTemporalClassVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgTemporalClassVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7F5114 -- DynamicVectorClass<TemporalClass*>.
template class DynamicVectorClass<TemporalClass*>;
typedef DynamicVectorClass<TemporalClass*> GgTemporalClassDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgTemporalClassDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgTemporalClassDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgTemporalClassDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgTemporalClassDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgTemporalClassDynamicVectorClass, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgTemporalClassDynamicVectorClass, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(TemporalClass*) == 4);

#include "../_layout/temporal_class.h"

#include "temporal_class_let_go_methods.h"

#include "temporal_class_warp_target_methods.h"

#include "../core/vector_class_operations.h"

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

// GLOBAL: GAMEMD 0x00B0EC60

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// SYNTHETIC: GAMEMD 0x0071A410 -- exit-time destructor stub of DAT_00B0EC60
DynamicVectorClass<TemporalClass*> DAT_00B0EC60;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x71AB10  (__thiscall)
// Accumulate this temporal's warp-per-step plus that of every helper temporal
// chained through unknown_44 (capped at 50 helpers deep), and cache the local
// value in WarpPerStep.
int TemporalClass::GetWarpPerStep(int nHelperCount) const
{
    int helper = 0;
    if (unknown_44) {
        if (nHelperCount <= 50)
            helper = unknown_44->GetWarpPerStep(nHelperCount + 1);
    }

    int amount = Owner->vf_3F8(Owner->vf_2E4(0))->Type->unknown_A4;
    unknown_4C = amount;
    return amount + helper;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x71ABC0  TemporalClass::LetGo
//
// Release the warp target. A temporal at the head of a chain hands the
// target (and its accumulated warp) to the next in line; the last one lets
// the target go for real: its back-link and warping flag clear, a building
// makes its house recount power and its tech tree, and the target is
// re-marked. A temporal in the middle or at the tail just unlinks itself.
// Every path ends by clearing the five link/target fields; each branch
// carries its own copy of that tail, as retail does.
//
// PARTIAL (85.5%, 71/83; mnemonic multiset identical). Retail keeps the
// previous link in EAX and the next one in ECX; VC6 assigns them the other
// way round, and every use of the two follows. Declaration order, testing
// the members instead of the locals, and dropping either local in favour of
// member re-reads (64.3% for prev-only) do not flip it — the same
// two-local naming tie-break as 0x4E15A0.
//
// TAIL-MERGE DIAGNOSTIC (eleventh-batch lever): does NOT apply here.
// Retail's callee-saved pushes sit exactly where ours do (prologue EBX, ESI on
// both sides), the
// number of epilogues agrees, and the compiled block order already matches,
// so there are no merged return blocks to split. The residual is register
// naming downstream of that, not a prologue hoist.
void Temporal_0071ABC0::LetGo()
{
    Temporal_0071ABC0* next = NextTemporal;
    Temporal_0071ABC0* prev = PrevTemporal;

    if (prev == 0) {
        Techno_0071ABC0* target = Target;
        if (next != 0) {
            if (target != 0)
                target->TemporalTargetingMe = next;
            NextTemporal->PrevTemporal = 0;
            NextTemporal->At_48 = At_48;
            Target = 0;
            NextTemporal = 0;
            PrevTemporal = 0;
            At_3C = 0;
            At_38 = 0;
            return;
        }
        if (target != 0) {
            target->TemporalTargetingMe = 0;
            Target->BeingWarpedOut = 0;
            if ((Target->*Target->Vptr->WhatAmI)() == 6) {
                Techno_0071ABC0* building = Target;
                building->Owner->PowerBlackoutWasActivated = 1;
                building->FUN_00452210();
                building->Owner->RecheckTechTree = 1;
            }
            (Target->*Target->Vptr->Mark)(2);
            Target = 0;
            NextTemporal = 0;
            PrevTemporal = 0;
            At_3C = 0;
            At_38 = 0;
            return;
        }
    } else if (next != 0) {
        next->PrevTemporal = prev;
        if (PrevTemporal != 0) {
            PrevTemporal->NextTemporal = NextTemporal;
            Target = 0;
            NextTemporal = 0;
            PrevTemporal = 0;
            At_3C = 0;
            At_38 = 0;
            return;
        }
    } else {
        prev->NextTemporal = 0;
    }

    Target = 0;
    NextTemporal = 0;
    PrevTemporal = 0;
    At_3C = 0;
    At_38 = 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x71AD40  (__thiscall)
// Release the target and unlink from both helper neighbours without notifying
// the owner (the lighter sibling of Detach).
void TemporalClass::JustLetGo()
{
    if (Target) {
        Target->unknown_270 = 0;
        Target->unknown_278 = 0;
        Target = 0;
    }

    if (unknown_44) {
        if (unknown_44->unknown_40 == this)
            unknown_44->unknown_40 = 0;
        unknown_44->Detach();
        unknown_44 = 0;
    }

    if (unknown_40) {
        if (unknown_40->unknown_44 == this)
            unknown_40->unknown_44 = 0;
        unknown_40->Detach();
        unknown_40 = 0;
    }

    unknown_44 = 0;
    unknown_40 = 0;
    unknown_3C = 0;
    unknown_38 = 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x71ADE0  (__thiscall)
// Detach this temporal: clear the (assumed non-null) target's impact flags,
// recursively detach both helper neighbours, then notify the owner.
void TemporalClass::Detach()
{
    Target->unknown_270 = 0;
    Target->unknown_278 = 0;
    Target = 0;

    if (unknown_44) {
        if (unknown_44->unknown_40 == this)
            unknown_44->unknown_40 = 0;
        unknown_44->Detach();
    }

    if (unknown_40) {
        if (unknown_40->unknown_44 == this)
            unknown_40->unknown_44 = 0;
        unknown_40->Detach();
    }

    unknown_44 = 0;
    unknown_40 = 0;
    unknown_3C = 0;
    unknown_38 = 0;

    if (Owner)
        Owner->vf_484(0, 1);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x71AE50
//
// Whether a techno may be temporal-warped. No target, a type without the
// +0xD3A flag, or a positive +0x160 virtual all refuse. A unit (WhatAmI == 1)
// whose first radio link is a building (WhatAmI == 6) of a type flagged at
// +0x16BD is refused when that building is the one standing on the unit's
// own cell — i.e. the unit is garrisoned inside it. Everything else warps.
bool TemporalClass_0071AE50::CanWarpTarget(Techno_0071AE50* target)
{
    if (target == 0)
        return false;

    if (!(target->*target->Vtbl->GetTechnoType)()->At_D3A)
        return false;

    if ((target->*target->Vtbl->At_160)())
        return false;

    if ((target->*target->Vtbl->WhatAmI)() == 1) {
        Techno_0071AE50* link = target->FUN_0065AD30(0);
        if (link != 0
            && (link->*link->Vtbl->WhatAmI)() == 6
            && link->Type->At_16BD)
        {
            CoordStruct_0071AE50 crd = target->Location;
            if (MapInstance_0071AE50->GetTargetCell(crd)->GetBuilding() == link)
                return false;
        }
    }

    return true;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x71B240
// DynamicVectorClass<TemporalClass*>::Clear

// FUNCTION: GAMEMD 0x71B270
// DynamicVectorClass<TemporalClass*>::Slot5

// FUNCTION: GAMEMD 0x71B290
// VectorClass<TemporalClass*>::Slot6

// FUNCTION: GAMEMD 0x71B2A0
// VectorClass<TemporalClass*>::operator==

// FUNCTION: GAMEMD 0x71B2E0
// VectorClass<TemporalClass*>::SetCapacity

// FUNCTION: GAMEMD 0x71B390
// VectorClass<TemporalClass*>::Clear

// FUNCTION: GAMEMD 0x71B3C0
// VectorClass<TemporalClass*>::FindItemIndex

// FUNCTION: GAMEMD 0x71B400
// VectorClass<TemporalClass*>::Slot5

// FUNCTION: GAMEMD 0x71B420
// DynamicVectorClass<TemporalClass*>::SetCapacity

// FUNCTION: GAMEMD 0x71B4D0
// DynamicVectorClass<TemporalClass*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x71B500
// VectorClass<TemporalClass*>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x71B550
// DynamicVectorClass<TemporalClass*>::scalar deleting destructor
