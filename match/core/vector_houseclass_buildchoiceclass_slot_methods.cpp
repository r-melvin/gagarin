// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Retail RTTI type descriptors name VectorClass<HouseClass::BuildChoiceClass*> and
// DynamicVectorClass<HouseClass::BuildChoiceClass*>; each address below is the vtable slot body
// of that specialization (slot owner read from the retail vtables).
// Pointer/scalar/enum element: no element layout is claimed.
#include "vector_class_operations.h"

class HouseClass {
public:
    struct BuildChoiceClass;
};

// TEMPLATE: GAMEMD 0x50E670
// DynamicVectorClass<HouseClass::BuildChoiceClass*>::Slot5 (slot 5)
// TEMPLATE: GAMEMD 0x50E690
// VectorClass<HouseClass::BuildChoiceClass*>::Slot6 (slot 6)
// TEMPLATE: GAMEMD 0x50F4E0
// VectorClass<HouseClass::BuildChoiceClass*>::operator== (slot 1)
// TEMPLATE: GAMEMD 0x50F520
// VectorClass<HouseClass::BuildChoiceClass*>::SetCapacity (slot 2)
// TEMPLATE: GAMEMD 0x50F600
// VectorClass<HouseClass::BuildChoiceClass*>::FindItemIndex (slot 4)
// TEMPLATE: GAMEMD 0x50F640
// VectorClass<HouseClass::BuildChoiceClass*>::Slot5 (slot 5)
// TEMPLATE: GAMEMD 0x50F660
// DynamicVectorClass<HouseClass::BuildChoiceClass*>::SetCapacity (slot 2)
// TEMPLATE: GAMEMD 0x50F710
// DynamicVectorClass<HouseClass::BuildChoiceClass*>::FindItemIndex (slot 4)
template class VectorClass<HouseClass::BuildChoiceClass*>;
template class DynamicVectorClass<HouseClass::BuildChoiceClass*>;

GG_STATIC_ASSERT(sizeof(HouseClass::BuildChoiceClass*) == 4);
GG_STATIC_ASSERT(sizeof(VectorClass<HouseClass::BuildChoiceClass* >) == 0x10);
GG_STATIC_ASSERT(sizeof(DynamicVectorClass<HouseClass::BuildChoiceClass* >) == 0x18);
