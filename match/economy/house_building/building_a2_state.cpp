// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   The six large BuildingClass state-machine bodies of the building-a2 cluster. Every body was read from the
//   retail gamemd.exe v1.001 from its entry to its last RET with a LINEAR decode of the retail bytes
//   (Ghidra's function-flow listing drops instructions after some calls); offsets are pinned in
//   building_a2_views.h. Method names are slot labels (vf_N = primary-table byte offset / 4).

#include "building_a2_views.h"

// CAPPED (partial, readable): 95.2% of the retail instructions align (96.9% with registers ignored); the positional
// score is lower (66.7%) because of two small shifts. Remaining delta: (1) in the state-2 countdown retail keeps the
// elapsed ticks in ECX and the remaining ticks in EAX, our register choice is the other way round (4 instructions);
// (2) retail does not cross-jump the third timer start into the first one (3 stores). Variants tried: the 900.0 and
// 1.0 constants as globals / literals, the frame (hoisted coordinate, 16-byte by-value result of slot 75), the order of
// the timer stores and BState store, and four spellings of the elapsed/left comparison.
// FUNCTION: GAMEMD 0x44E440
// Slot 149, the construction (build-up) mission step: unknown_BC 0 starts the build-up animation, 1 and 4 wait for
// it, 2 counts the timer down, 3 starts the sell-style reverse run; every path ends with the price query.
int BA2Building::vf_149()
{
    HBCoord where;   // declared up front: the retail frame keeps it apart from the later temporaries
    if (Type->unknown_16B7) {
        switch (unknown_BC) {
        case 0:
            if (Stage.FUN_004A51B0()) {
                BA2Timer t;
                t.TimeLeft = t.Duration = (int)(Type->unknown_E28 * 900.0);
                t.StartTime = Frame_A8ED84;
                unknown_BC = 2;
                Timer = t;
                break;
            }
            if (!Stage.FUN_004A5110()) {
                if (Stage.FUN_004A5130()) {
                    Stage.FUN_004A5290();
                } else {
                    Stage.FUN_004A51F0(Type->unknown_3C8);
                    where = Location;
                    FUN_007509E0(RulesInstance_8871E0->unknown_408, &where, 0);
                    DAT_00887324->FUN_006D2790(vf_75(), 0);
                }
            }
            {
                unknown_BC = 1;
                BA2Timer t;
                t.TimeLeft = t.Duration = (int)(Type->unknown_E28 * 900.0);
                t.StartTime = Frame_A8ED84;
                Timer = t;
            }
            return 0;
        case 3:
            {
                Stage.FUN_004A5240(Type->unknown_3C8);
                unknown_BC = 4;
                HBCoord where = Location;
                FUN_007509E0(RulesInstance_8871E0->unknown_404, &where, 0);
            }
            return 0;
        case 2:
            if (!FUN_0044E3A0()) {
                int duration = Timer.Duration;
                if (duration) {
                    int left = Timer.TimeLeft;
                    if (Timer.StartTime != -1) {
                        int elapsed = Frame_A8ED84 - Timer.StartTime;
                        if (elapsed >= left) {
                            left = 0;
                        } else {
                            left = left - elapsed;
                        }
                    }
                    if ((double)(duration - left) / duration != 1.0) {
                        break;
                    }
                }
                unknown_BC = 3;
            } else {
                BA2Timer t;
                t.TimeLeft = t.Duration = (int)(Type->unknown_E28 * 900.0);
                t.StartTime = Frame_A8ED84;
                Timer = t;
            }
            break;
        case 1:
            if (Stage.FUN_004A51B0()) {
                unknown_BC = 2;
            }
            // fall through
        case 4:
            if (Stage.FUN_004A51D0()) {
                vf_289(false, 1);
                unknown_BC = 5;
                unknown_80 = 1;
            }
            if (Stage.FUN_004A5110() || Stage.FUN_004A5130() || Stage.FUN_004A51B0()) {
                int v = (int)(Stage.FUN_004A52F0() * Type->unknown_16F8);
                if (v != unknown_703) {
                    unknown_703 = (signed char)v;
                    unknown_80 = 1;
                }
            }
            return 0;
        }
        int price = (int)(FUN_005B3A00()->unknown_10 * 900.0);
        return price + DAT_00A8B230->Counter.FUN_0065C7E0(0, 2);
    }
    vf_122(5, 0);
    return 1;
}
