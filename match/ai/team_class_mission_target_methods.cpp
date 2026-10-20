// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes diffed against retail gamemd.exe v1.001 at 0x6E9050.

#include "team_class_mission_target_methods.h"

// FUNCTION: GAMEMD 0x6E9050  TeamClass::AssignMissionTarget
//
// Switch the team's target. Members still aimed at or heading for the old
// one are told to guard (mission 5) and have that target or destination
// cleared; the secondary at +0x40 follows when it tracked the old target or
// was empty. A cell target off the usable map flags the team and sends every
// member home; an on-map cell clears the flag. The member cursor is loaded
// before the old-target null test, as retail schedules it.
void Team_006E9050::AssignMissionTarget(Abstract_006E9050* target)
{
    if (target != Target) {
        Foot_006E9050* member = FirstUnit;
        if (Target != 0)
        for (; member != 0; member = member->NextTeamMember) {
            Abstract_006E9050* old = Target;
            bool aimed = member->Target == old;
            bool heading = member->Destination == old;
            if (aimed || heading) {
                (member->*member->Vptr->QueueMission)(5, false);
                if (heading)
                    (member->*member->Vptr->SetDestination)(0, true);
                if (aimed)
                    (member->*member->Vptr->SetTarget)(0);
            }
        }
    }

    if (At_40 == Target || At_40 == 0)
        At_40 = target;
    Target = target;

    if (target != 0 && (target->*target->Vptr->WhatAmI)() == 0xB) {
        if (!MapInstance_006E9050.IsWithinUsableArea(target, true)) {
            Foot_006E9050* member = FirstUnit;
            At_82 = 1;
            for (; member != 0; member = member->NextTeamMember)
                (member->*member->Vptr->SetDestination)(0, true);
        } else {
            At_82 = 0;
        }
    }
}
