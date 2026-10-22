// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy
// Retail PAVUnitClass RTTI establishes the pointer element type and zero-offset
// DynamicVectorClass -> VectorClass base chain. Complete entry-origin spans
// establish the bound methods. GX emits a short derived deleting wrapper;
// no GX reproduces its full retail body. No TypeList or constructor is bound;
// original TU boundaries, final link and complete object sizes are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
#include "vector_class_operations.h"
class UnitClass;

// FUNCTION: GAMEMD 0x4E88A0
// DynamicVectorClass<UnitClass*>::Clear

// FUNCTION: GAMEMD 0x4E88D0
// DynamicVectorClass<UnitClass*>::Slot5

// FUNCTION: GAMEMD 0x4E88F0
// VectorClass<UnitClass*>::Slot6

// FUNCTION: GAMEMD 0x4EB980
// VectorClass<UnitClass*>::operator==

// FUNCTION: GAMEMD 0x4EB9C0
// VectorClass<UnitClass*>::SetCapacity

// FUNCTION: GAMEMD 0x4EBA70
// VectorClass<UnitClass*>::Clear

// FUNCTION: GAMEMD 0x4EBAA0
// VectorClass<UnitClass*>::FindItemIndex

// FUNCTION: GAMEMD 0x4EBAE0
// VectorClass<UnitClass*>::Slot5

// FUNCTION: GAMEMD 0x4EBB00
// DynamicVectorClass<UnitClass*>::SetCapacity

// FUNCTION: GAMEMD 0x4EBBB0
// DynamicVectorClass<UnitClass*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x4EFF30
// VectorClass<UnitClass*>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x4EFF80
// DynamicVectorClass<UnitClass*>::scalar deleting destructor

// VTABLE: GAMEMD 0x7E9EC4 -- VectorClass<UnitClass*>.
template class VectorClass<UnitClass*>;
typedef VectorClass<UnitClass*> GgUnitClassVectorClass;
GG_STATIC_ASSERT(offsetof(GgUnitClassVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgUnitClassVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgUnitClassVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgUnitClassVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7E9EA4 -- DynamicVectorClass<UnitClass*>.
template class DynamicVectorClass<UnitClass*>;
typedef DynamicVectorClass<UnitClass*> GgUnitClassDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgUnitClassDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgUnitClassDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgUnitClassDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgUnitClassDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgUnitClassDynamicVectorClass, ActiveCount) == 0x10);
GG_STATIC_ASSERT(offsetof(GgUnitClassDynamicVectorClass, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(UnitClass*) == 4);
