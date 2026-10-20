// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets/layout derived from the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI (member-access disassembly at 0x5AEAD0-0x5AEB0E),
//   cross-checked against YRpp Matrix3D.h (consult-only; reconfirmed here).
//
// Matrix3D — a 4x3 (3 rows x 4 cols) row-major float affine transform.
//   Storage is a flat float[3][4] at offset 0 (no base class / no vtable).
//   ScaleX/ScaleY multiply a single column in-place: ScaleX touches
//   col0 (byte 0x00/0x10/0x20), ScaleY touches col1 (byte 0x04/0x14/0x24).
//   This mirrors the committed match/movement/matrix3d_methods.h 0x30 layout.
#ifndef GG_MATCH_MOVEMENT_MATRIX3D_SCALE_METHODS_H
#define GG_MATCH_MOVEMENT_MATRIX3D_SCALE_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Matrix3D
{
    void ScaleX(float x);         // GAMEMD 0x5AEAD0 __thiscall
    void ScaleY(float y);         // GAMEMD 0x5AEAF0 __thiscall

    // 3 rows of 4 floats = 0x30 bytes. Row[i][j] lives at byte (i*4 + j)*4.
    float Row[3][4];              // +0x00
};

GG_STATIC_ASSERT(sizeof(Matrix3D) == 0x30);
GG_STATIC_ASSERT(offsetof(Matrix3D, Row) == 0x00);

#endif  // GG_MATCH_MOVEMENT_MATRIX3D_SCALE_METHODS_H
