// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes and the global address read off the user's retail gamemd.exe v1.001
//   via the local Ghidra CLI at 0x4093B0. Name cross-checked against YRpp
//   (`Audio::GetTime`).
//
// The audio clock is indirected through a hook pointer so the sound backend can
// supply its own timebase; with no backend installed the engine reports 0.
#ifndef GG_MATCH_AUDIO_AUDIO_TIME_METHODS_H
#define GG_MATCH_AUDIO_AUDIO_TIME_METHODS_H

// The installed clock. Returning __int64 is what the retail miss path proves:
// it zeroes *both* EAX and EDX before returning.
typedef __int64 (__cdecl* AudioTimeFunc)(void);

// GLOBAL: GAMEMD 0x0087E848
extern AudioTimeFunc AudioTimeHook;

__int64 __fastcall Unsorted_AudioGetTime();   // GAMEMD 0x4093B0

#endif  // GG_MATCH_AUDIO_AUDIO_TIME_METHODS_H
