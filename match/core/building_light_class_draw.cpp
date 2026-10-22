// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Complete 0x435BE0..0x4361C8 body (RET 8) read from the entry-bounded retail
//   function. The two drawing calls are slot 14 (0x38) of the Surface at
//   DSurface::Temp, whose clip rectangle comes from slot 30 (0x78, GetRect,
//   hidden result pointer), matching surface_class.h.
#include "building_light_class.h"
#include "../renderer/shadow_block_list_methods.h"
#include "../map/map_class_methods.h"
#include "../renderer/surface_class.h"
#include "../renderer/matrix3d_rotate_methods.h"
#include "../core/rules_class.h"
#include "../ui/tactical_class_coords_to_client_methods.h"
#include "../ui/tactical_class_position_methods.h"

// FUNCTION: GAMEMD 0x7C5F00 (decl; reloc) -- __ftol.
// FUNCTION: GAMEMD 0x4CAD80 (decl; reloc) -- the double-to-double math helper
// applied to the distance ratio.
extern "C" double __cdecl FUN_004CAD80(double ratio);
// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc) -- sqrt.
extern "C" double __cdecl FUN_004CAC40(double value);

struct LightVector
{
    float X, Y, Z;
};

// FUNCTION: GAMEMD 0x5AFB80 (decl; reloc) -- result = matrix * vector.
LightVector* __fastcall FUN_005AFB80(LightVector* result, const Matrix3D* matrix,
                                     const LightVector* vector);

// GLOBAL: GAMEMD 0xA8B230 -- the scenario object; a flag word is read at its start.
extern int* DAT_00A8B230;
// GLOBAL: GAMEMD 0x87F7E8 -- the map.
extern MapClass DAT_0087F7E8;
// GLOBAL: GAMEMD 0x887314 -- DSurface::Temp.
extern Surface* DAT_00887314;
// GLOBAL: GAMEMD 0x887324 -- the tactical object.
extern Tactical_006D2140* DAT_00887324;
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

    Payload_005FF250 payload = { Location.X, Location.Y, Location.Z };
    SpotLightClass* spot = new SpotLightClass(payload, 0x10);

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
    int minimum = RulesInstance->unknown_78C;
    int pulse = 0;
    if (distance >= minimum)
        pulse = (distance - minimum) / ((RulesInstance->unknown_788 - minimum) / 10);
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
    int rangeLimit = (int)(range * DAT_007E3A98) + RulesInstance->unknown_7A8;
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
