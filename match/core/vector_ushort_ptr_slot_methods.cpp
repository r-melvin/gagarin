// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Retail RTTI type descriptors name VectorClass<unsigned short*> and
// DynamicVectorClass<unsigned short*>; each address below is the vtable slot body
// of that specialization (slot owner read from the retail vtables).
// Pointer/scalar/enum element: no element layout is claimed.
#include "vector_class_operations.h"

// TEMPLATE: GAMEMD 0x54A1C0
// DynamicVectorClass<unsigned short*>::Slot5 (slot 5)
// TEMPLATE: GAMEMD 0x54A1E0
// VectorClass<unsigned short*>::Slot6 (slot 6)
// TEMPLATE: GAMEMD 0x54A250
// VectorClass<unsigned short*>::operator== (slot 1)
// TEMPLATE: GAMEMD 0x54A290
// VectorClass<unsigned short*>::SetCapacity (slot 2)
// TEMPLATE: GAMEMD 0x54A370
// VectorClass<unsigned short*>::FindItemIndex (slot 4)
// TEMPLATE: GAMEMD 0x54A3B0
// VectorClass<unsigned short*>::Slot5 (slot 5)
// TEMPLATE: GAMEMD 0x54A3D0
// DynamicVectorClass<unsigned short*>::SetCapacity (slot 2)
// TEMPLATE: GAMEMD 0x54A480
// DynamicVectorClass<unsigned short*>::FindItemIndex (slot 4)
template class VectorClass<unsigned short*>;
template class DynamicVectorClass<unsigned short*>;

GG_STATIC_ASSERT(sizeof(unsigned short*) == 4);
GG_STATIC_ASSERT(sizeof(VectorClass<unsigned short* >) == 0x10);
GG_STATIC_ASSERT(sizeof(DynamicVectorClass<unsigned short* >) == 0x18);
