// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy
// Retail PAVWarheadTypeClass RTTI establishes the pointer element type and zero-offset
// DynamicVectorClass -> VectorClass base chain. Complete entry-origin spans
// establish the bound methods. GX emits a short derived deleting wrapper;
// no GX reproduces its full retail body. No TypeList or constructor is bound;
// original TU boundaries, final link and complete object sizes are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
#include "vector_class_operations.h"
class WarheadTypeClass;

// FUNCTION: GAMEMD 0x40F5E0
// DynamicVectorClass<WarheadTypeClass*>::Clear

// FUNCTION: GAMEMD 0x40F610
// DynamicVectorClass<WarheadTypeClass*>::Slot5

// FUNCTION: GAMEMD 0x40F630
// VectorClass<WarheadTypeClass*>::Slot6

// FUNCTION: GAMEMD 0x40F640
// VectorClass<WarheadTypeClass*>::operator==

// FUNCTION: GAMEMD 0x40F680
// VectorClass<WarheadTypeClass*>::SetCapacity

// FUNCTION: GAMEMD 0x40F730
// VectorClass<WarheadTypeClass*>::Clear

// FUNCTION: GAMEMD 0x40F760
// VectorClass<WarheadTypeClass*>::FindItemIndex

// FUNCTION: GAMEMD 0x40F7A0
// VectorClass<WarheadTypeClass*>::Slot5

// FUNCTION: GAMEMD 0x40F7C0
// DynamicVectorClass<WarheadTypeClass*>::SetCapacity

// FUNCTION: GAMEMD 0x40F870
// DynamicVectorClass<WarheadTypeClass*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x40F8A0
// VectorClass<WarheadTypeClass*>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x40F8F0
// DynamicVectorClass<WarheadTypeClass*>::scalar deleting destructor

// VTABLE: GAMEMD 0x7E1EA4 -- VectorClass<WarheadTypeClass*>.
template class VectorClass<WarheadTypeClass*>;
typedef VectorClass<WarheadTypeClass*> GgWarheadTypeClassVectorClass;
GG_STATIC_ASSERT(offsetof(GgWarheadTypeClassVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgWarheadTypeClassVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgWarheadTypeClassVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgWarheadTypeClassVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7E1E84 -- DynamicVectorClass<WarheadTypeClass*>.
template class DynamicVectorClass<WarheadTypeClass*>;
typedef DynamicVectorClass<WarheadTypeClass*> GgWarheadTypeClassDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgWarheadTypeClassDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgWarheadTypeClassDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgWarheadTypeClassDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgWarheadTypeClassDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgWarheadTypeClassDynamicVectorClass, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgWarheadTypeClassDynamicVectorClass, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(WarheadTypeClass*) == 4);
