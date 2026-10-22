// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /DNDEBUG /Gy
// Retail PAVBuildingLightClass RTTI establishes the pointer element type and zero-offset
// DynamicVectorClass -> VectorClass base chain. Complete entry-origin spans
// establish the bound methods. GX emits a short derived deleting wrapper;
// no GX reproduces its full retail body. No TypeList or constructor is bound;
// original TU boundaries, final link and complete object sizes are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
#include "vector_class_operations.h"

class BuildingLightClass;

// FUNCTION: GAMEMD 0x4E8410
// DynamicVectorClass<BuildingLightClass*>::Clear

// FUNCTION: GAMEMD 0x4E8440
// DynamicVectorClass<BuildingLightClass*>::Slot5

// FUNCTION: GAMEMD 0x4E8460
// VectorClass<BuildingLightClass*>::Slot6

// FUNCTION: GAMEMD 0x4E9B80
// VectorClass<BuildingLightClass*>::operator==

// FUNCTION: GAMEMD 0x4E9BC0
// VectorClass<BuildingLightClass*>::SetCapacity

// FUNCTION: GAMEMD 0x4E9C70
// VectorClass<BuildingLightClass*>::Clear

// FUNCTION: GAMEMD 0x4E9CA0
// VectorClass<BuildingLightClass*>::FindItemIndex

// FUNCTION: GAMEMD 0x4E9CE0
// VectorClass<BuildingLightClass*>::Slot5

// FUNCTION: GAMEMD 0x4E9D00
// DynamicVectorClass<BuildingLightClass*>::SetCapacity

// FUNCTION: GAMEMD 0x4E9DB0
// DynamicVectorClass<BuildingLightClass*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x4EF760
// VectorClass<BuildingLightClass*>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x4EF7B0
// DynamicVectorClass<BuildingLightClass*>::scalar deleting destructor

// VTABLE: GAMEMD 0x7E9C44 -- VectorClass<BuildingLightClass*>.
template class VectorClass<BuildingLightClass*>;
typedef VectorClass<BuildingLightClass*> GgBuildingLightClassVectorClass;
GG_STATIC_ASSERT(offsetof(GgBuildingLightClassVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgBuildingLightClassVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgBuildingLightClassVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgBuildingLightClassVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7E9C24 -- DynamicVectorClass<BuildingLightClass*>.
template class DynamicVectorClass<BuildingLightClass*>;
typedef DynamicVectorClass<BuildingLightClass*> GgBuildingLightClassDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgBuildingLightClassDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgBuildingLightClassDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgBuildingLightClassDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgBuildingLightClassDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgBuildingLightClassDynamicVectorClass, ActiveCount) == 0x10);
GG_STATIC_ASSERT(offsetof(GgBuildingLightClassDynamicVectorClass, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(BuildingLightClass*) == 4);
