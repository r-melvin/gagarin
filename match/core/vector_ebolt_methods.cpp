// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT
// Retail PAVEBolt RTTI establishes the pointer element type and zero-offset
// DynamicVectorClass -> VectorClass base chain. Complete entry-origin spans
// establish the bound methods. GX emits a short derived deleting wrapper;
// no GX reproduces its full retail body. No TypeList or constructor is bound;
// original TU boundaries, final link and complete object sizes are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
#include "vector_class_operations.h"

class EBolt;

// FUNCTION: GAMEMD 0x4C2C40
// DynamicVectorClass<EBolt*>::Clear

// FUNCTION: GAMEMD 0x4C2C70
// DynamicVectorClass<EBolt*>::Slot5

// FUNCTION: GAMEMD 0x4C2C90
// VectorClass<EBolt*>::Slot6

// FUNCTION: GAMEMD 0x4C2CA0
// VectorClass<EBolt*>::operator==

// FUNCTION: GAMEMD 0x4C2CE0
// VectorClass<EBolt*>::SetCapacity

// FUNCTION: GAMEMD 0x4C2D90
// VectorClass<EBolt*>::Clear

// FUNCTION: GAMEMD 0x4C2DC0
// VectorClass<EBolt*>::FindItemIndex

// FUNCTION: GAMEMD 0x4C2E00
// VectorClass<EBolt*>::Slot5

// FUNCTION: GAMEMD 0x4C2E20
// DynamicVectorClass<EBolt*>::SetCapacity

// FUNCTION: GAMEMD 0x4C2ED0
// DynamicVectorClass<EBolt*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x4C2F00
// VectorClass<EBolt*>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x4C2F50
// DynamicVectorClass<EBolt*>::scalar deleting destructor

// VTABLE: GAMEMD 0x7E86AC -- VectorClass<EBolt*>.
template class VectorClass<EBolt*>;
typedef VectorClass<EBolt*> GgEboltVectorClass;
GG_STATIC_ASSERT(offsetof(GgEboltVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgEboltVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgEboltVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgEboltVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7E868C -- DynamicVectorClass<EBolt*>.
template class DynamicVectorClass<EBolt*>;
typedef DynamicVectorClass<EBolt*> GgEboltDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgEboltDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgEboltDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgEboltDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgEboltDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgEboltDynamicVectorClass, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgEboltDynamicVectorClass, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(EBolt*) == 4);
