// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Slot 64 of the building-a2 cluster: the exit step that lets a newly produced object leave the building
//   (BuildingClass::Exit_Object). Read from the retail gamemd.exe v1.001 from its entry to its last RET with a
//   LINEAR decode of the retail bytes (Ghidra's function-flow listing drops instructions after some calls);
//   offsets are pinned in building_a2_views.h. Method names are slot labels (vf_N = primary-table byte offset / 4).
//   The result is 0 (not placed), 1 (queued) or 2 (placed). The object kinds (slot 11) are 1 and 15 (the
//   free-roaming kinds), 2 (the vehicle kind) and 6 (the building kind).

#include "building_a2_views.h"
extern int DAT_00A8B238;

// The cell of a coordinate (leptons / 256, rounding towards zero like the original's signed shift).
static inline HBCell BA2CellOf(const HBCoord* c)
{
    return HBCell(c->X / 256, c->Y / 256);
}

// The cell centre as a coordinate.
static inline HBCoord BA2CentreOf(const HBCell& c)
{
    HBCoord r;
    r.X = c.X * 256 + 128;
    r.Y = c.Y * 256 + 128;
    r.Z = 0;
    return r;
}

// CAPPED (partial, readable): 58.2% of the retail instructions align (67.3% with stack offsets ignored; 81.5% with
// registers also ignored). Remaining delta: retail funnels eleven exits through one `--counter; return 2` block (0x444971),
// seven through `--counter; return 0` (0x444EDE) and sixteen through the shared `return 0` (0x445696), ours repeats them
// inline; register choice of the constants 0 / 1 in the 15-argument cell search call; scheduling of the exit-offset
// additions. A goto-label version of the two counter exits was started once and dropped before it compiled to the same
// instruction count (inconclusive, not proven either way).
// FUNCTION: GAMEMD 0x443C60
int BA2Building::vf_64(BA2Other* obj, HBCell where)
{
    if (!obj) {
        return 0;
    }
    obj->unknown_3D5 = 1;
    BA2Other* vehicle = obj->vf_11() == 2 ? obj : 0;

    switch (obj->vf_11()) {
    case 2:
        Owner->FUN_00509700(2);
        Owner->unknown_5658 = -1;
        if (FUN_0065ADF0(obj) || (Owner->FUN_0053A130() && !vehicle->unknown_6C4->unknown_E0D)) {
            vehicle->FUN_005F6060(0);
            ++DAT_00A8E7AC;
            if (Owner->FUN_0053A130()) {
                HBCell spot = vehicle->FUN_00703590(this);
                HBCoord at = BA2CentreOf(spot);
                if (!vehicle->vf_54(&at, vehicle->FUN_00417FD0())) {
                    --DAT_00A8E7AC;
                    return 0;
                }
            } else {
                HBCoord out;
                if (!vehicle->vf_54(vf_42(&out, vehicle), vehicle->FUN_00417FD0())) {
                    --DAT_00A8E7AC;
                    return 0;
                }
                vf_158(2, vehicle);
                vf_158(0x18, vehicle);
                HBCoord out2;
                vehicle->vf_109(vf_42(&out2, vehicle));
                vehicle->unknown_6CC = this;
                if (unknown_218 && !vehicle->unknown_6C4->unknown_E0D) {
                    vehicle->vf_288(unknown_218, 1);
                    vehicle->vf_122(2, 0);
                }
            }
            --DAT_00A8E7AC;
            return 2;
        }
        if (!vehicle->unknown_6C4->unknown_E0D) {
            HBCell cE8(DAT_0087F8E8, DAT_0087F8E8);
            HBCell cE4(DAT_0087F8E4, -DAT_0087F8E4);
            HBCell u = cE4 + HBCell(1, DAT_0087F8DC) + cE8;
            HBCoord tmp;
            HBCell here = BA2CellOf(vf_18(&tmp));
            HBCell target;
            if ((short)(here.X - u.X) - (short)(here.Y - u.Y) > DAT_0087F8EC) {
                target = HBCell(u.X - 1, u.Y) + HBCell(DAT_0087F8EC, -DAT_0087F8EC);
            } else {
                target = HBCell(u.X - 1, u.Y);
            }
            int jitter = DAT_00A8B230->unknown_0218.RandomRanged(0, DAT_0087F8F0);
            target.X += jitter;
            target.Y += jitter;
            ++DAT_00A8E7AC;
            HBCoord at = BA2CentreOf(target);
            if (!vehicle->vf_54(&at, 0)) {
                --DAT_00A8E7AC;
                return 0;
            }
            if (unknown_218) {
                vehicle->vf_288(unknown_218, 1);
                vehicle->vf_124(2);
            } else {
                HBCell spot = vehicle->FUN_00703590(this);
                if (spot.X == DAT_0089C818.X && spot.Y == DAT_0089C818.Y) {
                    vehicle->vf_288(0, 1);
                    vehicle->vf_124(2);
                } else {
                    vehicle->vf_288(DAT_0087F7E8.FUN_005657A0(&spot), 1);
                    vehicle->vf_124(2);
                }
            }
            --DAT_00A8E7AC;
            return 2;
        }
        return 0;
    case 1:
    case 0xF:
        if (!Type->unknown_16C1 && !Type->unknown_16C2 && !Type->unknown_16BD && !FUN_0065ADC0()) {
            return 1;
        }
        if (!Type->unknown_16C1 && !Type->unknown_16C2) {
            Owner->FUN_00509700(obj->vf_11());
            if (obj->vf_11() == 1) {
                Owner->unknown_5650 = -1;
            }
            if (obj->vf_11() == 0xF) {
                Owner->unknown_5654 = -1;
            }
        }
        if (!Type->unknown_16BB && !Type->unknown_16BC) {
            if (Type->unknown_16BD) {
                if (Type->unknown_CCE) {
                    if (!FUN_0065AE30()) {
                        vf_122(0x10, 0);
                    }
                    HBCoord tmp;
                    HBCell here = BA2CellOf(vf_18(&tmp));
                        if (unknown_218) {
                        HBCoord tmp1;
                        HBCell target = BA2CellOf(unknown_218->vf_18(&tmp1));
                        HBCell base = vf_110();
                        BA2Dir angle;
                        angle.Raw = (short)(int)((FUN_004CAE30((double)(target.Y - base.Y), (double)(target.X - base.X))
                                                  - DAT_007E2820) * DAT_007E2818);
                        int dir = ((angle.Whole >> 12) + 1 >> 1) & 7;
                        if (DAT_0087F7E8.FUN_005657A0(&here)->FUN_0047C520() == this) {
                            do {
                                here = here + DAT_0089F688[dir & 7];
                            } while (DAT_0087F7E8.FUN_005657A0(&here)->FUN_0047C520() == this);
                        }
                    }
                    HBCell spare[2];
                    spare[0] = HBCell(0, 0);
                    spare[1] = HBCell(0, 0);
                    if (!unknown_218 || DAT_0087F7E8.FUN_005657A0(&here)->unknown_EC != 2
                        || DAT_0087F7E8.FUN_005657A0(&here)->FUN_0047C3D0(spare, 0, 0) != 0
                        || !DAT_0087F7E8.FUN_00578460(&here, 1)) {
                        HBCell none(0, 0);
                    HBCell searched[2];
                    HBCoord tmp2;
                    HBCell origin = BA2CellOf(vf_18(&tmp2));
                    here = *DAT_0087F7E8.FUN_0056DC20(searched, &origin, obj->vf_33()->unknown_67C, -1, 0, 0, 1, 1, 0, 0, 0, 1,
                                                      &none, 0, 0);
                }
                HBCoord spotTmp;
                    if (!obj->vf_54(DAT_0087F7E8.FUN_005657A0(&here)->vf_18(&spotTmp), 0x40)) {
                        return 0;
                    }
                    if (unknown_218) {
                        obj->vf_288(unknown_218, 1);
                        obj->vf_122(2, 0);
                    }
                    obj->vf_73(0);
                    HBCoord spot2;
                    obj->vf_109(DAT_0087F7E8.FUN_005657A0(&here)->FUN_00480A30(&spot2));
                    obj->vf_73(1);
                    return 2;
                }
                obj->FUN_0070C610(unknown_218);
                if (vf_97() == 0x10) {
                    int n = Owner->unknown_78;
                    for (int i = 0; i < n; i++) {
                        BA2Building* other = Owner->unknown_6C[i];
                        if (other->Type == Type && other != this && other->vf_97() == 5 && !other->unknown_524) {
                            int saved = unknown_524;
                            other->unknown_524 = saved;
                            unknown_524 = 0;
                            int result = other->vf_64(obj, DAT_0089C818);
                            other->unknown_524 = 0;
                            unknown_524 = saved;
                            return result;
                        }
                    }
                    return 1;
                }
                ++DAT_00A8E7AC;
                HBCoord out;
                if (!obj->vf_54(vf_45(&out, 0), 0x40)) {
                    --DAT_00A8E7AC;
                    return 0;
                }
                obj->vf_73(0);
                HBCoord out2;
                obj->vf_109(vf_45(&out2, 0));
                obj->vf_73(1);
                vf_158(2, obj);
                vf_158(0x18, obj);
                vf_122(0x10, 0);
                --DAT_00A8E7AC;
                return 2;
            }
            if (Type->unknown_EB8 != 0x10 && !Type->unknown_16C1 && !Type->unknown_16C2 && !Type->unknown_16AC) {
                HBCell c = vf_309(obj, where);
                if (c.X == DAT_0089C818.X && c.Y == DAT_0089C818.Y) {
                    return 0;
                }
                HBCoord centre = BA2CentreOf(c);
                HBCoord tmp;
                HBCoord* p = vf_18(&tmp);
                BA2Dir angle;
                angle.Raw = (short)(int)((FUN_004CAE30((double)p->Y - (double)centre.Y, (double)centre.X - (double)p->X)
                                          - DAT_007E2820) * DAT_007E2818);
                int facing = ((angle.Whole >> 7) + 1 >> 1) & 0xFF;
                HBCell base = vf_110();
                HBCell edge = c;
                if (edge.X < Type->FUN_0045EC90() + base.X) {
                    if (edge.X < base.X) {
                        edge.X++;
                    }
                } else {
                    edge.X--;
                }
                if (edge.Y < Type->FUN_0045ECA0(0) + base.Y) {
                    if (edge.Y < base.Y) {
                        edge.Y++;
                    }
                } else {
                    edge.Y--;
                }
                HBCoord exitAt = BA2CentreOf(edge);
                if (Type->unknown_16E4 && c.X == base.X + 1 && c.Y == base.Y + 2) {
                    exitAt.X += Type->ExitOffset.X;
                    exitAt.Y += Type->ExitOffset.Y;
                    exitAt.Z += Type->ExitOffset.Z;
                }
                if (Type->unknown_16E5 && c.X == base.X + 2 && c.Y == base.Y + 2) {
                    exitAt.X += Type->ExitOffset.X;
                    exitAt.Y += Type->ExitOffset.Y;
                    exitAt.Z += Type->ExitOffset.Z;
                }
                if (Type->unknown_16E6 && c.X == base.X + 2 && c.Y == base.Y + 1) {
                    exitAt.X += Type->ExitOffset.X;
                    exitAt.Y += Type->ExitOffset.Y;
                    exitAt.Z += Type->ExitOffset.Z;
                }
                ++DAT_00A8E7AC;
                if (!obj->vf_54(&exitAt, facing)) {
                    --DAT_00A8E7AC;
                    return 0;
                }
                obj->vf_122(2, 0);
                obj->vf_288(DAT_0087F7E8.FUN_005657A0(&c), 1);
                if (!Owner->FUN_0050B730()) {
                    obj->vf_122(0xB, 0);
                    HBCell q = Owner->FUN_00500200(obj);
                    if ((q.X == DAT_0089C818.X && q.Y == DAT_0089C818.Y) || !Type->unknown_EB8) {
                        obj->FUN_0070C610(0);
                    } else {
                        obj->FUN_0070C610(DAT_0087F7E8.FUN_005657A0(&q));
                    }
                }
                --DAT_00A8E7AC;
                return 2;
            }
            obj->FUN_0070C610(unknown_218);
            {
                HBCell c = vf_309(obj, DAT_0089C818);
                if (c.X == DAT_0089C818.X && c.Y == DAT_0089C818.Y) {
                    return 0;
                }
                if (Type->unknown_EB8 == 0 && !Type->unknown_16AC) {
                    BA2Type* objType = obj->vf_33();
                    for (int i = 0; i < Owner->unknown_108; i++) {
                        BA2Building* other = Owner->unknown_FC[i];
                        other->vf_64(objType->vf_35(other->Owner), DAT_0089C818);
                    }
                }
                HBCoord centre = BA2CentreOf(c);
                HBCoord tmp;
                HBCoord* p = vf_18(&tmp);
                BA2Dir angle;
                angle.Raw = (short)(int)((FUN_004CAE30((double)p->Y - (double)centre.Y, (double)centre.X - (double)p->X)
                                          - DAT_007E2820) * DAT_007E2818);
                int facing = ((angle.Whole >> 7) + 1 >> 1) & 0xFF;
                HBCell base = vf_110();
                HBCell edge = c;
                if (edge.X < Type->FUN_0045EC90() + base.X) {
                    if (edge.X < base.X) {
                        edge.X++;
                    }
                } else {
                    edge.X--;
                }
                if (edge.Y < Type->FUN_0045ECA0(0) + base.Y) {
                    if (edge.Y < base.Y) {
                        edge.Y++;
                    }
                } else {
                    edge.Y--;
                }
                HBCoord exitAt = BA2CentreOf(edge);
                if (Type->unknown_16E4 && c.X == base.X + 1 && c.Y == base.Y + 2) {
                    exitAt.X += Type->ExitOffset.X;
                    exitAt.Y += Type->ExitOffset.Y;
                    exitAt.Z += Type->ExitOffset.Z;
                }
                if (Type->unknown_16E5 && c.X == base.X + 2 && c.Y == base.Y + 2) {
                    exitAt.X += Type->ExitOffset.X;
                    exitAt.Y += Type->ExitOffset.Y;
                    exitAt.Z += Type->ExitOffset.Z;
                }
                if (Type->unknown_16E6 && c.X == base.X + 2 && c.Y == base.Y + 1) {
                    exitAt.X += Type->ExitOffset.X;
                    exitAt.Y += Type->ExitOffset.Y;
                    exitAt.Z += Type->ExitOffset.Z;
                }
                ++DAT_00A8E7AC;
                if (!obj->vf_54(&exitAt, facing)) {
                    --DAT_00A8E7AC;
                    return 0;
                }
                if (obj->unknown_5A4 && !obj->vf_33()->unknown_D94 && !obj->vf_33()->unknown_CD4) {
                    if (obj->unknown_5A4) {
                        obj->FUN_0070C610(obj->unknown_5A4);
                    }
                    obj->vf_122(2, 0);
                    obj->vf_288(DAT_0087F7E8.FUN_005657A0(&c), 1);
                }
                if (!Owner->FUN_0050B730() || Type->unknown_16C1) {
                    obj->vf_122(0xB, 0);
                    HBCell q = Owner->FUN_00500200(obj);
                    if ((q.X == DAT_0089C818.X && q.Y == DAT_0089C818.Y) || !Type->unknown_EB8) {
                        obj->FUN_0070C610(0);
                    } else {
                        obj->FUN_0070C610(DAT_0087F7E8.FUN_005657A0(&q));
                        obj->FUN_004DA0E0(DAT_0087F7E8.FUN_005657A0(&q));
                    }
                }
                if (vf_158(2, obj) == 1) {
                    vf_158(9, obj);
                }
                --DAT_00A8E7AC;
                return 2;
            }
        } else {
                if (obj->vf_11() != 1) {
                    obj->vf_93(&DAT_0089C848, 1, 0);
                    return 0;
                }
                HBCoord tmp;
                HBCell cell = BA2CellOf(vf_18(&tmp));
                cell = cell + DAT_0089F69C;
                ++DAT_00A8E7AC;
                HBCell spot = cell + DAT_0089F698;
                HBCoord at = BA2CentreOf(spot);
                if (obj->vf_54(&at, 0xA0)) {
                    BA2Dir dir;
                    dir.Raw = 0x8000;
                    obj->Facing.FUN_004C9300(&dir);
                    obj->vf_122(0xA, 0);
                }
                --DAT_00A8E7AC;
                return 0;
        }
    case 6:
        {
            if (Owner->FUN_0050B730()) {
                return 0;
            }
            Owner->FUN_00509700(6);
            Owner->unknown_564C = -1;
            BA2Type* objType = obj->Type;
            BA2Entry* entry = Owner->unknown_5700.FUN_0042EB20(objType->unknown_DF8);
            HBCoord pos;
            pos.X = 0;
            pos.Y = 0;
            pos.Z = 0;
            if (!entry || (entry->Cell.X == 0 && entry->Cell.Y == 0)) {
                if (!objType->unknown_E88) {
                    pos = BA2CentreOf(Owner->FUN_005060B0(objType, FUN_00505F80, -1));
                } else {
                    HBCell found = Owner->FUN_00506B90(objType);
                    if (!(found.X == DAT_0089C818.X && found.Y == DAT_0089C818.Y)) {
                        pos = BA2CentreOf(found);
                    }
                }
                if (entry && !(pos.X == DAT_0089C848.X && pos.Y == DAT_0089C848.Y && pos.Z == DAT_0089C848.Z)) {
                    entry->Cell = BA2CellOf(&pos);
                }
            } else if (!objType->unknown_E88 && !Owner->FUN_0050B760(objType, &entry->Cell)) {
                pos = BA2CentreOf(Owner->FUN_005060B0(objType, FUN_00505F80, -1));
                if (pos.X == DAT_0089C848.X && pos.Y == DAT_0089C848.Y && pos.Z == DAT_0089C848.Z) {
                    return 0;
                }
                entry->Cell = BA2CellOf(&pos);
            } else {
                pos = BA2CentreOf(entry->Cell);
            }
            if (!(pos.X == DAT_0089C848.X && pos.Y == DAT_0089C848.Y && pos.Z == DAT_0089C848.Z)) {
                HBCell destination = BA2CellOf(&pos);
                switch (obj->vf_34()->FUN_0045EE70(&destination, Owner)) {
                case 1:
                    {
                        int value = Owner->unknown_5700.FUN_0042F380(entry);
                        if (DAT_00A8B238 && value > RulesInstance_8871E0->unknown_E48 && entry) {
                            Owner->unknown_5700.List.RemoveAt(Owner->unknown_5700.List.vf_5(entry));
                        }
                        return 1;
                    }
                case 0:
                    if (obj->vf_54(&pos, 0)) {
                        if (obj->unknown_2D8) {
                            obj->unknown_2D8->FUN_006B0D60();
                        }
                        if (entry && objType->unknown_DF8 == Owner->unknown_564C) {
                            Owner->unknown_564C = -1;
                        }
                        if (obj->unknown_AC == -1 && obj->unknown_B4 == 0x12) {
                            obj->vf_123();
                        }
                        if (obj->vf_11() == 6) {
                            BA2Type* t = obj->Type;
                            if (t->unknown_16C0) {
                                HBCell c = BA2CellOf(&pos);
                                DAT_0087F7E8.FUN_00588570(&c, Owner, t);
                            } else if (t->unknown_E54 && t->unknown_E54->unknown_2A8) {
                                HBCell c = BA2CellOf(&pos);
                                DAT_0087F7E8.FUN_00588750(&c, Owner, t);
                            }
                        }
                        if (obj->Type == RulesInstance_8871E0->unknown_87C) {
                            BA2EntryList& list = Owner->unknown_5700.List;
                            for (int j = list.vf_5(entry) + 1; j < list.Count; j++) {
                                BA2Entry* e = &list.Items[j];
                                if (e->Key >= 0 && DAT_00A83C6C[e->Key]->unknown_1706) {
                                    e->Cell = BA2CellOf(&obj->Location);
                                    break;
                                }
                            }
                        }
                        return 2;
                    }
                    // fall through
                case 2:
                    if (!entry) {
                        return 0;
                    }
                    {
                        int index = Owner->unknown_5700.List.vf_5(entry);
                        BA2Type* entryType = DAT_00A83C6C[entry->Key];
                        if (entryType->unknown_1571 || entryType->unknown_16B7) {
                            Owner->unknown_5700.List.RemoveAt(index);
                        } else {
                            HBCell wanted = BA2CellOf(&pos);
                            for (int i = 0; i < Owner->unknown_5700.List.Count; i++) {
                                BA2Entry* e = &Owner->unknown_5700.List.Items[i];
                                if (e->Cell.X == wanted.X && e->Cell.Y == wanted.Y) {
                                    e->Cell = HBCell(0, 0);
                                }
                            }
                        }
                        return 0;
                    }
                default:
                    return 0;
                }
            } else {
                if (objType->unknown_E88 && Owner->unknown_5700.FUN_0042EB20(-1) == entry) {
                    Owner->unknown_5700.List.RemoveAt(Owner->unknown_5700.FUN_0042EB50(-1));
                }
                return 0;
            }
        }
    }
    return 0;
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0xA8B238
int DAT_00A8B238;
// END defined globals
