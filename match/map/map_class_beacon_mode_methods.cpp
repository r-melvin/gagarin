// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x4AC960.

#include "map_class_beacon_mode_methods.h"

// FUNCTION: GAMEMD 0x4AC960  MapClass::SetPlaceBeaconMode (__thiscall, ret 0x4)
//
// The fourth cursor-mode setter, same tri-state as the sell/repair/power
// ones (-1 toggles, 0 clears, 1 sets, anything else leaves it alone). It
// differs in its gate: entering the mode is refused unless the beacon manager
// says the local player may still place one, and that check runs *before* the
// other four flags are cleared and the +0x48 slot is called, whereas the
// others test the player's counter after.
//
// The starting value of the wanted flag is read from RepairMode (+0x11B0),
// not from PlaceBeaconMode (+0x11B4): retail's `MOV BL,[ESI+0x11B0]` at
// entry against `CMP BL,[ESI+0x11B4]` after the switch. That is almost
// certainly a copy-paste slip in the original (the sibling setters seed from
// their own flag), but it is what the bytes say, and it is why there is no
// CSE copy here where the siblings keep one: the two reads are of different
// members. Seeding from PlaceBeaconMode was the only reason this sat at 10.7%.
void MapView_4AC960::SetPlaceBeaconMode(int mode)
{
    bool want = RepairMode;

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

    if (want != PlaceBeaconMode && unknown_11A8 == 0)
    {
        if (want && !BeaconManager.CanPlaceBeacon(CurrentPlayer->ArrayIndex)) {
            want = false;
        }

        SellMode = false;
        TogglePowerMode = false;
        unknown_11B3 = false;
        RepairMode = false;

        Slot_48(0, 0);

        if (want)
        {
            PlaceBeaconMode = true;
            ModeEntered();
            return;
        }

        PlaceBeaconMode = false;
        Slot_50();
    }
}
