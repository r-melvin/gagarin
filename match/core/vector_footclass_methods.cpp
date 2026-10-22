// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy
// Retail PAVFootClass RTTI establishes the pointer element type and zero-offset
// DynamicVectorClass -> VectorClass base chain. Complete entry-origin spans
// establish the bound methods. GX emits a short derived deleting wrapper;
// no GX reproduces its full retail body. No TypeList or constructor is bound;
// original TU boundaries, final link and complete object sizes are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
#include "vector_class_operations.h"
class FootClass;

// FUNCTION: GAMEMD 0x4E01F0
// DynamicVectorClass<FootClass*>::Clear

// FUNCTION: GAMEMD 0x4E0220
// DynamicVectorClass<FootClass*>::Slot5

// FUNCTION: GAMEMD 0x4E0240
// VectorClass<FootClass*>::Slot6

// FUNCTION: GAMEMD 0x4E0580
// VectorClass<FootClass*>::operator==

// FUNCTION: GAMEMD 0x4E05C0
// VectorClass<FootClass*>::SetCapacity

// FUNCTION: GAMEMD 0x4E0670
// VectorClass<FootClass*>::Clear

// FUNCTION: GAMEMD 0x4E06A0
// VectorClass<FootClass*>::FindItemIndex

// FUNCTION: GAMEMD 0x4E06E0
// VectorClass<FootClass*>::Slot5

// FUNCTION: GAMEMD 0x4E0700
// DynamicVectorClass<FootClass*>::SetCapacity

// FUNCTION: GAMEMD 0x4E07B0
// DynamicVectorClass<FootClass*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x4E0CE0
// VectorClass<FootClass*>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x4E0D30
// DynamicVectorClass<FootClass*>::scalar deleting destructor

// VTABLE: GAMEMD 0x7E8C48 -- VectorClass<FootClass*>.
template class VectorClass<FootClass*>;
typedef VectorClass<FootClass*> GgFootClassVectorClass;
GG_STATIC_ASSERT(offsetof(GgFootClassVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgFootClassVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgFootClassVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgFootClassVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7E8C28 -- DynamicVectorClass<FootClass*>.
template class DynamicVectorClass<FootClass*>;
typedef DynamicVectorClass<FootClass*> GgFootClassDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgFootClassDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgFootClassDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgFootClassDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgFootClassDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgFootClassDynamicVectorClass, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgFootClassDynamicVectorClass, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(FootClass*) == 4);
