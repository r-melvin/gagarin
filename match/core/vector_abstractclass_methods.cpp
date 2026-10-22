// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy
// Retail PAVAbstractClass RTTI establishes the pointer element type and zero-offset
// DynamicVectorClass -> VectorClass base chain. Complete entry-origin spans
// establish the bound methods. GX emits a short derived deleting wrapper;
// no GX reproduces its full retail body. No TypeList or constructor is bound;
// original TU boundaries, final link and complete object sizes are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
#include "vector_class_operations.h"
class AbstractClass;

// FUNCTION: GAMEMD 0x4E0190
// DynamicVectorClass<AbstractClass*>::Clear

// FUNCTION: GAMEMD 0x4E01C0
// DynamicVectorClass<AbstractClass*>::Slot5

// FUNCTION: GAMEMD 0x4E01E0
// VectorClass<AbstractClass*>::Slot6

// SYNTHETIC: GAMEMD 0x4E0270
// DynamicVectorClass<AbstractClass*>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x4E02D0
// VectorClass<AbstractClass*>::scalar deleting destructor

// FUNCTION: GAMEMD 0x4E0320
// VectorClass<AbstractClass*>::operator==

// FUNCTION: GAMEMD 0x4E0360
// VectorClass<AbstractClass*>::SetCapacity

// FUNCTION: GAMEMD 0x4E0410
// VectorClass<AbstractClass*>::Clear

// FUNCTION: GAMEMD 0x4E0440
// VectorClass<AbstractClass*>::FindItemIndex

// FUNCTION: GAMEMD 0x4E0480
// VectorClass<AbstractClass*>::Slot5

// FUNCTION: GAMEMD 0x4E04A0
// DynamicVectorClass<AbstractClass*>::SetCapacity

// FUNCTION: GAMEMD 0x4E0550
// DynamicVectorClass<AbstractClass*>::FindItemIndex

// VTABLE: GAMEMD 0x7E920C -- VectorClass<AbstractClass*>.
template class VectorClass<AbstractClass*>;
typedef VectorClass<AbstractClass*> GgAbstractClassVectorClass;
GG_STATIC_ASSERT(offsetof(GgAbstractClassVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgAbstractClassVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgAbstractClassVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgAbstractClassVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7E91EC -- DynamicVectorClass<AbstractClass*>.
template class DynamicVectorClass<AbstractClass*>;
typedef DynamicVectorClass<AbstractClass*> GgAbstractClassDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgAbstractClassDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgAbstractClassDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgAbstractClassDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgAbstractClassDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgAbstractClassDynamicVectorClass, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgAbstractClassDynamicVectorClass, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(AbstractClass*) == 4);
