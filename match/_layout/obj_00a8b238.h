// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra; shared address-named view (one definition for every TU that uses it).
#ifndef GG_MATCH__LAYOUT_OBJ_00A8B238_H_H
#define GG_MATCH__LAYOUT_OBJ_00A8B238_H_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_00A8B238
{
    // FUNCTION: GAMEMD 0x6970A0 (decl; reloc)
    Obj_00A8B238();
    // FUNCTION: GAMEMD 0x697840 (decl; reloc)
    ~Obj_00A8B238();
    // FUNCTION: GAMEMD 0x69B720 (decl; reloc) -- no arguments.
    int FUN_0069B720();
    // FUNCTION: GAMEMD 0x69B760 (decl; reloc) -- __thiscall, (value, flag), RET 8.
    void FUN_0069B760(int value, bool flag);
    // FUNCTION: GAMEMD 0x69B7E0 (decl; reloc) -- __thiscall, (value, flag), RET 8.
    void FUN_0069B7E0(int value, bool flag);
};

#endif
