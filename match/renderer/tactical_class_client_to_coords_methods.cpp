// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x6D2280.
//   FUNCTION: GAMEMD 0x5AFB80  Matrix3D::MatrixApply (referenced; reloc)
//   LIBRARY:  GAMEMD 0x7C5F00  __ftol                (referenced; reloc)

#include "tactical_class_client_to_coords_methods.h"

// FUNCTION: GAMEMD 0x6D2280
//
// Client (screen) point to a world coordinate — the inverse of
// TacticalClass::CoordsToScreen. A point outside the view's X/Y extents gets
// the "no coordinate" global. Otherwise the point is shifted by the view
// offset, run through the iso transform matrix at +0xDE4 as a float vector
// (Z taken as 0), and the transformed X/Y are truncated back to ints; Z of
// the result is 0.
//
// Phrasing (each piece load-bearing, 65.6% -> 100%): the shifted point is a
// Point2D local in its own block, so its two int slots are written before
// the first FILD and are then reused by the apply helper's result vector in
// the next block (retail's 0x18-byte frame: r low, v high); the view offset
// is read as one Point2D (`MOV EAX,[ECX+0xB0]; MOV EDX,[ECX+0xB4]` back to
// back), which is also what puts the client X/Y in EDI/ESI and the limits in
// EDX — member-wise reads of the offset give the caller-saved allocation. The
// Y limit is written `DAT_00B0CE34 + DAT_00B0CE2C` so the +0x34 global is
// loaded first. The helper's result is copied back into the input vector (the
// 3-dword copy off the returned pointer) exactly as in
// TacticalClass::ApplyMatrix_Pixel, and the result is stored to pDest as one
// struct so all three stores follow the second conversion.
Coord_006D2280* Tactical_006D2280::ClientToCoords(Coord_006D2280* pDest,
                                                  const Point2D_006D2280* pClient)
{
    if (pClient->X < DAT_00B0CE30 && pClient->Y < DAT_00B0CE34 + DAT_00B0CE2C) {
        Vector3D_006D2280 v;
        {
            Point2D_006D2280 pt;
            Point2D_006D2280 off = this->Offset_B0;
            pt.X = pClient->X + off.X;
            pt.Y = pClient->Y + off.Y;
            v.X = (float)pt.X;
            v.Y = (float)pt.Y;
            v.Z = 0.0f;
        }
        {
            Vector3D_006D2280 r;
            v = *Matrix3D_006D2280::MatrixApply(&r, &this->IsoTransformMatrix, &v);
        }

        Coord_006D2280 c;
        c.X = (int)v.X;
        c.Y = (int)v.Y;
        c.Z = 0;
        *pDest = c;
        return pDest;
    }

    *pDest = DAT_00B0CE08;
    return pDest;
}
