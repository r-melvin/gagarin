// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x406060:
//     handle  [ESI+0x0] Voice, [ESI+0x4] Serial, [ESI+0x8] Token,
//             [ESI+0xC] Owner (compared against the address 0x87E294)
//     voice   [EDI+0x18] Flags (TEST ..,0x20; OR ..,0x60), [EDI+0x24] Token,
//             [EDI+0xB0] Peer, [EDI+0x138] Serial
//     token   [EAX+0x10] Flags (TEST byte,1), [EAX+0x4C] unknown_4C
//     peer    [EAX+0xC0] Voice (back-pointer)
//   The same handle/voice/peer shapes are already pinned by 0x405FD0 in
//   match/audio/sample_registry_methods.h; this TU redeclares them locally
//   (with the token typed as a pointer, which is how 0x406060 reads it) so it
//   stands alone. YRpp names 0x406060 Audio::EndLooping.
#ifndef GG_MATCH_AUDIO_AUDIO_END_LOOPING_METHODS_H
#define GG_MATCH_AUDIO_AUDIO_END_LOOPING_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0x87E2A0 — nonzero once the audio subsystem is up.
extern int DAT_0087E2A0;
// GLOBAL: GAMEMD 0x87E294 — the sample table; the handle's owner is compared
// against its address.
extern char DAT_0087E294[];

struct Voice_00406060;

// The object a voice's token points at (the same shape as Obj_00406600b in
// match/core/small_misc2_methods.h: Flags +0x10, unknown_4C +0x4C).
struct Token_00406060
{
    char _pad000[0x10];      // +0x0000
    int  Flags;              // +0x0010  bit 0 = looping
    char _pad014[0x4C - 0x14];
    int  unknown_4C;         // +0x004C
};
GG_STATIC_ASSERT(offsetof(Token_00406060, Flags) == 0x10);
GG_STATIC_ASSERT(offsetof(Token_00406060, unknown_4C) == 0x4C);

struct Peer_00406060
{
    char _pad000[0xC0];      // +0x0000
    Voice_00406060* Voice;   // +0x00C0

    // FUNCTION: GAMEMD 0x4026A0 (decl; reloc) — __thiscall forwarder.
    void FUN_004026A0();
    // FUNCTION: GAMEMD 0x4026B0 (decl; reloc) — __thiscall forwarder.
    void FUN_004026B0();
};
GG_STATIC_ASSERT(offsetof(Peer_00406060, Voice) == 0xC0);

struct Voice_00406060
{
    char _pad000[0x18];      // +0x0000
    union {
        unsigned int  Flags;     // +0x0018  bits 5 and 6 mark it finished
        unsigned char FlagsLow;  // +0x0018  the same word, byte-tested
    };
    char _pad01C[0x8];       // +0x001C
    Token_00406060* Token;   // +0x0024
    char _pad028[0x88];      // +0x0028
    Peer_00406060* Peer;     // +0x00B0
    char _pad0B4[0x84];      // +0x00B4
    int  Serial;             // +0x0138
};
GG_STATIC_ASSERT(offsetof(Voice_00406060, Flags) == 0x18);
GG_STATIC_ASSERT(offsetof(Voice_00406060, Token) == 0x24);
GG_STATIC_ASSERT(offsetof(Voice_00406060, Peer) == 0xB0);
GG_STATIC_ASSERT(offsetof(Voice_00406060, Serial) == 0x138);

// The caller's handle on a playing voice.
struct AudioHandle_00406060
{
    Voice_00406060* Voice;   // +0x0000
    int   Serial;            // +0x0004
    Token_00406060* Token;   // +0x0008
    void* Owner;             // +0x000C

    // FUNCTION: GAMEMD 0x406060
    void EndLooping();
};
GG_STATIC_ASSERT(offsetof(AudioHandle_00406060, Serial) == 0x4);
GG_STATIC_ASSERT(offsetof(AudioHandle_00406060, Token) == 0x8);
GG_STATIC_ASSERT(offsetof(AudioHandle_00406060, Owner) == 0xC);

#endif  // GG_MATCH_AUDIO_AUDIO_END_LOOPING_METHODS_H
