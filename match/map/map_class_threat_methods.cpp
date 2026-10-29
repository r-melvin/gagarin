// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe (Ghidra disasm). Offsets reconfirmed
//   numerically from the disassembly at the listed address.
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x56BCD0  MapClass::GetThreatPosed  (__thiscall)

#include "map_class_threat_methods.h"

// Globals reconfirmed numerically from the disasm:
//   0x0087F924  Cells       — pointer to the flat CellClass* array.
//   0x00ABDC50  InvalidCell — dummy cell used when the index is out of range
//                             or empty (its MapCoords @0x24 => 0x00ABDC74).
extern CellClass** Cells;
extern CellClass   InvalidCell;

// FUNCTION: GAMEMD 0x56BCD0  (__thiscall, this unused)
// Resolve the live cell for `cell` (fall back to InvalidCell stamped with the
// requested coord), reduce its MapCoords to a 4x4 quadrant per axis, and return
// the house's threat estimate for that quadrant.
int MapClass::GetThreatPosed(const CellStruct& cell, HouseClass* pHouse) const
{
    int idx = (cell.Y << 9) + cell.X;

    CellClass* pCell;
    if (idx < 0 || idx >= 0x40000 || (pCell = Cells[idx]) == 0)
    {
        InvalidCell.MapCoords = cell;
        pCell = &InvalidCell;
    }

    CellStruct mc = pCell->MapCoords;
    int qy = mc.Y / 4;
    int qx = mc.X / 4;
    return pHouse->ThreatPosedEstimates[qy + 1][qx + 1];
}
