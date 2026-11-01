// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Retail RTTI type descriptors name VectorClass<unsigned int> and
// DynamicVectorClass<unsigned int>; each address below is the vtable slot body
// of that specialization (slot owner read from the retail vtables).
// Pointer/scalar/enum element: no element layout is claimed.
#include "vector_class_operations.h"

// TEMPLATE: GAMEMD 0x42D570
// DynamicVectorClass<unsigned int>::Slot5 (slot 5)
// TEMPLATE: GAMEMD 0x42D590
// VectorClass<unsigned int>::Slot6 (slot 6)
// TEMPLATE: GAMEMD 0x42D600
// VectorClass<unsigned int>::operator== (slot 1)
// TEMPLATE: GAMEMD 0x42D640
// VectorClass<unsigned int>::SetCapacity (slot 2)
// TEMPLATE: GAMEMD 0x42D720
// VectorClass<unsigned int>::FindItemIndex (slot 4)
// TEMPLATE: GAMEMD 0x42D760
// VectorClass<unsigned int>::Slot5 (slot 5)
// TEMPLATE: GAMEMD 0x42D880
// DynamicVectorClass<unsigned int>::FindItemIndex (slot 4)
template class VectorClass<unsigned int>;
template class DynamicVectorClass<unsigned int>;

GG_STATIC_ASSERT(sizeof(unsigned int) == 4);
GG_STATIC_ASSERT(sizeof(VectorClass<unsigned int >) == 0x10);
GG_STATIC_ASSERT(sizeof(DynamicVectorClass<unsigned int >) == 0x18);
