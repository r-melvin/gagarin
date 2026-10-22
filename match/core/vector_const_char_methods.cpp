// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy
// Retail PBD RTTI establishes the pointer element type and zero-offset
// DynamicVectorClass -> VectorClass base chain. Complete entry-origin spans
// establish the bound methods. GX emits a short derived deleting wrapper;
// no GX reproduces its full retail body. No TypeList or constructor is bound;
// original TU boundaries, final link and complete object sizes are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
#include "vector_class_operations.h"

// FUNCTION: GAMEMD 0x5C0A70
// DynamicVectorClass<const char*>::Clear

// FUNCTION: GAMEMD 0x5C0AA0
// DynamicVectorClass<const char*>::Slot5

// FUNCTION: GAMEMD 0x5C0AC0
// VectorClass<const char*>::Slot6

// FUNCTION: GAMEMD 0x5C0AD0
// VectorClass<const char*>::operator==

// FUNCTION: GAMEMD 0x5C0B10
// VectorClass<const char*>::SetCapacity

// FUNCTION: GAMEMD 0x5C0BC0
// VectorClass<const char*>::Clear

// FUNCTION: GAMEMD 0x5C0BF0
// VectorClass<const char*>::FindItemIndex

// FUNCTION: GAMEMD 0x5C0C30
// VectorClass<const char*>::Slot5

// FUNCTION: GAMEMD 0x5C0C50
// DynamicVectorClass<const char*>::SetCapacity

// FUNCTION: GAMEMD 0x5C0D00
// DynamicVectorClass<const char*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x5C0D30
// VectorClass<const char*>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x5C0D80
// DynamicVectorClass<const char*>::scalar deleting destructor

// VTABLE: GAMEMD 0x7EE0D4 -- VectorClass<const char*>.
template class VectorClass<const char*>;
typedef VectorClass<const char*> GgConstCharVectorClass;
GG_STATIC_ASSERT(offsetof(GgConstCharVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgConstCharVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgConstCharVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgConstCharVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7EE0B4 -- DynamicVectorClass<const char*>.
template class DynamicVectorClass<const char*>;
typedef DynamicVectorClass<const char*> GgConstCharDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgConstCharDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgConstCharDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgConstCharDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgConstCharDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgConstCharDynamicVectorClass, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgConstCharDynamicVectorClass, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(const char*) == 4);
