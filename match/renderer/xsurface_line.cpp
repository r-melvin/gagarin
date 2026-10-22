// SPDX-License-Identifier: GPL-3.0-or-later
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy
// ^ no /GX: paired probe on the XSurface scalar deleting destructor (0x4115A0): with /GX VC6 keeps a
// separate ~XSurface call (0/12), without it the destructor inlines and matches (12/12). The Blit*
// stack locals of 0x7BBB90 also carry no unwind frame in retail.
// Provenance: own-binary-via-Ghidra. XSurface line drawing: DrawLineEx
// (slot +0x2C), DrawDottedLine (+0x48) and DrawLineCallback (+0x44).
#include <stdlib.h>
#include <string.h>
#include "surface_class.h"

// FUNCTION: GAMEMD 0x7BA610
bool XSurface::DrawLineEx(RectangleStruct* clip, Point2D* from, Point2D* to,
                          unsigned int color)
{
    RectangleStruct tmp;
    RectangleStruct* bounds = &GetRect();
    RectangleStruct region = *RectIntersect(&tmp, clip, bounds, 0, 0);
    Point2D a;
    Point2D b;

    a.X = from->X + region.X;
    a.Y = from->Y + region.Y;
    b.Y = to->Y + region.Y;
    b.X = to->X + region.X;
    if (!ClipLine(&a, &b, &region))
        return false;

    if (a.X > b.X) {
        int swap = a.X;
        a.X = b.X;
        b.X = swap;
        swap = a.Y;
        a.Y = b.Y;
        b.Y = swap;
    }

    int bpp = GetBytesPerPixel();
    unsigned char* p = (unsigned char*)Lock(a);
    if (!p)
        return false;

    if (a.Y == b.Y) {
        if (bpp == 1) {
            memset(p, (unsigned char)color, b.X - a.X + 1);
        } else {
            for (int i = 0; i <= b.X - a.X; i++) {
                *(unsigned short*)p = (unsigned short)color;
                p += 2;
            }
        }
    } else if (a.X == b.X) {
        int step = (a.Y > b.Y) ? -(int)GetPitch() : (int)GetPitch();
        int count = abs(b.Y - a.Y);
        for (int n = count + 1; n != 0; n--) {
            if (bpp == 1)
                *p = (unsigned char)color;
            else
                *(unsigned short*)p = (unsigned short)color;
            p += step;
        }
    } else {
        int dy = b.Y - a.Y;
        int dx = b.X - a.X;
        int step = GetPitch();
        if (dy < 0)
            step = -step;
        int adjust = abs(dy);
        if (dx > adjust) {
            int err = 2 * adjust - dx;
            for (int i = 0; i < dx; i++) {
                if (bpp == 1)
                    p[i] = (unsigned char)color;
                else
                    ((unsigned short*)p)[i] = (unsigned short)color;
                if (err > 0) {
                    p += step;
                    err -= 2 * dx;
                }
                err += 2 * adjust;
            }
        } else {
            int err = 2 * dx - adjust;
            int j = 0;
            for (int n = adjust; n > 0; n--) {
                if (bpp == 1)
                    p[j] = (unsigned char)color;
                else
                    ((unsigned short*)p)[j] = (unsigned short)color;
                if (err > 0) {
                    j++;
                    err -= 2 * adjust;
                }
                err += 2 * dx;
                p += step;
            }
        }
    }
    Unlock();
    return true;
}

