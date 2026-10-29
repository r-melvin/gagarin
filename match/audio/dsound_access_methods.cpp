// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Derived from entry-point disassembly of retail gamemd.exe v1.001.
//   No arguments are consumed; the integer/pointer result is returned in EAX.

#include "dsound_access_methods.h"

// FUNCTION: GAMEMD 0x409FF0
// An indirect callback at 0x816370 points here. The entry is decoded but is
// absent from Ghidra's function list. The final RET is at 0x40A083 (0x94 bytes).
void __cdecl FUN_00409FF0()
{
    if (DAT_0087E89C) {
        DAT_0087E89C->Vptr->Release(DAT_0087E89C);
        DAT_0087E89C = 0;
    }

    if (DAT_0087E898) {
        if (--DAT_0087E878 < 0) {
            DAT_0087E878 = 0;
        }
        if (DAT_0087E878 == 0) {
            DAT_0087E850.unknown_00 = 1;
            // Retail repeatedly reloads the flag while waiting for the worker.
            while (!DAT_0087E850.unknown_08) {
            }
            WaitForSingleObject(DAT_0087E86C, 5000);
            CloseHandle(DAT_0087E86C);
            DAT_0087E898 = 0;
        }
    }
    DeleteCriticalSection(&DAT_0087E880);
}

// FUNCTION: GAMEMD 0x40A770
int __cdecl FUN_0040A770()
{
    return 0x80040000;
}

// FUNCTION: GAMEMD 0x40A780
int __cdecl FUN_0040A780()
{
    EnterCriticalSection(&DAT_0087E880);
    return 0;
}

// FUNCTION: GAMEMD 0x40A790
int __cdecl FUN_0040A790()
{
    LeaveCriticalSection(&DAT_0087E880);
    return 0;
}

// FUNCTION: GAMEMD 0x40A7B0
SoundBuffer_0040A7B0* __cdecl FUN_0040A7B0()
{
    return DAT_0087E8A0;
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x87E850
BackendState_004095B0 DAT_0087E850;
// GLOBAL: GAMEMD 0x87E880
CRITICAL_SECTION DAT_0087E880;
// GLOBAL: GAMEMD 0x87E89C
DirectSoundResource_00409FF0* DAT_0087E89C;
// GLOBAL: GAMEMD 0x87E8A0
SoundBuffer_0040A7B0* DAT_0087E8A0;
// END defined globals
