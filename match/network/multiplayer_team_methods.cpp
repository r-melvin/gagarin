// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: retail gamemd.exe v1.001 disassembly at 0x5D8CB0 (MultiplayerTeam slot 2, vtable
//   0x7EEEDC), 0x5C1090 and 0x5C10B0 (MultiplayerBattleTeam slots 1 and 2, vtable 0x7EE258) and
//   0x5C94C0 (MultiplayerObserverTeam slot 1, vtable 0x7EE6C8).
//
// Address index: 0x5C1090 0x5C10B0 0x5C94C0 0x5D8CB0

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

// FUNCTION: GAMEMD 0x5C1090
// Slot 1: forwards to the base check.
bool MultiplayerBattleTeam::vf_1(int playerIndex)
{
    return MultiplayerTeam::vf_1(playerIndex) ? true : false;
}

// FUNCTION: GAMEMD 0x5C10B0
// Slot 2: forwards to the base assignment.
bool MultiplayerBattleTeam::vf_2(int playerIndex)
{
    return MultiplayerTeam::vf_2(playerIndex) ? true : false;
}

// FUNCTION: GAMEMD 0x5C94C0
// Slot 1: forwards to the base check.
bool MultiplayerObserverTeam::vf_1(int playerIndex)
{
    return MultiplayerTeam::vf_1(playerIndex);
}

// FUNCTION: GAMEMD 0x5D8CB0
// Puts a valid player into this team by storing the team number in the player object.
bool MultiplayerTeam::vf_2(int playerIndex)
{
    if (!vf_1(playerIndex))
        return false;
    DAT_00A8DA78[playerIndex]->unknown_6B = unknown_08;
    return true;
}
