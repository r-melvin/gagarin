// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes, globals and slots read off the user's retail gamemd.exe v1.001 via
//   the local Ghidra CLI at 0x5D6540: the team vector embedded at +0x08
//   (vptr +0x08, Items +0x0C, Count +0x18, its slot +0x0C), the mode's own
//   vtable slot +0xC0 taking the vector, the team's vtable slot 0 called
//   with 1 (deleting destructor), the team's Title at +0x04 and Index at
//   +0x08, the game-mode array at 0xA8DA74 (Items 0xA8DA78, Count 0xA8DA84)
//   whose packed entries carry the dword at +0x6B, and SendMessageA through
//   the import slot 0x7E14A4. YRpp names
//   PopulateTeamDropdownForPlayer, CreateMPTeams and the MPTeam members;
//   every offset reconfirmed here.
#ifndef GG_MATCH_NETWORK_MP_GAME_MODE_CLASS_DROPDOWN_METHODS_H
#define GG_MATCH_NETWORK_MP_GAME_MODE_CLASS_DROPDOWN_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

// A team entry. The virtual destructor at slot 0 is what `delete` dispatches
// through with the deleting flag.
struct MPTeam_005D6540
{
    virtual ~MPTeam_005D6540();

    wchar_t* Title;    // +0x04
    int      Index;    // +0x08
};
GG_STATIC_ASSERT(offsetof(MPTeam_005D6540, Title) == 0x04);
GG_STATIC_ASSERT(offsetof(MPTeam_005D6540, Index) == 0x08);

// FUNCTION: GAMEMD 0x7B7140 (decl; reloc) — the title, or a static empty
// wide string when it is null.
extern "C" const wchar_t* __fastcall MPTeam_TitleOrEmpty_005D6540(wchar_t** title);

// FUNCTION: GAMEMD 0x623840 (decl; reloc) — empty the combo box.
extern "C" void __fastcall FUN_00623840(void* hWnd);

// DynamicVectorClass<MPTeam*>; slot +0x0C is Clear().
struct MPTeamVector_005D6540
{
    virtual void vt_000();
    virtual void vt_004();
    virtual void vt_008();
    virtual void Clear();              // +0x000C

    MPTeam_005D6540** Items;           // +0x0004
    char _pad0008[0x08];               // +0x0008
    int  Count;                        // +0x0010
};
GG_STATIC_ASSERT(offsetof(MPTeamVector_005D6540, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(MPTeamVector_005D6540, Count) == 0x10);

// One game-mode record (packed: the dword sits at the odd offset +0x6B).
#pragma pack(push, 1)
struct MPGameModeEntry_005D6540
{
    char _pad00[0x6B];   // +0x0000
    int  At_6B;          // +0x006B
};
#pragma pack(pop)
GG_STATIC_ASSERT(offsetof(MPGameModeEntry_005D6540, At_6B) == 0x6B);

struct MPGameModeArray_005D6540
{
    void* Vptr;                            // +0x0000
    MPGameModeEntry_005D6540** Items;      // +0x0004
    char _pad0008[0x08];                   // +0x0008
    int  Count;                            // +0x0010
};
GG_STATIC_ASSERT(offsetof(MPGameModeArray_005D6540, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(MPGameModeArray_005D6540, Count) == 0x10);

// GLOBAL: GAMEMD 0xA8DA74 — the game-mode array (Items 0xA8DA78, Count 0xA8DA84).
extern MPGameModeArray_005D6540 DAT_00A8DA74;

struct Vtbl_005D6540;

struct MultiplayerGameMode_005D6540
{
    Vtbl_005D6540* Vptr;                   // +0x0000
    int _pad0004;                          // +0x0004
    MPTeamVector_005D6540 Teams;           // +0x0008

    // FUNCTION: GAMEMD 0x5D6540 — MultiplayerGameMode::PopulateTeamDropdownForPlayer.
    void PopulateTeamDropdownForPlayer(void* hWnd, int idx);
};
GG_STATIC_ASSERT(offsetof(MultiplayerGameMode_005D6540, Teams) == 0x08);

typedef void (MultiplayerGameMode_005D6540::*FnC0_005D6540)(MPTeamVector_005D6540* teams);

struct Vtbl_005D6540
{
    char _pad000[0xC0];          // +0x0000
    FnC0_005D6540 CreateMPTeams; // +0x00C0
};
GG_STATIC_ASSERT(offsetof(Vtbl_005D6540, CreateMPTeams) == 0xC0);

#endif  // GG_MATCH_NETWORK_MP_GAME_MODE_CLASS_DROPDOWN_METHODS_H
