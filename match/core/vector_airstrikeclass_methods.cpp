// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /DNDEBUG /Gy
// Retail RTTI TypeDescriptors 0x818058 and 0x818088 identify
// VectorClass<AirstrikeClass*> and DynamicVectorClass<AirstrikeClass*>;
// the latter's CHD names the former as its zero-offset base.
// Full entry-origin spans bind these methods; no original TU or standalone
// constructor is claimed. No GX matches the full derived deleting body.
#include "vector_class_operations.h"
class AirstrikeClass;

// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.

// FUNCTION: GAMEMD 0x41DDE0
// DynamicVectorClass<AirstrikeClass*>::Clear
// FUNCTION: GAMEMD 0x41DE10
// DynamicVectorClass<AirstrikeClass*>::Slot5
// FUNCTION: GAMEMD 0x41DE30
// VectorClass<AirstrikeClass*>::Slot6
// FUNCTION: GAMEMD 0x41DE40
// VectorClass<AirstrikeClass*>::operator==
// FUNCTION: GAMEMD 0x41DE80
// VectorClass<AirstrikeClass*>::SetCapacity
// FUNCTION: GAMEMD 0x41DF30
// VectorClass<AirstrikeClass*>::Clear
// FUNCTION: GAMEMD 0x41DF60
// VectorClass<AirstrikeClass*>::FindItemIndex
// FUNCTION: GAMEMD 0x41DFA0
// VectorClass<AirstrikeClass*>::Slot5
// FUNCTION: GAMEMD 0x41DFC0
// DynamicVectorClass<AirstrikeClass*>::SetCapacity
// FUNCTION: GAMEMD 0x41E070
// DynamicVectorClass<AirstrikeClass*>::FindItemIndex
// SYNTHETIC: GAMEMD 0x41E0A0
// VectorClass<AirstrikeClass*>::scalar deleting destructor
// SYNTHETIC: GAMEMD 0x41E0F0
// DynamicVectorClass<AirstrikeClass*>::scalar deleting destructor

// VTABLE: GAMEMD 0x7E295C -- VectorClass<AirstrikeClass*>.
template class VectorClass<AirstrikeClass*>;
// VTABLE: GAMEMD 0x7E293C -- DynamicVectorClass<AirstrikeClass*>.
template class DynamicVectorClass<AirstrikeClass*>;

typedef VectorClass<AirstrikeClass*> GgAirstrikeVector;
typedef DynamicVectorClass<AirstrikeClass*> GgAirstrikeDynamicVector;
GG_STATIC_ASSERT(sizeof(AirstrikeClass*) == 4);
GG_STATIC_ASSERT(sizeof(GgAirstrikeVector) == 0x10);
GG_STATIC_ASSERT(offsetof(GgAirstrikeVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgAirstrikeVector, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgAirstrikeVector, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgAirstrikeVector, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgAirstrikeVector, unknown_0E) == 0x0E);
GG_STATIC_ASSERT(sizeof(GgAirstrikeDynamicVector) == 0x18);
GG_STATIC_ASSERT(offsetof(GgAirstrikeDynamicVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgAirstrikeDynamicVector, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgAirstrikeDynamicVector, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgAirstrikeDynamicVector, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgAirstrikeDynamicVector, unknown_0E) == 0x0E);
GG_STATIC_ASSERT(offsetof(GgAirstrikeDynamicVector, ActiveCount) == 0x10);
GG_STATIC_ASSERT(offsetof(GgAirstrikeDynamicVector, CapacityIncrement) == 0x14);
