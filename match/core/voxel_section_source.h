// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   The voxel section source as its readers see it. FUN_007540f0 (queues one
//   section) calls 0x7564B0 with (section, frame) and reads eight corner
//   vectors at +0x40 of the record it returns. 0x7564B0 itself reads the
//   section table at +0x10 (12-byte rows, first dword = the row's first
//   record) and the record array at +0x14, stride 0xA4
//   (`LEA EDX,[EAX+EAX*4]; LEA EAX,[EAX+EDX*8]; LEA EAX,[ECX+EAX*4]`).
//   Placeholder names: no string or RTTI names these types.
#ifndef GG_MATCH_CORE_VOXEL_SECTION_SOURCE_H
#define GG_MATCH_CORE_VOXEL_SECTION_SOURCE_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../movement/matrix3d_apply_methods.h"

struct VoxelSectionBounds
{
	unsigned char unknown_00[0x40];
	Vector3D Corners[8];   // +0x40
	unsigned char unknown_A0[4];
};
GG_STATIC_ASSERT(offsetof(VoxelSectionBounds, Corners) == 0x40);
GG_STATIC_ASSERT(sizeof(VoxelSectionBounds) == 0xA4);

struct VoxelSectionRow
{
	int FirstRecord;       // +0x00
	int unknown_04[2];     // +0x04
};
GG_STATIC_ASSERT(sizeof(VoxelSectionRow) == 0xC);

struct VoxelSectionSource
{
	unsigned char unknown_00[0x10];
	VoxelSectionRow* Rows;          // +0x10
	VoxelSectionBounds* Records;    // +0x14

	// FUNCTION: GAMEMD 0x7564B0 (defined in voxel_unit_block_00754940.cpp)
	VoxelSectionBounds *FUN_007564b0(int section, int frame);
};
GG_STATIC_ASSERT(offsetof(VoxelSectionSource, Rows) == 0x10);
GG_STATIC_ASSERT(offsetof(VoxelSectionSource, Records) == 0x14);

#endif  // GG_MATCH_CORE_VOXEL_SECTION_SOURCE_H
