// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x646480.

#include "matrix3d_axis_methods.h"

// Scale each component; the divisor is taken by value so its last use is the
// third division (retail's `FDIVR` consumes it there).
static inline Vector3 Divide(const Vector3& a, double d)
{
    return Vector3(a.X / d, a.Y / d, a.Z / d);
}

// FUNCTION: GAMEMD 0x646480
//
// Axis/angle to quaternion. The axis is normalised (left alone when its
// length is zero), the angle halved, and the result is the axis scaled by
// sin(half) with cos(half) as the scalar part.
//
// PARTIAL (85.9%, 73/85 by position; multiset identical, 85 vs 85; raw
// bytes 223/266 with one real run at 0xBB..0xD4): everything up to and
// including the sin call, and everything from the `FSTP ST0` before the cos
// call to the end, is byte-exact. The single delta is where the two
// `PUSH EDI; PUSH EBX` for the cos argument sit: retail hoists them to just
// after the first `FLD n.X; FMUL ST1`, ahead of the three product stores
// (which are then addressed as [ESP+0x38/0x3C/0x40]); cl 8804 leaves them
// immediately before `CALL cos` and addresses the stores as
// [ESP+0x30/0x34/0x38]. Variants tried, all giving the same stream: the
// three product statements plus `q.W = cos(half)` (kept); a four-float
// constructor in the return; a Vector3 temporary plus a (Vector3, float)
// constructor (also moves the division temporaries); cos into a double
// local first; the products through an inline helper taking the sine by
// value (the trick that fixed the division block); `s * n.X` operand order
// in a nested scope; and /Ox. Recorded as a suspected 8447-vs-8804 push-
// hoisting difference in the same family as the FromQuaternion store-hoisting
// residual in quaternion_matrix_methods.cpp.
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
Quaternion Matrix3D::FromAxis(const Vector3& axis, float angle)
{
    Vector3 v = axis;
    double len = FUN_004CAC40(v.X * v.X + v.Y * v.Y + v.Z * v.Z);
    Vector3 n;
    if (len != 0.0) {
        n = Divide(v, len);
    } else {
        n = v;
    }

    double half = angle * 0.5f;
    double s = FUN_004CACB0(half);
    Quaternion q;
    q.X = (float)(n.X * s);
    q.Y = (float)(n.Y * s);
    q.Z = (float)(n.Z * s);
    q.W = (float)FUN_004CAD00(half);
    return q;
}
