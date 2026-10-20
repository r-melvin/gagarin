// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm). Names
//   cross-checked against YRpp Matrix3D.h (consult-only).
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x5AEAD0  Matrix3D::ScaleX (__thiscall)
//   FUNCTION: GAMEMD 0x5AEAF0  Matrix3D::ScaleY (__thiscall)

#include "matrix3d_scale_methods.h"

// FUNCTION: GAMEMD 0x5AEAD0  (__thiscall)
// Scale the local X axis: multiply column 0 of every row by x in place.
// Retail is fully unrolled x87: FLD x / FMUL [col0] / FSTP [col0] x3.
void Matrix3D::ScaleX(float x)
{
    Row[0][0] *= x;
    Row[1][0] *= x;
    Row[2][0] *= x;
}

// FUNCTION: GAMEMD 0x5AEAF0  (__thiscall)
// Scale the local Y axis: multiply column 1 of every row by y in place.
void Matrix3D::ScaleY(float y)
{
    Row[0][1] *= y;
    Row[1][1] *= y;
    Row[2][1] *= y;
}
