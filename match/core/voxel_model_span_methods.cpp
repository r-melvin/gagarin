// Provenance: own-binary-via-Ghidra | YRpp-cross-check | behaviour-confirmed-name
//
// Voxel model section rasteriser set-up: per-section header lookups and the
// fixed-point stepping parameters handed to the span-drawer dispatch table.
//   GLOBAL: GAMEMD 0x846840  DAT_00846840 (span drawer function table)
//   GLOBAL: GAMEMD 0x8468C0  DAT_008468c0 (VoxelCornerView[8], stride 0x24)
//   GLOBAL: GAMEMD 0xB43180  DAT_00b43180 (int, depth buffer in use)
//   GLOBAL: GAMEMD 0xB43184  DAT_00b43184 (int)
//   GLOBAL: GAMEMD 0xB1D5E0  DAT_00b1d5e0 (unsigned char[0x10000], depth buffer)
//   GLOBAL: GAMEMD 0xB2FF78  DAT_00b2ff78 (unsigned char[0x10000], colour buffer)
//   GLOBAL: GAMEMD 0xB45590  DAT_00b45590 (VoxelStepPair[], per-skip x/y offsets)
// The eight span drawers (table slots 0-3 and 8-11) differ only in walk
// direction (bit 0), depth testing (bit 1) and one-byte records (bit 3).

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../movement/matrix3d_apply_methods.h"

struct VoxelPoint
{
	VoxelPoint() {}
	VoxelPoint(float x, float y, float z) : X(x), Y(y), Z(z) {}
	float X;
	float Y;
	float Z;
};

struct VoxelSection_00756590
{
	int *A;                       // +0x00
	int *B;                       // +0x04
	unsigned char *C;             // +0x08
	unsigned char unknown_0C[0x34];
	VoxelPoint Corners[8];        // +0x40
	unsigned char SizeX;          // +0xA0
	unsigned char SizeY;          // +0xA1
	unsigned char SizeZ;          // +0xA2
	unsigned char Flag;           // +0xA3
};
GG_STATIC_ASSERT(offsetof(VoxelSection_00756590, Corners) == 0x40);
GG_STATIC_ASSERT(offsetof(VoxelSection_00756590, SizeX) == 0xA0);
GG_STATIC_ASSERT(offsetof(VoxelSection_00756590, Flag) == 0xA3);
GG_STATIC_ASSERT(sizeof(VoxelSection_00756590) == 0xA4);   // array stride (index * 0xA4)

struct VoxelSectionEntry
{
	int Start;                    // +0x00
	int unknown_04;
	int unknown_08;
};
GG_STATIC_ASSERT(sizeof(VoxelSectionEntry) == 0x0C);   // array stride (index * 0x0C)

struct VoxelDrawEntry
{
	void *Source;                 // +0x00
	int Section;                  // +0x04
	int Frame;                    // +0x08
	int MinZCorner;               // +0x0C
	Vector3D Min;                 // +0x10
	Vector3D Max;                 // +0x1C
	Vector3D Corners[8];          // +0x28
};
GG_STATIC_ASSERT(offsetof(VoxelDrawEntry, Section) == 0x04);
GG_STATIC_ASSERT(offsetof(VoxelDrawEntry, Frame) == 0x08);
GG_STATIC_ASSERT(offsetof(VoxelDrawEntry, MinZCorner) == 0x0C);
GG_STATIC_ASSERT(offsetof(VoxelDrawEntry, Corners) == 0x28);

struct VoxelCornerView
{
	int Flags;                    // +0x00
	int Corner[4];                // +0x04
	int StrideX;                  // +0x14
	int StrideY;                  // +0x18
	int StepA;                    // +0x1C
	int StepB;                    // +0x20
};
GG_STATIC_ASSERT(offsetof(VoxelCornerView, StrideX) == 0x14);
GG_STATIC_ASSERT(offsetof(VoxelCornerView, StepB) == 0x20);
GG_STATIC_ASSERT(sizeof(VoxelCornerView) == 0x24);   // array stride (index * 0x24)

