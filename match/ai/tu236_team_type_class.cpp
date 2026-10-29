// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Original translation unit TU236 of retail gamemd.exe v1.001; its source-file name is
//   not attested by the binary, so the file keeps a placeholder name. Code range 0x6f0470-0x6f289f,
//   segmented from retail evidence (link-ordered static-initialiser table, RTTI class
//   ownership, neighbouring object bounds). Functions are in ascending retail address order.
//   Obj_/Gbl_ views below are per-function placeholder receivers. Replacing
//   them with the canonical class re-mangles their symbols, so that is left to
//   a separate rename-only change.
//
// Retail RTTI names VectorClass/DynamicVectorClass over ZoneConnectionClass, WaypointClass and
// DiscreteDistributionClass<T>::DistributionObject<T*>. WaypointClass and the distribution objects have
// element destructors, so their ctor/Clear/SetCapacity bodies (array-delete paths) are not claimed here.
//
//   0x6F2070 (Ghidra disasm).  Structure cross-checked against an outside reference
//   (each offset,
//   global and call target reconfirmed against the user's binary).
//
// Translation unit: TeamTypeClass house/taskforce/instance helpers.
//   GLOBAL:   GAMEMD 0xA8ECA0   TeamTypeClass::Array
//   GLOBAL:   GAMEMD 0x8B40E8   TeamClass::Array
//   CALLEE:   GAMEMD 0x6F1FA0   TeamTypeClass::ProcessTaskForce
//   CALLEE:   GAMEMD 0x510F60   FUN_00510F60 / 0x510ED0 FindHouseByCountryIndex

#include "../core/vector_class_operations.h"
#include "../core/zone_connection_class.h"

// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.



// VTABLE: GAMEMD 0x007ED4E0 -- VectorClass<ZoneConnectionClass>.
template class VectorClass<ZoneConnectionClass>;
template class DynamicVectorClass<ZoneConnectionClass>;

#include "../_layout/waypoint_class.h"

// VTABLE: GAMEMD 0x007F6EF4 -- VectorClass<WaypointClass>.
template class VectorClass<WaypointClass>;
template class DynamicVectorClass<WaypointClass>;

class CellClass; template<class C> struct DiscreteDistributionClass { template<class P> struct DistributionObject { P Object; int Weight; DistributionObject() : Weight(0) {} ~DistributionObject() {} DistributionObject(const DistributionObject<P>& o) : Object(o.Object), Weight(o.Weight) {} bool operator==(const DistributionObject<P>& o) const { return Object==o.Object && Weight==o.Weight; } bool operator!=(const DistributionObject<P>& o) const { return !(*this==o); } }; };

template class DynamicVectorClass<DiscreteDistributionClass<CellClass>::DistributionObject<CellClass*> >;

class BuildingTypeClass; 
template class DynamicVectorClass<DiscreteDistributionClass<BuildingTypeClass>::DistributionObject<BuildingTypeClass*> >;

class AITriggerTypeClass; 

template class DynamicVectorClass<DiscreteDistributionClass<AITriggerTypeClass>::DistributionObject<AITriggerTypeClass*> >;

//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_006F20A0;
struct Obj_006F20B0;
struct Obj_006F20C0;

struct Obj_006F20A0
{
    // FUNCTION: GAMEMD 0x6F20A0
    int FUN_006F20A0() const;
};

struct Obj_006F20B0
{
    // FUNCTION: GAMEMD 0x6F20B0
    int FUN_006F20B0() const;
};

struct Obj_006F20C0
{
    char unknown_00[0x98];
    int unknown_98;   // +0x0098
    // FUNCTION: GAMEMD 0x6F20C0
    int FUN_006F20C0() const;
};
GG_STATIC_ASSERT(offsetof(Obj_006F20C0, unknown_98) == 0x98);


void __cdecl FUN_006F25D0();


#include "team_type_class_house_methods.h"

// Globals read by this TU's static initialisers (placeholder names).
// GLOBAL: GAMEMD 0x7E1718
extern const double DAT_007E1718;
// GLOBAL: GAMEMD 0x7F4790
extern const double DAT_007F4790;
// GLOBAL: GAMEMD 0xB0E9D0
extern double DAT_00B0E9D0;

// GLOBAL: GAMEMD 0x00B0EA20
extern double DAT_00B0EA20;

