// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /DNDEBUG /Gy
// Retail PAVAbstractTypeClass RTTI establishes the pointer element type and zero-offset
// DynamicVectorClass -> VectorClass base chain. Complete entry-origin spans
// establish the bound methods. GX emits a short derived deleting wrapper;
// no GX reproduces its full retail body. No TypeList or constructor is bound;
// original TU boundaries, final link and complete object sizes are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
#include "vector_class_operations.h"

class AbstractTypeClass;

// FUNCTION: GAMEMD 0x4E91A0
// DynamicVectorClass<AbstractTypeClass*>::Clear

// FUNCTION: GAMEMD 0x4E91D0
// DynamicVectorClass<AbstractTypeClass*>::Slot5

// FUNCTION: GAMEMD 0x4E91F0
// VectorClass<AbstractTypeClass*>::Slot6

// FUNCTION: GAMEMD 0x4EF280
// VectorClass<AbstractTypeClass*>::operator==

// FUNCTION: GAMEMD 0x4EF2C0
// VectorClass<AbstractTypeClass*>::SetCapacity

// FUNCTION: GAMEMD 0x4EF370
// VectorClass<AbstractTypeClass*>::Clear

// FUNCTION: GAMEMD 0x4EF3A0
// VectorClass<AbstractTypeClass*>::FindItemIndex

// FUNCTION: GAMEMD 0x4EF3E0
// VectorClass<AbstractTypeClass*>::Slot5

// FUNCTION: GAMEMD 0x4EF400
// DynamicVectorClass<AbstractTypeClass*>::SetCapacity

// FUNCTION: GAMEMD 0x4EF4B0
// DynamicVectorClass<AbstractTypeClass*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x4F0E30
// VectorClass<AbstractTypeClass*>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x4F0E80
// DynamicVectorClass<AbstractTypeClass*>::scalar deleting destructor

// VTABLE: GAMEMD 0x7EA544 -- VectorClass<AbstractTypeClass*>.
template class VectorClass<AbstractTypeClass*>;
typedef VectorClass<AbstractTypeClass*> GgAbstractTypeClassVectorClass;
GG_STATIC_ASSERT(offsetof(GgAbstractTypeClassVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgAbstractTypeClassVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgAbstractTypeClassVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgAbstractTypeClassVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7EA524 -- DynamicVectorClass<AbstractTypeClass*>.
template class DynamicVectorClass<AbstractTypeClass*>;
typedef DynamicVectorClass<AbstractTypeClass*> GgAbstractTypeClassDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgAbstractTypeClassDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgAbstractTypeClassDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgAbstractTypeClassDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgAbstractTypeClassDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgAbstractTypeClassDynamicVectorClass, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgAbstractTypeClassDynamicVectorClass, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(AbstractTypeClass*) == 4);
