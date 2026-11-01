// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Retail PAVAnimClass RTTI establishes the pointer element type and zero-offset
// DynamicVectorClass -> VectorClass base chain. Complete entry-origin spans
// establish the bound methods. GX emits a short derived deleting wrapper;
// no GX reproduces its full retail body. No TypeList or constructor is bound;
// original TU boundaries, final link and complete object sizes are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
#include "vector_class_operations.h"

class AnimClass;

// FUNCTION: GAMEMD 0x4E8960
// DynamicVectorClass<AnimClass*>::Clear

// FUNCTION: GAMEMD 0x4E8990
// DynamicVectorClass<AnimClass*>::Slot5

// FUNCTION: GAMEMD 0x4E89B0
// VectorClass<AnimClass*>::Slot6

// FUNCTION: GAMEMD 0x4EBE40
// VectorClass<AnimClass*>::operator==

// FUNCTION: GAMEMD 0x4EBE80
// VectorClass<AnimClass*>::SetCapacity

// FUNCTION: GAMEMD 0x4EBF30
// VectorClass<AnimClass*>::Clear

// FUNCTION: GAMEMD 0x4EBF60
// VectorClass<AnimClass*>::FindItemIndex

// FUNCTION: GAMEMD 0x4EBFA0
// VectorClass<AnimClass*>::Slot5

// FUNCTION: GAMEMD 0x4EBFC0
// DynamicVectorClass<AnimClass*>::SetCapacity

// FUNCTION: GAMEMD 0x4EC070
// DynamicVectorClass<AnimClass*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x4F0070
// VectorClass<AnimClass*>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x4F00C0
// DynamicVectorClass<AnimClass*>::scalar deleting destructor

// VTABLE: GAMEMD 0x7E9F44 -- VectorClass<AnimClass*>.
template class VectorClass<AnimClass*>;
typedef VectorClass<AnimClass*> GgAnimclassVectorClass;
GG_STATIC_ASSERT(offsetof(GgAnimclassVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgAnimclassVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgAnimclassVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgAnimclassVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7E9F24 -- DynamicVectorClass<AnimClass*>.
template class DynamicVectorClass<AnimClass*>;
typedef DynamicVectorClass<AnimClass*> GgAnimclassDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgAnimclassDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgAnimclassDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgAnimclassDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgAnimclassDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgAnimclassDynamicVectorClass, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgAnimclassDynamicVectorClass, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(AnimClass*) == 4);
