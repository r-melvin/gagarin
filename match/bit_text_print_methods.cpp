// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x434B90.
//
// reccmp annotations:
//   FUNCTION: GAMEMD 0x434B90   FUN_00434B90 (__stdcall)

#include "bit_text_print_methods.h"

// FUNCTION: GAMEMD 0x434B90  (__stdcall)
//
// Bind the target surface and a position to the font, draw, then release the
// surface again. A null font is a no-op that hands back the position argument
// unchanged, which is also what the draw call returns on the live path — the
// caller uses it to advance.
int __stdcall FUN_00434B90(BitFont* font, Surface* surface, const unsigned short* text,
                           int arg4, int arg5, int arg6, int arg7)
{
    int result = arg4;

    if (font != 0) {
        font->Lock(surface);
        font->FUN_00434110(result);

        result = font->FUN_00434500(text, result, arg5, arg6, arg7);

        font->UnLock(surface);
    }

    return result;
}
