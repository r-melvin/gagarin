// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: retail gamemd.exe v1.001 disassembly at 0x645CD0, 0x645D00 and 0x645D20: member
//   operations on a four-float value (the rotation quaternion of Matrix3D::FromAxis).
//
// Address index: 0x645CD0 0x645D00 0x645D20

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// Placeholder receiver for the four-float value; the canonical Quaternion keeps its
// operators inline, so these out-of-line bodies are written on a local view.
struct FloatQuad_00645CD0
{
    float unknown_00;   // +0x00
    float unknown_04;   // +0x04
    float unknown_08;   // +0x08
    float unknown_0C;   // +0x0C

    float At(int i) const { return (&unknown_00)[i]; }
    void FUN_00645CD0(float factor);
    float* FUN_00645D00(int index);
    FloatQuad_00645CD0 FUN_00645D20(const FloatQuad_00645CD0& source);
};
GG_STATIC_ASSERT(offsetof(FloatQuad_00645CD0, unknown_0C) == 0x0C);
GG_STATIC_ASSERT(sizeof(FloatQuad_00645CD0) == 0x10);

// FUNCTION: GAMEMD 0x645CD0
// Multiply all four components by a factor.
void FloatQuad_00645CD0::FUN_00645CD0(float factor)
{
    unknown_00 *= factor;
    unknown_04 *= factor;
    unknown_08 *= factor;
    unknown_0C *= factor;
}

// FUNCTION: GAMEMD 0x645D00
// Address of one component by index.
float* FloatQuad_00645CD0::FUN_00645D00(int index)
{
    return &unknown_00 + index;
}

// FUNCTION: GAMEMD 0x645D20
// Assign the four components and return a copy of the result.
FloatQuad_00645CD0 FloatQuad_00645CD0::FUN_00645D20(const FloatQuad_00645CD0& source)
{
    unknown_00 = source.At(0);
    unknown_04 = source.At(1);
    unknown_08 = source.At(2);
    unknown_0C = source.At(3);
    return *this;
}
