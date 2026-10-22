// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Retail RTTI type descriptors name VectorClass<const CommandClass*> and
// DynamicVectorClass<const CommandClass*>; each address below is the vtable slot body
// of that specialization (slot owner read from the retail vtables).
// Pointer/scalar/enum element: no element layout is claimed.
#include "vector_class_operations.h"

class CommandClass;

// TEMPLATE: GAMEMD 0x40BE80
// DynamicVectorClass<const CommandClass*>::Slot5 (slot 5)
// TEMPLATE: GAMEMD 0x40BEA0
// VectorClass<const CommandClass*>::Slot6 (slot 6)
// TEMPLATE: GAMEMD 0x40BEB0
// VectorClass<const CommandClass*>::operator== (slot 1)
// TEMPLATE: GAMEMD 0x40BEF0
// VectorClass<const CommandClass*>::SetCapacity (slot 2)
// TEMPLATE: GAMEMD 0x40BFD0
// VectorClass<const CommandClass*>::FindItemIndex (slot 4)
// TEMPLATE: GAMEMD 0x40C010
// VectorClass<const CommandClass*>::Slot5 (slot 5)
// TEMPLATE: GAMEMD 0x40C030
// DynamicVectorClass<const CommandClass*>::SetCapacity (slot 2)
// TEMPLATE: GAMEMD 0x40C0E0
// DynamicVectorClass<const CommandClass*>::FindItemIndex (slot 4)
template class VectorClass<const CommandClass*>;
template class DynamicVectorClass<const CommandClass*>;

GG_STATIC_ASSERT(sizeof(const CommandClass*) == 4);
GG_STATIC_ASSERT(sizeof(VectorClass<const CommandClass* >) == 0x10);
GG_STATIC_ASSERT(sizeof(DynamicVectorClass<const CommandClass* >) == 0x18);
