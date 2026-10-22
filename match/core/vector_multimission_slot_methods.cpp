// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Retail RTTI type descriptors name VectorClass<MultiMission*> and
// DynamicVectorClass<MultiMission*>; each address below is the vtable slot body
// of that specialization (slot owner read from the retail vtables).
// Pointer/scalar/enum element: no element layout is claimed.
#include "vector_class_operations.h"

class MultiMission;

// TEMPLATE: GAMEMD 0x69C5D0
// DynamicVectorClass<MultiMission*>::Slot5 (slot 5)
// TEMPLATE: GAMEMD 0x69C5F0
// VectorClass<MultiMission*>::Slot6 (slot 6)
// TEMPLATE: GAMEMD 0x69CD40
// VectorClass<MultiMission*>::operator== (slot 1)
// TEMPLATE: GAMEMD 0x69CD80
// VectorClass<MultiMission*>::SetCapacity (slot 2)
// TEMPLATE: GAMEMD 0x69CE60
// VectorClass<MultiMission*>::FindItemIndex (slot 4)
// TEMPLATE: GAMEMD 0x69CEA0
// VectorClass<MultiMission*>::Slot5 (slot 5)
// TEMPLATE: GAMEMD 0x69CEC0
// DynamicVectorClass<MultiMission*>::SetCapacity (slot 2)
// TEMPLATE: GAMEMD 0x69CF70
// DynamicVectorClass<MultiMission*>::FindItemIndex (slot 4)
template class VectorClass<MultiMission*>;
template class DynamicVectorClass<MultiMission*>;

GG_STATIC_ASSERT(sizeof(MultiMission*) == 4);
GG_STATIC_ASSERT(sizeof(VectorClass<MultiMission* >) == 0x10);
GG_STATIC_ASSERT(sizeof(DynamicVectorClass<MultiMission* >) == 0x18);
