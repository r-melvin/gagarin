// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Shapes read off retail gamemd.exe v1.001 at 0x646480..0x646A75: every
//   function is __fastcall with the hidden result pointer in ECX and the first
//   reference argument in EDX. Quaternion is four floats {X, Y, Z, W}
//   (0x646730 / 0x646590 seed a local at +0/+4/+8/+0xC with 0,0,0,1.0f and
//   copy it out with four dword moves); Matrix3D is the 3x4 row-major float
//   block (0x646730 reads +0x00/+0x14/+0x28 as its diagonal).
#ifndef GG_MATCH_RENDERER_QUATERNION_MATRIX_METHODS_H
#define GG_MATCH_RENDERER_QUATERNION_MATRIX_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/vector3d.h"
#include "../_layout/quaternion.h"
#include "../_layout/matrix3d.h"

// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc) -- sqrt(double).
extern "C" double __cdecl FUN_004CAC40(double v);
// FUNCTION: GAMEMD 0x4CACB0 (decl; reloc) -- sin(double).
extern "C" double __cdecl FUN_004CACB0(double angle);
// FUNCTION: GAMEMD 0x4CAD00 (decl; reloc) -- cos(double).
extern "C" double __cdecl FUN_004CAD00(double angle);
// FUNCTION: GAMEMD 0x4CADB0 (decl; reloc) -- acos(double).
extern "C" double __cdecl FUN_004CADB0(double v);
// FUNCTION: GAMEMD 0x4CAE30 (decl; reloc) -- atan2(double y, double x).
extern "C" double __cdecl FUN_004CAE30(double y, double x);

Quaternion FUN_00646590(const Quaternion& a, const Quaternion& b, float t);
Quaternion FUN_00646730(const Matrix3D& m);

#endif
