// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets/layout derived from the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI (member-access disassembly at 0x5AE890-0x5AEB40),
//   cross-checked against YRpp Matrix3D.h (consult-only; reconfirmed here).
//
// Matrix3D — a 4x3 (3 rows x 4 cols) row-major float affine transform.
//   Storage is a flat float[3][4] at offset 0 (no base class / no vtable):
//   Row[i][0..2] is the rotation/scale 3x3, Row[i][3] the translation column.
//   Byte offset of Row[i][j] is (i*4 + j)*4.  Mirrors the committed
//   match/movement/matrix3d_methods.h 0x30 layout.
//
//   Translate (0x5AE890) is the fully-unrolled combined translate: for each
//   row, Row[i][3] += y*Row[i][1] + z*Row[i][2] + x*Row[i][0] (x87 add order
//   confirmed from disasm: y*col1, z*col2, sum, +x*col0, +col3).
//   Scale   (0x5AEA10) scales the 3x3 rotation block column-by-column.
//   ScaleZ  (0x5AEB20) scales column 2 (byte 0x08/0x18/0x28) in place.
#ifndef GG_MATCH_MOVEMENT_MATRIX3D_MORE_METHODS_H
#define GG_MATCH_MOVEMENT_MATRIX3D_MORE_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Matrix3D
{
    void Translate(float x, float y, float z);  // GAMEMD 0x5AE890 __thiscall
    void Scale(float factor);                   // GAMEMD 0x5AEA10 __thiscall
    void ScaleZ(float z);                       // GAMEMD 0x5AEB20 __thiscall

    // 3 rows of 4 floats = 0x30 bytes. Row[i][j] lives at byte (i*4 + j)*4.
    float Row[3][4];                            // +0x00
};

GG_STATIC_ASSERT(sizeof(Matrix3D) == 0x30);
GG_STATIC_ASSERT(offsetof(Matrix3D, Row) == 0x00);

#endif  // GG_MATCH_MOVEMENT_MATRIX3D_MORE_METHODS_H
