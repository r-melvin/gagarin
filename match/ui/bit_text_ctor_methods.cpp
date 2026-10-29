// SPDX-License-Identifier: GPL-3.0-or-later
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /Ob2 /MT
// /Ob2 inlines the real destructor into the retail scalar wrapper at 0x435560.
// The normal destructor remains a separately emitted function.
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x434AD0.
//
// reccmp annotations:
//   FUNCTION: GAMEMD 0x434AD0   BitText::BitText (__thiscall)
//   VTABLE:   GAMEMD 0x7E3A80   BitText
//   GLOBAL:   GAMEMD 0x89C4D0   TheGameFont
//   STRING:   GAMEMD 0x818B98   "GAME.FNT"

#include "bit_text_ctor_methods.h"

// LIBRARY: GAMEMD 0x7C8E17 — operator new.
// LIBRARY: GAMEMD 0x7C8B3D — operator delete in the generated scalar wrapper.

// FUNCTION: GAMEMD 0x434AD0  BitText::BitText (__thiscall)
//
// The whole body is one `new`. Retail's shape here is not hand-written control
// flow, it is what VC6 emits for `p = new T(arg)`: size to operator new, test
// the result, run the constructor only on success, and store null otherwise.
// Writing the null check explicitly would produce a second test.
BitText::BitText()
{
    TheGameFont = new BitFont("GAME.FNT");
}

// FUNCTION: GAMEMD 0x434B10
// SYNTHETIC: GAMEMD 0x435560
BitText::~BitText()
{
    BitFont* previous = TheGameFont;
    delete previous;
    if (previous == TheGameFont) TheGameFont = 0;
}
