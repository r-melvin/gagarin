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
#include "../_layout/vector3d.h"
#include "../_layout/matrix3d.h"

#include "../_layout/geometry2d.h"
GG_STATIC_ASSERT(sizeof(Point2D) == 0x8);

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
