// SPDX-License-Identifier: GPL-3.0-or-later
// ^ no /GX: paired probe on the XSurface scalar deleting destructor (0x4115A0): with /GX VC6 keeps a
// separate ~XSurface call (0/12), without it the destructor inlines and matches (12/12). The Blit*
// stack locals of 0x7BBB90 also carry no unwind frame in retail.
// Provenance: own-binary-via-Ghidra. XSurface::DrawEllipse (slot +0x20), a | YRpp-cross-check
// midpoint ellipse outline for 16-bit surfaces. It writes through raw
// unsigned short pointers (the surface must already be 16 bits per pixel) except
// for the four axis extremes, which go through PutPixel (slot +0x24).
#include "surface_class.h"

#define ELLIPSE_IN(px, py) \
    ((px) >= clip.X && (px) < clip.Width + clip.X && (py) >= clip.Y && (py) < clip.Height + clip.Y)

// FUNCTION: GAMEMD 0x7BB350
// PARTIAL (second look, 5.4% positional, 483 retail vs 455 compiled instructions). Row words are the
// signed `(int)GetPitch() >> 1` (SAR, not SHR) and `2*rx2`/`2*ry2` are named locals. Remaining delta:
// retail spills far more of the loop state to the stack ([ESP+0x10..0x58]) and rebuilds the four row
// pointers with LEA; not reproduced.
bool XSurface::DrawEllipse(int cx, int cy, int rx, int ry, RectangleStruct clip,
                           unsigned int color)
{
    int rowWords = (int)GetPitch() >> 1;
    Point2D pt;

    int below = cy + ry;
    if (ELLIPSE_IN(cx, below)) {
        pt.X = cx;
        pt.Y = below;
        PutPixel(&pt, color);
    }
    int above = cy - ry;
    if (ELLIPSE_IN(cx, above)) {
        pt.X = cx;
        pt.Y = above;
        PutPixel(&pt, color);
    }

    int rx2 = rx * rx;
    int ry2 = ry * ry;
    int rx22 = 2 * rx2;
    int ry22 = 2 * ry2;
    int bound = 2 * rx2 * ry;
    int term = 0;
    int y = ry;
    int d = rx2 / 4 - rx2 * ry;
    int xl = cx;
    int xr = cx;

    Point2D origin;
    origin.X = 0;
    origin.Y = 0;
    unsigned short* base = (unsigned short*)Lock(origin);
    unsigned short* pBelowRight = base + (cy + ry) * rowWords + cx;
    unsigned short* pAboveLeft = base + (cy - ry) * rowWords + cx;
    unsigned short* pAboveRight = pAboveLeft;
    unsigned short* pBelowLeft = pBelowRight;

    for (;;) {
        d += term + ry2;
        if (d >= 0) {
            bound -= rx22;
            d -= bound;
            y--;
            pBelowRight -= rowWords;
            pAboveLeft += rowWords;
            pAboveRight += rowWords;
            pBelowLeft -= rowWords;
        }
        term += ry22;
        xr++;
        xl--;
        pBelowRight++;
        pAboveLeft--;
        pAboveRight++;
        pBelowLeft--;
        if (term >= bound)
            break;
        int lower = cy + y;
        int upper = cy - y;
        if (ELLIPSE_IN(xr, lower))
            *pBelowRight = (unsigned short)color;
        if (ELLIPSE_IN(xl, upper))
            *pAboveLeft = (unsigned short)color;
        if (ELLIPSE_IN(xr, upper))
            *pAboveRight = (unsigned short)color;
        if (ELLIPSE_IN(xl, lower))
            *pBelowLeft = (unsigned short)color;
    }

    xr = cx + rx;
    if (ELLIPSE_IN(xr, cy)) {
        pt.X = xr;
        pt.Y = cy;
        PutPixel(&pt, color);
    }
    xl = cx - rx;
    if (ELLIPSE_IN(xl, cy)) {
        pt.X = xl;
        pt.Y = cy;
        PutPixel(&pt, color);
    }

    int j = 0;
    term = 0;
    bound = 2 * ry2 * rx;
    d = ry2 / 4 - ry2 * rx;
    unsigned short* rowRight = base + cy * rowWords + cx + rx;
    unsigned short* rowLeft = base + cy * rowWords + cx - rx;
    pBelowRight = rowRight;
    pAboveRight = rowRight;
    pAboveLeft = rowLeft;
    pBelowLeft = rowLeft;

    for (;;) {
        d += term + rx2;
        if (d >= 0) {
            bound -= ry22;
            d -= bound;
            pBelowRight--;
            pAboveLeft++;
            xr--;
            pAboveRight--;
            xl++;
            pBelowLeft++;
        }
        term += rx22;
        j++;
        pBelowRight += rowWords;
        pAboveLeft -= rowWords;
        pAboveRight -= rowWords;
        pBelowLeft += rowWords;
        if (term > bound)
            break;
        int lower = cy + j;
        int upper = cy - j;
        if (ELLIPSE_IN(xr, lower))
            *pBelowRight = (unsigned short)color;
        if (ELLIPSE_IN(xl, upper))
            *pAboveLeft = (unsigned short)color;
        if (ELLIPSE_IN(xr, upper))
            *pAboveRight = (unsigned short)color;
        if (ELLIPSE_IN(xl, lower))
            *pBelowLeft = (unsigned short)color;
    }
    return Unlock();
}
