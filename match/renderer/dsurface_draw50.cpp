// SPDX-License-Identifier: GPL-3.0-or-later
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy
// Frozen milestone flag set: /O2 /DNDEBUG /Gy without /GX.
// Provenance: own-binary-via-Ghidra. DSurface (RTTI .?AVDSurface@@, vtable 0x7E85D4) slot +0x50:
// a clipped line drawn into a 16-bit surface, masked by a circular word buffer that is walked in
// lockstep with the line. Span is CFG-closed (0x4C0E30..0x4C1431).
#include <stdlib.h>
#include "dsurface_class.h"
#include "drawing.h"
#include "../render/blitters/b_shared_alpha.h"
// LIBRARY: abs (CRT intrinsic, cdq/xor/sub inline)

// The circular mask buffer object (pointer global at 0x87E8A4, also read by the blitter alpha leaves).
// Layout evidence: +0x04, +0x18, +0x1C, +0x20, +0x28 read at 0x4C0EE5..0x4C1192.
struct MaskRing
{
    int unknown_00;
    int originY;                 // +0x04, subtracted from the start row
    unsigned char unknown_08[0x10];
    unsigned short* wrapLow;     // +0x18, wrap up when the pointer falls below
    unsigned short* wrapHigh;    // +0x1C, wrap down when the pointer reaches it
    unsigned int wrapBytes;      // +0x20
    int unknown_24;
    int rowStride;               // +0x28, mask-row step in words
};
GG_STATIC_ASSERT(offsetof(MaskRing, unknown_00) == 0x00);
GG_STATIC_ASSERT(offsetof(MaskRing, originY) == 0x04);
GG_STATIC_ASSERT(offsetof(MaskRing, unknown_08) == 0x08);
GG_STATIC_ASSERT(sizeof(((MaskRing*)0)->unknown_08) == 0x10);
GG_STATIC_ASSERT(offsetof(MaskRing, wrapLow) == 0x18);
GG_STATIC_ASSERT(offsetof(MaskRing, wrapHigh) == 0x1C);
GG_STATIC_ASSERT(offsetof(MaskRing, wrapBytes) == 0x20);
GG_STATIC_ASSERT(offsetof(MaskRing, unknown_24) == 0x24);
GG_STATIC_ASSERT(offsetof(MaskRing, rowStride) == 0x28);
GG_STATIC_ASSERT(sizeof(MaskRing) == 0x2C);


// Step the mask pointer by `delta` words, wrapping the circular buffer in the direction of travel
// (retail expands this inline at every step).
#define STEP_MASK(mask, delta, dir)                                              \
    do {                                                                         \
        (mask) += (delta);                                                       \
        if ((dir) > 0) {                                                         \
            if ((mask) >= ((MaskRing*)gg_blit_alpha_wrap_global)->wrapHigh)                                  \
                (mask) = (unsigned short*)((char*)(mask) - ((MaskRing*)gg_blit_alpha_wrap_global)->wrapBytes); \
        } else {                                                                 \
            if ((mask) < ((MaskRing*)gg_blit_alpha_wrap_global)->wrapLow)                                    \
                (mask) = (unsigned short*)((char*)(mask) + ((MaskRing*)gg_blit_alpha_wrap_global)->wrapBytes); \
        }                                                                        \
    } while (0)

