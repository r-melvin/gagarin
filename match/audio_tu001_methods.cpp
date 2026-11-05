// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//   Audio event and peer helpers from the first original translation unit (0x403FA0..0x4062C0).
//
// Ordered ascending by retail address.

#include <string.h>
#include "_layout/audio_event.h"
#include "small_misc7_methods.h"
#include "engine_core_globals.h"
#include "module_tu002.h"
#include "leaf_accessor_methods.h"
#include "randomizer.h"
#include "audio_stop_methods.h"

// GLOBAL: GAMEMD 0x87E29C -- peer pool.
extern void* DAT_0087E29C;

// GLOBAL: GAMEMD 0x87E180 -- ring of live events.
extern ListNode DAT_0087E180;
// GLOBAL: GAMEMD 0x87E250 -- ring of descriptors.
extern ListNode DAT_0087E250;
// GLOBAL: GAMEMD 0x87E298 -- the reporting manager, null while reporting is off.
struct Mgr_00401B00;
extern Mgr_00401B00* DAT_0087E298;
// GLOBAL: GAMEMD 0x87E2A4 -- event pool ready.
extern int DAT_0087E2A4;
// FUNCTION: GAMEMD 0x401B00 (decl; reloc) -- tear the manager down.
void FUN_00401B00(Mgr_00401B00* self);
// GLOBAL: GAMEMD 0x87E28C -- live event count.
extern int DAT_0087E28C;

// FUNCTION: GAMEMD 0x402030 (decl; reloc) -- reached by a tail jump, so spelled as a free __fastcall function
void* __fastcall FUN_00402030(Obj_00402000* sub);

// FUNCTION: GAMEMD 0x403FA0
// PARTIAL (83.3%, 114/114 instructions): identical multiset; the residual is scheduling only. Retail
// loads the next link before the flag byte, cl loads the flag byte first; the flags OR is hoisted
// ahead of the stores, and the second ring walk's head load sits after the pop. Variants: head hoisted
// above the enabled test (2.5%), second walk as an inline helper (83.3%, same bytes).
// Shut the audio event system down: stop and retire every live event, drop the finished ones, delete all
// descriptors, the reporting manager and the event pool, then clear the ready flags.
void __cdecl FUN_00403FA0()
{
    if (g_AudioEnabled != 0) {
        ListNode* node = DAT_0087E180.Prev;
        if (node != &DAT_0087E180) {
            do {
                AudioEvent* event = (AudioEvent*)node;
                ListNode* next = event->Prev;
                if ((event->FlagsLow & 1) == 0) {
                    event->FUN_00404140();
                    for (int i = 0; i < event->SubCount; ++i) {
                        FUN_00401F90(event->Subs[i]);
                        event->Subs[i] = 0;
                    }
                    event->SubCount = 0;
                    event->State = 4;
                    event->Serial = 0;
                    event->Controller = 0;
                    event->Flags = event->Flags | 1;
                }
                node->FUN_00407450();
                event->Serial = 0;
                if (event->FlagsLow & 0x80)
                    delete event;
                else
                    DAT_0087E2A8->FUN_00407530(event);
                DAT_0087E28C--;
                node = next;
            } while (node != &DAT_0087E180);
        }
    }
    if (g_AudioEnabled != 0) {
        ListNode* node = DAT_0087E180.Prev;
        if (node != &DAT_0087E180) {
            do {
                AudioEvent* event = (AudioEvent*)node;
                ListNode* next = event->Prev;
                if (event->FlagsLow & 1) {
                    node->FUN_00407450();
                    event->Serial = 0;
                    if (event->FlagsLow & 0x80)
                        delete event;
                    else
                        DAT_0087E2A8->FUN_00407530(event);
                    DAT_0087E28C--;
                }
                node = next;
            } while (node != &DAT_0087E180);
        }
    }
    for (ListNode* node = DAT_0087E250.FUN_004073C0(); node != 0; node = DAT_0087E250.FUN_004073C0()) {
        node->FUN_00407450();
        delete (AudioEventType*)node;
    }
    if (DAT_0087E298 != 0) {
        FUN_00401B00(DAT_0087E298);
        DAT_0087E298 = 0;
    }
    if (DAT_0087E2A8 != 0) {
        DAT_0087E2A8->FUN_00407510();
        DAT_0087E2A8 = 0;
    }
    DAT_0087E2A4 = 0;
    g_AudioEnabled = 0;
}

