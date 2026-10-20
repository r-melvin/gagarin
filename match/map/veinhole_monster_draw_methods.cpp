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
// PARTIAL (15.2%, 14/92; multiset is retail minus three `xor`). Every
// instruction of the body is present; the only mnemonic-level delta is that
// retail materialises its zeros into registers and pushes those -- `XOR
// EDX,EDX` for the coordinate's Z and `XOR ECX,ECX` / `XOR EAX,EAX` for the
// five trailing blitter arguments, pushed as ECX/EAX/ECX/ECX/ECX -- where cl
// 8804 pushes the immediate `0` under every flag set. That is the recorded
// 8447-vs-8804 "repeated push constants materialised into registers" class
// (see docs/matching_methodology_and_toolchain.md), already observed at
// 0x4FBF60, 0x703590 and 0x41A2C0. The three missing XORs shift the whole
// stream, which is why the reported percentage is far below the real delta;
// the secondary difference is that retail holds the cell-centre X in EAX and Y
// in ECX where VC6 names them the other way round. Variants tried: a shared
// `int zero = 0;` feeding the Z store and all five trailing arguments (cl
// constant-folds it; byte-identical, 15.2%); the Y assignment written before
// the X assignment (byte-identical, 15.2%, kept the natural order).
// Lift pass 2 (2026-09-18): re-read against retail and classified, not
// re-chased. Retail's `XOR EDX,EDX` for coord.Z is the SAME 8447 heuristic as
// the five pushed zeros - `XOR reg,reg; MOV [mem],reg` is 5 bytes against
// cl 8804's 7-byte `MOV dword ptr [mem],0` - so all three missing XORs are one
// banked 8447-vs-8804 constant-materialisation class, not three deltas. The
// residual X/Y register swap is downstream of the resulting shift. Best
// measured form kept at 15.2%.
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

    void* remap = DAT_00B054D4[DAT_00A83D4C->PlayerIndex]->unknown_30C;

    FUN_004AED70(DAT_00887314, remap, shape, palette, &point, &DAT_00886FA0,
                 0x2E00, 0, -0x11 - lift, 0,
                 DAT_0087F7E8.GetCellAtCoord(coord)->unknown_10C,
                 0, 0, 0, 0, 0);
}
