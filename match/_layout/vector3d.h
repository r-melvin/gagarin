// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Three-float vector (position, direction or axis). Layout: Matrix3D apply
// 0x5AFB80 reads X/Y/Z at +0/+4/+8 of its stack operand and writes the
// 0xC-byte result through ECX; Matrix3D::Translate 0x5AE8F0 reads the same
// three fields; the voxel bounds walk 0x7540F0 strides 0xC per corner.
#ifndef GG_MATCH_LAYOUT_VECTOR3D_H
#define GG_MATCH_LAYOUT_VECTOR3D_H
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Vector3D
{
    float X;   // +0x00
    float Y;   // +0x04
    float Z;   // +0x08

    // FUNCTION: GAMEMD 0x754900 -- emitted for record-array construction.
    Vector3D() {}
    Vector3D(float x, float y, float z) : X(x), Y(y), Z(z) {}
};
GG_STATIC_ASSERT(offsetof(Vector3D, X) == 0x00);
GG_STATIC_ASSERT(offsetof(Vector3D, Y) == 0x04);
GG_STATIC_ASSERT(offsetof(Vector3D, Z) == 0x08);
GG_STATIC_ASSERT(sizeof(Vector3D) == 0x0C);

#endif  // GG_MATCH_LAYOUT_VECTOR3D_H
