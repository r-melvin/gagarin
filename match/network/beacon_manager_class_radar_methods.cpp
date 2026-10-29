// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes diffed against retail gamemd.exe v1.001 at 0x431700.

#include "beacon_manager_class_radar_methods.h"

// FUNCTION: GAMEMD 0x431700  BeaconManagerClass::DrawRadar
//
// The radar-map twin of Draw (0x430AC0): draw every placed beacon whose owning
// house the current player is allied with (both ways) and which is not in the
// +0x1F5 state, but only during the "on" part of the blink — the frame
// counter modulo the animation period must still be inside the frame count.
// Nothing is drawn while no beacon is allocated. The loops are plain counted-up
// indexes into the 8x3 table: VC6 strength-reduces them into one walking
// pointer and two down-counters on the frame.
void BeaconManager_00431700::DrawRadar(Surface_00431700* surface, Rect_00431700 bounds)
{
    if (AllocatedCount != 0
        && CurrentFrame % RadarBeaconAnimPeriod < BeaconManagerInstance.RadarBeaconFrameCount + 1) {
        for (int row = 0; row < 8; ++row) {
            for (int col = 0; col < 3; ++col) {
                Beacon_00431700* beacon = Beacons[row][col];
                if (beacon != 0 && (beacon->Flags & 1)
                    && DAT_00A83D4C->IsAlliedWith(beacon->HouseIndex)
                    && DAT_00A8022C[beacon->HouseIndex]->IsAlliedWith(DAT_00A83D4C)
                    && DAT_00A8022C[beacon->HouseIndex]->Defeated == 0) {
                    beacon->DrawRadar(surface, bounds, 0);
                }
            }
        }
    }
}
