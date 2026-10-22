// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
// Ordered ascending by retail address.

#include "small_misc8_methods.h"

// FUNCTION: GAMEMD 0x4092F0
// Always resets with zero, then again with the stored value if there is one.
// The constant returned is a fixed status rather than anything computed.
int Obj_004092F0::FUN_004092F0()
{
    FUN_004091C0(this, 0);

    int value = unknown_08;

    if (value) {
        FUN_004091C0(this, value);
    }

    return 0x80040000;
}

// FUNCTION: GAMEMD 0x410410
void Obj_00410410::FUN_00410410(Sink_004A1C00* sink)
{
    sink->FUN_004A1D50(unknown_10);
    sink->FUN_004A1CA0(unknown_20);
}

// FUNCTION: GAMEMD 0x410BE0
// The two scalar fields first (through 0x410410), then three raw blocks at
// +0x24, +0x64 and +0x3D. The last offset overlaps the +0x24 block, so these
// are not disjoint records - the third write is a sub-range of the first.
void Obj_00410410::FUN_00410BE0(Sink_004A1C00* sink)
{
    FUN_00410410(sink);

    sink->FUN_004A1DB0((char*)this + 0x24);
    sink->FUN_004A1DB0((char*)this + 0x64);
    sink->FUN_004A1DB0((char*)this + 0x3D);
}

// FUNCTION: GAMEMD 0x41CAF0
void __cdecl FUN_0041CAF0()
{
    DAT_00889F5C = FUN_005B40B0(DAT_00817FE4, 0);
    DAT_00889F60 = FUN_005B40B0(DAT_00817FD8, 0);
}

// FUNCTION: GAMEMD 0x459F40
// Hand back the object only if it is of the expected kind. Retail computes the
// selection branchlessly (`SUB 6; NEG; SBB; NOT; AND`), which is what the
// conditional expression produces here.
Obj_00459F40* Obj_00459F40::FUN_00459F40()
{
    if (this == 0) {
        return 0;
    }

    return (WHAT_AM_I(this) == 6) ? this : 0;
}
