// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
// Flag tests, a flag clear and a clamped setter, ascending by retail address.

#include "flag_and_clamp_methods.h"

// FUNCTION: GAMEMD 0x4010A0
// True when any of the three sub-objects has bit 1 set.
int Obj_00401000::FUN_004010A0() const
{
    return (First.Flags32 & 2) || (Second.Flags32 & 2) || (Third.Flags32 & 2);
}

// FUNCTION: GAMEMD 0x401170
// Clear that bit on all three. The write order is +0x00, +0x50, +0x28 — not
// ascending, and reproduced as retail has it rather than tidied.
void Obj_00401000::FUN_00401170()
{
    First.Flags32 &= ~2;
    Third.Flags32 &= ~2;
    Second.Flags32 &= ~2;
}

// Store clamped to 0..100.
//
// The clamp is a value-returning inline helper that narrows a local, upper bound
// first: retail materialises each bound into EAX and stores from there
// (`MOV EAX,0x64; MOV [ECX+0x68],EAX`). Early-returning arms or a conditional
// expression make VC6 go branchless or lose the arm shape; two successive
// `if`s on one local reproduce the three-arm layout byte-for-byte.
static __forceinline int ClampPercent(int value)
{
    int result = value;
    if (result > 100) {
        result = 100;
    }
    if (result < 0) {
        result = 0;
    }
    return result;
}

// FUNCTION: GAMEMD 0x406620
void AudioEventType::FUN_00406620(int value)
{
    VShift = ClampPercent(value);
}

// FUNCTION: GAMEMD 0x407000
// `XOR EAX,EAX; TEST; SETNZ AL` is the bool materialisation of a pointer test,
// not a branch.
bool __cdecl FUN_00407000()
{
    return DAT_0087E728 != 0;
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x87E728
void* DAT_0087E728;
// END defined globals
