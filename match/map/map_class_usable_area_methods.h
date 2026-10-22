// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x578540: on the cell `MOVSX EDX,[EAX+0x26]` /
//   `MOVSX EDI,[EAX+0x24]` (MapCoords.Y / .X), `MOV BL,[EAX+0x11C]`
//   (SlopeIndex byte) and `MOVSX ESI,[EAX+0x11B]` (Level, signed char); on
//   the map `[ECX+0xF4]` (MapRect.Width), `[ECX+0xFC]` / `[ECX+0x100]` /
//   `[ECX+0x104]` / `[ECX+0x108]` (VisibleRect X / Y / Width / Height).
//   Names cross-checked against YRpp;
//   MapRect @0xEC / VisibleRect @0xFC agree with
//   match/map/map_class_more_methods.h (Width @0xF4, Height @0xF8) and
//   match/map/map_class_sublocation_methods.h (Level @0x11B).
#ifndef GG_MATCH_MAP_MAP_CLASS_USABLE_AREA_METHODS_H
#define GG_MATCH_MAP_MAP_CLASS_USABLE_AREA_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// CellClass — only the map coordinate and the two level bytes are read.
struct Cell_00578540
{
    char          _pad000[0x24];         // +0x0000
    short         X;                     // +0x0024 MapCoords.X
    short         Y;                     // +0x0026 MapCoords.Y
    char          _pad028[0x11B - 0x28]; // +0x0028
    signed char   Level;                 // +0x011B
    unsigned char SlopeIndex;            // +0x011C
};
GG_STATIC_ASSERT(offsetof(Cell_00578540, X)          == 0x24);
GG_STATIC_ASSERT(offsetof(Cell_00578540, Y)          == 0x26);
GG_STATIC_ASSERT(offsetof(Cell_00578540, Level)      == 0x11B);
GG_STATIC_ASSERT(offsetof(Cell_00578540, SlopeIndex) == 0x11C);

// MapClass — MapRect {X,Y,Width,Height} @0xEC and VisibleRect @0xFC.
class MapClass
{
public:
    char _pad000[0xEC];      // +0x0000
    int  MapRectX;           // +0x00EC
    int  MapRectY;           // +0x00F0
    int  MapRectWidth;       // +0x00F4
    int  MapRectHeight;      // +0x00F8
    int  VisibleRectX;       // +0x00FC
    int  VisibleRectY;       // +0x0100
    int  VisibleRectWidth;   // +0x0104
    int  VisibleRectHeight;  // +0x0108

    // FUNCTION: GAMEMD 0x578540
    bool IsWithinUsableArea(Cell_00578540* pCell, bool checkLevel) const;
};
GG_STATIC_ASSERT(offsetof(MapClass, MapRectWidth)      == 0xF4);
GG_STATIC_ASSERT(offsetof(MapClass, VisibleRectX)      == 0xFC);
GG_STATIC_ASSERT(offsetof(MapClass, VisibleRectY)      == 0x100);
GG_STATIC_ASSERT(offsetof(MapClass, VisibleRectWidth)  == 0x104);
GG_STATIC_ASSERT(offsetof(MapClass, VisibleRectHeight) == 0x108);

#endif  // GG_MATCH_MAP_MAP_CLASS_USABLE_AREA_METHODS_H
