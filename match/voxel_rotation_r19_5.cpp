// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//   Address index: 0x7559D0 0x755A40.

#include "quaternion_matrix_methods.h"

// GLOBAL: GAMEMD 0xB43F10 -- the first rotation matrix table (0x30 bytes each).
extern Matrix3D DAT_00B43F10[];
// GLOBAL: GAMEMD 0xB44348 -- the first quaternion table.
extern QuaternionEntry DAT_00B44348[];
// GLOBAL: GAMEMD 0xB43188 -- the second quaternion table.
extern QuaternionEntry DAT_00B43188[];
// GLOBAL: GAMEMD 0xB45188 -- the second rotation matrix table.
extern Matrix3D DAT_00B45188[];

// FUNCTION: GAMEMD 0x7559D0
// The rotation between two table entries as a matrix: the table matrix when
// both indices are the same, else the interpolated quaternion converted.
void __fastcall FUN_007559D0(int from, int to, Matrix3D* out, double t)
{
    if (from == to) {
        *out = DAT_00B43F10[to];
        return;
    }
    *out = Matrix3D::FromQuaternion(FUN_00646590(DAT_00B44348[from], DAT_00B44348[to], (float)t));
}

// FUNCTION: GAMEMD 0x755A40
// Same as 0x7559D0 over the second pair of tables; returns the output matrix.
Matrix3D* __fastcall FUN_00755A40(Matrix3D* out, int from, int to, double t)
{
    if (from != to) {
        *out = Matrix3D::FromQuaternion(FUN_00646590(DAT_00B43188[from], DAT_00B43188[to], (float)t));
        return out;
    }
    *out = DAT_00B45188[to];
    return out;
}
