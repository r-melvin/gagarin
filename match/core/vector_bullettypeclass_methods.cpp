// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT
// Retail PAVBulletTypeClass RTTI establishes the pointer element type and zero-offset
// DynamicVectorClass -> VectorClass base chain. Complete entry-origin spans
// establish the bound methods. GX emits a short derived deleting wrapper;
// no GX reproduces its full retail body. No TypeList or constructor is bound;
// original TU boundaries, final link and complete object sizes are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
#include "vector_class_operations.h"

class BulletTypeClass;

// FUNCTION: GAMEMD 0x4E8F60
// DynamicVectorClass<BulletTypeClass*>::Clear

// FUNCTION: GAMEMD 0x4E8F90
// DynamicVectorClass<BulletTypeClass*>::Slot5

// FUNCTION: GAMEMD 0x4E8FB0
// VectorClass<BulletTypeClass*>::Slot6

// FUNCTION: GAMEMD 0x4EE440
// VectorClass<BulletTypeClass*>::operator==

// FUNCTION: GAMEMD 0x4EE480
// VectorClass<BulletTypeClass*>::SetCapacity

// FUNCTION: GAMEMD 0x4EE530
// VectorClass<BulletTypeClass*>::Clear

// FUNCTION: GAMEMD 0x4EE560
// VectorClass<BulletTypeClass*>::FindItemIndex

// FUNCTION: GAMEMD 0x4EE5A0
// VectorClass<BulletTypeClass*>::Slot5

// FUNCTION: GAMEMD 0x4EE5C0
// DynamicVectorClass<BulletTypeClass*>::SetCapacity

// FUNCTION: GAMEMD 0x4EE670
// DynamicVectorClass<BulletTypeClass*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x4F0A70
// VectorClass<BulletTypeClass*>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x4F0AC0
// DynamicVectorClass<BulletTypeClass*>::scalar deleting destructor

// VTABLE: GAMEMD 0x7EA384 -- VectorClass<BulletTypeClass*>.
template class VectorClass<BulletTypeClass*>;
typedef VectorClass<BulletTypeClass*> GgBullettypeclassVectorClass;
GG_STATIC_ASSERT(offsetof(GgBullettypeclassVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgBullettypeclassVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgBullettypeclassVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgBullettypeclassVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7EA364 -- DynamicVectorClass<BulletTypeClass*>.
template class DynamicVectorClass<BulletTypeClass*>;
typedef DynamicVectorClass<BulletTypeClass*> GgBullettypeclassDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgBullettypeclassDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgBullettypeclassDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgBullettypeclassDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgBullettypeclassDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgBullettypeclassDynamicVectorClass, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgBullettypeclassDynamicVectorClass, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(BulletTypeClass*) == 4);
