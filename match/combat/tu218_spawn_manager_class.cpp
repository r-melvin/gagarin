// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Original translation unit TU218 of retail gamemd.exe v1.001; its source-file name is
//   not attested by the binary, so the file keeps a placeholder name. Code range 0x6b6a00-0x6b88ef,
//   segmented from retail evidence (link-ordered static-initialiser table, RTTI class
//   ownership, neighbouring object bounds). Functions are in ascending retail address order.
//   Obj_/Gbl_ views below are per-function placeholder receivers. Replacing
//   them with the canonical class re-mangles their symbols, so that is left to
//   a separate rename-only change.
//
// Retail RTTI type descriptors name VectorClass<SpawnManagerClass*> and
// DynamicVectorClass<SpawnManagerClass*>; each address below is the vtable slot body
// of that specialization (slot owner read from the retail vtables).
// Pointer/scalar/enum element: no element layout is claimed.
//
// Retail RTTI type descriptors name VectorClass<SpawnManagerClass::SpawnControl*> and
// DynamicVectorClass<SpawnManagerClass::SpawnControl*>; each address below is the vtable slot body
// of that specialization (slot owner read from the retail vtables).
// Pointer/scalar/enum element: no element layout is claimed.
//
// The remaining address-scoped scalar deleting destructors of the 30-byte family,
// by retail address. Each runs its class's real destructor, then frees the
// object when bit 0 of the flag argument is set, and returns `this`.
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
// 10 remaining four-byte-element resize bodies retain address-scoped
// views until their actual template classes are integrated. Recovered entries
// are bound in their native specialization implementations.
// Entry-origin spans are 0xB0 bytes. Instructions confirm Items+4, Capacity+8,
// initialization flag+C, ownership flag+D, live count+10 and Clear slot+C.
// Original source ownership and TU grouping are not established by this sweep.
//
// The source keeps the base resize as an inline call and clamps the count only
// on success. The capacity-zero branch dispatches Clear; allocation failure
// returns false. The ownership expression retains the verified short-circuit
// term so VC6 schedules SETZ and the pointer/capacity stores as retail does.
// These views remain verified under the default flags (/O2 /Gr /DNDEBUG /Gy, no /GX).

#include "../core/vector_class_operations.h"

class SpawnManagerClass;

template class DynamicVectorClass<SpawnManagerClass*>;

GG_STATIC_ASSERT(sizeof(SpawnManagerClass*) == 4);
GG_STATIC_ASSERT(sizeof(VectorClass<SpawnManagerClass* >) == 0x10);
GG_STATIC_ASSERT(sizeof(DynamicVectorClass<SpawnManagerClass* >) == 0x18);

#include "../core/vector_class_operations.h"

class SpawnManagerClass {
public:
    struct SpawnControl;
};

template class DynamicVectorClass<SpawnManagerClass::SpawnControl*>;

GG_STATIC_ASSERT(sizeof(SpawnManagerClass::SpawnControl*) == 4);
GG_STATIC_ASSERT(sizeof(VectorClass<SpawnManagerClass::SpawnControl* >) == 0x10);
GG_STATIC_ASSERT(sizeof(DynamicVectorClass<SpawnManagerClass::SpawnControl* >) == 0x18);

//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_006B7C40;
struct Obj_006B8120;
struct Obj_006B8130;

struct Obj_006B7C40
{
    char unknown_00[0x68];
    int unknown_68;   // +0x0068
    int unknown_6C;   // +0x006C
    // FUNCTION: GAMEMD 0x6B7C40
    unsigned char FUN_006B7C40();
};
GG_STATIC_ASSERT(offsetof(Obj_006B7C40, unknown_68) == 0x68);
GG_STATIC_ASSERT(offsetof(Obj_006B7C40, unknown_6C) == 0x6C);

struct Obj_006B8120
{
    // FUNCTION: GAMEMD 0x6B8120
    int FUN_006B8120() const;
};

struct Obj_006B8130
{
    // FUNCTION: GAMEMD 0x6B8130
    int FUN_006B8130() const;
};




#include "spawn_manager_class_reset_methods.h"

#include "../core/deleting_dtor_sweep.h"
#include "../network/transport/winsock_interface_class.h"
#include "../_layout/pipe.h"
#include "../_layout/straw.h"

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

// GLOBAL: GAMEMD 0x0087F658

#include "../core/vector_resize_family_methods.h"

// Globals read by this TU's static initialisers (placeholder names).
// GLOBAL: GAMEMD 0x7E1718
extern const double DAT_007E1718;
// GLOBAL: GAMEMD 0x7F35D0
extern const double DAT_007F35D0;
// GLOBAL: GAMEMD 0xB0B828
extern double DAT_00B0B828;

// SYNTHETIC: GAMEMD 0x6B6A30
// GLOBAL: GAMEMD 0xB0B878
double DAT_00B0B878 = DAT_00B0B828 / DAT_007F35D0;

