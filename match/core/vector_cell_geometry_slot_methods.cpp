// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT
// Retail RTTI names VectorClass/DynamicVectorClass over Cell, BaseNodeClass, TPoint3D<int>, Point2D,
// TRect<int> and DirtyAreaStruct. Element layouts and compare shapes are read from the FindItemIndex,
// Slot5, Slot6 and SetCapacity bodies; field names are placeholders.
#include "vector_class_operations.h"

// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.

struct Cell { short X; short Y; Cell() {} bool operator==(const Cell& o) const { return X==o.X && Y==o.Y; } bool operator!=(const Cell& o) const { return !(*this==o); } };
// FUNCTION: GAMEMD 0x0042F620
// VectorClass<Cell>::operator==
// FUNCTION: GAMEMD 0x0042F6F0
// VectorClass<Cell>::SetCapacity
// FUNCTION: GAMEMD 0x0042F7F0
// VectorClass<Cell>::FindItemIndex
// FUNCTION: GAMEMD 0x0042F840
// VectorClass<Cell>::Slot5
// FUNCTION: GAMEMD 0x0042F470
// VectorClass<Cell>::Slot6
// FUNCTION: GAMEMD 0x0042F860
// DynamicVectorClass<Cell>::SetCapacity
// FUNCTION: GAMEMD 0x0042F930
// DynamicVectorClass<Cell>::FindItemIndex
// FUNCTION: GAMEMD 0x0042F450
// DynamicVectorClass<Cell>::Slot5
// VTABLE: GAMEMD 0x007E38D0 -- VectorClass<Cell>.
// VTABLE: GAMEMD 0x007E3890 -- DynamicVectorClass<Cell>.
template class VectorClass<Cell>;
template class DynamicVectorClass<Cell>;

 struct BaseNodeClass { int unknown_00; Cell unknown_04; unsigned char unknown_08; int unknown_0C; BaseNodeClass() {} BaseNodeClass(const BaseNodeClass& o) : unknown_00(o.unknown_00), unknown_04(o.unknown_04), unknown_08(o.unknown_08), unknown_0C(o.unknown_0C) {} bool operator==(const BaseNodeClass& o) const { return unknown_00==o.unknown_00 && unknown_04==o.unknown_04; } bool operator!=(const BaseNodeClass& o) const { return !(*this==o); } };
// FUNCTION: GAMEMD 0x0042F490
// VectorClass<BaseNodeClass>::operator==
// FUNCTION: GAMEMD 0x0042F9C0
// VectorClass<BaseNodeClass>::SetCapacity
// FUNCTION: GAMEMD 0x0042FAE0
// VectorClass<BaseNodeClass>::FindItemIndex
// FUNCTION: GAMEMD 0x0042FB30
// VectorClass<BaseNodeClass>::Slot5
// FUNCTION: GAMEMD 0x0042F3F0
// VectorClass<BaseNodeClass>::Slot6
// FUNCTION: GAMEMD 0x0042F4F0
// DynamicVectorClass<BaseNodeClass>::SetCapacity
// FUNCTION: GAMEMD 0x0042F5E0
// DynamicVectorClass<BaseNodeClass>::FindItemIndex
// FUNCTION: GAMEMD 0x0042F3D0
// DynamicVectorClass<BaseNodeClass>::Slot5
// VTABLE: GAMEMD 0x007E38F0 -- VectorClass<BaseNodeClass>.
// VTABLE: GAMEMD 0x007E38B0 -- DynamicVectorClass<BaseNodeClass>.
template class VectorClass<BaseNodeClass>;
template class DynamicVectorClass<BaseNodeClass>;

template<class T> struct TPoint3D { T X; T Y; T Z; TPoint3D() {} bool operator==(const TPoint3D<T>& o) const { return X==o.X && Y==o.Y && Z==o.Z; } bool operator!=(const TPoint3D<T>& o) const { return !(*this==o); } };
// FUNCTION: GAMEMD 0x00465E10
// VectorClass<TPoint3D<int>>::operator==
// FUNCTION: GAMEMD 0x00465E70
// VectorClass<TPoint3D<int>>::SetCapacity
// FUNCTION: GAMEMD 0x00465F80
// VectorClass<TPoint3D<int>>::FindItemIndex
// FUNCTION: GAMEMD 0x00465FD0
// VectorClass<TPoint3D<int>>::Slot5
// FUNCTION: GAMEMD 0x00465DE0
// VectorClass<TPoint3D<int>>::Slot6
// VTABLE: GAMEMD 0x007E4638 -- VectorClass<TPoint3D<int>>.
template class VectorClass<TPoint3D<int> >;

#include "../_layout/geometry2d.h"
template class DynamicVectorClass<Point2D>;

template class DynamicVectorClass<TRect<int> >;

#include "../_layout/dirty_area.h"
template class DynamicVectorClass<DirtyAreaStruct>;

