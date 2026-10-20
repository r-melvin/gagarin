// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes diffed against retail gamemd.exe v1.001 at 0x578390 and 0x578460.

#include "map_class_local_radar_methods.h"

// FUNCTION: GAMEMD 0x578390  MapClass::InLocalRadar
//
// A rectangle of cells is on the usable map when all four of its corners are:
// top-left, top-right, bottom-left, bottom-right, each checked in turn with
// the level flag passed through. The corner sums go through int locals so the
// arithmetic stays dword (a cast on the sum folds it to word ADDs, 21.7%), and
// the tests nest positively so every reject shares retail's one zero tail.
//
// PARTIAL (94.4%, 67/71; mnemonic multiset identical). The two Y + Height
// sums load their operands into EAX/ECX the other way round from retail
// (retail Y first; the X + Width sums match). Operand order in the sum,
// parenthesisation of the -1, named locals for either operand, and implicit
// int-to-short assignment (54.9%) do not move it — the same commutative-load
// tie-break seen at 0x4E15A0.
//
// The re-derive-at-the-use-site lever (the re-derived operand becomes the LEA
// base, the named local the index) was measured against this residual and does
// not reach it. Both sums are already a `LEA reg,[base+index*1-1]`, and cl
// makes the *higher* member offset the base regardless of how the source is
// written: eleven spellings in two compiles all give `[Height + Y*1 - 1]`
// where retail has `[Y + Height*1 - 1]` — the operands swapped, the `-1`
// parenthesised, the `-1` folded onto the Y term, Height named and Y
// re-derived, Y named and Height re-derived, the sum through an inline
// `Bottom(rect)` helper, and a volatile read of Height (73.2%). Naming Y once
// at the top of the function and reusing it for both corner rows is 11.3% and
// naming Height per block 9.6% — both collapse the corner blocks. The X+Width
// sums, whose base is likewise the higher offset, match retail already, so the
// two sums genuinely disagree about which operand retail put in the base.
//
// TAIL-MERGE DIAGNOSTIC (eleventh-batch lever): does NOT apply here.
// Retail's callee-saved pushes sit exactly where ours do (prologue EBX, ESI,
// EDI on both sides), the
// number of epilogues agrees, and the compiled block order already matches,
// so there are no merged return blocks to split. The residual is register
// naming downstream of that, not a prologue hoist.
int Map_00578390::InLocalRadar(Rect_00578390* rect, bool checkLevel)
{
    Cell_00578390 topLeft;
    topLeft.X = (short)rect->X;
    topLeft.Y = (short)rect->Y;
    if (IsWithinUsableArea(&topLeft, checkLevel)) {
        Cell_00578390 topRight;
        int right = rect->X + rect->Width - 1;
        topRight.X = (short)right;
        topRight.Y = (short)rect->Y;
        if (IsWithinUsableArea(&topRight, checkLevel)) {
            Cell_00578390 bottomLeft;
            int bottom = rect->Height + rect->Y - 1;
            bottomLeft.X = (short)rect->X;
            bottomLeft.Y = (short)bottom;
            if (IsWithinUsableArea(&bottomLeft, checkLevel)) {
                Cell_00578390 bottomRight;
                int right2 = rect->X + rect->Width - 1;
                int bottom2 = rect->Height + rect->Y - 1;
                bottomRight.X = (short)right2;
                bottomRight.Y = (short)bottom2;
                if (IsWithinUsableArea(&bottomRight, checkLevel))
                    return 1;
            }
        }
    }
    return 0;
}

// MapClass::operator[](CellStruct) as VC6 inlines it: the fixed 512x512
// bound through the global instance, then the fallback cell with the
// coordinate stamped into it.
static inline CellClass_00578390* CellAt_00578390(Cell_00578390* pos)
{
    int idx = (pos->Y << 9) + pos->X;
    if (idx >= 0 && idx < 0x40000) {
        CellClass_00578390* pCell = MapInstance_00578390.Cells[idx];
        if (pCell != 0)
            return pCell;
    }
    InvalidCell_00578390.MapCoords = *pos;
    return &InvalidCell_00578390;
}

// FUNCTION: GAMEMD 0x578460  MapClass::IsWithinUsableArea
//
// Is the cell inside the usable (visible) diamond of the map. The isometric
// diamond is tested on the two diagonals x+y and x-y against the visible
// rectangle scaled by two. With `checkLevel` the cell is looked up and its
// height level shifts the x+y band; a sloped cell just inside the top edge
// counts one level higher. `x` is declared before `y` so the y + x sums
// take y as the LEA base, as retail has them.
bool Map_00578390::IsWithinUsableArea(Cell_00578390* cell, bool checkLevel)
{
    int level = 0;
    int x = cell->X;
    int y = cell->Y;

    if (checkLevel) {
        CellClass_00578390* pCell = CellAt_00578390(cell);
        level = pCell->Level;
        if (pCell->SlopeIndex != 0) {
            if (y + x < this->MapRectWidth + this->VisibleRectY * 2 + 4 + level)
                level = level + 1;
        }
    }

    if (y + x > this->MapRectWidth + this->VisibleRectY * 2 + level
        && y + x <= this->MapRectWidth
                    + (this->VisibleRectHeight + this->VisibleRectY) * 2 + 2 + level
        && x - y < (this->VisibleRectWidth + this->VisibleRectX) * 2 - this->MapRectWidth
        && y - x < this->MapRectWidth - this->VisibleRectX * 2)
        return true;
    return false;
}
