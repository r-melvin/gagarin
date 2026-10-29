// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   The BuildingClass state-machine body at slot 149 (0x44E440), written against the canonical BuildingClass.
//   Read from the retail gamemd.exe v1.001 from its entry to its last RET with a LINEAR decode of the retail
//   bytes (Ghidra's function-flow listing drops instructions after some calls). Method names are slot labels
//   (vf_N = primary-table byte offset / 4).

#include "building_a2_fold.h"

// CAPPED (partial, readable): 95.2% of the retail instructions align (96.9% with registers ignored); the positional
// score is lower (66.7%) because of two small shifts. Remaining delta: (1) in the state-2 countdown retail keeps the
// elapsed ticks in ECX and the remaining ticks in EAX, our register choice is the other way round (4 instructions);
// (2) retail does not cross-jump the third timer start into the first one (3 stores). Variants tried: the 900.0 and
// 1.0 constants as globals / literals, the frame (hoisted coordinate, 16-byte by-value result of slot 75), the order of
// the timer stores and BState store, and four spellings of the elapsed/left comparison.
// FUNCTION: GAMEMD 0x44E440
// Slot 149, the construction (build-up) mission step: MissionStatus 0 starts the build-up animation, 1 and 4 wait for
// it, 2 counts the timer down, 3 starts the sell-style reverse run; every path ends with the price query.
int BuildingClass::vf_149()
{
    CoordStruct where;   // declared up front: the retail frame keeps it apart from the later temporaries
    if (Type->bools_16A4[19]) {
        switch (MissionStatus) {
        case 0:
            if (UnloadTimer.FUN_004A51B0()) {
                RateTimer t;
                t.Timer.TimeLeft = t.Rate = (int)(Type->GateCloseDelay * 900.0);
                t.Timer.StartTime = CurrentFrame;
                MissionStatus = 2;
                GateTimer = t;
                break;
            }
            if (!UnloadTimer.FUN_004A5110()) {
                if (UnloadTimer.FUN_004A5130()) {
                    UnloadTimer.FUN_004A5290();
                } else {
                    UnloadTimer.FUN_004A51F0(Type->DeployTime);
                    where = Location;
                    FUN_007509E0(RulesInstance->GateDown, &where, 0);
                    DAT_00887324->FUN_006D2790(vf_75(), 0);
                }
            }
            {
                MissionStatus = 1;
                RateTimer t;
                t.Timer.TimeLeft = t.Rate = (int)(Type->GateCloseDelay * 900.0);
                t.Timer.StartTime = CurrentFrame;
                GateTimer = t;
            }
            return 0;
        case 3:
            {
                UnloadTimer.FUN_004A5240(Type->DeployTime);
                MissionStatus = 4;
                CoordStruct where = Location;
                FUN_007509E0(RulesInstance->GateUp, &where, 0);
            }
            return 0;
        case 2:
            if (!FUN_0044E3A0()) {
                int duration = GateTimer.Rate;
                if (duration) {
                    int left = GateTimer.Timer.TimeLeft;
                    if (GateTimer.Timer.StartTime != -1) {
                        int elapsed = CurrentFrame - GateTimer.Timer.StartTime;
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
                MissionStatus = 3;
            } else {
                RateTimer t;
                t.Timer.TimeLeft = t.Rate = (int)(Type->GateCloseDelay * 900.0);
                t.Timer.StartTime = CurrentFrame;
                GateTimer = t;
            }
            break;
        case 1:
            if (UnloadTimer.FUN_004A51B0()) {
                MissionStatus = 2;
            }
            // fall through
        case 4:
            if (UnloadTimer.FUN_004A51D0()) {
                EnterIdleMode(false, 1);
                MissionStatus = 5;
                NeedsRedraw = 1;
            }
            if (UnloadTimer.FUN_004A5110() || UnloadTimer.FUN_004A5130() || UnloadTimer.FUN_004A51B0()) {
                int v = (int)(UnloadTimer.FUN_004A52F0() * Type->GateStages);
                if (v != GateStage) {
                    GateStage = (signed char)v;
                    NeedsRedraw = 1;
                }
            }
            return 0;
        }
        int price = (int)(FUN_005B3A00()->Rate * 900.0);
        return price + DAT_00A8B230->unknown_0218.RandomRanged(0, 2);
    }
    vf_122(5, 0);
    return 1;
}
