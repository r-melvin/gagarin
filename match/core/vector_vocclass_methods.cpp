// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /DNDEBUG /Gy
// Retail PAVVocClass RTTI establishes the pointer element type and zero-offset
// DynamicVectorClass -> VectorClass base chain. Complete entry-origin spans
// establish the bound methods. GX emits a short derived deleting wrapper;
// no GX reproduces its full retail body. No TypeList or constructor is bound;
// original TU boundaries, final link and complete object sizes are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
#include "vector_class_operations.h"

class VocClass;

// FUNCTION: GAMEMD 0x7518D0
// DynamicVectorClass<VocClass*>::Clear

// FUNCTION: GAMEMD 0x751900
// DynamicVectorClass<VocClass*>::Slot5

// FUNCTION: GAMEMD 0x751920
// VectorClass<VocClass*>::Slot6

// FUNCTION: GAMEMD 0x751930
// VectorClass<VocClass*>::operator==

// FUNCTION: GAMEMD 0x751970
// VectorClass<VocClass*>::SetCapacity

// FUNCTION: GAMEMD 0x751A20
// VectorClass<VocClass*>::Clear

// FUNCTION: GAMEMD 0x751A50
// VectorClass<VocClass*>::FindItemIndex

// FUNCTION: GAMEMD 0x751A90
// VectorClass<VocClass*>::Slot5

// FUNCTION: GAMEMD 0x751AB0
// DynamicVectorClass<VocClass*>::SetCapacity

// FUNCTION: GAMEMD 0x751B60
// DynamicVectorClass<VocClass*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x751B90
// VectorClass<VocClass*>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x751BE0
// DynamicVectorClass<VocClass*>::scalar deleting destructor

// VTABLE: GAMEMD 0x7F68CC -- VectorClass<VocClass*>.
template class VectorClass<VocClass*>;
typedef VectorClass<VocClass*> GgVocClassVectorClass;
GG_STATIC_ASSERT(offsetof(GgVocClassVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgVocClassVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgVocClassVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgVocClassVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7F68AC -- DynamicVectorClass<VocClass*>.
template class DynamicVectorClass<VocClass*>;
typedef DynamicVectorClass<VocClass*> GgVocClassDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgVocClassDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgVocClassDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgVocClassDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgVocClassDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgVocClassDynamicVectorClass, ActiveCount) == 0x10);
GG_STATIC_ASSERT(offsetof(GgVocClassDynamicVectorClass, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(VocClass*) == 4);
