// Provenance: own-binary-via-Ghidra
//
// Builds the 32-level voxel shading remap table from a palette and a set of
// per-level brightness scales (a default ramp is generated when none is given).
//   GLOBAL: GAMEMD 0xB45A90  DAT_00b45a90 (float[32], default brightness ramp)

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct VoxelShadePalette
{
	int RangeLow;                 // +0x00
	int RangeHigh;                // +0x04
	int LevelCount;               // +0x08
	int unknown_0C;
	unsigned char *Palette;       // +0x10
	unsigned char *Remap;         // +0x14

	unsigned char FUN_00758ea0(float r, float g, float b, bool inRange);
	void FUN_00758b70(float *scales, int count);
};
GG_STATIC_ASSERT(offsetof(VoxelShadePalette, LevelCount) == 0x08);
GG_STATIC_ASSERT(offsetof(VoxelShadePalette, Palette) == 0x10);
GG_STATIC_ASSERT(offsetof(VoxelShadePalette, Remap) == 0x14);

extern float DAT_00b45a90[32];

// FUNCTION: GAMEMD 0x758b70
void VoxelShadePalette::FUN_00758b70(float *scales, int count)
{
	float *levels;
	if (scales != 0 && count != 0) {
		LevelCount = count;
		levels = scales;
	} else {
		levels = DAT_00b45a90;
		LevelCount = 32;
		int i;
		for (i = 0; i < 16; i++) {
			DAT_00b45a90[i] = (i / 16.0f) * 0.8f + 0.6f;
		}
		for (i = 16; i < 32; i++) {
			DAT_00b45a90[i] = ((float)(i - 16) + i) * 0.0625f + 0.4f;
		}
	}

	int level;
	for (level = 0; level < 16; level++) {
		for (int i = 1; i < 256; i++) {
			bool inRange = i >= RangeLow && i <= RangeHigh;
			float scale = levels[level];
			unsigned char *colour = &Palette[i * 3];
			float r = colour[0] * scale;
			float g = colour[1] * scale;
			float b = colour[2] * scale;
			Remap[(level << 8) | i] = FUN_00758ea0(r, g, b, inRange);
		}
	}
	for (level = 16; level < 32; level++) {
		for (int i = 1; i < 256; i++) {
			bool inRange = i >= RangeLow && i <= RangeHigh;
			float scale = levels[level];
			unsigned char *colour = &Palette[i * 3];
			float r = colour[0] * scale;
			float g = colour[1] * scale;
			float b = colour[2] * scale;
			if (r > 255.0f) {
				r = 255.0f;
			}
			if (g > 255.0f) {
				g = 255.0f;
			}
			if (b > 255.0f) {
				b = 255.0f;
			}
			Remap[(level << 8) | i] = FUN_00758ea0(r, g, b, inRange);
		}
	}
}
