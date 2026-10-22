// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy
// Retail PAVTemporalClass RTTI establishes the pointer element type and zero-offset
// DynamicVectorClass -> VectorClass base chain. Complete entry-origin spans
// establish the bound methods. GX emits a short derived deleting wrapper;
// no GX reproduces its full retail body. No TypeList or constructor is bound;
// original TU boundaries, final link and complete object sizes are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
#include "vector_class_operations.h"

class TemporalClass;

// FUNCTION: GAMEMD 0x71B240
// DynamicVectorClass<TemporalClass*>::Clear

// FUNCTION: GAMEMD 0x71B270
// DynamicVectorClass<TemporalClass*>::Slot5

// FUNCTION: GAMEMD 0x71B290
// VectorClass<TemporalClass*>::Slot6

// FUNCTION: GAMEMD 0x71B2A0
// VectorClass<TemporalClass*>::operator==

// FUNCTION: GAMEMD 0x71B2E0
// VectorClass<TemporalClass*>::SetCapacity

// FUNCTION: GAMEMD 0x71B390
// VectorClass<TemporalClass*>::Clear

// FUNCTION: GAMEMD 0x71B3C0
// VectorClass<TemporalClass*>::FindItemIndex

// FUNCTION: GAMEMD 0x71B400
// VectorClass<TemporalClass*>::Slot5

// FUNCTION: GAMEMD 0x71B420
// DynamicVectorClass<TemporalClass*>::SetCapacity

// FUNCTION: GAMEMD 0x71B4D0
// DynamicVectorClass<TemporalClass*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x71B500
// VectorClass<TemporalClass*>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x71B550
// DynamicVectorClass<TemporalClass*>::scalar deleting destructor

// VTABLE: GAMEMD 0x7F5134 -- VectorClass<TemporalClass*>.
template class VectorClass<TemporalClass*>;
typedef VectorClass<TemporalClass*> GgTemporalClassVectorClass;
GG_STATIC_ASSERT(offsetof(GgTemporalClassVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgTemporalClassVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgTemporalClassVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgTemporalClassVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7F5114 -- DynamicVectorClass<TemporalClass*>.
template class DynamicVectorClass<TemporalClass*>;
typedef DynamicVectorClass<TemporalClass*> GgTemporalClassDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgTemporalClassDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgTemporalClassDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgTemporalClassDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgTemporalClassDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgTemporalClassDynamicVectorClass, ActiveCount) == 0x10);
GG_STATIC_ASSERT(offsetof(GgTemporalClassDynamicVectorClass, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(TemporalClass*) == 4);
