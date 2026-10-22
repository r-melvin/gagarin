// Provenance: own-binary-via-Ghidra
//
// Queues one voxel section for drawing: records its source, projects the eight
// bounding-box corners through the supplied matrix and grows both the
// per-entry and the global screen-space bounds.
//   GLOBAL: GAMEMD 0xB2D5E0  DAT_00b2d5e0 (Vector3D, global bounds minimum)
//   GLOBAL: GAMEMD 0xB2D820  DAT_00b2d820 (int, queued entry count)
//   GLOBAL: GAMEMD 0xB2D948  DAT_00b2d948 (Vector3D, global bounds maximum)
//   GLOBAL: GAMEMD 0xB2D958  DAT_00b2d958 (VoxelDrawEntry[], stride 0x88)

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../movement/matrix3d_apply_methods.h"
#include "voxel_section_source.h"

struct BoundsFloat3
{
	BoundsFloat3() {}
	BoundsFloat3(float x, float y, float z) : X(x), Y(y), Z(z) {}
	float X;
	float Y;
	float Z;
};

struct VoxelDrawEntry
{
	VoxelSectionSource *Source;   // +0x00
	int Section;                  // +0x04
	int Frame;                    // +0x08
	int MinZCorner;               // +0x0C
	BoundsFloat3 Min;             // +0x10
	BoundsFloat3 Max;             // +0x1C
	Vector3D Corners[8];          // +0x28
};
GG_STATIC_ASSERT(offsetof(VoxelDrawEntry, MinZCorner) == 0x0C);
GG_STATIC_ASSERT(offsetof(VoxelDrawEntry, Min) == 0x10);
GG_STATIC_ASSERT(offsetof(VoxelDrawEntry, Max) == 0x1C);
GG_STATIC_ASSERT(offsetof(VoxelDrawEntry, Corners) == 0x28);
GG_STATIC_ASSERT(sizeof(VoxelDrawEntry) == 0x88);   // array stride (index * 0x88)

extern BoundsFloat3 DAT_00b2d5e0;
extern int DAT_00b2d820;
extern BoundsFloat3 DAT_00b2d948;
extern VoxelDrawEntry DAT_00b2d958[];

// FUNCTION: GAMEMD 0x7540f0
void __fastcall FUN_007540f0(VoxelSectionSource *source, int section, int frame, Matrix3DRows *matrix)
{
	VoxelSectionBounds *bounds = source->FUN_007564b0(section, frame);
	VoxelDrawEntry &entry = DAT_00b2d958[DAT_00b2d820];
	entry.Source = source;
	entry.Section = section;
	entry.Frame = frame;
	entry.Min = BoundsFloat3(10000.0f, 10000.0f, 10000.0f);
	entry.Max = BoundsFloat3(-10000.0f, -10000.0f, -10000.0f);

	for (int i = 0; i < 8; i++) {
		Vector3D tmp;
		entry.Corners[i] = *Matrix3D_MatrixApply(&tmp, matrix, &bounds->Corners[i]);
		entry.Corners[i].Y = -entry.Corners[i].Y;
		if (entry.Corners[i].X < entry.Min.X) {
			entry.Min.X = entry.Corners[i].X;
		}
		if (entry.Corners[i].X > entry.Max.X) {
			entry.Max.X = entry.Corners[i].X;
		}
		if (entry.Corners[i].Y < entry.Min.Y) {
			entry.Min.Y = entry.Corners[i].Y;
		}
		if (entry.Corners[i].Y > entry.Max.Y) {
			entry.Max.Y = entry.Corners[i].Y;
		}
		if (entry.Corners[i].Z < entry.Min.Z) {
			entry.Min.Z = entry.Corners[i].Z;
			entry.MinZCorner = i;
		}
		if (entry.Corners[i].Z > entry.Max.Z) {
			entry.Max.Z = entry.Corners[i].Z;
		}
	}

	if (entry.Min.X < DAT_00b2d5e0.X) {
		DAT_00b2d5e0.X = entry.Min.X;
	}
	if (entry.Min.Y < DAT_00b2d5e0.Y) {
		DAT_00b2d5e0.Y = entry.Min.Y;
	}
	if (entry.Min.Z < DAT_00b2d5e0.Z) {
		DAT_00b2d5e0.Z = entry.Min.Z;
	}
	if (entry.Max.X > DAT_00b2d948.X) {
		DAT_00b2d948.X = entry.Max.X;
	}
	if (entry.Max.Y > DAT_00b2d948.Y) {
		DAT_00b2d948.Y = entry.Max.Y;
	}
	if (entry.Max.Z > DAT_00b2d948.Z) {
		DAT_00b2d948.Z = entry.Max.Z;
	}
	DAT_00b2d820++;
}
