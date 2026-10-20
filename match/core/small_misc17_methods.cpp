// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
// Ordered ascending by retail address.

#include "small_misc17_methods.h"

// FUNCTION: GAMEMD 0x4103E0
long __stdcall FUN_004103E0(Provider_004103E0* provider, void** out)
{
    if (out == 0) {
        return 0x80004003;
    }

    // Volatile-qualified so the pair keeps source order: retail writes the
    // pointer before the companion word, and a plain assignment lets VC6 emit
    // them the other way round.
    *(void* volatile*)&out[0] = SLOT_30(provider) + 4;
    *(void* volatile*)&out[1] = 0;

    return 0;
}

// FUNCTION: GAMEMD 0x473A80
// Base construction, then the sub-object, then this class's own fields - with
// the vtable installed between two of them rather than first, which is why this
// is written as a plain method returning the object.
Obj_00473A80* Obj_00473A80::FUN_00473A80()
{
    FUN_0047AA30(this);

    Sub.FUN_0043AD00(0, 0);

    unknown_64 = 0;

    *(char**)this = VT_007E16B0;

    unknown_68 = 0;

    return this;
}
