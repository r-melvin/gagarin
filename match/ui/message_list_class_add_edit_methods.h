// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x5D4210 and agree member-for-member with the already
//   matched match/ui/message_list_class_init_methods.h and
//   message_list_class_manage_methods.h (read, not edited): the list head
//   `[ESI]`, MessagePos.Y `[ESI+0x8]`, MaxMessageCount `[ESI+0xC]`, Height
//   `[ESI+0x14]`, IsEdit `[ESI+0x19]`, AdjustEdit `[ESI+0x1A]`, EditPos
//   `[ESI+0x1C]`/`[ESI+0x20]`, EditLabel `[ESI+0x24]`, the 0x144-byte
//   EditBuffer at `LEA EBP,[ESI+0x28]` (zeroed by `MOV ECX,0x51; REP STOSD`),
//   OverflowBuffer `[ESI+0x16C]`, EditCurrentPos `[ESI+0x2B0]`,
//   EditInitialPos `[ESI+0x2B4]`, the cursor `MOV word [ESI+0x2B8],AX`
//   (MOVSX'd from a byte argument), Width `[ESI+0x2C4]`, the fourteen
//   0x144-byte message buffers from `LEA ECX,[ESI+0x2C8]` (`ADD ECX,0x144`)
//   and the fourteen word flags from `LEA EAX,[ESI+0x1480]`
//   (`MOV word [EAX],1`). On the label: `[EDI+0x30]` (Text), `[EAX+0x10]`
//   (Y), `[EAX+0x38]` (the width the label draws to), and the vtable slots
//   +0x00 (scalar deleting destructor, `PUSH 1`), +0x04 (GetNext), +0x24
//   (unlink, returns the new head) and +0x50 (release the edit label).
//   Five stack arguments (`RET 0x14`), read back after the four pushes as
//   `[ESP+0x14]`..`[ESP+0x24]`. Helpers: the empty wide string at 0x887734,
//   CRT wcscpy 0x7CA489, wcslen 0x7CA405, operator new 0x7C8E17 with
//   `PUSH 0x4C`, the label constructor 0x72A440 and the no-argument
//   0x778180. Names cross-checked against YRpp MessageListClass /
//   TextLabelClass.
#ifndef GG_MATCH_UI_MESSAGE_LIST_CLASS_ADD_EDIT_METHODS_H
#define GG_MATCH_UI_MESSAGE_LIST_CLASS_ADD_EDIT_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

extern "C" {
// LIBRARY: GAMEMD 0x7CA489 (decl; reloc) — CRT wcscpy.
wchar_t* __cdecl wcscpy(wchar_t* dst, const wchar_t* src);
// LIBRARY: GAMEMD 0x7CA405 (decl; reloc) — CRT wcslen.
unsigned int __cdecl wcslen(const wchar_t* s);
// LIBRARY: GAMEMD 0x7C8E17 (decl; reloc) — operator new, __cdecl.
void* __cdecl FUN_007C8E17(unsigned int size);
void* __cdecl memset(void* dst, int value, unsigned int count);
}

// FUNCTION: GAMEMD 0x778180 (decl; reloc) — takes nothing, returns nothing.
void __cdecl FUN_00778180();

// GLOBAL: GAMEMD 0x887734 — the empty wide string substituted for a null text.
extern wchar_t DAT_00887734[];

// A displayed message (TextLabelClass : GadgetClass : LinkClass). Slot 0 is
// the scalar deleting destructor, slot 1 (+0x04) returns the next gadget,
// slot 9 (+0x24) unlinks and returns the new head, and slot 20 (+0x50) is the
// one the edit label is retired through.
struct Label_005D4210
{
    virtual ~Label_005D4210();                 // +0x00
    virtual Label_005D4210* GetNext();         // +0x04
    virtual void Slot_08();
    virtual void Slot_0C();
    virtual void Slot_10();
    virtual void Slot_14();
    virtual void Slot_18();
    virtual void Slot_1C();
    virtual void Slot_20();
    virtual Label_005D4210* Remove();          // +0x24
    virtual void Slot_28();
    virtual void Slot_2C();
    virtual void Slot_30();
    virtual void Slot_34();
    virtual void Slot_38();
    virtual void Slot_3C();
    virtual void Slot_40();
    virtual void Slot_44();
    virtual void Slot_48();
    virtual void Slot_4C();
    virtual void Slot_50();                    // +0x50

