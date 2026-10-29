// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x5AEC40 / 0x5AEE50. Each mixes two whole rows (all four columns, translation
//   included) by an angle: rows 1+2 for X, rows 0+1 for Z.

#include "matrix3d_rotate_methods.h"

// FUNCTION: GAMEMD 0x5AEC40
// Rotate the Y and Z rows into each other by an angle in radians.
void Matrix3D::PreRotateX(float angle)
{
    float s = FUN_004CACB0(angle);
    float c = FUN_004CAD00(angle);

    float ns = -s;
    float a0 = Row[1][0];
    float a1 = Row[1][1];
    float a2 = Row[1][2];
    float a3 = Row[1][3];
    float b0 = Row[2][0];
    float b1 = Row[2][1];
    float b2 = Row[2][2];
    float b3 = Row[2][3];
    Row[1][0] = a0 * c + b0 * ns;
    Row[1][1] = a1 * c + b1 * ns;
    Row[1][2] = a2 * c + b2 * ns;
    Row[1][3] = a3 * c + b3 * ns;
    Row[2][0] = a0 * s + b0 * c;
    Row[2][1] = a1 * s + b1 * c;
    Row[2][2] = a2 * s + b2 * c;
    Row[2][3] = a3 * s + b3 * c;
}

// FUNCTION: GAMEMD 0x5AEE50
// Rotate the X and Y rows into each other by an angle in radians.
void Matrix3D::PreRotateZ(float angle)
{
    float s = FUN_004CACB0(angle);
    float c = FUN_004CAD00(angle);
    float ns = -s;

    float a0 = Row[0][0];
    float a1 = Row[0][1];
    float a2 = Row[0][2];
    float a3 = Row[0][3];
    float b0 = Row[1][0];
    float b1 = Row[1][1];
    float b2 = Row[1][2];
    float b3 = Row[1][3];
    Row[0][0] = a0 * c + b0 * ns;
    Row[0][1] = a1 * c + b1 * ns;
    Row[0][2] = a2 * c + b2 * ns;
    Row[0][3] = a3 * c + b3 * ns;
    Row[1][0] = a0 * s + b0 * c;
    Row[1][1] = a1 * s + b1 * c;
    Row[1][2] = a2 * s + b2 * c;
    Row[1][3] = a3 * s + b3 * c;
}
