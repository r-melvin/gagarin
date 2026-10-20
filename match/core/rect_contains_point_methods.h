// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Layout read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x63DB20: `this` is a four-int rectangle (X at +0x0,
//   Y at +0x4, Width at +0x8, Height at +0xC, all confirmed by the four
//   `CMP`/`ADD` pairs); the stack argument is a two-int point (X at +0x0,
//   Y at +0x4). `__thiscall`, one stack argument, `RET 0x4`, returns 1/0 in
//   EAX.
#ifndef GG_MATCH_CORE_RECT_CONTAINS_POINT_METHODS_H
#define GG_MATCH_CORE_RECT_CONTAINS_POINT_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Point_0063DB20
{
    int X;   // +0x00
    int Y;   // +0x04
};
GG_STATIC_ASSERT(offsetof(Point_0063DB20, Y) == 0x04);

struct Rect_0063DB20
{
    int X;        // +0x00
    int Y;        // +0x04
    int Width;    // +0x08
    int Height;   // +0x0C

    // FUNCTION: GAMEMD 0x63DB20
    int Contains(const Point_0063DB20* pt) const;
};
GG_STATIC_ASSERT(offsetof(Rect_0063DB20, Y)      == 0x04);
GG_STATIC_ASSERT(offsetof(Rect_0063DB20, Width)  == 0x08);
GG_STATIC_ASSERT(offsetof(Rect_0063DB20, Height) == 0x0C);

#endif  // GG_MATCH_CORE_RECT_CONTAINS_POINT_METHODS_H
