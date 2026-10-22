// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Third batch of the building-a cluster: the larger BuildingClass virtual methods. Every body was read from
//   the retail gamemd.exe v1.001 from its entry to its last RET with a linear decode of the retail bytes
//   (Ghidra's function-flow listing drops instructions after some calls); offsets are pinned in
//   building_a_views.h. Method names are slot labels (vf_N = primary-table byte offset / 4).

#include <stdlib.h>
#include "building_a_views.h"

// FUNCTION: GAMEMD 0x447210
// CAPPED at 3.3% (first transcription, two forms). Delta: retail pushes EDI after the early returns and has a 0xc frame;
// the same register-lifetime effect as vf_80 but in the other direction.
int BuildingAView::vf_29(BAObjView* obj, char flag)
{
    int r;
    if (Type->unknown_1701) {
        return 0;
    }
    if (obj->vf_11() == 6 && obj->unknown_520->unknown_1701) {
        return 0;
    }
    r = FUN_006FFEC0(obj, flag);
    if (r == 8) {
        return 8;
    }
    if (r == 4) {
        if (Type->unknown_CD1 && DAT_00A83D4C == Owner) {
            if (!unknown_268) {
                if (Owner->unknown_24.vf_8() - Owner->unknown_24.vf_9() <= Type->unknown_EEC) {
                    r = 0;
                    return r;
                }
            }
        } else if (!((Type->unknown_16AE || Type->unknown_16AF) && unknown_114 > 0)) {
            if (vf_258() <= 0 && Type->unknown_EB8 == 0) {
                r = 0;
                return r;
            }
        }
        r = 4;
        if (Type->unknown_EB8 != 0 && unknown_3D3) {
            r = 0;
        }
        return r;
    }
    if (r == 5) {
        if (vf_254(0)->First == 0) {
            goto checkTarget;
        }
        if (!vf_254(0)->First->Type->unknown_2A5 || Type->unknown_16C3) {
            r = 0;
        }
        if (unknown_AC == 0x13) {
            r = 0;
            return r;
        }
    }
    if (r == 1 || r == 2) {
        if (!vf_40()) {
            r = 7;
            return r;
        }
        int kind = Type->unknown_EB8;
        if (kind == 0x10 || kind == 0x28 || kind == 3) {
            if (!DAT_0087F770->FUN_0054F5C0(DAT_00A8EBF8) && !DAT_0087F770->FUN_0054F5C0(DAT_00A8EBFC)) {
                r = 7;
                return r;
            }
            HBCoord tmp;
            HBCoord* c = obj->vf_18(&tmp);
            HBCell cell;
            cell.X = (short)(c->X / 256);
            cell.Y = (short)(c->Y / 256);
            HBCell cellCopy = cell;
            if (Type->unknown_EB8 != 3) {
                HBCoord where;
                where.X = (cell.X << 8) + 0x80;
                where.Y = (cell.Y << 8) + 0x80;
                where.Z = 0;
                if (!vf_179(&where)) {
                    r = 2;
                }
                if (!(DAT_0087F7E8.FUN_005657A0(&cellCopy)->unknown_140 & 0x100)
                    && DAT_0087F7E8.FUN_005657A0(&cellCopy)->unknown_4C != 0) {
                    r = 2;
                    return r;
                }
            }
        }
    }
    if (r != 5) {
        return r;
    }
checkTarget:
    if (obj->vf_34()->unknown_233) {
        r = 2;
    }
    return r;
}

