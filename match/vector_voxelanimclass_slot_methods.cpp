// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Retail RTTI type descriptors name VectorClass<VoxelAnimClass*> and
// DynamicVectorClass<VoxelAnimClass*>; each address below is the vtable slot body
// of that specialization (slot owner read from the retail vtables).
// Pointer/scalar/enum element: no element layout is claimed.
#include "vector_class_operations.h"

class VoxelAnimClass;

// TEMPLATE: GAMEMD 0x40EEF0
// DynamicVectorClass<VoxelAnimClass*>::Slot5 (slot 5)
// TEMPLATE: GAMEMD 0x40EF10
// VectorClass<VoxelAnimClass*>::Slot6 (slot 6)
// TEMPLATE: GAMEMD 0x40EF20
// VectorClass<VoxelAnimClass*>::operator== (slot 1)
// TEMPLATE: GAMEMD 0x40EF60
// VectorClass<VoxelAnimClass*>::SetCapacity (slot 2)
// TEMPLATE: GAMEMD 0x40F040
// VectorClass<VoxelAnimClass*>::FindItemIndex (slot 4)
// TEMPLATE: GAMEMD 0x40F080
// VectorClass<VoxelAnimClass*>::Slot5 (slot 5)
// TEMPLATE: GAMEMD 0x40F0A0
// DynamicVectorClass<VoxelAnimClass*>::SetCapacity (slot 2)
// TEMPLATE: GAMEMD 0x40F150
// DynamicVectorClass<VoxelAnimClass*>::FindItemIndex (slot 4)
template class VectorClass<VoxelAnimClass*>;
template class DynamicVectorClass<VoxelAnimClass*>;

GG_STATIC_ASSERT(sizeof(VoxelAnimClass*) == 4);
GG_STATIC_ASSERT(sizeof(VectorClass<VoxelAnimClass* >) == 0x10);
GG_STATIC_ASSERT(sizeof(DynamicVectorClass<VoxelAnimClass* >) == 0x18);
