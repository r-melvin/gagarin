// SPDX-License-Identifier: GPL-3.0-or-later
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy
// Frozen milestone flag set: /O2 /DNDEBUG /Gy without /GX.
// Provenance: own-binary-via-Ghidra. DSurface (RTTI .?AVDSurface@@, vtable 0x7E85D4) slot +0x40: | YRpp-cross-check | behaviour-confirmed-name
// a depth-tested, alpha-shaded 16-bit line. Read from 0x4BDF00's entry disassembly. The Z buffer
// (0x887644) and alpha buffer (0x87E8A4) are circular row buffers, as in the blitters module.
// The candidate is readable C++ and remains a partial match; this comment makes no claim about
// the source technique used to produce the retail instruction sequence.
// Names of the arguments are inferred from the body; unknown_40 keeps its slot name.
#include <stdlib.h>
#include "dsurface_class.h"
#include "drawing.h"
#include "drawing_more_methods.h"
#include "../render/blitters/r_shared_zwrap.h"
#include "../render/blitters/b_shared_alpha.h"

// Circular row-buffer object behind 0x887644 (Z) and 0x87E8A4 (alpha). Offsets read at 0x4BE263.. and
// 0x7BD130: +0x04 row origin, +0x14 backing surface (Lock/Unlock slots +0x5C/+0x60), +0x18/+0x1C wrap
// bounds, +0x20 wrap size in bytes, +0x24 (word) base, +0x28 row step in words.
struct LineBuffer_004BDF00
{
    int unknown_00;
    int RowOrigin;           // +0x04
    int unknown_08[2];       // +0x08
    int unknown_10;          // +0x10
    Surface* Backing;        // +0x14
    unsigned short* Start;   // +0x18
    unsigned short* End;     // +0x1C
    int WrapBytes;           // +0x20
    short Base;              // +0x24
    short unknown_26;        // +0x26
    int RowStep;             // +0x28
};
GG_STATIC_ASSERT(offsetof(LineBuffer_004BDF00, RowOrigin) == 0x04);
GG_STATIC_ASSERT(offsetof(LineBuffer_004BDF00, unknown_08) == 0x08);
GG_STATIC_ASSERT(sizeof(((LineBuffer_004BDF00*)0)->unknown_08) == 8);
GG_STATIC_ASSERT(offsetof(LineBuffer_004BDF00, unknown_10) == 0x10);
GG_STATIC_ASSERT(offsetof(LineBuffer_004BDF00, Backing) == 0x14);
GG_STATIC_ASSERT(offsetof(LineBuffer_004BDF00, Start) == 0x18);
GG_STATIC_ASSERT(offsetof(LineBuffer_004BDF00, End) == 0x1C);
GG_STATIC_ASSERT(offsetof(LineBuffer_004BDF00, WrapBytes) == 0x20);
GG_STATIC_ASSERT(offsetof(LineBuffer_004BDF00, Base) == 0x24);
GG_STATIC_ASSERT(offsetof(LineBuffer_004BDF00, unknown_26) == 0x26);
GG_STATIC_ASSERT(offsetof(LineBuffer_004BDF00, RowStep) == 0x28);
GG_STATIC_ASSERT(sizeof(LineBuffer_004BDF00) == 0x2C);


// FUNCTION: GAMEMD 0x4BE9D0 (decl; reloc). ECX = pixel colour bytes, EDX = red delta, stack = (green, blue),
// RET 8: adds the deltas (saturating) and packs the 16-bit pixel.
unsigned short BlendPixel(const unsigned char* rgb, int r, int g, int b);

// Advance a circular-buffer pointer by `step` words and wrap it into [Start, End).
static inline unsigned short* WrapStep(LineBuffer_004BDF00* buffer, unsigned short* p, int step)
{
    p += step;
    if (step > 0) {
        if (p >= buffer->End)
            p = (unsigned short*)((char*)p - buffer->WrapBytes);
    } else {
        if (p < buffer->Start)
            p = (unsigned short*)((char*)p + buffer->WrapBytes);
    }
    return p;
}

// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc) -- LIBRARY: CRT sqrt (cdecl, double on the stack, result in ST0).
double __cdecl LibrarySqrt(double value);

static inline int Distance(int dx, int dy)
{
    return (int)LibrarySqrt((double)dx * (double)dx + (double)dy * (double)dy);
}

#define Abs abs

