// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x4C6210.
//   LIBRARY: GAMEMD 0x7C5F00  __ftol (CRT double->long; the (int) cast; reloc)

#include "evade_class_do_methods.h"

// FUNCTION: GAMEMD 0x4C6210
//
// Apply the carried-over campaign state to the freshly loaded scenario: the
// fifty global flags, the carried-over credits (scaled by the scenario's
// multiplier and clamped to its cap when one is set), the difficulty handicap,
// then — if the scenario wants it — the carried-over mission timer, and finally
// the carried-over stage number.
void EvadeClass::Do()
{
    for (int i = 0; i < 50; i++) {
        ScenarioInstance_004C6210->FUN_00689670(i, this->CarryOverGlobals[i]);
    }

    Scenario_004C6210* scenario = ScenarioInstance_004C6210;
    int cap = scenario->At_1C80;
    double money = (double)this->CarryOverMoney * scenario->At_1C78;
    if (cap != -1) {
        double limit = (double)cap;
        if (money >= limit) {
            money = limit;
        }
    }
    int amount = (int)money;

    CurrentPlayer_004C6210->GiveMoney(amount);
    CurrentPlayer_004C6210->At_1DC += amount;
    CurrentPlayer_004C6210->AssignHandicap(this->CarryOverDifficulty);

    if (ScenarioInstance_004C6210->At_34AD) {
        int timer = this->CarryOverTimer;
        if (timer > 0) {
            ScenarioInstance_004C6210->Timer_11E8 = CDTimer_004C6210(timer);
            ScenarioInstance_004C6210->Timer_11E8.Start();
        }
    }

    ScenarioInstance_004C6210->At_35A0 = this->CarryOverStage;
}
