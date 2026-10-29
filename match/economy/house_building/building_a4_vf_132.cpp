// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   BuildingClass primary-table slot 132 at 0x44ACF0 (0xA35 bytes of code plus the 11-entry jump table at
//   0x44B728, 0xA64 in all), read from the retail gamemd.exe v1.001 from its entry to its last RET (linear
//   decode; Ghidra could not recover the jump table). It is a per-tick mission body that returns the delay
//   to the next tick; slot 240 returns a result code 0..10 that the table dispatches. The original name is
//   not confirmed here.
//   +0x708 (two arms of case 2): retail copies a 12-byte stack value whose upper words were never written
//   (indeterminate). The source stores a zeroed value instead, which is well-defined; the function stays partial.

#include "building_a4_views.h"

// FUNCTION: GAMEMD 0x44ACF0
int BuildingClass::vf_132()
{
    if (Type->bools_16A4[20]) {
        switch (MissionStatus) {
        case 0:
            {
                if (Type->bools_1570[3] && Type->PowerDrain > 0 && Owner->GetPowerPercentage() < 1.0) {
                    return 1;
                }
                ObjectClass* techno = BA4As<ObjectClass>(Target, 2);
                if (!Target || !techno || !techno->FUN_005F5F30()) {
                    vf_242(0);
                    MissionStatus = 0;
                    vf_122(5, 0);
                    vf_123();
                    return 1;
                }
                if (PrimaryFacing.FUN_004C9480()) {
                    return 1;
                }
                DirStruct wanted = vf_314(Target);
                if (abs((short)0x2000) < abs((short)(PrimaryFacing.FUN_004C93D0().Raw - wanted.Raw))) {
                    PrimaryFacing.SetDesired(vf_314(Target));
                    return 1;
                }
                MissionStatus = 1;
                return 1;
            }
        case 1:
            {
                ObjectClass* techno = BA4As<ObjectClass>(Target, 2);
                if (!Target || !techno || !techno->FUN_005F5F30()) {
                    vf_242(0);
                    MissionStatus = 0;
                    return 1;
                }
                int result = vf_240(Target, 0, 1);
                if (result == 5 || result == 6 || result == 8) {
                    vf_242(0);
                    MissionStatus = 0;
                    return 1;
                }
                if (result == 2) {
                    MissionStatus = 0;
                    return 1;
                }
                if (result != 0) {
                    return 1;
                }
                vf_243(Target, 0);
                vf_243(Target, 1);
                MissionStatus = 0;
                return 1;
            }
        default:
            int base = (int)(FUN_005B3A00()->AARate * 900.0);
            return base + DAT_00A8B230->unknown_0218.RandomRanged(0, 2);
        }
    }

    if (!Target) {
        vf_242(0);
        SupportingPrisms = 0;
        if (vf_268()) {
            FUN_00705D60();
        }
        if (vf_97() == 0x1C) {
            return 1;
        }
        vf_122(5, 0);
        vf_123();
        return 1;
    }

    int direction = vf_185(Target);
    IsReadyToCommence = 1;
    int result = vf_240(Target, direction, 1);
    if (result == 2) {
        if (vf_255() && Type->bools_16A4[33]) {
            DirStruct wanted = vf_314(Target);
            int turn = Type->ROT;
            if (!turn || !(abs((short)(turn << 8)) < abs((short)(PrimaryFacing.FUN_004C93D0().Raw - wanted.Raw)))) {
                PrimaryFacing.FUN_004C9300(&wanted);
                result = vf_240(Target, direction, 1);
            }
        }
    }
    switch (result) {
    case 0:
        if (UpgradeLevel != 0 && Upgrades[1] != 0) {
            if (Upgrades[1]->FUN_00712130()) {
                vf_243(Target, 0);
                vf_243(Target, 1);
            }
        } else if (Type == RulesInstance->PrismType) {
            BuildingClass* best = 0;
            int bestDistance = 0x7FFFFFFF;
            CoordStruct here = vf_43();
            if (SupportingPrisms < RulesInstance->PrismSupportMax) {
                int count = Owner->Buildings.Count;
                for (int i = 0; i < count; i++) {
                    BuildingClass* candidate = Owner->Buildings.Items[i];
                    if (candidate && candidate->IsAlive && candidate->Type == RulesInstance->PrismType) {
                        int length = candidate->RearmTimer.GetTimeLeft();
                        if (length == 0 && candidate->DelayBeforeFiring == 0 && !candidate->IsBeingDrained()
                            && candidate->vf_97() != 1 && candidate != this) {
                            CoordStruct there = candidate->vf_43();
                            double dx = here.X - there.X;
                            double dy = there.Y - here.Y;
                            float dz = here.Z - there.Z;
                            int distance = (int)FUN_004CAC40(dx * dx + dz * dz + dy * dy);
                            if (distance <= vf_90(1)) {
                                if (!best || distance < bestDistance) {
                                    best = candidate;
                                    bestDistance = distance;
                                }
                            }
                        }
                    }
                }
                if (best) {
                    SupportingPrisms++;
                    CoordStruct zero;
                    zero.X = 0;
                    zero.Y = 0;
                    zero.Z = 0;
                    CoordStruct where = vf_44(0, zero);
                    best->DelayBeforeFiring = best->Type->DelayedFireDelay;
                    best->PrismStage = 2;
                    best->PrismTargetCoords = where;
                    best->DestroyNthAnim(3);
                    char* text;
                    int flag;
                    if (best->FUN_005F5C60() > RulesInstance->ConditionYellow) {
                        text = &best->Type->BuildingAnim[10].Anim[0];
                        flag = 0;
                    } else {
                        text = &best->Type->BuildingAnim[10].Damaged[0];
                        flag = 1;
                    }
                    if (text && *text) {
                        best->PlayAnim(text, 10, flag, 0, 0);
                    }
                    break;
                }
            }
            CoordStruct cleared = {0, 0, 0};
            DelayBeforeFiring = Type->DelayedFireDelay;
            PrismTargetCoords = cleared;
            PrismStage = 1;
            DestroyNthAnim(3);
            char* text;
            int flag;
            if (FUN_005F5C60() > RulesInstance->ConditionYellow) {
                text = &Type->BuildingAnim[10].Anim[0];
                flag = 0;
            } else {
                text = &Type->BuildingAnim[10].Damaged[0];
                flag = 1;
            }
            if (text && *text) {
                PlayAnim(text, 10, flag, 0, 0);
            }
        } else if (Type->bools_16A4[3]) {
            CoordStruct cleared = {0, 0, 0};
            DelayBeforeFiring = Type->DelayedFireDelay;
            PrismTargetCoords = cleared;
            PrismStage = 1;
            DestroyNthAnim(3);
            char* text;
            int flag;
            if (FUN_005F5C60() > RulesInstance->ConditionYellow) {
                text = &Type->BuildingAnim[10].Anim[0];
                flag = 0;
            } else {
                text = &Type->BuildingAnim[10].Damaged[0];
                flag = 1;
            }
            if (text && *text) {
                PlayAnim(text, 10, flag, 0, 0);
            }
        } else {
            vf_243(Target, direction);
        }
        if (Type->IsGattling) {
            FUN_0070DE70(MissionAccumulateTime);
            MissionAccumulateTime = 0;
            return 1;
        }
        TurretAnimFrame++;
        return 1;

    case 1:
    case 5:
    case 6:
    case 8:
        vf_242(0);
        SupportingPrisms = 0;
        if (vf_268()) {
            FUN_00705D60();
        }
        if (vf_97() == 0x1C) {
            return 1;
        }
        if (Type->IsGattling) {
            FUN_0070E000(MissionAccumulateTime);
            MissionAccumulateTime = 0;
        }
        vf_122(5, 0);
        vf_123();
        break;

    case 2:
        if (Target) {
            PrimaryFacing.SetDesired(vf_314(Target));
        }
        if (Type->IsGattling) {
            FUN_0070DE70(MissionAccumulateTime);
            MissionAccumulateTime = 0;
        }
        return 2;

    case 3:
        if (Target) {
            PrimaryFacing.SetDesired(vf_314(Target));
        }
        if (Type->IsGattling) {
            FUN_0070DE70(MissionAccumulateTime);
            MissionAccumulateTime = 0;
            return 2;
        }
        TurretAnimFrame++;
        return 2;

    case 9:
        vf_279(0);
        if (Type->IsGattling) {
            FUN_0070E000(MissionAccumulateTime);
            MissionAccumulateTime = 0;
        }
        break;

    case 10:
        if (Type->IsGattling) {
            FUN_0070E000(MissionAccumulateTime);
            MissionAccumulateTime = 0;
        }
        return 1;

    default:
        break;
    }
    if (Target) {
        PrimaryFacing.SetDesired(vf_314(Target));
    }
    MissionAccumulateTime = 0;
    return 1;
}
