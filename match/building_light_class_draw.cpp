// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Complete 0x435BE0..0x4361C8 body (RET 8) read from the entry-bounded retail
//   function. The two drawing calls are slot 14 (0x38) of the Surface at
//   DSurface::Temp, whose clip rectangle comes from slot 30 (0x78, GetRect,
//   hidden result pointer), matching surface_class.h.
#include "_layout/building_light_class.h"
#include "shadow_block_list_methods.h"
#include "map_class_methods.h"
#include "wwlib/surface/surface_class.h"
#include "matrix3d_rotate_methods.h"
#include "rules_class.h"
#include "tactical_class_coords_to_client_methods.h"
#include "tactical_class_position_methods.h"
#include "_layout/map_0087f7e8.h"
#include "_layout/tag_class.h"
#include "_layout/cell_class.h"
#include "_layout/house_class.h"
#include "building_light_distance.h"

// LIBRARY: GAMEMD 0x7C5F00 (decl; reloc) -- __ftol.
// FUNCTION: GAMEMD 0x4CAD80 (decl; reloc) -- the double-to-double math helper
// applied to the distance ratio.
extern "C" double __cdecl FUN_004CAD80(double ratio);

struct LightVector
{
    float X, Y, Z;
};

// FUNCTION: GAMEMD 0x5AFB80 (decl; reloc) -- result = matrix * vector.
LightVector* FUN_005AFB80(LightVector* result, const Matrix3D* matrix,
                          const LightVector* vector);

// GLOBAL: GAMEMD 0xA8B230 -- the scenario object; a flag word is read at its start.
extern int* DAT_00A8B230;
// GLOBAL: GAMEMD 0x887314 -- DSurface::Temp.
extern Surface* DAT_00887314;
// GLOBAL: GAMEMD 0x887324 -- the tactical object.
extern Tactical* DAT_00887324;
// GLOBAL: GAMEMD 0x886FA0 -- the view rectangle (X, Y, Width, Height).
extern RectangleStruct DAT_00886FA0;
// GLOBAL: GAMEMD 0x7E3A98 -- scale applied to the light's range.
extern const double DAT_007E3A98;

// FUNCTION: GAMEMD 0x435BE0
void BuildingLightClass::FUN_00435BE0(int, int)
{
    if (unknown_DC == 0 || source == 0)
        return;
    if (source->vf_11() != 6)
        return;
    BuildingClass* building = source;
    if (building == 0)
        return;
    if (!building->IsAlive)
        return;
    if (!building->vf_212())
        return;
    if (building->IsFogged)
        return;

    if (*DAT_00A8B230 & 0x1000) {
        CoordStruct location = Location;
        if (DAT_0087F7E8.IsLocationFogged(&location))
            return;
    }

    SpotLightClass* spot = new SpotLightClass(Location, 0x10);

    CoordStruct sourcePosition = building->vf_18();
    CoordStruct ownPosition = vf_18();
    CoordStruct offset;
    CoordStruct* difference = ownPosition.FUN_00437160(&offset, &sourcePosition);
    double squared = (double)difference->X * difference->X
                   + (double)difference->Y * difference->Y
                   + (double)difference->Z * difference->Z;
    int sourceDistance = (int)FUN_004CAC40(squared);

    sourcePosition = building->vf_18();
    ownPosition = vf_18();
    int distance = ownPosition.FUN_00437160(&offset, &sourcePosition)->FUN_0041C380();
    int minimum = RulesInstance->SpotlightLocationRadius;
    int pulse = 0;
    if (distance >= minimum)
        pulse = (distance - minimum) / ((RulesInstance->SpotlightMovementRadius - minimum) / 10);
    if (sourceDistance > minimum && unknown_DC == 3) {
        int age = pulse + 0x50;
        if (age <= 0)
            age = 0;
        if (age >= 0x59)
            age = 0x59;
        spot->Age = age;
    } else {
        spot->Age = 0x50;
    }
    spot->Draw();
    delete spot;

    sourcePosition = building->vf_18();
    ownPosition = vf_18();
    CoordStruct built;
    CoordStruct delta = *built.FUN_0041C230(ownPosition.X - sourcePosition.X,
                                            ownPosition.Y - sourcePosition.Y,
                                            ownPosition.Z - sourcePosition.Z);
    int lightRange = delta.FUN_0041C380();
    int range = FUN_00436E80();
    int rangeLimit = (int)(range * DAT_007E3A98) + RulesInstance->SpotlightRadius;
    if (lightRange < rangeLimit)
        return;

    double angle = FUN_004CAD80((double)rangeLimit / lightRange);
    Matrix3D rotation;
    rotation.MakeIdentity();
    rotation.RotateZ((float)angle);
    LightVector toLight = { (float)(Location.X - sourcePosition.X),
                            (float)(Location.Y - sourcePosition.Y),
                            (float)(Location.Z - sourcePosition.Z) };
    LightVector rotated;
    FUN_005AFB80(&rotated, &rotation, &toLight);
    CoordStruct first;
    first.X = (int)(sourcePosition.X + rotated.X);
    first.Y = (int)(sourcePosition.Y + rotated.Y);
    first.Z = (int)(sourcePosition.Z + rotated.Z);

    rotation.MakeIdentity();
    rotation.RotateZ(-(float)angle);
    FUN_005AFB80(&rotated, &rotation, &toLight);
    CoordStruct second;
    second.X = (int)(sourcePosition.X + rotated.X);
    second.Y = (int)(sourcePosition.Y + rotated.Y);
    second.Z = (int)(sourcePosition.Z + rotated.Z);

    Point2D firstPoint, secondPoint, apexPoint;
    DAT_00887324->CoordsToClient(&first, &firstPoint);
    DAT_00887324->CoordsToClient(&second, &secondPoint);
    CoordStruct apex = sourcePosition;
    apex.Z = sourcePosition.Z + 0x1AE;
    DAT_00887324->CoordsToClient(&apex, &apexPoint);

    firstPoint.X += DAT_00886FA0.X;
    firstPoint.Y += DAT_00886FA0.Y;
    secondPoint.X += DAT_00886FA0.X;
    secondPoint.Y += DAT_00886FA0.Y;
    apexPoint.X += DAT_00886FA0.X;
    apexPoint.Y += DAT_00886FA0.Y;

    int firstLift = -AdjustForZ_006D6070(sourcePosition.Z + 0x190);
    int secondLift = -AdjustForZ_006D6070(sourcePosition.Z + 0xFA);
    int brightness = 0x4B - pulse * 6;

    if (ClipLine(&firstPoint, &apexPoint, &DAT_00886FA0)) {
        RectangleStruct clip = DAT_00887314->GetRect();
        DAT_00887314->unknown_38(&clip, &firstPoint, &apexPoint, brightness,
                                 firstLift, secondLift, false);
    }
    if (ClipLine(&secondPoint, &apexPoint, &DAT_00886FA0)) {
        RectangleStruct clip = DAT_00887314->GetRect();
        DAT_00887314->unknown_38(&clip, &secondPoint, &apexPoint, brightness,
                                 firstLift, secondLift, false);
    }
}


