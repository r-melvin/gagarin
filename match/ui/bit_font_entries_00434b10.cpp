// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Full retail body 0x434B40..0x434B8F was validated from its entry with
//   Ghidra/REA. It calls the BitFont entries 0x4348F0/0x434110/0x434120/
//   0x434990 and returns x unchanged when the first argument is null.
#include "bit_font_entries_00434b10.h"

// FUNCTION: GAMEMD 0x434B10
void BitText_00434B10_View::FUN_00434B10()
{
    this->Vptr = &VT_007E3A80;
    BitFont_00434B10* previous = DAT_0089C4D0;
    delete previous;
    if (previous == DAT_0089C4D0) {
        DAT_0089C4D0 = 0;
    }
}

// FUNCTION: GAMEMD 0x434B40
// PARTIAL: 32/35 instructions (91.4%; 28 exact, 4 relocation-normalised,
// 3 differing). The only delta is the compiler's order for loading the two
// remaining stack arguments relative to pushing the -1 argument.
int __stdcall FUN_00434B40(BitFont_00434B40* font,
    Surface* surface, int glyph, int x, int y)
{
    int glyphValue;
    int yValue;
    int result = x;
    if (font != 0) {
        font->Lock(surface);
        font->FUN_00434110(x);
        glyphValue = glyph;
        yValue = y;
        result = font->FUN_00434120(glyphValue, x, yValue, -1);
        font->UnLock(surface);
    }
    return result;
}

// FUNCTION: GAMEMD 0x434BF0
// Complete retail span: 0xE0 bytes, including RET immediate at 0x434CCD.
// PARTIAL: 63/87 instructions (72.4%; 52 exact, 11 relocation-normalised,
// 24 differing). The remaining differences are register/local scheduling;
// retail and candidate instruction multisets are identical.
int __stdcall FUN_00434BF0(BitFont_00434B40* font,
    Surface* surface, int first, int second, int third, int fourth)
{
    int result = 0;
    if (font != 0) {
        if (font->At_040 != 0) {
            font->At_02C = 2;
            font->Lock(surface);
            font->FUN_00434110(second);
            result = font->FUN_00434500(first, second, third, fourth, 0);
            font->UnLock(surface);
            font->Lock(surface);
            font->FUN_00434110(second + 1);
            result = font->FUN_00434500(first, second + 1, third, fourth, 0);
            font->UnLock(surface);
            font->At_02C = 1;
            return result;
        }
        font->Lock(surface);
        font->FUN_00434110(second);
        result = font->FUN_00434500(first, second, third, fourth, 0);
        font->UnLock(surface);
    }
    return result;
}
