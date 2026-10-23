// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT
// Retail PAVTagClass RTTI establishes the pointer element type and zero-offset
// DynamicVectorClass -> VectorClass base chain. Complete entry-origin spans
// establish the bound methods. GX emits a short derived deleting wrapper;
// no GX reproduces its full retail body. No TypeList or constructor is bound;
// original TU boundaries, final link and complete object sizes are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
#include "vector_class_operations.h"
class TagClass;

// FUNCTION: GAMEMD 0x4E8290
// DynamicVectorClass<TagClass*>::Clear

// FUNCTION: GAMEMD 0x4E82C0
// DynamicVectorClass<TagClass*>::Slot5

// FUNCTION: GAMEMD 0x4E82E0
// VectorClass<TagClass*>::Slot6

// FUNCTION: GAMEMD 0x4E9200
// VectorClass<TagClass*>::operator==

// FUNCTION: GAMEMD 0x4E9240
// VectorClass<TagClass*>::SetCapacity

// FUNCTION: GAMEMD 0x4E92F0
// VectorClass<TagClass*>::Clear

// FUNCTION: GAMEMD 0x4E9320
// VectorClass<TagClass*>::FindItemIndex

// FUNCTION: GAMEMD 0x4E9360
// VectorClass<TagClass*>::Slot5

// FUNCTION: GAMEMD 0x4E9380
// DynamicVectorClass<TagClass*>::SetCapacity

// FUNCTION: GAMEMD 0x4E9430
// DynamicVectorClass<TagClass*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x4EF4E0
// VectorClass<TagClass*>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x4EF530
// DynamicVectorClass<TagClass*>::scalar deleting destructor

// VTABLE: GAMEMD 0x7EA5C4 -- VectorClass<TagClass*>.
template class VectorClass<TagClass*>;
typedef VectorClass<TagClass*> GgTagClassVectorClass;
GG_STATIC_ASSERT(offsetof(GgTagClassVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgTagClassVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgTagClassVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgTagClassVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7EA5A4 -- DynamicVectorClass<TagClass*>.
template class DynamicVectorClass<TagClass*>;
typedef DynamicVectorClass<TagClass*> GgTagClassDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgTagClassDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgTagClassDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgTagClassDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgTagClassDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgTagClassDynamicVectorClass, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgTagClassDynamicVectorClass, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(TagClass*) == 4);
