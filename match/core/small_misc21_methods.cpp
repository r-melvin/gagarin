// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
// Ordered ascending by retail address.

#include "small_misc21_methods.h"

// FUNCTION: GAMEMD 0x406F00
// The probe skips only the first three steps; the last two run either way.
// Retail's `JNZ` lands on the fourth call rather than on a return, which is
// what says so - reading it as an early return drops two calls on that path.
void __cdecl FUN_00406F00()
{
    if (!FUN_0053BAD0()) {
        if (DAT_0087E728c) {
            FUN_00403770b(DAT_0087E728c, 1);
        }

        FUN_00404FD0b();
        FUN_00751040b();
    }

    FUN_007535B0();
    FUN_00753500();
}

// FUNCTION: GAMEMD 0x40A610
// Only runs while either of two flag bits is set. The interface release and the
// notify callback are independently optional, and the result is a constant.
int Obj_0040A610::FUN_0040A610()
{
    if (Flags & 5) {
        IFace* held = unknown_158->at64;

        if (held) {
            IFACE_CALL(held, 0x48);
        }

        NotifyFn notify = unknown_164;

        if (notify) {
            notify(this);
        }
    }

    return 0;
}

// FUNCTION: GAMEMD 0x437160
Triple3ib Triple3ib::FUN_00437160(const Triple3ib* other) const
{
    Triple3ib result;

    result.a = a - other->a;
    result.b = b - other->b;
    result.c = c - other->c;

    return result;
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x87E728
void* DAT_0087E728c;
// END defined globals
