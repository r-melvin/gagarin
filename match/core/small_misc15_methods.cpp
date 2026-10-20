// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
// Ordered ascending by retail address. The two allocate-and-construct helpers
// are written out longhand per the family rule.

#include "small_misc15_methods.h"

// FUNCTION: GAMEMD 0x41CB20
char* Obj_0041CB20::FUN_0041CB20(int arg)
{
    void* p = FUN_007C8E17(0x6D8);

    if (p) {
        return ((Made_0041CB20*)p)->FUN_00413D20(this, arg);
    }

    return 0;
}

// FUNCTION: GAMEMD 0x459840
// The first non-zero of three sub-object counters, falling back to the owner's
// own field. All four returns share one epilogue.
int Obj_00459840::FUN_00459840() const
{
    if (unknown_520->atEA4) {
        return unknown_520->atEA4;
    }

    if (unknown_520->atEA8) {
        return unknown_520->atEA8;
    }

    if (unknown_520->atEAC) {
        return unknown_520->atEAC;
    }

    return unknown_6F4;
}

// FUNCTION: GAMEMD 0x45E880
char* BuildingTypeClass_0045E880::FUN_0045E880(int arg)
{
    void* p = FUN_007C8E17(0x720);

    if (p) {
        return ((Made_0045E880*)p)->FUN_0043B740(this, arg);
    }

    return 0;
}
