// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets/convention derived from the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI (member-access disassembly at 0x6F1870 / 0x6F18A0 /
//   0x6F18E0), cross-checked against YRpp
//   (every offset reconfirmed numerically below).
//
// TeamTypeClass — an AI [TeamTypes] INI "team blueprint", derived from
// AbstractTypeClass.  Only the members the three matched accessors touch are
// modelled; the full layout is P2.  Confirmed offsets:
//   Group             @ +0x9C  (MOV EAX,[ECX+0x9c] in GetGroup)
//   Waypoint          @ +0xD4  (MOV EAX,[ECX+0xd4] in GetWaypoint)
//   TransportWaypoint @ +0xD8  (MOV EAX,[ECX+0xd8] in GetTransportWaypoint)
//   TaskForce         @ +0xE4  (MOV ECX,[ECX+0xe4] then [ECX+0x98] in GetGroup; the INI reader
//                               0x6F1090 fills it from the "TaskForce" key. The owner house is at +0xC4.)
#ifndef GG_MATCH_AI_TEAM_TYPE_CLASS_METHODS_H
#define GG_MATCH_AI_TEAM_TYPE_CLASS_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/abstract_type_class.h"
#include "../_layout/team_type_class.h"

// CellStruct — 2D short cell coordinate (sizeof = 4).  Self-guarded for reuse.
#include "../_layout/cell.h"
GG_STATIC_ASSERT(sizeof(CellStruct) == 4);


// ---------------------------------------------------------------------------
// Waypoint-coordinate locator.  GetWaypoint/GetTransportWaypoint load a global
// object pointer (GAMEMD 0xA8B230) into ECX and __thiscall 0x68BCC0 with an
// out-buffer + waypoint index; it returns the buffer holding the cell.  Declared
// body-less so cl emits a reloc-normalised direct call.
// ---------------------------------------------------------------------------
struct WaypointLocator
{
    CellStruct* GetCoords(CellStruct* out, int index);   // GAMEMD 0x68BCC0
};
extern WaypointLocator* WaypointLocatorPtr;              // GAMEMD 0xA8B230
extern CellStruct       DefaultWaypointCell;             // GAMEMD 0xB0E9C8



#endif  // GG_MATCH_AI_TEAM_TYPE_CLASS_METHODS_H
