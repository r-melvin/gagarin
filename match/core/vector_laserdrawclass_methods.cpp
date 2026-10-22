// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /DNDEBUG /Gy
// Retail PAVLaserDrawClass RTTI establishes the pointer element type and zero-offset
// DynamicVectorClass -> VectorClass base chain. Complete entry-origin spans
// establish the bound methods. GX emits a short derived deleting wrapper;
// no GX reproduces its full retail body. No TypeList or constructor is bound;
// original TU boundaries, final link and complete object sizes are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
#include "vector_class_operations.h"

class LaserDrawClass;

// FUNCTION: GAMEMD 0x5512D0
// DynamicVectorClass<LaserDrawClass*>::Clear

// FUNCTION: GAMEMD 0x551300
// DynamicVectorClass<LaserDrawClass*>::Slot5

// FUNCTION: GAMEMD 0x551320
// VectorClass<LaserDrawClass*>::Slot6

// FUNCTION: GAMEMD 0x551330
// VectorClass<LaserDrawClass*>::operator==

// FUNCTION: GAMEMD 0x551370
// VectorClass<LaserDrawClass*>::SetCapacity

// FUNCTION: GAMEMD 0x551420
// VectorClass<LaserDrawClass*>::Clear

// FUNCTION: GAMEMD 0x551450
// VectorClass<LaserDrawClass*>::FindItemIndex

// FUNCTION: GAMEMD 0x551490
// VectorClass<LaserDrawClass*>::Slot5

// FUNCTION: GAMEMD 0x5514B0
// DynamicVectorClass<LaserDrawClass*>::SetCapacity

// FUNCTION: GAMEMD 0x551560
// DynamicVectorClass<LaserDrawClass*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x551590
// VectorClass<LaserDrawClass*>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x5515E0
// DynamicVectorClass<LaserDrawClass*>::scalar deleting destructor

// VTABLE: GAMEMD 0x7ECEFC -- VectorClass<LaserDrawClass*>.
template class VectorClass<LaserDrawClass*>;
typedef VectorClass<LaserDrawClass*> GgLaserdrawclassVectorClass;
GG_STATIC_ASSERT(offsetof(GgLaserdrawclassVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgLaserdrawclassVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgLaserdrawclassVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgLaserdrawclassVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7ECEDC -- DynamicVectorClass<LaserDrawClass*>.
template class DynamicVectorClass<LaserDrawClass*>;
typedef DynamicVectorClass<LaserDrawClass*> GgLaserdrawclassDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgLaserdrawclassDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgLaserdrawclassDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgLaserdrawclassDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgLaserdrawclassDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgLaserdrawclassDynamicVectorClass, ActiveCount) == 0x10);
GG_STATIC_ASSERT(offsetof(GgLaserdrawclassDynamicVectorClass, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(LaserDrawClass*) == 4);
