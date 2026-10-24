// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Class names from the retail RTTI, read off the user's gamemd.exe v1.001
//   through each vtable's complete-object locator:
//     0x7EE184 -> MultiplayerBattle (a MultiplayerGameMode leaf)
//     0x7EE258 -> `.?AVMultiplayerBattleTeam@@`
#ifndef GG_MATCH_NETWORK_MP_BATTLE_CLASS_H
#define GG_MATCH_NETWORK_MP_BATTLE_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "multiplayer_game_mode.h"

// VTABLE: GAMEMD 0x7EE184
class MultiplayerBattle : public MultiplayerGameMode
{
public:
    MultiplayerBattle(const Obj_007B66D0& a, const Obj_007B66D0& b, const Wstring& c, const Wstring& d, bool e, int f);
    virtual ~MultiplayerBattle();
    virtual bool vf_16();
};

// VTABLE: GAMEMD 0x7EE258
class MultiplayerBattleTeam : public MultiplayerTeam
{
public:
    MultiplayerBattleTeam(const Obj_007B66D0& name, int index);
};

#endif  // GG_MATCH_NETWORK_MP_BATTLE_CLASS_H
