// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes diffed against the user's retail gamemd.exe v1.001; bodies ascending
//   by retail address.
#include "cell_class_sensor_methods.h"


// FUNCTION: GAMEMD 0x487EA0
// Step `src` one square in direction `dir`, wrapping the direction into the
// eight-entry step table. The pair is built in a temporary and copied out as a
// single dword, which is the shape retail emits.
CellStruct* FUN_00487EA0(CellStruct* dest, CellStruct const* src,
                         int dir)
{
    CellStruct const* step = &AdjacentCellTable[dir & 7];
    CellStruct out;

    out.X = (short)(step->X + src->X);
    out.Y = (short)(step->Y + src->Y);
    *dest = out;
    return dest;
}
