// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary; retail entry disassembly 4354D0, 435500, 435530.
// Retail allocation at 0x4354D0 has no exception-unwind frame; /GX adds one.
#include "bit_font_singleton_methods.h"
// FUNCTION: GAMEMD 0x4354D0
void CreateBitFontSingleton()
{
    // STRING: GAMEMD 0x818B98
    TheGameFont = new BitFont("GAME.FNT");
}
// FUNCTION: GAMEMD 0x435500
void DestroyBitFontSingleton()
{
    BitFont* font = TheGameFont;
    delete font;
    if (font == TheGameFont) TheGameFont = 0;
}
// FUNCTION: GAMEMD 0x435530
void __stdcall DestroyBitFontIfSingleton(BitFont* font)
{
    delete font;
    if (font == TheGameFont) TheGameFont = 0;
}
