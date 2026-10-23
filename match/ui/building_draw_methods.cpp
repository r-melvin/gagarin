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

// Cell containing a world coordinate (256 leptons per cell).
static inline CellStruct CoordToCell(const CoordStruct& coord)
{
    CellStruct result;
    result.X = (short)(coord.X / 256);
    result.Y = (short)(coord.Y / 256);
    return result;
}

// Colour-table entries are packed into a 16-bit pixel the way the surface
// format selected by FUN_004BBC90() wants (mode 1 and 2 add one extra form each).
// FUNCTION: GAMEMD 0x43D290
// Draws the building at `point` inside `clip`. Slot 69.
void BuildingClass::vf_69(Point2D* point, RectangleStruct* clip)
{
    CellStruct cell = vf_110();
    SHPStruct* shape = static_cast<SHPStruct*>(vf_27());
    if (!shape)
        return;

    if (this && vf_11() == 6 && BState == 0 && vf_97() == 0x13) {
        for (int i = 0; i < 0x15; i++) {
            if (Anims[i])
                Anims[i]->Invisible = 1;
        }
    }

    if (Type->bools_1700[1])
        return;

    int zAdjust = Type->NormalZAdjust;
    Point2D shift;
    shift.X = 0xC6;
    shift.Y = 0x1BE;
    bool useRoof = false;
    if (vf_97() == 0x10) {
        ObjectClass* produced = FUN_0065AD40(0);
        if (produced) {
            if (produced->vf_33()->bools_D94[0] || produced->vf_33()->BalloonHover)
                useRoof = true;
        }
    }

    unsigned short tintColor = 0;
    if (Airstrike) {
        Rules_008871E0* rules = DAT_008871E0;
        const unsigned char* entry = rules->unknown_1874[rules->unknown_18A4];
        unsigned char c0 = entry[0];
        unsigned char c1 = entry[1];
        unsigned char c2 = entry[2];
        int mode = FUN_004BBC90();
        if (mode == 2)
            tintColor |= (((c0 << 6) | c1) << 5) | c2;
        if (mode == 1 || mode == 2)
            tintColor |= ((((c0 << 5) | (c1 >> 1))) << 6) | c2;
        tintColor |= ((((c0 << 5) | (c1 >> 1))) << 5) | c2;
    }
    if (vf_88() && ForceShielded == 1) {
        Rules_008871E0* rules = DAT_008871E0;
        const unsigned char* entry = rules->unknown_1874[rules->unknown_18B0];
        unsigned char c0 = entry[0];
        unsigned char c1 = entry[1];
        unsigned char c2 = entry[2];
        int mode = FUN_004BBC90();
        if (mode == 2)
            tintColor |= (((c0 << 6) | c1) << 5) | c2;
        if (mode == 1 || mode == 2)
            tintColor |= ((((c0 << 5) | (c1 >> 1))) << 6) | c2;
        tintColor |= ((((c0 << 5) | (c1 >> 1))) << 5) | c2;
    }

    CellStruct standingCell = CoordToCell(vf_18());
    if (FUN_00487950(DAT_0087F7E8.FUN_005657A0(standingCell)))
        tintColor = 0;

    if (vf_97() == 0x18
        && (UnloadTimer.FUN_004A5110() || UnloadTimer.FUN_004A5130() || UnloadTimer.FUN_004A51B0())) {
        int stage = (int)(UnloadTimer.PercentageDone() * Type->GateStages);
        if (UnloadTimer.FUN_004A5130())
            stage = Type->GateStages - stage;
        if (UnloadTimer.FUN_004A51D0())
            stage = 0;
        if (UnloadTimer.FUN_004A51B0())
            stage = Type->GateStages - 1;
        if (stage >= Type->GateStages)
            stage = Type->GateStages - 1;
        if (stage < 0)
            stage = 0;
        SHPStruct* gateShape = static_cast<SHPStruct*>(vf_27());
        int damaged = GetHealthPercentage() <= DAT_008871E0->unknown_1700 ? Type->GateStages + 1 : 0;
        FUN_00705E00(gateShape, damaged + stage, point, clip, 0, 0x100,
                     zAdjust - FUN_006D20E0(FUN_005F5F30()), 2, 1,
                     DAT_0087F7E8.FUN_005657A0(cell)->unknown_10A, tintColor, 0, 0, 0, 0, 0);
        return;
    }

    if (vf_97() == 0x10) {
        if (useRoof) {
            if (Type->RoofDeployingAnim) {
                shape = Type->RoofDeployingAnim;
                zAdjust = -0x28;
            }
        } else if (Type->DeployingAnim) {
            shape = Type->DeployingAnim;
            zAdjust = -0x14;
        }
    }

    int state = vf_97();
    if (state != 0x12 && state != 0x13) {
        shift.X = Type->ZShapePointMove.X + 0xC6;
        shift.Y = Type->ZShapePointMove.Y + 0x1BE;
    }
    Point2D foundation;
    foundation.Y = (Type->GetFoundationHeight(false) << 8) - 0x100;
    foundation.X = (Type->GetFoundationWidth() << 8) - 0x100;
    Point2D transformed;
    Point2D* offset = DAT_00887324->FUN_006D1FE0(&transformed, &foundation);
    shift.X -= offset->X;
    shift.Y -= offset->Y;
    int tint2 = DAT_0089DDBC;
    if (Type->GetFoundationWidth() >= 8)
        tint2 = 0;

    if (clip->Height > 0) {
        int half = shape->unknown_06 / 2;
        int height = FUN_0043EF90() < half ? FUN_0043EF90() : half;
        FUN_00705E00(shape, height, point, clip, 0, 0x100,
                     zAdjust - FUN_006D20E0(FUN_005F5F30()), 2, 1,
                     DAT_0087F7E8.FUN_005657A0(cell)->unknown_10A + Type->ExtraLight,
                     tintColor, tint2, 0, shift.X, shift.Y, 0);
    }

    if (Type->BibShape && BState) {
        FUN_00705E00(Type->BibShape, FUN_0043EF90(), point, clip, 0, 0x100,
                     -1 - FUN_006D20E0(FUN_005F5F30()), 0, 1,
                     DAT_0087F7E8.FUN_005657A0(cell)->unknown_10A + Type->ExtraLight,
                     tintColor, 0, 0, 0, 0, 0);
    }

    if (vf_97() != 0x10)
        return;
    if (useRoof) {
        if (!Type->UnderRoofDoorAnim)
            return;
        int closed = GetHealthPercentage() <= DAT_008871E0->unknown_1700;
        FUN_00705E00(Type->UnderRoofDoorAnim, closed, point, clip, 0, 0x100,
                     -FUN_006D20E0(FUN_005F5F30()), 0, 1,
                     DAT_0087F7E8.FUN_005657A0(cell)->unknown_10A + Type->ExtraLight,
                     tintColor, 0, 0, 0, 0, 0);
        return;
    }
    if (Type->UnderDoorAnim) {
        int closed = GetHealthPercentage() <= DAT_008871E0->unknown_1700;
        FUN_00705E00(Type->UnderDoorAnim, closed, point, clip, 0, 0x100,
                     -FUN_006D20E0(FUN_005F5F30()), 0, 1,
                     DAT_0087F7E8.FUN_005657A0(cell)->unknown_10A + Type->ExtraLight,
                     tintColor, 0, 0, 0, 0, 0);
    }
}
