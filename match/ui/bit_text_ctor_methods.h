// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Read numerically off the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI at 0x434AD0. Name from YRpp BitText.h (consult-only); the
//   address is the private constructor it declares.
//
// BitText::BitText @0x434AD0 — loads the game font.
#ifndef GG_MATCH_UI_BIT_TEXT_CTOR_METHODS_H
#define GG_MATCH_UI_BIT_TEXT_CTOR_METHODS_H

// BitFont — constructed from a font filename. Direct __thiscall at a fixed
// address, declared without a body so cl emits a reloc-normalised direct call.
// 0x44 bytes, the size retail passes to operator new at 0x434AD3.
struct BitFont
{
    BitFont(const char* filename) throw();   // GAMEMD 0x433880
    char _pad[0x44];
};

// GLOBAL: GAMEMD 0x89C4D0 — the game font instance this constructor installs.
// Retail writes it on both paths, storing null when the allocation fails.
extern BitFont* TheGameFont;

// VTABLE: GAMEMD 0x7E3A80 — slot 0 is the destructor at 0x435560. The vtable
// store at 0x434AD5 is what makes this class virtual here; the destructor
// declared below is a stand-in so cl emits a table to point at. The real body
// is now matched separately as BitText::ScalarDeletingDestructor in
// match/core/small_misc44_methods.cpp (RTTI-confirmed against this same
// vtable's complete object locator) — this stand-in stays deliberately
// un-annotated for 0x435560 to avoid a double claim on one address.
struct BitText
{
    virtual ~BitText();

    // FUNCTION: GAMEMD 0x434AD0
    BitText();
};

#endif  // GG_MATCH_UI_BIT_TEXT_CTOR_METHODS_H
