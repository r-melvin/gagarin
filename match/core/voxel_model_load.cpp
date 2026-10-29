// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Native 0x755DB0..0x756491: file blocks, optional palette loading, record
// transforms, bounding corners and cleanup on every checked short read.
#include "../_layout/voxel_resource_data.h"
#include "../platform/ccfile_class.h"
#include "voxel_shade_palette.h"
#include <new.h>

// GLOBAL: GAMEMD 0xB2FB78
extern unsigned char DAT_00b2fb78[768];
// GLOBAL: GAMEMD 0xB41178
extern unsigned char DAT_00b41178[][256];

// Gagarin names for on-disk records, pinned by the native read lengths and
// the subsequent loads. No external format declarations are transcribed.
struct GgModelHeader {
    char unknown_00[16];
    unsigned int unknown_10;
    unsigned int unknown_14;
    unsigned int unknown_18;
    unsigned int unknown_1C;
};
struct GgModelSectionHeader {
    char unknown_00[16];
    int unknown_10;
    int unknown_14;
    unsigned char unknown_18;
    unsigned char unknown_19[3];
};
struct GgModelFooter {
    int unknown_00;
    int unknown_04;
    int unknown_08;
    float unknown_0C;
    Matrix3D unknown_10;
    Vector3D unknown_40;
    Vector3D unknown_4C;
    unsigned char unknown_58[4];
};
GG_STATIC_ASSERT(sizeof(GgModelHeader) == 32);
GG_STATIC_ASSERT(sizeof(GgModelSectionHeader) == 28);
GG_STATIC_ASSERT(sizeof(GgModelFooter) == 92);

// Gagarin helper for the repeated native release-and-zero sequence.
static inline void GgReleaseModelStorage(Obj_00755D10* model)
{
    if (model->Block0) ::operator delete(model->Block0);
    model->Block0 = 0;
    if (model->Block1) ::operator delete(model->Block1);
    model->Block1 = 0;
    if (model->Block2) ::operator delete(model->Block2);
    model->Block2 = 0;
}

