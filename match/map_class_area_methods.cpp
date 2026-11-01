// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe (Ghidra disasm). Offsets reconfirmed
//   numerically from the disassembly at the listed address.
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x5785F0  MapClass::IsWithinUsableArea  (__thiscall)

#include "map_class_area_methods.h"

// FUNCTION: GAMEMD 0x5785F0  (__thiscall)
// Convert the world coord to a map cell (signed /256 per axis, stored as
// shorts) and delegate to the CellStruct overload @ 0x578460 with the
// level-check flag forced true.
bool MapClass::IsWithinUsableArea(const CoordStruct& coords) const
{
    return IsWithinUsableArea(Coord2Cell(coords), true);
}
