// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x458810.

#include "building_class_voxel_barrel_methods.h"

// GLOBAL: GAMEMD 0x7E4408
// One 32nd of a turn, negated: the double at 0x7E4408.
static const double VoxelBarrelStep_00458810 = -0.19634954084936207;

// A 16-bit binary angle rounded to one of 32 facings, then re-centred on
// facing 8: `(raw >> 10) + 1 >> 1 & 0x1F` picks the nearest 32nd of a turn.
// The helper has to take the DirStruct rather than its raw word: reading
// `->Raw` at the call site instead costs 26 points (see the note below).
static inline int BarrelFacingIndex_00458810(const DirStruct_00458810* dir)
{
    return (int)((((dir->Raw >> 10) + 1) >> 1) & 0x1F) - 8;
}

// FUNCTION: GAMEMD 0x458810
//
// Build the transform that carries a building's voxel barrel from model space
// to its firing pose: translate out to the building pivot, yaw by the turret's
// current facing, translate out to the rotation pivot, pitch by the barrel's
// current facing, translate out to the pitch pivot, then scale uniformly by
// the type's barrel scale.
//
// The facing index helper takes the returned direction object. A named float
// pitch temporary preserves retail's floating-point instruction order before
// the pitch-pivot translations. Read the scale after those translations.
Matrix3D_00458810* BuildingClass_00458810::GetVoxelBarrelOffsetMatrix(
    Matrix3D_00458810& ret)
{
    Matrix3D_00458810 mtx;
    mtx.MakeIdentity();
    mtx.TranslateX((float)Type->VoxelBarrelOffsetToBuildingPivotPoint.X);
    mtx.TranslateY((float)Type->VoxelBarrelOffsetToBuildingPivotPoint.Y);
    mtx.TranslateZ((float)Type->VoxelBarrelOffsetToBuildingPivotPoint.Z);

    DirStruct_00458810 dir;
    int turret = BarrelFacingIndex_00458810(PrimaryFacing.Current(&dir));
    mtx.RotateZ((float)(turret * VoxelBarrelStep_00458810));

    mtx.TranslateX((float)Type->VoxelBarrelOffsetToRotatePivotPoint.X);
    mtx.TranslateY((float)Type->VoxelBarrelOffsetToRotatePivotPoint.Y);
    mtx.TranslateZ((float)Type->VoxelBarrelOffsetToRotatePivotPoint.Z);

    int barrel = BarrelFacingIndex_00458810(BarrelFacing.Current(&dir));
    float pitch = (float)-(barrel * VoxelBarrelStep_00458810);
    mtx.RotateY(pitch);

    mtx.TranslateX((float)Type->VoxelBarrelOffsetToPitchPivotPoint.X);
    mtx.TranslateY((float)Type->VoxelBarrelOffsetToPitchPivotPoint.Y);
    mtx.TranslateZ((float)Type->VoxelBarrelOffsetToPitchPivotPoint.Z);

    float scale = (float)Type->VoxelBarrelScale;
    mtx.ScaleX(scale);
    mtx.ScaleY(scale);
    mtx.ScaleZ(scale);

    ret = mtx;
    return &ret;
}
