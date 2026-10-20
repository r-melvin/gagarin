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
    return (unknown_00 & 2) || (unknown_28 & 2) || (unknown_50 & 2);
}

// FUNCTION: GAMEMD 0x401170
// Clear that bit on all three. The write order is +0x00, +0x50, +0x28 — not
// ascending, and reproduced as retail has it rather than tidied.
void Obj_00401000::FUN_00401170()
{
    unknown_00 &= ~2;
    unknown_50 &= ~2;
    unknown_28 &= ~2;
}

// PARTIAL (50% - 6/12). The upper bound is exact; the lower one is not. Retail
// branches on it (`TEST EDX,EDX; JGE`), while our compiler
// recognises `v < 0 ? 0 : v` as a max and goes branchless with
// `XOR EAX,EAX; TEST; SETL AL; DEC EAX; AND EAX,EDX`. Four phrasings were
// tried - the clamp inline in the setter, as a helper, force-inlined, and with
// the lower test written `>= 0` instead of `< 0` - and every one that inlines
// at all produces the branchless form. 8447 did not do that transform.
//
// FUNCTION: GAMEMD 0x406620
// Store clamped to 0..100.
//
// The clamp is written as a value-returning helper rather than inline: retail
// materialises each bound into EAX and stores from there
// (`MOV EAX,0x64; MOV [ECX+0x68],EAX`), which is what an inlined function
// returning the value produces. Assigning the constant directly gives
// `MOV dword ptr [ECX+0x68],0x64` and misses.
static __forceinline int ClampPercent(int value)
{
    if (value > 100) {
        return 100;
    }
    if (value < 0) {
        return 0;
    }
    return value;
}

void __fastcall FUN_00406620(Obj_00406600* obj, int value)
{
    obj->unknown_68 = ClampPercent(value);
}

// FUNCTION: GAMEMD 0x407000
// `XOR EAX,EAX; TEST; SETNZ AL` is the bool materialisation of a pointer test,
// not a branch.
bool __cdecl FUN_00407000()
{
    return DAT_0087E728 != 0;
}
