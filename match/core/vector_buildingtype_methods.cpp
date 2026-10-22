// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy
// Raw PBVBuildingTypeClass RTTI identifies const pointer elements and the
// TypeList -> DynamicVectorClass -> VectorClass zero-offset base chain.
// Complete entry-origin spans establish all bound methods. GX emits shorter
// derived deleting wrappers; no GX reproduces the retail 0x49-byte bodies.
// Original TU boundaries, final link and complete TypeList size are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
#include "vector_class_operations.h"
#include "type_list.h"
class BuildingTypeClass;

// FUNCTION: GAMEMD 0x50E4A0
// DynamicVectorClass<const BuildingTypeClass*>::Clear

// FUNCTION: GAMEMD 0x50E4D0
// DynamicVectorClass<const BuildingTypeClass*>::Slot5

// FUNCTION: GAMEMD 0x50E4F0
// VectorClass<const BuildingTypeClass*>::Slot6

// FUNCTION: GAMEMD 0x50E910
// VectorClass<const BuildingTypeClass*>::operator==

// FUNCTION: GAMEMD 0x50E950
// VectorClass<const BuildingTypeClass*>::SetCapacity

// FUNCTION: GAMEMD 0x50EA00
// VectorClass<const BuildingTypeClass*>::Clear

// FUNCTION: GAMEMD 0x50EA30
// VectorClass<const BuildingTypeClass*>::FindItemIndex

// FUNCTION: GAMEMD 0x50EA70
// VectorClass<const BuildingTypeClass*>::Slot5

// FUNCTION: GAMEMD 0x50EA90
// DynamicVectorClass<const BuildingTypeClass*>::SetCapacity

// FUNCTION: GAMEMD 0x50EB40
// DynamicVectorClass<const BuildingTypeClass*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x50FFF0
// VectorClass<const BuildingTypeClass*>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x510040
// DynamicVectorClass<const BuildingTypeClass*>::scalar deleting destructor

// FUNCTION: GAMEMD 0x5105A0
// VectorClass<const BuildingTypeClass*>::capacity constructor

// FUNCTION: GAMEMD 0x5AC400
// TypeList<const BuildingTypeClass*>::default constructor

// SYNTHETIC: GAMEMD 0x5AC650
// TypeList<const BuildingTypeClass*>::scalar deleting destructor

// FUNCTION: GAMEMD 0x5AC900
// DynamicVectorClass<const BuildingTypeClass*>::capacity constructor

// FUNCTION: GAMEMD 0x5AD660
// TypeList<const BuildingTypeClass*>::copy constructor

// VTABLE: GAMEMD 0x7EAA08 -- VectorClass<const BuildingTypeClass*>.
template class VectorClass<const BuildingTypeClass*>;
typedef VectorClass<const BuildingTypeClass*> GgBuildingTypeVectorClass;
GG_STATIC_ASSERT(offsetof(GgBuildingTypeVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgBuildingTypeVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgBuildingTypeVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgBuildingTypeVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7EAA28 -- DynamicVectorClass<const BuildingTypeClass*>.
template class DynamicVectorClass<const BuildingTypeClass*>;
typedef DynamicVectorClass<const BuildingTypeClass*> GgBuildingTypeDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgBuildingTypeDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgBuildingTypeDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgBuildingTypeDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgBuildingTypeDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgBuildingTypeDynamicVectorClass, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgBuildingTypeDynamicVectorClass, CapacityIncrement) == 0x14);

// VTABLE: GAMEMD 0x7ED90C -- TypeList<const BuildingTypeClass*>.
template class TypeList<const BuildingTypeClass*>;
typedef TypeList<const BuildingTypeClass*> GgBuildingTypeTypeList;
GG_STATIC_ASSERT(offsetof(GgBuildingTypeTypeList, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgBuildingTypeTypeList, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgBuildingTypeTypeList, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgBuildingTypeTypeList, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgBuildingTypeTypeList, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgBuildingTypeTypeList, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(const BuildingTypeClass*) == 4);
