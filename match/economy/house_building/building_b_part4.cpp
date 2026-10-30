// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//
// BuildingClass entries 0x4565E0..0x4581F0 of the "building-b" cluster (views: building_b_views.h).

#include <new.h>
#include "building_b_views.h"
#include "../../_layout/building_class.h"
#include "../../_layout/infantry_class.h"
#include "../../_layout/cell_class.h"
#include "../../_layout/map_0087f7e8.h"
#include "../../core/vector_class.h"

// GLOBAL: GAMEMD 0xA83DEC / 0xA83DF8 -- InfantryClass array items and count.
extern InfantryClass** DAT_00A83DEC;
extern int DAT_00A83DF8;
// GLOBAL: GAMEMD 0x89C848 -- the zero coordinate.
extern CoordStruct DAT_0089C848;

// The sum of two screen points.
static inline Point2D PointSum(const Point2D& a, const Point2D& b)
{
    Point2D r;
    r.X = a.X + b.X;
    r.Y = a.Y + b.Y;
    return r;
}

// FUNCTION: GAMEMD 0x4565E0
// Takes the building's foundation cells off the radar and stops tracking it.
void BuildingClass::vf_294()
{
    DynamicVectorClass<Point2D>* foundation = DAT_0087F7E8.FUN_00656580(Type);
    for (int i = 0; i < foundation->Count; i++) {
        Point2D at = PointSum(RadarPosition, foundation->Items[i]);
        DAT_0087F7E8.FUN_00655740(this, at.X, at.Y);
    }
    IsRadarTracked = false;
}

// FUNCTION: GAMEMD 0x456640
// Redraws the radar pixel of every foundation cell.
void BuildingClass::vf_295()
{
    DynamicVectorClass<Point2D>* foundation = DAT_0087F7E8.FUN_00656580(Type);
    for (int i = 0; i < foundation->Count; i++) {
        Point2D point = PointSum(RadarPosition, foundation->Items[i]);
        DAT_0087F7E8.FUN_006562D0(&point);
    }
}

// The function-local white of the flashing glow; the empty destructor is registered with atexit (0x456970 is a RET).
class BuildingBWhite : public ColorStruct
{
public:
    BuildingBWhite()
    {
        R = 0xFF;
        G = 0xFF;
        B = 0xFF;
    }
    ~BuildingBWhite() {}
};

// FUNCTION: GAMEMD 0x456750
void BuildingBView::vf_76(ColorStruct tint)
{
    int level = Func_4566B0();
    if (level > 0 && HasPower && Owner->IsControlledByCurrentPlayer()) {
        if (Type->unknown_1708) {
            static BuildingBWhite white;
            tint = Owner->Color;
            unsigned int phase = (timeGetTime() >> 1) & 0x3FF;
            if (!(phase & 0x200)) {
                if (!(phase & 0x100))
                    tint.FUN_006612C0(~phase & 0xFF, white);
                HBCoord tmp;
                BuildingBFunc_456980(0, 0, *vf_18(&tmp), tint, (float)level, 0, 1);
            }
            unsigned int spark = (unsigned int)((level + 0.5) / BuildingBFunc_4CAC40(2.0) * 60.0) * phase >> 10;
            if (spark > 0x20) {
                HBCoord tmp;
                BuildingBFunc_456980(0, 0, *vf_18(&tmp), Owner->Color, (float)spark, 1, 1);
            }
        } else {
            HBCoord tmp;
            BuildingBFunc_456980(tint.R, 1, *vf_18(&tmp), Owner->Color, (float)level, 0, 1);
        }
    }
}

// FUNCTION: GAMEMD 0x456E00
// CAPPED at 95.2% (multiset identical, vptr register naming only: retail loads the vf_88 vptr into eax, cl into edx).
// Variants tried: ||-chain kept here, an if/goto form, a split frame declaration, a local for the vf_111 result.
void BuildingBView::vf_82(int a)
{
    if (a)
        NeedsRedraw = true;
    Func_6F9DD0(a);
    int frame;
    frame = vf_121();
    BuildingBCellView* cell = vf_111();
    int base = vf_281(cell->unknown_10A);
    if (vf_88() || (unknown_294 && unknown_294->unknown_50 == BuildingBCastBuilding(this)))
        base = Func_70E360(base);
    unknown_short_700 = base;
    unsigned int mask = (unsigned short)base;
    for (int i = 0; i < 21; i++) {
        BuildingBAnimObjView* anim = Anims[i];
        if (anim) {
            if (anim->unknown_C8 && anim->unknown_C8->unknown_35C) {
                anim->unknown_D4 = frame;
                anim->unknown_FC = mask;
            }
            ApplyAnimLevel();
        }
    }
    ApplyAnimLevel();
}

// FUNCTION: GAMEMD 0x456F80
int BuildingClass::vf_281(int a)
{
    if ((DurationRemaining & 2) == 2) {
        if (a > 0x5DC)
            return a - 0x1F4;
        return a + 0x1F4;
    }
    return a;
}

