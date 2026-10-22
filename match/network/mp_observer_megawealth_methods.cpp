// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001. These sit in the retail
//   block of MPObserver.cpp (its __FILE__ string 0x82FD40).

#include "mp_game_mode_leaf_classes.h"
#include "../ui/input_controls/ui_display_chain.h"

// FUNCTION: GAMEMD 0x5C93E0
Megawealth::Megawealth(const Obj_007B66D0& a, const Obj_007B66D0& b, const Obj_007B4620& c, const Obj_007B4620& d, bool e, int f)
    : MultiplayerGameMode(a, b, c, d, e, f)
{
}

// FUNCTION: GAMEMD 0x5C9420
Megawealth::~Megawealth()
{
}

// FUNCTION: GAMEMD 0x5C9430
// Slot 35: call the map's 0x577F30 with no house, and succeed.
bool Megawealth::vf_35()
{
    Map_0087F7E8.FUN_00577F30(0);
    return true;
}
