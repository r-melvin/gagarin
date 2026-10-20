// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm at
//   0x5AF410-0x5AF46C). Names cross-checked against YRpp Matrix3D.h
//   (consult-only; every offset/signature reconfirmed numerically here).
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
// Phrasing note: our compiler is a stronger optimiser than retail's
// 8447 and would copy-propagate/DSE the `return ret` struct copy away entirely
// (reading the MatrixApply result straight into the atan2 args). Capturing the
// MatrixApply return pointer (an opaque extern result => EAX-relative reads,
// matching retail) plus a `volatile` destination is what forces our compiler to retain
// the copy. The ONLY residual vs retail is the placement of the two arg-reserve
// `sub esp,8` instructions: `volatile` orders the copy stores ahead of the
// float marshalling, whereas 8447 wove the reserves into the copy. That is a
// pure unexplained-codegen scheduling delta (the prologue, EAX-relative copy, x87
// float promotion, the atan2 call and the epilogue all match exactly).
//
// FLOAT-CONSISTENCY FLAG (/Op): measured this pass and REFUTED for this
// function. /Op rounds every double-typed intermediate through memory, which
// is the shape retail sometimes shows, but adding it to this TU's flag line
// makes the score collapse rather than close: the five float-heavy partials
// were swept together under `/nologo /c /O2 /DNDEBUG /Gy /GX /Op` and scored
// GetYRotation 58.3%->8.0%, MatrixApply 72.1%->72.1%, FromAxis 85.9%->3.3%,
// FromQuaternion 19.8%->1.1% and DistanceFrom3D 92.9%->67.9%. Retail's x87
// code in this family is *not* /Op code; do not re-test the flag here.
double Matrix3D::GetYRotation() const
{
    Vector3D axis(0.0f, 0.0f, 1.0f);
    Vector3D tmp;
    Vector3D* p = MatrixApply(&tmp, this, &axis);
    volatile Vector3D res;
    res.X = p->X;
    res.Y = p->Y;
    res.Z = p->Z;
    return atan2(res.X, res.Z);
}
