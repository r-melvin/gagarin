// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy
// Retail PAVSmudgeTypeClass RTTI establishes the pointer element type and zero-offset
// DynamicVectorClass -> VectorClass base chain. Complete entry-origin spans
// establish the bound methods. GX emits a short derived deleting wrapper;
// no GX reproduces its full retail body. No TypeList or constructor is bound;
// original TU boundaries, final link and complete object sizes are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
#include "vector_class_operations.h"
class SmudgeTypeClass;

// FUNCTION: GAMEMD 0x4E8CC0
// DynamicVectorClass<SmudgeTypeClass*>::Clear

// FUNCTION: GAMEMD 0x4E8CF0
// DynamicVectorClass<SmudgeTypeClass*>::Slot5

// FUNCTION: GAMEMD 0x4E8D10
// VectorClass<SmudgeTypeClass*>::Slot6

// FUNCTION: GAMEMD 0x4ED3A0
// VectorClass<SmudgeTypeClass*>::operator==

// FUNCTION: GAMEMD 0x4ED3E0
// VectorClass<SmudgeTypeClass*>::SetCapacity

// FUNCTION: GAMEMD 0x4ED490
// VectorClass<SmudgeTypeClass*>::Clear

// FUNCTION: GAMEMD 0x4ED4C0
// VectorClass<SmudgeTypeClass*>::FindItemIndex

// FUNCTION: GAMEMD 0x4ED500
// VectorClass<SmudgeTypeClass*>::Slot5

// FUNCTION: GAMEMD 0x4ED520
// DynamicVectorClass<SmudgeTypeClass*>::SetCapacity

// FUNCTION: GAMEMD 0x4ED5D0
// DynamicVectorClass<SmudgeTypeClass*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x4F0610
// VectorClass<SmudgeTypeClass*>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x4F0660
// DynamicVectorClass<SmudgeTypeClass*>::scalar deleting destructor

// VTABLE: GAMEMD 0x7EA1C4 -- VectorClass<SmudgeTypeClass*>.
template class VectorClass<SmudgeTypeClass*>;
typedef VectorClass<SmudgeTypeClass*> GgSmudgeTypeClassVectorClass;
GG_STATIC_ASSERT(offsetof(GgSmudgeTypeClassVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgSmudgeTypeClassVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgSmudgeTypeClassVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgSmudgeTypeClassVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7EA1A4 -- DynamicVectorClass<SmudgeTypeClass*>.
template class DynamicVectorClass<SmudgeTypeClass*>;
typedef DynamicVectorClass<SmudgeTypeClass*> GgSmudgeTypeClassDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgSmudgeTypeClassDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgSmudgeTypeClassDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgSmudgeTypeClassDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgSmudgeTypeClassDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgSmudgeTypeClassDynamicVectorClass, ActiveCount) == 0x10);
GG_STATIC_ASSERT(offsetof(GgSmudgeTypeClassDynamicVectorClass, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(SmudgeTypeClass*) == 4);
