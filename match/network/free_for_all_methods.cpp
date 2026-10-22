// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001, 0x5C5CE0..0x5C5E32.

#include <windows.h>
#include "free_for_all.h"
#include "mp_game_mode_class_methods.h"
#include "mpteams_methods.h"

// FUNCTION: GAMEMD 0x623840 (decl; reloc) -- empty a combo box.
int FUN_00623840(HWND hWnd);

// FUNCTION: GAMEMD 0x5C5CE0
// All six arguments go straight to the base constructor.
FreeForAll::FreeForAll(const Obj_007B66D0& a, const Obj_007B66D0& b, const Obj_007B4620& c, const Obj_007B4620& d, bool e, int f)
    : MultiplayerGameMode(a, b, c, d, e, f)
{
}

// FUNCTION: GAMEMD 0x5C5D20
FreeForAll::~FreeForAll()
{
}

// FUNCTION: GAMEMD 0x5C5D30
bool FreeForAll::vf_4()
{
    return MultiplayerGameMode::vf_4();
}

// FUNCTION: GAMEMD 0x5C5D40
// After the base slot succeeds, number every entry of the game-mode array that
// is not marked -1 with its own index.
//
// PARTIAL (34.6%). Retail hoists the Items load out of the loop, keeps the
// entry in ESI and re-reads Items only after a store (`MOV ECX,ESI` before
// the store suggests an inlined thiscall setter); cl here reloads Items every
// pass as in 0x5C5D90. Tried: through a local entry, through two Items[i]
// reads, and an early `continue` -- all 34.6%.
bool FreeForAll::vf_5(Obj_007B66D0& a)
{
    if (!MultiplayerGameMode::vf_5(a)) {
        return false;
    }
    for (int i = 0; i < MPGameModeArray.Count; i++) {
        MPGameModeEntry* entry = ((MPGameModeEntry**)MPGameModeArray.Items)[i];
        if (entry->unknown_6B != -1) {
            entry->unknown_6B = i;
        }
    }
    return true;
}

// FUNCTION: GAMEMD 0x5C5D90
bool FreeForAll::vf_6()
{
    if (!MultiplayerGameMode::vf_6()) {
        return false;
    }
    for (int i = 0; i < MPGameModeArray.Count; i++) {
        MPGameModeEntry* entry = ((MPGameModeEntry**)MPGameModeArray.Items)[i];
        if (entry->unknown_6B != -1) {
            entry->unknown_6B = i;
        }
    }
    return true;
}

// FUNCTION: GAMEMD 0x5C5DD0
// Empty the combo, add the team for this player and the -1 team, then select
// the first item (CB_SETCURSEL 0).
void FreeForAll::PopulateTeamDropdownForPlayer(void* hWnd, int idx)
{
    FUN_00623840((HWND)hWnd);
    MPTeam* team = FUN_005D6620(idx);
    if (team != 0) {
        team->AddToList(hWnd);
    }
    team = FUN_005D6620(-1);
    if (team != 0) {
        team->AddToList(hWnd);
    }
    SendMessageA((HWND)hWnd, CB_SETCURSEL, 0, 0);
}

// FUNCTION: GAMEMD 0x5C5E30
bool FreeForAll::vf_16()
{
    return true;
}
