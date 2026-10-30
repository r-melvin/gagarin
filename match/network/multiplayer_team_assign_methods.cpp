// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: retail gamemd.exe v1.001 disassembly at 0x5D8CB0 (MultiplayerTeam slot 2, vtable
//   0x7EEEDC). Kept apart from multiplayer_team_methods.cpp so the battle team's slot 2 there
//   calls it as retail does instead of expanding it.

#include "mp_battle_class.h"

// The slot player object: only the team number at +0x6B (unaligned) is written.
#pragma pack(push, 1)
struct MultiplayerSlotView_005D8CB0
{
    char unknown_00[0x6B];
    int  unknown_6B;   // +0x6B  team number
};
#pragma pack(pop)
GG_STATIC_ASSERT(offsetof(MultiplayerSlotView_005D8CB0, unknown_6B) == 0x6B);

// GLOBAL: GAMEMD 0xA8DA78 -- the table of slot player objects.
extern MultiplayerSlotView_005D8CB0** DAT_00A8DA78;

// FUNCTION: GAMEMD 0x5D8CB0
// Puts a valid player into this team by storing the team number in the player object.
bool MultiplayerTeam::vf_2(int playerIndex)
{
    if (!vf_1(playerIndex))
        return false;
    DAT_00A8DA78[playerIndex]->unknown_6B = unknown_08;
    return true;
}
