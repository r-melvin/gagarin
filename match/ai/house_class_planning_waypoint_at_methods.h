// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check | behaviour-confirmed-name
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x5023B0: `LEA EBX,[ECX+0x210]` + `ADD EBX,4` /
//   `CMP ESI,0xC` (PlanningPaths[12] @0x210), `PUSH 0x40` / `CALL 0x7C8E17` /
//   `CALL 0x763810` (0x40-byte WaypointPathClass + one-int ctor),
//   `MOV EAX,[ECX+0x38]` (Waypoints.Count), `CALL 0x763980` (GetWaypoint)
//   and the node's X/Y ints at +0x00/+0x04 (`MOV EAX,[ESI]` / `[ESI+4]`,
//   each signed-divided by 256 via CDQ/AND EDX,0xFF/ADD/SAR 8 and compared as
//   16 bits against the CellStruct argument). Names from YRpp
//   (every offset reconfirmed here). The
//   layout agrees with match/ai/house_class_planning_methods.h (not edited;
//   re-derived here so the TU stands alone).
#ifndef GG_MATCH_AI_HOUSE_CLASS_PLANNING_WAYPOINT_AT_METHODS_H
#define GG_MATCH_AI_HOUSE_CLASS_PLANNING_WAYPOINT_AT_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

#include "../_layout/cell.h"
GG_STATIC_ASSERT(sizeof(CellStruct) == 4);

// WaypointClass — a path node: a leptons-space coordinate (stride 0xC).
struct WaypointClass
{
    int X;   // +0x00
    int Y;   // +0x04
    int Z;   // +0x08
};
GG_STATIC_ASSERT(offsetof(WaypointClass, Y) == 0x04);
GG_STATIC_ASSERT(sizeof(WaypointClass) == 0xC);

// WaypointPathClass — only Waypoints.Count @0x38 and the size 0x40 matter.
class WaypointPathClass
{
public:
    // FUNCTION: GAMEMD 0x763810 (decl; reloc)
    explicit WaypointPathClass(int index) throw();

    // FUNCTION: GAMEMD 0x763980 (decl; reloc)
    WaypointClass* GetWaypoint(int idx) const;

    char _pad000[0x38];      // +0x0000
    int  WaypointCount;      // +0x0038
    char _pad03C[0x4];       // +0x003C
};
GG_STATIC_ASSERT(offsetof(WaypointPathClass, WaypointCount) == 0x38);
GG_STATIC_ASSERT(sizeof(WaypointPathClass) == 0x40);

class HouseClass
{
public:
    char               _pad000[0x210];     // +0x0000
    WaypointPathClass* PlanningPaths[12];  // +0x0210

    // FUNCTION: GAMEMD 0x5023B0
    WaypointClass* GetPlanningWaypointAt(const CellStruct* cell);
};
GG_STATIC_ASSERT(offsetof(HouseClass, PlanningPaths) == 0x210);

#endif  // GG_MATCH_AI_HOUSE_CLASS_PLANNING_WAYPOINT_AT_METHODS_H
