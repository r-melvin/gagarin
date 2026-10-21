// SPDX-License-Identifier: GPL-3.0-or-later
// VC6FLAGS: /nologo /c /O2 /DNDEBUG /Gy
// Frozen milestone flag set: /O2 /DNDEBUG /Gy without /GX.
// Provenance: own-binary-via-Ghidra. DSurface (RTTI .?AVDSurface@@, vtable 0x7E85D4)
// rectangle fill and Copy_From overrides that go through the DirectDraw Blt; spans are CFG-closed.
#include <string.h>
#include "dsurface_class.h"
#include "../render/blitters/r_shared_zwrap.h"
#include "../render/blitters/b_shared_alpha.h"

// FUNCTION: GAMEMD 0x4BB080
bool DSurface::CopyFromPart(RectangleStruct* dest, Surface* src, RectangleStruct* srcRect, bool a, bool b)
{
    return CopyFrom(&GetRect(), dest, src, &src->GetRect(), srcRect, a, b);
}

// FUNCTION: GAMEMD 0x4BB5F0
bool DSurface::FillRect(RectangleStruct* rect, unsigned int color)
{
    return DSurface::FillRectEx(&GetRect(), rect, color);
}

// FUNCTION: GAMEMD 0x4BB620
bool DSurface::FillRectEx(RectangleStruct* clip, RectangleStruct* rect, unsigned int color)
{
    if (!DDSurf)
        return false;
    if (rect->Width <= 0 || rect->Height <= 0)
        return false;
    if (DAT_008205D4 && !IsLocked() && DDSurf->lpVtbl->GetBltStatus(DDSurf, 1) == 0) {
        if (!DAT_0089F978 && !DAT_00A8ED80)
            return false;
        if (!Recover())
            return false;
        RectangleStruct scratch;
        RectangleStruct* surfaceRect = &GetRect();
        RectangleStruct visible = *RectIntersect(&scratch, clip, surfaceRect, 0, 0);
        RectangleStruct target = *rect;
        target.X += clip->X;
        target.Y += clip->Y;
        target = *RectIntersect(&scratch, &target, &visible, 0, 0);
        if (target.Width <= 0 || target.Height <= 0)
            return false;
        DDRect bounds;
        bounds.left = target.X;
        bounds.top = target.Y;
        bounds.right = target.X + target.Width;
        bounds.bottom = target.Y + target.Height;
        DDBltFx fx;
        memset(&fx, 0, sizeof(fx));
        fx.dwSize = sizeof(fx);
        fx.dwFillColor = color;
        return DDSurf->lpVtbl->Blt(DDSurf, &bounds, 0, 0, 0x1000400, &fx) == 0;
    }
    return XSurface::FillRectEx(clip, rect, color);
}

// FUNCTION: GAMEMD 0x4BB830
// Alpha-blended rectangle fill on 16-bit surfaces. The base declaration's argument types are placeholders: the
// second argument points at a 3-byte colour and the third is an opacity percentage (clamped to 100).
bool DSurface::unknown_1C(RectangleStruct* rect, RectangleStruct* colorBytes, int percent)
{
    if (GetBytesPerPixel() < 2)
        return false;
    if (rect->Width <= 0 || rect->Height <= 0)
        return false;

    RectangleStruct scratch;
    RectangleStruct* surfaceRect = &GetRect();
    RectangleStruct area = *RectIntersect(&scratch, surfaceRect, rect, 0, 0);
    if (area.Width <= 0 || area.Height <= 0)
        return false;

    unsigned short maskA = 0xFF;
    maskA >>= gg_b_translucent_pixel_format.loss0;
    maskA <<= gg_b_translucent_pixel_format.pos0;
    unsigned short maskC = 0xFF;
    maskC >>= gg_b_translucent_pixel_format.loss2;
    maskC <<= gg_b_translucent_pixel_format.pos2;
    unsigned short maskB = 0xFF;
    maskB >>= gg_b_translucent_pixel_format.loss1;
    maskB <<= gg_b_translucent_pixel_format.pos1;

    Point2D origin;
    unsigned char* buffer = (unsigned char*)Lock(*((PointCopier*)&area)->CopyTo(&origin));
    if (!buffer)
        return false;

    unsigned int opacity = percent;
    if (opacity > 100)
        opacity = 100;
    unsigned int weight = opacity * 255 / 100;
    unsigned short inverse = 255 - weight;

    const unsigned char* rgb = (const unsigned char*)colorBytes;
    unsigned char byte2 = rgb[2];
    byte2 >>= gg_b_translucent_pixel_format.loss1;
    unsigned short part2 = byte2;
    unsigned char byte1 = rgb[1];
    byte1 >>= gg_b_translucent_pixel_format.loss2;
    unsigned short part1 = byte1;
    unsigned char byte0 = rgb[0];
    byte0 >>= gg_b_translucent_pixel_format.loss0;
    unsigned short part0 = byte0;
    unsigned short color = (part2 << gg_b_translucent_pixel_format.pos1) | (part1 << gg_b_translucent_pixel_format.pos2) |
                           (part0 << gg_b_translucent_pixel_format.pos0);

    for (int y = 0; y < area.Height; y++) {
        unsigned short* pixel = (unsigned short*)buffer + ((int)GetPitch() / 2) * y;
        for (int x = 0; x < area.Width; x++) {
            unsigned short old = *pixel;
            *pixel++ = ((((maskA & old) * inverse + (maskA & color) * weight) >> 8) & maskA) |
                       ((((maskC & old) * inverse + (maskC & color) * weight) >> 8) & maskC) |
                       ((((maskB & old) * inverse + (maskB & color) * weight) >> 8) & maskB);
        }
    }
    Unlock();
    return true;
}
