// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against the user's retail gamemd.exe v1.001, 0x5C0E30..0x5C0FD3.
//   Each body is the slot named in multiplayer_game_mode.h of the base table
//   0x7EED60 and of every leaf table that inherits it. They sit together in
//   the movie-handle / MultiplayerBattle unit, just before the
//   MultiplayerBattle deleting destructor 0x5C0FE0, which is how a unit that
//   emits the leaf's vtable lays out the base class's inline virtuals.

#include "multiplayer_game_mode.h"

// FUNCTION: GAMEMD 0x5C0E30
bool MultiplayerGameMode::vf_1()
{
    return false;
}

// FUNCTION: GAMEMD 0x5C0E40
bool MultiplayerGameMode::vf_2()
{
    return false;
}

// FUNCTION: GAMEMD 0x5C0E50
bool MultiplayerGameMode::vf_3(int)
{
    return true;
}

// FUNCTION: GAMEMD 0x5C0E60
void MultiplayerGameMode::vf_8()
{
}

// FUNCTION: GAMEMD 0x5C0E70
void MultiplayerGameMode::vf_9()
{
}

// FUNCTION: GAMEMD 0x5C0E80
void MultiplayerGameMode::vf_14(int)
{
}

// FUNCTION: GAMEMD 0x5C0E90
// Only the by-value vector's destructor survives (free Items if allocated).
bool MultiplayerGameMode::vf_22(int, MPGameModeArgVector, int, int)
{
    return false;
}

// FUNCTION: GAMEMD 0x5C0EB0
bool MultiplayerGameMode::vf_21(int, MPGameModeArgVector)
{
    return false;
}

// FUNCTION: GAMEMD 0x5C0ED0
bool MultiplayerGameMode::vf_23(int, int, int)
{
    return true;
}

// FUNCTION: GAMEMD 0x5C0EE0
bool MultiplayerGameMode::vf_26()
{
    return true;
}

// FUNCTION: GAMEMD 0x5C0EF0
void MultiplayerGameMode::vf_29(int, int)
{
}

// FUNCTION: GAMEMD 0x5C0F00
void MultiplayerGameMode::vf_30(int)
{
}

// FUNCTION: GAMEMD 0x5C0F10
void MultiplayerGameMode::vf_36()
{
}

// FUNCTION: GAMEMD 0x5C0F20
void MultiplayerGameMode::vf_37()
{
}

// FUNCTION: GAMEMD 0x5C0F30
int MultiplayerGameMode::vf_38()
{
    return -1;
}

// FUNCTION: GAMEMD 0x5C0F40
void MultiplayerGameMode::vf_39()
{
}

// FUNCTION: GAMEMD 0x5C0F50
void MultiplayerGameMode::vf_40(int)
{
}

// FUNCTION: GAMEMD 0x5C0F60
void MultiplayerGameMode::vf_41(int)
{
}

// FUNCTION: GAMEMD 0x5C0F70
bool MultiplayerGameMode::vf_42()
{
    return false;
}

// FUNCTION: GAMEMD 0x5C0F80
void MultiplayerGameMode::vf_43()
{
}

// FUNCTION: GAMEMD 0x5C0F90
void MultiplayerGameMode::vf_44()
{
}

// FUNCTION: GAMEMD 0x5C0FA0
bool MultiplayerGameMode::vf_45(MPGameModeArgVector, int)
{
    return false;
}

// FUNCTION: GAMEMD 0x5C0FC0
int MultiplayerGameMode::vf_46()
{
    return 0;
}

// FUNCTION: GAMEMD 0x5C0FD0
bool MultiplayerGameMode::vf_47()
{
    return true;
}
