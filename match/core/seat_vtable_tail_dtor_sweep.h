// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Every entry point, vtable constant and jump target below was read off the
//   user's own retail gamemd.exe v1.001 with the local Ghidra CLI.
//
// Seven eleven-byte base destructors.
//
// The shape is MSVC's non-deleting destructor for a derived class with nothing
// of its own to tear down: store the base class's vtable pointer over the
// object's first dword, then tail-jump into the base destructor, which does the
// actual work and returns to the original caller. Eleven bytes exactly:
// `MOV dword ptr [ECX],<vtable>; JMP <base dtor>`.
//
// The tail jump falls out of writing the base call last in a `void __fastcall`
// function of the same signature; cl emits `JMP` rather than `CALL`/`RET`.
//
// Reviewed in the batch forty-one pass
// (the free-`__fastcall`-with-a-receiver debt) and deliberately LEFT as free
// functions. Converting would cost nothing in bytes — a member spelled
// `__fastcall` keeps the receiver in ECX and the first explicit argument in
// EDX — but `SeatDtorObject` is not one recovered class: it is seven separate destructors spread from 0x535A60 to 0x77D1F0, modelled against one
// shared layout because the extraction proved the layout identical, not
// because they are one type. Declaring them members of a single struct would
// assert a class identity the evidence does not establish, which batch
// forty-one explicitly rules out. Each receiver's true class is undetermined.
#ifndef GG_MATCH_CORE_SEAT_VTABLE_TAIL_DTOR_SWEEP_H
#define GG_MATCH_CORE_SEAT_VTABLE_TAIL_DTOR_SWEEP_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// Only the vtable addresses matter here; no slot of any of them is called.
// VTABLE: GAMEMD 0x7E1668
extern char VTABLE_007E1668[];
// VTABLE: GAMEMD 0x7F7014
extern char VTABLE_007F7014[];
// VTABLE: GAMEMD 0x7F7024
extern char VTABLE_007F7024[];
// VTABLE: GAMEMD 0x7F7040
extern char VTABLE_007F7040[];
// VTABLE: GAMEMD 0x7F7060
extern char VTABLE_007F7060[];
// VTABLE: GAMEMD 0x7F71C4
extern char VTABLE_007F71C4[];
// VTABLE: GAMEMD 0x7F7624
extern char VTABLE_007F7624[];

void FUN_00431B80(void* self);   // GAMEMD 0x431B80  base destructor
void FUN_00624130(void* self);   // GAMEMD 0x624130  base destructor
void FUN_0065D460(void* self);   // GAMEMD 0x65D460  base destructor
void FUN_0065D660(void* self);   // GAMEMD 0x65D660  base destructor

// Every one of the seven touches only the vtable pointer at +0.
struct SeatDtorObject
{
    void* Vtbl;   // +0x0000
};
GG_STATIC_ASSERT(offsetof(SeatDtorObject, Vtbl) == 0x0);

void FUN_00535A60(SeatDtorObject* self);   // FUNCTION: GAMEMD 0x535A60
void FUN_00767300(SeatDtorObject* self);   // FUNCTION: GAMEMD 0x767300

#endif  // GG_MATCH_CORE_SEAT_VTABLE_TAIL_DTOR_SWEEP_H
