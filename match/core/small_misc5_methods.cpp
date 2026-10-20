// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
// Ordered ascending by retail address.

#include "small_misc5_methods.h"

// FUNCTION: GAMEMD 0x401080
// Initialise all three sub-objects; the last is a tail call.
void Obj_00401080::FUN_00401080()
{
    FUN_004071C0(this);
    FUN_004071C0((char*)this + 0x28);
    FUN_004071C0((char*)this + 0x50);
}

// FUNCTION: GAMEMD 0x406E80
void __cdecl FUN_00406E80()
{
    if (DAT_0087E728) {
        FUN_00403730(DAT_0087E728, 1);
    }

    FUN_00404E70();
}

// FUNCTION: GAMEMD 0x406EA0
void __cdecl FUN_00406EA0()
{
    if (DAT_0087E728) {
        FUN_00403770(DAT_0087E728, 1);
    }

    FUN_00404FD0();
    FUN_00751040();
}

// FUNCTION: GAMEMD 0x406EC0
void __cdecl FUN_00406EC0()
{
    FUN_00751080();
    FUN_00405040();

    if (DAT_0087E728) {
        FUN_004037C0(DAT_0087E728, 1);
    }
}

// FUNCTION: GAMEMD 0x406EE0
void __cdecl FUN_00406EE0()
{
    if (DAT_0087E728) {
        FUN_00403730(DAT_0087E728, 1);
    }

    FUN_00404E70();
    FUN_004081A0();
}

// FUNCTION: GAMEMD 0x432C50
// Both comparisons are unsigned (`JNC`/`JC`), so a value past the halfway point
// of the range reads as large rather than negative.
int Obj_00432C50::FUN_00432C50() const
{
    return unknown_04->atC >= unknown_04->at8 || unknown_04->atC < unknown_30;
}

// FUNCTION: GAMEMD 0x46D330
Obj_0046D330* Obj_0046D330::FUN_0046D330()
{
    _vtable = VT_007E4AAC;
    unknown_04 = 0;

    DAT_0089E050 = 0;
    DAT_0081B1E8 = -1;

    return this;
}
