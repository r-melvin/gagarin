// SPDX-License-Identifier: GPL-3.0-or-later
// VC6FLAGS: /nologo /c /O2 /DNDEBUG /Gy
// Frozen milestone flag set: /O2 /DNDEBUG /Gy without /GX.
// Provenance: own-binary-via-Ghidra. DSurface slot +0x90 (0x4BF750, DSurface-only): a clipped line on a 16-bit
// surface whose colour is blended between two 3-byte colours; the blend factor ping-pongs in [0,1] by a step.
// Span CFG-closed from the entry disassembly.
#include <stdlib.h>
#include "dsurface_class.h"

// FUNCTION: GAMEMD 0x661020 (decl; reloc). thiscall colour blend: ECX = 3-byte result, stack = (colour a, colour b,
// float t by value), RET 0xC, returns the result pointer. Not in the surface cluster's reserved list.
struct BlendedColor
{
    unsigned char Channel[3];
    BlendedColor* Blend(const unsigned char* a, const unsigned char* b, float t);
};

static inline unsigned short PackPixel(const BlendedColor& c)
{
    return (c.Channel[2] >> gg_b_translucent_pixel_format.loss2) << gg_b_translucent_pixel_format.pos2 |
           (c.Channel[1] >> gg_b_translucent_pixel_format.loss1) << gg_b_translucent_pixel_format.pos1 |
           (c.Channel[0] >> gg_b_translucent_pixel_format.loss0) << gg_b_translucent_pixel_format.pos0;
}

// Pixel for the current blend factor.
static inline unsigned short PixelAt(const unsigned char* a, const unsigned char* b, float* blend)
{
    BlendedColor mixer;
    BlendedColor c = *mixer.Blend(a, b, *blend);
    return PackPixel(c);
}

// Advance the blend factor; the step reverses direction at 0 and 1.
static inline void Advance(float* step, float* blend)
{
    float next = *step + *blend;
    *blend = next;
    if (next >= 0.0f || *step >= 0.0f) {
        if (next > 1.0f && *step > 0.0f) {
            *blend = 1.0f;
            *step = -*step;
        }
    } else {
        *blend = 0.0f;
        *step = -*step;
    }
}

// FUNCTION: GAMEMD 0x4BF750
bool DSurface::DrawLineGradient(RectangleStruct* clip, Point2D* from, Point2D* to, const unsigned char* colorA,
                                const unsigned char* colorB, float* step, float* blend)
{
    RectangleStruct scratch;
    RectangleStruct* surfaceRect = &GetRect();
    RectangleStruct area = *RectIntersect(&scratch, clip, surfaceRect, 0, 0);

    Point2D p1;
    Point2D p2;
    p1.X = from->X + area.X;
    p1.Y = from->Y + area.Y;
    p2.X = to->X + area.X;
    p2.Y = to->Y + area.Y;
    if (ClipLine(&p1, &p2, &area)) {
        if (p1.X > p2.X) {
            Point2D swap = p1;
            p1 = p2;
            p2 = swap;
        }
        if (GetBytesPerPixel() == 2) {
            unsigned short* pixel = (unsigned short*)Lock(p1);
            if (pixel) {
            if (p1.Y == p2.Y) {
                for (int i = 0; i <= p2.X - p1.X; i++) {
                    *pixel++ = PixelAt(colorA, colorB, blend);
                    Advance(step, blend);
                }
                Unlock();
                return true;
            }
            if (p1.X == p2.X) {
                int pitch = p1.Y > p2.Y ? -(int)GetPitch() : (int)GetPitch();
                int dy = abs(p2.Y - p1.Y);
                for (int i = 0; i <= dy; i++) {
                    *pixel = PixelAt(colorA, colorB, blend);
                    Advance(step, blend);
                    pixel = (unsigned short*)((char*)pixel + pitch);
                }
                Unlock();
                return true;
            }
            int dy = p2.Y - p1.Y;
            int dx = p2.X - p1.X;
            int pitch = GetPitch();
            if (dy < 0)
                pitch = -pitch;
            int ady = abs(dy);
            if (dx > ady) {
                int err = ady * 2 - dx;
                for (int i = 0; i <= dx; i++) {
                    pixel[i] = PixelAt(colorA, colorB, blend);
                    Advance(step, blend);
                    if (err > 0) {
                        pixel = (unsigned short*)((char*)pixel + pitch);
                        err -= dx * 2;
                    }
                    err += ady * 2;
                }
                Unlock();
                return true;
            }
            int err = dx * 2 - ady;
            int xoff = 0;
            for (int i = 0; i <= ady; i++) {
                *(unsigned short*)((char*)pixel + xoff) = PixelAt(colorA, colorB, blend);
                Advance(step, blend);
                if (err > 0) {
                    xoff += 2;
                    err -= ady * 2;
                }
                err += dx * 2;
                pixel = (unsigned short*)((char*)pixel + pitch);
            }
            Unlock();
            return true;
            }
        }
    }
    return false;
}
