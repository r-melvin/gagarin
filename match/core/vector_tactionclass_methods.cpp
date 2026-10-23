// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT
// Retail PAVTActionClass RTTI establishes the pointer element type and zero-offset
// DynamicVectorClass -> VectorClass base chain. Complete entry-origin spans
// establish the bound methods. GX emits a short derived deleting wrapper;
// no GX reproduces its full retail body. No TypeList or constructor is bound;
// original TU boundaries, final link and complete object sizes are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
#include "vector_class_operations.h"

class TActionClass;

// FUNCTION: GAMEMD 0x6E47F0
// DynamicVectorClass<TActionClass*>::Clear

// FUNCTION: GAMEMD 0x6E4820
// DynamicVectorClass<TActionClass*>::Slot5

// FUNCTION: GAMEMD 0x6E4840
// VectorClass<TActionClass*>::Slot6

// FUNCTION: GAMEMD 0x6E4850
// VectorClass<TActionClass*>::operator==

// FUNCTION: GAMEMD 0x6E4890
// VectorClass<TActionClass*>::SetCapacity

// FUNCTION: GAMEMD 0x6E4940
// VectorClass<TActionClass*>::Clear

// FUNCTION: GAMEMD 0x6E4970
// VectorClass<TActionClass*>::FindItemIndex

// FUNCTION: GAMEMD 0x6E49B0
// VectorClass<TActionClass*>::Slot5

// FUNCTION: GAMEMD 0x6E49D0
// DynamicVectorClass<TActionClass*>::SetCapacity

// FUNCTION: GAMEMD 0x6E4A80
// DynamicVectorClass<TActionClass*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x6E4AB0
// VectorClass<TActionClass*>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x6E4B00
// DynamicVectorClass<TActionClass*>::scalar deleting destructor

// VTABLE: GAMEMD 0x7F43F0 -- VectorClass<TActionClass*>.
template class VectorClass<TActionClass*>;
typedef VectorClass<TActionClass*> GgTActionClassVectorClass;
GG_STATIC_ASSERT(offsetof(GgTActionClassVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgTActionClassVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgTActionClassVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgTActionClassVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7F43D0 -- DynamicVectorClass<TActionClass*>.
template class DynamicVectorClass<TActionClass*>;
typedef DynamicVectorClass<TActionClass*> GgTActionClassDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgTActionClassDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgTActionClassDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgTActionClassDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgTActionClassDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgTActionClassDynamicVectorClass, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgTActionClassDynamicVectorClass, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(TActionClass*) == 4);
