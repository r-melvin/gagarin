// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: retail gamemd.exe v1.001 disassembly at 0x56D3A0. MapClass keeps its map size at
//   +0xF4/+0xF8 and a table of four-byte word entries at +0x68 with the entry count at +0x6C.
//
// Address index: 0x56D3A0

#include "ui_display_chain.h"

// FUNCTION: GAMEMD 0x56D3A0
// The word value for a cell, indexed row-major over (Width + Height + 1) columns and
// clamped to the table (the sum of the size members, plus one, is the row width).
unsigned int MapClass::FUN_0056D3A0(const CellStruct* cell) const
{
    int index = (MapRect.Height + MapRect.Width + 1) * cell->Y + cell->X;
    if (index < 0) {
        index = 0;
    } else if (index >= WordCount) {
        index = WordCount - 1;
    }
    return Words[index].Value;
}