// SYNTHETIC: GAMEMD 0x6B6A50
// GLOBAL: GAMEMD 0xB0B860
double DAT_00B0B860 = DAT_007E1718 / DAT_00B0B878;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// SYNTHETIC: GAMEMD 0x006B6C50 -- exit-time destructor stub of DAT_00B0B880
DynamicVectorClass<SpawnManagerClass*> DAT_00B0B880;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6B7BB0
//
// Drop the current target. Every node in the recallable state whose unit's
// type carries the flag is handed to the kamikaze manager against the old
// target, the manager's timer is restarted at two frames, and the unit is
// unlinked from this manager. Then the target, pending target and status are
// all cleared.
void SpawnManager_006B7BB0::ResetTarget()
{
    for (int i = 0; i < Count; ++i) {
        SpawnControl_006B7BB0* node = Items[i];
        if (node->Status == 2 && node->Unit->Type->At_D68 != 0) {
            DAT_00ABC5F8.Add(node->Unit, Target);
            DAT_00ABC5F8.UpdateTimer = CDTimer_006B7BB0(2);
            UnlinkPointer((AbstractClass*)Items[i]->Unit);
        }
    }

    Status = 0;
    NewTarget = 0;
    Target = 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6B7C40
// Branching.
unsigned char Obj_006B7C40::FUN_006B7C40()
{
    if (unknown_6C != 0)
    {
        unknown_68 = unknown_6C;
        unknown_6C = 0;
        return 1;
    }
    return 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6B7C60
//
// Something is going away. If it was the target, drop it and, with no
// pending target either, fall back to ResetTarget; if it was the pending
// target, just forget it. Otherwise look for it among the spawned units,
// searching from the top: a unit that is still alive, not on a kamikaze run
// and whose node is not in the 1 state is left alone, any other is detached,
// marked dead and given a fresh respawn countdown. Finally, if it was the
// owner itself, every node is released and the target reset.
void SpawnManager_006B7BB0::UnlinkPointer(AbstractClass* remove)
{
    if (remove == Target) {
        Target = 0;
        if (NewTarget == 0)
            ResetTarget();
        return;
    }

    if (remove == NewTarget) {
        NewTarget = 0;
        return;
    }

    for (int i = Count - 1; i >= 0; --i) {
        if (remove == (AbstractClass*)Items[i]->Unit) {
            SpawnControl_006B7BB0* node = Items[i];
            SpawnUnit_006B7BB0* unit = node->Unit;
            if (unit->Health > 0 && unit->At_6CA == 0 && node->At_14 != 1)
                return;
            node->Unit = 0;
            Items[i]->Status = 7;
            Items[i]->Timer = CDTimer_006B7BB0(RegenRate);
            return;
        }
    }

    if (remove == Owner) {
        FUN_006B7100();
        ResetTarget();
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6B8120
// Returns a constant. Vtable slot 12 of SpawnManagerClass (RTTI).
int Obj_006B8120::FUN_006B8120() const
{
    return 0x74;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6B8130
// Returns a constant. Vtable slot 11 of SpawnManagerClass (RTTI).
int Obj_006B8130::FUN_006B8130() const
{
    return 0x41;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6B8140
void* Obj_6B8140::FUN_6B8140(unsigned int flags)
{
    FUN_006B7010(this);

    if (flags & 1) {
        FUN_007C8B3D(this);
    }

    return this;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x6B8190
// DynamicVectorClass<SpawnManagerClass::SpawnControl*>::Slot5 (slot 5)
// TEMPLATE: GAMEMD 0x6B81B0
// VectorClass<SpawnManagerClass::SpawnControl*>::Slot6 (slot 6)
// TEMPLATE: GAMEMD 0x6B8220
// VectorClass<SpawnManagerClass::SpawnControl*>::operator== (slot 1)
// TEMPLATE: GAMEMD 0x6B8260
// VectorClass<SpawnManagerClass::SpawnControl*>::SetCapacity (slot 2)
// TEMPLATE: GAMEMD 0x6B8340
// VectorClass<SpawnManagerClass::SpawnControl*>::FindItemIndex (slot 4)
// TEMPLATE: GAMEMD 0x6B8380
// VectorClass<SpawnManagerClass::SpawnControl*>::Slot5 (slot 5)
// TEMPLATE: GAMEMD 0x6B84B0
// DynamicVectorClass<SpawnManagerClass::SpawnControl*>::FindItemIndex (slot 4)
template class VectorClass<SpawnManagerClass::SpawnControl*>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x6B81F0
// DynamicVectorClass<SpawnManagerClass*>::Slot5 (slot 5)
// TEMPLATE: GAMEMD 0x6B8210
// VectorClass<SpawnManagerClass*>::Slot6 (slot 6)
// TEMPLATE: GAMEMD 0x6B84E0
// VectorClass<SpawnManagerClass*>::operator== (slot 1)
// TEMPLATE: GAMEMD 0x6B8520
// VectorClass<SpawnManagerClass*>::SetCapacity (slot 2)
// TEMPLATE: GAMEMD 0x6B8600
// VectorClass<SpawnManagerClass*>::FindItemIndex (slot 4)
// TEMPLATE: GAMEMD 0x6B8640
// VectorClass<SpawnManagerClass*>::Slot5 (slot 5)
// TEMPLATE: GAMEMD 0x6B8660
// DynamicVectorClass<SpawnManagerClass*>::SetCapacity (slot 2)
// TEMPLATE: GAMEMD 0x6B8710
// DynamicVectorClass<SpawnManagerClass*>::FindItemIndex (slot 4)
template class VectorClass<SpawnManagerClass*>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6B8400
bool VectorResizeFamily::FUN_6B8400(int newsize, void** array)
{
    if (ResizeBase(newsize, array)) {
        if (Length < Count) {
            Count = Length;
        }
        return true;
    }

    return false;
}
