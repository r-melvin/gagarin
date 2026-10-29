// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | linear objdump decode of the retail bytes
//   BuildingClass primary-table slot 147 (+0x24C): the per-frame mission body of a service building (repair /
//   reload / unload style missions selected by flags of the building type), returning the delay until its next
//   call. Span 0x44B780..0x44C97D (0x11FD bytes, one stack frame, no tables). The method names are slot labels /
//   FUN_<addr>; no original name is confirmed.
// CAPPED (final) at 3.9% positional (55/1425), 51.8% by sequence alignment; 163 of the 164 calls match retail's order (the cross-jumped
// `vf_122(5,0)` of the repair cases is shared here). Delta: the constant 0 is in EBX against retail's EDI (and retail also holds the
// constant 1 in EBX in the main mission), the frame is 0x40 against 0x28 (the passenger cell / coordinate locals are not overlapped),
// the first scale test compares through TEST where retail compares with the zero register.
// Variants tried: switch against if chains for the status (switch matches the retail dispatch), macro against helper function for the
// health-name pick, the 0x20 / 0x21 / 10 action cases in source order, the passenger walk as a do loop with a goto label, the
// 16AA walk before / after the 16A9 block (after matches), cell locals by value (frame 0x60, worse).

#include "building_a3_views.h"

// The stage counter step shared by several states: when the timer ran out and the rate is set, advance the stage by
// the step and restart the timer; the "changed" flag tells whether it advanced.
inline void BA3AdvanceStage(BA3StageView& s)
{
    if (!s.Timer.FUN_00426630() && s.Rate != 0) {
        s.Changed = 1;
        s.Stage += s.Step;
        BA3Timer restart;
        restart.Start = DAT_00A8ED84;
        restart.Delay = s.Rate;
        s.Timer = restart;
    } else {
        s.Changed = 0;
    }
}

// The same inline downcast the original used on its passenger: only a techno (flag 4 of the abstract flags) counts.
inline BA3TechnoView* BA3AsTechno(BA3TechnoView* object)
{
    if (!object) {
        return 0;
    }
    return (object->unknown_14 & 4) ? object : 0;
}

