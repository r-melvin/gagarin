// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy
// Retail PAUMPlayerScoreType RTTI identifies mutable struct pointers and
// DynamicVectorClass -> VectorClass at offset zero. Complete entry-origin
// spans establish the bound methods; no GX emits the full deleting bodies.
// No TypeList or dynamic capacity constructor is claimed. Original TU
// boundaries, final link and complete object sizes remain unestablished.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
#include "vector_class_operations.h"
struct MPlayerScoreType;

// FUNCTION: GAMEMD 0x5C4F30
// DynamicVectorClass<MPlayerScoreType*>::copy constructor

// SYNTHETIC: GAMEMD 0x5C4FC0
// DynamicVectorClass<MPlayerScoreType*>::scalar deleting destructor

// FUNCTION: GAMEMD 0x5C5010
// DynamicVectorClass<MPlayerScoreType*>::Clear

// FUNCTION: GAMEMD 0x5C5040
// DynamicVectorClass<MPlayerScoreType*>::Slot5

// FUNCTION: GAMEMD 0x5C5060
// VectorClass<MPlayerScoreType*>::Slot6

// FUNCTION: GAMEMD 0x5C5130
// VectorClass<MPlayerScoreType*>::operator==

// FUNCTION: GAMEMD 0x5C5170
// VectorClass<MPlayerScoreType*>::SetCapacity

// FUNCTION: GAMEMD 0x5C5220
// VectorClass<MPlayerScoreType*>::Clear

// FUNCTION: GAMEMD 0x5C5250
// VectorClass<MPlayerScoreType*>::FindItemIndex

// FUNCTION: GAMEMD 0x5C5290
// VectorClass<MPlayerScoreType*>::Slot5

// FUNCTION: GAMEMD 0x5C52B0
// DynamicVectorClass<MPlayerScoreType*>::SetCapacity

// FUNCTION: GAMEMD 0x5C5360
// DynamicVectorClass<MPlayerScoreType*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x5C5850
// VectorClass<MPlayerScoreType*>::scalar deleting destructor

// FUNCTION: GAMEMD 0x5C59E0
// VectorClass<MPlayerScoreType*>::capacity constructor

// VTABLE: GAMEMD 0x7EE3D0 -- VectorClass<MPlayerScoreType*>.
template class VectorClass<MPlayerScoreType*>;
typedef VectorClass<MPlayerScoreType*> GgMPlayerScoreVectorClass;
GG_STATIC_ASSERT(offsetof(GgMPlayerScoreVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgMPlayerScoreVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgMPlayerScoreVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgMPlayerScoreVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7EE3F0 -- DynamicVectorClass<MPlayerScoreType*>.
template class DynamicVectorClass<MPlayerScoreType*>;
typedef DynamicVectorClass<MPlayerScoreType*> GgMPlayerScoreDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgMPlayerScoreDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgMPlayerScoreDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgMPlayerScoreDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgMPlayerScoreDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgMPlayerScoreDynamicVectorClass, ActiveCount) == 0x10);
GG_STATIC_ASSERT(offsetof(GgMPlayerScoreDynamicVectorClass, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(MPlayerScoreType*) == 4);
