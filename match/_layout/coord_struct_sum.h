// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// CoordStruct::operator+ (component-wise sum), declared in coord_struct.h. Retail inlines it
// where two coordinates are added (AnimClass::vf_18 0x422BE0, BuildingClass 0x4500CB..0x4500E0);
// the by-value result is written in place. Include this after coord_struct.h in a TU that
// uses the operator.
#ifndef GG_MATCH_LAYOUT_COORD_STRUCT_SUM_H
#define GG_MATCH_LAYOUT_COORD_STRUCT_SUM_H
#include "coord_struct.h"

inline CoordStruct CoordStruct::operator+(const CoordStruct& b) const
{
    CoordStruct r;
    r.X = X + b.X;
    r.Y = Y + b.Y;
    r.Z = Z + b.Z;
    return r;
}

#endif  // GG_MATCH_LAYOUT_COORD_STRUCT_SUM_H
