// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x6D1F10.

#include "tactical_class_coords_to_screen_methods.h"

// Lepton (x, y) to the un-normalised iso pixel offset, read through a pointer
// to a two-int local. This is the pClient shape of the sibling
// TacticalClass::AdjustForZShapeMove (match/renderer/tactical_class_matrix_
// methods.cpp) and it is what retail inlined here: the address-taken local
// makes VC6 store Y into the temporary's second slot and reload it
// (`MOV [ESP+0x10],EAX; MOV EDI,[ESP+0x10]`), while X is forwarded straight
// into ESI. With plain int arguments, or with a struct passed by value or
// reference, that spill and reload vanish and the Z load and the bias store
// move ahead of the first LEA (9.7%). The struct returned by value is what
// produces the dead X spill into the temporary's first slot, which Z later
// reuses for its FILD.
static inline Point2D_006D1F10 IsoProject(const int* p)
{
    Point2D_006D1F10 r;
    r.X = p[0] * 60 / 2;
    r.Y = p[0] * 30 / 2;
    r.X += p[1] * -60 / 2;
    r.Y += p[1] * 30 / 2;
    return r;
}

// Height in leptons to the rounded pixel lift, (int)(z * scale + bias + 0.5)
// with bias 1 once the height reaches a bridge level (728 leptons). This is
// TacticalClass::AdjustForZ (0x6D20E0, match/ui/tactical_class_methods.cpp)
// inlined; the bias lands in the dead pCoord parameter slot.
static inline int AdjustForZ(int z)
{
    int bias = 0;
    if (z >= 728) {
        bias = 1;
    }
    return (int)(z * DAT_00B0CD48 + bias + 0.5);
}

// FUNCTION: GAMEMD 0x6D1F10
//
// World coordinate to the raw iso screen point: the (x, y) leptons go through
// the 60x30 projection and a signed divide by 256, then the height lift is
// subtracted from Y. Z is read off pCoord only when the lift is computed, which
// keeps pCoord in EBX across the projection and lets Z take over EBX after it.
// The result is stored to pDest as one Point2D and pDest comes back in EAX.
Point2D_006D1F10* Tactical_006D1F10::CoordsToScreen(Point2D_006D1F10* pDest,
                                                     const Coord_006D1F10* pCoord)
{
    int xy[2];
    xy[0] = pCoord->X;
    xy[1] = pCoord->Y;

    Point2D_006D1F10 r = IsoProject(xy);
    r.X /= 256;
    r.Y /= 256;
    r.Y -= AdjustForZ(pCoord->Z);

    *pDest = r;
    return pDest;
}
