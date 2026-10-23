// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT
// Retail PAVTiberiumClass RTTI establishes the pointer element type and zero-offset
// DynamicVectorClass -> VectorClass base chain. Complete entry-origin spans
// establish the bound methods. GX emits a short derived deleting wrapper;
// no GX reproduces its full retail body. No TypeList or constructor is bound;
// original TU boundaries, final link and complete object sizes are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
#include "vector_class_operations.h"

class TiberiumClass;

// FUNCTION: GAMEMD 0x723730
// DynamicVectorClass<TiberiumClass*>::Clear

// FUNCTION: GAMEMD 0x723760
// DynamicVectorClass<TiberiumClass*>::Slot5

// FUNCTION: GAMEMD 0x723780
// VectorClass<TiberiumClass*>::Slot6

// FUNCTION: GAMEMD 0x723790
// VectorClass<TiberiumClass*>::operator==

// FUNCTION: GAMEMD 0x7237D0
// VectorClass<TiberiumClass*>::SetCapacity

// FUNCTION: GAMEMD 0x723880
// VectorClass<TiberiumClass*>::Clear

// FUNCTION: GAMEMD 0x7238B0
// VectorClass<TiberiumClass*>::FindItemIndex

// FUNCTION: GAMEMD 0x7238F0
// VectorClass<TiberiumClass*>::Slot5

// FUNCTION: GAMEMD 0x723910
// DynamicVectorClass<TiberiumClass*>::SetCapacity

// FUNCTION: GAMEMD 0x7239C0
// DynamicVectorClass<TiberiumClass*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x7239F0
// VectorClass<TiberiumClass*>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x723A40
// DynamicVectorClass<TiberiumClass*>::scalar deleting destructor

// VTABLE: GAMEMD 0x7F56DC -- VectorClass<TiberiumClass*>.
template class VectorClass<TiberiumClass*>;
typedef VectorClass<TiberiumClass*> GgTiberiumClassVectorClass;
GG_STATIC_ASSERT(offsetof(GgTiberiumClassVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgTiberiumClassVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgTiberiumClassVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgTiberiumClassVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7F56BC -- DynamicVectorClass<TiberiumClass*>.
template class DynamicVectorClass<TiberiumClass*>;
typedef DynamicVectorClass<TiberiumClass*> GgTiberiumClassDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgTiberiumClassDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgTiberiumClassDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgTiberiumClassDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgTiberiumClassDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgTiberiumClassDynamicVectorClass, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgTiberiumClassDynamicVectorClass, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(TiberiumClass*) == 4);
