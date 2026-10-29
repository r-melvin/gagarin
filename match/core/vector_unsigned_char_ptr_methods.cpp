// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Retail PAE RTTI establishes the pointer element type and zero-offset
// DynamicVectorClass -> VectorClass base chain. Complete entry-origin spans
// establish the bound methods. GX emits a short derived deleting wrapper;
// no GX reproduces its full retail body. No TypeList or constructor is bound;
// original TU boundaries, final link and complete object sizes are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
#include "vector_class_operations.h"

// FUNCTION: GAMEMD 0x7B42C0
// DynamicVectorClass<unsigned char*>::Clear

// FUNCTION: GAMEMD 0x7B42F0
// DynamicVectorClass<unsigned char*>::Slot5

// FUNCTION: GAMEMD 0x7B4310
// VectorClass<unsigned char*>::Slot6

// FUNCTION: GAMEMD 0x7B4320
// VectorClass<unsigned char*>::operator==

// FUNCTION: GAMEMD 0x7B4360
// VectorClass<unsigned char*>::SetCapacity

// FUNCTION: GAMEMD 0x7B4410
// VectorClass<unsigned char*>::Clear

// FUNCTION: GAMEMD 0x7B4440
// VectorClass<unsigned char*>::FindItemIndex

// FUNCTION: GAMEMD 0x7B4480
// VectorClass<unsigned char*>::Slot5

// FUNCTION: GAMEMD 0x7B44A0
// DynamicVectorClass<unsigned char*>::SetCapacity

// FUNCTION: GAMEMD 0x7B4550
// DynamicVectorClass<unsigned char*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x7B4580
// VectorClass<unsigned char*>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x7B45D0
// DynamicVectorClass<unsigned char*>::scalar deleting destructor

// VTABLE: GAMEMD 0x7F7B0C -- VectorClass<unsigned char*>.
template class VectorClass<unsigned char*>;
typedef VectorClass<unsigned char*> GgUnsignedCharPtrVectorClass;
GG_STATIC_ASSERT(offsetof(GgUnsignedCharPtrVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgUnsignedCharPtrVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgUnsignedCharPtrVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgUnsignedCharPtrVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7F7AEC -- DynamicVectorClass<unsigned char*>.
template class DynamicVectorClass<unsigned char*>;
typedef DynamicVectorClass<unsigned char*> GgUnsignedCharPtrDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgUnsignedCharPtrDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgUnsignedCharPtrDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgUnsignedCharPtrDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgUnsignedCharPtrDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgUnsignedCharPtrDynamicVectorClass, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgUnsignedCharPtrDynamicVectorClass, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(unsigned char*) == 4);
