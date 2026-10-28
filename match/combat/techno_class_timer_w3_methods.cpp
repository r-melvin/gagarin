// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: retail gamemd.exe v1.001 disassembly at each address below. TechnoClass timer starters.
//   The countdown is built as a temporary and copied over the member, which carries the temporary's
//   never-written middle word across (see CDTimerClass in frame_timer.h).
//
// Address index: 0x70E2B0 0x70E300 0x70F770

#include "../_layout/techno_class.h"
#include "../core/scenario_class_methods.h"

// GLOBAL: GAMEMD 0xA8B230 -- the scenario object.
extern ScenarioClass* DAT_00A8B230;
// GLOBAL: GAMEMD 0xA8E7AC -- nonzero while a scenario is being set up.
extern int DAT_00A8E7AC;

// FUNCTION: GAMEMD 0x70E2B0
// Starts the invulnerability countdown and notes whether it forces the shield.
void TechnoClass::FUN_0070E2B0(int duration, int unused, bool forceShielded)
{
    IronCurtainTimer = CDTimerClass(duration);
    IronTintStage = 0;
    if (forceShielded) {
        ForceShielded = 1;
    } else {
        ForceShielded = 0;
    }
}

// FUNCTION: GAMEMD 0x70E300
// Starts the airstrike countdown.
void TechnoClass::FUN_0070E300(int duration)
{
    AirstrikeTimer = CDTimerClass(duration);
    AirstrikeTintStage = 0;
}

// FUNCTION: GAMEMD 0x70F770
// While more than ten frames remain on the targeting timer (and no scenario is loading),
// restarts it with a random 4 to 8 frames.
void TechnoClass::FUN_0070F770()
{
    if (TargetingTimer.GetTimeLeft() > 10 && !DAT_00A8E7AC) {
        TargetingTimer = CDTimerClass(DAT_00A8B230->unknown_0218.RandomRanged(4, 8));
    }
}
