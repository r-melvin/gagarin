// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /DNDEBUG /Gy
// Retail PAUNodeNameType RTTI establishes the pointer element type and zero-offset
// DynamicVectorClass -> VectorClass base chain. Complete entry-origin spans
// establish the bound methods. GX emits a short derived deleting wrapper;
// no GX reproduces its full retail body. No TypeList or constructor is bound;
// original TU boundaries, final link and complete object sizes are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
#include "vector_class_operations.h"

struct NodeNameType;

// FUNCTION: GAMEMD 0x5C5070
// DynamicVectorClass<NodeNameType*>::Clear

// FUNCTION: GAMEMD 0x5C50A0
// DynamicVectorClass<NodeNameType*>::Slot5

// FUNCTION: GAMEMD 0x5C50C0
// VectorClass<NodeNameType*>::Slot6

// FUNCTION: GAMEMD 0x5C5390
// VectorClass<NodeNameType*>::operator==

// FUNCTION: GAMEMD 0x5C53D0
// VectorClass<NodeNameType*>::SetCapacity

// FUNCTION: GAMEMD 0x5C5480
// VectorClass<NodeNameType*>::Clear

// FUNCTION: GAMEMD 0x5C54B0
// VectorClass<NodeNameType*>::FindItemIndex

// FUNCTION: GAMEMD 0x5C54F0
// VectorClass<NodeNameType*>::Slot5

// FUNCTION: GAMEMD 0x5C5510
// DynamicVectorClass<NodeNameType*>::SetCapacity

// FUNCTION: GAMEMD 0x5C55C0
// DynamicVectorClass<NodeNameType*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x5C58A0
// VectorClass<NodeNameType*>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x5C58F0
// DynamicVectorClass<NodeNameType*>::scalar deleting destructor

// VTABLE: GAMEMD 0x7EE390 -- VectorClass<NodeNameType*>.
template class VectorClass<NodeNameType*>;
typedef VectorClass<NodeNameType*> GgNodenametypeVectorClass;
GG_STATIC_ASSERT(offsetof(GgNodenametypeVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgNodenametypeVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgNodenametypeVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgNodenametypeVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7EE370 -- DynamicVectorClass<NodeNameType*>.
template class DynamicVectorClass<NodeNameType*>;
typedef DynamicVectorClass<NodeNameType*> GgNodenametypeDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgNodenametypeDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgNodenametypeDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgNodenametypeDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgNodenametypeDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgNodenametypeDynamicVectorClass, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgNodenametypeDynamicVectorClass, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(NodeNameType*) == 4);
