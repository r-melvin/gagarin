// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   First batch of the building-a cluster: the short BuildingClass virtual methods. Every body was read
//   from the retail gamemd.exe v1.001 from its entry to its last RET, and every offset it touches is
//   pinned in building_a_views.h. Method names are slot labels (vf_N = primary-table byte offset / 4)
//   or FUN_<addr>: no original name is confirmed for them.

#include "building_a_views.h"

// FUNCTION: GAMEMD 0x43E900
int BuildingAView::vf_187()
{
    int value = -FUN_006D20E0(vf_116());

    BATypeView* type = Type;

    if (type->unknown_16C5) {
        return type->unknown_11E8 + value;
    }

    return value;
}

// FUNCTION: GAMEMD 0x443B90
// CAPPED at 17.1%. Retail places the Base(0) fallback inline right after the first two tests and jumps back
// to it from the later failures; the three shapes tried (target=0 else-if, if/else with a trailing call, early
// returns) all put that block last. Instruction multiset differs by one jcc sense.
void BuildingAView::vf_242(BAObjView* target)
{
    if (unknown_AC != 0x13 && vf_212()) {
        if (target && vf_254(0)->First && !vf_254(0)->First->Type->unknown_2A4 && !vf_235(target)) {
            FUN_006FCDB0(0);
            if (Type->unknown_16C4 || Type->unknown_16CA) {
                if (!Owner->FUN_0050B730() && !vf_223()) {
                    vf_122(0x13, 0);
                    vf_123();
                }
            }
            return;
        }
    } else {
        target = 0;
    }
    FUN_006FCDB0(target);
}

// FUNCTION: GAMEMD 0x445E50
//
// The facing towards the target (or the current facing without one). The two X differences are kept in
// integer temporaries of their own (the frame is 0x20 bytes only with them), the angle callee takes the
// Y difference first and the X difference second, and the result is a 16-bit direction.
HBDir BuildingAView::vf_170()
{
    if (!vf_255() && Target) {
        HBCoord a, b;
        HBCoord* pa = Target->vf_18(&a);
        HBCoord* pb = vf_18(&b);
        int bx = pb->X;
        int ax = pa->X;
        HBDir d;
        d.Raw = (short)((FUN_004CAE30((double)pb->Y - pa->Y, (double)ax - bx) - DAT_007E2820) * DAT_007E2818);
        return d;
    }
    return Facing.FUN_004C93D0();
}

// FUNCTION: GAMEMD 0x445F00
void BuildingAView::vf_241(unsigned int flags, int b, int c)
{
    if (vf_254(0)->First != 0) {
        flags |= FUN_00772A90(vf_254(0)->First);
    }
    if (vf_254(1)->First != 0) {
        flags |= FUN_00772A90(vf_254(1)->First);
    }
    FUN_006F8DF0(flags | 1, b, c);
}

// FUNCTION: GAMEMD 0x447AC0
HBCoord BuildingAView::FUN_00447AC0()
{
    int height = Type->FUN_0045ECA0(0) * 128 - 128;
    int width = Type->FUN_0045EC90() * 128 - 128;

    HBCoord c = Location;

    HBCoord temp;
    temp.X = width + c.X;
    temp.Y = height + c.Y;
    temp.Z = c.Z;
    return temp;
}

// A squared difference as a double (inline in retail: the integer is converted and multiplied by itself).
inline double BASquare(int v)
{
    return (double)v * v;
}

// FUNCTION: GAMEMD 0x447E00
//
// The straight-line distance to a target. CAPPED at 75.9% (instruction multiset identical): retail keeps
// the Y difference alone in a stack slot, converts it first and has a 0x24-byte frame; the variants tried
// (named differences, doubles, the inline square helper in three operand orders) all give 0x20.
int BuildingAView::vf_310(BAObjView* target)
{
    HBCoord a, b;
    HBCoord* pa = target->vf_18(&a);
    HBCoord* pb = vf_42(&b, target);
    return (int)FUN_004CAC40(BASquare(pb->X - pa->X) + BASquare(pb->Y - pa->Y) + BASquare(pb->Z - pa->Z));
}

// FUNCTION: GAMEMD 0x447E90
HBCoord BuildingAView::FUN_00447E90(BAObjView* arg)
{
    HBCoord tmp;
    if (Type->unknown_16CB) {
        return *vf_42(&tmp, arg);
    }
    if (!Type->unknown_16A9 && !Type->unknown_16AB) {
        return *vf_18(&tmp);
    }
    return *vf_42(&tmp, arg);
}

