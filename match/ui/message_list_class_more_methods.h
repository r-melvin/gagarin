// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets derived from the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI (member-access disassembly at 0x5D4AD0), cross-checked against
//   YRpp (reconfirmed here).
//
// MessageListClass::SetWidth — propagate a new pixel width (minus an 8px
// margin) onto the list object, every message gadget in the GetNext-walked
// linked list, and the active edit-line gadget. Reuses the binding shape of
// message_list_class_methods.h; this TU only needs the few members SetWidth
// actually touches, so they are modelled here directly and offset-asserted.
#ifndef GG_MATCH_UI_MESSAGE_LIST_CLASS_MORE_METHODS_H
#define GG_MATCH_UI_MESSAGE_LIST_CLASS_MORE_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// Message gadget node (GadgetClass : LinkClass). SetWidth needs:
//   * vtable slot 1 (+0x04) = GadgetClass::GetNext -> `mov edx,[this]; call [edx+4]`
//   * Width @ +0x38, written for every node (`mov [eax+0x38], esi`).
class TextLabelClass
{
public:
    virtual ~TextLabelClass();             // slot 0 (destructor)
    virtual TextLabelClass* GetNext();     // slot 1 (+0x04) — walked here
    char _gap04[0x38 - 0x04];              // LinkClass tail + GadgetClass fields
    int  Width;                            // +0x38
};

#if GG_TARGET_ABI_32
GG_STATIC_ASSERT(offsetof(TextLabelClass, Width) == 0x38);
#endif

// MessageListClass. Only the members SetWidth reads/writes are modelled:
//   MessageList @0x00, IsEdit @0x19, EditLabel @0x24, Width @0x2C4.
struct MessageListClass
{
    void SetWidth(int width);              // GAMEMD 0x5D4AD0 __thiscall

    TextLabelClass* MessageList;           // +0x00  list head
    char _gap04[0x19 - 0x04];              // +0x04  MessagePos/counts/Height/flags
    unsigned char   IsEdit;                // +0x19
    char _gap1a[0x24 - 0x1A];              // +0x1A  AdjustEdit + EditPos
    TextLabelClass* EditLabel;             // +0x24  active edit-line gadget
    char _gap28[0x2C4 - 0x28];             // +0x28  text buffers + edit positions
    int  Width;                            // +0x2C4
};

#if GG_TARGET_ABI_32
GG_STATIC_ASSERT(offsetof(MessageListClass, MessageList) == 0x00);
GG_STATIC_ASSERT(offsetof(MessageListClass, IsEdit)      == 0x19);
GG_STATIC_ASSERT(offsetof(MessageListClass, EditLabel)   == 0x24);
GG_STATIC_ASSERT(offsetof(MessageListClass, Width)       == 0x2C4);
#endif

#endif  // GG_MATCH_UI_MESSAGE_LIST_CLASS_MORE_METHODS_H
