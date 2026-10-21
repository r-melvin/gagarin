// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /DNDEBUG /Gy
// Retail PAVAITriggerTypeClass RTTI establishes the pointer element type and zero-offset
// DynamicVectorClass -> VectorClass base chain. Complete entry-origin spans
// establish the bound methods. GX emits a short derived deleting wrapper;
// no GX reproduces its full retail body. No TypeList or constructor is bound;
// original TU boundaries, final link and complete object sizes are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
#include "vector_class_operations.h"

class AITriggerTypeClass;

// FUNCTION: GAMEMD 0x4E83B0
// DynamicVectorClass<AITriggerTypeClass*>::Clear

// FUNCTION: GAMEMD 0x4E83E0
// DynamicVectorClass<AITriggerTypeClass*>::Slot5

// FUNCTION: GAMEMD 0x4E8400
// VectorClass<AITriggerTypeClass*>::Slot6

// FUNCTION: GAMEMD 0x4E9920
// VectorClass<AITriggerTypeClass*>::operator==

// FUNCTION: GAMEMD 0x4E9960
// VectorClass<AITriggerTypeClass*>::SetCapacity

// FUNCTION: GAMEMD 0x4E9A10
// VectorClass<AITriggerTypeClass*>::Clear

// FUNCTION: GAMEMD 0x4E9A40
// VectorClass<AITriggerTypeClass*>::FindItemIndex

// FUNCTION: GAMEMD 0x4E9A80
// VectorClass<AITriggerTypeClass*>::Slot5

// FUNCTION: GAMEMD 0x4E9AA0
// DynamicVectorClass<AITriggerTypeClass*>::SetCapacity

// FUNCTION: GAMEMD 0x4E9B50
// DynamicVectorClass<AITriggerTypeClass*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x4EF6C0
// VectorClass<AITriggerTypeClass*>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x4EF710
// DynamicVectorClass<AITriggerTypeClass*>::scalar deleting destructor

// VTABLE: GAMEMD 0x7E9B84 -- VectorClass<AITriggerTypeClass*>.
template class VectorClass<AITriggerTypeClass*>;
typedef VectorClass<AITriggerTypeClass*> GgAITriggerTypeClassVectorClass;
GG_STATIC_ASSERT(offsetof(GgAITriggerTypeClassVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgAITriggerTypeClassVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgAITriggerTypeClassVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgAITriggerTypeClassVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7E9B64 -- DynamicVectorClass<AITriggerTypeClass*>.
template class DynamicVectorClass<AITriggerTypeClass*>;
typedef DynamicVectorClass<AITriggerTypeClass*> GgAITriggerTypeClassDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgAITriggerTypeClassDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgAITriggerTypeClassDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgAITriggerTypeClassDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgAITriggerTypeClassDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgAITriggerTypeClassDynamicVectorClass, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgAITriggerTypeClassDynamicVectorClass, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(AITriggerTypeClass*) == 4);
