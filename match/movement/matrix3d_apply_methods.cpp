// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x5AFB80.

#include "matrix3d_apply_methods.h"

// x87 TERM ORDER IS NOT SOURCE-CONTROLLED. Retail evaluates rows 1 and 2 as
// (m0*X + m2*Z) + m1*Y and row 0 as (m2*Z + m1*Y) + m0*X - three orders that
// look like they came from the source. They did not: writing the rows in
// retail's apparent order gives byte-for-byte the same output as the
// conventional X,Y,Z order, byte-identical either way. VC6 schedules the FPU
// stack itself, and row 0 differs only because its first FLD is hoisted above
// the ESI load. The
// conventional order is kept for readability.
// FUNCTION: GAMEMD 0x5AFB80  Matrix3D::MatrixApply (__fastcall)
// Transform a point by the full 3x4 matrix — rotation times the vector plus the
// translation column — writing through a stack temporary so the destination may
// alias the source.
//
// PARTIAL 72.1% (31/43 instructions; the 81.4% recorded here earlier was a
// stale reading — re-measured against the current harness this pass). All nine multiplies, all six adds, the
// three translation adds, the temporary's slots and the struct copy out are
// exact. The residual is x87 scheduling: retail places `MOV EAX,ECX` three
// instructions later, and picks a different multiply order within rows 1 and 2
// than within row 0 (row 0 takes Z first, rows 1 and 2 take X first).
//
// Rewriting the source in retail's per-row order changes nothing — VC6
// canonicalises the operand order itself — so this is the allocation/scheduling
// class rather than the §4.8 redundancy wall. Four shapes measured: `float[3]`
// temp (39.5%), three separate floats (11.6%, and raw byte diffs), reordered
// terms (39.5%), and the struct temp with a struct copy out (kept, and still
// the best measured form at 72.1%).
//
// FLOAT-CONSISTENCY FLAG (/Op): measured this pass and REFUTED for this
// function. /Op rounds every double-typed intermediate through memory, which
// is the shape retail sometimes shows, but adding it to this TU's flag line
// makes the score collapse rather than close: the five float-heavy partials
// were swept together under `/nologo /c /O2 /DNDEBUG /Gy /GX /Op` and scored
// GetYRotation 58.3%->8.0%, MatrixApply 72.1%->72.1%, FromAxis 85.9%->3.3%,
// FromQuaternion 19.8%->1.1% and DistanceFrom3D 92.9%->67.9%. Retail's x87
// code in this family is *not* /Op code; do not re-test the flag here.
Vector3D* __fastcall Matrix3D_MatrixApply(Vector3D* out, Matrix3DRows* matrix,
                                          Vector3D* vector)
{
    Vector3D result;

    result.X = matrix->Row[0][0] * vector->X + matrix->Row[0][1] * vector->Y
             + matrix->Row[0][2] * vector->Z + matrix->Row[0][3];
    result.Y = matrix->Row[1][0] * vector->X + matrix->Row[1][1] * vector->Y
             + matrix->Row[1][2] * vector->Z + matrix->Row[1][3];
    result.Z = matrix->Row[2][0] * vector->X + matrix->Row[2][1] * vector->Y
             + matrix->Row[2][2] * vector->Z + matrix->Row[2][3];

    *out = result;
    return out;
}
