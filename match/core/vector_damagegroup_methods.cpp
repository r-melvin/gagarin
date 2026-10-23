// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT
// Retail PAUDamageGroup RTTI establishes the pointer element type and zero-offset
// DynamicVectorClass -> VectorClass base chain. Complete entry-origin spans
// establish the bound methods. GX emits a short derived deleting wrapper;
// no GX reproduces its full retail body. No TypeList or constructor is bound;
// original TU boundaries, final link and complete object sizes are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
#include "vector_class_operations.h"

struct DamageGroup;

// FUNCTION: GAMEMD 0x48AD10
// DynamicVectorClass<DamageGroup*>::Clear

// FUNCTION: GAMEMD 0x48AD40
// DynamicVectorClass<DamageGroup*>::Slot5

// FUNCTION: GAMEMD 0x48AD60
// VectorClass<DamageGroup*>::Slot6

// FUNCTION: GAMEMD 0x48AD70
// VectorClass<DamageGroup*>::operator==

// FUNCTION: GAMEMD 0x48ADB0
// VectorClass<DamageGroup*>::SetCapacity

// FUNCTION: GAMEMD 0x48AE60
// VectorClass<DamageGroup*>::Clear

// FUNCTION: GAMEMD 0x48AE90
// VectorClass<DamageGroup*>::FindItemIndex

// FUNCTION: GAMEMD 0x48AED0
// VectorClass<DamageGroup*>::Slot5

// FUNCTION: GAMEMD 0x48AEF0
// DynamicVectorClass<DamageGroup*>::SetCapacity

// FUNCTION: GAMEMD 0x48AFA0
// DynamicVectorClass<DamageGroup*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x48AFD0
// VectorClass<DamageGroup*>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x48B020
// DynamicVectorClass<DamageGroup*>::scalar deleting destructor

// VTABLE: GAMEMD 0x7E5144 -- VectorClass<DamageGroup*>.
template class VectorClass<DamageGroup*>;
typedef VectorClass<DamageGroup*> GgDamageGroupVectorClass;
GG_STATIC_ASSERT(offsetof(GgDamageGroupVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgDamageGroupVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgDamageGroupVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgDamageGroupVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7E5170 -- DynamicVectorClass<DamageGroup*>.
template class DynamicVectorClass<DamageGroup*>;
typedef DynamicVectorClass<DamageGroup*> GgDamageGroupDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgDamageGroupDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgDamageGroupDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgDamageGroupDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgDamageGroupDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgDamageGroupDynamicVectorClass, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgDamageGroupDynamicVectorClass, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(DamageGroup*) == 4);
