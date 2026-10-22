// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy
// Retail RTTI names VectorClass/DynamicVectorClass over ZoneConnectionClass, WaypointClass and
// DiscreteDistributionClass<T>::DistributionObject<T*>. WaypointClass and the distribution objects have
// element destructors, so their ctor/Clear/SetCapacity bodies (array-delete paths) are not claimed here.
#include "vector_class_operations.h"

// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.

struct ZoneCell { short X; short Y; ZoneCell() : X(0), Y(0) {} bool operator==(const ZoneCell& o) const { return X==o.X && Y==o.Y; } bool operator!=(const ZoneCell& o) const { return !(*this==o); } }; struct ZoneConnectionClass { ZoneCell unknown_00; ZoneCell unknown_04; unsigned char unknown_08; int unknown_0C; ZoneConnectionClass() : unknown_08(0), unknown_0C(-1) {} ZoneConnectionClass(const ZoneConnectionClass& o) : unknown_00(o.unknown_00), unknown_04(o.unknown_04), unknown_08(o.unknown_08), unknown_0C(o.unknown_0C) {} bool operator==(const ZoneConnectionClass& o) const { return unknown_00==o.unknown_00 && unknown_04==o.unknown_04; } bool operator!=(const ZoneConnectionClass& o) const { return !(*this==o); } };
// FUNCTION: GAMEMD 0x00589370
// VectorClass<ZoneConnectionClass>::SetCapacity
// FUNCTION: GAMEMD 0x005894D0
// VectorClass<ZoneConnectionClass>::FindItemIndex
// FUNCTION: GAMEMD 0x00589530
// VectorClass<ZoneConnectionClass>::Slot5
// VTABLE: GAMEMD 0x007ED4E0 -- VectorClass<ZoneConnectionClass>.
template class VectorClass<ZoneConnectionClass>;
template class DynamicVectorClass<ZoneConnectionClass>;

struct WaypointClass { int unknown_00; int unknown_04; int unknown_08; WaypointClass(int a = 0, int b = 0, int c = 0) : unknown_00(a), unknown_04(b), unknown_08(c) {} ~WaypointClass() {} bool operator==(const WaypointClass& o) const { return unknown_00==o.unknown_00 && unknown_04==o.unknown_04 && unknown_08==o.unknown_08; } bool operator!=(const WaypointClass& o) const { return !(*this==o); } };
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
template class VectorClass<WaypointClass>;
template class DynamicVectorClass<WaypointClass>;

class CellClass; template<class C> struct DiscreteDistributionClass { template<class P> struct DistributionObject { P Object; int Weight; DistributionObject() : Object(0) {} ~DistributionObject() {} DistributionObject(const DistributionObject<P>& o) : Object(o.Object), Weight(o.Weight) {} bool operator==(const DistributionObject<P>& o) const { return Object==o.Object && Weight==o.Weight; } bool operator!=(const DistributionObject<P>& o) const { return !(*this==o); } }; };
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
template class VectorClass<DiscreteDistributionClass<CellClass>::DistributionObject<CellClass*> >;
template class DynamicVectorClass<DiscreteDistributionClass<CellClass>::DistributionObject<CellClass*> >;

class BuildingTypeClass; 
// FUNCTION: GAMEMD 0x0050FC00
// VectorClass<DiscreteDistributionClass<BuildingTypeClass>::DistributionObject<BuildingTypeClass*>>::operator==
// FUNCTION: GAMEMD 0x0050FDB0
// VectorClass<DiscreteDistributionClass<BuildingTypeClass>::DistributionObject<BuildingTypeClass*>>::FindItemIndex
// FUNCTION: GAMEMD 0x0050FE00
// VectorClass<DiscreteDistributionClass<BuildingTypeClass>::DistributionObject<BuildingTypeClass*>>::Slot5
// FUNCTION: GAMEMD 0x0050FFB0
// DynamicVectorClass<DiscreteDistributionClass<BuildingTypeClass>::DistributionObject<BuildingTypeClass*>>::FindItemIndex
// FUNCTION: GAMEMD 0x0050E7A0
// DynamicVectorClass<DiscreteDistributionClass<BuildingTypeClass>::DistributionObject<BuildingTypeClass*>>::Slot5
template class VectorClass<DiscreteDistributionClass<BuildingTypeClass>::DistributionObject<BuildingTypeClass*> >;
template class DynamicVectorClass<DiscreteDistributionClass<BuildingTypeClass>::DistributionObject<BuildingTypeClass*> >;

class AITriggerTypeClass; 
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
template class VectorClass<DiscreteDistributionClass<AITriggerTypeClass>::DistributionObject<AITriggerTypeClass*> >;
template class DynamicVectorClass<DiscreteDistributionClass<AITriggerTypeClass>::DistributionObject<AITriggerTypeClass*> >;

