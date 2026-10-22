// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
// Flag bisection: a paired /GX probe of every entry in this TU produced the same scores as the
// line above. /GX is omitted because controls_static_button.cpp shows retail has no unwind code.
//
// TextLabelClass entries (layout and evidence: ui_gadget.h).
#include "controls_views.h"

#include <string.h>

// FUNCTION: GAMEMD 0x72A4A0
// CAPPED at 18.9% (27 of 143 instructions; multiset delta: retail has 3 `mov` more). Retail spills the
// font pointer to a stack local ([esp+0xC], frame 0x1C) and reloads it into EBP after the typing-effect
// tick arithmetic borrows EBP; ours keeps it in EBP (frame 0x18). Retail also stores `Y` before `X`
// into the rectangle and interleaves the surface-width calls with those stores. Variants tried:
// separate field stores (this) and the `Rect(x, y, width, height)` constructor (16.1%).
int TextLabelClass::Draw(int forced)
{
    if (!IsHidden && GadgetClass::Draw(forced)) {
        int count = DAT_00B054D0.Count;
        int index = SchemeIndex;
        if (count) {
            if (index <= 0 || index >= count)
                index = 0;
            ColorScheme* scheme = DAT_00B054D0.Items[index];
            if (scheme) {
                Font* font = FUN_004A60D0(unknown_2C);
                Rect area;
                area.X = X;
                area.Y = Y;
                int width = MaxWidth;
                if (width < 0)
                    width = DAT_00887314->GetWidth();
                area.Width = width;
                area.Height = font->Height;
                int overflow = area.X + area.Width - DAT_00887314->GetWidth();
                if (overflow > 0) {
                    area.Width -= overflow;
                    if (area.Width <= 0 || area.Height <= 0)
                        return 0;
                }
                RGBTriple tint = *scheme->Tint.Adjust(&forced);
                unsigned colour = (tint.Blue << 8 | tint.Green) << 8 | tint.Red;
                int length = wcslen(Text);
                if (IsTyping) {
                    unsigned long now = timeGetTime();
                    int shown = CharsShown;
                    if (shown == 0)
                        CharsShown = 1;
                    else
                        CharsShown = shown + ((now - unknown_48) >> 4);
                    if (shown != CharsShown)
                        unknown_48 = now;
                    if (CharsShown <= length)
                        ControlsPlaySound(ControlsRulesInstance->TextSound, 0x2000, 1.0f, 0);
                }
                FUN_00623880(DAT_00887314, &area, Text, length, font, colour,
                                      &unknown_3C, IsFocused(), 0, 1, CharsShown);
                return 1;
            }
        }
    }
    return 0;
}

// FUNCTION: GAMEMD 0x72A660
void TextLabelClass::SetText(const wchar_t* text)
{
    Text = text;
}
