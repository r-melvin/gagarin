// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against the user's retail gamemd.exe v1.001 (Ghidra CLI
//   disassembly from each entry) at 0x5C0DD0..0x5C1087.
#include "mp_battle_class.h"

// FUNCTION: GAMEMD 0x7B7DD0 (decl; reloc)
Obj_007B66D0 __fastcall FUN_007B7DD0(int index);

// FUNCTION: GAMEMD 0x5C0DD0
MultiplayerBattle::MultiplayerBattle(const Obj_007B66D0& a, const Obj_007B66D0& b, const Obj_007B4620& c, const Obj_007B4620& d, bool e, int f)
    : MultiplayerGameMode(a, b, c, d, e, f)
{
}

// FUNCTION: GAMEMD 0x5C0E10
MultiplayerBattle::~MultiplayerBattle()
{
}

// FUNCTION: GAMEMD 0x5C0E20
bool MultiplayerBattle::vf_16()
{
    return true;
}

// FUNCTION: GAMEMD 0x5C1010
MultiplayerBattleTeam::MultiplayerBattleTeam(const Obj_007B66D0& name, int index)
    : MultiplayerTeam(name, index)
{
}

// FUNCTION: GAMEMD 0x5C1030
// PARTIAL (67.6%): instruction multiset identical; retail keeps the index in
// EDI and the block in ESI, cl swaps them. Tried: direct return, a named
// local, an unsigned index.
MultiplayerTeam* __fastcall FUN_005C1030(int index)
{
    return new MultiplayerBattleTeam(FUN_007B7DD0(index), index);
}
