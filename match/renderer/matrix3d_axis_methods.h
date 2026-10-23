// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Layout and calling shape read numerically off the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI at 0x646480: the __fastcall
//   entry with the hidden result pointer in ECX (copied to EAX and returned
//   with `RET 4`), the axis in EDX read as the three floats `[EDX]`,
//   `[EDX+4]`, `[EDX+8]`, the angle as `FLD float [ESP+0x3C]` (the one stack
//   argument); the length through `CALL 0x4CAC40` (sqrt) compared with the
//   0.0 double at 0x7E2800 (`TEST AH,0x40`), the half angle `FMUL float
//   [0x7E5168]` (0.5f) pushed twice as a double to `CALL 0x4CACB0` (sin) and
//   `CALL 0x4CAD00` (cos), and the four result floats copied out with four
//   dword moves to `[EAX]..[EAX+0xC]`. Names from the YRpp method map
//  : Matrix3D::FromAxis; the result layout is the
//   Quaternion {X, Y, Z, W} of match/_layout/quaternion.h.
#ifndef GG_MATCH_RENDERER_MATRIX3D_AXIS_METHODS_H
#define GG_MATCH_RENDERER_MATRIX3D_AXIS_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/vector3d.h"
#include "../_layout/quaternion.h"
#include "../_layout/matrix3d.h"

// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc) -- sqrt(double).
extern "C" double __cdecl FUN_004CAC40(double v);
// FUNCTION: GAMEMD 0x4CACB0 (decl; reloc) -- table sin(double).
extern "C" double __cdecl FUN_004CACB0(double angle);
// FUNCTION: GAMEMD 0x4CAD00 (decl; reloc) -- table cos(double).
extern "C" double __cdecl FUN_004CAD00(double angle);

#endif  // GG_MATCH_RENDERER_MATRIX3D_AXIS_METHODS_H
