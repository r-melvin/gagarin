// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x5D3A60: `[ESI+0x2C4]` (Width = arg11 - 8, logged
//   through the __cdecl 0x4068E0 with the format at 0x830680), the list
//   head `[ESI]` walked with label slot +0x24 (Remove, returns the new head)
//   and `PUSH 1; CALL [vtbl+0]` (scalar deleting destructor), the seven
//   dword fill of 0x10001 at `[ESI+0x1480]` (fourteen wchar_t BufferAvail
//   set to 1), `byte [ESI+0x19]` (IsEdit) guarding the delete of
//   `[ESI+0x24]` (EditLabel), then the member run `[+0x04]` X, `[+0x08]` Y,
//   `[+0x0C]` MaxMessageCount (capped 14), `[+0x10]` MaxCharacters (capped
//   0x70), `[+0x14]` = 0x13 Height, `byte [+0x18]` EnableOverflow (arg 8
//   read as a byte), `byte [+0x1A]` AdjustEdit, `[+0x1C]`/`[+0x20]` EditPos,
//   `word [+0x28]` EditBuffer[0], `word [+0x16C]` OverflowBuffer[0],
//   `[+0x2B0]`/`[+0x2B4]` edit positions, `word [+0x2B8]` cursor,
//   `[+0x2BC]`/`[+0x2C0]` OverflowStart/End clamped against MaxCharacters.
//   Eleven stack arguments (`RET 0x2C`); arg 5 is never read. Names are
//   YRpp's MessageListClass.h (consult-only, no LICENSE); layout agrees with
//   match/ui/message_list_class_draw_methods.h.
#ifndef GG_MATCH_UI_MESSAGE_LIST_CLASS_INIT_METHODS_H
#define GG_MATCH_UI_MESSAGE_LIST_CLASS_INIT_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// STRING: GAMEMD 0x830680 — "MessageListClass::Init(Width: %d)\n".
extern const char STR_00830680[];
// FUNCTION: GAMEMD 0x4068E0 (decl; reloc) — printf-style log sink.
extern "C" void __cdecl FUN_004068E0(const char* format, ...);

// TextLabelClass as a list node: the scalar deleting destructor in slot 0
// and Remove (detach, return the new head) in slot +0x24.
struct Label_005D3A60
{
    virtual ~Label_005D3A60();               // +0x0000
    virtual void vf04();                     // +0x0004
    virtual void vf08();                     // +0x0008
    virtual void vf0C();                     // +0x000C
    virtual void vf10();                     // +0x0010
    virtual void vf14();                     // +0x0014
    virtual void vf18();                     // +0x0018
    virtual void vf1C();                     // +0x001C
    virtual void vf20();                     // +0x0020
    virtual Label_005D3A60* Remove();        // +0x0024
};

struct MessageList_005D3A60
{
    Label_005D3A60* MessageList;      // +0x0000
    int     MessageX;                 // +0x0004
    int     MessageY;                 // +0x0008
    int     MaxMessageCount;          // +0x000C
    int     MaxCharacters;            // +0x0010
    int     Height;                   // +0x0014
    bool    EnableOverflow;           // +0x0018
    bool    IsEdit;                   // +0x0019
    bool    AdjustEdit;               // +0x001A
    char    _pad01B[1];               // +0x001B
    int     EditX;                    // +0x001C
    int     EditY;                    // +0x0020
    Label_005D3A60* EditLabel;        // +0x0024
    wchar_t EditBuffer[162];          // +0x0028
    wchar_t OverflowBuffer[162];      // +0x016C
    int     EditCurrentPos;           // +0x02B0
    int     EditInitialPos;           // +0x02B4
    wchar_t CursorCharacter;          // +0x02B8
    char    _pad2BA[2];               // +0x02BA
    int     OverflowStart;            // +0x02BC
    int     OverflowEnd;              // +0x02C0
    int     Width;                    // +0x02C4
    wchar_t MessageBuffers[14][162];  // +0x02C8
    wchar_t BufferAvail[14];          // +0x1480

    // FUNCTION: GAMEMD 0x5D3A60 — MessageListClass::Init.
    void Init(int x, int y, int maxMessages, int maxChars, int height,
              int editX, int editY, bool enableOverflow, int overflowStart,
              int overflowEnd, int width);
};
GG_STATIC_ASSERT(offsetof(MessageList_005D3A60, MessageX)        == 0x004);
GG_STATIC_ASSERT(offsetof(MessageList_005D3A60, MaxMessageCount) == 0x00C);
GG_STATIC_ASSERT(offsetof(MessageList_005D3A60, MaxCharacters)   == 0x010);
GG_STATIC_ASSERT(offsetof(MessageList_005D3A60, Height)          == 0x014);
GG_STATIC_ASSERT(offsetof(MessageList_005D3A60, EnableOverflow)  == 0x018);
GG_STATIC_ASSERT(offsetof(MessageList_005D3A60, IsEdit)          == 0x019);
GG_STATIC_ASSERT(offsetof(MessageList_005D3A60, AdjustEdit)      == 0x01A);
GG_STATIC_ASSERT(offsetof(MessageList_005D3A60, EditX)           == 0x01C);
GG_STATIC_ASSERT(offsetof(MessageList_005D3A60, EditY)           == 0x020);
GG_STATIC_ASSERT(offsetof(MessageList_005D3A60, EditLabel)       == 0x024);
GG_STATIC_ASSERT(offsetof(MessageList_005D3A60, EditBuffer)      == 0x028);
GG_STATIC_ASSERT(offsetof(MessageList_005D3A60, OverflowBuffer)  == 0x16C);
GG_STATIC_ASSERT(offsetof(MessageList_005D3A60, EditCurrentPos)  == 0x2B0);
GG_STATIC_ASSERT(offsetof(MessageList_005D3A60, EditInitialPos)  == 0x2B4);
GG_STATIC_ASSERT(offsetof(MessageList_005D3A60, CursorCharacter) == 0x2B8);
GG_STATIC_ASSERT(offsetof(MessageList_005D3A60, OverflowStart)   == 0x2BC);
GG_STATIC_ASSERT(offsetof(MessageList_005D3A60, OverflowEnd)     == 0x2C0);
GG_STATIC_ASSERT(offsetof(MessageList_005D3A60, Width)           == 0x2C4);
GG_STATIC_ASSERT(offsetof(MessageList_005D3A60, MessageBuffers)  == 0x2C8);
GG_STATIC_ASSERT(offsetof(MessageList_005D3A60, BufferAvail)     == 0x1480);
GG_STATIC_ASSERT(sizeof(MessageList_005D3A60) == 0x149C);

#endif  // GG_MATCH_UI_MESSAGE_LIST_CLASS_INIT_METHODS_H