// FUNCTION: GAMEMD 0x75F540 (decl; reloc) -- the point a fraction of the way between two coordinates.
CoordStruct* __fastcall FUN_0075F540(CoordStruct* out, const CoordStruct* b, const CoordStruct* a, float t);
// GLOBAL: GAMEMD 0x89C4F0 -- the cell handed to the tag when a unit is seen near the spotlight.
extern CellStruct DAT_0089C4F0;

// `to` minus `from`, built through the coordinate constructor 0x41C230; expanded inline at its user.
static inline CoordStruct OffsetBetween_004361D0(const CoordStruct& to, const CoordStruct& from)
{
    CoordStruct scratch;
    return *scratch.FUN_0041C230(to.X - from.X, to.Y - from.Y, to.Z - from.Z);
}

// The spotlight's per-frame step. The beam's aim is chosen by the state: 1 sweeps the beam about its
// source by a speed that ramps up and down, 2 spins it steadily, 3 chases the target object until it
// is within reach (and otherwise parks the beam), anything else rests on the light's own position.
// The aim is handed to the object's position slot; while sweeping, every object inner the aim that is not
// an ally and is within the light's reach reports itself to the source building's tag.
// FUNCTION: GAMEMD 0x4361D0
// PARTIAL: best 82.1% positional, identical instruction multiset (513 of 513). The residue is frame layout:
// retail's frame is 0xC0 bytes, ours 0xA8, so the stack slots of the coordinate temporaries and the
// matrix sit at other offsets, and a few operand schedules differ. Tried: references to the position
// temporaries (copied into registers instead), separate hoisted matrix and vector locals (drops an fadd),
// a cast on the cell words (no change).
void BuildingLightClass::vf_23()
{
    if (source == 0 || !source->IsAlive) {
        vf_62();
        return;
    }

    CoordStruct aim;
    switch (unknown_DC) {
    case 1:
        unknown_B0 = unknown_D0 + unknown_B0;
        if (unknown_D8) {
            if (unknown_B0 > RulesInstance->SpotlightAngle * 0.5) {
                unknown_D0 = unknown_D0 - RulesInstance->SpotlightAcceleration;
                if (unknown_D0 < 0.0) {
                    unknown_D0 = 0;
                    unknown_D8 = false;
                }
            } else if (unknown_D0 < RulesInstance->SpotlightSpeed) {
                unknown_D0 = RulesInstance->SpotlightAcceleration + unknown_D0;
            }
        } else if (unknown_B0 < RulesInstance->SpotlightAngle * -0.5) {
            unknown_D0 = RulesInstance->SpotlightAcceleration + unknown_D0;
            if (unknown_D0 > 0.0) {
                unknown_D0 = 0;
                unknown_D8 = true;
            }
        } else if (-RulesInstance->SpotlightSpeed < unknown_D0) {
            unknown_D0 = unknown_D0 - RulesInstance->SpotlightAcceleration;
        }
        {
            Matrix3D turn;
            turn.MakeIdentity();
            turn.RotateZ((float)unknown_B0);
            LightVector offset;
            offset.X = (float)(unknown_C4.X - unknown_B8.X);
            offset.Y = (float)(unknown_C4.Y - unknown_B8.Y);
            offset.Z = (float)(unknown_C4.Z - unknown_B8.Z);
            LightVector turned;
            offset = *FUN_005AFB80(&turned, &turn, &offset);
            int aimX = (int)(unknown_B8.X + offset.X);
            int aimY = (int)(unknown_B8.Y + offset.Y);
            int aimZ = (int)(unknown_B8.Z + offset.Z);
            aim = CoordStructInit(aimX, aimY, aimZ);
        }
        break;
    case 2: {
        CoordStruct origin = source->Location;
        unknown_B0 = RulesInstance->SpotlightSpeed * 4.0 + unknown_B0;
        if (unknown_B0 > 6.283185307179586)
            unknown_B0 = unknown_B0 - 6.283185307179586;
        Matrix3D turn;
        turn.MakeIdentity();
        turn.RotateZ((float)unknown_B0);
        LightVector offset;
        offset.X = (float)(unknown_C4.X - origin.X);
        offset.Y = (float)(unknown_C4.Y - origin.Y);
        offset.Z = (float)(unknown_C4.Z - origin.Z);
        LightVector turned;
        offset = *FUN_005AFB80(&turned, &turn, &offset);
        int aimX = (int)(origin.X + offset.X);
        int aimY = (int)(origin.Y + offset.Y);
        int aimZ = (int)(origin.Z + offset.Z);
        aim = CoordStructInit(aimX, aimY, aimZ);
        break;
    }
    case 3: {
        AbstractClass* chased = unknown_E0;
        if (chased != 0 && static_cast<ObjectClass*>(chased)->IsAlive) {
            int gap = DistanceBetween_00436DA0(chased->vf_18(), source->vf_18());
            if (gap < RulesInstance->SpotlightMovementRadius) {
                CoordStruct to = static_cast<ObjectClass*>(chased)->Location;
                CoordStruct from = Location;
                CoordStruct middle;
                aim = *FUN_0075F540(&middle, &from, &to, 0.25f);
                break;
            }
        }
        FUN_00436BE0(1);
        break;
    }
    default:
        aim = Location;
        break;
    }
    vf_109(aim);

    BuildingClass* building = source->vf_11() == 6 ? source : 0;
    if (unknown_DC == 1 && building != 0 && building->IsAlive && building->vf_212() && building->AttachedTag != 0) {
        bool seen = false;
        CellStruct center = vf_110();
        CoordStruct offset = OffsetBetween_004361D0(vf_18(), source->vf_18());
        int spread = (int)FUN_004CAC40((double)offset.Y * offset.Y + (double)offset.Z * offset.Z + (double)offset.X * offset.X);
        int inner = RulesInstance->SpotlightLocationRadius;
        int ramp;
        if (spread < inner)
            ramp = 0;
        else
            ramp = (spread - inner) / ((RulesInstance->SpotlightMovementRadius - inner) / 10);
        int reach = (int)(ramp * DAT_007E3A98) + RulesInstance->SpotlightRadius + 0x1E;
        HouseClass* owner = source->Owner;
        for (int row = -1; row < 2; row++) {
            CellStruct cell;
            cell.X = center.X + row;
            for (int column = -1; column < 2; column++) {
                cell.Y = column;
                cell.Y += center.Y;
                for (ObjectClass* object = DAT_0087F7E8.FUN_005657A0(CellStruct(cell))->FirstObject; object != 0;
                     object = static_cast<ObjectClass*>(object->NextObject)) {
                    if (object->vf_11() == 0xF || object->vf_11() == 1) {
                        if (!owner->IsAlliedWith(object)) {
                            CoordStruct here = Location;
                            if (DistanceBetween_00436DA0(object->vf_18(), here) < reach)
                                seen = true;
                        }
                    }
                }
            }
        }
        if (seen)
            building->AttachedTag->FUN_006E53A0(0x23, building, DAT_0089C4F0, 0, 0);
    }
}
