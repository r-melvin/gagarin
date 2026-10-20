// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x70E000.

#include "techno_class_gattling_rate_methods.h"

// FUNCTION: GAMEMD 0x70E000
//
// Spin the gattling gun down. The value drops by RateDown per tick and is
// clamped at zero; once both value and stage are zero any still-playing
// spin sounds are stopped. Otherwise the weapon for the current stage is
// re-selected and, when the value has fallen below the stage's threshold
// (elite or normal table), the stage steps down and the spin-down sound
// stops.
void Techno_0070E000::GattlingRateDown(int rate)
{
    GattlingSoundController.EndLooping();
    IsGattlingSoundPlaying = 0;

    int step = (this->*Vptr->GetTechnoType)()->RateDown * rate;
    GattlingValue -= step;
    if (GattlingValue < 0 || step == 0) {
        GattlingValue = 0;
    }

    int value = GattlingValue;
    int stage = CurrentGattlingStage;
    if (value == 0 && stage == 0) {
        if (IsUnusedGattlingSoundPlaying || IsGattlingSoundPlaying) {
            GattlingSoundController.FUN_00405D40();
            UnusedGattlingSoundController.FUN_00405D40();
            IsUnusedGattlingSoundPlaying = 0;
            IsGattlingSoundPlaying = 0;
        }
    } else {
        (this->*Vptr->GetWeapon)(stage * 2);
        if (stage > 0) {
            int threshold;
            if (FUN_00750010(&Veterancy)) {
                threshold = (this->*Vptr->GetTechnoType)()->EliteStage[stage - 1];
            } else {
                threshold = (this->*Vptr->GetTechnoType)()->WeaponStage[stage - 1];
            }
            if (value < threshold) {
                stage--;
                if (stage >= 0) {
                    CurrentGattlingStage = stage;
                }
                (this->*Vptr->GetWeapon)(stage * 2);
                UnusedGattlingSoundController.FUN_00405D40();
                IsUnusedGattlingSoundPlaying = 0;
            }
        }
    }
}
