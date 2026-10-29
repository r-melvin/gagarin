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

// Element of the two 21-entry rotation tables at 0xB44348 and 0xB43188. Their
// static initialisers (0x754B40, 0x754B70) call one out-of-line constructor
// (0x645C30) per element with the arguments (0, 0, 0, 1.0f), which only a
// declared default-argument constructor produces: the inline Quaternion
// constructors are expanded in place and a plain array would not push them.
// A separate type keeps the inline Quaternion constructors of other users.
struct QuaternionEntry : Quaternion
{
    // FUNCTION: GAMEMD 0x645C30 (decl; reloc) -- shared with the stored-four-words constructor there.
    QuaternionEntry(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 1.0f);
};
GG_STATIC_ASSERT(sizeof(QuaternionEntry) == 0x10);

#endif  // GG_MATCH_LAYOUT_QUATERNION_H
