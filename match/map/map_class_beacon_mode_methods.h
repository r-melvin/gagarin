// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x4AC960: the selected flag byte is `[ESI+0x11B4]`
//   (the seed value is read from `[ESI+0x11B0]`, RepairMode),
//   the other four (`+0x11B1`, `+0x11B2`, `+0x11B3`, `+0x11B0`, cleared in
//   that order) and the refusal word `[ESI+0x11A8]`; the local player is
//   `[0xA83D4C]` and its index `[EAX+0x30]`, passed to the beacon manager
//   singleton at 0x89C3B0 (ECX immediate) via 0x430F30. Vtable slots
//   `[EDX+0x48]` (two zero args) and `[EAX+0x50]` are the same two the other
//   mode setters use (match/map/map_class_mode_methods). Names cross-checked
//   against YRpp MapClass::SetPlaceBeaconMode / BeaconManagerClass.
#ifndef GG_MATCH_MAP_MAP_CLASS_BEACON_MODE_METHODS_H
#define GG_MATCH_MAP_MAP_CLASS_BEACON_MODE_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct HouseClass
{
    char _pad000[0x30];    // +0x0000
    int  ArrayIndex;       // +0x0030
};
GG_STATIC_ASSERT(offsetof(HouseClass, ArrayIndex) == 0x30);

// GLOBAL: GAMEMD 0xA83D4C — HouseClass::CurrentPlayer.
extern HouseClass* CurrentPlayer;

// The beacon manager singleton; the call passes its address in ECX directly.
struct BeaconManagerClass
{
    char opaque[4];
    // FUNCTION: GAMEMD 0x430F30 (decl; reloc) — BeaconManagerClass::CanPlaceBeacon.
    bool CanPlaceBeacon(int houseIndex);
};
// GLOBAL: GAMEMD 0x89C3B0 — BeaconManagerClass::Instance.
extern BeaconManagerClass BeaconManager;

// FUNCTION: GAMEMD 0x48DC90 (decl; reloc) — the no-argument notify run after a
// mode is entered (the same call the other mode setters make).
void ModeEntered();

struct MapClass
{
#include "map_class_mode_slots.inc"

    char _padVtbl[0x11A8 - 4];   // +0x0004  (vptr occupies +0x0000)
    int  unknown_11A8;           // +0x11A8  a mode change is refused when set
    char _pad11AC[0x11B0 - 0x11AC];
    bool RepairMode;             // +0x11B0
    bool SellMode;               // +0x11B1
    bool TogglePowerMode;        // +0x11B2
    bool unknown_11B3;           // +0x11B3
    bool PlaceBeaconMode;        // +0x11B4

    // FUNCTION: GAMEMD 0x4AC960
    void SetPlaceBeaconMode(int mode);
};
GG_STATIC_ASSERT(offsetof(MapClass, unknown_11A8)    == 0x11A8);
GG_STATIC_ASSERT(offsetof(MapClass, RepairMode)      == 0x11B0);
GG_STATIC_ASSERT(offsetof(MapClass, SellMode)        == 0x11B1);
GG_STATIC_ASSERT(offsetof(MapClass, TogglePowerMode) == 0x11B2);
GG_STATIC_ASSERT(offsetof(MapClass, unknown_11B3)    == 0x11B3);
GG_STATIC_ASSERT(offsetof(MapClass, PlaceBeaconMode) == 0x11B4);

#endif  // GG_MATCH_MAP_MAP_CLASS_BEACON_MODE_METHODS_H
