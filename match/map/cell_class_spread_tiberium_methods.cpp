// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x483780.

#include "cell_class_spread_tiberium_methods.h"

// FUNCTION: GAMEMD 0x483780
//
// PARTIAL (76.7%, 89/116; instruction multiset identical). Everything up to the
// neighbour walk is exact; the residual delta is inside the inlined neighbour
// step, where cl 12.00.8804 names the two halves of the cell addition in DX/AX
// (loading the table word and adding the cell word) while retail accumulates
// both into CX, and picks a different frame slot for the spilled tiberium index
// (retail reuses the dead `forced` parameter home slot at [ESP+0x20]).
// Variants tried for that block: the two coordinates added by hand into a named
// temp (57-60%), the second table access bound to a pointer local (60.7%), a
// by-reference `operator+` with an explicit result local (60.7%, and it costs
// an extra MOV), and a by-value first operand mutated in place and returned
// (76.7%, kept; `a.Y = b.Y + a.Y` and `a.Y = a.Y + b.Y` score the same).
// Retail's frame is 4 bytes larger because it keeps the sum in its own
// CellStruct slot at [ESP+0x10] and copies it into `cell` at [ESP+0x14] as a
// whole dword; an explicit `CellStruct sum = cell + tbl[f]; cell = sum;`
// spelling is copy-propagated away by cl (still 76.7%), and giving operator+ an
// explicit result local instead of mutating the by-value operand costs a MOV
// and drops to 60.7%.
// The `if (facing >= 8) result = this; else ...` spelling is what puts retail's
// `this` arm on the fallthrough path, and the `forced == 0` arm has to come
// first for the two -1 tests to land in retail's order.
//
// CellClass::SpreadTiberium — try to push this cell's ore into one of its eight
// neighbours. Unless the caller forces it, the scenario must have the spread
// flag, the cell must actually carry tiberium, its overlay data must be past
// the halfway mark for that tiberium index, the cell must not be flagged at
// +0x11C, the tiberium's +0xA0 must not be below the rules constant, and the
// cell must be empty. The eight neighbours are then visited starting from a
// random facing, and the first one that will accept germination gets three
// units of this cell's tiberium laid into it.
bool Cell_00483780::SpreadTiberium(char forced)
{
    if (forced == 0) {
        if ((DAT_00A8B230->Flags & 0x80) == 0) {
            return false;
        }
        int index = OverlayTypeIndexToTiberium_00483780(this->OverlayTypeIndex);
        if (index == -1) {
            return false;
        }
        if (this->OverlayData <= index / 2) {
            return false;
        }
        if (this->At_11C != 0) {
            return false;
        }
        if (TiberiumArrayItems_00483780[index]->At_0A0 < DAT_007E3810) {
            return false;
        }
        if (this->FirstObject != 0) {
            return false;
        }
    }

    int tiberium = OverlayTypeIndexToTiberium_00483780(this->OverlayTypeIndex);
    if (forced == 0) {
        if (tiberium == -1) {
            return false;
        }
    } else {
        if (tiberium == -1) {
            tiberium = 0;
        }
    }

    Tiberium_00483780* type = TiberiumArrayItems_00483780[tiberium];
    int start = DAT_00A8B230->Random.RandomRanged(0, 7);

    for (int i = 0; i < 8; i++) {
        Cell_00483780* neighbour = this->GetNeighbourCell((i + start) & 7);
        if (neighbour != 0 && neighbour->CanTiberiumGerminate(type)) {
            return neighbour->FUN_00487190(tiberium, 3);
        }
    }

    return false;
}
