// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /DNDEBUG /Gy
// Raw PBVAnimClass RTTI identifies const pointer elements and the
// DynamicVectorClass -> VectorClass zero-offset base chain.
// Complete entry-origin spans establish all bound methods. GX emits shorter
// derived deleting wrappers; no GX reproduces the retail 0x49-byte bodies.
// No TypeList or constructor address is claimed. Original TU boundaries,
// final link and complete object sizes remain unestablished.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
#include "vector_class_operations.h"
class AnimClass;

// FUNCTION: GAMEMD 0x53C4C0
// DynamicVectorClass<const AnimClass*>::Clear

// FUNCTION: GAMEMD 0x53C4F0
// DynamicVectorClass<const AnimClass*>::Slot5

// FUNCTION: GAMEMD 0x53C510
// VectorClass<const AnimClass*>::Slot6

// FUNCTION: GAMEMD 0x53C520
// VectorClass<const AnimClass*>::operator==

// FUNCTION: GAMEMD 0x53C560
// VectorClass<const AnimClass*>::SetCapacity

// FUNCTION: GAMEMD 0x53C610
// VectorClass<const AnimClass*>::Clear

// FUNCTION: GAMEMD 0x53C640
// VectorClass<const AnimClass*>::FindItemIndex

// FUNCTION: GAMEMD 0x53C680
// VectorClass<const AnimClass*>::Slot5

// FUNCTION: GAMEMD 0x53C6A0
// DynamicVectorClass<const AnimClass*>::SetCapacity

// FUNCTION: GAMEMD 0x53C750
// DynamicVectorClass<const AnimClass*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x53C780
// VectorClass<const AnimClass*>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x53C7D0
// DynamicVectorClass<const AnimClass*>::scalar deleting destructor

// VTABLE: GAMEMD 0x7EBFEC -- VectorClass<const AnimClass*>.
template class VectorClass<const AnimClass*>;
typedef VectorClass<const AnimClass*> GgAnimVectorClass;
GG_STATIC_ASSERT(offsetof(GgAnimVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgAnimVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgAnimVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgAnimVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7EBFCC -- DynamicVectorClass<const AnimClass*>.
template class DynamicVectorClass<const AnimClass*>;
typedef DynamicVectorClass<const AnimClass*> GgAnimDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgAnimDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgAnimDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgAnimDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgAnimDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgAnimDynamicVectorClass, ActiveCount) == 0x10);
GG_STATIC_ASSERT(offsetof(GgAnimDynamicVectorClass, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(const AnimClass*) == 4);
