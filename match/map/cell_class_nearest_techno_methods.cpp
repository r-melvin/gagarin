// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x47C3D0.

#include "cell_class_nearest_techno_methods.h"

// FUNCTION: GAMEMD 0x47C3D0
//
// Nearest techno in this cell's occupier list (ground or bridge) to a pixel
// offset inside the cell, skipping one object. The offset is scaled by seven
// up front; each candidate's sub-cell lepton position (low byte of X and Y)
// is measured against it in double precision and truncated.
//
// Four phrasings are load-bearing. The head pointer is a separate variable
// from the loop cursor and the null test on the cursor sits inside the loop
// (retail re-tests it and jumps to the increment); the techno flag is a
// function-scope bool assigned in its own block and tested in the next, which
// is what stores it to the frame; a single `return best` after the guarded
// loop lets the null path return the zero register; and the X/Y difference is
// a 12-byte CoordStruct whose Z is never written, which gives the FILD slots
// their own 12 bytes and pushes the hidden-return temporary up to 0x28.
Obj_0047C3D0* Cell_0047C3D0::FindTechnoNearestTo(Point_0047C3D0* offset,
                                                 bool alt,
                                                 Obj_0047C3D0* exclude)
{
    Obj_0047C3D0* best = 0;
    int bestDist = 0;
    int x = offset->X * 7;
    int y = offset->Y * 7;
    bool techno;

    Obj_0047C3D0* head = alt ? AltObject : FirstObject;
    if (head != 0) {
        Obj_0047C3D0* obj = head;
        do {
            techno = false;
            if (obj != 0) {
                techno = (obj->AbstractFlags & 1) != 0;
            }
            if (techno && obj != exclude) {
                Coord_0047C3D0 c = (obj->*obj->Vptr->GetCoords)();
                Coord_0047C3D0 d;
                d.X = (c.X & 0xFF) - x;
                d.Y = (c.Y & 0xFF) - y;
                int dist = (int)FUN_004CAC40((double)d.X * d.X + (double)d.Y * d.Y);
                if (best == 0 || dist < bestDist) {
                    best = obj;
                    bestDist = dist;
                }
            }
            obj = obj->NextObject;
        } while (obj != 0);
    }
    return best;
}
