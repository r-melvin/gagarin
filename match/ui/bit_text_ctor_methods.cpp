// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x434AD0.
//
// reccmp annotations:
//   FUNCTION: GAMEMD 0x434AD0   BitText::BitText (__thiscall)
//   VTABLE:   GAMEMD 0x7E3A80   BitText
//   GLOBAL:   GAMEMD 0x89C4D0   TheGameFont
//   STRING:   GAMEMD 0x818B98   "GAME.FNT"

#include "bit_text_ctor_methods.h"

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

// Stand-in for the destructor at 0x435560 so the vtable has something to point
// at. Not annotated - matching 0x435560 is separate work.
BitText::~BitText()
{
}