// FUNCTION: GAMEMD 0x447540
// CAPPED at 42.2%. Delta: retail keeps one separate "xor ebx,ebx; jmp done" per exit and a flat r==1||r==2 test; goto, else-if and split forms all give the same 42.2%.
int BuildingAView::vf_28(HBCell* cell, char a, char b)
{
    int r;
    if (Type->unknown_1701) {
        return 0;
    }
    if (Type->unknown_408 != 0 && a != 0) {
        r = FUN_00700600(cell, 0, b);
        HBCoord tmp;
        if (!DAT_0087F7E8.FUN_00586360(DAT_0087F7E8.FUN_005657A0(cell)->vf_18(&tmp))
            && r == 1
            && DAT_0087F7E8.FUN_005657A0(cell)->unknown_EC == 5
            && Type->unknown_5ED && Type->unknown_5EC) {
            return 6;
        }
    } else {
        r = FUN_00700600(cell, a, b);
    }
    if (r == 1 || r == 2) {
        if (!vf_40() && r == 1) {
            r = 0;
            goto done;
        }
        if (vf_161()) {
            if (!DAT_0087F770->FUN_0054F5C0(DAT_00A8EBF8) && !DAT_0087F770->FUN_0054F5C0(DAT_00A8EBFC)) {
                r = 0;
                goto done;
            }
            if (Type->unknown_EB8 != 3) {
                HBCoord where;
                where.Z = 0;
                where.X = (cell->X << 8) + 0x80;
                where.Y = (cell->Y << 8) + 0x80;
                if (!vf_179(&where)) {
                    r = 2;
                }
                if (!(DAT_0087F7E8.FUN_005657A0(cell)->unknown_140 & 0x100)
                    && DAT_0087F7E8.FUN_005657A0(cell)->unknown_4C != 0) {
                    r = 2;
                    goto done;
                }
            }
        }
    }
    if (r == 5) {
        if (vf_254(0)->First == 0) {
            return r;
        }
        if (!vf_254(0)->First->Type->unknown_2A5 || Type->unknown_16C3) {
            r = 0;
        }
        if (unknown_AC == 0x13) {
            r = 0;
        } else if (r == 5) {
            return r;
        }
    }
done:
    if (vf_161() && Owner->FUN_0050B6F0()) {
        r = 1;
    }
    return r;
}

// FUNCTION: GAMEMD 0x447B20
// CAPPED at 5.3%. Delta: retail keeps a 0x34 frame with a dead Location copy (Z=0, X, Y stores) and shares one
// epilogue; early-return, single-result and per-block-temporary forms tried.
HBCoord BuildingAView::FUN_00447B20(BAObjView* arg)
{
    HBCoord tmp;
    HBCoord r;
    if (Type->unknown_16BC) {
        HBCell cell;
        HBCell* c = vf_110(&cell);
        HBCell shifted;
        shifted.X = c->X + 2;
        shifted.Y = c->Y + 1;
        r.X = (shifted.X << 8) + 0x80;
        r.Y = (shifted.Y << 8) + 0x80;
        r.Z = Location.Z;
        return r;
    }
    if (Type->unknown_16BB) {
        HBCoord* p = FUN_005F6C80(&tmp, arg);
        r.X = p->X + 0x80;
        r.Y = p->Y;
        r.Z = p->Z;
        return r;
    }
    if (Type->unknown_16AB && arg) {
        HBCoord* pa = arg->vf_18(&tmp);
        HBCoord tb;
        HBCoord* pb = vf_18(&tb);
        int bx = pb->X;
        int ax = pa->X;
        HBDir d;
        d.Raw = (short)((FUN_004CAE30((double)pb->Y - pa->Y, (double)ax - bx) - DAT_007E2820) * DAT_007E2818);
        int dir = ((d.Whole >> 7) + 1 >> 1) & 0xFF;
        HBCoord* pc = vf_18(&tb);
        if (dir >= 0 && dir < 0x40) {
            r.X = pc->X + 0x80;
            r.Y = pc->Y - 0x80;
        } else if (dir >= 0x40 && dir < 0x80) {
            r.X = pc->X + 0x80;
            r.Y = pc->Y + 0x80;
        } else if (dir >= 0x80 && dir < 0xC0) {
            r.X = pc->X - 0x80;
            r.Y = pc->Y + 0x80;
        } else {
            r.X = pc->X - 0x80;
            r.Y = pc->Y - 0x80;
        }
        r.Z = pc->Z;
        return r;
    }
    if (!Type->unknown_16CB && !Type->unknown_16A9) {
        return *FUN_005F6C80(&tmp, arg);
    }
    switch (Type->unknown_1780) {
    case 0:
        return *vf_18(&tmp);
    case 1: {
        HBCoord* pc = vf_18(&tmp);
        HBCoord* off = Type->unknown_1788;
        r.X = off->X + pc->X;
        r.Y = off->Y + pc->Y;
        r.Z = off->Z + pc->Z;
        return r;
    }
    default: {
        int idx = FUN_0065AD90(arg);
        if (idx >= 0 && idx < Type->unknown_1780) {
            HBCoord* off = &Type->unknown_1788[idx];
            HBCoord* pc = vf_18(&tmp);
            r.X = off->X + pc->X;
            r.Y = off->Y + pc->Y;
            r.Z = off->Z + pc->Z;
            return r;
        }
        return *vf_18(&tmp);
    }
    }
}

