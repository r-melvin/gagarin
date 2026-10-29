// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra; shared address-named view (one definition for every TU that uses it).
#ifndef GG_MATCH__LAYOUT_CD_004790E0_H_H
#define GG_MATCH__LAYOUT_CD_004790E0_H_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct CD_004790E0
{
    virtual bool FUN_004790E0(int value);
    unsigned int unknown_04;

    // ABI call view for the direct callee 0x4A8270: ECX is this and one
    // dword is passed on the stack. This declaration does not assign that
    // address to a CD member in the recovered class model.
    // FUNCTION: GAMEMD 0x004A8270 (call target declaration; owner unresolved)
    bool FUN_004A8270(int value);
};
GG_STATIC_ASSERT(offsetof(CD_004790E0, unknown_04) == 4);
#endif
