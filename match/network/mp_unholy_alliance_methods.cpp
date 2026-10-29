// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: retail gamemd.exe v1.001 disassembly at 0x5CB3A0: forwards the six arguments to
//   the MultiplayerGameMode constructor (0x5D5B60) and seats the UnholyAlliance vtable 0x7EE814
//   (RTTI .?AVUnholyAlliance@@).
//
// Address index: 0x5CB3A0
#include "mp_game_mode_leaf_classes.h"

// FUNCTION: GAMEMD 0x5CB3A0
UnholyAlliance::UnholyAlliance(const Obj_007B66D0& a, const Obj_007B66D0& b, const Wstring& c, const Wstring& d, bool e,
                               int f)
    : MultiplayerGameMode(a, b, c, d, e, f)
{
}
