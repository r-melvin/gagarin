// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Every entry point and offset below was read off the user's own retail
//   gamemd.exe v1.001 with the local Ghidra CLI: the held pointer at
//   `[ECX+0x10]` (`MOV EAX,[ECX+0x10]`) and one dereference of each side
//   (`MOV EAX,[EAX]`, `CMP EAX,[ECX]`).
//
// Five identical 27-byte identity tests.
//
// The object holds a pointer at +0x10. The test says: that pointer is not
// null, and the dword it points at equals the dword the argument points at --
// the two handles refer to the same underlying thing. All five instances are
// byte-for-byte identical, relocations included.
//
// Only one dereference per side. Spelled with two (`**self->Held == **other`)
// cl emits an extra load on each side and the body diverges after the fourth
// instruction.
//
// Reviewed against docs/matching_methodology_and_toolchain.md batch forty-one
// (the free-`__fastcall`-with-a-receiver debt) and deliberately LEFT as free
// functions. Converting would cost nothing in bytes — a member spelled
// `__fastcall` keeps the receiver in ECX and the first explicit argument in
// EDX — but `HandleHolder` is not one recovered class: it is five separate entry points spread from 0x52B4D0 to 0x746EA0, modelled against one
// shared layout because the extraction proved the layout identical, not
// because they are one type. Declaring them members of a single struct would
// assert a class identity the evidence does not establish, which batch
// forty-one explicitly rules out. Each receiver's true class is undetermined.
#ifndef GG_MATCH_CORE_SAME_OBJECT_TEST_SWEEP_H
#define GG_MATCH_CORE_SAME_OBJECT_TEST_SWEEP_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct HandleHolder
{
    char   _pad000[0x10];   // +0x0000
    void** Held;            // +0x0010
};
GG_STATIC_ASSERT(offsetof(HandleHolder, Held) == 0x10);

bool __fastcall FUN_0052B4D0(HandleHolder* self, int, void** other);   // FUNCTION: GAMEMD 0x52B4D0
bool __fastcall FUN_0052B600(HandleHolder* self, int, void** other);   // FUNCTION: GAMEMD 0x52B600
bool __fastcall FUN_0055F6C0(HandleHolder* self, int, void** other);   // FUNCTION: GAMEMD 0x55F6C0
bool __fastcall FUN_00724FA0(HandleHolder* self, int, void** other);   // FUNCTION: GAMEMD 0x724FA0
bool __fastcall FUN_00746EA0(HandleHolder* self, int, void** other);   // FUNCTION: GAMEMD 0x746EA0

#endif  // GG_MATCH_CORE_SAME_OBJECT_TEST_SWEEP_H
