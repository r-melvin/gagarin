// SPDX-License-Identifier: GPL-3.0-or-later
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT
// Frozen milestone flag set: /O2 /DNDEBUG /Gy without /GX.
// Provenance: own-binary-via-Ghidra. DSurface::CopyFrom (slot +0x0C, RTTI .?AVDSurface@@, vtable | YRpp-cross-check
// 0x7E85D4): the DirectDraw hardware blit with both clip rectangles. Retail inlines two copies of the
// rectangle intersection (the out-of-line body is 0x421B60) and one blit-rectangle clip call (0x7BBE20).
#include "dsurface_class.h"

// The inline form of 0x421B60: `b` clipped to `a`, an all-zero rectangle when nothing is left. The adjustment
// pointers of the out-of-line form are null at the two inlined uses and left out.
static inline RectangleStruct Intersect(const RectangleStruct* a, const RectangleStruct* b)
{
    RectangleStruct r = {0, 0, 0, 0};
    if (a->Width <= 0 || a->Height <= 0 || b->Width <= 0 || b->Height <= 0)
        return r;
    RectangleStruct t = *b;
    if (t.X < a->X) {
        t.Width += t.X - a->X;
        t.X = a->X;
    }
    if (t.Width < 1)
        return r;
    if (t.Y < a->Y) {
        t.Height += t.Y - a->Y;
        t.Y = a->Y;
    }
    if (t.Height < 1)
        return r;
    if (t.X + t.Width > a->X + a->Width)
        t.Width = a->X - t.X + a->Width;
    if (t.Width < 1)
        return r;
    if (t.Y + t.Height > a->Y + a->Height)
        t.Height = a->Y + a->Height - t.Y;
    if (t.Height < 1)
        return r;
    r = t;
    return r;
}

// FUNCTION: GAMEMD 0x4BB0D0
bool DSurface::CopyFrom(RectangleStruct* destClip, RectangleStruct* destRect, Surface* src,
                        RectangleStruct* srcClip, RectangleStruct* srcRect, bool a, bool b)
{
    if (destClip->Width <= 0 || destClip->Height <= 0)
        return false;
    if (srcClip->Width <= 0 || srcClip->Height <= 0)
        return false;
    if (destRect->Width <= 0 || destRect->Height <= 0)
        return false;
    if (srcRect->Width <= 0 || srcRect->Height <= 0)
        return false;

    DSurface* source = (DSurface*)src;
    bool useSoftware = false;
    if (!source->unknown_84() || source->IsLocked() == true || a == true || GetBytesPerPixel() != source->GetBytesPerPixel())
        useSoftware = true;

    bool direct = (IsPrimary == true && DAT_0089F978 == true) ? false : b;
    if (!useSoftware && direct == true) {
        if (!InVideoMemory || (source->unknown_84() == true && !source->InVideoMemory)) {
            if (srcRect->Width == destRect->Width && srcRect->Height == destRect->Height)
                useSoftware = true;
        }
    }

    if (!DAT_0089F978 && !DAT_00A8ED80)
        return false;
    if (!Recover())
        return false;
    if (useSoftware)
        return XSurface::CopyFromPart(destRect, src, srcRect, a, true);

    RectangleStruct dest = *destRect;
    RectangleStruct from = *srcRect;
    RectangleStruct srcVisible = Intersect(srcClip, &src->GetRect());
    RectangleStruct destVisible = Intersect(destClip, &GetRect());
    if (!ClipBlitRects(&dest, &destVisible, &from, &srcVisible))
        return false;

    DDRect destBounds;
    destBounds.left = destVisible.X + dest.X;
    destBounds.top = destVisible.Y + dest.Y;
    destBounds.right = destVisible.X + dest.X + dest.Width;
    destBounds.bottom = destVisible.Y + dest.Y + dest.Height;
    DDRect srcBounds;
    srcBounds.left = srcVisible.X + from.X;
    srcBounds.top = srcVisible.Y + from.Y;
    srcBounds.right = srcVisible.X + from.X + from.Width;
    srcBounds.bottom = srcVisible.Y + from.Y + from.Height;
    return DDSurf->lpVtbl->Blt(DDSurf, &destBounds, source->DDSurf, &srcBounds, 0x1000000, 0) == 0;
}
