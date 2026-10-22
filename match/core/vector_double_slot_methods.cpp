// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Retail RTTI type descriptors name VectorClass<double> and
// DynamicVectorClass<double>; each address below is the vtable slot body
// of that specialization (slot owner read from the retail vtables).
// Pointer/scalar/enum element: no element layout is claimed.
#include "vector_class_operations.h"

// TEMPLATE: GAMEMD 0x5AC620
// DynamicVectorClass<double>::Slot5 (slot 5)
// TEMPLATE: GAMEMD 0x5AD270
// VectorClass<double>::Slot5 (slot 5)
template class VectorClass<double>;
template class DynamicVectorClass<double>;

GG_STATIC_ASSERT(sizeof(double) == 8);
GG_STATIC_ASSERT(sizeof(VectorClass<double >) == 0x10);
GG_STATIC_ASSERT(sizeof(DynamicVectorClass<double >) == 0x18);
