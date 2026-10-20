// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes diffed against retail gamemd.exe v1.001 at 0x5D6690.

#include "mp_game_mode_class_teams_methods.h"

// FUNCTION: GAMEMD 0x5D6690  MultiplayerGameMode::CreateMPTeams
//
// Fill the team list: one fresh default team, then the preset teams 1..N
// looked up by index. Both adds are the inlined vector AddItem.
void MultiplayerGameMode_005D6690::CreateMPTeams(MPTeamVector_005D6690* teams)
{
    MPTeam_005D6690* team = (MPTeam_005D6690*)operator new(sizeof(MPTeam_005D6690));
    teams->AddItem(team != 0 ? team->Construct() : 0);

    for (int i = 1; i <= DAT_00A8B548; ++i)
        teams->AddItem(FUN_005C1030(i));
}
