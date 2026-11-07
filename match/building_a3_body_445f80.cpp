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
#include "_layout/session_class.h"
#include "_layout/super_class.h"
#include "_layout/building_class.h"
#include "_layout/anim_class.h"
#include "_layout/light_source_class.h"
#include "_layout/unit_class.h"
#include "_layout/aircraft_class.h"

// The sound / animation name slot of a building type: nothing is played for a null or empty name.
// FUN_00451890 is reached through BuildingClass::PlayAnim(name, id, a, b, c).

// The 256-lepton cell a coordinate lies in.
inline CellStruct BA3CellOf(const CoordStruct& where)
{
    CellStruct cell;
    cell.X = (short)(where.X / 256);
    cell.Y = (short)(where.Y / 256);
    return cell;
}

// FUNCTION: GAMEMD 0x445F80
void BuildingClass::vf_311(char flag)
{
    if (ActuallyPlacedOnMap && !flag) {
        return;
    }

    if (Type->ProduceCashDelay) {
        CDTimerClass timer;
        timer.StartTime = DAT_00A8ED84;
        timer.TimeLeft = Type->ProduceCashDelay;
        CashProductionTimer = timer;
    }

    if (!ActuallyPlacedOnMap) {
        const char* name;
        if (Type->Refinery) {
            // Charge-up sounds: the stage is the charge in quarters.
            int stage = 0;
            if ((int)Tiberium.GetTotalAmount() != 0) {
                stage = ((int)Tiberium.GetTotalAmount() << 2) / Type->Storage;
            }
            StorageFilledSlots = stage;
            double ratio;
            int flagLow;
            if (stage >= 3) {
                ratio = FUN_005F5C60();
                if (ratio > RulesInstance->unknown_1700) {
                    name = Type->BuildingAnim[6].Anim;
                    flagLow = 0;
                } else {
                    name = Type->BuildingAnim[6].Damaged;
                    flagLow = 1;
                }
                if (name && *name) {
                    PlayAnim(name, 6, flagLow, 0, 0);
                }
            } else if (stage >= 2) {
                ratio = FUN_005F5C60();
                if (ratio > RulesInstance->unknown_1700) {
                    name = Type->BuildingAnim[5].Anim;
                    flagLow = 0;
                } else {
                    name = Type->BuildingAnim[5].Damaged;
                    flagLow = 1;
                }
                if (name && *name) {
                    PlayAnim(name, 5, flagLow, 0, 0);
                }
            } else if (stage >= 1) {
                ratio = FUN_005F5C60();
                if (ratio > RulesInstance->unknown_1700) {
                    name = Type->BuildingAnim[4].Anim;
                    flagLow = 0;
                } else {
                    name = Type->BuildingAnim[4].Damaged;
                    flagLow = 1;
                }
                if (name && *name) {
                    PlayAnim(name, 4, flagLow, 0, 0);
                }
            } else if (stage >= 0) {
                ratio = FUN_005F5C60();
                if (ratio > RulesInstance->unknown_1700) {
                    name = Type->BuildingAnim[3].Anim;
                    flagLow = 0;
                } else {
                    name = Type->BuildingAnim[3].Damaged;
                    flagLow = 1;
                }
                if (name && *name) {
                    PlayAnim(name, 3, flagLow, 0, 0);
                }
            }
        } else {
            // Health dependent sounds, one per condition slot.
            {
                double ratio = FUN_005F5C60();
                int low = ratio <= RulesInstance->unknown_1700;
                bool armed = vf_258() > 0;
                name = low ? Type->BuildingAnim[18].Damaged : (armed ? Type->BuildingAnim[18].Garrisoned : Type->BuildingAnim[18].Anim);
                if (name && *name) {
                    PlayAnim(name, 0x12, low, armed, 0);
                }
            }
            {
                double ratio = FUN_005F5C60();
                int low = ratio <= RulesInstance->unknown_1700;
                bool armed = vf_258() > 0;
                name = low ? Type->BuildingAnim[3].Damaged : (armed ? Type->BuildingAnim[3].Garrisoned : Type->BuildingAnim[3].Anim);
                if (name && *name) {
                    PlayAnim(name, 3, low, armed, 0);
                }
            }
            {
                double ratio = FUN_005F5C60();
                int flagLow;
                if (ratio > RulesInstance->unknown_1700) {
                    name = Type->BuildingAnim[4].Anim;
                    flagLow = 0;
                } else {
                    name = Type->BuildingAnim[4].Damaged;
                    flagLow = 1;
                }
                if (name && *name) {
                    PlayAnim(name, 4, flagLow, 0, 0);
                }
            }
            {
                double ratio = FUN_005F5C60();
                int flagLow;
                if (ratio > RulesInstance->unknown_1700) {
                    name = Type->BuildingAnim[5].Anim;
                    flagLow = 0;
                } else {
                    name = Type->BuildingAnim[5].Damaged;
                    flagLow = 1;
                }
                if (name && *name) {
                    PlayAnim(name, 5, flagLow, 0, 0);
                }
            }
            {
                double ratio = FUN_005F5C60();
                int flagLow;
                if (ratio > RulesInstance->unknown_1700) {
                    name = Type->BuildingAnim[6].Anim;
                    flagLow = 0;
                } else {
                    name = Type->BuildingAnim[6].Damaged;
                    flagLow = 1;
                }
                if (name && *name) {
                    PlayAnim(name, 6, flagLow, 0, 0);
                }
            }
        }

        if (Type->OrePurifier) {
            ++Owner->NumOrePurifiers;
        }
        if (Type->InfantryGainSelfHeal) {
            Owner->InfantrySelfHeal += Type->InfantryGainSelfHeal;
        }
        if (Type->UnitsGainSelfHeal) {
            Owner->UnitsSelfHeal += Type->UnitsGainSelfHeal;
        }
        if (Type->Helipad) {
            Owner->AirportDocks += Type->NumberOfDocks;
            DAT_0087F7E8.FUN_006A60E0(3);
        }

        // Super weapon timers of the owner that belong to this type: announce how long they still have to run.
        if (Type->SuperWeapon != -1) {
            for (int i = 0; i < Owner->Supers.Count; i++) {
                SuperClass* super = Owner->Supers.Items[i];
                if (super->Type->Type == Type->SuperWeapon) {
                    int remaining = super->RechargeTimer.TimeLeft;
                    if (super->RechargeTimer.StartTime != -1) {
                        int elapsed = DAT_00A8ED84 - super->RechargeTimer.StartTime;
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
                        name = low ? Type->BuildingAnim[16].Damaged : (armed ? Type->BuildingAnim[16].Garrisoned : Type->BuildingAnim[16].Anim);
                        if (name && *name) {
                            PlayAnim(name, 0x10, low, armed, 0);
                        }
                    } else {
                        double ratio = FUN_005F5C60();
                        int low = ratio <= RulesInstance->unknown_1700;
                        bool armed = vf_258() > 0;
                        name = low ? Type->BuildingAnim[14].Damaged : (armed ? Type->BuildingAnim[14].Garrisoned : Type->BuildingAnim[14].Anim);
                        if (name && *name) {
                            PlayAnim(name, 0xE, low, armed, 0);
                        }
                    }
                }
            }
        }

        if (vf_255() && !Type->TurretAnimIsVoxel) {
            int previous = unknown_5FC;
            if (previous == -1) {
                name = Type->BuildingAnim[9].Anim;
                if (name && *name) {
                    PlayAnim(name, 9, 0, 0, 0);
                }
            } else {
                unknown_5FC = -1;
                if (!Type->TurretAnimIsVoxel) {
                    DestroyNthAnim(9);
                    char buffer[0x40];
                    strcpy(buffer, Type->ImageFile);
                    strcat(buffer, DAT_00818D7C);
                    buffer[strlen(buffer)] = (char)(previous + 'B');
                    buffer[strlen(buffer) + 1] = 0;
                    PlayAnim(buffer, 9, 0, 0, 0);
                    unknown_5FC = previous;
                }
            }
            if (vf_255() && Anims[9]) {
                DirStruct facing = PrimaryFacing.FUN_004C93D0();
                if (Anims[9]) {
                    Anims[9]->Value = DAT_007F4890[(facing.Whole >> 10) + 1 >> 1 & 0x1F];
                    Anims[9]->Step = 0;
                }
            }
        }

        if (Type->LightIntensity) {
            if (!LightSource) {
                BA3LightMem* mem = new BA3LightMem;
                if (mem) {
                    LightSource = mem->FUN_00554760(vf_18(), Type->LightVisibility, Type->LightIntensity, Type->LightRedTint,
                                                    Type->LightGreenTint, Type->LightBlueTint);
                } else {
                    LightSource = 0;
                }
            }
            LightSource->Activate(0);
        }

        if (Type->LaserFencePost) {
            CreateEndPost(false);
        }
        if (Type->SensorArray) {
            vf_317(DAT_0089C818);
        }
        if (Type->DetectDisguise) {
            vf_319(DAT_0089C818);
        }
        IsReadyToCommence = 1;
    }

    if (Type->Powered) {
        FUN_004547C0();
    }

    if (Type->RevealToAll && !Owner->IsControlledByCurrentPlayer()) {
        if (!flag) {
            vf_290(0, 0, 1, DAT_00A83D4C, 0);
            CoordStruct where = Location;
            DAT_0087F7E8.FUN_00567DA0(&where, 0, LastSightRange + 3, 0);
        }
        CellStruct cell;
        cell.X = (short)(Location.X / 256);
        cell.Y = (short)(Location.Y / 256);
        ((BA3EvaView*)12)->FUN_0065FA70(cell);
    }

    // The EVA announcement of a super weapon building.
    if (!Owner->IsControlledByCurrentPlayer() && !Owner->IsAlliedWith(DAT_00A83D4C) && DAT_00A8B538 == 0 && Session_00A8B238.GameMode
        && (Type->SuperWeapon == -1 || DAT_00A83CBC[Type->SuperWeapon]->unknown_28->unknown_C8 == 0
            || Owner->ActiveBuildingTypes.FUN_0049FAE0(DAT_00A83CBC[Type->SuperWeapon]->unknown_28->unknown_C8->unknown_DF8) != 0)) {
        const char* eva;
        switch (Type->SuperWeapon) {
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
    if (Type->WeaponsFactory && Type->Naval && ArchiveTarget == 0) {
        CellStruct zero;
        zero.X = 0;
        zero.Y = 0;
        CellStruct start;
        CellStruct found = *DAT_0087F7E8.FUN_0056DC20(&start, vf_110(), 5, -1, 10, 0, 5, 5, 0, 0, 0, 1, zero, 0, 0);
        CellStruct moved;
        moved.X = found.X + 2;
        moved.Y = found.Y + 2;
        if (moved.X != DAT_0089C818.X || moved.Y != DAT_0089C818.Y) {
            FUN_00443860(&moved, 0);
        }
    }

    Owner->RecheckTechTree = 1;
    ActuallyPlacedOnMap = 1;
    Owner->RecheckPower = 1;
    Owner->RecheckRadar = 1;
    if (vf_33()->GapGenerator) {
        vf_261();
    }

    // The free unit of the building type.
    if (Type->FreeUnit && DAT_00A8E7AC == 0 && !flag && !DAT_00A8ED6B) {
        if (!Owner->IsControlledByHuman() || !Value || Value > Type->FreeUnit->vf_43()) {
            CoordStruct at = vf_18();
            CellStruct base;
            base.X = (short)(at.X / 256);
            base.Y = (short)(at.Y / 256);
            CellStruct spot;
            spot.X = base.X + DAT_0089F698.X;
            spot.Y = base.Y + DAT_0089F698.Y;
            BA3UnitMem* mem = new BA3UnitMem;
            UnitClass* unit;
            if (mem) {
                unit = mem->FUN_007353C0(Type->FreeUnit, Owner);
            } else {
                unit = 0;
            }
            if (unit) {
                CoordStruct target;
                target.X = spot.X * 256 + 0x80;
                target.Y = spot.Y * 256 + 0x80;
                target.Z = 0;
                if (!unit->vf_54(target, 0xC0)) {
                    // Not placeable there: let the cell search look around the building, twice with different options.
                    int movement = unit->Type->MovementZone;
                    {
                        CellStruct zeroCell;
                        zeroCell.X = 0;
                        zeroCell.Y = 0;
                        CoordStruct loc = Location;
                        CellStruct cell = BA3CellOf(loc);
                        CellStruct start;
                        CellStruct zoneCell = cell;
                        CellStruct result = *DAT_0087F7E8.FUN_0056DC20(
                            &start, &cell, 2, DAT_0087F7E8.FUN_0056D230(&zoneCell, movement, 0), movement, 0, 1, 1, 1, 1, 0, 0,
                            &zeroCell, 0, 0);
                        if (result.X != DAT_0089C818.X || result.Y != DAT_0089C818.Y) {
                            CoordStruct to;
                            to.X = result.X * 256 + 0x80;
                            to.Y = result.Y * 256 + 0x80;
                            to.Z = 0;
                            if (unit->vf_54(to, 0xA0)) {
                                goto unitPlaced;
                            }
                        }
                    }
                    {
                        CellStruct zeroCell;
                        zeroCell.X = 0;
                        zeroCell.Y = 0;
                        CoordStruct loc = Location;
                        CellStruct cell = BA3CellOf(loc);
                        CellStruct start;
                        CellStruct zoneCell = cell;
                        CellStruct result = *DAT_0087F7E8.FUN_0056DC20(
                            &start, &cell, 2, DAT_0087F7E8.FUN_0056D230(&zoneCell, movement, 0), movement, 0, 1, 1, 0, 1, 0, 0,
                            &zeroCell, 0, 0);
                        if (result.X != DAT_0089C818.X || result.Y != DAT_0089C818.Y) {
                            CoordStruct to;
                            to.X = result.X * 256 + 0x80;
                            to.Y = result.Y * 256 + 0x80;
                            to.Z = 0;
                            if (unit->vf_54(to, 0xA0)) {
                                goto unitPlaced;
                            }
                        }
                    }
                    Owner->GiveMoney(unit->Type->vf_46(Owner, 1));
                    delete unit;
                } else {
                unitPlaced:
                    unit->vf_122(10, 0);
                    unit->vf_123();
                }
            } else {
                Owner->GiveMoney(Type->FreeUnit->vf_46(Owner, 1));
            }
        }
    }

    // The spawned object of the rules (a harvester-like helper), created while the counter is raised.
    if (!RulesInstance->unknown_17E8 && Type->HoverPad && !flag) {
        ++DAT_00A8E7AC;
        BA3SpawnMem* mem = new BA3SpawnMem;
        if (mem) {
            AircraftClass* helper = mem->FUN_00413D20(*RulesInstance->unknown_B5C, Owner);
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
