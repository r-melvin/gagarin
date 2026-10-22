// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x5AEF60 / 0x5AF080 /
//   0x5AF1A0. Names from YRpp (consult-only).

#include "matrix3d_rotate_methods.h"

// FUNCTION: GAMEMD 0x5AEF60
//
// Rotate about the local X axis by an angle in radians. The angle is widened
// to double once, both table-trig helpers are called on it, and the (Sin, Cos)
// body is expanded in place. The sine is spilled to a stack slot while the
// cosine, computed last, stays on the x87 stack.
void Matrix3D::RotateX(float angle)
{
    float s = FUN_004CACB0(angle);
    float c = FUN_004CAD00(angle);
    this->RotateX(s, c);
}

// FUNCTION: GAMEMD 0x5AF080
//
// Rotate about the local Y axis by an angle in radians; same shape as RotateX.
void Matrix3D::RotateY(float angle)
{
    float s = FUN_004CACB0(angle);
    float c = FUN_004CAD00(angle);
    this->RotateY(s, c);
}

// FUNCTION: GAMEMD 0x5AF1A0
//
// Rotate about the local Z axis by an angle in radians. Unlike X and Y the
// cosine is fetched first here, so it is the sine that stays on the x87 stack.
void Matrix3D::RotateZ(float angle)
{
    float c = FUN_004CAD00(angle);
    float s = FUN_004CACB0(angle);
    this->RotateZ(s, c);
}
