// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Retail PAVBulletClass RTTI establishes the pointer element type and zero-offset
// DynamicVectorClass -> VectorClass base chain. Complete entry-origin spans
// establish the bound methods. GX emits a short derived deleting wrapper;
// no GX reproduces its full retail body. No TypeList or constructor is bound;
// original TU boundaries, final link and complete object sizes are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
#include "vector_class_operations.h"
class BulletClass;

// FUNCTION: GAMEMD 0x46B5E0
// DynamicVectorClass<BulletClass*>::Clear

// FUNCTION: GAMEMD 0x46B610
// DynamicVectorClass<BulletClass*>::Slot5

// FUNCTION: GAMEMD 0x46B630
// VectorClass<BulletClass*>::Slot6

// FUNCTION: GAMEMD 0x46B660
// VectorClass<BulletClass*>::operator==

// FUNCTION: GAMEMD 0x46B6A0
// VectorClass<BulletClass*>::SetCapacity

// FUNCTION: GAMEMD 0x46B750
// VectorClass<BulletClass*>::Clear

// FUNCTION: GAMEMD 0x46B780
// VectorClass<BulletClass*>::FindItemIndex

// FUNCTION: GAMEMD 0x46B7C0
// VectorClass<BulletClass*>::Slot5

// FUNCTION: GAMEMD 0x46B7E0
// DynamicVectorClass<BulletClass*>::SetCapacity

// FUNCTION: GAMEMD 0x46B890
// DynamicVectorClass<BulletClass*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x46B8C0
// VectorClass<BulletClass*>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x46B910
// DynamicVectorClass<BulletClass*>::scalar deleting destructor

// VTABLE: GAMEMD 0x7E4698 -- VectorClass<BulletClass*>.
template class VectorClass<BulletClass*>;
typedef VectorClass<BulletClass*> GgBulletClassVectorClass;
GG_STATIC_ASSERT(offsetof(GgBulletClassVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgBulletClassVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgBulletClassVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgBulletClassVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7E4678 -- DynamicVectorClass<BulletClass*>.
template class DynamicVectorClass<BulletClass*>;
typedef DynamicVectorClass<BulletClass*> GgBulletClassDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgBulletClassDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgBulletClassDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgBulletClassDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgBulletClassDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgBulletClassDynamicVectorClass, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgBulletClassDynamicVectorClass, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(BulletClass*) == 4);