struct VoxelSpanParams
{
	int *A;                       // +0x00
	int *B;                       // +0x04
	unsigned char *C;             // +0x08
	int Offset;                   // +0x0C
	int StepA;                    // +0x10
	int StepB;                    // +0x14
	short Origin[3];              // +0x18
	short StepX[3];               // +0x1E
	short StepY[3];               // +0x24
	short StepZ[3];               // +0x2A
	unsigned char Size[3];        // +0x30
};
GG_STATIC_ASSERT(offsetof(VoxelSpanParams, Origin) == 0x18);
GG_STATIC_ASSERT(offsetof(VoxelSpanParams, StepX) == 0x1E);
GG_STATIC_ASSERT(offsetof(VoxelSpanParams, StepZ) == 0x2A);
GG_STATIC_ASSERT(offsetof(VoxelSpanParams, Size) == 0x30);

typedef void (__cdecl *VoxelSpanDrawer)(VoxelSpanParams *params);

struct VoxelModel
{
	unsigned char unknown_00[0x08];
	unsigned int SectionCount;    // +0x08
	unsigned char unknown_0C[0x04];
	VoxelSectionEntry *unknown_10;        // +0x10
	VoxelSection_00756590 *Sections; // +0x14

	void FUN_00756590(VoxelDrawEntry *entry, Vector3D *origin);
	void FUN_00756bb0();
};
GG_STATIC_ASSERT(offsetof(VoxelModel, SectionCount) == 0x08);
GG_STATIC_ASSERT(offsetof(VoxelModel, unknown_10) == 0x10);
GG_STATIC_ASSERT(offsetof(VoxelModel, Sections) == 0x14);

extern VoxelSpanDrawer DAT_00846840[];
extern VoxelCornerView DAT_008468c0[];
struct VoxelStepPair
{
	short X;
	short Y;
};

extern int DAT_00b43180;
extern int DAT_00b43184;
extern unsigned char DAT_00b1d5e0[0x10000];
extern unsigned char DAT_00b2ff78[0x10000];
extern VoxelStepPair DAT_00b45590[];

// FUNCTION: GAMEMD 0x756590
void VoxelModel::FUN_00756590(VoxelDrawEntry *entry, Vector3D *origin)
{
	VoxelSection_00756590 *header = &Sections[unknown_10[entry->Section].Start + entry->Frame];
	int view = entry->MinZCorner;
	VoxelSpanParams params;

	unsigned char sx = header->SizeX;
	unsigned char sy = header->SizeY;
	unsigned char sz = header->SizeZ;
	params.Size[0] = sx;
	params.Size[1] = sy;
	params.Size[2] = sz;
	params.A = header->A;
	params.B = header->B;
	params.C = header->C;

	Vector3D *c0 = &entry->Corners[DAT_008468c0[view].Corner[0]];
	Vector3D *c1 = &entry->Corners[DAT_008468c0[view].Corner[1]];
	Vector3D *c2 = &entry->Corners[DAT_008468c0[view].Corner[2]];
	Vector3D *c3 = &entry->Corners[DAT_008468c0[view].Corner[3]];

	params.StepA = DAT_008468c0[view].StepA;
	params.StepB = DAT_008468c0[view].StepB * sx;
	params.Offset = DAT_008468c0[view].StrideY * (sy - 1) * sx + DAT_008468c0[view].StrideX * (sx - 1);

	params.Origin[0] = (short)((c0->X + 128.0f - origin->X) * 256.0f);
	params.Origin[1] = (short)((c0->Y + 128.0f - origin->Y) * 256.0f);
	params.Origin[2] = (short)((c0->Z + 128.0f - origin->Z) * 256.0f);

	float fx = sx;
	params.StepX[0] = (short)((c1->X - c0->X) / fx * 256.0f);
	float fy = sy;
	params.StepY[0] = (short)((c2->X - c0->X) / fy * 256.0f);
	float fz = sz;
	params.StepZ[0] = (short)((c3->X - c0->X) / fz * 256.0f);
	params.StepX[1] = (short)((c1->Y - c0->Y) / fx * 256.0f);
	params.StepY[1] = (short)((c2->Y - c0->Y) / fy * 256.0f);
	params.StepZ[1] = (short)((c3->Y - c0->Y) / fz * 256.0f);
	if (DAT_00b43180 != 0) {
		params.StepX[2] = (short)((c1->Z - c0->Z) / fx * 256.0f);
		params.StepY[2] = (short)((c2->Z - c0->Z) / fy * 256.0f);
		params.StepZ[2] = (short)((c3->Z - c0->Z) / fz * 256.0f);
	}

	int mode = DAT_008468c0[view].Flags;
	if (DAT_00b43180 != 0) {
		mode |= 2;
	}
	if (DAT_00b43184 != 0) {
		mode |= 4;
	}
	if (header->Flag == 0) {
		mode |= 8;
	}
	DAT_00846840[mode](&params);
}

