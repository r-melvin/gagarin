// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 through
//   the local Ghidra CLI at 0x405D40:
//     handle  [EAX+0x0] Voice, [EAX+0x4] Serial, [EAX+0x8] Token,
//             [EAX+0xC] Owner (CMP dword ptr [EAX+0xC],0x87E294)
//     voice   [ESI+0x18] Flags (TEST byte,1 / TEST byte,2 / OR ..,1),
//             [ESI+0x1C] State (set to 4), [ESI+0x24] Token,
//             [ESI+0x28] the sub-object array walked by LEA EDI,[ESI+0x28],
//             [ESI+0xA8] the array count, [ESI+0xB0] Peer,
//             [ESI+0x138] Serial, [ESI+0x278] unknown_278
//     peer    [..+0x90], [..+0x98], [..+0x9C], [..+0xB4], [..+0xB8],
//             [..+0xBC], [..+0xC0] Voice (back-pointer, CMP ESI,[ECX+0xC0])
//   The same handle/voice/peer shapes are pinned by 0x406060 in
//   match/audio/audio_end_looping_methods.h and by 0x405FD0 in
//   match/audio/sample_registry_methods.h; neither is edited — this TU
//   redeclares the parts it needs (plus the peer fields 0x90..0xBC and the
//   voice fields 0x1C/0x28/0xA8/0x278, which are new here) so it stands alone.
//   The parent map names 0x405D40 Audio::Stop (YRpp Audio.h, consult-only).
#ifndef GG_MATCH_AUDIO_AUDIO_STOP_METHODS_H
#define GG_MATCH_AUDIO_AUDIO_STOP_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0x87E2A0 — nonzero once the audio subsystem is up.
extern int DAT_0087E2A0;
// GLOBAL: GAMEMD 0x87E294 — the sample table; the handle's owner is compared
// against its address.
extern char DAT_0087E294[];

struct Voice_00405D40;

// FUNCTION: GAMEMD 0x401F90 (decl; reloc) — release one voice sub-object.
void __fastcall FUN_00401F90(void* sub);

struct Peer_00405D40
{
    char _pad000[0x90];       // +0x0000
    int  At_90;               // +0x0090
    char _pad094[0x98 - 0x94];
    int  At_98;               // +0x0098
    int  At_9C;               // +0x009C
    char _pad0A0[0xB4 - 0xA0];
    int  At_B4;               // +0x00B4
    int  At_B8;               // +0x00B8
    int  At_BC;               // +0x00BC
    Voice_00405D40* Voice;    // +0x00C0

    // FUNCTION: GAMEMD 0x4025B0 (decl; reloc) — __thiscall forwarder.
    void FUN_004025B0();
    // FUNCTION: GAMEMD 0x4026F0 (decl; reloc) — __thiscall forwarder.
    void FUN_004026F0();
};
GG_STATIC_ASSERT(offsetof(Peer_00405D40, At_90) == 0x90);
GG_STATIC_ASSERT(offsetof(Peer_00405D40, At_98) == 0x98);
GG_STATIC_ASSERT(offsetof(Peer_00405D40, At_9C) == 0x9C);
GG_STATIC_ASSERT(offsetof(Peer_00405D40, At_B4) == 0xB4);
GG_STATIC_ASSERT(offsetof(Peer_00405D40, At_B8) == 0xB8);
GG_STATIC_ASSERT(offsetof(Peer_00405D40, At_BC) == 0xBC);
GG_STATIC_ASSERT(offsetof(Peer_00405D40, Voice) == 0xC0);

struct Voice_00405D40
{
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
    void* Token;              // +0x0024
    void* Subs[(0xA8 - 0x28) / 4];  // +0x0028
    int   SubCount;           // +0x00A8
    char  _pad0AC[0xB0 - 0xAC];
    Peer_00405D40* Peer;      // +0x00B0
    char  _pad0B4[0x138 - 0xB4];
    int   Serial;             // +0x0138
    char  _pad13C[0x278 - 0x13C];
    int   At_278;             // +0x0278
};
GG_STATIC_ASSERT(offsetof(Voice_00405D40, Flags) == 0x18);
GG_STATIC_ASSERT(offsetof(Voice_00405D40, State) == 0x1C);
GG_STATIC_ASSERT(offsetof(Voice_00405D40, Token) == 0x24);
GG_STATIC_ASSERT(offsetof(Voice_00405D40, Subs) == 0x28);
GG_STATIC_ASSERT(offsetof(Voice_00405D40, SubCount) == 0xA8);
GG_STATIC_ASSERT(offsetof(Voice_00405D40, Peer) == 0xB0);
GG_STATIC_ASSERT(offsetof(Voice_00405D40, Serial) == 0x138);
GG_STATIC_ASSERT(offsetof(Voice_00405D40, At_278) == 0x278);

// The caller's handle on a playing voice.
struct AudioHandle_00405D40
{
    Voice_00405D40* Voice;    // +0x0000
    int   Serial;             // +0x0004
    void* Token;              // +0x0008
    void* Owner;              // +0x000C

    // FUNCTION: GAMEMD 0x405D40
    void Stop();
};
GG_STATIC_ASSERT(offsetof(AudioHandle_00405D40, Serial) == 0x4);
GG_STATIC_ASSERT(offsetof(AudioHandle_00405D40, Token) == 0x8);
GG_STATIC_ASSERT(offsetof(AudioHandle_00405D40, Owner) == 0xC);

#endif  // GG_MATCH_AUDIO_AUDIO_STOP_METHODS_H
