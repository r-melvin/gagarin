// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x458810.

#include "building_class_voxel_barrel_methods.h"

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
// PARTIAL (96.6%, 113/117 instructions; the instruction multiset is identical
// throughout, so every residual is scheduling). Two levers were found:
//   * the facing index helper must take the DirStruct the facing slot returns,
//     not its raw word. Dereferencing `->Raw` at the call site lets cl land the
//     first index chain in EAX where retail uses ECX, and that one register
//     choice then shifts the EAX/ECX/EDX rotation of the type-pointer load by
//     one register across all nine translate calls downstream: 70.9% versus
//     96.6%. Taking the DirStruct by const reference works equally well.
//   * the barrel scale must be read AFTER the pitch-pivot translates, in
//     retail's own textual order; reading it before them costs 31 points.
// The 4-instruction residual is the first translate of the pitch-pivot group,
// where retail issues `FILD [ECX+0x1730]` before the `PUSH ECX` that allocates
// the float argument slot and cl issues it after. It is the only one of the
// nine translate blocks retail schedules that way (the other eight, this one
// included in our output, push first), so it is a scheduler coin-flip rather
// than a shape. Eighteen phrasings were measured across three batches scored
// in one compile each: two separate DirStruct temporaries (59.8%); the raw
// word bound to its own local before the call (49.6% / 96.6% depending on
// where); the index expression written inline with no int locals (70.9%); the
// dir temporary declared after the matrix (70.9%); the multiply written with
// the constant first (70.9%); the pitch pivot bound to a reference (70.9%) or
// to a pointer (70.9%); the type pointer cached once for the whole body
// (7.7%); all three translate groups routed through a free helper (18.8%);
// just the pitch group routed through it (69.2%); and the scale re-read at
// each of the three Scale calls (76.2%).
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
    mtx.RotateY((float)-(barrel * VoxelBarrelStep_00458810));

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
