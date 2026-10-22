// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /DNDEBUG /Gy
// Raw PBVInfantryTypeClass RTTI identifies const pointer elements and the
// TypeList -> DynamicVectorClass -> VectorClass zero-offset base chain.
// Complete entry-origin spans establish all bound methods. GX emits shorter
// derived deleting wrappers; no GX reproduces the retail 0x49-byte bodies.
// Original TU boundaries, final link and complete TypeList size are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
#include "vector_class_operations.h"
#include "type_list.h"
class InfantryTypeClass;

// FUNCTION: GAMEMD 0x5128A0
// DynamicVectorClass<const InfantryTypeClass*>::Clear

// FUNCTION: GAMEMD 0x5128D0
// DynamicVectorClass<const InfantryTypeClass*>::Slot5

// FUNCTION: GAMEMD 0x5128F0
// VectorClass<const InfantryTypeClass*>::Slot6

// SYNTHETIC: GAMEMD 0x5129F0
// TypeList<const InfantryTypeClass*>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x512AE0
// VectorClass<const InfantryTypeClass*>::scalar deleting destructor

// FUNCTION: GAMEMD 0x512C40
// VectorClass<const InfantryTypeClass*>::operator==

// FUNCTION: GAMEMD 0x512C80
// VectorClass<const InfantryTypeClass*>::SetCapacity

// FUNCTION: GAMEMD 0x512D30
// VectorClass<const InfantryTypeClass*>::Clear

// FUNCTION: GAMEMD 0x512D60
// VectorClass<const InfantryTypeClass*>::FindItemIndex

// FUNCTION: GAMEMD 0x512DA0
// VectorClass<const InfantryTypeClass*>::Slot5

// FUNCTION: GAMEMD 0x512DC0
// DynamicVectorClass<const InfantryTypeClass*>::capacity constructor

// SYNTHETIC: GAMEMD 0x512E20
// DynamicVectorClass<const InfantryTypeClass*>::scalar deleting destructor

// FUNCTION: GAMEMD 0x512E70
// DynamicVectorClass<const InfantryTypeClass*>::SetCapacity

// FUNCTION: GAMEMD 0x512F70
// DynamicVectorClass<const InfantryTypeClass*>::FindItemIndex

// FUNCTION: GAMEMD 0x513860
// DynamicVectorClass<const InfantryTypeClass*>::copy constructor

// FUNCTION: GAMEMD 0x5138F0
// VectorClass<const InfantryTypeClass*>::capacity constructor

// FUNCTION: GAMEMD 0x67A820
// TypeList<const InfantryTypeClass*>::default constructor

// VTABLE: GAMEMD 0x7EAC28 -- VectorClass<const InfantryTypeClass*>.
template class VectorClass<const InfantryTypeClass*>;
typedef VectorClass<const InfantryTypeClass*> GgInfantrytypeVectorClass;
GG_STATIC_ASSERT(offsetof(GgInfantrytypeVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgInfantrytypeVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgInfantrytypeVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgInfantrytypeVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7EAC88 -- DynamicVectorClass<const InfantryTypeClass*>.
template class DynamicVectorClass<const InfantryTypeClass*>;
typedef DynamicVectorClass<const InfantryTypeClass*> GgInfantrytypeDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgInfantrytypeDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgInfantrytypeDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgInfantrytypeDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgInfantrytypeDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgInfantrytypeDynamicVectorClass, ActiveCount) == 0x10);
GG_STATIC_ASSERT(offsetof(GgInfantrytypeDynamicVectorClass, CapacityIncrement) == 0x14);

// VTABLE: GAMEMD 0x7EAC08 -- TypeList<const InfantryTypeClass*>.
template class TypeList<const InfantryTypeClass*>;
typedef TypeList<const InfantryTypeClass*> GgInfantrytypeTypeList;
GG_STATIC_ASSERT(offsetof(GgInfantrytypeTypeList, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgInfantrytypeTypeList, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgInfantrytypeTypeList, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgInfantrytypeTypeList, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgInfantrytypeTypeList, ActiveCount) == 0x10);
GG_STATIC_ASSERT(offsetof(GgInfantrytypeTypeList, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(const InfantryTypeClass*) == 4);
