// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Layout read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x5AFC20: the source matrix is 3 rows x 4 floats at
//   `[EDX+0x00..0x2C]` (translation column `[EDX+0xC]`, `[EDX+0x1C]`,
//   `[EDX+0x2C]`); the result is built as a 0x30-byte stack local and copied
//   out with `MOV ECX,0xC; REP MOVSD` into the hidden return buffer that
//   arrived in ECX (`MOV EAX,ECX` .. `MOV EDI,EAX`). Method name from YRpp
//   (name only, no text copied).
#ifndef GG_MATCH_RENDERER_MATRIX3D_TRANSPOSE_METHODS_H
#define GG_MATCH_RENDERER_MATRIX3D_TRANSPOSE_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// 3x4 row-major float affine transform (see match/movement/matrix3d_methods.h;
// redefined locally so this TU stays standalone). Kept POD so the by-value
// return is the plain 12-dword block copy retail has.
struct Matrix3D
{
    float Row[3][4];          // +0x0000

    // FUNCTION: GAMEMD 0x5AFC20
    static Matrix3D TransposeMatrix(const Matrix3D& mat);
};
GG_STATIC_ASSERT(offsetof(Matrix3D, Row) == 0x0);
GG_STATIC_ASSERT(sizeof(Matrix3D) == 0x30);

#endif  // GG_MATCH_RENDERER_MATRIX3D_TRANSPOSE_METHODS_H
