// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   See building_draw_methods.h. Slot numbers and offsets are those of the
//   primary BuildingClass table at 0x7E3EBC; every field offset below is the
//   one the instruction at the cited retail address uses.
#include "building_draw_methods.h"

// FUNCTION: GAMEMD 0x43CEA0
// Redraws the part of the building that falls inside `rect`; returns whether
// anything overlapped. Slot 65.
bool BuildingClass::vf_65(RectangleStruct* rect, bool force, int draw)
{
    if (DAT_00A8ED6B == 0 && DAT_00B73550 != 0) {
        if (!force && !NeedsRedraw)
            return false;
        if (!IsOnMap)
            return false;
        if (InLimbo)
            return false;
    }

    RectangleStruct extent;
    NeedsRedraw = false;
    *rect = *FUN_00421B60(&extent, rect, &DAT_00886FA0, 0, 0);

    int clipX = DAT_00886FA0.X;
    int clipY = DAT_00886FA0.Y;
    extent = vf_75();
    int left = extent.X + clipX;
    int top = extent.Y + clipY;
    int right = left + extent.Width;
    int bottom = top + extent.Height;

    if (rect->X < right && rect->Y < bottom
        && rect->X + rect->Width > left && rect->Y + rect->Height > top) {
        Point2D point;
        DAT_00887324->FUN_006D2140(vf_43(), &point);
        if (rect->X > DAT_00886FA0.X)
            point.X += DAT_00886FA0.X - rect->X;
        if (rect->Y > DAT_00886FA0.Y)
            point.Y += DAT_00886FA0.Y - rect->Y;
        if (draw) {
            if (!IsFogged)
                vf_313(&point, rect);
        } else {
            vf_69(&point, rect);
        }
        return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x43D030
// Draws the building's deploy/undeploy shape in two strips around `point`.
// Slot 70.
void BuildingClass::vf_70(Point2D* point, RectangleStruct* clip)
{
    CellStruct cell = vf_110();
    SHPStruct* shape = static_cast<SHPStruct*>(vf_27());
    if (!shape)
        return;
    if (Type->bools_1700[1])
        return;
    if (vf_97() == 0x18 && !UnloadTimer.FUN_004A51D0())
        return;
    if (vf_97() == 0x10 && Type->DeployingAnim) {
        ObjectClass* produced = Factory->FUN_004CA160();
        if (produced && produced->vf_33()->bools_D94[0])
            shape = Type->RoofDeployingAnim;
        else
            shape = Type->DeployingAnim;
    }

    Point2D origin = *point;
    int halfHeight = shape->unknown_04 / 2;
    int stripBottom = origin.Y - halfHeight;
    RectangleStruct rect = *clip;
    if (rect.Height > stripBottom)
        rect.Height = stripBottom;
    if (rect.Height > 0) {
        FUN_00705E00(shape, FUN_0043EF90(), &origin, &rect, 0, 0x100,
                     -2 - FUN_006D20E0(FUN_005F5F30()), 2, 0,
                     DAT_0087F7E8.FUN_005657A0(cell)->unknown_10A, 0, 0, 0, 0, 0, 0);
    }

    Point2D lowerOrigin(point->X, origin.Y - stripBottom);
    rect = *clip;
    rect.Y += stripBottom;
    rect.Height = shape->unknown_04;
    if (rect.Y + shape->unknown_04 > clip->Y + clip->Height)
        rect.Height = clip->Y + clip->Height - rect.Y;
    if (rect.Y < clip->Y) {
        int clippedAway = rect.Y - clip->Y;
        rect.Y = clip->Y;
        rect.Height += clippedAway;
        lowerOrigin.Y += clippedAway;
    }
    if (rect.Height > 0) {
        FUN_00705E00(shape, FUN_0043EF90(), &lowerOrigin, &rect, 0, 0x100,
                     -FUN_006D20E0(FUN_005F5F30()), 0, 0,
                     DAT_0087F7E8.FUN_005657A0(cell)->unknown_10A, 0, 0, 0, 0, 0, 0);
    }
}

// BuildingClass::vf_69 (0x43D290) has no body here. Its earlier body scored 30.0%
// and relied on a dead `this &&` test; without it the plain body scores 3.7%.
