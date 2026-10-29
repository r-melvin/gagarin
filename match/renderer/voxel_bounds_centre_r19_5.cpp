// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at the address below.
//   Address index: 0x7564E0.

#include "../_layout/voxel_resource_data.h"

// FUNCTION: GAMEMD 0x7564E0
// Centre of one frame's bounding box: half the sum of two opposite corners.
Vector3D* Obj_00755D10::FUN_007564E0(Vector3D* out, int section, int frame)
{
    VoxelSectionBounds* bounds = &Block1[Block0[section].FirstRecord + frame];
    Vector3D sum(bounds->Corners[4].X + bounds->Corners[2].X, bounds->Corners[4].Y + bounds->Corners[2].Y,
                 bounds->Corners[4].Z + bounds->Corners[2].Z);
    Vector3D half(sum.X * 0.5f, sum.Y * 0.5f, sum.Z * 0.5f);
    *out = half;
    return out;
}
