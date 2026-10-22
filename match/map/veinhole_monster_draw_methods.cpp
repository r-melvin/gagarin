// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes diffed against retail gamemd.exe v1.001 at 0x74D490.

#include "veinhole_monster_draw_methods.h"

// FUNCTION: GAMEMD 0x74D490  VeinholeMonsterClass::DrawIt (__thiscall)
//
// Blit a living veinhole. The monster's cell centre is projected to screen
// space, the shape is drawn without its palette when the cell is hidden
// (flag 0x400000), the sprite is lifted 0x3A plus fifteen pixels per cell
// level, and the result is registered with the tactical selectable list
// before the blitter runs with the local player's remap table.
//
// PARTIAL (20.7%). The blitter's last two arguments are one point passed by
// value; with that, cl zeroes two registers and pushes the trailing zeros
// from them as retail does. Remaining: retail also zeroes EDX for the
// coordinate's Z, and holds the cell-centre X in EAX and Y in ECX where cl
// names them the other way round. Variants tried earlier: a shared
// `int zero = 0;` (constant-folded), the Y assignment before the X one.
//
// TAIL-MERGE DIAGNOSTIC (eleventh-batch lever): does NOT apply here.
// Retail's callee-saved pushes sit exactly where ours do (a single prologue
// EDI on both sides, seven sunk on both), the
// number of epilogues agrees, and the compiled block order already matches,
// so there are no merged return blocks to split. The residual is register
// naming downstream of that, not a prologue hoist.
void Monster_0074D490::DrawIt()
{
    if (IsDead)
        return;

    void* shape = DAT_00B1D2EC;
    void* palette = unknown_FC;

    Coord_0074D490 coord;
    coord.X = Cell.X * 256 + 0x80;
    coord.Y = Cell.Y * 256 + 0x80;
    coord.Z = 0;

    if (DAT_0087F7E8.GetCellAtCoord(coord)->Flags & 0x400000)
        palette = 0;

    Point_0074D490 point;
    DAT_00887324->CoordsToClient(&coord, &point);

    int lift = DAT_0087F7E8.GetCellAt(Cell)->Level * 15;
    point.Y = point.Y - 0x3A - lift;

    DAT_00887324->AddSelectable(this, point.X, DAT_00886FA4 + point.Y + 0x3A);

    void* remap = DAT_00B054D4[DAT_00A83D4C->unknown_16054]->unknown_30C;

    Point_0074D490 offset = {0, 0};
    FUN_004AED70(DAT_00887314, remap, shape, palette, &point, &DAT_00886FA0,
                 0x2E00, 0, -0x11 - lift, 0,
                 DAT_0087F7E8.GetCellAtCoord(coord)->unknown_10C,
                 0, 0, 0, offset);
}
