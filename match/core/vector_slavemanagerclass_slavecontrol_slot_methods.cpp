// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Retail RTTI type descriptors name VectorClass<SlaveManagerClass::SlaveControl*> and
// DynamicVectorClass<SlaveManagerClass::SlaveControl*>; each address below is the vtable slot body
// of that specialization (slot owner read from the retail vtables).
// Pointer/scalar/enum element: no element layout is claimed.
#include "vector_class_operations.h"

class SlaveManagerClass {
public:
    struct SlaveControl;
};

// TEMPLATE: GAMEMD 0x6B13E0
// DynamicVectorClass<SlaveManagerClass::SlaveControl*>::Slot5 (slot 5)
// TEMPLATE: GAMEMD 0x6B1400
// VectorClass<SlaveManagerClass::SlaveControl*>::Slot6 (slot 6)
// TEMPLATE: GAMEMD 0x6B1470
// VectorClass<SlaveManagerClass::SlaveControl*>::operator== (slot 1)
// TEMPLATE: GAMEMD 0x6B14B0
// VectorClass<SlaveManagerClass::SlaveControl*>::SetCapacity (slot 2)
// TEMPLATE: GAMEMD 0x6B1590
// VectorClass<SlaveManagerClass::SlaveControl*>::FindItemIndex (slot 4)
// TEMPLATE: GAMEMD 0x6B15D0
// VectorClass<SlaveManagerClass::SlaveControl*>::Slot5 (slot 5)
// TEMPLATE: GAMEMD 0x6B16A0
// DynamicVectorClass<SlaveManagerClass::SlaveControl*>::FindItemIndex (slot 4)
template class VectorClass<SlaveManagerClass::SlaveControl*>;
template class DynamicVectorClass<SlaveManagerClass::SlaveControl*>;

GG_STATIC_ASSERT(sizeof(SlaveManagerClass::SlaveControl*) == 4);
GG_STATIC_ASSERT(sizeof(VectorClass<SlaveManagerClass::SlaveControl* >) == 0x10);
GG_STATIC_ASSERT(sizeof(DynamicVectorClass<SlaveManagerClass::SlaveControl* >) == 0x18);
