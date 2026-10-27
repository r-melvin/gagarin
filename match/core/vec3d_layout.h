// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Vec3d helper bodies 0x41C350/0x41C430 load double fields at +0/+8;
//   0x41C3C0 additionally loads +0x10; 0x46B960 accesses all three fields.
//   The Bullet caller's ECX points directly at its three-double velocity local.
#ifndef GG_MATCH_CORE_VEC3D_LAYOUT_H
#define GG_MATCH_CORE_VEC3D_LAYOUT_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Vec3d
{
    double x;   // +0x0000
    double y;   // +0x0008
    double z;   // +0x0010

    // Native method at 0x41C350; implementation is in small_misc7_methods.cpp.
    double FUN_0041C350() const;
    // Native method at 0x41C430; implementation is in small_misc7_methods.cpp.
    double FUN_0041C430() const;
    // Native method at 0x41C3C0; implementation is in small_misc7_methods.cpp.
    double FUN_0041C3C0() const;
    // Native method at 0x46B960; implementation is in small_misc7_methods.cpp.
    Vec3d* FUN_0046B960(const Vec3d* other);
};

GG_STATIC_ASSERT(offsetof(Vec3d, x) == 0x00);
GG_STATIC_ASSERT(offsetof(Vec3d, y) == 0x08);
GG_STATIC_ASSERT(offsetof(Vec3d, z) == 0x10);
GG_STATIC_ASSERT(sizeof(((Vec3d*)0)->x) == 8);
GG_STATIC_ASSERT(sizeof(((Vec3d*)0)->y) == 8);
GG_STATIC_ASSERT(sizeof(((Vec3d*)0)->z) == 8);
GG_STATIC_ASSERT(sizeof(Vec3d) == 0x18);

#endif  // GG_MATCH_CORE_VEC3D_LAYOUT_H
