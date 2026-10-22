// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu238_methods.h"

// FUNCTION: GAMEMD 0x711E90
// Branching. Vtable slot 41 of TechnoTypeClass (RTTI).
bool Obj_00711E90::FUN_00711E90()
{
    if (unknown_898 == 0 || unknown_6C8 != 0)
    {
        return false;
    }
    return true;
}

// FUNCTION: GAMEMD 0x711EC0
// Branching. Vtable slot 28 of TechnoTypeClass (RTTI) and 4 derived vtable(s).
int Obj_00711EC0::FUN_00711EC0()
{
    if (unknown_C99 != 0)
    {
        if (DAT_00A8B238 == 0)
        {
            return unknown_6CC;
        }
        return 0x7FFFFFFF;
    }
    return unknown_6CC;
}

// FUNCTION: GAMEMD 0x712120
// Member getter (dword). Vtable slot 45 of TechnoTypeClass (RTTI) and 2 derived vtable(s).
int Obj_00712120::FUN_00712120() const
{
    return DAT_008871E0->unknown_16CC;
}

// FUNCTION: GAMEMD 0x717800
// Branching. Vtable slot 47 of TechnoTypeClass (RTTI) and 4 derived vtable(s).
int Obj_00717800::FUN_00717800()
{
    if (unknown_618 == -1)
    {
        return DAT_008871E0->unknown_7B4;
    }
    return unknown_618;
}
