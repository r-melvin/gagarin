// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x4DCFE0.

#include "foot_class_move_to_tiberium_methods.h"

// FUNCTION: GAMEMD 0x4DCFE0
//
// Head for the nearest tiberium. Nothing happens while a destination is
// already set. The cell search (slot 0x338) hands back a cell or the "no cell"
// sentinel; if it is the cell this object already stands on, report true,
// otherwise make it the destination and report false.
bool Obj_004DCFE0::MoveToTiberium(int radius, int scanClose)
{
    if (this->Destination != 0) {
        return false;
    }

    Cell_004DCFE0 buf;
    Cell_004DCFE0 cell = *(this->*this->Vtbl->At_338)(&buf, radius, scanClose);

    if (cell.X != NoCell_004DCFE0.X || cell.Y != NoCell_004DCFE0.Y) {
        Coord_004DCFE0 coordBuf;
        Coord_004DCFE0* coords = (this->*this->Vtbl->GetCoords)(&coordBuf);
        Cell_004DCFE0 mine;
        mine.X = (short)(coords->X / 256);
        mine.Y = (short)(coords->Y / 256);
        if (cell.X == mine.X && cell.Y == mine.Y) {
            return true;
        }
        (this->*this->Vtbl->SetDestination)(MapInstance_004DCFE0.GetCellAt(cell), 1);
    }
    return false;
}
