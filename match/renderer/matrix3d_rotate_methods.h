// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Layout read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x5AEF60 / 0x5AF080 / 0x5AF1A0: the matrix is 3 rows x
//   4 floats at `[ESI+0x00..0x2C]`; RotateX touches `[ESI+0x4]/[ESI+0x8]`
//   (cols 1,2), RotateY `[ESI]/[ESI+0x8]` (cols 0,2), RotateZ `[ESI]/[ESI+0x4]`
//   (cols 0,1) in each of the three rows (+0x00, +0x10, +0x20). Method names
//   from YRpp (names only, no text copied).
//
// Matrix3D -- a 3x4 row-major float affine transform, the same 0x30 layout
// already proven in match/movement/matrix3d_methods.h. Redefined locally so
// this TU stays standalone.
#ifndef GG_MATCH_RENDERER_MATRIX3D_ROTATE_METHODS_H
#define GG_MATCH_RENDERER_MATRIX3D_ROTATE_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// Table-driven trig helpers. Both take a double on the stack (the caller
// widens the float angle once and pushes the same 8 bytes twice) and hand back
// the table entry in ST(0).
// FUNCTION: GAMEMD 0x4CACB0 (decl; reloc) -- table sin(double).
extern "C" float __cdecl FUN_004CACB0(double angle);
// FUNCTION: GAMEMD 0x4CAD00 (decl; reloc) -- table cos(double).
extern "C" float __cdecl FUN_004CAD00(double angle);

struct Matrix3D
{
    float Row[3][4];          // +0x0000

    // The (Sin, Cos) forms. In retail these are also standalone functions
    // (0x5AF000 / 0x5AF120 matched in match/movement); here they are the
    // in-class bodies the angle forms below expand. Term order per row is the
    // x87 emission order read off the retail bytes.
    void RotateX(float Sin, float Cos)
    {
        float b, c;

        b = this->Row[0][1];
        c = this->Row[0][2];
        this->Row[0][1] = b * Cos + c * Sin;
        this->Row[0][2] = c * Cos - b * Sin;

        b = this->Row[1][1];
        c = this->Row[1][2];
        this->Row[1][1] = b * Cos + c * Sin;
        this->Row[1][2] = c * Cos - b * Sin;

        b = this->Row[2][1];
        c = this->Row[2][2];
        this->Row[2][1] = b * Cos + c * Sin;
        this->Row[2][2] = c * Cos - b * Sin;
    }

    void RotateY(float Sin, float Cos)
    {
        float a, c;

        a = this->Row[0][0];
        c = this->Row[0][2];
        this->Row[0][0] = a * Cos - c * Sin;
        this->Row[0][2] = c * Cos + a * Sin;

        a = this->Row[1][0];
        c = this->Row[1][2];
        this->Row[1][0] = a * Cos - c * Sin;
        this->Row[1][2] = c * Cos + a * Sin;

        a = this->Row[2][0];
        c = this->Row[2][2];
        this->Row[2][0] = a * Cos - c * Sin;
        this->Row[2][2] = c * Cos + a * Sin;
    }

    void RotateZ(float Sin, float Cos)
    {
        float a, b;

        a = this->Row[0][0];
        b = this->Row[0][1];
        this->Row[0][0] = b * Sin + a * Cos;
        this->Row[0][1] = b * Cos - a * Sin;

        a = this->Row[1][0];
        b = this->Row[1][1];
        this->Row[1][0] = b * Sin + a * Cos;
        this->Row[1][1] = b * Cos - a * Sin;

        a = this->Row[2][0];
        b = this->Row[2][1];
        this->Row[2][0] = b * Sin + a * Cos;
        this->Row[2][1] = b * Cos - a * Sin;
    }

    // FUNCTION: GAMEMD 0x5AE860 (decl; reloc) -- identity (body in
    // movement/matrix3d_methods.cpp, same symbol).
    void MakeIdentity();
    // FUNCTION: GAMEMD 0x5AEF60
    void RotateX(float angle);
    // FUNCTION: GAMEMD 0x5AF080
    void RotateY(float angle);
    // FUNCTION: GAMEMD 0x5AF1A0
    void RotateZ(float angle);
};
GG_STATIC_ASSERT(offsetof(Matrix3D, Row) == 0x00);
GG_STATIC_ASSERT(sizeof(Matrix3D) == 0x30);

#endif  // GG_MATCH_RENDERER_MATRIX3D_ROTATE_METHODS_H
