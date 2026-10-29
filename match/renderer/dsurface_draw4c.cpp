// SPDX-License-Identifier: GPL-3.0-or-later
// Frozen milestone flag set: /O2 /DNDEBUG /Gy without /GX.
// Provenance: own-binary-via-Ghidra. DSurface (RTTI .?AVDSurface@@, vtable 0x7E85D4) slot +0x4C, a | YRpp-cross-check
// patterned line draw on 16-bit surfaces that is gated by a second ring-buffer layer (global 0x87E8A4). The span
// is CFG-closed from the entry disassembly.
// This readable candidate remains partial; the source technique behind the unmatched retail instructions
// is not established.
#include "dsurface_class.h"
#include "drawing.h"
#include "../render/blitters/b_shared_alpha.h"

// The layer object behind global 0x87E8A4 (same object the blitter module calls the alpha buffer).
// Offsets read at 0x4C07E9 (+4), 0x4C07FE (+0x28), 0x4C0890 (+0x1C), 0x4C089F (+0x18), 0x4C089A (+0x20).
struct RingLayer
{
    unsigned char unknown_00[4];
    int OriginY;           // +0x04
    unsigned char unknown_08[0x10];
    unsigned short* Low;   // +0x18
    unsigned short* High;  // +0x1C
    int WrapBytes;         // +0x20
    unsigned char unknown_24[4];
    int RowStride;         // +0x28 (elements)

};
GG_STATIC_ASSERT(offsetof(RingLayer, OriginY) == 0x04);
GG_STATIC_ASSERT(offsetof(RingLayer, Low) == 0x18);
GG_STATIC_ASSERT(offsetof(RingLayer, High) == 0x1C);
GG_STATIC_ASSERT(offsetof(RingLayer, WrapBytes) == 0x20);
GG_STATIC_ASSERT(offsetof(RingLayer, RowStride) == 0x28);


static inline unsigned short* Wrap(unsigned short* p, int stride)
{
    RingLayer* layer = ((RingLayer*)gg_blit_alpha_wrap_global);
    if (stride > 0) {
        if (p >= layer->High)
            p = (unsigned short*)((char*)p - layer->WrapBytes);
    } else {
        if (p < layer->Low)
            p = (unsigned short*)((char*)p + layer->WrapBytes);
    }
    return p;
}

static inline int WrapPhase(int phase)
{
    if (phase < 0)
        phase += 16;
    if (phase >= 16)
        phase -= 16;
    return phase;
}

// FUNCTION: GAMEMD 0x4C0750
// Arguments (evidence: 0x4C0750 prologue loads [ESP+0x24], [ESP+0x38]; 0x4C087A reads the colour word at
// [ESP+0x3C]; 0x4C086E the pattern at [ESP+0x40]; the phase at [ESP+0x44]; the invert flag at [ESP+0x48]):
// (Point2D* from, Point2D* to, unsigned short color, unsigned char* pattern, int phase, bool invert).
// Returns the phase after
// the last pixel, or 0 when the surface is not 16-bit.
int DSurface::unknown_4C(Point2D* from, Point2D* to, unsigned short color, unsigned char* pattern, int phase, bool invert)
{
    int x1 = from->X;
    int y1 = from->Y;
    int x2 = to->X;
    int y2 = to->Y;
    int phaseStep = 1;

    if (GetBytesPerPixel() != 2)
        return 0;
    if (x1 > x2) {
        int t = x1;
        x1 = x2;
        x2 = t;
        t = y1;
        y1 = y2;
        y2 = t;
        phaseStep = -1;
    }

    unsigned short* layerPtr = (unsigned short*)((ABuffer*)gg_blit_alpha_wrap_global)->GetBuffer(x1, y1 - ((RingLayer*)gg_blit_alpha_wrap_global)->OriginY);
    int stride = ((RingLayer*)gg_blit_alpha_wrap_global)->RowStride;
    if (y1 > y2)
        stride = -stride;

    Point2D origin;
    origin.X = x1;
    origin.Y = y1;
    unsigned short* dst = (unsigned short*)Lock(origin);
    if (!dst)
        return phase;

    int dx = x2 - x1;
    int dy = y2 - y1;
    int rowBytes = (int)GetPitch();
    if (dy < 0)
        rowBytes = -rowBytes;

    if (y1 == y2) {
        for (int n = dx + 1; n > 0; n--) {
            phase = WrapPhase(phase);
            if (pattern[phase] && ((*layerPtr == 0) == invert))
                *dst = color;
            layerPtr = Wrap(layerPtr + 1, stride);
            dst++;
            phase += phaseStep;
        }
    } else if (x1 == x2) {
        for (int n = (dy < 0 ? -dy : dy) + 1; n > 0; n--) {
            phase = WrapPhase(phase);
            if (pattern[phase] && ((*layerPtr == 0) == invert))
                *dst = color;
            dst = (unsigned short*)((char*)dst + rowBytes);
            layerPtr = Wrap(layerPtr + stride, stride);
            phase += phaseStep;
        }
    } else {
        int ady = dy < 0 ? -dy : dy;
        if (dx > ady) {
            int err = -dx;
            int i = 0;
            for (int n = 0; n < dx; n++) {
                err += ady * 2;
                phase = WrapPhase(phase);
                if (pattern[phase] && ((*layerPtr == 0) == invert))
                    dst[i] = color;
                if (err > 0) {
                    dst = (unsigned short*)((char*)dst + rowBytes);
                    layerPtr = Wrap(layerPtr + stride, stride);
                    err -= dx * 2;
                }
                layerPtr = Wrap(layerPtr + 1, stride);
                i++;
                phase += phaseStep;
            }
        } else {
            int err = -ady;
            char* row = (char*)dst;
            int bytes = 0;
            for (int n = 0; n < ady; n++) {
                err += dx * 2;
                phase = WrapPhase(phase);
                if (pattern[phase] && ((*layerPtr == 0) == invert))
                    *(unsigned short*)(row + bytes) = color;
                if (err > 0) {
                    layerPtr = Wrap(layerPtr + 1, stride);
                    bytes += 2;
                    err -= ady * 2;
                }
                layerPtr = Wrap(layerPtr + stride, stride);
                row += rowBytes;
                phase += phaseStep;
            }
        }
    }
    Unlock();
    return phase;
}
