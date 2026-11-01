// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Raw PBVUnitTypeClass RTTI identifies const pointer elements and the
// TypeList -> DynamicVectorClass -> VectorClass zero-offset base chain.
// Complete entry-origin spans establish all bound methods. GX emits shorter
// derived deleting wrappers; no GX reproduces the retail 0x49-byte bodies.
// Original TU boundaries, final link and complete TypeList size are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
#include "vector_class_operations.h"
#include "type_list.h"
class UnitTypeClass;

// FUNCTION: GAMEMD 0x512900
// DynamicVectorClass<const UnitTypeClass*>::Clear

// FUNCTION: GAMEMD 0x512930
// DynamicVectorClass<const UnitTypeClass*>::Slot5

// FUNCTION: GAMEMD 0x512950
// VectorClass<const UnitTypeClass*>::Slot6

// SYNTHETIC: GAMEMD 0x512A40
// TypeList<const UnitTypeClass*>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x512B30
// VectorClass<const UnitTypeClass*>::scalar deleting destructor

// FUNCTION: GAMEMD 0x513010
// VectorClass<const UnitTypeClass*>::operator==

// FUNCTION: GAMEMD 0x513050
// VectorClass<const UnitTypeClass*>::SetCapacity

// FUNCTION: GAMEMD 0x513100
// VectorClass<const UnitTypeClass*>::Clear

// FUNCTION: GAMEMD 0x513130
// VectorClass<const UnitTypeClass*>::FindItemIndex

// FUNCTION: GAMEMD 0x513170
// VectorClass<const UnitTypeClass*>::Slot5

// FUNCTION: GAMEMD 0x513190
// DynamicVectorClass<const UnitTypeClass*>::capacity constructor

// SYNTHETIC: GAMEMD 0x5131F0
// DynamicVectorClass<const UnitTypeClass*>::scalar deleting destructor

// FUNCTION: GAMEMD 0x513240
// DynamicVectorClass<const UnitTypeClass*>::SetCapacity

// FUNCTION: GAMEMD 0x513340
// DynamicVectorClass<const UnitTypeClass*>::FindItemIndex

// FUNCTION: GAMEMD 0x513740
// TypeList<const UnitTypeClass*>::copy constructor

// FUNCTION: GAMEMD 0x513940
// VectorClass<const UnitTypeClass*>::capacity constructor

// FUNCTION: GAMEMD 0x67A740
// TypeList<const UnitTypeClass*>::default constructor

// VTABLE: GAMEMD 0x7EAC48 -- VectorClass<const UnitTypeClass*>.
template class VectorClass<const UnitTypeClass*>;
typedef VectorClass<const UnitTypeClass*> GgUnittypeVectorClass;
GG_STATIC_ASSERT(offsetof(GgUnittypeVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgUnittypeVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgUnittypeVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgUnittypeVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7EACA8 -- DynamicVectorClass<const UnitTypeClass*>.
template class DynamicVectorClass<const UnitTypeClass*>;
typedef DynamicVectorClass<const UnitTypeClass*> GgUnittypeDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgUnittypeDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgUnittypeDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgUnittypeDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgUnittypeDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgUnittypeDynamicVectorClass, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgUnittypeDynamicVectorClass, CapacityIncrement) == 0x14);

// VTABLE: GAMEMD 0x7EABE8 -- TypeList<const UnitTypeClass*>.
template class TypeList<const UnitTypeClass*>;
typedef TypeList<const UnitTypeClass*> GgUnittypeTypeList;
GG_STATIC_ASSERT(offsetof(GgUnittypeTypeList, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgUnittypeTypeList, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgUnittypeTypeList, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgUnittypeTypeList, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgUnittypeTypeList, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgUnittypeTypeList, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(const UnitTypeClass*) == 4);
