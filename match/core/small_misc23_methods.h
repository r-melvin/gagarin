// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI. None is bound by YRpp or the
//   seed map.
#ifndef GG_MATCH_CORE_SMALL_MISC23_METHODS_H
#define GG_MATCH_CORE_SMALL_MISC23_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "intrusive_list_methods.h"

extern "C" double __cdecl FUN_004CAC40b(double v);   // GAMEMD 0x4CAC40

// A three-int vector. The components are widened to double for the helper
// (`FILD`), and the result narrowed back on return - which is why the function
// ends in a tail jump to the CRT's float-to-int conversion rather than a RET.
struct Triple3iLen
{
    int a, b, c;

    // FUNCTION: GAMEMD 0x41C380
    int FUN_0041C380() const;
};

struct Owner_00408E20 { int Count; char _pad04[0x10 - 0x04]; int Flags; int Total; };

struct Obj_00408E20
{
    char              _pad00[0x1C];
    int               unknown_1C;   // +0x001C
    char              _pad20[0x30 - 0x20];
    Owner_00408E20*   Owner;        // +0x0030

    // FUNCTION: GAMEMD 0x408E20
    void FUN_00408E20();
};
GG_STATIC_ASSERT(offsetof(Obj_00408E20, Owner) == 0x30);
GG_STATIC_ASSERT(offsetof(Owner_00408E20, Total) == 0x14);

#endif  // GG_MATCH_CORE_SMALL_MISC23_METHODS_H
