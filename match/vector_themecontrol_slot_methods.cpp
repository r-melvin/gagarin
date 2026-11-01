// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Retail RTTI type descriptors name VectorClass<ThemeControl*> and
// DynamicVectorClass<ThemeControl*>; each address below is the vtable slot body
// of that specialization (slot owner read from the retail vtables).
// Pointer/scalar/enum element: no element layout is claimed.
#include "vector_class_operations.h"

struct ThemeControl;

// TEMPLATE: GAMEMD 0x4E8530
// VectorClass<ThemeControl*>::Slot6 (slot 6)
// TEMPLATE: GAMEMD 0x4EA2A0
// VectorClass<ThemeControl*>::operator== (slot 1)
// TEMPLATE: GAMEMD 0x4EA2E0
// VectorClass<ThemeControl*>::SetCapacity (slot 2)
// TEMPLATE: GAMEMD 0x4EA3C0
// VectorClass<ThemeControl*>::FindItemIndex (slot 4)
// TEMPLATE: GAMEMD 0x4EA400
// VectorClass<ThemeControl*>::Slot5 (slot 5)
// TEMPLATE: GAMEMD 0x7212E0
// DynamicVectorClass<ThemeControl*>::Slot5 (slot 5)
// TEMPLATE: GAMEMD 0x721300
// DynamicVectorClass<ThemeControl*>::SetCapacity (slot 2)
// TEMPLATE: GAMEMD 0x7213B0
// DynamicVectorClass<ThemeControl*>::FindItemIndex (slot 4)
template class VectorClass<ThemeControl*>;
template class DynamicVectorClass<ThemeControl*>;

GG_STATIC_ASSERT(sizeof(ThemeControl*) == 4);
GG_STATIC_ASSERT(sizeof(VectorClass<ThemeControl* >) == 0x10);
GG_STATIC_ASSERT(sizeof(DynamicVectorClass<ThemeControl* >) == 0x18);
