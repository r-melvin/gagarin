// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy
// Retail PAVMSTextEntry RTTI establishes the pointer element type and zero-offset
// DynamicVectorClass -> VectorClass base chain. Complete entry-origin spans
// establish the bound methods. GX emits a short derived deleting wrapper;
// no GX reproduces its full retail body. No TypeList or constructor is bound;
// original TU boundaries, final link and complete object sizes are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
#include "vector_class_operations.h"

class MSTextEntry;

// FUNCTION: GAMEMD 0x5D0610
// DynamicVectorClass<MSTextEntry*>::Clear

// FUNCTION: GAMEMD 0x5D0640
// DynamicVectorClass<MSTextEntry*>::Slot5

// FUNCTION: GAMEMD 0x5D0660
// VectorClass<MSTextEntry*>::Slot6

// FUNCTION: GAMEMD 0x5D0AE0
// VectorClass<MSTextEntry*>::operator==

// FUNCTION: GAMEMD 0x5D0B20
// VectorClass<MSTextEntry*>::SetCapacity

// FUNCTION: GAMEMD 0x5D0BD0
// VectorClass<MSTextEntry*>::Clear

// FUNCTION: GAMEMD 0x5D0C00
// VectorClass<MSTextEntry*>::FindItemIndex

// FUNCTION: GAMEMD 0x5D0C40
// VectorClass<MSTextEntry*>::Slot5

// FUNCTION: GAMEMD 0x5D0C60
// DynamicVectorClass<MSTextEntry*>::SetCapacity

// FUNCTION: GAMEMD 0x5D0D10
// DynamicVectorClass<MSTextEntry*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x5D1760
// VectorClass<MSTextEntry*>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x5D17B0
// DynamicVectorClass<MSTextEntry*>::scalar deleting destructor

// VTABLE: GAMEMD 0x7EEB94 -- VectorClass<MSTextEntry*>.
template class VectorClass<MSTextEntry*>;
typedef VectorClass<MSTextEntry*> GgMSTextEntryVectorClass;
GG_STATIC_ASSERT(offsetof(GgMSTextEntryVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgMSTextEntryVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgMSTextEntryVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgMSTextEntryVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7EEB34 -- DynamicVectorClass<MSTextEntry*>.
template class DynamicVectorClass<MSTextEntry*>;
typedef DynamicVectorClass<MSTextEntry*> GgMSTextEntryDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgMSTextEntryDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgMSTextEntryDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgMSTextEntryDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgMSTextEntryDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgMSTextEntryDynamicVectorClass, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgMSTextEntryDynamicVectorClass, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(MSTextEntry*) == 4);
