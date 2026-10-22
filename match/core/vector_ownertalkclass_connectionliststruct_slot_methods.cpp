// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Retail RTTI type descriptors name VectorClass<OwnerTalkClass::ConnectionListStruct*> and
// DynamicVectorClass<OwnerTalkClass::ConnectionListStruct*>; each address below is the vtable slot body
// of that specialization (slot owner read from the retail vtables).
// Pointer/scalar/enum element: no element layout is claimed.
#include "vector_class_operations.h"

class OwnerTalkClass {
public:
    struct ConnectionListStruct;
};

// TEMPLATE: GAMEMD 0x6647E0
// DynamicVectorClass<OwnerTalkClass::ConnectionListStruct*>::Slot5 (slot 5)
// TEMPLATE: GAMEMD 0x664800
// VectorClass<OwnerTalkClass::ConnectionListStruct*>::Slot6 (slot 6)
// TEMPLATE: GAMEMD 0x664810
// VectorClass<OwnerTalkClass::ConnectionListStruct*>::operator== (slot 1)
// TEMPLATE: GAMEMD 0x664850
// VectorClass<OwnerTalkClass::ConnectionListStruct*>::SetCapacity (slot 2)
// TEMPLATE: GAMEMD 0x664930
// VectorClass<OwnerTalkClass::ConnectionListStruct*>::FindItemIndex (slot 4)
// TEMPLATE: GAMEMD 0x664970
// VectorClass<OwnerTalkClass::ConnectionListStruct*>::Slot5 (slot 5)
// TEMPLATE: GAMEMD 0x664990
// DynamicVectorClass<OwnerTalkClass::ConnectionListStruct*>::SetCapacity (slot 2)
// TEMPLATE: GAMEMD 0x664A40
// DynamicVectorClass<OwnerTalkClass::ConnectionListStruct*>::FindItemIndex (slot 4)
template class VectorClass<OwnerTalkClass::ConnectionListStruct*>;
template class DynamicVectorClass<OwnerTalkClass::ConnectionListStruct*>;

GG_STATIC_ASSERT(sizeof(OwnerTalkClass::ConnectionListStruct*) == 4);
GG_STATIC_ASSERT(sizeof(VectorClass<OwnerTalkClass::ConnectionListStruct* >) == 0x10);
GG_STATIC_ASSERT(sizeof(DynamicVectorClass<OwnerTalkClass::ConnectionListStruct* >) == 0x18);
