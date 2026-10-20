// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Offsets, argument slots and the shared callee read numerically off the
//   user's retail gamemd.exe v1.001 via the local Ghidra CLI at 0x433EF0 and
//   0x4340A0.
//
// Two forwarders onto 0x433CF0. Both branch on the byte at +0x40: when it is
// set the call is bracketed by writing 2 then 1 to the state word at +0x2C,
// and when it is clear the same call is made bare. Retail emits the call twice
// rather than sharing it, so both arms are written out.
#ifndef GG_MATCH_CORE_GUARDED_FORWARD2_METHODS_H
#define GG_MATCH_CORE_GUARDED_FORWARD2_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Forwarder_00433EF0
{
    char _pad000[0x2C];
    int  State;   // +0x002C
    char _pad030[0x40 - 0x30];
    char Guard;   // +0x0040

    // FUNCTION: GAMEMD 0x433CF0 — the shared callee, __thiscall with four
    // stack arguments.
    void FUN_00433CF0(void* first, void* second, int third, void* fourth);

    // FUNCTION: GAMEMD 0x433EF0
    //
    // Two arguments in, four out: the second argument's own stack home is
    // reused as the out-parameter cell, which is why retail takes its address
    // (`LEA ECX,[ESP+0x10]`) *and* passes its original value, then reads the
    // cell back as the return value.
    void* FUN_00433EF0(void* first, void* second);

    // FUNCTION: GAMEMD 0x4340A0
    //
    // The four-argument form, passed straight through with nothing returned.
    void FUN_004340A0(void* first, void* second, int third, void* fourth);
};
GG_STATIC_ASSERT(offsetof(Forwarder_00433EF0, State) == 0x2C);
GG_STATIC_ASSERT(offsetof(Forwarder_00433EF0, Guard) == 0x40);

#endif  // GG_MATCH_CORE_GUARDED_FORWARD2_METHODS_H
