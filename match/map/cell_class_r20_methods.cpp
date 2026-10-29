// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm), CellClass height helpers.

#include "../_layout/cell_class.h"

// FUNCTION: GAMEMD 0x4CC680
// True when the third cell stands at least 4 height steps above the second and
// strictly above the first.
int __fastcall FUN_004CC680(CellClass* first, CellClass* second, CellClass* third)
{
    if (third->FUN_00487D50() - second->FUN_00487D50() >= 4) {
        if (third->FUN_00487D50() - first->FUN_00487D50() > 0)
            return 1;
    }
    return 0;
}
