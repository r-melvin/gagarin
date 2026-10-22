// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets/layout derived from the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI (member-access disassembly at 0x5AE860-0x5AEA07),
//   cross-checked against YRpp (reconfirmed here).
//
// Matrix3D — a 4x3 (3 rows x 4 cols) row-major float affine transform.
//   Storage is a flat float[3][4] at offset 0 (no base class / no vtable):
//   Row[i][0..2] is the rotation/scale 3x3, Row[i][3] the translation column.
//   Confirmed from MakeIdentity writing the bit pattern 0x3f800000 (=1.0f) at
//   byte offsets 0x00, 0x14, 0x28 (the i==j diagonal) and 0.0f elsewhere.
#ifndef GG_MATCH_MOVEMENT_MATRIX3D_METHODS_H
#define GG_MATCH_MOVEMENT_MATRIX3D_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Matrix3D
{
    void MakeIdentity();          // GAMEMD 0x5AE860 __thiscall
    void TranslateX(float x);     // GAMEMD 0x5AE980 __thiscall
    void TranslateY(float y);     // GAMEMD 0x5AE9B0 __thiscall
    void TranslateZ(float z);     // GAMEMD 0x5AE9E0 __thiscall

    // 3 rows of 4 floats = 0x30 bytes. Row[i][j] lives at byte (i*4 + j)*4.
    float Row[3][4];              // +0x00
};

GG_STATIC_ASSERT(sizeof(Matrix3D) == 0x30);
GG_STATIC_ASSERT(offsetof(Matrix3D, Row) == 0x00);

#endif  // GG_MATCH_MOVEMENT_MATRIX3D_METHODS_H
