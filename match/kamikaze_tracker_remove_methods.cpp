// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x54E590.

#include "kamikaze_tracker_remove_methods.h"

// The cell a coordinate falls in (the inlined coord-to-cell conversion: a
// signed divide by 256 of X and Y).
static inline Cell_0054E590 CoordToCell_0054E590(const Coord_0054E590* coord)
{
    Cell_0054E590 cell;
    cell.X = (short)(coord->X / 256);
    cell.Y = (short)(coord->Y / 256);
    return cell;
}

// FUNCTION: GAMEMD 0x54E590  Kamikaze::Remove (__thiscall, ret 4)
//
// An object is leaving the game: walk the kamikaze nodes back to front. If
// it is a node's aircraft the node is freed and pulled out of the vector
// (the remaining entries slide down). If it is a node's target cell, the
// aircraft is retargeted at the cell under the object's current coordinate
// and told to attack it, and the node remembers that cell instead. Only the
// first node touching the object is handled.
//
// The slide-down after the free is DynamicVectorClass::RemoveItem's loop with
// the index already known: it runs on a second index `j` copied from `i`
// (retail's `MOV EAX,ESI` before the loop); reusing `i` itself keeps the
// loop in ESI and turns the count decrement into a DEC (68.1%). The cell
// handed to GetCellAt is the by-value result of an inline coord-to-cell
// helper, which VC6 builds in the parameter's home slot and then copies
// into a 4-byte temporary for the const-reference argument.
void Kamikaze_0054E590::Remove(Abstract_0054E590* object)
{
    for (int i = this->Nodes.Count - 1; i >= 0; i--) {
        if ((void*)object == (void*)this->Nodes.Items[i]->Item) {
            GameDelete_0054E590(this->Nodes.Items[i]);
            if (i < this->Nodes.Count) {
                this->Nodes.Count = this->Nodes.Count - 1;
                for (int j = i; j < this->Nodes.Count; ++j)
                    this->Nodes.Items[j] = this->Nodes.Items[j + 1];
            }
            return;
        }
        if ((void*)object == (void*)this->Nodes.Items[i]->Cell) {
            Coord_0054E590 coord;
            CellClass_0054E590* cell = DAT_0087F7E8.GetCellAt(
                CoordToCell_0054E590((object->*object->Vtbl->GetCoords)(&coord)));
            (this->Nodes.Items[i]->Item->*this->Nodes.Items[i]->Item->Vtbl->SetTarget)(cell);
            (this->Nodes.Items[i]->Item->*this->Nodes.Items[i]->Item->Vtbl->QueueMission)(1, 0);
            this->Nodes.Items[i]->Cell = cell;
            return;
        }
    }
}
