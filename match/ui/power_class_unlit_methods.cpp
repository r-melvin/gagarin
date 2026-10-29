// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   PowerClass::FUN_0063F850 (unlit power-bar segments), bytes matched against retail gamemd.exe
//   v1.001. Kept out of power_class_methods.cpp: retail calls it from 0x63F8F0, and /Ob2 in that TU
//   would inline it. Layout and evidence: input_controls/ui_display_chain.h.
//
//   0x63F850  PowerClass::FUN_0063F850

#include "input_controls/ui_display_chain.h"
#include "../_layout/house_class.h"
#include "../_layout/building_class.h"
#include "../_layout/building_type_class_layout.h"

// GLOBAL: GAMEMD 0xA83D4C
extern HouseClass* CurrentPlayer;
// GLOBAL: GAMEMD 0xB0B504
extern int StripHeight_00B0B504;

// FUNCTION: GAMEMD 0x63F850
// How many bar segments are unlit: the strip's segment count less the share the
// player's total building power (bonus plus drain) takes, clamped to the bar.
int PowerClass::FUN_0063F850()
{
    int segments = (StripHeight_00B0B504 + 3) / 3;
    int drain = 0;
    int bonus = 0;
    for (int i = 0; i < CurrentPlayer->Buildings.Count; ++i) {
        BuildingClass* building = CurrentPlayer->Buildings.Items[i];
        drain += building->Type->PowerDrain;
        bonus += building->Type->PowerBonus;
    }
    int lit = (int)(400.0 / ((double)(bonus + drain) + 400.0) * segments);
    lit = lit > 0 ? lit : 0;
    lit = lit < segments - 1 ? lit : segments - 1;
    return segments - lit;
}
