// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//
// BuildingClass entries 0x4544A0..0x455DA0 of the "building-b" cluster (views: building_b_views.h).

#include <new.h>
#include "building_b_views.h"
#include "../../_layout/building_class.h"

// FUNCTION: GAMEMD 0x4544A0
// Both arms compute one flag and share a single `return 3` / `return 5` pair,
// which is retail's layout (one block each). Returning from inside the arms
// makes cl duplicate the `return 5` epilogue (70.1%).
int BuildingBView::vf_26(bool a, BuildingBTargetView* target)
{
    char level = Translucency;
    if (level != 0) {
        if (level > 10) {
            bool keep;
            if (a) {
                keep = false;
                if (target != 0) {
                    HBCoord loc = Location;
                    HBCell cell = BuildingBCellOf(loc);
                    keep = BuildingBMap.Func_5657A0(&cell)->Func_4870D0(target->unknown_30);
                }
            } else {
                keep = unknown_41A || vf_202() || BuildingBGlobal_00B73550 == 0
                    || (BuildingBGlobal_00A8B238 != 0 && Owner != 0 && BuildingBPlayer != 0
                        && BuildingBPlayer->Func_4F9A50(Owner) && Owner->Func_4F9A50(BuildingBPlayer));
            }
            if (keep)
                return 3;
            return 5;
        }
        return (level > 5) + 1;
    }
    return Func_703860(a, target);
}

