// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
// The nine tail-jump thunks, ordered ascending by retail address.

#include "tail_jmp_thunk_sweep.h"

// FUNCTION: GAMEMD 0x4DA2B0
void FUN_004DA2B0(void* self)
{
    FUN_005B2EF0(self);
}

// FUNCTION: GAMEMD 0x4DE620
void FUN_004DE620(void* self)
{
    FUN_005F6B90(self);
}


// FUNCTION: GAMEMD 0x6D0260
void FUN_006D0260(void* self)
{
    FUN_006A5000(self);
}


// FUNCTION: GAMEMD 0x7717F0
void FUN_007717F0(void* self)
{
    FUN_007529E0(self);
}

