// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe (Ghidra disasm). Signatures
//   cross-checked against YRpp.
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x4F42D0  MapClass::FUN_004F42D0      (__thiscall)
//   FUNCTION: GAMEMD 0x568300  MapClass::CoordinatesLegal  (__thiscall)

#include "map_class_more_methods.h"

// FUNCTION: GAMEMD 0x4F42D0  (__thiscall)
// Unconditionally force the bitfield to the "full redraw" state (2), unlike
// GScreenClass::FlagToRedraw (0x4F42F0) which only sets it when not already 2.
void MapClass::FUN_004F42D0()
{
    this->RedrawFlag = 2;
}

// FUNCTION: GAMEMD 0x568300  (__thiscall)
// Diamond-bounds test in iso cell coordinates against MapRect.Width / Height.
bool MapClass::CoordinatesLegal(const CellStruct& cell) const
{
    int x = cell.X;
    int y = cell.Y;
    int w = this->MapRect.Width;
    bool legal = (x + y) > w
        && (x - y) < w
        && (y - x) < w
        && (x + y) <= w + 2 * this->MapRect.Height;
    return legal;
}
