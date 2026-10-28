// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: retail gamemd.exe v1.001 disassembly at 0x5D63E0, 0x5D6620 and 0x5D6750
//   (MultiplayerGameMode, original unit Multiplayer.cpp).
//
// Address index: 0x5D63E0 0x5D6620 0x5D6750

#include "multiplayer_game_mode.h"
#include "../core/vector_class_operations.h"
#include "session_entry.h"
#include "mpteams_methods.h"
#include "../platform/ccini_class_methods.h"

// FUNCTION: GAMEMD 0x77D940 (decl; reloc)
bool FUN_0077D940();

// FUNCTION: GAMEMD 0x5D63E0
// Whether a session map entry is playable in this mode: entries that accept
// every mode defer to slot 15, otherwise the entry's own mode list decides.
bool MultiplayerGameMode::FUN_005D63E0(MultiMission* entry)
{
    if (entry->FUN_0069ADF0()) {
        return vf_15();
    }
    if (!entry->unknown_17C && FUN_0077D940()) {
        return false;
    }
    return entry->FUN_0069AE10(&unknown_30);
}

// FUNCTION: GAMEMD 0x5D6620
// The team whose index is `index`, building the default team list first when
// fewer than three exist.
MPTeam* MultiplayerGameMode::FUN_005D6620(int index)
{
    if (Teams.Count < 3) {
        for (int i = 0; i < Teams.Count; ++i) {
            MultiplayerTeam* team = Teams.Items[i];
            if (team != 0)
                delete team;
        }
        Teams.Clear();
        CreateMPTeams(Teams);
    }
    for (int i = 0; i < Teams.Count; ++i) {
        MultiplayerTeam* team = Teams.Items[i];
        if (team != 0 && team->unknown_08 == index)
            return (MPTeam*)team;
    }
    return 0;
}

// FUNCTION: GAMEMD 0x5D6750
// Delete every team and empty the team list.
void MultiplayerGameMode::FUN_005D6750()
{
    for (int i = 0; i < Teams.Count; ++i) {
        MultiplayerTeam* team = Teams.Items[i];
        if (team != 0)
            delete team;
    }
    Teams.Clear();
}

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
