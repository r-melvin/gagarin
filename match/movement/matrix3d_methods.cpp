// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm). Names
//   cross-checked against YRpp.
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x5AE610  Matrix3D::FUN_005AE610 (__thiscall)
//   FUNCTION: GAMEMD 0x5AE980  Matrix3D::TranslateX   (__thiscall)
//   FUNCTION: GAMEMD 0x5AE9B0  Matrix3D::TranslateY   (__thiscall)
//   FUNCTION: GAMEMD 0x5AE9E0  Matrix3D::TranslateZ   (__thiscall)
//   FUNCTION: GAMEMD 0x5AF980  FUN_005AF980 (__fastcall result/left, right on stack)

#include "matrix3d_native_helpers.h"


GG_STATIC_ASSERT(offsetof(Matrix3D, Row) + sizeof(((Matrix3D*)0)->Row[0]) * 0 + sizeof(float) * 0 == 0x00);
GG_STATIC_ASSERT(offsetof(Matrix3D, Row) + sizeof(((Matrix3D*)0)->Row[0]) * 0 + sizeof(float) * 1 == 0x04);
GG_STATIC_ASSERT(offsetof(Matrix3D, Row) + sizeof(((Matrix3D*)0)->Row[0]) * 0 + sizeof(float) * 2 == 0x08);
GG_STATIC_ASSERT(offsetof(Matrix3D, Row) + sizeof(((Matrix3D*)0)->Row[0]) * 0 + sizeof(float) * 3 == 0x0C);
GG_STATIC_ASSERT(offsetof(Matrix3D, Row) + sizeof(((Matrix3D*)0)->Row[0]) * 1 + sizeof(float) * 0 == 0x10);
GG_STATIC_ASSERT(offsetof(Matrix3D, Row) + sizeof(((Matrix3D*)0)->Row[0]) * 1 + sizeof(float) * 1 == 0x14);
GG_STATIC_ASSERT(offsetof(Matrix3D, Row) + sizeof(((Matrix3D*)0)->Row[0]) * 1 + sizeof(float) * 2 == 0x18);
GG_STATIC_ASSERT(offsetof(Matrix3D, Row) + sizeof(((Matrix3D*)0)->Row[0]) * 1 + sizeof(float) * 3 == 0x1C);
GG_STATIC_ASSERT(offsetof(Matrix3D, Row) + sizeof(((Matrix3D*)0)->Row[0]) * 2 + sizeof(float) * 0 == 0x20);
GG_STATIC_ASSERT(offsetof(Matrix3D, Row) + sizeof(((Matrix3D*)0)->Row[0]) * 2 + sizeof(float) * 1 == 0x24);
GG_STATIC_ASSERT(offsetof(Matrix3D, Row) + sizeof(((Matrix3D*)0)->Row[0]) * 2 + sizeof(float) * 2 == 0x28);
GG_STATIC_ASSERT(offsetof(Matrix3D, Row) + sizeof(((Matrix3D*)0)->Row[0]) * 2 + sizeof(float) * 3 == 0x2C);

// Native 0x5AE610 copies twelve dwords from the stack source to ECX,
// returns ECX in EAX and uses RET 4. The placeholder does not assert
// constructor versus assignment identity.
// FUNCTION: GAMEMD 0x5AE610
Matrix3D& Matrix3D::FUN_005AE610(const Matrix3D& source)
{
    *this = source;
    return *this;
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

// Native 0x5AF980 computes all twelve affine coefficients into a temporary,
// then copies that complete result to the hidden output; inputs may alias it.
// The left translation is added only in column3.
// FUNCTION: GAMEMD 0x5AF980
Matrix3D FUN_005AF980(const Matrix3D& left, const Matrix3D& right)
{
    Matrix3D result;
    result.Row[0][0] = left.Row[0][2] * right.Row[2][0] + left.Row[0][1] * right.Row[1][0] + left.Row[0][0] * right.Row[0][0];
    result.Row[1][0] = left.Row[1][2] * right.Row[2][0] + left.Row[1][1] * right.Row[1][0] + left.Row[1][0] * right.Row[0][0];
    result.Row[2][0] = left.Row[2][2] * right.Row[2][0] + left.Row[2][1] * right.Row[1][0] + left.Row[2][0] * right.Row[0][0];
    result.Row[0][1] = left.Row[0][2] * right.Row[2][1] + left.Row[0][1] * right.Row[1][1] + left.Row[0][0] * right.Row[0][1];
    result.Row[1][1] = left.Row[1][2] * right.Row[2][1] + left.Row[1][1] * right.Row[1][1] + left.Row[1][0] * right.Row[0][1];
    result.Row[2][1] = left.Row[2][2] * right.Row[2][1] + left.Row[2][1] * right.Row[1][1] + left.Row[2][0] * right.Row[0][1];
    result.Row[0][2] = left.Row[0][2] * right.Row[2][2] + left.Row[0][1] * right.Row[1][2] + left.Row[0][0] * right.Row[0][2];
    result.Row[1][2] = left.Row[1][2] * right.Row[2][2] + left.Row[1][1] * right.Row[1][2] + left.Row[1][0] * right.Row[0][2];
    result.Row[2][2] = left.Row[2][2] * right.Row[2][2] + left.Row[2][1] * right.Row[1][2] + left.Row[2][0] * right.Row[0][2];
    result.Row[0][3] = left.Row[0][2] * right.Row[2][3] + left.Row[0][1] * right.Row[1][3] + left.Row[0][0] * right.Row[0][3] + left.Row[0][3];
    result.Row[1][3] = left.Row[1][2] * right.Row[2][3] + left.Row[1][1] * right.Row[1][3] + left.Row[1][0] * right.Row[0][3] + left.Row[1][3];
    result.Row[2][3] = left.Row[2][2] * right.Row[2][3] + left.Row[2][1] * right.Row[1][3] + left.Row[2][0] * right.Row[0][3] + left.Row[2][3];
    return result;
}
