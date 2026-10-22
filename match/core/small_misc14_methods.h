// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI. None is bound by YRpp.
#ifndef GG_MATCH_CORE_SMALL_MISC14_METHODS_H
#define GG_MATCH_CORE_SMALL_MISC14_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// A __thiscall callback: the element goes in ECX and nothing on the stack.
typedef void (* ElemFn)(void* elem);

// FUNCTION: GAMEMD 0x4068F0 — apply the callback across a strided array,
// walking forwards. The trip count is taken as `count - 1` and tested for
// negative, so a count of zero does nothing rather than wrapping.
void __stdcall FUN_004068F0(char* base, int stride, int count, ElemFn fn);

struct Flagged_00431060 { char _pad[0xC]; unsigned char at0C; };

struct Obj_00431060
{
    Flagged_00431060* Slots[24];   // +0x0000 .. +0x005F
    int               unknown_60;  // +0x0060

    // FUNCTION: GAMEMD 0x431060
    void FUN_00431060();
};
GG_STATIC_ASSERT(offsetof(Obj_00431060, unknown_60) == 0x60);

#endif  // GG_MATCH_CORE_SMALL_MISC14_METHODS_H
