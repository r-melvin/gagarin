// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy
// Retail PAVInfantryClass RTTI establishes the pointer element type and zero-offset
// DynamicVectorClass -> VectorClass base chain. Complete entry-origin spans
// establish the bound methods. GX emits a short derived deleting wrapper;
// no GX reproduces its full retail body. No TypeList or constructor is bound;
// original TU boundaries, final link and complete object sizes are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
#include "vector_class_operations.h"
class InfantryClass;

// FUNCTION: GAMEMD 0x459FF0
// DynamicVectorClass<InfantryClass*>::Clear

// FUNCTION: GAMEMD 0x45A020
// DynamicVectorClass<InfantryClass*>::Slot5

// FUNCTION: GAMEMD 0x45A040
// VectorClass<InfantryClass*>::Slot6

// FUNCTION: GAMEMD 0x45A3E0
// VectorClass<InfantryClass*>::operator==

// FUNCTION: GAMEMD 0x45A420
// VectorClass<InfantryClass*>::SetCapacity

// FUNCTION: GAMEMD 0x45A4D0
// VectorClass<InfantryClass*>::Clear

// FUNCTION: GAMEMD 0x45A500
// VectorClass<InfantryClass*>::FindItemIndex

// FUNCTION: GAMEMD 0x45A540
// VectorClass<InfantryClass*>::Slot5

// FUNCTION: GAMEMD 0x45A560
// DynamicVectorClass<InfantryClass*>::SetCapacity

// FUNCTION: GAMEMD 0x45A610
// DynamicVectorClass<InfantryClass*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x45AA60
// VectorClass<InfantryClass*>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x45AAB0
// DynamicVectorClass<InfantryClass*>::scalar deleting destructor

// VTABLE: GAMEMD 0x7E43E8 -- VectorClass<InfantryClass*>.
template class VectorClass<InfantryClass*>;
typedef VectorClass<InfantryClass*> GgInfantryClassVectorClass;
GG_STATIC_ASSERT(offsetof(GgInfantryClassVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgInfantryClassVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgInfantryClassVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgInfantryClassVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7E43C8 -- DynamicVectorClass<InfantryClass*>.
template class DynamicVectorClass<InfantryClass*>;
typedef DynamicVectorClass<InfantryClass*> GgInfantryClassDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgInfantryClassDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgInfantryClassDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgInfantryClassDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgInfantryClassDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgInfantryClassDynamicVectorClass, ActiveCount) == 0x10);
GG_STATIC_ASSERT(offsetof(GgInfantryClassDynamicVectorClass, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(InfantryClass*) == 4);
