// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Retail PAVVoxClass RTTI establishes the pointer element type and zero-offset
// DynamicVectorClass -> VectorClass base chain. Complete entry-origin spans
// establish the bound methods. GX emits a short derived deleting wrapper;
// no GX reproduces its full retail body. No TypeList or constructor is bound;
// original TU boundaries, final link and complete object sizes are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
#include "vector_class_operations.h"

class VoxClass;

// FUNCTION: GAMEMD 0x753650
// DynamicVectorClass<VoxClass*>::Clear

// FUNCTION: GAMEMD 0x753680
// DynamicVectorClass<VoxClass*>::Slot5

// FUNCTION: GAMEMD 0x7536A0
// VectorClass<VoxClass*>::Slot6

// FUNCTION: GAMEMD 0x7536B0
// VectorClass<VoxClass*>::operator==

// FUNCTION: GAMEMD 0x7536F0
// VectorClass<VoxClass*>::SetCapacity

// FUNCTION: GAMEMD 0x7537A0
// VectorClass<VoxClass*>::Clear

// FUNCTION: GAMEMD 0x7537D0
// VectorClass<VoxClass*>::FindItemIndex

// FUNCTION: GAMEMD 0x753810
// VectorClass<VoxClass*>::Slot5

// FUNCTION: GAMEMD 0x753830
// DynamicVectorClass<VoxClass*>::SetCapacity

// FUNCTION: GAMEMD 0x7538E0
// DynamicVectorClass<VoxClass*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x753910
// VectorClass<VoxClass*>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x753960
// DynamicVectorClass<VoxClass*>::scalar deleting destructor

// VTABLE: GAMEMD 0x7F6924 -- VectorClass<VoxClass*>.
template class VectorClass<VoxClass*>;
typedef VectorClass<VoxClass*> GgVoxClassVectorClass;
GG_STATIC_ASSERT(offsetof(GgVoxClassVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgVoxClassVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgVoxClassVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgVoxClassVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7F6904 -- DynamicVectorClass<VoxClass*>.
template class DynamicVectorClass<VoxClass*>;
typedef DynamicVectorClass<VoxClass*> GgVoxClassDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgVoxClassDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgVoxClassDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgVoxClassDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgVoxClassDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgVoxClassDynamicVectorClass, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgVoxClassDynamicVectorClass, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(VoxClass*) == 4);
