// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu269_methods.h"

// FUNCTION: GAMEMD 0x75F880
// Returns a constant. Vtable slot 12 of WaveClass (RTTI).
int Obj_0075F880::FUN_0075F880() const
{
    return 0x240;
}

// FUNCTION: GAMEMD 0x75F890
// Returns a constant. Vtable slot 30 of WaveClass (RTTI).
int Obj_0075F890::FUN_0075F890() const
{
    return 3;
}

// FUNCTION: GAMEMD 0x75F8A0
// Returns zero. Vtable slot 34 of WaveClass (RTTI).
int Obj_0075F8A0::FUN_0075F8A0() const
{
    return 0;
}

// FUNCTION: GAMEMD 0x7610D0
// Branching.
void Obj_007610D0::FUN_007610D0()
{
    unknown_1D0 += -6;
    if (unknown_1D0 < 0x20)
    {
        vf_62();
    }
}

// FUNCTION: GAMEMD 0x762060
// Empty function.
void __cdecl FUN_00762060()
{
}

// FUNCTION: GAMEMD 0x762AE0
// Empty function.
void __cdecl FUN_00762AE0()
{
}

// FUNCTION: GAMEMD 0x7631F0
// Returns a constant. Vtable slot 11 of WaveClass (RTTI).
int Obj_007631F0::FUN_007631F0() const
{
    return 0x2B;
}