// FUNCTION: GAMEMD 0x44B780
int BuildingA3View::vf_147()
{
    if (Type->unknown_16AB) {
        FUN_00458E50();
    }

    if (Type->unknown_16B9) {
        switch (Status) {
        case 0:
            FUN_00447780(2);
            BA3_PLAY_NAME(this, unknown_1128, unknown_1138, 7)
            Status = 2;
            break;
        case 2:
            if (!FUN_0065AE30()) {
                vf_122(5, 0);
                FUN_00451E40(7);
                return 1;
            }
            break;
        }
        return 1;
    }

    if (Type->unknown_16C1) {
        switch (Status) {
        case 0:
            Status = 2;
            unknown_6DD = 0;
            unknown_620.Stage = 0;
            unknown_620.Rate = 1;
            unknown_620.Timer.Start = DAT_00A8ED84;
            unknown_620.Timer.Delay = 1;
            if (Type->unknown_684 != -1) {
                unknown_2FC = unknown_2FC - 1 <= 0 ? 0 : unknown_2FC - 1;
            }
            break;
        case 2:
            BA3AdvanceStage(unknown_620);
            if ((double)unknown_620.Stage >= RulesInstance->unknown_16F0 * DAT_007E27F8) {
                unknown_6DD = 0;
                unknown_620.Stage = 0;
                switch (vf_157(0x1C)) {
                case 0x21:
                    if (Owner->IsControlledByCurrentPlayer()) {
                        HBCell cellTmp;
                        HBCell* cell = vf_110(&cellTmp);
                        if (((BA3EvaView*)8)->FUN_0065FA70(*cell)) {
                            FUN_00752700(s_EVA_UnitRepaired_0081905C, -1, -1);
                        }
                        HBCoord where = Location;
                        FUN_007509E0(RulesInstance->unknown_718, &where, 0);
                    }
                case 10:
                    vf_64(unknown_114.FUN_00473430(), DAT_0089C818);
                    vf_122(5, 0);
                    return 1;
                case 0x20:
                    vf_64(unknown_114.FUN_00473430(), DAT_0089C818);
                    return 1;
                default:
                    return 1;
                }
            }
            return 1;
        }
        goto finish;
    }

    if (Type->unknown_16C2) {
        switch (Status) {
        case 0:
            Status = 2;
            unknown_6DD = 0;
            unknown_620.Stage = 0;
            unknown_620.Rate = 1;
            unknown_620.Timer.Start = DAT_00A8ED84;
            unknown_620.Timer.Delay = 1;
            unknown_2FC = unknown_2FC - 1 <= 0 ? 0 : unknown_2FC - 1;
            break;
        case 2:
            BA3AdvanceStage(unknown_620);
            if ((double)unknown_620.Stage >= RulesInstance->unknown_16F0 * DAT_007E27F8) {
                BA3FlashView* flash = &FUN_0065AD30(0)->unknown_150;
                if (flash->FUN_0074FFF0()) {
                    flash->FUN_00750090(1);
                } else {
                    flash->FUN_007500B0(1);
                }
                vf_64(unknown_114.FUN_00473430(), DAT_0089C818);
                vf_122(5, 0);
            }
        }
        goto finish;
    }

    if (Type->unknown_16A9) {
        // The main service mission (the building services one passenger at a time).
        switch (Status) {
        case 0: {
            if (!FUN_0065AE30()) {
                FUN_00451E40(8);
                FUN_00451E40(0xB);
                BA3_PLAY_NAME(this, unknown_127C, unknown_128C, 0xC)
                BA3_PLAY_NAME(this, unknown_1018, unknown_1028, 3)
                vf_122(5, 0);
                return 1;
            }
            unknown_6DD = 0;
            int limit = 100;
            BA3ComPtr* hold = &FUN_0065AD30(0)->unknown_674;
            BA3ComPtr persist;
            persist.p = 0;
            if (hold->p) {
                long hr = persist.FUN_0045AEA0(hold);
                if (hr < 0 && hr != (long)0x80004002) {
                    FUN_007DC720(hr);
                }
            }
            unsigned char clsid[16];
            persist->vf_3(clsid);
            if (!memcmp(clsid, DAT_007E9A40, 16)) {
                limit = 200;
            }
            if (!memcmp(clsid, DAT_007E9AB0, 16)) {
                limit = 200;
            }
            if (vf_157(0x13) == 1 && vf_310(FUN_0065AD30(0)) < limit) {
                Status = 1;
                if (persist.p) {
                    persist.p->Release();
                }
                return 3;
            }
            if (!Owner->IonSensitivesShouldBeOffline()) {
                (*hold)->vf_22();
            }
            if (persist.p) {
                persist.p->Release();
            }
            break;
        }
        case 1: {
            if (!FUN_0065AE30()) {
                if (unknown_57C != 0 || unknown_588 != 0) {
                    BA3_PLAY_NAME(this, unknown_127C, unknown_128C, 0xC)
                    BA3_PLAY_NAME(this, unknown_1018, unknown_1028, 3)
                    FUN_00451E40(8);
                    FUN_00451E40(0xB);
                }
                if (unknown_58C == 0) {
                    unknown_6DD = 1;
                    vf_122(5, 1);
                }
                return 1;
            }
            if (unknown_57C != 0) {
                return 1;
            }
            BA3TechnoView* first = FUN_0065AD30(0);
            if (vf_310(FUN_0065AD30(0)) < 200) {
                if (first->unknown_674->vf_24()) {
                    if (!first->unknown_674->vf_4()) {
                        first->unknown_674->vf_23();
                    }
                    return 1;
                }
                if (!first->unknown_674->vf_24() && FUN_0065AD30(0)->unknown_5A4 != 0) {
                    FUN_0065AD30(0)->FUN_004DF0D0();
                }
            }
            if (vf_157(0x13) == 1) {
                BA3TechnoView* techno = FUN_0065AD30(0);
                double health = techno->FUN_005F5C60();
                double threshold = RulesInstance->unknown_16F8;
                unsigned char flagged = techno->vf_33()->unknown_D24;
                int action = vf_157(0x1C);
                bool noAction = (action != 1 && action != 0x21);
                if ((threshold <= health && !flagged) || noAction) {
                    if (techno->FUN_005F5C60() == RulesInstance->unknown_16F8) {
                        if (!techno->unknown_674->vf_24()) {
                            BA3TechnoView* generic = BA3AsTechno(FUN_0065AD30(0));
                            generic->unknown_674->vf_22();
                            if (generic->unknown_218 == 0 || Owner->FUN_0050B730()) {
                                HBCell cellTmp;
                        HBCell where = *vf_309(&cellTmp, FUN_0065AD30(0), DAT_0089C818);
                                if (unknown_218) {
                                    HBCoord coordTmp;
                                    HBCoord c = unknown_218->vf_18();
                                    (void)coordTmp;
                                    where.X = (short)(c.X / 256);
                                    where.Y = (short)(c.Y / 256);
                                }
                                if (where.X == DAT_0089C818.X && where.Y == DAT_0089C818.Y) {
                                    goto finish;
                                }
                                generic->vf_122(2, 0);
                                generic->vf_288(DAT_0087F7E8.FUN_005657A0(&where), 1);
                                generic->FUN_0070C610(0);
                                vf_157(3);
                                generic->unknown_500 = 0;
                            } else {
                                generic->vf_122(2, 0);
                                generic->vf_288(generic->unknown_218, 1);
                                generic->FUN_0070C610(0);
                                generic->unknown_500 = 0;
                                vf_157(3);
                            }
                        }
                    }
                } else if (!techno->unknown_3D0 || Owner->FUN_0050B730()) {
                    if (unknown_41A) {
                        FUN_00752700(s_EVA_Repairing_00818F18, -1, -1);
                    }
                    Status = 2;
                    BA3_PLAY_NAME(this, unknown_11F4, unknown_1204, 10)
                    FUN_00451E40(3);
                    FUN_00451E40(0x12);
                    unknown_6DD = 0;
                    unknown_620.Stage = 0;
                    unknown_620.Timer.Start = DAT_00A8ED84;
                    unknown_620.Rate = 1;
                    unknown_620.Timer.Delay = 1;
                } else {
                    techno->vf_104(1);
                    Status = 0;
                    unknown_6DD = 1;
                }
            } else if (!Owner->IonSensitivesShouldBeOffline()) {
                if (!FUN_0065AD30(0)->unknown_674->vf_24()) {
                    FUN_0065AD30(0)->unknown_674->vf_22();
                }
            }
            break;
        }
        case 2: {
            if (!FUN_0065AE30()) {
                FUN_00451E40(8);
                FUN_00451E40(0xB);
                BA3_PLAY_NAME(this, unknown_127C, unknown_128C, 0xC)
                BA3_PLAY_NAME(this, unknown_1018, unknown_1028, 3)
                Status = 1;
                return 1;
            }
            if (unknown_620.Rate == 0) {
                unknown_620.Rate = 1;
            }
            BA3AdvanceStage(unknown_620);
            if ((double)unknown_620.Stage >= RulesInstance->unknown_16E8 * DAT_007E27F8 && vf_157(0x13) == 1) {
                unknown_6DD = 0;
                unknown_620.Stage = 0;
                int action = vf_157(0x1C);
                if (action != 1) {
                    if (action != 0x20) {
                        if (unknown_41A) {
                            HBCell cellTmp;
                        HBCell* cell = vf_110(&cellTmp);
                        if (((BA3EvaView*)8)->FUN_0065FA70(*cell)) {
                                FUN_00752700(s_EVA_UnitRepaired_0081905C, -1, -1);
                            }
                        }
                        FUN_00451E40(8);
                        FUN_00451E40(0xB);
                        BA3_PLAY_NAME(this, unknown_127C, unknown_128C, 0xC)
                        BA3_PLAY_NAME(this, unknown_1018, unknown_1028, 3)
                        Status = 1;
                        BA3TechnoView* techno = BA3AsTechno(FUN_0065AD30(0));
                        if (techno->unknown_218 != 0 && !Owner->FUN_0050B730()) {
                            techno->vf_122(2, 0);
                            techno->vf_288(techno->unknown_218, 1);
                            techno->FUN_0070C610(0);
                            vf_157(3);
                            techno->unknown_500 = 0;
                            return 1;
                        }
                        HBCell cellTmp;
                        HBCell where = *vf_309(&cellTmp, FUN_0065AD30(0), DAT_0089C818);
                        if (unknown_218) {
                            HBCoord c = unknown_218->vf_18();
                            where.X = (short)(c.X / 256);
                            where.Y = (short)(c.Y / 256);
                        }
                        if (where.X != DAT_0089C818.X || where.Y != DAT_0089C818.Y) {
                            techno->vf_122(2, 0);
                            techno->vf_288(DAT_0087F7E8.FUN_005657A0(&where), 1);
                            vf_157(3);
                            techno->unknown_500 = 0;
                            return 1;
                        }
                    } else {
                        if (unknown_41A && Owner->vf_06() == 0) {
                            FUN_00752700(s_EVA_InsufficientFunds_00819044, -1, -1);
                        }
                        FUN_00451E40(8);
                        FUN_00451E40(0xB);
                        BA3_PLAY_NAME(this, unknown_127C, unknown_128C, 0xC)
                        BA3_PLAY_NAME(this, unknown_1018, unknown_1028, 3)
                        Status = 1;
                    }
                }
            }
            return 1;
        }
        }

finish:
        return (int)(FUN_005B3A00()->unknown_10 * DAT_007E27F8);
    }

    if (!Type->unknown_16AA) {
        return 0xF;
    }
    // Walk the passengers and release or send them on, depending on what they are doing.
    int index = 0;
    bool found = false;
    if (unknown_E8 > 0) {
        do {
            BA3TechnoView* passenger = FUN_0065AD30(index);
            if (passenger) {
                if (vf_158(0x1D, passenger) == 1 && passenger->unknown_6C == passenger->vf_33()->unknown_A0) {
                    goto release;
                }
                if (passenger->vf_97() != 7 && vf_158(0x13, passenger) == 1) {
                    found = true;
                    if (passenger->vf_97() != 0) {
                        passenger->vf_122(0, 0);
                    } else if (vf_158(0x1F, passenger) != 1 && vf_158(0x1C, passenger) != 1) {
                    release:
                        passenger->vf_289(false, 1);
                        passenger->vf_124(5);
                        passenger->vf_205();
                    }
                }
            }
            index++;
        } while (index < unknown_E8);
        if (found) {
            return (int)(RulesInstance->unknown_1508 * DAT_007E27F8);
        }
    }
    vf_122(5, 0);
    return 3;
}
