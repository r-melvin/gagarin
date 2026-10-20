// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x5AE8F0.

#include "matrix3d_translate_methods.h"

// FUNCTION: GAMEMD 0x5AE8F0
//
// Post-multiplies the affine transform by a translation: the translation column
// Row[i][3] gains vec.X * Row[i][0] + vec.Y * Row[i][1] + vec.Z * Row[i][2].
// Phrased as the three per-axis translations in sequence, which is what the
// retail bytes are: each axis loads its component once, and the running
// Row[i][3] values are kept in two spill slots plus the x87 stack between axes.
void Matrix3D::Translate(const Vector3D& vec)
{
    this->TranslateX(vec.X);
    this->TranslateY(vec.Y);
    this->TranslateZ(vec.Z);
}
