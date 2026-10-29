// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets and constants read numerically off the user's retail gamemd.exe
//   v1.001 via the local Ghidra CLI at 0x401000.
//
// Arm three timers — the object itself, and the ones embedded at +0x28 and
// +0x50 — then configure all three, then set the first one's level.
//
// The order is not grouped by timer: all three arms run, then all three
// configures, and the two sub-objects' addresses are computed once and held
// across the lot. The final call is a tail `JMP`, so it is a free __fastcall
// function while the others are ordinary calls.
#ifndef GG_MATCH_CORE_TRIPLE_TIMER_INIT_METHODS_H
#define GG_MATCH_CORE_TRIPLE_TIMER_INIT_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Timer_00401000
{
    // Retail tests the low flag byte at 0x4010A0 and clears the DWORD
    // at 0x401170; both accesses begin at offset zero.
    union {
        unsigned char Flags;    // +0x0000  bit 1 = running
        unsigned int  Flags32;  // +0x0000
    };
    unsigned int Value;       // +0x0004  16.16 fixed point
    union { unsigned char Flags2; unsigned Target; }; // +0x08
    int unknown_0C;
    unsigned __int64 unknown_10;
    __int64 unknown_18;
    char unknown_20[8];
};
GG_STATIC_ASSERT(offsetof(Timer_00401000, Flags32) == 0);
GG_STATIC_ASSERT(sizeof(((Timer_00401000*)0)->Flags32) == 4);
GG_STATIC_ASSERT(offsetof(Timer_00401000, Value) == 0x4);
GG_STATIC_ASSERT(offsetof(Timer_00401000, Target) == 8);
GG_STATIC_ASSERT(offsetof(Timer_00401000, unknown_0C) == 0xC);
GG_STATIC_ASSERT(offsetof(Timer_00401000, unknown_10) == 0x10);
GG_STATIC_ASSERT(offsetof(Timer_00401000, unknown_18) == 0x18);
GG_STATIC_ASSERT(sizeof(Timer_00401000) == 0x28);

// FUNCTION: GAMEMD 0x407100 — arm, __fastcall with the period in EDX.
void FUN_00407100(Timer_00401000* timer, int period);
// FUNCTION: GAMEMD 0x4071A0 — configure, __fastcall with two more on the stack.
void FUN_004071A0(Timer_00401000* timer, int value, int a, int b);
// FUNCTION: GAMEMD 0x407150 — set the level, reached by `JMP`.
void FUN_00407150(Timer_00401000* timer, int level);

struct Obj_00401000
{
    // FUNCTION: GAMEMD 0x4010A0 (decl)
    int FUN_004010A0() const;
    // FUNCTION: GAMEMD 0x401170 (decl)
    void FUN_00401170();
    Timer_00401000 First;    // +0x0000
    Timer_00401000 Second;   // +0x0028
    Timer_00401000 Third;    // +0x0050
};
GG_STATIC_ASSERT(offsetof(Obj_00401000, First) == 0);
GG_STATIC_ASSERT(offsetof(Obj_00401000, Second) == 0x28);
GG_STATIC_ASSERT(offsetof(Obj_00401000, Third) == 0x50);

// FUNCTION: GAMEMD 0x4071C0 — reset, __thiscall (ECX only, no argument).
int FUN_004071C0(Timer_00401000* timer);

// FUNCTION: GAMEMD 0x401000
void FUN_00401000(Obj_00401000* self);
// FUNCTION: GAMEMD 0x4010C0
void FUN_004010C0(Obj_00401000* self, Obj_00401000* other);

// FUNCTION: GAMEMD 0x401170 — re-arm the group's first timer; __thiscall in
// retail, spelled __fastcall here (receiver in ECX, no argument).
void FUN_00401170(Obj_00401000* self);

// FUNCTION: GAMEMD 0x401190 — derive the playback rate from the timer group and
// the caller's setting; __fastcall (group in ECX, setting in EDX).
int FUN_00401190(Obj_00401000* self, int value);

#endif  // GG_MATCH_CORE_TRIPLE_TIMER_INIT_METHODS_H
