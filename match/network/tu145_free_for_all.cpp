// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Original translation unit TU145 of retail gamemd.exe v1.001; its source-file name is
//   not attested by the binary, so the file keeps a placeholder name. Code range 0x5c5af0-0x5c5e8f,
//   segmented from retail evidence (link-ordered static-initialiser table, RTTI class
//   ownership, neighbouring object bounds). Functions are in ascending retail address order.
//   Obj_/Gbl_ views below are per-function placeholder receivers. Replacing
//   them with the canonical class re-mangles their symbols, so that is left to
//   a separate rename-only change.
//
// The header initialiser group at 0x5C5B20, 0x5C5B40 and 0x5C5CC0
// (header_init_shapes.h): two derived doubles and a {128, 128, 0} coordinate,
// in __xc order. The divisor at 0x7EE410 reads 60.0 (ghidra memory read).

#include "../FUNCTION.H"
#include "free_for_all.h"
#include "mp_game_mode_class_methods.h"
#include "mpteams_methods.h"

// FUNCTION: GAMEMD 0x623840 (decl; reloc) -- empty a combo box.
int FUN_00623840(HWND hWnd);

#include "../core/header_init_shapes.h"

// GLOBAL: GAMEMD 0xABF4C0
extern double DAT_00ABF4C0;
// GLOBAL: GAMEMD 0x7EE410
const double DAT_007EE410 = 60.0;

// GLOBAL: GAMEMD 0xABF510
extern double DAT_00ABF510;

// GLOBAL: GAMEMD 0xABF4F8
extern double DAT_00ABF4F8;

// GLOBAL: GAMEMD 0xABF500
extern HeaderCoordInit DAT_00ABF500;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5C5CE0
// All six arguments go straight to the base constructor.
FreeForAll::FreeForAll(const Obj_007B66D0& a, const Obj_007B66D0& b, const Wstring& c, const Wstring& d, bool e, int f)
    : MultiplayerGameMode(a, b, c, d, e, f)
{
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5C5D20
FreeForAll::~FreeForAll()
{
}

// SYNTHETIC: GAMEMD 0x5C5E40 -- FreeForAll scalar deleting destructor, emitted by the compiler from the virtual destructor above

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5C5D30
bool FreeForAll::vf_4()
{
    return MultiplayerGameMode::vf_4();
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
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

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
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

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
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

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5C5E30
bool FreeForAll::vf_16()
{
    return true;
}
