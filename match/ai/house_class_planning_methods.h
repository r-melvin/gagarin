// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check | behaviour-confirmed-name
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x502460: `LEA ESI,[ECX+0x210]` + `ADD ESI,4` /
//   `CMP EDI,0xC` (PlanningPaths[12] @0x210), `PUSH 0x40` / `CALL 0x7C8E17`
//   / `CALL 0x763810` (0x40-byte WaypointPathClass + one-int ctor),
//   `MOV EAX,[ECX+0x38]` (Waypoints.Count = vector @0x28 + Count @0x10) and
//   `CALL 0x763980` (GetWaypoint). Names from YRpp
//   (every offset reconfirmed here).
#ifndef GG_MATCH_AI_HOUSE_CLASS_PLANNING_METHODS_H
#define GG_MATCH_AI_HOUSE_CLASS_PLANNING_METHODS_H

#include "../movement/waypoint_path_class_methods.h"
#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/house_class.h"

class WaypointClass;   // opaque here — only compared by pointer identity

// Path and node types use their shared owners above.

GG_STATIC_ASSERT(offsetof(HouseClass, PlanningPaths) == 0x210);

#endif  // GG_MATCH_AI_HOUSE_CLASS_PLANNING_METHODS_H
