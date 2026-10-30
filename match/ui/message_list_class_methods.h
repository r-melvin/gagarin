// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
// Canonical message-list storage, native constructor5D39D0 and Init5D3A60.
// Complete embedded extent149C is bounded by Session+A28..1EC4.
#ifndef GG_MATCH_UI_MESSAGE_LIST_CLASS_METHODS_H
#define GG_MATCH_UI_MESSAGE_LIST_CLASS_METHODS_H
#include <stddef.h>
#include "../_rt/gg_static_assert.h"
class TextLabelClass;
struct MessageListClass
{
    // Declaration: GAMEMD 0x5D39D0 -- no arguments, EAX returns this.
    MessageListClass();
    // Declaration: GAMEMD 0x5D3A40 -- resets through Init, no root vtable.
    ~MessageListClass();
    // Declaration: GAMEMD 0x5D3A60 -- eleven stack words, RET2C.
    void Init(int x, int y, int count, int chars, int height, int editX, int editY,
        bool overflow, int start, int end, int width);
    // Declaration: GAMEMD 0x5D3BA0 (decl; reloc)
    TextLabelClass* FUN_005D3BA0(const wchar_t*, int, const wchar_t*, int, unsigned int, int, bool);
    // Declaration: GAMEMD 0x5D3FC0 -- four stack arguments.
    int FUN_005D3FC0(const wchar_t*, int, const wchar_t*, int);
    // Declaration: GAMEMD 0x5D3F60 -- text of the label whose +0x28 field equals the argument.
    const wchar_t* FUN_005D3F60(int key);
    // Declaration: GAMEMD 0x5D3F90 -- the label whose +0x28 field equals the argument.
    TextLabelClass* FUN_005D3F90(int key);
    // Declaration: GAMEMD 0x5D41E0 -- gives the edit label the focus while editing.
    void FUN_005D41E0();
    // Declaration: GAMEMD 0x5D4210 -- creates and returns the edit label.
    TextLabelClass* AddEdit(int a1, int a2, const wchar_t* text, char cursor, int width);
    // Declaration: GAMEMD 0x5D4390.
    void RemoveEdit();
    wchar_t* GetEditBuffer() const; // Declaration: GAMEMD 0x5D4400
    int Manage(); // Declaration: GAMEMD 0x5D4430
    void Draw(); // Declaration: GAMEMD 0x5D49A0
    int NumMessages() const; // Declaration: GAMEMD 0x5D4AA0
    void SetWidth(int width); // Declaration: GAMEMD 0x5D4AD0
    int TrimMessage(wchar_t* dest, wchar_t* src, int minLen, int maxLen, int fromEnd); // 0x5D4B20
    void ComputeY(); // Declaration: GAMEMD 0x5D4BF0

