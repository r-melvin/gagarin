// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /DNDEBUG /Gy
// Retail PAVBuildingTypeClass RTTI establishes the pointer element type and zero-offset
// DynamicVectorClass -> VectorClass base chain. Complete entry-origin spans
// establish the bound methods. GX emits a short derived deleting wrapper;
// no GX reproduces its full retail body. No TypeList or constructor is bound;
// original TU boundaries, final link and complete object sizes are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
#include "vector_class_operations.h"
class BuildingTypeClass;

// FUNCTION: GAMEMD 0x4E8D80
// DynamicVectorClass<BuildingTypeClass*>::Clear

// FUNCTION: GAMEMD 0x4E8DB0
// DynamicVectorClass<BuildingTypeClass*>::Slot5

// FUNCTION: GAMEMD 0x4E8DD0
// VectorClass<BuildingTypeClass*>::Slot6

// FUNCTION: GAMEMD 0x4ED860
// VectorClass<BuildingTypeClass*>::operator==

// FUNCTION: GAMEMD 0x4ED8A0
// VectorClass<BuildingTypeClass*>::SetCapacity

// FUNCTION: GAMEMD 0x4ED950
// VectorClass<BuildingTypeClass*>::Clear

// FUNCTION: GAMEMD 0x4ED980
// VectorClass<BuildingTypeClass*>::FindItemIndex

// FUNCTION: GAMEMD 0x4ED9C0
// VectorClass<BuildingTypeClass*>::Slot5

// FUNCTION: GAMEMD 0x4ED9E0
// DynamicVectorClass<BuildingTypeClass*>::SetCapacity

// FUNCTION: GAMEMD 0x4EDA90
// DynamicVectorClass<BuildingTypeClass*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x4F0750
// VectorClass<BuildingTypeClass*>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x4F07A0
// DynamicVectorClass<BuildingTypeClass*>::scalar deleting destructor

// VTABLE: GAMEMD 0x7EA244 -- VectorClass<BuildingTypeClass*>.
template class VectorClass<BuildingTypeClass*>;
typedef VectorClass<BuildingTypeClass*> GgBuildingTypeClassVectorClass;
GG_STATIC_ASSERT(offsetof(GgBuildingTypeClassVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgBuildingTypeClassVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgBuildingTypeClassVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgBuildingTypeClassVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7EA224 -- DynamicVectorClass<BuildingTypeClass*>.
template class DynamicVectorClass<BuildingTypeClass*>;
typedef DynamicVectorClass<BuildingTypeClass*> GgBuildingTypeClassDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgBuildingTypeClassDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgBuildingTypeClassDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgBuildingTypeClassDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgBuildingTypeClassDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgBuildingTypeClassDynamicVectorClass, ActiveCount) == 0x10);
GG_STATIC_ASSERT(offsetof(GgBuildingTypeClassDynamicVectorClass, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(BuildingTypeClass*) == 4);