// FUNCTION: GAMEMD 0x447F10
//
// CAPPED at 91.0% (instruction multiset identical): retail takes the absolute value of the quantised limit
// before the absolute value of the facing difference; every operand order tried evaluates them the other way.
int BuildingAView::vf_240(BAObjView* target, int b, int c)
{
    if (!Type->unknown_157B || (Type->unknown_157C && vf_258())) {
        if (!FUN_0070FEC0()) {
            if (Type->unknown_16C3) {
                return 6;
            }
            if (vf_97() != 0x13 && vf_97() != 0x12) {
                if (!vf_212()) {
                    return 6;
                }
                if (unknown_714) {
                    return 3;
                }
                int r = FUN_006FC0B0(target, b, c);
                if (r == 0 && vf_255()) {
                    HBDir want = vf_314(target);
                    int quant = Type->unknown_16C5 ? 0 : 8;
                    short diff = Facing.FUN_004C93D0().Raw;
                    diff -= want.Raw;
                    if (abs((short)(quant << 8)) < abs(diff)) {
                        return 2;
                    }
                }
                return r;
            }
        }
    }
    return 5;
}

// FUNCTION: GAMEMD 0x4496B0
// CAPPED at 41.5%. Delta: retail realigns the stack (AND ESP,-8, 0x38 frame), keeps a masked flag byte in a stack
// local and evaluates the price conversion before the counter call; local flag, temp price and operand-swap forms tried.
int BuildingAView::vf_135()
{
    int i;
    unsigned char active;
    if (vf_33()->unknown_CD5) {
        FUN_0070E000(unknown_C4);
        unknown_C4 = 0;
    }
    if (vf_171()) {
        unknown_6DD = 1;
        if (!Type->unknown_16C3) {
            int idx = Type->unknown_16F0;
            HBIdx3View* link;
            if (idx == -1 || (link = DAT_00A83CBC[idx]->unknown_28->unknown_C8) == 0
                || Owner->unknown_5550.FUN_0049FAE0(link->unknown_DF8) != 0) {
                if (Type->unknown_16F0 != -1) {
                    goto price;
                }
            }
            if (!Type->unknown_157B || vf_258() > 0) {
                if (Target) {
                    vf_122(1, 0);
                    vf_123();
                    return 1;
                }
            }
        }
    price:
        int price = (int)(DAT_007E27F8 * FUN_005B3A00()->unknown_18);
        return DAT_00A8B230->Counter.FUN_0065C7E0(0, 2) + price;
    }
    if (Type->unknown_16B5) {
        return 100;
    }
    switch (unknown_BC) {
    case 0:
        FUN_00447780(1);
        unknown_BC = 1;
        break;
    case 1:
        if (Type->unknown_16A9 || Type->unknown_16AA || Type->unknown_16AB) {
            for (i = 0; i < unknown_E8; i++) {
                BAObjView* o = FUN_0065AD30(i);
                if (o && (active = o->unknown_14 & 1) != 0) {
                    if (o->vf_97() == 7) {
                        HBCoord a, b, d;
                        HBCoord* pa = o->vf_18(&a);
                        HBCoord* pb = vf_18(&b);
                        HBCoord* diff = d.FUN_0041C230(pb->X - pa->X, pb->Y - pa->Y, pb->Z - pa->Z);
                        if ((int)FUN_004CAC40((double)diff->X * diff->X + (double)diff->Z * diff->Z + (double)diff->Y * diff->Y) < 0x40) {
                            if (vf_158(0x13, o) == 1) {
                                vf_122(0x14, 0);
                                return 1;
                            }
                        }
                    }
                }
            }
        }
        if (Type->unknown_16BD) {
            FUN_00449540();
        }
        break;
    }
    if (Type->unknown_16AA && FUN_0065AE30()) {
        if (vf_157(0x1D) != 1 && vf_157(0x13) == 1) {
            vf_122(0x14, 0);
        }
    }
    if (Type->unknown_16A9) {
        int price = (int)(DAT_007E27F8 * FUN_005B3A00()->unknown_10);
        return DAT_00A8B230->Counter.FUN_0065C7E0(0, 2) + price;
    }
    int price = (int)(DAT_007E27F8 * FUN_005B3A00()->unknown_10);
    return DAT_00A8B230->Counter.FUN_0065C7E0(0, 2) + price * 3;
}

