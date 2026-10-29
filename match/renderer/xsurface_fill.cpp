// SPDX-License-Identifier: GPL-3.0-or-later
// ^ no /GX: paired probe on the XSurface scalar deleting destructor (0x4115A0): with /GX VC6 keeps a
// separate ~XSurface call (0/12), without it the destructor inlines and matches (12/12). The Blit*
// stack locals of 0x7BBB90 also carry no unwind frame in retail.
// Provenance: own-binary-via-Ghidra. XSurface::FillRectEx (slot +0x10), the | YRpp-cross-check
// clipped solid rectangle fill used by Fill/FillRect.
#include <string.h>
#include "surface_class.h"

// FUNCTION: GAMEMD 0x7BB050
bool XSurface::FillRectEx(RectangleStruct* clip, RectangleStruct* rect, unsigned int color)
{
    if (rect->Width <= 0 || rect->Height <= 0)
        return false;

    RectangleStruct tmp1;
    RectangleStruct surface = *RectIntersect(&tmp1, clip, &GetRect(), 0, 0);

    Point2D origin;
    origin.X = clip->X + rect->X;
    origin.Y = rect->Y + clip->Y;
    RectangleStruct built;
    RectangleStruct target = *built.FromPointSize(&origin, rect->Width, rect->Height);

    RectangleStruct tmp2;
    RectangleStruct area = *RectIntersect(&tmp2, &surface, &target, 0, 0);
    if (area.Width <= 0 || area.Height <= 0)
        return false;

    int pitch = GetPitch();
    int row;
    int i;
    unsigned char* line = (unsigned char*)Lock(*((PointCopier*)&area)->CopyTo(&origin));
    if (!line)
        return false;

    if (GetBytesPerPixel() == 1) {
        for (row = 0; row < area.Height; row++) {
            memset(line, (unsigned char)color, area.Width);
            line += pitch;
        }
    } else {
        unsigned short value = (unsigned short)color;
        int width = area.Width;
        unsigned int align = (unsigned int)line & 3;
        unsigned int both = ((unsigned int)value << 16) | value;
        if (align == 0) {
            int pairs = width >> 1;
            for (row = 0; row < area.Height; row++) {
                unsigned int* dst = (unsigned int*)line;
                for (i = 0; i < pairs; i++)
                    *dst++ = both;
                if (width & 1)
                    *(unsigned short*)dst = value;
                line += pitch;
            }
        } else if (align == 2) {
            if (width < 2) {
                if (width == 1) {
                    for (row = 0; row < area.Height; row++) {
                        *(unsigned short*)line = value;
                        line += pitch;
                    }
                }
            } else {
                int pairs = (width - 1) >> 1;
                for (row = 0; row < area.Height; row++) {
                    *(unsigned short*)line = value;
                    unsigned int* dst = (unsigned int*)(line + 2);
                    for (i = 0; i < pairs; i++)
                        *dst++ = both;
                    if ((width - 1) & 1)
                        *(unsigned short*)dst = value;
                    line += pitch;
                }
            }
        } else {
            for (row = 0; row < area.Height; row++) {
                unsigned int* dst = (unsigned int*)line;
                for (i = 0; i < (width >> 1); i++)
                    *dst++ = both;
                for (i = 0; i < (width & 1); i++) {
                    *(unsigned short*)dst = value;
                    dst = (unsigned int*)((char*)dst + 2);
                }
                line += pitch;
            }
        }
    }
    Unlock();
    return true;
}
