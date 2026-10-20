// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm).
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x4135A0  AircraftTrackerClass::IsJumpjet (__thiscall)

#include "foot_class_jumpjet.h"

// FUNCTION: GAMEMD 0x4135A0  (__thiscall)
// True when the cell `entry` stands on is already occupied by *another*
// jumpjet.  Retail loads entry->GetCell() (virtual @ vtable+0x1BC), reads the
// cell's Jumpjet occupant (CellClass+0xE0) and returns it != 0 && it != entry.
// `this` (the AircraftTrackerClass*) is unused — the body works on `entry`.
bool AircraftTrackerClass::IsJumpjet(TechnoClass* entry)
{
    void* jj = entry->GetCell()->Jumpjet;
    bool occupied = jj != 0 && jj != (void*)entry;
    return occupied;
}
