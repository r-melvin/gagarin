// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy
// Retail PAUCrossDissolveEffect RTTI establishes the pointer element type and zero-offset
// DynamicVectorClass -> VectorClass base chain. Complete entry-origin spans
// establish the bound methods. GX emits a short derived deleting wrapper;
// no GX reproduces its full retail body. No TypeList or constructor is bound;
// original TU boundaries, final link and complete object sizes are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
#include "vector_class_operations.h"

struct CrossDissolveEffect;

// FUNCTION: GAMEMD 0x4B9C40
// DynamicVectorClass<CrossDissolveEffect*>::Clear

// FUNCTION: GAMEMD 0x4B9C70
// DynamicVectorClass<CrossDissolveEffect*>::Slot5

// FUNCTION: GAMEMD 0x4B9C90
// VectorClass<CrossDissolveEffect*>::Slot6

// FUNCTION: GAMEMD 0x4B9F00
// VectorClass<CrossDissolveEffect*>::operator==

// FUNCTION: GAMEMD 0x4B9F40
// VectorClass<CrossDissolveEffect*>::SetCapacity

// FUNCTION: GAMEMD 0x4B9FF0
// VectorClass<CrossDissolveEffect*>::Clear

// FUNCTION: GAMEMD 0x4BA020
// VectorClass<CrossDissolveEffect*>::FindItemIndex

// FUNCTION: GAMEMD 0x4BA060
// VectorClass<CrossDissolveEffect*>::Slot5

// FUNCTION: GAMEMD 0x4BA080
// DynamicVectorClass<CrossDissolveEffect*>::SetCapacity

// FUNCTION: GAMEMD 0x4BA130
// DynamicVectorClass<CrossDissolveEffect*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x4BA250
// VectorClass<CrossDissolveEffect*>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x4BA2A0
// DynamicVectorClass<CrossDissolveEffect*>::scalar deleting destructor

// VTABLE: GAMEMD 0x7E8520 -- VectorClass<CrossDissolveEffect*>.
template class VectorClass<CrossDissolveEffect*>;
typedef VectorClass<CrossDissolveEffect*> GgCrossdissolveeffectVectorClass;
GG_STATIC_ASSERT(offsetof(GgCrossdissolveeffectVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgCrossdissolveeffectVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgCrossdissolveeffectVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgCrossdissolveeffectVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7E854C -- DynamicVectorClass<CrossDissolveEffect*>.
template class DynamicVectorClass<CrossDissolveEffect*>;
typedef DynamicVectorClass<CrossDissolveEffect*> GgCrossdissolveeffectDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgCrossdissolveeffectDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgCrossdissolveeffectDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgCrossdissolveeffectDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgCrossdissolveeffectDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgCrossdissolveeffectDynamicVectorClass, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgCrossdissolveeffectDynamicVectorClass, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(CrossDissolveEffect*) == 4);
