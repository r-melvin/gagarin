// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy
// Retail PAVUnitTypeClass RTTI establishes the pointer element type and zero-offset
// DynamicVectorClass -> VectorClass base chain. Complete entry-origin spans
// establish the bound methods. GX emits a short derived deleting wrapper;
// no GX reproduces its full retail body. No TypeList or constructor is bound;
// original TU boundaries, final link and complete object sizes are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
#include "vector_class_operations.h"
class UnitTypeClass;

// FUNCTION: GAMEMD 0x4E8E40
// DynamicVectorClass<UnitTypeClass*>::Clear

// FUNCTION: GAMEMD 0x4E8E70
// DynamicVectorClass<UnitTypeClass*>::Slot5

// FUNCTION: GAMEMD 0x4E8E90
// VectorClass<UnitTypeClass*>::Slot6

// FUNCTION: GAMEMD 0x4EDD20
// VectorClass<UnitTypeClass*>::operator==

// FUNCTION: GAMEMD 0x4EDD60
// VectorClass<UnitTypeClass*>::SetCapacity

// FUNCTION: GAMEMD 0x4EDE10
// VectorClass<UnitTypeClass*>::Clear

// FUNCTION: GAMEMD 0x4EDE40
// VectorClass<UnitTypeClass*>::FindItemIndex

// FUNCTION: GAMEMD 0x4EDE80
// VectorClass<UnitTypeClass*>::Slot5

// FUNCTION: GAMEMD 0x4EDEA0
// DynamicVectorClass<UnitTypeClass*>::SetCapacity

// FUNCTION: GAMEMD 0x4EDF50
// DynamicVectorClass<UnitTypeClass*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x4F0890
// VectorClass<UnitTypeClass*>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x4F08E0
// DynamicVectorClass<UnitTypeClass*>::scalar deleting destructor

// VTABLE: GAMEMD 0x7EA2C4 -- VectorClass<UnitTypeClass*>.
template class VectorClass<UnitTypeClass*>;
typedef VectorClass<UnitTypeClass*> GgUnitTypeClassVectorClass;
GG_STATIC_ASSERT(offsetof(GgUnitTypeClassVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgUnitTypeClassVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgUnitTypeClassVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgUnitTypeClassVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7EA2A4 -- DynamicVectorClass<UnitTypeClass*>.
template class DynamicVectorClass<UnitTypeClass*>;
typedef DynamicVectorClass<UnitTypeClass*> GgUnitTypeClassDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgUnitTypeClassDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgUnitTypeClassDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgUnitTypeClassDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgUnitTypeClassDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgUnitTypeClassDynamicVectorClass, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgUnitTypeClassDynamicVectorClass, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(UnitTypeClass*) == 4);
