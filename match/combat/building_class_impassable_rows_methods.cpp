// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x458A00.

#include "building_class_impassable_rows_methods.h"

// FUNCTION: GAMEMD 0x458A00
//
// Does this building block the given cell? The cell has to actually hold this
// building (`CellClass::GetBuilding` must answer `this`); a type that left
// NumberImpassableRows at -1 blocks everywhere; a bunker type blocks while
// something is linked into it; otherwise the impassable band is the first
// NumberImpassableRows columns measured from the building's own top-left map
// coordinate, so the cell is blocked while its X still falls inside that band.
//
// MATCHED (100.0%, 44/44). Two levers, both measured across a 17-variant batch
// scored in one compile:
//   * the cell's coordinate has to be bound to an `int` local BEFORE the
//     map-coords slot is called. Retail hoists `MOVSX EDI,word ptr [EDI+0x24]`
//     above the call because the cell pointer is dead there and its incoming
//     argument slot is then free to serve as the slot's hidden out-pointer
//     (`LEA ECX,[ESP+0xc]`, and the function allocates no frame at all).
//     Reading the coordinate inside the comparison instead leaves it after the
//     call: 68.9%. The local takes it to 77.8%, and binding the slot's result
//     to its own `int edge` as well reaches 86.7%.
//   * the last 13.3% is a stray `XOR EAX,EAX` that cl 8804 inserts ahead of
//     `CMP/SETG AL` when a comparison is returned directly. Retail has no such
//     zero here (it does have one at 0x50E1B0, where the comparison is the
//     whole body), so the bool must not reach the return as a bare relational
//     expression. Spelling the test as an `if` with the two constant returns —
//     the same shape as every other arm of this predicate — removes it.
//     `bool r = ...; return r;` and a `? true : false` ternary also reach
//     100.0%; a `!(a <= b)` inversion, an `(a - b) > 0` rewrite, a `(char)`
//     cast, an inline `Exceeds(a, b)` helper, an `int limit` temporary,
//     swapping the comparison round, copying the coordinate struct by value
//     and moving the local's declaration all stay at 86.7% or worse.
bool BuildingClass_00458A00::IsCellImpassable(CellClass_00458A00* cell)
{
    if (cell->GetBuilding() != this) {
        return false;
    }
    if (Type->NumberImpassableRows == -1) {
        return true;
    }
    if (Type->Bunker && BunkerLinkedItem != 0) {
        return true;
    }

    int cellX = cell->MapCoords.X;
    CellStruct_00458A00 here;
    int edge = (this->*this->Vtbl->GetMapCoords)(&here)->X;
    if (Type->NumberImpassableRows + edge > cellX) {
        return true;
    }
    return false;
}
