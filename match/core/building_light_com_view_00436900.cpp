// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   All bodies follow complete retail entries: 0x436900 (6 bytes), 0x436910
//   (56), 0x4369C0 (23), 0x4369E0 (3), 0x4369F0 (6), and 0x436A00 (56).
//   Their vtable slot numbers are confirmed by pointer words at 0x7E3AD0.
//   Calls at 0x4369CF and 0x436A0F target 0x410320 and 0x5F5230 respectively;
//   each target entry independently confirms its argument cleanup and ABI.
#include "building_light_com_view_00436900.h"

// FUNCTION: GAMEMD 0x436900
int BuildingLightMethodView_00436900::FUN_00436900()
{
    return 0xE8;
}

// FUNCTION: GAMEMD 0x436910
int __stdcall FUN_00436910(void*, unsigned int* outWords)
{
    if (outWords == 0)
        return (int)0x80004003;

    outWords[0] = DAT_007E9730;
    outWords[1] = DAT_007E9734;
    outWords[2] = DAT_007E9738;
    outWords[3] = DAT_007E973C;
    return 0;
}

// FUNCTION: GAMEMD 0x4369C0
int __stdcall FUN_004369C0(void* self, void* stream, int clearDirty)
{
    return FUN_00410320(self, stream, clearDirty);
}

// FUNCTION: GAMEMD 0x4369E0
int BuildingLightMethodView_00436900::FUN_004369E0()
{
    return 0;
}

// FUNCTION: GAMEMD 0x4369F0
int BuildingLightMethodView_00436900::FUN_004369F0()
{
    return 3;
}

// FUNCTION: GAMEMD 0x436A00
void BuildingLightMethodView_00436900::FUN_00436A00(int unknownArg0, char unknownArg1)
{
    ((ThiscallTarget_005F5230*)this)->Call(unknownArg0, unknownArg1);
    if (this->unknown_E0 == (unsigned int)unknownArg0)
        this->unknown_E0 = 0;
    if (this->unknown_E4 == (unsigned int)unknownArg0)
        this->unknown_E4 = 0;
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x7E9730
unsigned int DAT_007E9730 = 0x54822258;
// GLOBAL: GAMEMD 0x7E9734
unsigned int DAT_007E9734 = 0x11D1D8A8;
// GLOBAL: GAMEMD 0x7E9738
unsigned int DAT_007E9738 = 0x600062B4;
// GLOBAL: GAMEMD 0x7E973C
unsigned int DAT_007E973C = 0x79A9C697;
// END defined globals
