// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI: `LEA EDX,[ECX+0xDE4]` at 0x6D2078 (the iso transform
//   matrix passed to the Matrix3D apply helper), the 12-byte vector copy
//   `[EAX]`/`[EAX+4]`/`[EAX+8]` at 0x6D20A1-0x6D20B5, and the helper's own
//   body at 0x5AFB80 (ECX = result, EDX = matrix, one stack arg = vector,
//   3 rows x 4 float columns at `[EDX+0x00..0x2C]`). Method names from the
//   YRpp method map (names only, no text copied).
#ifndef GG_MATCH_RENDERER_TACTICAL_CLASS_MATRIX_METHODS_H
#define GG_MATCH_RENDERER_TACTICAL_CLASS_MATRIX_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Point2D
{
    int X;                    // +0x0000
    int Y;                    // +0x0004
};
GG_STATIC_ASSERT(sizeof(Point2D) == 0x8);

struct Vector3D
{
    float X;                  // +0x0000
    float Y;                  // +0x0004
    float Z;                  // +0x0008
};
GG_STATIC_ASSERT(sizeof(Vector3D) == 0xC);
GG_STATIC_ASSERT(offsetof(Vector3D, Y) == 0x4);
GG_STATIC_ASSERT(offsetof(Vector3D, Z) == 0x8);

// 3x4 row-major float affine transform (see match/movement/matrix3d_methods.h;
// redefined locally so this TU stays standalone and can carry the apply
// helper's declaration).
struct Matrix3D
{
    float Row[3][4];          // +0x0000

    // FUNCTION: GAMEMD 0x5AFB80 (decl; reloc) — result = mat * vec, with the
    // result pointer in ECX, the matrix in EDX and the vector on the stack.
    static Vector3D* __fastcall MatrixApply(Vector3D* ret, const Matrix3D* mat,
                                            const Vector3D* vec);
};
GG_STATIC_ASSERT(sizeof(Matrix3D) == 0x30);

class Tactical
{
public:
    char     _pad000[0xDE4];  // +0x0000
    Matrix3D IsoTransformMatrix;  // +0x0DE4  passed to MatrixApply in EDX

    // FUNCTION: GAMEMD 0x6D1FE0
    int* AdjustForZShapeMove(int* pDest, const int* pClient);

    // FUNCTION: GAMEMD 0x6D2070
    int* ApplyMatrix_Pixel(int* pOut, const int* pIn);
};
GG_STATIC_ASSERT(offsetof(Tactical, IsoTransformMatrix) == 0xDE4);

#endif  // GG_MATCH_RENDERER_TACTICAL_CLASS_MATRIX_METHODS_H
