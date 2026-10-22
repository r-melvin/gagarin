// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Retail RTTI type descriptors name VectorClass<SpawnManagerClass::SpawnControl*> and
// DynamicVectorClass<SpawnManagerClass::SpawnControl*>; each address below is the vtable slot body
// of that specialization (slot owner read from the retail vtables).
// Pointer/scalar/enum element: no element layout is claimed.
#include "vector_class_operations.h"

class SpawnManagerClass {
public:
    struct SpawnControl;
};

// TEMPLATE: GAMEMD 0x6B8190
// DynamicVectorClass<SpawnManagerClass::SpawnControl*>::Slot5 (slot 5)
// TEMPLATE: GAMEMD 0x6B81B0
// VectorClass<SpawnManagerClass::SpawnControl*>::Slot6 (slot 6)
// TEMPLATE: GAMEMD 0x6B8220
// VectorClass<SpawnManagerClass::SpawnControl*>::operator== (slot 1)
// TEMPLATE: GAMEMD 0x6B8260
// VectorClass<SpawnManagerClass::SpawnControl*>::SetCapacity (slot 2)
// TEMPLATE: GAMEMD 0x6B8340
// VectorClass<SpawnManagerClass::SpawnControl*>::FindItemIndex (slot 4)
// TEMPLATE: GAMEMD 0x6B8380
// VectorClass<SpawnManagerClass::SpawnControl*>::Slot5 (slot 5)
// TEMPLATE: GAMEMD 0x6B84B0
// DynamicVectorClass<SpawnManagerClass::SpawnControl*>::FindItemIndex (slot 4)
template class VectorClass<SpawnManagerClass::SpawnControl*>;
template class DynamicVectorClass<SpawnManagerClass::SpawnControl*>;

GG_STATIC_ASSERT(sizeof(SpawnManagerClass::SpawnControl*) == 4);
GG_STATIC_ASSERT(sizeof(VectorClass<SpawnManagerClass::SpawnControl* >) == 0x10);
GG_STATIC_ASSERT(sizeof(DynamicVectorClass<SpawnManagerClass::SpawnControl* >) == 0x18);
