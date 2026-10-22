// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Retail RTTI type descriptors name VectorClass<MultiplayerGameMode*> and
// DynamicVectorClass<MultiplayerGameMode*>; each address below is the vtable slot body
// of that specialization (slot owner read from the retail vtables).
// Pointer/scalar/enum element: no element layout is claimed.
#include "vector_class_operations.h"

class MultiplayerGameMode;

// TEMPLATE: GAMEMD 0x5D8140
// DynamicVectorClass<MultiplayerGameMode*>::Slot5 (slot 5)
// TEMPLATE: GAMEMD 0x5D8160
// VectorClass<MultiplayerGameMode*>::Slot6 (slot 6)
// TEMPLATE: GAMEMD 0x5D8550
// VectorClass<MultiplayerGameMode*>::operator== (slot 1)
// TEMPLATE: GAMEMD 0x5D8590
// VectorClass<MultiplayerGameMode*>::SetCapacity (slot 2)
// TEMPLATE: GAMEMD 0x5D8670
// VectorClass<MultiplayerGameMode*>::FindItemIndex (slot 4)
// TEMPLATE: GAMEMD 0x5D86B0
// VectorClass<MultiplayerGameMode*>::Slot5 (slot 5)
// TEMPLATE: GAMEMD 0x5D87E0
// DynamicVectorClass<MultiplayerGameMode*>::FindItemIndex (slot 4)
template class VectorClass<MultiplayerGameMode*>;
template class DynamicVectorClass<MultiplayerGameMode*>;

GG_STATIC_ASSERT(sizeof(MultiplayerGameMode*) == 4);
GG_STATIC_ASSERT(sizeof(VectorClass<MultiplayerGameMode* >) == 0x10);
GG_STATIC_ASSERT(sizeof(DynamicVectorClass<MultiplayerGameMode* >) == 0x18);
