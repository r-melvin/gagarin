// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy
// Retail PAVCoopCampaignClass RTTI establishes the pointer element type and zero-offset
// DynamicVectorClass -> VectorClass base chain. Complete entry-origin spans
// establish the bound methods. GX emits a short derived deleting wrapper;
// no GX reproduces its full retail body. No TypeList or constructor is bound;
// original TU boundaries, final link and complete object sizes are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
#include "vector_class_operations.h"

class CoopCampaignClass;

// FUNCTION: GAMEMD 0x5C50D0
// DynamicVectorClass<CoopCampaignClass*>::Clear

// FUNCTION: GAMEMD 0x5C5100
// DynamicVectorClass<CoopCampaignClass*>::Slot5

// FUNCTION: GAMEMD 0x5C5120
// VectorClass<CoopCampaignClass*>::Slot6

// FUNCTION: GAMEMD 0x5C55F0
// VectorClass<CoopCampaignClass*>::operator==

// FUNCTION: GAMEMD 0x5C5630
// VectorClass<CoopCampaignClass*>::SetCapacity

// FUNCTION: GAMEMD 0x5C56E0
// VectorClass<CoopCampaignClass*>::Clear

// FUNCTION: GAMEMD 0x5C5710
// VectorClass<CoopCampaignClass*>::FindItemIndex

// FUNCTION: GAMEMD 0x5C5750
// VectorClass<CoopCampaignClass*>::Slot5

// FUNCTION: GAMEMD 0x5C5770
// DynamicVectorClass<CoopCampaignClass*>::SetCapacity

// FUNCTION: GAMEMD 0x5C5820
// DynamicVectorClass<CoopCampaignClass*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x5C5940
// VectorClass<CoopCampaignClass*>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x5C5990
// DynamicVectorClass<CoopCampaignClass*>::scalar deleting destructor

// VTABLE: GAMEMD 0x7EE3B0 -- VectorClass<CoopCampaignClass*>.
template class VectorClass<CoopCampaignClass*>;
typedef VectorClass<CoopCampaignClass*> GgCoopCampaignClassVectorClass;
GG_STATIC_ASSERT(offsetof(GgCoopCampaignClassVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgCoopCampaignClassVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgCoopCampaignClassVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgCoopCampaignClassVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7EE350 -- DynamicVectorClass<CoopCampaignClass*>.
template class DynamicVectorClass<CoopCampaignClass*>;
typedef DynamicVectorClass<CoopCampaignClass*> GgCoopCampaignClassDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgCoopCampaignClassDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgCoopCampaignClassDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgCoopCampaignClassDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgCoopCampaignClassDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgCoopCampaignClassDynamicVectorClass, ActiveCount) == 0x10);
GG_STATIC_ASSERT(offsetof(GgCoopCampaignClassDynamicVectorClass, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(CoopCampaignClass*) == 4);
