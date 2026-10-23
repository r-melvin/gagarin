// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
#ifndef GG_MATCH_LAYOUT_DIRTY_AREA_H
#define GG_MATCH_LAYOUT_DIRTY_AREA_H
#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "geometry2d.h"

// DirtyAreaStruct (RTTI `.?AU`, stride 0x14): a TRect<int> followed by a
// flag byte. Retail VectorClass<DirtyAreaStruct> element copy 0x6DC540 moves
// the first 16 bytes as one block (four dwords through EDX/ESI) and then the
// byte at +0x10, the implicit copy of a nested rectangle member.
struct DirtyAreaStruct
{
    TRect<int>    Rect;         // +0x00
    unsigned char unknown_10;   // +0x10

    DirtyAreaStruct()
    {
        Rect.X = 0;
        Rect.Y = 0;
        Rect.Width = 0;
        Rect.Height = 0;
        unknown_10 = 0;
    }
    DirtyAreaStruct(const DirtyAreaStruct& o) : Rect(o.Rect), unknown_10(o.unknown_10) {}
    bool operator==(const DirtyAreaStruct& o) const
    {
        return unknown_10 == o.unknown_10 && Rect == o.Rect;
    }
    bool operator!=(const DirtyAreaStruct& o) const { return !(*this == o); }
};
GG_STATIC_ASSERT(offsetof(DirtyAreaStruct, Rect) == 0x00);
GG_STATIC_ASSERT(offsetof(DirtyAreaStruct, unknown_10) == 0x10);
GG_STATIC_ASSERT(sizeof(DirtyAreaStruct) == 0x14);

#endif  // GG_MATCH_LAYOUT_DIRTY_AREA_H
