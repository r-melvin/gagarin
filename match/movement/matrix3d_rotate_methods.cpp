// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm). Names
//   cross-checked against YRpp.
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x5AF000  Matrix3D::RotateX (__thiscall)
//   FUNCTION: GAMEMD 0x5AF120  Matrix3D::RotateY (__thiscall)

#include "../_layout/matrix3d.h"

// FUNCTION: GAMEMD 0x5AF000  (__thiscall)
// In-place rotation about the local X axis given pre-computed Sin/Cos, and the
// exact counterpart of RotateY below: it mixes the col1 (byte 0x04) and col2
// (byte 0x08) entries of each row, leaving col0 and the translation column
// alone. Retail is fully unrolled x87, three identical blocks.
//
// The parameter order was taken from the x87 trace, not assumed: the first
// argument is the one multiplied into the cross term, i.e. Sin, matching
// RotateY's (Sin, Cos) convention.
void Matrix3D::RotateX(float Sin, float Cos)
{
    float b, c;

    b = Row[0][1];
    c = Row[0][2];
    Row[0][1] = c * Sin + b * Cos;
    Row[0][2] = c * Cos - b * Sin;

    b = Row[1][1];
    c = Row[1][2];
    Row[1][1] = c * Sin + b * Cos;
    Row[1][2] = c * Cos - b * Sin;

    b = Row[2][1];
    c = Row[2][2];
    Row[2][1] = c * Sin + b * Cos;
    Row[2][2] = c * Cos - b * Sin;
}

// FUNCTION: GAMEMD 0x5AF120  (__thiscall)
// In-place rotation about the local Y axis given pre-computed Sin/Cos.
// For each of the 3 rows, mix the col0 (byte 0x00) and col2 (byte 0x08)
// entries; col1 and the translation column are untouched. Retail is fully
// unrolled x87 (FLD col0 / FLD col2 / dup-mul-subtract -> col0,
// dup-mul-add -> col2) three times.
void Matrix3D::RotateY(float Sin, float Cos)
{
    float a, c;

    a = Row[0][0];
    c = Row[0][2];
    Row[0][0] = a * Cos - c * Sin;
    Row[0][2] = c * Cos + a * Sin;

    a = Row[1][0];
    c = Row[1][2];
    Row[1][0] = a * Cos - c * Sin;
    Row[1][2] = c * Cos + a * Sin;

    a = Row[2][0];
    c = Row[2][2];
    Row[2][0] = a * Cos - c * Sin;
    Row[2][2] = c * Cos + a * Sin;
}
