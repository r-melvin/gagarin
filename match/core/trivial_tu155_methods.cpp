// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu155_methods.h"

// FUNCTION: GAMEMD 0x5D5850
// Branching.
void Obj_005D5850::FUN_005D5850()
{
    if (unknown_00 != 0)
    {
        FUN_007C93E8(unknown_00);
    }
}

// FUNCTION: GAMEMD 0x5D5860
// Empty function that pops its stack arguments.
void __stdcall FUN_005D5860(int a1)
{
}

// FUNCTION: GAMEMD 0x5D5880
// Calls other functions.
void __cdecl FUN_005D5880()
{
    timeEndPeriod(1);
}

// FUNCTION: GAMEMD 0x5D58A0
// Tail-calls an imported function.
void __cdecl FUN_005D58A0()
{
    timeGetTime();
}
