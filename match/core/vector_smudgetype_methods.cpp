// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /DNDEBUG /Gy
// Raw PBVSmudgeTypeClass RTTI identifies const pointer elements and the
// TypeList -> DynamicVectorClass -> VectorClass zero-offset base chain.
// Complete entry-origin spans establish all bound methods. GX emits shorter
// derived deleting wrappers; no GX reproduces the retail 0x49-byte bodies.
// Original TU boundaries, final link and complete TypeList size are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
#include "vector_class_operations.h"
#include "type_list.h"
class SmudgeTypeClass;

// FUNCTION: GAMEMD 0x67A600
// TypeList<const SmudgeTypeClass*>::default constructor

// FUNCTION: GAMEMD 0x67A680
// DynamicVectorClass<const SmudgeTypeClass*>::Clear

// FUNCTION: GAMEMD 0x67A6B0
// DynamicVectorClass<const SmudgeTypeClass*>::Slot5

// FUNCTION: GAMEMD 0x67A6D0
// VectorClass<const SmudgeTypeClass*>::Slot6

// SYNTHETIC: GAMEMD 0x67A9E0
// TypeList<const SmudgeTypeClass*>::scalar deleting destructor

// FUNCTION: GAMEMD 0x67AE70
// VectorClass<const SmudgeTypeClass*>::operator==

// FUNCTION: GAMEMD 0x67AEB0
// VectorClass<const SmudgeTypeClass*>::SetCapacity

// FUNCTION: GAMEMD 0x67AF60
// VectorClass<const SmudgeTypeClass*>::Clear

// FUNCTION: GAMEMD 0x67AF90
// VectorClass<const SmudgeTypeClass*>::FindItemIndex

// FUNCTION: GAMEMD 0x67AFD0
// VectorClass<const SmudgeTypeClass*>::Slot5

// FUNCTION: GAMEMD 0x67AFF0
// DynamicVectorClass<const SmudgeTypeClass*>::capacity constructor

// FUNCTION: GAMEMD 0x67B050
// DynamicVectorClass<const SmudgeTypeClass*>::SetCapacity

// FUNCTION: GAMEMD 0x67B150
// DynamicVectorClass<const SmudgeTypeClass*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x67C0B0
// VectorClass<const SmudgeTypeClass*>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x67C100
// DynamicVectorClass<const SmudgeTypeClass*>::scalar deleting destructor

// FUNCTION: GAMEMD 0x67C280
// TypeList<const SmudgeTypeClass*>::copy constructor

// FUNCTION: GAMEMD 0x67C3A0
// VectorClass<const SmudgeTypeClass*>::capacity constructor

// VTABLE: GAMEMD 0x7F0D7C -- VectorClass<const SmudgeTypeClass*>.
template class VectorClass<const SmudgeTypeClass*>;
typedef VectorClass<const SmudgeTypeClass*> GgSmudgeTypeVectorClass;
GG_STATIC_ASSERT(offsetof(GgSmudgeTypeVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgSmudgeTypeVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgSmudgeTypeVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgSmudgeTypeVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7F0DEC -- DynamicVectorClass<const SmudgeTypeClass*>.
template class DynamicVectorClass<const SmudgeTypeClass*>;
typedef DynamicVectorClass<const SmudgeTypeClass*> GgSmudgeTypeDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgSmudgeTypeDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgSmudgeTypeDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgSmudgeTypeDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgSmudgeTypeDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgSmudgeTypeDynamicVectorClass, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgSmudgeTypeDynamicVectorClass, CapacityIncrement) == 0x14);

// VTABLE: GAMEMD 0x7F0D1C -- TypeList<const SmudgeTypeClass*>.
template class TypeList<const SmudgeTypeClass*>;
typedef TypeList<const SmudgeTypeClass*> GgSmudgeTypeTypeList;
GG_STATIC_ASSERT(offsetof(GgSmudgeTypeTypeList, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgSmudgeTypeTypeList, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgSmudgeTypeTypeList, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgSmudgeTypeTypeList, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgSmudgeTypeTypeList, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgSmudgeTypeTypeList, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(const SmudgeTypeClass*) == 4);
