// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x4AC700.

#include "map_class_waypoint_mode_methods.h"

// FUNCTION: GAMEMD 0x4AC700  MapClass::SetWaypointMode (__thiscall, ret 0x8)
//
// The waypoint cursor-mode setter, same tri-state as the sell/repair/power
// ones (-1 toggles, 0 clears, 1 sets, anything else leaves it alone). On a
// real change the other four mode flags are cleared and the local player is
// asked for a waypoint slot. Entering the mode with no slot available (and,
// unless `somebool`, no slot already remembered on the player) leaves the
// mode off and drops the parked record; otherwise the mode is entered and
// the slot is remembered unless `somebool`. Leaving the mode hands the parked
// 12-byte record back through the +0x11BC receiver and shows the mouse.
void Map_004AC700::SetWaypointMode(int mode, bool somebool)
{
    bool want = WaypointMode;

    switch (mode) {
    case -1:
        want = !want;
        break;
    case 0:
        want = false;
        break;
    case 1:
        want = (bool)mode;
        break;
    }

    if (want != WaypointMode && unknown_11A8 == 0)
    {
        RepairMode = false;
        SellMode = false;
        TogglePowerMode = false;
        PlaceBeaconMode = false;

        int slot = CurrentPlayer_004AC700->FUN_005090A0();

        if (want)
        {
            if (slot == -1 && (!somebool || CurrentPlayer_004AC700->At_20C == -1)) {
                WaypointMode = false;
                Slot_50();
                At_11BC = 0;
                return;
            }
            WaypointMode = true;
            if (!somebool) {
                CurrentPlayer_004AC700->At_20C = slot;
            }
            ModeEntered_004AC700();
            return;
        }

        WaypointMode = false;
        Slot_50();

        Coord_004AC700* out = At_11BC;
        if (out) {
            *out = At_11C0;
            At_11BC = 0;
            (DAT_00887640->*DAT_00887640->Vtbl->At_10)();
        }
    }
}
