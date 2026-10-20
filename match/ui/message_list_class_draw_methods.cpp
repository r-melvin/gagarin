// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x5D49A0.

#include "message_list_class_draw_methods.h"

// FUNCTION: GAMEMD 0x5D49A0
//
// Draw the message list. While an edit line is open the mouse is hidden, the
// edit label is drawn, and if there is a cursor character and room left before
// the character limit, the cursor is printed just past the label's text (its
// pixel width from the label's font) in the label's colour scheme; then the
// mouse is shown again. Finally the message chain is drawn through the head
// gadget's slot +0x2C.
//
// Phrasing that matters: the font comes back into a local before the width
// call (retail calls the getter, then pushes the text), and the cursor position
// is built through the two-argument Point2D constructor (both loads, then Y
// stored before X); member-wise stores in either order leave X stored before Y
// is loaded (94-95%).
void MessageList_005D49A0::Draw()
{
    wchar_t cursor[2];
    cursor[0] = 0;
    cursor[1] = 0;

    if (this->IsEdit) {
        (DAT_00887640->*DAT_00887640->Vtbl->At_0C)();
        (this->EditLabel->*this->EditLabel->Vtbl->At_6C)(1);
        Font_005D49A0* font = FUN_004A60D0(this->EditLabel->Flags);
        int width = font->TextWidth(this->EditLabel->Text, 0);
        if (this->EditCursor != 0
            && this->EditCurrentPos - this->EditInitialPos < this->MaxCharacters - 1) {
            if ((this->EditLabel->*this->EditLabel->Vtbl->At_58)()) {
                cursor[0] = this->EditCursor;
                Point2D_005D49A0 pos(this->EditLabel->X + width, this->EditLabel->Y);
                Rect_005D49A0 rect;
                FUN_004A61C0(cursor, DAT_00887314,
                             (DAT_00887314->*DAT_00887314->Vtbl->GetRect)(&rect),
                             &pos, DAT_00B054D4[this->EditLabel->SchemeIndex], 0,
                             this->EditLabel->Flags);
            }
        }
        (DAT_00887640->*DAT_00887640->Vtbl->At_10)();
    }

    if (this->MessageList != 0) {
        (this->MessageList->*this->MessageList->Vtbl->At_2C)(1);
    }
}
