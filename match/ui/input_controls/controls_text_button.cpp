// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
// Flag bisection: a paired /GX probe of every entry in this TU produced the same scores as the
// line above. /GX is omitted because controls_static_button.cpp shows retail has no unwind code.
//
// TextButtonClass entries (layout and evidence: ui_gadget.h).
#include "controls_views.h"


// FUNCTION: GAMEMD 0x71FF20
// Build a text button at a position and size; a size of -1 in either direction is taken from the
// text measured in the button's font.
TextButtonClass::TextButtonClass(int id, const wchar_t* text, int printFlags, int x, int y, int w, int h,
                                 bool outline, bool hidden) : ToggleClass(id, x, y, w, h), HasOutline(outline), unknown_35(hidden), Text(text), unknown_3C(printFlags)
{
    if (w == -1 || h == -1) {
        Font* font = FUN_004A60D0(unknown_3C);
        if (w == -1) {
            Width = font->TextWidth(Text, 0) + 8;
        }
        if (h == -1) {
            Height = font->Height + 2;
        }
    }
}

// FUNCTION: GAMEMD 0x71FFE0
int TextButtonClass::Draw(int forced)
{
    if (ControlClass::Draw(forced)) {
        vf_36();
        DrawText(Text);
        return 1;
    }
    return 0;
}

// FUNCTION: GAMEMD 0x720020
void TextButtonClass::SetText(const wchar_t* text, bool resize)
{
    Text = text;
    MarkRedraw();
    if (resize && Text) {
        Font* font = FUN_004A60D0(unknown_3C);
        Width = font->TextWidth(Text, 0) + 8;
        Height = font->Height + 2;
    }
}

// FUNCTION: GAMEMD 0x720070
void TextButtonClass::vf_36()
{
    if (!unknown_35) {
        if (HasOutline) {
            ColorConvert* lookup = DAT_00B054D0[GetColorScheme()]->Convert;
            unsigned colour = lookup->Lookup(0xC);
            Box box;
            box.Left = X - 1;
            box.Top = Y - 1;
            box.Right = X + Width + 2;
            box.Bottom = Y + Height + 2;
            DAT_00887314->OutlineRect(&box, colour);
        }
        int style = IsDisabled ? 3 : !unknown_2C;
        {
            Rect area(X, Y, Width, Height);
            FUN_004A5A50(&area, style, 1);
        }
    }
}

// FUNCTION: GAMEMD 0x720140
// CAPPED at 46.2% (30 of 65 instructions; multiset identical, scheduling/register naming only). The
// print-flag word is held in EDX in retail and in ECX in ours, which renames the count, the scheme
// pointer and the half-width temporaries. Variants tried: int instead of unsigned flags, the
// three orderings of `unknown_3C | flags | 0x100`.
void TextButtonClass::DrawText(const wchar_t* text)
{
    int index = GetColorScheme();
    if (Text) {
        unsigned flags;
        if (IsDisabled)
            flags = 0;
        else if (unknown_2C || IsOn)
            flags = 0x6000;
        else
            flags = 0x5000;
        if (DAT_00B054D0.Count) {
            if (index <= 0 || index >= DAT_00B054D0.Count)
                index = 0;
            ColorScheme* scheme = DAT_00B054D0.Items[index];
            if (scheme) {
                Point2D position(X + (Width >> 1) - 1, Y + 1);
                Point2D result;
                FUN_004A6010(&result, text, DAT_00887314, &DAT_00887314->GetRect(),
                                    &position, scheme, 0, unknown_3C | flags | 0x100, 1);
            }
        }
    }
}

// FUNCTION: GAMEMD 0x720200
void TextButtonClass::SetPrintFlags(int flags)
{
    unknown_3C = flags;
}
