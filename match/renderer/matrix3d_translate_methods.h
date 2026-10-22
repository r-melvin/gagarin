// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Layout read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x5AE8F0: the vector is a 3-float array on the stack
//   arg (`[EAX]`, `[EAX+4]`, `[EAX+8]`), the matrix is 3 rows x 4 floats at
//   `[ECX+0x00..0x2C]` with the translation column at `[ECX+0xC]`,
//   `[ECX+0x1C]`, `[ECX+0x2C]`. Method name from YRpp (consult-only;
//   name only, no text copied).
#ifndef GG_MATCH_RENDERER_MATRIX3D_TRANSLATE_METHODS_H
#define GG_MATCH_RENDERER_MATRIX3D_TRANSLATE_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Vector3D
{
    float X;                  // +0x0000
    float Y;                  // +0x0004
    float Z;                  // +0x0008
};
GG_STATIC_ASSERT(offsetof(Vector3D, Y) == 0x4);
GG_STATIC_ASSERT(offsetof(Vector3D, Z) == 0x8);
GG_STATIC_ASSERT(sizeof(Vector3D) == 0xC);

// 3x4 row-major float affine transform (see match/movement/matrix3d_methods.h;
// redefined locally so this TU stays standalone).
struct Matrix3D
{
    float Row[3][4];          // +0x0000

    // Per-axis translations. In retail these are also standalone functions
    // (0x5AE980 / 0x5AE9B0 / 0x5AE9E0, matched in match/movement); here they
    // are the inline bodies that Translate expands.
    void TranslateX(float x)
    {
        this->Row[0][3] += x * this->Row[0][0];
        this->Row[1][3] += x * this->Row[1][0];
        this->Row[2][3] += x * this->Row[2][0];
    }
    void TranslateY(float y)
    {
        this->Row[0][3] += y * this->Row[0][1];
        this->Row[1][3] += y * this->Row[1][1];
        this->Row[2][3] += y * this->Row[2][1];
    }
    void TranslateZ(float z)
    {
        this->Row[0][3] += z * this->Row[0][2];
        this->Row[1][3] += z * this->Row[1][2];
        this->Row[2][3] += z * this->Row[2][2];
    }

    // FUNCTION: GAMEMD 0x5AE8F0
    void Translate(const Vector3D& vec);
};
GG_STATIC_ASSERT(offsetof(Matrix3D, Row) == 0x0);
GG_STATIC_ASSERT(sizeof(Matrix3D) == 0x30);

#endif  // GG_MATCH_RENDERER_MATRIX3D_TRANSLATE_METHODS_H
