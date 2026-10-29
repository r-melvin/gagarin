// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: retail gamemd.exe v1.001 disassembly at 0x5D30C0, 0x5D3170 and 0x5D31D0
//   (the font's character-width slot and its two text measuring helpers).
//
// Address index: 0x5D30C0 0x5D3170 0x5D31D0

#include <windows.h>
#include <string.h>
#include "msanim_family_methods.h"

// FUNCTION: GAMEMD 0x5D31D0 (partial 86.4%: retail folds the glyph offset as ADD -0x21 and builds the frame index in ECX ahead of the rectangle pointer)
// Width of one character: a space is eight, anything printable is its glyph's
// frame width plus one, anything else is nothing.
int MSFont::CharWidth(wchar_t ch)
{
    char c = (char)ch;
    CharToOemBuffA(&c, &c, 1);
    if (c == ' ')
        return 8;
    if ((unsigned char)c > ' ') {
        int glyph = (unsigned char)c + -0x21;
        if (glyph <= 0)
            glyph = 0;
        else if (glyph >= 0xD8)
            glyph = 0xD8;
        MSRect frame;
        return Glyphs->GetFrameRect(&frame, glyph * 3 + 2)->Width + 1;
    }
    return 0;
}

// FUNCTION: GAMEMD 0x5D3170
// Widest line of a text; a line ends at a newline or the terminator.
int MSFont::LineWidth(const wchar_t* text)
{
    int widest = 0;
    if (text != 0) {
        do {
            int width = 0;
            wchar_t ch = *text;
            while (ch != 0 && ch != '\n') {
                text++;
                width += CharWidth(ch);
                ch = *text;
            }
            if (*text == '\n')
                text++;
            if (width > widest)
                widest = width;
        } while (*text != 0);
    }
    return widest;
}

// FUNCTION: GAMEMD 0x5D30C0
// Measure a text into a rectangle at the origin: the widest line plus the lead
// across, one line height per line down; an empty text measures nothing.
void MSFont::Measure(const wchar_t* text, MSRect* out)
{
    int widest = 0;
    if (text != 0 && wcslen(text) != 0) {
        int height = LineHeight;
        do {
            int width = 0;
            wchar_t ch = *text;
            while (ch != 0 && ch != '\n') {
                text++;
                width += CharWidth(ch);
                ch = *text;
            }
            if (width > widest)
                widest = width;
            if (*text == '\n') {
                text++;
                height += LineHeight;
            }
        } while (*text != 0);
        int across = Lead + widest;
        out->Height = height;
        out->Width = across;
        out->X = 0;
        out->Y = 0;
        return;
    }
    out->X = 0;
    out->Y = 0;
    out->Width = 0;
    out->Height = 0;
}
