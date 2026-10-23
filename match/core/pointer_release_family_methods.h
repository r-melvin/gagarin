// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Read numerically off the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI at 0x7B5340 and the remaining duplicate helpers: release the block held
//   at +0 and forget it. The helpers are byte-identical apart from the call
//   relocation, which resolves to the CRT free in every one.
//
// Reviewed in the batch forty-one pass
// (the free-`__fastcall`-with-a-receiver debt) and deliberately LEFT as free
// functions. Converting would cost nothing in bytes — a member spelled
// `__fastcall` keeps the receiver in ECX and the first explicit argument in
// EDX — but `Holder_007B46F0` is not one recovered class: it is four separate releases spread from 0x7B46F0 to 0x7B7040, modelled against one
// shared layout because the extraction proved the layout identical, not
// because they are one type. The recovered 0x7B46F0 Wstring destructor now
// lives in string_class_methods.cpp. Declaring the remaining helpers members
// of a single struct would
// assert a class identity the evidence does not establish, which batch
// forty-one explicitly rules out. Each receiver's true class is undetermined.
#ifndef GG_MATCH_CORE_POINTER_RELEASE_FAMILY_METHODS_H
#define GG_MATCH_CORE_POINTER_RELEASE_FAMILY_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// LIBRARY: GAMEMD 0x7C8B3D (decl; reloc) — CRT free.
extern "C" void __cdecl gg_free(void* block);

struct Holder_007B46F0
{
    void* Block;  // +0x0000
};
GG_STATIC_ASSERT(offsetof(Holder_007B46F0, Block) == 0x0);

// FUNCTION: GAMEMD 0x007B5340
void FUN_00007B5340(Holder_007B46F0* self);
// FUNCTION: GAMEMD 0x007B6760
void FUN_00007B6760(Holder_007B46F0* self);
// FUNCTION: GAMEMD 0x007B7040
void FUN_00007B7040(Holder_007B46F0* self);

#endif  // GG_MATCH_CORE_POINTER_RELEASE_FAMILY_METHODS_H