// FUNCTION: GAMEMD 0x454DB0
// CAPPED at 0.6% (5 of 648 instructions; 629 compiled; retail-only 18 `mov`, 5 `xor`, 2 `test`, `jge`, `jmp`;
// compiled-only 2 `cmp`, `jl`, 4 `pop`, `ret`). The semantics are recovered (build-up/sell-down translucency ramp,
// the cloak-sensor sweep over the cells under the sensor radius and the neighbour refresh) but the frame is 0x58
// against retail 0x44 and cl keeps `this` in ebp and zero in edi where retail keeps this in esi and zero in ebp, so
// the position-based score collapses. Variants tried: per-use coordinate temporaries, one shared coordinate temporary
// (kept), and wrapping the body in positive ifs instead of early returns.
void BuildingBView::vf_260(bool refresh)
{
    if (Type != 0) {
    HBCoord tmp;
    HBCell cell = BuildingBCellOf(*vf_18(&tmp));
    if (unknown_220 == 1) {
        if (Translucency < 15) {
            char step = Translucency + 1;
            Translucency = step;
            if (step == 1 || step == 6 || step == 11)
                NeedsRedraw = true;
            int level = step;
            if (level == 15 && vf_26(false, 0) == 5)
                level = 16;
            for (int i = 0; i < 21; i++) {
                if (Anims[i])
                    Anims[i]->unknown_178 = level;
            }
            if (Translucency == 15) {
                unknown_220 = 2;
                if (unknown_30C) {
                    unknown_30C->vf_8(1);
                    unknown_30C = 0;
                }
            }
        }
    } else if (unknown_220 == 3) {
        if (Translucency >= 0) {
            if (Translucency > 0)
                Translucency = Translucency - 1;
            char step = Translucency;
            if (step == 0 || step == 5 || step == 10)
                NeedsRedraw = true;
            int level = step;
            if (level == 15 && vf_26(false, 0) == 5)
                level = 16;
            for (int i = 0; i < 21; i++) {
                if (Anims[i])
                    Anims[i]->unknown_178 = level;
            }
            if (Translucency == 0) {
                unknown_220 = 0;
                if (unknown_30C == 0) {
                    HBCoord offset = Type->unknown_coord_768;
                    if (!(offset == BuildingBEmptyCoord)) {
                        BuildingBParticleSystemView* system = 0;
                        HBCoord where = Location + offset;
                        HBCoord here = Location;
                        BuildingBCellView* under = BuildingBMap.Func_565730(&here);
                        system = new BuildingBParticleSystemView(Type->unknown_764, &where, under, 0,
                                                                 &BuildingBEmptyCoord, 0);
                        unknown_30C = system;
                    }
                }
            }
        }
    }
    if (unknown_220 == 2 && vf_169())
        vf_279(0);
    if (unknown_220 == 0 && vf_168())
        vf_280(0);
    if (HasCloakingData && Type->unknown_16C7) {
    BuildingBSurfaceView* surface = BuildingBSurface;
    int owner = Owner->unknown_30;
    int size = surface->vf_31();
    int half = size / 2;
    if (HasCloakingData > 0) {
        if (CloakRadius == Type->unknown_1707) {
            HasCloakingData = 0;
            return;
        }
        CloakRadius = CloakRadius + 1;
        surface->vf_6(0);
        BuildingBColor16 color;
        surface->Func_7BB920(half, half, CloakRadius, *surface->vf_30(&color, 1));
        char* mask = surface->vf_23(0, 0);
        HBCell origin;
        origin.X = cell.X - half;
        origin.Y = cell.Y - half;
        for (int y = 0; y < size; y++) {
            for (int x = 0; x < size; x++) {
                if (*mask++ == 0)
                    continue;
                HBCell at(origin.X + x, origin.Y + y);
                BuildingBCellView* target = BuildingBMap.Func_5657A0(&at);
                if (target->Func_4870B0(owner))
                    continue;
                target->Func_487110(owner);
                for (BuildingBObjectView* object = target->FirstObject; object; object = object->NextObject) {
                    int kind = object->vf_11();
                    if (kind == 1 || kind == 0xF || kind == 2)
                        object->vf_264();
                }
                BuildingBView* building = target->Func_47C520();
                if (building && building->Owner->unknown_30 == owner) {
                                        HBCell there = BuildingBCellOf(*building->vf_18(&tmp));
                    if (there.X == cell.X && there.Y == cell.Y) {
                        CloakRadius = CloakRadius - 1;
                        return;
                    }
                }
            }
        }
    } else {
        if (CloakRadius == 0) {
            HasCloakingData = 0;
            return;
        }
        CloakRadius = CloakRadius - 1;
        surface->vf_6(2);
        BuildingBColor16 color;
        surface->Func_7BB920(half, half, Type->unknown_1707, *surface->vf_30(&color, 0));
        if (CloakRadius)
            surface->Func_7BB920(half, half, CloakRadius, *surface->vf_30(&color, 1));
        char* mask = surface->vf_23(0, 0);
        HBCell origin;
        origin.X = cell.X - half;
        origin.Y = cell.Y - half;
        for (int y = 0; y < size; y++) {
            for (int x = 0; x < size; x++) {
                if (*mask++ != 0)
                    continue;
                HBCell at(origin.X + x, origin.Y + y);
                BuildingBCellView* target = BuildingBMap.Func_5657A0(&at);
                if (!target->Func_4870B0(owner))
                    continue;
                target->Func_487130(owner);
                for (BuildingBObjectView* object = target->FirstObject; object; object = object->NextObject) {
                    int kind = object->vf_11();
                    if (kind == 1 || kind == 0xF || kind == 2)
                        object->vf_264();
                }
                BuildingBView* building = target->Func_47C520();
                if (building && building->Owner->unknown_30 == owner) {
                                        HBCell there = BuildingBCellOf(*building->vf_18(&tmp));
                    if (there.X == at.X && there.Y == at.Y) {
                        if (!refresh) {
                            CloakRadius = CloakRadius + 1;
                            return;
                        }
                    }
                }
            }
        }
        if (CloakRadius == 0) {
            for (int i = 0; i < BuildingBBuildingCount; i++) {
                BuildingBView* other = BuildingBBuildingItems[i];
                if (other->IsAlive && other != this && other->Type->unknown_16C7 && other->vf_212()
                    && !other->HasCloakingData) {
                                        HBCell there = BuildingBCellOf(*other->vf_18(&tmp));
                    short dx = cell.X - there.X;
                    short dy = cell.Y - there.Y;
                    int reach = Type->unknown_1707 + 2;
                    if (dx * dx + dy * dy < reach * reach * 4) {
                        if (other->Type->unknown_16C7) {
                            char old = other->CloakRadius;
                            other->HasCloakingData = 1;
                            if (old == other->Type->unknown_1707)
                                other->CloakRadius = 0;
                            other->NeedsRedraw = true;
                        }
                        if (other->CloakRadius)
                            other->CloakRadius = other->CloakRadius - 1;
                    }
                }
            }
        }
    }
    }
    }
}

