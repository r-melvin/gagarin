// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /DNDEBUG /Gy
// Retail PAVAnimTypeClass RTTI establishes the pointer element type and zero-offset
// DynamicVectorClass -> VectorClass base chain. Complete entry-origin spans
// establish the bound methods. GX emits a short derived deleting wrapper;
// no GX reproduces its full retail body. No TypeList or constructor is bound;
// original TU boundaries, final link and complete object sizes are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
#include "vector_class_operations.h"
class AnimTypeClass;

// FUNCTION: GAMEMD 0x4E8EA0
// DynamicVectorClass<AnimTypeClass*>::Clear

// FUNCTION: GAMEMD 0x4E8ED0
// DynamicVectorClass<AnimTypeClass*>::Slot5

// FUNCTION: GAMEMD 0x4E8EF0
// VectorClass<AnimTypeClass*>::Slot6

// FUNCTION: GAMEMD 0x4EDF80
// VectorClass<AnimTypeClass*>::operator==

// FUNCTION: GAMEMD 0x4EDFC0
// VectorClass<AnimTypeClass*>::SetCapacity

// FUNCTION: GAMEMD 0x4EE070
// VectorClass<AnimTypeClass*>::Clear

// FUNCTION: GAMEMD 0x4EE0A0
// VectorClass<AnimTypeClass*>::FindItemIndex

// FUNCTION: GAMEMD 0x4EE0E0
// VectorClass<AnimTypeClass*>::Slot5

// FUNCTION: GAMEMD 0x4EE100
// DynamicVectorClass<AnimTypeClass*>::SetCapacity

// FUNCTION: GAMEMD 0x4EE1B0
// DynamicVectorClass<AnimTypeClass*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x4F0930
// VectorClass<AnimTypeClass*>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x4F0980
// DynamicVectorClass<AnimTypeClass*>::scalar deleting destructor

// VTABLE: GAMEMD 0x7EA304 -- VectorClass<AnimTypeClass*>.
template class VectorClass<AnimTypeClass*>;
typedef VectorClass<AnimTypeClass*> GgAnimTypeClassVectorClass;
GG_STATIC_ASSERT(offsetof(GgAnimTypeClassVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgAnimTypeClassVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgAnimTypeClassVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgAnimTypeClassVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7EA2E4 -- DynamicVectorClass<AnimTypeClass*>.
template class DynamicVectorClass<AnimTypeClass*>;
typedef DynamicVectorClass<AnimTypeClass*> GgAnimTypeClassDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgAnimTypeClassDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgAnimTypeClassDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgAnimTypeClassDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgAnimTypeClassDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgAnimTypeClassDynamicVectorClass, ActiveCount) == 0x10);
GG_STATIC_ASSERT(offsetof(GgAnimTypeClassDynamicVectorClass, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(AnimTypeClass*) == 4);
