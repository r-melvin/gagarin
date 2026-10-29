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

#include "../movement/waypoint_path_class_methods.h"
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

#include "../_layout/cell.h"
#include "../_layout/house_class.h"
GG_STATIC_ASSERT(sizeof(CellStruct) == 4);

// Path and node types use their shared owners above.

GG_STATIC_ASSERT(offsetof(HouseClass, PlanningPaths) == 0x210);

#endif  // GG_MATCH_AI_HOUSE_CLASS_PLANNING_WAYPOINT_AT_METHODS_H
