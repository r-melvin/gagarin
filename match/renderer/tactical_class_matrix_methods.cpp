// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x6D1FE0 and 0x6D2070.
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x6D1FE0  TacticalClass::AdjustForZShapeMove (__thiscall)
//   FUNCTION: GAMEMD 0x6D2070  TacticalClass::ApplyMatrix_Pixel   (__thiscall)
//   FUNCTION: GAMEMD 0x5AFB80  Matrix3D::MatrixApply (referenced; reloc)
//   LIBRARY:  GAMEMD 0x7C5F00  __ftol                (referenced; reloc)

#include "tactical_class_matrix_methods.h"

// Lepton-space (x, y) to the un-normalised iso pixel offset: a 60x30 cell,
// phrased as the retail halves of the cell size, x-terms first then y-terms.
// This has to be a separate inline returning by value: the temporary VC6
// materialises for the returned struct is what gives retail its 8-byte frame
// and the dead spill of X (`MOV [ESP+8],ECX`) — the same computation written
// straight into the caller's local, or into the destination, drops both.
// `-60` must be a literal multiply: VC6 expands it as `SHL 4; SUB; NEG; SHL 2`
// and only folds it into a subtraction when the sum is in the same expression.
static inline Point2D IsoProject(int x, int y)
{
    Point2D r;
    r.X = x * 60 / 2;
    r.Y = x * 30 / 2;
    r.X += y * -60 / 2;
    r.Y += y * 30 / 2;
    return r;
}

// FUNCTION: GAMEMD 0x6D1FE0
//
// Pixel offset of a lepton-space (x, y): X = (x - y) * 30 / 256 and
// Y = (x + y) * 15 / 256, via the half-cell products above and a signed
// divide by the 256 leptons per cell. `this` is unused; the result is
// written to pDest as one Point2D and pDest is returned. x and y are read
// into named locals first so x claims ESI ahead of y (VC6 evaluates the
// inline's arguments right-to-left otherwise, which swaps ESI/EDI).
int* TacticalClass::AdjustForZShapeMove(int* pDest, const int* pClient)
{
    int x = pClient[0];
    int y = pClient[1];

    Point2D r = IsoProject(x, y);
    r.X /= 256;
    r.Y /= 256;

    *(Point2D*)pDest = r;
    return pDest;
}

// FUNCTION: GAMEMD 0x6D2070
//
// Runs an integer 2-D pixel offset through the iso transform matrix at +0xDE4
// (Z is taken as 0) and truncates the transformed X/Y back to ints in pOut.
// The helper's result is copied back into the input vector (the 3-dword copy
// off the returned pointer), both `__ftol` conversions are done into a
// Point2D, and that is stored to pOut as one struct so both stores follow
// the second conversion.
int* TacticalClass::ApplyMatrix_Pixel(int* pOut, const int* pIn)
{
    Vector3D v;
    Vector3D r;

    v.X = (float)pIn[0];
    v.Z = 0.0f;
    v.Y = (float)pIn[1];

    v = *Matrix3D::MatrixApply(&r, &this->IsoTransformMatrix, &v);

    Point2D pt;
    pt.X = (int)v.X;
    pt.Y = (int)v.Y;
    *(Point2D*)pOut = pt;
    return pOut;
}
