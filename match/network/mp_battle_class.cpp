// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against the user's retail gamemd.exe v1.001 (Ghidra CLI
//   disassembly from each entry) at 0x5C0DD0..0x5C1087.
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /Ob2 /MT
//
// /Ob2 measured on this TU (all five rows scored under default, /Ob1, /Ob2 and
// /Op): only /Ob2 moves anything, and it moves FUN_005C1030 from 67.6% (index
// and allocation in swapped registers, same instructions) to retail's exact
// register assignment; the other four rows are byte-identical either way.
#include "mp_battle_class.h"

// FUNCTION: GAMEMD 0x7B7DD0 (decl; reloc)
Obj_007B66D0 FUN_007B7DD0(int index);

// FUNCTION: GAMEMD 0x5C0DD0
MultiplayerBattle::MultiplayerBattle(const Obj_007B66D0& a, const Obj_007B66D0& b, const Wstring& c, const Wstring& d, bool e, int f)
    : MultiplayerGameMode(a, b, c, d, e, f)
{
}

// FUNCTION: GAMEMD 0x5C0E10
MultiplayerBattle::~MultiplayerBattle()
{
}

// SYNTHETIC: GAMEMD 0x5C0FE0 -- MultiplayerBattle scalar deleting destructor, emitted by the compiler from the virtual destructor above

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
// Exact only under the TU's /Ob2: the default flags give the same instructions
// with the index and the new block in swapped registers (EDI/ESI).
MultiplayerTeam* FUN_005C1030(int index)
{
    return new MultiplayerBattleTeam(FUN_007B7DD0(index), index);
}

// SYNTHETIC: GAMEMD 0x5C10D0 -- MultiplayerBattleTeam scalar deleting destructor, emitted by the compiler from the virtual destructor
