// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Layout and calling shape read numerically off the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI at 0x646980: the __fastcall
//   entry with the hidden result pointer in ECX (copied to EAX and returned)
//   and the quaternion in EDX, read as the four floats `[EDX]`, `[EDX+4]`,
//   `[EDX+8]`, `[EDX+0xC]` (X, Y, Z, W); the 12-float result built at
//   `[ESP+0x18..0x44]` with the fourth column zeroed at +0x24/+0x34/+0x44 and
//   copied out with `MOV ECX,0xC; REP MOVSD`; the 1.0f literal at 0x7E2AC8;
//   and the `FADD ST0,ST0` doublings. The matrix is the 3x4 row-major float
//   layout already proven in match/renderer/matrix3d_rotate_methods.h (not
//   edited). YRpp names only (consult-only, no LICENSE): Matrix3D::
//   FromQuaternion, Quaternion {X, Y, Z, W}.
#ifndef GG_MATCH_RENDERER_MATRIX3D_QUATERNION_METHODS_H
#define GG_MATCH_RENDERER_MATRIX3D_QUATERNION_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Quaternion
{
    float X;   // +0x00
    float Y;   // +0x04
    float Z;   // +0x08
    float W;   // +0x0C
};
GG_STATIC_ASSERT(offsetof(Quaternion, W) == 0xC);
GG_STATIC_ASSERT(sizeof(Quaternion) == 0x10);

// Matrix3D -- a 3x4 row-major float affine transform (0x30 bytes).
struct Matrix3D
{
    float Row[3][4];   // +0x0000

    // FUNCTION: GAMEMD 0x646980
    static Matrix3D __fastcall FromQuaternion(const Quaternion& q);
};
GG_STATIC_ASSERT(offsetof(Matrix3D, Row) == 0x00);
GG_STATIC_ASSERT(sizeof(Matrix3D) == 0x30);

#endif  // GG_MATCH_RENDERER_MATRIX3D_QUATERNION_METHODS_H
