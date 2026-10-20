// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x5D4430.

#include "message_list_class_manage_methods.h"

// FUNCTION: GAMEMD 0x5D4430
//
// Expire old messages. Every label with a non-zero expiry that the message
// timer has passed is unlinked (the unlink returns the new head), its text
// buffer is handed back to the pool by flagging the matching slot, and the
// label is deleted. When anything was removed the surviving labels are
// re-stacked from the list origin (one line lower while the edit line is
// being adjusted in). Returns whether anything changed.
//
// The changed flag is an int, not a bool: retail holds it in EBP (`XOR
// EBP,EBP` / `MOV EBP,1` / `MOV EAX,EBP`); a bool spills to BL and returns
// through `MOV AL,BL`. The `next` local is scoped inside the expiry branch so
// the else branch assigns the cursor straight from EAX, and the re-stacking
// loop advances the cursor before adding the line height, which is what puts
// `ADD ESI,[EDI+0x14]` after the GetNext call (57.6% before these three).
int MessageListClass::Manage()
{
    int changed = 0;

    TextLabelClass* label = this->MessageList;
    if (label != 0) {
        do {
            if (label->At_24 != 0 && MessageTimer.GetValue() > label->At_24) {
                TextLabelClass* next = label->GetNext();
                this->MessageList = label->Remove();
                for (int i = 0; i < 14; i++) {
                    if (label->Text == this->MessageBuffers[i]) {
                        this->BufferAvail[i] = 1;
                    }
                }
                delete label;
                changed = 1;
                label = next;
            } else {
                label = label->GetNext();
            }
        } while (label != 0);

        if (changed) {
            int y;
            if (this->IsEdit && this->AdjustEdit) {
                y = this->Height + this->MessagePos_Y;
            } else {
                y = this->MessagePos_Y;
            }
            TextLabelClass* p = this->MessageList;
            while (p != 0) {
                p->Y = y;
                p = p->GetNext();
                y += this->Height;
            }
        }
    }
    return changed;
}
