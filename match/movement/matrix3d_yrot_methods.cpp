// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm at
//   0x5AF410-0x5AF46C). Names cross-checked against YRpp
//   (every offset/signature reconfirmed numerically here).
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x5AF410  Matrix3D::GetYRotation (__thiscall)

#include "matrix3d_yrot_methods.h"

#include <math.h>

// Retail calls the CRT atan2 (0x4CAE30), not the x87 fpatan intrinsic; disable
// the intrinsic so cl emits a (reloc-normalised) call.
#pragma function(atan2)

// FUNCTION: GAMEMD 0x5AF410  (__thiscall)
// Transform the unit +Z axis (0,0,1) by this matrix, then return the heading
// angle about the local Y axis as atan2(result.X, result.Z). This mirrors the
// inlined operator*(Vector3D): { Vector3D ret; MatrixApply(&ret,this,&pt);
// return ret; }. Retail builds the {0,0,1} input on the stack, calls MatrixApply
// (0x5AFB80) into a temp, copies all three result components (the non-elided
// `return ret`), and tail-passes X then Z (promoted to double) to atan2
// (0x4CAE30), leaving the angle in ST0.
//
// MATCHED 100% (24/24 by diff_retail; raw bytes exact apart from the two
// relocated calls) with the plain copy `Vector3D res = *MatrixApply(...)`.
//
// FLOAT-CONSISTENCY FLAG (/Op): measured this pass and REFUTED for this
// function. /Op rounds every double-typed intermediate through memory, which
// is the shape retail sometimes shows, but adding it to this TU's flag line
// makes the score collapse rather than close: the five float-heavy partials
// were swept together under `/nologo /c /O2 /DNDEBUG /Gy /GX /Op` (the flags
// then in force, before /Gr and the removal of /GX) and scored
// GetYRotation 58.3%->8.0%, MatrixApply 72.1%->72.1%, FromAxis 85.9%->3.3%,
// FromQuaternion 19.8%->1.1% and DistanceFrom3D 92.9%->67.9%. Retail's x87
// code in this family is *not* /Op code; do not re-test the flag here.
double Matrix3D::GetYRotation() const
{
    Vector3D axis(0.0f, 0.0f, 1.0f);
    Vector3D tmp;
    Vector3D res = *MatrixApply(&tmp, this, &axis);
    return atan2(res.X, res.Z);
}
