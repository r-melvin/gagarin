// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu104_b_methods.h"

// FUNCTION: GAMEMD 0x53A0E0
// Branching.
int __cdecl FUN_0053A0E0()
{
    return DAT_00A9FAB4 != 0 || DAT_00A9FAB8 > 0;
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0xA9FAB8
int DAT_00A9FAB8;
// END defined globals
