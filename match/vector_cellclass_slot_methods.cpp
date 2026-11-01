// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Retail RTTI type descriptors name VectorClass<CellClass*> and
// DynamicVectorClass<CellClass*>; each address below is the vtable slot body
// of that specialization (slot owner read from the retail vtables).
// Pointer/scalar/enum element: no element layout is claimed.
#include "vector_class_operations.h"

class CellClass;

// TEMPLATE: GAMEMD 0x589CE0
// VectorClass<CellClass*>::SetCapacity (slot 2)
// TEMPLATE: GAMEMD 0x5AC5D0
// DynamicVectorClass<CellClass*>::Slot5 (slot 5)
// TEMPLATE: GAMEMD 0x5AD0C0
// DynamicVectorClass<CellClass*>::FindItemIndex (slot 4)
template class VectorClass<CellClass*>;
template class DynamicVectorClass<CellClass*>;

GG_STATIC_ASSERT(sizeof(CellClass*) == 4);
GG_STATIC_ASSERT(sizeof(VectorClass<CellClass* >) == 0x10);
GG_STATIC_ASSERT(sizeof(DynamicVectorClass<CellClass* >) == 0x18);
