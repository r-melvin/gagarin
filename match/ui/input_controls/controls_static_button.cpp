// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
// Flag bisection: /GX adds exception-unwind code to the placement-new and destructor paths;
// 0x6C6680, 0x6C6740 and 0x6C6880 fall to 1.4%, 0.0% and 9.5% with it, so retail was built without it.
//
// StaticButtonClass entries (layout and evidence: ui_gadget.h).
#include "controls_views.h"

#include <new.h>
#include <string.h>

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

// FUNCTION: GAMEMD 0x6C6640
int StaticButtonClass::Draw(int forced)
{
    if (GadgetClass::Draw(forced)) {
        vf_34();
        DrawText(Text);
        return 1;
    }
    return 0;
}

// FUNCTION: GAMEMD 0x6C6680
void StaticButtonClass::SetText(const wchar_t* text, bool resize)
{
    if (Text) {
        delete Text;
        Text = 0;
    }
    if (text) {
        Text = (wchar_t*)operator new(wcslen(text) * 2 + 2);
        if (Text)
            wcscpy(Text, text);
    }
    MarkRedraw();
    if (resize && Text) {
        vf_34();
        Font* font = FUN_004A60D0(unknown_34);
        Width = font->TextWidth(Text, 0);
        Height = font->Height;
        Background = ControlsBuffer(0, 0);
    }
}

// FUNCTION: GAMEMD 0x6C6740
void StaticButtonClass::vf_34()
{
    if (!Background.Buffer) {
        if (Width > 0 && Height > 0) {
            new (&Background) ControlsBuffer(DAT_00887314->GetBytesPerPixel() * Height * Width);
            if (Background.Buffer) {
                Rect area(X, Y, Width, Height);
                FUN_004371D0(DAT_00887314, &area, &Background);
            }
        }
        if (!Background.Buffer)
            return;
    }
    {
        Rect area(X, Y, Width, Height);
        FUN_00437290(DAT_00887314, &area, &Background);
    }
}

// FUNCTION: GAMEMD 0x6C67F0
// CAPPED at 56.9% (29 of 51 instructions; multiset identical, scheduling/register naming only). Retail
// stores the print position (`x`, `Y`) before it reads the scheme pointer and builds the call
// arguments; ours delays those two stores until the pointer is needed. Variants tried: the scheme
// in a local ahead of the position (this), the scheme read inside the call expression (27.5%), the
// scheme index in a local with the position built in between (41.2%), the position first (29.4%).
void StaticButtonClass::DrawText(const wchar_t* text)
{
    if (Text) {
        int flags = unknown_34;
        int x = X;
        if (flags & 0x100)
            x += Width / 2;
        if (flags & 0x200)
            x += Width - 1;
        ColorScheme* scheme = DAT_00B054D0[GetColorScheme()];
        Point2D position(x, Y);
        FUN_004A61C0(text, DAT_00887314, &DAT_00887314->GetRect(), &position,
                          scheme, 0, unknown_34);
    }
}

// SYNTHETIC: GAMEMD 0x6C6880
// StaticButtonClass::`scalar deleting destructor' is generated from the inline destructor in the header.
