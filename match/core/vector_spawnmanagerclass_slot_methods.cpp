// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Retail RTTI type descriptors name VectorClass<SpawnManagerClass*> and
// DynamicVectorClass<SpawnManagerClass*>; each address below is the vtable slot body
// of that specialization (slot owner read from the retail vtables).
// Pointer/scalar/enum element: no element layout is claimed.
#include "vector_class_operations.h"

class SpawnManagerClass;

// TEMPLATE: GAMEMD 0x6B81F0
// DynamicVectorClass<SpawnManagerClass*>::Slot5 (slot 5)
// TEMPLATE: GAMEMD 0x6B8210
// VectorClass<SpawnManagerClass*>::Slot6 (slot 6)
// TEMPLATE: GAMEMD 0x6B84E0
// VectorClass<SpawnManagerClass*>::operator== (slot 1)
// TEMPLATE: GAMEMD 0x6B8520
// VectorClass<SpawnManagerClass*>::SetCapacity (slot 2)
// TEMPLATE: GAMEMD 0x6B8600
// VectorClass<SpawnManagerClass*>::FindItemIndex (slot 4)
// TEMPLATE: GAMEMD 0x6B8640
// VectorClass<SpawnManagerClass*>::Slot5 (slot 5)
// TEMPLATE: GAMEMD 0x6B8660
// DynamicVectorClass<SpawnManagerClass*>::SetCapacity (slot 2)
// TEMPLATE: GAMEMD 0x6B8710
// DynamicVectorClass<SpawnManagerClass*>::FindItemIndex (slot 4)
template class VectorClass<SpawnManagerClass*>;
template class DynamicVectorClass<SpawnManagerClass*>;

GG_STATIC_ASSERT(sizeof(SpawnManagerClass*) == 4);
GG_STATIC_ASSERT(sizeof(VectorClass<SpawnManagerClass* >) == 0x10);
GG_STATIC_ASSERT(sizeof(DynamicVectorClass<SpawnManagerClass* >) == 0x18);
