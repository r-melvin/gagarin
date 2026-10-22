// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy
// Retail PAVTerrainClass RTTI establishes the pointer element type and zero-offset
// DynamicVectorClass -> VectorClass base chain. Complete entry-origin spans
// establish the bound methods. GX emits a short derived deleting wrapper;
// no GX reproduces its full retail body. No TypeList or constructor is bound;
// original TU boundaries, final link and complete object sizes are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
#include "vector_class_operations.h"
class TerrainClass;

// FUNCTION: GAMEMD 0x4E87E0
// DynamicVectorClass<TerrainClass*>::Clear

// FUNCTION: GAMEMD 0x4E8810
// DynamicVectorClass<TerrainClass*>::Slot5

// FUNCTION: GAMEMD 0x4E8830
// VectorClass<TerrainClass*>::Slot6

// FUNCTION: GAMEMD 0x4EB4C0
// VectorClass<TerrainClass*>::operator==

// FUNCTION: GAMEMD 0x4EB500
// VectorClass<TerrainClass*>::SetCapacity

// FUNCTION: GAMEMD 0x4EB5B0
// VectorClass<TerrainClass*>::Clear

// FUNCTION: GAMEMD 0x4EB5E0
// VectorClass<TerrainClass*>::FindItemIndex

// FUNCTION: GAMEMD 0x4EB620
// VectorClass<TerrainClass*>::Slot5

// FUNCTION: GAMEMD 0x4EB640
// DynamicVectorClass<TerrainClass*>::SetCapacity

// FUNCTION: GAMEMD 0x4EB6F0
// DynamicVectorClass<TerrainClass*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x4EFDF0
// VectorClass<TerrainClass*>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x4EFE40
// DynamicVectorClass<TerrainClass*>::scalar deleting destructor

// VTABLE: GAMEMD 0x7E9E04 -- VectorClass<TerrainClass*>.
template class VectorClass<TerrainClass*>;
typedef VectorClass<TerrainClass*> GgTerrainClassVectorClass;
GG_STATIC_ASSERT(offsetof(GgTerrainClassVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgTerrainClassVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgTerrainClassVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgTerrainClassVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7E9DE4 -- DynamicVectorClass<TerrainClass*>.
template class DynamicVectorClass<TerrainClass*>;
typedef DynamicVectorClass<TerrainClass*> GgTerrainClassDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgTerrainClassDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgTerrainClassDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgTerrainClassDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgTerrainClassDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgTerrainClassDynamicVectorClass, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgTerrainClassDynamicVectorClass, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(TerrainClass*) == 4);
