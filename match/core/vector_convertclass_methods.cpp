// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /DNDEBUG /Gy
// Retail PAVConvertClass RTTI establishes the pointer element type and zero-offset
// DynamicVectorClass -> VectorClass base chain. Complete entry-origin spans
// establish the bound methods. GX emits a short derived deleting wrapper;
// no GX reproduces its full retail body. No TypeList or constructor is bound;
// original TU boundaries, final link and complete object sizes are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
#include "vector_class_operations.h"

class ConvertClass;

// FUNCTION: GAMEMD 0x491390
// DynamicVectorClass<ConvertClass*>::Clear

// FUNCTION: GAMEMD 0x4913C0
// DynamicVectorClass<ConvertClass*>::Slot5

// FUNCTION: GAMEMD 0x4913E0
// VectorClass<ConvertClass*>::Slot6

// FUNCTION: GAMEMD 0x49AE80
// VectorClass<ConvertClass*>::operator==

// FUNCTION: GAMEMD 0x49AEC0
// VectorClass<ConvertClass*>::SetCapacity

// FUNCTION: GAMEMD 0x49AF70
// VectorClass<ConvertClass*>::Clear

// FUNCTION: GAMEMD 0x49AFA0
// VectorClass<ConvertClass*>::FindItemIndex

// FUNCTION: GAMEMD 0x49AFE0
// VectorClass<ConvertClass*>::Slot5

// FUNCTION: GAMEMD 0x49B000
// DynamicVectorClass<ConvertClass*>::SetCapacity

// FUNCTION: GAMEMD 0x49B0B0
// DynamicVectorClass<ConvertClass*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x49B0E0
// VectorClass<ConvertClass*>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x49B130
// DynamicVectorClass<ConvertClass*>::scalar deleting destructor

// VTABLE: GAMEMD 0x7E5338 -- VectorClass<ConvertClass*>.
template class VectorClass<ConvertClass*>;
typedef VectorClass<ConvertClass*> GgConvertClassVectorClass;
GG_STATIC_ASSERT(offsetof(GgConvertClassVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgConvertClassVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgConvertClassVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgConvertClassVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7E5318 -- DynamicVectorClass<ConvertClass*>.
template class DynamicVectorClass<ConvertClass*>;
typedef DynamicVectorClass<ConvertClass*> GgConvertClassDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgConvertClassDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgConvertClassDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgConvertClassDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgConvertClassDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgConvertClassDynamicVectorClass, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgConvertClassDynamicVectorClass, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(ConvertClass*) == 4);
