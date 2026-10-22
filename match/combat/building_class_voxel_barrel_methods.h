// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets, slots and constants read numerically off the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI at 0x458810:
//     * `[ESI+0x520]` — the building's type pointer (as at 0x457A10/0x458A00);
//     * `LEA ECX,[ESI+0x370]` and `LEA ECX,[ESI+0x388]` — two FacingClass
//       sub-objects 0x18 apart, each handed to CALL 0x4C93D0
//       (FacingClass::Current, hidden out-pointer, result dereferenced as a
//       dword);
//     * on the building type, `FLD double ptr [ECX+0x1728]` and three
//       CoordStructs of three ints each at 0x1730, 0x173C and 0x1748
//       (`FILD dword ptr [.. + 0x1730/0x1734/0x1738]` and the same pattern at
//       +0x173C and +0x1748);
//     * the rotation constant is the double at 0x7E4408, whose eight bytes
//       read 18 2D 44 54 FB 21 C9 BF = -0.19634954084936207 = -PI/16, i.e.
//       one 32nd of a turn per facing step, negated;
//     * the result is 0xC dwords wide (`MOV ECX,0xC; REP MOVSD`), which pins
//       Matrix3D at 48 bytes, and it is copied to the hidden reference
//       argument at `[ESP+0x44]` with `RET 0x4`.
//   Names cross-checked against YRpp BuildingClass::GetVoxelBarrelOffsetMatrix,
//  ; every offset above is
//   re-derived from the user's binary. NOTE: the double at 0x1728 falls inside
//   what YRpp spells as `char VoxelBarrelFile[0x1C]` at 0x1714 — the binary
//   says that array is 0x14 bytes and a double follows it, so the scale member
//   below is a corrected reading, and its name is transitional.
#ifndef GG_MATCH_COMBAT_BUILDING_CLASS_VOXEL_BARREL_METHODS_H
#define GG_MATCH_COMBAT_BUILDING_CLASS_VOXEL_BARREL_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// A 3x4 row-major affine transform: 0xC dwords, per the REP MOVSD count.
// Every operation below is an out-of-line __thiscall in the retail image.
struct Matrix3D_00458810
{
    float Row[3][4];   // +0x0000

    // FUNCTION: GAMEMD 0x5AE860 (decl; reloc) — Matrix3D::MakeIdentity.
    void MakeIdentity();
    // FUNCTION: GAMEMD 0x5AE980 (decl; reloc) — Matrix3D::TranslateX.
    void TranslateX(float x);
    // FUNCTION: GAMEMD 0x5AE9B0 (decl; reloc) — Matrix3D::TranslateY.
    void TranslateY(float y);
    // FUNCTION: GAMEMD 0x5AE9E0 (decl; reloc) — Matrix3D::TranslateZ.
    void TranslateZ(float z);
    // FUNCTION: GAMEMD 0x5AEAD0 (decl; reloc) — Matrix3D::ScaleX.
    void ScaleX(float factor);
    // FUNCTION: GAMEMD 0x5AEAF0 (decl; reloc) — Matrix3D::ScaleY.
    void ScaleY(float factor);
    // FUNCTION: GAMEMD 0x5AEB20 (decl; reloc) — Matrix3D::ScaleZ.
    void ScaleZ(float factor);
    // FUNCTION: GAMEMD 0x5AF080 (decl; reloc) — Matrix3D::RotateY.
    void RotateY(float theta);
    // FUNCTION: GAMEMD 0x5AF1A0 (decl; reloc) — Matrix3D::RotateZ.
    void RotateZ(float theta);
};
GG_STATIC_ASSERT(offsetof(Matrix3D_00458810, Row) == 0);
GG_STATIC_ASSERT(sizeof(Matrix3D_00458810) == 0x30);

// A 16-bit binary angle, read here as a dword.
struct DirStruct_00458810
{
    unsigned Raw;   // +0x0000
};
GG_STATIC_ASSERT(offsetof(DirStruct_00458810, Raw) == 0);
GG_STATIC_ASSERT(sizeof(DirStruct_00458810) == 4);

// FacingClass — 0x18 bytes (the two sub-objects at +0x370 and +0x388 are that
// far apart); only the current-facing query is reached.
struct Facing_00458810
{
    char _pad000[0x18];   // +0x0000

    // FUNCTION: GAMEMD 0x4C93D0 (decl; reloc) — FacingClass::Current
    // (returns DirStruct by value, so a hidden out-pointer).
    DirStruct_00458810* Current(DirStruct_00458810* out) const;
};
GG_STATIC_ASSERT(sizeof(Facing_00458810) == 0x18);

// A world coordinate triple of ints.
struct Coord_00458810
{
    int X;   // +0x0000
    int Y;   // +0x0004
    int Z;   // +0x0008
};
GG_STATIC_ASSERT(offsetof(Coord_00458810, X) == 0);
GG_STATIC_ASSERT(offsetof(Coord_00458810, Y) == 4);
GG_STATIC_ASSERT(offsetof(Coord_00458810, Z) == 8);
GG_STATIC_ASSERT(sizeof(Coord_00458810) == 0xC);

// BuildingTypeClass — only the voxel-barrel block.
struct BuildingType_00458810
{
    char           _pad000[0x1728];                          // +0x0000
    double         VoxelBarrelScale;                         // +0x1728
    Coord_00458810 VoxelBarrelOffsetToPitchPivotPoint;       // +0x1730
    Coord_00458810 VoxelBarrelOffsetToRotatePivotPoint;      // +0x173C
    Coord_00458810 VoxelBarrelOffsetToBuildingPivotPoint;    // +0x1748
};
GG_STATIC_ASSERT(offsetof(BuildingType_00458810, VoxelBarrelScale)                      == 0x1728 &&
                 offsetof(BuildingType_00458810, VoxelBarrelOffsetToPitchPivotPoint)    == 0x1730 &&
                 offsetof(BuildingType_00458810, VoxelBarrelOffsetToRotatePivotPoint)   == 0x173C &&
                 offsetof(BuildingType_00458810, VoxelBarrelOffsetToBuildingPivotPoint) == 0x1748);

struct BuildingClass_00458810
{
    char                   _pad000[0x370];    // +0x0000
    Facing_00458810        BarrelFacing;      // +0x0370
    Facing_00458810        PrimaryFacing;     // +0x0388
    char                   _pad3A0[0x180];    // +0x03A0
    BuildingType_00458810* Type;              // +0x0520

    // FUNCTION: GAMEMD 0x458810
    Matrix3D_00458810* GetVoxelBarrelOffsetMatrix(Matrix3D_00458810& ret);
};
GG_STATIC_ASSERT(offsetof(BuildingClass_00458810, BarrelFacing)  == 0x370 &&
                 offsetof(BuildingClass_00458810, PrimaryFacing) == 0x388 &&
                 offsetof(BuildingClass_00458810, Type)          == 0x520);

#endif  // GG_MATCH_COMBAT_BUILDING_CLASS_VOXEL_BARREL_METHODS_H
