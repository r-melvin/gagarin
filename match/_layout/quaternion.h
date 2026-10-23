// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Rotation quaternion {X, Y, Z, W}. Layout: Matrix3D::FromQuaternion 0x646980
// reads [EDX]..[EDX+0xC] as X, Y, Z, W; Matrix3D::FromAxis 0x646480 writes the
// four floats to [EAX]..[EAX+0xC]; BounceClass keeps one at +0x30 (0x4399E0).
// The interpolation at 0x646590 walks the four floats by index.
#ifndef GG_MATCH_LAYOUT_QUATERNION_H
#define GG_MATCH_LAYOUT_QUATERNION_H
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Quaternion
{
    float X;   // +0x00
    float Y;   // +0x04
    float Z;   // +0x08
    float W;   // +0x0C

    Quaternion() {}
    Quaternion(float x, float y, float z, float w) { X = x; Y = y; Z = z; W = w; }

    float& operator[](int i) { return (&X)[i]; }
    const float& operator[](int i) const { return (&X)[i]; }
};
GG_STATIC_ASSERT(offsetof(Quaternion, X) == 0x00);
GG_STATIC_ASSERT(offsetof(Quaternion, Y) == 0x04);
GG_STATIC_ASSERT(offsetof(Quaternion, Z) == 0x08);
GG_STATIC_ASSERT(offsetof(Quaternion, W) == 0x0C);
GG_STATIC_ASSERT(sizeof(Quaternion) == 0x10);

#endif  // GG_MATCH_LAYOUT_QUATERNION_H
