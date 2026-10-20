// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Layout + offsets derived from the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI (member-access disassembly), cross-checked against YRpp
//   Audio.h `AudioIDXData` / `AudioSampleData` (consult-only, NO LICENSE; every
//   offset reconfirmed numerically from the disassembly of 0x401640).
#ifndef GG_MATCH_AUDIO_AUDIO_SAMPLE_METHODS_H
#define GG_MATCH_AUDIO_AUDIO_SAMPLE_METHODS_H

#include <stddef.h>  // offsetof, size_t
#include "../_rt/gg_static_assert.h"
#include "audio.h"   // reuse AudioIDXData (+0x00 Samples) and AudioIDXEntry

// ---------------------------------------------------------------------------
// AudioSampleData — the decoded WAV header that GetSampleInformation @0x401640
// fills in. The disasm writes:
//   [EAX+0x00]=4           Data        (used as Format tag here: 4 == PCM/raw)
//   [EAX+0x04]=0|1         Format
//   [EAX+0x08]=entry+0x18  SampleRate  (AudioIDXEntry::SampleRate)
//   [EAX+0x0C]=1|2         NumChannels ((Flags&1)!=0)+1
//   [EAX+0x10]=1|2         BytesPerSample
//   [EAX+0x18]=entry+0x20  BlockAlign  (AudioIDXEntry::ChunkSize)
// (+0x14 ByteRate and +0x1C Flags are untouched by this leaf — P2.)
// ---------------------------------------------------------------------------
struct AudioSampleData
{
    unsigned int Data;            // +0x00
    unsigned int Format;          // +0x04
    unsigned int SampleRate;      // +0x08
    unsigned int NumChannels;     // +0x0C
    unsigned int BytesPerSample;  // +0x10
    unsigned int ByteRate;        // +0x14
    unsigned int BlockAlign;      // +0x18
    unsigned int Flags;           // +0x1C
};
GG_STATIC_ASSERT(offsetof(AudioSampleData, Data)           == 0x00);
GG_STATIC_ASSERT(offsetof(AudioSampleData, Format)         == 0x04);
GG_STATIC_ASSERT(offsetof(AudioSampleData, SampleRate)     == 0x08);
GG_STATIC_ASSERT(offsetof(AudioSampleData, NumChannels)    == 0x0C);
GG_STATIC_ASSERT(offsetof(AudioSampleData, BytesPerSample) == 0x10);
GG_STATIC_ASSERT(offsetof(AudioSampleData, BlockAlign)     == 0x18);

// __fastcall: this=ECX, index=EDX, pBuffer=[ESP+4]. Declared as a member of
// AudioIDXData in audio.h — see the note there.

#endif  // GG_MATCH_AUDIO_AUDIO_SAMPLE_METHODS_H
