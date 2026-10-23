// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x5AEF60 / 0x5AF080 /
//   0x5AF1A0. Names from YRpp.

#include "matrix3d_rotate_methods.h"

// The (Sin, Cos) rotations that the angle forms expand in place. Retail also
// has standalone RotateX/RotateY(Sin, Cos) at 0x5AF000 / 0x5AF120 (matched in
// match/movement, called from 0x5AF550), but the angle forms below do not call
// them, and their term order per row (the x87 emission order read off these
// bytes) differs from those bodies, so they are kept file-local here.
static inline void RotateRowsX(Matrix3D* m, float Sin, float Cos)
{
    float b, c;

    b = m->Row[0][1];
    c = m->Row[0][2];
    m->Row[0][1] = b * Cos + c * Sin;
    m->Row[0][2] = c * Cos - b * Sin;

    b = m->Row[1][1];
    c = m->Row[1][2];
    m->Row[1][1] = b * Cos + c * Sin;
    m->Row[1][2] = c * Cos - b * Sin;

    b = m->Row[2][1];
    c = m->Row[2][2];
    m->Row[2][1] = b * Cos + c * Sin;
    m->Row[2][2] = c * Cos - b * Sin;
}

static inline void RotateRowsY(Matrix3D* m, float Sin, float Cos)
{
    float a, c;

    a = m->Row[0][0];
    c = m->Row[0][2];
    m->Row[0][0] = a * Cos - c * Sin;
    m->Row[0][2] = c * Cos + a * Sin;

    a = m->Row[1][0];
    c = m->Row[1][2];
    m->Row[1][0] = a * Cos - c * Sin;
    m->Row[1][2] = c * Cos + a * Sin;

    a = m->Row[2][0];
    c = m->Row[2][2];
    m->Row[2][0] = a * Cos - c * Sin;
    m->Row[2][2] = c * Cos + a * Sin;
}

static inline void RotateRowsZ(Matrix3D* m, float Sin, float Cos)
{
    float a, b;

    a = m->Row[0][0];
    b = m->Row[0][1];
    m->Row[0][0] = b * Sin + a * Cos;
    m->Row[0][1] = b * Cos - a * Sin;

    a = m->Row[1][0];
    b = m->Row[1][1];
    m->Row[1][0] = b * Sin + a * Cos;
    m->Row[1][1] = b * Cos - a * Sin;

    a = m->Row[2][0];
    b = m->Row[2][1];
    m->Row[2][0] = b * Sin + a * Cos;
    m->Row[2][1] = b * Cos - a * Sin;
}

// FUNCTION: GAMEMD 0x5AEF60
//
// Rotate about the local X axis by an angle in radians. The angle is widened
// to double once, both table-trig helpers are called on it, and the (Sin, Cos)
// body is expanded in place. The sine is spilled to a stack slot while the
// cosine, computed last, stays on the x87 stack.
void Matrix3D::RotateX(float angle)
{
    float s = FUN_004CACB0(angle);
    float c = FUN_004CAD00(angle);
    RotateRowsX(this, s, c);
}

// FUNCTION: GAMEMD 0x5AF080
//
// Rotate about the local Y axis by an angle in radians; same shape as RotateX.
void Matrix3D::RotateY(float angle)
{
    float s = FUN_004CACB0(angle);
    float c = FUN_004CAD00(angle);
    RotateRowsY(this, s, c);
}

// FUNCTION: GAMEMD 0x5AF1A0
//
// Rotate about the local Z axis by an angle in radians. Unlike X and Y the
// cosine is fetched first here, so it is the sine that stays on the x87 stack.
void Matrix3D::RotateZ(float angle)
{
    float c = FUN_004CAD00(angle);
    float s = FUN_004CACB0(angle);
    RotateRowsZ(this, s, c);
}
