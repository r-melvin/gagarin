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
#include "../_layout/house_class.h"


#include "../_layout/rules_class.h"
extern RulesClass* DAT_008871E0;


GG_STATIC_ASSERT(offsetof(HouseClass, SelectedPathIndex) == 0x20C);
GG_STATIC_ASSERT(offsetof(HouseClass, PlanningPaths) == 0x210);

#endif  // GG_MATCH_AI_HOUSE_CLASS_PLANNING_PATH_OPEN_METHODS_H
