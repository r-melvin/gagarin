// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   FreeForAll, one MultiplayerGameMode leaf. Name from RTTI (the locator
//   under its vtable 0x7EE424). Read with `ghidra memory read 0x7EE424 208`
//   against the base table 0x7EED60: it overrides slots 0 (deleting dtor
//   0x5C5E40), 4 (0x5C5D30), 5 (0x5C5D40), 6 (0x5C5D90), 16 (0x5C5E30) and
//   20 (0x5C5DD0) and inherits the rest.
#ifndef GG_MATCH_NETWORK_FREE_FOR_ALL_H
#define GG_MATCH_NETWORK_FREE_FOR_ALL_H

#include "multiplayer_game_mode.h"

// VTABLE: GAMEMD 0x7EE424
class FreeForAll : public MultiplayerGameMode
{
public:
    FreeForAll(const Obj_007B66D0& a, const Obj_007B66D0& b, const Obj_007B4620& c, const Obj_007B4620& d, bool e, int f);
    virtual ~FreeForAll();
    virtual bool vf_4();
    virtual bool vf_5(Obj_007B66D0& a);
    virtual bool vf_6();
    virtual bool vf_16();
    virtual void PopulateTeamDropdownForPlayer(void* hWnd, int idx);
};
GG_STATIC_ASSERT(sizeof(FreeForAll) == sizeof(MultiplayerGameMode));

#endif  // GG_MATCH_NETWORK_FREE_FOR_ALL_H
