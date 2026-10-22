// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe (Ghidra disasm). Member offsets and
//   globals reconfirmed numerically from the disasm at each method address;
//   field names cross-checked against YRpp MapClass.h / GScreenClass.h
//   (consult-only, no license).
//
//   Confirmed from disasm:
//     MapClass::Bitfield       @ 0x0c (int)   -- FUN_004F42D0 [ECX+0xc]
//     MapClass::MapRect.Width  @ 0xf4 (int)   -- CoordinatesLegal [ECX+0xf4]
//     MapClass::MapRect.Height @ 0xf8 (int)   -- CoordinatesLegal [ECX+0xf8]
//   MapClass derives GScreenClass (vptr@0,ScreenShakeX@4,ScreenShakeY@8,
//   Bitfield@0xc -> sizeof 0x10); MapRect lands at 0xEC, so Width@0xF4 /
//   Height@0xF8 (RectangleStruct = {X,Y,Width,Height}).
#ifndef GG_MATCH_MAP_MAP_CLASS_MORE_METHODS_H
#define GG_MATCH_MAP_MAP_CLASS_MORE_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// CellStruct — packed cell coordinate (two signed shorts). Self-guarded so
// other map TUs can reuse it.
#ifndef GG_MATCH_LAYOUT_CELLSTRUCT_DEFINED
#define GG_MATCH_LAYOUT_CELLSTRUCT_DEFINED
struct CellStruct
{
    short X;   // +0x00
    short Y;   // +0x02
};
GG_STATIC_ASSERT(sizeof(CellStruct) == 0x4);
#endif  // GG_MATCH_LAYOUT_CELLSTRUCT_DEFINED

// MapClass (partial) — only the members the two matched methods touch.
struct MapClass
{
    char pad_00[0x0C];
    int  Bitfield;                 // +0x0C  (default 2)
    char pad_10[0xF4 - 0x10];
    int  MapRectWidth;             // +0xF4  (MapRect.Width)
    int  MapRectHeight;            // +0xF8  (MapRect.Height)

    // 0x4F42D0 — unconditional `Bitfield = 2`, sibling of
    // GScreenClass::FlagToRedraw's conditional set. No name is attested for
    // it; kept as a placeholder.
    void FUN_004F42D0();
    // 0x568300
    bool CoordinatesLegal(const CellStruct& cell) const;
};

GG_STATIC_ASSERT(offsetof(MapClass, Bitfield)       == 0x0C);
GG_STATIC_ASSERT(offsetof(MapClass, MapRectWidth)   == 0xF4);
GG_STATIC_ASSERT(offsetof(MapClass, MapRectHeight)  == 0xF8);

#endif  // GG_MATCH_MAP_MAP_CLASS_MORE_METHODS_H
