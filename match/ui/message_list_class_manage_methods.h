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

#include "../core/game_timing_methods.h"
#include "message_list_class_methods.h"

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

#endif
