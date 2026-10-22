// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy
// Retail RTTI TypeDescriptors 0x836890 and 0x8368C0 identify
// VectorClass<EventClass*> and DynamicVectorClass<EventClass*>; the latter's
// CHD names the former as its zero-offset base.
// Complete entry spans bind these methods. Original TUs and standalone
// constructors are unestablished; the derived deleting body needs GX off.
#include "vector_class_operations.h"
class EventClass;

// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.

// FUNCTION: GAMEMD 0x63DC80
// DynamicVectorClass<EventClass*>::Clear
// FUNCTION: GAMEMD 0x63DCB0
// DynamicVectorClass<EventClass*>::Slot5
// FUNCTION: GAMEMD 0x63DCD0
// VectorClass<EventClass*>::Slot6
// FUNCTION: GAMEMD 0x63E650
// VectorClass<EventClass*>::operator==
// FUNCTION: GAMEMD 0x63E690
// VectorClass<EventClass*>::SetCapacity
// FUNCTION: GAMEMD 0x63E740
// VectorClass<EventClass*>::Clear
// FUNCTION: GAMEMD 0x63E770
// VectorClass<EventClass*>::FindItemIndex
// FUNCTION: GAMEMD 0x63E7B0
// VectorClass<EventClass*>::Slot5
// FUNCTION: GAMEMD 0x63E7D0
// DynamicVectorClass<EventClass*>::SetCapacity
// FUNCTION: GAMEMD 0x63E8D0
// DynamicVectorClass<EventClass*>::FindItemIndex
// SYNTHETIC: GAMEMD 0x63EE30
// VectorClass<EventClass*>::scalar deleting destructor
// SYNTHETIC: GAMEMD 0x63EE80
// DynamicVectorClass<EventClass*>::scalar deleting destructor

// VTABLE: GAMEMD 0x7EFE24 -- VectorClass<EventClass*>.
template class VectorClass<EventClass*>;
// VTABLE: GAMEMD 0x7EFE04 -- DynamicVectorClass<EventClass*>.
template class DynamicVectorClass<EventClass*>;

typedef VectorClass<EventClass*> GgEventVector;
typedef DynamicVectorClass<EventClass*> GgEventDynamicVector;
GG_STATIC_ASSERT(sizeof(EventClass*) == 4);
GG_STATIC_ASSERT(sizeof(GgEventVector) == 0x10);
GG_STATIC_ASSERT(offsetof(GgEventVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgEventVector, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgEventVector, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgEventVector, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgEventVector, unknown_0E) == 0x0E);
GG_STATIC_ASSERT(sizeof(GgEventDynamicVector) == 0x18);
GG_STATIC_ASSERT(offsetof(GgEventDynamicVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgEventDynamicVector, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgEventDynamicVector, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgEventDynamicVector, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgEventDynamicVector, unknown_0E) == 0x0E);
GG_STATIC_ASSERT(offsetof(GgEventDynamicVector, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgEventDynamicVector, CapacityIncrement) == 0x14);
