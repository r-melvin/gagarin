// SPDX-License-Identifier: GPL-3.0-or-later
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy
// Frozen milestone flag set: /O2 /DNDEBUG /Gy without /GX.
// Provenance: own-binary-via-Ghidra. DSurface slot +0x3C (0x4BC750): depth-tested, anti-aliased line on a | YRpp-cross-check
// 16-bit surface. The candidate uses a readable loop structure and remains partial.
#include "dsurface_class.h"
#include "drawing.h"
#include "drawing_more_methods.h"
#include "../render/blitters/r_shared_zwrap.h"
#include "../render/blitters/b_shared_alpha.h"

// LIBRARY: GAMEMD 0x7C8FB0 (decl; reloc) (LIBRARY: _CIpow, x87 register ABI), 0x7C5F00 (LIBRARY: _ftol).
double __cdecl pow(double, double);

// Address view of the data read through 0x887644; +0x14 holds the Surface whose Lock gives pixel addresses
// (0x7BD130 GetPixelAddress: Lock(x,y) then Unlock). Evidence: 0x7BD130 body, 0x4BCAB8.
// Address view of data read through 0x87E8A4, same accessed layout. The wrap fields +0x18/+0x1C/+0x20
// (lower bound, upper bound, wrap size) are read at 0x4BCF9D..0x4BD030.
// Retail 0x4BCB14 reads the row stride at +0x28. The explicit gap below
// corrects an oversized draft gap; sizeof pins this view, not the full owner.
struct LineBuffer_004BC750
{
    int unknown_00;
    int Top;               // +0x04
    int unknown_08[3];
    Surface* Pixels;       // +0x14
    unsigned short* Low;   // +0x18
    unsigned short* High;  // +0x1C
    int WrapBytes;         // +0x20
    short ZBias;           // +0x24
    short unknown_26;
    int RowStep;           // +0x28
};
GG_STATIC_ASSERT(offsetof(LineBuffer_004BC750, Top) == 0x04);
GG_STATIC_ASSERT(offsetof(LineBuffer_004BC750, unknown_08) == 0x08);
GG_STATIC_ASSERT(sizeof(((LineBuffer_004BC750*)0)->unknown_08) == 0x0C);
GG_STATIC_ASSERT(offsetof(LineBuffer_004BC750, Pixels) == 0x14);
GG_STATIC_ASSERT(offsetof(LineBuffer_004BC750, Low) == 0x18);
GG_STATIC_ASSERT(offsetof(LineBuffer_004BC750, High) == 0x1C);
GG_STATIC_ASSERT(offsetof(LineBuffer_004BC750, WrapBytes) == 0x20);
GG_STATIC_ASSERT(offsetof(LineBuffer_004BC750, ZBias) == 0x24);
GG_STATIC_ASSERT(offsetof(LineBuffer_004BC750, RowStep) == 0x28);
GG_STATIC_ASSERT(sizeof(LineBuffer_004BC750) == 0x2C);

// FUNCTION: GAMEMD 0x4C1B50 (decl; reloc) -- thiscall sqrt(x*x + y*y) of a Point2D, rounded to int via _ftol.
struct Point2DLength_004BC750 : public Point2D
{
    int Length() const;
};

// The shared header gives these globals width-qualified address views. The table
// values below are a readable interpretation of the initialization instructions.

static unsigned int Expand(unsigned short pixel, int channel)
{
    return (unsigned char)(pixel >> DSurfacePixelShift(channel, 0)) << DSurfacePixelShift(channel, 1);
}

