// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | original
// Entry-point retail disassembly and Rea establish the two drawing passes.
#include "font_shadow_00435340.h"
// Keep the shadow-colour read in its own short local. This ordinary C++
// formulation was found by the permuter; the VC6 byte oracle is authoritative.
// FUNCTION: GAMEMD 0x435340
bool TextEngine_00435340::FUN_00435340(Font_00435340* font, int context,
    const unsigned short* text, int x, int y, int a, int b, int c, int d, int e)
{
    short shadowColor;
    if (!font) return false;
    font->SetValue(x);
    shadowColor = font->unknown_26;
    short oldColor = font->SwapColor(shadowColor);
    Print(font, context, text, x + 1, y + 1, a, b, c, d, e);
    font->SwapColor(oldColor);
    return Print(font, context, text, x, y, a, b, c, d, e);
}
