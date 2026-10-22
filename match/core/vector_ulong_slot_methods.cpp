// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Retail RTTI type descriptors name VectorClass<unsigned long> and
// DynamicVectorClass<unsigned long>; each address below is the vtable slot body
// of that specialization (slot owner read from the retail vtables).
// Pointer/scalar/enum element: no element layout is claimed.
#include "vector_class_operations.h"

// TEMPLATE: GAMEMD 0x6BED80
// DynamicVectorClass<unsigned long>::Slot5 (slot 5)
// TEMPLATE: GAMEMD 0x6BEDA0
// VectorClass<unsigned long>::Slot6 (slot 6)
// TEMPLATE: GAMEMD 0x6C61D0
// VectorClass<unsigned long>::operator== (slot 1)
// TEMPLATE: GAMEMD 0x6C6210
// VectorClass<unsigned long>::SetCapacity (slot 2)
// TEMPLATE: GAMEMD 0x6C62F0
// VectorClass<unsigned long>::FindItemIndex (slot 4)
// TEMPLATE: GAMEMD 0x6C6330
// VectorClass<unsigned long>::Slot5 (slot 5)
// TEMPLATE: GAMEMD 0x6C6350
// DynamicVectorClass<unsigned long>::SetCapacity (slot 2)
// TEMPLATE: GAMEMD 0x6C6450
// DynamicVectorClass<unsigned long>::FindItemIndex (slot 4)
template class VectorClass<unsigned long>;
template class DynamicVectorClass<unsigned long>;

GG_STATIC_ASSERT(sizeof(unsigned long) == 4);
GG_STATIC_ASSERT(sizeof(VectorClass<unsigned long >) == 0x10);
GG_STATIC_ASSERT(sizeof(DynamicVectorClass<unsigned long >) == 0x18);
