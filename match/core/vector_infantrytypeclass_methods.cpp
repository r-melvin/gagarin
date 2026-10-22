// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy
// Retail PAVInfantryTypeClass RTTI establishes the pointer element type and zero-offset
// DynamicVectorClass -> VectorClass base chain. Complete entry-origin spans
// establish the bound methods. GX emits a short derived deleting wrapper;
// no GX reproduces its full retail body. No TypeList or constructor is bound;
// original TU boundaries, final link and complete object sizes are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
#include "vector_class_operations.h"
class InfantryTypeClass;

// FUNCTION: GAMEMD 0x4E8F00
// DynamicVectorClass<InfantryTypeClass*>::Clear

// FUNCTION: GAMEMD 0x4E8F30
// DynamicVectorClass<InfantryTypeClass*>::Slot5

// FUNCTION: GAMEMD 0x4E8F50
// VectorClass<InfantryTypeClass*>::Slot6

// FUNCTION: GAMEMD 0x4EE1E0
// VectorClass<InfantryTypeClass*>::operator==

// FUNCTION: GAMEMD 0x4EE220
// VectorClass<InfantryTypeClass*>::SetCapacity

// FUNCTION: GAMEMD 0x4EE2D0
// VectorClass<InfantryTypeClass*>::Clear

// FUNCTION: GAMEMD 0x4EE300
// VectorClass<InfantryTypeClass*>::FindItemIndex

// FUNCTION: GAMEMD 0x4EE340
// VectorClass<InfantryTypeClass*>::Slot5

// FUNCTION: GAMEMD 0x4EE360
// DynamicVectorClass<InfantryTypeClass*>::SetCapacity

// FUNCTION: GAMEMD 0x4EE410
// DynamicVectorClass<InfantryTypeClass*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x4F09D0
// VectorClass<InfantryTypeClass*>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x4F0A20
// DynamicVectorClass<InfantryTypeClass*>::scalar deleting destructor

// VTABLE: GAMEMD 0x7EA344 -- VectorClass<InfantryTypeClass*>.
template class VectorClass<InfantryTypeClass*>;
typedef VectorClass<InfantryTypeClass*> GgInfantryTypeClassVectorClass;
GG_STATIC_ASSERT(offsetof(GgInfantryTypeClassVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgInfantryTypeClassVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgInfantryTypeClassVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgInfantryTypeClassVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7EA324 -- DynamicVectorClass<InfantryTypeClass*>.
template class DynamicVectorClass<InfantryTypeClass*>;
typedef DynamicVectorClass<InfantryTypeClass*> GgInfantryTypeClassDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgInfantryTypeClassDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgInfantryTypeClassDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgInfantryTypeClassDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgInfantryTypeClassDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgInfantryTypeClassDynamicVectorClass, ActiveCount) == 0x10);
GG_STATIC_ASSERT(offsetof(GgInfantryTypeClassDynamicVectorClass, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(InfantryTypeClass*) == 4);
