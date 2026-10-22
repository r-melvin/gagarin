// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Retail RTTI type descriptors name VectorClass<PlanningMemberClass*> and
// DynamicVectorClass<PlanningMemberClass*>; each address below is the vtable slot body
// of that specialization (slot owner read from the retail vtables).
// Pointer/scalar/enum element: no element layout is claimed.
#include "vector_class_operations.h"

class PlanningMemberClass;

// TEMPLATE: GAMEMD 0x63DB90
// DynamicVectorClass<PlanningMemberClass*>::Slot5 (slot 5)
// TEMPLATE: GAMEMD 0x63DBB0
// VectorClass<PlanningMemberClass*>::Slot6 (slot 6)
// TEMPLATE: GAMEMD 0x63DD40
// VectorClass<PlanningMemberClass*>::operator== (slot 1)
// TEMPLATE: GAMEMD 0x63DD80
// VectorClass<PlanningMemberClass*>::SetCapacity (slot 2)
// TEMPLATE: GAMEMD 0x63DE60
// VectorClass<PlanningMemberClass*>::FindItemIndex (slot 4)
// TEMPLATE: GAMEMD 0x63DEA0
// VectorClass<PlanningMemberClass*>::Slot5 (slot 5)
// TEMPLATE: GAMEMD 0x63DF20
// DynamicVectorClass<PlanningMemberClass*>::SetCapacity (slot 2)
// TEMPLATE: GAMEMD 0x63E020
// DynamicVectorClass<PlanningMemberClass*>::FindItemIndex (slot 4)
template class VectorClass<PlanningMemberClass*>;
template class DynamicVectorClass<PlanningMemberClass*>;

GG_STATIC_ASSERT(sizeof(PlanningMemberClass*) == 4);
GG_STATIC_ASSERT(sizeof(VectorClass<PlanningMemberClass* >) == 0x10);
GG_STATIC_ASSERT(sizeof(DynamicVectorClass<PlanningMemberClass* >) == 0x18);
