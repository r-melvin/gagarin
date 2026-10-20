// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x646980.

#include "matrix3d_quaternion_methods.h"

// FUNCTION: GAMEMD 0x646980
//
// Build the rotation matrix of a unit quaternion. The nine rotation terms are
// the textbook products; the fourth column is zero. The result is a local the
// caller's hidden pointer receives through REP MOVSD.
//
// PARTIAL (19.8%, 16/81 by position; multiset identical, 81 vs 81): the
// whole x87 stream — every product, spill slot, doubling, `FSUBR 1.0f` and
// store — is emitted in retail's order; the only delta is where the three
// fourth-column `MOV dword ptr [ESP+0x24/0x34/0x44],0` stores sit. Retail
// schedules them late, interleaved with the `MOV ECX,0xC; LEA ESI,[ESP+
// 0x18]; MOV EDI,EAX` copy setup between the m21 `FADD ST0,ST1` and its
// `FADD ST0,ST0` (in the order 0x44, 0x34, 0x24); cl 8804 hoists the three
// constant stores to the block entry (offset 0x15) whatever their source
// position and leaves the copy setup at the end, so every instruction in
// between is reported one slot off. Variants tried, all giving the same
// stream: the zeros as three statements first, last (forward and reverse
// order) and between m20/m21 and m21/m22; a chained assignment at the end;
// int-aliased stores; a pointer walk over the column; a 12-element zero
// loop ahead of the terms (changes the prologue). Recorded as a suspected
// 8447-vs-8804 store-hoisting difference (same family as the LEA-above-
// immediate-store note in the methodology).
//
// FLOAT-CONSISTENCY FLAG (/Op): measured this pass and REFUTED for this
// function. /Op rounds every double-typed intermediate through memory, which
// is the shape retail sometimes shows, but adding it to this TU's flag line
// makes the score collapse rather than close: the five float-heavy partials
// were swept together under `/nologo /c /O2 /DNDEBUG /Gy /GX /Op` and scored
// GetYRotation 58.3%->8.0%, MatrixApply 72.1%->72.1%, FromAxis 85.9%->3.3%,
// FromQuaternion 19.8%->1.1% and DistanceFrom3D 92.9%->67.9%. Retail's x87
// code in this family is *not* /Op code; do not re-test the flag here.
Matrix3D __fastcall Matrix3D::FromQuaternion(const Quaternion& q)
{
    Matrix3D m;

    m.Row[0][0] = 1.0f - 2.0f * (q.Y * q.Y + q.Z * q.Z);
    m.Row[0][1] = 2.0f * (q.X * q.Y - q.W * q.Z);
    m.Row[0][2] = 2.0f * (q.X * q.Z + q.W * q.Y);

    m.Row[1][0] = 2.0f * (q.X * q.Y + q.W * q.Z);
    m.Row[1][1] = 1.0f - 2.0f * (q.X * q.X + q.Z * q.Z);
    m.Row[1][2] = 2.0f * (q.Y * q.Z - q.W * q.X);

    m.Row[2][0] = 2.0f * (q.X * q.Z - q.W * q.Y);
    m.Row[2][1] = 2.0f * (q.Y * q.Z + q.W * q.X);
    m.Row[2][2] = 1.0f - 2.0f * (q.X * q.X + q.Y * q.Y);

    // The chained form stores [2][3], [1][3], [0][3] in that order — retail's
    // relative order for the three zero stores.
    m.Row[0][3] = m.Row[1][3] = m.Row[2][3] = 0.0f;

    return m;
}
