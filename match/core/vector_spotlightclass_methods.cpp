// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT
// Retail PAVSpotLightClass RTTI establishes the pointer element type and zero-offset
// DynamicVectorClass -> VectorClass base chain. Complete entry-origin spans
// establish the bound methods. GX emits a short derived deleting wrapper;
// no GX reproduces its full retail body. No TypeList or constructor is bound;
// original TU boundaries, final link and complete object sizes are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
#include "vector_class_operations.h"

class SpotLightClass;

// FUNCTION: GAMEMD 0x5FFFC0
// DynamicVectorClass<SpotLightClass*>::Clear

// FUNCTION: GAMEMD 0x5FFFF0
// DynamicVectorClass<SpotLightClass*>::Slot5

// FUNCTION: GAMEMD 0x600010
// VectorClass<SpotLightClass*>::Slot6

// FUNCTION: GAMEMD 0x600020
// VectorClass<SpotLightClass*>::operator==

// FUNCTION: GAMEMD 0x600060
// VectorClass<SpotLightClass*>::SetCapacity

// FUNCTION: GAMEMD 0x600110
// VectorClass<SpotLightClass*>::Clear

// FUNCTION: GAMEMD 0x600140
// VectorClass<SpotLightClass*>::FindItemIndex

// FUNCTION: GAMEMD 0x600180
// VectorClass<SpotLightClass*>::Slot5

// FUNCTION: GAMEMD 0x6001A0
// DynamicVectorClass<SpotLightClass*>::SetCapacity

// FUNCTION: GAMEMD 0x600250
// DynamicVectorClass<SpotLightClass*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x600280
// VectorClass<SpotLightClass*>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x6002D0
// DynamicVectorClass<SpotLightClass*>::scalar deleting destructor

// VTABLE: GAMEMD 0x7EF6DC -- VectorClass<SpotLightClass*>.
template class VectorClass<SpotLightClass*>;
typedef VectorClass<SpotLightClass*> GgSpotlightclassVectorClass;
GG_STATIC_ASSERT(offsetof(GgSpotlightclassVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgSpotlightclassVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgSpotlightclassVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgSpotlightclassVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7EF6BC -- DynamicVectorClass<SpotLightClass*>.
template class DynamicVectorClass<SpotLightClass*>;
typedef DynamicVectorClass<SpotLightClass*> GgSpotlightclassDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgSpotlightclassDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgSpotlightclassDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgSpotlightclassDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgSpotlightclassDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgSpotlightclassDynamicVectorClass, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgSpotlightclassDynamicVectorClass, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(SpotLightClass*) == 4);