    TextLabelClass* MessageList;
    int MessagePos_X;
    int MessagePos_Y;
    int MaxMessageCount;
    int MaxCharacters;
    int Height;
    unsigned char EnableOverflow;
    unsigned char IsEdit;
    unsigned char AdjustEdit;
    unsigned char unknown_1B;
    int EditX;
    int EditY;
    TextLabelClass* EditLabel;
    wchar_t EditBuffer[162];
    wchar_t OverflowBuffer[162];
    unsigned long EditCurrentPos;
    unsigned long EditInitialPos;
    wchar_t CursorCharacter;
    char unknown_2BA[2];
    int OverflowStart;
    int OverflowEnd;
    int Width;
    wchar_t MessageBuffers[14][162];
    wchar_t BufferAvail[14];
};
GG_STATIC_ASSERT(offsetof(MessageListClass, MessageList) == 0x0);
GG_STATIC_ASSERT(sizeof(((MessageListClass*)0)->MessageList) == 0x4);
GG_STATIC_ASSERT(offsetof(MessageListClass, MessagePos_X) == 0x4);
GG_STATIC_ASSERT(sizeof(((MessageListClass*)0)->MessagePos_X) == 0x4);
GG_STATIC_ASSERT(offsetof(MessageListClass, MessagePos_Y) == 0x8);
GG_STATIC_ASSERT(sizeof(((MessageListClass*)0)->MessagePos_Y) == 0x4);
GG_STATIC_ASSERT(offsetof(MessageListClass, MaxMessageCount) == 0xC);
GG_STATIC_ASSERT(sizeof(((MessageListClass*)0)->MaxMessageCount) == 0x4);
GG_STATIC_ASSERT(offsetof(MessageListClass, MaxCharacters) == 0x10);
GG_STATIC_ASSERT(sizeof(((MessageListClass*)0)->MaxCharacters) == 0x4);
GG_STATIC_ASSERT(offsetof(MessageListClass, Height) == 0x14);
GG_STATIC_ASSERT(sizeof(((MessageListClass*)0)->Height) == 0x4);
GG_STATIC_ASSERT(offsetof(MessageListClass, EnableOverflow) == 0x18);
GG_STATIC_ASSERT(sizeof(((MessageListClass*)0)->EnableOverflow) == 0x1);
GG_STATIC_ASSERT(offsetof(MessageListClass, IsEdit) == 0x19);
GG_STATIC_ASSERT(sizeof(((MessageListClass*)0)->IsEdit) == 0x1);
GG_STATIC_ASSERT(offsetof(MessageListClass, AdjustEdit) == 0x1A);
GG_STATIC_ASSERT(sizeof(((MessageListClass*)0)->AdjustEdit) == 0x1);
GG_STATIC_ASSERT(offsetof(MessageListClass, EditX) == 0x1C);
GG_STATIC_ASSERT(sizeof(((MessageListClass*)0)->EditX) == 0x4);
GG_STATIC_ASSERT(offsetof(MessageListClass, EditY) == 0x20);
GG_STATIC_ASSERT(sizeof(((MessageListClass*)0)->EditY) == 0x4);
GG_STATIC_ASSERT(offsetof(MessageListClass, EditLabel) == 0x24);
GG_STATIC_ASSERT(sizeof(((MessageListClass*)0)->EditLabel) == 0x4);
GG_STATIC_ASSERT(offsetof(MessageListClass, EditBuffer) == 0x28);
GG_STATIC_ASSERT(sizeof(((MessageListClass*)0)->EditBuffer) == 0x144);
GG_STATIC_ASSERT(offsetof(MessageListClass, OverflowBuffer) == 0x16C);
GG_STATIC_ASSERT(sizeof(((MessageListClass*)0)->OverflowBuffer) == 0x144);
GG_STATIC_ASSERT(offsetof(MessageListClass, EditCurrentPos) == 0x2B0);
GG_STATIC_ASSERT(sizeof(((MessageListClass*)0)->EditCurrentPos) == 0x4);
GG_STATIC_ASSERT(offsetof(MessageListClass, EditInitialPos) == 0x2B4);
GG_STATIC_ASSERT(sizeof(((MessageListClass*)0)->EditInitialPos) == 0x4);
GG_STATIC_ASSERT(offsetof(MessageListClass, CursorCharacter) == 0x2B8);
GG_STATIC_ASSERT(sizeof(((MessageListClass*)0)->CursorCharacter) == 0x2);
GG_STATIC_ASSERT(offsetof(MessageListClass, OverflowStart) == 0x2BC);
GG_STATIC_ASSERT(sizeof(((MessageListClass*)0)->OverflowStart) == 0x4);
GG_STATIC_ASSERT(offsetof(MessageListClass, OverflowEnd) == 0x2C0);
GG_STATIC_ASSERT(sizeof(((MessageListClass*)0)->OverflowEnd) == 0x4);
GG_STATIC_ASSERT(offsetof(MessageListClass, Width) == 0x2C4);
GG_STATIC_ASSERT(sizeof(((MessageListClass*)0)->Width) == 0x4);
GG_STATIC_ASSERT(offsetof(MessageListClass, MessageBuffers) == 0x2C8);
GG_STATIC_ASSERT(sizeof(((MessageListClass*)0)->MessageBuffers) == 0x11B8);
GG_STATIC_ASSERT(offsetof(MessageListClass, BufferAvail) == 0x1480);
GG_STATIC_ASSERT(sizeof(((MessageListClass*)0)->BufferAvail) == 0x1C);
GG_STATIC_ASSERT(sizeof(MessageListClass) == 0x149C);
#endif