// FUNCTION: GAMEMD 0x4047B0
// PARTIAL (86.6%, 82/82 instructions): only the last block differs. Retail tests the flag word in
// memory, loads the sub-object count, then reloads and ORs the flags; cl loads the flags once and
// reuses them. Variants: test before or after the count load, `|=` against `= ... |`.
void* __fastcall AudioEvent::FUN_004047B0()
{
    AudioEventType* type = EventType;
    unsigned int delay = type->DelayLow;
    int control = type->Control;
    if (delay < 0x21u || (Flags & 0x20) != 0) {
        int count = unknown_1E0;
        if (count != 0 && (Flags & 0x20) == 0) {
            if ((control & 2) != 0) {
                int pick = DAT_00886B88.RandomRanged(0, count - 1);
                unknown_AC = Order[pick];
                for (int i = pick; i < unknown_1E0 - 1; i++)
                    Order[i] = Order[i + 1];
            } else {
                unknown_AC++;
            }
            unknown_1E0--;
            return FUN_00402030(Subs[unknown_AC]);
        }
        if ((control & 1) != 0 && (Flags & 0x20) == 0) {
            int loops = type->Loop;
            if (loops == 0 || unknown_1E4 < loops - 1) {
                unknown_1E4++;
                return FUN_00404700();
            }
        }
        if ((control & 0x40) != 0) {
            int n = SubCount;
            if ((Flags & 0x10) == 0 && n >= 1) {
                Flags = Flags | 0x10;
                return FUN_00402030(Subs[n - 1]);
            }
        }
    }
    return 0;
}

// FUNCTION: GAMEMD 0x404E70
// PARTIAL (80.7%, 88/88 instructions): scheduling only. Retail loads the next link before the flag
// byte; cl loads the flag byte first, and hoists the flags load ahead of the stores. Variants: next
// read through the node or the event, the flag byte read into a local first.
void __cdecl FUN_00404E70()
{
    if (g_AudioEnabled != 0) {
        ListNode* node = DAT_0087E180.Prev;
        if (node != &DAT_0087E180) {
            do {
                AudioEvent* event = (AudioEvent*)node;
                ListNode* next = event->Prev;
                if ((event->FlagsLow & 1) == 0) {
                    Peer_00405D40* peer = event->Peer;
                    if (peer != 0 && event == peer->Voice) {
                        if ((event->FlagsWord & 2) != 0) {
                            peer->FUN_004025B0();
                        }
                        event->Peer->FUN_004026F0();
                        event->Peer->Voice = 0;
                        event->Peer->At_BC = 0;
                        event->Peer->At_B4 = 0;
                        event->Peer->At_B8 = 0;
                        event->Peer->At_90 = 0;
                        event->Peer->At_98 = 0;
                        event->Peer->At_9C = 0;
                        event->Peer = 0;
                    }
                    for (int i = 0; i < event->SubCount; ++i) {
                        FUN_00401F90(event->Subs[i]);
                        event->Subs[i] = 0;
                    }
                    event->SubCount = 0;
                    event->State = 4;
                    event->Serial = 0;
                    event->Controller = 0;
                    event->Flags = event->Flags | 1;
                }
                node->FUN_00407450();
                event->Serial = 0;
                if (event->FlagsLow & 0x80)
                    delete event;
                else
                    DAT_0087E2A8->FUN_00407530(event);
                DAT_0087E28C--;
                node = next;
            } while (node != &DAT_0087E180);
        }
    }
}

