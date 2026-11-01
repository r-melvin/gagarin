// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 @ 0x6F1870 / 0x6F18A0 /
//   0x6F18E0 (Ghidra disasm).  Structure cross-checked against YRpp
//   (each offset
//   and call target reconfirmed against the user's binary).
//
// Translation unit: TeamTypeClass waypoint/group accessors.
//   FUNCTION: GAMEMD 0x6F1870   TeamTypeClass::GetGroup             (__thiscall)
//   FUNCTION: GAMEMD 0x6F18A0   TeamTypeClass::GetWaypoint          (__thiscall)
//   FUNCTION: GAMEMD 0x6F18E0   TeamTypeClass::GetTransportWaypoint (__thiscall)
//   GLOBAL:   GAMEMD 0xA8B230   WaypointLocator pointer
//   GLOBAL:   GAMEMD 0xB0E9C8   DefaultWaypointCell (CellStruct)
//
// Match status (reccmp diff_retail.py vs retail, reloc-normalised): see report.

#include "team_type_class_methods.h"

// ---------------------------------------------------------------------------


// ---------------------------------------------------------------------------


// ---------------------------------------------------------------------------


// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0xB0E9C8
CellStruct DefaultWaypointCell;
// END defined globals
