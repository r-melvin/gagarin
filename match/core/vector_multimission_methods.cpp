// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /DNDEBUG /Gy /Ob2
// Raw PBVMultiMission RTTI identifies const pointer elements and the
// DynamicVectorClass -> VectorClass zero-offset base chain.
// Complete entry-origin spans establish all bound methods. GX emits shorter
// derived deleting wrappers; no GX reproduces the retail 0x49-byte bodies.
// Only the listed constructor is claimed; no TypeList specialization is bound.
// Original TU boundaries,
// final link and complete object sizes remain unestablished.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
#include "vector_class_operations.h"
class MultiMission;

// FUNCTION: GAMEMD 0x5EEBB0
// DynamicVectorClass<const MultiMission*>::Clear

// FUNCTION: GAMEMD 0x5EEBE0
// DynamicVectorClass<const MultiMission*>::Slot5

// FUNCTION: GAMEMD 0x5EEC00
// VectorClass<const MultiMission*>::Slot6

// FUNCTION: GAMEMD 0x5EEC10
// VectorClass<const MultiMission*>::operator==

// FUNCTION: GAMEMD 0x5EEC50
// VectorClass<const MultiMission*>::SetCapacity

// FUNCTION: GAMEMD 0x5EED00
// VectorClass<const MultiMission*>::Clear

// FUNCTION: GAMEMD 0x5EED30
// VectorClass<const MultiMission*>::FindItemIndex

// FUNCTION: GAMEMD 0x5EED70
// VectorClass<const MultiMission*>::Slot5

// FUNCTION: GAMEMD 0x5EED90
// DynamicVectorClass<const MultiMission*>::SetCapacity

// FUNCTION: GAMEMD 0x5EEE90
// DynamicVectorClass<const MultiMission*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x5EEEC0
// VectorClass<const MultiMission*>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x5EEF10
// DynamicVectorClass<const MultiMission*>::scalar deleting destructor

// FUNCTION: GAMEMD 0x5EF0B0
// VectorClass<const MultiMission*>::capacity constructor

// VTABLE: GAMEMD 0x7EEF50 -- VectorClass<const MultiMission*>.
template class VectorClass<const MultiMission*>;
typedef VectorClass<const MultiMission*> GgMultiMissionVectorClass;
GG_STATIC_ASSERT(offsetof(GgMultiMissionVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgMultiMissionVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgMultiMissionVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgMultiMissionVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7EEF70 -- DynamicVectorClass<const MultiMission*>.
template class DynamicVectorClass<const MultiMission*>;
typedef DynamicVectorClass<const MultiMission*> GgMultiMissionDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgMultiMissionDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgMultiMissionDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgMultiMissionDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgMultiMissionDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgMultiMissionDynamicVectorClass, ActiveCount) == 0x10);
GG_STATIC_ASSERT(offsetof(GgMultiMissionDynamicVectorClass, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(const MultiMission*) == 4);
