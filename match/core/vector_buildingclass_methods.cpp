// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy
// Retail PAVBuildingClass RTTI establishes the pointer element type and zero-offset
// DynamicVectorClass -> VectorClass base chain. Complete entry-origin spans
// establish the bound methods. GX emits a short derived deleting wrapper;
// no GX reproduces its full retail body. No TypeList or constructor is bound;
// original TU boundaries, final link and complete object sizes are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
#include "vector_class_operations.h"
class BuildingClass;

// FUNCTION: GAMEMD 0x4E82F0
// DynamicVectorClass<BuildingClass*>::Clear

// FUNCTION: GAMEMD 0x4E8320
// DynamicVectorClass<BuildingClass*>::Slot5

// FUNCTION: GAMEMD 0x4E8340
// VectorClass<BuildingClass*>::Slot6

// FUNCTION: GAMEMD 0x4E9460
// VectorClass<BuildingClass*>::operator==

// FUNCTION: GAMEMD 0x4E94A0
// VectorClass<BuildingClass*>::SetCapacity

// FUNCTION: GAMEMD 0x4E9550
// VectorClass<BuildingClass*>::Clear

// FUNCTION: GAMEMD 0x4E9580
// VectorClass<BuildingClass*>::FindItemIndex

// FUNCTION: GAMEMD 0x4E95C0
// VectorClass<BuildingClass*>::Slot5

// FUNCTION: GAMEMD 0x4E95E0
// DynamicVectorClass<BuildingClass*>::SetCapacity

// FUNCTION: GAMEMD 0x4E9690
// DynamicVectorClass<BuildingClass*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x4EF580
// VectorClass<BuildingClass*>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x4EF5D0
// DynamicVectorClass<BuildingClass*>::scalar deleting destructor

// VTABLE: GAMEMD 0x7E9E44 -- VectorClass<BuildingClass*>.
template class VectorClass<BuildingClass*>;
typedef VectorClass<BuildingClass*> GgBuildingClassVectorClass;
GG_STATIC_ASSERT(offsetof(GgBuildingClassVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgBuildingClassVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgBuildingClassVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgBuildingClassVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7E9E24 -- DynamicVectorClass<BuildingClass*>.
template class DynamicVectorClass<BuildingClass*>;
typedef DynamicVectorClass<BuildingClass*> GgBuildingClassDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgBuildingClassDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgBuildingClassDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgBuildingClassDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgBuildingClassDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgBuildingClassDynamicVectorClass, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgBuildingClassDynamicVectorClass, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(BuildingClass*) == 4);
