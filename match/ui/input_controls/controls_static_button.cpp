// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
// Flag bisection: /GX adds exception-unwind code to the placement-new and destructor paths;
// 0x6C6680, 0x6C6740 and 0x6C6880 fall to 1.4%, 0.0% and 9.5% with it, so retail was built without it.
//
// StaticButtonClass entries (layout and evidence: ui_gadget.h).
#include "controls_views.h"

#include <new.h>
#include <string.h>

// Constructor ownership before the class anchor0x6C6640 remains unresolved.
// Retained here with its naturally emitted deleting destructor.
// FUNCTION: GAMEMD 0x6C6540
// Expansion row (see the header): the constructor sizes the button to its text when a dimension is -1.
StaticButtonClass::StaticButtonClass(int unused, const wchar_t* text, int flags, int x, int y,
                                     int width, int height)
    : GadgetClass(x, y, width, height, 0, 0), Background(0, 0), Text(0), unknown_34(flags)
{
    SetText(text, false);
    if (width == -1 || height == -1) {
        Font* font = FUN_004A60D0(unknown_34);
        if (width == -1)
            Width = font->TextWidth(Text, 0);
        if (height == -1)
            Height = font->Height;
    }
}

// SYNTHETIC: GAMEMD 0x6C6880
// StaticButtonClass::`scalar deleting destructor' is generated from the inline destructor in the header.
