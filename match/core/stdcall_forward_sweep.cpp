// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
// The four argument forwarders, ordered ascending by retail address.

#include "stdcall_forward_sweep.h"

// FUNCTION: GAMEMD 0x658770
void __fastcall FUN_00658770(void*, int, void* arg)
{
    FUN_004AE4F0(arg);
}

// FUNCTION: GAMEMD 0x6AC5D0
void __fastcall FUN_006AC5D0(void*, int, void* arg)
{
    FUN_006568A0(arg);
}

// FUNCTION: GAMEMD 0x6AC5E0
void __fastcall FUN_006AC5E0(void*, int, void* arg)
{
    FUN_00656AC0(arg);
}

// FUNCTION: GAMEMD 0x6D1800
void __fastcall FUN_006D1800(void*, int, void* arg)
{
    FUN_006AC210(arg);
}

