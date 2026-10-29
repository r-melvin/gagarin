// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Both functions were read from their complete entry-bounded retail bodies:
//   0x434CD0 (RET 0x28 at 0x435310, jump table 0x435314/0x435324) and 0x4353F0
//   (RET 0x28 at 0x4354C0). Neither reads ECX for its own use; the producer
//   at 0x52BBAA stores a constructed BitText receiver at 0x89C4B8.
//   The first stack argument is the BitFont
//   (it is the ECX of the 0x4348F0/0x434110/0x434120/0x434990 helper calls).
//   BitFont members come from renderer/bit_font.h.
#ifndef GG_MATCH_UI_BIT_FONT_PRINT_METHODS_H
#define GG_MATCH_UI_BIT_FONT_PRINT_METHODS_H

#include "bit_text_ctor_methods.h"
// GLOBAL: GAMEMD 0x89C4B8
extern BitText* DAT_0089C4B8;
#endif  // GG_MATCH_UI_BIT_FONT_PRINT_METHODS_H
