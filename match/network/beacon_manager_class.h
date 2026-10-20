// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Layout + offsets derived from the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI (member-access disassembly at 0x430980 / 0x430F30 /
//   0x431410), cross-checked against YRpp BeaconManagerClass.h (consult-only;
//   reconfirmed numerically here).
//
// BeaconManagerClass — the multiplayer radar/map beacon table: an 8x3 grid of
// BeaconClass pointers (8 houses, up to 3 beacons each) plus the live count.
#ifndef GG_MATCH_NETWORK_BEACON_MANAGER_CLASS_H
#define GG_MATCH_NETWORK_BEACON_MANAGER_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

class BeaconClass;

// ---------------------------------------------------------------------------
// BeaconManagerClass
//
// Confirmed offsets:
//   +0x00  Beacons[8][3]   — 24 contiguous 4-byte pointers (96 bytes = 0x60).
//                            Reset walks `this` as 8*3 dwords; CanPlaceBeacon
//                            indexes [ECX + houseId*3*4]; DeleteAllBeacons does
//                            the same. (LEA EDX,[EDX+EDX*2]; LEA ECX,[ECX+EDX*4])
//   +0x60  AllocatedCount  — read as [this+0x60], cleared to 0 by Reset.
// ---------------------------------------------------------------------------
class BeaconManagerClass
{
public:
    // Declared ascending by retail address (reccmp/isle TU discipline).
    void Reset();                              // GAMEMD 0x430980 __thiscall
    bool CanPlaceBeacon(int houseId);          // GAMEMD 0x430F30 __thiscall
    void DeleteAllBeacons(int houseId);        // GAMEMD 0x431410 __thiscall

    // Referenced callee matched in its own TU; declared (no body) so cl emits
    // a __thiscall call (relocation-normalised by the harness).
    void DeleteBeacon(int houseId, int houseBeaconId);  // GAMEMD 0x4311C0

    BeaconClass* Beacons[8][3];   // +0x00
    int          AllocatedCount;  // +0x60
};

GG_STATIC_ASSERT(offsetof(BeaconManagerClass, Beacons)        == 0x00);
GG_STATIC_ASSERT(offsetof(BeaconManagerClass, AllocatedCount) == 0x60);

#endif  // GG_MATCH_NETWORK_BEACON_MANAGER_CLASS_H
