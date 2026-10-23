// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Layout read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x5AEF60 / 0x5AF080 / 0x5AF1A0: the matrix is 3 rows x
//   4 floats at `[ESI+0x00..0x2C]`; RotateX touches `[ESI+0x4]/[ESI+0x8]`
//   (cols 1,2), RotateY `[ESI]/[ESI+0x8]` (cols 0,2), RotateZ `[ESI]/[ESI+0x4]`
//   (cols 0,1) in each of the three rows (+0x00, +0x10, +0x20). Method names
//   from YRpp (names only, no text copied).
//
// Matrix3D itself is match/_layout/matrix3d.h.
#ifndef GG_MATCH_RENDERER_MATRIX3D_ROTATE_METHODS_H
#define GG_MATCH_RENDERER_MATRIX3D_ROTATE_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/matrix3d.h"

// Table-driven trig helpers. Both take a double on the stack (the caller
// widens the float angle once and pushes the same 8 bytes twice) and hand back
// the table entry in ST(0).
// FUNCTION: GAMEMD 0x4CACB0 (decl; reloc) -- table sin(double).
extern "C" float __cdecl FUN_004CACB0(double angle);
// FUNCTION: GAMEMD 0x4CAD00 (decl; reloc) -- table cos(double).
extern "C" float __cdecl FUN_004CAD00(double angle);

#endif  // GG_MATCH_RENDERER_MATRIX3D_ROTATE_METHODS_H
