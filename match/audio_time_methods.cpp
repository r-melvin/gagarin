// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x4093B0.

#include "audio_time_methods.h"

extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(__int64*);

// GLOBAL: GAMEMD 0x87E848
AudioTimeFunc AudioTimeHook;

// FUNCTION: GAMEMD 0x4093B0  Unsorted::AudioGetTime (__fastcall)
// The installed hook is tail-jumped to (`JMP EAX`) rather than called, so its
// 64-bit result becomes ours untouched.
__int64 Unsorted_AudioGetTime()
{
    if (AudioTimeHook != 0)
        return AudioTimeHook();

    return 0;
}

// FUNCTION: GAMEMD 0x4093C0
__int64 FUN_004093C0()
{
    __int64 counter;
    QueryPerformanceCounter(&counter);
    return counter / DAT_0087E828;
}
