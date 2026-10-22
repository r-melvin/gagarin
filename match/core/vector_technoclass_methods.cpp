// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy
// Retail PAVTechnoClass RTTI establishes the pointer element type and zero-offset
// DynamicVectorClass -> VectorClass base chain. Complete entry-origin spans
// establish the bound methods. GX emits a short derived deleting wrapper;
// no GX reproduces its full retail body. No TypeList or constructor is bound;
// original TU boundaries, final link and complete object sizes are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
#include "vector_class_operations.h"

class TechnoClass;

// FUNCTION: GAMEMD 0x40B6A0
// DynamicVectorClass<TechnoClass*>::Clear

// FUNCTION: GAMEMD 0x40B6D0
// DynamicVectorClass<TechnoClass*>::Slot5

// FUNCTION: GAMEMD 0x40B6F0
// VectorClass<TechnoClass*>::Slot6

// FUNCTION: GAMEMD 0x40B960
// VectorClass<TechnoClass*>::operator==

// FUNCTION: GAMEMD 0x40B9A0
// VectorClass<TechnoClass*>::SetCapacity

// FUNCTION: GAMEMD 0x40BA50
// VectorClass<TechnoClass*>::Clear

// FUNCTION: GAMEMD 0x40BA80
// VectorClass<TechnoClass*>::FindItemIndex

// FUNCTION: GAMEMD 0x40BAC0
// VectorClass<TechnoClass*>::Slot5

// FUNCTION: GAMEMD 0x40BAE0
// DynamicVectorClass<TechnoClass*>::SetCapacity

// FUNCTION: GAMEMD 0x40BB90
// DynamicVectorClass<TechnoClass*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x40BC60
// VectorClass<TechnoClass*>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x40BCB0
// DynamicVectorClass<TechnoClass*>::scalar deleting destructor

// VTABLE: GAMEMD 0x7E180C -- VectorClass<TechnoClass*>.
template class VectorClass<TechnoClass*>;
typedef VectorClass<TechnoClass*> GgTechnoClassVectorClass;
GG_STATIC_ASSERT(offsetof(GgTechnoClassVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgTechnoClassVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgTechnoClassVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgTechnoClassVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7E17AC -- DynamicVectorClass<TechnoClass*>.
template class DynamicVectorClass<TechnoClass*>;
typedef DynamicVectorClass<TechnoClass*> GgTechnoClassDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgTechnoClassDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgTechnoClassDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgTechnoClassDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgTechnoClassDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgTechnoClassDynamicVectorClass, ActiveCount) == 0x10);
GG_STATIC_ASSERT(offsetof(GgTechnoClassDynamicVectorClass, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(TechnoClass*) == 4);
