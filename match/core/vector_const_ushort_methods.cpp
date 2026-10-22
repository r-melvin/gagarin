// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /DNDEBUG /Gy
// Retail PBG RTTI establishes the pointer element type and zero-offset
// DynamicVectorClass -> VectorClass base chain. Complete entry-origin spans
// establish the bound methods. GX emits a short derived deleting wrapper;
// no GX reproduces its full retail body. No TypeList or constructor is bound;
// original TU boundaries, final link and complete object sizes are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
#include "vector_class_operations.h"

// SYNTHETIC: GAMEMD 0x558130
// DynamicVectorClass<const unsigned short*>::scalar deleting destructor

// FUNCTION: GAMEMD 0x5581E0
// DynamicVectorClass<const unsigned short*>::Clear

// FUNCTION: GAMEMD 0x558210
// DynamicVectorClass<const unsigned short*>::Slot5

// FUNCTION: GAMEMD 0x558230
// VectorClass<const unsigned short*>::Slot6

// FUNCTION: GAMEMD 0x558240
// VectorClass<const unsigned short*>::operator==

// FUNCTION: GAMEMD 0x558280
// VectorClass<const unsigned short*>::SetCapacity

// FUNCTION: GAMEMD 0x558330
// VectorClass<const unsigned short*>::Clear

// FUNCTION: GAMEMD 0x558360
// VectorClass<const unsigned short*>::FindItemIndex

// FUNCTION: GAMEMD 0x5583A0
// VectorClass<const unsigned short*>::Slot5

// FUNCTION: GAMEMD 0x5583C0
// DynamicVectorClass<const unsigned short*>::SetCapacity

// FUNCTION: GAMEMD 0x558470
// DynamicVectorClass<const unsigned short*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x5584A0
// VectorClass<const unsigned short*>::scalar deleting destructor

// VTABLE: GAMEMD 0x7ED1FC -- VectorClass<const unsigned short*>.
template class VectorClass<const unsigned short*>;
typedef VectorClass<const unsigned short*> GgConstUshortVectorClass;
GG_STATIC_ASSERT(offsetof(GgConstUshortVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgConstUshortVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgConstUshortVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgConstUshortVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7ED1DC -- DynamicVectorClass<const unsigned short*>.
template class DynamicVectorClass<const unsigned short*>;
typedef DynamicVectorClass<const unsigned short*> GgConstUshortDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgConstUshortDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgConstUshortDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgConstUshortDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgConstUshortDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgConstUshortDynamicVectorClass, ActiveCount) == 0x10);
GG_STATIC_ASSERT(offsetof(GgConstUshortDynamicVectorClass, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(const unsigned short*) == 4);
