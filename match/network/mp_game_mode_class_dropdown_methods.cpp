// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes diffed against retail gamemd.exe v1.001 at 0x5D6540.

#include <windows.h>
#include "mp_game_mode_class_dropdown_methods.h"

// FUNCTION: GAMEMD 0x5D6540  MultiplayerGameMode::PopulateTeamDropdownForPlayer
//
// Rebuild the team combo: empty it, delete and clear the old team list, ask
// the mode for a fresh one, then add every team's title (CB_ADDSTRING),
// preselect the one whose index is the chosen game mode's team value
// (CB_SETCURSEL) and tag each item with its team (CB_SETITEMDATA).
void MultiplayerGameMode_005D6540::PopulateTeamDropdownForPlayer(void* hWnd, int idx)
{
    FUN_00623840(hWnd);

    for (int i = 0; i < Teams.Count; ++i) {
        MPTeam_005D6540* team = Teams.Items[i];
        if (team != 0)
            delete team;
    }
    Teams.Clear();
    (this->*this->Vptr->CreateMPTeams)(&Teams);

    if (idx >= 0 && idx < DAT_00A8DA74.Count) {
        int mode = DAT_00A8DA74.Items[idx]->At_6B;
        for (int i = 0; i < Teams.Count; ++i) {
            MPTeam_005D6540* team = Teams.Items[i];
            WPARAM item = SendMessageA((HWND)hWnd, 0x143, 0,
                                       (LPARAM)MPTeam_TitleOrEmpty_005D6540(&team->Title));
            if (team->Index == mode)
                SendMessageA((HWND)hWnd, 0x14E, item, 0);
            SendMessageA((HWND)hWnd, 0x151, item, (LPARAM)team);
        }
    }
}
