// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | linear objdump decode of the retail bytes
//   BuildingClass primary-table slot 311 (+0x4DC): the placement reaction of a building (announcements, house
//   counters, the free unit). Span 0x445F80..0x446FE8 (0x1068 bytes: code to 0x446FC0 and the 10-entry jump table
//   of the super weapon EVA switch). The method names are slot labels / FUN_<addr>; no original name is confirmed.
// CAPPED (final) at 4.2% positional on the 0x1040-byte code span (50/1194; the 0x28-byte jump table is not scored by the decoder),
// 50.2% by sequence alignment; 81 calls in retail order bar one pair swapped. Delta: five flavours of the health-dependent name pick
// compiled as `bool low` in a register against retail's flag in ECX (set by the same branch that picks the name); the EVA
// switch is emitted with its case blocks in the retail order 0,1,2,7,9,3 but the surrounding stack frame is 0x7C against 0x58
// (the two cell searches and the pathfinding temporaries are named locals here); the free-unit placement is written as two explicit
// attempts as in retail.
// Variants tried: the pick as ternaries on a bool (aligned 45%), as an if/else setting the flag (aligned 50%), a helper inline, loop
// against two explicit attempts, goto against flag for the unit placement.

#include "building_a3_views.h"

// The sound / animation name slot of a building type: nothing is played for a null or empty name.
// FUN_00451890 is reached through BuildingA3View::FUN_00451890(name, id, a, b, c).

// The 256-lepton cell a coordinate lies in.
inline HBCell BA3CellOf(const HBCoord& where)
{
    HBCell cell;
    cell.X = (short)(where.X / 256);
    cell.Y = (short)(where.Y / 256);
    return cell;
}

