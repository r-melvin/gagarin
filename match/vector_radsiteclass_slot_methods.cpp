// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Retail RTTI type descriptors name VectorClass<RadSiteClass*> and
// DynamicVectorClass<RadSiteClass*>; each address below is the vtable slot body
// of that specialization (slot owner read from the retail vtables).
// Pointer/scalar/enum element: no element layout is claimed.
#include "vector_class_operations.h"

class RadSiteClass;

// TEMPLATE: GAMEMD 0x65BF20
// DynamicVectorClass<RadSiteClass*>::Slot5 (slot 5)
// TEMPLATE: GAMEMD 0x65BF40
// VectorClass<RadSiteClass*>::Slot6 (slot 6)
// TEMPLATE: GAMEMD 0x65BF50
// VectorClass<RadSiteClass*>::operator== (slot 1)
// TEMPLATE: GAMEMD 0x65BF90
// VectorClass<RadSiteClass*>::SetCapacity (slot 2)
// TEMPLATE: GAMEMD 0x65C070
// VectorClass<RadSiteClass*>::FindItemIndex (slot 4)
// TEMPLATE: GAMEMD 0x65C0B0
// VectorClass<RadSiteClass*>::Slot5 (slot 5)
// TEMPLATE: GAMEMD 0x65C0D0
// DynamicVectorClass<RadSiteClass*>::SetCapacity (slot 2)
// TEMPLATE: GAMEMD 0x65C180
// DynamicVectorClass<RadSiteClass*>::FindItemIndex (slot 4)
template class VectorClass<RadSiteClass*>;
template class DynamicVectorClass<RadSiteClass*>;

GG_STATIC_ASSERT(sizeof(RadSiteClass*) == 4);
GG_STATIC_ASSERT(sizeof(VectorClass<RadSiteClass* >) == 0x10);
GG_STATIC_ASSERT(sizeof(DynamicVectorClass<RadSiteClass* >) == 0x18);