    char     _pad004[0x10 - 0x04];             // +0x0004
    int      Y;                                // +0x0010
    char     _pad014[0x30 - 0x14];             // +0x0014
    wchar_t* Text;                             // +0x0030
    char     _pad034[4];                       // +0x0034
    int      At_38;                            // +0x0038  drawing width

    // FUNCTION: GAMEMD 0x72A440 (decl; reloc) — the label constructor.
    Label_005D4210* Construct(const wchar_t* text, int x, int y, int a4, int a5);
};
GG_STATIC_ASSERT(offsetof(Label_005D4210, Y)     == 0x10);
GG_STATIC_ASSERT(offsetof(Label_005D4210, Text)  == 0x30);
GG_STATIC_ASSERT(offsetof(Label_005D4210, At_38) == 0x38);

struct MessageList_005D4210
{
    Label_005D4210* MessageList;               // +0x0000  list head
    int             MessagePos_X;              // +0x0004
    int             MessagePos_Y;              // +0x0008
    int             MaxMessageCount;           // +0x000C
    int             MaxCharacters;             // +0x0010
    int             Height;                    // +0x0014
    unsigned char   EnableOverflow;            // +0x0018
    unsigned char   IsEdit;                    // +0x0019
    unsigned char   AdjustEdit;                // +0x001A
    char            _pad01B[1];                // +0x001B
    int             EditX;                     // +0x001C
    int             EditY;                     // +0x0020
    Label_005D4210* EditLabel;                 // +0x0024
    wchar_t         EditBuffer[162];           // +0x0028
    wchar_t         OverflowBuffer[162];       // +0x016C
    int             EditCurrentPos;            // +0x02B0
    int             EditInitialPos;            // +0x02B4
    wchar_t         CursorCharacter;           // +0x02B8
    char            _pad2BA[2];                // +0x02BA
    int             OverflowStart;             // +0x02BC
    int             OverflowEnd;               // +0x02C0
    int             Width;                     // +0x02C4
    wchar_t         MessageBuffers[14][162];   // +0x02C8
    wchar_t         BufferAvail[14];           // +0x1480

    // FUNCTION: GAMEMD 0x5D4210 — MessageListClass::AddEdit.
    Label_005D4210* AddEdit(int a1, int a2, const wchar_t* text, char cursor,
                            int width);
};
GG_STATIC_ASSERT(offsetof(MessageList_005D4210, MessagePos_Y)    == 0x008);
GG_STATIC_ASSERT(offsetof(MessageList_005D4210, MaxMessageCount) == 0x00C);
GG_STATIC_ASSERT(offsetof(MessageList_005D4210, Height)          == 0x014);
GG_STATIC_ASSERT(offsetof(MessageList_005D4210, IsEdit)          == 0x019);
GG_STATIC_ASSERT(offsetof(MessageList_005D4210, AdjustEdit)      == 0x01A);
GG_STATIC_ASSERT(offsetof(MessageList_005D4210, EditX)           == 0x01C);
GG_STATIC_ASSERT(offsetof(MessageList_005D4210, EditY)           == 0x020);
GG_STATIC_ASSERT(offsetof(MessageList_005D4210, EditLabel)       == 0x024);
GG_STATIC_ASSERT(offsetof(MessageList_005D4210, EditBuffer)      == 0x028);
GG_STATIC_ASSERT(offsetof(MessageList_005D4210, OverflowBuffer)  == 0x16C);
GG_STATIC_ASSERT(offsetof(MessageList_005D4210, EditCurrentPos)  == 0x2B0);
GG_STATIC_ASSERT(offsetof(MessageList_005D4210, EditInitialPos)  == 0x2B4);
GG_STATIC_ASSERT(offsetof(MessageList_005D4210, CursorCharacter) == 0x2B8);
GG_STATIC_ASSERT(offsetof(MessageList_005D4210, Width)           == 0x2C4);
GG_STATIC_ASSERT(offsetof(MessageList_005D4210, MessageBuffers)  == 0x2C8);
GG_STATIC_ASSERT(offsetof(MessageList_005D4210, BufferAvail)     == 0x1480);
GG_STATIC_ASSERT(sizeof(MessageList_005D4210) == 0x149C);

#endif  // GG_MATCH_UI_MESSAGE_LIST_CLASS_ADD_EDIT_METHODS_H
