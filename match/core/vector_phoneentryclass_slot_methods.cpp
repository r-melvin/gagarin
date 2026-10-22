// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Retail RTTI type descriptors name VectorClass<PhoneEntryClass*> and
// DynamicVectorClass<PhoneEntryClass*>; each address below is the vtable slot body
// of that specialization (slot owner read from the retail vtables).
// Pointer/scalar/enum element: no element layout is claimed.
#include "vector_class_operations.h"

class PhoneEntryClass;

// TEMPLATE: GAMEMD 0x69C690
// DynamicVectorClass<PhoneEntryClass*>::Slot5 (slot 5)
// TEMPLATE: GAMEMD 0x69C6B0
// VectorClass<PhoneEntryClass*>::Slot6 (slot 6)
// TEMPLATE: GAMEMD 0x69D200
// VectorClass<PhoneEntryClass*>::operator== (slot 1)
// TEMPLATE: GAMEMD 0x69D240
// VectorClass<PhoneEntryClass*>::SetCapacity (slot 2)
// TEMPLATE: GAMEMD 0x69D320
// VectorClass<PhoneEntryClass*>::FindItemIndex (slot 4)
// TEMPLATE: GAMEMD 0x69D360
// VectorClass<PhoneEntryClass*>::Slot5 (slot 5)
// TEMPLATE: GAMEMD 0x69D380
// DynamicVectorClass<PhoneEntryClass*>::SetCapacity (slot 2)
// TEMPLATE: GAMEMD 0x69D430
// DynamicVectorClass<PhoneEntryClass*>::FindItemIndex (slot 4)
template class VectorClass<PhoneEntryClass*>;
template class DynamicVectorClass<PhoneEntryClass*>;

GG_STATIC_ASSERT(sizeof(PhoneEntryClass*) == 4);
GG_STATIC_ASSERT(sizeof(VectorClass<PhoneEntryClass* >) == 0x10);
GG_STATIC_ASSERT(sizeof(DynamicVectorClass<PhoneEntryClass* >) == 0x18);
