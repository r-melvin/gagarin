// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets derived from the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI (member-access disassembly at 0x4399A0-0x439A07), cross-checked
//   against YRpp
//   (every offset reconfirmed numerically here).
//
// BounceClass - ballistic trajectory state used by (Voxel)Animations. Only the
// two read accessors GetCoords / GetDrawingMatrix are modelled in this TU; the
// full layout (Elasticity/Gravity/MaxVelocity/Velocity/AngularVelocity) is P2.
#ifndef GG_MATCH_MOVEMENT_BOUNCE_CLASS_H
#define GG_MATCH_MOVEMENT_BOUNCE_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// Engine integer world coordinate (3x int32). Filled by GetCoords.
struct CoordStruct
{
    int X;  // +0x00
    int Y;  // +0x04
    int Z;  // +0x08
};

// Sub-cell precision position/velocity component triple (3x float32).
struct Vector3D_float
{
    float X;  // +0x00
    float Y;  // +0x04
    float Z;  // +0x08
};

// Rotation quaternion (4x float32). BounceClass::CurrentAngle @ +0x30.
struct Quaternion
{
    float X;  // +0x00
    float Y;  // +0x04
    float Z;  // +0x08
    float W;  // +0x0C
};

// Row-major 3x4 affine matrix (12x float32 == 48 bytes); the rep-movsd unit
// copied out by GetDrawingMatrix. POD so `*pBuffer = *p` lowers to rep movsd.
struct Matrix3D
{
    // GAMEMD 0x646980  Matrix3D::FromQuaternion (__fastcall; declared, reloc)
    static Matrix3D* FromQuaternion(Matrix3D* mat, const Quaternion* q);

    float Data[12];  // +0x00 .. +0x2F
};

class BounceClass
{
public:
    // GAMEMD 0x4399A0  BounceClass::GetCoords        (__thiscall)
    CoordStruct* GetCoords(CoordStruct* pBuffer) const;
    // GAMEMD 0x4399E0  BounceClass::GetDrawingMatrix (__thiscall)
    Matrix3D* GetDrawingMatrix(Matrix3D* pBuffer) const;

    char           _pad0[0x18];   // +0x00  Elasticity/Gravity/MaxVelocity (P2)
    Vector3D_float Coords;        // +0x18  position with precision
    Vector3D_float Velocity;      // +0x24  speed components
    Quaternion     CurrentAngle;  // +0x30  drawing quaternion
    // Quaternion  AngularVelocity; // +0x40 (P2)
};

GG_STATIC_ASSERT(offsetof(CoordStruct, Z)        == 0x08);
GG_STATIC_ASSERT(offsetof(Quaternion, W)         == 0x0C);
GG_STATIC_ASSERT(sizeof(Matrix3D)                == 0x30);
GG_STATIC_ASSERT(offsetof(BounceClass, Coords)       == 0x18);
GG_STATIC_ASSERT(offsetof(BounceClass, Velocity)     == 0x24);
GG_STATIC_ASSERT(offsetof(BounceClass, CurrentAngle) == 0x30);

#endif  // GG_MATCH_MOVEMENT_BOUNCE_CLASS_H
