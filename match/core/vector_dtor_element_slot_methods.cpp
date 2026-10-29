// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Retail RTTI names VectorClass/DynamicVectorClass over ZoneConnectionClass, WaypointClass and
// DiscreteDistributionClass<T>::DistributionObject<T*>. WaypointClass and the distribution objects have
// element destructors, so their ctor/Clear/SetCapacity bodies (array-delete paths) are not claimed here.
#include "vector_class_operations.h"
#include "../_layout/waypoint_class.h"
#include "zone_connection_class.h"

// FUNCTION: GAMEMD 0x007640B0
// VectorClass<WaypointClass>::operator==
// FUNCTION: GAMEMD 0x00764110
// VectorClass<WaypointClass>::SetCapacity
// FUNCTION: GAMEMD 0x00764260
// VectorClass<WaypointClass>::FindItemIndex
// FUNCTION: GAMEMD 0x007642B0
// VectorClass<WaypointClass>::Slot5
// FUNCTION: GAMEMD 0x00763F60
// VectorClass<WaypointClass>::Slot6
// FUNCTION: GAMEMD 0x00764420
// DynamicVectorClass<WaypointClass>::FindItemIndex
// FUNCTION: GAMEMD 0x00763F30
// DynamicVectorClass<WaypointClass>::Slot5
// VTABLE: GAMEMD 0x007F6EF4 -- VectorClass<WaypointClass>.
// class VectorClass<WaypointClass>
template class VectorClass<WaypointClass>;
template class DynamicVectorClass<WaypointClass>;

// operator new(size_t) is supplied by the toolchain library.

// FUNCTION: GAMEMD 0x00589370
// VectorClass<ZoneConnectionClass>::SetCapacity
// FUNCTION: GAMEMD 0x005894D0
// VectorClass<ZoneConnectionClass>::FindItemIndex
// FUNCTION: GAMEMD 0x00589530
// VectorClass<ZoneConnectionClass>::Slot5
// VTABLE: GAMEMD 0x007ED4E0 -- VectorClass<ZoneConnectionClass>.
template class VectorClass<ZoneConnectionClass>;
template class DynamicVectorClass<ZoneConnectionClass>;

class CellClass; template<class C> struct DiscreteDistributionClass { template<class P> struct DistributionObject { P Object; int Weight; DistributionObject() : Weight(0) {} ~DistributionObject() {} DistributionObject(const DistributionObject<P>& o) : Object(o.Object), Weight(o.Weight) {} bool operator==(const DistributionObject<P>& o) const { return Object==o.Object && Weight==o.Weight; } bool operator!=(const DistributionObject<P>& o) const { return !(*this==o); } }; };
// FUNCTION: GAMEMD 0x004E07E0
// VectorClass<DiscreteDistributionClass<CellClass>::DistributionObject<CellClass*>>::operator==
// FUNCTION: GAMEMD 0x004E0990
// VectorClass<DiscreteDistributionClass<CellClass>::DistributionObject<CellClass*>>::FindItemIndex
// FUNCTION: GAMEMD 0x004E09E0
// VectorClass<DiscreteDistributionClass<CellClass>::DistributionObject<CellClass*>>::Slot5
// FUNCTION: GAMEMD 0x004E0250
// VectorClass<DiscreteDistributionClass<CellClass>::DistributionObject<CellClass*>>::Slot6
// FUNCTION: GAMEMD 0x004E0CA0
// DynamicVectorClass<DiscreteDistributionClass<CellClass>::DistributionObject<CellClass*>>::FindItemIndex
// FUNCTION: GAMEMD 0x004E0AF0
// DynamicVectorClass<DiscreteDistributionClass<CellClass>::DistributionObject<CellClass*>>::Slot5
// FUNCTION: GAMEMD 0x004E0840
// VectorClass<DiscreteDistributionClass<CellClass>::DistributionObject<CellClass*>>::SetCapacity
// FUNCTION: GAMEMD 0x004E0C40
// DynamicVectorClass<DiscreteDistributionClass<CellClass>::DistributionObject<CellClass*>>::AddItem
// FUNCTION: GAMEMD 0x004E0A00
// DynamicVectorClass<DiscreteDistributionClass<CellClass>::DistributionObject<CellClass*>>::DynamicVectorClass(int, T*)
template class VectorClass<DiscreteDistributionClass<CellClass>::DistributionObject<CellClass*> >;
template class DynamicVectorClass<DiscreteDistributionClass<CellClass>::DistributionObject<CellClass*> >;

class BuildingTypeClass; 
template class DynamicVectorClass<DiscreteDistributionClass<BuildingTypeClass>::DistributionObject<BuildingTypeClass*> >;

class AITriggerTypeClass; 
template class DynamicVectorClass<DiscreteDistributionClass<AITriggerTypeClass>::DistributionObject<AITriggerTypeClass*> >;

