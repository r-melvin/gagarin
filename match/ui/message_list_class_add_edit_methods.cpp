// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x5D4210.

#include "message_list_class_add_edit_methods.h"

// FUNCTION: GAMEMD 0x5D4210  MessageListClass::AddEdit (__thiscall, ret 0x14)
//
// Open the typing line. If one is already open nothing is created — the
// existing edit label is simply retired and null handed back. Otherwise the
// list is trimmed first, counting the messages plus the line about to be
// added and dropping the oldest (handing its buffer back to the pool) when
// that would overflow the visible count. The edit buffer is then cleared,
// seeded with the supplied text, and a fresh label built over it, drawn to
// the caller's width or the list's own. Finally the labels are re-stacked to
// make room for the edit line.
Label_005D4210* MessageList_005D4210::AddEdit(int a1, int a2,
                                              const wchar_t* text, char cursor,
                                              int width)
{
    if (this->IsEdit) {
        this->EditLabel->Slot_50();
        return 0;
    }

    if (this->AdjustEdit) {
        int count = 0;
        Label_005D4210* p = this->MessageList;
        while (p != 0) {
            ++count;
            p = p->GetNext();
        }
        if (this->IsEdit && this->AdjustEdit) {
            ++count;
        }
        ++count;
        if (count > this->MaxMessageCount) {
            Label_005D4210* oldest = this->MessageList;
            this->MessageList = oldest->Remove();
            for (int i = 0; i < 14; i++) {
                if (oldest->Text == this->MessageBuffers[i]) {
                    this->BufferAvail[i] = 1;
                }
            }
            delete oldest;
        }
    }

    const wchar_t* src = text;
    if (src == 0) {
        src = DAT_00887734;
    }

    this->CursorCharacter = cursor;
    memset(this->EditBuffer, 0, sizeof(this->EditBuffer));
    wcscpy(this->EditBuffer, src);
    this->OverflowBuffer[0] = 0;
    this->EditCurrentPos = this->EditInitialPos = wcslen(src);

    Label_005D4210* label = (Label_005D4210*)FUN_007C8E17(0x4C);
    if (label != 0) {
        label = label->Construct(this->EditBuffer, this->EditX, this->EditY,
                                 a1, a2 | 0x8000);
    } else {
        label = 0;
    }
    this->EditLabel = label;
    if (width > 0) {
        label->At_38 = width;
    } else {
        label->At_38 = this->Width;
    }

    if (this->EditLabel != 0) {
        this->IsEdit = 1;
        this->EditLabel->Slot_50();
    } else {
        this->IsEdit = 0;
    }

    FUN_00778180();

    if (this->AdjustEdit) {
        int y;
        if (this->IsEdit) {
            y = this->Height + this->MessagePos_Y;
        } else {
            y = this->MessagePos_Y;
        }
        Label_005D4210* q = this->MessageList;
        while (q != 0) {
            q->Y = y;
            q = q->GetNext();
            y += this->Height;
        }
        this->MaxMessageCount--;
    }

    return this->EditLabel;
}
