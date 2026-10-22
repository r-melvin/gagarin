// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy
// Retail PAVCampaignClass RTTI establishes the pointer element type and zero-offset
// DynamicVectorClass -> VectorClass base chain. Complete entry-origin spans
// establish the bound methods. GX emits a short derived deleting wrapper;
// no GX reproduces its full retail body. No TypeList or constructor is bound;
// original TU boundaries, final link and complete object sizes are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
#include "vector_class_operations.h"
class CampaignClass;

// FUNCTION: GAMEMD 0x4E8A20
// DynamicVectorClass<CampaignClass*>::Clear

// FUNCTION: GAMEMD 0x4E8A50
// DynamicVectorClass<CampaignClass*>::Slot5

// FUNCTION: GAMEMD 0x4E8A70
// VectorClass<CampaignClass*>::Slot6

// FUNCTION: GAMEMD 0x4EC300
// VectorClass<CampaignClass*>::operator==

// FUNCTION: GAMEMD 0x4EC340
// VectorClass<CampaignClass*>::SetCapacity

// FUNCTION: GAMEMD 0x4EC3F0
// VectorClass<CampaignClass*>::Clear

// FUNCTION: GAMEMD 0x4EC420
// VectorClass<CampaignClass*>::FindItemIndex

// FUNCTION: GAMEMD 0x4EC460
// VectorClass<CampaignClass*>::Slot5

// FUNCTION: GAMEMD 0x4EC480
// DynamicVectorClass<CampaignClass*>::SetCapacity

// FUNCTION: GAMEMD 0x4EC530
// DynamicVectorClass<CampaignClass*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x4F01B0
// VectorClass<CampaignClass*>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x4F0200
// DynamicVectorClass<CampaignClass*>::scalar deleting destructor

// VTABLE: GAMEMD 0x7EA004 -- VectorClass<CampaignClass*>.
template class VectorClass<CampaignClass*>;
typedef VectorClass<CampaignClass*> GgCampaignClassVectorClass;
GG_STATIC_ASSERT(offsetof(GgCampaignClassVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgCampaignClassVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgCampaignClassVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgCampaignClassVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7E9FE4 -- DynamicVectorClass<CampaignClass*>.
template class DynamicVectorClass<CampaignClass*>;
typedef DynamicVectorClass<CampaignClass*> GgCampaignClassDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgCampaignClassDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgCampaignClassDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgCampaignClassDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgCampaignClassDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgCampaignClassDynamicVectorClass, ActiveCount) == 0x10);
GG_STATIC_ASSERT(offsetof(GgCampaignClassDynamicVectorClass, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(CampaignClass*) == 4);
