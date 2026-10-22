// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//
// World Domination Tour conflict helpers and the rc_ptr<GameOption> vector
// instantiations (retail 0x765F60-0x767080). The vector bodies are the
// canonical VectorClass/DynamicVectorClass templates over rc_ptr<GameOption>,
// whose RTTI names the two vtables 0x7F6FF4 and 0x7F6FD4.
#include "world_domination_tour.h"
#include "../core/vector_class_operations.h"

// Byte readers whose addresses 0x7660F0 passes on; the object type is not
// identified.
struct Obj_007667E0
{
    char unknown_00[0x0E];      // +0x00
    unsigned char unknown_0E;   // +0x0E
    unsigned char unknown_0F;   // +0x0F
};

using WorldDominationTour::Conflict;

// FUNCTION: GAMEMD 0x765F60
// Wraps a new Conflict over the territory; the result is the hidden first
// argument.
rc_ptr<Conflict> __fastcall FUN_00765F60(const rc_ptr<WDTTerritory>& territory)
{
    return rc_ptr<Conflict>(new Conflict(territory));
}

// FUNCTION: GAMEMD 0x766010
bool Conflict::operator==(const Conflict& other) const
{
    return Territory == other.Territory;
}

// FUNCTION: GAMEMD 0x766060
int Conflict::FUN_00766060() const
{
    WDTTerritory* territory = Territory.Get();
    if (territory != 0)
        return territory->unknown_08;
    return 0;
}

// FUNCTION: GAMEMD 0x7667E0
int __fastcall FUN_007667E0(const Obj_007667E0* object)
{
    return object->unknown_0E;
}

// FUNCTION: GAMEMD 0x7667F0
int __fastcall FUN_007667F0(const Obj_007667E0* object)
{
    return object->unknown_0F;
}

typedef rc_ptr<WorldDominationTour::GameOption> GameOptionPtr;

// FUNCTION: GAMEMD 0x766850
// VectorClass<rc_ptr<GameOption> >::Slot6
// FUNCTION: GAMEMD 0x766BC0
// VectorClass<rc_ptr<GameOption> >::operator==
// FUNCTION: GAMEMD 0x766C10
// VectorClass<rc_ptr<GameOption> >::SetCapacity
// FUNCTION: GAMEMD 0x766D60
// VectorClass<rc_ptr<GameOption> >::FindItemIndex
template class VectorClass<GameOptionPtr>;
// FUNCTION: GAMEMD 0x766A80
// ValueGameOption<unsigned char>::vf_0C
template class WorldDominationTour::ValueGameOption<unsigned char>;
// FUNCTION: GAMEMD 0x766DC0
// DynamicVectorClass<rc_ptr<GameOption> >::SetCapacity
// FUNCTION: GAMEMD 0x766EE0
// DynamicVectorClass<rc_ptr<GameOption> >::AddItem
// FUNCTION: GAMEMD 0x766F40
// DynamicVectorClass<rc_ptr<GameOption> >::FindItemIndex
template class DynamicVectorClass<GameOptionPtr>;
// FUNCTION: GAMEMD 0x766F70
// rc_ptr<GameOption> copy constructor
// FUNCTION: GAMEMD 0x767010
// rc_ptr<GameOption> vector deleting destructor
template class rc_ptr<WorldDominationTour::GameOption>;
