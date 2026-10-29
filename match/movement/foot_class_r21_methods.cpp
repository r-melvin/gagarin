// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Offsets, vtable slots and callees read off the user's retail gamemd.exe v1.001 with the
//   local Ghidra CLI at the address in each annotation. FootClass vtable is 0x7E8C94.
//
// Round 21 FootClass slot overrides, ascending by retail address.
// Address index: 0x4DBDA0, 0x4DE580, 0x4DE5D0, 0x4DF1F0
#include "../_layout/foot_class.h"
#include "../_layout/capture_manager_class.h"
#include "../_layout/team_class.h"
#include "../_layout/house_class.h"
#include "waypoint_path_class_methods.h"
#include "../_layout/techno_type_class.h"
#include "loco_com.h"

// GLOBAL: GAMEMD 0xA83D4C -- HouseClass::CurrentPlayer.
extern HouseClass* DAT_00A83D4C;

// FUNCTION: GAMEMD 0x4DBDA0
// Slot 162: cloakable as a TechnoClass, and (for a type that cannot cloak while
// moving) only when the locomotor is not moving.
bool FootClass::IsCloakable()
{
    if (TechnoClass::IsCloakable()) {
        if (!vf_33()->bools_C8C[7] || !(*(ILocomotionPtr*)&Locomotor)->IsMovingNow())
            return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x4DE580
// Slot 205: with a planning path selected, step to the waypoint that follows the
// current one on the local player's path of that index.
void FootClass::vf_205()
{
    if (PlanningPathIdx != -1) {
        WaypointClass* current = DAT_00A83D4C->PlanningPaths[PlanningPathIdx]->GetWaypoint(WaypointIndex);
        FUN_004DC8C0(DAT_00A83D4C->PlanningPaths[PlanningPathIdx]->GetWaypointAfter(current));
    }
}

// FUNCTION: GAMEMD 0x4DE5D0
// Slot 62: before the ObjectClass step, release any units this one mind-controls,
// drop the locomotor target, and leave the team.
void FootClass::vf_62()
{
    if (CaptureManager)
        static_cast<CaptureManagerClass*>(CaptureManager)->FreeAll();
    if (LocomotorTarget)
        FUN_0070FEE0(true);
    if (Team)
        Team->LiberateMember(this, -1, 0);
    ObjectClass::vf_62();
}

// FUNCTION: GAMEMD 0x4DF1F0
// Slot 302: the coordinate of the mega destination, else of the mega target,
// else (-1, -1, -1).
CoordStruct FootClass::vf_302()
{
    if (MegaDestination)
        return ((AbstractClass*)MegaDestination)->vf_18();
    if (MegaTarget)
        return ((AbstractClass*)MegaTarget)->vf_18();
    CoordStruct none;
    none.X = -1;
    none.Y = -1;
    none.Z = -1;
    return none;
}
