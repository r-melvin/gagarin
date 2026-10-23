// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x5AE8F0.

#include "../_layout/matrix3d.h"

// The per-axis translations that Translate expands in place. Retail also has
// standalone TranslateX/Y/Z at 0x5AE980 / 0x5AE9B0 / 0x5AE9E0 (matched in
// match/movement), but Translate does not call them.
static inline void TranslateRowsX(Matrix3D* m, float x)
{
    m->Row[0][3] += x * m->Row[0][0];
    m->Row[1][3] += x * m->Row[1][0];
    m->Row[2][3] += x * m->Row[2][0];
}

static inline void TranslateRowsY(Matrix3D* m, float y)
{
    m->Row[0][3] += y * m->Row[0][1];
    m->Row[1][3] += y * m->Row[1][1];
    m->Row[2][3] += y * m->Row[2][1];
}

static inline void TranslateRowsZ(Matrix3D* m, float z)
{
    m->Row[0][3] += z * m->Row[0][2];
    m->Row[1][3] += z * m->Row[1][2];
    m->Row[2][3] += z * m->Row[2][2];
}

// FUNCTION: GAMEMD 0x5AE8F0
//
// Post-multiplies the affine transform by a translation: the translation column
// Row[i][3] gains vec.X * Row[i][0] + vec.Y * Row[i][1] + vec.Z * Row[i][2].
// Phrased as the three per-axis translations in sequence, which is what the
// retail bytes are: each axis loads its component once, and the running
// Row[i][3] values are kept in two spill slots plus the x87 stack between axes.
void Matrix3D::Translate(const Vector3D& vec)
{
    TranslateRowsX(this, vec.X);
    TranslateRowsY(this, vec.Y);
    TranslateRowsZ(this, vec.Z);
}
