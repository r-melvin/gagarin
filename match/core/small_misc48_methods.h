// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets, IAT slots, globals and call targets read numerically off the
//   user's retail gamemd.exe v1.001 via the local Ghidra CLI at 0x406570,
//   0x407FB0 and 0x409360.
#ifndef GG_MATCH_CORE_SMALL_MISC48_METHODS_H
#define GG_MATCH_CORE_SMALL_MISC48_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// ---------------------------------------------------------------------------
// 0x406570 — record a flag word and arm or clear two latches from two of its
// bits. Both arguments arrive in registers (`TEST DL,0x20` before anything is
// spilled), so this is __fastcall.
//
// Each latch is set to 1 only if it is currently zero, and cleared outright
// when its bit is absent. Retail borrows ESI for the first of those two tests -
// `PUSH ESI; MOV ESI,[ECX+0x138]; TEST ESI,ESI; POP ESI` - which is VC6's own
// choice under the register pressure here, not something the source asks for.
// ---------------------------------------------------------------------------
struct Obj_00406570
{
    char _pad000[0x10];
    int  Flags;      // +0x0010
    char _pad014[0x138 - 0x14];
    int  LatchA;     // +0x0138
    int  LatchB;     // +0x013C

    // A member, not a free function taking the object: the object is in ECX
    // and the flag word in EDX, which is `__fastcall` on a member.
    // FUNCTION: GAMEMD 0x406570
    void __fastcall FUN_00406570(int flags);
};
GG_STATIC_ASSERT(offsetof(Obj_00406570, Flags) == 0x10);
GG_STATIC_ASSERT(offsetof(Obj_00406570, LatchA) == 0x138);
GG_STATIC_ASSERT(offsetof(Obj_00406570, LatchB) == 0x13C);

// ---------------------------------------------------------------------------
// 0x407FB0 — on the first entry only, run one state transition under the
// critical section at 0x87E7F8, then count the entry.
//
// The flag rewrite is a single load, two ALU ops and one store, so it is one
// expression rather than two updates - the opposite of the 0x402650 case.
// ---------------------------------------------------------------------------
struct CriticalSection_00407FB0 { char Opaque[0x18]; };

extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(CriticalSection_00407FB0*);  // IAT 0x7E11E8
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(CriticalSection_00407FB0*);  // IAT 0x7E11EC

extern CriticalSection_00407FB0 DAT_0087E7F8;   // GLOBAL: GAMEMD 0x87E7F8

// FUNCTION: GAMEMD 0x402600 — the state transition, __fastcall.
void __fastcall FUN_00402600(void* subject);

struct Obj_00407FB0
{
    char  _pad000[0xC];
    int   Flags;    // +0x000C
    char  _pad010[0x14 - 0x10];
    void* Subject;  // +0x0014
    char  _pad018[0x80 - 0x18];
    int   Entered;  // +0x0080

    // Both are members; the object is the only register argument, so these are
    // ordinary __thiscall. Declared ascending by retail address.
    // FUNCTION: GAMEMD 0x407FB0
    void FUN_00407FB0();
    // FUNCTION: GAMEMD 0x408000 — the counterpart of 0x407FB0: floor the entry
    // count back down and, once it reaches zero, run the reverse transition
    // under the same critical section. The flag rewrite swaps bit 1 for bit 0,
    // the mirror of 0x407FB0's bit 0 for bit 1.
    void FUN_00408000();
};
GG_STATIC_ASSERT(offsetof(Obj_00407FB0, Flags) == 0xC);
GG_STATIC_ASSERT(offsetof(Obj_00407FB0, Subject) == 0x14);
GG_STATIC_ASSERT(offsetof(Obj_00407FB0, Entered) == 0x80);

// FUNCTION: GAMEMD 0x402650 — the reverse transition, __fastcall.
void __fastcall FUN_00402650(void* subject);

// ---------------------------------------------------------------------------
// 0x409360 — pick the timing back end.
//
// If the performance counter has a frequency, cache frequency/1000 as a 64-bit
// global and point the reader at 0x4093C0; otherwise point it at 0x4093F0. The
// division is the CRT's 64-bit helper at 0x7C92D0, reached with the dividend's
// two halves and then the divisor's - i.e. an ordinary `/ 1000` on an `__int64`.
// ---------------------------------------------------------------------------
extern "C" __declspec(dllimport) int __stdcall QueryPerformanceFrequency(__int64*);  // IAT 0x7E11D8

extern __int64 DAT_0087E828;   // GLOBAL: GAMEMD 0x87E828 — ticks per millisecond
extern void*   DAT_0087E848;   // GLOBAL: GAMEMD 0x87E848 — the selected reader

// FUNCTION: GAMEMD 0x4093C0 / 0x4093F0 — the two readers.
void __fastcall FUN_004093C0();
void __fastcall FUN_004093F0();

// FUNCTION: GAMEMD 0x409360
void __cdecl FUN_00409360();

#endif  // GG_MATCH_CORE_SMALL_MISC48_METHODS_H
