// SPDX-License-Identifier: GPL-3.0-or-later
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy
// Frozen milestone flag set: /O2 /DNDEBUG /Gy without /GX.
// Provenance: own-binary-via-Ghidra. DSurface (RTTI .?AVDSurface@@, vtable 0x7E85D4) slot +0x34 at 0x4BFD30: | YRpp-cross-check
// a Bresenham line on a 16-bit surface that is depth-tested against the Z buffer (global 0x887644) and
// tinted by the buffer at global 0x87E8A4; both observed buffers use circular wrapping. This is a readable
// partial candidate; the function's full control-flow extent is longer than the earlier saved span.
#include <math.h>
#include "dsurface_class.h"
#include "drawing.h"
#include "drawing_more_methods.h"
#include "../render/blitters/r_shared_zwrap.h"
#include "../render/blitters/b_shared_alpha.h"

#pragma function(sqrt)

// Circular row buffer object behind the Z buffer (0x887644) and the alpha buffer (0x87E8A4). Only the fields
// the line reads are modelled: +0x04 / +0x24 / +0x28 locate the pixel origin, +0x18 / +0x1C bound the
// buffer, +0x20 is the wrap distance in bytes (evidence: 0x4C02A1, 0x4C02A6..0x4C02B0, 0x4C0065).
struct WrapBuffer_004BFD30
{
    unsigned char unknown_00[4];
    int Top;                      // +0x04
    unsigned char unknown_08[0x10];
    unsigned short* WrapBegin;    // +0x18
    unsigned short* WrapEnd;      // +0x1C
    unsigned int WrapStep;        // +0x20
    unsigned short Origin;        // +0x24
    unsigned char unknown_26[2];
    int RowStride;                // +0x28 (in 16-bit units)
};
GG_STATIC_ASSERT(offsetof(WrapBuffer_004BFD30, unknown_00) == 0);
GG_STATIC_ASSERT(offsetof(WrapBuffer_004BFD30, unknown_08) == 0x08);
GG_STATIC_ASSERT(sizeof(((WrapBuffer_004BFD30*)0)->unknown_08) == 0x10);
GG_STATIC_ASSERT(offsetof(WrapBuffer_004BFD30, Top) == 0x04);
GG_STATIC_ASSERT(offsetof(WrapBuffer_004BFD30, WrapBegin) == 0x18);
GG_STATIC_ASSERT(offsetof(WrapBuffer_004BFD30, WrapEnd) == 0x1C);
GG_STATIC_ASSERT(offsetof(WrapBuffer_004BFD30, WrapStep) == 0x20);
GG_STATIC_ASSERT(offsetof(WrapBuffer_004BFD30, Origin) == 0x24);
GG_STATIC_ASSERT(offsetof(WrapBuffer_004BFD30, unknown_26) == 0x26);
GG_STATIC_ASSERT(offsetof(WrapBuffer_004BFD30, RowStride) == 0x28);
GG_STATIC_ASSERT(sizeof(WrapBuffer_004BFD30) == 0x2C);

// GLOBAL: GAMEMD 0x8A0DD0..0x8A0DE4 -- see dsurface.h (pair 0 = byte 0, pair 2 = byte 1, pair 1 = byte 2).
// LIBRARY: sqrt (0x4CAC40), _ftol (0x7C5F00).

static inline unsigned short* WrapRow(WrapBuffer_004BFD30* buf, unsigned short* p, int step)
{
    if (step > 0) {
        if (p >= buf->WrapEnd)
            p = (unsigned short*)((char*)p - buf->WrapStep);
    } else if (p < buf->WrapBegin) {
        p = (unsigned short*)((char*)p + buf->WrapStep);
    }
    return p;
}

static inline int Distance(int dx, int dy)
{
    return (int)sqrt((double)dx * (double)dx + (double)dy * (double)dy);
}

static inline unsigned short Shade(unsigned int alpha, unsigned int ch0, unsigned int ch1, unsigned int ch2)
{
    return (unsigned short)((((int)(alpha * ch0) >> 7) >> gg_b_translucent_pixel_format.loss0) << gg_b_translucent_pixel_format.pos0) |
           (unsigned short)((((int)(alpha * ch2) >> 7) >> gg_b_translucent_pixel_format.loss1) << gg_b_translucent_pixel_format.pos1) |
           (unsigned short)((((int)(alpha * ch1) >> 7) >> gg_b_translucent_pixel_format.loss2) << gg_b_translucent_pixel_format.pos2);
}

