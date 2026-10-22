// SPDX-License-Identifier: GPL-3.0-or-later
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy
// Frozen milestone flag set: /O2 /DNDEBUG /Gy without /GX.
// Provenance: own-binary-via-Ghidra. DSurface::unknown_38 (slot +0x38, 0x4BBCA0): a clipped, Z-buffer tested | YRpp-cross-check
// line draw on 16-bit surfaces that brightens the destination pixels by `brightness`/256. Read from the retail
// entry disassembly at 0x4BBCA0; the earlier candidate span is shorter than the current CFG extent.
#include <stdlib.h>
#include "dsurface_class.h"
#include "drawing_more_methods.h"
#include "../render/blitters/r_shared_zwrap.h"

// Address-scoped prefix view for data read through 0x887644. Only method-accessed fields are represented; offsets are read from
// the instructions at 0x4BBF2D..0x4BC2B0.
struct ZBufferLike_004BBCA0
{
    int unknown_00;                // +0x00
    int Top;                       // +0x04
    int unknown_08[3];             // +0x08
    int unknown_14;                // +0x14
    unsigned short* Low;           // +0x18 wrap lower bound
    unsigned short* High;          // +0x1C wrap upper bound
    int Size;                      // +0x20 wrap size in bytes
    short Extent;                  // +0x24
    short unknown_26;              // +0x26
    int Stride;                    // +0x28 row stride in depth words
};
GG_STATIC_ASSERT(offsetof(ZBufferLike_004BBCA0, unknown_00) == 0x00);
GG_STATIC_ASSERT(offsetof(ZBufferLike_004BBCA0, Top) == 0x04);
GG_STATIC_ASSERT(offsetof(ZBufferLike_004BBCA0, unknown_08) == 0x08);
GG_STATIC_ASSERT(sizeof(((ZBufferLike_004BBCA0*)0)->unknown_08) == 0x0C);
GG_STATIC_ASSERT(offsetof(ZBufferLike_004BBCA0, unknown_14) == 0x14);
GG_STATIC_ASSERT(offsetof(ZBufferLike_004BBCA0, Low) == 0x18);
GG_STATIC_ASSERT(offsetof(ZBufferLike_004BBCA0, High) == 0x1C);
GG_STATIC_ASSERT(offsetof(ZBufferLike_004BBCA0, Size) == 0x20);
GG_STATIC_ASSERT(offsetof(ZBufferLike_004BBCA0, Extent) == 0x24);
GG_STATIC_ASSERT(offsetof(ZBufferLike_004BBCA0, unknown_26) == 0x26);
GG_STATIC_ASSERT(offsetof(ZBufferLike_004BBCA0, Stride) == 0x28);
GG_STATIC_ASSERT(sizeof(ZBufferLike_004BBCA0) == 0x2C);


// FUNCTION: GAMEMD 0x4C1B50 (decl; reloc). fastcall: ECX = vector, returns (int)FUN_004CAC40(x*x + y*y).
struct LengthVector : public Point2D
{
    int Length() const;
};

// FUNCTION: GAMEMD 0x4CAC40 (decl; LIBRARY). cdecl square root wrapper: returns 0.0 for non-positive input
// (compares against the float at 0x7E1748). Takes the double on the stack, result in ST0.
double __cdecl FUN_004CAC40(double value);

static inline void StepRowUp(unsigned short*& zp, int step, ZBufferLike_004BBCA0* zb)
{
    zp += step;
    if (step <= 0) {
        if (zp < zb->Low)
            zp = (unsigned short*)((char*)zp + zb->Size);
    } else if (zp >= zb->High)
        zp = (unsigned short*)((char*)zp - zb->Size);
}

static inline void StepColumn(unsigned short*& zp, ZBufferLike_004BBCA0* zb)
{
    zp += 1;
    if (zp >= zb->High)
        zp = (unsigned short*)((char*)zp - zb->Size);
}

static inline void Brighten(unsigned short* pixel, int brightness)
{
    unsigned short old = *pixel;
    unsigned char c0 = (old >> gg_b_translucent_pixel_format.pos0) << gg_b_translucent_pixel_format.loss0;
    unsigned char c2 = (old >> gg_b_translucent_pixel_format.pos2) << gg_b_translucent_pixel_format.loss2;
    unsigned char c1 = (old >> gg_b_translucent_pixel_format.pos1) << gg_b_translucent_pixel_format.loss1;
    int r = c0 + ((c0 * brightness) >> 8);
    int g = c2 + ((c2 * brightness) >> 8);
    int b = c1 + ((c1 * brightness) >> 8);
    if (b > 255)
        b = 255;
    if (g > 255)
        g = 255;
    if (r > 255)
        r = 255;
    *pixel = ((r >> gg_b_translucent_pixel_format.loss0) << gg_b_translucent_pixel_format.pos0) |
             ((g >> gg_b_translucent_pixel_format.loss2) << gg_b_translucent_pixel_format.pos2) |
             ((b >> gg_b_translucent_pixel_format.loss1) << gg_b_translucent_pixel_format.pos1);
}

