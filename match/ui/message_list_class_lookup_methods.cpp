// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
// MessageListClass methods consolidated by retail address. Original TU is unknown.

#include "message_list_class_methods.h"
#include "message_list_class_init_methods.h"
#include "message_list_class_add_edit_methods.h"
#include "message_list_class_draw_methods.h"
#include "message_list_class_manage_methods.h"
#include "message_list_class_more_methods.h"
#include "message_list_class_trim_methods.h"
#include "message_list_remove_edit_methods.h"
#include "input_controls/ui_gadget.h"

// FUNCTION: GAMEMD 0x4068E0 (decl; reloc) — release-build variadic trace stub.
extern "C" int __cdecl FUN_004068E0(const char* fmt, ...);
extern const char STR_00830680[]; // STRING: GAMEMD 0x830680 (decl; reloc)

// FUNCTION: GAMEMD 0x5D39D0
MessageListClass::MessageListClass()
    : MessageList(0), MessagePos_X(0), MessagePos_Y(0), MaxMessageCount(0),
      MaxCharacters(0), Height(0), EnableOverflow(0), IsEdit(0), AdjustEdit(0),
      EditX(0), EditY(0), EditLabel(0), EditCurrentPos(0), EditInitialPos(0),
      CursorCharacter(0), OverflowStart(0), OverflowEnd(0), Width(0)
{
    EditBuffer[0] = 0;
    OverflowBuffer[0] = 0;
    for (int i = 0; i < 14; ++i) BufferAvail[i] = 1;
}

// FUNCTION: GAMEMD 0x5D3A40
MessageListClass::~MessageListClass()
{
    Init(0, 0, 0, 0, 0, 0, 0, false, 0, 0, 640);
}

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

// FUNCTION: GAMEMD 0x5D3F60
// Walks the label list for the label with the given key and returns its text, or 0.
const wchar_t* MessageListClass::FUN_005D3F60(int key)
{
    TextLabelClass* label = MessageList;
    while (label) {
        if (label->unknown_28 == key)
            return label->Text;
        label = static_cast<TextLabelClass*>(label->GetNext());
    }
    return 0;
}

// FUNCTION: GAMEMD 0x5D3F90
// Walks the label list for the label with the given key and returns it, or 0.
TextLabelClass* MessageListClass::FUN_005D3F90(int key)
{
    TextLabelClass* label = MessageList;
    while (label) {
        if (label->unknown_28 == key)
            return label;
        label = static_cast<TextLabelClass*>(label->GetNext());
    }
    return 0;
}

// FUNCTION: GAMEMD 0x5D41E0
// While editing, gives the edit label the focus.
void MessageListClass::FUN_005D41E0()
{
    if (IsEdit)
        EditLabel->SetFocus();
}

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
TextLabelClass* MessageListClass::AddEdit(int a1, int a2,
                                              const wchar_t* text, char cursor,
                                              int width)
{
    if (this->IsEdit) {
        reinterpret_cast<Label_005D4210*>(this->EditLabel)->Slot_50();
        return 0;
    }

    if (this->AdjustEdit) {
        int count = 0;
        Label_005D4210* p = reinterpret_cast<Label_005D4210*>(this->MessageList);
        while (p != 0) {
            ++count;
            p = p->GetNext();
        }
        if (this->IsEdit && this->AdjustEdit) {
            ++count;
        }
        ++count;
        if (count > this->MaxMessageCount) {
            Label_005D4210* oldest = reinterpret_cast<Label_005D4210*>(this->MessageList);
            this->MessageList = reinterpret_cast<TextLabelClass*>(oldest->Remove());
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
    this->EditLabel = reinterpret_cast<TextLabelClass*>(label);
    if (width > 0) {
        label->At_38 = width;
    } else {
        label->At_38 = this->Width;
    }

    if (this->EditLabel != 0) {
        this->IsEdit = 1;
        reinterpret_cast<Label_005D4210*>(this->EditLabel)->Slot_50();
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
        Label_005D4210* q = reinterpret_cast<Label_005D4210*>(this->MessageList);
        while (q != 0) {
            q->Y = y;
            q = q->GetNext();
            y += this->Height;
        }
        this->MaxMessageCount--;
    }

    return this->EditLabel;
}

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

// FUNCTION: GAMEMD 0x5D4400  (__thiscall)
// &EditBuffer[EditInitialPos]:  mov eax,[ecx+0x2b4]; lea eax,[ecx+eax*2+0x28].
wchar_t* MessageListClass::GetEditBuffer() const
{
    return (wchar_t*)&EditBuffer[EditInitialPos];
}

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
            if (label->unknown_24 != 0 && MessageTimer.GetValue() > label->unknown_24) {
                TextLabelClass* next = static_cast<TextLabelClass*>(label->GetNext());
                this->MessageList = static_cast<TextLabelClass*>(label->Remove());
                for (int i = 0; i < 14; i++) {
                    if (label->Text == this->MessageBuffers[i]) {
                        this->BufferAvail[i] = 1;
                    }
                }
                delete label;
                changed = 1;
                label = next;
            } else {
                label = static_cast<TextLabelClass*>(label->GetNext());
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
                p = static_cast<TextLabelClass*>(p->GetNext());
                y += this->Height;
            }
        }
    }
    return changed;
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x887338
TimerStruct_005D4430 MessageTimer;
// END defined globals

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
void MessageListClass::Draw()
{
    wchar_t cursor[2];
    cursor[0] = 0;
    cursor[1] = 0;

    if (this->IsEdit) {
        DAT_00887640->HideCursor();
        (reinterpret_cast<Label_005D49A0*>(this->EditLabel)->*reinterpret_cast<Label_005D49A0*>(this->EditLabel)->Vtbl->At_6C)(1);
        Font* font = FUN_004A60D0(reinterpret_cast<Label_005D49A0*>(this->EditLabel)->Flags);
        int width = font->TextWidth(reinterpret_cast<Label_005D49A0*>(this->EditLabel)->Text, 0);
        if (this->CursorCharacter != 0
            && static_cast<int>(this->EditCurrentPos) - static_cast<int>(this->EditInitialPos) < this->MaxCharacters - 1) {
            if ((reinterpret_cast<Label_005D49A0*>(this->EditLabel)->*reinterpret_cast<Label_005D49A0*>(this->EditLabel)->Vtbl->At_58)()) {
                cursor[0] = this->CursorCharacter;
                Point2D_005D49A0 pos(reinterpret_cast<Label_005D49A0*>(this->EditLabel)->X + width, reinterpret_cast<Label_005D49A0*>(this->EditLabel)->Y);
                Rect_005D49A0 rect;
                FUN_004A61C0(cursor, reinterpret_cast<Surface_005D49A0*>(DAT_00887314),
                             (reinterpret_cast<Surface_005D49A0*>(DAT_00887314)->*reinterpret_cast<Surface_005D49A0*>(DAT_00887314)->Vtbl->GetRect)(&rect),
                             &pos, DAT_00B054D4[reinterpret_cast<Label_005D49A0*>(this->EditLabel)->SchemeIndex], 0,
                             reinterpret_cast<Label_005D49A0*>(this->EditLabel)->Flags);
            }
        }
        DAT_00887640->ShowCursor();
    }

    if (this->MessageList != 0) {
        (reinterpret_cast<Label_005D49A0*>(this->MessageList)->*reinterpret_cast<Label_005D49A0*>(this->MessageList)->Vtbl->At_2C)(1);
    }
}