// FUNCTION: GAMEMD 0x4C0E30
// Arguments (base declaration types kept): from/to are Point2D* line ends relative to the surface origin,
// color is the 16-bit pixel value, the last is a byte flag: write where the mask word is zero (true) or non-zero.
bool DSurface::unknown_50(int fromArg, int toArg, int colorArg, int flagArg)
{
    Point2D* from = (Point2D*)fromArg;
    Point2D* to = (Point2D*)toArg;

    if (GetBytesPerPixel() != 2)
        return false;

    Point2D ends[2];
    Point2D& a = ends[0];
    Point2D& b = ends[1];
    RectangleStruct bounds = GetRect();
    a.X = from->X + bounds.X;
    a.Y = from->Y + bounds.Y;
    b.X = to->X + bounds.X;
    b.Y = to->Y + bounds.Y;
    if (!ClipLine(&a, &b, &bounds))
        return false;
    if (a.X > b.X) {
        Point2D t = a;
        a = b;
        b = t;
    }

    // The entry loads ECX from 0x87E8A4 and directly calls 0x4114B0.
    unsigned short* mask = (unsigned short*)((ABuffer*)gg_blit_alpha_wrap_global)->GetBuffer(a.X, a.Y - ((MaskRing*)gg_blit_alpha_wrap_global)->originY);
    int rowStride = ((MaskRing*)gg_blit_alpha_wrap_global)->rowStride;
    if (b.Y < a.Y)
        rowStride = -rowStride;

    Point2D origin = a;
    unsigned short* pixel = (unsigned short*)Lock(origin);
    if (!pixel)
        return false;

    int dx = b.X - a.X;
    int dy = b.Y - a.Y;
    if ((unsigned char)flagArg) {
        if (a.Y == b.Y) {
            for (int i = 0; i <= b.X - a.X; i++) {
                if ((*mask == 0))
                    *pixel = (unsigned short)colorArg;
                STEP_MASK(mask, 1, rowStride);
                pixel++;
            }
        } else if (a.X == b.X) {
            int pitch = GetPitch();
            if (a.Y > b.Y)
                pitch = -pitch;
            int count = abs(dy) + 1;
            for (; count > 0; count--) {
                if ((*mask == 0))
                    *pixel = (unsigned short)colorArg;
                STEP_MASK(mask, rowStride, rowStride);
                pixel = (unsigned short*)((char*)pixel + pitch);
            }
        } else {
            int pitch = GetPitch();
            if (dy < 0)
                pitch = -pitch;
            int ady = abs(dy);
            if (dx > ady) {
                int err = 2 * ady - dx;
                for (int i = 0; i < dx; i++) {
                    if ((*mask == 0))
                        pixel[i] = (unsigned short)colorArg;
                    if (err > 0) {
                        pixel = (unsigned short*)((char*)pixel + pitch);
                        STEP_MASK(mask, rowStride, 1);
                        err -= 2 * dx;
                    }
                    STEP_MASK(mask, 1, rowStride);
                    err += 2 * ady;
                }
            } else {
                int err = 2 * dx - ady;
                int xoff = 0;
                for (int i = 0; i < ady; i++) {
                    if ((*mask == 0))
                        pixel[xoff] = (unsigned short)colorArg;
                    if (err > 0) {
                        err -= 2 * ady;
                        STEP_MASK(mask, 1, 1);
                        xoff++;
                    }
                    STEP_MASK(mask, rowStride, rowStride);
                    pixel = (unsigned short*)((char*)pixel + pitch);
                    err += 2 * dx;
                }
            }
        }
    } else {
        if (a.Y == b.Y) {
            for (int i = 0; i <= b.X - a.X; i++) {
                if ((*mask != 0))
                    *pixel = (unsigned short)colorArg;
                STEP_MASK(mask, 1, rowStride);
                pixel++;
            }
        } else if (a.X == b.X) {
            int pitch = GetPitch();
            if (a.Y > b.Y)
                pitch = -pitch;
            int count = abs(dy) + 1;
            for (; count > 0; count--) {
                if ((*mask != 0))
                    *pixel = (unsigned short)colorArg;
                STEP_MASK(mask, rowStride, rowStride);
                pixel = (unsigned short*)((char*)pixel + pitch);
            }
        } else {
            int pitch = GetPitch();
            if (dy < 0)
                pitch = -pitch;
            int ady = abs(dy);
            if (dx > ady) {
                int err = 2 * ady - dx;
                for (int i = 0; i < dx; i++) {
                    if ((*mask != 0))
                        pixel[i] = (unsigned short)colorArg;
                    if (err > 0) {
                        pixel = (unsigned short*)((char*)pixel + pitch);
                        STEP_MASK(mask, rowStride, 1);
                        err -= 2 * dx;
                    }
                    STEP_MASK(mask, 1, rowStride);
                    err += 2 * ady;
                }
            } else {
                int err = 2 * dx - ady;
                int xoff = 0;
                for (int i = 0; i < ady; i++) {
                    if ((*mask != 0))
                        pixel[xoff] = (unsigned short)colorArg;
                    if (err > 0) {
                        err -= 2 * ady;
                        STEP_MASK(mask, 1, 1);
                        xoff++;
                    }
                    STEP_MASK(mask, rowStride, rowStride);
                    pixel = (unsigned short*)((char*)pixel + pitch);
                    err += 2 * dx;
                }
            }
        }
    }
    Unlock();
    return true;
}
