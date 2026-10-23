// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x4A80D0 / 0x6C8C40 /
//   0x732D00 via the local Ghidra disassembly.
//
// Global query leaves, ordered ascending by retail address.

#include "system_query_methods.h"

// Win32 import reached through the IAT (`CALL dword ptr [0x007E1530]`).
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime(void);

// FUNCTION: GAMEMD 0x4A80D0  CD::GetCDNumber (__fastcall)
int CD_GetCDNumber()
{
    return 2;
}

// FUNCTION: GAMEMD 0x6C8C40  Timer::GetTime (__fastcall)
int Timer_GetTime()
{
    return timeGetTime() >> 4;
}