// FUNCTION: GAMEMD 0x405B50
// Take a free voice record for a new sound: null while no pool exists, or when the best candidate still
// outranks the request; otherwise it is reset and tagged with the request's priority and looping flag.
Peer_00405D40* __fastcall FUN_00405B50(int priority, unsigned int flags)
{
    Peer_00405D40* peer = 0;
    if (DAT_0087E29C != 0) {
        peer = FUN_004035F0(DAT_0087E29C, 1);
        if (peer != 0) {
            if ((peer->At_A4 & 0x15) != 0 && peer->At_A0 > priority)
                return 0;
            peer->FUN_004025B0();
            peer->At_94 = DAT_0087E748;
            peer->At_9C = DAT_0087E758;
            peer->At_A0 = priority;
            if ((flags & 1) != 0)
                peer->At_A8 = -1;
            else
                peer->At_A8 = 0;
        }
    }
    return peer;
}

// FUNCTION: GAMEMD 0x405E80
// PARTIAL (92.9%, 85/85 instructions): the flags load is hoisted over the four stores before the OR
// (the recorded load-hoist class); everything else is identical. Variants: `|=`, a guarded OR (33.3%).
void AudioController::FUN_00405E80()
{
    if (g_AudioEnabled == 0) {
        EventType = 0;
        return;
    }
    if (AudioIndex != &AudioIDXData_Instance) {
        EventType = 0;
        return;
    }
    AudioEvent* voice = Event;
    if (voice == 0) {
        EventType = 0;
        return;
    }
    AudioEventType* token = voice->EventType;
    if (EventType != token || Stamp != voice->Serial) {
        Event = 0;
        EventType = 0;
        return;
    }
    if ((token->Control & 1) == 0 || token->Loop != 0) {
        EventType = 0;
        return;
    }
    if ((voice->Flags & 1) == 0) {
        Peer_00405D40* peer = voice->Peer;
        if (peer != 0 && voice == peer->Voice) {
            if ((voice->FlagsWord & 2) != 0) {
                peer->FUN_004025B0();
            }
            voice->Peer->FUN_004026F0();
            voice->Peer->Voice = 0;
            voice->Peer->At_BC = 0;
            voice->Peer->At_B4 = 0;
            voice->Peer->At_B8 = 0;
            voice->Peer->At_90 = 0;
            voice->Peer->At_98 = 0;
            voice->Peer->At_9C = 0;
            voice->Peer = 0;
        }
        for (int i = 0; i < voice->SubCount; ++i) {
            FUN_00401F90(voice->Subs[i]);
            voice->Subs[i] = 0;
        }
        voice->SubCount = 0;
        voice->State = 4;
        voice->Serial = 0;
        voice->Controller = 0;
        voice->Flags = voice->Flags | 1;
    }
    Event = 0;
    EventType = 0;
}

// FUNCTION: GAMEMD 0x406670
// Start the named descriptor's sound at a volume given in 1/256ths of the full ramp, if one exists.
void FUN_00406670(const char* name, int level)
{
    if (g_AudioEnabled != 0) {
        ListNode* node = DAT_0087E250.FUN_004073C0();
        while (node) {
            if (_stricmp(name, ((AudioEventType*)node)->Name) == 0)
                break;
            node = node->FUN_004073E0();
        }
        if (node) {
            AudioEvent* event = ((AudioEventType*)node)->FUN_00405190();
            if (event) {
                unsigned int scaled = (unsigned int)((__int64)level * 0x4000 / 0x100);
                unsigned int clamped = scaled;
                if (scaled > 0x4000)
                    clamped = 0x4000;
                else if ((int)scaled < 0)
                    clamped = 0;
                event->Sink.Set((event->EventType->Volume.Value >> 16) * clamped >> 14);
            }
        }
    }
}
