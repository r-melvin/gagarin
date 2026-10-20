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
//   MapClass.h / CellClass.h (consult-only) and used as names only.
#ifndef GG_MATCH_MAP_MAP_CLASS_AREA_FREE_METHODS_H
#define GG_MATCH_MAP_MAP_CLASS_AREA_FREE_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct CellStruct_00586780
{
    short X;                  // +0x0000
    short Y;                  // +0x0002
};
GG_STATIC_ASSERT(sizeof(CellStruct_00586780) == 4);

struct Rect_00586780
{
    int X;                    // +0x0000
    int Y;                    // +0x0004
    int Width;                // +0x0008
    int Height;               // +0x000C
};
GG_STATIC_ASSERT(sizeof(Rect_00586780) == 0x10);

// CellClass — the members the sweep inspects.
struct Cell_00586780
{
    char          _pad000[0x24];          // +0x0000
    CellStruct_00586780 MapCoords;        // +0x0024
    char          _pad028[0x44 - 0x28];   // +0x0028
    int           OverlayTypeIndex;       // +0x0044
    char          _pad048[4];             // +0x0048
    void*         At_04C;                 // +0x004C
    char          _pad050[0xDC - 0x50];   // +0x0050
    unsigned int  At_0DC;                 // +0x00DC  bit set tested against 1 << bit
    char          _pad0E0[0x11C - 0xE0];  // +0x00E0
    unsigned char SlopeIndex;             // +0x011C

    // FUNCTION: GAMEMD 0x47C520 (decl; reloc) — CellClass::GetBuilding.
    void* GetBuilding();
    // FUNCTION: GAMEMD 0x47C550 (decl; reloc) — CellClass::GetTerrain(bool alt).
    void* GetTerrain(bool alt);
};
GG_STATIC_ASSERT(offsetof(Cell_00586780, MapCoords) == 0x24);
GG_STATIC_ASSERT(offsetof(Cell_00586780, OverlayTypeIndex) == 0x44);
GG_STATIC_ASSERT(offsetof(Cell_00586780, At_04C) == 0x4C);
GG_STATIC_ASSERT(offsetof(Cell_00586780, At_0DC) == 0xDC);
GG_STATIC_ASSERT(offsetof(Cell_00586780, SlopeIndex) == 0x11C);

// GLOBAL: GAMEMD 0x87F924 — MapClass::Cells items (flat CellClass* array).
extern Cell_00586780** Cells_00586780;
// GLOBAL: GAMEMD 0xABDC50 — MapClass::InvalidCell.
extern Cell_00586780 InvalidCell_00586780;

struct Map_00586780
{
    char opaque[4];

    // FUNCTION: GAMEMD 0x578390 (decl; reloc) — MapClass::InLocalRadar(RectangleStruct&, bool).
    bool InLocalRadar(Rect_00586780* rect, bool flag);

    // Inlined cell lookup (body in the .cpp ahead of its caller).
    Cell_00586780* GetCellAt(CellStruct_00586780 c);

    // FUNCTION: GAMEMD 0x586780 — MapClass::IsAreaFree.
    bool IsAreaFree(Rect_00586780* rect, int bit);
};

#endif  // GG_MATCH_MAP_MAP_CLASS_AREA_FREE_METHODS_H
