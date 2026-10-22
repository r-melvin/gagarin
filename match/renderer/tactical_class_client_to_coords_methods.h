// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x6D2280: the client point is read as `[EAX]` /
//   `[EAX+4]` off the second stacked argument, the view limits are the
//   globals `[0xB0CE30]` (X bound) and `[0xB0CE2C] + [0xB0CE34]` (Y bound),
//   the view offset is `[ECX+0xB0]` / `[ECX+0xB4]` (loaded together, one
//   Point2D), the iso transform is
//   `LEA EDX,[ECX+0xDE4]` handed to the Matrix3D apply helper at 0x5AFB80
//   (ECX = result, EDX = matrix, one stack arg = vector), the truncation is
//   the CRT `__ftol` at 0x7C5F00, and the out-of-view result is the 12-byte
//   global at 0xB0CE08 copied dword-wise. The method name is the YRpp one
//   (name only). +0xDE4 is the IsoTransformMatrix already
//   confirmed in match/renderer/tactical_class_matrix_methods.h (not edited;
//   re-declared here so this TU stands alone).
#ifndef GG_MATCH_RENDERER_TACTICAL_CLASS_CLIENT_TO_COORDS_METHODS_H
#define GG_MATCH_RENDERER_TACTICAL_CLASS_CLIENT_TO_COORDS_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Point2D_006D2280
{
    int X;                    // +0x0000
    int Y;                    // +0x0004
};
GG_STATIC_ASSERT(sizeof(Point2D_006D2280) == 0x8);

struct Coord_006D2280
{
    int X;                    // +0x0000
    int Y;                    // +0x0004
    int Z;                    // +0x0008
};
GG_STATIC_ASSERT(sizeof(Coord_006D2280) == 0xC);
GG_STATIC_ASSERT(offsetof(Coord_006D2280, Z) == 0x8);

struct Vector3D_006D2280
{
    float X;                  // +0x0000
    float Y;                  // +0x0004
    float Z;                  // +0x0008
};
GG_STATIC_ASSERT(sizeof(Vector3D_006D2280) == 0xC);

// 3x4 row-major float affine transform.
struct Matrix3D_006D2280
{
    float Row[3][4];          // +0x0000

    // FUNCTION: GAMEMD 0x5AFB80 (decl; reloc) — result = mat * vec, with the
    // result pointer in ECX, the matrix in EDX and the vector on the stack.
    static Vector3D_006D2280* __fastcall MatrixApply(Vector3D_006D2280* ret,
                                                     const Matrix3D_006D2280* mat,
                                                     const Vector3D_006D2280* vec);
};
GG_STATIC_ASSERT(sizeof(Matrix3D_006D2280) == 0x30);

// GLOBAL: GAMEMD 0xB0CE08 — the "no coordinate" CoordStruct returned for a
// client point outside the view.
extern Coord_006D2280 DAT_00B0CE08;
// GLOBAL: GAMEMD 0xB0CE2C — view Y origin (added to the Y extent below).
extern int DAT_00B0CE2C;
// GLOBAL: GAMEMD 0xB0CE30 — view X extent.
extern int DAT_00B0CE30;
// GLOBAL: GAMEMD 0xB0CE34 — view Y extent.
extern int DAT_00B0CE34;

struct Tactical_006D2280
{
    char     _pad000[0xB0];              // +0x0000
    Point2D_006D2280 Offset_B0;          // +0x00B0  view offset (X, Y), read as one struct
    char     _padB8[0xDE4 - 0xB8];       // +0x00B8
    Matrix3D_006D2280 IsoTransformMatrix; // +0x0DE4

    // FUNCTION: GAMEMD 0x6D2280 — TacticalClass::ClientToCoords.
    Coord_006D2280* ClientToCoords(Coord_006D2280* pDest,
                                   const Point2D_006D2280* pClient);
};
GG_STATIC_ASSERT(offsetof(Tactical_006D2280, Offset_B0) == 0xB0);
GG_STATIC_ASSERT(offsetof(Tactical_006D2280, Offset_B0.Y) == 0xB4);
GG_STATIC_ASSERT(offsetof(Tactical_006D2280, IsoTransformMatrix) == 0xDE4);

#endif  // GG_MATCH_RENDERER_TACTICAL_CLASS_CLIENT_TO_COORDS_METHODS_H
