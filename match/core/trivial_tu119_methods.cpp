// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu119_methods.h"

// FUNCTION: GAMEMD 0x556620
// Member getter (dword). Vtable slot 1 of LinkClass (RTTI) and 1 derived vtable(s).
int Obj_00556620::FUN_00556620() const
{
    return unknown_04;
}

// FUNCTION: GAMEMD 0x556630
// Member getter (dword). Vtable slot 2 of LinkClass (RTTI) and 1 derived vtable(s).
int Obj_00556630::FUN_00556630() const
{
    return unknown_08;
}
