// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Retail RTTI type descriptors name VectorClass<Reestablish*> and
// DynamicVectorClass<Reestablish*>; each address below is the vtable slot body
// of that specialization (slot owner read from the retail vtables).
// Pointer/scalar/enum element: no element layout is claimed.
#include "vector_class_operations.h"

class Reestablish;

// TEMPLATE: GAMEMD 0x45A100
// DynamicVectorClass<Reestablish*>::Slot5 (slot 5)
// TEMPLATE: GAMEMD 0x45A120
// VectorClass<Reestablish*>::Slot6 (slot 6)
// TEMPLATE: GAMEMD 0x45A760
// VectorClass<Reestablish*>::operator== (slot 1)
// TEMPLATE: GAMEMD 0x45A7A0
// VectorClass<Reestablish*>::SetCapacity (slot 2)
// TEMPLATE: GAMEMD 0x45A880
// VectorClass<Reestablish*>::FindItemIndex (slot 4)
// TEMPLATE: GAMEMD 0x45A8C0
// VectorClass<Reestablish*>::Slot5 (slot 5)
// TEMPLATE: GAMEMD 0x45A8E0
// DynamicVectorClass<Reestablish*>::SetCapacity (slot 2)
// TEMPLATE: GAMEMD 0x45A990
// DynamicVectorClass<Reestablish*>::FindItemIndex (slot 4)
template class VectorClass<Reestablish*>;
template class DynamicVectorClass<Reestablish*>;

GG_STATIC_ASSERT(sizeof(Reestablish*) == 4);
GG_STATIC_ASSERT(sizeof(VectorClass<Reestablish* >) == 0x10);
GG_STATIC_ASSERT(sizeof(DynamicVectorClass<Reestablish* >) == 0x18);
