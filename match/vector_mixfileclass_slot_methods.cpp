// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | own-binary-via-REA
// Retail RTTI type descriptors name VectorClass<MixFileClass*> and
// DynamicVectorClass<MixFileClass*>; each address below is the vtable slot body
// of that specialization (slot owner read from the retail vtables).
// Pointer/scalar/enum element: no element layout is claimed.
#include "vector_class_operations.h"

class MixFileClass;

// TEMPLATE: GAMEMD 0x40D540
// DynamicVectorClass<MixFileClass*>::Clear (slot 3)
// TEMPLATE: GAMEMD 0x40D570
// DynamicVectorClass<MixFileClass*>::Slot5 (slot 5)
// TEMPLATE: GAMEMD 0x40D590
// VectorClass<MixFileClass*>::Slot6 (slot 6)
// TEMPLATE: GAMEMD 0x40D5A0
// VectorClass<MixFileClass*>::operator== (slot 1)
// TEMPLATE: GAMEMD 0x40D5E0
// VectorClass<MixFileClass*>::SetCapacity (slot 2)
// TEMPLATE: GAMEMD 0x40D690
// VectorClass<MixFileClass*>::Clear (slot 3)
// TEMPLATE: GAMEMD 0x40D6C0
// VectorClass<MixFileClass*>::FindItemIndex (slot 4)
// TEMPLATE: GAMEMD 0x40D700
// VectorClass<MixFileClass*>::Slot5 (slot 5)
// TEMPLATE: GAMEMD 0x40D720
// DynamicVectorClass<MixFileClass*>::SetCapacity (slot 2)
// TEMPLATE: GAMEMD 0x40D7D0
// DynamicVectorClass<MixFileClass*>::FindItemIndex (slot 4)
// SYNTHETIC: GAMEMD 0x40D800
// VectorClass<MixFileClass*>::scalar deleting destructor (slot 0)
// SYNTHETIC: GAMEMD 0x40D850
// DynamicVectorClass<MixFileClass*>::scalar deleting destructor (slot 0)
// VTABLE: GAMEMD 0x7E1A64 -- VectorClass<MixFileClass*>.
template class VectorClass<MixFileClass*>;
// VTABLE: GAMEMD 0x7E1A44 -- DynamicVectorClass<MixFileClass*>.
template class DynamicVectorClass<MixFileClass*>;

GG_STATIC_ASSERT(sizeof(MixFileClass*) == 4);
GG_STATIC_ASSERT(sizeof(VectorClass<MixFileClass* >) == 0x10);
GG_STATIC_ASSERT(sizeof(DynamicVectorClass<MixFileClass* >) == 0x18);

GG_STATIC_ASSERT(offsetof(VectorClass<MixFileClass*>, Items) == 0x4);
GG_STATIC_ASSERT(sizeof(((VectorClass<MixFileClass*>*)0)->Items) == 4);

GG_STATIC_ASSERT(offsetof(VectorClass<MixFileClass*>, Capacity) == 0x8);
GG_STATIC_ASSERT(sizeof(((VectorClass<MixFileClass*>*)0)->Capacity) == 4);

GG_STATIC_ASSERT(offsetof(VectorClass<MixFileClass*>, IsInitialized) == 0xC);
GG_STATIC_ASSERT(sizeof(((VectorClass<MixFileClass*>*)0)->IsInitialized) == 1);

GG_STATIC_ASSERT(offsetof(VectorClass<MixFileClass*>, IsAllocated) == 0xD);
GG_STATIC_ASSERT(sizeof(((VectorClass<MixFileClass*>*)0)->IsAllocated) == 1);

GG_STATIC_ASSERT(offsetof(DynamicVectorClass<MixFileClass*>, Items) == 0x4);
GG_STATIC_ASSERT(sizeof(((DynamicVectorClass<MixFileClass*>*)0)->Items) == 4);

GG_STATIC_ASSERT(offsetof(DynamicVectorClass<MixFileClass*>, Capacity) == 0x8);
GG_STATIC_ASSERT(sizeof(((DynamicVectorClass<MixFileClass*>*)0)->Capacity) == 4);

GG_STATIC_ASSERT(offsetof(DynamicVectorClass<MixFileClass*>, IsInitialized) == 0xC);
GG_STATIC_ASSERT(sizeof(((DynamicVectorClass<MixFileClass*>*)0)->IsInitialized) == 1);

GG_STATIC_ASSERT(offsetof(DynamicVectorClass<MixFileClass*>, IsAllocated) == 0xD);
GG_STATIC_ASSERT(sizeof(((DynamicVectorClass<MixFileClass*>*)0)->IsAllocated) == 1);

GG_STATIC_ASSERT(offsetof(DynamicVectorClass<MixFileClass*>, Count) == 0x10);
GG_STATIC_ASSERT(sizeof(((DynamicVectorClass<MixFileClass*>*)0)->Count) == 4);

GG_STATIC_ASSERT(offsetof(DynamicVectorClass<MixFileClass*>, CapacityIncrement) == 0x14);
GG_STATIC_ASSERT(sizeof(((DynamicVectorClass<MixFileClass*>*)0)->CapacityIncrement) == 4);
