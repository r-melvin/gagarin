// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   MultiplayerManBattle (vtable 0x7EE50C) and Megawealth (vtable 0x7EE5F4),
//   two MultiplayerGameMode leaves; names from the RTTI locators under the
//   tables. Compared slot by slot with the base table 0x7EED60 (`ghidra memory
//   read`): MultiplayerManBattle overrides only slot 0 (deleting dtor
//   0x5C61A0); Megawealth overrides slot 0 (0x5C9440) and slot 35 (0x5C9430).
#ifndef GG_MATCH_NETWORK_MP_GAME_MODE_LEAF_CLASSES_H
#define GG_MATCH_NETWORK_MP_GAME_MODE_LEAF_CLASSES_H

#include "multiplayer_game_mode.h"

// VTABLE: GAMEMD 0x7EE50C
class MultiplayerManBattle : public MultiplayerGameMode
{
public:
    MultiplayerManBattle(const Obj_007B66D0& a, const Obj_007B66D0& b, const Wstring& c, const Wstring& d, bool e, int f);
    virtual ~MultiplayerManBattle();
};
GG_STATIC_ASSERT(sizeof(MultiplayerManBattle) == sizeof(MultiplayerGameMode));

// VTABLE: GAMEMD 0x7EE5F4
class Megawealth : public MultiplayerGameMode
{
public:
    Megawealth(const Obj_007B66D0& a, const Obj_007B66D0& b, const Wstring& c, const Wstring& d, bool e, int f);
    virtual ~Megawealth();
    virtual bool vf_35();
};
GG_STATIC_ASSERT(sizeof(Megawealth) == sizeof(MultiplayerGameMode));

// VTABLE: GAMEMD 0x7EE814
class UnholyAlliance : public MultiplayerGameMode
{
public:
    UnholyAlliance(const Obj_007B66D0& a, const Obj_007B66D0& b, const Wstring& c, const Wstring& d, bool e, int f);
    virtual ~UnholyAlliance();
};
GG_STATIC_ASSERT(sizeof(UnholyAlliance) == sizeof(MultiplayerGameMode));

#endif  // GG_MATCH_NETWORK_MP_GAME_MODE_LEAF_CLASSES_H
