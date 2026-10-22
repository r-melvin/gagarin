// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /DNDEBUG /Gy
// Retail PAUtConnInfoStruct RTTI establishes the pointer element type and zero-offset
// DynamicVectorClass -> VectorClass base chain. Complete entry-origin spans
// establish the bound methods. GX emits a short derived deleting wrapper;
// no GX reproduces its full retail body. No TypeList or constructor is bound;
// original TU boundaries, final link and complete object sizes are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
#include "vector_class_operations.h"

struct tConnInfoStruct;

// FUNCTION: GAMEMD 0x7AC970
// DynamicVectorClass<tConnInfoStruct*>::Clear

// FUNCTION: GAMEMD 0x7AC9A0
// DynamicVectorClass<tConnInfoStruct*>::Slot5

// FUNCTION: GAMEMD 0x7AC9C0
// VectorClass<tConnInfoStruct*>::Slot6

// FUNCTION: GAMEMD 0x7AD090
// VectorClass<tConnInfoStruct*>::operator==

// FUNCTION: GAMEMD 0x7AD0D0
// VectorClass<tConnInfoStruct*>::SetCapacity

// FUNCTION: GAMEMD 0x7AD180
// VectorClass<tConnInfoStruct*>::Clear

// FUNCTION: GAMEMD 0x7AD1B0
// VectorClass<tConnInfoStruct*>::FindItemIndex

// FUNCTION: GAMEMD 0x7AD1F0
// VectorClass<tConnInfoStruct*>::Slot5

// FUNCTION: GAMEMD 0x7AD210
// DynamicVectorClass<tConnInfoStruct*>::SetCapacity

// FUNCTION: GAMEMD 0x7AD2C0
// DynamicVectorClass<tConnInfoStruct*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x7AD370
// VectorClass<tConnInfoStruct*>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x7AD3C0
// DynamicVectorClass<tConnInfoStruct*>::scalar deleting destructor

// VTABLE: GAMEMD 0x7F78A4 -- VectorClass<tConnInfoStruct*>.
template class VectorClass<tConnInfoStruct*>;
typedef VectorClass<tConnInfoStruct*> GgtConnInfoStructVectorClass;
GG_STATIC_ASSERT(offsetof(GgtConnInfoStructVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgtConnInfoStructVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgtConnInfoStructVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgtConnInfoStructVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7F78C4 -- DynamicVectorClass<tConnInfoStruct*>.
template class DynamicVectorClass<tConnInfoStruct*>;
typedef DynamicVectorClass<tConnInfoStruct*> GgtConnInfoStructDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgtConnInfoStructDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgtConnInfoStructDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgtConnInfoStructDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgtConnInfoStructDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgtConnInfoStructDynamicVectorClass, ActiveCount) == 0x10);
GG_STATIC_ASSERT(offsetof(GgtConnInfoStructDynamicVectorClass, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(tConnInfoStruct*) == 4);
