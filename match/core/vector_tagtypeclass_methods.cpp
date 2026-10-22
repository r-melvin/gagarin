// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy
// Retail PAVTagTypeClass RTTI establishes the pointer element type and zero-offset
// DynamicVectorClass -> VectorClass base chain. Complete entry-origin spans
// establish the bound methods. GX emits a short derived deleting wrapper;
// no GX reproduces its full retail body. No TypeList or constructor is bound;
// original TU boundaries, final link and complete object sizes are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
#include "vector_class_operations.h"

class TagTypeClass;

// FUNCTION: GAMEMD 0x6E64E0
// DynamicVectorClass<TagTypeClass*>::Clear

// FUNCTION: GAMEMD 0x6E6510
// DynamicVectorClass<TagTypeClass*>::Slot5

// FUNCTION: GAMEMD 0x6E6530
// VectorClass<TagTypeClass*>::Slot6

// FUNCTION: GAMEMD 0x6E6540
// VectorClass<TagTypeClass*>::operator==

// FUNCTION: GAMEMD 0x6E6580
// VectorClass<TagTypeClass*>::SetCapacity

// FUNCTION: GAMEMD 0x6E6630
// VectorClass<TagTypeClass*>::Clear

// FUNCTION: GAMEMD 0x6E6660
// VectorClass<TagTypeClass*>::FindItemIndex

// FUNCTION: GAMEMD 0x6E66A0
// VectorClass<TagTypeClass*>::Slot5

// FUNCTION: GAMEMD 0x6E66C0
// DynamicVectorClass<TagTypeClass*>::SetCapacity

// FUNCTION: GAMEMD 0x6E6770
// DynamicVectorClass<TagTypeClass*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x6E67A0
// VectorClass<TagTypeClass*>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x6E67F0
// DynamicVectorClass<TagTypeClass*>::scalar deleting destructor

// VTABLE: GAMEMD 0x7F4578 -- VectorClass<TagTypeClass*>.
template class VectorClass<TagTypeClass*>;
typedef VectorClass<TagTypeClass*> GgTagTypeClassVectorClass;
GG_STATIC_ASSERT(offsetof(GgTagTypeClassVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgTagTypeClassVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgTagTypeClassVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgTagTypeClassVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7F4558 -- DynamicVectorClass<TagTypeClass*>.
template class DynamicVectorClass<TagTypeClass*>;
typedef DynamicVectorClass<TagTypeClass*> GgTagTypeClassDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgTagTypeClassDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgTagTypeClassDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgTagTypeClassDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgTagTypeClassDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgTagTypeClassDynamicVectorClass, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgTagTypeClassDynamicVectorClass, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(TagTypeClass*) == 4);
