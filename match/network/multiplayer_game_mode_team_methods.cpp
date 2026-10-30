// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: retail gamemd.exe v1.001 disassembly at 0x5D5D20
//   (MultiplayerGameMode, original unit Multiplayer.cpp). This out-of-line destructor copy
//   cannot share a file with the inline destructor of Multiplayer.cpp (same-TU redefinition).
//
// Address index: 0x5D5D20

#include "multiplayer_game_mode.h"
#include "../core/vector_class_operations.h"
#include "session_entry.h"
#include "mpteams_methods.h"
#include "../platform/ccini_class_methods.h"

// FUNCTION: GAMEMD 0x5D5D20
// Delete every team and empty the list, then the owned INI.
// PARTIAL (96.4%): identical instruction multiset; retail stores the vtable
// pointer before loading Teams.Count, cl loads the count first. Tried: local
// loop index, direct Items[] tests, an explicit null test on the INI.
MultiplayerGameMode::~MultiplayerGameMode()
{
    for (int i = 0; i < Teams.Count; ++i) {
        MultiplayerTeam* team = Teams.Items[i];
        if (team != 0)
            delete team;
    }
    Teams.Clear();
    delete unknown_38;
}
