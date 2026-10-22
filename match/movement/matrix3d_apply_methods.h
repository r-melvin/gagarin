// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes and the frame read off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x5AFB80. Row stride 0x10 matches the committed
//   Matrix3D model; the translation column is Row[i][3].
//
// Genuine three-argument __fastcall: the destination arrives in ECX, the matrix
// in EDX and the source vector on the stack, and the destination is also the
// return value (`MOV EAX,ECX` early in the body).
//
// The result is built in a 12-byte stack temporary and only copied to the
// destination at the end, which is what lets the destination alias the source.
#ifndef GG_MATCH_MOVEMENT_MATRIX3D_APPLY_METHODS_H
#define GG_MATCH_MOVEMENT_MATRIX3D_APPLY_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Vector3D
{
    float X;   // +0x00
    float Y;   // +0x04
    float Z;   // +0x08
};
GG_STATIC_ASSERT(sizeof(Vector3D) == 0x0C);

struct Matrix3DRows
{
    float Row[3][4];   // +0x00, row stride 0x10
};
GG_STATIC_ASSERT(sizeof(Matrix3DRows) == 0x30);

Vector3D* Matrix3D_MatrixApply(Vector3D* out, Matrix3DRows* matrix,
                               Vector3D* vector);   // GAMEMD 0x5AFB80

#endif  // GG_MATCH_MOVEMENT_MATRIX3D_APPLY_METHODS_H
