// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
#ifndef GG_CORE_VOXEL_SHADE_PALETTE_H
#define GG_CORE_VOXEL_SHADE_PALETTE_H
#include <stddef.h>
#include "../_rt/gg_static_assert.h"
// Gagarin view name retained from the shading method; no original class
// spelling is asserted. Native lifetime entries pin ownership DWORDs at +18/+1C.
struct VoxelShadePalette
{
	// FUNCTION: GAMEMD 0x758950
	VoxelShadePalette(unsigned char* palette, unsigned char* remap);
	// FUNCTION: GAMEMD 0x7589C0
	~VoxelShadePalette();
	int RangeLow;                 // +0x00
	int RangeHigh;                // +0x04
	int LevelCount;               // +0x08
	int unknown_0C;
	unsigned char *Palette;       // +0x10
	unsigned char *Remap;         // +0x14

	int unknown_18;
	int unknown_1C;

	// FUNCTION: GAMEMD 0x758B70
	void FUN_00758b70(float *scales, int count);
	// FUNCTION: GAMEMD 0x758EA0 (declaration)
	unsigned char FUN_00758ea0(float r, float g, float b, bool inRange);
};
GG_STATIC_ASSERT(offsetof(VoxelShadePalette, RangeLow) == 0x0);
GG_STATIC_ASSERT(offsetof(VoxelShadePalette, RangeHigh) == 0x4);
GG_STATIC_ASSERT(offsetof(VoxelShadePalette, LevelCount) == 0x8);
GG_STATIC_ASSERT(offsetof(VoxelShadePalette, unknown_0C) == 0xc);
GG_STATIC_ASSERT(offsetof(VoxelShadePalette, Palette) == 0x10);
GG_STATIC_ASSERT(offsetof(VoxelShadePalette, Remap) == 0x14);
GG_STATIC_ASSERT(offsetof(VoxelShadePalette, unknown_18) == 0x18);
GG_STATIC_ASSERT(offsetof(VoxelShadePalette, unknown_1C) == 0x1c);
GG_STATIC_ASSERT(sizeof(VoxelShadePalette) == 32);
#endif
