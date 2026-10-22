// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Retail RTTI type descriptors name VectorClass<SlaveManagerClass*> and
// DynamicVectorClass<SlaveManagerClass*>; each address below is the vtable slot body
// of that specialization (slot owner read from the retail vtables).
// Pointer/scalar/enum element: no element layout is claimed.
#include "vector_class_operations.h"

class SlaveManagerClass;

// TEMPLATE: GAMEMD 0x6B1440
// DynamicVectorClass<SlaveManagerClass*>::Slot5 (slot 5)
// TEMPLATE: GAMEMD 0x6B1460
// VectorClass<SlaveManagerClass*>::Slot6 (slot 6)
// TEMPLATE: GAMEMD 0x6B16D0
// VectorClass<SlaveManagerClass*>::operator== (slot 1)
// TEMPLATE: GAMEMD 0x6B1710
// VectorClass<SlaveManagerClass*>::SetCapacity (slot 2)
// TEMPLATE: GAMEMD 0x6B17F0
// VectorClass<SlaveManagerClass*>::FindItemIndex (slot 4)
// TEMPLATE: GAMEMD 0x6B1830
// VectorClass<SlaveManagerClass*>::Slot5 (slot 5)
// TEMPLATE: GAMEMD 0x6B1850
// DynamicVectorClass<SlaveManagerClass*>::SetCapacity (slot 2)
// TEMPLATE: GAMEMD 0x6B1900
// DynamicVectorClass<SlaveManagerClass*>::FindItemIndex (slot 4)
template class VectorClass<SlaveManagerClass*>;
template class DynamicVectorClass<SlaveManagerClass*>;

GG_STATIC_ASSERT(sizeof(SlaveManagerClass*) == 4);
GG_STATIC_ASSERT(sizeof(VectorClass<SlaveManagerClass* >) == 0x10);
GG_STATIC_ASSERT(sizeof(DynamicVectorClass<SlaveManagerClass* >) == 0x18);
