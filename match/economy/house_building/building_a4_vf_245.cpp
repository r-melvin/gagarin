// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   BuildingClass primary-table slot 245 at 0x448260 (0x11A6 bytes), read from the retail gamemd.exe v1.001
//   from its entry to its last RET (linear decode; Ghidra's flow listing mixes up the old and the new owner
//   in the second half). It moves the building to another house: the old house's lists drop it, the base
//   class changes the owner, the new house's lists take it. The original name is not confirmed here.

#include "building_a4_views.h"

// FUNCTION: GAMEMD 0x448260
bool BA4Building::vf_245(BA4House* newOwner, bool announce)
{
    int i;

    if (newOwner != Owner) {        if (unknown_38 && !Type->unknown_157B) {
            unknown_38->FUN_004389B0();
        }
        if (Type->unknown_16C7) {
            newOwner->unknown_56F8 = 1;
        }
        if (Owner->unknown_34->unknown_1A6 && Type->unknown_1558) {
            newOwner->FUN_004F9950(Type->unknown_1558);
            HBCoordPod tmp;
            tmp.X = DAT_00A8ED84;
            tmp.Z = Type->unknown_1560;
            unknown_6D0 = tmp;
        }
        unsigned int bit = 1 << (newOwner->unknown_34->unknown_B8);
        if ((bit & unknown_210) != 0) {
            unknown_210 = unknown_210 - bit;
            if (Type->unknown_16A4) {
                Owner->unknown_54E4 = 0;
                int count = Owner->unknown_68.Count;
            for (i = 0; i < count; i++) {
                    BA4Building* b = Owner->unknown_68.Items[i];
                    if (b && !b->unknown_81 && b->Type->unknown_16A4) {
                        Owner->unknown_54E4 |= b->unknown_210;
                    }
                }
                DAT_0087F7E8.FUN_004F42F0(2);
            }
        }
        unknown_3D3 = 0;
        if (Type->unknown_16BE) {
            FUN_00452A40(0);
        }
        if (Owner->FUN_0050B6F0() || newOwner->FUN_0050B6F0()) {
            if (!newOwner->unknown_34->unknown_1A6 && announce) {
                if (Type->unknown_1552) {
                    if (Owner != newOwner) {
                        if (Owner->FUN_0050B6F0()) {
                            FUN_00752700(s_EVA_TechBuildingLost_00818FC4, -1, -1);
                        }
                        if (newOwner->FUN_0050B6F0() && newOwner->FUN_0050B6F0() && Type->unknown_1554 != -1) {
                            FUN_00752480(Type->unknown_1554, -1, -1);
                        }
                    }
                } else {
                    HBCell scratch;
                    if (FUN_0065FA70(10, *vf_110(&scratch))) {
                        FUN_00752700(s_EVA_BuildingCaptured_00818FAC, -1, -1);
                    }
                }
            }
            DAT_00880CF4 = 1;
            DAT_0087F7E8.FUN_004F42F0(0);
        }
        unknown_80 = 1;
        unknown_6CC = 1;
        if (Type->unknown_1552) {
            unknown_6EA = 1;
            if (unknown_614) {
                unknown_614->FUN_00554A60(0);
            }
            if (Type->unknown_16BE) {
                FUN_004533A0(0);
            }
            for (int k = 0; k < 21; k++) {
                if (Type->unknown_F4C[k].unknown_40 && Anims[k]) {
                    Anims[k]->FUN_00425270();
                }
            }
        }
        if (DAT_00A8B238 == 4 && !vf_33()->unknown_C9F) {
            newOwner->unknown_4368.FUN_00749020(Type->unknown_DF8);
        }

        BA4HeldList held;
        for (i = 0; i < unknown_E8; i++) {
            BA4Object* object = FUN_0065AD30(i);
            if (object) {
                if (!(object->unknown_14 & 4)) {
                    object = 0;
                } else if (vf_158(0x13, object) == 1) {
                    bool inRange = false;
                    if (!Type->unknown_16BD) {
                        HBCoordPod scratchA;
                        HBCoordPod scratchB;
                        HBCoordPod* a = vf_42(&scratchA, object);
                        HBCoordPod* b = object->vf_18(&scratchB);
                        HBCoordPod scratchC;
                        HBCoordPod diff = *scratchC.FUN_0041C230(b->X - a->X, b->Y - a->Y, b->Z - a->Z);
                        inRange = diff.FUN_0041C380() < 0x40;
                    } else {
                        inRange = true;
                    }
                    if (inRange) {
                        unsigned char flag = object->unknown_418;
                        object->vf_245(newOwner, 1);
                        BA4Held* entry = new BA4Held(object, flag);
                        held.AddItem(entry);
                        continue;
                    }
                    vf_158(0x17, object);
                    vf_158(3, object);
                    continue;
                }
                vf_158(0x17, object);
                vf_158(3, object);
            }
        }
        if (unknown_524) {
            unknown_524->FUN_004C9FF0();
            if (unknown_524) {
                unknown_524->vf_8(1);
            }
            unknown_524 = 0;
        }
        Owner->FUN_004FF980(this);
        BA4House* oldOwner = Owner;
        BA4TargetRef target;
        target.FUN_006E6AB0(this);
        unknown_6E3 = 1;

        for (i = 0; i < DAT_008871E0->unknown_8BC; i++) {
            if (DAT_008871E0->unknown_8B0[i] == Type) {
                oldOwner->unknown_50.RemoveItem(this);
                break;
            }
        }
        if (Type->unknown_16A9) {
            oldOwner->unknown_80.RemoveItem(this);
        }
        if (Type->unknown_16AD) {
            oldOwner->unknown_98.RemoveItem(this);
        }
        if (Type->unknown_16AE || Type->unknown_16AF) {
            oldOwner->unknown_B0.RemoveItem(this);
        }
        if (Type->unknown_16AB) {
            oldOwner->unknown_C8.RemoveItem(this);
        }
        if (Type->unknown_157B && Type->unknown_634 > -1) {
            oldOwner->unknown_E0.RemoveItem(this);
        }
        if (Type->unknown_16AC) {
            oldOwner->unknown_F8.RemoveItem(this);
        }
        if (Type->unknown_16B0) {
            oldOwner->unknown_110.RemoveItem(this);
        }
        if (Type->unknown_170C > 0) {
            oldOwner->unknown_128.RemoveItem(this);
        }
        if (Type->unknown_16CD) {
            oldOwner->unknown_140.RemoveItem(this);
            oldOwner->FUN_0050BF60();
        }
        oldOwner->unknown_68.RemoveItem(this);
        if (Type->unknown_16CC) {
            oldOwner->unknown_538C--;
        }
        if (Type->unknown_1564 && unknown_6E4) {
            Owner->unknown_164 -= Type->unknown_1564;
            if (Owner->unknown_164 < 0) {
                Owner->unknown_164 = 0;
            }
        }
        if (Type->unknown_1568 && unknown_6E4) {
            Owner->unknown_168 -= Type->unknown_1568;
            if (Owner->unknown_168 < 0) {
                Owner->unknown_168 = 0;
            }
        }
        if (Type->unknown_16CB) {
            oldOwner->unknown_2D4 -= Type->unknown_1780;
        }
        if (Type->unknown_16C7) {
            unknown_6EB = 0xFF;
            if (!unknown_6EC) {
                unknown_6EC = Type->unknown_1707;
            }
            unknown_80 = 1;
            unknown_6EC = 1;
            vf_260(1);
        }
        if (Type->unknown_CD1) {
            vf_262();
        }
        vf_291(0, 0, 0, 0);
        FUN_007014A0(newOwner, 1);
        if (Type->unknown_16C7 && vf_212() && Type->unknown_16C7) {
            unknown_6EB = 1;
            if (unknown_6EC == Type->unknown_1707) {
                unknown_6EC = 0;
            }
            unknown_80 = 1;
        }
        if (Type->unknown_CD1 && vf_212()) {
            vf_261();
        }
        FUN_00448070(0);
        oldOwner->unknown_54E0 = this;
        oldOwner->FUN_004FD150();
        Owner->FUN_004FD150();
        if (Owner->unknown_54E0 == this) {
            Owner->unknown_54E0 = 0;
        }
        if (oldOwner->FUN_0050B6F0() && Type->unknown_16B9) {
            DAT_0088098C = 0;
            DAT_00880990 = 0;
            DAT_00880994 = -1;
            DAT_0087F7E8.FUN_004A8BF0(0);
        }
        Owner->FUN_004FFA50(this);
        unknown_6E8 = 0;
        vf_311(1);
        if (Type->unknown_16BE && !DAT_00A8E7AC) {
            if (unknown_90 && !unknown_81) {
                FUN_00452DC0(0);
                FUN_00452DC0(2);
                FUN_00452DC0(4);
                FUN_00452DC0(6);
                FUN_004533A0(1);
                if (DAT_00A8E7AC) {
                    goto afterFacing;
                }
            }
            if (Type->unknown_16BE) {
                unknown_618 = 0;
            }
        }
    afterFacing:
        if (Owner->FUN_0050B6F0()) {
            vf_290(0, 0, 0, 0, 0);
            DAT_0087F7E8.FUN_004F42F0(1);
        }
        bit = 1 << (newOwner->unknown_34->unknown_B8);
        if ((bit & unknown_210) != 0) {
            unknown_210 = ~bit & unknown_210;
        }
        int value = vf_121();
        int angle = vf_281(vf_111()->unknown_10A);
        if (vf_88() || (unknown_294 && unknown_294->unknown_50 == FUN_00459F40())) {
            angle = FUN_0070E360(angle);
        }
        unknown_700 = (short)angle;
        FUN_00451F60(value, angle & 0xFFFF);
        FUN_00452170(unknown_6ED);

        for (i = 0; i < DAT_008871E0->unknown_8BC; i++) {
            if (DAT_008871E0->unknown_8B0[i] == Type) {
                newOwner->unknown_50.AddItem(this);
                break;
            }
        }
        if (Type->unknown_16A9) {
            newOwner->unknown_80.AddItem(this);
        }
        if (Type->unknown_16AD) {
            newOwner->unknown_98.AddItem(this);
        }
        if (Type->unknown_16AE || Type->unknown_16AF) {
            newOwner->unknown_B0.AddItem(this);
        }
        if (Type->unknown_16AB) {
            newOwner->unknown_C8.AddItem(this);
        }
        if (Type->unknown_157B && Type->unknown_634 > -1) {
            newOwner->unknown_E0.AddItem(this);
        }
        if (Type->unknown_16AC) {
            newOwner->unknown_F8.AddItem(this);
        }
        if (Type->unknown_16B0) {
            newOwner->unknown_110.AddItem(this);
        }
        if (Type->unknown_170C > 0) {
            newOwner->unknown_128.AddItem(this);
        }
        if (Type->unknown_16CD) {
            newOwner->unknown_140.AddItem(this);
            newOwner->FUN_0050BF60();
        }
        newOwner->unknown_68.AddItem(this);
        if (Type->unknown_16CC) {
            Owner->unknown_538C++;
        }
        if (Type->unknown_1564) {
            Owner->unknown_164 += Type->unknown_1564;
        }
        if (Type->unknown_1568) {
            Owner->unknown_168 += Type->unknown_1568;
        }
        if (Type->unknown_16CB) {
            Owner->unknown_2D4 += Type->unknown_1780;
        }
        if (Type->unknown_EB8) {
            oldOwner->FUN_00509140(Type->unknown_EB8, Type->unknown_CCE, 0);
            newOwner->FUN_00509140(Type->unknown_EB8, Type->unknown_CCE, 0);
        }
        for (i = 0; i < held.Count; i++) {
            vf_158(2, held.Items[i]->Object);
            if (held.Items[i]->Flag) {
                unknown_418 = 1;
                held.Items[i]->Object->unknown_418 = 1;
            }
        }
        if (DAT_00A8B238 && !newOwner->FUN_0050B730() && unknown_14C != newOwner && !unknown_14C->unknown_34->unknown_1A6) {
            while (unknown_702 > 0) {
                int r = Upgrades[unknown_702]->vf_46(Owner, 1);
                Owner->FUN_004F9950(r);
                FUN_00451690();
                Owner->unknown_5778 = 1;
                Owner->unknown_5779 = 1;
            }
            vf_104(1);
        }
        oldOwner->unknown_1FC = 1;
        newOwner->unknown_1FC = 1;
        return true;
    }
    return false;
}
