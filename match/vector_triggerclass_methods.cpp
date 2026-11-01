// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Retail PAVTriggerClass RTTI establishes the pointer element type and zero-offset
// DynamicVectorClass -> VectorClass base chain. Complete entry-origin spans
// establish the bound methods. GX emits a short derived deleting wrapper;
// no GX reproduces its full retail body. No TypeList or constructor is bound;
// original TU boundaries, final link and complete object sizes are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
#include "vector_class_operations.h"
class TriggerClass;

// FUNCTION: GAMEMD 0x4E8540
// DynamicVectorClass<TriggerClass*>::Clear

// FUNCTION: GAMEMD 0x4E8570
// DynamicVectorClass<TriggerClass*>::Slot5

// FUNCTION: GAMEMD 0x4E8590
// VectorClass<TriggerClass*>::Slot6

// FUNCTION: GAMEMD 0x4EA420
// VectorClass<TriggerClass*>::operator==

// FUNCTION: GAMEMD 0x4EA460
// VectorClass<TriggerClass*>::SetCapacity

// FUNCTION: GAMEMD 0x4EA510
// VectorClass<TriggerClass*>::Clear

// FUNCTION: GAMEMD 0x4EA540
// VectorClass<TriggerClass*>::FindItemIndex

// FUNCTION: GAMEMD 0x4EA580
// VectorClass<TriggerClass*>::Slot5

// FUNCTION: GAMEMD 0x4EA5A0
// DynamicVectorClass<TriggerClass*>::SetCapacity

// FUNCTION: GAMEMD 0x4EA650
// DynamicVectorClass<TriggerClass*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x4EF990
// VectorClass<TriggerClass*>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x4EF9E0
// DynamicVectorClass<TriggerClass*>::scalar deleting destructor

// VTABLE: GAMEMD 0x7E9C04 -- VectorClass<TriggerClass*>.
template class VectorClass<TriggerClass*>;
typedef VectorClass<TriggerClass*> GgTriggerClassVectorClass;
GG_STATIC_ASSERT(offsetof(GgTriggerClassVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgTriggerClassVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgTriggerClassVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgTriggerClassVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7E9BE4 -- DynamicVectorClass<TriggerClass*>.
template class DynamicVectorClass<TriggerClass*>;
typedef DynamicVectorClass<TriggerClass*> GgTriggerClassDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgTriggerClassDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgTriggerClassDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgTriggerClassDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgTriggerClassDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgTriggerClassDynamicVectorClass, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgTriggerClassDynamicVectorClass, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(TriggerClass*) == 4);
