// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
// Gate-guarded accessors and one short-pair add, ordered ascending by address.

#include "guarded_getter_methods.h"

// FUNCTION: GAMEMD 0x405130
int Obj_00405100::FUN_00405130() const
{
    if (DAT_0087E2A0 == 0) {
        return 0;
    }
    return unknown_50;
}

// FUNCTION: GAMEMD 0x405140
// The neutral value here is the float 0.0 loaded from 0x7E1748 rather than an
// immediate - x87 has no way to push a constant other than 1.0 directly, so
// even a literal zero comes from memory.
float Obj_00405100::FUN_00405140() const
{
    if (DAT_0087E2A0 == 0) {
        return 0.0f;
    }
    return unknown_54;
}

// FUNCTION: GAMEMD 0x405160
int Obj_00405100::FUN_00405160() const
{
    if (DAT_0087E2A0 == 0) {
        return 0;
    }
    return unknown_14;
}

// FUNCTION: GAMEMD 0x405170
// Written as a conditional expression rather than an early return: retail loads
// the placeholder pointer *before* the branch and overwrites it on the live
// path, which is the ternary shape, not the if-return shape.
//
// The arms are ordered gate-clear-first on purpose. VC6 materialises the
// *true* arm ahead of the test and patches in the false arm afterwards, so
// `gate ? live : placeholder` loads the live value first and gets the branch
// backwards; `gate == 0 ? placeholder : live` puts the placeholder in EAX
// before the test, as retail has it.
const char* Obj_00405100::FUN_00405170() const
{
    return DAT_0087E2A0 == 0 ? NoEventsString : &unknown_6C;
}

// FUNCTION: GAMEMD 0x42E6D0
void Obj_0042E600::FUN_0042E6D0(ShortPair delta)
{
    unknown_04 += delta.x;
    unknown_06 += delta.y;
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x816204
extern const char NoEventsString[] = "no events";
// END defined globals
