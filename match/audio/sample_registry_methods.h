// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x405FD0 and 0x4064A0. The subsystem is named from the
//   format string at 0x816218, "Missing sample %s\n", which 0x4064A0 logs when
//   a lookup fails.
#ifndef GG_MATCH_AUDIO_SAMPLE_REGISTRY_METHODS_H
#define GG_MATCH_AUDIO_SAMPLE_REGISTRY_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0x87E2A0 — nonzero once the audio subsystem is up.
extern int DAT_0087E2A0;
// GLOBAL: GAMEMD 0x87E294 — the sample table. 0x4064A0 reads its value as a
// pointer, 0x405FD0 compares a handle's owner against its address, so both
// spellings are in use.
extern void* DAT_0087E294;

// FUNCTION: GAMEMD 0x4015C0 — resolve a sample name to an index, or ~0.
unsigned int FUN_004015C0(void* table, const char* name);
// FUNCTION: GAMEMD 0x4068E0 — printf-style log sink.
extern "C" void __cdecl FUN_004068E0(const char* format, ...);

struct Voice_00405FD0;

struct Peer_00405FD0
{
    char _pad000[0xC0];      // +0x0000
    Voice_00405FD0* Voice;   // +0x00C0
};
GG_STATIC_ASSERT(offsetof(Peer_00405FD0, Voice) == 0xC0);

struct Voice_00405FD0
{
    char _pad000[0x18];      // +0x0000
    unsigned int Flags;      // +0x0018  bits 5 and 6 mark it finished
    char _pad01C[0x8];       // +0x001C
    int  Token;              // +0x0024
    char _pad028[0x88];      // +0x0028
    Peer_00405FD0* Peer;     // +0x00B0
    char _pad0B4[0x84];      // +0x00B4
    int  Serial;             // +0x0138
};
GG_STATIC_ASSERT(offsetof(Voice_00405FD0, Flags) == 0x18);
GG_STATIC_ASSERT(offsetof(Voice_00405FD0, Token) == 0x24);
GG_STATIC_ASSERT(offsetof(Voice_00405FD0, Peer) == 0xB0);
GG_STATIC_ASSERT(offsetof(Voice_00405FD0, Serial) == 0x138);

// The caller's handle on a playing voice: the voice itself plus the serial and
// token it was issued with, so a stale handle can be told from a live one.
struct Handle_00405FD0
{
    Voice_00405FD0* Voice;   // +0x0000
    int  Serial;             // +0x0004
    int  Token;              // +0x0008
    void* Owner;             // +0x000C
};
GG_STATIC_ASSERT(offsetof(Handle_00405FD0, Owner) == 0xC);

// FUNCTION: GAMEMD 0x4026A0
void FUN_004026A0(Peer_00405FD0* peer);
// FUNCTION: GAMEMD 0x4026B0
void FUN_004026B0(Peer_00405FD0* peer);

// The queue 0x4064A0 appends to: at most 0x20 sample indices, with the count
// immediately after the array (`CMP [EDI+0x134],0x20` bounds it).
struct Queue_004064A0
{
    char _pad000[0xC];       // +0x0000
    int  field_0C;           // +0x000C  cleared when a name fails to resolve
    char _pad010[0xA4];      // +0x0010
    unsigned int Samples[0x20];  // +0x00B4
    int  Count;              // +0x0134
};
GG_STATIC_ASSERT(offsetof(Queue_004064A0, Samples) == 0xB4);
GG_STATIC_ASSERT(offsetof(Queue_004064A0, Count) == 0x134);

// FUNCTION: GAMEMD 0x405FD0
void FUN_00405FD0(Handle_00405FD0* handle);
// FUNCTION: GAMEMD 0x4064A0
int FUN_004064A0(Queue_004064A0* self, const char* name);

#endif  // GG_MATCH_AUDIO_SAMPLE_REGISTRY_METHODS_H
