// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets derived from the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI (member-access disassembly at 0x5D4400 / 0x5D4AA0 / 0x5D4BF0),
//   cross-checked against YRpp
//   (reconfirmed here).
//
// MessageListClass — the on-screen chat/message list. Its messages are a
// singly-linked list of TextLabelClass gadgets (head pointer at +0x00, walked
// via the GadgetClass GetNext virtual at vtable slot 1 / +0x04), plus the
// in-place edit line (IsEdit/AdjustEdit flags + the EditBuffer text).
#ifndef GG_MATCH_UI_MESSAGE_LIST_CLASS_METHODS_H
#define GG_MATCH_UI_MESSAGE_LIST_CLASS_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// Minimal node view of a message gadget (GadgetClass : LinkClass). Only the two
// facts the matched methods need are modelled:
//   * vtable slot 1 (+0x04) = GadgetClass::GetNext  -> `mov edx,[this]; call [edx+4]`
//   * GadgetClass::Y @ +0x10 (LinkClass base 0x0C: vptr/Next/Prev, then X@0x0C,Y@0x10)
struct TextLabelClass
{
    virtual ~TextLabelClass();             // slot 0 (destructor)
    virtual TextLabelClass* GetNext();     // slot 1 (+0x04) — walked here
    char _link_pad[0x10 - 0x04];           // LinkClass tail + GadgetClass::X (0x04..0x0F)
    int  Y;                                // +0x10
};

#if GG_TARGET_ABI_32
GG_STATIC_ASSERT(offsetof(TextLabelClass, Y) == 0x10);
#endif

// MessageListClass. Members confirmed numerically from the disassembly; the
// untouched runs (EditPos+EditLabel @0x1C..0x27, the two text buffers) are
// padded out so the touched offsets land exactly.
struct MessageListClass
{
    wchar_t* GetEditBuffer() const;        // GAMEMD 0x5D4400 __thiscall
    int      NumMessages() const;          // GAMEMD 0x5D4AA0 __thiscall
    void     ComputeY();                   // GAMEMD 0x5D4BF0 __thiscall

    TextLabelClass* MessageList;           // +0x00  list head
    int  MessagePos_X;                     // +0x04  MessagePos.X
    int  MessagePos_Y;                     // +0x08  MessagePos.Y
    int  MaxMessageCount;                  // +0x0C
    int  MaxCharacters;                    // +0x10
    int  Height;                           // +0x14
    unsigned char EnableOverflow;          // +0x18
    unsigned char IsEdit;                  // +0x19
    unsigned char AdjustEdit;              // +0x1A
    unsigned char _pad1b;                  // +0x1B
    char _gap1c[0x28 - 0x1C];              // +0x1C  EditPos(Point2D)+EditLabel
    wchar_t EditBuffer[162];               // +0x28
    wchar_t OverflowBuffer[162];           // +0x16C
    unsigned long EditCurrentPos;          // +0x2B0
    unsigned long EditInitialPos;          // +0x2B4
};

#if GG_TARGET_ABI_32
GG_STATIC_ASSERT(offsetof(MessageListClass, MessageList)    == 0x00);
GG_STATIC_ASSERT(offsetof(MessageListClass, MessagePos_Y)   == 0x08);
GG_STATIC_ASSERT(offsetof(MessageListClass, Height)         == 0x14);
GG_STATIC_ASSERT(offsetof(MessageListClass, IsEdit)         == 0x19);
GG_STATIC_ASSERT(offsetof(MessageListClass, AdjustEdit)     == 0x1A);
GG_STATIC_ASSERT(offsetof(MessageListClass, EditBuffer)     == 0x28);
GG_STATIC_ASSERT(offsetof(MessageListClass, EditInitialPos) == 0x2B4);
#endif

#endif  // GG_MATCH_UI_MESSAGE_LIST_CLASS_METHODS_H
