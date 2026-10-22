// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary; retail entry disassembly 4354D0, 435500, 435530.
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy
// Retail allocation at 0x4354D0 has no exception-unwind frame; /GX adds one.
#include "bit_font_singleton_methods.h"
// FUNCTION: GAMEMD 0x4354D0
void CreateBitFontSingleton()
{
    BitFontSingleton = new BitFontSingletonView(BitFontGameName);
}
// FUNCTION: GAMEMD 0x435500
void DestroyBitFontSingleton()
{
    BitFontSingletonView* font = BitFontSingleton;
    delete font;
    if (font == BitFontSingleton) BitFontSingleton = 0;
}
// FUNCTION: GAMEMD 0x435530
void __stdcall DestroyBitFontIfSingleton(BitFontSingletonView* font)
{
    delete font;
    if (font == BitFontSingleton) BitFontSingleton = 0;
}