// FUNCTION: GAMEMD 0x4BFD30
// The base declaration keeps seven ints (retail RET 0x1c), so the typed values are recovered by casts:
// (RectangleStruct* clip, Point2D* from, Point2D* to, unsigned int color, int zEnd, int zStart, bool writeZ).
bool DSurface::unknown_34(RectangleStruct* clip, Point2D* from, Point2D* to, unsigned int color, int zEnd, int zStart, bool writeZ)
{
    RectangleStruct scratch;
    RectangleStruct* surfaceRect = &GetRect();
    RectangleStruct area = *RectIntersect(&scratch, clip, surfaceRect, 0, 0);
    if (area.Width == 0 && area.Height == 0)
        return false;

    Point2D pt[2];
    pt[0].X = from->X + area.X;
    pt[0].Y = from->Y + area.Y;
    pt[1].X = to->X + area.X;
    pt[1].Y = to->Y + area.Y;
    if (pt[1].X < pt[0].X) {
        Point2D t = pt[0];
        pt[0] = pt[1];
        pt[1] = t;
        int zt = zEnd;
        zEnd = zStart;
        zStart = zt;
    }
    Point2D& a = pt[0];
    Point2D& b = pt[1];
    int& zA = zStart;
    int& zB = zEnd;

    Point2D origA = a;
    Point2D origB = b;
    if (!ClipLine(&a, &b, &area))
        return false;

    if (b.X != origB.X || b.Y != origB.Y) {
        int cut = Distance(origA.X - b.X, origA.Y - b.Y);
        int total = Distance(origA.X - origB.X, origA.Y - origB.Y);
        int delta = abs((int)(((double)cut / (double)total) * (double)(zB - zA)));
        zB = zB < zA ? zA - delta : zA + delta;
    }
    if (a.X != origA.X || a.Y != origA.Y) {
        int cut = Distance(a.X - origA.X, a.Y - origA.Y);
        int total = Distance(origB.X - origA.X, origB.Y - origA.Y);
        int delta = abs((int)(((double)cut / (double)total) * (double)(zB - zA)));
        zA = zA < zB ? zA + delta : zA - delta;
    }

    GetBytesPerPixel();
    unsigned short* dest = (unsigned short*)Lock(a);
    if (!((WrapBuffer_004BFD30*)gg_rle_zwrap_global))
        return false;
    // Entry callsites load ECX from 0x887644 before CALL 0x7BD130, then from
    // 0x87E8A4 before CALL 0x4114B0. These are address-checked receiver views.
    unsigned short* zrow = (unsigned short*)((AlphaBuffer*)gg_rle_zwrap_global)->GetBuffer(a.X, a.Y - ((WrapBuffer_004BFD30*)gg_rle_zwrap_global)->Top);
    unsigned short* arow = (unsigned short*)((ABuffer*)gg_blit_alpha_wrap_global)->GetBuffer(a.X, a.Y - ((WrapBuffer_004BFD30*)gg_blit_alpha_wrap_global)->Top);
    int zStep = -1;
    int zCur = (unsigned short)(((WrapBuffer_004BFD30*)gg_rle_zwrap_global)->Origin + ((WrapBuffer_004BFD30*)gg_rle_zwrap_global)->Top) - a.Y - area.Y + zA;
    int rowStride = ((WrapBuffer_004BFD30*)gg_rle_zwrap_global)->RowStride;
    if (!dest)
        return false;

    unsigned char ch0 = color >> gg_b_translucent_pixel_format.pos0;
    ch0 <<= gg_b_translucent_pixel_format.loss0;
    unsigned char ch1 = color >> gg_b_translucent_pixel_format.pos2;
    ch1 <<= gg_b_translucent_pixel_format.loss2;
    unsigned char ch2 = color >> gg_b_translucent_pixel_format.pos1;
    ch2 <<= gg_b_translucent_pixel_format.loss1;

    int dx = b.X - a.X;
    int dy = b.Y - a.Y;
    int pitch = GetPitch();
    int rowDelta = pitch;
    if (dy < 0) {
        rowDelta = -pitch;
        rowStride = -rowStride;
        zStep = 1;
    }
    int ystep = 1;
    if ((zB - zA) < 0)
        ystep = -1;
    int adx = abs(dx);
    int ady = abs(dy);
    int adx2 = adx * 2;
    int ady2 = ady * 2;

    if (dx < ady && adx < ady) {
        // steep line: one row per step
        int err = -ady;
        int errX = -ady;
        for (int i = 0; i < ady; i++) {
            errX += dx * 2;
            err += adx2;
            unsigned int alpha = *arow;
            if ((unsigned short)zCur < *zrow && alpha != 0) {
                unsigned short px = color;
                if (alpha != 0x7F)
                    px = Shade(alpha, ch0, ch1, ch2);
                *(unsigned short*)((char*)dest + i * 2) = px;
                if (writeZ)
                    *zrow = zCur;
            }
            if (err > 0) {
                dest = (unsigned short*)((char*)dest + rowDelta);
                err -= ady2;
                zrow = WrapRow(((WrapBuffer_004BFD30*)gg_rle_zwrap_global), zrow + rowStride, rowStride);
                arow = WrapRow(((WrapBuffer_004BFD30*)gg_blit_alpha_wrap_global), arow + rowStride, rowStride);
                zCur += zStep;
            }
            if (errX > 0) {
                zrow = WrapRow(((WrapBuffer_004BFD30*)gg_rle_zwrap_global), zrow + 1, 1);
                arow = WrapRow(((WrapBuffer_004BFD30*)gg_blit_alpha_wrap_global), arow + 1, 1);
                errX -= ady2;
            }
            zCur += ystep;
        }
    } else if (adx < dx) {
        int err = -dx;
        int errY = -dx;
        for (int i = 0; i < dx; i++) {
            err += ady2;
            errY += adx2;
            unsigned int alpha = *arow;
            if ((unsigned short)zCur < *zrow && alpha != 0) {
                unsigned short px = color;
                if (alpha != 0x7F)
                    px = Shade(alpha, ch0, ch1, ch2);
                *(unsigned short*)((char*)dest + i * 2) = px;
                if (writeZ)
                    *zrow = zCur;
            }
            if (errY > 0) {
                dest = (unsigned short*)((char*)dest + rowDelta);
                errY -= dx * 2;
                zrow = WrapRow(((WrapBuffer_004BFD30*)gg_rle_zwrap_global), zrow + rowStride, rowStride);
                zCur += zStep;
                arow = WrapRow(((WrapBuffer_004BFD30*)gg_blit_alpha_wrap_global), arow + rowStride, rowStride);
            }
            if (err > 0) {
                zCur += ystep;
                err -= dx * 2;
            }
            zrow = WrapRow(((WrapBuffer_004BFD30*)gg_rle_zwrap_global), zrow + 1, 1);
            arow = WrapRow(((WrapBuffer_004BFD30*)gg_blit_alpha_wrap_global), arow + 1, 1);
        }
    } else {
        int err = -adx;
        int errMinor = ady2 - adx;
        for (int i = 0; i < adx; i++) {
            err += ady2;
            unsigned int alpha = *arow;
            if ((unsigned short)zCur < *zrow && alpha != 0) {
                unsigned short px = color;
                if (alpha != 0x7F)
                    px = Shade(alpha, ch0, ch1, ch2);
                *(unsigned short*)((char*)dest + i * 2) = px;
                if (writeZ)
                    *zrow = zCur;
            }
            if (err > 0) {
                zrow = WrapRow(((WrapBuffer_004BFD30*)gg_rle_zwrap_global), zrow + 1, 1);
                arow = WrapRow(((WrapBuffer_004BFD30*)gg_blit_alpha_wrap_global), arow + 1, 1);
                err -= adx2;
            }
            if (errMinor > 0) {
                zCur += ystep;
                errMinor -= adx2;
            }
            errMinor += ady2;
            dest = (unsigned short*)((char*)dest + rowDelta);
            zrow = WrapRow(((WrapBuffer_004BFD30*)gg_rle_zwrap_global), zrow + rowStride, rowStride);
            zCur += zStep;
            arow = WrapRow(((WrapBuffer_004BFD30*)gg_blit_alpha_wrap_global), arow + rowStride, rowStride);
        }
    }
    Unlock();
    return true;
}
