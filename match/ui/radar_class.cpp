// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm @ 0x653F50,
//   0x654490). Names cross-checked against YRpp (consult-only,
//   no LICENSE; every offset/address reconfirmed against the user's binary).
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x653F50   RadarClass::CreateEmptyMap   (__thiscall)
//   FUNCTION: GAMEMD 0x654490   RadarClass::SetVisibleRect   (__thiscall)
//   GLOBAL:   GAMEMD 0x87F7E8   RadarClass::Instance

#include "radar_class.h"

// FUNCTION: GAMEMD 0x653F50  (__thiscall)
// RadarClass override of MapClass::CreateEmptyMap — a pure forward to the base
// (0x565C10) with the same four arguments and the same `this`.
void RadarClass::CreateEmptyMap(const RectangleStruct& mapRect, bool reuse,
                               char nLevel, bool bUnk2)
{
    Map_CreateEmptyMap(mapRect, reuse, nLevel, bUnk2);
}

// FUNCTION: GAMEMD 0x654490  (__thiscall)
// Reset the radar's bounding rectangle to "empty" (X=Y=10000, W=H=0), recompute
// the map-pixel origin offsets, then walk the radar tracking list and grow the
// bounds to enclose every still-visible tracked cell.
//
// The 0x10-byte frame is two CellStruct locals (a at [ESP+0xC], b at
// [ESP+0x14]) whose halves are built in 32-bit from the int members and stored
// as words; the inlined operator+ then loads each pair back as a dword and adds
// before the MOVSX group. The cell handed to the visibility probe is a by-value
// GetCell() temporary bound to a const reference (the reused mapRect slot at
// [ESP+0x24]); the same getter feeds the x/y arithmetic after the call.
//
// PARTIAL (78.9%, 97/123). Mnemonic multiset identical; every diff is slot or
// register naming. (1) cl gives `a` the upper slot and `b` the lower
// ([ESP+0x14]/[ESP+0xC], retail the reverse) whichever is declared or
// assigned first; building b as a MakeCell() temporary or an operator+
// argument temporary does not swap them either. (2) Retail widens all four
// halves in place (`MOVSX ECX,CX; MOVSX EDX,DX; MOVSX EAX,AX; MOVSX EDI,DI`)
// before both SUBs; cl widens a.Y/a.X into fresh EDX/EAX after the first SUB.
// (3) In the loop retail keeps cell.Y in ECX and cell.X in EDX and interleaves
// the two sums (`SUB EAX,ECX; SUB ECX,EBP; ADD EAX,EDX; ADD ECX,EDX`); cl
// swaps the pair and finishes x before y, whether the sums are one expression
// each, split into four statements, or read through int locals. (4) The X
// bound check names Width EBX and span+x EBP where retail has EBP/EBX; both
// `x + span > Width + lo` and `lo + Width < span + x` give the same
// allocation. Earlier phrasings: 16-bit short locals (8.1%), int locals for
// left/top (swap the two leading loads), members read straight into shorts
// (16-bit loads), `return Cell;` getter (early temp store, 70.7%). This pass
// added: the four widened halves bound to int locals in retail's MOVSX order
// before the two SUBs (no change, 78.9%), and the `a`/`b` declarations
// swapped (76.4%) — cl gives the *first-used* struct the higher slot, which is
// the opposite of retail, where the first-stored struct is at [ESP+0xC].
void RadarClass::SetVisibleRect(const RectangleStruct& mapRect)
{
    Base_SetVisibleRect(mapRect);
    RadarBounds.Height = 0;
    RadarBounds.Y      = 10000;
    RadarBounds.X      = 10000;

    CellStruct b;
    CellStruct a;
    int ax = MapCellTop + MapCellLeft + 1;                 // [0x100] + [0xFC] + 1
    int ay = (MapSizeX - MapCellLeft) + MapCellTop;        // [0xF4]
    a.X = (short)ax;
    a.Y = (short)ay;
    RadarBounds.Width = 0;
    int bx = MapCellWidth - 1;                             // [0x104]
    int by = 1 - MapCellWidth;
    b.X = (short)bx;
    b.Y = (short)by;
    unknown_1498 = -1;
    CellStruct c = a + b;
    unknown_1494 = c.X - c.Y;
    unknown_1490 = a.Y - a.X;

    Instance.Func_578350();
    RadarTrackNode* node = Iterate_578290();
    while (node != 0)
    {
        if (Func_578460(node->GetCell(), true))
        {
            if (unknown_1498 == -1)
                unknown_1498 = node->Cell.Y + node->Cell.X;
            CellStruct cell = node->GetCell();
            int x = (unknown_1490 - cell.Y) + cell.X;
            int y = (cell.Y - unknown_1498) + cell.X;
            int span = 2;
            if (x == -1)
            {
                x = 0;
                span = 1;
            }
            else if (x == MapCellWidth * 2 - 1)
            {
                span = 1;
            }
            int lo = RadarBounds.X;
            if (x < lo)
                RadarBounds.X = x;
            else if (x + span > RadarBounds.Width + lo)
                RadarBounds.Width = (span - lo) + x;
            int top = RadarBounds.Y;
            if (y < top)
                RadarBounds.Y = y;
            else if (y + 1 > top + RadarBounds.Height)
                RadarBounds.Height = (y - top) + 1;
        }
        node = Iterate_578290();
    }
}
