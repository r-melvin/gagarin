// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Retail RTTI type descriptors name VectorClass<MixFileClass*> and
// DynamicVectorClass<MixFileClass*>; each address below is the vtable slot body
// of that specialization (slot owner read from the retail vtables).
// Pointer/scalar/enum element: no element layout is claimed.
#include "vector_class_operations.h"

class MixFileClass;

// TEMPLATE: GAMEMD 0x40D570
// DynamicVectorClass<MixFileClass*>::Slot5 (slot 5)
// TEMPLATE: GAMEMD 0x40D590
// VectorClass<MixFileClass*>::Slot6 (slot 6)
// TEMPLATE: GAMEMD 0x40D5A0
// VectorClass<MixFileClass*>::operator== (slot 1)
// TEMPLATE: GAMEMD 0x40D5E0
// VectorClass<MixFileClass*>::SetCapacity (slot 2)
// TEMPLATE: GAMEMD 0x40D6C0
// VectorClass<MixFileClass*>::FindItemIndex (slot 4)
// TEMPLATE: GAMEMD 0x40D700
// VectorClass<MixFileClass*>::Slot5 (slot 5)
// TEMPLATE: GAMEMD 0x40D720
// DynamicVectorClass<MixFileClass*>::SetCapacity (slot 2)
// TEMPLATE: GAMEMD 0x40D7D0
// DynamicVectorClass<MixFileClass*>::FindItemIndex (slot 4)
template class VectorClass<MixFileClass*>;
template class DynamicVectorClass<MixFileClass*>;

GG_STATIC_ASSERT(sizeof(MixFileClass*) == 4);
GG_STATIC_ASSERT(sizeof(VectorClass<MixFileClass* >) == 0x10);
GG_STATIC_ASSERT(sizeof(DynamicVectorClass<MixFileClass* >) == 0x18);
