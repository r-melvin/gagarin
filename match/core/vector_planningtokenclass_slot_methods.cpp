// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Retail RTTI type descriptors name VectorClass<PlanningTokenClass*> and
// DynamicVectorClass<PlanningTokenClass*>; each address below is the vtable slot body
// of that specialization (slot owner read from the retail vtables).
// Pointer/scalar/enum element: no element layout is claimed.
#include "vector_class_operations.h"

class PlanningTokenClass;

// TEMPLATE: GAMEMD 0x63DD10
// DynamicVectorClass<PlanningTokenClass*>::Slot5 (slot 5)
// TEMPLATE: GAMEMD 0x63DD30
// VectorClass<PlanningTokenClass*>::Slot6 (slot 6)
// TEMPLATE: GAMEMD 0x63E950
// VectorClass<PlanningTokenClass*>::operator== (slot 1)
// TEMPLATE: GAMEMD 0x63E990
// VectorClass<PlanningTokenClass*>::SetCapacity (slot 2)
// TEMPLATE: GAMEMD 0x63EA70
// VectorClass<PlanningTokenClass*>::FindItemIndex (slot 4)
// TEMPLATE: GAMEMD 0x63EAB0
// VectorClass<PlanningTokenClass*>::Slot5 (slot 5)
// TEMPLATE: GAMEMD 0x63EAD0
// DynamicVectorClass<PlanningTokenClass*>::SetCapacity (slot 2)
// TEMPLATE: GAMEMD 0x63EC20
// DynamicVectorClass<PlanningTokenClass*>::FindItemIndex (slot 4)
template class VectorClass<PlanningTokenClass*>;
template class DynamicVectorClass<PlanningTokenClass*>;

GG_STATIC_ASSERT(sizeof(PlanningTokenClass*) == 4);
GG_STATIC_ASSERT(sizeof(VectorClass<PlanningTokenClass* >) == 0x10);
GG_STATIC_ASSERT(sizeof(DynamicVectorClass<PlanningTokenClass* >) == 0x18);
