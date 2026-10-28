// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Retail 0x40948E creates the DirectSound interface at 0x87E89C through
// DSOUND.dll ordinal 1. The CreateSoundBuffer call at 0x40A16D supplies
// 0x87E8A0.
// Retail 0x40A7C0/0x40A850 use that buffer's Stop, SetFormat and Play slots.
// WAVEFORMATEX is the toolchain's platform ABI, not a recovered game layout.
#ifndef GG_MATCH_AUDIO_PRIMARY_SOUND_BUFFER_FORMAT_H
#define GG_MATCH_AUDIO_PRIMARY_SOUND_BUFFER_FORMAT_H

#include <windows.h>
#include <mmsystem.h>
#include "dsound_access_methods.h"

// All fields are written by 0x40A7C0 and 0x40A850. The format pointer passed
// to SetFormat at 0x40A8E2 is ESP+4; the last word is stored at ESP+0x14.
GG_STATIC_ASSERT(offsetof(WAVEFORMATEX, wFormatTag) == 0x00);
GG_STATIC_ASSERT(offsetof(WAVEFORMATEX, nChannels) == 0x02);
GG_STATIC_ASSERT(offsetof(WAVEFORMATEX, nSamplesPerSec) == 0x04);
GG_STATIC_ASSERT(offsetof(WAVEFORMATEX, nAvgBytesPerSec) == 0x08);
GG_STATIC_ASSERT(offsetof(WAVEFORMATEX, nBlockAlign) == 0x0C);
GG_STATIC_ASSERT(offsetof(WAVEFORMATEX, wBitsPerSample) == 0x0E);
GG_STATIC_ASSERT(offsetof(WAVEFORMATEX, cbSize) == 0x10);
GG_STATIC_ASSERT(sizeof(WAVEFORMATEX) == 0x12);

// Prefix through Stop; later interface slots are not accessed here.
// SDK slot order is confirmed by calls at 0x40A873, 0x40A8E2, 0x40A8F3.
struct SoundBufferVtbl_0040A850
{
    char unknown_00[0x30];
    HRESULT (__stdcall* Play)(SoundBuffer_0040A7B0*, DWORD, DWORD, DWORD);
    char unknown_34[4];
    HRESULT (__stdcall* SetFormat)(SoundBuffer_0040A7B0*, const WAVEFORMATEX*);
    char unknown_3C[0xC];
    HRESULT (__stdcall* Stop)(SoundBuffer_0040A7B0*);
};
GG_STATIC_ASSERT(offsetof(SoundBufferVtbl_0040A850, Play) == 0x30);
GG_STATIC_ASSERT(offsetof(SoundBufferVtbl_0040A850, SetFormat) == 0x38);
GG_STATIC_ASSERT(offsetof(SoundBufferVtbl_0040A850, Stop) == 0x48);
struct SoundBuffer_0040A7B0 { SoundBufferVtbl_0040A850* Vptr; };
GG_STATIC_ASSERT(offsetof(SoundBuffer_0040A7B0, Vptr) == 0);
GG_STATIC_ASSERT(sizeof(SoundBuffer_0040A7B0) == 4);

// The getter is declared with its recovered ABI in leaf_accessor_methods.h.
// Its returned owner carries AudioSampleData at +0x44; the accesses here
// select sample rate +0x4C, channels +0x50 and bytes per sample +0x54.
#include "../core/leaf_accessor_methods.h"
#include "../core/floored_decrement_methods.h"
GG_STATIC_ASSERT(offsetof(Pool_00402860, unknown_44) +
    offsetof(AudioSampleData, SampleRate) == 0x4C);
GG_STATIC_ASSERT(offsetof(Pool_00402860, unknown_44) +
    offsetof(AudioSampleData, NumChannels) == 0x50);
GG_STATIC_ASSERT(offsetof(Pool_00402860, unknown_44) +
    offsetof(AudioSampleData, BytesPerSample) == 0x54);

// FUNCTION: GAMEMD 0x40A7C0
void FUN_0040A7C0(int samplesPerSecond, int bitsPerSample, int channels);
// FUNCTION: GAMEMD 0x40A850
void FUN_0040A850();
#endif
