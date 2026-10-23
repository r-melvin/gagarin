// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT
// Retail PAVHouseClass RTTI establishes the pointer element type and zero-offset
// DynamicVectorClass -> VectorClass base chain. Complete entry-origin spans
// establish the bound methods. GX emits a short derived deleting wrapper;
// no GX reproduces its full retail body. No TypeList or constructor is bound;
// original TU boundaries, final link and complete object sizes are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
#include "vector_class_operations.h"
class HouseClass;

// FUNCTION: GAMEMD 0x4E8900
// DynamicVectorClass<HouseClass*>::Clear

// FUNCTION: GAMEMD 0x4E8930
// DynamicVectorClass<HouseClass*>::Slot5

// FUNCTION: GAMEMD 0x4E8950
// VectorClass<HouseClass*>::Slot6

// FUNCTION: GAMEMD 0x4EBBE0
// VectorClass<HouseClass*>::operator==

// FUNCTION: GAMEMD 0x4EBC20
// VectorClass<HouseClass*>::SetCapacity

// FUNCTION: GAMEMD 0x4EBCD0
// VectorClass<HouseClass*>::Clear

// FUNCTION: GAMEMD 0x4EBD00
// VectorClass<HouseClass*>::FindItemIndex

// FUNCTION: GAMEMD 0x4EBD40
// VectorClass<HouseClass*>::Slot5

// FUNCTION: GAMEMD 0x4EBD60
// DynamicVectorClass<HouseClass*>::SetCapacity

// FUNCTION: GAMEMD 0x4EBE10
// DynamicVectorClass<HouseClass*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x4EFFD0
// VectorClass<HouseClass*>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x4F0020
// DynamicVectorClass<HouseClass*>::scalar deleting destructor

// VTABLE: GAMEMD 0x7E9F04 -- VectorClass<HouseClass*>.
template class VectorClass<HouseClass*>;
typedef VectorClass<HouseClass*> GgHouseClassVectorClass;
GG_STATIC_ASSERT(offsetof(GgHouseClassVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgHouseClassVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgHouseClassVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgHouseClassVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7E9EE4 -- DynamicVectorClass<HouseClass*>.
template class DynamicVectorClass<HouseClass*>;
typedef DynamicVectorClass<HouseClass*> GgHouseClassDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgHouseClassDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgHouseClassDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgHouseClassDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgHouseClassDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgHouseClassDynamicVectorClass, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgHouseClassDynamicVectorClass, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(HouseClass*) == 4);
