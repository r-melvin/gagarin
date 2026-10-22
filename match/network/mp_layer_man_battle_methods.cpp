// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001. These sit in the retail
//   block of MPLayer.CPP (its __FILE__ string 0x82E134).

#include "mp_game_mode_leaf_classes.h"

// FUNCTION: GAMEMD 0x5C6150
MultiplayerManBattle::MultiplayerManBattle(const Obj_007B66D0& a, const Obj_007B66D0& b, const Obj_007B4620& c, const Obj_007B4620& d, bool e, int f)
    : MultiplayerGameMode(a, b, c, d, e, f)
{
}

// FUNCTION: GAMEMD 0x5C6190
MultiplayerManBattle::~MultiplayerManBattle()
{
}