// FUNCTION: GAMEMD 0x755DB0
int Obj_00755D10::FUN_00755DB0(FileClass* file, int unknown)
{
    GgReleaseModelStorage(this);
    if (file->Open(1) == 0) return 0;
    GgModelHeader header;
    file->ReadBytes(&header, sizeof(header));
    unknown_04 = header.unknown_14;
    unknown_08 = header.unknown_18;
    unknown_0C = header.unknown_1C;
    Block0 = new VoxelSectionRow[unknown_04];
    Block1 = new VoxelSectionBounds[unknown_08];
    Block2 = new unsigned char[unknown_0C];
    if (Block0 && Block1 && Block2) {
        if (unknown) {
            VoxelShadePalette palette(DAT_00b2fb78, DAT_00b41178[0]);
            unsigned char low, high;
            if (file->ReadBytes(&low, 1) != 1) {
                file->Close();
                GgReleaseModelStorage(this);
                return 0;
            }
            if (file->ReadBytes(&high, 1) != 1) {
                file->Close();
                GgReleaseModelStorage(this);
                return 0;
            }
            palette.RangeLow = low;
            palette.RangeHigh = high;
            for (int color = 0; color < 256; ++color) {
                file->ReadBytes(&DAT_00b2fb78[color * 3], 1);
                file->ReadBytes(&DAT_00b2fb78[color * 3 + 1], 1);
                file->ReadBytes(&DAT_00b2fb78[color * 3 + 2], 1);
            }
            if (header.unknown_10 > 1)
                file->Seek(header.unknown_10 * 768 - 768, 1);
            palette.FUN_00758b70(0, 0);
        } else {
            file->Seek(header.unknown_10 * 770, 1);
        }
        for (unsigned int section = 0; section < unknown_04; ++section) {
            GgModelSectionHeader sectionHeader;
            if (file->ReadBytes(&sectionHeader, sizeof(sectionHeader)) != sizeof(sectionHeader)) {
                GgReleaseModelStorage(this);
                file->Close();
                return 0;
            }
            Block0[section].FirstRecord = sectionHeader.unknown_10;
            Block0[section].unknown_04 = sectionHeader.unknown_14;
            Block0[section].unknown_08 = sectionHeader.unknown_18;
        }
        if (file->ReadBytes(Block2, unknown_0C) == unknown_0C) {
            for (unsigned int record = 0; record < unknown_08; ++record) {
                GgModelFooter footer;
                if (file->ReadBytes(&footer, sizeof(footer)) != sizeof(footer)) {
                    GgReleaseModelStorage(this);
                    file->Close();
                    return 0;
                }
                Block1[record].unknown_A0[0] = footer.unknown_58[0];
                Block1[record].unknown_A0[1] = footer.unknown_58[1];
                Block1[record].unknown_A0[2] = footer.unknown_58[2];
                Block1[record].unknown_A0[3] = footer.unknown_58[3];
                Block1[record].unknown_0C = footer.unknown_0C;
                Matrix3D converted;
                Block1[record].unknown_10 = converted.FUN_005AE5E0(footer.unknown_10);
                Vector3D corner0 = Vector3D(footer.unknown_4C.X, footer.unknown_4C.Y, footer.unknown_40.Z);
                Vector3D corner1 = Vector3D(footer.unknown_4C.X, footer.unknown_40.Y, footer.unknown_40.Z);
                Vector3D corner2 = Vector3D(footer.unknown_40.X, footer.unknown_40.Y, footer.unknown_40.Z);
                Vector3D corner3 = Vector3D(footer.unknown_40.X, footer.unknown_4C.Y, footer.unknown_40.Z);
                Vector3D corner4 = Vector3D(footer.unknown_4C.X, footer.unknown_4C.Y, footer.unknown_4C.Z);
                Vector3D corner5 = Vector3D(footer.unknown_4C.X, footer.unknown_40.Y, footer.unknown_4C.Z);
                Vector3D corner6 = Vector3D(footer.unknown_40.X, footer.unknown_40.Y, footer.unknown_4C.Z);
                Vector3D corner7 = Vector3D(footer.unknown_40.X, footer.unknown_4C.Y, footer.unknown_4C.Z);
                Block1[record].Corners[0] = corner0;
                Block1[record].Corners[1] = corner1;
                Block1[record].Corners[2] = corner2;
                Block1[record].Corners[3] = corner3;
                Block1[record].Corners[4] = corner4;
                Block1[record].Corners[5] = corner5;
                Block1[record].Corners[6] = corner6;
                Block1[record].Corners[7] = corner7;
                Block1[record].unknown_00 = Block2 + footer.unknown_00;
                Block1[record].unknown_04 = Block2 + footer.unknown_04;
                Block1[record].unknown_08 = Block2 + footer.unknown_08;
            }
            file->Close();
            return 1;
        }
    }
    GgReleaseModelStorage(this);
    file->Close();
    return 0;
}
GG_STATIC_ASSERT(offsetof(GgModelHeader, unknown_10) == 0x10);
GG_STATIC_ASSERT(offsetof(GgModelHeader, unknown_14) == 0x14);
GG_STATIC_ASSERT(offsetof(GgModelHeader, unknown_18) == 0x18);
GG_STATIC_ASSERT(offsetof(GgModelHeader, unknown_1C) == 0x1c);
GG_STATIC_ASSERT(offsetof(GgModelSectionHeader, unknown_10) == 0x10);
GG_STATIC_ASSERT(offsetof(GgModelSectionHeader, unknown_14) == 0x14);
GG_STATIC_ASSERT(offsetof(GgModelSectionHeader, unknown_18) == 0x18);
GG_STATIC_ASSERT(offsetof(GgModelFooter, unknown_00) == 0x0);
GG_STATIC_ASSERT(offsetof(GgModelFooter, unknown_04) == 0x4);
GG_STATIC_ASSERT(offsetof(GgModelFooter, unknown_08) == 0x8);
GG_STATIC_ASSERT(offsetof(GgModelFooter, unknown_0C) == 0xc);
GG_STATIC_ASSERT(offsetof(GgModelFooter, unknown_10) == 0x10);
GG_STATIC_ASSERT(offsetof(GgModelFooter, unknown_40) == 0x40);
GG_STATIC_ASSERT(offsetof(GgModelFooter, unknown_4C) == 0x4c);
GG_STATIC_ASSERT(offsetof(GgModelFooter, unknown_58) == 0x58);
