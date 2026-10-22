// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /DNDEBUG /Gy
// Retail RTTI TypeDescriptors 0x8168E8 and 0x816918 identify
// VectorClass<BombClass*> and DynamicVectorClass<BombClass*>; the latter's
// CHD names the former as its zero-offset base.
// Full entry-origin spans bind these methods; no original TU or standalone
// constructor is claimed. No GX matches the full derived deleting body.
#include "vector_class_operations.h"
class BombClass;

// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.

// FUNCTION: GAMEMD 0x40B640
// DynamicVectorClass<BombClass*>::Clear
// FUNCTION: GAMEMD 0x40B670
// DynamicVectorClass<BombClass*>::Slot5
// FUNCTION: GAMEMD 0x40B690
// VectorClass<BombClass*>::Slot6
// FUNCTION: GAMEMD 0x40B700
// VectorClass<BombClass*>::operator==
// FUNCTION: GAMEMD 0x40B740
// VectorClass<BombClass*>::SetCapacity
// FUNCTION: GAMEMD 0x40B7F0
// VectorClass<BombClass*>::Clear
// FUNCTION: GAMEMD 0x40B820
// VectorClass<BombClass*>::FindItemIndex
// FUNCTION: GAMEMD 0x40B860
// VectorClass<BombClass*>::Slot5
// FUNCTION: GAMEMD 0x40B880
// DynamicVectorClass<BombClass*>::SetCapacity
// FUNCTION: GAMEMD 0x40B930
// DynamicVectorClass<BombClass*>::FindItemIndex
// SYNTHETIC: GAMEMD 0x40BBC0
// VectorClass<BombClass*>::scalar deleting destructor
// SYNTHETIC: GAMEMD 0x40BC10
// DynamicVectorClass<BombClass*>::scalar deleting destructor

// VTABLE: GAMEMD 0x7E17EC -- VectorClass<BombClass*>.
template class VectorClass<BombClass*>;
// VTABLE: GAMEMD 0x7E17CC -- DynamicVectorClass<BombClass*>.
template class DynamicVectorClass<BombClass*>;

typedef VectorClass<BombClass*> GgBombVector;
typedef DynamicVectorClass<BombClass*> GgBombDynamicVector;
GG_STATIC_ASSERT(sizeof(BombClass*) == 4);
GG_STATIC_ASSERT(sizeof(GgBombVector) == 0x10);
GG_STATIC_ASSERT(offsetof(GgBombVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgBombVector, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgBombVector, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgBombVector, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgBombVector, unknown_0E) == 0x0E);
GG_STATIC_ASSERT(sizeof(GgBombDynamicVector) == 0x18);
GG_STATIC_ASSERT(offsetof(GgBombDynamicVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgBombDynamicVector, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgBombDynamicVector, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgBombDynamicVector, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgBombDynamicVector, unknown_0E) == 0x0E);
GG_STATIC_ASSERT(offsetof(GgBombDynamicVector, ActiveCount) == 0x10);
GG_STATIC_ASSERT(offsetof(GgBombDynamicVector, CapacityIncrement) == 0x14);
