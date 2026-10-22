// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
// Ordered ascending by retail address.

#include "small_misc7_methods.h"

// FUNCTION: GAMEMD 0x4036C0
// Allocate of kind 1, then initialise only if the allocation succeeded. The
// pointer comes back either way.
Obj_004035F0* Obj_004036C0::FUN_004036C0(int arg)
{
    Obj_004035F0* p = FUN_004035F0(this, 1);

    if (p) {
        FUN_00402440(p, arg);
    }

    return p;
}

// FUNCTION: GAMEMD 0x41C350
// The planar length, squared, handed to the helper. Only the first two
// components take part; the third is skipped.
double Vec3d::FUN_0041C350() const
{
    return FUN_004CAC40(x * x + y * y);
}

// FUNCTION: GAMEMD 0x41C430
double Vec3d::FUN_0041C430() const
{
    return FUN_004CAC40(x * x + y * y);
}

// FUNCTION: GAMEMD 0x41C3C0
double Vec3d::FUN_0041C3C0() const
{
    return FUN_004CAC40(x * x + y * y + z * z);
}

// FUNCTION: GAMEMD 0x46B960
// Right-hand side first, as with the float pair: `x = other.x + x`.
Vec3d* Vec3d::FUN_0046B960(const Vec3d* other)
{
    x = other->x + x;
    y = other->y + y;
    z = other->z + z;

    return this;
}

