// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes diffed against retail gamemd.exe v1.001 at 0x586990.

#include "ui_display_chain.h"
#include "_layout/cell_class.h"

// FUNCTION: GAMEMD 0x586990  MapClass::Update_Pathfinding_2 (__thiscall, ret 4)
//
// Second half of the pathfinding refresh over a list of dirtied cells. The
// first pass walks the list backwards, and for every cell that is inside the
// usable area clears its sub-zone record and asks the cell itself to redraw.
// The second pass walks the same list again and, for every still-cleared
// sub-zone record, rebuilds that cell's zone.
void MapClass::Update_Pathfinding_2(DynamicVectorClass<CellStruct>* cells)
{
    int i;

    for (i = cells->Count - 1; i >= 0; i--)
    {
        if (IsWithinUsableArea(cells->Items[i], true))
        {
            int index = (MapRect.Height + MapRect.Width + 1) * cells->Items[i].Y
                      + cells->Items[i].X;
            if (index < 0)
                index = 0;
            else if (index >= WordCount)
                index = WordCount - 1;
            Records[index].Value = 0;

            CellStruct* p = &cells->Items[i];
            int flat = p->Y * 512 + p->X;
            CellClass* cell;
            if (flat < 0 || flat >= 0x40000 || (cell = Map_0087F7E8.Owned[flat]) == 0)
            {
                InvalidCell.MapCoords = *p;
                cell = &InvalidCell;
            }
            cell->FUN_0047D2B0(-1);
        }
    }

    for (i = cells->Count - 1; i >= 0; i--)
    {
        CellStruct cell = cells->Items[i];
        if (IsWithinUsableArea(cell, true))
        {
            int index = (MapRect.Height + MapRect.Width + 1) * cell.Y + cell.X;
            if (index < 0)
                index = 0;
            else if (index >= WordCount)
                index = WordCount - 1;
            if (Records[index].Value == 0)
                FUN_00584550(cell);
        }
    }
}