// GLOBAL: GAMEMD 0x00B0EA08
extern double DAT_00B0EA08;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// ---------------------------------------------------------------------------
// FUNCTION: GAMEMD 0x6F0A70  TeamTypeClass::DestroyAllInstances (__thiscall)
//
// Remove every live TeamClass spawned from this TeamTypeClass.  Walks the global
// TeamClass::Array; each team whose Type == this is removed (vtable+0x20, flag 1)
// and the index stepped back so the shifted array slot is re-examined.  Count is
// re-read from the global each pass because the remove call mutates the array.
// ---------------------------------------------------------------------------
void TeamTypeClass::DestroyAllInstances()
{
    for (int i = 0; i < TeamInstanceArray.Count; i++) {
        TeamClass* team = ((TeamClass**)TeamInstanceArray.Items)[i];
        if (this == team->Type) {
            if (team) {
                delete team;
            }
            i--;
        }
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// ---------------------------------------------------------------------------
// FUNCTION: GAMEMD 0x6F2040  TeamTypeClass::ProcessAllTaskforces (static)
//
// Run one taskforce-processing tick for every TeamTypeClass in the global type
// array.  The per-element call prevents the compiler from hoisting Items/Count,
// so both are re-read from the global on each iteration.
// ---------------------------------------------------------------------------
void TeamTypeClass::ProcessAllTaskforces()
{
    for (int i = 0; i < TeamTypeArray.Count; i++) {
        ((TeamTypeClass**)TeamTypeArray.Items)[i]->ProcessTaskForce();
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// ---------------------------------------------------------------------------
// FUNCTION: GAMEMD 0x6F2070  TeamTypeClass::GetHouse (__thiscall)
//
// Resolve the team's owning house.  A cached Owner pointer is returned verbatim;
// otherwise the team's country index is validated and mapped to a HouseClass*
// (returning null when the index names no real country).
// ---------------------------------------------------------------------------
HouseClass* TeamTypeClass::GetHouse() const
{
    if (this->Owner) {
        return this->Owner;
    }
    if (FUN_00510F60(this->idxHouse)) {
        return FindHouseByCountryIndex(this->idxHouse);
    }
    return 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6F20A0
// Returns a constant. Vtable slot 11 of TeamTypeClass (RTTI).
int Obj_006F20A0::FUN_006F20A0() const
{
    return 0x23;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6F20B0
// Returns a constant. Vtable slot 12 of TeamTypeClass (RTTI).
int Obj_006F20B0::FUN_006F20B0() const
{
    return 0xF8;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6F20C0
// Member getter (dword). Vtable slot 16 of TeamTypeClass (RTTI).
int Obj_006F20C0::FUN_006F20C0() const
{
    return unknown_98;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x006F2290
// VectorClass<DiscreteDistributionClass<AITriggerTypeClass>::DistributionObject<AITriggerTypeClass*>>::operator==
// FUNCTION: GAMEMD 0x006F2440
// VectorClass<DiscreteDistributionClass<AITriggerTypeClass>::DistributionObject<AITriggerTypeClass*>>::FindItemIndex
// FUNCTION: GAMEMD 0x006F2490
// VectorClass<DiscreteDistributionClass<AITriggerTypeClass>::DistributionObject<AITriggerTypeClass*>>::Slot5
// FUNCTION: GAMEMD 0x006F2210
// VectorClass<DiscreteDistributionClass<AITriggerTypeClass>::DistributionObject<AITriggerTypeClass*>>::Slot6
// FUNCTION: GAMEMD 0x006F2640
// DynamicVectorClass<DiscreteDistributionClass<AITriggerTypeClass>::DistributionObject<AITriggerTypeClass*>>::FindItemIndex
// FUNCTION: GAMEMD 0x006F21F0
// DynamicVectorClass<DiscreteDistributionClass<AITriggerTypeClass>::DistributionObject<AITriggerTypeClass*>>::Slot5
// FUNCTION: GAMEMD 0x006F22F0
// VectorClass<DiscreteDistributionClass<AITriggerTypeClass>::DistributionObject<AITriggerTypeClass*>>::SetCapacity
// FUNCTION: GAMEMD 0x006F25E0
// DynamicVectorClass<DiscreteDistributionClass<AITriggerTypeClass>::DistributionObject<AITriggerTypeClass*>>::AddItem
template class VectorClass<DiscreteDistributionClass<AITriggerTypeClass>::DistributionObject<AITriggerTypeClass*> >;
// SYNTHETIC: GAMEMD 0x6F26E0 -- compiler-generated vector deleting destructor of DiscreteDistributionClass<AITriggerTypeClass>::DistributionObject<AITriggerTypeClass*>.

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6F25D0
// Empty function.
void __cdecl FUN_006F25D0()
{
}
