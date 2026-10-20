// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes diffed against retail gamemd.exe v1.001 at 0x5F6360.

#include "abstract_class_distance3d_methods.h"

// FUNCTION: GAMEMD 0x5F6360
//
// Full three-axis lepton distance between this object and another. As in the
// planar twin, a building is measured to its footprint: the foundation's
// height plus width, in cells, comes off and the result is clamped at zero.
//
// PARTIAL (92.9%, 78/84; mnemonic multiset identical). Retail forms the Y
// difference before the Z difference (`SUB EDX,ECX; SUB EAX,EBX` and the two
// spill stores in that order); VC6 schedules Z first. Source order of the
// three differences, the 2D twin's copy-then-decrement form, named locals for
// the other object's coordinates and all six orderings of the sum of squares
// leave it unchanged — a scheduling tie-break, not a phrasing.
//
// FLOAT-CONSISTENCY FLAG (/Op): measured this pass and REFUTED for this
// function. /Op rounds every double-typed intermediate through memory, which
// is the shape retail sometimes shows, but adding it to this TU's flag line
// makes the score collapse rather than close: the five float-heavy partials
// were swept together under `/nologo /c /O2 /DNDEBUG /Gy /GX /Op` and scored
// GetYRotation 58.3%->8.0%, MatrixApply 72.1%->72.1%, FromAxis 85.9%->3.3%,
// FromQuaternion 19.8%->1.1% and DistanceFrom3D 92.9%->67.9%. Retail's x87
// code in this family is *not* /Op code; do not re-test the flag here.
//
// TAIL-MERGE DIAGNOSTIC (eleventh-batch lever): does NOT apply here.
// Retail's callee-saved pushes sit exactly where ours do (prologue EBX, EDI
// plus one sunk push on both sides), the
// number of epilogues agrees, and the compiled block order already matches,
// so there are no merged return blocks to split. The residual is register
// naming downstream of that, not a prologue hoist.
int Obj_005F6360::DistanceFrom3D(Obj_005F6360* that)
{
    if (that == 0) {
        return 0;
    }

    Coord_005F6360 thatBuf;
    Coord_005F6360* thatCoords = (that->*that->Vtbl->GetCoords)(&thatBuf);

    Coord_005F6360 thisBuf;
    Coord_005F6360* thisCoords = (this->*this->Vtbl->GetCoords)(&thisBuf);

    Coord_005F6360 d;
    d.X = thisCoords->X - thatCoords->X;
    d.Y = thisCoords->Y - thatCoords->Y;
    d.Z = thisCoords->Z - thatCoords->Z;

    int distance = (int)FUN_004CAC40((double)d.X * d.X + (double)d.Z * d.Z + (double)d.Y * d.Y);

    Obj_005F6360* building = ((that->*that->Vtbl->WhatAmI)() == 6) ? that : 0;
    if (building != 0) {
        distance += (building->Type->GetFoundationHeight(0)
                     + building->Type->GetFoundationWidth()) * -64;
        if (distance < 0) {
            distance = 0;
        }
    }

    return distance;
}
