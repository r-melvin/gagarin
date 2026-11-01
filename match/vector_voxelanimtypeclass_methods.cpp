// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Retail PAVVoxelAnimTypeClass RTTI establishes the pointer element type and zero-offset
// DynamicVectorClass -> VectorClass base chain. Complete entry-origin spans
// establish the bound methods. GX emits a short derived deleting wrapper;
// no GX reproduces its full retail body. No TypeList or constructor is bound;
// original TU boundaries, final link and complete object sizes are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
#include "vector_class_operations.h"
class VoxelAnimTypeClass;

// FUNCTION: GAMEMD 0x4E8FC0
// DynamicVectorClass<VoxelAnimTypeClass*>::Clear

// FUNCTION: GAMEMD 0x4E8FF0
// DynamicVectorClass<VoxelAnimTypeClass*>::Slot5

// FUNCTION: GAMEMD 0x4E9010
// VectorClass<VoxelAnimTypeClass*>::Slot6

// FUNCTION: GAMEMD 0x4EE6A0
// VectorClass<VoxelAnimTypeClass*>::operator==

// FUNCTION: GAMEMD 0x4EE6E0
// VectorClass<VoxelAnimTypeClass*>::SetCapacity

// FUNCTION: GAMEMD 0x4EE790
// VectorClass<VoxelAnimTypeClass*>::Clear

// FUNCTION: GAMEMD 0x4EE7C0
// VectorClass<VoxelAnimTypeClass*>::FindItemIndex

// FUNCTION: GAMEMD 0x4EE800
// VectorClass<VoxelAnimTypeClass*>::Slot5

// FUNCTION: GAMEMD 0x4EE820
// DynamicVectorClass<VoxelAnimTypeClass*>::SetCapacity

// FUNCTION: GAMEMD 0x4EE8D0
// DynamicVectorClass<VoxelAnimTypeClass*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x4F0B10
// VectorClass<VoxelAnimTypeClass*>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x4F0B60
// DynamicVectorClass<VoxelAnimTypeClass*>::scalar deleting destructor

// VTABLE: GAMEMD 0x7EA3C4 -- VectorClass<VoxelAnimTypeClass*>.
template class VectorClass<VoxelAnimTypeClass*>;
typedef VectorClass<VoxelAnimTypeClass*> GgVoxelAnimTypeClassVectorClass;
GG_STATIC_ASSERT(offsetof(GgVoxelAnimTypeClassVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgVoxelAnimTypeClassVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgVoxelAnimTypeClassVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgVoxelAnimTypeClassVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7EA3A4 -- DynamicVectorClass<VoxelAnimTypeClass*>.
template class DynamicVectorClass<VoxelAnimTypeClass*>;
typedef DynamicVectorClass<VoxelAnimTypeClass*> GgVoxelAnimTypeClassDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgVoxelAnimTypeClassDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgVoxelAnimTypeClassDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgVoxelAnimTypeClassDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgVoxelAnimTypeClassDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgVoxelAnimTypeClassDynamicVectorClass, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgVoxelAnimTypeClassDynamicVectorClass, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(VoxelAnimTypeClass*) == 4);
