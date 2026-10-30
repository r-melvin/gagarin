// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra; shared address-named view (one definition for every TU that uses it).
//   Offsets read numerically off the user's retail gamemd.exe v1.001 through the local Ghidra CLI at
//   0x405D40 (Stop) and 0x405C00 (the release body shared with it) and the controller methods
//   0x4060F0 / 0x406130:
//     event  [ESI+0x18] Flags (TEST byte,1 / TEST byte,2 / OR ..,1), [ESI+0x1C] State (set to 4),
//            [ESI+0x24] EventType (the descriptor the event plays), [ESI+0x28] the sub-object
//            array walked by LEA EDI,[ESI+0x28], [ESI+0xA8] its count, [ESI+0xB0] Peer,
//            [ESI+0x138] Serial (copied to the controller's Stamp), [ESI+0x278] the owning controller
//     peer   [..+0x90], [..+0x98], [..+0x9C], [..+0xB4], [..+0xB8], [..+0xBC],
//            [..+0xC0] Voice (back-pointer, CMP ESI,[ECX+0xC0])
//   The live-event pool string "AudioEvents : %05d - Max: %05d" (0x81624C) attests the name AudioEvent;
//   the descriptor name AudioEventType is a placeholder. Touched-prefix model of the 0x280-byte event.
#ifndef GG_MATCH__LAYOUT_AUDIO_EVENT_H
#define GG_MATCH__LAYOUT_AUDIO_EVENT_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../core/triple_timer_init_methods.h"
#include "../core/tail_call_methods.h"
#include "audio_controller.h"
#include "audio_event_type.h"

struct Peer_00405D40
{
    char _pad000[0x10];
    Timer_00401000 unknown_10;
    char unknown_38[0x90 - 0x38];       // +0x0000
    int  At_90;               // +0x0090
    int At_94;
    int  At_98;               // +0x0098
    int  At_9C;               // +0x009C
    char _pad0A0[0xB0 - 0xA0];
    int (__fastcall* unknown_B0)(void*);
    int  At_B4;               // +0x00B4
    int (__fastcall* At_B8)(void*);               // +0x00B8
    int (__fastcall* At_BC)(void*);               // +0x00BC
    AudioEvent* Voice;    // +0x00C0
    char unknown_C4[0x1A8 - 0xC4];
    unsigned __int64 unknown_1A8;
    unsigned __int64 unknown_1B0;
    // FUNCTION: GAMEMD 0x402790 (decl; reloc)
    void __fastcall FUN_00402790(Obj_00408500b*);
    // FUNCTION: GAMEMD 0x402720 (decl; reloc)
    int FUN_00402720();

    // FUNCTION: GAMEMD 0x4025B0 (decl; reloc) — __thiscall forwarder.
    void FUN_004025B0();
    // FUNCTION: GAMEMD 0x4026F0 (decl; reloc) — __thiscall forwarder.
    void FUN_004026F0();
    // FUNCTION: GAMEMD 0x4026A0 (decl; reloc) — __thiscall forwarder.
    void FUN_004026A0();
    // FUNCTION: GAMEMD 0x4026B0 (decl; reloc) — __thiscall forwarder.
    void FUN_004026B0();
};
GG_STATIC_ASSERT(offsetof(Peer_00405D40, unknown_10) == 0x10);
GG_STATIC_ASSERT(offsetof(Peer_00405D40, unknown_1A8) == 0x1A8);
GG_STATIC_ASSERT(offsetof(Peer_00405D40, unknown_1B0) == 0x1B0);
GG_STATIC_ASSERT(offsetof(Peer_00405D40, At_90) == 0x90);
GG_STATIC_ASSERT(offsetof(Peer_00405D40, At_94) == 0x94);
GG_STATIC_ASSERT(offsetof(Peer_00405D40, unknown_B0) == 0xB0);
GG_STATIC_ASSERT(offsetof(Peer_00405D40, At_98) == 0x98);
GG_STATIC_ASSERT(offsetof(Peer_00405D40, At_9C) == 0x9C);
GG_STATIC_ASSERT(offsetof(Peer_00405D40, At_B4) == 0xB4);
GG_STATIC_ASSERT(offsetof(Peer_00405D40, At_B8) == 0xB8);
GG_STATIC_ASSERT(offsetof(Peer_00405D40, At_BC) == 0xBC);
GG_STATIC_ASSERT(offsetof(Peer_00405D40, Voice) == 0xC0);

