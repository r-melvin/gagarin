// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Retail RTTI type descriptors name VectorClass<IsometricTileTypeClass::TileInsertType*> and
// DynamicVectorClass<IsometricTileTypeClass::TileInsertType*>; each address below is the vtable slot body
// of that specialization (slot owner read from the retail vtables).
// Pointer/scalar/enum element: no element layout is claimed.
#include "vector_class_operations.h"

class IsometricTileTypeClass {
public:
    struct TileInsertType;
};

// TEMPLATE: GAMEMD 0x54A220
// DynamicVectorClass<IsometricTileTypeClass::TileInsertType*>::Slot5 (slot 5)
// TEMPLATE: GAMEMD 0x54A240
// VectorClass<IsometricTileTypeClass::TileInsertType*>::Slot6 (slot 6)
// TEMPLATE: GAMEMD 0x54A4B0
// VectorClass<IsometricTileTypeClass::TileInsertType*>::operator== (slot 1)
// TEMPLATE: GAMEMD 0x54A4F0
// VectorClass<IsometricTileTypeClass::TileInsertType*>::SetCapacity (slot 2)
// TEMPLATE: GAMEMD 0x54A5D0
// VectorClass<IsometricTileTypeClass::TileInsertType*>::FindItemIndex (slot 4)
// TEMPLATE: GAMEMD 0x54A610
// VectorClass<IsometricTileTypeClass::TileInsertType*>::Slot5 (slot 5)
// TEMPLATE: GAMEMD 0x54A630
// DynamicVectorClass<IsometricTileTypeClass::TileInsertType*>::SetCapacity (slot 2)
// TEMPLATE: GAMEMD 0x54A6E0
// DynamicVectorClass<IsometricTileTypeClass::TileInsertType*>::FindItemIndex (slot 4)
template class VectorClass<IsometricTileTypeClass::TileInsertType*>;
template class DynamicVectorClass<IsometricTileTypeClass::TileInsertType*>;

GG_STATIC_ASSERT(sizeof(IsometricTileTypeClass::TileInsertType*) == 4);
GG_STATIC_ASSERT(sizeof(VectorClass<IsometricTileTypeClass::TileInsertType* >) == 0x10);
GG_STATIC_ASSERT(sizeof(DynamicVectorClass<IsometricTileTypeClass::TileInsertType* >) == 0x18);