// FUNCTION: GAMEMD 0x756bb0
void VoxelModel::FUN_00756bb0()
{
	for (unsigned int i = 0; i < SectionCount; i++) {
		VoxelSection_00756590 &header = Sections[i];
		int sx = header.SizeX;
		int sy = header.SizeY;
		int sz = header.SizeZ;
		header.Corners[0] = VoxelPoint(sx * 0.5f, sy * 0.5f, -sz * 0.5f);
		header.Corners[1] = VoxelPoint(sx * 0.5f, -sy * 0.5f, -sz * 0.5f);
		header.Corners[2] = VoxelPoint(-sx * 0.5f, -sy * 0.5f, -sz * 0.5f);
		header.Corners[3] = VoxelPoint(-sx * 0.5f, sy * 0.5f, -sz * 0.5f);
		header.Corners[4] = VoxelPoint(sx * 0.5f, sy * 0.5f, sz * 0.5f);
		header.Corners[5] = VoxelPoint(sx * 0.5f, -sy * 0.5f, sz * 0.5f);
		header.Corners[6] = VoxelPoint(-sx * 0.5f, -sy * 0.5f, sz * 0.5f);
		header.Corners[7] = VoxelPoint(-sx * 0.5f, sy * 0.5f, sz * 0.5f);
	}
}

// FUNCTION: GAMEMD 0x756dd0
void __cdecl FUN_00756dd0(VoxelSpanParams *params)
{
	DAT_00b45590[0].X = 0;
	DAT_00b45590[0].Y = 0;
	for (unsigned int i = 1; i < params->Size[2]; i++) {
		DAT_00b45590[i].X = DAT_00b45590[i - 1].X + params->StepZ[0];
		DAT_00b45590[i].Y = params->StepZ[1] + DAT_00b45590[i - 1].Y;
	}

	unsigned short px = params->Origin[0];
	unsigned short py = params->Origin[1];
	for (unsigned int row = 0; row < params->Size[1]; row++) {
		unsigned short rowX = px;
		unsigned short rowY = py;
		int rowOffset = params->Offset;
		for (unsigned int col = 0; col < params->Size[0]; col++) {
			unsigned short colX = px;
			unsigned short colY = py;
			int span = params->A[params->Offset];
			if (span != -1) {
				unsigned char *data = params->C + span;
				int remaining = params->Size[2];
				while (remaining != 0) {
					unsigned char skip = *data;
					data++;
					px += DAT_00b45590[skip].X;
					py += DAT_00b45590[skip].Y;
					remaining -= skip;
					int count = *data++;
					if (count != 0) {
						remaining -= count;
						int n = count;
						do {
							unsigned char colour = *data;
							data += 2;
							DAT_00b2ff78[(py & 0xFF00) | (px >> 8)] = colour;
							px += params->StepZ[0];
							py += params->StepZ[1];
						} while (--n);
					}
					data++;
				}
			}
			px = params->StepX[0] + colX;
			py = params->StepX[1] + colY;
			params->Offset += params->StepA;
		}
		px = params->StepY[0] + rowX;
		py = params->StepY[1] + rowY;
		params->Offset = params->StepB + rowOffset;
	}
}

