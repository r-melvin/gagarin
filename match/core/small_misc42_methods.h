// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets, globals and call targets read numerically off the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI at 0x402940, 0x40E390 and
//   0x429500.
#ifndef GG_MATCH_CORE_SMALL_MISC42_METHODS_H
#define GG_MATCH_CORE_SMALL_MISC42_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

extern "C" void __cdecl FUN_007C8B3D(void* block);

// ---------------------------------------------------------------------------
// 0x402940 — one-shot module initialiser.
// ---------------------------------------------------------------------------
struct Module_00402940
{
    char _pad000[0x18];
    int  field_18;   // +0x0018
    char _pad01C[0x20 - 0x1C];
    char Tail[0x4];  // +0x0020
};
GG_STATIC_ASSERT(offsetof(Module_00402940, field_18) == 0x18);
GG_STATIC_ASSERT(offsetof(Module_00402940, Tail) == 0x20);

// FUNCTION: GAMEMD 0x4072C0 / 0x401000 — the two reset helpers, __fastcall.
void FUN_004072C0(void* part);
void FUN_00401000(void* part);

extern Module_00402940* DAT_00815E98;   // GLOBAL: GAMEMD 0x815E98
extern void*            DAT_0087DE30;   // GLOBAL: GAMEMD 0x87DE30
extern int              DAT_0087DE2C;   // GLOBAL: GAMEMD 0x87DE2C

// FUNCTION: GAMEMD 0x402940
int __cdecl FUN_00402940();

// ---------------------------------------------------------------------------
// 0x429500 — a COM accessor: `this` on the stack, an HRESULT back.
//
// `RET 8` with nothing in ECX and the out-pointer at [ESP+0xC] makes this a
// __stdcall method; the two HRESULTs are 0x80004003 (E_POINTER) for a null
// destination and zero for success.
//
// The reading is a base counter at +0x61C, plus - while the timer word at
// +0x614 is not -1 - the elapsed span since it started.
// ---------------------------------------------------------------------------
struct Timer_00429500
{
    int Started;   // +0x0000
    int Handle;    // +0x0004
};

// FUNCTION: GAMEMD 0x6C8C40 — reads the current tick from the timer's +0x4.
int FUN_006C8C40(void* handle);

struct Source_00429500
{
    char           _pad000[0x614];
    Timer_00429500 Timer;   // +0x0614
    int            Base;    // +0x061C
};
GG_STATIC_ASSERT(offsetof(Source_00429500, Timer) == 0x614);
GG_STATIC_ASSERT(offsetof(Source_00429500, Base) == 0x61C);

extern Source_00429500* DAT_00A8B230;   // GLOBAL: GAMEMD 0xA8B230

// FUNCTION: GAMEMD 0x429500
// PLACEHOLDER DELIBERATELY KEPT (RTTI sweep): 0x429500 is
// slot 7 (byte-off 0x1C) of ApplicationClass's own vtable 0x7E36D4 and appears
// in no other table, so ApplicationClass declares it. Same reason as 0x429420:
// the receiver is an untouched first stack argument of a free `__stdcall`, so
// there is nothing to hang the class name on without changing the signature.
long __stdcall FUN_00429500(void* self, int* value);

#endif  // GG_MATCH_CORE_SMALL_MISC42_METHODS_H
