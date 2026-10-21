// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /DNDEBUG /Gy
// Retail PAVSubTitle RTTI establishes the pointer element type and zero-offset
// DynamicVectorClass -> VectorClass base chain. Complete entry-origin spans
// establish the bound methods. GX emits short base and derived deleting wrappers;
// no GX reproduces its full retail body. No TypeList or constructor is bound;
// original TU boundaries, final link and complete object sizes are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
#include "vector_class_operations.h"

class SubTitle;

// FUNCTION: GAMEMD 0x6CA7C0
// DynamicVectorClass<SubTitle*>::Clear

// FUNCTION: GAMEMD 0x6CA7F0
// DynamicVectorClass<SubTitle*>::Slot5

// FUNCTION: GAMEMD 0x6CA810
// VectorClass<SubTitle*>::Slot6

// FUNCTION: GAMEMD 0x6CA820
// VectorClass<SubTitle*>::operator==

// FUNCTION: GAMEMD 0x6CA860
// DynamicVectorClass<SubTitle*>::SetCapacity

// FUNCTION: GAMEMD 0x6CA910
// DynamicVectorClass<SubTitle*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x6CA9C0
// DynamicVectorClass<SubTitle*>::scalar deleting destructor

// FUNCTION: GAMEMD 0x6CAA10
// VectorClass<SubTitle*>::SetCapacity

// FUNCTION: GAMEMD 0x6CAAC0
// VectorClass<SubTitle*>::Clear

// FUNCTION: GAMEMD 0x6CAAF0
// VectorClass<SubTitle*>::FindItemIndex

// FUNCTION: GAMEMD 0x6CAB30
// VectorClass<SubTitle*>::Slot5

// SYNTHETIC: GAMEMD 0x6CAB50
// VectorClass<SubTitle*>::scalar deleting destructor

// VTABLE: GAMEMD 0x7F3F8C -- VectorClass<SubTitle*>.
template class VectorClass<SubTitle*>;
typedef VectorClass<SubTitle*> GgSubtitleVectorClass;
GG_STATIC_ASSERT(offsetof(GgSubtitleVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgSubtitleVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgSubtitleVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgSubtitleVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7F3F6C -- DynamicVectorClass<SubTitle*>.
template class DynamicVectorClass<SubTitle*>;
typedef DynamicVectorClass<SubTitle*> GgSubtitleDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgSubtitleDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgSubtitleDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgSubtitleDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgSubtitleDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgSubtitleDynamicVectorClass, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgSubtitleDynamicVectorClass, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(SubTitle*) == 4);
