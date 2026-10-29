// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Retail RTTI names VectorClass/DynamicVectorClass over Cell, BaseNodeClass, TPoint3D<int>, Point2D,
// TRect<int> and DirtyAreaStruct. Element layouts and compare shapes are read from the FindItemIndex,
// Slot5, Slot6 and SetCapacity bodies; field names are placeholders.
#include "vector_class_operations.h"

// CALLEE: GAMEMD 0x007C8E17 -- operator new(size_t), ??2@YAPAXI@Z.

#include "../_layout/cell.h"

// FUNCTION: GAMEMD 0x0042F3A0
// DynamicVectorClass<BaseNodeClass>::Clear

// FUNCTION: GAMEMD 0x0042F3D0
// DynamicVectorClass<BaseNodeClass>::Slot5

// FUNCTION: GAMEMD 0x0042F3F0
// VectorClass<BaseNodeClass>::Slot6

// FUNCTION: GAMEMD 0x0042F420
// DynamicVectorClass<Cell>::Clear

// FUNCTION: GAMEMD 0x0042F450
// DynamicVectorClass<Cell>::Slot5

// FUNCTION: GAMEMD 0x0042F470
// VectorClass<Cell>::Slot6

// FUNCTION: GAMEMD 0x0042F490
// VectorClass<BaseNodeClass>::operator==

// FUNCTION: GAMEMD 0x0042F4F0
// DynamicVectorClass<BaseNodeClass>::SetCapacity

// FUNCTION: GAMEMD 0x0042F5E0
// DynamicVectorClass<BaseNodeClass>::FindItemIndex

// FUNCTION: GAMEMD 0x0042F620
// VectorClass<Cell>::operator==

// FUNCTION: GAMEMD 0x0042F6F0
// VectorClass<Cell>::SetCapacity

// FUNCTION: GAMEMD 0x0042F7C0
// VectorClass<Cell>::Clear

// FUNCTION: GAMEMD 0x0042F7F0
// VectorClass<Cell>::FindItemIndex

// FUNCTION: GAMEMD 0x0042F840
// VectorClass<Cell>::Slot5

// FUNCTION: GAMEMD 0x0042F860
// DynamicVectorClass<Cell>::SetCapacity

// FUNCTION: GAMEMD 0x0042F930
// DynamicVectorClass<Cell>::FindItemIndex

// SYNTHETIC: GAMEMD 0x0042F970
// DynamicVectorClass<BaseNodeClass>::scalar deleting destructor

// FUNCTION: GAMEMD 0x0042F9C0
// VectorClass<BaseNodeClass>::SetCapacity

// FUNCTION: GAMEMD 0x0042FAB0
// VectorClass<BaseNodeClass>::Clear

// FUNCTION: GAMEMD 0x0042FAE0
// VectorClass<BaseNodeClass>::FindItemIndex

// FUNCTION: GAMEMD 0x0042FB30
// VectorClass<BaseNodeClass>::Slot5

// SYNTHETIC: GAMEMD 0x0042FB50
// VectorClass<BaseNodeClass>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x0042FBA0
// VectorClass<Cell>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x0042FBF0
// DynamicVectorClass<Cell>::scalar deleting destructor

// FUNCTION: GAMEMD 0x0068C2B0
// VectorClass<Cell>::operator=























// VTABLE: GAMEMD 0x007E38D0 -- VectorClass<Cell>.
// VTABLE: GAMEMD 0x007E3890 -- DynamicVectorClass<Cell>.
template class VectorClass<Cell>;
template class DynamicVectorClass<Cell>;

#include "../_layout/base_node_class.h"
// VTABLE: GAMEMD 0x007E38F0 -- VectorClass<BaseNodeClass>.
// VTABLE: GAMEMD 0x007E38B0 -- DynamicVectorClass<BaseNodeClass>.
template class VectorClass<BaseNodeClass>;
template class DynamicVectorClass<BaseNodeClass>;

template<class T> struct TPoint3D { T X; T Y; T Z; TPoint3D() {} bool operator==(const TPoint3D<T>& o) const { return X==o.X && Y==o.Y && Z==o.Z; } bool operator!=(const TPoint3D<T>& o) const { return !(*this==o); } };
// VTABLE: GAMEMD 0x007E4638 -- VectorClass<TPoint3D<int>>.
template class VectorClass<TPoint3D<int> >;

#include "../_layout/geometry2d.h"
template class DynamicVectorClass<Point2D>;

template class DynamicVectorClass<TRect<int> >;

#include "../_layout/dirty_area.h"
template class DynamicVectorClass<DirtyAreaStruct>;







