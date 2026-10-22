// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   BuildingClass primary-table slot 54 at 0x440580 (0x1069 bytes), read from the retail gamemd.exe v1.001
//   from its entry to its last RET (linear decode). It takes a world coordinate and a facing and puts the
//   building on the map; slot 54 follows the take-off-the-map virtual at slot 53 (0x445880), and the
//   original name is not confirmed here.

#include "building_a4_views.h"

// FUNCTION: GAMEMD 0x440580
bool BA4Building::vf_54(HBCoordPod* where, int dir)
{
    int i;
    int x;
    int y;
    bool ok = vf_107(DAT_0087F7E8.FUN_00565730(where), -1, -1, 0, 1) == 0;

    if (ok) {
        if (Type == DAT_008871E0->unknown_87C) {
            BA4MapCell* mc = DAT_0087F7E8.FUN_00565730(where);
            BA4House* cellOwner = 0;
            if (mc->unknown_50 >= 0) {
                cellOwner = DAT_00A8022C[mc->unknown_50];
            }
            if (cellOwner == Owner && (mc->unknown_44 == 2 || mc->unknown_44 == 0)) {
                Owner->FUN_004FCE80(&mc->unknown_24, 1);
            }
        } else if (Type->unknown_E54) {
            BA4MapCell* mc = DAT_0087F7E8.FUN_00565730(where);
            BA4House* cellOwner = 0;
            if (mc->unknown_50 >= 0) {
                cellOwner = DAT_00A8022C[mc->unknown_50];
            }
            if (cellOwner == Owner && mc->unknown_44 == Type->unknown_E54->unknown_294) {
                Owner->FUN_004FCE80(&mc->unknown_24, 1);
            }
        } else if (Type->unknown_16B7) {
            HBCell cell(where->X / 256, where->Y / 256);
            for (HBCell* p = Type->vf_36(1); !(p->X == 0x7FFF && p->Y == 0x7FFF); p++) {
                BA4MapCell* mc = DAT_0087F7E8.FUN_005657A0(*p + cell);
                BA4House* cellOwner = 0;
                if (mc->unknown_50 >= 0) {
                    cellOwner = DAT_00A8022C[mc->unknown_50];
                }
                if (cellOwner == Owner && (mc->unknown_44 == 2 || mc->unknown_44 == 0 || mc->unknown_44 == 0x1A)) {
                    Owner->FUN_004FCE80(&mc->unknown_24, 1);
                }
                BA4Building* neighbour = mc->FUN_0047C520();
                if (neighbour && neighbour->Type->unknown_16BF) {
                    if (neighbour->vf_14() == vf_14()) {
                        HBCell copy = mc->unknown_24;
                        copy.FUN_00453240();
                    }
                }
            }
        }
    }

    if (Type->unknown_1571) {
        if (vf_107(DAT_0087F7E8.FUN_00565730(where), -1, -1, 0, 1) == 0) {
            BA4Object* created = Type->unknown_E54->vf_35(Owner);
            if (created && created->vf_54(where, 0)) {
                DAT_0087F7E8.FUN_00565730(where)->unknown_50 = Owner->unknown_30;
                vf_157(3);
                DAT_0087F7E8.FUN_005678E0(where, Type->unknown_5E8, Owner, 0, 0, 0, 1, 0);
                DAT_0087F7E8.FUN_005678E0(where, Type->unknown_5E8, Owner, 0, 0, 0, 1, 1);
                vf_62();
                return true;
            }
        }
        goto refuse;
    }

    if (Type->unknown_E88) {
        HBPoint2D unused;
        unused.X = 0;
        unused.Y = 0;
        HBCell cell(where->X / 256, where->Y / 256);
        BA4Building* other = DAT_0087F7E8.FUN_004AA290(&cell, &unused);
        if (!other || other->vf_11() != 6) {
            goto refuse;
        }
        BA4Type* thisType = Type;
        if (Owner != other->Owner) {
            goto refuse;
        }
        if (_stricmp(&thisType->unknown_E88, &other->Type->unknown_24) != 0) {
            goto refuse;
        }
        int levels = thisType->unknown_16FC;
        if (levels == -1) {
            if (!(other->unknown_702 < other->Type->unknown_14E0)) {
                if (other->unknown_702 != 0) {
                    goto refuse;
                }
            }
        } else {
            if (levels <= 0 || levels > 3) {
                goto refuse;
            }
            if (other->unknown_702 != 0) {
                goto refuse;
            }
        }
        Owner->unknown_5779 = 1;
        Owner->unknown_5778 = 1;
        int count = Type->unknown_16FC;
        if (count == -1) {
            count = 1;
        }
        char* name = &other->Type->unknown_F4C[other->unknown_702].unknown_00[0];
        if (_stricmp(name, &Type->unknown_1F8) != 0) {
            strncpy(name, &Type->unknown_1F8, 16);
        }
        for (; count != 0; count--) {
            other->FUN_00451400();
        }
        other->Upgrades[other->unknown_702] = Type;
        Owner->FUN_0050B1D0();
        Owner->unknown_1FC = 1;
        if (Type->unknown_1763) {
            Owner->FUN_00509130();
        }
        vf_62();
        return true;
    }

    if (Type->unknown_16BF) {
        HBDir facing((unsigned char)dir);
        if ((((facing.Whole >> 12) + 1) & 6) == 4) {
            unknown_618 = 8;
        } else {
            unknown_618 = 12;
        }
    }
    if (ok && Type->unknown_16BE) {
        unknown_618 = 0;
        HBCell cell(where->X / 256, where->Y / 256);
        BA4Building* other = DAT_0087F7E8.FUN_005657A0(cell)->FUN_0047C520();
        if (other && other->Type->unknown_16BF) {
            if (other->vf_14() == vf_14()) {
                other->vf_62();
            }
        }
    }
    if (!FUN_006F6CA0(where, dir)) {
        goto refuse;
    }
    if (Type->unknown_16C7) {
        Owner->unknown_56F8 = 1;
    }
    if (!unknown_90) {
        return true;
    }
    if (DAT_00A8B238 && !Owner->FUN_0050B730() && !Owner->unknown_34->unknown_1A6) {
        unknown_6CB = 1;
    }
    if (DAT_00A8B230->unknown_00 & 0x1000) {
        HBCell scratch;
        HBCell here = *vf_110(&scratch);
        HBCell* p;
        for (p = Type->vf_36(0); !(p->X == 0x7FFF && p->Y == 0x7FFF); p++) {
            if (DAT_0087F7E8.FUN_005657A0(p->FUN_0042D510(here))->unknown_140 & 0x400000) {
                goto skip;
            }
        }
        FUN_00457AA0(0, 0, 0);
    }
skip:
    if ((!Type->unknown_408 || !Type->unknown_5EC) && !vf_32()) {
        FUN_00455F10(0);
    }
    {
        int width = Type->FUN_0045EC90();
        int height = Type->FUN_0045ECA0(false);
        HBCell cell(where->X / 256, where->Y / 256);
        for (y = 0; y < height + 2; y++) {
            for (x = 0; x < width + 2; x++) {
                DAT_0087F7E8.FUN_005657A0(cell + HBCell(x - 1, y - 1))->unknown_122++;
            }
        }
    }
    Owner->FUN_004FD150();
    Owner->FUN_004FFA50(this);
    Owner->unknown_1FC = 1;
    unknown_544 = 0;
    if ((!unknown_41B && (DAT_0087F7E8.FUN_00565730(where)->unknown_12C & 0x10)) || DAT_00A8B238) {
        vf_102(DAT_00A83D4C);
    } else if (Type->unknown_E34) {
        if (!unknown_614) {
            BA4Light* light = new BA4Light(*vf_18(&Location), Type->unknown_E30, Type->unknown_E34, Type->unknown_E38, Type->unknown_E3C, Type->unknown_E40);
            unknown_614 = light;
        }
        unknown_614->FUN_00554A60(0);
    }
    if (Type->unknown_16BE && !DAT_00A8E7AC && unknown_90 && !unknown_81) {
        FUN_00452DC0(0);
        FUN_00452DC0(2);
        FUN_00452DC0(4);
        FUN_00452DC0(6);
        FUN_004533A0(1);
    }
    if (!Owner->FUN_0050B730()) {
        vf_102(Owner);
    }
    if (unknown_41A) {
        DAT_00880CF4 = 1;
        DAT_0087F7E8.FUN_004F42F0(0);
    }
    if (Type->unknown_764 && !unknown_30C) {
        HBCoordPod offset = Type->unknown_768;
        HBCoordPod loc = Location;
        HBCoordPod target;
        target.X = Location.X + offset.X;
        target.Y = Location.Y + offset.Y;
        target.Z = Location.Z + offset.Z;
        unknown_30C = new BA4Tracker(Type->unknown_764, &target, DAT_0087F7E8.FUN_00565730(&loc), 0, &DAT_0089C848, 0);
    }
    if (Type == DAT_008871E0->unknown_87C) {
        HBCell base = DAT_0087F7E8.FUN_00565730(where)->unknown_24;
        DAT_0087F7E8.FUN_005657A0(base + HBCell(1, 0))->FUN_00480630(0);
        DAT_0087F7E8.FUN_005657A0(base + HBCell(-1, 0))->FUN_00480630(0);
        DAT_0087F7E8.FUN_005657A0(base + HBCell(0, 1))->FUN_00480630(0);
        DAT_0087F7E8.FUN_005657A0(base + HBCell(0, -1))->FUN_00480630(0);
    }
    if (Type == DAT_008871E0->unknown_86C || Type == DAT_008871E0->unknown_874) {
        HBCell base = DAT_0087F7E8.FUN_00565730(where)->unknown_24;
        DAT_0087F7E8.FUN_005657A0(base + HBCell(-1, 0))->FUN_00480630(0);
        DAT_0087F7E8.FUN_005657A0(base + HBCell(3, 0))->FUN_00480630(0);
    }
    if (Type == DAT_008871E0->unknown_870 || Type == DAT_008871E0->unknown_878) {
        HBCell base = DAT_0087F7E8.FUN_00565730(where)->unknown_24;
        DAT_0087F7E8.FUN_005657A0(base + HBCell(0, -1))->FUN_00480630(0);
        DAT_0087F7E8.FUN_005657A0(base + HBCell(0, 3))->FUN_00480630(0);
    }
    if (Type->unknown_154B) {
        Spotlight = new BA4Spotlight(this);
    }
    unknown_3D3 = 0;
    if (Type->unknown_EB8) {
        FUN_00448070(0);
    }
    for (i = 0; i < DAT_008871E0->unknown_8BC; i++) {
        if (DAT_008871E0->unknown_8B0[i] == Type) {
            Owner->unknown_50.AddItem(this);
            break;
        }
    }
    if (Type->unknown_16A9) {
        Owner->unknown_80.AddItem(this);
    }
    if (Type->unknown_16AD) {
        Owner->unknown_98.AddItem(this);
    }
    if (Type->unknown_16AE || Type->unknown_16AF) {
        Owner->unknown_B0.AddItem(this);
    }
    if (Type->unknown_16AB) {
        Owner->unknown_C8.AddItem(this);
    }
    if (Type->unknown_157B && Type->unknown_634 > -1) {
        Owner->unknown_E0.AddItem(this);
    }
    if (Type->unknown_16AC) {
        Owner->unknown_F8.AddItem(this);
    }
    if (Type->unknown_16B0) {
        Owner->unknown_110.AddItem(this);
    }
    if (Type->unknown_170C > 0) {
        Owner->unknown_128.AddItem(this);
    }
    if (Type->unknown_16CD) {
        Owner->unknown_140.AddItem(this);
        Owner->FUN_0050BF60();
    }
    Owner->unknown_68.AddItem(this);
    if (!Owner->FUN_0050B730()) {
        Owner->unknown_5700.FUN_0042F260(this);
    }
    if (Type->unknown_EB8) {
        Owner->FUN_00509140(Type->unknown_EB8, Type->unknown_CCE, 0);
    }
    return true;
refuse:
    return false;
}
