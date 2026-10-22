// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Retail RTTI type descriptors name VectorClass<DiskID> and
// DynamicVectorClass<DiskID>; each address below is the vtable slot body
// of that specialization (slot owner read from the retail vtables).
// Pointer/scalar/enum element: no element layout is claimed.
#include "vector_class_operations.h"

enum DiskID { DiskID_placeholder };

// TEMPLATE: GAMEMD 0x69C4F0
// VectorClass<DiskID>::Slot6 (slot 6)
// TEMPLATE: GAMEMD 0x69C710
// VectorClass<DiskID>::operator== (slot 1)
// TEMPLATE: GAMEMD 0x69C750
// VectorClass<DiskID>::SetCapacity (slot 2)
// TEMPLATE: GAMEMD 0x69C830
// VectorClass<DiskID>::FindItemIndex (slot 4)
// TEMPLATE: GAMEMD 0x69C870
// VectorClass<DiskID>::Slot5 (slot 5)
template class VectorClass<DiskID>;
template class DynamicVectorClass<DiskID>;

GG_STATIC_ASSERT(sizeof(DiskID) == 4);
GG_STATIC_ASSERT(sizeof(VectorClass<DiskID >) == 0x10);
GG_STATIC_ASSERT(sizeof(DynamicVectorClass<DiskID >) == 0x18);
