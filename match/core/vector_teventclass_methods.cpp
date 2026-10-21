// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /DNDEBUG /Gy
// Retail PAVTEventClass RTTI establishes the pointer element type and zero-offset
// DynamicVectorClass -> VectorClass base chain. Complete entry-origin spans
// establish the bound methods. GX emits a short derived deleting wrapper;
// no GX reproduces its full retail body. No TypeList or constructor is bound;
// original TU boundaries, final link and complete object sizes are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
#include "vector_class_operations.h"

class TEventClass;

// FUNCTION: GAMEMD 0x71FBA0
// DynamicVectorClass<TEventClass*>::Clear

// FUNCTION: GAMEMD 0x71FBD0
// DynamicVectorClass<TEventClass*>::Slot5

// FUNCTION: GAMEMD 0x71FBF0
// VectorClass<TEventClass*>::Slot6

// FUNCTION: GAMEMD 0x71FC00
// VectorClass<TEventClass*>::operator==

// FUNCTION: GAMEMD 0x71FC40
// VectorClass<TEventClass*>::SetCapacity

// FUNCTION: GAMEMD 0x71FCF0
// VectorClass<TEventClass*>::Clear

// FUNCTION: GAMEMD 0x71FD20
// VectorClass<TEventClass*>::FindItemIndex

// FUNCTION: GAMEMD 0x71FD60
// VectorClass<TEventClass*>::Slot5

// FUNCTION: GAMEMD 0x71FD80
// DynamicVectorClass<TEventClass*>::SetCapacity

// FUNCTION: GAMEMD 0x71FE30
// DynamicVectorClass<TEventClass*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x71FE60
// VectorClass<TEventClass*>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x71FEB0
// DynamicVectorClass<TEventClass*>::scalar deleting destructor

// VTABLE: GAMEMD 0x7F552C -- VectorClass<TEventClass*>.
template class VectorClass<TEventClass*>;
typedef VectorClass<TEventClass*> GgTEventClassVectorClass;
GG_STATIC_ASSERT(offsetof(GgTEventClassVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgTEventClassVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgTEventClassVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgTEventClassVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7F550C -- DynamicVectorClass<TEventClass*>.
template class DynamicVectorClass<TEventClass*>;
typedef DynamicVectorClass<TEventClass*> GgTEventClassDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgTEventClassDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgTEventClassDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgTEventClassDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgTEventClassDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgTEventClassDynamicVectorClass, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgTEventClassDynamicVectorClass, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(TEventClass*) == 4);
