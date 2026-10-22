// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Retail RTTI type descriptors name VectorClass<ObjectClass*> and
// DynamicVectorClass<ObjectClass*>; each address below is the vtable slot body
// of that specialization (slot owner read from the retail vtables).
// Pointer/scalar/enum element: no element layout is claimed.
#include "vector_class_operations.h"

class ObjectClass;

// TEMPLATE: GAMEMD 0x40CCA0
// DynamicVectorClass<ObjectClass*>::Slot5 (slot 5)
// TEMPLATE: GAMEMD 0x40CCC0
// VectorClass<ObjectClass*>::Slot6 (slot 6)
// TEMPLATE: GAMEMD 0x40CCD0
// VectorClass<ObjectClass*>::operator== (slot 1)
// TEMPLATE: GAMEMD 0x40CD10
// VectorClass<ObjectClass*>::SetCapacity (slot 2)
// TEMPLATE: GAMEMD 0x40CDF0
// VectorClass<ObjectClass*>::FindItemIndex (slot 4)
// TEMPLATE: GAMEMD 0x40CE30
// VectorClass<ObjectClass*>::Slot5 (slot 5)
// TEMPLATE: GAMEMD 0x40CF00
// DynamicVectorClass<ObjectClass*>::FindItemIndex (slot 4)
template class VectorClass<ObjectClass*>;
template class DynamicVectorClass<ObjectClass*>;

GG_STATIC_ASSERT(sizeof(ObjectClass*) == 4);
GG_STATIC_ASSERT(sizeof(VectorClass<ObjectClass* >) == 0x10);
GG_STATIC_ASSERT(sizeof(DynamicVectorClass<ObjectClass* >) == 0x18);
