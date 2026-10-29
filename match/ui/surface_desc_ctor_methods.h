// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x433880. The rectangle at +0x30 is identified by the
//   SetRect import call (`CALL DWORD PTR [0x7E14B4]` with the address of +0x30
//   and four zeroes), which fixes it at 0x10 bytes and puts the two flag bytes
//   immediately after it at +0x40/+0x41.
#ifndef GG_MATCH_UI_SURFACE_DESC_CTOR_METHODS_H
#define GG_MATCH_UI_SURFACE_DESC_CTOR_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

#include "../renderer/bit_font.h"

extern "C" __declspec(dllimport) int __stdcall SetRect(LTRBStruct*, int, int, int, int);

// What 0x433990 resolves the argument to. Only the two fields the constructor
// copies out are modelled.
BitFontInternalData* FUN_00433990(const char* key);

inline void BitFont::Reset()
{
    int zero = 0;
    int one = 1;
    InternalPTR = 0;
    unknown_24 = 0x7FFF;
    unknown_26 = 0x3555;
    unknown_28 = 0x40;
    unknown_40 = (char)one;
    unknown_41 = (char)one;
    Width = one;
    unknown_1C = one;
    unknown_20 = zero;
    pGraphBuffer = 0;
    Pointer_8 = 0;
    SetRect(&Bounds, zero, zero, zero, zero);
    unknown_2C = one;
}

#endif  // GG_MATCH_UI_SURFACE_DESC_CTOR_METHODS_H
