// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x4AC660 / 0x4AC820 /
//   0x4AC8C0.
//
// The three cursor-mode setters. Each takes a tri-state: -1 toggles, 0 clears,
// 1 sets, anything else leaves the mode alone. Entering a mode clears the other
// four and is refused unless the local player's counter at +0x2F0 is positive;
// leaving one runs the vtable slot at +0x50.
//
// Written out three times rather than macro-generated, which turned out to
// matter: the three are *not* byte-identical templates. SetSellMode and
// SetTogglePowerMode call the vtable slot before clearing the other flags,
// while SetRepairMode clears first and calls after. The orders are mutually
// exclusive — imposing either on all three gives two at 100% and one at 92% —
// so each function follows its own bytes.
//
// The tri-state itself is a `switch`, not an if/else chain. Retail emits the
// three compares up front and the bodies *after* them in reverse label order,
// which is the switch lowering; an if/else chain inlines each body at its test
// and scores 80%.

#include "map_class_mode_methods.h"

// FUNCTION: GAMEMD 0x4AC660  MapClass::SetSellMode (__thiscall, ret 0x4)
void MapClass::SetSellMode(int mode)
{
    bool want = SellMode;

    switch (mode) {
    case -1:
        want = !SellMode;
        break;
    case 0:
        want = false;
        break;
    case 1:
        want = (bool)mode;
        break;
    }

    if (want != SellMode && unknown_11A8 == 0)
    {
        Slot_48(0, 0);

        RepairMode = false;
        TogglePowerMode = false;
        unknown_11B3 = false;
        unknown_11B4 = false;

        if (want && CurrentPlayer->unknown_2F0 > 0)
        {
            SellMode = true;
            ModeEntered();
            return;
        }

        SellMode = false;
        Slot_50();
    }
}

// FUNCTION: GAMEMD 0x4AC820  MapClass::SetTogglePowerMode (__thiscall, ret 0x4)
void MapClass::SetTogglePowerMode(int mode)
{
    bool want = TogglePowerMode;

    switch (mode) {
    case -1:
        want = !TogglePowerMode;
        break;
    case 0:
        want = false;
        break;
    case 1:
        want = (bool)mode;
        break;
    }

    if (want != TogglePowerMode && unknown_11A8 == 0)
    {
        Slot_48(0, 0);

        RepairMode = false;
        SellMode = false;
        unknown_11B3 = false;
        unknown_11B4 = false;

        if (want && CurrentPlayer->unknown_2F0 > 0)
        {
            TogglePowerMode = true;
            ModeEntered();
            return;
        }

        TogglePowerMode = false;
        Slot_50();
    }
}

// FUNCTION: GAMEMD 0x4AC8C0  MapClass::SetRepairMode (__thiscall, ret 0x4)
void MapClass::SetRepairMode(int mode)
{
    bool want = RepairMode;

    switch (mode) {
    case -1:
        want = !RepairMode;
        break;
    case 0:
        want = false;
        break;
    case 1:
        want = (bool)mode;
        break;
    }

    if (want != RepairMode && unknown_11A8 == 0)
    {
        SellMode = false;
        TogglePowerMode = false;
        unknown_11B3 = false;
        unknown_11B4 = false;

        Slot_48(0, 0);

        if (want && CurrentPlayer->unknown_2F0 > 0)
        {
            RepairMode = true;
            ModeEntered();
            return;
        }

        RepairMode = false;
        Slot_50();
    }
}

