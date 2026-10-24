// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x5D4390.

#include "message_list_remove_edit_methods.h"
#include "input_controls/ui_gadget.h"

// FUNCTION: GAMEMD 0x5D4390  MessageListClass::RemoveEdit (__thiscall)
// Tear down the chat edit line and reflow the messages that were sitting below
// it. The null check retail performs before the delete is the one VC6 inlines
// for every scalar delete, not a source-level guard.
//
// Everything after the IsEdit test lives *inside* that branch — including
// the unlock. With the unlock hoisted out, the not-editing path jumps to it
// instead of to the epilogue, which is a single wrong branch target and 97.6%.
// The bytes are unambiguous that retail skips the whole body, so the paired
// call at 0x778170 is not an unlock in the RAII sense whatever its name.
void MessageListClass::RemoveEdit()
{
    MessageListLock();

    if (IsEdit) {
        IsEdit = false;
        delete EditLabel;

        MessageListUnlock();

        if (AdjustEdit) {
            int y = IsEdit ? Height + MessagePos_Y : MessagePos_Y;

            TextLabelClass* message = MessageList;
            if (message != 0) {
                do {
                    message->Y = y;
                    message = static_cast<TextLabelClass*>(message->GetNext());
                    y += Height;
                }
                while (message != 0);
            }

            MaxMessageCount++;
        }
    }
}
