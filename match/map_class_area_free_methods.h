// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x586780: the rectangle is read as `[EBX]`, `[EBX+4]`,
//   `[EBX+8]`, `[EBX+0xC]` (X, Y, Width, Height); the cell index is
//   `(short)Y << 9 + (short)X` bounded by 0x40000 into the array at
//   `[0x87F924]` with the fallback cell 0xABDC50 whose MapCoords (+0x24 =
//   0xABDC74) receive the requested coordinate; on the cell `[ESI+0xDC]`
//   (masked by 1 << bit), `[ESI+0x44]` (OverlayTypeIndex, -1 = none),
//   `[ESI+0x4C]` and the byte `[ESI+0x11C]` (SlopeIndex). Calls: 0x47C550 with
//   one pushed 0 and 0x47C520 with none (both __thiscall on the cell), and
//   0x578390 on the map with (rect, 1). Names cross-checked against YRpp
//   and used as names only.
#ifndef GG_MATCH_MAP_MAP_CLASS_AREA_FREE_METHODS_H
#define GG_MATCH_MAP_MAP_CLASS_AREA_FREE_METHODS_H

#include <stddef.h>
#include "_rt/gg_static_assert.h"

struct Rect_00586780
{
    int X;                    // +0x0000
    int Y;                    // +0x0004
    int Width;                // +0x0008
    int Height;               // +0x000C
};
GG_STATIC_ASSERT(sizeof(Rect_00586780) == 0x10);

#include "_layout/cell_class.h"
#include "cell_flag_search_shared.h"
#include "ui_display_chain.h"

struct Map_00586780
{
    char opaque[4];

    // FUNCTION: GAMEMD 0x578390 (decl; reloc) — MapClass::InLocalRadar(RectangleStruct&, bool).
    bool InLocalRadar(Rect_00586780* rect, bool flag);

    // Inlined cell lookup (body in the .cpp ahead of its caller).
    CellClass* GetCellAt(CellStruct c);

    // FUNCTION: GAMEMD 0x586780 — MapClass::IsAreaFree.
    bool IsAreaFree(Rect_00586780* rect, int bit);
};

#endif  // GG_MATCH_MAP_MAP_CLASS_AREA_FREE_METHODS_H
