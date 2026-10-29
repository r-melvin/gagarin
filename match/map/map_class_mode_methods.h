// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes and offsets read off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x4AC660 / 0x4AC820 / 0x4AC8C0. The three are one
//   template — identical instruction sequence, differing only in which of the
//   flag bytes is the *selected* one; the other four are cleared in ascending
//   offset order in every instance. That was established by diffing the three
//   constant sets, not assumed from the names.
//
//     SetRepairMode       0x4AC8C0  selects +0x11B0
//     SetSellMode         0x4AC660  selects +0x11B1
//     SetTogglePowerMode  0x4AC820  selects +0x11B2
#ifndef GG_MATCH_MAP_MAP_CLASS_MODE_METHODS_H
#define GG_MATCH_MAP_MAP_CLASS_MODE_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// The house driving this machine; the mode is refused when its counter at
// +0x2F0 is not positive.
#include "../_layout/house_class.h"
GG_STATIC_ASSERT(offsetof(HouseClass, OwnedBuildings) == 0x2F0);

// GLOBAL: GAMEMD 0x00A83D4C — HouseClass::CurrentPlayer.
extern HouseClass* CurrentPlayer;

// GAMEMD 0x0048DC90 — the no-argument notify run after a mode is entered.
void ModeEntered();

class MapClass
{
public:
#include "map_class_mode_slots.inc"

    char _padVtbl[0x11A8 - 4];   // +0x0004  (vptr occupies +0x0000)
    int  unknown_11A8;           // +0x11A8  a mode change is refused when set
    char _pad11AC[0x11B0 - 0x11AC];
    bool RepairMode;             // +0x11B0
    bool SellMode;               // +0x11B1
    bool TogglePowerMode;        // +0x11B2
    bool unknown_11B3;           // +0x11B3
    bool unknown_11B4;           // +0x11B4

    void SetSellMode(int mode);         // GAMEMD 0x4AC660
    void SetTogglePowerMode(int mode);  // GAMEMD 0x4AC820
    void SetRepairMode(int mode);       // GAMEMD 0x4AC8C0
};
GG_STATIC_ASSERT(offsetof(MapClass, unknown_11A8)    == 0x11A8);
GG_STATIC_ASSERT(offsetof(MapClass, RepairMode)      == 0x11B0);
GG_STATIC_ASSERT(offsetof(MapClass, SellMode)        == 0x11B1);
GG_STATIC_ASSERT(offsetof(MapClass, TogglePowerMode) == 0x11B2);
GG_STATIC_ASSERT(offsetof(MapClass, unknown_11B4)    == 0x11B4);

#endif  // GG_MATCH_MAP_MAP_CLASS_MODE_METHODS_H