// FUNCTION: GAMEMD 0x756f80
void __cdecl FUN_00756f80(VoxelSpanParams *params)
{
	DAT_00b45590[0].X = 0;
	DAT_00b45590[0].Y = 0;
	for (unsigned int i = 1; i < params->Size[2]; i++) {
		DAT_00b45590[i].X = DAT_00b45590[i - 1].X + params->StepZ[0];
		DAT_00b45590[i].Y = DAT_00b45590[i - 1].Y + params->StepZ[1];
	}

	unsigned short px = params->Origin[0];
	unsigned short py = params->Origin[1];
	for (unsigned int row = 0; row < params->Size[1]; row++) {
		unsigned short rowX = px;
		unsigned short rowY = py;
		int rowOffset = params->Offset;
		for (unsigned int col = 0; col < params->Size[0]; col++) {
			unsigned short colX = px;
			unsigned short colY = py;
			int span = params->B[params->Offset];
			if (span != -1) {
				unsigned char *data = params->C + span;
				int remaining = params->Size[2];
				while (remaining != 0) {
					int count = *data--;
					if (count != 0) {
						remaining -= count;
						int n = count;
						do {
							unsigned char colour = *--data;
							data--;
							DAT_00b2ff78[(py & 0xFF00) | (px >> 8)] = colour;
							px += params->StepZ[0];
							py += params->StepZ[1];
						} while (--n);
					}
					unsigned char skip = *--data;
					data--;
					px += DAT_00b45590[skip].X;
					py += DAT_00b45590[skip].Y;
					remaining -= skip;
				}
			}
			px = params->StepX[0] + colX;
			py = params->StepX[1] + colY;
			params->Offset += params->StepA;
		}
		px = params->StepY[0] + rowX;
		py = params->StepY[1] + rowY;
		params->Offset = params->StepB + rowOffset;
	}
}

// FUNCTION: GAMEMD 0x757120
void __cdecl FUN_00757120(VoxelSpanParams *params)
{
	DAT_00b45590[0].X = 0;
	DAT_00b45590[0].Y = 0;
	for (unsigned int i = 1; i < params->Size[2]; i++) {
		DAT_00b45590[i].X = DAT_00b45590[i - 1].X + params->StepZ[0];
		DAT_00b45590[i].Y = DAT_00b45590[i - 1].Y + params->StepZ[1];
	}

	unsigned short px = params->Origin[0];
	unsigned short py = params->Origin[1];
	unsigned short pz = params->Origin[2];
	for (unsigned int row = 0; row < params->Size[1]; row++) {
		int rowOffset = params->Offset;
		unsigned short rowX = px;
		unsigned short rowY = py;
		unsigned short rowZ = pz;
		for (unsigned int col = 0; col < params->Size[0]; col++) {
			unsigned short colX = px;
			unsigned short colY = py;
			unsigned short colZ = pz;
			int span = params->A[params->Offset];
			if (span != -1) {
				unsigned char *data = params->C + span;
				int remaining = params->Size[2];
				while (remaining != 0) {
					unsigned char value;
					value = *data;
					data++;
					px += DAT_00b45590[value].X;
					py += DAT_00b45590[value].Y;
					pz += value * params->StepZ[2];
					remaining -= value;
					int count = *data++;
					if (count != 0) {
						remaining -= count;
						int n = count;
						do {
							value = *data;
							int index = (py & 0xFF00) | (px >> 8);
							data += 2;
							if ((unsigned short)(pz >> 8) > DAT_00b1d5e0[index]) {
								DAT_00b1d5e0[index] = (unsigned char)(pz >> 8);
								DAT_00b2ff78[index] = value;
								DAT_00b2ff78[index + 1] = value;
								DAT_00b1d5e0[index + 1] = (unsigned char)(pz >> 8);
							}
							px += params->StepZ[0];
							py += params->StepZ[1];
							pz += params->StepZ[2];
						} while (--n);
					}
					data++;
				}
			}
			px = params->StepX[0] + colX;
			py = params->StepX[1] + colY;
			pz = params->StepX[2] + colZ;
			params->Offset += params->StepA;
		}
		px = params->StepY[0] + rowX;
		py = params->StepY[1] + rowY;
		pz = params->StepY[2] + rowZ;
		params->Offset = params->StepB + rowOffset;
	}
}

