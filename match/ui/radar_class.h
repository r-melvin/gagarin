// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets derived from the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI (member-access disassembly at 0x653F50 / 0x654490),
//   cross-checked against YRpp RadarClass.h (consult-only; reconfirmed here).
//
// RadarClass — the in-game radar/minimap. RadarClass derives (deeply) from
// MapClass; the vtable sits at offset 0 and the few members the matched methods
// touch live in the MapClass region (0xF4..0x107) and the RadarClass-specific
// bounding-rectangle region (0x1490..0x14AB). The full layout is P2.
#ifndef GG_MATCH_UI_RADAR_CLASS_H
#define GG_MATCH_UI_RADAR_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// RectangleStruct — { int X, Y, Width, Height }. YRpp BasicStructures.h.
#include "../_layout/geometry2d.h"

// CellStruct — 2D short cell coordinate (sizeof == 4). The empty user-declared
// constructor is load-bearing: it makes the by-value GetCell() temporary use the
// hidden-pointer convention, which is what schedules the `MOV [ESP+0x2C],EAX`
// store of the visibility-test argument after the pushes (retail's shape).
// operator+ is the inlined Vector2D<short> sum: each half is loaded as a dword
// from the two stack slots and added in 32-bit before the MOVSX.
struct CellStruct
{
    short X;  // +0x00
    short Y;  // +0x02

    CellStruct() {}

    CellStruct operator+(CellStruct const& a) const
    {
        CellStruct r;
        r.X = X + a.X;
        r.Y = Y + a.Y;
        return r;
    }
};
GG_STATIC_ASSERT(sizeof(CellStruct) == 4);

// RadarTrackNode — one entry in the radar tracking list returned by the
// iterator at 0x578290. Only its cell coordinate at +0x24 is touched
// (`MOV EAX,[EDI+0x24]`, `MOVSX EDX,[EDI+0x26]`, `MOVSX EAX,[EDI+0x24]`).
// GetCell() returns it by value through a named local: that is the spelling
// that reproduces the two dword copies into the reused parameter slot.
struct RadarTrackNode
{
    char       _pad[0x24];
    CellStruct Cell;   // +0x24  (X at +0x24, Y at +0x26)

    CellStruct GetCell() const
    {
        CellStruct r = Cell;
        return r;
    }
};
#if GG_TARGET_ABI_32
GG_STATIC_ASSERT(offsetof(RadarTrackNode, Cell) == 0x24);
#endif

// RadarClass — modelled as a flat byte image (no C++ vtable of our own: the
// retail vtable already lives at offset 0 and is covered by the leading pad).
struct RadarClass
{
    // ---- matched methods (ascending by retail address) ----
    void CreateEmptyMap(const RectangleStruct& mapRect, bool reuse,
                        char nLevel, bool bUnk2);          // GAMEMD 0x653F50 __thiscall
    void SetVisibleRect(const RectangleStruct& mapRect);   // GAMEMD 0x654490 __thiscall

    // ---- referenced retail callees (declared, body lives elsewhere) ----
    void            Map_CreateEmptyMap(const RectangleStruct& mapRect, bool reuse,
                                       char nLevel, bool bUnk2);   // GAMEMD 0x565C10
    void            Base_SetVisibleRect(const RectangleStruct& mapRect); // GAMEMD 0x567230
    void            Func_578350();                                 // GAMEMD 0x578350
    RadarTrackNode* Iterate_578290();                              // GAMEMD 0x578290
    bool            Func_578460(CellStruct const& cell, bool flag); // GAMEMD 0x578460

    // ---- members touched by the matched methods ----
    char _base[0xF4];        // 0x000  vtable + base (MapClass/DisplayClass) — P2
    int  MapSizeX;           // 0x0F4
    char _gap_F8[0x4];       // 0x0F8
    int  MapCellLeft;        // 0x0FC
    int  MapCellTop;         // 0x100
    int  MapCellWidth;       // 0x104
    char _gap_108[0x1490 - 0x108];  // 0x108
    int  unknown_1490;       // 0x1490
    int  unknown_1494;       // 0x1494
    int  unknown_1498;       // 0x1498
    RectangleStruct RadarBounds;    // 0x149C (X,Y,Width,Height = 0x149C..0x14A8)
};

#if GG_TARGET_ABI_32
GG_STATIC_ASSERT(offsetof(RadarClass, MapSizeX)     == 0x0F4);
GG_STATIC_ASSERT(offsetof(RadarClass, MapCellLeft)  == 0x0FC);
GG_STATIC_ASSERT(offsetof(RadarClass, MapCellTop)   == 0x100);
GG_STATIC_ASSERT(offsetof(RadarClass, MapCellWidth) == 0x104);
GG_STATIC_ASSERT(offsetof(RadarClass, unknown_1490) == 0x1490);
GG_STATIC_ASSERT(offsetof(RadarClass, unknown_1494) == 0x1494);
GG_STATIC_ASSERT(offsetof(RadarClass, unknown_1498) == 0x1498);
GG_STATIC_ASSERT(offsetof(RadarClass, RadarBounds)  == 0x149C);
#endif

// GLOBAL: GAMEMD 0x87F7E8  RadarClass::Instance (the radar singleton).
extern RadarClass Instance;

#endif  // GG_MATCH_UI_RADAR_CLASS_H
