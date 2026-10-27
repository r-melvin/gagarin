// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Offsets and widths are from retail member accesses at 0x4399A0-0x439A07,
//   0x439A10, 0x439B00 and 0x74A7CE. The double accesses establish the
//   natural 8-byte alignment; the final 16-byte span is established by the
//   adjacent component in AnimClass and the VoxelAnimClass allocation/layout.
//
// BounceClass is a 0x50-byte component shared by AnimClass and VoxelAnimClass.
#ifndef GG_MATCH_MOVEMENT_BOUNCE_CLASS_H
#define GG_MATCH_MOVEMENT_BOUNCE_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/vector3d.h"
#include "../_layout/quaternion.h"
#include "../_layout/matrix3d.h"

// Engine integer world coordinate (3x int32). Filled by GetCoords.
#include "../_layout/coord_struct.h"

class BounceClass
{
public:
    // GAMEMD 0x4399A0  BounceClass::GetCoords        (__thiscall)
    CoordStruct* GetCoords(CoordStruct* pBuffer) const;
    // GAMEMD 0x4399E0  BounceClass::GetDrawingMatrix (__thiscall)
    Matrix3D* GetDrawingMatrix(Matrix3D* pBuffer) const;

    unsigned char  unknown_00[0x08]; // +0x00; raw prefix, member semantics unconfirmed
    double         unknown_08;       // +0x08; qword loads at 0x439B00 and 0x74A7CE
    double         unknown_10;       // +0x10; qword load at 0x439B00
    Vector3D       Coords;           // +0x18; three float loads in GetCoords
    Vector3D       Velocity;         // +0x24; three float fields
    Quaternion     CurrentAngle;     // +0x30; four floats read by GetDrawingMatrix
    unsigned char  unknown_40[0x10]; // +0x40..+0x4F; width closed by component size
};

GG_STATIC_ASSERT(offsetof(CoordStruct, Z)        == 0x08);
GG_STATIC_ASSERT(offsetof(Quaternion, W)         == 0x0C);
GG_STATIC_ASSERT(sizeof(Matrix3D)                == 0x30);
GG_STATIC_ASSERT(sizeof(double)                  == 0x08);
GG_STATIC_ASSERT(offsetof(BounceClass, unknown_00) == 0x00);
GG_STATIC_ASSERT(sizeof(((BounceClass*)0)->unknown_00) == 0x08);
GG_STATIC_ASSERT(offsetof(BounceClass, unknown_08) == 0x08);
GG_STATIC_ASSERT(offsetof(BounceClass, unknown_10) == 0x10);
GG_STATIC_ASSERT(offsetof(BounceClass, Coords)       == 0x18);
GG_STATIC_ASSERT(offsetof(BounceClass, Velocity)     == 0x24);
GG_STATIC_ASSERT(offsetof(BounceClass, CurrentAngle) == 0x30);
GG_STATIC_ASSERT(offsetof(BounceClass, unknown_40) == 0x40);
GG_STATIC_ASSERT(sizeof(((BounceClass*)0)->unknown_40) == 0x10);
GG_STATIC_ASSERT(sizeof(BounceClass) == 0x50);
struct BounceClassAlignmentProbe { char prefix; BounceClass value; };
GG_STATIC_ASSERT(offsetof(BounceClassAlignmentProbe, value) == 0x08);

#endif  // GG_MATCH_MOVEMENT_BOUNCE_CLASS_H
