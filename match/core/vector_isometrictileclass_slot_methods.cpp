// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Retail RTTI type descriptors name VectorClass<IsometricTileClass*> and
// DynamicVectorClass<IsometricTileClass*>; each address below is the vtable slot body
// of that specialization (slot owner read from the retail vtables).
// Pointer/scalar/enum element: no element layout is claimed.
#include "vector_class_operations.h"

class IsometricTileClass;

// TEMPLATE: GAMEMD 0x40C850
// DynamicVectorClass<IsometricTileClass*>::Slot5 (slot 5)
// TEMPLATE: GAMEMD 0x40C870
// VectorClass<IsometricTileClass*>::Slot6 (slot 6)
// TEMPLATE: GAMEMD 0x40C880
// VectorClass<IsometricTileClass*>::operator== (slot 1)
// TEMPLATE: GAMEMD 0x40C8C0
// VectorClass<IsometricTileClass*>::SetCapacity (slot 2)
// TEMPLATE: GAMEMD 0x40C9A0
// VectorClass<IsometricTileClass*>::FindItemIndex (slot 4)
// TEMPLATE: GAMEMD 0x40C9E0
// VectorClass<IsometricTileClass*>::Slot5 (slot 5)
// TEMPLATE: GAMEMD 0x40CA00
// DynamicVectorClass<IsometricTileClass*>::SetCapacity (slot 2)
// TEMPLATE: GAMEMD 0x40CAB0
// DynamicVectorClass<IsometricTileClass*>::FindItemIndex (slot 4)
template class VectorClass<IsometricTileClass*>;
template class DynamicVectorClass<IsometricTileClass*>;

GG_STATIC_ASSERT(sizeof(IsometricTileClass*) == 4);
GG_STATIC_ASSERT(sizeof(VectorClass<IsometricTileClass* >) == 0x10);
GG_STATIC_ASSERT(sizeof(DynamicVectorClass<IsometricTileClass* >) == 0x18);