// FUNCTION: GAMEMD 0x4555D0
// Every refusal shares one epilogue in retail; written as separate returns cl gives each its own.
bool BuildingBView::vf_212()
{
    int two = 2;
    if (!HasPower && Overpowerers.Count < two)
        goto refuse;
    if (EMPLockRemaining > 0)
        goto refuse;
    if (Health == 0)
        goto refuse;
    if (Type->unknown_1573 && Type->unknown_EE4 > 0 && Owner->Func_4FCE30() < 1.0) {
        if (Overpowerers.Count < two)
            goto refuse;
    }
    {
        BuildingBTypeView* type = Type;
        if (type->unknown_1574) {
            BuildingBHouseView* owner = Owner;
            if (owner->unknown_timer_2A4.GetTimeLeft() != 0)
                goto refuse;
            if (owner->unknown_577B)
                goto refuse;
        }
        if (type->unknown_1552 && !HasEngineer)
            goto refuse;
    }
    if (vf_97() != 0x12 && vf_97() != 0x13)
        return true;
refuse:
    return false;
}

// FUNCTION: GAMEMD 0x4556D0
// CAPPED at 3.8% (4 of 105). Retail pushes one callee-saved register late (ahead of the loop nest) and gives the radius
// ebx, the outer variable ebp, the inner variable esi and the squared outer variable edi; cl takes the radius in ebp and the
// outer variable in edi. Cause unproven. Variants tried: declared loop variables, swapped field arithmetic, an operator+
// cell sum, an operator== empty-cell test, R*R inline, a probe pointer to the cell, a hoisted outer-square local (kept;
// it stopped cl caching the cell word and lifted 455980/455A80 from 10.8/7.9), loop variables declared up front, a deferred
// radiusSq assignment, owner/radius declaration swap.
void BuildingBView::vf_318(HBCell cell)
{
    int radius = Type->unknown_1707;
    int radiusSq = radius * radius;
    int owner = Owner->unknown_30;
    if (cell == BuildingBEmptyCell) {
        HBCoord tmp;
        cell = BuildingBCellOf(*vf_18(&tmp));
    }
    for (int dy = -radius; dy < radius; dy++) {
        int dySq = dy * dy;
        for (int dx = -radius; dx < radius; dx++) {
            if (dx * dx + dySq < radiusSq) {
                HBCell c;
                c.X = cell.X + dx;
                c.Y = cell.Y + dy;
                BuildingBCellView* target = BuildingBMap.Func_5657A0(&c);
                target->Func_487160(owner);
                for (BuildingBObjectView* object = target->FirstObject; object; object = object->NextObject) {
                    int kind = object->vf_11();
                    if (kind == 1 || kind == 0xF || kind == 2)
                        object->vf_264();
                }
            }
        }
    }
}

// FUNCTION: GAMEMD 0x455820
// CAPPED at 24.3% (instruction multiset identical). Retail pushes one callee-saved register late (ahead of the loop nest) and gives the radius
// ebx, the outer variable ebp, the inner variable esi and the squared outer variable edi; cl takes the radius in ebp and the
// outer variable in edi. Cause unproven. Variants tried: declared loop variables, swapped field arithmetic, an operator+
// cell sum, an operator== empty-cell test, R*R inline, a probe pointer to the cell, a hoisted outer-square local (kept;
// it stopped cl caching the cell word and lifted 455980/455A80 from 10.8/7.9), loop variables declared up front, a deferred
// radiusSq assignment, owner/radius declaration swap.
void BuildingBView::vf_317(HBCell cell)
{
    if (!vf_212())
        return;
    int radius = Type->unknown_5F0;
    int radiusSq = radius * radius;
    int owner = Owner->unknown_30;
    if (cell == BuildingBEmptyCell) {
        HBCoord tmp;
        cell = BuildingBCellOf(*vf_18(&tmp));
    }
    for (int dy = -radius; dy < radius; dy++) {
        int dySq = dy * dy;
        for (int dx = -radius; dx < radius; dx++) {
            if (dx * dx + dySq < radiusSq) {
                HBCell c;
                c.X = cell.X + dx;
                c.Y = cell.Y + dy;
                BuildingBCellView* target = BuildingBMap.Func_5657A0(&c);
                target->Func_487150(owner);
                for (BuildingBObjectView* object = target->FirstObject; object; object = object->NextObject) {
                    int kind = object->vf_11();
                    if (kind == 1 || kind == 0xF || kind == 2)
                        object->vf_264();
                }
            }
        }
    }
}

