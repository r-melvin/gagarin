// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x6D2140.
//   LIBRARY: GAMEMD 0x7C5F00  __ftol  (CRT double->long; the (int) cast; reloc)

#include "tactical_class_coords_to_client_methods.h"

// Lepton (x, y) to the un-normalised iso pixel offset, read through a pointer
// to a two-int local — the inlined CoordsToScreen shape of
// match/renderer/tactical_class_coords_to_screen_methods.cpp (the
// address-taken local is what spills Y into the temporary's second slot and
// reloads it).
static inline Point2D_006D2140 IsoProject(const int* p)
{
    Point2D_006D2140 r;
    r.X = p[0] * 60 / 2;
    r.Y = p[0] * 30 / 2;
    r.X += p[1] * -60 / 2;
    r.Y += p[1] * 30 / 2;
    return r;
}

// TacticalClass::AdjustForZ (0x6D20E0) inlined; the bias lands in the dead
// pCoord parameter slot.
static inline int AdjustForZ(int z)
{
    int bias = 0;
    if (z >= 728) {
        bias = 1;
    }
    return (int)(z * DAT_00B0CD48 + bias + 0.5);
}

// TacticalClass::CoordsToScreen (0x6D1F10) inlined.
static inline void CoordsToScreen(Point2D_006D2140* pDest, const Coord_006D2140* pCoord)
{
    int xy[2];
    xy[0] = pCoord->X;
    xy[1] = pCoord->Y;

    Point2D_006D2140 r = IsoProject(xy);
    r.X /= 256;
    r.Y /= 256;
    r.Y -= AdjustForZ(pCoord->Z);

    *pDest = r;
}

// Is the client point within 360 x 180 pixels of the view rectangle. Takes
// the two scalars so the compares run on volatile register copies after the
// callee-saved pops (`MOV ECX,EDI; MOV EAX,ESI; POP; POP; POP; CMP`); each
// false exit is its own `XOR AL,AL; ADD ESP,8; RET 8` and the last test is
// a named bool so it ends in a bare `SETLE AL`.
static inline bool InView(int x, int y)
{
    if (x < -360) {
        return false;
    }
    if (x > DAT_00B0CE30 + 360) {
        return false;
    }
    if (y < -180) {
        return false;
    }
    bool inside = y <= DAT_00B0CE34 + 180;
    return inside;
}

// FUNCTION: GAMEMD 0x6D2140
//
// World coordinate to a client (view-relative) point: the raw iso screen
// point is stored to pDest, the view offset (read first as one Point2D into
// ECX/EBP) is subtracted from it in place with a reload through pDest, and
// the result says whether the point lies within 360 pixels horizontally and
// 180 pixels vertically of the view rectangle. The per-axis copy right after
// each in-place store is what interleaves `MOV [EAX],EDI; MOV ECX,EDI;
// MOV [EAX+4],ESI; MOV EAX,ESI`; a struct copy or a by-value helper argument
// puts both stores before both copies (98.1%), and testing pDest's fields
// directly keeps the pops inside the branches (63.2%).
bool Tactical_006D2140::CoordsToClient(const Coord_006D2140* pCoord, Point2D_006D2140* pDest)
{
    CoordsToScreen(pDest, pCoord);

    Point2D_006D2140 off = this->Offset_B0;
    pDest->X -= off.X;
    int x = pDest->X;
    pDest->Y -= off.Y;
    int y = pDest->Y;

    return InView(x, y);
}
