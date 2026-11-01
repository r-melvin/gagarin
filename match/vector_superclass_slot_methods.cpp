// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Retail RTTI type descriptors name VectorClass<SuperClass*> and
// DynamicVectorClass<SuperClass*>; each address below is the vtable slot body
// of that specialization (slot owner read from the retail vtables).
// Pointer/scalar/enum element: no element layout is claimed.
#include "vector_class_operations.h"

class SuperClass;

// TEMPLATE: GAMEMD 0x4E8380
// DynamicVectorClass<SuperClass*>::Slot5 (slot 5)
// TEMPLATE: GAMEMD 0x4E83A0
// VectorClass<SuperClass*>::Slot6 (slot 6)
// TEMPLATE: GAMEMD 0x4E96C0
// VectorClass<SuperClass*>::operator== (slot 1)
// TEMPLATE: GAMEMD 0x4E9700
// VectorClass<SuperClass*>::SetCapacity (slot 2)
// TEMPLATE: GAMEMD 0x4E97E0
// VectorClass<SuperClass*>::FindItemIndex (slot 4)
// TEMPLATE: GAMEMD 0x4E9820
// VectorClass<SuperClass*>::Slot5 (slot 5)
// TEMPLATE: GAMEMD 0x4E98F0
// DynamicVectorClass<SuperClass*>::FindItemIndex (slot 4)
template class VectorClass<SuperClass*>;
template class DynamicVectorClass<SuperClass*>;

GG_STATIC_ASSERT(sizeof(SuperClass*) == 4);
GG_STATIC_ASSERT(sizeof(VectorClass<SuperClass* >) == 0x10);
GG_STATIC_ASSERT(sizeof(DynamicVectorClass<SuperClass* >) == 0x18);
