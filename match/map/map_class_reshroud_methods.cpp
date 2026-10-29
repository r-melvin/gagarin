// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x577AB0.

#include "map_class_reshroud_methods.h"

// FUNCTION: GAMEMD 0x577AB0
//
// Put the shroud back over the whole map for a house. The house's own
// registry entry has its 0x241 byte cleared first; then, only when the house
// is the local player (or nobody at all, which is logged), every cell is reset
// to shrouded through the map's cell iterator, the current player's 0x240
// byte is cleared, the map reprocesses itself and the screen is flagged for a
// full redraw through vtable slot 0x38.
//
// PARTIAL (92.3%, 60/65): the instruction multiset is identical; the only
// delta is the scheduling of the inlined iterator reset. Retail keeps the
// out-of-line 0x578350 order (`MOV EAX,[ESI+0xF4]; MOV [ESI+0x10C],1; MOV
// [ESI+0x110],EAX; LEA EDX,[EAX-1]; MOV [ESI+0x114],EDX; MOV ECX,[ESI+0x13C];
// SHL EAX,0xB; LEA EDX,[EAX+ECX+4]`), while cl 8804 hoists `MOV
// ECX,[ESI+0x13C]` to just after the count load and the `SHL` above the
// IterLast store. The same body compiled out of line (this in ECX) matches
// 0x578350 byte for byte, so the delta is the scheduler's use of the free
// ECX in the inlined context. Variants tried, all identical: operand order
// `count * 0x800 + At_13C + 4`; re-reading IterCount/IterLast from the
// members; a char* cast on the base; `(count << 11) + 4` grouped; the
// parenthesised `At_13C + (count * 0x800 + 4)`.
void MapView_578350::Reshroud(HouseClass* house)
{
    if (house != 0) {
        DAT_00A80228.Items[house->ArrayIndex]->MapIsClear = 0;
    }

    if (house == DAT_00A83D4C || house == 0) {
        if (house == 0) {
            FUN_004068E0(DAT_0082AD48);
        }

        MapInstance.FUN_004ADEE0(0, 0);

        this->CellIteratorReset();
        Cell_00577AB0* cell = this->CellIteratorNext();
        while (cell != 0) {
            cell->AltFlags &= ~0x18;
            cell->ShroudCounter = 1;
            cell->At_134 = 0;
            cell->Flags &= ~3;
            cell = this->CellIteratorNext();
        }

        MapInstance.FUN_004ADCD0(0, 0);
        DAT_00A83D4C->Visionary = 0;
        MapInstance.FUN_00657CE0();
        (this->*this->Vtbl->At_38)(2);
    }
}
