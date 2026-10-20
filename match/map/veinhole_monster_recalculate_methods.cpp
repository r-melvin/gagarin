// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x74E930.

#include "veinhole_monster_recalculate_methods.h"

// FUNCTION: GAMEMD 0x74E930
//
// Stamp the veinhole onto the map: the monster's own cell gets the veinhole
// overlay (type 0x7E), its eight neighbours alternate between the veinhole
// overlay and no overlay, every cell of the surrounding 5x5 block is
// re-evaluated, the spread is recomputed, the zones around the cell are
// rebuilt and the monster is flagged as placed.
//
// PARTIAL (87.0%, 67/77): the instruction multiset is identical; the only
// delta is the callee-saved register naming in the first half. Retail holds
// the centre cell in ESI and the facing counter in EDI (`MOV ESI,EAX ...
// XOR EDI,EDI; PUSH EDI; MOV ECX,ESI ... INC EDI; CMP EDI,8`); cl 8804 gives
// the counter ESI and the cell EDI. The 5x5 walk (dy in EBX, dx in ESI,
// the cell in EDI), the by-value CellOffset temporary and the tail are
// byte-exact. Variants tried, all identical: the counter declared before
// the cell; a ternary body; the neighbour stamp in a static inline helper;
// do/while and while forms of the loop; the cell assigned in a separate
// statement; the parity as a named bool; `register` on either or both;
// the overlay written unconditionally then overridden. Adding a use of the
// cell inside the loop changes the whole allocation (EBP/EBX), so retail's
// source has the same use counts and the difference is the allocator's
// tie-break.
//
// TAIL-MERGE DIAGNOSTIC (eleventh-batch lever): does NOT apply. There is one
// return, retail's prologue (SUB ESP,0xC; PUSH EBX; PUSH EBP; LEA EBP,[ECX+0xF8];
// PUSH ESI; PUSH EDI) is reproduced byte-for-byte, and both sides share one
// epilogue. Nine further spellings measured this pass, all 87.0% and
// byte-identical to the control: the eight-facing loop lifted into a free
// inline helper taking the cell; the centre stamp and that loop lifted
// together; the counter scoped to the `for` init; a do/while form; the 5x5
// tail lifted into an inline helper (whole tail, and the two loops alone);
// and `const` on the cell and neighbour pointers. Only two spellings move at
// all and both are worse: a ternary overlay assignment (28.2%) and the swapped
// parity arms (83.1%). Measuring the body as a free __fastcall function rather
// than a member costs 7.8 points on its own (79.2%), so variant sweeps for this
// function must clone the class, not lift the body out of it.
void VeinholeMonsterClass::Recalculate()
{
    Cell_0074E930* cell = MapInstance.GetCellAt(this->Cell);
    cell->OverlayTypeIndex = 0x7E;
    cell->OverlayData = 0;
    cell->RecalcAttributes(-1);

    int i;
    for (i = 0; i < 8; i++) {
        Cell_0074E930* neighbour = cell->GetNeighbourCell(i);
        if (i % 2 != 0) {
            neighbour->OverlayTypeIndex = -1;
        } else {
            neighbour->OverlayTypeIndex = 0x7E;
        }
        neighbour->OverlayData = 0;
    }

    int dy;
    for (dy = -2; dy <= 2; dy++) {
        int dx;
        for (dx = -2; dx <= 2; dx++) {
            Cell_0074E930* around = MapInstance.GetCellAt(CellOffset(this->Cell, dx, dy));
            around->FUN_00485AF0();
            around->RecalcAttributes(-1);
        }
    }

    this->RecalculateSpread();
    MapInstance.ResetZones(this->Cell);
    MapInstance.RecalculateSubZones(this->Cell);
    this->At_100 = 1;
}
