// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   First batch of the building-a cluster: the short BuildingClass virtual methods. Every body was read
//   from the retail gamemd.exe v1.001 from its entry to its last RET, and every offset it touches is
//   pinned in building_a_views.h. Method names are slot labels (vf_N = primary-table byte offset / 4)
//   or FUN_<addr>: no original name is confirmed for them.

#include "building_a_views.h"
#include "../../_layout/building_class.h"
#include "../../_layout/house_class.h"
#include "../../_layout/tactical.h"

// FUNCTION: GAMEMD 0x772A90 (decl; reloc) - WeaponTypeClass::AllowedThreats, the weapon type in ECX.
unsigned int FUN_00772A90(WeaponTypeClass* weapon);

// FUNCTION: GAMEMD 0x43E900
int BuildingClass::vf_187()
{
    int value = -Tactical::AdjustForZ(FUN_005F5F30());

    BuildingTypeClass* type = Type;

    if (type->bools_16A4[0x16C5 - 0x16A4]) {
        return type->BuildingAnim[9].ZAdjust + value;
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

// The 16-bit direction from `to` towards `from`; inlined at its call sites.
static inline DirStruct DirectionTo(const CoordStruct& to, const CoordStruct& from)
{
    int bx = to.X;
    int ax = from.X;
    DirStruct d;
    d.Raw = (short)((FUN_004CAE30((double)to.Y - from.Y, (double)ax - bx) - DAT_007E2820) * DAT_007E2818);
    return d;
}

// FUNCTION: GAMEMD 0x445E50
//
// The facing towards the target (or the current facing without one). The two X differences are kept in
// integer temporaries of their own (the frame is 0x20 bytes only with them), the angle callee takes the
// Y difference first and the X difference second, and the result is a 16-bit direction.
DirStruct BuildingClass::vf_170()
{
    if (!vf_255() && Target) {
        return DirectionTo(vf_18(), Target->vf_18());
    }
    return PrimaryFacing.FUN_004C93D0();
}

// FUNCTION: GAMEMD 0x445F00
AbstractClass* BuildingClass::vf_241(unsigned int threat, CoordStruct* coord, bool a3)
{
    if (vf_254(0)->WeaponType != 0) {
        threat |= FUN_00772A90(vf_254(0)->WeaponType);
    }
    if (vf_254(1)->WeaponType != 0) {
        threat |= FUN_00772A90(vf_254(1)->WeaponType);
    }
    return TechnoClass::vf_241(threat | 1, coord, a3);
}

// FUNCTION: GAMEMD 0x447AC0
CoordStruct BuildingClass::vf_18()
{
    int height = Type->GetFoundationHeight(false) * 128 - 128;
    int width = Type->GetFoundationWidth() * 128 - 128;

    CoordStruct c = Location;

    CoordStruct temp;
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

// The straight-line distance between two coordinates; inlined at its call sites.
static inline int Distance(const CoordStruct& b, const CoordStruct& a)
{
    return (int)FUN_004CAC40(BASquare(b.X - a.X) + BASquare(b.Y - a.Y) + BASquare(b.Z - a.Z));
}

// FUNCTION: GAMEMD 0x447E00
//
// The straight-line distance to a target. CAPPED at 75.9% (instruction multiset identical): retail keeps
// the Y difference alone in a stack slot, converts it first and has a 0x24-byte frame; the variants tried
// (named differences, doubles, the inline square helper in three operand orders) all give 0x20.
int BuildingClass::vf_310(AbstractClass* target)
{
    return Distance(vf_42(target), target->vf_18());
}

// FUNCTION: GAMEMD 0x447E90
CoordStruct BuildingClass::vf_19(AbstractClass* arg)
{
    if (Type->bools_16A4[0x16CB - 0x16A4]) {
        return vf_42(arg);
    }
    if (!Type->bools_16A4[0x16A9 - 0x16A4] && !Type->bools_16A4[0x16AB - 0x16A4]) {
        return vf_18();
    }
    return vf_42(arg);
}

// FUNCTION: GAMEMD 0x449410
int BuildingClass::GetYSort() const
{
    int base = ObjectClass::GetYSort();

    BuildingTypeClass* flags = Type;

    return base + ((flags->bools_16A4[0x16C5 - 0x16A4] ? 0x20 : 0) - (flags->bools_16A4[0x16B7 - 0x16A4] ? 0x10 : 0));
}

// FUNCTION: GAMEMD 0x449440
int BuildingClass::vf_107(CellClass* target, int a2, int a3, int a4, int a5)
{
    CellStruct cell = target->MapCoords;
    BuildingTypeClass* type = Type;
    if (type->UndeploysInto != 0 && IsOnMap) {
        return DAT_0087F7E8.FUN_005657A0(&cell)->FUN_0047C620(type->SpeedType, type, Owner) ? 0 : 7;
    }
    return type->vf_42(&cell, Owner) ? 0 : 7;
}

// FUNCTION: GAMEMD 0x4494C0
bool BuildingClass::vf_38()
{
    if (!IsBeingDrained() && !Type->bools_1570[0x1579 - 0x1570]) {
        if (HasBuildUp && BState != 0) {
            if (vf_97() != 0x13 && vf_97() != 0x12) {
                return true;
            }
        }
        if (Type->bools_16A4[0x16C0 - 0x16A4] && !Owner->FirestormActive) {
            return true;
        }
    }
    return false;
}

// FUNCTION: GAMEMD 0x449A40
int BuildingClass::vf_136()
{
    return vf_135();
}

// FUNCTION: GAMEMD 0x44B760
int BuildingClass::vf_133()
{
    return MissionClass::vf_133();
}

// FUNCTION: GAMEMD 0x44B770
int BuildingClass::vf_137()
{
    return MissionClass::vf_137();
}

// FUNCTION: GAMEMD 0x44D5D0
bool BuildingClass::vf_102(HouseClass* house)
{
    if (TechnoClass::vf_102(house)) {
        if (!DAT_00A8E7AC) {
            Owner->LastBuiltBuildingType = Type->ArrayIndex;
            Owner->IsBuiltSomething = 1;
        }
        Owner->RecheckTechTree = 1;
        if (!HasAnyLink() && Owner->IsControlledByHuman() && vf_97() != 0x12 && QueuedMission != 0x12) {
            vf_311(0);
        } else if (!HasAnyLink() && !Owner->IsControlledByHuman() && house == Owner && vf_97() != 0x12) {
            vf_311(0);
        }
        return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x44D6A0
bool BuildingClass::EnterIdleMode(bool initial, bool a2)
{
    int mission;
    if (initial && !DAT_00A8E7AC && !DAT_00A8ED6B) {
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
int BuildingClass::vf_174()
{
    BuildingTypeClass* type = Type;
    switch (type->PipScale) {
    case 2:
        if (type->bools_16A4[0x16BC - 0x16A4]) {
            double d = Owner->GetWeedStoragePercentage();
            return (int)(type->vf_29() * d);
        }
        return 0;
    default:
        return TechnoClass::vf_174();
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
int BuildingClass::vf_195()
{
    if (!HasBeenCaptured && DAT_00A8B230->Counter.FUN_0065C7E0(0, 0x63) < 0x19 && Type->Factory == 7) {
        return RulesInstance->unknown_F70;
    }
    return TechnoClass::vf_195();
}
