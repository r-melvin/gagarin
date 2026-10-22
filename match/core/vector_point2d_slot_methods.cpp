// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Retail RTTI type descriptors name VectorClass<Point2D> and
// DynamicVectorClass<Point2D>; each address below is the vtable slot body
// of that specialization (slot owner read from the retail vtables). The
// element compare in operator== and FindItemIndex is Point2D's member-wise
// equality from geometry2d.h.
#include "vector_class_operations.h"
#include "../_layout/geometry2d.h"

// TEMPLATE: GAMEMD 0x5D05D0
// DynamicVectorClass<Point2D>::Slot5 (slot 5)
// TEMPLATE: GAMEMD 0x5D05F0
// VectorClass<Point2D>::Slot6 (slot 6)
// TEMPLATE: GAMEMD 0x5D07F0
// VectorClass<Point2D>::operator== (slot 1)
// TEMPLATE: GAMEMD 0x5D0950
// VectorClass<Point2D>::FindItemIndex (slot 4)
// TEMPLATE: GAMEMD 0x5D09A0
// VectorClass<Point2D>::Slot5 (slot 5)
template class VectorClass<Point2D>;
template class DynamicVectorClass<Point2D>;

GG_STATIC_ASSERT(sizeof(VectorClass<Point2D>) == 0x10);
GG_STATIC_ASSERT(sizeof(DynamicVectorClass<Point2D>) == 0x18);