// FUNCTION: GAMEMD 0x4BBCA0
// The base declaration keeps seven ints (retail RET 0x1c), so the typed values are recovered by casts:
// (RectangleStruct* clip, Point2D* from, Point2D* to, int brightness, int zFrom, int zTo, bool writeZ).
bool DSurface::unknown_38(RectangleStruct* clip, Point2D* from, Point2D* to, int brightness, int zFrom, int zTo, bool writeZ)
{
    RectangleStruct scratch;
    RectangleStruct* surfaceRect = &GetRect();
    RectangleStruct bounds = *RectIntersect(&scratch, clip, surfaceRect, 0, 0);
    if (bounds.Width == 0 && bounds.Height == 0)
        return false;

    Point2D p0;
    Point2D p1;
    p0.X = from->X + bounds.X;
    p0.Y = from->Y + bounds.Y;
    p1.X = to->X + bounds.X;
    p1.Y = to->Y + bounds.Y;
    if (p0.X > p1.X) {
        Point2D t = p0;
        p0 = p1;
        p1 = t;
        int swapZ = zFrom;
        zFrom = zTo;
        zTo = swapZ;
    }

    int ox = p0.X;
    int oy = p0.Y;
    int ex = p1.X;
    int ey = p1.Y;
    if (!ClipLine(&p0, &p1, &bounds))
        return false;

    if (p1.X != ex || p1.Y != ey) {
        LengthVector whole;
        whole.X = ox - ex;
        whole.Y = oy - ey;
        LengthVector part;
        part.X = ox - p1.X;
        part.Y = oy - p1.Y;
        int wholeLength = whole.Length();
        int partLength = part.Length();
        int dz = abs((int)((double)partLength / wholeLength * (zFrom - zTo)));
        if (zFrom < zTo)
            zTo = dz + zFrom;
        else
            zTo = zFrom - dz;
    }
    if (p0.X != ox || p0.Y != oy) {
        double partLength = FUN_004CAC40((double)(p0.X - ex) * (p0.X - ex) + (double)(p0.Y - ey) * (p0.Y - ey));
        int partLen = (int)partLength;
        int wholeLen = (int)FUN_004CAC40((double)(ox - ex) * (ox - ex) +
                                 (double)(oy - ey) * (oy - ey));
        int dz = abs((int)(partLen / (double)wholeLen * (zFrom - zTo)));
        if (zTo > zFrom)
            zFrom = zTo - dz;
        else
            zFrom = dz + zTo;
    }

    int bytesPerPixel = GetBytesPerPixel();
    unsigned char* row = (unsigned char*)Lock(p0);
    ZBufferLike_004BBCA0* zb = ((ZBufferLike_004BBCA0*)gg_rle_zwrap_global);
    if (!zb || !row)
        return false;

    // The entry loads ECX from 0x887644 and directly calls 0x7BD130.
    unsigned short* zp = (unsigned short*)((AlphaBuffer*)gg_rle_zwrap_global)->GetBuffer(p0.X, p0.Y - zb->Top);
    int zRowStep = zb->Stride;
    int zCur = (unsigned short)(zb->Extent + zb->Top) - p0.Y - bounds.Y + zFrom;
    int zRowDir = -1;

    int dx = p1.X - p0.X;
    int dy = p1.Y - p0.Y;
    int dz = zTo - zFrom;
    int pitch = GetPitch();
    if (dy < 0) {
        pitch = -pitch;
        zRowStep = -zRowStep;
        zRowDir = 1;
    }
    int absDy = abs(dy);
    int zSign = 1;
    if (dz < 0)
        zSign = -1;
    int absDz = abs(dz);
    int xOffset = 0;

    if (dx < absDz && absDy < absDz) {
        int errY = -absDz;
        int errX = -absDz;
        for (int n = absDz; n > 0; n--) {
            errY += absDy * 2;
            errX += dx * 2;
            if ((unsigned short)zCur < *zp) {
                Brighten((unsigned short*)(row + xOffset), brightness);
                if (writeZ)
                    *zp = (unsigned short)zCur;
            }
            if (errY > 0) {
                row += pitch;
                errY -= absDz * 2;
                StepRowUp(zp, zRowStep, zb);
                zCur += zRowDir;
            }
            if (errX > 0) {
                StepColumn(zp, zb);
                xOffset += 2;
                errX -= absDz * 2;
            }
            zCur += zSign;
        }
    } else if (absDy < dx) {
        int errZ = -dx;
        int errY = absDy * 2 - dx;
        for (int x = 0; x < dx; x++) {
            errZ += absDz * 2;
            if ((unsigned short)zCur < *zp) {
                Brighten((unsigned short*)(row + x * 2), brightness);
                if (writeZ)
                    *zp = (unsigned short)zCur;
            }
            if (errY > 0) {
                row += pitch;
                errY -= dx * 2;
                StepRowUp(zp, zRowStep, zb);
                zCur += zRowDir;
            }
            if (errZ > 0) {
                zCur += zSign;
                errZ -= dx * 2;
            }
            StepColumn(zp, zb);
            errY += absDy * 2;
        }
    } else {
        int errX = dx * 2 - absDy;
        int errZ = -absDy;
        for (int n = absDy; n > 0; n--) {
            errZ += absDz * 2;
            if ((unsigned short)zCur < *zp) {
                Brighten((unsigned short*)(row + xOffset), brightness);
                if (writeZ)
                    *zp = (unsigned short)zCur;
            }
            if (errX > 0) {
                StepColumn(zp, zb);
                xOffset += 2;
                errX -= absDy * 2;
            }
            if (errZ > 0) {
                zCur += zSign;
                errZ -= absDy * 2;
            }
            errX += dx * 2;
            row += pitch;
            StepRowUp(zp, zRowStep, zb);
            zCur += zRowDir;
        }
    }
    Unlock();
    return true;
}
