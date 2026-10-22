// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm). Names
//   cross-checked against YRpp.
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x5AE860  Matrix3D::MakeIdentity (__thiscall)
//   FUNCTION: GAMEMD 0x5AE980  Matrix3D::TranslateX   (__thiscall)
//   FUNCTION: GAMEMD 0x5AE9B0  Matrix3D::TranslateY   (__thiscall)
//   FUNCTION: GAMEMD 0x5AE9E0  Matrix3D::TranslateZ   (__thiscall)

#include "matrix3d_methods.h"

// FUNCTION: GAMEMD 0x5AE860  (__thiscall)
// Reset to the identity transform. Retail is fully unrolled: 1.0f's bit
// pattern is hoisted into EDX, 0.0f into EAX, then the 12 cells are stored in
// source order, so the flat assignment list below reproduces it exactly.
void Matrix3D::MakeIdentity()
{
    Row[0][0] = 1.0f; Row[0][1] = 0.0f; Row[0][2] = 0.0f; Row[0][3] = 0.0f;
    Row[1][0] = 0.0f; Row[1][1] = 1.0f; Row[1][2] = 0.0f; Row[1][3] = 0.0f;
    Row[2][0] = 0.0f; Row[2][1] = 0.0f; Row[2][2] = 1.0f; Row[2][3] = 0.0f;
}

// FUNCTION: GAMEMD 0x5AE980  (__thiscall)
// Post-translate along local X: each row's translation gains x * its col0.
void Matrix3D::TranslateX(float x)
{
    Row[0][3] += x * Row[0][0];
    Row[1][3] += x * Row[1][0];
    Row[2][3] += x * Row[2][0];
}

// FUNCTION: GAMEMD 0x5AE9B0  (__thiscall)
void Matrix3D::TranslateY(float y)
{
    Row[0][3] += y * Row[0][1];
    Row[1][3] += y * Row[1][1];
    Row[2][3] += y * Row[2][1];
}

// FUNCTION: GAMEMD 0x5AE9E0  (__thiscall)
void Matrix3D::TranslateZ(float z)
{
    Row[0][3] += z * Row[0][2];
    Row[1][3] += z * Row[1][2];
    Row[2][3] += z * Row[2][2];
}
