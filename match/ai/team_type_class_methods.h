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
//   Owner (house ptr) @ +0xE4  (MOV ECX,[ECX+0xe4] then [ECX+0x98] in GetGroup)
#ifndef GG_MATCH_AI_TEAM_TYPE_CLASS_METHODS_H
#define GG_MATCH_AI_TEAM_TYPE_CLASS_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/abstract_type_class.h"

// CellStruct — 2D short cell coordinate (sizeof = 4).  Self-guarded for reuse.
#ifndef GG_MATCH_LAYOUT_CELLSTRUCT_DEFINED
#define GG_MATCH_LAYOUT_CELLSTRUCT_DEFINED
struct CellStruct
{
    short X;   // +0x00
    short Y;   // +0x02
};
GG_STATIC_ASSERT(sizeof(CellStruct) == 4);
#endif

// ---------------------------------------------------------------------------
// Partial HouseClass view: GetGroup reads the dword at house+0x98 when a team's
// Group is the "owner's group" sentinel (-1).  Only that one member is pinned.
// ---------------------------------------------------------------------------
struct TeamOwnerHouse
{
    char _pad_00[0x98];   // +0x00..0x97
    int  Group;           // +0x98
};
GG_STATIC_ASSERT(offsetof(TeamOwnerHouse, Group) == 0x98);

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

// ---------------------------------------------------------------------------
// TeamTypeClass  (AbstractTypeClass + the touched members; full layout = P2)
// ---------------------------------------------------------------------------
struct TeamTypeClass : AbstractTypeClass
{
    int             ArrayIndex;          // +0x98
    int             Group;               // +0x9C
    char            _pad_A0[0xD4 - 0xA0];// +0xA0..0xD3 (P2)
    int             Waypoint;            // +0xD4
    int             TransportWaypoint;   // +0xD8
    char            _pad_DC[0xE4 - 0xDC];// +0xDC..0xE3 (P2)
    TeamOwnerHouse* Owner;               // +0xE4

    int         GetGroup() const;
    CellStruct* GetWaypoint(CellStruct* buffer) const;
    CellStruct* GetTransportWaypoint(CellStruct* buffer) const;
};

GG_STATIC_ASSERT(offsetof(TeamTypeClass, Group)             == 0x9C);
GG_STATIC_ASSERT(offsetof(TeamTypeClass, Waypoint)          == 0xD4);
GG_STATIC_ASSERT(offsetof(TeamTypeClass, TransportWaypoint) == 0xD8);
GG_STATIC_ASSERT(offsetof(TeamTypeClass, Owner)             == 0xE4);

#endif  // GG_MATCH_AI_TEAM_TYPE_CLASS_METHODS_H
