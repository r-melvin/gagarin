// SPDX-License-Identifier: GPL-3.0-or-later
// ^ no /GX: paired probe on the XSurface scalar deleting destructor (0x4115A0): with /GX VC6 keeps a
// separate ~XSurface call (0/12), without it the destructor inlines and matches (12/12). The Blit*
// stack locals of 0x7BBB90 also carry no unwind frame in retail.
// Provenance: own-binary-via-Ghidra. XSurface Copy_From family (slots +0x04, | YRpp-cross-check
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
//
// PARTIAL: the clip test is written as the positive `if (ClipBlitRects(...))`
// with `return false` after it, which is what puts retail's failure epilogue at
// the end and stops the four BlitDriver tails merging (21.5% -> 85.1%, multiset
// identical). Remaining delta: retail keeps the four blitter locals in four
// distinct 4-byte stack slots (frame 0x40) and stores each vptr after the
// argument setup; this build overlaps the sibling-scope locals (frame 0x30), so
// every ESP displacement into the blitter slots differs. Tried: the four
// blitters as function-scope locals (vptr stores hoisted to the top, 23.1%),
// an inline template helper (still overlapped) and address-of temporaries
// (still overlapped).
bool XSurface::CopyFromPart(RectangleStruct* dest, Surface* src,
                            RectangleStruct* srcRect, bool a, bool b)
{
    RectangleStruct *srcSurfaceRect = &src->GetRect(), *surfaceRect = &GetRect();
    RectangleStruct d = *dest;
    RectangleStruct s = *srcRect;

    if (ClipBlitRects(&d, surfaceRect, &s, srcSurfaceRect)) {
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
    return false;
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

// Lock-and-clip helper for a two-surface blit; its body is not part of this file.
bool FUN_007BC040(Surface* destSurface, RectangleStruct* destSurfaceRect,
                   RectangleStruct* destRect, Surface* srcSurface,
                   RectangleStruct* srcSurfaceRect, RectangleStruct* srcRect,
                   bool* overlapped, void** destPixels, void** srcPixels);

// FUNCTION: GAMEMD 0x7BBFF0
// Dead in retail (no callers).
bool FUN_007BBFF0(Surface* destSurface, RectangleStruct* destRect, Surface* srcSurface,
                  RectangleStruct* srcRect, bool* overlapped, void** destPixels,
                  void** srcPixels)
{
    return FUN_007BC040(destSurface, &destSurface->GetRect(), destRect, srcSurface,
                        &srcSurface->GetRect(), srcRect, overlapped, destPixels,
                        srcPixels);
}

// FUNCTION: GAMEMD 0x7BC1F0
// Dead in retail (no callers). Whole-rectangle copy through the plain blitters.
bool FUN_007BC1F0(Surface* dest, RectangleStruct* destRect, Surface* src,
                  RectangleStruct* srcRect)
{
    if (dest->GetBytesPerPixel() == 1) {
        BlitPlain<unsigned char> blitter;
        return BlitDriver(dest, destRect, src, srcRect, &blitter, 0, 3, 1000, 0);
    } else {
        BlitPlain<unsigned short> blitter;
        return BlitDriver(dest, destRect, src, srcRect, &blitter, 0, 3, 1000, 0);
    }
}

// FUNCTION: GAMEMD 0x7BC250
// Dead in retail (no callers). The same copy through the transparent blitters.
bool FUN_007BC250(Surface* dest, RectangleStruct* destRect, Surface* src,
                  RectangleStruct* srcRect)
{
    if (dest->GetBytesPerPixel() == 1) {
        BlitTrans<unsigned char> blitter;
        return BlitDriver(dest, destRect, src, srcRect, &blitter, 0, 3, 1000, 0);
    } else {
        BlitTrans<unsigned short> blitter;
        return BlitDriver(dest, destRect, src, srcRect, &blitter, 0, 3, 1000, 0);
    }
}

