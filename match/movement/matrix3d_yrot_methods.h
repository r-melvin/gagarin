// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets/layout derived from the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI (member-access disassembly at 0x5AF410-0x5AF46C, plus the
//   callee signatures at 0x5AFB80 MatrixApply and 0x4CAE30 atan2), cross-checked
//   against YRpp Matrix3D.h (consult-only; reconfirmed here).
//
// Matrix3D — a 4x3 (3 rows x 4 cols) row-major float affine transform.
//   Storage is a flat float[3][4] at offset 0 (no base class / no vtable),
//   matching the committed match/movement/matrix3d_methods.h 0x30 layout.
//   GetYRotation transforms the unit +Z axis (0,0,1) through the matrix and
//   returns atan2(result.X, result.Z) — the rotation angle about the Y axis.
#ifndef GG_MATCH_MOVEMENT_MATRIX3D_YROT_METHODS_H
#define GG_MATCH_MOVEMENT_MATRIX3D_YROT_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// 3x float32 sub-cell point. MatrixApply reads X/Y/Z at byte 0x00/0x04/0x08.
struct Vector3D
{
    float X;  // +0x00
    float Y;  // +0x04
    float Z;  // +0x08

    Vector3D() {}
    Vector3D(float x, float y, float z) : X(x), Y(y), Z(z) {}
};

GG_STATIC_ASSERT(offsetof(Vector3D, X) == 0x00);
GG_STATIC_ASSERT(offsetof(Vector3D, Y) == 0x04);
GG_STATIC_ASSERT(offsetof(Vector3D, Z) == 0x08);

struct Matrix3D
{
    Vector3D operator*(const Vector3D& point) const;   // inline via 0x5AFB80
    double GetYRotation() const;                        // GAMEMD 0x5AF410

    // 3 rows of 4 floats = 0x30 bytes. Row[i][j] lives at byte (i*4 + j)*4.
    float Row[3][4];                                    // +0x00
};

GG_STATIC_ASSERT(sizeof(Matrix3D) == 0x30);
GG_STATIC_ASSERT(offsetof(Matrix3D, Row) == 0x00);

// Retail callee at 0x5AFB80 — Matrix3D x Vector3D affine apply. NOT matched
// here; declared so cl emits a (reloc-normalised) call. __fastcall: ret in
// ECX, mat in EDX, vec on the stack; returns the ret pointer.
Vector3D* __fastcall MatrixApply(Vector3D* ret, const Matrix3D* mat, const Vector3D* vec);

// Inlined into GetYRotation: builds the transformed point in place.
inline Vector3D Matrix3D::operator*(const Vector3D& point) const
{
    Vector3D ret;
    MatrixApply(&ret, this, &point);
    return ret;
}

#endif  // GG_MATCH_MOVEMENT_MATRIX3D_YROT_METHODS_H
