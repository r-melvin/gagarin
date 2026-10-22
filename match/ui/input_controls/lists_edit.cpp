// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Flags: /GX is left off. A paired /GX probe changes nothing except the compiler-emitted scalar deleting
//   destructors, which stop inlining their bodies with it (0x4E1A60 100% -> 6.5%, 0x558060 and 0x488F00 -> 0%,
//   0x4B55F0 -> 17.6%); every other function here scores identically with and without it.
//   Lists cluster: EditClass vtable bodies at 0x4C30E0..0x4C3570 (shared by DropListClass's vtable).
#include "lists_views.h"

// FUNCTION: GAMEMD 0x4C30E0
// EditClass::SetText slot (+0x88): edits `text` in place, at most size-1 characters, and redraws.
void EditClass::SetText(wchar_t* text, int size)
{
    Text = text;
    MaxLength = size - 1;
    Length = wcslen(text);
    MarkRedraw();
}

// FUNCTION: GAMEMD 0x4C3110
// EditClass::Draw slot (+0x6C): when the base draws, hides the mouse over the box and paints the frame and text.
int EditClass::Draw(int forced)
{
    if (ControlClass::Draw(forced)) {
        DAT_00887640->HideRegion(Rect(X, Y, Width, Height));
        vf_36();
        DrawText(Text);
        DAT_00887640->ShowRegion();
        return 1;
    }
    return 0;
}

// FUNCTION: GAMEMD 0x4C3190
// CAPPED at 2.9% after three attempts (early return then body; inverted if(!IsReadOnly){body}; flags=0 local before the
// Escape-path base call). Remaining delta: the body is the same instruction multiset except for four instructions,
// but retail pushes esi first and then ebx and edi after the read-only test (order esi, ebx, edi, each return
// path popping only what it pushed), and pushes the zero arguments of the Escape-path base call through ebx;
// this build pushes ebx, esi, edi in its prologue and pushes immediates, which shifts every later offset.
// EditClass::Action slot (+0x7C): clicking takes the focus; while focused, Escape drops it and printable keys are
// fed to vf_38 (and swallowed when accepted).
int EditClass::Action(unsigned flags, unsigned* key, int modifier)
{
    if (IsReadOnly) {
        return 0;
    }
    if (flags & 1) {
        flags &= ~1u;
        SetFocus();
        MarkRedraw();
    }
    if ((flags & 0x100) && IsFocused()) {
        if (*key == 0x1B) {
            KillFocus();
            return ControlClass::Action(0, key, 0);
        }
        int ascii = DAT_0087F770->ToAscii(*key) & 0xFF;
        if ((*key & 0x1000) && ascii >= '0' && ascii <= '9') {
            *key &= ~0x1000u;
            if (!(flags & 0x44) && vf_38(ascii)) {
                flags &= ~0x100u;
                *key = 0;
            }
        } else if ((!(*key & 0x1000) && ascii >= 0x20 && ascii < 0x100) || *key == 0xD || *key == 8) {
            if (!(flags & 0x44) && vf_38(DAT_0087F770->ToAscii(*key))) {
                flags &= ~0x100u;
                *key = 0;
            }
        }
    }
    return ControlClass::Action(flags, key, 0);
}

// FUNCTION: GAMEMD 0x4C32A0
// EditClass::vf_36 slot (+0x90): the sunken frame around the box.
void EditClass::vf_36()
{
    FUN_004A5A50(&Rect(X, Y, Width, Height), 4, 1);
}

// FUNCTION: GAMEMD 0x4C32E0
// EditClass::DrawText slot (+0x94): draws `text` inside the frame and, while focused with room left, the cursor.
void EditClass::DrawText(wchar_t const* text)
{
    unsigned focusFlag = IsFocused() ? 0x2000 : 0;
    FUN_004A6500(text, DAT_00887314, &DAT_00887314->GetRect(), &Point2D(X + 1, Y + 1),
                 DAT_00B054D0[SchemeIndex], 0, TextFlags | focusFlag, Width - 2, 0);
    Font* font = FUN_004A60D0(TextFlags);
    if (IsFocused()) {
        if (wcslen(text) < MaxLength) {
            if (font->TextWidth(text, 0) + font->TextWidth(DAT_0082076C, 0) < Width - 2) {
                FUN_004A6500(DAT_0082076C, DAT_00887314, &DAT_00887314->GetRect(),
                             &Point2D(font->TextWidth(text, 0) + X + 1, Y + 1), DAT_00B054D0[SchemeIndex], 0,
                             TextFlags | focusFlag, -1, 0);
            }
        }
    }
}

// FUNCTION: GAMEMD 0x4C3420
// EditClass::vf_38 slot (+0x98): applies one typed character to the text (Backspace, Enter, or a character
// accepted by the unknown_30 filters). Returns false only when Enter ended the edit.
bool EditClass::vf_38(int ch)
{
    Font* font = FUN_004A60D0(TextFlags);
    switch (ch) {
    case 0:
        return true;
    case 8:
        if (Length) {
            Length--;
            Text[Length] = 0;
            MarkRedraw();
        }
        return true;
    case 0xD:
        KillFocus();
        return false;
    }
    if (font->TextWidth(Text, 0) + font->CharWidth(ch) >= Width - 2) {
        return true;
    }
    if (Length >= MaxLength) {
        return true;
    }
    if ((!isgraph(ch) && ch != 0x20) || (ch == 0x20 && !Length)) {
        return true;
    }
    if ((unknown_30 & 8) && isalpha(ch)) {
        ch = toupper(ch);
    }
    if (!((unknown_30 & 2) && isdigit(ch))) {
        if (!((unknown_30 & 1) && isalpha(ch))) {
            if ((!(unknown_30 & 4) || isalnum(ch)) && ch != 0x20) {
                return true;
            }
        }
    }
    Text[Length] = (wchar_t)ch;
    Length++;
    Text[Length] = 0;
    MarkRedraw();
    return true;
}

// FUNCTION: GAMEMD 0x4C3570
// EditClass::SetFocus slot (+0x50): re-measures the text, then takes the focus.
void EditClass::SetFocus()
{
    Length = 0;
    if (Text) {
        Length = wcslen(Text);
    }
    GadgetClass::SetFocus();
}
