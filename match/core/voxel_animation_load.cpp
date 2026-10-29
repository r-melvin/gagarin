// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// /Ob0 scores 3.9%; /Ob1 and /Ob2 reproduce the full loader.
// Native 0x5BD5C0..0x5BD729 reads a 24-byte header, skips 16 bytes per
// section, then reads frame/section matrices; short reads close and clear.
#include "../_layout/voxel_resource_data.h"
#include "../platform/ccfile_class.h"
#include <new.h>

struct GgAnimationHeader
{
    char unknown_00[16];
    unsigned int unknown_10;
    unsigned int unknown_14;
};
GG_STATIC_ASSERT(offsetof(GgAnimationHeader, unknown_10) == 0x10);
GG_STATIC_ASSERT(offsetof(GgAnimationHeader, unknown_14) == 0x14);
GG_STATIC_ASSERT(sizeof(GgAnimationHeader) == 24);

// FUNCTION: GAMEMD 0x5BD5C0
int Obj_005BD5A0::FUN_005BD5C0(FileClass* file)
{
    if (unknown_0C) delete[] unknown_0C;
    unknown_0C = 0;
    if (file->Open(1) == 0) return 0;
    GgAnimationHeader header;
    file->ReadBytes(&header, sizeof(header));
    unknown_04 = header.unknown_14;
    unknown_08 = header.unknown_10;
    if (unknown_0C) delete[] unknown_0C;
    unknown_0C = new Matrix3D[unknown_08 * unknown_04];
    if (!unknown_0C) {
        unknown_0C = 0;
        file->Close();
        return 0;
    }
    file->Seek(unknown_04 << 4, 1);
    for (unsigned int frame = 0; frame < unknown_08; ++frame) {
        for (unsigned int section = 0; section < unknown_04; ++section) {
            Matrix3D raw;
            if (file->ReadBytes(&raw, sizeof(raw)) != sizeof(raw)) {
                file->Close();
                if (unknown_0C) delete[] unknown_0C;
                unknown_0C = 0;
                return 0;
            }
            Matrix3D converted;
            unknown_0C[unknown_04 * frame + section] = converted.FUN_005AE5E0(raw);
        }
    }
    file->Close();
    return 1;
}

// FUNCTION: GAMEMD 0x5BD730
void Obj_005BD5A0::FUN_005BD730(float scale)
{
    for (unsigned int frame = 0; frame < unknown_08; ++frame) {
        for (unsigned int section = 0; section < unknown_04; ++section) {
            unknown_0C[unknown_04 * frame + section].Row[0][3] *= scale;
            unknown_0C[unknown_04 * frame + section].Row[1][3] *= scale;
            unknown_0C[unknown_04 * frame + section].Row[2][3] *= scale;
        }
    }
}
GG_STATIC_ASSERT(offsetof(Matrix3D, Row) + 3 * sizeof(float) == 0x0C);
GG_STATIC_ASSERT(offsetof(Matrix3D, Row) + sizeof(((Matrix3D*)0)->Row[0]) + 3 * sizeof(float) == 0x1C);
GG_STATIC_ASSERT(offsetof(Matrix3D, Row) + 2 * sizeof(((Matrix3D*)0)->Row[0]) + 3 * sizeof(float) == 0x2C);
