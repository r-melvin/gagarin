// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Retail RTTI names VectorClass<TPoint3D<int>> (vtable 0x7E4638). The element is three ints; the compare
//   shapes are read from the FindItemIndex and Slot5 bodies of that vector.
#ifndef GG_MATCH_LAYOUT_TPOINT3D_H
#define GG_MATCH_LAYOUT_TPOINT3D_H

template<class T> class TPoint3D { public: T X; T Y; T Z; TPoint3D() {} bool operator==(const TPoint3D<T>& o) const { return X==o.X && Y==o.Y && Z==o.Z; } bool operator!=(const TPoint3D<T>& o) const { return !(*this==o); } };

#endif  // GG_MATCH_LAYOUT_TPOINT3D_H