// FUNCTION: GAMEMD 0x455980
// CAPPED at 33.7% (multiset differs by 1 `mov`). Retail pushes one callee-saved register late (ahead of the loop nest) and gives the radius
// ebx, the outer variable ebp, the inner variable esi and the squared outer variable edi; cl takes the radius in ebp and the
// outer variable in edi. Cause unproven. Variants tried: declared loop variables, swapped field arithmetic, an operator+
// cell sum, an operator== empty-cell test, R*R inline, a probe pointer to the cell, a hoisted outer-square local (kept;
// it stopped cl caching the cell word and lifted 455980/455A80 from 10.8/7.9), loop variables declared up front, a deferred
// radiusSq assignment, owner/radius declaration swap.
void BuildingBView::vf_320(HBCell cell)
{
    int radius = Type->unknown_5F4;
    int radiusSq = radius * radius;
    int owner = Owner->unknown_30;
    if (cell == BuildingBEmptyCell) {
        HBCoord tmp;
        cell = BuildingBCellOf(*vf_18(&tmp));
    }
    for (int dy = -radius; dy < radius; dy++) {
        int dySq = dy * dy;
        for (int dx = -radius; dx < radius; dx++) {
            if (dx * dx + dySq < radiusSq) {
                HBCell c;
                c.X = cell.X + dx;
                c.Y = cell.Y + dy;
                BuildingBMap.Func_5657A0(&c)->Func_487180(owner);
            }
        }
    }
}

// FUNCTION: GAMEMD 0x455A80
// CAPPED at 34.8% (multiset differs by 1 `mov`). Retail pushes one callee-saved register late (ahead of the loop nest) and gives the radius
// ebx, the outer variable ebp, the inner variable esi and the squared outer variable edi; cl takes the radius in ebp and the
// outer variable in edi. Cause unproven. Variants tried: declared loop variables, swapped field arithmetic, an operator+
// cell sum, an operator== empty-cell test, R*R inline, a probe pointer to the cell, a hoisted outer-square local (kept;
// it stopped cl caching the cell word and lifted 455980/455A80 from 10.8/7.9), loop variables declared up front, a deferred
// radiusSq assignment, owner/radius declaration swap.
void BuildingBView::vf_319(HBCell cell)
{
    if (!vf_212())
        return;
    int radius = Type->unknown_5F4;
    int radiusSq = radius * radius;
    int owner = Owner->unknown_30;
    if (cell == BuildingBEmptyCell) {
        HBCoord tmp;
        cell = BuildingBCellOf(*vf_18(&tmp));
    }
    for (int dy = -radius; dy < radius; dy++) {
        int dySq = dy * dy;
        for (int dx = -radius; dx < radius; dx++) {
            if (dx * dx + dySq < radiusSq) {
                HBCell c;
                c.X = cell.X + dx;
                c.Y = cell.Y + dy;
                BuildingBMap.Func_5657A0(&c)->Func_487170(owner);
            }
        }
    }
}

// FUNCTION: GAMEMD 0x455C20
// CAPPED at 75.3% (multiset identical, 89 instructions; the frame is 0x3C against retail 0x34, so every stack
// offset after the prologue differs). Variants tried: field-by-field rect sums, an operator+ without the named
// `shifted` temporary, an early-return hit path, and 40 declaration orders of the locals.
HBRect* BuildingBView::vf_75(HBRect* out)
{
    HBCoord tmp;
    HBCoord coord = *vf_43(&tmp);
    HBPoint2D point = BuildingBTactical->Offset;
    HBRect rect;
    if (coord == unknown_coord_64C && point == unknown_point_658) {
        rect = unknown_rect_63C;
    } else {
        HBPoint2D pixel;
        BuildingBTactical->Func_6D2140(&coord, &pixel);
        HBRect typeRect;
        HBRect shifted = *Type->Func_465570(&typeRect) + pixel;
        rect = shifted;
        unknown_coord_64C = coord;
        unknown_point_658 = point;
        unknown_rect_63C = rect;
    }
    *out = rect;
    return out;
}

// FUNCTION: GAMEMD 0x455D50
void BuildingClass::SetDestination(AbstractClass* target, bool a2)
{
    if (CurrentMission == 0x13)
        return;
    if (vf_161() || Type->bools_16A4[0x16B9 - 0x16A4])
        SetArchiveTarget(target);
    TechnoClass::SetDestination(target, a2);
}

// FUNCTION: GAMEMD 0x455DA0
bool BuildingClass::vf_161()
{
    BuildingTypeClass* type = Type;
    int mode = type->Factory;
    if (mode != 0x28 && mode != 0x10 && !type->bools_16A4[0x16AC - 0x16A4] && !type->bools_16A4[0x16A9 - 0x16A4])
        return false;
    return true;
}
