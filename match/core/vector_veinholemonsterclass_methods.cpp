// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT
// Retail PAVVeinholeMonsterClass RTTI establishes the pointer element type and zero-offset
// DynamicVectorClass -> VectorClass base chain. Complete entry-origin spans
// establish the bound methods. GX emits a short derived deleting wrapper;
// no GX reproduces its full retail body. No TypeList or constructor is bound;
// original TU boundaries, final link and complete object sizes are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
#include "vector_class_operations.h"

class VeinholeMonsterClass;

// FUNCTION: GAMEMD 0x74F360
// DynamicVectorClass<VeinholeMonsterClass*>::Clear

// FUNCTION: GAMEMD 0x74F390
// DynamicVectorClass<VeinholeMonsterClass*>::Slot5

// FUNCTION: GAMEMD 0x74F3B0
// VectorClass<VeinholeMonsterClass*>::Slot6

// FUNCTION: GAMEMD 0x74F3C0
// VectorClass<VeinholeMonsterClass*>::operator==

// FUNCTION: GAMEMD 0x74F400
// VectorClass<VeinholeMonsterClass*>::SetCapacity

// FUNCTION: GAMEMD 0x74F4B0
// VectorClass<VeinholeMonsterClass*>::Clear

// FUNCTION: GAMEMD 0x74F4E0
// VectorClass<VeinholeMonsterClass*>::FindItemIndex

// FUNCTION: GAMEMD 0x74F520
// VectorClass<VeinholeMonsterClass*>::Slot5

// FUNCTION: GAMEMD 0x74F540
// DynamicVectorClass<VeinholeMonsterClass*>::SetCapacity

// FUNCTION: GAMEMD 0x74F5F0
// DynamicVectorClass<VeinholeMonsterClass*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x74F650
// VectorClass<VeinholeMonsterClass*>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x74F6A0
// DynamicVectorClass<VeinholeMonsterClass*>::scalar deleting destructor

// VTABLE: GAMEMD 0x7F665C -- VectorClass<VeinholeMonsterClass*>.
template class VectorClass<VeinholeMonsterClass*>;
typedef VectorClass<VeinholeMonsterClass*> GgVeinholeMonsterClassVectorClass;
GG_STATIC_ASSERT(offsetof(GgVeinholeMonsterClassVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgVeinholeMonsterClassVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgVeinholeMonsterClassVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgVeinholeMonsterClassVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7F663C -- DynamicVectorClass<VeinholeMonsterClass*>.
template class DynamicVectorClass<VeinholeMonsterClass*>;
typedef DynamicVectorClass<VeinholeMonsterClass*> GgVeinholeMonsterClassDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgVeinholeMonsterClassDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgVeinholeMonsterClassDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgVeinholeMonsterClassDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgVeinholeMonsterClassDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgVeinholeMonsterClassDynamicVectorClass, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgVeinholeMonsterClassDynamicVectorClass, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(VeinholeMonsterClass*) == 4);
