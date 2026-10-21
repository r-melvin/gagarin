// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /DNDEBUG /Gy
// Retail PAVEgoClass RTTI establishes the pointer element type and zero-offset
// DynamicVectorClass -> VectorClass base chain. Complete entry-origin spans
// establish the bound methods. GX emits a short derived deleting wrapper;
// no GX reproduces its full retail body. No TypeList or constructor is bound;
// original TU boundaries, final link and complete object sizes are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
#include "vector_class_operations.h"

class EgoClass;

// FUNCTION: GAMEMD 0x4C49A0
// DynamicVectorClass<EgoClass*>::Clear

// FUNCTION: GAMEMD 0x4C49D0
// DynamicVectorClass<EgoClass*>::Slot5

// FUNCTION: GAMEMD 0x4C49F0
// VectorClass<EgoClass*>::Slot6

// FUNCTION: GAMEMD 0x4C4A00
// VectorClass<EgoClass*>::operator==

// FUNCTION: GAMEMD 0x4C4A40
// VectorClass<EgoClass*>::SetCapacity

// FUNCTION: GAMEMD 0x4C4AF0
// VectorClass<EgoClass*>::Clear

// FUNCTION: GAMEMD 0x4C4B20
// VectorClass<EgoClass*>::FindItemIndex

// FUNCTION: GAMEMD 0x4C4B60
// VectorClass<EgoClass*>::Slot5

// FUNCTION: GAMEMD 0x4C4B80
// DynamicVectorClass<EgoClass*>::SetCapacity

// FUNCTION: GAMEMD 0x4C4C30
// DynamicVectorClass<EgoClass*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x4C4C60
// VectorClass<EgoClass*>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x4C4CB0
// DynamicVectorClass<EgoClass*>::scalar deleting destructor

// VTABLE: GAMEMD 0x7E86FC -- VectorClass<EgoClass*>.
template class VectorClass<EgoClass*>;
typedef VectorClass<EgoClass*> GgEgoClassVectorClass;
GG_STATIC_ASSERT(offsetof(GgEgoClassVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgEgoClassVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgEgoClassVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgEgoClassVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7E86DC -- DynamicVectorClass<EgoClass*>.
template class DynamicVectorClass<EgoClass*>;
typedef DynamicVectorClass<EgoClass*> GgEgoClassDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgEgoClassDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgEgoClassDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgEgoClassDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgEgoClassDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgEgoClassDynamicVectorClass, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgEgoClassDynamicVectorClass, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(EgoClass*) == 4);
