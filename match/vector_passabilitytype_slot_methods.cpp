// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Retail RTTI type descriptors name VectorClass<PassabilityType> and
// DynamicVectorClass<PassabilityType>; each address below is the vtable slot body
// of that specialization (slot owner read from the retail vtables).
// Pointer/scalar/enum element: no element layout is claimed.
#include "vector_class_operations.h"

enum PassabilityType { PassabilityType_placeholder };

// TEMPLATE: GAMEMD 0x589EF0
// VectorClass<PassabilityType>::SetCapacity (slot 2)
// TEMPLATE: GAMEMD 0x58A030
// DynamicVectorClass<PassabilityType>::SetCapacity (slot 2)
template class VectorClass<PassabilityType>;
template class DynamicVectorClass<PassabilityType>;

GG_STATIC_ASSERT(sizeof(PassabilityType) == 4);
GG_STATIC_ASSERT(sizeof(VectorClass<PassabilityType >) == 0x10);
GG_STATIC_ASSERT(sizeof(DynamicVectorClass<PassabilityType >) == 0x18);
