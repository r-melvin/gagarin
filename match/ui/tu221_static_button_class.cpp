// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Original translation unit candidate TU221; no original source filename is
//   attested, so this file keeps a placeholder name. The static-button functions
//   consolidated here span 0x6C6640..0x6C6878, with the confirmed class anchor at
//   0x6C6640. The broader table-derived candidate window also contains factory
//   and vector code that remains with its existing owners. Function claims are
//   in ascending retail address order; this grouping is not unique source identity.
//
// Flag bisection: /GX adds exception-unwind code to the placement-new and destructor paths;
// 0x6C6680, 0x6C6740 and 0x6C6880 fall to 1.4%, 0.0% and 9.5% with it, so retail was built without it.
//
// StaticButtonClass entries (layout and evidence: ui_gadget.h).

#include "input_controls/controls_views.h"

#include <new.h>
#include <string.h>

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
        Background = MemoryBuffer(0, 0);
    }
}

// FUNCTION: GAMEMD 0x6C6740
void StaticButtonClass::vf_34()
{
    if (!Background.Buffer) {
        if (Width > 0 && Height > 0) {
            new (&Background) MemoryBuffer(DAT_00887314->GetBytesPerPixel() * Height * Width);
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
