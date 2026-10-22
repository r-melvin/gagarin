// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Both functions were read from their complete entry-bounded retail bodies:
//   0x434CD0 (RET 0x28 at 0x435310, jump table 0x435314/0x435324) and 0x4353F0
//   (RET 0x28 at 0x4354C0). Neither reads ECX for its own use; 0x4353F0 only
//   forwards its ECX to 0x434CD0, so the receiver is an unidentified object
//   with the placeholder type below. The first stack argument is the BitFont
//   (it is the ECX of the 0x4348F0/0x434110/0x434120/0x434990 helper calls).
//   BitFont members come from renderer/bit_font.h.
#ifndef GG_MATCH_UI_BIT_FONT_PRINT_METHODS_H
#define GG_MATCH_UI_BIT_FONT_PRINT_METHODS_H

#include "../renderer/bit_font.h"

struct Obj_00434CD0
{
    // FUNCTION: GAMEMD 0x434CD0
    // Draws text, wrapping at maxWidth and stopping at maxHeight.
    bool FUN_00434CD0(BitFont* font, Surface* surface, const unsigned short* text,
                      int x, int y, int maxWidth, int maxHeight, int alignment,
                      int fadeStart, int fadeLength);

    // FUNCTION: GAMEMD 0x4353F0
    bool FUN_004353F0(BitFont* font, Surface* surface, const unsigned short* text,
                      int x, int y, int maxWidth, int maxHeight, int alignment,
                      int fadeStart, int fadeLength);
};

#endif  // GG_MATCH_UI_BIT_FONT_PRINT_METHODS_H
