// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x4093B0.

#include "audio_time_methods.h"

// FUNCTION: GAMEMD 0x4093B0  Unsorted::AudioGetTime (__fastcall)
// The installed hook is tail-jumped to (`JMP EAX`) rather than called, so its
// 64-bit result becomes ours untouched.
__int64 __fastcall Unsorted_AudioGetTime()
{
    if (AudioTimeHook != 0)
        return AudioTimeHook();

    return 0;
}
