// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Record producer 0x7540F0 writes the fields below; the pointer-array walk
// at 0x754373..0x754402 passes each 0x88-byte record to 0x756590.
// The C++ type names describe the recovered uses, not retail source names.
#ifndef GG_MATCH_CORE_VOXEL_DRAW_ENTRY_H
#define GG_MATCH_CORE_VOXEL_DRAW_ENTRY_H
#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/vector3d.h"

struct Obj_00755D10;

struct BoundsFloat3
{
    BoundsFloat3() {}
    BoundsFloat3(float x, float y, float z) : X(x), Y(y), Z(z) {}
    float X;
    float Y;
    float Z;
};
GG_STATIC_ASSERT(offsetof(BoundsFloat3, X) == 0);
GG_STATIC_ASSERT(offsetof(BoundsFloat3, Y) == 4);
GG_STATIC_ASSERT(offsetof(BoundsFloat3, Z) == 8);
GG_STATIC_ASSERT(sizeof(BoundsFloat3) == 0x0C);

struct VoxelDrawEntry
{
    Obj_00755D10* Source; // +0x00
    int Section;          // +0x04
    int Frame;            // +0x08
    int MinZCorner;       // +0x0C
    BoundsFloat3 Min;     // +0x10
    BoundsFloat3 Max;     // +0x1C
    Vector3D Corners[8];  // +0x28
};
GG_STATIC_ASSERT(offsetof(VoxelDrawEntry, Source) == 0x00);
GG_STATIC_ASSERT(sizeof(((VoxelDrawEntry*)0)->Source) == 4);
GG_STATIC_ASSERT(offsetof(VoxelDrawEntry, Section) == 0x04);
GG_STATIC_ASSERT(sizeof(((VoxelDrawEntry*)0)->Section) == 4);
GG_STATIC_ASSERT(offsetof(VoxelDrawEntry, Frame) == 0x08);
GG_STATIC_ASSERT(sizeof(((VoxelDrawEntry*)0)->Frame) == 4);
GG_STATIC_ASSERT(offsetof(VoxelDrawEntry, MinZCorner) == 0x0C);
GG_STATIC_ASSERT(sizeof(((VoxelDrawEntry*)0)->MinZCorner) == 4);
GG_STATIC_ASSERT(offsetof(VoxelDrawEntry, Min) == 0x10);
GG_STATIC_ASSERT(sizeof(((VoxelDrawEntry*)0)->Min) == 0x0C);
GG_STATIC_ASSERT(offsetof(VoxelDrawEntry, Max) == 0x1C);
GG_STATIC_ASSERT(sizeof(((VoxelDrawEntry*)0)->Max) == 0x0C);
GG_STATIC_ASSERT(offsetof(VoxelDrawEntry, Corners) == 0x28);
GG_STATIC_ASSERT(sizeof(((VoxelDrawEntry*)0)->Corners[0]) == 0x0C);
GG_STATIC_ASSERT(sizeof(((VoxelDrawEntry*)0)->Corners) == 0x60);
GG_STATIC_ASSERT(sizeof(VoxelDrawEntry) == 0x88);
#endif // GG_MATCH_CORE_VOXEL_DRAW_ENTRY_H
