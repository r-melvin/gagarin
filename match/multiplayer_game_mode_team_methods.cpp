// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: retail gamemd.exe v1.001 disassembly at 0x5D5D20
//   (MultiplayerGameMode, original unit Multiplayer.cpp). This out-of-line destructor copy
//   cannot share a file with the inline destructor of Multiplayer.cpp (same-TU redefinition).
//
// Address index: 0x5D5D20

#include "FUNCTION.H"
#include "multiplayer_game_mode.h"
#include "session_entry.h"
#include "mpteams_methods.h"
#include "ccini_class_methods.h"

// FUNCTION: GAMEMD 0x5D5D20
// Delete every team and empty the list, then the owned INI.
// The count is read through the vector's inline GetCount(): the call's receiver is the
// vector, so cl keeps the vtable-pointer store ahead of the first count load as retail does.
MultiplayerGameMode::~MultiplayerGameMode()
{
    for (int i = 0; i < Teams.GetCount(); ++i) {
        MultiplayerTeam* team = Teams.Items[i];
        if (team != 0)
            delete team;
    }
    Teams.Clear();
    delete unknown_38;
}
