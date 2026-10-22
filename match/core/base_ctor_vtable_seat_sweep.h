// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Every entry point, base-constructor target and vtable constant below was
//   read off the user's own retail gamemd.exe v1.001 with the local Ghidra CLI.
//
// Five eighteen-byte derived constructors.
//
// MSVC's constructor for a derived class that adds no members of its own: run
// the base constructor on `this`, overwrite the vtable pointer the base just
// installed with the derived one, and return `this`. Eighteen bytes:
// `PUSH ESI; MOV ESI,ECX; CALL <base ctor>; MOV [ESI],<vtable>; MOV EAX,ESI;
// POP ESI; RET`.
//
// The `this` return is load-bearing: written as `void` the trailing
// `MOV EAX,ESI` disappears.
//
// Reviewed in the batch forty-one pass
// (the free-`__fastcall`-with-a-receiver debt) and deliberately LEFT as free
// functions. Converting would cost nothing in bytes — a member spelled
// `__fastcall` keeps the receiver in ECX and the first explicit argument in
// EDX — but `the receiver struct` is not one recovered class: it is five separate constructors on different hierarchies, modelled against one
// shared layout because the extraction proved the layout identical, not
// because they are one type. Declaring them members of a single struct would
// assert a class identity the evidence does not establish, which batch
// forty-one explicitly rules out. Each receiver's true class is undetermined.
#ifndef GG_MATCH_CORE_BASE_CTOR_VTABLE_SEAT_SWEEP_H
#define GG_MATCH_CORE_BASE_CTOR_VTABLE_SEAT_SWEEP_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// VTABLE: GAMEMD 0x7EBFA4
extern char VTABLE_007EBFA4[];
// VTABLE: GAMEMD 0x7F6F34
extern char VTABLE_007F6F34[];
// VTABLE: GAMEMD 0x7F7024
extern char VTABLE_007F7024[];
// VTABLE: GAMEMD 0x7F71C4
extern char VTABLE_007F71C4[];
// VTABLE: GAMEMD 0x7F7624
extern char VTABLE_007F7624[];

void FUN_00624110(void* self);   // GAMEMD 0x624110  base constructor
void FUN_0065D430(void* self);   // GAMEMD 0x65D430  base constructor

// The five touch only the vtable pointer at +0.
struct CtorSeatObject
{
    void* Vtbl;   // +0x0000
};
GG_STATIC_ASSERT(offsetof(CtorSeatObject, Vtbl) == 0x0);

CtorSeatObject* FUN_00765C70(CtorSeatObject* self);   // FUNCTION: GAMEMD 0x765C70
CtorSeatObject* FUN_007670D0(CtorSeatObject* self);   // FUNCTION: GAMEMD 0x7670D0
CtorSeatObject* FUN_0076A7C0(CtorSeatObject* self);   // FUNCTION: GAMEMD 0x76A7C0
CtorSeatObject* FUN_0076BC60(CtorSeatObject* self);   // FUNCTION: GAMEMD 0x76BC60
CtorSeatObject* FUN_0077D1D0(CtorSeatObject* self);   // FUNCTION: GAMEMD 0x77D1D0

#endif  // GG_MATCH_CORE_BASE_CTOR_VTABLE_SEAT_SWEEP_H
