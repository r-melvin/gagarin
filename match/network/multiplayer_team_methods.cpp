// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: retail gamemd.exe v1.001 disassembly at 0x5D8CB0 (MultiplayerTeam slot 2, vtable
//   0x7EEEDC), 0x5C1090 and 0x5C10B0 (MultiplayerBattleTeam slots 1 and 2, vtable 0x7EE258) and
//   0x5C94C0 (MultiplayerObserverTeam slot 1, vtable 0x7EE6C8).
//
// Address index: 0x5C1090 0x5C10B0 0x5C9470 0x5C94C0

#include "mp_battle_class.h"

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

// GLOBAL: GAMEMD 0x82FD40 -- "D:\\ra2mdpost\\MPObserver.cpp", the build path handed to the label lookup.
extern const char DAT_0082FD40[];

// FUNCTION: GAMEMD 0x734E60 (decl; reloc) -- resolve a label to its localised
// text; __fastcall with the file and line on the stack, RET 8.
const wchar_t* FUN_00734E60(const char* label, int flags, const char* file, int line);

// FUNCTION: GAMEMD 0x5C9470
MultiplayerObserverTeam::MultiplayerObserverTeam()
    : MultiplayerTeam(FUN_00734E60("MP:ObserverTeam", 0, DAT_0082FD40, 5), -1)
{
}

// FUNCTION: GAMEMD 0x5C94C0
// Slot 1: forwards to the base check.
bool MultiplayerObserverTeam::vf_1(int playerIndex)
{
    return MultiplayerTeam::vf_1(playerIndex);
}

// SYNTHETIC: GAMEMD 0x5C94D0 -- MultiplayerObserverTeam scalar deleting destructor, emitted by the compiler from the
// virtual destructor where this TU seats the vtable.

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x82FD40
extern const char DAT_0082FD40[] = "D:\\ra2mdpost\\MPObserver.cpp";
// END defined globals
