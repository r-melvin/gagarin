// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Every entry point and stored constant below was read off the user's own
//   retail gamemd.exe v1.001 with the local Ghidra CLI.
//
// Four seven-byte constant stores.
//
// `MOV dword ptr [ECX],<imm32>; RET` and nothing else: the whole function
// writes one constant over the object's first dword. Two of the four store
// zero (clearing a head pointer) and two store a vtable address (seating a
// base class's virtual table without any further construction work).
//
// Reviewed in the batch forty-one pass
// (the free-`__fastcall`-with-a-receiver debt) and deliberately LEFT as free
// functions. Converting would cost nothing in bytes — a member spelled
// `__fastcall` keeps the receiver in ECX and the first explicit argument in
// EDX — but `ConstStoreObject` is not one recovered class: it is four separate leaves spread from 0x5D8FC0 to 0x7ACBD0, modelled against one
// shared layout because the extraction proved the layout identical, not
// because they are one type. Declaring them members of a single struct would
// assert a class identity the evidence does not establish, which batch
// forty-one explicitly rules out. Each receiver's true class is undetermined.
#ifndef GG_MATCH_CORE_CONST_STORE_LEAF_SWEEP_H
#define GG_MATCH_CORE_CONST_STORE_LEAF_SWEEP_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// VTABLE: GAMEMD 0x7EF720
extern char VTABLE_007EF720[];
// VTABLE: GAMEMD 0x7F0954
extern char VTABLE_007F0954[];

struct ConstStoreObject
{
    void* Head;   // +0x0000  vtable pointer or list head, depending on the site
};
GG_STATIC_ASSERT(offsetof(ConstStoreObject, Head) == 0x0);

void FUN_005D8FC0(ConstStoreObject* self);   // FUNCTION: GAMEMD 0x5D8FC0
void FUN_00624130(ConstStoreObject* self);   // FUNCTION: GAMEMD 0x624130
void FUN_0065D660(ConstStoreObject* self);   // FUNCTION: GAMEMD 0x65D660
void FUN_007ACBD0(ConstStoreObject* self);   // FUNCTION: GAMEMD 0x7ACBD0

#endif  // GG_MATCH_CORE_CONST_STORE_LEAF_SWEEP_H
