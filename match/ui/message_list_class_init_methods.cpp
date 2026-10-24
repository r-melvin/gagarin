// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x5D3A60.

#include "message_list_class_init_methods.h"
#include "input_controls/ui_gadget.h"
extern const char STR_00830680[]; // STRING: GAMEMD 0x830680 (decl; reloc)
extern "C" int __cdecl FUN_004068E0(const char*, ...); // Declaration: GAMEMD 0x4068E0

// FUNCTION: GAMEMD 0x5D3A60
//
// (Re)initialise the on-screen message list: record the usable width (eight
// less than the screen width) and log it, destroy every queued label and the
// edit label, mark all fourteen message buffers free, then take the layout
// parameters — message origin, message and character limits (capped at 14
// and 112), fixed 19-pixel line height, overflow flag, edit origin (which
// follows the message origin when either edit coordinate is -1) and the
// overflow window, clamped so that it ends inside the character limit and
// starts before its end. The fifth argument (height) is ignored.
void MessageListClass::Init(int x, int y, int maxMessages, int maxChars,
                                int height, int editX, int editY,
                                bool enableOverflow, int overflowStart,
                                int overflowEnd, int width)
{
    this->Width = width - 8;
    FUN_004068E0(STR_00830680, this->Width);

    TextLabelClass* label = this->MessageList;
    while (label != 0) {
        this->MessageList = static_cast<TextLabelClass*>(label->Remove());
        delete label;
        label = this->MessageList;
    }

    int i;
    for (i = 0; i < 14; i++) {
        this->BufferAvail[i] = 1;
    }

    if (this->IsEdit) {
        if (this->EditLabel != 0) {
            delete this->EditLabel;
        }
        this->EditLabel = 0;
    }

    this->MessageList = 0;
    this->MessagePos_X = x;
    this->MessagePos_Y = y;
    this->MaxMessageCount = maxMessages;
    if (maxMessages > 14) {
        this->MaxMessageCount = 14;
    }
    this->MaxCharacters = maxChars;
    if (maxChars > 112) {
        this->MaxCharacters = 112;
    }
    this->Height = 19;
    this->EnableOverflow = enableOverflow;
    this->IsEdit = false;

    if (editX != -1 && editY != -1) {
        this->AdjustEdit = false;
        this->EditX = editX;
        this->EditY = editY;
    } else {
        this->AdjustEdit = true;
        this->EditX = x;
        this->EditY = y;
    }

    this->EditLabel = 0;
    this->EditBuffer[0] = 0;
    this->OverflowBuffer[0] = 0;
    this->EditCurrentPos = 0;
    this->EditInitialPos = 0;
    this->CursorCharacter = 0;
    this->OverflowStart = overflowStart;
    this->OverflowEnd = overflowEnd;
    if (overflowEnd >= this->MaxCharacters) {
        this->OverflowEnd = this->MaxCharacters - 1;
    }
    if (overflowStart >= this->OverflowEnd) {
        this->OverflowStart = this->OverflowEnd - 1;
    }
}