// FUNCTION: GAMEMD 0x457020
// PARTIAL 67.4%, multiset identical. `return false` is the last statement, so
// every refusal shares the final block and the two `return true` blocks stay
// separate (retail has four return blocks). Remaining delta is register choice:
// retail keeps `this` in edi, the two pixel offsets in ebx/ebp and &Location in
// esi; cl keeps this in esi and the offsets in edi/ebx. Also tried: the corner
// from the `here` copy (31.2%) and a &Location pointer local (no change).
bool BuildingBView::vf_201(int* flag)
{
    if (Type->unknown_C9A)
        return false;
    if (InLimbo)
        return false;
    if (Owner->IsControlledByCurrentPlayer())
        return unknown_41B ? true : false;
    {
        HBCoord tmp;
        HBCell cell = BuildingBCellOf(*vf_18(&tmp));
        if (!BuildingBMap.Func_578460(&cell, 1))
            return false;
    }
    int widthPixels = (Type->Func_45ECA0(0) << 8) - 0x100;
    int heightPixels = (Type->Func_45EC90() << 8) - 0x100;
    bool blocked;
    HBCoord here = Location;
    if (BuildingBMap.Func_586360(&here)) {
        HBCoord corner;
        corner.X = Location.X + heightPixels;
        corner.Y = Location.Y + widthPixels;
        corner.Z = Location.Z;
        if (BuildingBMap.Func_586360(&corner) && BuildingBGlobal_00B73550)
            blocked = true;
        else
            blocked = false;
    } else {
        blocked = false;
    }
    if (unknown_220 != 2 && Translucency != 0xF && !IsFogged && !blocked)
        return true;
    if (vf_202()) {
        if (!BuildingBPlayer->IsAlliedWith(Owner) && !IsFogged && !blocked)
            *flag = 1;
        return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x457620
bool BuildingClass::vf_32()
{
    return Type->FUN_00465D40();
}

// FUNCTION: GAMEMD 0x4576F0
// Sends away every infantryman standing on this building's cell who is not heading elsewhere.
void BuildingClass::vf_184()
{
    for (int i = 0; i < DAT_00A83DF8; i++) {
        InfantryClass* unit = DAT_00A83DEC[i];
        BuildingClass* building = DAT_0087F7E8.FUN_00565730(unit->vf_19(0))->FUN_0047C520();
        if (unit->IsAlive && building && building == this) {
            if (unit->Destination == 0 || unit->Destination == building)
                unit->vf_93(DAT_0089C848, 1, 1);
        }
    }
}

// FUNCTION: GAMEMD 0x457770
// CAPPED at 15.4% (multiset: retail-only 5 `mov`, 2 `test`, 1 `add`; cl-only 1 `lea`, 2 `cmp`). Retail keeps the loop
// counters and both cell counts in stack slots and tests the found object and the type flag through registers
// (`mov cl,[eax+0xC9D]; test cl,cl`) where cl emits `cmp byte ptr`. Variants tried: operator+ cell sum, field-wise
// cell sum, goto-based exits, hoisted loop variables, a type local for the flag.
bool BuildingBView::vf_168()
{
    if (!Func_6FBDC0())
        goto refuse;
    {
        HBCell tmp;
        HBCell base = *vf_110(&tmp);
        int width = Type->Func_45EC90();
        int height = Type->Func_45ECA0(0);
        int x;
        int y;
        for (x = -1; x <= width; x++) {
            for (y = -1; y <= height; y++) {
                HBPoint2D zero;
                zero.X = 0;
                zero.Y = 0;
                HBCell cell;
                cell.X = base.X + x;
                cell.Y = base.Y + y;
                BuildingBView* found = BuildingBMap.Func_5657A0(&cell)->Func_47C3D0(&zero, 0, 0);
                if (found == this) {
                    HBCell again = cell;
                    found = BuildingBMap.Func_5657A0(&again)->Func_47EC40(0);
                }
                if (found && found->Owner != Owner && found->vf_33()->unknown_C9D)
                    goto refuse;
            }
        }
    }
    return true;
refuse:
    return false;
}

// FUNCTION: GAMEMD 0x4578C0
// CAPPED at 15.4% (multiset: retail-only 5 `mov`, 2 `test`, 1 `add`; cl-only 1 `lea`, 2 `cmp`). Retail keeps the loop
// counters and both cell counts in stack slots and tests the found object and the type flag through registers
// (`mov cl,[eax+0xC9D]; test cl,cl`) where cl emits `cmp byte ptr`. Variants tried: operator+ cell sum, field-wise
// cell sum, goto-based exits, hoisted loop variables, a type local for the flag.
bool BuildingBView::vf_169()
{
    if (Func_6FBC90())
        goto accept;
    {
        HBCell tmp;
        HBCell base = *vf_110(&tmp);
        int width = Type->Func_45EC90();
        int height = Type->Func_45ECA0(0);
        int x;
        int y;
        for (x = -1; x <= width; x++) {
            for (y = -1; y <= height; y++) {
                HBPoint2D zero;
                zero.X = 0;
                zero.Y = 0;
                HBCell cell;
                cell.X = base.X + x;
                cell.Y = base.Y + y;
                BuildingBView* found = BuildingBMap.Func_5657A0(&cell)->Func_47C3D0(&zero, 0, 0);
                if (found == this) {
                    HBCell again = cell;
                    found = BuildingBMap.Func_5657A0(&again)->Func_47EC40(0);
                }
                if (found && found->Owner != Owner && found->vf_33()->unknown_C9D)
                    goto accept;
            }
        }
    }
    return false;
accept:
    return true;
}

// FUNCTION: GAMEMD 0x457C90
// Clears a planted C4 charge (its timer restarts idle) and starts the invulnerability timer.
void BuildingClass::vf_85(int a, int b, bool c)
{
    if (C4Applied) {
        C4Applied = false;
        CDTimerClass idle;
        idle.StartTime = CurrentFrame;
        idle.TimeLeft = 0;
        C4Timer = idle;
        C4AppliedBy = 0;
    }
    FUN_0070E2B0(a, b, c);
}

// FUNCTION: GAMEMD 0x4581F0
int BuildingClass::vf_258()
{
    return Occupants.Count;
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x89C848
CoordStruct DAT_0089C848;
// GLOBAL: GAMEMD 0xA83D4C
HouseClass* BuildingBPlayer;
// GLOBAL: GAMEMD 0xB73550
int BuildingBGlobal_00B73550;
// END defined globals
