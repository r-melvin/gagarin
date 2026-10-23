// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT
//
// The retail block 0x754910..0x758F8F (one unit, header initialisers at
// __xc 0x815694..0x8156E8). Only the bodies listed below are drafted here,
// in retail address order; the other initialisers of the block and the large
// draw routines are not.

#include "../core/header_tuning_globals.h"
#include "../renderer/matrix3d_rotate_methods.h"
#include "../movement/matrix3d_apply_methods.h"
#include "voxel_section_source.h"

// ---- run-time initialised copies of the shared tuning globals --------------

// GLOBAL: GAMEMD 0xB43EF8
extern double DAT_00B43EF8;
// GLOBAL: GAMEMD 0x7F6940
const double DAT_007F6940 = 60.0;

// SYNTHETIC: GAMEMD 0x754940
// GLOBAL: GAMEMD 0xB45180
double DAT_00B45180 = DAT_00B43EF8 / DAT_007F6940;
// SYNTHETIC: GAMEMD 0x754960
// GLOBAL: GAMEMD 0xB450A0
double DAT_00B450A0 = 1.0 / DAT_00B45180;
// SYNTHETIC: GAMEMD 0x754AE0
// GLOBAL: GAMEMD 0xB450A8
TuningCoordInit DAT_00B450A8(128, 128, 0);

// Globals whose constructors are empty: retail keeps each initialiser as a
// lone RET in __xc (entries 0x8156CC, 0x8156D0, 0x8156DC..0x8156E8). Their
// storage is not identified; placeholder names after the initialiser.
struct VoxelEmptyInit
{
    VoxelEmptyInit() {}
};
// SYNTHETIC: GAMEMD 0x754B20
VoxelEmptyInit unknown_00754B20;
// SYNTHETIC: GAMEMD 0x754B30
VoxelEmptyInit unknown_00754B30;
// SYNTHETIC: GAMEMD 0x754BA0
VoxelEmptyInit unknown_00754BA0;
// SYNTHETIC: GAMEMD 0x754BB0
VoxelEmptyInit unknown_00754BB0;
// SYNTHETIC: GAMEMD 0x754BC0
VoxelEmptyInit unknown_00754BC0;
// SYNTHETIC: GAMEMD 0x754BD0
VoxelEmptyInit unknown_00754BD0;

// ---- 0x754C00: the light direction ------------------------------------------

// GLOBAL: GAMEMD 0x88746C
float DAT_0088746C;
// GLOBAL: GAMEMD 0x887470
Vector3D DAT_00887470;
// GLOBAL: GAMEMD 0x887420
Vector3D DAT_00887420;

// A vector built in place from three components.
struct VoxelVector : Vector3D
{
    VoxelVector(float x, float y, float z) { X = x; Y = y; Z = z; }
};

// FUNCTION: GAMEMD 0x754C00
// Rotate the fixed direction (-0.707106, -0.707106, 0) about Y by the angle,
// keep the angle and the result, and derive a second vector from the
// result's X scaled by -6.
void __stdcall FUN_00754C00(float angle)
{
    Matrix3D m;
    m.MakeIdentity();
    DAT_0088746C = angle;
    m.RotateY(angle);
    Vector3D v;
    v.X = -0.707106f;
    v.Y = -0.707106f;
    v.Z = 0.0f;
    Vector3D r;
    // Matrix3DRows is matrix3d_apply_methods.h's view of the same 3x4 rows.
    DAT_00887470 = *Matrix3D_MatrixApply(&r, (Matrix3DRows*)&m, &v);
    DAT_00887420 = VoxelVector(DAT_00887470.X * -6.0f, 0.0f, 0.0f);
}

// ---- small accessors --------------------------------------------------------

// GLOBAL: GAMEMD 0x8467FC
extern int DAT_008467FC[];

// FUNCTION: GAMEMD 0x755AC0
int FUN_00755AC0(int index)
{
    return DAT_008467FC[index];
}

// FUNCTION: GAMEMD 0x5F99E0 (decl; reloc) - takes no arguments (plain RET).
void FUN_005F99E0();

// FUNCTION: GAMEMD 0x755C50
// A forwarder: the call is a tail jump.
void FUN_00755C50()
{
    FUN_005F99E0();
}

// FUNCTION: GAMEMD 0x7564B0
VoxelSectionBounds *VoxelSectionSource::FUN_007564b0(int section, int frame)
{
    return &Records[Rows[section].FirstRecord + frame];
}