// FUNCTION: GAMEMD 0x757360
void __cdecl FUN_00757360(VoxelSpanParams *params)
{
	DAT_00b45590[0].X = 0;
	DAT_00b45590[0].Y = 0;
	for (unsigned int i = 1; i < params->Size[2]; i++) {
		DAT_00b45590[i].X = DAT_00b45590[i - 1].X + params->StepZ[0];
		DAT_00b45590[i].Y = DAT_00b45590[i - 1].Y + params->StepZ[1];
	}

	unsigned short px = params->Origin[0];
	unsigned short py = params->Origin[1];
	unsigned short pz = params->Origin[2];
	for (unsigned int row = 0; row < params->Size[1]; row++) {
		int rowOffset = params->Offset;
		unsigned short rowX = px;
		unsigned short rowY = py;
		unsigned short rowZ = pz;
		for (unsigned int col = 0; col < params->Size[0]; col++) {
			unsigned short colX = px;
			unsigned short colY = py;
			unsigned short colZ = pz;
			int span = params->B[params->Offset];
			if (span != -1) {
				unsigned char *data = params->C + span;
				int remaining = params->Size[2];
				while (remaining != 0) {
					unsigned char value;
					int count = *data--;
					if (count != 0) {
						remaining -= count;
						int n = count;
						do {
							value = *--data;
							data--;
							int index = (py & 0xFF00) | (px >> 8);
							if ((unsigned short)(pz >> 8) > DAT_00b1d5e0[index]) {
								DAT_00b1d5e0[index] = (unsigned char)(pz >> 8);
								DAT_00b2ff78[index] = value;
								DAT_00b2ff78[index + 1] = value;
								DAT_00b1d5e0[index + 1] = (unsigned char)(pz >> 8);
							}
							px += params->StepZ[0];
							py += params->StepZ[1];
							pz += params->StepZ[2];
						} while (--n);
					}
					value = *--data;
					data--;
					px += DAT_00b45590[value].X;
					py += DAT_00b45590[value].Y;
					pz += value * params->StepZ[2];
					remaining -= value;
				}
			}
			px = params->StepX[0] + colX;
			py = params->StepX[1] + colY;
			pz = params->StepX[2] + colZ;
			params->Offset += params->StepA;
		}
		px = params->StepY[0] + rowX;
		py = params->StepY[1] + rowY;
		pz = params->StepY[2] + rowZ;
		params->Offset = params->StepB + rowOffset;
	}
}

