// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x5AFC20. Name from
//   YRpp.

#include "matrix3d_transpose_methods.h"

// FUNCTION: GAMEMD 0x5AFC20
//
// Inverse of a rigid transform: the 3x3 rotation block is transposed and the
// translation column becomes minus the transposed rotation applied to the
// original translation. The result is assembled in a stack local and block-
// copied into the caller's return buffer.
Matrix3D __fastcall Matrix3D::TransposeMatrix(const Matrix3D& mat)
{
    Matrix3D t;

    t.Row[0][0] = mat.Row[0][0];
    t.Row[0][1] = mat.Row[1][0];
    t.Row[0][2] = mat.Row[2][0];
    t.Row[1][0] = mat.Row[0][1];
    t.Row[1][1] = mat.Row[1][1];
    t.Row[1][2] = mat.Row[2][1];
    t.Row[2][0] = mat.Row[0][2];
    t.Row[2][1] = mat.Row[1][2];
    t.Row[2][2] = mat.Row[2][2];

    t.Row[0][3] = -(t.Row[0][0] * mat.Row[0][3] + t.Row[0][2] * mat.Row[2][3] + t.Row[0][1] * mat.Row[1][3]);
    t.Row[1][3] = -(t.Row[1][0] * mat.Row[0][3] + t.Row[1][2] * mat.Row[2][3] + t.Row[1][1] * mat.Row[1][3]);
    t.Row[2][3] = -(t.Row[2][0] * mat.Row[0][3] + t.Row[2][2] * mat.Row[2][3] + t.Row[2][1] * mat.Row[1][3]);

    return t;
}
