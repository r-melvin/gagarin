// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes diffed against retail gamemd.exe v1.001 at 0x430AC0.

#include "beacon_manager_class_draw_methods.h"

// FUNCTION: GAMEMD 0x430AC0  BeaconManagerClass::Draw
//
// Draw every placed beacon whose owning house the current player is allied
// with (both ways) and which is not in the +0x1F5 state. Nothing is drawn
// while no beacon is allocated. The loops are plain counted-up indexes into
// the 8x3 table: VC6 strength-reduces them into one walking pointer kept in
// the `this` register and two down-counters on the frame. An explicit
// walking pointer gets a caller-saved register and a spill (14.9%).
void BeaconManager_00430AC0::Draw(Surface_00430AC0* surface, Rect_00430AC0 bounds)
{
    if (AllocatedCount != 0) {
        for (int row = 0; row < 8; ++row) {
            for (int col = 0; col < 3; ++col) {
                Beacon_00430AC0* beacon = Beacons[row][col];
                if (beacon != 0 && (beacon->Flags & 1)
                    && DAT_00A83D4C->FUN_004F9A10(beacon->HouseIndex)
                    && DAT_00A8022C[beacon->HouseIndex]->FUN_004F9A50(DAT_00A83D4C)
                    && DAT_00A8022C[beacon->HouseIndex]->At_1F5 == 0) {
                    beacon->Draw(surface, bounds);
                }
            }
        }
    }
}
