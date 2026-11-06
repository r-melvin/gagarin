// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Constructor body read from the entry-bounded retail function at 0x435820
//   (0x330 bytes, RET 4). Helper ABIs and globals are read from its call and
//   load operands. IPersistStream::Load at 0x436950 and the scalar deleting destructor at 0x4370C0 (slot 8, the
//   destructor expanded) come from the same image; offsets read numerically.
#include <new.h>
#include "FUNCTION.H"
#include "rules_class.h"
#include "quaternion_matrix_methods.h"
#include "_layout/layer_class.h"
#include "_layout/swizzle_manager_class.h"

// GLOBAL: GAMEMD 0x89C510 -- a CoordStruct used as the initial value of both light positions.
extern CoordStruct DAT_0089C510;
// GLOBAL: GAMEMD 0x7E2810 -- binary angle to radians scale.
extern const double DAT_007E2810;
// GLOBAL: GAMEMD 0x8B4190 -- the list every BuildingLightClass joins (its
// vtable is the DynamicVectorClass<BuildingLightClass*> one).
extern DynamicVectorClass<BuildingLightClass*> DAT_008B4190;

// FUNCTION: GAMEMD 0x435820
//
// PARTIAL (67.2% positional, 77.6% aligned). Retail's frame is 0x54 bytes, ours 0x5C-0x6C: one coordinate
// temporary fewer. The member list stores the vptrs after the members as retail does.
BuildingLightClass::BuildingLightClass(BuildingClass* sourceBuilding)
    : unknown_B0(0), unknown_B8(DAT_0089C510), unknown_C4(DAT_0089C510), unknown_D0(0),
      unknown_D8(false), unknown_DC(0), unknown_E0(0), source(sourceBuilding)
{
    DAT_008B4190.AddItem(this);

    if (sourceBuilding == 0)
        return;

    CoordStruct location = sourceBuilding->Location;
    int zOffset = RulesInstance->SpotlightLocationRadius;
    DirStruct heading;
    double angle = (double)((short)sourceBuilding->PrimaryFacing.FUN_004C93D0(&heading)->Raw - 0x3FFF)
                 * DAT_007E2810;
    CoordStruct first;
    CoordStruct coordinate;
    coordinate = *first.FUN_00437090((int)(FUN_004CAD00(angle) * zOffset + location.Y),
                       (int)(location.X - FUN_004CACB0(angle) * zOffset), location.Z);
    unknown_C4 = coordinate;

    location = sourceBuilding->Location;
    int drawOffset = -RulesInstance->SpotlightMovementRadius;
    angle = (double)((short)sourceBuilding->PrimaryFacing.FUN_004C93D0(&heading)->Raw - 0x3FFF)
          * DAT_007E2810;
    CoordStruct second;
    unknown_B8 = *second.FUN_00437090((int)(FUN_004CAD00(angle) * drawOffset + location.Y),
                        (int)(location.X - FUN_004CACB0(angle) * drawOffset), location.Z);

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

// FUNCTION: GAMEMD 0x436950
// Loads the object prefix, rebuilds the object around the loaded bytes and registers the two
// building pointers for swizzling.
HRESULT __stdcall BuildingLightClass::Load(IStream* pStm)
{
    HRESULT hr = ObjectClass::Load(pStm);
    if (hr >= 0) {
        new(this) BuildingLightClass(AbstractNoInit());
        DAT_00B0C110.SwizzleManagerClass::vf_4(&source);
        DAT_00B0C110.SwizzleManagerClass::vf_4(&unknown_E0);
    }
    return hr;
}

// FUNCTION: GAMEMD 0x436F40
// Slot 13: feed the object prefix, the accumulators, both spotlight coordinates, the flag and the
// two referenced objects' identities to the synchronisation checksum.
void BuildingLightClass::vf_13(Obj_004A1D30* crc)
{
    ObjectClass::vf_13(crc);
    crc->FUN_004A1D90(unknown_B0);
    crc->FUN_004A1D50(unknown_B8.X);
    crc->FUN_004A1D50(unknown_B8.Y);
    crc->FUN_004A1D50(unknown_B8.Z);
    crc->FUN_004A1D50(unknown_C4.X);
    crc->FUN_004A1D50(unknown_C4.Y);
    crc->FUN_004A1D50(unknown_C4.Z);
    crc->FUN_004A1D90(unknown_D0);
    crc->FUN_004A1CA0(unknown_D8);
    crc->FUN_004A1D50(unknown_DC);
    if (unknown_E0) {
        crc->FUN_004A1D50(unknown_E0->vf_rtti_4());
    }
    if (source) {
        crc->FUN_004A1D50(source->vf_rtti_4());
    }
}

// SYNTHETIC: GAMEMD 0x4370C0
// Scalar deleting destructor (primary slot 8), the destructor expanded in place.
BuildingLightClass::~BuildingLightClass()
{
    if (vf_53())
        DAT_0087F778.RemoveObject(this);
    DAT_008B4190.RemoveItem(this);
}
