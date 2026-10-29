// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT /Ob2
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

namespace WorldDominationTour { class Campaign; }

using WorldDominationTour::Conflict;

typedef rc_ptr<Conflict> ConflictPtr;

// FUNCTION: GAMEMD 0x764F30
// Releases the +0x48 string, the conflict list, then the history and
// properties handles, and the ReferenceCounted destructor.
WorldDominationTour::Campaign::~Campaign()
{
}

// SYNTHETIC: GAMEMD 0x765600 -- WorldDominationTour::Campaign::`scalar deleting destructor'

// FUNCTION: GAMEMD 0x7656B0
// DynamicVectorClass<rc_ptr<Conflict> >::Slot5
// FUNCTION: GAMEMD 0x7656D0
// VectorClass<rc_ptr<Conflict> >::Slot6
// FUNCTION: GAMEMD 0x7657F0
// VectorClass<rc_ptr<Conflict> >::operator==
// FUNCTION: GAMEMD 0x765990
// VectorClass<rc_ptr<Conflict> >::FindItemIndex
// FUNCTION: GAMEMD 0x7659D0
// VectorClass<rc_ptr<Conflict> >::Slot5
// FUNCTION: GAMEMD 0x765B10
// DynamicVectorClass<rc_ptr<Conflict> >::FindItemIndex
// FUNCTION: GAMEMD 0x765BB0
// rc_ptr<Conflict>: the deleting destructor the compiler emits for it.
// FUNCTION: GAMEMD 0x765C70
// rc_ptr<Conflict>: default constructor (base constructor, then the derived vtable seat).
// SYNTHETIC: GAMEMD 0x765710 -- rc_ptr<CampaignProperties>::`scalar deleting destructor'
// SYNTHETIC: GAMEMD 0x765740 -- rc_ptr<History>::`scalar deleting destructor'
// SYNTHETIC: GAMEMD 0x765790 -- rc_ptr<Campaign>::`scalar deleting destructor'
// SYNTHETIC: GAMEMD 0x7657C0 -- rc_ptr<State>::`scalar deleting destructor'
// SYNTHETIC: GAMEMD 0x766930 -- rc_ptr<Conflict>::`scalar deleting destructor'
// SYNTHETIC: GAMEMD 0x766960 -- rc_ptr<ValueGameOption<unsigned char>>::`scalar deleting destructor'
// SYNTHETIC: GAMEMD 0x766990 -- rc_ptr<FlagGameOption>::`scalar deleting destructor'
// SYNTHETIC: GAMEMD 0x7669C0 -- rc_ptr<MapSizeGameOption>::`scalar deleting destructor'
// FUNCTION: GAMEMD 0x7668F0
// rc_ptr<GameOption>: destructor (stores the vtable, tail-calls the base destructor).
// FUNCTION: GAMEMD 0x766900
// rc_ptr<FlagGameOption>: destructor.
// FUNCTION: GAMEMD 0x766910
// rc_ptr<MapSizeGameOption>: destructor.
// FUNCTION: GAMEMD 0x765C90
// VectorClass<rc_ptr<Conflict> >::VectorClass
template class VectorClass<ConflictPtr>;
template class DynamicVectorClass<ConflictPtr>;
template class rc_ptr<Conflict>;
template class rc_ptr<WorldDominationTour::CampaignProperties>;
template class rc_ptr<WorldDominationTour::History>;
template class rc_ptr<WorldDominationTour::Campaign>;
template class rc_ptr<WorldDominationTour::State>;
template class rc_ptr<WorldDominationTour::ValueGameOption<unsigned char> >;
template class rc_ptr<WorldDominationTour::FlagGameOption>;
template class rc_ptr<WorldDominationTour::MapSizeGameOption>;

// FUNCTION: GAMEMD 0x766030
// Seats the Conflict table, then the territory handle and the
// ReferenceCounted destructor.
Conflict::~Conflict()
{
}

// FUNCTION: GAMEMD 0x765F60
// Wraps a new Conflict over the territory; the result is the hidden first
// argument.
rc_ptr<Conflict> FUN_00765F60(const rc_ptr<WDTTerritory>& territory)
{
    return rc_ptr<Conflict>(new Conflict(territory));
}

// FUNCTION: GAMEMD 0x765FD0
// The constructor: expanded into the factory above (/Ob2) and also kept out of line.
Conflict::Conflict(const rc_ptr<WDTTerritory>& territory)
    : Territory(territory)
{
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
int FUN_007667E0(const Obj_007667E0* object)
{
    return object->unknown_0E;
}

// FUNCTION: GAMEMD 0x7667F0
int FUN_007667F0(const Obj_007667E0* object)
{
    return object->unknown_0F;
}

typedef rc_ptr<WorldDominationTour::GameOption> GameOptionPtr;

// FUNCTION: GAMEMD 0x766830
// DynamicVectorClass<rc_ptr<GameOption> >::Slot5
// FUNCTION: GAMEMD 0x766850
// VectorClass<rc_ptr<GameOption> >::Slot6
// FUNCTION: GAMEMD 0x766BC0
// VectorClass<rc_ptr<GameOption> >::operator==
// FUNCTION: GAMEMD 0x766C10
// VectorClass<rc_ptr<GameOption> >::SetCapacity
// FUNCTION: GAMEMD 0x766D60
// VectorClass<rc_ptr<GameOption> >::FindItemIndex
// FUNCTION: GAMEMD 0x766DA0
// VectorClass<rc_ptr<GameOption> >::Slot5
template class VectorClass<GameOptionPtr>;
// FUNCTION: GAMEMD 0x766A10
// ValueGameOption<unsigned char>::ValueGameOption
// SYNTHETIC: GAMEMD 0x766A60
// GameOption scalar deleting destructor (the destructor stays out of line here).
// FUNCTION: GAMEMD 0x766A80
// ValueGameOption<unsigned char>::vf_0C
// SYNTHETIC: GAMEMD 0x766B90
// ValueGameOption<unsigned char> scalar deleting destructor
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
// FUNCTION: GAMEMD 0x7670D0
// rc_ptr<GameOption>: default constructor.
template class rc_ptr<WorldDominationTour::GameOption>;

// SYNTHETIC: GAMEMD 0x7667A0
// Conflict scalar deleting destructor, the destructor body inlined.

// FUNCTION: GAMEMD 0x766880
// The ValueGameOption<unsigned char> factory: a new option over the values, returned in a handle (hidden
// result pointer in ECX, the flags in EDX).
rc_ptr<WorldDominationTour::ValueGameOption<unsigned char> > FUN_00766880(
    unsigned int flags, int when_set, Member_7B46F0 name, int when_clear)
{
    return rc_ptr<WorldDominationTour::ValueGameOption<unsigned char> >(
        new WorldDominationTour::ValueGameOption<unsigned char>(flags, when_set, name, when_clear));
}
