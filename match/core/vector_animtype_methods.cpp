// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy
// Raw PBVAnimTypeClass RTTI identifies const pointer elements and the
// TypeList -> DynamicVectorClass -> VectorClass zero-offset base chain.
// Complete entry-origin spans establish all bound methods. GX emits shorter
// derived deleting wrappers; no GX reproduces the retail 0x49-byte bodies.
// Original TU boundaries, final link and complete TypeList size are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
#include "vector_class_operations.h"
#include "type_list.h"
class AnimTypeClass;

// FUNCTION: GAMEMD 0x524ED0
// DynamicVectorClass<const AnimTypeClass*>::Clear

// FUNCTION: GAMEMD 0x524F00
// DynamicVectorClass<const AnimTypeClass*>::Slot5

// FUNCTION: GAMEMD 0x524FB0
// VectorClass<const AnimTypeClass*>::Slot6

// SYNTHETIC: GAMEMD 0x524FC0
// TypeList<const AnimTypeClass*>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x525010
// VectorClass<const AnimTypeClass*>::scalar deleting destructor

// FUNCTION: GAMEMD 0x5250D0
// VectorClass<const AnimTypeClass*>::operator==

// FUNCTION: GAMEMD 0x525110
// VectorClass<const AnimTypeClass*>::SetCapacity

// FUNCTION: GAMEMD 0x5251C0
// VectorClass<const AnimTypeClass*>::Clear

// FUNCTION: GAMEMD 0x5251F0
// VectorClass<const AnimTypeClass*>::FindItemIndex

// FUNCTION: GAMEMD 0x525230
// VectorClass<const AnimTypeClass*>::Slot5

// FUNCTION: GAMEMD 0x525250
// DynamicVectorClass<const AnimTypeClass*> capacity constructor

// SYNTHETIC: GAMEMD 0x5252B0
// DynamicVectorClass<const AnimTypeClass*>::scalar deleting destructor

// FUNCTION: GAMEMD 0x525300
// DynamicVectorClass<const AnimTypeClass*>::SetCapacity

// FUNCTION: GAMEMD 0x525400
// DynamicVectorClass<const AnimTypeClass*>::FindItemIndex

// FUNCTION: GAMEMD 0x5255F0
// TypeList<const AnimTypeClass*> copy constructor

// FUNCTION: GAMEMD 0x525680
// VectorClass<const AnimTypeClass*> capacity constructor

// FUNCTION: GAMEMD 0x67A470
// TypeList<const AnimTypeClass*> default constructor

// VTABLE: GAMEMD 0x7EB6F4 -- VectorClass<const AnimTypeClass*>.
template class VectorClass<const AnimTypeClass*>;
typedef VectorClass<const AnimTypeClass*> GgAnimVectorClass;
GG_STATIC_ASSERT(offsetof(GgAnimVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgAnimVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgAnimVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgAnimVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7EB714 -- DynamicVectorClass<const AnimTypeClass*>.
template class DynamicVectorClass<const AnimTypeClass*>;
typedef DynamicVectorClass<const AnimTypeClass*> GgAnimDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgAnimDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgAnimDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgAnimDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgAnimDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgAnimDynamicVectorClass, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgAnimDynamicVectorClass, CapacityIncrement) == 0x14);

// VTABLE: GAMEMD 0x7EB6D4 -- TypeList<const AnimTypeClass*>.
template class TypeList<const AnimTypeClass*>;
typedef TypeList<const AnimTypeClass*> GgAnimTypeList;
GG_STATIC_ASSERT(offsetof(GgAnimTypeList, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgAnimTypeList, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgAnimTypeList, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgAnimTypeList, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgAnimTypeList, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgAnimTypeList, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(const AnimTypeClass*) == 4);
