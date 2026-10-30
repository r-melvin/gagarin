// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Constructor body read from the entry-bounded retail function at 0x435820
//   (0x330 bytes, RET 4). Helper ABIs and globals are read from its call and
//   load operands.
#include "../FUNCTION.H"
#include "../core/rules_class.h"
#include "../renderer/quaternion_matrix_methods.h"

// GLOBAL: GAMEMD 0x89C510 -- a CoordStruct used as the initial value of both light positions.
extern CoordStruct DAT_0089C510;
// GLOBAL: GAMEMD 0x7E2810 -- binary angle to radians scale.
extern const double DAT_007E2810;
// GLOBAL: GAMEMD 0x8B4190 -- the list every BuildingLightClass joins (its
// vtable is the DynamicVectorClass<BuildingLightClass*> one).
extern DynamicVectorClass<BuildingLightClass*> DAT_008B4190;

// FUNCTION: GAMEMD 0x435820
BuildingLightClass::BuildingLightClass(BuildingClass* sourceBuilding)
{
    unknown_B0 = 0;
    unknown_B4 = 0;
    unknown_B8 = DAT_0089C510;
    unknown_C4 = DAT_0089C510;
    unknown_D0 = 0;
    unknown_D4 = 0;
    unknown_D8 = false;
    unknown_DC = 0;
    unknown_E0 = 0;
    source = sourceBuilding;

    DAT_008B4190.AddItem(this);

    if (sourceBuilding == 0)
        return;

    CoordStruct location = sourceBuilding->Location;
    int zOffset = RulesInstance->SpotlightLocationRadius;
    DirStruct heading;
    double angle = (double)((short)sourceBuilding->PrimaryFacing.FUN_004C93D0(&heading)->Raw - 0x3FFF)
                 * DAT_007E2810;
    CoordStruct first;
    first.FUN_00437090((int)(FUN_004CAD00(angle) * zOffset + location.Y),
                       (int)(location.X - FUN_004CACB0(angle) * zOffset), location.Z);
    CoordStruct coordinate;
    coordinate.X = first.X;
    coordinate.Y = first.Y;
    coordinate.Z = first.Z;
    unknown_C4 = coordinate;

    int drawOffset = -RulesInstance->SpotlightMovementRadius;
    angle = (double)((short)sourceBuilding->PrimaryFacing.FUN_004C93D0(&heading)->Raw - 0x3FFF)
          * DAT_007E2810;
    CoordStruct second;
    second.FUN_00437090((int)(FUN_004CAD00(angle) * drawOffset + location.Y),
                        (int)(location.X - FUN_004CACB0(angle) * drawOffset), location.Z);
    unknown_B8.X = second.X;
    unknown_B8.Y = second.Y;
    unknown_B8.Z = second.Z;

    vf_109(coordinate);

    CoordStruct bounds = Location;
    if (vf_54(bounds, 0))
        DAT_0087F778.AddObject(this, false);
    FUN_00436BE0(1);

    int index = -1;
    for (int i = 0; i < DAT_008B4190.Count; i++) {
        if (DAT_008B4190.Items[i] == this) {
            index = i;
            break;
        }
    }
    unknown_D8 = index % 2 != 0;
}
