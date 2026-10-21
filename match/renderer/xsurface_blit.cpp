// SPDX-License-Identifier: GPL-3.0-or-later
// VC6FLAGS: /nologo /c /O2 /DNDEBUG /Gy
// ^ no /GX: paired probe on the XSurface scalar deleting destructor (0x4115A0): with /GX VC6 keeps a
// separate ~XSurface call (0/12), without it the destructor inlines and matches (12/12). The Blit*
// stack locals of 0x7BBB90 also carry no unwind frame in retail.
// Provenance: own-binary-via-Ghidra. XSurface Copy_From family (slots +0x04,
// +0x08, +0x0C). The BlitPlain/BlitTrans objects are stack locals in retail:
// only their vptr is stored (0x7F7BDC/0x7F7BC4 plain, 0x7F7C0C/0x7F7BF4 trans).
#include "surface_class.h"
#include "../render/blitters/blit_plain.h"

#include "../render/blitters/b_trans.h"

// FUNCTION: GAMEMD 0x7BBAF0
bool XSurface::CopyFromWhole(Surface* src, bool a, bool b)
{
    RectangleStruct dest = GetRect();
    dest.X = 0;
    dest.Y = 0;
    RectangleStruct srcRect = src->GetRect();
    srcRect.X = 0;
    srcRect.Y = 0;
    return CopyFromPart(&dest, src, &srcRect, a, b);
}

// FUNCTION: GAMEMD 0x7BBB90
// The fifth argument is not read.
bool XSurface::CopyFromPart(RectangleStruct* dest, Surface* src,
                            RectangleStruct* srcRect, bool a, bool b)
{
    RectangleStruct *srcSurfaceRect = &src->GetRect(), *surfaceRect = &GetRect();
    RectangleStruct d = *dest;
    RectangleStruct s = *srcRect;

    if (!ClipBlitRects(&d, surfaceRect, &s, srcSurfaceRect))
        return false;

    if (a) {
        if (GetBytesPerPixel() == 1) {
            BlitTrans<unsigned char> blitter;
            return BlitDriver(this, &d, src, &s, &blitter, 0, 3, 1000, 0);
        }
        BlitTrans<unsigned short> blitter;
        return BlitDriver(this, &d, src, &s, &blitter, 0, 3, 1000, 0);
    }
    if (GetBytesPerPixel() == 1) {
        BlitPlain<unsigned char> blitter;
        return BlitDriver(this, &d, src, &s, &blitter, 0, 3, 1000, 0);
    }
    BlitPlain<unsigned short> blitter;
    return BlitDriver(this, &d, src, &s, &blitter, 0, 3, 1000, 0);
}

// FUNCTION: GAMEMD 0x7BBCF0
// Arguments 1/4 are the clip rectangles of the destination/source surfaces,
// 2/5 the rectangles to copy; the seventh argument is not read.
bool XSurface::CopyFrom(RectangleStruct* destClip, RectangleStruct* destRect,
                        Surface* src, RectangleStruct* srcClip,
                        RectangleStruct* srcRect, bool a, bool b)
{
    RectangleStruct d = *destRect;
    RectangleStruct s = *srcRect;

    if (!ClipBlitRects(&d, destClip, &s, srcClip))
        return false;

    if (a) {
        if (GetBytesPerPixel() == 1) {
            BlitTrans<unsigned char> blitter;
            return BlitDriver(this, &d, src, &s, &blitter, 0, 3, 1000, 0);
        }
        BlitTrans<unsigned short> blitter;
        return BlitDriver(this, &d, src, &s, &blitter, 0, 3, 1000, 0);
    }
    if (GetBytesPerPixel() == 1) {
        BlitPlain<unsigned char> blitter;
        return BlitDriver(this, &d, src, &s, &blitter, 0, 3, 1000, 0);
    }
    BlitPlain<unsigned short> blitter;
    return BlitDriver(this, &d, src, &s, &blitter, 0, 3, 1000, 0);
}
