// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT
// Retail PAUGlobalPacketType RTTI establishes the pointer element type and zero-offset
// DynamicVectorClass -> VectorClass base chain. Complete entry-origin spans
// establish the bound methods. GX emits a short derived deleting wrapper;
// no GX reproduces its full retail body. No TypeList or constructor is bound;
// original TU boundaries, final link and complete object sizes are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
#include "vector_class_operations.h"

struct GlobalPacketType;

// FUNCTION: GAMEMD 0x69C600
// DynamicVectorClass<GlobalPacketType*>::Clear

// FUNCTION: GAMEMD 0x69C630
// DynamicVectorClass<GlobalPacketType*>::Slot5

// FUNCTION: GAMEMD 0x69C650
// VectorClass<GlobalPacketType*>::Slot6

// FUNCTION: GAMEMD 0x69CFA0
// VectorClass<GlobalPacketType*>::operator==

// FUNCTION: GAMEMD 0x69CFE0
// VectorClass<GlobalPacketType*>::SetCapacity

// FUNCTION: GAMEMD 0x69D090
// VectorClass<GlobalPacketType*>::Clear

// FUNCTION: GAMEMD 0x69D0C0
// VectorClass<GlobalPacketType*>::FindItemIndex

// FUNCTION: GAMEMD 0x69D100
// VectorClass<GlobalPacketType*>::Slot5

// FUNCTION: GAMEMD 0x69D120
// DynamicVectorClass<GlobalPacketType*>::SetCapacity

// FUNCTION: GAMEMD 0x69D1D0
// DynamicVectorClass<GlobalPacketType*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x69D630
// VectorClass<GlobalPacketType*>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x69D680
// DynamicVectorClass<GlobalPacketType*>::scalar deleting destructor

// VTABLE: GAMEMD 0x7F1234 -- VectorClass<GlobalPacketType*>.
template class VectorClass<GlobalPacketType*>;
typedef VectorClass<GlobalPacketType*> GgGlobalpackettypeVectorClass;
GG_STATIC_ASSERT(offsetof(GgGlobalpackettypeVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgGlobalpackettypeVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgGlobalpackettypeVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgGlobalpackettypeVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7F11D4 -- DynamicVectorClass<GlobalPacketType*>.
template class DynamicVectorClass<GlobalPacketType*>;
typedef DynamicVectorClass<GlobalPacketType*> GgGlobalpackettypeDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgGlobalpackettypeDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgGlobalpackettypeDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgGlobalpackettypeDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgGlobalpackettypeDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgGlobalpackettypeDynamicVectorClass, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgGlobalpackettypeDynamicVectorClass, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(GlobalPacketType*) == 4);
