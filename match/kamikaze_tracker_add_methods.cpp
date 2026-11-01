// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x54E3B0.

#include <new.h>
#include "kamikaze_tracker_add_methods.h"

// FUNCTION: GAMEMD 0x54E3B0
//
// Register an aircraft for a kamikaze run. A type that cannot spawn a
// missile simply crashes. Otherwise a node pairs the aircraft with its
// target cell: the cell of the given target, or, with no target, the cell
// one step ahead along the aircraft's facing. The aircraft is flagged and
// given one round, and the node appended to the tracker's list.
//
// The cell-ahead branch is an inline member whose facing local lives in EDI
// across the GetCell call (facing first, then the cell bound to a local,
// then the neighbour lookup); that is what gives retail the PUSH/POP EDI
// around that branch alone and keeps the node in EBX and this in EBP.
void Kamikaze_0054E3B0::Add(Techno_0054E3B0* item, Abstract_0054E3B0* target)
{
    if (!item->Type->MissileSpawn) {
        (item->*item->Vptr->Crash)(0);
        return;
    }

    Node_0054E3B0* node = (Node_0054E3B0*)operator new(sizeof(Node_0054E3B0));
    node->Item = item;
    if (target == 0) {
        node->Cell = item->CellAhead();
    } else {
        Coord_0054E3B0 buf;
        node->Cell = MapInstance_0054E3B0.GetCellAt(
            CoordToCell_0054E3B0((target->*target->Vptr->GetCoords)(&buf)));
    }
    item->At_6CA = 1;
    item->Ammo = 1;

    Nodes.AddItem(node);
}
