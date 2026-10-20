// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes read off the user's retail gamemd.exe v1.001 via the local Ghidra
//   CLI at 0x578390: the rectangle's X/Y/Width/Height at +0/+4/+8/+0xC, four
//   corner CellStructs handed to 0x578460 with the bool forwarded, the first
//   two built in the dead parameter slots and the last two in the 8-byte
//   frame. YRpp (consult-only, no LICENSE) names InLocalRadar and the callee
//   IsWithinUsableArea(CellStruct*, bool); the retail return is a full-width
//   int (MOV EAX,1 / XOR EAX,EAX), not YRpp's bool. IsWithinUsableArea itself
//   (0x578460) reads the map rectangle at [ECX+0xF4] and the visible
//   rectangle at [ECX+0xFC..+0x108], resolves the cell through the global
//   cell array at 0x87F924 with the 0x40000 bound (fallback 0xABDC50, coords
//   at 0xABDC74) and reads the cell's Level (+0x11B, signed) and SlopeIndex
//   (+0x11C); member names follow the sibling match/map/
//   map_class_usable_area_methods.h for the CellClass* overload at 0x578540.
#ifndef GG_MATCH_MAP_MAP_CLASS_LOCAL_RADAR_METHODS_H
#define GG_MATCH_MAP_MAP_CLASS_LOCAL_RADAR_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Cell_00578390 { short X; short Y; };
GG_STATIC_ASSERT(sizeof(Cell_00578390) == 0x4);

struct Rect_00578390
{
    int X;        // +0x00
    int Y;        // +0x04
    int Width;    // +0x08
    int Height;   // +0x0C
};
GG_STATIC_ASSERT(sizeof(Rect_00578390) == 0x10);

struct CellClass_00578390
{
    char _pad0000[0x24];              // +0x0000
    Cell_00578390 MapCoords;          // +0x0024
    char _pad0028[0x11B - 0x28];      // +0x0028
    signed char Level;                // +0x011B
    char SlopeIndex;                  // +0x011C
};
GG_STATIC_ASSERT(offsetof(CellClass_00578390, MapCoords) == 0x24);
GG_STATIC_ASSERT(offsetof(CellClass_00578390, Level) == 0x11B);
GG_STATIC_ASSERT(offsetof(CellClass_00578390, SlopeIndex) == 0x11C);

// GLOBAL: GAMEMD 0xABDC50 — MapClass::InvalidCell (its MapCoords is 0xABDC74).
extern CellClass_00578390 InvalidCell_00578390;

struct Map_00578390
{
    char _pad0000[0xF4];              // +0x0000
    int MapRectWidth;                 // +0x00F4
    int MapRectHeight;                // +0x00F8
    int VisibleRectX;                 // +0x00FC
    int VisibleRectY;                 // +0x0100
    int VisibleRectWidth;             // +0x0104
    int VisibleRectHeight;            // +0x0108
    char _pad010C[0x13C - 0x10C];     // +0x010C
    CellClass_00578390** Cells;       // +0x013C

    // FUNCTION: GAMEMD 0x578390 — MapClass::InLocalRadar.
    int InLocalRadar(Rect_00578390* rect, bool checkLevel);
    // FUNCTION: GAMEMD 0x578460 — MapClass::IsWithinUsableArea.
    bool IsWithinUsableArea(Cell_00578390* cell, bool checkLevel);
};
GG_STATIC_ASSERT(offsetof(Map_00578390, MapRectWidth) == 0xF4);
GG_STATIC_ASSERT(offsetof(Map_00578390, VisibleRectX) == 0xFC);
GG_STATIC_ASSERT(offsetof(Map_00578390, VisibleRectY) == 0x100);
GG_STATIC_ASSERT(offsetof(Map_00578390, VisibleRectWidth) == 0x104);
GG_STATIC_ASSERT(offsetof(Map_00578390, VisibleRectHeight) == 0x108);
GG_STATIC_ASSERT(offsetof(Map_00578390, Cells) == 0x13C);

// GLOBAL: GAMEMD 0x87F7E8 — the map instance; its Cells member is 0x87F924.
extern Map_00578390 MapInstance_00578390;

#endif  // GG_MATCH_MAP_MAP_CLASS_LOCAL_RADAR_METHODS_H
