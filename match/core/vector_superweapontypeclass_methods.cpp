// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /DNDEBUG /Gy
// Retail PAVSuperWeaponTypeClass RTTI establishes the pointer element type and zero-offset
// DynamicVectorClass -> VectorClass base chain. Complete entry-origin spans
// establish the bound methods. GX emits a short derived deleting wrapper;
// no GX reproduces its full retail body. No TypeList or constructor is bound;
// original TU boundaries, final link and complete object sizes are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
#include "vector_class_operations.h"
class SuperWeaponTypeClass;

// FUNCTION: GAMEMD 0x4E9140
// DynamicVectorClass<SuperWeaponTypeClass*>::Clear

// FUNCTION: GAMEMD 0x4E9170
// DynamicVectorClass<SuperWeaponTypeClass*>::Slot5

// FUNCTION: GAMEMD 0x4E9190
// VectorClass<SuperWeaponTypeClass*>::Slot6

// FUNCTION: GAMEMD 0x4EF020
// VectorClass<SuperWeaponTypeClass*>::operator==

// FUNCTION: GAMEMD 0x4EF060
// VectorClass<SuperWeaponTypeClass*>::SetCapacity

// FUNCTION: GAMEMD 0x4EF110
// VectorClass<SuperWeaponTypeClass*>::Clear

// FUNCTION: GAMEMD 0x4EF140
// VectorClass<SuperWeaponTypeClass*>::FindItemIndex

// FUNCTION: GAMEMD 0x4EF180
// VectorClass<SuperWeaponTypeClass*>::Slot5

// FUNCTION: GAMEMD 0x4EF1A0
// DynamicVectorClass<SuperWeaponTypeClass*>::SetCapacity

// FUNCTION: GAMEMD 0x4EF250
// DynamicVectorClass<SuperWeaponTypeClass*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x4F0D90
// VectorClass<SuperWeaponTypeClass*>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x4F0DE0
// DynamicVectorClass<SuperWeaponTypeClass*>::scalar deleting destructor

// VTABLE: GAMEMD 0x7EA4C4 -- VectorClass<SuperWeaponTypeClass*>.
template class VectorClass<SuperWeaponTypeClass*>;
typedef VectorClass<SuperWeaponTypeClass*> GgSuperWeaponTypeClassVectorClass;
GG_STATIC_ASSERT(offsetof(GgSuperWeaponTypeClassVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgSuperWeaponTypeClassVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgSuperWeaponTypeClassVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgSuperWeaponTypeClassVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7EA4A4 -- DynamicVectorClass<SuperWeaponTypeClass*>.
template class DynamicVectorClass<SuperWeaponTypeClass*>;
typedef DynamicVectorClass<SuperWeaponTypeClass*> GgSuperWeaponTypeClassDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgSuperWeaponTypeClassDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgSuperWeaponTypeClassDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgSuperWeaponTypeClassDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgSuperWeaponTypeClassDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgSuperWeaponTypeClassDynamicVectorClass, ActiveCount) == 0x10);
GG_STATIC_ASSERT(offsetof(GgSuperWeaponTypeClassDynamicVectorClass, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(SuperWeaponTypeClass*) == 4);