// FUNCTION: GAMEMD 0x4BDF00
// clip = clip rectangle, from/to = endpoints, color = 3 bytes scaled by `scale`, zFrom/zTo = depths.
// The base declaration keeps seven ints (retail RET 0x1c), so the typed values are recovered by casts.
bool DSurface::unknown_40(RectangleStruct* clip, Point2D* from, Point2D* to, unsigned char* color, float scale, int zFrom, int zTo)
{
    int c0 = (int)(color[0] * scale);
    int c1 = (int)(color[1] * scale);
    int c2 = (int)(color[2] * scale);
    if (c0 < 8 && c1 < 8 && c2 < 8)
        return false;

    RectangleStruct scratch;
    RectangleStruct* surfaceRectTemp = &GetRect();
    RectangleStruct bounds = *RectIntersect(&scratch, clip, surfaceRectTemp, 0, 0);
    if (bounds.Width == 0 && bounds.Height == 0)
        return false;

    Point2D a;
    Point2D b;
    a.X = from->X + bounds.X;
    a.Y = from->Y + bounds.Y;
    b.X = to->X + bounds.X;
    b.Y = to->Y + bounds.Y;
    if (a.X > b.X) {
        Point2D t = a;
        a = b;
        b = t;
        int z = zFrom;
        zFrom = zTo;
        zTo = z;
    }
    int ax = a.X;
    int ay = a.Y;
    int bx = b.X;
    int by = b.Y;
    bool ok = ClipLine(&a, &b, &bounds);
    if (ok) {

    if (b.X != bx || b.Y != by) {
        int clipped = Distance(ax - b.X, ay - b.Y);
        int full = Distance(ax - bx, ay - by);
        int delta = Abs((int)((double)clipped / (double)full * (double)(zFrom - zTo)));
        zTo = zFrom < zTo ? zFrom + delta : zFrom - delta;
    }
    if (a.X != ax || a.Y != ay) {
        int clipped = Distance(a.X - bx, a.Y - by);
        int full = Distance(ax - bx, ay - by);
        int delta = Abs((int)((double)clipped / (double)full * (double)(zFrom - zTo)));
        zFrom = zFrom < zTo ? zTo - delta : zTo + delta;
    }

    GetBytesPerPixel();
    unsigned char* row = (unsigned char*)Lock(a);
    if (!((LineBuffer_004BDF00*)gg_rle_zwrap_global))
        return false;
    LineBuffer_004BDF00* zb = ((LineBuffer_004BDF00*)gg_rle_zwrap_global);
    // Entry callsites load ECX from 0x887644 before CALL 0x7BD130, then from
    // 0x87E8A4 before CALL 0x4114B0. These are address-checked receiver views.
    unsigned short* zp = (unsigned short*)((AlphaBuffer*)zb)->GetBuffer(a.X, a.Y - zb->RowOrigin);
    LineBuffer_004BDF00* ab = ((LineBuffer_004BDF00*)gg_blit_alpha_wrap_global);
    unsigned short* ap = (unsigned short*)((ABuffer*)ab)->GetBuffer(a.X, a.Y - ab->RowOrigin);
    int ySign = -1;
    int zStep = zb->RowStep;
    int zRef = (short)(zb->Base + zb->RowOrigin) - a.Y - bounds.Y + zFrom;
    if (!row)
        return false;

    int dx = b.X - a.X;
    int dy = b.Y - a.Y;
    int dz = zTo - zFrom;
    int pitch = GetPitch();
    if (dy < 0) {
        ySign = 1;
        pitch = -pitch;
        zStep = -zStep;
    }
    int zDir = dz < 0 ? -1 : 1;
    int ady = Abs(dy);
    int adz = Abs(dz);
    int twoDx = dx * 2;
    int twoAdy = ady * 2;
    int twoAdz = adz * 2;
    unsigned char rgb[3] = {0, 0, 0};
    int xOffset = 0;

    // Plot: depth test, read back, scale the alpha-buffer value by the colour, store.
#define PLOT(OFFSET)                                                                            \
    if ((unsigned short)zRef < *zp) {                                                           \
        unsigned short old = *(unsigned short*)(row + (OFFSET));                                \
        rgb[0] = (old >> gg_b_translucent_pixel_format.pos0) << gg_b_translucent_pixel_format.loss0;                    \
        rgb[1] = (old >> gg_b_translucent_pixel_format.pos2) << gg_b_translucent_pixel_format.loss2;                    \
        rgb[2] = (old >> gg_b_translucent_pixel_format.pos1) << gg_b_translucent_pixel_format.loss1;                    \
        int alpha = *ap;                                                                        \
        *(unsigned short*)(row + (OFFSET)) = BlendPixel(rgb, (alpha * c0) >> 7, (alpha * c1) >> 7, (alpha * c2) >> 7); \
    }

    if (dx < adz && ady < adz) {
        int errY = twoAdy - adz;
        int errX = twoDx - adz;
        for (int n = adz; n > 0; n--) {
            PLOT(xOffset)
            if (errY > 0) {
                row += pitch;
                zp = WrapStep(zb, zp, zStep);
                ap = WrapStep(ab, ap, zStep);
                zRef += ySign;
                errY -= twoAdz;
            }
            if (errX > 0) {
                zp = WrapStep(zb, zp, 1);
                xOffset += 2;
                errX -= twoAdz;
            }
            zRef += zDir;
            errX += twoDx;
            errY += twoAdy;
        }
    } else if (ady < dx) {
        int errY = twoAdy - dx;
        int errZ = twoAdz - dx;
        for (int x = 0; x < dx; x++) {
            PLOT(x * 2)
            if (errY > 0) {
                row += pitch;
                errY -= twoDx;
                zp = WrapStep(zb, zp, zStep);
                ap = WrapStep(ab, ap, zStep);
                zRef += ySign;
            }
            if (errZ > 0) {
                zRef += zDir;
                errZ -= twoDx;
            }
            errY += twoAdy;
            errZ += twoAdz;
            zp = WrapStep(zb, zp, 1);
        }
    } else {
        int errX = twoDx - ady;
        int errZ = twoAdz - ady;
        for (int n = ady; n > 0; n--) {
            PLOT(xOffset)
            if (errX > 0) {
                zp = WrapStep(zb, zp, 1);
                xOffset += 2;
                errX -= twoAdy;
            }
            if (errZ > 0) {
                zRef += zDir;
                errZ -= twoAdy;
            }
            errX += twoDx;
            errZ += twoAdz;
            row += pitch;
            zp = WrapStep(zb, zp, zStep);
            ap = WrapStep(ab, ap, zStep);
            zRef += ySign;
        }
    }
#undef PLOT
    Unlock();
    return true;
    }
    return false;
}
