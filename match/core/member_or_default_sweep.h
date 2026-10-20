// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Every entry point and default-object address below was read off the user's
//   own retail gamemd.exe v1.001 with the local Ghidra CLI.
//
// Four twelve-byte "the member, or the fallback singleton" accessors.
//
// `MOV EAX,[ECX]; TEST EAX,EAX; JNZ +5; MOV EAX,<global>; RET`. The object's
// first dword holds a pointer that may be null; when it is, the accessor hands
// back a fixed global object instead, so callers never see a null. Two of the
// four fall back to 0x889F64 and two to 0x887734.
//
// The positive arm has to be written first: spelled as `if (p == 0) return
// <global>; return p;` cl lays the constant load ahead of the test and the
// bytes diverge from the first instruction.
//
// Reviewed against docs/matching_methodology_and_toolchain.md batch forty-one
// (the free-`__fastcall`-with-a-receiver debt) and deliberately LEFT as free
// functions. Converting would cost nothing in bytes — a member spelled
// `__fastcall` keeps the receiver in ECX and the first explicit argument in
// EDX — but `DefaultingHolder` is not one recovered class: it is four separate accessors in two widely separated pairs (0x7B54xx and 0x7B71xx), modelled against one
// shared layout because the extraction proved the layout identical, not
// because they are one type. Declaring them members of a single struct would
// assert a class identity the evidence does not establish, which batch
// forty-one explicitly rules out. Each receiver's true class is undetermined.
#ifndef GG_MATCH_CORE_MEMBER_OR_DEFAULT_SWEEP_H
#define GG_MATCH_CORE_MEMBER_OR_DEFAULT_SWEEP_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0x887734
extern char GLOBAL_00887734[];
// GLOBAL: GAMEMD 0x889F64
extern char GLOBAL_00889F64[];

struct DefaultingHolder
{
    void* Object;   // +0x0000  may be null; the global stands in when it is
};
GG_STATIC_ASSERT(offsetof(DefaultingHolder, Object) == 0x0);

void* __fastcall FUN_007B5400(DefaultingHolder* self);   // FUNCTION: GAMEMD 0x7B5400
void* __fastcall FUN_007B5440(DefaultingHolder* self);   // FUNCTION: GAMEMD 0x7B5440
void* __fastcall FUN_007B7100(DefaultingHolder* self);   // FUNCTION: GAMEMD 0x7B7100
void* __fastcall FUN_007B7140(DefaultingHolder* self);   // FUNCTION: GAMEMD 0x7B7140

#endif  // GG_MATCH_CORE_MEMBER_OR_DEFAULT_SWEEP_H
