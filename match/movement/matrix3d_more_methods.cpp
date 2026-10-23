// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm). Names
//   cross-checked against YRpp.
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x5AE890  Matrix3D::Translate (__thiscall)
//   FUNCTION: GAMEMD 0x5AEA10  Matrix3D::Scale     (__thiscall)
//   FUNCTION: GAMEMD 0x5AEB20  Matrix3D::ScaleZ    (__thiscall)

#include "../_layout/matrix3d.h"


// FUNCTION: GAMEMD 0x5AEA10  (__thiscall)
// Uniform scale of the 3x3 rotation block, evaluated column-major
// (col0 rows 0..2, col1 rows 0..2, col2 rows 0..2). Translation untouched.
void Matrix3D::Scale(float factor)
{
    Row[0][0] *= factor;
    Row[1][0] *= factor;
    Row[2][0] *= factor;
    Row[0][1] *= factor;
    Row[1][1] *= factor;
    Row[2][1] *= factor;
    Row[0][2] *= factor;
    Row[1][2] *= factor;
    Row[2][2] *= factor;
}

// FUNCTION: GAMEMD 0x5AEB20  (__thiscall)
// Scale the local Z axis: multiply column 2 of every row by z in place.
void Matrix3D::ScaleZ(float z)
{
    Row[0][2] *= z;
    Row[1][2] *= z;
    Row[2][2] *= z;
}
