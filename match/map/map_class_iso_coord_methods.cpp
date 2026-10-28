// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: retail gamemd.exe v1.001 disassembly at 0x565470-0x565668 (0x565580, 0x5655C0 and 0x565660 are unmatched). MapClass keeps an
//   isometric projection origin at +0xF4 and two offsets at +0xFC/+0x100; these helpers
//   convert between two 2D coordinate systems with them, on Point2D and on CellStruct.
//
// Address index: 0x565470 0x5654A0 0x5654E0 0x565520 0x565610

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/geometry2d.h"
#include "../_layout/cell.h"

// Minimal MapClass view: only the projection members these helpers read.
class MapClass
{
public:
    char unknown_000[0xF4];
    int  unknown_F4;      // +0xF4  projection origin
    int  unknown_F8;      // +0xF8
    int  unknown_FC;      // +0xFC  X offset
    int  unknown_100;     // +0x100 Y offset

    Point2D FUN_00565470(const Point2D& in) const;
    Point2D FUN_005654A0(const Point2D& in) const;
    Point2D FUN_005654E0(const Point2D& in) const;
    Point2D FUN_00565520(const Point2D& in) const;
    CellStruct* FUN_00565610(CellStruct* out, const CellStruct* in) const;
};
GG_STATIC_ASSERT(offsetof(MapClass, unknown_F4) == 0xF4);
GG_STATIC_ASSERT(offsetof(MapClass, unknown_FC) == 0xFC);
GG_STATIC_ASSERT(offsetof(MapClass, unknown_100) == 0x100);

// FUNCTION: GAMEMD 0x565470
// Projects a point: X + half of Y rounded up, origin + half of Y - X.
Point2D MapClass::FUN_00565470(const Point2D& in) const
{
    Point2D out;
    out.X = in.X + ((in.Y + 1) >> 1);
    out.Y = unknown_F4 + (in.Y >> 1) - in.X;
    return out;
}

// FUNCTION: GAMEMD 0x5654A0
// Same projection after adding the +0xFC/+0x100 offsets to the point.
Point2D MapClass::FUN_005654A0(const Point2D& in) const
{
    Point2D p(unknown_FC, unknown_100);
    int x = in.X + p.X;
    int y = in.Y + p.Y;
    return Point2D(x + ((y + 1) >> 1), unknown_F4 + (y >> 1) - x);
}

// FUNCTION: GAMEMD 0x5654E0
// Inverse projection of the point.
Point2D MapClass::FUN_005654E0(const Point2D& in) const
{
    int f = unknown_F4;
    int x = in.X;
    int y = in.Y;
    int d = (f & 1) ? x - y + 1 : x - y;
    return Point2D((d >> 1) + f / 2, x + y - f);
}

// FUNCTION: GAMEMD 0x565520
// Inverse projection, then the +0xFC/+0x100 offsets taken off the result.
Point2D MapClass::FUN_00565520(const Point2D& in) const
{
    Point2D p(unknown_FC, unknown_100);
    int f = unknown_F4;
    int x = in.X;
    int y = in.Y;
    int d = (f & 1) ? x - y + 1 : x - y;
    Point2D q((d >> 1) + f / 2, x + y - f);
    return Point2D(q.X - p.X, q.Y - p.Y);
}

// FUNCTION: GAMEMD 0x565610
// The inverse projection of FUN_005654E0 on a cell coordinate.
CellStruct* MapClass::FUN_00565610(CellStruct* out, const CellStruct* in) const
{
    int f = unknown_F4;
    int x = in->X;
    int y = in->Y;
    int d = (f & 1) ? x - y + 1 : x - y;
    CellStruct r;
    r.X = (short)((d >> 1) + f / 2);
    r.Y = (short)(x + y - f);
    *out = r;
    return out;
}