// FUNCTION: GAMEMD 0x757e70
void __cdecl FUN_00757e70(VoxelSpanParams *params)
{
	DAT_00b45590[0].X = 0;
	DAT_00b45590[0].Y = 0;
	for (unsigned int i = 1; i < params->Size[2]; i++) {
		DAT_00b45590[i].X = DAT_00b45590[i - 1].X + params->StepZ[0];
		DAT_00b45590[i].Y = DAT_00b45590[i - 1].Y + params->StepZ[1];
	}

	unsigned short px = params->Origin[0];
	unsigned short py = params->Origin[1];
	for (unsigned int row = 0; row < params->Size[1]; row++) {
		unsigned short rowX = px;
		unsigned short rowY = py;
		int rowOffset = params->Offset;
		for (unsigned int col = 0; col < params->Size[0]; col++) {
			unsigned short colX = px;
			unsigned short colY = py;
			int span = params->A[params->Offset];
			if (span != -1) {
				unsigned char *data = params->C + span;
				int remaining = params->Size[2];
				while (remaining != 0) {
					unsigned char skip = *data;
					data++;
					px += DAT_00b45590[skip].X;
					py += DAT_00b45590[skip].Y;
					remaining -= skip;
					int count = *data++;
					if (count != 0) {
						remaining -= count;
						int n = count;
						do {
							unsigned char colour = *data;
							data += 1;
							DAT_00b2ff78[(py & 0xFF00) | (px >> 8)] = colour;
							DAT_00b2ff78[((py & 0xFF00) + 1) | (px >> 8)] = colour;
							px += params->StepZ[0];
							py += params->StepZ[1];
						} while (--n);
					}
					data++;
				}
			}
			px = params->StepX[0] + colX;
			py = params->StepX[1] + colY;
			params->Offset += params->StepA;
		}
		px = params->StepY[0] + rowX;
		py = params->StepY[1] + rowY;
		params->Offset = params->StepB + rowOffset;
	}
}

// FUNCTION: GAMEMD 0x758030
void __cdecl FUN_00758030(VoxelSpanParams *params)
{
	DAT_00b45590[0].X = 0;
	DAT_00b45590[0].Y = 0;
	for (unsigned int i = 1; i < params->Size[2]; i++) {
		DAT_00b45590[i].X = DAT_00b45590[i - 1].X + params->StepZ[0];
		DAT_00b45590[i].Y = DAT_00b45590[i - 1].Y + params->StepZ[1];
	}

	unsigned short px = params->Origin[0];
	unsigned short py = params->Origin[1];
	for (unsigned int row = 0; row < params->Size[1]; row++) {
		unsigned short rowX = px;
		unsigned short rowY = py;
		int rowOffset = params->Offset;
		for (unsigned int col = 0; col < params->Size[0]; col++) {
			unsigned short colX = px;
			unsigned short colY = py;
			int span = params->B[params->Offset];
			if (span != -1) {
				unsigned char *data = params->C + span;
				int remaining = params->Size[2];
				while (remaining != 0) {
					int count = *data--;
					if (count != 0) {
						remaining -= count;
						int n = count;
						do {
							unsigned char colour = *data--;
							DAT_00b2ff78[(py & 0xFF00) | (px >> 8)] = colour;
							DAT_00b2ff78[((py & 0xFF00) + 1) | (px >> 8)] = colour;
							px += params->StepZ[0];
							py += params->StepZ[1];
						} while (--n);
					}
					unsigned char skip = *--data;
					data--;
					px += DAT_00b45590[skip].X;
					py += DAT_00b45590[skip].Y;
					remaining -= skip;
				}
			}
			px = params->StepX[0] + colX;
			py = params->StepX[1] + colY;
			params->Offset += params->StepA;
		}
		px = params->StepY[0] + rowX;
		py = params->StepY[1] + rowY;
		params->Offset = params->StepB + rowOffset;
	}
}

