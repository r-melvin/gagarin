// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x5F6440.

#include "abstract_class_distance_methods.h"

// FUNCTION: GAMEMD 0x5F6440
//
// Planar (X/Y) lepton distance between this object and another. When the other
// object is a building the distance is measured to its footprint rather than
// its centre: the foundation's height plus width, in cells, is taken off and
// the result clamped at zero.
//
// Two phrasings are load-bearing. The difference is an 8-byte aggregate that is
// first *copied* from this object's coordinate and then decremented member by
// member (`d.X = c->X; d.Y = c->Y; d.X -= tx; d.Y -= ty;`): written as two
// subtractions (`d.X = c->X - tx;`) VC6 reads Y before X into EDX and copies the
// __ftol result into EBX eagerly, where retail reads X into ECX, Y into the dying
// pointer register EAX, and only parks EAX in EBX after loading the WhatAmI
// vtable. The foundation sum stays inside the multiply; naming the two calls
// moves the accumulator from EDI to EAX.
int Obj_005F6440::DistanceFrom(Obj_005F6440* that)
{
    if (that == 0) {
        return 0;
    }

    Coord_005F6440 thatBuf;
    Coord_005F6440* thatCoords = (that->*that->Vtbl->GetCoords)(&thatBuf);
    int thatX = thatCoords->X;
    int thatY = thatCoords->Y;

    Coord_005F6440 thisBuf;
    Coord_005F6440* thisCoords = (this->*this->Vtbl->GetCoords)(&thisBuf);

    Point_005F6440 d;
    d.X = thisCoords->X;
    d.Y = thisCoords->Y;
    d.X -= thatX;
    d.Y -= thatY;

    int distance = (int)FUN_004CAC40((double)d.Y * d.Y + (double)d.X * d.X);

    // A building, or null: retail folds the type test into the pointer
    // (`SUB ESI,6; NEG; SBB; NOT; AND ESI,EDI`) rather than branching.
    Obj_005F6440* building = ((that->*that->Vtbl->WhatAmI)() == 6) ? that : 0;
    if (building != 0) {
        distance += (building->Type->GetFoundationHeight(0)
                     + building->Type->GetFoundationWidth()) * -64;
        if (distance < 0) {
            distance = 0;
        }
    }

    return distance;
}
