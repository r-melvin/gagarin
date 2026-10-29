// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Read numerically off the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI at 0x434AD0. Name from YRpp; the
//   address is the private constructor it declares.
//
// BitText::BitText @0x434AD0 — loads the game font.
#ifndef GG_MATCH_UI_BIT_TEXT_CTOR_METHODS_H
#define GG_MATCH_UI_BIT_TEXT_CTOR_METHODS_H

#include "../renderer/bit_font.h"

// GLOBAL: GAMEMD 0x89C4D0 — the game font instance this constructor installs.
// Retail writes it on both paths, storing null when the allocation fails.
extern BitFont* TheGameFont;

// VTABLE: GAMEMD 0x7E3A80 — slot 0 is the deleting destructor at 0x435560.
class BitText
{
public:
    virtual ~BitText();

    // FUNCTION: GAMEMD 0x434AD0
    BitText();
    bool FUN_00434CD0(BitFont*, Surface*, const unsigned short*, int, int, int, int, int, int, int);
    bool FUN_004353F0(BitFont*, Surface*, const unsigned short*, int, int, int, int, int, int, int);
};

GG_STATIC_ASSERT(sizeof(BitText) == 4);

#endif  // GG_MATCH_UI_BIT_TEXT_CTOR_METHODS_H
