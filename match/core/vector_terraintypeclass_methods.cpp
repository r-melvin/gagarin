// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT
// Retail PAVTerrainTypeClass RTTI establishes the pointer element type and zero-offset
// DynamicVectorClass -> VectorClass base chain. Complete entry-origin spans
// establish the bound methods. GX emits a short derived deleting wrapper;
// no GX reproduces its full retail body. No TypeList or constructor is bound;
// original TU boundaries, final link and complete object sizes are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
#include "vector_class_operations.h"
class TerrainTypeClass;

// FUNCTION: GAMEMD 0x4E8D20
// DynamicVectorClass<TerrainTypeClass*>::Clear

// FUNCTION: GAMEMD 0x4E8D50
// DynamicVectorClass<TerrainTypeClass*>::Slot5

// FUNCTION: GAMEMD 0x4E8D70
// VectorClass<TerrainTypeClass*>::Slot6

// FUNCTION: GAMEMD 0x4ED600
// VectorClass<TerrainTypeClass*>::operator==

// FUNCTION: GAMEMD 0x4ED640
// VectorClass<TerrainTypeClass*>::SetCapacity

// FUNCTION: GAMEMD 0x4ED6F0
// VectorClass<TerrainTypeClass*>::Clear

// FUNCTION: GAMEMD 0x4ED720
// VectorClass<TerrainTypeClass*>::FindItemIndex

// FUNCTION: GAMEMD 0x4ED760
// VectorClass<TerrainTypeClass*>::Slot5

// FUNCTION: GAMEMD 0x4ED780
// DynamicVectorClass<TerrainTypeClass*>::SetCapacity

// FUNCTION: GAMEMD 0x4ED830
// DynamicVectorClass<TerrainTypeClass*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x4F06B0
// VectorClass<TerrainTypeClass*>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x4F0700
// DynamicVectorClass<TerrainTypeClass*>::scalar deleting destructor

// VTABLE: GAMEMD 0x7EA204 -- VectorClass<TerrainTypeClass*>.
template class VectorClass<TerrainTypeClass*>;
typedef VectorClass<TerrainTypeClass*> GgTerrainTypeClassVectorClass;
GG_STATIC_ASSERT(offsetof(GgTerrainTypeClassVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgTerrainTypeClassVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgTerrainTypeClassVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgTerrainTypeClassVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7EA1E4 -- DynamicVectorClass<TerrainTypeClass*>.
template class DynamicVectorClass<TerrainTypeClass*>;
typedef DynamicVectorClass<TerrainTypeClass*> GgTerrainTypeClassDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgTerrainTypeClassDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgTerrainTypeClassDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgTerrainTypeClassDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgTerrainTypeClassDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgTerrainTypeClassDynamicVectorClass, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgTerrainTypeClassDynamicVectorClass, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(TerrainTypeClass*) == 4);
