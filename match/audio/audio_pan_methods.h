// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Layout + offsets derived from the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI (member-access disassembly), cross-checked against YRpp
//   `AdjustAudioEventPanning` (every offset
//   reconfirmed numerically from the disassembly).
//
// AdjustAudioEventPanning clamps a pan value to [0, 0x4000] and dispatches it to
// one of two per-channel pan setters depending on the event's playback type
// ([event+0x1c] == 3 selects the 0x407170 variant, else the 0x407150 variant).
// Neither pan setter is matched here — they are declared so cl emits the
// (relocation-normalised) tail-call jump the retail code uses.
#ifndef GG_MATCH_AUDIO_AUDIO_PAN_METHODS_H
#define GG_MATCH_AUDIO_AUDIO_PAN_METHODS_H

#include <stddef.h>  // offsetof, size_t
#include "../_rt/gg_static_assert.h"

// ---------------------------------------------------------------------------
// AudioEventTag — the live audio-event record (0x148 bytes; allocated at
// 0x4063FA). Only the two members AdjustAudioEventPanning touches are modelled:
//   +0x1C  Type    (MOV EAX,[ECX+0x1c]; CMP EAX,3   @0x406270)
//   +0x108 Channel (ADD ECX,0x108 before the tail call @0x40628d / 0x4062ad)
// The rest of the record is P2.
// ---------------------------------------------------------------------------
struct AudioEventTag
{
    char _pad_00[0x1C];
    int  Type;                         // +0x1C
    char _pad_20[0x108 - (0x1C + 4)];
    char Channel;                      // +0x108 (sub-object marker)
};
GG_STATIC_ASSERT(offsetof(AudioEventTag, Type)    == 0x1C);
#if GG_TARGET_ABI_32
GG_STATIC_ASSERT(offsetof(AudioEventTag, Channel) == 0x108);
#endif

// The two per-channel pan setters (ECX = &event->Channel, EDX = clamped pan).
// Declared only — bodies live elsewhere; cl emits a tail-call jump (reloc).
void __fastcall AudioEvent_SetPanType0(void* channel, unsigned int pan);  // GAMEMD 0x407150
void __fastcall AudioEvent_SetPanType3(void* channel, unsigned int pan);  // GAMEMD 0x407170

// Clamp `pan` to [0, 0x4000] and route it to the type-appropriate pan setter.
void __fastcall AdjustAudioEventPanning(void* event, unsigned int pan);   // GAMEMD 0x406270

#endif  // GG_MATCH_AUDIO_AUDIO_PAN_METHODS_H
