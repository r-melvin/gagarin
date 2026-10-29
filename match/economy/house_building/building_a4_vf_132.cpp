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
int BA4Building::vf_132()
{
    if (Type->unknown_16B8) {
        switch (unknown_BC) {
        case 0:
            {
                if (Type->unknown_1573 && Type->unknown_EE4 > 0 && Owner->FUN_004FCE30() < 1.0) {
                    return 1;
                }
                BA4Object* techno = BA4As(Target, 2);
                if (!Target || !techno || !techno->vf_116()) {
                    vf_242(0);
                    unknown_BC = 0;
                    vf_122(5, 0);
                    vf_123();
                    return 1;
                }
                if (Facing.FUN_004C9480()) {
                    return 1;
                }
                HBDir bufferA;
                HBDir* wanted = vf_314(&bufferA, Target);
                if (abs((short)0x2000) < abs((short)(Facing.FUN_004C93D0().Raw - wanted->Raw))) {
                    HBDir bufferC;
                    Facing.FUN_004C9220(vf_314(&bufferC, Target));
                    return 1;
                }
                unknown_BC = 1;
                return 1;
            }
        case 1:
            {
                BA4Object* techno = BA4As(Target, 2);
                if (!Target || !techno || !techno->vf_116()) {
                    vf_242(0);
                    unknown_BC = 0;
                    return 1;
                }
                int result = vf_240(Target, 0, 1);
                if (result == 5 || result == 6 || result == 8) {
                    vf_242(0);
                    unknown_BC = 0;
                    return 1;
                }
                if (result == 2) {
                    unknown_BC = 0;
                    return 1;
                }
                if (result != 0) {
                    return 1;
                }
                vf_243(Target, 0);
                vf_243(Target, 1);
                unknown_BC = 0;
                return 1;
            }
        default:
            int base = (int)(FUN_005B3A00()->unknown_18 * 900.0);
            return base + DAT_00A8B230->unknown_0218.RandomRanged(0, 2);
        }
    }

    if (!Target) {
        vf_242(0);
        unknown_664 = 0;
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
    unknown_6DD = 1;
    int result = vf_240(Target, direction, 1);
    if (result == 2) {
        if (vf_255() && Type->unknown_16C5) {
            HBDir buffer;
            HBDir wanted = *vf_314(&buffer, Target);
            int turn = Type->unknown_71C;
            if (!turn || !(abs((short)(turn << 8)) < abs((short)(Facing.FUN_004C93D0().Raw - wanted.Raw)))) {
                Facing.FUN_004C9300(&wanted);
                result = vf_240(Target, direction, 1);
            }
        }
    }
    switch (result) {
    case 0:
        if (unknown_702 != 0 && Upgrades[1] != 0) {
            if (Upgrades[1]->FUN_00712130()) {
                vf_243(Target, 0);
                vf_243(Target, 1);
            }
        } else if (Type == DAT_008871E0->unknown_498) {
            BA4Building* best = 0;
            int bestDistance = 0x7FFFFFFF;
            HBCoordPod scratch;
            HBCoordPod here = *vf_43(&scratch);
            if (unknown_664 < DAT_008871E0->unknown_4A0) {
                int count = Owner->unknown_68.Count;
                for (int i = 0; i < count; i++) {
                    BA4Building* candidate = Owner->unknown_68.Items[i];
                    if (candidate && candidate->unknown_90 && candidate->Type == DAT_008871E0->unknown_498) {
                        int started = candidate->unknown_2EC;
                        int length = candidate->unknown_2F4;
                        if (started != -1) {
                            int elapsed = DAT_00A8ED84 - started;
                            if (elapsed < length) {
                                length = length - elapsed;
                            } else {
                                length = 0;
                            }
                        }
                        if (length == 0 && candidate->unknown_714 == 0 && !candidate->FUN_0070FEC0()
                            && candidate->vf_97() != 1 && candidate != this) {
                            HBCoordPod scratchCandidate;
                            HBCoordPod* there = candidate->vf_43(&scratchCandidate);
                            double dx = here.X - there->X;
                            double dy = there->Y - here.Y;
                            float dz = here.Z - there->Z;
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
                    unknown_664++;
                    HBCoordPod zero;
                    zero.X = 0;
                    zero.Y = 0;
                    zero.Z = 0;
                    HBCoordPod scratchTarget;
                    HBCoordPod* where = vf_44(&scratchTarget, 0, zero);
                    best->unknown_714 = best->Type->unknown_16EC;
                    best->unknown_704 = 2;
                    best->unknown_708 = *where;
                    best->FUN_00451E40(3);
                    char* text;
                    int flag;
                    if (best->FUN_005F5C60() > DAT_008871E0->unknown_1700) {
                        text = &best->Type->unknown_F4C[10].unknown_00[0];
                        flag = 0;
                    } else {
                        text = &best->Type->unknown_F4C[10].unknown_10[0];
                        flag = 1;
                    }
                    if (text && *text) {
                        best->FUN_00451890(text, 10, flag, 0, 0);
                    }
                    break;
                }
            }
            HBCoordPod cleared = {0, 0, 0};
            unknown_714 = Type->unknown_16EC;
            unknown_708 = cleared;
            unknown_704 = 1;
            FUN_00451E40(3);
            char* text;
            int flag;
            if (FUN_005F5C60() > DAT_008871E0->unknown_1700) {
                text = &Type->unknown_F4C[10].unknown_00[0];
                flag = 0;
            } else {
                text = &Type->unknown_F4C[10].unknown_10[0];
                flag = 1;
            }
            if (text && *text) {
                FUN_00451890(text, 10, flag, 0, 0);
            }
        } else if (Type->unknown_16A7) {
            HBCoordPod cleared = {0, 0, 0};
            unknown_714 = Type->unknown_16EC;
            unknown_708 = cleared;
            unknown_704 = 1;
            FUN_00451E40(3);
            char* text;
            int flag;
            if (FUN_005F5C60() > DAT_008871E0->unknown_1700) {
                text = &Type->unknown_F4C[10].unknown_00[0];
                flag = 0;
            } else {
                text = &Type->unknown_F4C[10].unknown_10[0];
                flag = 1;
            }
            if (text && *text) {
                FUN_00451890(text, 10, flag, 0, 0);
            }
        } else {
            vf_243(Target, direction);
        }
        if (Type->unknown_CD5) {
            FUN_0070DE70(unknown_C4);
            unknown_C4 = 0;
            return 1;
        }
        unknown_148++;
        return 1;

    case 1:
    case 5:
    case 6:
    case 8:
        vf_242(0);
        unknown_664 = 0;
        if (vf_268()) {
            FUN_00705D60();
        }
        if (vf_97() == 0x1C) {
            return 1;
        }
        if (Type->unknown_CD5) {
            FUN_0070E000(unknown_C4);
            unknown_C4 = 0;
        }
        vf_122(5, 0);
        vf_123();
        break;

    case 2:
        if (Target) {
            HBDir buffer;
            Facing.FUN_004C9220(vf_314(&buffer, Target));
        }
        if (Type->unknown_CD5) {
            FUN_0070DE70(unknown_C4);
            unknown_C4 = 0;
        }
        return 2;

    case 3:
        if (Target) {
            HBDir buffer;
            Facing.FUN_004C9220(vf_314(&buffer, Target));
        }
        if (Type->unknown_CD5) {
            FUN_0070DE70(unknown_C4);
            unknown_C4 = 0;
            return 2;
        }
        unknown_148++;
        return 2;

    case 9:
        vf_279(0);
        if (Type->unknown_CD5) {
            FUN_0070E000(unknown_C4);
            unknown_C4 = 0;
        }
        break;

    case 10:
        if (Type->unknown_CD5) {
            FUN_0070E000(unknown_C4);
            unknown_C4 = 0;
        }
        return 1;

    default:
        break;
    }
    if (Target) {
        HBDir buffer;
        Facing.FUN_004C9220(vf_314(&buffer, Target));
    }
    unknown_C4 = 0;
    return 1;
}
