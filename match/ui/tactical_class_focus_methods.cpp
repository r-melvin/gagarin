// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x6D2420.

#include "tactical_class_focus_methods.h"

// Lepton (x, y) to the un-normalised iso pixel offset, read through a pointer
// to a two-int local — the inlined CoordsToScreen shape of
// match/renderer/tactical_class_coords_to_screen_methods.cpp (the
// address-taken local spills Y into the temporary's second slot and reloads
// it).
static inline Point2D_006D2420 IsoProject(const int* p)
{
    Point2D_006D2420 r;
    r.X = p[0] * 60 / 2;
    r.Y = p[0] * 30 / 2;
    r.X += p[1] * -60 / 2;
    r.Y += p[1] * 30 / 2;
    return r;
}

// Tactical::AdjustForZ (0x6D20E0) inlined: (int)(z * scale + bias + 0.5)
// with bias 1 from a bridge height (728 leptons) up.
static inline int AdjustForZ(int z)
{
    int bias = 0;
    if (z >= 728) {
        bias = 1;
    }
    return (int)(z * DAT_00B0CD48 + bias + 0.5);
}

static inline Point2D_006D2420 CoordsToScreen(const Coord_006D2420* pCoord)
{
    int xy[2];
    xy[0] = pCoord->X;
    xy[1] = pCoord->Y;

    Point2D_006D2420 r = IsoProject(xy);
    r.X /= 256;
    r.Y /= 256;
    r.Y -= AdjustForZ(pCoord->Z);
    return r;
}

// FUNCTION: GAMEMD 0x6D2420
//
// Start a smooth scroll of the tactical view towards a world coordinate.
// The progress counter is reset and the per-frame step taken from the speed
// table; the coordinate is projected to its iso screen point (CoordsToScreen
// and AdjustForZ inlined), taken relative to the view offset and back again,
// and recorded as the target of the move, while the current view position
// is recorded as its start.
//
// Phrasing that matters: the target point is stored as one struct
// assignment (X then Y); per-member stores come out Y first (97.8%).
void Tactical_006D2420::FocusOn(const Coord_006D2420* pCoord, int speed)
{
    this->At_DC = 0;
    this->FocusStep = DAT_008428EC[speed];

    Point2D_006D2420 pt = CoordsToScreen(pCoord);
    pt.X -= this->Offset_B0.X;
    pt.Y -= this->Offset_B0.Y;
    pt.X += this->Offset_B0.X;
    pt.Y += this->Offset_B0.Y;

    this->FocusTarget = pt;
    this->FocusStart.X = this->TacticalPos.X;
    this->FocusStart.Y = this->TacticalPos.Y;
}
