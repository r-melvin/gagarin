// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: disassembly of 0x6907A0 (loops a UTF-16 string, calling slot 1 per character).
//
// ScoreFontClass slot 2: pixel width of a wide string, one pixel of spacing per character.
// Address index: 0x6907A0 vf_2.

#include "../_layout/score_font_class.h"

// FUNCTION: GAMEMD 0x6907A0
int ScoreFontClass::vf_2(const unsigned short* text)
{
    int width = 0;
    unsigned short ch = *text;
    while (ch != 0) {
        text++;
        width += vf_1(ch) + 1;
        ch = *text;
    }
    return width;
}
