// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes, globals and offsets read off the user's retail gamemd.exe v1.001
//   via the local Ghidra CLI at 0x430AC0: the 24 beacon pointers walked from
//   +0x00 as 8 rows of 3 (two down-counters kept on the frame), the count at
//   +0x60, the beacon's flag byte at +0x0C (bit 0) and house index at +0x110,
//   the current player at 0xA83D4C, HouseClass::Array.Items at 0xA8022C and
//   the house byte at +0x1F5. The two house probes 0x4F9A10 (int) and
//   0x4F9A50 (HouseClass*) are __thiscall with one pushed argument; the
//   beacon's own Draw at 0x430250 takes the surface and the bounds rectangle
//   by value. YRpp names Draw, Beacons,
//   AllocatedCount and CurrentPlayer; every offset reconfirmed here.
#ifndef GG_MATCH_NETWORK_BEACON_MANAGER_CLASS_DRAW_METHODS_H
#define GG_MATCH_NETWORK_BEACON_MANAGER_CLASS_DRAW_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Surface_00430AC0;

struct Rect_00430AC0
{
    int X;        // +0x00
    int Y;        // +0x04
    int Width;    // +0x08
    int Height;   // +0x0C
};
GG_STATIC_ASSERT(sizeof(Rect_00430AC0) == 0x10);

struct House_00430AC0
{
    char _pad0000[0x1F5];    // +0x0000
    char At_1F5;             // +0x01F5

    // FUNCTION: GAMEMD 0x4F9A10 (decl; reloc) — allied with the house at an index.
    bool FUN_004F9A10(int houseIndex);
    // FUNCTION: GAMEMD 0x4F9A50 (decl; reloc) — allied with a house.
    bool FUN_004F9A50(House_00430AC0* house);
};
GG_STATIC_ASSERT(offsetof(House_00430AC0, At_1F5) == 0x1F5);

// GLOBAL: GAMEMD 0xA83D4C — HouseClass::CurrentPlayer.
extern House_00430AC0* DAT_00A83D4C;
// GLOBAL: GAMEMD 0xA8022C — HouseClass::Array.Items.
extern House_00430AC0** DAT_00A8022C;

struct Beacon_00430AC0
{
    char _pad0000[0x0C];         // +0x0000
    char Flags;                  // +0x000C  bit 0 = placed
    char _pad000D[0x110 - 0x0D]; // +0x000D
    int  HouseIndex;             // +0x0110

    // FUNCTION: GAMEMD 0x430250 (decl; reloc) — BeaconClass::Draw.
    void Draw(Surface_00430AC0* surface, Rect_00430AC0 bounds);
};
GG_STATIC_ASSERT(offsetof(Beacon_00430AC0, Flags) == 0x0C);
GG_STATIC_ASSERT(offsetof(Beacon_00430AC0, HouseIndex) == 0x110);

struct BeaconManager_00430AC0
{
    Beacon_00430AC0* Beacons[8][3];   // +0x0000
    int AllocatedCount;               // +0x0060

    // FUNCTION: GAMEMD 0x430AC0 — BeaconManagerClass::Draw.
    void Draw(Surface_00430AC0* surface, Rect_00430AC0 bounds);
};
GG_STATIC_ASSERT(offsetof(BeaconManager_00430AC0, AllocatedCount) == 0x60);

#endif  // GG_MATCH_NETWORK_BEACON_MANAGER_CLASS_DRAW_METHODS_H
