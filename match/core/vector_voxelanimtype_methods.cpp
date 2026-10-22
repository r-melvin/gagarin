// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy
// Raw PBVVoxelAnimTypeClass RTTI identifies const pointer elements and the
// TypeList -> DynamicVectorClass -> VectorClass zero-offset base chain.
// Complete entry-origin spans establish all bound methods. GX emits shorter
// derived deleting wrappers; no GX reproduces the retail 0x49-byte bodies.
// Original TU boundaries, final link and complete TypeList size are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
#include "vector_class_operations.h"
#include "type_list.h"
class VoxelAnimTypeClass;

// FUNCTION: GAMEMD 0x67A390
// TypeList<const VoxelAnimTypeClass*>::default constructor

// FUNCTION: GAMEMD 0x67A410
// DynamicVectorClass<const VoxelAnimTypeClass*>::Clear

// FUNCTION: GAMEMD 0x67A440
// DynamicVectorClass<const VoxelAnimTypeClass*>::Slot5

// FUNCTION: GAMEMD 0x67A460
// VectorClass<const VoxelAnimTypeClass*>::Slot6

// SYNTHETIC: GAMEMD 0x67A990
// TypeList<const VoxelAnimTypeClass*>::scalar deleting destructor

// FUNCTION: GAMEMD 0x67AAF0
// VectorClass<const VoxelAnimTypeClass*>::operator==

// FUNCTION: GAMEMD 0x67AB30
// VectorClass<const VoxelAnimTypeClass*>::SetCapacity

// FUNCTION: GAMEMD 0x67ABE0
// VectorClass<const VoxelAnimTypeClass*>::Clear

// FUNCTION: GAMEMD 0x67AC10
// VectorClass<const VoxelAnimTypeClass*>::FindItemIndex

// FUNCTION: GAMEMD 0x67AC50
// VectorClass<const VoxelAnimTypeClass*>::Slot5

// FUNCTION: GAMEMD 0x67AC70
// DynamicVectorClass<const VoxelAnimTypeClass*>::capacity constructor

// FUNCTION: GAMEMD 0x67ACD0
// DynamicVectorClass<const VoxelAnimTypeClass*>::SetCapacity

// FUNCTION: GAMEMD 0x67ADD0
// DynamicVectorClass<const VoxelAnimTypeClass*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x67C010
// VectorClass<const VoxelAnimTypeClass*>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x67C060
// DynamicVectorClass<const VoxelAnimTypeClass*>::scalar deleting destructor

// FUNCTION: GAMEMD 0x67C1F0
// TypeList<const VoxelAnimTypeClass*>::copy constructor

// FUNCTION: GAMEMD 0x67C310
// VectorClass<const VoxelAnimTypeClass*>::capacity constructor

// FUNCTION: GAMEMD 0x75E6B0
// DynamicVectorClass<const VoxelAnimTypeClass*>::copy constructor

// VTABLE: GAMEMD 0x7F0D5C -- VectorClass<const VoxelAnimTypeClass*>.
template class VectorClass<const VoxelAnimTypeClass*>;
typedef VectorClass<const VoxelAnimTypeClass*> GgVoxelAnimTypeVectorClass;
GG_STATIC_ASSERT(offsetof(GgVoxelAnimTypeVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgVoxelAnimTypeVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgVoxelAnimTypeVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgVoxelAnimTypeVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7F0DCC -- DynamicVectorClass<const VoxelAnimTypeClass*>.
template class DynamicVectorClass<const VoxelAnimTypeClass*>;
typedef DynamicVectorClass<const VoxelAnimTypeClass*> GgVoxelAnimTypeDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgVoxelAnimTypeDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgVoxelAnimTypeDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgVoxelAnimTypeDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgVoxelAnimTypeDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgVoxelAnimTypeDynamicVectorClass, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgVoxelAnimTypeDynamicVectorClass, CapacityIncrement) == 0x14);

// VTABLE: GAMEMD 0x7F0D3C -- TypeList<const VoxelAnimTypeClass*>.
template class TypeList<const VoxelAnimTypeClass*>;
typedef TypeList<const VoxelAnimTypeClass*> GgVoxelAnimTypeTypeList;
GG_STATIC_ASSERT(offsetof(GgVoxelAnimTypeTypeList, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgVoxelAnimTypeTypeList, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgVoxelAnimTypeTypeList, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgVoxelAnimTypeTypeList, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgVoxelAnimTypeTypeList, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgVoxelAnimTypeTypeList, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(const VoxelAnimTypeClass*) == 4);
