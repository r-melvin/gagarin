// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Offsets read off the user's retail gamemd.exe v1.001 at 0x5090F0
//   (SelectedPathIndex +0x20C, PlanningPaths +0x210, path Waypoints.Count
//   +0x38, path CurrentWaypointIndex +0x24, Rules +0x90).
#ifndef GG_MATCH_AI_HOUSE_CLASS_PLANNING_PATH_OPEN_METHODS_H
#define GG_MATCH_AI_HOUSE_CLASS_PLANNING_PATH_OPEN_METHODS_H

#include "../movement/waypoint_path_class_methods.h"
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// Rules view: the one field this function reads.
struct Rules_005090F0
{
    char _pad000[0x90];
    int  unknown_090;    // +0x90 planning-path length limit
};
GG_STATIC_ASSERT(offsetof(Rules_005090F0, unknown_090) == 0x90);

extern Rules_005090F0* DAT_008871E0;   // GLOBAL: GAMEMD 0x8871E0

class HouseClass
{
public:
    char               _pad000[0x20C];     // +0x0000
    int                SelectedPathIndex;  // +0x020C
    WaypointPathClass* PlanningPaths[12];  // +0x0210

    // FUNCTION: GAMEMD 0x5090F0
    bool CanExtendSelectedPlanningPath();
};
GG_STATIC_ASSERT(offsetof(HouseClass, SelectedPathIndex) == 0x20C);
GG_STATIC_ASSERT(offsetof(HouseClass, PlanningPaths) == 0x210);

#endif  // GG_MATCH_AI_HOUSE_CLASS_PLANNING_PATH_OPEN_METHODS_H