// FUNCTION: GAMEMD 0x449410
int BuildingAView::vf_46()
{
    int base = FUN_005F6BD0();

    BATypeView* flags = Type;

    return base + ((flags->unknown_16C5 ? 0x20 : 0) - (flags->unknown_16B7 ? 0x10 : 0));
}

// FUNCTION: GAMEMD 0x449440
int BuildingAView::vf_107(BAOccupierView* occ, int a2, int a3, int a4, int a5)
{
    HBCell cell = occ->Cell;
    BATypeView* type = Type;
    if (type->unknown_408 != 0 && unknown_74) {
        return DAT_0087F7E8.FUN_005657A0(&cell)->FUN_0047C620(type->unknown_67C, type, Owner) ? 0 : 7;
    }
    return type->vf_42(&cell, Owner) ? 0 : 7;
}

// FUNCTION: GAMEMD 0x4494C0
bool BuildingAView::vf_38()
{
    if (!FUN_0070FEC0() && !Type->unknown_1579) {
        if (unknown_6E9 && BState != 0) {
            if (vf_97() != 0x13 && vf_97() != 0x12) {
                return true;
            }
        }
        if (Type->unknown_16C0 && !Owner->unknown_1FA) {
            return true;
        }
    }
    return false;
}

// FUNCTION: GAMEMD 0x449A40
void BuildingAView::vf_136()
{
    vf_135();
}

// FUNCTION: GAMEMD 0x44B760
void BuildingAView::vf_133()
{
    FUN_005B2E50();
}

// FUNCTION: GAMEMD 0x44B770
void BuildingAView::vf_137()
{
    FUN_005B2E90();
}

// FUNCTION: GAMEMD 0x44D5D0
bool BuildingAView::vf_102(BAHouseView* house)
{
    if (FUN_006F4960(house)) {
        if (!DAT_00A8E7AC) {
            Owner->unknown_26C = Type->unknown_DF8;
            Owner->unknown_246 = 1;
        }
        Owner->unknown_1FC = 1;
        if (!FUN_0065AE30() && Owner->FUN_0050B730() && vf_97() != 0x12 && unknown_B4 != 0x12) {
            vf_311(0);
        } else if (!FUN_0065AE30() && !Owner->FUN_0050B730() && house == Owner && vf_97() != 0x12) {
            vf_311(0);
        }
        return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x44D6A0
bool BuildingAView::vf_289(bool flag, int unused)
{
    int mission;
    if (flag && !DAT_00A8E7AC && !DAT_00A8ED6B) {
        FUN_00447780(0);
        mission = 0x12;
    } else {
        FUN_00447780(1);
        mission = 5;
    }
    vf_122(mission, 0);
    return false;
}

// FUNCTION: GAMEMD 0x44D700
int BuildingAView::vf_174()
{
    BATypeView* type = Type;
    switch (type->unknown_3D4) {
    case 2:
        if (type->unknown_16BC) {
            double d = Owner->FUN_004F9750();
            return (int)(type->vf_29() * d);
        }
        return 0;
    default:
        return FUN_00708C30();
    }
}

// FUNCTION: GAMEMD 0x44D760
void BuildingAView::vf_238(void* arg)
{
    if (arg && Owner->FUN_0050B6F0()) {
        HBCoord coordTmp;
        HBCoord* c = vf_19(&coordTmp, 0);
        HBCell cell;
        cell.X = (short)(c->X / 256);
        cell.Y = (short)(c->Y / 256);
        HBCell tmp = cell;
        tmp.FUN_00660B80();
    }
}

// FUNCTION: GAMEMD 0x44D7D0
//
// A direction quantised from the facing: 8 bits without a target, 5 bits when the type allows the
// coarse form, otherwise the one the target slot computes. The pointer-returning form with the
// multiply by 0x800 is what keeps the 5-bit mask (a shift would let the compiler drop it).
HBDir* BuildingAView::vf_194(HBDir* out)
{
    if (Target == 0) {
        unsigned int raw = Facing.FUN_004C93D0().Whole;
        out->Raw = (short)((unsigned char)(((raw >> 7) + 1) >> 1) << 8);
    } else if (vf_255() && !Type->unknown_16C5) {
        unsigned int raw = Facing.FUN_004C93D0().Whole;
        out->Raw = (short)(((((raw >> 10) + 1) >> 1) & 0x1F) * 0x800);
    } else {
        *out = vf_314(Target);
    }
    return out;
}

// FUNCTION: GAMEMD 0x44EB10
int BuildingAView::vf_195()
{
    if (!unknown_6E3 && DAT_00A8B230->Counter.FUN_0065C7E0(0, 0x63) < 0x19 && Type->unknown_EB8 == 7) {
        return RulesInstance->unknown_F70;
    }
    return FUN_00707D20();
}