// FUNCTION: GAMEMD 0x44E8F0
void BuildingAView::vf_10(BAObjView* ptr, bool removed)
{
    FUN_007077C0(ptr, removed);
    if (C4AppliedBy == ptr) {
        C4AppliedBy = 0;
    }
    if (FirestormAnim == ptr) {
        FirestormAnim = 0;
    }
    if (Factory == ptr) {
        Factory = 0;
    }
    if (Spotlight == ptr) {
        Spotlight = 0;
    }
    if (LightSource == ptr) {
        LightSource = 0;
    }
    if (Anims[8] == ptr) {
        double ratio = FUN_005F5C60();
        char* name;
        int low;
        if (ratio <= RulesInstance->unknown_1700) {
            low = 1;
            name = Type->unknown_1424;
        } else {
            low = 0;
            name = Type->unknown_1414;
        }
        if (name && *name) {
            FUN_00451890(name, 0x12, low, 0, 0);
        }
    }
    if (Type->unknown_16AD && Anims[10] == ptr) {
        double ratio = FUN_005F5C60();
        char* name;
        int low;
        if (ratio <= RulesInstance->unknown_1700) {
            low = 1;
            name = Type->unknown_1028;
        } else {
            low = 0;
            name = Type->unknown_1018;
        }
        if (name && *name) {
            FUN_00451890(name, 3, low, 0, 0);
        }
    }
    if (ptr) {
        if (ptr->unknown_04.vf_3() == 4) {
            int i;
            for (i = 0; i < 8; i++) {
                if (DamageFireAnims[i] == ptr) {
                    DamageFireAnims[i] = 0;
                    return;
                }
            }
            if (ptr->unknown_118) {
                FUN_00451B40(ptr);
                return;
            }
        }
    }
    if (Type == (BATypeView*)ptr) {
        Type = 0;
    }
    int i;
    for (i = 0; i < 3; i++) {
        if (Upgrades[i] == ptr) {
            Upgrades[i] = 0;
        }
    }
    Overpowerers.RemoveItem(ptr);
    if (DAT_00A8E7AC) {
        Occupants.RemoveItem(ptr);
    }
}

// One refund of a production slot: the production object is looked up, the building is flagged while the
// owner is told, then the flag is restored (inline in retail, once per slot).
inline void BAReleaseSlot(BuildingAView* b, int handle)
{
    BAProdView* prod = FUN_004CA160(handle);
    unsigned char saved = b->unknown_81;
    b->unknown_81 = 1;
    if (prod) {
        if (!prod->vf_33()->vf_37(1, 0, 0, b->Owner)) {
            b->Owner->FUN_004FAA10(b->Type->unknown_EB8, prod->vf_33()->vf_16(0, 0));
        }
    }
    b->unknown_81 = saved;
}

// FUNCTION: GAMEMD 0x44EBF0
// CAPPED at 67.4%. Delta: retail merges the type!=7 path into the fifth inlined slot copy (jump into the middle);
// loop, helper-inline and if/else-with-helper forms tried, none merges.
void BuildingAView::vf_55(char arg)
{
    if (arg) {
        if (Factory) {
            FUN_004C9FF0(Factory);
            if (Factory) {
                Factory->vf_8(1);
            }
            Factory = 0;
        }
        if (Owner) {
            if (Type->unknown_EB8 == 7) {
                if (Owner->unknown_53BC[0]) {
                    BAReleaseSlot(this, Owner->unknown_53BC[0]);
                }
                if (Owner->unknown_53BC[1]) {
                    BAReleaseSlot(this, Owner->unknown_53BC[1]);
                }
                if (Owner->unknown_53BC[2]) {
                    BAReleaseSlot(this, Owner->unknown_53BC[2]);
                }
                if (Owner->unknown_53BC[3]) {
                    BAReleaseSlot(this, Owner->unknown_53BC[3]);
                }
                if (Owner->unknown_53BC[4]) {
                    BAReleaseSlot(this, Owner->unknown_53BC[4]);
                }
            } else {
                int handle = Owner->FUN_00500510(Type->unknown_EB8, Type->unknown_CCE, 0);
                if (handle) {
                    BAReleaseSlot(this, handle);
                }
            }
        }
        vf_160(3);
    } else {
        int i;
        for (i = 0; i < unknown_E8; i++) {
            BAObjView* o = FUN_0065AD30(i);
            if (o && !Owner->FUN_004F9A90(o)) {
                vf_158(3, o);
            }
        }
    }
    FUN_005F5280(arg);
}
