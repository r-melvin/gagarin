// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Retail RTTI type descriptors name VectorClass<PlanningBranchClass*> and
// DynamicVectorClass<PlanningBranchClass*>; each address below is the vtable slot body
// of that specialization (slot owner read from the retail vtables).
// Pointer/scalar/enum element: no element layout is claimed.
#include "vector_class_operations.h"

class PlanningBranchClass;

// TEMPLATE: GAMEMD 0x63DBF0
// DynamicVectorClass<PlanningBranchClass*>::Slot5 (slot 5)
// TEMPLATE: GAMEMD 0x63DC10
// VectorClass<PlanningBranchClass*>::Slot6 (slot 6)
// TEMPLATE: GAMEMD 0x63E050
// VectorClass<PlanningBranchClass*>::operator== (slot 1)
// TEMPLATE: GAMEMD 0x63E090
// VectorClass<PlanningBranchClass*>::SetCapacity (slot 2)
// TEMPLATE: GAMEMD 0x63E170
// VectorClass<PlanningBranchClass*>::FindItemIndex (slot 4)
// TEMPLATE: GAMEMD 0x63E1B0
// VectorClass<PlanningBranchClass*>::Slot5 (slot 5)
// TEMPLATE: GAMEMD 0x63E230
// DynamicVectorClass<PlanningBranchClass*>::SetCapacity (slot 2)
// TEMPLATE: GAMEMD 0x63E2E0
// DynamicVectorClass<PlanningBranchClass*>::FindItemIndex (slot 4)
template class VectorClass<PlanningBranchClass*>;
template class DynamicVectorClass<PlanningBranchClass*>;

GG_STATIC_ASSERT(sizeof(PlanningBranchClass*) == 4);
GG_STATIC_ASSERT(sizeof(VectorClass<PlanningBranchClass* >) == 0x10);
GG_STATIC_ASSERT(sizeof(DynamicVectorClass<PlanningBranchClass* >) == 0x18);