// FUNCTION: GAMEMD 0x4BC750
// RET 0x2C: eleven stack arguments.
bool DSurface::unknown_3C(RectangleStruct* clip, Point2D* from, Point2D* to, unsigned char* rgb, int zFrom, int zTo, bool writeZ, bool blendA, bool blendB, bool blendC, float scale)
{
    if (!DAT_008A0DF1) {
        DAT_008A0DF1 = true;
        for (int i = 0; i <= 256; i++)
            DAT_008A0980[i] = (int)((pow(i / 128.0 - 1.0, 3.0) + 1.0) * 128.0);
    }

    RectangleStruct scratch;
    RectangleStruct* surfaceRect = &GetRect();
    RectangleStruct inner = *surfaceRect;
    inner.X += 1;
    inner.Y += 1;
    inner.Width -= 2;
    inner.Height -= 2;
    RectangleStruct bounds = *RectIntersect(&scratch, clip, &inner, 0, 0);
    if (bounds.Width == 0 && bounds.Height == 0)
        return false;

    Point2D a, b;
    a.X = bounds.X + from->X;
    a.Y = bounds.Y + from->Y;
    b.X = bounds.X + to->X;
    b.Y = bounds.Y + to->Y;
    int za = zFrom, zb = zTo;
    if (a.X > b.X) {
        Point2D t = a; a = b; b = t;
        int tz = za; za = zb; zb = tz;
    }
    Point2D oa = a, ob = b;
    if (!ClipLine(&a, &b, &bounds))
        return false;
    if (a.X != oa.X || a.Y != oa.Y) {
        Point2D whole, cut;
        whole.X = ob.X - oa.X;
        whole.Y = ob.Y - oa.Y;
        cut.X = b.X - a.X;
        cut.Y = b.Y - a.Y;
        int total = ((Point2DLength_004BC750*)&whole)->Length();
        int part = ((Point2DLength_004BC750*)&cut)->Length();
        int delta = (int)((double)part / total * (zb - za));
        za = (delta < 0 ? -delta : delta) + za;
    }
    if (b.X != ob.X || b.Y != ob.Y) {
        Point2D whole, cut;
        whole.X = ob.X - oa.X;
        whole.Y = ob.Y - oa.Y;
        cut.X = ob.X - b.X;
        cut.Y = ob.Y - b.Y;
        int total = ((Point2DLength_004BC750*)&whole)->Length();
        int part = ((Point2DLength_004BC750*)&cut)->Length();
        int delta = (int)((double)part / total * (zb - za));
        zb = zb - (delta < 0 ? -delta : delta);
    }

    unsigned short* pixel = (unsigned short*)Lock(a);
    if (!((LineBuffer_004BC750*)gg_rle_zwrap_global)) {
        Unlock();
        return false;
    }
    LineBuffer_004BC750* depth = (LineBuffer_004BC750*)gg_rle_zwrap_global;
    LineBuffer_004BC750* alpha = (LineBuffer_004BC750*)gg_blit_alpha_wrap_global;
    // Entry callsites load ECX from 0x887644 before CALL 0x7BD130, then from
    // 0x87E8A4 before CALL 0x4114B0. These are address-checked receiver views.
    unsigned short* zPixel = (unsigned short*)((AlphaBuffer*)gg_rle_zwrap_global)->GetBuffer(a.X, a.Y - ((LineBuffer_004BC750*)gg_rle_zwrap_global)->Top);
    unsigned short* aPixel = (unsigned short*)((ABuffer*)gg_blit_alpha_wrap_global)->GetBuffer(a.X - ((int*)((LineBuffer_004BC750*)gg_blit_alpha_wrap_global))[0], a.Y - ((LineBuffer_004BC750*)gg_blit_alpha_wrap_global)->Top);
    if (!pixel) {
        Unlock();
        return false;
    }

    int dx = b.X - a.X;
    int dy = b.Y - a.Y;
    int adx = dx < 0 ? -dx : dx;
    int ady = dy < 0 ? -dy : dy;
    int major = adx > ady ? adx : ady;
    int minor = adx > ady ? ady : adx;
    if (major == 0) {
        Unlock();
        return false;
    }
    int pitch = (int)GetPitch();
    int yStep = dy < 0 ? -pitch : pitch;
    int zStep = (zb - za) < 0 ? -1 : 1;
    int zSpan = (zb - za) < 0 ? za - zb : zb - za;
    int zError = 0;
    int slope = (int)((double)minor / major * 256.0);
    int accum = 0;
    int z = za;
    unsigned int base[3] = {rgb[0], rgb[1], rgb[2]};
    bool enabled[3] = {blendA, blendB, blendC};

    for (int step = 0; step < major; step++) {
        unsigned int depthValue = *aPixel;
        if ((unsigned short)z < *zPixel && depthValue != 0) {
            int w1 = (int)((256 - accum) * scale);
            int w2 = (int)(accum * scale);
            unsigned short* second = (unsigned short*)((char*)pixel + (adx > ady ? yStep : 2));
            unsigned short* both[2] = {pixel, second};
            int weightHi[2] = {DAT_008A0980[256 - w1], DAT_008A0980[256 - w2]};
            int weightLo[2] = {DAT_008A0980[w1], DAT_008A0980[w2]};
            for (int p = 0; p < 2; p++) {
                unsigned int out[3];
                for (int c = 0; c < 3; c++) {
                    unsigned int v = Expand(*both[p], c);
                    if (enabled[c])
                        v = ((v * weightHi[p] + weightLo[p] * base[c]) * depthValue) >> 15;
                    out[c] = v > 255 ? 255 : v;
                }
                *both[p] = (unsigned short)((out[0] >> gg_b_translucent_pixel_format.loss0 << gg_b_translucent_pixel_format.pos0) |
                                            (out[1] >> gg_b_translucent_pixel_format.loss2 << gg_b_translucent_pixel_format.pos2) |
                                            (out[2] >> gg_b_translucent_pixel_format.loss1 << gg_b_translucent_pixel_format.pos1));
            }
            if (writeZ)
                *zPixel = (unsigned short)z;
        }
        accum += slope;
        if (adx > ady) {
            pixel = (unsigned short*)((char*)pixel + 2);
            zPixel++;
            aPixel++;
            if (accum > 256) {
                accum -= 256;
                pixel = (unsigned short*)((char*)pixel + yStep);
                zPixel += (dy < 0 ? -1 : 1) * (depth->RowStep / 2);
                aPixel += (dy < 0 ? -1 : 1) * (alpha->RowStep / 2);
            }
        } else {
            pixel = (unsigned short*)((char*)pixel + yStep);
            zPixel += (dy < 0 ? -1 : 1) * (depth->RowStep / 2);
            aPixel += (dy < 0 ? -1 : 1) * (alpha->RowStep / 2);
            if (accum > 256) {
                accum -= 256;
                pixel = (unsigned short*)((char*)pixel + 2);
                zPixel++;
                aPixel++;
            }
        }
        zError += zSpan;
        while (zError >= major) {
            zError -= major;
            z += zStep;
        }
    }
    Unlock();
    return true;
}
