// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy
// Retail PAVDiskLaserClass RTTI establishes the pointer element type and zero-offset
// DynamicVectorClass -> VectorClass base chain. Complete entry-origin spans
// establish the bound methods. GX emits a short derived deleting wrapper;
// no GX reproduces its full retail body. No TypeList or constructor is bound;
// original TU boundaries, final link and complete object sizes are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
#include "vector_class_operations.h"

class DiskLaserClass;

// FUNCTION: GAMEMD 0x4A7D20
// DynamicVectorClass<DiskLaserClass*>::Clear

// FUNCTION: GAMEMD 0x4A7D50
// DynamicVectorClass<DiskLaserClass*>::Slot5

// FUNCTION: GAMEMD 0x4A7D70
// VectorClass<DiskLaserClass*>::Slot6

// FUNCTION: GAMEMD 0x4A7D80
// VectorClass<DiskLaserClass*>::operator==

// FUNCTION: GAMEMD 0x4A7DC0
// VectorClass<DiskLaserClass*>::SetCapacity

// FUNCTION: GAMEMD 0x4A7E70
// VectorClass<DiskLaserClass*>::Clear

// FUNCTION: GAMEMD 0x4A7EA0
// VectorClass<DiskLaserClass*>::FindItemIndex

// FUNCTION: GAMEMD 0x4A7EE0
// VectorClass<DiskLaserClass*>::Slot5

// FUNCTION: GAMEMD 0x4A7F00
// DynamicVectorClass<DiskLaserClass*>::SetCapacity

// FUNCTION: GAMEMD 0x4A7FB0
// DynamicVectorClass<DiskLaserClass*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x4A8030
// VectorClass<DiskLaserClass*>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x4A8080
// DynamicVectorClass<DiskLaserClass*>::scalar deleting destructor

// VTABLE: GAMEMD 0x7E5EFC -- VectorClass<DiskLaserClass*>.
template class VectorClass<DiskLaserClass*>;
typedef VectorClass<DiskLaserClass*> GgDiskLaserClassVectorClass;
GG_STATIC_ASSERT(offsetof(GgDiskLaserClassVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgDiskLaserClassVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgDiskLaserClassVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgDiskLaserClassVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7E5EDC -- DynamicVectorClass<DiskLaserClass*>.
template class DynamicVectorClass<DiskLaserClass*>;
typedef DynamicVectorClass<DiskLaserClass*> GgDiskLaserClassDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgDiskLaserClassDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgDiskLaserClassDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgDiskLaserClassDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgDiskLaserClassDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgDiskLaserClassDynamicVectorClass, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgDiskLaserClassDynamicVectorClass, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(DiskLaserClass*) == 4);
