// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Slot 146 of the building-a2 cluster: the sell mission step (BuildingClass::Mission_Deconstruction). Read from
//   the retail gamemd.exe v1.001 from its entry to its last RET with a LINEAR decode of the retail bytes
//   (Ghidra's function-flow listing drops instructions after some calls); offsets are pinned in
//   building_a2_views.h. Method names are slot labels (vf_N = primary-table byte offset / 4). The status at +0xBC
//   runs 0 (start the sell animation), 1 (unload the occupants and spawn the cargo), 2 (the final replacement).

#include "building_a2_views.h"
#include "../../_layout/session_class.h"

// The condition under which the sale produces a replacement unit (the unit type exists and, for the
// network-synchronised kind, the local multiplayer conditions hold).
inline bool BA2Building::SpawnsUnit()
{
    return Type->unknown_408
        && (!Type->unknown_16B9
            || (Session_00A8B238.GameMode && unknown_218 && Owner->FUN_0050B730() && Session_00A8B238.GameMode && DAT_00A8B320 && !unknown_2C0));
}

// CAPPED (partial, readable): 80.1% of the retail instructions align (88.8% with stack offsets ignored). Remaining
// delta: the occupant lookups read the returned cell through its pointer in retail (ours copies the dword), a few
// schedule/register differences in the coordinate arithmetic of the three spawn loops, and the failure paths of the
// occupant release that retail merges into one block.
// FUNCTION: GAMEMD 0x449C30
int BA2Building::vf_146()
{
    vf_103(0);
    unsigned char wasSold = unknown_83;
    int i;

    switch (unknown_BC) {
    case 0:
        if (SpawnsUnit()) {
            if (Type->unknown_16CA || Type->unknown_16C4) {
                vf_242(0);
            }
        }
        if (SpawnsUnit() && Type->unknown_408) {
            vf_219();
            if (vf_33()->unknown_56C != -1) {
                HBCoord where = Location;
                FUN_007509E0(vf_33()->unknown_56C, &where, 0);
            }
        }
        if (unknown_2D8) {
            if (unknown_218 != vf_111() && unknown_218 && unknown_218->vf_11() == 0xB) {
                BA2Tether* tether = !unknown_218 ? 0 : (unknown_218->vf_11() == 0xB ? unknown_218 : 0);
                if (tether->unknown_EC == 5) {
                    unknown_2D8->FUN_006B0DB0();
                }
            }
        }
        if (unknown_2E4) {
            FUN_004593A0();
        }
        if (unknown_702) {
            BA2Obj* upgrade = UpgradeSlots[unknown_702]->vf_35(Owner);
            Owner->FUN_004F9950(upgrade->vf_175());
            if (upgrade) {
                upgrade->vf_8(1);
            }
            FUN_00451690();
            Owner->unknown_5778 = 1;
            Owner->unknown_5779 = 1;
            if (unknown_41A) {
                FUN_00752700(s_EVA_StructureSold_00819030, -1, -1);
            }
            vf_122(5, 0);
            return 1;
        }
        unknown_6DD = 0;
        vf_160(0x17);
        if (Type->unknown_16BE) {
            FUN_004533A0(0);
        }
        for (i = 0; i < 8; i++) {
            if (DamageFireAnims[i]) {
                DamageFireAnims[i]->vf_62();
                DamageFireAnims[i] = 0;
            }
        }
        unknown_BC = 1;
        break;
    case 1:
        {
            vf_160(3);
            if (unknown_418) {
                break;
            }
            if (!unknown_218 || !Type->unknown_408) {
                int cargo = vf_180();
                bool changed = false;
                HBCell* cells = vf_66(0);
                int count = 0;
                for (HBCell* c = cells; !(c->X == 0x7FFF && c->Y == 0x7FFF); c++) {
                    count++;
                }
                HBCell base = vf_110();
                if ((Type->unknown_16AE || Type->unknown_16AF) && unknown_114.Count > 0) {
                    BA2Infantry* inf = unknown_114.FUN_00473430();
                    while (inf) {
                        HBCell* offset = cells++;
                        HBCoord pos;
                        pos.X = (short)(offset->X + base.X) * 256 + 128;
                        pos.Y = (short)(offset->Y + base.Y) * 256 + 164;
                        pos.Z = 0;
                        if (inf->vf_11() == 1) {
                            HBCoord tmp;
                            pos = *DAT_0087F7E8.FUN_00565730(&pos)->vf_18(&tmp);
                        } else {
                            HBCoord out;
                            pos = *DAT_0087F7E8.FUN_00565730(&pos)->FUN_00481180(&out, &pos, 0, 0, 0);
                        }
                        ++DAT_00A8E7AC;
                        inf->unknown_8C = unknown_8C;
                        HBCoord at = Location;
                        HBCoord tmp2;
                        at.Z = vf_111()->vf_18(&tmp2)->Z;
                        if (!unknown_6E0) {
                            BA2Dir facing;
                            BA2Dir* current = Facing.FUN_004C93D0(&facing);
                            if (inf->vf_54(&at, ((current->Whole >> 7) + 1 >> 1) & 0xFF)) {
                                if (!inf->unknown_438) {
                                    inf->Owner->unknown_2F4++;
                                    inf->unknown_438 = 1;
                                }
                                inf->unknown_439 = 0;
                                inf->vf_93(&DAT_0089C848, 1, 0);
                                if (!Owner->FUN_0050B730()) {
                                    inf->vf_122(0xF, 0);
                                }
                            } else {
                                inf->vf_56(0);
                                inf->vf_8(1);
                            }
                        } else {
                            inf->vf_56(0);
                            inf->vf_8(1);
                        }
                        --DAT_00A8E7AC;
                        inf = unknown_114.FUN_00473430();
                    }
                }
                HBCell* cells2 = vf_66(0);
                if (vf_258() > 0) {
                    FUN_00457DE0(0, 1);
                }
                for (int n = cargo; n != 0; n--) {
                    BA2InfSize* kind = vf_195();
                    if (kind->unknown_EC3) {
                        do {
                            if (!changed) {
                                break;
                            }
                            kind = vf_195();
                        } while (kind->unknown_EC3);
                        if (kind->unknown_EC3) {
                            changed = true;
                        }
                    }
                    if (kind) {
                        BA2Infantry* soldier = new BA2Infantry(kind, Owner);
                        if (soldier) {
                            ++DAT_00A8E7AC;
                            HBCell* offset = cells2 + DAT_00A8B230->unknown_0218.RandomRanged(0, count - 1);
                            HBCell here = vf_110();
                            HBCoord pos;
                            pos.X = (short)(offset->X + here.X) * 256 + 128;
                            pos.Y = (short)(offset->Y + here.Y) * 256 + 164;
                            pos.Z = 0;
                            HBCoord out;
                            HBCoord target = *DAT_0087F7E8.FUN_00565730(&pos)->FUN_00481180(&out, &pos, 0, 0, 0);
                            if (!(target.X == DAT_0089C848.X && target.Y == DAT_0089C848.Y && target.Z == DAT_0089C848.Z)
                                && soldier->vf_54(&target, 0)) {
                                if (soldier->unknown_6C0->unknown_C9E) {
                                    soldier->unknown_6D9 = 1;
                                }
                                --DAT_00A8E7AC;
                                soldier->vf_93(&DAT_0089C848, 1, 0);
                                ++DAT_00A8E7AC;
                                soldier->vf_122(2, 0);
                            } else {
                                soldier->vf_8(1);
                            }
                            --DAT_00A8E7AC;
                        }
                    }
                }
            }
            if (Owner->FUN_0050B6F0() && !vf_32()) {
                if (!SpawnsUnit()) {
                    HBCoord where = Location;
                    FUN_007509E0(RulesInstance_8871E0->unknown_6A4, &where, 0);
                }
                if (Type->unknown_E70 != -1) {
                    HBCoord where = Location;
                    FUN_007509E0(Type->unknown_E70, &where, &Audio);
                }
            }
            unknown_BC = 2;
            FUN_00447780(0);
            unknown_6DD = 0;
            if (wasSold) {
                vf_83();
                return 1;
            }
        }
        break;
    case 2:
        {
            HBCoord here = Location;
            FUN_00750D40(&here, &Audio);
            if (!unknown_6DD) {
                break;
            }
            Owner->unknown_1FC = 1;
            vf_242(0);
            if (unknown_41A && !Type->unknown_408) {
                FUN_00752700(s_EVA_StructureSold_00819030, -1, -1);
            }
            if (SpawnsUnit()) {
                BA2Dir turretDir, facingDir;
                if (Type->unknown_16CA) {
                    if ((unsigned short)((unsigned char)Type->unknown_1710 << 8) != Turret.FUN_004C93D0(&turretDir)->Raw
                        || (unsigned short)((unsigned char)Type->unknown_ED8 << 8) != Facing.FUN_004C93D0(&facingDir)->Raw) {
                        BA2Dir newTurret;
                        newTurret.Raw = (unsigned short)((unsigned char)Type->unknown_1710 << 8);
                        Turret.FUN_004C9220(&newTurret);
                        BA2Dir newFacing;
                        newFacing.Raw = (unsigned short)((unsigned char)Type->unknown_ED8 << 8);
                        Facing.FUN_004C9220(&newFacing);
                        return 1;
                    }
                }
                ++DAT_00A8E7AC;
                BA2Unit* unit = new BA2Unit(Type->unknown_408, Owner);
                --DAT_00A8E7AC;
                if (unit) {
                    double ratio = FUN_005F5C60();
                    int id = vf_175();
                    BA2Tether* tether = unknown_218;
                    HBCoord where;
                    if (Type->FUN_0045EC90() <= 2 && Type->FUN_0045ECA0(0) <= 2) {
                        where = Location;
                    } else {
                        int x = Location.X + DAT_0089F6F0;
                        where.Z = Location.Z;
                        int y = Location.Y + DAT_0089F6F4;
                        where.X = x / 256 * 256 + 128;
                        where.Y = y / 256 * 256 + 128;
                    }
                    if (LightSource) {
                        LightSource->FUN_00554A80(0);
                    }
                    BA2InlineDynVector<BA2Tech*> watchers;
                    for (i = 0; i < DAT_00A8EC88; i++) {
                        BA2Tech* other = DAT_00A8EC7C[i];
                        if (other->unknown_2B4 && other->unknown_2B4->vf_11() == 6 && other->unknown_2B4 == this
                            && other->unknown_90 && other != this && other != unit) {
                            watchers.AddItem(other);
                        }
                    }
                    vf_53();
                    if (unit->vf_54(&where, Type->FUN_00465D70())) {
                        int hp = unit->unknown_6C = (int)(unit->vf_34()->unknown_A0 * ratio);
                        if (hp <= 1) {
                            hp = 1;
                        }
                        unit->unknown_6C = hp;
                        unit->unknown_70 = hp;
                        if (unknown_2D8) {
                            unknown_2D8->FUN_006AF580(unit);
                        }
                        unit->unknown_214 = unknown_214;
                        unit->unknown_150 = unknown_150;
                        if (Type->unknown_16CA) {
                            BA2Dir dir;
                            dir.Raw = (unsigned short)((unsigned char)Type->unknown_1710 << 8);
                            unit->Turret.FUN_004C9300(&dir);
                        }
                        if (tether) {
                            unit->vf_288(tether, 1);
                            unit->vf_122(2, 0);
                        }
                        if (unknown_34) {
                            unit->FUN_005F5B50(unknown_34);
                            unknown_34->unknown_2C--;
                            unknown_34 = 0;
                        }
                        unit->unknown_4DC = unknown_4DC;
                        unit->unknown_4F0 = unknown_4F0;
                        unit->unknown_4F4 = unknown_4F4;
                        FUN_004060F0(&unknown_4DC, 0, 0);
                        unknown_4F0 = -1;
                        unknown_4F4 = -1;
                        if (wasSold) {
                            unsigned char saved = DAT_00822CF2;
                            DAT_00822CF2 = 0;
                            unit->vf_83();
                            DAT_00822CF2 = saved;
                        }
                        for (int k = 0; k < watchers.Count; k++) {
                            watchers.Items[k]->vf_242(unit);
                        }
                    } else {
                        Owner->FUN_004F9950(id);
                    }
                } else {
                    Owner->FUN_004F9950(vf_175());
                }
                vf_55(1);
                Audio.FUN_00406060();
                vf_62();
                return 1;
            }
            unknown_53C = -1;
            vf_56(0);
            if (LightSource) {
                LightSource->FUN_00554A80(0);
            }
            Owner->FUN_004F9950(vf_175());
            vf_53();
            for (int index = unknown_33C.FUN_006C9820(); index != -1; index = unknown_33C.FUN_006C9820()) {
                int whole = (int)unknown_33C.FUN_006C96B0(unknown_33C.FUN_006C9680(index), index);
                Owner->FUN_004F9610((float)whole, index);
            }
            vf_62();
            if (Type->unknown_16C7) {
                unknown_6EB = 0xFF;
                if (!unknown_6EC) {
                    unknown_6EC = Type->unknown_1707;
                }
                unknown_80 = 1;
                unknown_6EC = 1;
                vf_260(1);
                return 1;
            }
        }
        break;
    }
    return 1;
}
