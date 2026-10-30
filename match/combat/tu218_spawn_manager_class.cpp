// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Original translation unit TU218 of retail gamemd.exe v1.001; its source-file name is
//   not attested by the binary, so the file keeps a placeholder name. Code range 0x6b6a00-0x6b88ef,
//   segmented from retail evidence (link-ordered static-initialiser table, RTTI class
//   ownership, neighbouring object bounds). Functions are in ascending retail address order.
//   The SpawnManagerClass methods of this range (0x6b6fa0-0x6b8140) live here on the
//   canonical class (match/_layout/spawn_manager_class.h).
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
// VC6FLAGS: /nologo /c /O2 /Gr /GR /DNDEBUG /Gy /MT /Ob2
//   /Ob2: retail's __xc entries point straight at the initialiser bodies (no
//   out-of-line _$E thunk behind a jump).

#include "../core/vector_class_operations.h"

class SpawnManagerClass;

template class DynamicVectorClass<SpawnManagerClass*>;

GG_STATIC_ASSERT(sizeof(SpawnManagerClass*) == 4);
GG_STATIC_ASSERT(sizeof(VectorClass<SpawnManagerClass* >) == 0x10);
GG_STATIC_ASSERT(sizeof(DynamicVectorClass<SpawnManagerClass* >) == 0x18);

#include "../core/vector_class_operations.h"

#include "../_layout/spawn_manager_class.h"

template class DynamicVectorClass<SpawnManagerClass::SpawnControl*>;

GG_STATIC_ASSERT(sizeof(SpawnManagerClass::SpawnControl*) == 4);
GG_STATIC_ASSERT(sizeof(VectorClass<SpawnManagerClass::SpawnControl* >) == 0x10);
GG_STATIC_ASSERT(sizeof(DynamicVectorClass<SpawnManagerClass::SpawnControl* >) == 0x18);

//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.

#include <stddef.h>
#include "../_rt/gg_static_assert.h"


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

// The canonical class headers follow the static initialisers: VC6 numbers the _$E/_$S
// stubs in parse order and the type-list headers consume a number when seen earlier.
#include "../_layout/techno_class.h"
#include "../_layout/aircraft_class.h"
#include "../_layout/aircraft_type_class.h"
#include "../_layout/kamikaze_class.h"

// FUNCTION: GAMEMD 0x6B6FA0
// NoInit constructor (save-game load path): base NoInit constructor, an empty
// growable node vector (step 10), both timers started at the current frame
// with no time left, and the four COM vtable pointers.
SpawnManagerClass::SpawnManagerClass(const AbstractNoInit& noInit)
    : AbstractClass(noInit), SpawnedNodes(0, 0), SpawnTimer(0), UpdateTimer(0)
{
}


// FUNCTION: GAMEMD 0x6B7100
//
// Kill every spawned unit and put its node into the dead state with a fresh
// respawn countdown — immediate when the owner is still alive and flagged,
// otherwise the regen rate. Walking the nodes from the top: a node already
// dead is left alone; an idle or returning unit (0, 6) is simply taken off
// the map; a unit on a kamikaze run (1) is first withdrawn from the
// kamikaze manager; anything else is handed to the kamikaze manager against
// the current target instead of being removed.
void SpawnManagerClass::KillNodes()
{
    int duration;
    if (Owner->Health > 0 && Owner->IsAlive != 0) {
        duration = 0;
    } else {
        duration = unknown_30;
    }

    for (int i = SpawnedNodes.Count - 1; i >= 0; --i) {
        SpawnControl* node = SpawnedNodes.Items[i];
        int status = node->Status;
        if (status != 7) {
            if (status == 0 || status == 6) {
                node->Status = 7;
                SpawnedNodes.Items[i]->Unit->vf_62();
                SpawnedNodes.Items[i]->Unit = 0;
                SpawnedNodes.Items[i]->Timer = CDTimerClass(duration);
            } else if (status == 1) {
                DAT_00ABC5F8.Remove(node->Unit);
                SpawnedNodes.Items[i]->Status = 7;
                SpawnedNodes.Items[i]->Unit->vf_62();
                SpawnedNodes.Items[i]->Unit = 0;
                SpawnedNodes.Items[i]->Timer = CDTimerClass(duration);
            } else {
                node->Status = 7;
                DAT_00ABC5F8.Add(SpawnedNodes.Items[i]->Unit, Target);
                SpawnedNodes.Items[i]->Unit = 0;
                SpawnedNodes.Items[i]->Timer = CDTimerClass(duration);
            }
        }
    }
}

// FUNCTION: GAMEMD 0x6B7B90  (__thiscall)
// Record a pending target. If it already equals the live Target, do nothing;
// otherwise stash it in NewTarget for the next UpdateTarget pass.
void SpawnManagerClass::SetTarget(AbstractClass* pTarget)
{
    if (pTarget != Target)
        NewTarget = pTarget;
}


// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6B7BB0
//
// Drop the current target. Every node in the recallable state whose unit's
// type carries the flag is handed to the kamikaze manager against the old
// target, the manager's timer is restarted at two frames, and the unit is
// unlinked from this manager. Then the target, pending target and status are
// all cleared.
// Under /Ob2 cl would fold this body into its callers; retail keeps the call.
#pragma auto_inline(off)
void SpawnManagerClass::ResetTarget()
{
    for (int i = 0; i < SpawnedNodes.Count; ++i) {
        SpawnControl* node = SpawnedNodes.Items[i];
        if (node->Status == 2 && node->Unit->Type->MissileSpawn != 0) {
            DAT_00ABC5F8.Add(node->Unit, Target);
            DAT_00ABC5F8.UpdateTimer = CDTimerClass(2);
            UnlinkPointer(SpawnedNodes.Items[i]->Unit);
        }
    }

    unknown_70 = 0;
    NewTarget = 0;
    Target = 0;
}
#pragma auto_inline(on)

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6B7C40
// Branching.
unsigned char SpawnManagerClass::FUN_006B7C40()
{
    if (NewTarget != 0)
    {
        Target = NewTarget;
        NewTarget = 0;
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
void SpawnManagerClass::UnlinkPointer(AbstractClass* remove)
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

    for (int i = SpawnedNodes.Count - 1; i >= 0; --i) {
        if (remove == SpawnedNodes.Items[i]->Unit) {
            SpawnControl* node = SpawnedNodes.Items[i];
            AircraftClass* unit = node->Unit;
            if (unit->Health > 0 && unit->IsKamikaze == 0 && node->unknown_14 != 1)
                return;
            node->Unit = 0;
            SpawnedNodes.Items[i]->Status = 7;
            SpawnedNodes.Items[i]->Timer = CDTimerClass(unknown_30);
            return;
        }
    }

    if (remove == Owner) {
        KillNodes();
        ResetTarget();
    }
}

// FUNCTION: GAMEMD 0x6B7D30  (__thiscall)
// Count spawn nodes that are not Dead (Status != 7).
int SpawnManagerClass::CountAliveSpawns() const
{
    int count = 0;
    int n = SpawnedNodes.Count;
    if (n > 0) {
        SpawnManagerClass::SpawnControl** node = SpawnedNodes.Items;
        do {
            if ((*node)->Status != 7)
                ++count;
            ++node;
            --n;
        } while (n != 0);
    }
    return count;
}

// FUNCTION: GAMEMD 0x6B7D50  (__thiscall)
// Count docked spawn nodes: Reloading (Status == 6) or Idle (Status == 0).
int SpawnManagerClass::CountDockedSpawns() const
{
    int count = 0;
    int n = SpawnedNodes.Count;
    if (n > 0) {
        SpawnManagerClass::SpawnControl** node = SpawnedNodes.Items;
        do {
            int status = (*node)->Status;
            if (status == 6 || status == 0)
                ++count;
            ++node;
            --n;
        } while (n != 0);
    }
    return count;
}

// FUNCTION: GAMEMD 0x6B7D80  (__thiscall)
// Count spawn nodes that are mid-launch. A node counts when Status == 1
// (TakeOff); it also counts when Status == 2 (CoolDown) and its live Unit is
// not flagged at +0x81 and the unit's type (GetType, vtable +0x84) carries the
// launch flag at type +0xD68. Items / Count are re-read each pass (the virtual
// call may mutate the vector).
//
// MATCH: 38/38 exact (100.0%). Phrasing note: the two Status comparisons must
// read node->Status as independent memory expressions (NOT a single cached
// `int status` local). cl CSEs them back to one load (matching retail's single
// MOV ECX,[EAX+0x4]), but a cached local lets cl prove Status==1 and Status==2
// mutually exclusive and tail-merge both `++count` sites into one shared INC,
// which retail (build 8447) does not do. The two-read form keeps retail's
// fall-through structure (Status==1 INC falls into the CMP ECX,2 re-test).
int SpawnManagerClass::CountLaunchingSpawns() const
{
    int count = 0;
    for (int i = 0; i < SpawnedNodes.Count; ++i) {
        SpawnManagerClass::SpawnControl* node = SpawnedNodes.Items[i];
        if (node->Status == 1)
            ++count;
        if (node->Status == 2) {
            AircraftClass* unit = node->Unit;
            if (unit != 0 && unit->InLimbo == 0) {
                if (unit->vf_33()->MissileSpawn != 0)
                    ++count;
            }
        }
    }
    return count;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6B8120
// Returns a constant. Vtable slot 12 of SpawnManagerClass (RTTI).
int SpawnManagerClass::vf_12()
{
    return 0x74;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6B8130
// Returns a constant. Vtable slot 11 of SpawnManagerClass (RTTI).
int SpawnManagerClass::vf_11()
{
    return 0x41;
}

// SYNTHETIC: GAMEMD 0x6B8140 -- SpawnManagerClass scalar deleting destructor, emitted by the compiler from the
// virtual destructor where this TU seats the vtable.

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

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x7F35D0
extern const double DAT_007F35D0 = 60.0;
// END defined globals
