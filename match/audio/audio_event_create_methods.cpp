// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes read off the user's retail gamemd.exe v1.001 at 0x405190 (start a live event for a descriptor)
//   and 0x4063B0 (find or create a descriptor by name). The live-event pool
//   string "AudioEvents : %05d - Max: %05d" (0x81624C) attests the counters at 0x87E28C / 0x87E290.

#include <string.h>
#include <new.h>
#include "../_layout/audio_event.h"

extern "C" int __cdecl _stricmp(const char* a, const char* b);

// GLOBAL: GAMEMD 0x87E2A0 -- nonzero once the audio subsystem is up.
extern int DAT_0087E2A0;
// GLOBAL: GAMEMD 0x816108 -- audio switch.
extern int DAT_00816108;
// GLOBAL: GAMEMD 0x81610C -- next event serial.
extern int DAT_0081610C;
// GLOBAL: GAMEMD 0x87E180 -- ring of live events.
extern ListNode DAT_0087E180;
// GLOBAL: GAMEMD 0x87E250 -- ring of descriptors.
extern ListNode DAT_0087E250;
// GLOBAL: GAMEMD 0x87E28C -- live event count.
extern int DAT_0087E28C;
// GLOBAL: GAMEMD 0x87E290 -- high-water mark of the live event count.
extern int DAT_0087E290;
// GLOBAL: GAMEMD 0x87E2A4 -- event pool ready.
extern int DAT_0087E2A4;
// GLOBAL: GAMEMD 0x87E2A8 -- free pool of event blocks.
extern Obj_00407520* DAT_0087E2A8;

// FUNCTION: GAMEMD 0x405190
// PARTIAL (86.6%, 84/97): identical instruction multiset; the residual is scheduling only. After the
// 0x4072D0 call retail stores the state word, then computes `LEA ECX,[ESI+0xB8]` and stores the other
// clears; cl hoists the LEA ahead of the state store, and after the 0x401000 call retail stores +0x158
// before loading EDX/ECX for the ring splice where cl stores it after. Variants tried: statement orders
// of the five clears, the `Count > High` operand order (kept, it fixed the compare), `next` read through
// the node or the event (kept).
// Start a live event for this descriptor. Take a block from the event pool; when it is empty, retire every
// ring event already marked finished (bit 0) and try again. The block is cleared and the event armed.
AudioEvent* AudioEventType::FUN_00405190()
{
    if (DAT_00816108 == 0 || DAT_0087E2A4 == 0 || unknown_0C == 0)
        return 0;

    AudioEvent* event = (AudioEvent*)DAT_0087E2A8->FUN_00407520();
    if (event == 0) {
        if (DAT_0087E2A0 != 0) {
            ListNode* node = DAT_0087E180.Prev;
            if (node != &DAT_0087E180) {
                do {
                    AudioEvent* done = (AudioEvent*)node;
                    ListNode* next = done->Prev;
                    if (done->Flags & 1) {
                        node->FUN_00407450();
                        done->Serial = 0;
                        if (done->Flags & 0x80)
                            delete done;
                        else
                            DAT_0087E2A8->FUN_00407530(done);
                        DAT_0087E28C--;
                    }
                    node = next;
                } while (node != &DAT_0087E180);
            }
        }
        event = (AudioEvent*)DAT_0087E2A8->FUN_00407520();
        if (event == 0)
            return 0;
    }

    DAT_0087E28C++;
    if (DAT_0087E28C > DAT_0087E290)
        DAT_0087E290 = DAT_0087E28C;

    memset(event, 0, sizeof(AudioEvent));
    event->EventType = this;
    event->FUN_004072D0();
    event->State = 0;
    event->unknown_154 = 0;
    event->unknown_268 = 0;
    event->unknown_1E0 = 0;
    event->SubCount = 0;
    FUN_00401000(&event->Timers);
    event->unknown_158 = 0;
    DAT_0087E180.FUN_00407420(event);
    event->Serial = DAT_0081610C;
    DAT_0081610C++;
    return event;
}

// FUNCTION: GAMEMD 0x4063B0
// The descriptor named `name`, created with its defaults on first use; null while audio is off.
AudioEventType* AudioEventType::FUN_004063B0(const char* name)
{
    if (DAT_0087E2A0 == 0)
        return 0;

    ListNode* node = DAT_0087E250.FUN_004073C0();
    while (node) {
        if (_stricmp(name, ((AudioEventType*)node)->Name) == 0)
            break;
        node = node->FUN_004073E0();
    }
    if (node)
        return (AudioEventType*)node;

    AudioEventType* type = (AudioEventType*)operator new(sizeof(AudioEventType));
    // Retail zeroes the 0x148 bytes twice (two `REP STOSD` of 0x52 dwords) before arming the link.
    memset(type, 0, sizeof(AudioEventType));
    memset(type, 0, sizeof(AudioEventType));
    type->FUN_004072D0();
    type->unknown_0C = 1;
    type->Control = 0;
    type->Type = 0x20;
    type->Limit = 3;
    type->Priority = 2;
    type->Range = 10;
    type->MinVolume = 0.2f;
    FUN_00407100(&type->Volume, 0x4000);
    strncpy(type->Name, name, 0x1F);
    type->Name[0x1F] = 0;
    DAT_0087E250.FUN_00407420(type);
    return type;
}
