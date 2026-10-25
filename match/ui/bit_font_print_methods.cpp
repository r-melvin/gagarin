// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   See bit_font_print_methods.h. The colour-fade path builds a 3-byte colour
//   (0x4355B0), blends it towards the colour at 0xA80220 (0x6612C0) and packs
//   it with Drawing::RGB_To_Int (0x4355D0) through the six pixel-format shift
//   globals at 0x8A0DD0..0x8A0DE4.
#include "../renderer/pixel_shift_view.h"
#include "bit_font_print_methods.h"
#include "../renderer/drawing.h"
#include "../core/small_struct_ctor_methods.h"

// 3-byte colour with the blend routine at 0x6612C0 (thiscall; alpha and the
// target colour pointer on the stack).
struct BlendColor : Obj_004355B0
{
    BlendColor(unsigned char r, unsigned char g, unsigned char b) : Obj_004355B0(r, g, b) {}
    // FUNCTION: GAMEMD 0x6612C0 (decl; reloc)
    void FUN_006612C0(int alpha, const Obj_004355B0* target);
};

// GLOBAL: GAMEMD 0xA80220 -- colour the fade blends towards.
extern Obj_004355B0 DAT_00A80220;

// Colour for the glyph being drawn: the font colour, or while inside the fade
// window the font colour blended towards DAT_00A80220.
static __forceinline int FadedColor(unsigned short color, int remaining, int step, int fadeLength)
{
    unsigned char red   = (unsigned char)(color >> gg_b_translucent_pixel_format.pos0 << gg_b_translucent_pixel_format.loss0);
    unsigned char green = (unsigned char)(color >> gg_b_translucent_pixel_format.pos1 << gg_b_translucent_pixel_format.loss1);
    unsigned char blue  = (unsigned char)(color >> gg_b_translucent_pixel_format.pos2 << gg_b_translucent_pixel_format.loss2);
    BlendColor rgb(red, green, blue);
    rgb.FUN_006612C0(255 / fadeLength * step, &DAT_00A80220);
    return Drawing::RGB_To_Int(rgb.unknown_00, rgb.unknown_01, rgb.unknown_02);
}

// Draws [from, to) one glyph at a time. Returns false when the fade window
// ends the text early.
static __forceinline bool DrawRun(BitFont* font, const unsigned short* from, const unsigned short* to,
                           int& penX, int penY, int& drawIndex, int fadeStart, int fadeLength)
{
    unsigned short color = font->unknown_24;
    while (from < to) {
        ++drawIndex;
        int pixel = color;
        if (fadeStart != 0) {
            if (drawIndex >= fadeStart)
                return false;
            int remaining = fadeStart - drawIndex - 1;
            if (remaining < fadeLength)
                pixel = FadedColor(color, remaining, drawIndex - fadeStart + fadeLength + 1, fadeLength);
        }
        if (pixel == -1)
            return false;
        penX = font->FUN_00434120(*from++, penX, penY, pixel);
    }
    return true;
}

// Left edge of a line of lineWidth pixels inside maxWidth: centred (alignment
// bit 0), right-aligned (bit 1) or flush left.
static __forceinline int LineStart(int x, int maxWidth, int lineWidth, int alignment)
{
    int offset = 0;
    if (maxWidth > lineWidth) {
        if (alignment & 1)
            offset = (maxWidth - lineWidth) / 2;
        else if (alignment & 2)
            offset = maxWidth - lineWidth;
    }
    return x + offset;
}

// FUNCTION: GAMEMD 0x434CD0
bool Obj_00434CD0::FUN_00434CD0(BitFont* font, Surface* surface, const unsigned short* text,
                                int x, int y, int maxWidth, int maxHeight, int alignment,
                                int fadeStart, int fadeLength)
{
    if (!font || !text)
        return false;

    font->Lock(surface);
    font->FUN_00434110(x);

    const unsigned short* drawFrom = text;
    const unsigned short* wordEnd = 0;
    unsigned short color = font->unknown_24;
    int lineWidth = 0;
    int wordWidth = 0;
    int glyphCount = 0;
    int linesHeight = 0;
    int drawIndex = 0;
    int penX;
    unsigned short ch = *text;

    while (ch != 0) {
        switch (ch) {
        case '\t':
            lineWidth += font->unknown_28;
            lineWidth -= lineWidth % font->unknown_28;
            break;
        case '\n':
        case '\r':
            if (ch == '\r') {
                ++drawFrom;
                break;
            }
            penX = LineStart(x, maxWidth, lineWidth, alignment);
            if (drawFrom < text && !DrawRun(font, drawFrom, text, penX, y, drawIndex, fadeStart, fadeLength))
                goto done;
            linesHeight += font->unknown_1C;
            if (maxHeight != 0 && linesHeight >= maxHeight)
                goto done;
            y += font->unknown_1C;
            ++drawFrom;
            lineWidth = 0;
            glyphCount = 0;
            break;
        case ' ':
            wordWidth = lineWidth;
            wordEnd = text;
            // fall through: a space is measured like any other glyph
        default: {
            unsigned char* bitmap = font->GetCharacterBitmap(ch);
            if (!bitmap)
                bitmap = font->GetCharacterBitmap('?');
            if (!bitmap)
                break;
            ++glyphCount;
            int advance = font->unknown_2C + *bitmap;
            lineWidth += advance;
            if (maxWidth == 0 || lineWidth <= maxWidth)
                break;
            if (wordEnd) {
                if (glyphCount > 1) {
                    lineWidth = wordWidth;
                    text = wordEnd;
                }
            } else if (glyphCount > 1) {
                lineWidth -= advance;
                --text;
            }
            penX = LineStart(x, maxWidth, lineWidth, alignment);
            if (drawFrom < text && !DrawRun(font, drawFrom, text, penX, y, drawIndex, fadeStart, fadeLength))
                goto done;
            if (text == wordEnd) {
                wordEnd = 0;
                ++drawFrom;
            }
            linesHeight += font->unknown_1C;
            if (maxHeight != 0 && linesHeight >= maxHeight)
                goto done;
            y += font->unknown_1C;
            lineWidth = 0;
            glyphCount = 0;
            break;
        }
        }
        ch = *++text;
    }

    penX = LineStart(x, maxWidth, lineWidth, alignment);
    if (drawFrom < text)
        DrawRun(font, drawFrom, text, penX, y, drawIndex, fadeStart, fadeLength);

done:
    font->UnLock(surface);
    return true;
}

// FUNCTION: GAMEMD 0x4353F0
bool Obj_00434CD0::FUN_004353F0(BitFont* font, Surface* surface, const unsigned short* text,
                                int x, int y, int maxWidth, int maxHeight, int alignment,
                                int fadeStart, int fadeLength)
{
    if (font) {
        font->FUN_00434110(x);
        if (!font->unknown_40)
            return FUN_00434CD0(font, surface, text, x, y, maxWidth, maxHeight, alignment, fadeStart, fadeLength);
        font->unknown_2C = 2;
        FUN_00434CD0(font, surface, text, x, y, maxWidth, maxHeight, alignment, fadeStart, fadeLength);
        bool result = FUN_00434CD0(font, surface, text, x + 1, y, maxWidth, maxHeight,
                                   alignment, fadeStart, fadeLength);
        font->unknown_2C = 1;
        return result;
    }
    return false;
}