// FUNCTION: GAMEMD 0x445F80
void BuildingA3View::vf_311(char flag)
{
    if (unknown_6E4 && !flag) {
        return;
    }

    if (Type->unknown_1560) {
        BA3Timer timer;
        timer.Start = DAT_00A8ED84;
        timer.Delay = Type->unknown_1560;
        unknown_6D0 = timer;
    }

    if (!unknown_6E4) {
        const char* name;
        if (Type->unknown_16BB) {
            // Charge-up sounds: the stage is the charge in quarters.
            int stage = 0;
            if ((int)unknown_33C.FUN_006C9650() != 0) {
                stage = ((int)unknown_33C.FUN_006C9650() << 2) / Type->unknown_800;
            }
            unknown_6F0 = stage;
            double ratio;
            int flagLow;
            if (stage >= 3) {
                ratio = FUN_005F5C60();
                if (ratio > RulesInstance->unknown_1700) {
                    name = Type->unknown_10E4;
                    flagLow = 0;
                } else {
                    name = Type->unknown_10F4;
                    flagLow = 1;
                }
                if (name && *name) {
                    FUN_00451890(name, 6, flagLow, 0, 0);
                }
            } else if (stage >= 2) {
                ratio = FUN_005F5C60();
                if (ratio > RulesInstance->unknown_1700) {
                    name = Type->unknown_10A0;
                    flagLow = 0;
                } else {
                    name = Type->unknown_10B0;
                    flagLow = 1;
                }
                if (name && *name) {
                    FUN_00451890(name, 5, flagLow, 0, 0);
                }
            } else if (stage >= 1) {
                ratio = FUN_005F5C60();
                if (ratio > RulesInstance->unknown_1700) {
                    name = Type->unknown_105C;
                    flagLow = 0;
                } else {
                    name = Type->unknown_106C;
                    flagLow = 1;
                }
                if (name && *name) {
                    FUN_00451890(name, 4, flagLow, 0, 0);
                }
            } else if (stage >= 0) {
                ratio = FUN_005F5C60();
                if (ratio > RulesInstance->unknown_1700) {
                    name = Type->unknown_1018;
                    flagLow = 0;
                } else {
                    name = Type->unknown_1028;
                    flagLow = 1;
                }
                if (name && *name) {
                    FUN_00451890(name, 3, flagLow, 0, 0);
                }
            }
        } else {
            // Health dependent sounds, one per condition slot.
            {
                double ratio = FUN_005F5C60();
                int low = ratio <= RulesInstance->unknown_1700;
                bool armed = vf_258() > 0;
                name = low ? Type->unknown_1424 : (armed ? Type->unknown_1434 : Type->unknown_1414);
                if (name && *name) {
                    FUN_00451890(name, 0x12, low, armed, 0);
                }
            }
            {
                double ratio = FUN_005F5C60();
                int low = ratio <= RulesInstance->unknown_1700;
                bool armed = vf_258() > 0;
                name = low ? Type->unknown_1028 : (armed ? Type->unknown_1038 : Type->unknown_1018);
                if (name && *name) {
                    FUN_00451890(name, 3, low, armed, 0);
                }
            }
            {
                double ratio = FUN_005F5C60();
                int flagLow;
                if (ratio > RulesInstance->unknown_1700) {
                    name = Type->unknown_105C;
                    flagLow = 0;
                } else {
                    name = Type->unknown_106C;
                    flagLow = 1;
                }
                if (name && *name) {
                    FUN_00451890(name, 4, flagLow, 0, 0);
                }
            }
            {
                double ratio = FUN_005F5C60();
                int flagLow;
                if (ratio > RulesInstance->unknown_1700) {
                    name = Type->unknown_10A0;
                    flagLow = 0;
                } else {
                    name = Type->unknown_10B0;
                    flagLow = 1;
                }
                if (name && *name) {
                    FUN_00451890(name, 5, flagLow, 0, 0);
                }
            }
            {
                double ratio = FUN_005F5C60();
                int flagLow;
                if (ratio > RulesInstance->unknown_1700) {
                    name = Type->unknown_10E4;
                    flagLow = 0;
                } else {
                    name = Type->unknown_10F4;
                    flagLow = 1;
                }
                if (name && *name) {
                    FUN_00451890(name, 6, flagLow, 0, 0);
                }
            }
        }

        if (Type->unknown_16CC) {
            ++Owner->unknown_538C;
        }
        if (Type->unknown_1564) {
            Owner->unknown_164 += Type->unknown_1564;
        }
        if (Type->unknown_1568) {
            Owner->unknown_168 += Type->unknown_1568;
        }
        if (Type->unknown_16CB) {
            Owner->unknown_2D4 += Type->unknown_1780;
            DAT_0087F7E8.FUN_006A60E0(3);
        }

        // Super weapon timers of the owner that belong to this type: announce how long they still have to run.
        if (Type->unknown_16F0 != -1) {
            for (int i = 0; i < Owner->unknown_264; i++) {
                BA3SuperView* super = Owner->unknown_258[i];
                if (super->unknown_28->unknown_B4 == Type->unknown_16F0) {
                    int remaining = super->unknown_38;
                    if (super->unknown_30 != -1) {
                        int elapsed = DAT_00A8ED84 - super->unknown_30;
                        if (elapsed < remaining) {
                            remaining = remaining - elapsed;
                        } else {
                            remaining = 0;
                        }
                    }
                    if (remaining / 15 * 60 <= 4) {
                        double ratio = FUN_005F5C60();
                        int low = ratio <= RulesInstance->unknown_1700;
                        bool armed = vf_258() > 0;
                        name = low ? Type->unknown_139C : (armed ? Type->unknown_13AC : Type->unknown_138C);
                        if (name && *name) {
                            FUN_00451890(name, 0x10, low, armed, 0);
                        }
                    } else {
                        double ratio = FUN_005F5C60();
                        int low = ratio <= RulesInstance->unknown_1700;
                        bool armed = vf_258() > 0;
                        name = low ? Type->unknown_1314 : (armed ? Type->unknown_1324 : Type->unknown_1304);
                        if (name && *name) {
                            FUN_00451890(name, 0xE, low, armed, 0);
                        }
                    }
                }
            }
        }

        if (vf_255() && !Type->unknown_16C5) {
            int previous = unknown_5FC;
            if (previous == -1) {
                name = Type->unknown_11B0;
                if (name && *name) {
                    FUN_00451890(name, 9, 0, 0, 0);
                }
            } else {
                unknown_5FC = -1;
                if (!Type->unknown_16C5) {
                    FUN_00451E40(9);
                    char buffer[0x40];
                    strcpy(buffer, Type->unknown_1F8);
                    strcat(buffer, DAT_00818D7C);
                    buffer[strlen(buffer)] = (char)(previous + 'B');
                    buffer[strlen(buffer) + 1] = 0;
                    FUN_00451890(buffer, 9, 0, 0, 0);
                    unknown_5FC = previous;
                }
            }
            if (vf_255() && unknown_580) {
                HBDir facing = Facing388.FUN_004C93D0();
                if (unknown_580) {
                    unknown_580->unknown_AC = DAT_007F4890[(facing.Whole >> 10) + 1 >> 1 & 0x1F];
                    unknown_580->unknown_C4 = 0;
                }
            }
        }

        if (Type->unknown_E34) {
            if (!LightSource) {
                BA3LightMem* mem = new BA3LightMem;
                if (mem) {
                    LightSource = mem->FUN_00554760(vf_18(), Type->unknown_E30, Type->unknown_E34, Type->unknown_E38,
                                                    Type->unknown_E3C, Type->unknown_E40);
                } else {
                    LightSource = 0;
                }
            }
            LightSource->FUN_00554A60(0);
        }

        if (Type->unknown_16BE) {
            FUN_004533A0(0);
        }
        if (Type->unknown_16C8) {
            vf_317(DAT_0089C818);
        }
        if (Type->unknown_D31) {
            vf_319(DAT_0089C818);
        }
        unknown_6DD = 1;
    }

    if (Type->unknown_1573) {
        FUN_004547C0();
    }

    if (Type->unknown_5EE && !Owner->FUN_0050B6F0()) {
        if (!flag) {
            vf_290(0, 0, 1, DAT_00A83D4C, 0);
            HBCoord where = Location;
            DAT_0087F7E8.FUN_00567DA0(&where, 0, unknown_260 + 3, 0);
        }
        HBCell cell;
        cell.X = (short)(Location.X / 256);
        cell.Y = (short)(Location.Y / 256);
        ((BA3EvaView*)12)->FUN_0065FA70(cell);
    }

    // The EVA announcement of a super weapon building.
    if (!Owner->FUN_0050B6F0() && !Owner->FUN_004F9A50(DAT_00A83D4C) && DAT_00A8B538 == 0 && DAT_00A8B238
        && (Type->unknown_16F0 == -1 || DAT_00A83CBC[Type->unknown_16F0]->unknown_28->unknown_C8 == 0
            || Owner->unknown_5550.FUN_0049FAE0(DAT_00A83CBC[Type->unknown_16F0]->unknown_28->unknown_C8->unknown_DF8) != 0)) {
        const char* eva;
        switch (Type->unknown_16F0) {
        case 0:
            eva = s_EVA_NuclearSiloDetected_00818F00;
            break;
        case 1:
            eva = s_EVA_IronCurtainDetected_00818EE8;
            break;
        case 2:
            eva = s_EVA_WeatherDeviceReady_00818ED0;
            break;
        case 7:
            eva = s_EVA_PsychicDominatorDetected_00818EB0;
            break;
        case 9:
            eva = s_EVA_GeneticMutatorDetected_00818E94;
            break;
        case 3:
            eva = s_EVA_ChronosphereDetected_00818E78;
            break;
        default:
            goto afterEva;
        }
        FUN_00752700(eva, -1, -1);
    }
afterEva:

    // A building with a second exit: look for a free cell next to it and move there.
    if (Type->unknown_16BD && Type->unknown_CCE && unknown_218 == 0) {
        HBCell zero;
        zero.X = 0;
        zero.Y = 0;
        HBCoord start;
        HBCell scratch;
        HBCell found = *DAT_0087F7E8.FUN_0056DC20(&start, vf_110(&scratch), 5, -1, 10, 0, 5, 5, 0, 0, 0, 1, &zero, 0, 0);
        HBCell moved;
        moved.X = found.X + 2;
        moved.Y = found.Y + 2;
        if (moved.X != DAT_0089C818.X || moved.Y != DAT_0089C818.Y) {
            FUN_00443860(moved, 0);
        }
    }

    Owner->unknown_1FC = 1;
    unknown_6E4 = 1;
    Owner->unknown_5778 = 1;
    Owner->unknown_5779 = 1;
    if (vf_33()->unknown_CD1) {
        vf_261();
    }

    // The free unit of the building type.
    if (Type->unknown_EA0 && DAT_00A8E7AC == 0 && !flag && !DAT_00A8ED6B) {
        if (!Owner->FUN_0050B730() || !unknown_300 || unknown_300 > Type->unknown_EA0->vf_43()) {
            HBCoord at = vf_18();
            HBCell base;
            base.X = (short)(at.X / 256);
            base.Y = (short)(at.Y / 256);
            HBCell spot;
            spot.X = base.X + DAT_0089F698.X;
            spot.Y = base.Y + DAT_0089F698.Y;
            BA3UnitMem* mem = new BA3UnitMem;
            BA3UnitView* unit;
            if (mem) {
                unit = mem->FUN_007353C0(Type->unknown_EA0, Owner);
            } else {
                unit = 0;
            }
            if (unit) {
                HBCoord target;
                target.X = spot.X * 256 + 0x80;
                target.Y = spot.Y * 256 + 0x80;
                target.Z = 0;
                if (!unit->vf_54(target, 0xC0)) {
                    // Not placeable there: let the cell search look around the building, twice with different options.
                    int movement = unit->unknown_6C4->unknown_5B4;
                    {
                        HBCell zeroCell;
                        zeroCell.X = 0;
                        zeroCell.Y = 0;
                        HBCoord start = Location;
                        HBCell cell = BA3CellOf(start);
                        HBCell zoneCell = cell;
                        HBCell result = *DAT_0087F7E8.FUN_0056DC20(
                            &start, &cell, 2, DAT_0087F7E8.FUN_0056D230(&zoneCell, movement, 0), movement, 0, 1, 1, 1, 1, 0, 0,
                            &zeroCell, 0, 0);
                        if (result.X != DAT_0089C818.X || result.Y != DAT_0089C818.Y) {
                            HBCoord to;
                            to.X = result.X * 256 + 0x80;
                            to.Y = result.Y * 256 + 0x80;
                            to.Z = 0;
                            if (unit->vf_54(to, 0xA0)) {
                                goto unitPlaced;
                            }
                        }
                    }
                    {
                        HBCell zeroCell;
                        zeroCell.X = 0;
                        zeroCell.Y = 0;
                        HBCoord start = Location;
                        HBCell cell = BA3CellOf(start);
                        HBCell zoneCell = cell;
                        HBCell result = *DAT_0087F7E8.FUN_0056DC20(
                            &start, &cell, 2, DAT_0087F7E8.FUN_0056D230(&zoneCell, movement, 0), movement, 0, 1, 1, 0, 1, 0, 0,
                            &zeroCell, 0, 0);
                        if (result.X != DAT_0089C818.X || result.Y != DAT_0089C818.Y) {
                            HBCoord to;
                            to.X = result.X * 256 + 0x80;
                            to.Y = result.Y * 256 + 0x80;
                            to.Z = 0;
                            if (unit->vf_54(to, 0xA0)) {
                                goto unitPlaced;
                            }
                        }
                    }
                    Owner->FUN_004F9950(unit->unknown_6C4->vf_46(Owner, 1));
                    unit->vf_8(1);
                } else {
                unitPlaced:
                    unit->vf_122(10, 0);
                    unit->vf_123();
                }
            } else {
                Owner->FUN_004F9950(Type->unknown_EA0->vf_46(Owner, 1));
            }
        }
    }

    // The spawned object of the rules (a harvester-like helper), created while the counter is raised.
    if (!RulesInstance->unknown_17E8 && Type->unknown_154E && !flag) {
        ++DAT_00A8E7AC;
        BA3SpawnMem* mem = new BA3SpawnMem;
        if (mem) {
            BA3UnitView* helper = mem->FUN_00413D20(*RulesInstance->unknown_B5C, Owner);
            if (helper) {
                helper->vf_115(0);
                if (helper->vf_54(vf_18(), helper->FUN_00417FD0())) {
                    helper->vf_122(5, 0);
                    helper->vf_158(2, this);
                    vf_158(0x18, helper);
                }
            }
        }
        --DAT_00A8E7AC;
    }
}
