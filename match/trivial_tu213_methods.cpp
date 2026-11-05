// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu213_methods.h"
#include "_layout/slave_manager_class.h"

// FUNCTION: GAMEMD 0x6B1370
// Returns a constant. Vtable slot 12 of SlaveManagerClass (RTTI).
int SlaveManagerClass::vf_12()
{
    return 0x64;
}

// FUNCTION: GAMEMD 0x6B1380
// Returns a constant. Vtable slot 11 of SlaveManagerClass (RTTI).
int SlaveManagerClass::vf_11()
{
    return 0x48;
}
