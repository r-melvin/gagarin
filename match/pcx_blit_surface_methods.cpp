// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x6BA580.

#include "pcx_get_surface_methods.h"
#include "wwlib/surface/surface_class.h"

// FUNCTION: GAMEMD 0x6BA580
//
// Copy a source surface onto a destination at the rectangle's corner,
// leaving pixels of the transparent colour alone. Both surfaces are locked
// for the duration; a failed lock backs the other one out. Lock takes its
// origin as a Point2D by value (the zero pair is built in registers).
//
// PARTIAL (25.9%, was 1.0% on a private surface view with a pointer-to-member Lock(0, 0)). Written on the canonical
// Surface / RectangleStruct / PCX: the Point2D argument reproduces the materialised zero pair and the signed pitch halve
// needs an int local. Remaining delta (105 vs 108 instructions): retail copies the rectangle to a 16-byte local whose X/Y
// stay in registers and spills Width/Height, uses a 0x14 frame with the destination in ESI and the source in EDI; this build
// takes an extra callee-saved register (0x18 frame, EBX). Tried: scalar x/y/width/height (kept), whole-rectangle copy with
// x/y locals, whole-rectangle copy with Width/Height written back, copy with direct member use.
bool PCX::FUN_006BA580(const RectangleStruct* area, Surface* dst, Surface* src, unsigned short transparent)
{
    unsigned short* target = (unsigned short*)dst->Lock(Point2D(0, 0));
    if (target == 0) {
        return false;
    }

    unsigned short* source = (unsigned short*)src->Lock(Point2D(0, 0));
    if (source == 0) {
        dst->Unlock();
        return false;
    }

    int x = area->X;
    int y = area->Y;
    int width = src->GetWidth();
    int height = src->GetHeight();
    int pitch = dst->GetPitch();
    int stride = pitch / 2;

    if (height > 0) {
        unsigned short* row = target + (y * stride + x);
        do {
            if (width > 0) {
                unsigned short* from = source;
                unsigned short* to = row;
                int n = width;
                source += width;
                do {
                    if (*from != transparent) {
                        *to = *from;
                    }
                    from++;
                    to++;
                    n--;
                } while (n != 0);
            }
            row += stride;
            height--;
        } while (height != 0);
    }

    src->Unlock();
    dst->Unlock();
    return true;
}
