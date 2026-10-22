// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy
// Raw PBVTerrainTypeClass RTTI identifies const pointer elements and the
// TypeList -> DynamicVectorClass -> VectorClass zero-offset base chain.
// Complete entry-origin spans establish all bound methods. GX emits shorter
// derived deleting wrappers; no GX reproduces the retail 0x49-byte bodies.
// Original TU boundaries, final link and complete TypeList size are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
#include "vector_class_operations.h"
#include "type_list.h"
class TerrainTypeClass;

// FUNCTION: GAMEMD 0x67A8B0
// TypeList<const TerrainTypeClass*>::default constructor

// FUNCTION: GAMEMD 0x67A930
// DynamicVectorClass<const TerrainTypeClass*>::Clear

// FUNCTION: GAMEMD 0x67A960
// DynamicVectorClass<const TerrainTypeClass*>::Slot5

// FUNCTION: GAMEMD 0x67A980
// VectorClass<const TerrainTypeClass*>::Slot6

// SYNTHETIC: GAMEMD 0x67AA30
// TypeList<const TerrainTypeClass*>::scalar deleting destructor

// FUNCTION: GAMEMD 0x67B1F0
// VectorClass<const TerrainTypeClass*>::operator==

// FUNCTION: GAMEMD 0x67B230
// VectorClass<const TerrainTypeClass*>::SetCapacity

// FUNCTION: GAMEMD 0x67B2E0
// VectorClass<const TerrainTypeClass*>::Clear

// FUNCTION: GAMEMD 0x67B310
// VectorClass<const TerrainTypeClass*>::FindItemIndex

// FUNCTION: GAMEMD 0x67B350
// VectorClass<const TerrainTypeClass*>::Slot5

// FUNCTION: GAMEMD 0x67B370
// DynamicVectorClass<const TerrainTypeClass*>::capacity constructor

// FUNCTION: GAMEMD 0x67B3D0
// DynamicVectorClass<const TerrainTypeClass*>::SetCapacity

// FUNCTION: GAMEMD 0x67B4D0
// DynamicVectorClass<const TerrainTypeClass*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x67C150
// VectorClass<const TerrainTypeClass*>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x67C1A0
// DynamicVectorClass<const TerrainTypeClass*>::scalar deleting destructor

// FUNCTION: GAMEMD 0x67C430
// VectorClass<const TerrainTypeClass*>::capacity constructor

// VTABLE: GAMEMD 0x7F0D9C -- VectorClass<const TerrainTypeClass*>.
template class VectorClass<const TerrainTypeClass*>;
typedef VectorClass<const TerrainTypeClass*> GgTerrainTypeVectorClass;
GG_STATIC_ASSERT(offsetof(GgTerrainTypeVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgTerrainTypeVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgTerrainTypeVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgTerrainTypeVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7F0E0C -- DynamicVectorClass<const TerrainTypeClass*>.
template class DynamicVectorClass<const TerrainTypeClass*>;
typedef DynamicVectorClass<const TerrainTypeClass*> GgTerrainTypeDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgTerrainTypeDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgTerrainTypeDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgTerrainTypeDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgTerrainTypeDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgTerrainTypeDynamicVectorClass, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgTerrainTypeDynamicVectorClass, CapacityIncrement) == 0x14);

// VTABLE: GAMEMD 0x7F0CFC -- TypeList<const TerrainTypeClass*>.
template class TypeList<const TerrainTypeClass*>;
typedef TypeList<const TerrainTypeClass*> GgTerrainTypeTypeList;
GG_STATIC_ASSERT(offsetof(GgTerrainTypeTypeList, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgTerrainTypeTypeList, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgTerrainTypeTypeList, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgTerrainTypeTypeList, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgTerrainTypeTypeList, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgTerrainTypeTypeList, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(const TerrainTypeClass*) == 4);
