// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VoxelStruct destruction at 0x5F61A0 deletes these two owned resources.
// ObjectType's loader allocates 0x1C bytes before 0x755CD0 (0x5F8183), and
// 0x10 before 0x5BD570 (0x5F81FB). Names remain address placeholders.
#ifndef GG_MATCH_LAYOUT_VOXEL_RESOURCE_DATA_H
#define GG_MATCH_LAYOUT_VOXEL_RESOURCE_DATA_H
#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "matrix3d.h"
class FileClass;

// Native 0x7564B0: 12-byte section rows index 164-byte bound records.
struct VoxelSectionBounds
{
    unsigned char* unknown_00;
    unsigned char* unknown_04;
    unsigned char* unknown_08;
    float unknown_0C;
    Matrix3D unknown_10;
    Vector3D Corners[8];
    unsigned char unknown_A0[4];
};
GG_STATIC_ASSERT(offsetof(VoxelSectionBounds, Corners) == 0x40);
GG_STATIC_ASSERT(sizeof(VoxelSectionBounds) == 0xA4);
struct VoxelSectionRow
{
    int FirstRecord;
    int unknown_04;
    unsigned char unknown_08;
    unsigned char unknown_09[3];
};
GG_STATIC_ASSERT(offsetof(VoxelSectionRow, FirstRecord) == 0);
GG_STATIC_ASSERT(sizeof(VoxelSectionRow) == 12);

struct Obj_00755D10
{
    // FUNCTION: GAMEMD 0x755CD0 (RET 8)
    Obj_00755D10(FileClass* file, int unknown);
    // FUNCTION: GAMEMD 0x755D60
    void FUN_00755D60();
    // FUNCTION: GAMEMD 0x755DB0 (declaration)
    int FUN_00755DB0(FileClass* file, int unknown);
    // FUNCTION: GAMEMD 0x7564A0
    VoxelSectionRow* FUN_007564A0(int section);
    // FUNCTION: GAMEMD 0x7564B0
    VoxelSectionBounds* FUN_007564b0(int section, int frame);
    // FUNCTION: GAMEMD 0x7564E0 -- centre of the frame's bounds; returns `out`.
    Vector3D* FUN_007564E0(Vector3D* out, int section, int frame);
    // FUNCTION: GAMEMD 0x755D10
    ~Obj_00755D10();
    unsigned char unknown_00;
    unsigned char unknown_01[3];
    unsigned int unknown_04;
    unsigned int unknown_08;
    unsigned int unknown_0C;
    VoxelSectionRow* Block0;
    VoxelSectionBounds* Block1;
    unsigned char* Block2;
};
GG_STATIC_ASSERT(offsetof(Obj_00755D10, Block0) == 0x10);
GG_STATIC_ASSERT(offsetof(Obj_00755D10, Block1) == 0x14);
GG_STATIC_ASSERT(offsetof(Obj_00755D10, Block2) == 0x18);
GG_STATIC_ASSERT(sizeof(((Obj_00755D10*)0)->Block0) == 4);
GG_STATIC_ASSERT(sizeof(((Obj_00755D10*)0)->Block1) == 4);
GG_STATIC_ASSERT(sizeof(((Obj_00755D10*)0)->Block2) == 4);
GG_STATIC_ASSERT(sizeof(Obj_00755D10) == 0x1C);

struct Obj_005BD5A0
{
    // FUNCTION: GAMEMD 0x5BD570 (RET 4)
    Obj_005BD5A0(FileClass* file);
    // FUNCTION: GAMEMD 0x5BD5C0 (declaration)
    int FUN_005BD5C0(FileClass* file);
    // FUNCTION: GAMEMD 0x5BD7C0
    void FUN_005BD7C0();
    // FUNCTION: GAMEMD 0x5BD730 -- scales translation components of each matrix.
    void FUN_005BD730(float scale);
    // FUNCTION: GAMEMD 0x5BD5A0
    ~Obj_005BD5A0();
    unsigned char unknown_00;
    unsigned char unknown_01[3];
    unsigned int unknown_04;
    unsigned int unknown_08;
    Matrix3D* unknown_0C;
};
GG_STATIC_ASSERT(offsetof(Obj_005BD5A0, unknown_0C) == 0xC);
GG_STATIC_ASSERT(sizeof(((Obj_005BD5A0*)0)->unknown_0C) == 4);
GG_STATIC_ASSERT(sizeof(Obj_005BD5A0) == 0x10);
GG_STATIC_ASSERT(offsetof(Obj_00755D10, unknown_00) == 0x0);
GG_STATIC_ASSERT(offsetof(Obj_00755D10, unknown_04) == 0x4);
GG_STATIC_ASSERT(offsetof(Obj_00755D10, unknown_08) == 0x8);
GG_STATIC_ASSERT(offsetof(Obj_00755D10, unknown_0C) == 0xc);
GG_STATIC_ASSERT(offsetof(Obj_005BD5A0, unknown_00) == 0x0);
GG_STATIC_ASSERT(offsetof(Obj_005BD5A0, unknown_04) == 0x4);
GG_STATIC_ASSERT(offsetof(Obj_005BD5A0, unknown_08) == 0x8);
GG_STATIC_ASSERT(offsetof(VoxelSectionBounds, unknown_00) == 0);
GG_STATIC_ASSERT(offsetof(VoxelSectionBounds, unknown_04) == 4);
GG_STATIC_ASSERT(offsetof(VoxelSectionBounds, unknown_08) == 8);
GG_STATIC_ASSERT(offsetof(VoxelSectionBounds, unknown_0C) == 12);
GG_STATIC_ASSERT(offsetof(VoxelSectionBounds, unknown_10) == 16);
GG_STATIC_ASSERT(offsetof(VoxelSectionBounds, unknown_A0) == 0xA0);
GG_STATIC_ASSERT(offsetof(VoxelSectionRow, unknown_04) == 4);
GG_STATIC_ASSERT(offsetof(VoxelSectionRow, unknown_08) == 8);
#endif