// FUNCTION: GAMEMD 0x7BA8C0
// Unclipped dotted line. `pattern` is a 16-entry on/off table indexed by a phase that
// wraps into 0..15 before every pixel; the final phase is returned. The horizontal
// case stores 16-bit pixels whatever GetBytesPerPixel() says (retail behaviour).
unsigned int XSurface::DrawDottedLine(Point2D* from, Point2D* to, unsigned int color,
                                      unsigned char* pattern, unsigned int phase)
{
    int x0 = from->X;
    int y0 = from->Y;
    int x1 = to->X;
    int y1 = to->Y;
    int dir = 1;

    if (x0 > x1) {
        int swapX = x1;
        x1 = x0;
        x0 = swapX;
        int swapY = y1;
        y1 = y0;
        y0 = swapY;
        int length = abs(x0 - x1);
        int tall = abs(y0 - y1) + 1;
        if (length < tall)
            length = tall;
        phase = (length + (int)phase) % 16;
        dir = -1;
    }

    int bpp = GetBytesPerPixel();
    Point2D start;
    start.X = x0;
    start.Y = y0;
    unsigned char* p = (unsigned char*)Lock(start);
    if (!p)
        return phase;

    int phaseNow = phase;
    if (y0 == y1) {
        for (int n = x1 - x0 + 1; n > 0; n--) {
            if (phaseNow < 0)
                phaseNow += 16;
            if (phaseNow >= 16)
                phaseNow -= 16;
            if (pattern[phaseNow])
                *(unsigned short*)p = (unsigned short)color;
            p += 2;
            phaseNow += dir;
        }
    } else if (x0 == x1) {
        int step = (y0 > y1) ? -(int)GetPitch() : (int)GetPitch();
        for (int n = abs(y1 - y0) + 1; n > 0; n--) {
            if (phaseNow < 0)
                phaseNow += 16;
            if (phaseNow >= 16)
                phaseNow -= 16;
            if (pattern[phaseNow]) {
                if (bpp == 1)
                    *p = (unsigned char)color;
                else
                    *(unsigned short*)p = (unsigned short)color;
            }
            p += step;
            phaseNow += dir;
        }
    } else {
        int dy = y1 - y0;
        int dx = x1 - x0;
        int step = GetPitch();
        if (dy < 0)
            step = -step;
        int adjust = abs(dy);
        if (dx > adjust) {
            int err = 2 * adjust - dx;
            for (int i = 0; i < dx; i++) {
                if (phaseNow < 0)
                    phaseNow += 16;
                if (phaseNow >= 16)
                    phaseNow -= 16;
                if (pattern[phaseNow]) {
                    if (bpp == 1)
                        p[i] = (unsigned char)color;
                    else
                        ((unsigned short*)p)[i] = (unsigned short)color;
                }
                if (err > 0) {
                    p += step;
                    err -= 2 * dx;
                }
                err += 2 * adjust;
                phaseNow += dir;
            }
        } else {
            int err = 2 * dx - adjust;
            int j = 0;
            for (int n = adjust; n > 0; n--) {
                if (phaseNow < 0)
                    phaseNow += 16;
                if (phaseNow >= 16)
                    phaseNow -= 16;
                if (pattern[phaseNow]) {
                    if (bpp == 1)
                        p[j] = (unsigned char)color;
                    else
                        ((unsigned short*)p)[j] = (unsigned short)color;
                }
                if (err > 0) {
                    j++;
                    err -= 2 * adjust;
                }
                err += 2 * dx;
                p += step;
                phaseNow += dir;
            }
        }
    }
    Unlock();
    return phaseNow;
}
// FUNCTION: GAMEMD 0x7BAB90
// Clips the line to `clip` (relative coordinates) and calls `callback` once
// per pixel with the pixel's Point2D in ECX. Retail calls Unlock (+0x60) at the end although
// no Lock call precedes it.
bool XSurface::DrawLineCallback(RectangleStruct* clip, Point2D* from, Point2D* to,
                                SurfacePixelCallback callback)
{
    RectangleStruct tmp;
    RectangleStruct* bounds = &GetRect();
    RectangleStruct region = *RectIntersect(&tmp, clip, bounds, 0, 0);
    Point2D a;
    Point2D b;

    a.X = from->X + region.X;
    a.Y = from->Y + region.Y;
    b.X = to->X + region.X;
    b.Y = to->Y + region.Y;
    if (!ClipLine(&a, &b, &region))
        return false;

    if (a.X > b.X) {
        int swap = a.X;
        a.X = b.X;
        b.X = swap;
        swap = a.Y;
        a.Y = b.Y;
        b.Y = swap;
    }

    Point2D pixel;
    if (a.Y == b.Y) {
        for (int i = 0; i <= b.X - a.X; i++) {
            pixel.X = a.X + i;
            pixel.Y = b.Y;
            callback(&pixel);
        }
    } else if (a.X == b.X) {
        int count = abs(a.Y - b.Y);
        int top = a.Y < b.Y ? a.Y : b.Y;
        for (int i = 0; i <= count; i++) {
            pixel.X = a.X;
            pixel.Y = top + i;
            callback(&pixel);
        }
    } else {
        int dx = b.X - a.X;
        int dy = b.Y - a.Y;
        int step = dy < 0 ? -1 : 1;
        int adjust = abs(dy);
        int x = a.X;
        int y = a.Y;
        if (dx > adjust) {
            int err = 2 * adjust - dx;
            for (; x <= b.X; x++) {
                pixel.X = x;
                pixel.Y = y;
                callback(&pixel);
                if (err > 0) {
                    err -= 2 * dx;
                    y += step;
                }
                err += 2 * adjust;
            }
        } else {
            int err = 2 * dx - adjust;
            for (int n = adjust + 1; n != 0; n--) {
                pixel.X = x;
                pixel.Y = y;
                callback(&pixel);
                if (err > 0) {
                    x++;
                    err -= 2 * adjust;
                }
                err += 2 * dx;
                y += step;
            }
        }
    }
    Unlock();
    return true;
}
