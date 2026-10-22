// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets, slots and globals read numerically off the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI at 0x5D4430: the list head
//   `[EDI]`, MessagePos.Y `[EDI+0x8]`, Height `[EDI+0x14]`, IsEdit
//   `[EDI+0x19]`, AdjustEdit `[EDI+0x1A]`, the fourteen 0x144-byte message
//   buffers walked from `LEA ECX,[EDI+0x2C8]` (`ADD ECX,0x144`) and the
//   fourteen word flags from `LEA EAX,[EDI+0x1480]` (`MOV word [EAX],1`);
//   on the label: the expiry tick `[ESI+0x24]`, the text pointer
//   `[ESI+0x30]`, Y `[EAX+0x10]`, vtable slots +0x00 (scalar deleting dtor,
//   `PUSH 1`), +0x04 (GetNext) and +0x24 (unlink, returns the new head).
//   The elapsed timer is the 12-byte global at 0x887338 (StartTime
//   0x887338, the clock object 0x88733C reached by `MOV ECX,0x88733C; CALL
//   0x6C8C40`, TimeLeft 0x887340). Names cross-checked against YRpp
//   (every offset
//   reconfirmed above).
#ifndef GG_MATCH_UI_MESSAGE_LIST_CLASS_MANAGE_METHODS_H
#define GG_MATCH_UI_MESSAGE_LIST_CLASS_MANAGE_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// The clock member whose GetTime is a __thiscall leaf that ignores `this`
// (matched in match/platform/system_query_methods.cpp).
struct GameClockClass
{
    // FUNCTION: GAMEMD 0x6C8C40 (decl; reloc)
    int GetTime();
};

// An elapsed-time timer: while started (StartTime != -1) its value is the
// accumulated TimeLeft plus the span since it started.
struct TimerStruct_005D4430
{
    int            StartTime;   // +0x0000
    GameClockClass Clock;       // +0x0004
    int            TimeLeft;    // +0x0008

    int GetValue()
    {
        int value = TimeLeft;
        if (StartTime != -1) {
            value += Clock.GetTime() - StartTime;
        }
        return value;
    }
};
GG_STATIC_ASSERT(offsetof(TimerStruct_005D4430, Clock) == 0x4);
GG_STATIC_ASSERT(offsetof(TimerStruct_005D4430, TimeLeft) == 0x8);
GG_STATIC_ASSERT(sizeof(TimerStruct_005D4430) == 0xC);

// GLOBAL: GAMEMD 0x887338 -- the message-list elapsed timer.
extern TimerStruct_005D4430 MessageTimer;

// A displayed message (TextLabelClass : GadgetClass : LinkClass). Slot 0 is
// the scalar deleting destructor, slot 1 returns the next gadget and slot 9
// (+0x24) unlinks the gadget from its list and returns the new head.
struct TextLabelClass
{
    virtual ~TextLabelClass();                 // +0x00
    virtual TextLabelClass* GetNext();         // +0x04
    virtual void Slot_08();                    // +0x08
    virtual void Slot_0C();                    // +0x0C
    virtual void Slot_10();                    // +0x10
    virtual void Slot_14();                    // +0x14
    virtual void Slot_18();                    // +0x18
    virtual void Slot_1C();                    // +0x1C
    virtual void Slot_20();                    // +0x20
    virtual TextLabelClass* Remove();          // +0x24

    char     _pad004[0x10 - 0x04];             // +0x0004
    int      Y;                                // +0x0010
    char     _pad014[0x24 - 0x14];             // +0x0014
    int      At_24;                            // +0x0024  expiry tick
    char     _pad028[0x30 - 0x28];             // +0x0028
    wchar_t* Text;                             // +0x0030
};
GG_STATIC_ASSERT(offsetof(TextLabelClass, Y) == 0x10);
GG_STATIC_ASSERT(offsetof(TextLabelClass, At_24) == 0x24);
GG_STATIC_ASSERT(offsetof(TextLabelClass, Text) == 0x30);

struct MessageListClass
{
    TextLabelClass* MessageList;               // +0x0000  list head
    int             MessagePos_X;              // +0x0004
    int             MessagePos_Y;              // +0x0008
    int             MaxMessageCount;           // +0x000C
    int             MaxCharacters;             // +0x0010
    int             Height;                    // +0x0014
    unsigned char   EnableOverflow;            // +0x0018
    unsigned char   IsEdit;                    // +0x0019
    unsigned char   AdjustEdit;                // +0x001A
    char            _pad01B[0x2C8 - 0x1B];     // +0x001B
    wchar_t         MessageBuffers[14][162];   // +0x02C8
    wchar_t         BufferAvail[14];           // +0x1480

    // FUNCTION: GAMEMD 0x5D4430
    int Manage();
};
GG_STATIC_ASSERT(offsetof(MessageListClass, MessagePos_Y) == 0x08);
GG_STATIC_ASSERT(offsetof(MessageListClass, Height) == 0x14);
GG_STATIC_ASSERT(offsetof(MessageListClass, IsEdit) == 0x19);
GG_STATIC_ASSERT(offsetof(MessageListClass, AdjustEdit) == 0x1A);
GG_STATIC_ASSERT(offsetof(MessageListClass, MessageBuffers) == 0x2C8);
GG_STATIC_ASSERT(sizeof(wchar_t) * 162 == 0x144);
GG_STATIC_ASSERT(offsetof(MessageListClass, BufferAvail) == 0x1480);

#endif  // GG_MATCH_UI_MESSAGE_LIST_CLASS_MANAGE_METHODS_H
