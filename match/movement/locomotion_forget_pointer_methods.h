// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Found by sweeping the address run 0x70F600..0x710700 as raw bytes: this
//   entry sits behind an alignment pad and the Ghidra analysis does not list
//   it. Read numerically at 0x710410: four member pointers at +0x12C, +0x1D4,
//   +0x2C8 and +0x130 are each cleared when they equal the argument, all four
//   stores sharing one zeroed register, and the argument is then handed to
//   0x5F6DA0. The pop of the saved register is scheduled between the fourth
//   compare and its store, which is why the fourth test is written last.
#ifndef GG_MATCH_MOVEMENT_LOCOMOTION_FORGET_POINTER_METHODS_H
#define GG_MATCH_MOVEMENT_LOCOMOTION_FORGET_POINTER_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// FUNCTION: GAMEMD 0x5F6DA0 (decl; reloc) — the shared release helper.
void __stdcall FUN_005F6DA0(void* item);

struct Holder_00710410
{
    char  _pad000[0x12C];        // +0x0000
    void* RefA;                  // +0x012C
    void* RefD;                  // +0x0130
    char  _pad134[0x1D4 - 0x134];
    void* RefB;                  // +0x01D4
    char  _pad1D8[0x2C8 - 0x1D8];
    void* RefC;                  // +0x02C8

    // FUNCTION: GAMEMD 0x710410
    void FUN_00710410(void* item);
};
GG_STATIC_ASSERT(offsetof(Holder_00710410, RefA) == 0x12C);
GG_STATIC_ASSERT(offsetof(Holder_00710410, RefD) == 0x130);
GG_STATIC_ASSERT(offsetof(Holder_00710410, RefB) == 0x1D4);
GG_STATIC_ASSERT(offsetof(Holder_00710410, RefC) == 0x2C8);

#endif  // GG_MATCH_MOVEMENT_LOCOMOTION_FORGET_POINTER_METHODS_H
