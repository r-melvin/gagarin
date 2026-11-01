// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x6BA580.

#include "pcx_blit_surface_methods.h"

// FUNCTION: GAMEMD 0x6BA580
//
// Copy a source surface onto a destination at the rectangle's corner,
// leaving pixels of the transparent colour alone. Both surfaces are locked
// for the duration; a failed lock backs the other one out.
//
// PARTIAL (1.0% by position, 100 instructions against retail's 105). The
// lock pair with its back-out, the geometry reads, the halved stride, the
// row walk and the keyed inner copy with its 16-bit compare (both pixel and
// key are `unsigned short`, or the compare sign-extends through `movsx`)
// are all present and in order. Retail materialises the four zero lock
// arguments into registers before pushing them and keeps a separate
// epilogue per exit, which is five instructions this build does not emit;
// everything after the first of them is shifted, so the position score
// understates the agreement badly. Recorded as the materialised
// push-constant class.
bool __stdcall PCX_BlitToSurface(const Rect_006BA580* area, Surface_006BA580* dst,
                                 Surface_006BA580* src, unsigned short transparent)
{
    unsigned short* target = (unsigned short*)(dst->*dst->Vptr->Lock)(0, 0);
    if (target == 0) {
        return false;
    }

    unsigned short* source = (unsigned short*)(src->*src->Vptr->Lock)(0, 0);
    if (source == 0) {
        (dst->*dst->Vptr->Unlock)();
        return false;
    }

    int x = area->X;
    int y = area->Y;
    int width = (src->*src->Vptr->GetWidth)();
    int height = (src->*src->Vptr->GetHeight)();
    int stride = (dst->*dst->Vptr->GetPitch)() / 2;

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

    (src->*src->Vptr->Unlock)();
    (dst->*dst->Vptr->Unlock)();
    return true;
}
