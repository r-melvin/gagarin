// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra; shared address-named view (one definition for every TU that uses it).
#ifndef GG_MATCH_CORE_OBJ_0087E758_H_H
#define GG_MATCH_CORE_OBJ_0087E758_H_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_0087E758
{
    int Flags;   // +0x0000

    // FUNCTION: GAMEMD 0x4072B0 (decl; reloc) -- __thiscall getter.
    unsigned int FUN_004072B0() const;
    // FUNCTION: GAMEMD 0x407150 (decl; reloc) -- __fastcall: this=ECX, value=EDX.
    void __fastcall FUN_00407150(int value);
};

#endif
