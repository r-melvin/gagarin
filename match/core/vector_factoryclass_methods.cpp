// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT
// Retail PAVFactoryClass RTTI establishes the pointer element type and zero-offset
// DynamicVectorClass -> VectorClass base chain. Complete entry-origin spans
// establish the bound methods. GX emits a short derived deleting wrapper;
// no GX reproduces its full retail body. No TypeList or constructor is bound;
// original TU boundaries, final link and complete object sizes are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
#include "vector_class_operations.h"

class FactoryClass;

// FUNCTION: GAMEMD 0x4E89C0
// DynamicVectorClass<FactoryClass*>::Clear

// FUNCTION: GAMEMD 0x4E89F0
// DynamicVectorClass<FactoryClass*>::Slot5

// FUNCTION: GAMEMD 0x4E8A10
// VectorClass<FactoryClass*>::Slot6

// FUNCTION: GAMEMD 0x4EC0A0
// VectorClass<FactoryClass*>::operator==

// FUNCTION: GAMEMD 0x4EC0E0
// VectorClass<FactoryClass*>::SetCapacity

// FUNCTION: GAMEMD 0x4EC190
// VectorClass<FactoryClass*>::Clear

// FUNCTION: GAMEMD 0x4EC1C0
// VectorClass<FactoryClass*>::FindItemIndex

// FUNCTION: GAMEMD 0x4EC200
// VectorClass<FactoryClass*>::Slot5

// FUNCTION: GAMEMD 0x4EC220
// DynamicVectorClass<FactoryClass*>::SetCapacity

// FUNCTION: GAMEMD 0x4EC2D0
// DynamicVectorClass<FactoryClass*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x4F0110
// VectorClass<FactoryClass*>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x4F0160
// DynamicVectorClass<FactoryClass*>::scalar deleting destructor

// VTABLE: GAMEMD 0x7E9FC4 -- VectorClass<FactoryClass*>.
template class VectorClass<FactoryClass*>;
typedef VectorClass<FactoryClass*> GgFactoryClassVectorClass;
GG_STATIC_ASSERT(offsetof(GgFactoryClassVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgFactoryClassVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgFactoryClassVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgFactoryClassVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7E9FA4 -- DynamicVectorClass<FactoryClass*>.
template class DynamicVectorClass<FactoryClass*>;
typedef DynamicVectorClass<FactoryClass*> GgFactoryClassDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgFactoryClassDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgFactoryClassDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgFactoryClassDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgFactoryClassDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgFactoryClassDynamicVectorClass, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgFactoryClassDynamicVectorClass, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(FactoryClass*) == 4);
