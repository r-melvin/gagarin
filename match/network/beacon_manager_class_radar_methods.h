// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes, globals and offsets read off the user's retail gamemd.exe v1.001
//   via the local Ghidra CLI at 0x431700: the count at +0x60 (`MOV EAX,
//   [ECX+0x60]`), the animation period at +0x7C (`IDIV [ECX+0x7C]`) with the
//   frame counter at 0xA8ED84 as dividend and the frame count read by
//   absolute address 0x89C428 (= Instance 0x89C3B0 + 0x78); the 24 beacon
//   pointers walked from +0x00 as 8 rows of 3 (two down-counters on the
//   frame), the beacon's flag byte at +0x0C (bit 0) and house index at
//   +0x110, the current player at 0xA83D4C, HouseClass::Array.Items at
//   0xA8022C and the house byte at +0x1F5. The two house probes 0x4F9A10 and
//   0x4F9A50 are __thiscall with one pushed argument; the beacon's own
//   DrawRadar at 0x430650 takes the surface, the bounds rectangle by value
//   and a pushed 0. YRpp (consult-only, no LICENSE) names DrawRadar, Beacons,
//   AllocatedCount, RadarBeaconFrameCount, RadarBeaconAnimPeriod,
//   CurrentFrame and CurrentPlayer; every offset reconfirmed here.
#ifndef GG_MATCH_NETWORK_BEACON_MANAGER_CLASS_RADAR_METHODS_H
#define GG_MATCH_NETWORK_BEACON_MANAGER_CLASS_RADAR_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Surface_00431700;

struct Rect_00431700
{
    int X;        // +0x00
    int Y;        // +0x04
    int Width;    // +0x08
    int Height;   // +0x0C
};
GG_STATIC_ASSERT(sizeof(Rect_00431700) == 0x10);

struct House_00431700
{
    char _pad0000[0x1F5];    // +0x0000
    char At_1F5;             // +0x01F5

    // FUNCTION: GAMEMD 0x4F9A10 (decl; reloc) — allied with the house at an index.
    bool FUN_004F9A10(int houseIndex);
    // FUNCTION: GAMEMD 0x4F9A50 (decl; reloc) — allied with a house.
    bool FUN_004F9A50(House_00431700* house);
};
GG_STATIC_ASSERT(offsetof(House_00431700, At_1F5) == 0x1F5);

// GLOBAL: GAMEMD 0xA83D4C — HouseClass::CurrentPlayer.
extern House_00431700* DAT_00A83D4C;
// GLOBAL: GAMEMD 0xA8022C — HouseClass::Array.Items.
extern House_00431700** DAT_00A8022C;
// GLOBAL: GAMEMD 0xA8ED84 — Unsorted::CurrentFrame.
#include "../core/frame_counter.h"

struct Beacon_00431700
{
    char _pad0000[0x0C];         // +0x0000
    char Flags;                  // +0x000C  bit 0 = placed
    char _pad000D[0x110 - 0x0D]; // +0x000D
    int  HouseIndex;             // +0x0110

    // FUNCTION: GAMEMD 0x430650 (decl; reloc) — BeaconClass::DrawRadar.
    void DrawRadar(Surface_00431700* surface, Rect_00431700 bounds, int toClear);
};
GG_STATIC_ASSERT(offsetof(Beacon_00431700, Flags) == 0x0C);
GG_STATIC_ASSERT(offsetof(Beacon_00431700, HouseIndex) == 0x110);

struct BeaconManager_00431700
{
    Beacon_00431700* Beacons[8][3];   // +0x0000
    int AllocatedCount;               // +0x0060
    int BeaconSizeX;                  // +0x0064
    int BeaconSizeY;                  // +0x0068
    int BeaconFrameCount;             // +0x006C
    int RadarBeaconSizeX;             // +0x0070
    int RadarBeaconSizeY;             // +0x0074
    int RadarBeaconFrameCount;        // +0x0078
    int RadarBeaconAnimPeriod;        // +0x007C

    // FUNCTION: GAMEMD 0x431700 — BeaconManagerClass::DrawRadar.
    void DrawRadar(Surface_00431700* surface, Rect_00431700 bounds);
};
GG_STATIC_ASSERT(offsetof(BeaconManager_00431700, AllocatedCount) == 0x60);
GG_STATIC_ASSERT(offsetof(BeaconManager_00431700, RadarBeaconFrameCount) == 0x78);
GG_STATIC_ASSERT(offsetof(BeaconManager_00431700, RadarBeaconAnimPeriod) == 0x7C);

// GLOBAL: GAMEMD 0x89C3B0 — BeaconManagerClass::Instance (retail reads its
// RadarBeaconFrameCount by absolute address 0x89C428).
extern BeaconManager_00431700 BeaconManagerInstance;

#endif  // GG_MATCH_NETWORK_BEACON_MANAGER_CLASS_RADAR_METHODS_H
