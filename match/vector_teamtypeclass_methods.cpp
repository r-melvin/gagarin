// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Retail PAVTeamTypeClass RTTI establishes the pointer element type and zero-offset
// DynamicVectorClass -> VectorClass base chain. Complete entry-origin spans
// establish the bound methods. GX emits a short derived deleting wrapper;
// no GX reproduces its full retail body. No TypeList or constructor is bound;
// original TU boundaries, final link and complete object sizes are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
#include "vector_class_operations.h"

class TeamTypeClass;

// FUNCTION: GAMEMD 0x4E8BA0
// DynamicVectorClass<TeamTypeClass*>::Clear

// FUNCTION: GAMEMD 0x4E8BD0
// DynamicVectorClass<TeamTypeClass*>::Slot5

// FUNCTION: GAMEMD 0x4E8BF0
// VectorClass<TeamTypeClass*>::Slot6

// FUNCTION: GAMEMD 0x4ECC80
// VectorClass<TeamTypeClass*>::operator==

// FUNCTION: GAMEMD 0x4ECCC0
// VectorClass<TeamTypeClass*>::SetCapacity

// FUNCTION: GAMEMD 0x4ECD70
// VectorClass<TeamTypeClass*>::Clear

// FUNCTION: GAMEMD 0x4ECDA0
// VectorClass<TeamTypeClass*>::FindItemIndex

// FUNCTION: GAMEMD 0x4ECDE0
// VectorClass<TeamTypeClass*>::Slot5

// FUNCTION: GAMEMD 0x4ECE00
// DynamicVectorClass<TeamTypeClass*>::SetCapacity

// FUNCTION: GAMEMD 0x4ECEB0
// DynamicVectorClass<TeamTypeClass*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x4F0430
// VectorClass<TeamTypeClass*>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x4F0480
// DynamicVectorClass<TeamTypeClass*>::scalar deleting destructor

// VTABLE: GAMEMD 0x7EA104 -- VectorClass<TeamTypeClass*>.
template class VectorClass<TeamTypeClass*>;
typedef VectorClass<TeamTypeClass*> GgTeamTypeClassVectorClass;
GG_STATIC_ASSERT(offsetof(GgTeamTypeClassVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgTeamTypeClassVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgTeamTypeClassVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgTeamTypeClassVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7EA0E4 -- DynamicVectorClass<TeamTypeClass*>.
template class DynamicVectorClass<TeamTypeClass*>;
typedef DynamicVectorClass<TeamTypeClass*> GgTeamTypeClassDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgTeamTypeClassDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgTeamTypeClassDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgTeamTypeClassDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgTeamTypeClassDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgTeamTypeClassDynamicVectorClass, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgTeamTypeClassDynamicVectorClass, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(TeamTypeClass*) == 4);