// FUNCTION: GAMEMD 0x7581f0
void __cdecl FUN_007581f0(VoxelSpanParams *params)
{
	DAT_00b45590[0].X = 0;
	DAT_00b45590[0].Y = 0;
	for (unsigned int i = 1; i < params->Size[2]; i++) {
		DAT_00b45590[i].X = DAT_00b45590[i - 1].X + params->StepZ[0];
		DAT_00b45590[i].Y = DAT_00b45590[i - 1].Y + params->StepZ[1];
	}

	unsigned short px = params->Origin[0];
	unsigned short py = params->Origin[1];
	unsigned short pz = params->Origin[2];
	for (unsigned int row = 0; row < params->Size[1]; row++) {
		int rowOffset = params->Offset;
		unsigned short rowX = px;
		unsigned short rowY = py;
		unsigned short rowZ = pz;
		for (unsigned int col = 0; col < params->Size[0]; col++) {
			unsigned short colX = px;
			unsigned short colY = py;
			unsigned short colZ = pz;
			int span = params->A[params->Offset];
			if (span != -1) {
				unsigned char *data = params->C + span;
				int remaining = params->Size[2];
				while (remaining != 0) {
					unsigned char value;
					value = *data;
					data++;
					px += DAT_00b45590[value].X;
					py += DAT_00b45590[value].Y;
					pz += value * params->StepZ[2];
					remaining -= value;
					int count = *data++;
					if (count != 0) {
						remaining -= count;
						int n = count;
						do {
							value = *data;
							int index = (py & 0xFF00) | (px >> 8);
							data += 1;
							if ((unsigned short)(pz >> 8) > DAT_00b1d5e0[index]) {
								DAT_00b1d5e0[index] = (unsigned char)(pz >> 8);
								DAT_00b2ff78[index] = value;
								DAT_00b2ff78[index + 1] = value;
								DAT_00b1d5e0[index + 1] = (unsigned char)(pz >> 8);
							}
							px += params->StepZ[0];
							py += params->StepZ[1];
							pz += params->StepZ[2];
						} while (--n);
					}
					data++;
				}
			}
			px = params->StepX[0] + colX;
			py = params->StepX[1] + colY;
			pz = params->StepX[2] + colZ;
			params->Offset += params->StepA;
		}
		px = params->StepY[0] + rowX;
		py = params->StepY[1] + rowY;
		pz = params->StepY[2] + rowZ;
		params->Offset = params->StepB + rowOffset;
	}
}

// FUNCTION: GAMEMD 0x758430
void __cdecl FUN_00758430(VoxelSpanParams *params)
{
	DAT_00b45590[0].X = 0;
	DAT_00b45590[0].Y = 0;
	for (unsigned int i = 1; i < params->Size[2]; i++) {
		DAT_00b45590[i].X = DAT_00b45590[i - 1].X + params->StepZ[0];
		DAT_00b45590[i].Y = DAT_00b45590[i - 1].Y + params->StepZ[1];
	}

	unsigned short px = params->Origin[0];
	unsigned short py = params->Origin[1];
	unsigned short pz = params->Origin[2];
	for (unsigned int row = 0; row < params->Size[1]; row++) {
		int rowOffset = params->Offset;
		unsigned short rowX = px;
		unsigned short rowY = py;
		unsigned short rowZ = pz;
		for (unsigned int col = 0; col < params->Size[0]; col++) {
			unsigned short colX = px;
			unsigned short colY = py;
			unsigned short colZ = pz;
			int span = params->B[params->Offset];
			if (span != -1) {
				unsigned char *data = params->C + span;
				int remaining = params->Size[2];
				while (remaining != 0) {
					unsigned char value;
					int count = *data--;
					if (count != 0) {
						remaining -= count;
						int n = count;
						do {
							value = *data--;
							int index = (py & 0xFF00) | (px >> 8);
							if ((unsigned short)(pz >> 8) > DAT_00b1d5e0[index]) {
								DAT_00b1d5e0[index] = (unsigned char)(pz >> 8);
								DAT_00b2ff78[index] = value;
								DAT_00b2ff78[index + 1] = value;
								DAT_00b1d5e0[index + 1] = (unsigned char)(pz >> 8);
							}
							px += params->StepZ[0];
							py += params->StepZ[1];
							pz += params->StepZ[2];
						} while (--n);
					}
					value = *--data;
					data--;
					px += DAT_00b45590[value].X;
					py += DAT_00b45590[value].Y;
					pz += value * params->StepZ[2];
					remaining -= value;
				}
			}
			px = params->StepX[0] + colX;
			py = params->StepX[1] + colY;
			pz = params->StepX[2] + colZ;
			params->Offset += params->StepA;
		}
		px = params->StepY[0] + rowX;
		py = params->StepY[1] + rowY;
		pz = params->StepY[2] + rowZ;
		params->Offset = params->StepB + rowOffset;
	}
}