// A level sink at AudioEvent +0xB8: a ramp timer whose level is set, then latched.
struct AudioEventSink
{
    Timer_00401000 Timer;   // +0x00
    int Set(int scaled)
    {
        FUN_00407150(&Timer, scaled);
        return FUN_004071C0(&Timer);
    }
};
GG_STATIC_ASSERT(offsetof(AudioEventSink, Timer) == 0);

struct AudioEvent
{
    // FUNCTION: GAMEMD 0x406190 -- scale the clamped level by the descriptor's ramp and apply it to Sink
    void __fastcall FUN_00406190(unsigned level);
    // FUNCTION: GAMEMD 0x4061D0 -- AdjustAudioEventVolume
    int __fastcall FUN_004061D0(unsigned level);
    // FUNCTION: GAMEMD 0x406270 -- AdjustAudioEventPanning
    void __fastcall AdjustAudioEventPanning(unsigned pan);
    // FUNCTION: GAMEMD 0x406310 -- the descriptor this event plays
    AudioEventType* GetEventType();

    char _pad000[0x18];       // +0x0000
    union {
        unsigned int  Flags;      // +0x0018  bit 0 = already stopped
        unsigned char  FlagsLow;  // +0x0018  byte alias
        unsigned short FlagsWord; // +0x0018  word alias — the second flag test
                                  //          must differ in width from the
                                  //          first or cl CSEs the two tests
                                  //          into one load (see the .cpp).
    };
    int   State;              // +0x001C
    char  _pad020[0x24 - 0x20];
    AudioEventType* EventType; // +0x0024
    void* Subs[(0xA8 - 0x28) / 4];  // +0x0028
    int   SubCount;           // +0x00A8
    char  _pad0AC[0xB0 - 0xAC];
    Peer_00405D40* Peer;      // +0x00B0
    char  _pad0B4[0xB8 - 0xB4];
    AudioEventSink Sink;      // +0x00B8
    char  _pad0E0[0x108 - 0xE0];
    Timer_00401000 Channel;   // +0x0108 (pan; initialized by 0x4062C0)
    char  _pad130[0x138 - 0x130];
    unsigned int Serial;      // +0x0138
    char  _pad13C[0x278 - 0x13C];
    AudioController* Controller; // +0x0278 (stored by SetEvent)
    char  _pad27C[0x280 - 0x27C];
};
GG_STATIC_ASSERT(offsetof(AudioEvent, Flags) == 0x18);
GG_STATIC_ASSERT(offsetof(AudioEvent, State) == 0x1C);
GG_STATIC_ASSERT(offsetof(AudioEvent, EventType) == 0x24);
GG_STATIC_ASSERT(offsetof(AudioEvent, Subs) == 0x28);
GG_STATIC_ASSERT(offsetof(AudioEvent, SubCount) == 0xA8);
GG_STATIC_ASSERT(offsetof(AudioEvent, Peer) == 0xB0);
GG_STATIC_ASSERT(offsetof(AudioEvent, Sink) == 0xB8);
GG_STATIC_ASSERT(offsetof(AudioEvent, Channel) == 0x108);
GG_STATIC_ASSERT(offsetof(AudioEvent, Serial) == 0x138);
GG_STATIC_ASSERT(offsetof(AudioEvent, Controller) == 0x278);
GG_STATIC_ASSERT(sizeof(AudioEvent) == 0x280);


#endif
