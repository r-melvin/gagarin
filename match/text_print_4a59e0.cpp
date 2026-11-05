// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | private-ref-cross-check
//   Text layout and print helpers in the code range 0x4A59E0-0x4A66D0 of retail gamemd.exe v1.001.
//   All of them read the shared game font (0x89C4D0). Functions are in ascending retail address order.
//   Calling conventions follow the project default (/Gr): the first two integer arguments travel in ECX and EDX.

#include "bit_text_ctor_methods.h"
#include "bit_font_print_methods.h"
#include "_layout/geometry2d.h"
#include "_layout/rgb_class.h"
#include "color_scheme_find_methods.h"
#include <stdarg.h>
#include <wchar.h>

#include "wwlib/surface/surface_class.h"
// LIBRARY: GAMEMD 0x7CA858 (decl; reloc) -- CRT vswprintf.
extern "C" int __cdecl vswprintf(unsigned short* buffer, const unsigned short* format, va_list args);

// Forward declaration of the tab-aware print defined below.
Point2D FUN_004A6360(const unsigned short* text, Surface* surface, RectangleStruct* clip, Point2D* pos,
                     int color, int background, int flags, unsigned int width, unsigned int* tabStops);



// GLOBAL: GAMEMD 0x8A0DD0..0x8A0DE4 -- the display's colour shift operands.
extern int DAT_008A0DD0;
extern int DAT_008A0DD4;
extern int DAT_008A0DD8;
extern int DAT_008A0DDC;
extern int DAT_008A0DE0;
extern int DAT_008A0DE4;
// GLOBAL: GAMEMD 0xB054D4 -- the colour scheme records.
extern ColorScheme** DAT_00B054D4;


// FUNCTION: GAMEMD 0x4A5E50
// Measure `text` wrapped at `columns` widest-glyph columns; answers the number of lines (0 without text or font).
int FUN_004A5E50(const unsigned short* text, int unknown_edx, int columns, int* width, int* height)
{
    *width = 0;
    *height = 0;
    BitFont* font = TheGameFont;
    if (text != 0 && font != 0) {
        font->FUN_00433CF0(text, width, height, font->FUN_004349B0(0x57) * columns);
        return *height / font->unknown_1C;
    }
    return 0;
}

// FUNCTION: GAMEMD 0x4A5EB0 (decl; reloc) -- prints one line of text and answers where the pen ended.
Point2D FUN_004A5EB0(const unsigned short* text, Surface* surface, RectangleStruct* clip, Point2D* pos,
                     int color, int background, int flags, int extra);

// FUNCTION: GAMEMD 0x4A6010
// Print a line in a colour scheme's colour converted to the display format.
Point2D FUN_004A6010(const unsigned short* text, Surface* surface, RectangleStruct* clip, Point2D* pos,
                     ColorScheme* scheme, int background, int flags, int extra)
{
    RGBClass rgb = scheme->unknown_308.FUN_00517440();
    int color = ((rgb.Red >> DAT_008A0DD4) << DAT_008A0DD0) | ((rgb.Green >> DAT_008A0DE4) << DAT_008A0DE0)
              | ((rgb.Blue >> DAT_008A0DDC) << DAT_008A0DD8);
    return FUN_004A5EB0(text, surface, clip, pos, color, background, flags, extra);
}

// FUNCTION: GAMEMD 0x4A60E0
// Format with vswprintf (a null format prints nothing) and print the result.
Point2D __cdecl FUN_004A60E0(const unsigned short* format, Surface* surface, RectangleStruct* clip, Point2D* pos,
                             int color, int background, int flags, ...)
{
    unsigned short buffer[0x200];
    if (format != 0) {
        va_list args;
        va_start(args, flags);
        vswprintf(buffer, format, args);
        va_end(args);
        return FUN_004A5EB0(buffer, surface, clip, pos, color, background, flags, 1);
    }
    return FUN_004A5EB0(0, surface, clip, pos, color, background, flags, 1);
}

// FUNCTION: GAMEMD 0x4A6360
// Print text that may contain tab characters: each tab-delimited piece is clipped to the room left under `width`
// and printed at the running offset; the offset then moves to the next tab stop (every 50 pixels without a table).
Point2D FUN_004A6360(const unsigned short* text, Surface* surface, RectangleStruct* clip, Point2D* pos,
                     int color, int background, int flags, unsigned int width, unsigned int* tabStops)
{
    Point2D end = *pos;
    if (text != 0) {
        unsigned short buffer[0x200];
        wcscpy(buffer, text);
        BitFont* font = TheGameFont;
        unsigned short* piece = buffer;
        unsigned int offset = 0;
        int more = 1;
        while (more) {
            if (offset >= width)
                break;
            unsigned short* tab = wcschr(piece, 9);
            if (tab != 0)
                *tab = 0;
            if (*piece != 0) {
                unsigned int used = 0;
                unsigned short* cursor = piece;
                do {
                    used += font->FUN_004349B0(*cursor++);
                } while (*cursor != 0 && used + offset < width);
                if (used + offset >= width) {
                    cursor--;
                    used -= font->FUN_004349B0(*cursor);
                    *cursor = 0;
                    more = 0;
                }
                Point2D at(pos->X + offset, pos->Y);
                end = FUN_004A5EB0(piece, surface, clip, &at, color, background, flags, 1);
                offset += used;
            }
            if (tab == 0)
                break;
            if (tabStops != 0) {
                if (offset > *tabStops) {
                    do {
                        tabStops++;
                    } while (offset > *tabStops);
                }
                offset = *tabStops;
            } else {
                offset = (offset + 1) * 50;
            }
            piece = tab + 1;
        }
    }
    return end;
}

// FUNCTION: GAMEMD 0x4A6500
// The tab-aware print in a colour scheme's colour converted to the display format.
Point2D FUN_004A6500(const unsigned short* text, Surface* surface, RectangleStruct* clip, Point2D* pos,
                     ColorScheme* scheme, int background, int flags, unsigned int width, unsigned int* tabStops)
{
    RGBClass rgb = scheme->unknown_308.FUN_00517440();
    int color = ((rgb.Red >> DAT_008A0DD4) << DAT_008A0DD0) | ((rgb.Green >> DAT_008A0DE4) << DAT_008A0DE0)
              | ((rgb.Blue >> DAT_008A0DDC) << DAT_008A0DD8);
    return FUN_004A6360(text, surface, clip, pos, color, background, flags, width, tabStops);
}

// FUNCTION: GAMEMD 0x4A66D0
// Print in the given colour, or in the colour of scheme `schemeIndex` unless that is -1.
Point2D FUN_004A66D0(const unsigned short* text, Surface* surface, RectangleStruct* clip, Point2D* pos,
                     int color, int background, int flags, int schemeIndex, int extra)
{
    if (schemeIndex == -1)
        return FUN_004A5EB0(text, surface, clip, pos, color, background, flags, extra);
    ColorScheme* scheme = DAT_00B054D4[schemeIndex];
    RGBClass rgb = scheme->unknown_308.FUN_00517440();
    int pixel = ((rgb.Green >> DAT_008A0DE4) << DAT_008A0DE0) | ((rgb.Blue >> DAT_008A0DDC) << DAT_008A0DD8)
              | ((rgb.Red >> DAT_008A0DD4) << DAT_008A0DD0);
    return FUN_004A5EB0(text, surface, clip, pos, pixel, background, flags, extra);
}
