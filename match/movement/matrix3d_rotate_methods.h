// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets/layout derived from the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI (member-access disassembly at 0x5AF120-0x5AF198),
//   cross-checked against YRpp (reconfirmed here).
//
// Matrix3D — a 4x3 (3 rows x 4 cols) row-major float affine transform.
//   Storage is a flat float[3][4] at offset 0 (no base class / no vtable).
//   RotateY(Sin, Cos) rotates about the local Y axis: for each row it mixes
//   col0 (byte 0x00/0x10/0x20) and col2 (byte 0x08/0x18/0x28) in place,
//   leaving col1 and the translation column untouched. This mirrors the
//   committed match/movement/matrix3d_methods.h 0x30 layout.
#ifndef GG_MATCH_MOVEMENT_MATRIX3D_ROTATE_METHODS_H
#define GG_MATCH_MOVEMENT_MATRIX3D_ROTATE_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Matrix3D
{
    void RotateX(float Sin, float Cos);   // GAMEMD 0x5AF000 __thiscall
    void RotateY(float Sin, float Cos);   // GAMEMD 0x5AF120 __thiscall

    // 3 rows of 4 floats = 0x30 bytes. Row[i][j] lives at byte (i*4 + j)*4.
    float Row[3][4];                      // +0x00
};

GG_STATIC_ASSERT(sizeof(Matrix3D) == 0x30);
GG_STATIC_ASSERT(offsetof(Matrix3D, Row) == 0x00);

#endif  // GG_MATCH_MOVEMENT_MATRIX3D_ROTATE_METHODS_H
