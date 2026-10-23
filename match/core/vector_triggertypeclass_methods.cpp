// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT
// Retail PAVTriggerTypeClass RTTI establishes the pointer element type and zero-offset
// DynamicVectorClass -> VectorClass base chain. Complete entry-origin spans
// establish the bound methods. GX emits a short derived deleting wrapper;
// no GX reproduces its full retail body. No TypeList or constructor is bound;
// original TU boundaries, final link and complete object sizes are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
#include "vector_class_operations.h"

class TriggerTypeClass;

// FUNCTION: GAMEMD 0x4E85A0
// DynamicVectorClass<TriggerTypeClass*>::Clear

// FUNCTION: GAMEMD 0x4E85D0
// DynamicVectorClass<TriggerTypeClass*>::Slot5

// FUNCTION: GAMEMD 0x4E85F0
// VectorClass<TriggerTypeClass*>::Slot6

// FUNCTION: GAMEMD 0x4EA680
// VectorClass<TriggerTypeClass*>::operator==

// FUNCTION: GAMEMD 0x4EA6C0
// VectorClass<TriggerTypeClass*>::SetCapacity

// FUNCTION: GAMEMD 0x4EA770
// VectorClass<TriggerTypeClass*>::Clear

// FUNCTION: GAMEMD 0x4EA7A0
// VectorClass<TriggerTypeClass*>::FindItemIndex

// FUNCTION: GAMEMD 0x4EA7E0
// VectorClass<TriggerTypeClass*>::Slot5

// FUNCTION: GAMEMD 0x4EA800
// DynamicVectorClass<TriggerTypeClass*>::SetCapacity

// FUNCTION: GAMEMD 0x4EA8B0
// DynamicVectorClass<TriggerTypeClass*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x4EFA30
// VectorClass<TriggerTypeClass*>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x4EFA80
// DynamicVectorClass<TriggerTypeClass*>::scalar deleting destructor

// VTABLE: GAMEMD 0x7E9BC4 -- VectorClass<TriggerTypeClass*>.
template class VectorClass<TriggerTypeClass*>;
typedef VectorClass<TriggerTypeClass*> GgTriggerTypeClassVectorClass;
GG_STATIC_ASSERT(offsetof(GgTriggerTypeClassVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgTriggerTypeClassVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgTriggerTypeClassVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgTriggerTypeClassVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7E9BA4 -- DynamicVectorClass<TriggerTypeClass*>.
template class DynamicVectorClass<TriggerTypeClass*>;
typedef DynamicVectorClass<TriggerTypeClass*> GgTriggerTypeClassDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgTriggerTypeClassDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgTriggerTypeClassDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgTriggerTypeClassDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgTriggerTypeClassDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgTriggerTypeClassDynamicVectorClass, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgTriggerTypeClassDynamicVectorClass, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(TriggerTypeClass*) == 4);
