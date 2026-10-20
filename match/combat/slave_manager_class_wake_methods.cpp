// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x6B1020.

#include "slave_manager_class_wake_methods.h"

// FUNCTION: GAMEMD 0x6B1020
//
// Should a sleeping slave miner start working? Only an owned, idle manager
// (State == 0) can. An AI-owned miner always wakes; a player's wakes when it is
// parked on ore, or - once the scan interval has elapsed - when a nearby-cell
// search within the rules range turns up a real cell.
bool SlaveManagerClass::ShouldWakeUpNow()
{
    if (this->Owner == 0) {
        return false;
    }
    if (this->State != 0) {
        return false;
    }

    if (!this->Owner->Owner->IsHumanPlayer) {
        return true;
    }

    if ((this->Owner->*this->Owner->Vtbl->At_1BC)()->At_EC == 5) {
        return true;
    }

    if (RulesInstance->At_1790 + this->LastScanFrame < CurrentFrame) {
        CellStruct cell = (this->Owner->*this->Owner->Vtbl->At_338)(
            RulesInstance->At_1780 / 256, 0);

        if (cell.X != DAT_00B0B5B8.X || cell.Y != DAT_00B0B5B8.Y) {
            return true;
        }
    }

    return false;
}