// FUNCTION: GAMEMD 0x5D4AA0  (__thiscall)
// Count the message gadgets (walk the GetNext list), plus one for the active
// edit line when IsEdit && AdjustEdit.
int MessageListClass::NumMessages() const
{
    int count = 0;
    for (TextLabelClass* node = MessageList; node; node = static_cast<TextLabelClass*>(node->GetNext()))
        ++count;
    if (IsEdit && AdjustEdit)
        ++count;
    return count;
}

// STRING: GAMEMD 0x8306A8 "MessageListClass::Set_Width(%d)\n"
// FUNCTION: GAMEMD 0x5D4AD0  (__thiscall)
// Apply a new width (less an 8px margin) to the list and every gadget: store on
// the object (+0x2C4), trace, walk the GetNext list assigning each node's Width
// (+0x38), then the edit-line gadget when an edit is active.
void MessageListClass::SetWidth(int width)
{
    width -= 8;
    Width = width;
    FUN_004068E0("MessageListClass::Set_Width(%d)\n", width);

    TextLabelClass* node = MessageList;
    while (node)
    {
        node->MaxWidth = width;
        node = static_cast<TextLabelClass*>(node->GetNext());
    }

    if (IsEdit)
        EditLabel->MaxWidth = width;
}

// FUNCTION: GAMEMD 0x5D4B20
//
// Split the head off a wide string at a break character (any code below or
// equal to a space, but not the terminator), looking between minLen and
// maxLen characters in — forwards, or backwards from the far end when
// fromEnd is set. When no break is found the cut lands at minLen. The head
// is copied into dest (when given) and terminated, the remainder of src is
// shifted down over it, and the cut length is returned; a non-positive
// minLen does nothing and returns zero (`minLen <= 0` gives retail's
// `TEST/JG`; `< 1` gives `CMP,1/JGE`).
//
// The tail-move length written as `(len - cut + 1) * sizeof(wchar_t)` is
// what produces retail's odd `NEG; SHL 0x1F; SUB; ADD; LEA [EAX*2+2]` fold
// (cl multiplies the subtracted term by 0x7FFFFFFF before doubling); the head
// copy is the /Oi memcpy intrinsic (`REP MOVSD`/`REP MOVSB`).
int MessageListClass::TrimMessage(wchar_t* dest, wchar_t* src, int minLen,
                                      int maxLen, int fromEnd)
{
    int cut;

    if (minLen <= 0) {
        return 0;
    }

    int len = wcslen(src);
    if (maxLen > len) {
        maxLen = len;
    }

    if (fromEnd == 0) {
        for (cut = minLen; cut <= maxLen; cut++) {
            wchar_t c = src[cut - 1];
            if (c != 0 && c <= 0x20) {
                goto found;
            }
        }
        cut = minLen;
    } else {
        for (cut = maxLen; cut >= minLen; cut--) {
            wchar_t c = src[cut - 1];
            if (c != 0 && c <= 0x20) {
                goto found;
            }
        }
        cut = minLen;
    }

found:
    if (dest != 0) {
        memcpy(dest, src, cut * sizeof(wchar_t));
        dest[cut] = 0;
    }
    memmove(src, src + cut, (len - cut + 1) * sizeof(wchar_t));
    return cut;
}

// FUNCTION: GAMEMD 0x5D4BF0  (__thiscall)
// Re-stack the message labels vertically: start at MessagePos.Y (offset by the
// edit-line height when an adjustable edit is active), then assign each gadget's
// Y and step down by Height.
void MessageListClass::ComputeY()
{
    int y;
    if (IsEdit && AdjustEdit)
        y = Height + MessagePos_Y;
    else
        y = MessagePos_Y;

    TextLabelClass* node = MessageList;
    while (node)
    {
        node->Y = y;
        node = static_cast<TextLabelClass*>(node->GetNext());
        y += Height;
    }
}
