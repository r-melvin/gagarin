// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Retail RTTI type descriptors name VectorClass<LightSourceClass::PendingCellClass*> and
// DynamicVectorClass<LightSourceClass::PendingCellClass*>; each address below is the vtable slot body
// of that specialization (slot owner read from the retail vtables).
// Pointer/scalar/enum element: no element layout is claimed.
#include "vector_class_operations.h"

class LightSourceClass {
public:
    class PendingCellClass;
};

// TEMPLATE: GAMEMD 0x555290
// DynamicVectorClass<LightSourceClass::PendingCellClass*>::Slot5 (slot 5)
// TEMPLATE: GAMEMD 0x5552B0
// VectorClass<LightSourceClass::PendingCellClass*>::Slot6 (slot 6)
// TEMPLATE: GAMEMD 0x555520
// VectorClass<LightSourceClass::PendingCellClass*>::operator== (slot 1)
// TEMPLATE: GAMEMD 0x555560
// VectorClass<LightSourceClass::PendingCellClass*>::SetCapacity (slot 2)
// TEMPLATE: GAMEMD 0x555640
// VectorClass<LightSourceClass::PendingCellClass*>::FindItemIndex (slot 4)
// TEMPLATE: GAMEMD 0x555680
// VectorClass<LightSourceClass::PendingCellClass*>::Slot5 (slot 5)
// TEMPLATE: GAMEMD 0x5556A0
// DynamicVectorClass<LightSourceClass::PendingCellClass*>::SetCapacity (slot 2)
// TEMPLATE: GAMEMD 0x555750
// DynamicVectorClass<LightSourceClass::PendingCellClass*>::FindItemIndex (slot 4)
template class VectorClass<LightSourceClass::PendingCellClass*>;
template class DynamicVectorClass<LightSourceClass::PendingCellClass*>;

GG_STATIC_ASSERT(sizeof(LightSourceClass::PendingCellClass*) == 4);
GG_STATIC_ASSERT(sizeof(VectorClass<LightSourceClass::PendingCellClass* >) == 0x10);
GG_STATIC_ASSERT(sizeof(DynamicVectorClass<LightSourceClass::PendingCellClass* >) == 0x18);
